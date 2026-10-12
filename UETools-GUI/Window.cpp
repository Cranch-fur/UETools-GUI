#include "Window.h"
#include "GUI.h"






extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);






void Window::SetTargetWindow(HWND hWindow)
{
    hTargetWindow = hWindow;
    SetForegroundWindow(hTargetWindow);
    GetWindowThreadProcessId(hTargetWindow, &dTargetPID);
    bTargetSet = true;
}

BOOL CALLBACK Window::EnumWind(HWND hWindow, LPARAM lParam)
{
    DWORD procID;
    GetWindowThreadProcessId(hWindow, &procID);

    if (GetCurrentProcessId() != procID)
    {
        return TRUE;
    }

    wchar_t className[64] = {};
    if (GetClassNameW(hWindow, className, static_cast<int>(std::size(className))) != 0 && wcscmp(className, overlayClassName) == 0) // Skip our own overlay.
    {
        return TRUE;
    }

    if (IsWindowValid(hWindow) == false) // Skip non-eligible windows.
    {
        return TRUE;
    }

    SetTargetWindow(hWindow);
    return FALSE; // Stop enumeration after finding the first match.
}

void Window::GetWindow()
{
    EnumWindows(EnumWind, 0);
}

void Window::MoveWindow(HWND hWindow, bool forceInvalidSize)
{
    if (hTargetWindow == nullptr)
    {
        return;
    }

    /* Title renders into client area only, so overlay must cover client area (not borders / caption). */
    RECT rect;
    if (GetClientRect(hTargetWindow, &rect) == FALSE)
    {
        return;
    }

    POINT clientOrigin = { 0, 0 };
    ClientToScreen(hTargetWindow, &clientOrigin);

    /*
        +1 px is intentional: foreground window exactly covering the monitor is treated by Windows as fullscreen app,
        DWM composition gets bypassed and transparent background turns solid black.
    */
    int lWindowWidth = forceInvalidSize ? 0 : rect.right - rect.left + 1;
    int lWindowHeight = forceInvalidSize ? 0 : rect.bottom - rect.top + 1;

    targetWindowSize = { rect.right - rect.left, rect.bottom - rect.top };

    SetWindowPos(hWindow, nullptr, clientOrigin.x, clientOrigin.y, lWindowWidth, lWindowHeight, SWP_SHOWWINDOW);
}

bool Window::IsWindowFocus(HWND hWindow)
{
    const HWND hCurrentWindowUsed = GetForegroundWindow();

    /* Compare handles, not class names: other UE titles share "UnrealWindow" class. */
    if ((hCurrentWindowUsed == hTargetWindow) || (hCurrentWindowUsed == hWindow))
    {
        return true;
    }

    const LONG unfocusedExStyles = WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOOLWINDOW;
    if (GetWindowLongW(hWindow, GWL_EXSTYLE) != unfocusedExStyles) // Avoid restyling the window every frame.
    {
        SetWindowLongW(hWindow, GWL_EXSTYLE, unfocusedExStyles);
    }

    return false;
}

bool Window::IsWindowValid(HWND hWindow)
{
    if ((IsWindowVisible(hWindow) == 0) || (IsIconic(hWindow) != 0) || (IsWindowCloaked(hWindow) == true))
    {
        return false;
    }

    RECT rect;
    GetClientRect(hWindow, &rect);

    DWORD styles = static_cast<DWORD>(GetWindowLongPtrW(hWindow, GWL_STYLE));
    DWORD exStyles = static_cast<DWORD>(GetWindowLongPtrW(hWindow, GWL_EXSTYLE));

    if (exStyles & WS_EX_TOOLWINDOW)
    {
        return false;
    }

    if (styles & WS_CHILD)
    {
        return false;
    }

    if ((rect.bottom == 0) || (rect.right == 0))
    {
        return false;
    }

    return true;
}

bool Window::IsWindowCloaked(HWND hWindow)
{
    DWORD cloaked = 0;
    HRESULT hr = DwmGetWindowAttribute(hWindow, DWMWA_CLOAKED, &cloaked, sizeof(cloaked));

    if (SUCCEEDED(hr) && (cloaked != 0))
    {
        return true;
    }

    return false;
}

