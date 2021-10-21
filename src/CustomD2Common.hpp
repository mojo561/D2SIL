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
//BACKGROUND_RED | BACKGROUND_RED
static const WORD BACKGROUND_YELLOW = BACKGROUND_RED | BACKGROUND_RED;

///////////

static struct rulemgr
{
	RuleEvaluatorImpl<D2C_ItemCodes> RuleEvalJunkItemCode;
	RuleEvaluatorImpl<D2C_ItemTypes> RuleEvalJunkItemType;
	RuleEvaluatorImpl<D2C_ItemTypes> RuleEvalILvlPrint;
	RuleEvaluatorImpl<D2C_Stat> RuleEvalStatMinDmg;
	RuleEvaluatorImpl<D2C_Stat> RuleEvalStatMaxDmg;
	RuleEvaluatorImpl<D2C_Stat> RuleEvalStatDmgPct;
	RuleEvaluatorImpl<D2C_Stat> RuleRvalUnprintableStats;

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

		//TODO: new
		RuleImpl<D2C_Stat> unprintStats[] = {
			RuleImpl<D2C_Stat>::RuleImpl(D2C_Stat::STATS_ITEM_SINGLESKILL),
			//RuleImpl<D2C_Stat>::RuleImpl(D2C_Stat::STATS_POISONMINDAM),
			//RuleImpl<D2C_Stat>::RuleImpl(D2C_Stat::STATS_POISONMAXDAM),
			RuleImpl<D2C_Stat>::RuleImpl(D2C_Stat::STATS_POISONLENGTH),
			RuleImpl<D2C_Stat>::RuleImpl(D2C_Stat::STATS_POISON_COUNT),
			RuleImpl<D2C_Stat>::RuleImpl(D2C_Stat::STATS_COLDLENGTH)
		};
		///////////

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

		//TODO: new
		for (size_t i = 0; i < _countof(unprintStats); ++i)
		{
			RuleRvalUnprintableStats.addRule(unprintStats[i]);
		}
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
		if (modCode >= _D2C_dwMaxMod)
			return false;
		if (statID >= _D2C_dwMaxStat)
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
		if (modCode >= _D2C_dwMaxMod)
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

