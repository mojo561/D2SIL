#pragma once

/****************************************************************************
*                                                                           *
*   D2Ptrs.h                                                                *
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
*   This file is used to declare pointers, be it function or variable       *
*   pointers, from the game's libraries.                                    *
*                                                                           *
*   It is recommended that you keep this file organized by which dll the    *
*   pointer is imported from, what type of pointer it is, etc. Ordering     *
*   them by address can also end up being very useful                       *
*                                                                           *
*****************************************************************************/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  These are the macros used by the template core to declare                                                                                                                                                                   ///
//  pointers. Do not touch unless you know what you're doing                                                                                                                                                                    ///
//                                                                                                                                                                                                                              ///
//                                                                                                                                                                                                                              ///
#ifdef _MSC_VER // MS Compiler                                                                                                                                                                                                  ///
#define D2FUNC(DLL, NAME, RETURN, CONV, ARGS, OFFSET) typedef RETURN (CONV* DLL##_##NAME##_t) ARGS; __declspec(selectany) extern DLL##_##NAME##_t DLL##_##NAME = (DLL##_##NAME##_t)GetDllOffset(#DLL, DLLBASE_##DLL, OFFSET);   ///
#define D2VAR(DLL, NAME, TYPE, OFFSET) typedef TYPE DLL##_##NAME##_vt; __declspec(selectany) extern DLL##_##NAME##_vt * DLL##_##NAME = (DLL##_##NAME##_vt *)GetDllOffset(#DLL, DLLBASE_##DLL, OFFSET);                          ///
#define D2PTR(DLL, NAME, OFFSET) __declspec(selectany) extern DWORD NAME = GetDllOffset(#DLL, DLLBASE_##DLL, OFFSET);                                                                                                           ///
#else // GCC Compiler                                                                                                                                                                                                           ///
#define D2FUNC(DLL, NAME, RETURN, CONV, ARGS, OFFSET) typedef RETURN (CONV* DLL##_##NAME##_t) ARGS; DLL##_##NAME##_t DLL##_##NAME __attribute__((weak)) = (DLL##_##NAME##_t)GetDllOffset(#DLL, DLLBASE_##DLL, OFFSET);          ///
#define D2VAR(DLL, NAME, TYPE, OFFSET) typedef TYPE DLL##_##NAME##_vt; DLL##_##NAME##_vt * DLL##_##NAME __attribute__((weak)) = (DLL##_##NAME##_vt *)GetDllOffset(#DLL, DLLBASE_##DLL, OFFSET);                                 ///
#define D2PTR(DLL, NAME, OFFSET) DWORD NAME __attribute__((weak)) = GetDllOffset(#DLL, DLLBASE_##DLL, OFFSET);                                                                                                                  ///
#endif                                                                                                                                                                                                                          ///
extern DWORD __fastcall GetDllOffset(char* ModuleName, DWORD BaseAddress, int Offset);                                                                                                                                          ///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************
*                                                                               *
*   D2GAME.DLL POINTERS                                                         *
*                                                                               *
*********************************************************************************/
//TODO: New/untested
D2VAR(D2GAME, ptrGame, Game*, 0x110C04);

D2VAR(D2GAME, ptrPlayersX, DWORD32*, 0x111C1C);

D2VAR(D2GAME, OnGameEnterMagicReturnValue, DWORD32*, 0x111C30);

/********************************************************************************
*                                                                               *
*   D2LANG.DLL POINTERS                                                       *
*                                                                               *
*********************************************************************************/
/*
	Function:		GetTableString
	Address:		D2Lang.#10003
	Notes:
	gets a string based on a table index...
*/
D2FUNC(D2LANG, GetTableString, wchar_t* , __fastcall, (DWORD32 dwTableIndex), -10003);

/*
	Function:		ToUnicode
	Address:		D2Lang.#10051
	Notes:
	Works!
	According to IDA:
	Exported entry 10051. ?toUnicode@Unicode@@SIPAU1@PAU1@PBDH@Z
	struct Unicode *__fastcall Unicode::toUnicode(struct Unicode *, const char *, int)
*/
D2FUNC(D2LANG, ToUnicode, wchar_t* , __fastcall, (wchar_t* szBuffer, const char* szSource, int nSourceLength), -10051);