bool Window::IsWindowAlive()
{
    if (hTargetWindow == nullptr)
    {
        return false;
    }

    if (IsWindow(hTargetWindow) == 0)
    {
        return false;
    }

    DWORD dCurrentPID;
    GetWindowThreadProcessId(hTargetWindow, &dCurrentPID);

    if (dCurrentPID != dTargetPID)
    {
        return false;
    }

    return true;
}




void Window::InitializeTextures(const std::function<bool(const std::string&, const std::vector<uint8_t>&, int32_t, int32_t)>& FnCreateTexture)
{
    /* S_FALSE means COM was already initialized on that thread, still needs balancing. */
    const HRESULT coInitializeResult = CoInitialize(NULL);

    std::vector<uint8_t> pixels;
    int32_t width = 0;
    int32_t height = 0;

    for (const std::wstring& resourceName : Utilities::Resources::GetResourceNames(L"PNG"))
    {
        if (Utilities::Resources::LoadPNG(resourceName, &pixels, &width, &height))
        {
            FnCreateTexture(Utilities::String::ToString(resourceName), pixels, width, height);
            pixels.clear();
        }
    }

    if (SUCCEEDED(coInitializeResult))
    {
        CoUninitialize();
    }
}




void Window::SetOverlayInteractive(HWND hWindow, bool isInteractive)
{
    LONG ex = GetWindowLongW(hWindow, GWL_EXSTYLE);
    if (isInteractive)
        ex &= ~WS_EX_TRANSPARENT;
    else
        ex |= WS_EX_TRANSPARENT;

    ex &= ~WS_EX_NOACTIVATE;
    ex |= (WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW);
    SetWindowLongW(hWindow, GWL_EXSTYLE, ex);
    SetWindowPos(hWindow, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

    if (isInteractive)
    {
        DWORD gameTid = GetWindowThreadProcessId(hTargetWindow, nullptr);
        DWORD myTid = GetCurrentThreadId();

        AttachThreadInput(myTid, gameTid, TRUE);
        SetForegroundWindow(hWindow);
        SetActiveWindow(hWindow);
        SetFocus(hWindow);
        AttachThreadInput(myTid, gameTid, FALSE);

        if (GetCapture() != hWindow)
        {
            SetCapture(hWindow);
        }
    }
    else
    {
        if (GetCapture() == hWindow)
        {
            ReleaseCapture();
        }

        if (IsWindow(hTargetWindow) != 0)
        {
            SetForegroundWindow(hTargetWindow);
        }
    }

    ImGui::GetIO().MouseDrawCursor = isInteractive;
}




LRESULT WINAPI Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam) != 0)
    {
        return true;
    }

    switch (msg)
    {
        case WM_SIZE:
        {
            if ((renderBackend.FnResize != nullptr) && (wParam != SIZE_MINIMIZED))
            {
                renderBackend.FnResize(static_cast<UINT>(LOWORD(lParam)), static_cast<UINT>(HIWORD(lParam)));
            }
            return 0;
        }

        case WM_SYSCOMMAND:
        {
            if ((wParam & 0xfff0) == SC_KEYMENU)
            {
                return 0;
            }
            break;
        }

        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }

        default:
        {
            break;
        }
    }

    return DefWindowProcW(hWnd, msg, wParam, lParam);
}




