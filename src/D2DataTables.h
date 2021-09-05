#pragma once

#pragma pack(1)

/****************************************************************************
*                                                                           *
*   D2DataTables.h                                                          *
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
*   This file is an expansion of D2Structs.h, meant to be used to declare   *
*   structs representing the record of a data table once loaded in memory   *
*   by the game, such as Monstats.txt or Charstats.txt                      *
*                                                                           *
*****************************************************************************/

/****************************************************************************
*                                                                           *
* DECLARATIONS                                                              *
*                                                                           *
*****************************************************************************/
struct D2ItemsTxt;
struct D2ItemTypesTxt;
struct D2AutoMagicTxt;
struct D2UniqueItemsTxt;

/****************************************************************************
*                                                                           *
* DEFINITIONS                                                               *
*                                                                           *
*****************************************************************************/
/*
https://d2mods.info/forum/viewtopic.php?f=8&t=61189
note: from v1.10 - still accurate?
*/
struct D2ItemsTxt
{
	char	szFlippyFile[32];			//0x00 -- verified...
	char	szInvFile[32];				//0x20
	char	szUniqueInvFile[32];		//0x40
	char	szSetInvFile[32];			//0x60
	union
	{
		DWORD32	dwCode;					//0x80
		char	szCode[4];				//0x80
	};
	DWORD32	dwNormCode;					//0x84 -- verified...
	DWORD32	dwUberCode;					//0x88 -- verified...
	DWORD32	dwUltraCode;				//0x8C -- verified...
	DWORD32	dwAlternateGfx;				//0x90
	DWORD32	dwPSpell;					//0x94
	WORD	wState;						//0x98
	WORD	wCState1;					//0x9A
	WORD	wCState2;					//0x9C
	WORD	wStat1;						//0x9E
	WORD	wStat2;						//0xA0
	WORD	wStat3;						//0xA2
	DWORD32	dwCalc1;					//0xA4
	DWORD32	dwCalc2;					//0xA8
	DWORD32	dwCalc3;					//0xAC
	DWORD32	dwLen;						//0xB0
	WORD	wSpellDesc;					//0xB4
	WORD	wSpellDescStr;				//0xB6
	DWORD32	dwSpellDescCalc;			//0xB8
	DWORD32	dwBetterGem;				//0xBC
	DWORD32	dwWClass;					//0xC0 -- verified...
	DWORD32	dw2HandedWClass;			//0xC4
	DWORD32	dwTMogType;					//0xC8
	DWORD32	dwMinAc;					//0xCC
	DWORD32	dwMaxAc;					//0xD0
	DWORD32	dwGambleCost;				//0xD4
	DWORD32	dwSpeed;					//0xD8
	DWORD32	dwBitfield1;				//0xDC
	DWORD32	dwCost;						//0xE0
	DWORD32	dwMinStack;					//0xE4
	DWORD32	dwMaxStack;					//0xE8
	DWORD32	dwSpawnStack;				//0xEC
	DWORD32	dwGemOffset;				//0xF0
	WORD	wNameStr;					//0xF4 (wTableIndex, used for d2lang_10003)
	WORD	wVersion;					//0xF6
	WORD	wAutoPrefix;				//0xF8
	WORD	wMissileType;				//0xFA
	BYTE	bRarity;					//0xFC
	BYTE	bLevel;						//0xFD
	BYTE	bMinDam;					//0xFE
	BYTE	bMaxDam;					//0xFF
	BYTE	bMinMisDam;					//0x100
	BYTE	bMaxMisDam;					//0x101
	BYTE	b2HandMinDam;				//0x102
	BYTE	b2HandMaxDam;				//0x103
	WORD	bRangeAdder;				//0x104
	WORD	wStrBonus;					//0x106
	WORD	wDexBonus;					//0x108
	WORD	wReqStr;					//0x10A
	WORD	wReqDex;					//0x10C
	BYTE	bAbsorbs;					//0x10E
	BYTE	bInvWidth;					//0x10F
	BYTE	bInvHeight;					//0x110
	BYTE	bBlock;						//0x111
	BYTE	bDurability;				//0x112
	BYTE	bNoDurability;				//0x113
	BYTE	bMissile;					//0x114
	BYTE	bComponent;					//0x115
	BYTE	bRArm;						//0x116
	BYTE	bLArm;						//0x117
	BYTE	bTorso;						//0x118
	BYTE	bLegs;						//0x119
	BYTE	bRSPad;						//0x11A
	BYTE	bLSPad;						//0x11B
	BYTE	b2Handed;					//0x11C
	BYTE	bUseable;					//0x11D
	WORD	wType;						//0x11E
	WORD	wType2;						//0x120
	WORD	bSubType;					//0x122
	WORD	wDropSound;					//0x124
	WORD	wUseSound;					//0x126
	BYTE	bDropSfxFrame;				//0x128
	BYTE	bUnique;					//0x129
	BYTE	bQuest;						//0x12A
	BYTE	bQuestDiffCheck;			//0x12B
	BYTE	bTransparent;				//0x12C
	BYTE	bTransTbl;					//0x12D
	BYTE 	pad0x12E;					//0x12E
	BYTE	bLightRadius;				//0x12F
	BYTE	bBelt;						//0x130
	BYTE	bAutoBelt;					//0x131
	BYTE	bStackable;					//0x132
	BYTE	bSpawnable;					//0x133
	BYTE	bSpellIcon;					//0x134
	BYTE	bDurWarning;				//0x135
	BYTE	bQntWarning;				//0x136
	BYTE	bHasInv;					//0x137
	BYTE	bGemSockets;				//0x138
	BYTE	bTransmogrify;				//0x139
	BYTE	bTMogMin;					//0x13A
	BYTE	bTMogMax;					//0x13B
	BYTE	bHitClass;					//0x13C
	BYTE	b1or2Handed;				//0x13D
	BYTE	bGemApplyType;				//0x13E
	BYTE	bLevelReq;					//0x13F
	BYTE	bMagicLvl;					//0x140
	BYTE	bTransform;					//0x141
	BYTE	bInvTrans;					//0x142
	BYTE	bCompactSave;				//0x143
	BYTE	bSkipName;					//0x144
	BYTE	bNameable;					//0x145
	BYTE	bAkaraMin;					//0x146
	BYTE	bGheedMin;					//0x147
	BYTE	bCharsiMin;					//0x148
	BYTE	bFaraMin;					//0x149
	BYTE	bLysanderMin;				//0x14A
	BYTE	bDrognanMin;				//0x14B
	BYTE	bHraltiMin;					//0x14C
	BYTE	bAlkorMin;					//0x14D
	BYTE	bOrmusMin;					//0x14E
	BYTE	bElzixMin;					//0x14F
	BYTE	bAshearaMin;				//0x150
	BYTE	bCainMin;					//0x151
	BYTE	bHalbuMin;					//0x152
	BYTE	bJamellaMin;				//0x153
	BYTE	bMalahMin;					//0x154
	BYTE	bLarzukMin;					//0x155
	BYTE	bDrehyaMin;					//0x156
	BYTE	bAkaraMax;					//0x157
	BYTE	bGheedMax;					//0x158
	BYTE	bCharsiMax;					//0x159
	BYTE	bFaraMax;					//0x15A
	BYTE	bLysanderMax;				//0x15B
	BYTE	bDrognanMax;				//0x15C
	BYTE	bHraltiMax;					//0x15D
	BYTE	bAlkorMax;					//0x15E
	BYTE	bOrmusMax;					//0x15F
	BYTE	bElzixMax;					//0x160
	BYTE	bAshearaMax;				//0x161
	BYTE	bCainMax;					//0x162
	BYTE	bHalbuMax;					//0x163
	BYTE	bJamellaMax;				//0x164
	BYTE	bMalahMax;					//0x165
	BYTE	bLarzukMax;					//0x166
	BYTE	bDrehyaMax;					//0x167
	BYTE	bAkaraMagicMin;				//0x168
	BYTE	bGheedMagicMin;				//0x169
	BYTE	bCharsiMagicMin;			//0x16A
	BYTE	bFaraMagicMin;				//0x16B
	BYTE	bLysanderMagicMin;			//0x16C
	BYTE	bDrognanMagicMin;			//0x16D
	BYTE	bHraltiMagicMin;			//0x16E
	BYTE	bAlkorMagicMin;				//0x16F
	BYTE	bOrmusMagicMin;				//0x170
	BYTE	bElzixMagicMin;				//0x171
	BYTE	bAshearaMagicMin;			//0x172
	BYTE	bCainMagicMin;				//0x173
	BYTE	bHalbuMagicMin;				//0x174
	BYTE	bJamellaMagicMin;			//0x175
	BYTE	bMalahMagicMin;				//0x176
	BYTE	bLarzukMagicMin;			//0x177
	BYTE	bDrehyaMagicMin;			//0x178
	BYTE	bAkaraMagicMax;				//0x179
	BYTE	bGheedMagicMax;				//0x17A
	BYTE	bCharsiMagicMax;			//0x17B
	BYTE	bFaraMagicMax;				//0x17C
	BYTE	bLysanderMagicMax;			//0x17D
	BYTE	bDrognanMagicMax;			//0x17E
	BYTE	bHraltiMagicMax;			//0x17F
	BYTE	bAlkorMagicMax;				//0x180
	BYTE	bOrmusMagicMax;				//0x181
	BYTE	bElzixMagicMax;				//0x182
	BYTE	bAshearaMagicMax;			//0x183
	BYTE	bCainMagicMax;				//0x184
	BYTE	bHalbuMagicMax;				//0x185
	BYTE	bJamellaMagicMax;			//0x186
	BYTE	bMalahMagicMax;				//0x187
	BYTE	bLarzukMagicMax;			//0x188
	BYTE	bDrehyaMagicMax;			//0x189
	BYTE	bAkaraMagicLvl;				//0x18A
	BYTE	bGheedMagicLvl;				//0x18B
	BYTE	bCharsiMagicLvl;			//0x18C
	BYTE	bFaraMagicLvl;				//0x18D
	BYTE	bLysanderMagicLvl;			//0x18E
	BYTE	bDrognanMagicLvl;			//0x18F
	BYTE	bHraltiMagicLvl;			//0x190
	BYTE	bAlkorMagicLvl;				//0x191
	BYTE	bOrmusMagicLvl;				//0x192
	BYTE	bElzixMagicLvl;				//0x193
	BYTE	bAshearaMagicLvl;			//0x194
	BYTE	bCainMagicLvl;				//0x195
	BYTE	bHalbuMagicLvl;				//0x196
	BYTE	bJamellaMagicLvl;			//0x197
	BYTE	bMalahMagicLvl;				//0x198
	BYTE	bLarzukMagicLvl;			//0x199
	BYTE	bDrehyaMagicLvl;			//0x19A
	BYTE	pad0x19B;					//0x19B
	DWORD32	dwNightmareUpgrade;			//0x19C
	DWORD32	dwHellUpgrade;				//0x1A0
	BYTE	bPermStoreItem;				//0x1A4
	BYTE	bMultibuy;					//0x1A5
	WORD	pad0x1A6;					//0x1A6
};

