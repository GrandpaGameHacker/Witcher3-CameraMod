#include "W3AnselHook.h"


BOOL __declspec(dllexport) WINAPI  DllMain(HINSTANCE hinstDLL,
    DWORD fdwReason,
    LPVOID lpReserved)
{
	switch( fdwReason )\
	{
		case DLL_PROCESS_ATTACH:
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&patch, 0, 0, 0);
			break;
		case DLL_THREAD_ATTACH:
         // Do thread-specific initialization.
            break;

        case DLL_THREAD_DETACH:
         // Do thread-specific cleanup.
            break;

        case DLL_PROCESS_DETACH:
         // Perform any necessary cleanup.
            break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}

void patch()
{
	Sleep(1000 * 15);
	HMODULE AnselDLL = GetModuleHandleA(szNvCamera);
	HMODULE Game = GetModuleHandleA(szGame);
	uintptr_t ansel_address1 = (unsigned long long) AnselDLL + ANSEL_OFFSET1;
	uintptr_t ansel_address2 = (unsigned long long) AnselDLL + ANSEL_OFFSET2;
	uintptr_t w3_address1 = (unsigned long long) Game + W3OFFSET1;
	patch_address(ansel_address1, ANSEL_PATCH1, sizeof(ANSEL_PATCH1));
	patch_address(ansel_address2, ANSEL_PATCH2, sizeof(ANSEL_PATCH2));
	patch_address(w3_address1, W3PATCH1, sizeof(W3PATCH1));
	HMODULE self = GetModuleHandleA("WitcherCameraMod.dll");
	if (self) {
		FreeLibraryAndExitThread(self, 0);
	};

}

void patch_address(uintptr_t address, const BYTE* bytes, size_t length)
{
	DWORD flOldProtect = 0;
	void* vaddress = (void*)address;
	VirtualProtect(vaddress, length, PAGE_EXECUTE_READWRITE, &flOldProtect);
	memcpy(vaddress, (void*) bytes, length);
	VirtualProtect(vaddress, length, flOldProtect, &flOldProtect);
}