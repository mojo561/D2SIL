#pragma once

//FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE
static const WORD FOREGROUND_WHITE = 0x7;
//BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE
static const WORD BACKGROUND_WHITE = 0x70;
//FOREGROUND_BLUE | FOREGROUND_GREEN
static const WORD FOREGROUND_TEAL = FOREGROUND_BLUE | FOREGROUND_GREEN;
//FOREGROUND_RED | FOREGROUND_BLUE
static const WORD FOREGROUND_PURPLE = FOREGROUND_RED | FOREGROUND_BLUE;
//FOREGROUND_GREEN | FOREGROUND_RED
static const WORD FOREGROUND_YELLOW = FOREGROUND_GREEN | FOREGROUND_RED;

///////////

static struct rulemgr
{
	RuleEvaluatorImpl<D2C_ItemCodes> RuleEvalJunkItemCode;
	RuleEvaluatorImpl<D2C_ItemTypes> RuleEvalJunkItemType;
	RuleEvaluatorImpl<D2C_ItemTypes> RuleEvalILvlPrint;

	//TODO:new/untested
	RuleEvaluatorImpl<D2C_Stat> RuleEvalStatMinDmg;
	RuleEvaluatorImpl<D2C_Stat> RuleEvalStatMaxDmg;
	RuleEvaluatorImpl<D2C_Stat> RuleEvalStatDmgPct;
	///////////////////

	//TODO: temp func for loading default rules (until txt config support)
	void reloadRules()
	{
		RuleEvalJunkItemCode.delRules();
		RuleEvalJunkItemType.delRules();
		RuleEvalILvlPrint.delRules();

		RuleImpl<D2C_ItemCodes> ignoreRules1[] = {
			RuleImpl<D2C_ItemCodes>::RuleImpl(D2C_ItemCodes::ITEMCODE_GOLD),
			RuleImpl<D2C_ItemCodes>::RuleImpl(D2C_ItemCodes::ITEMCODE_BOLTS),
			RuleImpl<D2C_ItemCodes>::RuleImpl(D2C_ItemCodes::ITEMCODE_ARROWS),
			RuleImpl<D2C_ItemCodes>::RuleImpl(D2C_ItemCodes::ITEMCODE_STAMINA),
			RuleImpl<D2C_ItemCodes>::RuleImpl(D2C_ItemCodes::ITEMCODE_ANTIDOTE),
			RuleImpl<D2C_ItemCodes>::RuleImpl(D2C_ItemCodes::ITEMCODE_THAWPOT),
			RuleImpl<D2C_ItemCodes>::RuleImpl(D2C_ItemCodes::ITEMCODE_REJUV)
		};
	
		RuleImpl<D2C_ItemTypes> ignoreRules2[] = {
			RuleImpl<D2C_ItemTypes>::RuleImpl(D2C_ItemTypes::ITEMTYPE_HEALPOT),
			RuleImpl<D2C_ItemTypes>::RuleImpl(D2C_ItemTypes::ITEMTYPE_MANAPOT),
			RuleImpl<D2C_ItemTypes>::RuleImpl(D2C_ItemTypes::ITEMTYPE_MISSPOT),
			RuleImpl<D2C_ItemTypes>::RuleImpl(D2C_ItemTypes::ITEMTYPE_SCROLL)
		};
	
		RuleImpl<D2C_ItemTypes> includeRules1[] = {
			RuleImpl<D2C_ItemTypes>::RuleImpl(D2C_ItemTypes::ITEMTYPE_JEWEL),
			RuleImpl<D2C_ItemTypes>::RuleImpl(D2C_ItemTypes::ITEMTYPE_RING),
			RuleImpl<D2C_ItemTypes>::RuleImpl(D2C_ItemTypes::ITEMTYPE_AMULET),
			RuleImpl<D2C_ItemTypes>::RuleImpl(D2C_ItemTypes::ITEMTYPE_CHARM_SMALL),
			RuleImpl<D2C_ItemTypes>::RuleImpl(D2C_ItemTypes::ITEMTYPE_CHARM_GRAND)
		};

		//TODO:new
		RuleImpl<D2C_Stat> minDmgStats[] = {
			RuleImpl<D2C_Stat>::RuleImpl(D2C_Stat::STATS_MINDAMAGE),
			RuleImpl<D2C_Stat>::RuleImpl(D2C_Stat::STATS_SECONDARY_MINDAMAGE),
			RuleImpl<D2C_Stat>::RuleImpl(D2C_Stat::STATS_ITEM_THROW_MINDAMAGE)
		};

		RuleImpl<D2C_Stat> maxDmgStats[] = {
			RuleImpl<D2C_Stat>::RuleImpl(D2C_Stat::STATS_MAXDAMAGE),
			RuleImpl<D2C_Stat>::RuleImpl(D2C_Stat::STATS_SECONDARY_MAXDAMAGE),
			RuleImpl<D2C_Stat>::RuleImpl(D2C_Stat::STATS_ITEM_THROW_MAXDAMAGE)
		};

		RuleImpl<D2C_Stat> pctDmgStats[] = {
			RuleImpl<D2C_Stat>::RuleImpl(D2C_Stat::STATS_ITEM_MAXDAMAGE_PERCENT),
			RuleImpl<D2C_Stat>::RuleImpl(D2C_Stat::STATS_ITEM_MINDAMAGE_PERCENT)
		};
		//////////

		for (size_t i = 0; i < _countof(ignoreRules1); ++i)
		{
			RuleEvalJunkItemCode.addRule(ignoreRules1[i]);
		}
	
		for (size_t i = 0; i < _countof(ignoreRules2); ++i)
		{
			RuleEvalJunkItemType.addRule(ignoreRules2[i]);
		}
	
		for (size_t i = 0; i < _countof(includeRules1); ++i)
		{
			RuleEvalILvlPrint.addRule(includeRules1[i]);
		}

		//TODO: new
		for (size_t i = 0; i < _countof(minDmgStats); ++i)
		{
			RuleEvalStatMinDmg.addRule(minDmgStats[i]);
		}
		for (size_t i = 0; i < _countof(maxDmgStats); ++i)
		{
			RuleEvalStatMaxDmg.addRule(maxDmgStats[i]);
		}
		for (size_t i = 0; i < _countof(pctDmgStats); ++i)
		{
			RuleEvalStatDmgPct.addRule(pctDmgStats[i]);
		}
		///////////
	}
} RuleManager;

