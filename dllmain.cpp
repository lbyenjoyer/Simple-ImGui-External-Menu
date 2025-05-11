#include "dllmain.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        this_thread::sleep_for(chrono::milliseconds(36));
        CreateThread(0, 0, MainThread, 0, 0, 0);
    }
    return TRUE;
}