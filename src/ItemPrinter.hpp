#pragma once

struct ItemPrinter
{
	__declspec(dllexport) static void __stdcall doPrintItemLowQualityString(Unit* ptrItemUnit);
	__declspec(dllexport) static bool __stdcall doPrintItemStats(Unit* ptrItemUnit);
	__declspec(dllexport) static void __stdcall doPrintItemRareAffix(Unit* ptrItemUnit);
	__declspec(dllexport) static void __stdcall doPrintItemUniqueAffix(Unit* const ptrItemUnit);
	__declspec(dllexport) static void __stdcall doPrintItemSetAffix(Unit* ptrItemUnit);
	__declspec(dllexport) static void __stdcall doPrintItemMagicPrefix(Unit* ptrItemUnit);
	__declspec(dllexport) static void __stdcall doPrintAffixWeight(D2AutoMagicTxt* ptrMagicAffixRecord, const D2Stat &d2Stat);
	__declspec(dllexport) static void __stdcall doPrintAffixWeights(Unit* ptrItemUnit);
	__declspec(dllexport) static void __stdcall doPrintItemMagicSuffix(Unit* ptrItemUnit);
	__declspec(dllexport) static void __fastcall doPrintItemName(Unit* ptrItemUnit);
};

namespace ItemPrinterDetour
{
	__declspec(naked) static DWORD32 __fastcall detourPrintItemName(void)
	{
		__asm
		{
			MOV ECX, DWORD PTR[EBP]
			CALL ItemPrinter::doPrintItemName
			MOV EAX, 1
			RETN
		}
	}
}

__declspec(dllexport) void __stdcall ItemPrinter::doPrintItemUniqueAffix(Unit* const ptrItemUnit)
{
	UniqueItemsBIN* ptrUniqueItemRecord = CommonD2Funcs::getItemUniqueAffix(ptrItemUnit);
	if (ptrUniqueItemRecord != nullptr)
	{
		std::wcout << D2LANG_GetTableString(ptrUniqueItemRecord->wUniqueItemID) << L"!! ";
	}
}

__declspec(dllexport) void __stdcall ItemPrinter::doPrintItemRareAffix(Unit* ptrItemUnit)
{
	WORD rarePrefix = D2COMMON_ITEMS_GetRarePrefix(ptrItemUnit);
	WORD rareSuffix = D2COMMON_ITEMS_GetRareSuffix(ptrItemUnit);

	RareAffixTable* rATable = D2COMMON_TXT_GetRareAffixRecord(rarePrefix);
	if (rATable != nullptr)
	{
		std::wcout << D2LANG_GetTableString(rATable->wTableIndex);
	}

	rATable = D2COMMON_TXT_GetRareAffixRecord(rareSuffix);
	if (rATable != nullptr)
	{
		std::wcout << ' ' << D2LANG_GetTableString(rATable->wTableIndex);
	}

	std::cout << "! ";
}

__declspec(dllexport) void __stdcall ItemPrinter::doPrintItemSetAffix(Unit* ptrItemUnit)
{
	SetItemsBIN* ptrSetItemRecord = D2COMMON_TXT_GetSetItemRecord(ptrItemUnit);
	if (ptrSetItemRecord != nullptr)
	{
		std::cout << ptrSetItemRecord->szName << "! ";
	}
}

