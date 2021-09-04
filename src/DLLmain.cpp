//moved to pch.h
//#define _D2VARS_H
#include "pch.h"

#include "DLLmain.h"
#include "D2Patch.h"

/****************************************************************************
*                                                                           *
*   DLLmain.h                                                               *
*                                                                           *
*   Licensed under the Apache License, Version 2.0 (the "License");         *
*   you may not use this file except in compliance with the License.        *
*   You may obtain a copy of the License at                                 *
*                                                                           *
*   http://www.apache.org/licenses/LICENSE-2.0                              *
*                                                                           *
*   Unless required by applicable law or agreed to in writing, software     *
*   distributed under the License is distributed on an "AS IS" BASIS,       *
*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.*
*   See the License for the specific language governing permissions and     *
*   limitations under the License.                                          *
*                                                                           *
*---------------------------------------------------------------------------*
*                                                                           *
*   https://github.com/olivier-verville/D2Template                          *
*                                                                           *
*   D2Template core file, do not modify unless you know what you're doing   *
*                                                                           *
*****************************************************************************/

void __fastcall D2TEMPLATE_FatalError(char* szMessage)
{
    MessageBoxA(NULL, szMessage, "D2Template", MB_OK | MB_ICONERROR);
    TerminateProcess(GetCurrentProcess(), -1);
}

BOOL __fastcall D2TEMPLATE_ApplyPatch(void* hGame, const DLLPatchStrc* hPatch)
{
    while (hPatch->nDLL != D2DLL_INVALID)
    {
        int nReturn = 0;
        int nDLL = hPatch->nDLL;
        if (nDLL < 0 || nDLL >= D2DLL_INVALID) return FALSE;
        
        DWORD dwAddress = hPatch->dwAddress;
        if (!dwAddress) return FALSE;

        DWORD dwBaseAddress = gptDllFiles[nDLL].dwAddress;
        if (!dwBaseAddress) return FALSE;

        dwAddress += dwBaseAddress;
        
        DWORD dwData = hPatch->dwData;
        if (hPatch->bRelative){ dwData = dwData - (dwAddress + sizeof(dwData)); }
        
        void* hAddress = (void*)dwAddress;
        DWORD dwOldPage;

        if (hPatch->nPatchSize > 0)
        {
            BYTE Buffer[1024];

            for (size_t i = 0; i < hPatch->nPatchSize; i++)
                Buffer[i] = (BYTE)dwData;

            VirtualProtect(hAddress, hPatch->nPatchSize, PAGE_EXECUTE_READWRITE, &dwOldPage);
            nReturn = WriteProcessMemory(hGame, hAddress, &Buffer, hPatch->nPatchSize, 0);
            VirtualProtect(hAddress, hPatch->nPatchSize, dwOldPage, 0);
        }

        else
        {
            VirtualProtect(hAddress, sizeof(dwData), PAGE_EXECUTE_READWRITE, &dwOldPage);
            nReturn = WriteProcessMemory(hGame, hAddress, &dwData, sizeof(dwData), 0);
            VirtualProtect(hAddress, sizeof(dwData), dwOldPage, 0);
        }
        
        if (nReturn == 0) return FALSE;
        
        hPatch++;
    }
    
    return TRUE;
}

BOOL __fastcall D2TEMPLATE_LoadModules()
{
    for (int i = 0; i < D2DLL_INVALID; i++)
    {
        DLLBaseStrc* hDllFile = &gptDllFiles[i];
        
        void* hModule = GetModuleHandle(hDllFile->szName);
        if (!hModule)
        {
            hModule = LoadLibrary(hDllFile->szName);
        }

        hDllFile->dwAddress = (DWORD)hModule;
    }

    return TRUE;
}

int __fastcall D2TEMPLATE_GetDebugPrivilege()
{
    void* hToken;
    LUID luid;
    TOKEN_PRIVILEGES tokenPrivileges;

    if (OpenProcessToken(GetCurrentProcess(),TOKEN_ALL_ACCESS,&hToken) == 0)
    {
        D2TEMPLATE_FatalError("OpenProcessToken Failed");
        return 0;
    }

    if (LookupPrivilegeValue(0,SE_DEBUG_NAME,&luid) == 0)
    {
        D2TEMPLATE_FatalError("LookupPrivilegeValue Failed");
        CloseHandle(hToken);
        return 0;
    }

    tokenPrivileges.PrivilegeCount = 1;
    tokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    tokenPrivileges.Privileges[0].Luid = luid;
    if (AdjustTokenPrivileges(hToken,0,&tokenPrivileges,sizeof(tokenPrivileges),0,0) == 0)
    {
        D2TEMPLATE_FatalError("AdjustTokenPrivileges Failed");
        CloseHandle(hToken);
        return 0;
    }

    CloseHandle(hToken);
    return 1;
}

int __stdcall DllAttach()
{
    D2TEMPLATE_GetDebugPrivilege();

    void* hGame = GetCurrentProcess();
    if (!hGame) 
    {
        D2TEMPLATE_FatalError("Failed to retrieve process");
        return 0;
    }

    if (!D2TEMPLATE_LoadModules())
    {
        D2TEMPLATE_FatalError("Failed to load modules");
        return 0;
    }

    D2TEMPLATE_ApplyPatch(hGame, gptTemplatePatches);

    return 1;
}

int __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, void* lpReserved)
{
    FILE *f = nullptr;

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		if (!DllAttach())
		{
			D2TEMPLATE_FatalError("Couldn't attach to Diablo II");
		}
		else
		{
			AllocConsole();
			freopen_s(&f, "CONOUT$", "w", stdout);
			HANDLE hStdout = CreateFile(L"CONOUT$", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			SetStdHandle(STD_OUTPUT_HANDLE, hStdout);
			//std::wcout.clear();
			//std::cout.clear();

			std::cout << "=================\n";
			std::cout << "Diablo II - Simple Item Logger v0.1\n";

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			std::cout << "Now with item logging!\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);

			std::cout << "=================\n";
		}
		break;
	case DLL_PROCESS_DETACH:
		fclose(f);
		FreeConsole();
		break;
	}

	return TRUE;
}

DWORD __fastcall GetDllOffset(char* ModuleName, DWORD BaseAddress, int Offset)
{
	if(!BaseAddress)
	{
		//BaseAddress = (DWORD)LoadLibraryA(GetModuleExt(ModuleName));
		char dllName[32] = { '\0' };
		char dllExt[5] = ".dll";
		size_t moduleNameLen = strnlen_s(ModuleName, (sizeof(dllName) / sizeof(dllName[0])));
		size_t dllNameBufferLen = (sizeof(dllName) / sizeof(dllName[0]));
		strncpy_s(dllName, dllNameBufferLen, ModuleName, moduleNameLen);
		strncat_s(dllName, dllNameBufferLen, dllExt, _TRUNCATE);
		BaseAddress = (DWORD)LoadLibraryA(dllName);
	}

	if(Offset < 0)
		return (DWORD)GetProcAddress((HMODULE)BaseAddress,(LPCSTR)(-Offset));

	return BaseAddress + Offset;
}

//char* __fastcall GetModuleExt(char* ModuleName)
//{
//	char DLLExt[] = ".dll";
//	char DLLName[32] = {0};
//	strcpy(DLLName,ModuleName);
//	return strcat(DLLName,DLLExt);
//}