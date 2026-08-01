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
protected:
    static inline bool bInit = false;

    static inline HWND hTargetWindow = nullptr;
    static inline bool bTargetSet = false;

    static inline DWORD dTargetPID = 0;


protected:
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


protected:
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

    
public:
    struct TextureMetaData 
    {
        int32_t resourceId;
        const char* name;
    };

    struct TextureCollection
    {
        TextureMetaData T_Placeholder =                { Placeholder, "Placeholder" };
        TextureMetaData T_Friendly =                   { Friendly, "Friendly" };
        TextureMetaData T_Hostile =                    { Hostile, "Hostile" };
        TextureMetaData T_Actor =                      { Actor_Base, "Actor_Base" };
        TextureMetaData T_Actor_PointLight =           { Actor_PointLight, "Actor_PointLight" };
        TextureMetaData T_Actor_SpotLight =            { Actor_SpotLight, "Actor_SpotLight" };
        TextureMetaData T_Actor_RectLight =            { Actor_RectLight, "Actor_RectLight" };
        TextureMetaData T_Actor_DirectionalLight =     { Actor_DirectionalLight, "Actor_DirectionalLight" };
        TextureMetaData T_Actor_SkyLight =             { Actor_SkyLight, "Actor_SkyLight" };
        TextureMetaData T_Actor_AtmosphericFog =       { Actor_AtmosphericFog, "Actor_AtmosphericFog" };
        TextureMetaData T_Actor_ExponentialHeightFog = { Actor_ExponentialHeightFog, "Actor_ExponentialHeightFog" };
        TextureMetaData T_Actor_Camera =               { Actor_Camera, "Actor_Camera" };
        TextureMetaData T_Actor_Pawn =                 { Actor_Pawn, "Actor_Pawn" };
        TextureMetaData T_Actor_DefaultPawn =          { Actor_DefaultPawn, "Actor_DefaultPawn" };
        TextureMetaData T_Actor_Decal =                { Actor_Decal, "Actor_Decal" };
        TextureMetaData T_Actor_TextRender =           { Actor_TextRender, "Actor_TextRender" };
        TextureMetaData T_Actor_TargetPoint =          { Actor_TargetPoint, "Actor_TargetPoint" };

        const TextureMetaData* begin() const { return reinterpret_cast<const TextureMetaData*>(this); }
        const TextureMetaData* end() const { return begin() + (sizeof(*this) / sizeof(TextureMetaData)); }
    };

    static inline const TextureCollection texturesCollection;

protected:
    static void InitializeTextures(const std::function<bool(const std::string&, const std::vector<uint8_t>&, int32_t, int32_t)>& FnCreateTexture);
};