__declspec(dllexport) void __stdcall ItemPrinter::doPrintItemMagicPrefix(Unit* ptrItemUnit)
{
	for (int i = 0; i < 3; ++i)
	{
		WORD wMagicPrefixCode = D2COMMON_ITEMRECORDS_GetItemMagicPrefix(ptrItemUnit, i);
		D2AutoMagicTxt* ptrMagicPrefixRecord = D2COMMON_TXT_GetMagicAffixRecord(wMagicPrefixCode);
		if (ptrMagicPrefixRecord != nullptr)
		{
			uintptr_t f = (uintptr_t)ptrMagicPrefixRecord;
			DWORD32 k = (DWORD32)*D2COMMON_ptrMagicAffixTable;
			DWORD32 fk = (f - k) / sizeof(D2AutoMagicTxt);
			std::cout << '[' << std::dec << fk << ']';
			std::cout << ptrMagicPrefixRecord->szName << ' ';

			//TODO: testing
			//printAffixWeights(ptrMagicPrefixRecord, ptrItemUnit);


			/*if (ptrMagicPrefixRecord->dwMod1Min >= 4294960000)
			{
				continue;
			}

			if (ptrItemUnit->ptStats != nullptr)
			{
				if (ptrItemUnit->ptStats->ptAffixStats != nullptr)
				{
					if (ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable != nullptr)
					{
						for (int i = 0; i < ptrItemUnit->ptStats->ptAffixStats->nbBaseStats; ++i)
						{
							D2Stat d2Stat = { 0 };
							d2Stat.index = ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable[i].index;
							d2Stat.id = ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable[i].id;
							d2Stat.value = ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable[i].value;

							//new: assuming that if stat1 of the current mod exceeds dwItemStatCostRecs, then there is just one stat for this mod
							if (ptrMagicPrefixRecord->dwMod1Code < (*D2COMMON_sgptDataTables)->dwProportiesRecs)
							{
								PropertiesBIN* ptrPropertyRec = (*D2COMMON_sgptDataTables)->pPropertiesTxt + ptrMagicPrefixRecord->dwMod1Code;
								if (ptrPropertyRec->stat1 >= (*D2COMMON_sgptDataTables)->dwItemStatCostRecs)
								{
									//if (ptrMagicPrefixRecord->dwMod1Min < ptrMagicPrefixRecord->dwMod1Max && static_cast<DWORD32>(d2Stat.value) <= ptrMagicPrefixRecord->dwMod1Max)
									DWORD32 modMin = 0;
									DWORD32 modMax = 0;
									float score = 0;
									if (ptrPropertyRec->modcode == ptrMagicPrefixRecord->dwMod1Code)
									{
										modMin = ptrMagicPrefixRecord->dwMod1Min;
										modMax = ptrMagicPrefixRecord->dwMod1Max;
									}
									else if (ptrPropertyRec->modcode == ptrMagicPrefixRecord->dwMod2Code)
									{
										modMin = ptrMagicPrefixRecord->dwMod2Min;
										modMax = ptrMagicPrefixRecord->dwMod2Max;
									}
									else if (ptrPropertyRec->modcode == ptrMagicPrefixRecord->dwMod3Code)
									{
										modMin = ptrMagicPrefixRecord->dwMod3Min;
										modMax = ptrMagicPrefixRecord->dwMod3Max;
									}

									if (modMin < modMax)
									{
										//std::cout << ' ' << d2Stat.id << ' ' << std::dec << ptrPropertyRec->modcode << ' ' << ptrMagicPrefixRecord->dwMod1Code << ' ';
										score = (float)modMax;
										char szdbgBuffer[0x100] = { 0 };
										sprintf_s(szdbgBuffer, _countof(szdbgBuffer), "[%d:%d/%d]", d2Stat.id, d2Stat.value, static_cast<int>( score ));
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
										std::cout << szdbgBuffer;
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
									}
									//break;
								}
							}
							//end new
							*/
							/*
							close... missing calculations for some items. eg:
							. . . . .
							Prevent Monster Heal
							+11% Enhanced Damage
							[932]Jagged Giant Sword of Vileness[275](1e)

							row 932: mod1 = 0x1D::(0)[10.20] (no other mods for this row)
							stat1-7 for mod 0x1D: all invalid... looks like this is somewhat common for other stats as well


							and the obvious formatting issue..
							. . . . .
							+6 poison damage over 2 seconds
							[1301]Septic (57: 100%) (58: 100%) (59: 161%) Pilum(2c)

							fyi
							D2C_Stat::STATS_POISONMINDAM,
							D2C_Stat::STATS_POISONMAXDAM,
							D2C_Stat::STATS_POISONLENGTH,


							hmmm..
							. . . . .
							22% Better Chance of Getting Magic Items
							Lightning Resist +19%
							[1136]Ocher (41: 95%) (80: 110%) Heavy Boots of Fortune[286](f)


							is this right?
							. . . . .
							11% Damage Taken Goes To Mana
							Magic Damage Reduced by 1
							[945]Vulpine (35: 1/12) (114: 11/12) [i17]Amulet of Warding[123](c)


							hmmm...
							. . . . .
							+1 to Mana after each Kill
							Adds 1-3 cold damage
							[1163]Triumphant (54: 1/1) (55: 3/1) (56: 75/1) (138: 1/1) Falchion of the Icicle[176](1e)


							lets try...

							do not compute 'star' value:
							if mod min > mod max
							if mod min == mod max
							if mod max <= 0

							*/

							//if (d2Stat.id >= (*D2COMMON_sgptDataTables)->dwItemStatCostRecs)
							//{
							//	continue;
							//}

							/*if (checkPropertyModContainsStat(ptrMagicPrefixRecord->dwMod1Code, d2Stat.id))
							{
								char szdbgBuffer[0x100] = { 0 };
								sprintf_s(szdbgBuffer, _countof(szdbgBuffer), "(%d: %d%%)", d2Stat.id, static_cast<int>( (d2Stat.value / (float)ptrMagicPrefixRecord->dwMod1Max) * 100) );
								std::cout << szdbgBuffer << ' ';
							}
							else*/

							//new
							/*
							float score = 0;

							if (d2Stat.id >= (*D2COMMON_sgptDataTables)->dwItemStatCostRecs)
							{
								//TODO: is this code ever reached?
								score = (float)ptrMagicPrefixRecord->dwMod1Max;
								char szdbgBuffer[0x100] = { 0 };
								sprintf_s(szdbgBuffer, _countof(szdbgBuffer), "<<%d:%d/%d>>", d2Stat.id, d2Stat.value, static_cast<int>( score ));
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
								std::cout << szdbgBuffer;
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
								break;
							}
							else if (checkPropertyModContainsStat(ptrMagicPrefixRecord->dwMod1Code, d2Stat.id))
							{
								score = (float)ptrMagicPrefixRecord->dwMod1Max;
							}
							else if (checkPropertyModContainsStat(ptrMagicPrefixRecord->dwMod2Code, d2Stat.id))
							{
								//if (ptrMagicPrefixRecord->dwMod2Min > ptrMagicPrefixRecord->dwMod2Max)
								//continue;
								//if (ptrMagicPrefixRecord->dwMod2Min == ptrMagicPrefixRecord->dwMod2Max)
								//	continue;
								//if (ptrMagicPrefixRecord->dwMod2Max <= 0)
								//	continue;

								
								//score = (d2Stat.value / (float)ptrMagicPrefixRecord->dwMod2Max) * 100.f;
								score = (float)ptrMagicPrefixRecord->dwMod2Max;
							}
							else if (checkPropertyModContainsStat(ptrMagicPrefixRecord->dwMod3Code, d2Stat.id))
							{
								//if (ptrMagicPrefixRecord->dwMod3Min > ptrMagicPrefixRecord->dwMod3Max)
								//continue;
								//if (ptrMagicPrefixRecord->dwMod3Min == ptrMagicPrefixRecord->dwMod3Max)
								//	continue;
								//if (ptrMagicPrefixRecord->dwMod3Max <= 0)
								//	continue;

								//score = (d2Stat.value / (float)ptrMagicPrefixRecord->dwMod3Max) * 100.f;
								score = (float)ptrMagicPrefixRecord->dwMod3Max;
							}
							//else... deal with mods that have invalid stat values? eg: mod 0x1D::(0)[21.30]
							//this doesn't make good output, because the stat probably belongs in suffix mod list
							//else if (ptrMagicPrefixRecord->dwMod1Min < ptrMagicPrefixRecord->dwMod1Max)
							//{
							//	std::cout << '!';
							//	score = (float)ptrMagicPrefixRecord->dwMod1Max;
							//	char szdbgBuffer[0x100] = { 0 };
							//	sprintf_s(szdbgBuffer, _countof(szdbgBuffer), "(%d:%d/%d)", d2Stat.id, d2Stat.value, static_cast<int>( score ));
							//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
							//	std::cout << szdbgBuffer;
							//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
							//	continue;
							//}

							if (score > 0)
							{
								char szdbgBuffer[0x100] = { 0 };

								if (d2Stat.value > score)
								{
									//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
									//sprintf_s(szdbgBuffer, _countof(szdbgBuffer), "(%d:%d/%d)", d2Stat.id, (d2Stat.value >> 8), static_cast<int>( score ));

									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
									//sprintf_s(szdbgBuffer, _countof(szdbgBuffer), "(%d:%d/%d)", d2Stat.id, (d2Stat.value >> 8), static_cast<int>( score ));
									ItemStatCostBIN* ptrISC = ((*D2COMMON_sgptDataTables)->pItemStatCostTxt) + d2Stat.id;
									BYTE bValShift = ptrISC->valshift;
									//assumption: valid valshift values are always 8...
									if (bValShift == 8)
									{
										score = ((d2Stat.value >> bValShift) / score) * 100.f;
										sprintf_s(szdbgBuffer, _countof(szdbgBuffer), "(%d:%d%%)", d2Stat.id, static_cast<int>( score ));
									}
									else
									{
										sprintf_s(szdbgBuffer, _countof(szdbgBuffer), "(%d:%d/%d)", d2Stat.id, d2Stat.value, static_cast<int>( score ));
									}
								}
								//new / test
								else if (std::abs(d2Stat.value) <= score )
								{
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
									score = (std::abs(d2Stat.value) / score) * 100.f;
									sprintf_s(szdbgBuffer, _countof(szdbgBuffer), "(%d:%d%%)", d2Stat.id, static_cast<int>( score ));
								}
								else
								{
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
									score = (d2Stat.value / score) * 100.f;
									sprintf_s(szdbgBuffer, _countof(szdbgBuffer), "(%d:%d%%)", d2Stat.id, static_cast<int>( score ));
								}
								
								std::cout << szdbgBuffer;
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
							}
						}
					}
				}
			}*/
			//end test

			///////////////////

		}
	}
}