/*
https://d2mods.info/forum/viewtopic.php?f=8&t=61189
note: from v1.10 - still accurate?
*/
struct D2ItemTypesTxt
{
	char szCode[4];						//0x00
	WORD wEquiv1;						//0x04
	WORD wEquiv2;						//0x06
	BYTE nRepair;						//0x08
	BYTE nBody;							//0x09
	BYTE nBodyLoc1;						//0x0A
	BYTE nBodyLoc2;						//0x0B
	WORD wShoots;						//0x0C
	WORD wQuiver;						//0x0E
	BYTE nThrowable;					//0x10
	BYTE nReload;						//0x11
	BYTE nReEquip;						//0x12
	BYTE nAutoStack;					//0x13
	BYTE nMagic;						//0x14
	BYTE nRare;							//0x15
	BYTE nNormal;						//0x16
	BYTE nCharm;						//0x17
	BYTE nGem;							//0x18
	BYTE nBeltable;						//0x19
	BYTE nMaxSock1;						//0x1A
	BYTE nMaxSock25;					//0x1B
	BYTE nMaxSock40;					//0x1C
	BYTE nTreasureClass;				//0x1D
	BYTE nRarity;						//0x1E
	BYTE nStaffMods;					//0x1F
	BYTE nCostFormula;					//0x20
	BYTE nClass;						//0x21
	BYTE nStorePage;					//0x22
	BYTE nVarInvGfx;					//0x23
	char szInvGfx1[32];					//0x24
	char szInvGfx2[32];					//0x44
	char szInvGfx3[32];					//0x64
	char szInvGfx4[32];					//0x84
	char szInvGfx5[32];					//0xA4
	char szInvGfx6[32];					//0xC4
};