/********************************************************************************
*                                                                               *
*   D2CLIENT.DLL POINTERS                                                       *
*                                                                               *
*********************************************************************************/

D2VAR(D2CLIENT, ptrPlayerUnit, Unit*, 0x11B800);

/*
	Function:		ITEMS_GetItemName
	Address:		D2CLIENT + 0x914F0
	Notes:
	returns 0 on failure. Item name is stored in szBuffer as a unicode string.
*/
D2FUNC(D2CLIENT, ITEMS_GetItemName, uint32_t, __stdcall, (Unit* ptrItemUnit, wchar_t* szBuffer, DWORD dwBufferLen), 0x914F0);

/*
	Function:		d2client_827C0
	Address:		D2CLIENT + 0x827C0
	Notes:
	TODO: unused - erase?
*/
D2FUNC(D2CLIENT, unk_827C0, void, __stdcall, (void), 0x827C0);

/*
	Function:		ITEMS_GetAffixText
	Address:		D2CLIENT + 0x560B0
	Notes:
	Gets all magic affix text for a given item and stores it in a wchar buffer (for now, buffer length should be 0x400).
	A wchar buffer must be passed to EDI before calling this function. The modified buffer is returned in EAX as well as EDI.
	No idea what args 2 and 3 are, just pass in 1 and 0 respectively for now...
*/
D2FUNC(D2CLIENT, ITEMS_GetAffixText, wchar_t*, __stdcall, (Unit* ptrItemUnit, DWORD32 unk_2, DWORD32 unk_3), 0x560B0);

/*
	Function:		CHAT_PrintClientMessage
	Address:		D2CLIENT + 0x7D850
	Notes:
	Credit: BH slashdiablo project
*/
D2FUNC(D2CLIENT, CHAT_PrintClientMessage, void, __stdcall, (wchar_t* wszMessage, BYTE nColor),0x7D850);

/********************************************************************************
*                                                                               *
*   D2COMMON.DLL POINTERS                                                       *
*                                                                               *
*********************************************************************************/

D2VAR(D2COMMON, sgptDataTables, sgptDataTable*, 0x99E1C);

D2VAR(D2COMMON, ptrMagicAffixTable, D2AutoMagicTxt*, 0x9FBC0);
D2VAR(D2COMMON, ptrMagicAffixTableLength, DWORD32*, 0x9FBB8);

//////////////////////////////////////////
//TODO:

/*
	Function:		STATS_GetExpForNextLevel
	Address:		D2Common.#10399
	Notes:

DWORD __stdcall STATS_GetExpForNextLevel(int nClass, int nLevel)
*/

/*
	Function:		ITEMCALC_Eval
	Address:		D2Common.#10428
	Notes:

int __stdcall ITEMCALC_Eval(D2UnitStrc* pUnit, D2UnitStrc* pItem, DWORD dwCalc)
*/

//////////////////////////////////////////

/*
	Function:		ITEMRECORDS_GetItemQualityRecord
	Address:		D2Common.#11007
	Notes:
	returns a QualityItems.txt record ptr based on a given file index, or nullptr if the index is invalid.
	The file index is retrieved from a superior item's itemdata unique ID (ptrItemData->uniqueID).
*/
D2FUNC(D2COMMON, ITEMRECORDS_GetItemQualityRecord, QualityItemsTXT*, __stdcall, (DWORD32 dwItemQualityIndex), -11007);

/*
	Function:		D2COMMON_GetMagicAffixTable
	Address:		D2Common.#10492
	Notes:
	returns ptr to DWORD magic affix table length. Add to this ptr to get prefix (+0xC) suffix (+8), or automagic(+0x10) tables.
	TODO: check AffixTxtTable in D2BinFile.h
*/
D2FUNC(D2COMMON, GetMagicAffixTable, void*, __stdcall, (void), -10492);