__declspec(dllexport) void __stdcall ItemPrinter::doPrintItemLowQualityString(Unit* ptrItemUnit)
{
	DWORD dwItemIndex = D2COMMON_ITEMS_GetFileIndex(ptrItemUnit);
	char* szPlzDontCrash = D2COMMON_ITEMRECORDS_GetQualityStringFromIndex(dwItemIndex);
	if (szPlzDontCrash != nullptr)
	{
		char buffer[32] = { 0 };
		strncpy_s(buffer, _countof(buffer), szPlzDontCrash, _TRUNCATE);
		std::cout << buffer << ' ';
	}
}

__declspec(dllexport) bool __stdcall ItemPrinter::doPrintItemStats(Unit* ptrItemUnit)
{
	if (ptrItemUnit->ptStats != nullptr)
	{
		if (ptrItemUnit->ptStats->ptAffixStats != nullptr)
		{
			if (ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable != nullptr)
			{
				const size_t nBufferLen = 0x800;
				wchar_t szAffixTextBuffer[nBufferLen] = { 0 };
				wchar_t buffer[nBufferLen] = { 0 };
				CommonD2Funcs::getItemAffixText(ptrItemUnit, szAffixTextBuffer);
				wcscpy_s(buffer, nBufferLen, szAffixTextBuffer);
				std::wcout << buffer;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
				return true;
			}
		}
	}
	return false;
}

