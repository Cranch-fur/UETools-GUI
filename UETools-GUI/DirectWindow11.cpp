#include "DirectWindow11.h"
#ifdef API_D3D11






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

    const HRESULT createShaderResourceViewResult = GetDevice()->CreateShaderResourceView(pTexture, &srvDesc, &out_srv);
    pTexture->Release();

    if (FAILED(createShaderResourceViewResult) || out_srv == nullptr)
        return false;

    ImGui::Texture2D::Add(textureName, (ImTextureID)out_srv);
    return true;
}




void DirectWindow11::Resize(UINT width, UINT height)
{
    if (GetDevice() == nullptr)
    {
        return;
    }

    InvalidateRenderTargetView();

    /* Overlay is shrunk to 0x0 when title loses focus; keep buffers and skip render target until it's restored. */
    if ((width == 0) || (height == 0))
    {
        return;
    }

    if (SUCCEEDED(GetSwapChain()->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0)))
    {
        CreateRenderTargetView();
    }
}

bool DirectWindow11::Present(bool renderDrawData)
{
    if (renderTargetView == nullptr)
    {
        return false;
    }

    const float colorTransparent[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

    GetDeviceContext()->OMSetRenderTargets(1, &renderTargetView, nullptr);
    GetDeviceContext()->ClearRenderTargetView(renderTargetView, colorTransparent);

    if (renderDrawData)
    {
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }

    GetSwapChain()->Present(1, 0); // VSync interval 1.
    return true;
}




void DirectWindow11::Create()
{
    RenderBackend backend;
    backend.useBackgroundBrush = true;

    backend.FnCreateDevice = CreateDevice;
    backend.FnCleanupDevice = [](HWND) { CleanupDevice(); };

    backend.FnInitImGui = []() { return ImGui_ImplDX11_Init(GetDevice(), GetDeviceContext()); };
    backend.FnShutdownImGui = ImGui_ImplDX11_Shutdown;
    backend.FnNewFrame = ImGui_ImplDX11_NewFrame;

    backend.FnPresent = Present;
    backend.FnResize = Resize;

    backend.FnCreateTexture = CreateTexture;
    backend.FnReleaseTexture = [](ImTextureID iTextureId)
        {
            if (ID3D11ShaderResourceView* shaderResourceView = (ID3D11ShaderResourceView*)(uintptr_t)iTextureId)
                shaderResourceView->Release();
        };

    Run(backend);
}
#endif