/*
	Function:		DRLG_GetRoomFromUnit
	Address:		D2Common.#10331
	Notes:
	this function always(?) returns null if the item is in a town.
*/
D2FUNC(D2COMMON, DRLG_GetRoomFromUnit, Room*, __stdcall, (Unit* ptrUnit), -10331);

/*
	Function:		UNITS_GetOffsetX
	Address:		D2Common.#10651
	Notes: Items not on the ground (equipped or in inventory) will have an X offset of 0
	TODO: D2Common.#11142 for offsetY?
*/
D2FUNC(D2COMMON, UNITS_GetOffsetX, int, __stdcall, (Unit* ptrUnit), -10651);

/*
	Function:		TXT_GetSetItemRecord
	Address:		D2Common.#10218
	Notes:
*/
D2FUNC(D2COMMON, TXT_GetSetItemRecord, SetItemsBIN* , __stdcall, (Unit* ptrItemUnit), -10218);

/*
	Function:		TXT_GetRareAffixRecord
	Address:		D2Common.#10365
	Notes:
	returns txt record for the given rare affix
*/
D2FUNC(D2COMMON, TXT_GetRareAffixRecord, RareAffixTable* , __stdcall, (WORD rareAffix), -10365);

/*
	Function:		ITEMS_GetRareSuffix
	Address:		D2Common.#10433
	Notes:
	returns ptrItemUnit->itemData->dwRareSuffix
*/
D2FUNC(D2COMMON, ITEMS_GetRareSuffix, WORD, __stdcall, (Unit* ptrItemUnit), -10433);

/*
	Function:		ITEMS_GetRarePrefix
	Address:		D2Common.#10380
	Notes:
	returns ptrItemUnit->itemData->dwRarePrefix
*/
D2FUNC(D2COMMON, ITEMS_GetRarePrefix, WORD, __stdcall, (Unit* ptrItemUnit), -10380);

/*
	Function:		ITEMRECORDS_GetItemMagicPrefix
	Address:		D2Common.#10257
	Notes:
	Returns a row index in MagicPrefix.txt (see: affixdump10.csv), or 0 if the prefix is invalid
*/
D2FUNC(D2COMMON, ITEMRECORDS_GetItemMagicPrefix, WORD, __stdcall, (Unit* ptrItemUnit, DWORD dwIndex), -10257);

/*
	Function:		TXT_GetMagicAffixRecord
	Address:		D2Common.#10248
	Notes:
	nRecord obtained from either D2Common.#10257 (ITEMRECORDS_GetItemMagicPrefix) or D2Common.#11028 (ITEMRECORDS_GetItemMagicSuffix)
*/
D2FUNC(D2COMMON, TXT_GetMagicAffixRecord, D2AutoMagicTxt* , __stdcall, (int nRecord), -10248);

/*
	Function:		ITEMRECORDS_GetItemMagicSuffix
	Address:		D2Common.#11028
	Notes:
	Returns a row index in MagicSuffix.txt (see also: affixdump10.csv), or 0 if the prefix is invalid
*/
D2FUNC(D2COMMON, ITEMRECORDS_GetItemMagicSuffix, WORD, __stdcall, (Unit* ptrItemUnit, DWORD dwIndex), -11028);

/*
	Function:		ITEMRECORDS_GetQualityStringFromIndex
	Address:		D2Common.#10961
	Notes:
	get quality string from lowquality.txt row index (see: d2common_10620). Works only for items with quality == 1 (see: d2common_10106)
;proof:
;X:\Games\Diablo 2 1.13\Diablo II\D2SE\CORES\1.13c\D2Client.dll	000000006FAB0000	0000000000135000
;X:\Games\Diablo 2 1.13\Diablo II\D2SE\CORES\1.13c\D2Common.dll	000000006FD50000	00000000000A9000
D2Client.dll:6FB416BD push    ebx
D2Client.dll:6FB416BE call    j_d2common_10620_0
D2Client.dll:6FB416C3 push    eax
D2Client.dll:6FB416C4 call    j_d2common_10961_0 ; returns char ptr to Dword(D2Common+9FD9C)+(0x22*EAX), or null if EAX >= value stored in dword_6FDEFD98 (usually 4)
D2Client.dll:6FB416C9 mov     esi, eax
D2Client.dll:6FB416CB test    esi, esi
*/
D2FUNC(D2COMMON, ITEMRECORDS_GetQualityStringFromIndex, char*, __stdcall, (DWORD fileIndex), -10961);

