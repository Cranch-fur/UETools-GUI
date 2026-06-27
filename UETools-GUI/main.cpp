#include <Windows.h>
#include "GUI.h"






DWORD WINAPI InitThread(LPVOID lpParam)
{
#ifdef ALLOC_CONSOLE
    Utilities::Console::Create(true);
#endif

    HMODULE hModule = (HMODULE)lpParam;
#ifdef WAIT_FOR_TITLE_INIT
    GUI::InitOnTitleInitialized(hModule);
#else
    GUI::Init(hModule);
#endif

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hModule);
            if (HANDLE hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)InitThread, hModule, 0, nullptr))
                CloseHandle(hThread);
            break;

        case DLL_THREAD_ATTACH:
            break;

        case DLL_THREAD_DETACH:
            break;

        case DLL_PROCESS_DETACH:
            break;
    }


    return TRUE;
}