namespace CommonD2Funcs
{
	//c++ functions have external linkage by default

	__declspec(dllexport) Unit* __stdcall getPlayerUnit(void)
	{
		if (*D2CLIENT_ptrPlayerUnit != nullptr)
		{
			return reinterpret_cast<Unit*>( *D2CLIENT_ptrPlayerUnit );
		}
		return nullptr;
	}

	__declspec(naked) void WINAPI getItemAffixText(Unit* ptrItemUnit, wchar_t* szAffixTextBuffer)
	{
		__asm
		{
			MOV EAX, [ESP + 0x4]
			PUSH EDI
			MOV EDI, [ESP + 0xC]
			PUSH 0
			PUSH 1
			PUSH EAX
			CALL D2CLIENT_ITEMS_GetAffixText
			POP EDI
			RETN 8
		}
	}

	__declspec(dllexport) bool __stdcall checkFlag(Unit* ptrItemUnit, D2C_ItemFlags flag)
	{
		if (ptrItemUnit->ptItemData != nullptr)
		{
			int dwFlag = static_cast<int>(flag);
			return (ptrItemUnit->ptItemData->flags2 & dwFlag) == dwFlag;
		}
		return false;
	}

	__declspec(dllexport) bool __stdcall checkPropertyModContainsStat(DWORD32 modCode, WORD statID)
	{
		if (modCode >= (*D2COMMON_sgptDataTables)->dwProportiesRecs)
			return false;
		if (statID >= (*D2COMMON_sgptDataTables)->dwItemStatCostRecs)
			return false;

		PropertiesBIN* ptrProperties = ((*D2COMMON_sgptDataTables)->pPropertiesTxt) + modCode;
		return	(ptrProperties->stat1 == statID) ||
				(ptrProperties->stat2 == statID) ||
				(ptrProperties->stat3 == statID) ||
				(ptrProperties->stat4 == statID) ||
				(ptrProperties->stat5 == statID) ||
				(ptrProperties->stat6 == statID) ||
				(ptrProperties->stat7 == statID);
	}

