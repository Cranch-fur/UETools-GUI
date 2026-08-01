#include "Window.h"






void Window::SetTargetWindow(const HWND& hWindow)
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

void Window::MoveWindow(const HWND& hWindow, const bool& forceInvalidSize)
{
    if (hTargetWindow == nullptr)
    {
        return;
    }

    RECT rect;
    GetWindowRect(hTargetWindow, &rect);

    int lWindowWidth = forceInvalidSize ? 0 : rect.right - rect.left + 1;
    int lWindowHeight = forceInvalidSize ? 0 : rect.bottom - rect.top + 1;

    SetWindowPos(hWindow, nullptr, rect.left, rect.top, lWindowWidth, lWindowHeight, SWP_SHOWWINDOW);
}

bool Window::IsWindowFocus(const HWND& hWindow)
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

bool Window::IsWindowValid(const HWND& hWindow)
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

bool Window::IsWindowCloaked(const HWND& hWindow)
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
    CoInitialize(NULL);

    std::vector<uint8_t> pixels;
    int32_t width = 0;
    int32_t height = 0;

    for (const TextureMetaData& texture : texturesCollection)
    {
        if (Utilities::Resources::LoadPNG(texture.resourceId, &pixels, &width, &height))
        {
            FnCreateTexture(texture.name, pixels, width, height);
            pixels.clear();
        }
    }
}
