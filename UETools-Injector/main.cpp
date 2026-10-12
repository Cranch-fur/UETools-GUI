#include "Injector.h" // Includes <Windows.h>, must come before GL/gl.h.
#include "definitions.h"
#include "resource.h"

#include <string>
#include <vector>
#include <filesystem>
#include <unordered_set>
#include <algorithm>

#include "imgui.h"
#include "imgui_impl_win32.h"

#if defined(API_D3D11)
    #include "imgui_impl_dx11.h"
    #include <d3d11.h>

    #pragma comment(lib, "d3d11.lib")
#elif defined(API_OPENGL3)
    #include "imgui_impl_opengl3.h"
    #include <GL/gl.h>

    #pragma comment(lib, "opengl32.lib")
#endif

#pragma comment(lib, "comdlg32.lib")

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);






/* ======================= Rendering backend ======================= */
#if defined(API_D3D11)
namespace Renderer
{
    static ID3D11Device* device = nullptr;
    static ID3D11DeviceContext* deviceContext = nullptr;
    static IDXGISwapChain* swapChain = nullptr;
    static ID3D11RenderTargetView* renderTargetView = nullptr;


    static void CreateRenderTarget()
    {
        ID3D11Texture2D* backBuffer = nullptr;
        swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
        if (backBuffer != nullptr)
        {
            device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
            backBuffer->Release();
        }
    }

    static void CleanupRenderTarget()
    {
        if (renderTargetView)
        {
            renderTargetView->Release();
            renderTargetView = nullptr;
        }
    }


    static bool CreateDevice(HWND hWnd)
    {
        DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
        swapChainDesc.BufferCount = 2;
        swapChainDesc.BufferDesc.Width = 0;
        swapChainDesc.BufferDesc.Height = 0;
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
        swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.OutputWindow = hWnd;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
        swapChainDesc.Windowed = TRUE;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        const UINT createDeviceFlags = 0;
        const D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };
        D3D_FEATURE_LEVEL outFeatureLevel;

        HRESULT result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevels, static_cast<UINT>(std::size(featureLevels)),
            D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, &outFeatureLevel, &deviceContext);

        if (result == DXGI_ERROR_UNSUPPORTED) // Fallback to WARP if no hardware support.
        {
            result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevels, static_cast<UINT>(std::size(featureLevels)),
                D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, &outFeatureLevel, &deviceContext);
        }

        if (FAILED(result))
        {
            return false;
        }

        CreateRenderTarget();
        return true;
    }

    static void CleanupDevice(HWND hWnd)
    {
        CleanupRenderTarget();
        if (swapChain) { swapChain->Release(); swapChain = nullptr; }
        if (deviceContext) { deviceContext->Release(); deviceContext = nullptr; }
        if (device) { device->Release(); device = nullptr; }
    }


    static bool InitImGui()
    {
        return ImGui_ImplDX11_Init(device, deviceContext);
    }

    static void ShutdownImGui()
    {
        ImGui_ImplDX11_Shutdown();
    }

    static void NewFrame()
    {
        ImGui_ImplDX11_NewFrame();
    }


    static void Resize(UINT width, UINT height)
    {
        CleanupRenderTarget();
        swapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
        CreateRenderTarget();
    }

    static void Present(const ImVec4& clearColor)
    {
        const float clearColorArray[4] = { clearColor.x, clearColor.y, clearColor.z, clearColor.w };
        deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
        deviceContext->ClearRenderTargetView(renderTargetView, clearColorArray);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        swapChain->Present(1, 0); // VSync.
    }
}
#elif defined(API_OPENGL3)
namespace Renderer
{
    static HDC deviceContext = nullptr;
    static HGLRC renderContext = nullptr;


    static bool CreateDevice(HWND hWnd)
    {
        deviceContext = GetDC(hWnd);
        if (deviceContext == nullptr)
        {
            return false;
        }

        PIXELFORMATDESCRIPTOR pfd = {};
        pfd.nSize = sizeof(pfd);
        pfd.nVersion = 1;
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 32;
        pfd.cAlphaBits = 8;
        pfd.cDepthBits = 24;
        pfd.cStencilBits = 8;
        pfd.iLayerType = PFD_MAIN_PLANE;

        const int pixelFormat = ChoosePixelFormat(deviceContext, &pfd);
        if (pixelFormat == 0 || SetPixelFormat(deviceContext, pixelFormat, &pfd) == FALSE)
        {
            return false;
        }

        renderContext = wglCreateContext(deviceContext);
        if (renderContext == nullptr || wglMakeCurrent(deviceContext, renderContext) == FALSE)
        {
            return false;
        }

        /* Enable VSync if driver exposes it, otherwise render loop would spin as fast as possible. */
        using FnSwapIntervalType = BOOL(WINAPI*)(int);
        const FnSwapIntervalType FnSwapInterval = reinterpret_cast<FnSwapIntervalType>(wglGetProcAddress("wglSwapIntervalEXT"));
        if (FnSwapInterval != nullptr)
        {
            FnSwapInterval(1);
        }

        return true;
    }