	__declspec(dllexport) WORD __stdcall findModContainingStat(D2AutoMagicTxt* ptrMagicPrefixRecord, const D2Stat &stat)
	{
		WORD rvalModCode = (std::numeric_limits<WORD>::max)();

		if (ptrMagicPrefixRecord == nullptr)
			return rvalModCode;

		if (CommonD2Funcs::checkPropertyModContainsStat(ptrMagicPrefixRecord->dwMod1Code, static_cast<WORD>(stat.id)))
			rvalModCode = ptrMagicPrefixRecord->dwMod1Code;
		else if (CommonD2Funcs::checkPropertyModContainsStat(ptrMagicPrefixRecord->dwMod2Code, static_cast<WORD>(stat.id)))
			rvalModCode = ptrMagicPrefixRecord->dwMod2Code;
		else if (CommonD2Funcs::checkPropertyModContainsStat(ptrMagicPrefixRecord->dwMod3Code, static_cast<WORD>(stat.id)))
			rvalModCode = ptrMagicPrefixRecord->dwMod3Code;
		return rvalModCode;
	}

	__declspec(dllexport) DWORD32 __stdcall findModMax(D2AutoMagicTxt* ptrMagicPrefixRecord, DWORD32 dwModCode)
	{
		DWORD32 rvalModMax = 0;
	
		if (ptrMagicPrefixRecord == nullptr)
			return rvalModMax;
	
		if (ptrMagicPrefixRecord->dwMod1Code == dwModCode)
			rvalModMax = ptrMagicPrefixRecord->dwMod1Max;
		else if (ptrMagicPrefixRecord->dwMod2Code == dwModCode)
			rvalModMax = ptrMagicPrefixRecord->dwMod2Max;
		else if (ptrMagicPrefixRecord->dwMod3Code == dwModCode)
			rvalModMax = ptrMagicPrefixRecord->dwMod3Max;
		return rvalModMax;
	}

	__declspec(dllexport) void __stdcall doSpecDMGModPrint(DWORD32 modCode, D2AutoMagicTxt* ptrMagicAffixRecord, Unit* ptrItemUnit, DWORD32 dwMaxStatValue)
	{
		if (modCode >= (*D2COMMON_sgptDataTables)->dwProportiesRecs)
			return;
		if (ptrMagicAffixRecord == nullptr)
			return;
		if (ptrItemUnit == nullptr)
			return;
		
		D2C_Mod mod = static_cast<D2C_Mod>(modCode);
		D2Stat d2Stat = { 0 };
		WORD wItemStatTableSize = ptrItemUnit->ptStats->ptAffixStats->nbBaseStats;

		switch (mod)
		{
		case D2C_Mod::MINDAMAGE:
			for (int i = 0; i < wItemStatTableSize; ++i)
			{
				d2Stat.id = ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable[i].id;
				d2Stat.value = ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable[i].value;
				if (!RuleManager.RuleEvalStatMinDmg.evaluate(d2Stat.id))
					continue;

				std::cout << std::dec << static_cast<WORD>(d2Stat.id) << ':' << d2Stat.value << '/' << dwMaxStatValue << std::endl;
			}
			break;
		case D2C_Mod::MAXDAMAGE:
			for (int i = 0; i < wItemStatTableSize; ++i)
			{
				d2Stat.id = ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable[i].id;
				d2Stat.value = ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable[i].value;
				if (!RuleManager.RuleEvalStatMaxDmg.evaluate(d2Stat.id))
					continue;

				std::cout << std::dec << static_cast<WORD>(d2Stat.id) << ':' << d2Stat.value << '/' << dwMaxStatValue << std::endl;
			}
			break;
		case D2C_Mod::WEAPONDAMAGE_PERCENT:
			for (int i = 0; i < wItemStatTableSize; ++i)
			{
				d2Stat.id = ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable[i].id;
				d2Stat.value = ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable[i].value;
				if (!RuleManager.RuleEvalStatDmgPct.evaluate(d2Stat.id))
					continue;

				std::cout << std::dec << static_cast<WORD>(d2Stat.id) << ':' << d2Stat.value << '/' << dwMaxStatValue << std::endl;
			}
			break;
		default:
			std::cout << '(' << std::hex <<  ptrMagicAffixRecord->dwMod1Code << ')' << std::dec << static_cast<WORD>(d2Stat.id) << ':' << d2Stat.value << '/' << dwMaxStatValue << std::endl;
			break;
		}
	}

