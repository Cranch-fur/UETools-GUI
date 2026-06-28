#pragma once
#include "GUI.h"
#include "definitions.h"

#ifdef API_OPENGL3
#include "imgui_impl_win32.h"
#include "imgui_impl_opengl3.h"

#include "resource.h"

#include <dwmapi.h>
#include <GL/gl.h>
#include <string>
#include <vector>

#pragma comment(lib, "opengl32.lib")






extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);




class OpenWindow3
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
    static inline HDC hDC = nullptr;
public:
    static HDC GetDCContext()
    {
        return hDC;
    }
    static void SetDCContext(HDC newDC)
    {
        hDC = newDC;
    }
    static void InvalidateDCContext()
    {
        hDC = nullptr;
    }


private:
    static inline HGLRC hRC = nullptr;
public:
    static HGLRC GetRCContext()
    {
        return hRC;
    }
    static void SetRCContext(HGLRC newRC)
    {
        hRC = newRC;
    }
    static void InvalidateRCContext()
    {
        if (hRC != nullptr)
        {
            wglDeleteContext(hRC);
            hRC = nullptr;
        }
    }


private:
    /* Initializes an OpenGL device context for the given window. */
    static bool CreateDevice(const HWND& hWnd);

    /* Releases all OpenGL resources. */
    static void CleanupDevice(const HWND& hWnd);

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
#define GL_CLAMP_TO_EDGE 0x812F
    static bool CreateTexture(const std::string& textureName, const std::vector<uint8_t>& pixels, const int32_t& width, const int32_t& height);
    


public:
    /* Creates the overlay window and starts the render loop. */
    static void Create();
};
#endif