void Window::Run(const RenderBackend& backend)
{
    renderBackend = backend;

    ImGui_ImplWin32_EnableDpiAwareness();

    if (hTargetWindow == nullptr)
    {
        GetWindow();
    }

    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(WNDCLASSEXW);
    const HBRUSH backgroundBrush = backend.useBackgroundBrush ? CreateSolidBrush(RGB(0, 0, 0)) : nullptr;
    wc.hbrBackground = backgroundBrush;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.hIcon = LoadIconW(nullptr, IDI_APPLICATION);
    wc.hIconSm = LoadIconW(nullptr, IDI_APPLICATION);
    wc.hInstance = GetModuleHandleW(nullptr);
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = overlayClassName;
    wc.style = CS_VREDRAW | CS_HREDRAW;

    RegisterClassExW(&wc);

    const HWND hwnd = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE,
        wc.lpszClassName, L"UETools-GUI", WS_POPUP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
        nullptr, nullptr, wc.hInstance, nullptr
    );

    SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA);

    const MARGINS margin = { -1, 0, 0, 0 };
    DwmExtendFrameIntoClientArea(hwnd, &margin);

    if (backend.FnCreateDevice(hwnd) == false)
    {
        backend.FnCleanupDevice(hwnd);
        DestroyWindow(hwnd);
        UnregisterClassW(wc.lpszClassName, wc.hInstance);

        if (backgroundBrush)
        {
            DeleteObject(backgroundBrush);
        }

        renderBackend = {};
        return;
    }

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    /* IMGUI SETUP */
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    const HMONITOR monitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFO info = {};
    info.cbSize = sizeof(MONITORINFO);
    GetMonitorInfoW(monitor, &info);

    const int monitorHeight = info.rcMonitor.bottom - info.rcMonitor.top;

    ImFontConfig cfg;
    ImFontConfig* pCfg = nullptr;

    /* Scale proportionally to 1080p (1440p -> x1.33, 2160p -> x2.0). */
    float fScale = static_cast<float>(monitorHeight) / 1080.0f;
    if (fScale > 2.0f)
        fScale = 2.0f;

    if (fScale > 1.0f)
    {
        cfg.SizePixels = 13.0f * fScale;
        pCfg = &cfg;
    }

    Features::Menu::fontBitmap = io.Fonts->AddFontDefault(pCfg);
    Features::Menu::fontVector = io.Fonts->AddFontDefaultVector(pCfg);

    io.FontDefault = Features::Menu::useVectorFont ? Features::Menu::fontVector : Features::Menu::fontBitmap;

    io.IniFilename = nullptr;

    ImGui_ImplWin32_Init(hwnd);
    backend.FnInitImGui();

    InitializeTextures(backend.FnCreateTexture);

    bInit = true;

    /* RENDER LOOP */
    bool bDone = false;
    bool lastIsMenuActive = !GUI::GetIsMenuActive(); // Forces overlay mode to be applied on first frame.

    while (bDone == false)
    {
        MSG msg;

        while (PeekMessageW(&msg, nullptr, 0U, 0U, PM_REMOVE) != 0)
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);

            if (msg.message == WM_QUIT)
            {
                bDone = true;
            }
        }

        if ((IsWindowAlive() == false) && (bTargetSet == true))
        {
            bDone = true;
        }

        if (GUI::GetIsUnloadRequested())
        {
            bDone = true;
        }

        if (bDone == true)
        {
            break;
        }

        if (hTargetWindow == nullptr)
        {
            /* Title window may appear later than overlay. */
            GetWindow();

            if (hTargetWindow == nullptr)
            {
                Sleep(100);
                continue;
            }
        }

        const bool isMenuActive = GUI::GetIsMenuActive();

        const bool isInFocus = IsWindowFocus(hwnd) && bTargetSet;
        GUI::SetIsTitleInFocus(isInFocus);

#ifdef INACTIVE_ZERO_SIZE
        MoveWindow(hwnd, (isInFocus == false || isMenuActive == false));
#else
        MoveWindow(hwnd, (isInFocus == false));
#endif

        if (isInFocus == false)
        {
            lastIsMenuActive = !isMenuActive;

            if (backend.FnPresent(false) == false)
            {
                Sleep(16); // Nothing to present, avoid spinning.
            }

            continue;
        }

        backend.FnNewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        GUI::Draw();

        ImGui::EndFrame();

        if (isMenuActive != lastIsMenuActive)
        {
            SetOverlayInteractive(hwnd, isMenuActive);
            lastIsMenuActive = isMenuActive;
        }

        ImGui::Render();

        if (backend.FnPresent(true) == false)
        {
            Sleep(16); // Render target is being recreated.
        }
    }

    /* SHUTDOWN */
    bInit = false;

    /* Background tasks may use ImGui and title objects, stop them before anything is released. */
    GUI::Shutdown();

    ImGui::Texture2D::Clear(backend.FnReleaseTexture);

    backend.FnShutdownImGui();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    backend.FnCleanupDevice(hwnd);
    DestroyWindow(hwnd);
    UnregisterClassW(wc.lpszClassName, wc.hInstance);

    if (backgroundBrush)
    {
        DeleteObject(backgroundBrush);
    }

    renderBackend = {};

    /* Give input back to the title (overlay could own focus while menu was open). */
    if (IsWindow(hTargetWindow) != 0)
    {
        SetForegroundWindow(hTargetWindow);
    }

    /* Unload module and exit without returning into (already unloaded) code. */
    FreeLibraryAndExitThread(GetApplicationModule(), 0);
}