__declspec(dllexport) void __stdcall ItemPrinter::doPrintAffixWeight(D2AutoMagicTxt* ptrMagicAffixRecord, const D2Stat &d2Stat)
{
	if (ptrMagicAffixRecord == nullptr)
		return;

	DWORD32 dwModNCode = CommonD2Funcs::findModContainingStat(ptrMagicAffixRecord, d2Stat);
	if (dwModNCode < _D2C_dwMaxMod)
	{
		DWORD32 dwModNMax = CommonD2Funcs::findModMax(ptrMagicAffixRecord, dwModNCode);
		uint32_t nStatValue = d2Stat.value;
		ItemStatCostBIN* ptrISC = ((*D2COMMON_sgptDataTables)->pItemStatCostTxt) + static_cast<WORD>(d2Stat.id);
		BYTE bValShift = ptrISC->valshift;
		if (bValShift > 0 && bValShift <= 32)
		{
			//nStatValue = nStatValue >> bValShift;
			//test
			do
			{
				std::cout << '*';
				nStatValue = nStatValue >> bValShift;
			} while ( (nStatValue >> bValShift) > dwModNMax);
			//end test
		}

		if (nStatValue <= dwModNMax)
		{
			if (ptrISC->descstrpos > 0 && ptrISC->descstrpos != static_cast<WORD>(D2ClassicStrings::D2STR_DUMMY))
			{
				std::wcout << D2LANG_GetTableString(ptrISC->descstrpos) << ": ";
			}
			else
			{
				std::cout << std::dec << static_cast<WORD>(d2Stat.id) << ": ";
			}
			std::cout << std::dec << nStatValue << '(' << std::setprecision(4) << (nStatValue / (float)dwModNMax) * 100 << "%)" << std::endl;
		}
		else
		{
			std::cout << std::hex << dwModNCode << ' ' << std::dec << static_cast<WORD>(d2Stat.id) << ' ' << d2Stat.value << ' ' << dwModNMax << std::endl;
		}
	}
	//TODO: new/testing
	//else if( ptrMagicAffixRecord->dwMod1Code < dwMaxModCode )
	//{
	//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
	//	PropertiesBIN* ptrProperties = ((*D2COMMON_sgptDataTables)->pPropertiesTxt) + ptrMagicAffixRecord->dwMod1Code;
	//	if (ptrProperties->stat1 >= (*D2COMMON_sgptDataTables)->dwItemStatCostRecs)
	//	{
	//		ItemStatCostBIN* ptrISC = ((*D2COMMON_sgptDataTables)->pItemStatCostTxt) + static_cast<WORD>(d2Stat.id);
	//
	//		std::cout << '[' << std::hex << std::uppercase << ptrMagicAffixRecord->dwMod1Code << ']';
	//
	//		if (ptrISC->descstrpos > 0 && ptrISC->descstrpos != static_cast<WORD>(D2ClassicStrings::D2STR_DUMMY))
	//		{
	//			std::wcout << D2LANG_GetTableString(ptrISC->descstrpos) << ": ";
	//		}
	//		else
	//		{
	//			std::cout << std::dec << static_cast<WORD>(d2Stat.id) << ": ";
	//		}
	//		std::cout << std::dec << d2Stat.value << '/' << ptrMagicAffixRecord->dwMod1Max << std::endl;
	//	}
	//}
	///////////////////
}

__declspec(dllexport) void __stdcall ItemPrinter::doPrintAffixWeights(Unit* ptrItemUnit)
{
	if (ptrItemUnit->ptStats == nullptr)
		return;
	if (ptrItemUnit->ptStats->ptAffixStats == nullptr)
		return;
	if (ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable == nullptr)
		return;

	std::cout << '\n';

	CommonD2Funcs::doMagicAffixPrint(ptrItemUnit);
}