	__declspec(dllexport) void __stdcall doModPrint(DWORD32 modCode, D2AutoMagicTxt* ptrMagicAffixRecord, Unit* ptrItemUnit, DWORD32 dwMaxStatValue)
	{
		if (modCode >= (*D2COMMON_sgptDataTables)->dwProportiesRecs)
			return;
		if (ptrMagicAffixRecord == nullptr)
			return;
		if (ptrItemUnit == nullptr)
			return;

		PropertiesBIN* ptrProperties = ((*D2COMMON_sgptDataTables)->pPropertiesTxt) + modCode;
		DWORD32 dwMaxStatID = (*D2COMMON_sgptDataTables)->dwItemStatCostRecs;

		if (ptrProperties->stat1 < dwMaxStatID)
		{
			//TODO: search through item stat table for stat1, stat2, etc...
		}
		else
		{	//check for min, max, or percentage dmg additive stats
			doSpecDMGModPrint(modCode, ptrMagicAffixRecord, ptrItemUnit, dwMaxStatValue);
		}
	}

	/*
		D2COMMON_ITEMRECORDS_GetItemMagicPrefix_t and D2COMMON_ITEMRECORDS_GetItemMagicSuffix_t type function pointers are acceptable here... don't use anything else
	*/
	__declspec(dllexport) void __stdcall doMagicAffixPrint( D2COMMON_ITEMRECORDS_GetItemMagicPrefix_t affixGetter, Unit* ptrItemUnit, WORD wConsoleColor)
	{	//these next for-loops: only rare items will have multiple prefixes and suffixes. magic items can only have 1 prefix and/or 1 suffix.
		//an affix can have more than one mod code
		//some mods are repeated. the stat value applied to the item is the sum of all duplicate mods, which was already calculated by the game before this point.
		//also: some stats are repeated, namely the + to skill(s) stats
		//the actual stat max value needs to be computed here, all duplicate mod max values are to be tallied.
		/*[0..3][0]: stores a valid or invalid mod code
		[0..3][1]: stores the sum of all mod max stat values found for each duplicate mod code, or 0*/
		std::unordered_map<DWORD32, DWORD32> dwModMaxMap;
		WORD wMagicAffixCode = 0;
		D2AutoMagicTxt* ptrMagicAffixRecord = nullptr;

		//prefix
		for (int i = 0; i < 3; ++i)
		{
			wMagicAffixCode = affixGetter(ptrItemUnit, i);
			if (wMagicAffixCode == 0)
				break;

			ptrMagicAffixRecord = D2COMMON_TXT_GetMagicAffixRecord(wMagicAffixCode);
			if (ptrMagicAffixRecord == nullptr || ptrMagicAffixRecord->dwMod1Code >= (*D2COMMON_sgptDataTables)->dwProportiesRecs)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				std::cout << "Failed to find magic affix record for affix code " << std::dec << wMagicAffixCode << std::endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
				break;
			}

			auto modMaxRecord = dwModMaxMap.find(ptrMagicAffixRecord->dwMod1Code);
			if (modMaxRecord != dwModMaxMap.end())
				modMaxRecord->second += ptrMagicAffixRecord->dwMod1Max;
			else
				dwModMaxMap.insert(std::make_pair(ptrMagicAffixRecord->dwMod1Code, ptrMagicAffixRecord->dwMod1Max));

			modMaxRecord = dwModMaxMap.find(ptrMagicAffixRecord->dwMod2Code);
			if (modMaxRecord != dwModMaxMap.end())
				modMaxRecord->second += ptrMagicAffixRecord->dwMod2Max;
			else if (ptrMagicAffixRecord->dwMod2Code < (*D2COMMON_sgptDataTables)->dwProportiesRecs)
				dwModMaxMap.insert(std::make_pair(ptrMagicAffixRecord->dwMod2Code, ptrMagicAffixRecord->dwMod2Max));

			modMaxRecord = dwModMaxMap.find(ptrMagicAffixRecord->dwMod3Code);
			if (modMaxRecord != dwModMaxMap.end())
				modMaxRecord->second += ptrMagicAffixRecord->dwMod3Max;
			else if (ptrMagicAffixRecord->dwMod3Code < (*D2COMMON_sgptDataTables)->dwProportiesRecs)
				dwModMaxMap.insert(std::make_pair(ptrMagicAffixRecord->dwMod3Code, ptrMagicAffixRecord->dwMod3Max));

		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wConsoleColor | FOREGROUND_INTENSITY);