/*
	Function:		ITEMFLAGS_CheckEthereal
	Address:		D2Common.#10225
	Notes:
	returns ptrItemUnit->ptrItemData->dwItemFlags & unk_400000 (sample val: 0x905A4D)
*/
D2FUNC(D2COMMON, ITEMFLAGS_CheckEthereal, BOOL, __stdcall, (Unit* ptrItemUnit), -10225);

/*
	Function:		UNITS_GetUnitStat
	Address:		D2Common.#10973
	Notes:
	pretty sure it's safe to pass 0 for arg Stat2. 0xC2 = itemsocket stat? Check ItemStatCost.txt
*/
D2FUNC(D2COMMON, UNITS_GetUnitStat, DWORD, __stdcall, (Unit* ptrUnit, DWORD stat, DWORD stat2), -10973);

/*
	Function:		ITEMS_GetLevel
	Address:		D2Common.#10086
	Notes:
	...
*/
D2FUNC(D2COMMON, ITEMS_GetLevel, int, __stdcall, (Unit* ptrItemUnit), -10086);

/*
	Function:		ITEMS_IsMagical
	Address:		D2Common.#10516
	Notes:
	returns 1 if pItem->itemData->dwQualityNo >= pItem->dwUnitType && pItem->itemData->dwQualityNo == 9 (validates ptrs as well...)
	unique, blue, and rare items are all magical (including normal items like ammys, rings, etc)
*/
D2FUNC(D2COMMON, ITEMS_IsMagical, BOOL, __stdcall, (Unit* ptrItemUnit), -10516);//D2FUNC(D2COMMON, ITEMS_IsMagical, BOOL, __stdcall, (uintptr_t* ptrItemUnit), -10516);

/*
	Function:		ITEMRECORDS_GetItemRecord
	Address:		D2Common.#10695
	Notes:
	returns 1 if pItem->itemData->dwQualityNo >= pItem->dwUnitType && pItem->itemData->dwQualityNo == 9 (validates ptrs as well...)
*/
D2FUNC(D2COMMON, ITEMRECORDS_GetItemRecord, D2ItemsTxt*, __stdcall, (int dwItemFileIndex), -10695);

/*
	Function:		ITEMRECORDS_GetMagic
	Address:		D2Common.#10710
	Notes:
	does not determine if an item is actually magic or not...
*/
D2FUNC(D2COMMON, ITEMRECORDS_GetMagic, BYTE, __stdcall, (Unit* ptrItemUnit), -10710);

/*
	Function:		ITEMRECORDS_GetRare
	Address:		D2Common.#11036
	Notes:
	does not determine if an item is actually rare or not...
*/
D2FUNC(D2COMMON, ITEMRECORDS_GetRare, BYTE, __stdcall, (Unit* ptrItemUnit), -11036);

/*
	Function:		ITEMRECORDS_GetUnique
	Address:		D2Common.#10119
	Notes:
	does not determine if an item is actually unique or not...
*/
D2FUNC(D2COMMON, ITEMRECORDS_GetUnique, BYTE, __stdcall, (Unit* ptrItemUnit), -10119);

/*
	Function:		ITEMS_GetQuality
	Address:		D2Common.#10106
	Notes:
	Returns 2 if: ptrItemUnit is null, ptrItemUnit's unit type is not set to 0x4, or ptrItemUnit->ptrItemData is null
	example usage:
	D2Client.dll:6FB1DB86 push    esi
	D2Client.dll:6FB1DB87 call    j_d2common_10106_0
	D2Client.dll:6FB1DB8C cmp     eax, 5
	An item's quality is only valid if it is between 0 and 0xA
*/
D2FUNC(D2COMMON, ITEMS_GetQuality, int, __stdcall, (Unit* ptrItemUnit), -10106);