__declspec(dllexport) void __stdcall ItemPrinter::doPrintItemMagicSuffix(Unit* ptrItemUnit)
{
	for (int i = 0; i < 3; ++i)
	{
		WORD wMagicSuffixCode = D2COMMON_ITEMRECORDS_GetItemMagicSuffix(ptrItemUnit, i);
		D2AutoMagicTxt* ptrMagicSuffixRecord = D2COMMON_TXT_GetMagicAffixRecord(wMagicSuffixCode);

		if (ptrMagicSuffixRecord != nullptr)
		{
			uintptr_t f = (uintptr_t)ptrMagicSuffixRecord;
			DWORD32 k = (DWORD32)*D2COMMON_ptrMagicAffixTable;
			DWORD32 fk = (f - k) / sizeof(D2AutoMagicTxt);

			//std::cout << '[' << std::hex << std::uppercase << ptrMagicSuffixRecord->dwGroup << ']';
			//char buffer[5] = { '\0' };
			//sprintf_s(buffer, sizeof(buffer) / sizeof(buffer[0]), "%04X", ptrMagicSuffixRecord->wTblIndex);
			//sprintf_s(buffer, sizeof(buffer) / sizeof(buffer[0]), "%04X", wMagicSuffixCode);
			//std::cout << '[' << buffer << ']';

			std::cout << ' ' << ptrMagicSuffixRecord->szName;
			std::cout << '[' << std::dec << fk << ']';
			//doModPrint(ptrMagicSuffixRecord->dwMod1Param, ptrMagicSuffixRecord->dwMod1Min, ptrMagicSuffixRecord->dwMod1Max);
			//doModPrint(ptrMagicSuffixRecord->dwMod2Param, ptrMagicSuffixRecord->dwMod2Min, ptrMagicSuffixRecord->dwMod2Max);
			//doModPrint(ptrMagicSuffixRecord->dwMod3Param, ptrMagicSuffixRecord->dwMod3Min, ptrMagicSuffixRecord->dwMod3Max);

			//TODO: testing
			//printAffixWeights(ptrMagicSuffixRecord, ptrItemUnit);


			/*if (ptrMagicSuffixRecord->dwMod1Min >= 4294960000)
			{
				continue;
			}

			if (ptrItemUnit->ptStats != nullptr)
			{
				if (ptrItemUnit->ptStats->ptAffixStats != nullptr)
				{
					if (ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable != nullptr)
					{
						for (int i = 0; i < ptrItemUnit->ptStats->ptAffixStats->nbBaseStats; ++i)
						{
							D2Stat d2Stat = { 0 };
							d2Stat.index = ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable[i].index;
							d2Stat.id = ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable[i].id;
							d2Stat.value = ptrItemUnit->ptStats->ptAffixStats->ptBaseStatsTable[i].value;

							//new: assuming that if stat1 of the current mod exceeds dwItemStatCostRecs, then there is just one stat for this mod
							if (ptrMagicSuffixRecord->dwMod1Code < (*D2COMMON_sgptDataTables)->dwProportiesRecs)
							{
								PropertiesBIN* ptrPropertyRec = (*D2COMMON_sgptDataTables)->pPropertiesTxt + ptrMagicSuffixRecord->dwMod1Code;
								if (ptrPropertyRec->stat1 >= (*D2COMMON_sgptDataTables)->dwItemStatCostRecs)
								{
									//if (ptrMagicPrefixRecord->dwMod1Min < ptrMagicPrefixRecord->dwMod1Max && static_cast<DWORD32>(d2Stat.value) <= ptrMagicPrefixRecord->dwMod1Max)
									DWORD32 modMin = 0;
									DWORD32 modMax = 0;
									float score = 0;
									if (ptrPropertyRec->modcode == ptrMagicSuffixRecord->dwMod1Code)
									{
										modMin = ptrMagicSuffixRecord->dwMod1Min;
										modMax = ptrMagicSuffixRecord->dwMod1Max;
									}
									else if (ptrPropertyRec->modcode == ptrMagicSuffixRecord->dwMod2Code)
									{
										modMin = ptrMagicSuffixRecord->dwMod2Min;
										modMax = ptrMagicSuffixRecord->dwMod2Max;
									}
									else if (ptrPropertyRec->modcode == ptrMagicSuffixRecord->dwMod3Code)
									{
										modMin = ptrMagicSuffixRecord->dwMod3Min;
										modMax = ptrMagicSuffixRecord->dwMod3Max;
									}

									if (modMin < modMax)
									{
										//std::cout << ' ' << d2Stat.id << ' ' << std::dec << ptrPropertyRec->modcode << ' ' << ptrMagicSuffixRecord->dwMod1Code << ' ';
										score = (float)modMax;
										char szdbgBuffer[0x100] = { 0 };
										sprintf_s(szdbgBuffer, _countof(szdbgBuffer), "[%d:%d/%d]", d2Stat.id, d2Stat.value, static_cast<int>( score ));
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
										std::cout << szdbgBuffer;
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
									}
									//break;
								}
							}
							//end new

							//new
							float score = 0;

							if (d2Stat.id >= (*D2COMMON_sgptDataTables)->dwItemStatCostRecs)
							{
								//TODO: is this code ever reached?
								score = (float)ptrMagicSuffixRecord->dwMod1Max;
								char szdbgBuffer[0x100] = { 0 };
								sprintf_s(szdbgBuffer, _countof(szdbgBuffer), "<<%d:%d/%d>>", d2Stat.id, d2Stat.value, static_cast<int>( score ));
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
								std::cout << szdbgBuffer;
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
								break;
							}
							else if (checkPropertyModContainsStat(ptrMagicSuffixRecord->dwMod1Code, d2Stat.id))
							{
								score = (float)ptrMagicSuffixRecord->dwMod1Max;
							}
							else if (checkPropertyModContainsStat(ptrMagicSuffixRecord->dwMod2Code, d2Stat.id))
							{
								//if (ptrMagicPrefixRecord->dwMod2Min > ptrMagicPrefixRecord->dwMod2Max)
								//continue;
								//if (ptrMagicPrefixRecord->dwMod2Min == ptrMagicPrefixRecord->dwMod2Max)
								//	continue;
								//if (ptrMagicPrefixRecord->dwMod2Max <= 0)
								//	continue;

								
								//score = (d2Stat.value / (float)ptrMagicPrefixRecord->dwMod2Max) * 100.f;
								score = (float)ptrMagicSuffixRecord->dwMod2Max;
							}
							else if (checkPropertyModContainsStat(ptrMagicSuffixRecord->dwMod3Code, d2Stat.id))
							{
								//if (ptrMagicPrefixRecord->dwMod3Min > ptrMagicPrefixRecord->dwMod3Max)
								//continue;
								//if (ptrMagicPrefixRecord->dwMod3Min == ptrMagicPrefixRecord->dwMod3Max)
								//	continue;
								//if (ptrMagicPrefixRecord->dwMod3Max <= 0)
								//	continue;

								//score = (d2Stat.value / (float)ptrMagicPrefixRecord->dwMod3Max) * 100.f;
								score = (float)ptrMagicSuffixRecord->dwMod3Max;
							}
							//else... deal with mods that have invalid stat values? eg: mod 0x1D::(0)[21.30]
							//this doesn't make good output, because the stat probably belongs in suffix mod list
							//else if (ptrMagicPrefixRecord->dwMod1Min < ptrMagicPrefixRecord->dwMod1Max)
							//{
							//	std::cout << '!';
							//	score = (float)ptrMagicPrefixRecord->dwMod1Max;
							//	char szdbgBuffer[0x100] = { 0 };
							//	sprintf_s(szdbgBuffer, _countof(szdbgBuffer), "(%d:%d/%d)", d2Stat.id, d2Stat.value, static_cast<int>( score ));
							//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
							//	std::cout << szdbgBuffer;
							//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
							//	continue;
							//}

							if (score > 0)
							{
								char szdbgBuffer[0x100] = { 0 };

								if (d2Stat.value > score)
								{
									//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
									//sprintf_s(szdbgBuffer, _countof(szdbgBuffer), "(%d:%d/%d)", d2Stat.id, (d2Stat.value >> 8), static_cast<int>( score ));

									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
									//sprintf_s(szdbgBuffer, _countof(szdbgBuffer), "(%d:%d/%d)", d2Stat.id, (d2Stat.value >> 8), static_cast<int>( score ));
									ItemStatCostBIN* ptrISC = ((*D2COMMON_sgptDataTables)->pItemStatCostTxt) + d2Stat.id;
									BYTE bValShift = ptrISC->valshift;
									//assumption: valid valshift values are always 8...
									if (bValShift == 8)
									{
										score = ((d2Stat.value >> bValShift) / score) * 100.f;
										sprintf_s(szdbgBuffer, _countof(szdbgBuffer), "(%d:%d%%)", d2Stat.id, static_cast<int>( score ));
									}
									else
									{
										sprintf_s(szdbgBuffer, _countof(szdbgBuffer), "(%d:%d/%d)", d2Stat.id, d2Stat.value, static_cast<int>( score ));
									}
								}
								//new / test
								else if (std::abs(d2Stat.value) <= score )
								{
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
									score = (std::abs(d2Stat.value) / score) * 100.f;
									sprintf_s(szdbgBuffer, _countof(szdbgBuffer), "(%d:%d%%)", d2Stat.id, static_cast<int>( score ));
								}
								else
								{
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
									score = (d2Stat.value / score) * 100.f;
									sprintf_s(szdbgBuffer, _countof(szdbgBuffer), "(%d:%d%%)", d2Stat.id, static_cast<int>( score ));
								}
								
								std::cout << szdbgBuffer;
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
							}
						}
					}
				}
			}*/
			//end test

			///////////////////

		}
	}
}