		for (int i = 0; i < 3; ++i)
		{
			wMagicAffixCode = affixGetter(ptrItemUnit, i);
			if (wMagicAffixCode == 0)
				break;
	
			ptrMagicAffixRecord = D2COMMON_TXT_GetMagicAffixRecord(wMagicAffixCode);
			if (ptrMagicAffixRecord == nullptr || ptrMagicAffixRecord->dwMod1Code >= (*D2COMMON_sgptDataTables)->dwProportiesRecs)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				std::cout << "Failed to find magic affix record for affix code " << std::dec << wMagicAffixCode << std::endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
				break;
			}

			auto modMaxRecord = dwModMaxMap.find(ptrMagicAffixRecord->dwMod1Code);
			if (modMaxRecord != dwModMaxMap.end())
			{
				doModPrint(modMaxRecord->first, ptrMagicAffixRecord, ptrItemUnit, modMaxRecord->second);
				dwModMaxMap.erase(modMaxRecord);
			}

			modMaxRecord = dwModMaxMap.find(ptrMagicAffixRecord->dwMod2Code);
			if (modMaxRecord != dwModMaxMap.end())
			{
				doModPrint(modMaxRecord->first, ptrMagicAffixRecord, ptrItemUnit, modMaxRecord->second);
				dwModMaxMap.erase(modMaxRecord);
			}

			modMaxRecord = dwModMaxMap.find(ptrMagicAffixRecord->dwMod3Code);
			if (modMaxRecord != dwModMaxMap.end())
			{
				doModPrint(modMaxRecord->first, ptrMagicAffixRecord, ptrItemUnit, modMaxRecord->second);
				dwModMaxMap.erase(modMaxRecord);
			}
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
	}

	__declspec(dllexport) UniqueItemsBIN* __stdcall getItemUniqueAffix(Unit* const ptrItemUnit)
	{
		DWORD32 nUniqueIndex = D2COMMON_ITEMS_GetFileIndex(ptrItemUnit);
		if (nUniqueIndex == 0)
			return nullptr;
		if (nUniqueIndex >= (*D2COMMON_sgptDataTables)->dwUniqItemsRecs)
			return nullptr;
		return ((*D2COMMON_sgptDataTables)->pUniqueItemsTxt) + nUniqueIndex;
	}

	__declspec(dllexport) Game* __stdcall getGame(void)
	{
		if (*D2GAME_ptrGame != nullptr)
		{
			return reinterpret_cast<Game*>( *D2GAME_ptrGame );
		}
		return nullptr;
	}

	__declspec(naked) void WINAPI freeHoverText(uintptr_t* ptrUnit, uintptr_t* ptrGame)
	{
		__asm
		{
			PUSH EBX
			PUSH ESI
			//ptrUnit
			MOV ESI, [ESP + 0xC] //+4(after ret instruction ptr) +8(after prev 2 pushes)
			//ptrGame
			MOV EBX, [ESP + 0x10] //+4(after ret instruction ptr) +8(after prev 2 pushes) +4(after arg_0)
			//reserved for ptrHoverText
			PUSH EDI

			//check if ptrUnit is null
			CMP ESI, 0
			JE prologue_freeHoverText
			//store ptrHoverText and check if null
			MOV EDI, [ESI + 0xA4]
			CMP EDI, 0
			JE prologue_freeHoverText
			//check if ptrGame is null
			CMP EBX, 0
			JE prologue_freeHoverText

		//sect_freeHoverText:
			MOV EAX, [EBX + 0x1C]
			PUSH EDI
			PUSH EAX
			CALL D2COMMON_CHAT_FreeHoverText
			PUSH ESI
			MOV DWORD PTR [ESI + 0xA4], 0
			CALL D2COMMON_UNITS_Update
			MOV EAX, [ESI + 0xC4]
			OR EAX, 0x100
			MOV [ESI + 0xC4], EAX
		prologue_freeHoverText:
			POP EDI
			POP ESI
			POP EBX
			RETN 0x8
		}
	}

	__declspec(naked) void WINAPI allocHoverText(uintptr_t* ptrUnit, uintptr_t* ptrGame, char* szText)
	{
		__asm
		{
			PUSH ESI
			MOV ESI, [ESP + 0x8]  //+4(after ret instruction ptr) +4(after prev push)
		#define ptrUnit ESI
			PUSH EBX
			MOV EBX, [ESP + 0x10] //+4(after ret instruction ptr) +4(after arg_0) +8(after prev 2 pushes)
		#define ptrGame EBX
			PUSH EBP
			//MOV, not LEA here... because c++ passes c_strings as a pointer to a pointer? So we dereference here
			MOV EBP, [ESP + 0x18]  //+4(after ret instruction ptr) +4(after arg_0) +4(after arg_1) +12(after 3 prev pushes)
		#define szText EBP

			CMP ptrUnit, 0
			JE prologue_allocHoverText
			CMP ptrGame, 0
			JE prologue_allocHoverText
			CMP szText, 0
			JE prologue_allocHoverText

			//check if pHoverText is null
			MOV EDX, [ptrUnit + 0xA4]
			CMP EDX, 0
			JE sect_allocHoverText
			//pHoverText is not null, let's free it first
			MOV ECX, [ptrGame + 0x1C]
			PUSH EDX
			PUSH ECX
			CALL D2COMMON_CHAT_FreeHoverText
		sect_allocHoverText:
			//ecx = pMemPool
			MOV ECX, [ptrGame + 0x1C]
			//edx = dwGameFrame
			MOV EDX, DWORD PTR [ptrGame + 0xA8]
			PUSH EDX
			PUSH szText
			PUSH ECX
			CALL D2COMMON_CHAT_AllocHoverText
			CMP EAX, 0
			JE prologue_allocHoverText
			XOR EDX, EDX
			PUSH EDX
			PUSH EAX
			CALL D2COMMON_CHAT_SetHoverLocale
			MOV [ptrUnit + 0xA4], EAX
			PUSH ptrUnit
			CALL D2COMMON_UNITS_Update
			OR DWORD PTR [ptrUnit + 0xC4], 0x100
		prologue_allocHoverText:
			POP EBP
			POP EBX
			POP ESI
			RETN 0xC
		#undef szText
		#undef ptrGame
		#undef ptrUnit
		}
	}
}

