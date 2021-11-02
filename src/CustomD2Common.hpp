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
	RuleEvaluatorImpl<D2C_ItemCodes> RuleEvalSpecialKeyCode;
	RuleEvaluatorImpl<D2C_ItemTypes> RuleEvalJunkItemType;
	RuleEvaluatorImpl<D2C_ItemTypes> RuleEvalILvlPrint;
	RuleEvaluatorImpl<D2C_Stat> RuleEvalStatMinDmg;
	RuleEvaluatorImpl<D2C_Stat> RuleEvalStatMaxDmg;
	RuleEvaluatorImpl<D2C_Stat> RuleEvalStatDmgPct;
	RuleEvaluatorImpl<D2C_Stat> RuleRvalUnprintableStats;

	//TODO: temp func for loading default rules (until txt config support)
	void reloadRules()
	{
		//RuleEvalJunkItemCode.delRules();
		//RuleEvalJunkItemType.delRules();
		//RuleEvalILvlPrint.delRules();

		RuleImpl<D2C_ItemCodes> ignoreRules1[] = {
			RuleImpl<D2C_ItemCodes>::RuleImpl(D2C_ItemCodes::ITEMCODE_GOLD),
			RuleImpl<D2C_ItemCodes>::RuleImpl(D2C_ItemCodes::ITEMCODE_BOLTS),
			RuleImpl<D2C_ItemCodes>::RuleImpl(D2C_ItemCodes::ITEMCODE_ARROWS),
			RuleImpl<D2C_ItemCodes>::RuleImpl(D2C_ItemCodes::ITEMCODE_STAMINA),
			RuleImpl<D2C_ItemCodes>::RuleImpl(D2C_ItemCodes::ITEMCODE_ANTIDOTE),
			RuleImpl<D2C_ItemCodes>::RuleImpl(D2C_ItemCodes::ITEMCODE_THAWPOT),
			RuleImpl<D2C_ItemCodes>::RuleImpl(D2C_ItemCodes::ITEMCODE_REJUV)
		};

		RuleImpl<D2C_ItemCodes> specialKeys[] = {
			RuleImpl<D2C_ItemCodes>::RuleImpl(D2C_ItemCodes::ITEMCODE_KEYOFTERROR),
			RuleImpl<D2C_ItemCodes>::RuleImpl(D2C_ItemCodes::ITEMCODE_KEYOFHATE),
			RuleImpl<D2C_ItemCodes>::RuleImpl(D2C_ItemCodes::ITEMCODE_KEYOFDESTRUCTION)
		};
	
		RuleImpl<D2C_ItemTypes> ignoreRules2[] = {
			RuleImpl<D2C_ItemTypes>::RuleImpl(D2C_ItemTypes::ITEMTYPE_HEALPOT),
			RuleImpl<D2C_ItemTypes>::RuleImpl(D2C_ItemTypes::ITEMTYPE_MANAPOT),
			RuleImpl<D2C_ItemTypes>::RuleImpl(D2C_ItemTypes::ITEMTYPE_MISSPOT),
			RuleImpl<D2C_ItemTypes>::RuleImpl(D2C_ItemTypes::ITEMTYPE_SCROLL),
			RuleImpl<D2C_ItemTypes>::RuleImpl(D2C_ItemTypes::ITEMTYPE_KEY)
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

		//TODO: more to be added
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

		for (size_t i = 0; i < _countof(specialKeys); ++i)
		{
			RuleEvalSpecialKeyCode.addRule(specialKeys[i]);
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
				//else // typical values that duplicate: stat 107
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

				bool isModDmgRelated = (d2cMod == D2C_Mod::MINDAMAGE || d2cMod == D2C_Mod::MAXDAMAGE || d2cMod == D2C_Mod::WEAPONDAMAGE_PERCENT);

				if (isModDmgRelated)
				{
					auto arrPropertyStatTableItor = arrPropertyStatTable.begin();
					auto mapPropertyStatMaxTableRecord = mapPropertyStatMaxTable.end();
					WORD wStatID = 0;

					#define _tmp_customd2common_(d2cStat) \
					if (arrPropertyStatTableItor != arrPropertyStatTable.end()) { \
						wStatID = static_cast<WORD>(d2cStat); \
						mapPropertyStatMaxTableRecord = mapPropertyStatMaxTable.find(wStatID); \
						if (mapPropertyStatMaxTableRecord != mapPropertyStatMaxTable.end()) { \
							ptrdiff_t i = std::distance(arrPropertyStatTable.begin(), arrPropertyStatTableItor); \
							if (i >= 0 && i < dwPropertyStatTableLength) { \
								arrPropertyStatTable[i] = wStatID; \
								++arrPropertyStatTableItor; \
							} \
						} \
					} //#def

					if (d2cMod == D2C_Mod::MINDAMAGE)
					{
						_tmp_customd2common_(D2C_Stat::STATS_MINDAMAGE)
						_tmp_customd2common_(D2C_Stat::STATS_SECONDARY_MINDAMAGE)
						_tmp_customd2common_(D2C_Stat::STATS_ITEM_THROW_MINDAMAGE)
					}
					else if (d2cMod == D2C_Mod::MAXDAMAGE)
					{
						_tmp_customd2common_(D2C_Stat::STATS_MAXDAMAGE)
						_tmp_customd2common_(D2C_Stat::STATS_SECONDARY_MAXDAMAGE)
						_tmp_customd2common_(D2C_Stat::STATS_ITEM_THROW_MAXDAMAGE)
					}
					else if (d2cMod == D2C_Mod::WEAPONDAMAGE_PERCENT)
					{
						//
						wStatID = static_cast<WORD>(D2C_Stat::STATS_ITEM_MAXDAMAGE_PERCENT);
						mapPropertyStatMaxTableRecord = mapPropertyStatMaxTable.find(wStatID);
						if (mapPropertyStatMaxTableRecord != mapPropertyStatMaxTable.end())
						{
							ptrdiff_t i = std::distance(arrPropertyStatTable.begin(), arrPropertyStatTableItor);
							if (i >= 0 && i < dwPropertyStatTableLength)
							{
								if (arrPropertyStatTableItor != arrPropertyStatTable.end())
								{
									arrPropertyStatTable[i] = wStatID;
									++arrPropertyStatTableItor;
								}
							}
						}
						else
						{	//is this a bug in D2 code? sometimes we'll roll an enhanced percentage damage mod, but the relevant stats are not in
							//the stat table for the item. This seems to affect nonmagic superior items only.
							//In this case, we'll just check for the other non-percentage stats...
							//TODO: seems to work so far, more investigation needed.
							//other mods such as + to attack rating, durability, etc seem to work as expected, even when paired with a strange min/max dmg % mod
							_tmp_customd2common_(D2C_Stat::STATS_MAXDAMAGE)
							_tmp_customd2common_(D2C_Stat::STATS_SECONDARY_MAXDAMAGE)
							_tmp_customd2common_(D2C_Stat::STATS_ITEM_THROW_MAXDAMAGE)
						}

						wStatID = static_cast<WORD>(D2C_Stat::STATS_ITEM_MINDAMAGE_PERCENT);
						mapPropertyStatMaxTableRecord = mapPropertyStatMaxTable.find(wStatID);
						if (mapPropertyStatMaxTableRecord != mapPropertyStatMaxTable.end())
						{
							ptrdiff_t i = std::distance(arrPropertyStatTable.begin(), arrPropertyStatTableItor);
							if (i >= 0 && i < dwPropertyStatTableLength)
							{
								if (arrPropertyStatTableItor != arrPropertyStatTable.end())
								{
									arrPropertyStatTable[i] = wStatID;
									++arrPropertyStatTableItor;
								}
							}
						}
						else
						{	//see comments above for STATS_ITEM_MAXDAMAGE_PERCENT
							_tmp_customd2common_(D2C_Stat::STATS_MINDAMAGE)
							_tmp_customd2common_(D2C_Stat::STATS_SECONDARY_MINDAMAGE)
							_tmp_customd2common_(D2C_Stat::STATS_ITEM_THROW_MINDAMAGE)
						}
					}

					#undef  _tmp_customd2common_
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
				else if (arrPropertyStatTable[j] == static_cast<WORD>(D2C_Stat::STATS_ITEM_NUMSOCKETS))
				{
					continue;
				}
				else
				{
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

		auto doSpecItemStatTableMerge = [&doMergeStatTable](DWORD32* ptrItemProp1Base, DWORD32 iterations)
		{
			if (ptrItemProp1Base == nullptr)
				return;

			DWORD32* ptrItemPropNBase = 0;
			DWORD32 dwPropNModCode = 0;
			DWORD32 dwMaxN = 0;
			for (DWORD32 i = 0; i < iterations; ++i)
			{
				ptrItemPropNBase = ptrItemProp1Base + (i * 4);
				dwPropNModCode = *ptrItemPropNBase;
				dwMaxN = *(ptrItemPropNBase + 3);

				if (dwPropNModCode >= _D2C_dwMaxMod)
					break;

				doMergeStatTable(dwPropNModCode, dwMaxN);
			}
		};

		if (itemQuality == D2C_ItemQuality::ITEMQUALITY_SET)
		{
			SetItemsBIN* ptrSetItemRecord = D2COMMON_TXT_GetSetItemRecord(ptrItemUnit);
			if (ptrSetItemRecord != nullptr)
			{
				DWORD32* ptrSetItemProp1Base = &ptrSetItemRecord->dwProp1;
				doSpecItemStatTableMerge(ptrSetItemProp1Base, 9);
			}
		}
		else if (itemQuality == D2C_ItemQuality::ITEMQUALITY_UNIQUE)
		{
			UniqueItemsBIN* ptrUniqueItemRecord = getItemUniqueAffix(ptrItemUnit);
			if (ptrUniqueItemRecord != nullptr)
			{
				DWORD32* ptrUniqueItemProp1Base = &ptrUniqueItemRecord->dwProp1ModCode;
				doSpecItemStatTableMerge(ptrUniqueItemProp1Base, 12);
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

					doMergeStatTable(blah->dwMod1Code, blah->dwMod1Max);
					doMergeStatTable(blah->dwMod2Code, blah->dwMod2Max);
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
					std::cout << "Couldn't find a valid QualityItemsTXT index!" << std::endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
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
				ItemData* ptrItemData = ptrItemUnit->ptItemData;
				if (ptrItemData != nullptr)
				{
					if (itemQuality == D2C_ItemQuality::ITEMQUALITY_SUPERIOR)
					{	//TODO: if all scenarios involving superior items were handled beforehand, then this block is dead code
						//check in QualityItems.txt
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE | FOREGROUND_INTENSITY);
						DWORD32 dwQualityItemsIndexCode = ptrItemData->uniqueID;
						QualityItemsTXT* blah = D2COMMON_ITEMRECORDS_GetItemQualityRecord(dwQualityItemsIndexCode);
						std::cout << '[' << std::hex << std::uppercase << blah->dwMod1Code << ']';
						std::cout << '[' << std::dec << blah->dwMod1Min << '-' << blah->dwMod1Max << ']';
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
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_WHITE);
		std::cout << "-----------------------------\n" << "Entering New Game\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
	
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