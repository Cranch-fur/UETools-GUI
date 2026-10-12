#pragma once
#include <windows.h>
#include <dwmapi.h>

#include <string>
#include <vector>
#include <functional>

#include "definitions.h"
#include "resource.h"
#include "Utilities.h"

#include "imgui_impl_win32.h"






class Window
{
public:
    /* Rendering API specific part of the overlay; everything else (window, ImGui, render loop) is shared. */
    struct RenderBackend
    {
        /* Overlay window class gets solid black background brush. */
        bool useBackgroundBrush = false;

        std::function<bool(HWND)> FnCreateDevice;
        std::function<void(HWND)> FnCleanupDevice;

        std::function<bool()> FnInitImGui;
        std::function<void()> FnShutdownImGui;
        std::function<void()> FnNewFrame;

        /* Clears overlay and presents it; ImGui draw data is rendered only if renderDrawData is true. Returns false if nothing was presented. */
        std::function<bool(bool)> FnPresent;

        /* Optional, called on WM_SIZE with new client size. */
        std::function<void(UINT, UINT)> FnResize;

        std::function<bool(const std::string&, const std::vector<uint8_t>&, int32_t, int32_t)> FnCreateTexture;
        std::function<void(ImTextureID)> FnReleaseTexture;
    };


protected:
    static inline const wchar_t* overlayClassName = L"UETools-GUI";

    static inline RenderBackend renderBackend;

    static inline bool bInit = false;

    static inline HWND hTargetWindow = nullptr;
    static inline bool bTargetSet = false;

    static inline DWORD dTargetPID = 0;

    /* Client area size of the target window, updated each frame by MoveWindow(). */
    static inline POINT targetWindowSize = { 0, 0 };


public:
    static HWND GetTargetWindow()
    {
        return hTargetWindow;
    }
    static POINT GetTargetWindowSize()
    {
        return targetWindowSize;
    }


protected:
    static inline HMODULE applicationModule = nullptr;
public:
    static HMODULE GetApplicationModule()
    {
        return applicationModule;
    }
    static void SetApplicationModule(HMODULE newApplicationModule)
    {
        applicationModule = newApplicationModule;
    }


protected:
    /* Setter function used to define the target window. */
    static void SetTargetWindow(HWND hWindow);

    /* Callback function that retrieves the main window of the process. */
    static BOOL CALLBACK EnumWind(HWND hWindow, LPARAM lParam);

    /* Function that starts retrieval of the main window of the process. */
    static void GetWindow();

    /* Moves the overlay on top of the targeted window. */
    static void MoveWindow(HWND hWindow, bool forceInvalidSize = false);

    /* Checks if the overlay window or the targeted window is in focus. */
    static bool IsWindowFocus(HWND hWindow);

    /* Checks if a window is valid for targeting. */
    static bool IsWindowValid(HWND hWindow);

    /* Checks if a window is cloaked (hidden by DWM). */
    static bool IsWindowCloaked(HWND hWindow);

    /* Checks if the targeted window has been closed. */
    static bool IsWindowAlive();

    /* Switches overlay between click-through (menu closed) and interactive (menu open) modes. */
    static void SetOverlayInteractive(HWND hWindow, bool isInteractive);


protected:
    /* Win32 window procedure for the overlay window. */
    static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    /* Creates the overlay window, runs the render loop and unloads the module once it's over. */
    static void Run(const RenderBackend& backend);

    
protected:
    /*
        Loads every PNG resource of the module as a texture named after its resource name.
        New texture only needs a file in Textures folder and a line in PNG section of UETools-GUI.rc.
    */
    static void InitializeTextures(const std::function<bool(const std::string&, const std::vector<uint8_t>&, int32_t, int32_t)>& FnCreateTexture);
};

