#pragma once

struct ItemPrinter
{
	__declspec(dllexport) static void __stdcall doPrintItemLowQualityString(Unit* ptrItemUnit);
	__declspec(dllexport) static bool __stdcall doPrintItemStats(Unit* ptrItemUnit);
	__declspec(dllexport) static void __stdcall doPrintItemRareAffix(Unit* ptrItemUnit);
	__declspec(dllexport) static void __stdcall doPrintItemUniqueAffix(Unit* const ptrItemUnit);
	__declspec(dllexport) static void __stdcall doPrintItemSetAffix(Unit* ptrItemUnit);
	__declspec(dllexport) static void __stdcall doPrintItemMagicPrefix(Unit* ptrItemUnit);
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
			std::cout << ' ' << ptrMagicSuffixRecord->szName;
			std::cout << '[' << std::dec << fk << ']';
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
			itemQuality != D2C_ItemQuality::ITEMQUALITY_SET)
		{
			bool isSupElite = CommonD2Funcs::checkIfItemElite(D2COMMON_ITEMRECORDS_GetCodeFromUnit(ptrItemUnit));
			isSupElite = isSupElite && (itemQuality == D2C_ItemQuality::ITEMQUALITY_SUPERIOR);
			if(!isSupElite)
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
			if (itemQuality != D2C_ItemQuality::ITEMQUALITY_CRAFTED)
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
				if (wAutoMagicAffixCode != 0)
				{
					D2AutoMagicTxt* ptrAutoMagicRecord = D2COMMON_TXT_GetMagicAffixRecord(wAutoMagicAffixCode);
					if (ptrAutoMagicRecord != nullptr)
					{
						bool isSuffix = (ptrAutoMagicRecord->szName[0] == 'o' && ptrAutoMagicRecord->szName[1] == 'f');
						if (!isSuffix)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE | FOREGROUND_INTENSITY);
							std::cout << '[' << std::dec << wAutoMagicAffixCode - 1 << ']';
							std::cout << ptrAutoMagicRecord->szName << ' ';
						}
					}
				}
			}
			break;
		case D2C_ItemQuality::ITEMQUALITY_MAGIC:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
			doPrintItemMagicPrefix(ptrItemUnit);
			break;
		case D2C_ItemQuality::ITEMQUALITY_SET:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
			doPrintItemSetAffix(ptrItemUnit);
			break;
		case D2C_ItemQuality::ITEMQUALITY_RARE:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE | FOREGROUND_INTENSITY);
			std::cout << '#' << std::dec << ++UniqueItemCounter;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
			std::cout << ' ';
			doPrintItemRareAffix(ptrItemUnit);
			//doPrintItemMagicPrefix(ptrItemUnit);
			//doPrintItemMagicSuffix(ptrItemUnit);
			break;
		case D2C_ItemQuality::ITEMQUALITY_UNIQUE:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_PURPLE | FOREGROUND_INTENSITY | BACKGROUND_WHITE);
			doPrintItemUniqueAffix(ptrItemUnit);
			break;
		case D2C_ItemQuality::ITEMQUALITY_CRAFTED:
			std::cout << "[CRAFTED]";
			break;
		case D2C_ItemQuality::ITEMQUALITY_TEMPERED:
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

	static const size_t nBufferLen = 0x100;
	wchar_t szBuffer[nBufferLen] = { '\0' };
	D2CLIENT_ITEMS_GetItemName(ptrItemUnit, szBuffer, nBufferLen);
	std::wcout << szBuffer;

	if (itemType == D2C_ItemTypes::ITEMTYPE_RUNE)
	{
		D2CLIENT_CHAT_PrintClientMessage(szBuffer, static_cast<BYTE>(D2C_D2Color::ORANGE));
	}
	else if (RuleManager.RuleEvalSpecialKeyCode.evaluate(itemCode))
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

	if (ptrItemUnit->ptItemData != nullptr)
	{
		WORD wAutoMagicAffixCode = ptrItemUnit->ptItemData->autoPref;
		if (wAutoMagicAffixCode != 0)
		{
			D2AutoMagicTxt* ptrAutoMagicRecord = D2COMMON_TXT_GetMagicAffixRecord(wAutoMagicAffixCode);
			if (ptrAutoMagicRecord != nullptr)
			{
				bool isSuffix = (ptrAutoMagicRecord->szName[0] == 'o' && ptrAutoMagicRecord->szName[1] == 'f');
				if (isSuffix)
				{
					std::cout << ' ' << ptrAutoMagicRecord->szName;
					std::cout << '[' << std::dec << wAutoMagicAffixCode - 1 << ']';
				}
			}
		}
	}

	doPrintAffixWeights(ptrItemUnit);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
	std::cout << std::endl;
}