    static void CleanupDevice(HWND hWnd)
    {
        if (renderContext)
        {
            wglMakeCurrent(nullptr, nullptr);
            wglDeleteContext(renderContext);
            renderContext = nullptr;
        }

        if (deviceContext)
        {
            ReleaseDC(hWnd, deviceContext);
            deviceContext = nullptr;
        }
    }


    static bool InitImGui()
    {
        return ImGui_ImplOpenGL3_Init("#version 130");
    }

    static void ShutdownImGui()
    {
        ImGui_ImplOpenGL3_Shutdown();
    }

    static void NewFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
    }


    static void Present(const ImVec4& clearColor)
    {
        const ImGuiIO& io = ImGui::GetIO();
        glViewport(0, 0, static_cast<int>(io.DisplaySize.x), static_cast<int>(io.DisplaySize.y));
        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SwapBuffers(deviceContext);
    }
}
#endif




/* ======================= Window ======================= */
static UINT resizeWidth = 0;
static UINT resizeHeight = 0;

/* Global hotkey: inject into the currently focused window. */
#define HOTKEY_INJECT_ID 1
static bool hotkeyInjectRequested = false;


static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
    {
        return true;
    }

    switch (msg)
    {
        case WM_SIZE:
            if (wParam == SIZE_MINIMIZED)
                return 0;
            resizeWidth = static_cast<UINT>(LOWORD(lParam));
            resizeHeight = static_cast<UINT>(HIWORD(lParam));
            return 0;

        case WM_HOTKEY:
            if (wParam == HOTKEY_INJECT_ID)
                hotkeyInjectRequested = true;
            return 0;

        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu.
                return 0;
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProcW(hWnd, msg, wParam, lParam);
}




