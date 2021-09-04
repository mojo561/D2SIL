#pragma once

#include "D2PatchConst.h"

/****************************************************************************
*                                                                           *
*   D2Patch.h                                                               *
*   Copyright (C) Olivier Verville                                          *
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
*   This file is where you declare all your patches, in order to inject     *
*   your own code into the game. Each patch should be declared in the       *
*   array, in order to be handled by D2Template's patcher                   *
*                                                                           *
*****************************************************************************/

/*
Patch Defintions Examples:
- The following patch would patch a block of 52 NOP's at D2Client.0x9A6F1: {D2DLL_D2CLIENT, 0x9A6F1, (DWORD)PATCH_NOPBLOCK, FALSE, 0x34}

- The following patch would replace the call to D2Client.0xC39E0 with our own function: {D2DLL_D2CLIENT, 0x4437C, (DWORD)D2UI_Main, TRUE, 0x00}
Notice we don't patch D2Client.0x4437B here, but rather one byte later as we do not want to overwrite the CALL instruction.

- Patching a function call (where there is no call instruction originally):
{D2DLL_D2CLIENT, 0x8B1DE, (DWORD)PATCH_CALL, FALSE, 0x00}, //must be defined first (we're patching a location where there is no call instruction originally, so we need to patch it ourself.)
{D2DLL_D2CLIENT, 0x8B1DF, (DWORD)DRLGUI_LevelBackground, TRUE, 0x00}

- You can do the same thing with a jump if you want:
{D2DLL_FOG, 0x17F60, (DWORD)PATCH_JMP, FALSE, 0x00},
{D2DLL_FOG, 0x17F61, (DWORD)SAVEFILE_GetSavePath, TRUE, 0x00}
*/
static const DLLPatchStrc gptTemplatePatches[] =
{
    /*
        All your patches should be added here
        Keep it organized to save yourself some headache
    */

	{D2DLL_D2GAME, 0xD014D, (DWORD32)DetourFuncs::detourAllocHoverText, TRUE, 0x00},

	//works for all except items that are crafted by the player
	{D2DLL_D2GAME, 0x1101B, (DWORD32)PATCH_CALL, FALSE, 0x00},
	{D2DLL_D2GAME, 0x1101C, (DWORD32)ItemPrinterDetour::detourPrintItemName, TRUE, 0x00},


	//fired when entering a new game... most D2 vars will not be initialized at this point in the code
	{D2DLL_D2GAME, 0x2C4D3, (DWORD32)PATCH_CALL, FALSE, 0x00},
	{D2DLL_D2GAME, 0x2C4D4, (DWORD32)DetourFuncs::detourEnterGame, TRUE, 0x00},
    
    {D2DLL_INVALID} // this must be the last entry in the array!
};

// end of file --------------------------------------------------------------