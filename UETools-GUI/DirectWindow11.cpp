#include "DirectWindow11.h"
#ifdef API_D3D11






LRESULT WINAPI DirectWindow11::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam) != 0)
    {
        return true;
    }

    switch (msg)
    {
        case WM_SIZE:
        {
            if ((GetDevice() != nullptr) && (wParam != SIZE_MINIMIZED))
            {
                InvalidateRenderTargetView();
                GetSwapChain()->ResizeBuffers(0, static_cast<UINT>(LOWORD(lParam)), static_cast<UINT>(HIWORD(lParam)), DXGI_FORMAT_UNKNOWN, 0);
                CreateRenderTargetView();
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




bool DirectWindow11::CreateRenderTargetView()
{
    ID3D11Texture2D* backBuffer = nullptr;
    HRESULT backBufferResult = GetSwapChain()->GetBuffer(0, IID_PPV_ARGS(&backBuffer));

    if (FAILED(backBufferResult))
    {
        return false;
    }

    HRESULT createRenderTargetViewResult = GetDevice()->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
    backBuffer->Release();

    if (FAILED(createRenderTargetViewResult))
    {
        return false;
    }

    return true;
}

bool DirectWindow11::CreateDevice(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferDesc.Width = 0;
    swapChainDesc.BufferDesc.Height = 0;

#ifdef API_HDR
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R10G10B10A2_UNORM;
#else
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
#endif

    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;

    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 2;

    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    swapChainDesc.OutputWindow = hWnd;
    swapChainDesc.Windowed = TRUE;

    const UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
    const D3D_FEATURE_LEVEL createDeviceFeatureLevels[] = { D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0 };
    D3D_FEATURE_LEVEL createDeviceOutFeatureLevel;

    /* Create Device + Swap Chain (hardware). */
    HRESULT createDeviceAndSwapChainResult = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, createDeviceFeatureLevels, static_cast<UINT>(std::size(createDeviceFeatureLevels)), D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, &createDeviceOutFeatureLevel, &deviceContext);

    if (createDeviceAndSwapChainResult == DXGI_ERROR_UNSUPPORTED) // Fallback to WARP if no hardware support.
    {
        createDeviceAndSwapChainResult = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, createDeviceFeatureLevels, static_cast<UINT>(std::size(createDeviceFeatureLevels)), D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, &createDeviceOutFeatureLevel, &deviceContext);
    }

    if (FAILED(createDeviceAndSwapChainResult))
    {
        return false;
    }

    CreateRenderTargetView();
    return true;
}

void DirectWindow11::CleanupDevice()
{
    InvalidateRenderTargetView();
    InvalidateDeviceContext();
    InvalidateSwapChain();
    InvalidateDevice();
}




bool DirectWindow11::CreateTexture(const std::string& textureName, const std::vector<uint8_t>& pixels, int32_t width, int32_t height)
{
    if (ImGui::Texture2D::Exists(textureName))
        return true;

    if (pixels.empty())
        return false;

    if (width == 0 || height == 0)
        return false;

    /* Texture data. */
    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;

    /* Pixel data. */
    D3D11_SUBRESOURCE_DATA subResource = {};
    subResource.pSysMem = pixels.data();
    subResource.SysMemPitch = width * 4;
    subResource.SysMemSlicePitch = 0;

    ID3D11Texture2D* pTexture = nullptr;
    if (FAILED(GetDevice()->CreateTexture2D(&desc, &subResource, &pTexture)))
        return false;

    /* Shader data. */
    ID3D11ShaderResourceView* out_srv = nullptr;
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = desc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;

    GetDevice()->CreateShaderResourceView(pTexture, &srvDesc, &out_srv);
    pTexture->Release();

    ImGui::Texture2D::Add(textureName, (ImTextureID)out_srv);
    return true;
}




void DirectWindow11::Create()
{
    ImGui_ImplWin32_EnableDpiAwareness();

    if (hTargetWindow == nullptr)
    {
        GetWindow();
    }

    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.hbrBackground = static_cast<HBRUSH>(CreateSolidBrush(RGB(0, 0, 0)));
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
        CleanupDevice();
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

    ImFontConfig cfg;
    ImFontConfig* pCfg = nullptr;

    if (monitorHeight > 1080)
    {
        const float fScale = 2.0f;
        cfg.SizePixels = 13.0f * fScale;
        pCfg = &cfg;
    }

    Features::Menu::fontBitmap = io.Fonts->AddFontDefault(pCfg);
    Features::Menu::fontVector = io.Fonts->AddFontDefaultVector(pCfg);

    io.FontDefault = Features::Menu::useVectorFont ? Features::Menu::fontVector : Features::Menu::fontBitmap;

    io.IniFilename = nullptr;

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(GetDevice(), GetDeviceContext());

    InitializeTextures(DirectWindow11::CreateTexture);

    bInit = true;

    /* RENDER LOOP */
    bool bDone = false;
    while (bDone == false)
    {
        static const float colorTransparent[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
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

        if (hTargetWindow == nullptr)
        {
            continue;
        }

        bool isMenuActive = GUI::GetIsMenuActive();
        static bool lastIsMenuActive = !isMenuActive;

        bool isInFocus = IsWindowFocus(hwnd) && bTargetSet;
        GUI::SetIsTitleInFocus(isInFocus);

#ifdef INACTIVE_ZERO_SIZE
        MoveWindow(hwnd, (isInFocus == false || isMenuActive == false));
#else
        MoveWindow(hwnd, (isInFocus == false));
#endif

        if (isInFocus == false)
        {
            lastIsMenuActive = !isMenuActive;

            GetDeviceContext()->OMSetRenderTargets(1, &renderTargetView, nullptr);
            GetDeviceContext()->ClearRenderTargetView(renderTargetView, colorTransparent);
            GetSwapChain()->Present(DXGI_SWAP_EFFECT_SEQUENTIAL, 0x0);

            continue;
        }

        ImGui_ImplDX11_NewFrame();
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
        GetDeviceContext()->OMSetRenderTargets(1, &renderTargetView, nullptr);
        GetDeviceContext()->ClearRenderTargetView(renderTargetView, colorTransparent);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        GetSwapChain()->Present(DXGI_SWAP_EFFECT_SEQUENTIAL, 0x0);
    }

    /* SHUTDOWN */
    bInit = false;

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDevice();
    DestroyWindow(hwnd);
    UnregisterClassW(wc.lpszClassName, wc.hInstance);

    CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(FreeLibrary), GetApplicationModule(), 0, nullptr);
}
#endif