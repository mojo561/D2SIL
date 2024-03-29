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

//reference: https://d2mods.info/forum/viewtopic.php?f=8&t=62109&p=482668&hilit=D2net#p482668

//moved to framework.h
//#define WIN32_LEAN_AND_MEAN
//let's use secure functions...
//#define _CRT_SECURE_NO_DEPRECATE
//https://docs.microsoft.com/en-us/cpp/porting/modifying-winver-and-win32-winnt?view=msvc-160
//moved to framework.h
//#define _WIN32_WINNT 0x600

//already included in framework.h
//#include <windows.h>
//#include <stdio.h>
//#include <stdlib.h>

static const DWORD DLLBASE_BNCLIENT     =   (DWORD)LoadLibraryA("Bnclient.dll");
static const DWORD DLLBASE_D2CLIENT     =   (DWORD)LoadLibraryA("D2Client.dll");
static const DWORD DLLBASE_D2CMP        =   (DWORD)LoadLibraryA("D2CMP.dll");
static const DWORD DLLBASE_D2COMMON     =   (DWORD)LoadLibraryA("D2Common.dll");
static const DWORD DLLBASE_D2DDRAW      =   (DWORD)LoadLibraryA("D2DDraw.dll");
static const DWORD DLLBASE_D2DIRECT3D   =   (DWORD)LoadLibraryA("D2Direct3D.dll");
static const DWORD DLLBASE_D2GAME       =   (DWORD)LoadLibraryA("D2Game.dll");
static const DWORD DLLBASE_D2GDI        =   (DWORD)LoadLibraryA("D2Gdi.dll");
static const DWORD DLLBASE_D2GFX        =   (DWORD)LoadLibraryA("D2Gfx.dll");
static const DWORD DLLBASE_D2GLIDE      =   (DWORD)LoadLibraryA("D2Glide.dll");
static const DWORD DLLBASE_D2LANG       =   (DWORD)LoadLibraryA("D2Lang.dll");
static const DWORD DLLBASE_D2LAUNCH     =   (DWORD)LoadLibraryA("D2Launch.dll");
static const DWORD DLLBASE_D2MCPCLIENT  =   (DWORD)LoadLibraryA("D2MCPClient.dll");
static const DWORD DLLBASE_D2MULTI      =   (DWORD)LoadLibraryA("D2Multi.dll");
static const DWORD DLLBASE_D2NET        =   (DWORD)LoadLibraryA("D2Net.dll");
static const DWORD DLLBASE_D2SOUND      =   (DWORD)LoadLibraryA("D2Sound.dll");
static const DWORD DLLBASE_D2WIN        =   (DWORD)LoadLibraryA("D2Win.dll");
static const DWORD DLLBASE_FOG          =   (DWORD)LoadLibraryA("Fog.dll");
static const DWORD DLLBASE_STORM        =   (DWORD)LoadLibraryA("Storm.dll");
static const DWORD DLLBASE_IJL11        =   (DWORD)LoadLibraryA("ijl11.dll");
static const DWORD DLLBASE_BINKW32      =   (DWORD)LoadLibraryA("binkw32.dll");
static const DWORD DLLBASE_SMACKW32     =   (DWORD)LoadLibraryA("SmackW32.dll");

#include "D2Constants.h"
#include "D2Structs.h"
#include "D2Ptrs.h"
#include "D2Vars.h"
#include "D2Strings.h"

#include "TemplateIncludes.h"

struct DLLBaseStrc
{
    //char* szName;
	LPCWSTR szName;
    DWORD dwAddress;
};

struct DLLPatchStrc
{
	/*
	This defines in which of the game's library this patch should be applied.
	This is needed so that the template's patcher can retrieve the said library's
	base address (as the patcher uses relative addresses patch definitions, to keep compatibility in case of reallocation).
	The dll name definitions are found in DLLmain.h.
	It is also possible to extend this in order to have it patch custom libraries that are not defined in the original template
	*/
    int nDLL;
	/*
	This is the relative address at which the patch should be applied.
	*/
    DWORD dwAddress;
	/*
	This is the data you want to patch. This can be a function, some bytes, whatever you want.
	*/
    DWORD dwData;
	/*
	This tells the patcher whether it should consider this patch as a relative address.
	*/
    BOOL bRelative;
	/*
	This here defines the number of bytes to patch. Setting this to 0 will make it patch a DWORD.
	You should use non-zero values only when you want to make big repetitive patches, such as nop blocks.
	*/
    size_t nPatchSize;
};

enum D2TEMPLATE_DLL_FILES
{
    D2DLL_BINKW32,
    D2DLL_BNCLIENT,
    D2DLL_D2CLIENT,
    D2DLL_D2CMP,
    D2DLL_D2COMMON,
    D2DLL_D2DDRAW,
    D2DLL_D2DIRECT3D,
    D2DLL_D2GAME,
    D2DLL_D2GDI,
    D2DLL_D2GFX,
    D2DLL_D2GLIDE,
    D2DLL_D2LANG,
    D2DLL_D2LAUNCH,
    D2DLL_D2MCPCLIENT,
    D2DLL_D2MULTI,
    D2DLL_D2NET,
    D2DLL_D2SOUND,
    D2DLL_D2WIN,
    D2DLL_FOG,
    D2DLL_IJL11,
    D2DLL_SMACKW32,
    D2DLL_STORM,
    D2DLL_INVALID
};

static DLLBaseStrc gptDllFiles [] =
{
    {L"Binkw32.dll",         NULL},
    {L"BnClient.dll",        NULL},
    {L"D2Client.dll",        NULL},
    {L"D2CMP.dll",           NULL},
    {L"D2Common.dll",        NULL},
    {L"D2DDraw.dll",         NULL},
    {L"D2Direct3D.dll",      NULL},
    {L"D2Game.dll",          NULL},
    {L"D2Gdi.dll",           NULL},
    {L"D2Gfx.dll",           NULL},
    {L"D2Glide.dll",         NULL},
    {L"D2Lang.dll",          NULL},
    {L"D2Launch.dll",        NULL},
    {L"D2MCPClient.dll",     NULL},
    {L"D2Multi.dll",         NULL},
    {L"D2Net.dll",           NULL},
    {L"D2Sound.dll",         NULL},
    {L"D2Win.dll",           NULL},
    {L"Fog.dll",             NULL},
    {L"Ijl11.dll",           NULL},
    {L"SmackW32.dll",        NULL},
    {L"Storm.dll",           NULL},
};

void __fastcall D2TEMPLATE_FatalError(char* szMessage);
DWORD __fastcall GetDllOffset(char* ModuleName, DWORD BaseAddress, int Offset);
//char* __fastcall GetModuleExt(char* ModuleName);