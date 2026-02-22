#include "script.h"

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD reason, LPVOID lpReserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        scriptRegister(hInstance, ScriptAttach);
        keyboardHandlerRegister(OnKeyboardMessage);
        break;

    case DLL_PROCESS_DETACH:
        ScriptDetach();
        scriptUnregister(hInstance);
        keyboardHandlerUnregister(OnKeyboardMessage);
        break;
    }
    return TRUE;
}