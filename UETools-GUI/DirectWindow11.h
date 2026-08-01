#pragma once
#include "Window.h"
#include "GUI.h"

#ifdef API_D3D11
#include "imgui_impl_dx11.h"
#include "d3d11.h"

#pragma comment(lib, "d3d11.lib")






extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class DirectWindow11 : public Window
{
private:
    /* Win32 window procedure for the overlay window. */
    static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


private:
    static inline ID3D11RenderTargetView* renderTargetView = nullptr;
public:
    static ID3D11RenderTargetView* GetRenderTargetView()
    {
        return renderTargetView;
    }
    static void InvalidateRenderTargetView()
    {
        if (renderTargetView != nullptr)
        {
            renderTargetView->Release();
            renderTargetView = nullptr;
        }
    }


private:
    static inline ID3D11DeviceContext* deviceContext = nullptr;
public:
    static ID3D11DeviceContext* GetDeviceContext()
    {
        return deviceContext;
    }
    static void SetDeviceContext(ID3D11DeviceContext* newDeviceContext)
    {
        deviceContext = newDeviceContext;
    }
    static void InvalidateDeviceContext()
    {
        if (deviceContext != nullptr)
        {
            deviceContext->Release();
            deviceContext = nullptr;
        }
    }


private:
    static inline IDXGISwapChain* swapChain = nullptr;
public:
    static IDXGISwapChain* GetSwapChain()
    {
        return swapChain;
    }
    static void SetSwapChain(IDXGISwapChain* newSwapChain)
    {
        swapChain = newSwapChain;
    }
    static void InvalidateSwapChain()
    {
        if (swapChain != nullptr)
        {
            swapChain->Release();
            swapChain = nullptr;
        }
    }


private:
    static inline ID3D11Device* device = nullptr;
public:
    static ID3D11Device* GetDevice()
    {
        return device;
    }
    static void SetDevice(ID3D11Device* newDevice)
    {
        device = newDevice;
    }
    static void InvalidateDevice()
    {
        if (device != nullptr)
        {
            device->Release();
            device = nullptr;
        }
    }


private:
    /* Creates (or recreates) the render target for the current swap chain back buffer. */
    static bool CreateRenderTargetView();

    /* Initializes a Direct3D device, device context, and swap chain for the given window. */
    static bool CreateDevice(const HWND& hWnd, const bool& HDR = false);

    /* Releases all Direct3D resources. */
    static void CleanupDevice();


public:
    static bool CreateTexture(const std::string& textureName, const std::vector<uint8_t>& pixels, int32_t width, int32_t height);


public:
    /* Creates the overlay window and starts the render loop. */
    static void Create();
};
#endif