				ItemStatCostBIN* ptrISC = ((*D2COMMON_sgptDataTables)->pItemStatCostTxt) + static_cast<WORD>(d2Stat.id);
				if (ptrISC->descstrpos > 0 && ptrISC->descstrpos != static_cast<WORD>(D2ClassicStrings::D2STR_DUMMY))
				{
					std::wcout << D2LANG_GetTableString(ptrISC->descstrpos) << ':' << std::dec << d2Stat.value << '/' << dwMaxStatValue << std::endl;
				}
				else
				{
					std::cout << std::dec << static_cast<WORD>(d2Stat.id) << ':' << d2Stat.value << '/' << dwMaxStatValue << std::endl;
				}
			}
			break;
		case D2C_Mod::MAXDAMAGE:
			for (int i = 0; i < wItemStatTableSize; ++i)
			{
				d2Stat.id = ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable[i].id;
				d2Stat.value = ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable[i].value;
				if (!RuleManager.RuleEvalStatMaxDmg.evaluate(d2Stat.id))
					continue;

				ItemStatCostBIN* ptrISC = ((*D2COMMON_sgptDataTables)->pItemStatCostTxt) + static_cast<WORD>(d2Stat.id);
				if (ptrISC->descstrpos > 0 && ptrISC->descstrpos != static_cast<WORD>(D2ClassicStrings::D2STR_DUMMY))
				{
					std::wcout << D2LANG_GetTableString(ptrISC->descstrpos) << ':' << std::dec << d2Stat.value << '/' << dwMaxStatValue << std::endl;
				}
				else
				{
					std::cout << std::dec << static_cast<WORD>(d2Stat.id) << ':' << d2Stat.value << '/' << dwMaxStatValue << std::endl;
				}
			}
			break;
		case D2C_Mod::WEAPONDAMAGE_PERCENT:
			for (int i = 0; i < wItemStatTableSize; ++i)
			{
				d2Stat.id = ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable[i].id;
				d2Stat.value = ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable[i].value;
				if (!RuleManager.RuleEvalStatDmgPct.evaluate(d2Stat.id))
					continue;

				ItemStatCostBIN* ptrISC = ((*D2COMMON_sgptDataTables)->pItemStatCostTxt) + static_cast<WORD>(d2Stat.id);
				if (ptrISC->descstrpos > 0 && ptrISC->descstrpos != static_cast<WORD>(D2ClassicStrings::D2STR_DUMMY))
				{
					std::wcout << D2LANG_GetTableString(ptrISC->descstrpos) << ':' << std::dec << d2Stat.value << '/' << dwMaxStatValue << std::endl;
				}
				else
				{
					std::cout << std::dec << static_cast<WORD>(d2Stat.id) << ':' << d2Stat.value << '/' << dwMaxStatValue << std::endl;
				}
			}
			break;
		default:
			std::cout << '(' << std::hex <<  ptrMagicAffixRecord->dwMod1Code << ')' << std::dec << static_cast<WORD>(d2Stat.id) << ':' << d2Stat.value << '/' << dwMaxStatValue << std::endl;
			break;
		}
	}

	__declspec(dllexport) void __stdcall doModPrint(DWORD32 modCode, D2AutoMagicTxt* ptrMagicAffixRecord, Unit* ptrItemUnit, DWORD32 dwMaxStatValue)
	{
		if (modCode >= _D2C_dwMaxMod)
			return;
		if (ptrMagicAffixRecord == nullptr)
			return;
		if (ptrItemUnit == nullptr)
			return;

		PropertiesBIN* ptrProperties = ((*D2COMMON_sgptDataTables)->pPropertiesTxt) + modCode;
		DWORD32 dwMaxStatID = _D2C_dwMaxStat;

		if (ptrProperties->stat1 < dwMaxStatID)
		{	//search through item stat table for stat1, stat2, etc...
			WORD wStatIds[] = {
				ptrProperties->stat1,
				ptrProperties->stat2,
				ptrProperties->stat3,
				ptrProperties->stat4,
				ptrProperties->stat5,
				ptrProperties->stat6,
				ptrProperties->stat7
			};
			WORD wItemStatTableSize = ptrItemUnit->ptStats->ptAffixStats->nbBaseStats;
			D2Stat d2Stat = { 0 };

			for (int i = 0; i < wItemStatTableSize; ++i)
			{
				d2Stat.id = ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable[i].id;
				d2Stat.value = ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable[i].value;
				for (int j = 0; j < _countof(wStatIds); ++j)
				{
					if (wStatIds[j] >= dwMaxStatID)
						break;

					if (wStatIds[j] == static_cast<WORD>(d2Stat.id))
					{
						ItemStatCostBIN* ptrISC = ((*D2COMMON_sgptDataTables)->pItemStatCostTxt) + wStatIds[j];
						int statValue = d2Stat.value;
						BYTE bValShift = ptrISC->valshift;

						if (bValShift > 0 && bValShift < 0x7F)
						{
							statValue = statValue >> bValShift;
						}

						if (ptrISC->descstrpos > 0 && ptrISC->descstrpos != static_cast<WORD>(D2ClassicStrings::D2STR_DUMMY))
						{
							//std::wcout << D2LANG_GetTableString(ptrISC->descstrpos) << ':' << std::dec << d2Stat.value << '/' << dwMaxStatValue << std::endl;
							std::wcout << D2LANG_GetTableString(ptrISC->descstrpos) << ':' << std::dec << statValue << '/' << dwMaxStatValue << std::endl;
						}
						else
						{
							//std::cout << std::dec << wStatIds[j] << ':' << d2Stat.value << '/' << dwMaxStatValue << std::endl;
							std::cout << std::dec << wStatIds[j] << ':' << statValue << '/' << dwMaxStatValue << std::endl;
						}
					}
				}
			}
		}
		else
		{	//check for min, max, or percentage dmg additive stats
			doSpecDMGModPrint(modCode, ptrMagicAffixRecord, ptrItemUnit, dwMaxStatValue);
		}
	}