namespace
{
	static ScopedThread<void(void)> tDeferPrintPlayer([]() {
		while (true)
		{
			std::this_thread::sleep_for( std::chrono::milliseconds(666) );
			Unit* ptrPlayerUnit = CommonD2Funcs::getPlayerUnit();
			if (ptrPlayerUnit)
			{
				if (ptrPlayerUnit->ptPlayerData)
				{
					char buffer[256] = { 0 };
					sprintf_s(buffer, "%s connected.", ptrPlayerUnit->ptPlayerData->name);
					std::cout << buffer << std::endl;
				}
				break;
			}
		}
	});
}

namespace EventFuncs
{
	__declspec(dllexport) void __stdcall EnterGame(void)
	{
		std::cout << "-----------------------------\n" << "Entering New Game\n";
		//TODO: both ptrgame and ptrunit are null at this point...
	
		if (D2GAME_ptrPlayersX != nullptr)
		{
			std::cout << "Players X: " << std::dec << reinterpret_cast<int>( *D2GAME_ptrPlayersX ) << std::endl;
		}

		tDeferPrintPlayer.start();
		RuleManager.reloadRules();
	}
}

namespace DetourFuncs
{
	__declspec(dllexport) uintptr_t* __stdcall detourAllocHoverText(void* pMemoryPool, char *szText, DWORD dwFrame)
	{
		//MessageBoxA(NULL, "player said something!", "D2Template", MB_OK | MB_ICONINFORMATION );
		std::cout << '"' << szText << '"' << std::endl;
		return D2COMMON_CHAT_AllocHoverText(pMemoryPool, szText, dwFrame);
	}

	__declspec(naked) BYTE __stdcall detourEnterGame(void) {__asm {
		CALL EventFuncs::EnterGame
		PUSH EDX
		MOV EDX, [D2GAME_OnGameEnterMagicReturnValue]
		MOV AL, BYTE PTR [EDX]
		POP EDX
		RETN
	}}
}

//testing
/*
class thisisatest
{
public:
	void testmethod();
};

void thisisatest::testmethod()
{
	std::cout << "Works!" << std::endl;
}

namespace one
{
	thisisatest tiat;
	thisisatest *tiatPtr = &tiat;
}
*/
//https://www.codeproject.com/Articles/11694/How-to-invoke-C-member-operations-from-inline-asse
/*
Called in ASM as follows (remember, foobar is a __thiscall function...):
MOV ECX, one::tiatPtr
call foobar
*/
//void (thisisatest::*foobar)(void) = &thisisatest::testmethod;