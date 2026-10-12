#include "Injector.h"

#include <TlHelp32.h>
#include <filesystem>
#include <algorithm>






namespace
{
    /* Determines target process architecture through IsWow64Process2 (reliable on native x64). */
    Injector::E_Architecture GetProcessArchitecture(HANDLE hProcess)
    {
        USHORT processMachine = IMAGE_FILE_MACHINE_UNKNOWN;
        USHORT nativeMachine = IMAGE_FILE_MACHINE_UNKNOWN;

        if (IsWow64Process2(hProcess, &processMachine, &nativeMachine) == FALSE)
        {
            return Injector::E_Architecture::Unknown;
        }

        /* Process running under WOW64 reports its own (32-bit) machine; native process reports UNKNOWN. */
        if (processMachine == IMAGE_FILE_MACHINE_I386)
        {
            return Injector::E_Architecture::x86;
        }

        if (processMachine == IMAGE_FILE_MACHINE_UNKNOWN)
        {
            /* Not WOW64, so it matches the native machine of the OS. */
            return (nativeMachine == IMAGE_FILE_MACHINE_I386) ? Injector::E_Architecture::x86 : Injector::E_Architecture::x64;
        }

        return Injector::E_Architecture::x64;
    }


    std::wstring GetProcessExecutablePath(HANDLE hProcess)
    {
        wchar_t buffer[MAX_PATH] = {};
        DWORD size = static_cast<DWORD>(std::size(buffer));

        if (QueryFullProcessImageNameW(hProcess, 0, buffer, &size) == FALSE)
        {
            return std::wstring();
        }

        return std::wstring(buffer, size);
    }


    std::wstring ToLower(const std::wstring& text)
    {
        std::wstring outText = text;
        std::transform(outText.begin(), outText.end(), outText.begin(), [](wchar_t c) { return static_cast<wchar_t>(towlower(c)); });
        return outText;
    }


    struct WindowSearch
    {
        DWORD processId = 0;
        std::wstring title;
        bool isUnrealWindow = false;
        bool hasVisibleWindow = false;
    };

    BOOL CALLBACK EnumWindowCallback(HWND hWindow, LPARAM lParam)
    {
        WindowSearch* search = reinterpret_cast<WindowSearch*>(lParam);

        DWORD windowProcessId = 0;
        GetWindowThreadProcessId(hWindow, &windowProcessId);

        if (windowProcessId != search->processId)
        {
            return TRUE;
        }

        if (IsWindowVisible(hWindow) == FALSE)
        {
            return TRUE;
        }

        /* Top-level application window (not an owned popup / tool window): what shows in the taskbar. */
        const LONG exStyle = static_cast<LONG>(GetWindowLongPtrW(hWindow, GWL_EXSTYLE));
        if ((exStyle & WS_EX_TOOLWINDOW) == 0 && GetAncestor(hWindow, GA_ROOTOWNER) == hWindow && GetWindowTextLengthW(hWindow) > 0)
        {
            search->hasVisibleWindow = true;
        }

        wchar_t className[128] = {};
        if (GetClassNameW(hWindow, className, static_cast<int>(std::size(className))) != 0)
        {
            if (wcscmp(className, L"UnrealWindow") == 0)
            {
                search->isUnrealWindow = true;
            }
        }

        if (search->title.empty())
        {
            wchar_t title[256] = {};
            if (GetWindowTextW(hWindow, title, static_cast<int>(std::size(title))) != 0)
            {
                search->title = title;
            }
        }

        return TRUE; // Keep enumerating: title & UnrealWindow may belong to different windows of the process.
    }

    WindowSearch FindMainWindow(DWORD processId)
    {
        WindowSearch search;
        search.processId = processId;

        EnumWindows(EnumWindowCallback, reinterpret_cast<LPARAM>(&search));
        return search;
    }


    bool PathLooksLikeUnrealEngine(const std::wstring& executablePath)
    {
        const std::wstring lowerPath = ToLower(executablePath);

        return lowerPath.find(L"\\binaries\\win64\\") != std::wstring::npos
            || lowerPath.find(L"\\binaries\\win32\\") != std::wstring::npos;
    }
}




const char* Injector::ResultToString(E_InjectionResult result)
{
    switch (result)
    {
        case E_InjectionResult::Success:              return "Injected successfully.";
        case E_InjectionResult::AlreadyInjected:      return "Library is already loaded in the target process.";
        case E_InjectionResult::ProcessNotFound:      return "Target process no longer exists.";
        case E_InjectionResult::AccessDenied:         return "Access denied. Try running the injector as administrator.";
        case E_InjectionResult::ArchitectureMismatch: return "Architecture mismatch (x64 injector can't inject into x86 process).";
        case E_InjectionResult::LibraryNotFound:      return "Library file wasn't found on disk.";
        case E_InjectionResult::AllocationFailed:     return "Failed to allocate memory in the target process.";
        case E_InjectionResult::WriteFailed:          return "Failed to write library path into the target process.";
        case E_InjectionResult::RemoteThreadFailed:   return "Failed to create a remote thread in the target process.";
        case E_InjectionResult::LoadLibraryFailed:    return "Target failed to load the library (check it matches the title).";
        case E_InjectionResult::VerificationFailed:   return "Remote thread finished, but the module isn't present in the target.";
        default:                                      return "Unknown result.";
    }
}




