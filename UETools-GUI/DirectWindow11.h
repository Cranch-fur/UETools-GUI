#pragma once
#include "GUI.h"
#include "definitions.h"

#ifdef API_D3D11
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "resource.h"

#include <dwmapi.h>
#include <d3d11.h>
#include <string>
#include <vector>

#pragma comment(lib, "d3d11.lib")






extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);




class DirectWindow11
{
private:
    /* Win32 window procedure for the overlay window. */
    static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    static inline bool bInit = false;
    static inline HWND hTargetWindow = nullptr;
    static inline bool bTargetSet = false;
    static inline DWORD dTargetPID = 0;


private:
    static inline HMODULE applicationModule = nullptr;
public:
    static HMODULE GetApplicationModule()
    {
        return applicationModule;
    }
    static void SetApplicationModule(const HMODULE& newApplicationModule)
    {
        applicationModule = newApplicationModule;
    }


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

    /* Setter function used to define the target window. */
    static void SetTargetWindow(const HWND& hWindow);

    /* Callback function that retrieves the main window of the process. */
    static BOOL CALLBACK EnumWind(HWND hWindow, LPARAM lParam);

    /* Function that starts retrieval of the main window of the process. */
    static void GetWindow();

    /* Moves the overlay on top of the targeted window. */
    static void MoveWindow(const HWND& hWindow, const bool& forceInvalidSize = false);

    /* Checks if the overlay window or the targeted window is in focus. */
    static bool IsWindowFocus(const HWND& hWindow);

    /* Checks if a window is valid for targeting. */
    static bool IsWindowValid(const HWND& hWindow);

    /* Checks if a window is cloaked (hidden by DWM). */
    static bool IsWindowCloaked(const HWND& hWindow);

    /* Checks if the targeted window has been closed. */
    static bool IsWindowAlive();


private:
    static void InitializeTextures();
public:
    static bool CreateTexture(const std::string& textureName, const std::vector<uint8_t>& pixels, const int32_t& width, const int32_t& height);


public:
    /* Creates the overlay window and starts the render loop. */
    static void Create();
};
#endif