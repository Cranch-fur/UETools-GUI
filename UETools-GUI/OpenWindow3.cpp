#include "OpenWindow3.h"
#ifdef API_OPENGL3






LRESULT WINAPI OpenWindow3::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam) != 0)
    {
        return true;
    }

    switch (msg)
    {
        case WM_SIZE:
        {
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




bool OpenWindow3::CreateDevice(const HWND& hWnd)
{
    hDC = GetDC(hWnd);
    if (hDC == nullptr)
    {
        return false;
    }

    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cAlphaBits = 8;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;

    int pixelFormat = ChoosePixelFormat(hDC, &pfd);
    if (pixelFormat == 0)
    {
        return false;
    }

    if (SetPixelFormat(hDC, pixelFormat, &pfd) == FALSE)
    {
        return false;
    }

    hRC = wglCreateContext(hDC);
    if (hRC == nullptr)
    {
        return false;
    }

    if (wglMakeCurrent(hDC, hRC) == FALSE)
    {
        return false;
    }

    return true;
}

void OpenWindow3::CleanupDevice(const HWND& hWnd)
{
    if (hRC != nullptr)
    {
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(hRC);
        hRC = nullptr;
    }
    if (hDC != nullptr)
    {
        ReleaseDC(hWnd, hDC);
        hDC = nullptr;
    }
}

void OpenWindow3::SetTargetWindow(const HWND& hWindow)
{
    hTargetWindow = hWindow;
    SetForegroundWindow(hTargetWindow);
    GetWindowThreadProcessId(hTargetWindow, &dTargetPID);
    bTargetSet = true;
}

BOOL CALLBACK OpenWindow3::EnumWind(HWND hWindow, LPARAM lParam)
{
    DWORD procID;
    GetWindowThreadProcessId(hWindow, &procID);

    if (GetCurrentProcessId() != procID)
    {
        return TRUE;
    }

    if (IsWindowValid(hWindow) == false)
    {
        return TRUE;
    }

    SetTargetWindow(hWindow);
    return FALSE;
}

void OpenWindow3::GetWindow()
{
    EnumWindows(EnumWind, 0);
}

void OpenWindow3::MoveWindow(const HWND& hWindow, const bool& forceInvalidSize)
{
    if (hTargetWindow == nullptr)
    {
        return;
    }

    RECT rect;
    GetWindowRect(hTargetWindow, &rect);

    /*
        When the graphics driver (NVIDIA/AMD) or Windows detects that our overlay window exactly matches
        the screen or target window dimensions, it may promote it to "Direct Flip" or "Independent Flip" mode.

        This bypasses the Desktop Window Manager (DWM) composition to optimize performance, which
        breaks our transparent alpha channel and causes the background to render as solid black.

        To prevent this, we add +1 pixel to the window dimensions. This intentionally breaks the
        exact-size heuristic, forcing DWM to handle the composition and keeping our background transparent.
    */
    int lWindowWidth = forceInvalidSize ? 0 : rect.right - rect.left + 1;
    int lWindowHeight = forceInvalidSize ? 0 : rect.bottom - rect.top + 1;

    SetWindowPos(hWindow, nullptr, rect.left, rect.top, lWindowWidth, lWindowHeight, SWP_SHOWWINDOW);
}

bool OpenWindow3::IsWindowFocus(const HWND& hWindow)
{
    char lpCurrentWindowUsedClass[125];
    char lpCurrentWindowClass[125];
    char lpOverlayWindowClass[125];

    const HWND hCurrentWindowUsed = GetForegroundWindow();

    if (GetClassNameA(hCurrentWindowUsed, lpCurrentWindowUsedClass, sizeof(lpCurrentWindowUsedClass)) == 0)
    {
        return false;
    }

    if (GetClassNameA(hTargetWindow, lpCurrentWindowClass, sizeof(lpCurrentWindowClass)) == 0)
    {
        return false;
    }

    if (GetClassNameA(hWindow, lpOverlayWindowClass, sizeof(lpOverlayWindowClass)) == 0)
    {
        return false;
    }

    if ((strcmp(lpCurrentWindowUsedClass, lpCurrentWindowClass) != 0) && (strcmp(lpCurrentWindowUsedClass, lpOverlayWindowClass) != 0))
    {
        SetWindowLongW(hWindow, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOOLWINDOW);
        return false;
    }

    return true;
}

bool OpenWindow3::IsWindowValid(const HWND& hWindow)
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

bool OpenWindow3::IsWindowCloaked(const HWND& hWindow)
{
    DWORD cloaked = 0;
    HRESULT hr = DwmGetWindowAttribute(hWindow, DWMWA_CLOAKED, &cloaked, sizeof(cloaked));

    if (SUCCEEDED(hr) && (cloaked != 0))
    {
        return true;
    }

    return false;
}

bool OpenWindow3::IsWindowAlive()
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




void OpenWindow3::InitializeTextures()
{
    CoInitialize(NULL);

    std::vector<uint8_t> pixels;
    int32_t width = 0;
    int32_t height = 0;

    if (Utilities::Resources::LoadPNG(Actor_Green, &pixels, &width, &height))
    {
        CreateTexture("Actor_Green", pixels, width, height);
        pixels.clear();
    }

    if (Utilities::Resources::LoadPNG(Actor_Red, &pixels, &width, &height))
    {
        CreateTexture("Actor_Red", pixels, width, height);
        pixels.clear();
    }
}

bool OpenWindow3::CreateTexture(const std::string& textureName, const std::vector<uint8_t>& pixels, const int32_t& width, const int32_t& height)
{
    if (ImGui::Texture2D::Exists(textureName))
        return true;

    if (pixels.empty())
        return false;

    if (width == 0 || height == 0)
        return false;

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
    ImGui::Texture2D::Add(textureName, (ImTextureID)(intptr_t)texture);

    return true;
}




void OpenWindow3::Create()
{
    ImGui_ImplWin32_EnableDpiAwareness();

    if (hTargetWindow == nullptr)
    {
        GetWindow();
    }

    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.hbrBackground = nullptr;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.hIcon = LoadIconW(nullptr, IDI_APPLICATION);
    wc.hIconSm = LoadIconW(nullptr, IDI_APPLICATION);
    wc.hInstance = GetModuleHandleW(nullptr);
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = L"UETools-GUI";
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

    if (CreateDevice(hwnd) == false)
    {
        CleanupDevice(hwnd);
        UnregisterClassW(wc.lpszClassName, wc.hInstance);
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

    if (monitorHeight > 1080)
    {
        const float fScale = 2.0f;
        ImFontConfig cfg;
        cfg.SizePixels = 13.0f * fScale;
        io.Fonts->AddFontDefault(&cfg);
    }

    io.IniFilename = nullptr;

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplOpenGL3_Init("#version 130");

    InitializeTextures();

    bInit = true;

    /* RENDER LOOP */
    bool bDone = false;
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

        if (bDone == true)
        {
            break;
        }

        bool isMenuActive = GUI::GetIsMenuActive();
        static bool lastIsMenuActive = !isMenuActive;

        bool isInFocus = IsWindowFocus(hwnd) && bTargetSet;
        GUI::SetIsTitleInFocus(isInFocus);

        if (hTargetWindow != nullptr)
        {
#ifdef INACTIVE_ZERO_SIZE
            MoveWindow(hwnd, (isMenuActive == false) || (isInFocus == false));
#else
            MoveWindow(hwnd);
#endif
        }
        else
        {
            continue;
        }

        if (isInFocus == false)
        {
            lastIsMenuActive = !isMenuActive;

            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            SwapBuffers(hDC);

            continue;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        GUI::Draw();

        ImGui::EndFrame();

        if (isMenuActive != lastIsMenuActive)
        {
            if (isMenuActive == true)
            {
                LONG ex = GetWindowLongW(hwnd, GWL_EXSTYLE);
                ex &= ~WS_EX_TRANSPARENT;
                ex &= ~WS_EX_NOACTIVATE;
                ex |= (WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW);
                SetWindowLongW(hwnd, GWL_EXSTYLE, ex);
                SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

                DWORD gameTid = GetWindowThreadProcessId(hTargetWindow, nullptr);
                DWORD myTid = GetCurrentThreadId();

                AttachThreadInput(myTid, gameTid, TRUE);
                SetForegroundWindow(hwnd);
                SetActiveWindow(hwnd);
                SetFocus(hwnd);
                AttachThreadInput(myTid, gameTid, FALSE);

                if (GetCapture() != hwnd)
                {
                    SetCapture(hwnd);
                }

                io.MouseDrawCursor = true;
            }
            else
            {
                LONG ex = GetWindowLongW(hwnd, GWL_EXSTYLE);
                ex |= WS_EX_TRANSPARENT;
                ex &= ~WS_EX_NOACTIVATE;
                ex |= (WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW);
                SetWindowLongW(hwnd, GWL_EXSTYLE, ex);
                SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

                if (GetCapture() == hwnd)
                {
                    ReleaseCapture();
                }

                io.MouseDrawCursor = false;

                if (IsWindow(hTargetWindow) != 0)
                {
                    SetForegroundWindow(hTargetWindow);
                }
            }

            lastIsMenuActive = isMenuActive;
        }

        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SwapBuffers(hDC);
    }

    /* SHUTDOWN */
    bInit = false;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDevice(hwnd);
    DestroyWindow(hwnd);
    UnregisterClassW(wc.lpszClassName, wc.hInstance);

    CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(FreeLibrary), GetApplicationModule(), 0, nullptr);
}
#endif