/*
	Function:		ITEMRECORDS_GetItemIndexFromCode
	Address:		D2Common.#10814
	Notes:
	...
*/
D2FUNC(D2COMMON, ITEMRECORDS_GetItemIndexFromCode, int, __stdcall, (DWORD dwItemCode), -10814);

/*
	Function:		ITEMRECORDS_GetItemTypeFromItem
	Address:		D2Common.#11088
	Notes:
	returns file row index in ItemTypes.txt.
*/
D2FUNC(D2COMMON, ITEMRECORDS_GetItemTypeFromItem, int, __stdcall, (Unit* ptrItemUnit), -11088);

/*
	Function:		ITEMRECORDS_GetCodeFromUnit
	Address:		D2Common.#10802
	Notes:
	returns item code.
*/
D2FUNC(D2COMMON, ITEMRECORDS_GetCodeFromUnit, DWORD, __stdcall, (Unit* ptrItemUnit), -10802);

/*
	Function:		ITEMTYPERECORDS_GetNormal
	Address:		D2Common.#10556
	Notes:
	returns true or false.
*/
D2FUNC(D2COMMON, ITEMTYPERECORDS_GetNormal, BYTE, __stdcall, (Unit* ptrItemUnit), -10556);

/*
	Function:		ITEMS_GetFileIndex TODO: rename - I think this is for unique items only
	Address:		D2Common.#10620
	Notes:
	returns (int)pItem[0x28] (ptrUnit->dwInitSeed).
	This value is used for functions such as d2common_10961 (with fileIndex stored in eax, d2common_10961 returns char ptr to Dword(D2Common+9FD9C)+(0x22*EAX), or null if EAX >= value stored in dword_6FDEFD98 (usually 4))
	Return values are used differently depending on the item (does not denote item quality), a negative result indicates failure
*/
D2FUNC(D2COMMON, ITEMS_GetFileIndex, int, __stdcall, (Unit* ptrItemUnit), -10620);

/*
	Function:		CHAT_AllocHoverText
	Address:		D2Common.#10454 (6FD68280 - 6FD50000 = 0x18280)
	Notes:
	chat starting with '!'.
	dwFrame's value comes from D2Client.dll+113ACE
*/
D2FUNC(D2COMMON, CHAT_AllocHoverText, uintptr_t*, __stdcall, (void* pMemoryPool, char *szText, DWORD dwFrame), -10454);

/*
	Function:		CHAT_FreeHoverText
	Address:		D2Common.#10422 (6FD68260 - 6FD50000 = 0x18260)
	Notes:
	free as in C's 'free', chat is wiped from screen here.
	as per disasm, pMemoryPool is always explicitly set to 0
*/
D2FUNC(D2COMMON, CHAT_FreeHoverText, void, __stdcall, (void* pMemoryPool, uintptr_t* pHoverText), -10422);

/*
	Function:		CHAT_SetHoverLocale
	Address:		D2Common.#10097 (0x52581E0 - 0x5240000 = 0x181E0)
	Notes:
	locale looks to be 0 for English?
*/
D2FUNC(D2COMMON, CHAT_SetHoverLocale, void, __stdcall, (uintptr_t* pHoverText, DWORD nLocale), -10097);

/*
	Function:		UNITS_Update
	Address:		D2Common.#10158
	Notes:
	void __stdcall UNITS_Update(D2UnitStrc* pUnit)
	Remember to update unit flags after calling this function... eg:
	MOV EAX, [ESI + 0xC4]
	OR EAX, 0x100
*/
D2FUNC(D2COMMON, UNITS_Update, void, __stdcall, (Unit* ptrUnit), -10158);

// end of file -----------------------------------------------------------------