/* ======================= Helpers ======================= */
static std::string NarrowUtf8(const std::wstring& wideString)
{
    if (wideString.empty())
        return std::string();

    const int size = WideCharToMultiByte(CP_UTF8, 0, wideString.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (size <= 1)
        return std::string();

    std::string outString(static_cast<size_t>(size), '\0');
    WideCharToMultiByte(CP_UTF8, 0, wideString.c_str(), -1, outString.data(), size, nullptr, nullptr);
    outString.resize(static_cast<size_t>(size) - 1); // Drop null terminator.

    return outString;
}

static std::string ToLowerAscii(std::string text)
{
    for (char& c : text)
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    return text;
}

static const char* ArchitectureToString(Injector::E_Architecture architecture)
{
    switch (architecture)
    {
        case Injector::E_Architecture::x86: return "x86";
        case Injector::E_Architecture::x64: return "x64";
        default:                            return "?";
    }
}


/* Directory the injector executable resides in. */
static std::wstring GetExecutableDirectory()
{
    wchar_t buffer[MAX_PATH] = {};
    const DWORD length = GetModuleFileNameW(nullptr, buffer, static_cast<DWORD>(std::size(buffer)));
    if (length == 0)
        return std::wstring();

    return std::filesystem::path(std::wstring(buffer, length)).parent_path().wstring();
}

/* Default library: UETools-GUI.dll next to the injector (both are built together). */
static std::wstring GetDefaultLibraryPath()
{
    const std::wstring directory = GetExecutableDirectory();
    if (directory.empty())
        return L"UETools-GUI.dll";

    return (std::filesystem::path(directory) / L"UETools-GUI.dll").wstring();
}

/* Open file dialog filtered to injectable libraries. */
static bool BrowseForLibrary(HWND owner, std::wstring* outPath)
{
    wchar_t fileBuffer[MAX_PATH] = {};

    OPENFILENAMEW openFileName = {};
    openFileName.lStructSize = sizeof(openFileName);
    openFileName.hwndOwner = owner;
    openFileName.lpstrFilter = L"Injectable libraries (*.dll;*.asi)\0*.dll;*.asi\0All files (*.*)\0*.*\0";
    openFileName.lpstrFile = fileBuffer;
    openFileName.nMaxFile = static_cast<DWORD>(std::size(fileBuffer));
    openFileName.lpstrTitle = L"Select library to inject";
    openFileName.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;

    if (GetOpenFileNameW(&openFileName) == FALSE)
        return false;

    *outPath = fileBuffer;
    return true;
}




/* ======================= Application state & UI ======================= */
namespace App
{
    static std::vector<Injector::ProcessInfo> processes;
    static std::unordered_set<uint32_t> injectedProcessIds;
    static int selectedIndex = -1;

    static char searchBuffer[256] = {};

    /* Process list views, from the most to the least filtered. */
    enum class E_View
    {
        Windows,      // Processes with a visible window (default: least noisy, enough in most cases).
        UnrealEngine, // Processes that look like Unreal Engine titles.
        All           // Every running process.
    };
    static E_View currentView = E_View::UnrealEngine; // Unreal Engine titles are the common target.

    static int windowsCount = 0;
    static int unrealEngineCount = 0;

    static std::wstring libraryPath;

    static std::string statusText = "Select a process and press Inject, or press Ctrl+Alt+I to inject into the active window.";
    static ImVec4 statusColor = ImVec4(0.75f, 0.75f, 0.75f, 1.0f);

    /* Process list is re-enumerated automatically on this interval. */
    static constexpr double AUTO_REFRESH_INTERVAL = 1.0; // Seconds.
    static double lastRefreshTime = -1.0;


    static bool MatchesView(const Injector::ProcessInfo& process)
    {
        switch (currentView)
        {
            case E_View::Windows:      return process.hasVisibleWindow;
            case E_View::UnrealEngine: return process.looksLikeUnrealEngine;
            default:                   return true;
        }
    }

    /* File name of the library that would be injected (used to detect it inside target processes). */
    static std::wstring InjectedModuleName()
    {
        if (libraryPath.empty())
            return std::wstring();

        return std::filesystem::path(libraryPath).filename().wstring();
    }

    static void RefreshProcesses()
    {
        /* Remember selection so auto-refresh doesn't drop it when the list is rebuilt. */
        const uint32_t previousSelectedId = (selectedIndex >= 0 && selectedIndex < static_cast<int>(processes.size()))
            ? processes[selectedIndex].processId : 0;

        processes = Injector::GetProcesses();

        selectedIndex = -1;
        if (previousSelectedId != 0)
        {
            for (int i = 0; i < static_cast<int>(processes.size()); ++i)
            {
                if (processes[i].processId == previousSelectedId)
                {
                    selectedIndex = i;
                    break;
                }
            }
        }

        windowsCount = 0;
        unrealEngineCount = 0;
        for (const Injector::ProcessInfo& process : processes)
        {
            if (process.hasVisibleWindow)
                ++windowsCount;

            if (process.looksLikeUnrealEngine)
                ++unrealEngineCount;
        }

        for (Injector::ProcessInfo& process : processes)
        {
            process.isInjected = false;
        }

        const std::wstring moduleName = InjectedModuleName();
        if (!moduleName.empty())
        {
            for (auto it = injectedProcessIds.begin(); it != injectedProcessIds.end(); )
            {
                const uint32_t pid = *it;
                auto procIt = std::find_if(processes.begin(), processes.end(), [pid](const Injector::ProcessInfo& p) 
                {
                    return p.processId == pid;
                });

                if (procIt == processes.end())
                {
                    it = injectedProcessIds.erase(it); // Process has ended.
                }
                else if (Injector::IsModuleLoaded(pid, moduleName))
                {
                    procIt->isInjected = true;
                    ++it;
                }
                else
                {
                    it = injectedProcessIds.erase(it); // Module was unloaded.
                }
            }
        }
    }

    static void SetStatus(const std::string& text, const ImVec4& color)
    {
        statusText = text;
        statusColor = color;
    }

    static bool PassesFilter(const Injector::ProcessInfo& process)
    {
        if (MatchesView(process) == false)
            return false;

        if (searchBuffer[0] == '\0')
            return true;

        const std::string filter = ToLowerAscii(searchBuffer);
        const std::string name = ToLowerAscii(NarrowUtf8(process.processName));
        const std::string title = ToLowerAscii(NarrowUtf8(process.windowTitle));

        return name.find(filter) != std::string::npos || title.find(filter) != std::string::npos;
    }
}




static void PerformInjection(HWND owner)
{
    if (App::selectedIndex < 0 || App::selectedIndex >= static_cast<int>(App::processes.size()))
    {
        App::SetStatus("No process selected.", ImVec4(0.90f, 0.70f, 0.20f, 1.0f));
        return;
    }

    const Injector::ProcessInfo& process = App::processes[App::selectedIndex];
    const Injector::E_InjectionResult result = Injector::Inject(process.processId, App::libraryPath);

    const bool isSuccess = (result == Injector::E_InjectionResult::Success);
    const bool isBenign = isSuccess || (result == Injector::E_InjectionResult::AlreadyInjected);

    if (isBenign)
    {
        App::injectedProcessIds.insert(process.processId);
        App::RefreshProcesses();
    }

    const ImVec4 color = isSuccess ? ImVec4(0.35f, 0.80f, 0.35f, 1.0f)
                                   : (isBenign ? ImVec4(0.90f, 0.70f, 0.20f, 1.0f) : ImVec4(0.90f, 0.35f, 0.35f, 1.0f));

    App::SetStatus(Injector::ResultToString(result), color);
}


/* Injects into the process that owns the currently focused window (triggered by the global hotkey). */
static void PerformForegroundInjection(HWND ownWindow)
{
    const HWND foreground = GetForegroundWindow();
    if (foreground == nullptr || foreground == ownWindow)
    {
        App::SetStatus("No active window to inject into.", ImVec4(0.90f, 0.70f, 0.20f, 1.0f));
        return;
    }

    DWORD processId = 0;
    GetWindowThreadProcessId(foreground, &processId);
    if (processId == 0 || processId == GetCurrentProcessId())
    {
        App::SetStatus("No active window to inject into.", ImVec4(0.90f, 0.70f, 0.20f, 1.0f));
        return;
    }

    const Injector::E_InjectionResult result = Injector::Inject(processId, App::libraryPath);

    const bool isSuccess = (result == Injector::E_InjectionResult::Success);
    const bool isBenign = isSuccess || (result == Injector::E_InjectionResult::AlreadyInjected);

    if (isBenign)
    {
        App::injectedProcessIds.insert(processId);
        App::RefreshProcesses();
    }

    const ImVec4 color = isSuccess ? ImVec4(0.35f, 0.80f, 0.35f, 1.0f)
                                   : (isBenign ? ImVec4(0.90f, 0.70f, 0.20f, 1.0f) : ImVec4(0.90f, 0.35f, 0.35f, 1.0f));

    App::SetStatus(std::string("[Ctrl+Alt+I] PID ") + std::to_string(processId) + ": " + Injector::ResultToString(result), color);
}


static void RenderUI(HWND owner)
{
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    const ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus;

    /* Periodically re-enumerate processes so the list stays current without manual refresh. */
    const double currentTime = ImGui::GetTime();
    if (App::lastRefreshTime < 0.0 || currentTime - App::lastRefreshTime >= App::AUTO_REFRESH_INTERVAL)
    {
        App::RefreshProcesses();
        App::lastRefreshTime = currentTime;
    }

    if (ImGui::Begin("##UEToolsInjector", nullptr, windowFlags) == false)
    {
        ImGui::End();
        return;
    }

    /* --- Controls row --- */
    if (ImGui::Button("Refresh"))
    {
        App::RefreshProcesses();
    }
    ImGui::SameLine();
    ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::InputTextWithHint("##Search", "Search by process name or window title...", App::searchBuffer, sizeof(App::searchBuffer));

    /* --- View tabs --- */
    if (ImGui::BeginTabBar("##Views"))
    {
        const std::string windowsTab = "Windows (" + std::to_string(App::windowsCount) + ")###Windows";
        const std::string unrealTab = "Unreal Engine (" + std::to_string(App::unrealEngineCount) + ")###Unreal";
        const std::string allTab = "All (" + std::to_string(static_cast<int>(App::processes.size())) + ")###All";

        const App::E_View previousView = App::currentView;

        if (ImGui::BeginTabItem(unrealTab.c_str()))
        {
            App::currentView = App::E_View::UnrealEngine;
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem(windowsTab.c_str()))
        {
            App::currentView = App::E_View::Windows;
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem(allTab.c_str()))
        {
            App::currentView = App::E_View::All;
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();

        /* Recompute injection marks immediately for the newly selected view. */
        if (App::currentView != previousView)
        {
            App::RefreshProcesses();
        }
    }

    /* --- Process list --- */
    /* Library & Inject rows below the table: 2 frames, each preceded by Spacing() and item spacing. */
    const float reservedHeight = ImGui::GetFrameHeight() * 2.0f + ImGui::GetStyle().ItemSpacing.y * 4.0f;
    const ImGuiTableFlags tableFlags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY | ImGuiTableFlags_Resizable | ImGuiTableFlags_SizingStretchProp;

    if (ImGui::BeginTable("##Processes", 4, tableFlags, ImVec2(0.0f, -reservedHeight)))
    {
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableSetupColumn("Process", ImGuiTableColumnFlags_WidthStretch, 0.35f);
        ImGui::TableSetupColumn("PID", ImGuiTableColumnFlags_WidthFixed, 60.0f);
        ImGui::TableSetupColumn("Arch", ImGuiTableColumnFlags_WidthFixed, 45.0f);
        ImGui::TableSetupColumn("Window Title", ImGuiTableColumnFlags_WidthStretch, 0.55f);
        ImGui::TableHeadersRow();

        for (int i = 0; i < static_cast<int>(App::processes.size()); ++i)
        {
            const Injector::ProcessInfo& process = App::processes[i];
            if (App::PassesFilter(process) == false)
                continue;

            ImGui::TableNextRow();
            ImGui::PushID(static_cast<int>(process.processId)); // Process names repeat (e.g. chrome.exe), PID doesn't.

            ImGui::TableSetColumnIndex(0);
            /* Green for processes UETools is already injected into, blue for Unreal Engine ones. */
            const bool colored = process.isInjected || process.looksLikeUnrealEngine;
            if (colored)
            {
                const ImVec4 color = process.isInjected ? ImVec4(0.40f, 0.85f, 0.45f, 1.0f) : ImVec4(0.45f, 0.75f, 1.0f, 1.0f);
                ImGui::PushStyleColor(ImGuiCol_Text, color);
            }

            const bool isSelected = (App::selectedIndex == i);
            const std::string label = NarrowUtf8(process.processName) + (process.isInjected ? "   [ injected ]" : "");
            if (ImGui::Selectable(label.c_str(), isSelected, ImGuiSelectableFlags_SpanAllColumns))
            {
                App::selectedIndex = i;
            }

            if (colored)
                ImGui::PopStyleColor();

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%u", process.processId);

            ImGui::TableSetColumnIndex(2);
            ImGui::TextUnformatted(ArchitectureToString(process.architecture));

            ImGui::TableSetColumnIndex(3);
            ImGui::TextUnformatted(NarrowUtf8(process.windowTitle).c_str());

            ImGui::PopID();
        }

        ImGui::EndTable();
    }

    ImGui::Spacing();

    /* --- Library path --- */
    ImGui::TextUnformatted("Library:");
    ImGui::SameLine();

    std::string pathUtf8 = NarrowUtf8(App::libraryPath);
    ImGui::SetNextItemWidth(-(ImGui::CalcTextSize("Browse...").x + ImGui::CalcTextSize("Default").x + ImGui::GetStyle().FramePadding.x * 4.0f + ImGui::GetStyle().ItemSpacing.x * 2.0f));
    ImGui::InputText("##LibraryPath", pathUtf8.data(), pathUtf8.size() + 1, ImGuiInputTextFlags_ReadOnly);
    ImGui::SameLine();
    if (ImGui::Button("Browse..."))
    {
        std::wstring chosenPath;
        if (BrowseForLibrary(owner, &chosenPath))
            App::libraryPath = chosenPath;
    }
    ImGui::SameLine();
    if (ImGui::Button("Default"))
    {
        App::libraryPath = GetDefaultLibraryPath();
    }

    ImGui::Spacing();

    /* --- Inject --- */
    const bool canInject = (App::selectedIndex >= 0);
    ImGui::BeginDisabled(canInject == false);
    if (ImGui::Button("Inject", ImVec2(120.0f, 0.0f)))
    {
        PerformInjection(owner);
    }
    ImGui::EndDisabled();

    ImGui::SameLine();
    ImGui::TextColored(App::statusColor, "%s", App::statusText.c_str());

    ImGui::End();
}






/* ======================= Entry point ======================= */
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(wc);
    wc.style = CS_OWNDC; // OpenGL needs a private device context; harmless for Direct3D.
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.hIcon = static_cast<HICON>(LoadImageW(hInstance, MAKEINTRESOURCEW(IDI_INJECTOR), IMAGE_ICON, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), 0));
    wc.hIconSm = static_cast<HICON>(LoadImageW(hInstance, MAKEINTRESOURCEW(IDI_INJECTOR), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0));
    wc.lpszClassName = L"UETools-Injector";
    RegisterClassExW(&wc);

    /* Fixed size window: no sizing border, no maximize button. */
    const DWORD windowStyle = WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX);
    const int windowWidth = 760;
    const int windowHeight = 470;

    /* Center within the work area (excludes the taskbar). */
    RECT workArea = {};
    SystemParametersInfoW(SPI_GETWORKAREA, 0, &workArea, 0);
    const int positionX = workArea.left + ((workArea.right - workArea.left) - windowWidth) / 2;
    const int positionY = workArea.top + ((workArea.bottom - workArea.top) - windowHeight) / 2;

    const HWND hWnd = CreateWindowExW(0, wc.lpszClassName, L"UETools Injector", windowStyle,
        positionX, positionY, windowWidth, windowHeight, nullptr, nullptr, wc.hInstance, nullptr);

    if (Renderer::CreateDevice(hWnd) == false)
    {
        Renderer::CleanupDevice(hWnd);
        DestroyWindow(hWnd);
        UnregisterClassW(wc.lpszClassName, wc.hInstance);
        MessageBoxW(nullptr, L"Failed to initialize rendering device.", L"UETools Injector", MB_ICONERROR | MB_OK);
        return 1;
    }

    ShowWindow(hWnd, SW_SHOWDEFAULT);
    UpdateWindow(hWnd);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.IniFilename = nullptr; // Don't persist layout for a single-window tool.

    ImGui::StyleColorsDark();

    /* Modern vector font instead of the pixel one. */
    io.FontDefault = io.Fonts->AddFontDefaultVector();

    /* Default font covers Latin only; Segoe UI is merged in for Cyrillic & other window titles. */
    wchar_t windowsDirectory[MAX_PATH] = {};
    if (GetWindowsDirectoryW(windowsDirectory, MAX_PATH) != 0)
    {
        const std::filesystem::path fallbackFontPath = std::filesystem::path(windowsDirectory) / L"Fonts" / L"segoeui.ttf";

        std::error_code errorCode;
        if (std::filesystem::exists(fallbackFontPath, errorCode))
        {
            ImFontConfig fallbackConfig;
            fallbackConfig.MergeMode = true;
            io.Fonts->AddFontFromFileTTF(fallbackFontPath.string().c_str(), 0.0f, &fallbackConfig);
        }
    }

    ImGui_ImplWin32_Init(hWnd);
    Renderer::InitImGui();

    /* Initial state (process list is populated on the first frame by auto-refresh). */
    App::libraryPath = GetDefaultLibraryPath();

    /* Global hotkey to inject into the focused window from anywhere. */
    if (RegisterHotKey(hWnd, HOTKEY_INJECT_ID, MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, 'I') == FALSE)
    {
        App::SetStatus("Ctrl+Alt+I hotkey is already in use by another application.", ImVec4(0.90f, 0.70f, 0.20f, 1.0f));
    }

    const ImVec4 clearColor = ImVec4(0.10f, 0.10f, 0.12f, 1.0f);

    bool bDone = false;
    while (bDone == false)
    {
        MSG msg;
        while (PeekMessageW(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);

            if (msg.message == WM_QUIT)
                bDone = true;
        }

        if (bDone)
            break;

        /* Hotkey injection is handled on the main thread, outside the window procedure. */
        if (hotkeyInjectRequested)
        {
            hotkeyInjectRequested = false;
            PerformForegroundInjection(hWnd);
        }

        /* Handle pending window resize. */
        if (resizeWidth != 0 && resizeHeight != 0)
        {
            resizeWidth = 0;
            resizeHeight = 0;
        }

        if (IsIconic(hWnd)) // Don't render while minimized.
        {
            Sleep(16);
            continue;
        }

        Renderer::NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        RenderUI(hWnd);

        ImGui::Render();
        Renderer::Present(clearColor);
    }

    UnregisterHotKey(hWnd, HOTKEY_INJECT_ID);

    Renderer::ShutdownImGui();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    Renderer::CleanupDevice(hWnd);
    DestroyWindow(hWnd);
    UnregisterClassW(wc.lpszClassName, wc.hInstance);

    if (wc.hIcon) DestroyIcon(wc.hIcon);
    if (wc.hIconSm) DestroyIcon(wc.hIconSm);

    return 0;
}
