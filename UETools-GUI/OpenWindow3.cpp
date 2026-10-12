#include "OpenWindow3.h"
#ifdef API_OPENGL3






bool OpenWindow3::CreateDevice(HWND hWnd)
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
#ifdef API_HDR
    pfd.cRedBits = 10;
    pfd.cGreenBits = 10;
    pfd.cBlueBits = 10;
    pfd.cAlphaBits = 2;
#else
    pfd.cAlphaBits = 8;
#endif

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

void OpenWindow3::CleanupDevice(HWND hWnd)
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




bool OpenWindow3::CreateTexture(const std::string& textureName, const std::vector<uint8_t>& pixels, int32_t width, int32_t height)
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




bool OpenWindow3::Present(bool renderDrawData)
{
    if (renderDrawData)
    {
        ImGuiIO& io = ImGui::GetIO();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (renderDrawData)
    {
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    SwapBuffers(hDC);
    return true;
}




void OpenWindow3::Create()
{
    RenderBackend backend;
    backend.useBackgroundBrush = false;

    backend.FnCreateDevice = CreateDevice;
    backend.FnCleanupDevice = CleanupDevice;

    backend.FnInitImGui = []() { return ImGui_ImplOpenGL3_Init("#version 130"); };
    backend.FnShutdownImGui = ImGui_ImplOpenGL3_Shutdown;
    backend.FnNewFrame = ImGui_ImplOpenGL3_NewFrame;

    backend.FnPresent = Present;

    backend.FnCreateTexture = CreateTexture;
    backend.FnReleaseTexture = [](ImTextureID iTextureId)
        {
            /* OpenGL context is still current at that point. */
            GLuint texture = static_cast<GLuint>((uintptr_t)iTextureId);
            glDeleteTextures(1, &texture);
        };

    Run(backend);
}
#endif