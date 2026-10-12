#pragma once
#include "Window.h"
#include "GUI.h"

#ifdef API_OPENGL3
#include "imgui_impl_opengl3.h"
#include "GL/gl.h"

#pragma comment(lib, "opengl32.lib")

#define GL_CLAMP_TO_EDGE 0x812F






class OpenWindow3 : public Window
{
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
    static bool CreateDevice(HWND hWnd);

    /* Releases all OpenGL resources. */
    static void CleanupDevice(HWND hWnd);

    /* Clears overlay, optionally renders ImGui draw data and swaps buffers. */
    static bool Present(bool renderDrawData);


public:
    static bool CreateTexture(const std::string& textureName, const std::vector<uint8_t>& pixels, int32_t width, int32_t height);


public:
    /* Creates the overlay window and starts the render loop (see Window::Run()). */
    static void Create();
};
#endif