/*
https://d2mods.info/forum/viewtopic.php?f=8&t=61189
note: from v1.10 - still accurate?
returned by D2Common.#10248
size: 0x90 bytes
*/
struct D2AutoMagicTxt
{
	char szName[32];					//0x00
	WORD wTblIndex;						//0x20
	WORD wVersion;						//0x22
	DWORD32 dwMod1Code;					//0x24 (note: missing mod codes tend to equal 2^32-1)
	DWORD32 dwMod1Param;					//0x28
	DWORD32 dwMod1Min;					//0x2C
	DWORD32 dwMod1Max;					//0x30
	DWORD32 dwMod2Code;					//0x34
	DWORD32 dwMod2Param;					//0x38
	DWORD32 dwMod2Min;					//0x3C
	DWORD32 dwMod2Max;					//0x40
	DWORD32 dwMod3Code;					//0x44
	DWORD32 dwMod3Param;					//0x48
	DWORD32 dwMod3Min;					//0x4C
	DWORD32 dwMod3Max;					//0x50
	WORD wSpawnable;					//0x54
	WORD wTransformColor;				//0x56
	DWORD32 dwLevel;						//0x58
	DWORD32 dwGroup;						//0x5C
	DWORD32 dwMaxLevel;					//0x60
	BYTE nRare;							//0x64
	BYTE nLevelReq;						//0x65
	BYTE nClassSpecific;				//0x66
	BYTE nClass;						//0x67
	WORD wClassLevelReq;				//0x68
	WORD wIType1;						//0x6A
	WORD wIType2;						//0x6C
	WORD wIType3;						//0x6E
	WORD wIType4;						//0x70
	WORD wIType5;						//0x72
	WORD wIType6;						//0x74
	WORD wIType7;						//0x76
	WORD wEType1;						//0x78
	WORD wEType2;						//0x7A
	WORD wEType3;						//0x7C
	WORD wEType4;						//0x7E
	WORD wEType5;						//0x80
	WORD wFrequency;					//0x82
	DWORD32 dwDivide;						//0x84
	DWORD32 dwMultiply;					//0x88
	DWORD32 dwAdd;						//0x8C
};