/*
	__declspec(dllexport) void __stdcall doMagicAffixPrint(Unit* ptrItemUnit)
	{	//these next for-loops: only rare items will have multiple prefixes and suffixes. magic items can only have 1 prefix and/or 1 suffix.
		//an affix can have more than one mod code
		//some mods are repeated. the stat value applied to the item is the sum of all duplicate mods, which was already calculated by the game before this point.
		//duplicate stats can also be found when comparing mods, even if the mod codes do not match.
		//also: some stats are repeated, namely the + to skill(s) stats
		//the actual stat max value needs to be computed here, all duplicate max values for stats/mods are to be tallied.
		//[0..3][0]: stores a valid or invalid mod code
		//[0..3][1]: stores the sum of all mod max stat values found for each duplicate mod code, or 0
		std::unordered_map<DWORD32, DWORD32> dwModMaxMap;

		auto blah = [&dwModMaxMap](D2COMMON_ITEMRECORDS_GetItemMagicPrefix_t affixGetter, Unit* ptrItemUnit) {
			WORD wMagicAffixCode = 0;
			D2AutoMagicTxt* ptrMagicAffixRecord = nullptr;
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
		};

		blah(D2COMMON_ITEMRECORDS_GetItemMagicPrefix, ptrItemUnit);
		blah(D2COMMON_ITEMRECORDS_GetItemMagicSuffix, ptrItemUnit);

		auto blah2 = [&dwModMaxMap](D2COMMON_ITEMRECORDS_GetItemMagicPrefix_t affixGetter, Unit* ptrItemUnit) {

			if (dwModMaxMap.empty())
				return;

			WORD wMagicAffixCode = 0;
			D2AutoMagicTxt* ptrMagicAffixRecord = nullptr;
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
		};

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_TEAL | FOREGROUND_INTENSITY);
		blah2(D2COMMON_ITEMRECORDS_GetItemMagicPrefix, ptrItemUnit);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_PURPLE | FOREGROUND_INTENSITY);
		blah2(D2COMMON_ITEMRECORDS_GetItemMagicSuffix, ptrItemUnit);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
	}
*/

	__declspec(dllexport) bool __stdcall checkIfItemElite(DWORD32 dwItemCode)
	{
		int dwFileIndex = D2COMMON_ITEMRECORDS_GetItemIndexFromCode(dwItemCode); //D2COMMON_ITEMS_GetFileIndex(ptrItemUnit);
		if (dwFileIndex != 0)
		{
			D2ItemsTxt* d2it = D2COMMON_ITEMRECORDS_GetItemRecord(dwFileIndex);
			if (d2it != nullptr)
			{
				if (dwItemCode == d2it->dwUltraCode)
				{
					return true;
				}
			}
		}
		return false;
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

	__declspec(dllexport) void __stdcall doMagicAffixPrint(Unit* ptrItemUnit)
	{	//only rare items will have multiple prefixes and suffixes. magic items can only have 1 prefix and/or 1 suffix unless they were socketed (ignoring socketed magic items for now).
		//an affix can have more than one mod code
		//some mods are repeated. the stat value applied to the item is the sum of all duplicate mods, which was already calculated by the game before this point.
		//duplicate stats can also be found when comparing mods, even if the mod codes do not match.
		//also, some stats are repeated in ptBaseStatsTable, namely the + to skill(s) stats (stat id 107)
		//the actual stat max value needs to be computed here, all duplicate max values for stats/mods are to be tallied.

		//ptBaseStatsTable contains just the stats that were added by mods/affixes.
		//Some 'inherent' stats are not included in this table (such as + to zon skills in matriarch bows, or +50% dmg to undead for clubs)
		if (ptrItemUnit->ptStats == nullptr)
			return;
		if (ptrItemUnit->ptStats->ptAffixStats == nullptr)
			return;
		if (ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable == nullptr)
			return;

		int dwQuality = D2COMMON_ITEMS_GetQuality(ptrItemUnit);
		D2C_ItemQuality itemQuality = static_cast<D2C_ItemQuality>(dwQuality);

		DWORD32 dwMaxStatID = _D2C_dwMaxStat;
		D2Stat d2Stat = { 0 };

		//total number of unique stats added to the item via mods/affixes
		WORD wItemStatTableSize = ptrItemUnit->ptStats->ptAffixStats->nbBaseStats;

		/* Key: stores a valid or invalid stat ID.
		Value: stores the sum of all max stat values found for each duplicate mod/stat code, or 0 */
		std::unordered_map<WORD, DWORD32> mapPropertyStatMaxTable;

		for (int i = 0; i < wItemStatTableSize; ++i)
		{
			WORD wStatID = static_cast<WORD>(ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable[i].id);
			if (wStatID < dwMaxStatID)
			{
				auto record = mapPropertyStatMaxTable.find(wStatID);
				if (record == mapPropertyStatMaxTable.end())
					mapPropertyStatMaxTable.insert(std::make_pair(wStatID, 0));
				//else // typical values that dupicate: stat 107
				//	std::cout << "Dupe! " << std::dec << wStatID << std::endl;
			}
		}

		static const DWORD32 dwPropertyStatTableLength = 7;
		//property table for a specific mod. May contain invalid stat ids
		std::array<WORD, dwPropertyStatTableLength> arrPropertyStatTable;

		auto doMergeStatTable = [&arrPropertyStatTable, &mapPropertyStatMaxTable](DWORD32 dwModCode, DWORD32 dwModNMax) {
			if (dwModCode >= _D2C_dwMaxMod)
				return;

			PropertiesBIN* ptrProperties = ((*D2COMMON_sgptDataTables)->pPropertiesTxt) + dwModCode;
			
			if (ptrProperties->stat1 >= _D2C_dwMaxStat)
			{	//dmg related mod
				arrPropertyStatTable.fill( ptrProperties->stat1 );
				D2C_Mod d2cMod = static_cast<D2C_Mod>(dwModCode);

				switch (d2cMod)
				{
					case D2C_Mod::MINDAMAGE:
						arrPropertyStatTable[0] = static_cast<WORD>(D2C_Stat::STATS_MINDAMAGE);
						arrPropertyStatTable[1] = static_cast<WORD>(D2C_Stat::STATS_SECONDARY_MINDAMAGE);
						arrPropertyStatTable[2] = static_cast<WORD>(D2C_Stat::STATS_ITEM_THROW_MINDAMAGE);
						break;
					case D2C_Mod::MAXDAMAGE:
						arrPropertyStatTable[0] = static_cast<WORD>(D2C_Stat::STATS_MAXDAMAGE);
						arrPropertyStatTable[1] = static_cast<WORD>(D2C_Stat::STATS_SECONDARY_MAXDAMAGE);
						arrPropertyStatTable[2] = static_cast<WORD>(D2C_Stat::STATS_ITEM_THROW_MAXDAMAGE);
						break;
					case D2C_Mod::WEAPONDAMAGE_PERCENT:
						arrPropertyStatTable[0] = static_cast<WORD>(D2C_Stat::STATS_ITEM_MAXDAMAGE_PERCENT);
						arrPropertyStatTable[1] = static_cast<WORD>(D2C_Stat::STATS_ITEM_MINDAMAGE_PERCENT);
						break;
				}
			}
			else
			{
				arrPropertyStatTable = {
					ptrProperties->stat1,
					ptrProperties->stat2,
					ptrProperties->stat3,
					ptrProperties->stat4,
					ptrProperties->stat5,
					ptrProperties->stat6,
					ptrProperties->stat7
				};
			}
			for (size_t j = 0; j < dwPropertyStatTableLength; ++j)
			{
				auto record = mapPropertyStatMaxTable.find(arrPropertyStatTable[j]);
				if (record != mapPropertyStatMaxTable.end())
				{
					record->second += dwModNMax;
				}
				else if (arrPropertyStatTable[j] >= _D2C_dwMaxStat)
				{
					break;
				}
				else
				{	//TODO: this seems to happen regularly..
					std::cout << "Missed " << std::dec << arrPropertyStatTable[j] << ", adding with modNMax " << dwModNMax << std::endl;
					mapPropertyStatMaxTable.insert(std::make_pair(arrPropertyStatTable[j], dwModNMax));
				}
			}
		};

		auto dofillTable = [&doMergeStatTable](D2COMMON_ITEMRECORDS_GetItemMagicPrefix_t affixGetterFunc, Unit* ptrItemUnit) {
			for (int i = 0; i < 3; ++i)
			{
				WORD wMagicAffixCode = affixGetterFunc(ptrItemUnit, i);
				if (wMagicAffixCode == 0)
					break;

				D2AutoMagicTxt* ptrMagicAffixRecord = D2COMMON_TXT_GetMagicAffixRecord(wMagicAffixCode);
				if (ptrMagicAffixRecord == nullptr || ptrMagicAffixRecord->dwMod1Code >= _D2C_dwMaxMod)
					break;

				doMergeStatTable(ptrMagicAffixRecord->dwMod1Code, ptrMagicAffixRecord->dwMod1Max);
				doMergeStatTable(ptrMagicAffixRecord->dwMod2Code, ptrMagicAffixRecord->dwMod2Max);
				doMergeStatTable(ptrMagicAffixRecord->dwMod3Code, ptrMagicAffixRecord->dwMod3Max);
			}
		};

		if (itemQuality == D2C_ItemQuality::ITEMQUALITY_SET)
		{
			SetItemsBIN* ptrSetItemRecord = D2COMMON_TXT_GetSetItemRecord(ptrItemUnit);
			if (ptrSetItemRecord != nullptr)
			{
				DWORD32* ptrSetItemProp1Base = &ptrSetItemRecord->dwProp1;
				for (int i = 0; i < 9; ++i)
				{
					DWORD32* ptrSetItemPropNBase = ptrSetItemProp1Base + (i * 4);
					DWORD32 dwPropNModCode = *ptrSetItemPropNBase;
					DWORD32 dwMaxN = *(ptrSetItemPropNBase + 3);

					if (dwPropNModCode >= _D2C_dwMaxMod)
						break;

					doMergeStatTable(dwPropNModCode, dwMaxN);
				}
			}
		}
		else if (itemQuality == D2C_ItemQuality::ITEMQUALITY_UNIQUE)
		{
			UniqueItemsBIN* ptrUniqueItemRecord = getItemUniqueAffix(ptrItemUnit);
			if (ptrUniqueItemRecord != nullptr)
			{
				DWORD32* ptrUniqueItemProp1Base = &ptrUniqueItemRecord->dwProp1ModCode;
				for (int i = 0; i < 12; ++i)
				{
					DWORD32* ptrUniqueItemPropNBase = ptrUniqueItemProp1Base + (i * 4);
					DWORD32 dwPropNModCode = *ptrUniqueItemPropNBase;
					DWORD32 dwMaxN = *(ptrUniqueItemPropNBase + 3);

					if (dwPropNModCode >= _D2C_dwMaxMod)
						break;

					doMergeStatTable(dwPropNModCode, dwMaxN);
				}
			}
		}
		else
		{
			dofillTable(D2COMMON_ITEMRECORDS_GetItemMagicPrefix, ptrItemUnit);
			dofillTable(D2COMMON_ITEMRECORDS_GetItemMagicSuffix, ptrItemUnit);
		}

		//automagic affix... move to it's own function?
		ItemData* ptrItemData = ptrItemUnit->ptItemData;
		if (ptrItemData != nullptr)
		{
			WORD wAutoMagicAffixCode = ptrItemData->autoPref;
			DWORD32 dwQualityItemsIndexCode = ptrItemData->uniqueID;
			if (itemQuality == D2C_ItemQuality::ITEMQUALITY_SUPERIOR)
			{	//check in QualityItems.txt
				QualityItemsTXT* blah = D2COMMON_ITEMRECORDS_GetItemQualityRecord(dwQualityItemsIndexCode);
				if (blah != nullptr)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE | FOREGROUND_INTENSITY);
					std::cout << blah->szEffect1 << std::endl;
					if(blah->wNumMods == 2)
						std::cout << blah->szEffect2 << std::endl;

					//TODO: sometimes modNMax is 0...?
					/*
					+1 to Maximum Damage
					[5S]Superior Long Bow
					improved damage
					[1]24:1/0
					*/

					doMergeStatTable(blah->dwMod1Code, blah->dwMod1Max);
					doMergeStatTable(blah->dwMod2Code, blah->dwMod2Max);
				}
			}
			if (wAutoMagicAffixCode != 0)
			{	//check for automagic affix record
				D2AutoMagicTxt* ptrAutoMagicAffixRecord = D2COMMON_TXT_GetMagicAffixRecord(ptrItemData->autoPref);
				if (ptrAutoMagicAffixRecord != nullptr)
				{
					doMergeStatTable(ptrAutoMagicAffixRecord->dwMod1Code, ptrAutoMagicAffixRecord->dwMod1Max);
					doMergeStatTable(ptrAutoMagicAffixRecord->dwMod2Code, ptrAutoMagicAffixRecord->dwMod2Max);
					doMergeStatTable(ptrAutoMagicAffixRecord->dwMod3Code, ptrAutoMagicAffixRecord->dwMod3Max);
				}
			}
		}
		//////////////////////////////////////////////////////////

		for (int i = 0; i < wItemStatTableSize; ++i)
		{
			//ptrItemUnit->ptStats->ptAffixStats->ptStats : nope
			//ptrItemUnit->ptStats->ptAffixStats->ptItemStats : maybe
			//ptrItemUnit->ptStats->ptNextStats2 : nope
			d2Stat.id = ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable[i].id;
			d2Stat.value = ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable[i].value;
			if (static_cast<WORD>(d2Stat.id) >= dwMaxStatID)
				continue;

			auto record = mapPropertyStatMaxTable.find(static_cast<WORD>(d2Stat.id));
			if (record == mapPropertyStatMaxTable.end())
				continue;

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			//TODO: RuleRvalUnprintableStats holds ALL non-printable stats... are there any that we actually want to check here?
			if (record->second == 0 && !RuleManager.RuleRvalUnprintableStats.evaluate(static_cast<D2C_Stat>(record->first)))
			{
				//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
				//std::cout << "ptrItemUnit->ptStats->ptAffixStats->ptStats: 0x" << std::hex << std::uppercase << ptrItemUnit->ptStats->ptAffixStats->ptStats << std::endl;
				//std::cout << "ptrItemUnit->ptStats->ptAffixStats->ptItemStats: 0x" << std::hex << std::uppercase << ptrItemUnit->ptStats->ptAffixStats->ptItemStats << std::endl;
				//std::cout << "ptrItemUnit->ptStats->ptNextStats2: 0x" << std::hex << std::uppercase << ptrItemUnit->ptStats->ptNextStats2 << std::endl;
				//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				/*Stats* ptrItemStats = ptrItemUnit->ptStats->ptAffixStats->ptItemStats;
				if (ptrItemStats != nullptr)
				{
					WORD wItemInherentStatTableSize = ptrItemStats->nbBaseStats;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
					std::cout << std::dec << wItemInherentStatTableSize << std::endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				}*/
				/*
				almost works
				there are other inherent item mods though:

				All Resistances +5
				Damaged Damaged Rondache
				2
				39:5/0
				2
				41:5/0
				2
				43:5/0
				2
				45:5/0

				hmmm...

				+89 to Attack Rating
				+41% Enhanced Damage
				Protector Shield
				0,0,0
				17:41/0
				0,0,0
				18:41/0
				0,0,0
				19:89/0


				this works, because it's specifically superior?
				+10% Enhanced Defense
				Superior Antlers
				2,0,0
				16:10/0
				*/

				ItemData* ptrItemData = ptrItemUnit->ptItemData;
				if (ptrItemData != nullptr)
				{
					int dwQuality = D2COMMON_ITEMS_GetQuality(ptrItemUnit);
					D2C_ItemQuality itemQuality = static_cast<D2C_ItemQuality>(dwQuality);

					if (itemQuality == D2C_ItemQuality::ITEMQUALITY_SUPERIOR)
					{	//check in QualityItems.txt
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE | FOREGROUND_INTENSITY);
						//std::cout << '[' << std::dec << ptrItemData->uniqueID << ']';
						DWORD32 dwQualityItemsIndexCode = ptrItemData->uniqueID;
						QualityItemsTXT* blah = D2COMMON_ITEMRECORDS_GetItemQualityRecord(dwQualityItemsIndexCode);
						//std::cout << '[' << std::hex << std::uppercase << blah << ']';
						std::cout << '[' << std::hex << std::uppercase << blah->dwMod1Code << ']';
						std::cout << '[' << std::dec << blah->dwMod1Min << '-' << blah->dwMod1Max << ']';
					}
					//void* wtfIsThis = D2COMMON_GetMagicAffixTable(); //works...
					if (ptrItemData->autoPref != 0)
					{	//additional stats (other than staff mods) max values can be computed here (examples: affixdump10.1434 and 1436 == + to mana, and! affixdump10.1442 for a Rondache!, affixdump10.1424 for Elite Matriarchal Javelin)
						//this works, but let's move this code somewhere else where all other computations are done
						D2AutoMagicTxt* ptrAutoMagicRecord = D2COMMON_TXT_GetMagicAffixRecord(ptrItemData->autoPref);
						if (ptrAutoMagicRecord != nullptr)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
							std::cout << '[' << std::dec << ptrItemData->autoPref - 1 << ']';
							std::cout << ptrAutoMagicRecord->szName << ' ';
						}
					}
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				}
			}
			//else
			{
				std::cout << std::dec << record->first << ':' << d2Stat.value << '/' << record->second << std::endl;
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE | FOREGROUND_INTENSITY);
		}
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

	__declspec(naked) BYTE __stdcall detourEnterGame(void) {
		UniqueItemCounter = 0;
		__asm {
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