std::vector<Injector::ProcessInfo> Injector::GetProcesses()
{
    std::vector<ProcessInfo> outProcesses;

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        return outProcesses;
    }

    PROCESSENTRY32W entry = {};
    entry.dwSize = sizeof(entry);

    const DWORD currentProcessId = GetCurrentProcessId();

    if (Process32FirstW(hSnapshot, &entry))
    {
        do
        {
            if (entry.th32ProcessID == 0 || entry.th32ProcessID == currentProcessId) // Skip System Idle & injector itself.
            {
                continue;
            }

            ProcessInfo info;
            info.processId = entry.th32ProcessID;
            info.processName = entry.szExeFile;

            /* Limited query rights are enough for path & architecture and are usually granted without elevation. */
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, entry.th32ProcessID);
            if (hProcess != nullptr)
            {
                info.architecture = GetProcessArchitecture(hProcess);
                info.executablePath = GetProcessExecutablePath(hProcess);
                CloseHandle(hProcess);
            }

            const WindowSearch window = FindMainWindow(entry.th32ProcessID);
            info.windowTitle = window.title;
            info.hasVisibleWindow = window.hasVisibleWindow;
            info.looksLikeUnrealEngine = window.isUnrealWindow || PathLooksLikeUnrealEngine(info.executablePath);

            outProcesses.push_back(std::move(info));
        }
        while (Process32NextW(hSnapshot, &entry));
    }

    CloseHandle(hSnapshot);

    std::sort(outProcesses.begin(), outProcesses.end(), [](const ProcessInfo& a, const ProcessInfo& b)
        {
            /* Unreal Engine processes first, then alphabetically by name. */
            if (a.looksLikeUnrealEngine != b.looksLikeUnrealEngine)
                return a.looksLikeUnrealEngine;

            return ToLower(a.processName) < ToLower(b.processName);
        });

    return outProcesses;
}




bool Injector::IsModuleLoaded(uint32_t processId, const std::wstring& moduleName)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    const std::wstring targetName = ToLower(moduleName);

    MODULEENTRY32W entry = {};
    entry.dwSize = sizeof(entry);

    bool isLoaded = false;
    if (Module32FirstW(hSnapshot, &entry))
    {
        do
        {
            if (ToLower(entry.szModule) == targetName)
            {
                isLoaded = true;
                break;
            }
        }
        while (Module32NextW(hSnapshot, &entry));
    }

    CloseHandle(hSnapshot);
    return isLoaded;
}




Injector::E_InjectionResult Injector::Inject(uint32_t processId, const std::wstring& libraryPath)
{
    std::error_code errorCode;
    if (std::filesystem::exists(libraryPath, errorCode) == false)
    {
        return E_InjectionResult::LibraryNotFound;
    }

    /* Absolute path is used so the target resolves it regardless of its own working directory. */
    std::wstring absolutePath = std::filesystem::absolute(libraryPath, errorCode).wstring();
    if (absolutePath.empty())
    {
        absolutePath = libraryPath;
    }

    const std::wstring moduleName = std::filesystem::path(absolutePath).filename().wstring();
    if (IsModuleLoaded(processId, moduleName))
    {
        return E_InjectionResult::AlreadyInjected;
    }

    /* Full access is required to allocate, write and create a remote thread. */
    const DWORD accessRights = PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ;
    HANDLE hProcess = OpenProcess(accessRights, FALSE, processId);
    if (hProcess == nullptr)
    {
        return (GetLastError() == ERROR_ACCESS_DENIED) ? E_InjectionResult::AccessDenied : E_InjectionResult::ProcessNotFound;
    }

    const SIZE_T pathBytes = (absolutePath.size() + 1) * sizeof(wchar_t); // +1 for null terminator.

    /* Memory for the library path inside the target process. */
    void* remotePath = VirtualAllocEx(hProcess, nullptr, pathBytes, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (remotePath == nullptr)
    {
        CloseHandle(hProcess);
        return E_InjectionResult::AllocationFailed;
    }

    if (WriteProcessMemory(hProcess, remotePath, absolutePath.c_str(), pathBytes, nullptr) == FALSE)
    {
        VirtualFreeEx(hProcess, remotePath, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return E_InjectionResult::WriteFailed;
    }

    /*
        LoadLibraryW resides in kernel32, which is mapped at the same address in every process of the same
        architecture, so its address in the injector is valid as a remote thread entry point.
    */
    HMODULE hKernel32 = GetModuleHandleW(L"kernel32.dll");
    LPTHREAD_START_ROUTINE loadLibraryAddress = reinterpret_cast<LPTHREAD_START_ROUTINE>(GetProcAddress(hKernel32, "LoadLibraryW"));
    if (loadLibraryAddress == nullptr)
    {
        VirtualFreeEx(hProcess, remotePath, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return E_InjectionResult::RemoteThreadFailed;
    }

    HANDLE hThread = CreateRemoteThread(hProcess, nullptr, 0, loadLibraryAddress, remotePath, 0, nullptr);
    if (hThread == nullptr)
    {
        VirtualFreeEx(hProcess, remotePath, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return E_InjectionResult::RemoteThreadFailed;
    }

    WaitForSingleObject(hThread, INFINITE);

    /*
        Thread exit code holds the HMODULE returned by LoadLibraryW, but it's truncated to 32 bits on x64,
        so it's only used to tell "load failed" (0) from "loaded"; actual presence is verified via module list.
    */
    DWORD threadExitCode = 0;
    GetExitCodeThread(hThread, &threadExitCode);

    CloseHandle(hThread);
    VirtualFreeEx(hProcess, remotePath, 0, MEM_RELEASE);
    CloseHandle(hProcess);

    if (threadExitCode == 0)
    {
        return E_InjectionResult::LoadLibraryFailed;
    }

    /* Confirm the module is actually present (DLL could have detached itself, or exit code could be a false positive). */
    if (IsModuleLoaded(processId, moduleName) == false)
    {
        return E_InjectionResult::VerificationFailed;
    }

    return E_InjectionResult::Success;
}