//https://d2mods.info/forum/viewtopic.php?f=8&t=61189
//note: from v1.10 - still accurate?
struct D2UniqueItemsTxt
{
	WORD wUniqueID;						//0x00
	char szName[32];					//0x02
	WORD wTblID;						//...
	union
	{
		DWORD32 dwBaseItemCode;			//0x28
		char szBaseItemCode[4];			//0x28
	};
	DWORD32 dwUniqueItemFlags;			//0x2C
	DWORD32 dwRarity;						//0x30
	WORD wLvl;							//0x34
	WORD wLvlReq;						//0x36
	BYTE nChrTransform;					//0x38
	BYTE nInvTransform;					//0x39
	char szFlippyFile[32];				//0x3A
	char szInvFile[34];					//0x5A
	DWORD32 dwCostMult;					//0x7C
	DWORD32 dwCostAdd;					//0x80
	WORD wDropSound;					//0x84
	WORD wUseSound;						//0x86
	DWORD32 dwDropSfxFrame;				//0x88	
	DWORD32 dwProp1;						//0x8C
	DWORD32 dwPar1;						//0x90
	DWORD32 dwMin1;						//0x94
	DWORD32 dwMax1;						//0x98
	DWORD32 dwProp2;						//0x9C
	DWORD32 dwPar2;						//0xA0
	DWORD32 dwMin2;						//0xA4
	DWORD32 dwMax2;						//0xA8
	DWORD32 dwProp3;						//0xAC
	DWORD32 dwPar3;						//0xB0
	DWORD32 dwMin3;						//0xB4
	DWORD32 dwMax3;						//0xB8
	DWORD32 dwProp4;						//0xBC
	DWORD32 dwPar4;						//0xC0
	DWORD32 dwMin4;						//0xC4
	DWORD32 dwMax4;						//0xC8
	DWORD32 dwProp5;						//0xCC
	DWORD32 dwPar5;						//0xD0
	DWORD32 dwMin5;						//0xD4
	DWORD32 dwMax5;						//0xD8
	DWORD32 dwProp6;						//0xDC
	DWORD32 dwPar6;						//0xE0
	DWORD32 dwMin6;						//0xE4
	DWORD32 dwMax6;						//0xE8
	DWORD32 dwProp7;						//0xEC
	DWORD32 dwPar7;						//0xF0
	DWORD32 dwMin7;						//0xF4
	DWORD32 dwMax7;						//0xF8
	DWORD32 dwProp8;						//0xFC
	DWORD32 dwPar8;						//0x100
	DWORD32 dwMin8;						//0x104
	DWORD32 dwMax8;						//0x10
	DWORD32 dwProp9;						//0x10C
	DWORD32 dwPar9;						//0x110
	DWORD32 dwMin9;						//0x114
	DWORD32 dwMax9;						//0x118
	DWORD32 dwProp10;						//0x11C
	DWORD32 dwPar10;						//0x120
	DWORD32 dwMin10;						//0x124
	DWORD32 dwMax10;						//0x128
	DWORD32 dwProp11;						//0x12C
	DWORD32 dwPar11;						//0x130
	DWORD32 dwMin11;						//0x134
	DWORD32 dwMax11;						//0x138
	DWORD32 dwProp12;						//0x13C
	DWORD32 dwPar12;						//0x140
	DWORD32 dwMin12;						//0x144
	DWORD32 dwMax12;						//0x148
};

// end of file --------------------------------------------------------------
#pragma pack()