__declspec(dllexport) void __fastcall ItemPrinter::doPrintItemName(Unit* ptrItemUnit)
{
	if (ptrItemUnit == nullptr)
		return;

	if (ptrItemUnit->nUnitType != static_cast<DWORD32>(D2C_UnitType::UNIT_ITEM))
		return;

	int dwQuality = D2COMMON_ITEMS_GetQuality(ptrItemUnit);
	D2C_ItemQuality itemQuality = static_cast<D2C_ItemQuality>(dwQuality);

	//This test should fix log spamming while shopping
	if (D2COMMON_DRLG_GetRoomFromUnit(ptrItemUnit) == nullptr)
	{
		if (itemQuality != D2C_ItemQuality::ITEMQUALITY_RARE &&
			itemQuality != D2C_ItemQuality::ITEMQUALITY_UNIQUE &&
			itemQuality != D2C_ItemQuality::ITEMQUALITY_SET &&
			itemQuality != D2C_ItemQuality::ITEMQUALITY_SUPERIOR)
		{
			bool isElite = CommonD2Funcs::checkIfItemElite(D2COMMON_ITEMRECORDS_GetCodeFromUnit(ptrItemUnit));
			bool isWhiteElite = (isElite && itemQuality != D2C_ItemQuality::ITEMQUALITY_MAGIC);
			bool isSocketed = false;
			if (isWhiteElite)
			{
				DWORD32 dwItemSockets = D2COMMON_UNITS_GetUnitStat(ptrItemUnit, static_cast<int>(D2C_Stat::STATS_ITEM_NUMSOCKETS), 0);
				if (dwItemSockets > 0)
					isSocketed = true;
			}
			if (!(isWhiteElite && isSocketed))
				return;
		}
	}


	DWORD dwItemCode = D2COMMON_ITEMRECORDS_GetCodeFromUnit(ptrItemUnit);
	D2C_ItemCodes itemCode = static_cast<D2C_ItemCodes>(dwItemCode);
	
	bool isJunkItem = RuleManager.RuleEvalJunkItemCode.evaluate(itemCode);
	if (isJunkItem)
		return;

	int dwItemType = D2COMMON_ITEMRECORDS_GetItemTypeFromItem(ptrItemUnit);
	D2C_ItemTypes itemType = static_cast<D2C_ItemTypes>( dwItemType );

	isJunkItem = RuleManager.RuleEvalJunkItemType.evaluate(itemType);
	if (isJunkItem)
		return;


	BYTE isNormal = D2COMMON_ITEMTYPERECORDS_GetNormal(ptrItemUnit);
	if (!isNormal)
	{
		//skip low quality items?
		if (itemQuality >= D2C_ItemQuality::ITEMQUALITY_CRACKED && itemQuality <= D2C_ItemQuality::ITEMQUALITY_TEMPERED)
		{
			if (itemQuality == D2C_ItemQuality::ITEMQUALITY_CRAFTED)
			{
				std::cout << "[NEW:" << CommonD2Funcs::checkFlag(ptrItemUnit, D2C_ItemFlags::ITEMFLAG_NEWITEM) << ']';
				std::cout << "[NEW2:" << CommonD2Funcs::checkFlag(ptrItemUnit, D2C_ItemFlags::ITEMFLAG_NEWITEM2) << ']';
				std::cout << "[ID? " << CommonD2Funcs::checkFlag(ptrItemUnit, D2C_ItemFlags::ITEMFLAG_IS_IDENTIFIED) << ']';
				
				//always junk value
				/*if (ptrItemUnit->ptItemData != nullptr)
				{
					std::cout << '[' << ptrItemUnit->ptItemData->playerID << ']';
				}*/
				//TODO: crafted items have multiple affixes applied to them, however not all of the are applied at this point
				//std::cout << '|' << D2COMMON_ITEMS_GetMagicPrefix(ptrItemUnit, 0) << '|';
				//std::cout << '|' << D2COMMON_ITEMRECORDS_GetItemSuffix(ptrItemUnit, 0) << '|';
			}
			else
			{
				bool bHasStats = doPrintItemStats(ptrItemUnit);
				if (itemQuality == D2C_ItemQuality::ITEMQUALITY_CRACKED && !bHasStats)
				{
					return;
				}
			}
		}
	}

	if (itemQuality <= D2C_ItemQuality::ITEMQUALITY_TEMPERED && !isNormal)
	{
		switch (itemQuality)
		{
		case D2C_ItemQuality::ITEMQUALITY_CRACKED:
			doPrintItemLowQualityString(ptrItemUnit);
			break;
		case D2C_ItemQuality::ITEMQUALITY_SUPERIOR:
			if (ptrItemUnit->ptItemData != nullptr)
			{
				WORD wAutoMagicAffixCode = ptrItemUnit->ptItemData->autoPref;
				//TODO: instead of hardcoding 747 and 1448, could we just look at the number of records for whatever file comes before autoaffix?
				if (wAutoMagicAffixCode > 747 && wAutoMagicAffixCode < 1448)
				{
					D2AutoMagicTxt* ptrAutoMagicRecord = D2COMMON_TXT_GetMagicAffixRecord(wAutoMagicAffixCode);
					if (ptrAutoMagicRecord != nullptr)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE | FOREGROUND_INTENSITY);
						std::cout << '[' << std::dec << wAutoMagicAffixCode - 1 << ']';
						std::cout << ptrAutoMagicRecord->szName << ' ';
					}
				}
			}
			break;
		case D2C_ItemQuality::ITEMQUALITY_MAGIC:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
			doPrintItemMagicPrefix(ptrItemUnit);
			//TODO: testing
			//printAffixWeights(ptrItemUnit);
			///////////////
			break;
		case D2C_ItemQuality::ITEMQUALITY_SET:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_WHITE);
			doPrintItemSetAffix(ptrItemUnit);
			break;
		case D2C_ItemQuality::ITEMQUALITY_RARE:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | BACKGROUND_YELLOW);
			std::cout << '#' << std::dec << ++UniqueItemCounter;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
			std::cout << ' ';
			doPrintItemRareAffix(ptrItemUnit);
			//TODO: testing
			//printAffixWeights(ptrItemUnit);
			//doPrintItemMagicPrefix(ptrItemUnit);
			//doPrintItemMagicSuffix(ptrItemUnit);
			///////////////
			break;
		case D2C_ItemQuality::ITEMQUALITY_UNIQUE:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_PURPLE | FOREGROUND_INTENSITY | BACKGROUND_WHITE);
			doPrintItemUniqueAffix(ptrItemUnit);
			//TODO: testing
			//printAffixWeights(ptrItemUnit);
			///////////////
			break;
		case D2C_ItemQuality::ITEMQUALITY_CRAFTED:
			//TODO
			std::cout << "[CRAFTED]";
			//works... but only if the crafted item is completely formed...
			//printItemMagicPrefix(ptrItemUnit);
			//printItemMagicSuffix(ptrItemUnit);
			break;
		case D2C_ItemQuality::ITEMQUALITY_TEMPERED:
			//TODO
			std::cout << "[TEMPERED]";
			break;
		}
	}
	/* ================================= */

	bool bPrintilvl = RuleManager.RuleEvalILvlPrint.evaluate(itemType);

	if (bPrintilvl)
	{
		if (itemQuality == D2C_ItemQuality::ITEMQUALITY_RARE)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | BACKGROUND_YELLOW);
		int dwItemlvl = D2COMMON_ITEMS_GetLevel(ptrItemUnit);
		std::cout << "[i" << std::dec << dwItemlvl << ']';
	}
	else
	{
		if (CommonD2Funcs::checkIfItemElite(dwItemCode))
		{
			std::cout << "Elite ";
		}

		int dwItemSockets = D2COMMON_UNITS_GetUnitStat(ptrItemUnit, static_cast<int>(D2C_Stat::STATS_ITEM_NUMSOCKETS), 0);
		if (dwItemSockets > 1)
			std::cout << '[' << dwItemSockets << "S]";

		BOOL isEthereal = D2COMMON_ITEMFLAGS_CheckEthereal(ptrItemUnit);
		if (isEthereal)
			std::cout << "Eth ";
	}

	const size_t nBufferLen = 0x100;
	wchar_t szBuffer[nBufferLen] = { '\0' };
	D2CLIENT_ITEMS_GetItemName(ptrItemUnit, szBuffer, nBufferLen);
	std::wcout << szBuffer;

	if (itemType == D2C_ItemTypes::ITEMTYPE_RUNE)
	{
		D2CLIENT_CHAT_PrintClientMessage(szBuffer, static_cast<BYTE>(D2C_D2Color::ORANGE));
	}

	if (itemQuality == D2C_ItemQuality::ITEMQUALITY_UNIQUE)
	{
		UniqueItemsBIN* ptrUniqueItemRecord = CommonD2Funcs::getItemUniqueAffix(ptrItemUnit);
		BOOL isEthereal = D2COMMON_ITEMFLAGS_CheckEthereal(ptrItemUnit);
		if (ptrUniqueItemRecord != nullptr)
		{
			if (isEthereal)
			{
				const wchar_t wszEthereal[] = L" (Ethereal!)";
				wchar_t *wszUniqueItemTitle = D2LANG_GetTableString(ptrUniqueItemRecord->wUniqueItemID);
				size_t nUniqueItemTitleLen = wcsnlen_s(wszUniqueItemTitle, 0x800) + _countof(wszEthereal) + 1;
				std::unique_ptr<wchar_t[]> wszMessage = std::make_unique<wchar_t[]>(nUniqueItemTitleLen);
				wcsncpy_s(wszMessage.get(), nUniqueItemTitleLen, wszUniqueItemTitle, _TRUNCATE);
				wcsncat_s(wszMessage.get(), nUniqueItemTitleLen, wszEthereal, _TRUNCATE);
				D2CLIENT_CHAT_PrintClientMessage(wszMessage.get(), static_cast<BYTE>(D2C_D2Color::DARK_YELLOW));
			}
			else
			{
				D2CLIENT_CHAT_PrintClientMessage(D2LANG_GetTableString(ptrUniqueItemRecord->wUniqueItemID), static_cast<BYTE>(D2C_D2Color::DARK_YELLOW));
			}
		}
	}

	if (itemQuality == D2C_ItemQuality::ITEMQUALITY_SET)
	{
		SetItemsBIN* ptrSetItemRecord = D2COMMON_TXT_GetSetItemRecord(ptrItemUnit);
		if (ptrSetItemRecord != nullptr)
		{
			D2CLIENT_CHAT_PrintClientMessage( D2LANG_GetTableString(ptrSetItemRecord->dwTblIndex)  , static_cast<BYTE>(D2C_D2Color::GREEN));
		}
	}

	if (itemQuality == D2C_ItemQuality::ITEMQUALITY_MAGIC && !isNormal)
	{
		doPrintItemMagicSuffix(ptrItemUnit);
		std::cout << '(' << std::hex << static_cast<int>(dwItemType) << ')';
	}

	//TODO:new
	if (ptrItemUnit->ptItemData != nullptr)
	{
		WORD wAutoMagicAffixCode = ptrItemUnit->ptItemData->autoPref;
		//TODO: instead of hardcoding 747 and 1447, could we just look at the number of records for whatever file comes before autoaffix?
		if (wAutoMagicAffixCode != 0 && (wAutoMagicAffixCode < 747 || wAutoMagicAffixCode > 1447))
		{
			D2AutoMagicTxt* ptrAutoMagicRecord = D2COMMON_TXT_GetMagicAffixRecord(wAutoMagicAffixCode);
			if (ptrAutoMagicRecord != nullptr)
			{
				std::cout << ' ' << ptrAutoMagicRecord->szName;
				std::cout << '[' << std::dec << wAutoMagicAffixCode - 1 << ']';
			}
		}
	}

	//TODO: testing
	doPrintAffixWeights(ptrItemUnit);
	///////////////

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
	std::cout << std::endl;
}