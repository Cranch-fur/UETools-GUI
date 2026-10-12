#pragma once
#include <Windows.h>

#include <string>
#include <vector>
#include <cstdint>






namespace Injector
{
    enum class E_Architecture
    {
        Unknown,
        x86,
        x64
    };

    struct ProcessInfo
    {
        uint32_t processId = 0;
        std::wstring processName;    // Executable file name (e.g. "LiesOfP-Win64-Shipping.exe").
        std::wstring executablePath; // Full path to the executable (empty if access was denied).
        std::wstring windowTitle;    // Title of the process main window (empty if none).

        E_Architecture architecture = E_Architecture::Unknown;
        bool hasVisibleWindow = false;      // Has a top-level visible window (shows up in taskbar / Alt+Tab).
        bool looksLikeUnrealEngine = false; // Heuristic (UnrealWindow class or \Binaries\Win64\ path).
        bool isInjected = false;            // Target library is currently loaded in this process (filled by the UI).
    };

    enum class E_InjectionResult
    {
        Success,
        AlreadyInjected,
        ProcessNotFound,
        AccessDenied,            // OpenProcess failed (missing rights / elevation).
        ArchitectureMismatch,    // Injector is x64, target process is x86.
        LibraryNotFound,         // DLL file doesn't exist on disk.
        AllocationFailed,
        WriteFailed,
        RemoteThreadFailed,
        LoadLibraryFailed,       // Remote LoadLibraryW returned null (DLL present but failed to load).
        VerificationFailed       // Remote thread finished but module isn't present in target.
    };

    /* Architecture this injector was compiled for (determines which processes can be injected into). */
    constexpr E_Architecture SelfArchitecture = sizeof(void*) == 8 ? E_Architecture::x64 : E_Architecture::x86;

    const char* ResultToString(E_InjectionResult result);

    /* Snapshot of currently running processes. */
    std::vector<ProcessInfo> GetProcesses();

    /* Checks if a module with given file name is already loaded in the target process. */
    bool IsModuleLoaded(uint32_t processId, const std::wstring& moduleName);

    /* Injects a library into target process via remote LoadLibraryW (as Cheat Engine / System Informer do). */
    E_InjectionResult Inject(uint32_t processId, const std::wstring& libraryPath);
}
