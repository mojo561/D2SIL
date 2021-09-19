#pragma once
#pragma pack(push, 1)
enum D2CubeItemFlag  
{  
	CUBE_COWPORTAL		=1,
	CUBE_USEITEM		=0xFF,
	CUBE_USETYPE		=0xFE,
	CUBE_TYPE			=0xFD,
	CUBE_ITEM			=0xFC
};

struct CubeOutput//size: 0x54=84 (source total : fct of dll)
{
	union {
		WORD flag;				//+00
		struct {
			WORD	keepModifiers:1;			//",mod"
			WORD	haveSockets:1;				//",sock=#nbsocket"
			WORD	isEthereal:1;				//",eth"
			WORD	isSpecificItem:1;			//"#itemUniqueName" or "#itemSetName" (set byItemID too)
			WORD	destroysFillers :1;			//",uns"
			WORD	removeFillers:1;			//",rem"
			WORD	regeneratesUnique:1;		//",reg"
			WORD	upgradeToExceptional:1;		//",exc"
			WORD	upgradeToElite:1;			//",eli"
			WORD	repair:1;					//",rep"
			WORD	recharge:1;					//",rch"
		};
	};
	WORD	ID;					//+02
	WORD	specificID;			//+04
	BYTE	quality;			//+06	1=",low"; 2=",nor"; 3=",hiq"; 4=",mag"; 5=",set"; 6=",rar"; 7=",uni"; 8=",crf"; 9=",tmp"
	BYTE	quantityOrNbSockets;//+07	",qty=#quantity" Or ",sock=#nbsocket"
	BYTE	outputType;			//+08	02="Pand. Portal" 01="Cow Portal" FF="usetype"; FE="useitem" FC="#item4Code" FD="#type4Code"
	BYTE	lvl;				//+09	//+55
	BYTE	plvl;				//+0A	//+56
	BYTE	ilvl;				//+0B	//+57
	WORD	Prefix;				//+0C
	WORD	PrefixMin;			//+0E (always 0)
	WORD	PrefixMax;			//+10 (always 0)
	WORD	Suffix;				//+12
	WORD	SuffixMin;			//+14 (always 0)
	WORD	SuffixMax;			//+16 (always 0)
	DWORD32	mod1;				//+18	//+64(13)
	WORD	mod1param;			//+1C	//+68
	WORD	mod1min;			//+1E	//+6A
	WORD	mod1max;			//+20	//+6C
	BYTE	mod1chance;			//+22	//+6E
	DWORD32	mod2;				//+24	//+70
	WORD	mod2param;			//+28	//+74
	WORD	mod2min;			//+2A	//+76
	WORD	mod2max;			//+2C	//+78
	BYTE	mod2chance;			//+2E	//+7A
	DWORD32	mod3;				//+30	//+7C
	WORD	mod3param;			//+34	//+80
	WORD	mod3min;			//+36	//+82
	WORD	mod3max;			//+38	//+84
	BYTE	mod3chance;			//+3A	//+86
	DWORD32	mod4;				//+3C	//+88
	WORD	mod41param;			//+40	//+8C
	WORD	mod4min;			//+42	//+8E
	WORD	mod4max;			//+44	//+90
	BYTE	mod4chance;			//+46	//+92
	DWORD32	mod5;				//+48	//+94
	WORD	mod5param;			//+4C	//+98
	WORD	mod5min;			//+4E	//+9A
	WORD	mod5max;			//+50	//+9C
	BYTE	mod5chance;			//+52	//+9E
};


struct CubeInput//size: 8 (source total : fct of dll)
{
	union {
		WORD flag;			//+00
		struct {
			WORD	byItemID:1;					//"#item4Code" or "any"
			WORD	byItemTypeID:1;				//"#itemType4Code"
			WORD	haveNoSocket:1;				//",nos"
			WORD	haveSockets:1;				//",sock"
			WORD	isEthereal:1;				//",eth"
			WORD	isNotEthereal:1;			//",noe"
			WORD	isSpecificItem:1;			//"#itemUniqueName" or "#itemSetName" (set byItemID too)
			WORD	includeUpgradedVersions:1;	//",upg"
			WORD	isBasic:1;					//",bas"
			WORD	isExceptional:1;			//",exc"
			WORD	isElite:1;					//",eli"
			WORD	isNotRuneword:1;			//",nru"
		};
	};
	WORD	ID;				//+02	FFFF = any items
	WORD	specificID;		//+04
	BYTE	quality;		//+06	1=",low"; 2=",nor"; 3=",hiq"; 4=",mag"; 5=",set"; 6=",rar"; 7=",uni"; 8=",crf"; 9=",tmp"
	BYTE	quantity;		//+07	",qty=#quantity"
};


struct CubeMainBIN//size: 0x148=328  (source total : fct of dll) (total size in LoD1.10 : BDA0)
{
	BYTE		enabled;	//+00
	BYTE		ladder;		//+01
	BYTE		minDiff;	//+02
	BYTE		playerClass;//+03 FF=all classes
	BYTE		op;			//+04
	DWORD32		param;		//+08
	DWORD32		value;		//+0C
	BYTE		numinputs;	//+10
	WORD		version;	//+12
	CubeInput	input1;		//+14
	CubeInput	input2;		//+1C
	CubeInput	input3;		//+24
	CubeInput	input4;		//+2C
	CubeInput	input5;		//+34
	CubeInput	input6;		//+3C
	CubeInput	input7;		//+44
	CubeOutput	output1;	//+4C
	CubeOutput	output2;	//+A0
	CubeOutput	output3;	//+F4
};

struct TreasureClassBIN
{

};

struct ObjectsBIN
{

};

struct LevelsBIN//size=0x220
{

};

struct GemsBIN //size: 0xC0=192 (source : fct of dll)
{
	char	name[0x20];		//+00
	char	letter[6];		//+20
	BYTE	uk1[2];			//+26
	DWORD32	code;			//+28
	BYTE	uk2[2];			//+2C
	BYTE	nummods;		//+2E
	BYTE	transform;		//+2F
	int		weaponmod1code;	//+30
	DWORD32	weaponmod1param;//+34
	DWORD32	weaponmod1min;	//+38
	DWORD32	weaponmod1max;	//+3C
	int		weaponmod2code;	//+40
	DWORD32	weaponmod2param;//+44
	DWORD32	weaponmod2min;	//+48
	DWORD32	weaponmod2max;	//+4C
	int		weaponmod3code;	//+50
	DWORD32	weaponmod3param;//+54
	DWORD32	weaponmod3min;	//+58
	DWORD32	weaponmod3max;	//+5C
	int		helmmod1code;	//+60
	DWORD32	helmmod1param;	//+64
	DWORD32	helmmod1min;	//+68
	DWORD32	helmmod1max;	//+6C
	int		helmmod2code;	//+70
	DWORD32	helmmod2param;	//+74
	DWORD32	helmmod2min;	//+78
	DWORD32	helmmod2max;	//+7C
	int		helmmod3code;	//+80
	DWORD32	helmmod3param;	//+84
	DWORD32	helmmod3min;	//+88
	DWORD32	helmmod3max;	//+8C
	int		shieldmod1code;	//+90
	DWORD32	shieldmod1param;//+94
	DWORD32	shieldmod1min;	//+98
	DWORD32	shieldmod1max;	//+9C
	int		shieldmod2code;	//+A0
	DWORD32	shieldmod2param;//+A4
	DWORD32	shieldmod2min;	//+A8
	DWORD32	shieldmod2max;	//+AC
	int		shieldmod3code;	//+B0
	DWORD32	shieldmod3param;//+B4
	DWORD32	shieldmod3min;	//+B8
	DWORD32	shieldmod3max;	//+BC
};

struct ItemsBIN //size: 0x1A8=424 (source : fct of dll) (nblines : 134 CA 8B) Gold:20B
{  
	char	FlippyFile[0x20];		//+00  
	char	InvFile[0x20];			//+20  
	char	UniqueInvFile[0x20];	//+40  
	char	SetInvFile[0x20];		//+60  
	DWORD32	ItemCode;				//+80  
	DWORD32	NormCode;				//+84  
	DWORD32	UberCode;				//+88  
	DWORD32	HellCode;				//+8C  
	DWORD32	AlternateGfx;			//+90  
	DWORD32	pSpell;					//+94  
	WORD	State;					//+98  
	WORD	cState1;				//+9A  
	WORD	cState2;				//+9C  
	WORD	Stat1;					//+9E  
	WORD	Stat2;					//+A0  
	WORD	Stat3;					//+A2  
	DWORD32	Calc1;					//+A4  
	DWORD32	Calc2;					//+A8  
	DWORD32	Calc3;					//+AC  
	DWORD32	Len;					//+B0  
	WORD	SpellDesc;				//+B4  
	WORD	SpellDescStr;			//+B6  
	DWORD32	SpellDescCalc;			//+B8  
	DWORD32	BetterGem;				//+BC  
	DWORD32	WClass;					//+C0  
	DWORD32	TwoHandedWClass;		//+C4  
	DWORD32	TMogType;				//+C8  
	DWORD32	MinAC;					//+CC  
	DWORD32	MaxAC;					//+D0  
	DWORD32	GambleCost;				//+D4  
	DWORD32	Speed;					//+D8  
	DWORD32	BitField;				//+DC  
	DWORD32	Cost;					//+E0  
	DWORD32	MinStack;				//+E4  
	DWORD32	MaxStack;				//+E8  
	DWORD32	SpawnStack;				//+EC  
	DWORD32	GemOffset;				//+F0  
	WORD	NameStr;				//+F4  
	WORD	Version;				//+F6  
	WORD	AutoPrefix;				//+F8  
	WORD	MissileType;			//+FA  
	BYTE	Rarity;					//+FC  
	BYTE	Level;					//+FD  
	BYTE	MinDam;					//+FE  
	BYTE	MaxDam;					//+FF  
	BYTE	MinMisDam;				//+100  
	BYTE	MaxMisDam;				//+101  
	BYTE	TwoHandMinDam;			//+102  
	BYTE	TwoHandMaxDam;			//+103  
	BYTE	RangeAdder;				//+104  
	BYTE	NotUsed1;				//+105  
	WORD	StrBonus;				//+106  
	WORD	DexBonus;				//+108  
	WORD	RegStr;					//+10A  
	WORD	RegDex;					//+10C  
	BYTE	Absorbs;				//+10E  
	BYTE	InvWidth;				//+10F  
	BYTE	InvHeight;				//+110  
	BYTE	Block;					//+111  
	BYTE	Durability;				//+112  
	BYTE	NoDurability;			//+113
	BYTE	Missile;				//+114  
	BYTE	Component;				//+115  
	BYTE	RArm;					//+116  
	BYTE	LArm;					//+117  
	BYTE	Torso;					//+118  
	BYTE	Legs;					//+119  
	BYTE	RSpad;					//+11A  
	BYTE	LSpad;					//+11B  
	BYTE	TwoHanded;				//+11C  
	BYTE	Usable;					//+11D  
	WORD	Type;					//+11E  
	WORD	Type2;					//+120  
	BYTE	SubType;				//+122  
	BYTE	NotUsed2;				//+123  
	WORD	DropSound;				//+124
	WORD	UseSound;				//+126
	BYTE	DropSfxFrame;			//+128
	BYTE	Unique;					//+129
	BYTE	Quest;					//+12A
	BYTE	QuestDiffCheck;			//+12B  
	BYTE	Transparent;			//+12C  
	BYTE	TransTbl;				//+12D  
	BYTE	NotUsed3;				//+12E  
	BYTE	LightRadius;			//+12F  
	BYTE	Belt;					//+130  
	BYTE	AutoBelt;				//+131  
	BYTE	Stackable;				//+132  
	BYTE	Spawnable;				//+133  
	BYTE	SpellIcon;				//+134  
	BYTE	DurWarning;				//+135  
	BYTE	QntWaning;				//+136  
	BYTE	HasInv;					//+137  
	BYTE	GemSockets;				//+138  
	BYTE	TransmoGrify;			//+139  
	BYTE	TMogMin;				//+13A  
	BYTE	TMogMax;				//+13B  
	BYTE	HitClass;				//+13C  
	BYTE	OneOrTwoHanded;			//+13D  
	BYTE	GemApplyType;			//+13E  
	BYTE	LevelReq;				//+13F  
	BYTE	MagicLvl;				//+140  
	BYTE	Transform;				//+141  
	BYTE	InvTrans;				//+142  
	BYTE	CompactSave;			//+143  
	BYTE	SkipName;				//+144  
	BYTE	NotUsed4;				//+145  
	BYTE	VendorMin[17];			//+146  
	BYTE	VendorMax[17];			//+157  
	BYTE	VendorMagicMin[17];		//+168  
	BYTE	VendorMagicMax[17];		//+179  
	BYTE	VendorMagicLvl[17];		//+18A  
	BYTE	NotUsed5;				//+19B  
	DWORD32	NightmareUpgrade;		//+19C  
	DWORD32	HellUpgrade;			//+1A0  
	BYTE	PermStoreItem;			//+1A4  
	BYTE	Multibuy;				//+1A5  
	WORD	zeros;					//+1A6
};

struct RunesBIN	//size: 0x120=288 (1.10 ok)
{  
	char	Name[0x40];		//+00
	char	RuneName[0x40];	//+40
	BYTE	Complete;		//+80
	BYTE	Server;			//+81
	WORD	RuneNameID;		//+82
	WORD	zero;			//+84 (=0x0000)
	WORD	Itypes[6];		//+86
	WORD	Etypes[3];		//+92
	int		Runes[6];		//+98
	DWORD32	t1code1;		//+B0
	DWORD32	t1param1;		//+B4
	DWORD32	t1min1;			//+B8
	DWORD32	t1max1;			//+BC
	DWORD32	t1code2;		//+C0
	DWORD32	t1param2;		//+C4
	DWORD32	t1min2;			//+C8
	DWORD32	t1max2;			//+CC
	DWORD32	t1code3;		//+D0
	DWORD32	t1param3;		//+D4
	DWORD32	t1min3;			//+D8
	DWORD32	t1max3;			//+DC
	DWORD32	t1code4;		//+E0
	DWORD32	t1param4;		//+E4
	DWORD32	t1min4;			//+E8
	DWORD32	t1max4;			//+EC
	DWORD32	t1code5;		//+F0
	DWORD32	t1param5;		//+F4
	DWORD32	t1min5;			//+F8
	DWORD32	t1max5;			//+FC
	DWORD32	t1code6;		//+100
	DWORD32	t1param6;		//+104
	DWORD32	t1min6;			//+108
	DWORD32	t1max6;			//+10C
	DWORD32	t1code7;		//+110
	DWORD32	t1param7;		//+114
	DWORD32	t1min7;			//+118
	DWORD32	t1max7;			//+11C
};

/*struct ItemStatsBIN	//size: 0x234=564
{
	BYTE	uk1[0x80];			//+00
	DWORD32	code;				//+80 		// ou 0x90
	BYTE	uk2[0xB3];			//+84
	BYTE	itemStat137;		//+137
};*/


struct CharStatsBIN //size= 0xC4=196
{
	WCHAR	nameU[0x10];
	char	name[0x10];
	BYTE	baseSTR;	//+20
	BYTE	baseDEX;
	BYTE	baseENE;
	BYTE	baseVIT;
	BYTE	baseStamina;
	BYTE	HPAdd;
	BYTE	percentStr;
	BYTE	percentDex;
	BYTE	percentInt;
	BYTE	percentVit;      
	WORD	manaRegen;
	DWORD32	toHitFactor;
	BYTE	walkVelocity;//+30
	BYTE	runVelocity;
	BYTE	runDrain;
	BYTE	lifePerLevel;
	BYTE	staminaPerLevel;
	BYTE	manaPerLevel;
	BYTE	lifePerVitality;
	BYTE	staminaPerVitality;
	BYTE	manaPerMagic;
    BYTE	blockFactor;
	WORD	startSkill;
	DWORD32	baseWClass;
	DWORD32	unknown1[3];
	DWORD32	item1;
	BYTE	item1Loc;
	BYTE	item1Count;
	WORD	item1Unknown;
	DWORD32	item2;
	BYTE	item2Loc;
	BYTE	item2Count;
	WORD	item2Unknown;
	DWORD32	item3;
	BYTE	item3Loc;
	BYTE	item3Count;
	WORD	item3Unknown;
	DWORD32	item4;
	BYTE	item4Loc;
	BYTE	item4Count;
	WORD	item4Unknown;
	DWORD32	item5;
	BYTE	item5Loc;
	BYTE	item5Count;
	WORD	item5Unknown;
    DWORD32	item6;
	BYTE	item6Loc;
	BYTE	item6Count;
	WORD	item6Unknown;
	DWORD32	item7;
	BYTE	item7Loc;
	BYTE	item7Count;
	WORD	item7Unknown;
	DWORD32	item8;
	BYTE	item8Loc;
	BYTE	item8Count;
	WORD	item8Unknown;
	DWORD32	item9;
	BYTE	item9Loc;
	BYTE	item9Count;
	WORD	item9Unknown;
	DWORD32	item10;
	BYTE	item10Loc;
	BYTE	item10Count;
	WORD	item10Unknown;
	BYTE	unknown2[0x18]; 
};
/*
struct D2CharStats  
{  
     wchar_t     Class_t[0x10];               //+00  
     char     Class[0x10];               //+20  
     BYTE     Str;                         //+30  
     BYTE     Dex;                         //+31  
     BYTE     Int;                         //+32  
     BYTE     Vit;                         //+33  
     BYTE     Stamina;                    //+34  
     BYTE     HpAdd;                         //+35  
     BYTE     PercentStr;                    //+36  
     BYTE     PercentInt;                    //+37  
     BYTE     PercentDex;                    //+38  
     BYTE     PercentVit;                    //+39  
     BYTE     ManaRegen;                    //+3A  
     BYTE     NotUsed1;                    //+3B  
     DWORD32     ToHitFactor;               //+3C  
     BYTE     WalkVelocity;               //+40  
     BYTE     RunVelocity;               //+41  
     BYTE     RunDrain;                    //+42  
     BYTE     LifePerLevel;               //+43  
     BYTE     StamianPerLevel;          //+44  
     BYTE     ManaPerLevel;               //+45  
     BYTE     LifePerVitality;          //+46  
     BYTE     StaminaPerVitality;          //+47  
     BYTE     ManaPerMagic;               //+48  
     BYTE     BlockFactor;               //+49  
     BYTE     NotUsed2[2];               //+4A  
     DWORD32     BaseWClass;                    //+4C  
     BYTE     StatPerLevel;               //+50  
     BYTE     NotUsed3;                    //+51  
     WORD     StrAllSkills;               //+52  
     WORD     StrSkillTab1;               //+54  
     WORD     StrSkillTab2;               //+56  
     WORD     StrSkillTab3;               //+58  
     WORD     StrClassOnly;               //+5A  
     DWORD32     Item1;                         //+5C  
     BYTE     Item1Loc;                    //+60  
     BYTE     Item1Count;                    //+61  
     BYTE     NotUsed4[2];               //+62  
     DWORD32     Item2;                         //+64  
     BYTE     Item2Loc;                    //+68  
     BYTE     Item2Count;                    //+69  
     BYTE     NotUsed5[2];               //+6A  
     DWORD32     Item3;                         //+6C  
     BYTE     Item3Loc;                    //+70  
     BYTE     Item3Count;                    //+71  
     BYTE     NotUsed6[2];               //+72  
     DWORD32     Item4;                         //+74  
     BYTE     Item4Loc;                    //+78  
     BYTE     Item4Count;                    //+79  
     BYTE     NotUsed7[2];               //+7A  
     DWORD32     Item5;                         //+7C  
     BYTE     Item5Loc;                    //+80  
     BYTE     Item5Count;                    //+81  
     BYTE     NotUsed8[2];               //+82  
     DWORD32     Item6;                         //+84  
     BYTE     Item6Loc;                    //+88  
     BYTE     Item6Count;                    //+89  
     BYTE     NotUsed9[2];               //+8A  
     DWORD32     Item7;                         //+8C  
     BYTE     Item7Loc;                    //+90  
     BYTE     Item7Count;                    //+91  
     BYTE     NotUsed10[2];               //+92  
     DWORD32     Item8;                         //+94  
     BYTE     Item8Loc;                    //+98  
     BYTE     Item8Count;                    //+99  
     BYTE     NotUsed11[2];               //+9A  
     DWORD32     Item9;                         //+9C  
     BYTE     Item9Loc;                    //+A0  
     BYTE     Item9Count;                    //+A1  
     BYTE     NotUsed12[2];               //+A2  
     DWORD32     Item10;                         //+A4  
     BYTE     Item10Loc;                    //+A8  
     BYTE     Item10Count;               //+A9  
     BYTE     NotUsed13[2];               //+AA  
     WORD     StartSkill;                    //+AC  
     WORD     Skill1;                         //+AE  
     WORD     Skill2;                         //+B0  
     WORD     Skill3;                         //+B2  
     WORD     Skill4;                         //+B4  
     WORD     Skill5;                         //+B6  
     WORD     Skill6;                         //+B8  
     WORD     Skill7;                         //+BA  
     WORD     Skill8;                         //+BC  
     WORD     Skill9;                         //+BE  
     WORD     Skill10;                    //+C0  
     BYTE     NotUSed14[2];               //+C2  
};

*/

struct UniqueItemsBIN //size=0x14C (332)
{
	WORD	uniqueId;				//+00
	char	szItemTitle[0x20];		//+02
	WORD	uniqueNameId;			//+22
	BYTE	uk2[0x08];				//+24
	union {
		BYTE	flag;		//+2C
		struct {
			BYTE ukf:2;
			BYTE carry1:1;
		};
	};
	BYTE	uk3[0x11F];		//+2D
};


/*struct SetItemsBIN //size=0x1B8 (source : fct of dll)
{
	WORD	setId;			//+00
	char	index[0x20];	//+02
	BYTE	uk1;			//+04
	WORD	setNameId;		//+24
	BYTE	uk2[0x192];		//+26
};*/
//credit: https://d2mods.info/forum/viewtopic.php?f=8&t=61189
struct SetItemsBIN
{
	WORD wSetItemId;					//0x00
	char szName[32];					//0x02
	WORD pad0x22;						//0x22
	DWORD32 dwTblIndex;					//0x24
	char szItemCode[4];					//0x28
	DWORD32 pad0x2C;						//0x2C
	WORD wLvl;							//0x30
	WORD wLvlReq;						//0x32
	DWORD32 dwRarity;						//0x34
	DWORD32 dwCostMult;					//0x38
	DWORD32 dwCostAdd;					//0x3C
	BYTE nChrTransform;					//0x40
	BYTE nInvTransform;					//0x41
	char szFlippyFile[32];				//0x42
	char szInvFile[32];					//0x62
	WORD wDropSound;					//0x82
	WORD wUseSound;						//0x84
	BYTE nDropSfxFrame;					//0x86
	BYTE nAddFunc;						//0x87
	DWORD32 dwProp1;						//0x88
	DWORD32 dwPar1;						//0x8C
	DWORD32 dwMin1;						//0x90
	DWORD32 dwMax1;						//0x94
	DWORD32 dwProp2;						//0x98
	DWORD32 dwPar2;						//0x9C
	DWORD32 dwMin2;						//0xA0
	DWORD32 dwMax2;						//0xA4
	DWORD32 dwProp3;						//0xA8
	DWORD32 dwPar3;						//0xAC
	DWORD32 dwMin3;						//0xB0
	DWORD32 dwMax3;						//0xB4
	DWORD32 dwProp4;						//0xB8
	DWORD32 dwPar4;						//0xBC
	DWORD32 dwMin4;						//0xC0
	DWORD32 dwMax4;						//0xC4
	DWORD32 dwProp5;						//0xC8
	DWORD32 dwPar5;						//0xCC
	DWORD32 dwMin5;						//0xD0
	DWORD32 dwMax5;						//0xD4
	DWORD32 dwProp6;						//0xD8
	DWORD32 dwPar6;						//0xDC
	DWORD32 dwMin6;						//0xE0
	DWORD32 dwMax6;						//0xE4
	DWORD32 dwProp7;						//0xE8
	DWORD32 dwPar7;						//0xEC
	DWORD32 dwMin7;						//0xF0
	DWORD32 dwMax7;						//0xF4
	DWORD32 dwProp8;						//0xF8
	DWORD32 dwPar8;						//0xFC
	DWORD32 dwMin8;						//0x100
	DWORD32 dwMax8;						//0x104
	DWORD32 dwProp9;						//0x108
	DWORD32 dwPar9;						//0x10C
	DWORD32 dwMin9;						//0x110
	DWORD32 dwMax9;						//0x114
	DWORD32 dwAProp1a;					//0x118
	DWORD32 dwAPar1a;						//0x11C
	DWORD32 dwAMin1a;						//0x120
	DWORD32 dwAMax1a;						//0x124
	DWORD32 dwAProp1b;					//0x128
	DWORD32 dwAPar1b;						//0x12C
	DWORD32 dwAMin1b;						//0x130
	DWORD32 dwAMax1b;						//0x134
	DWORD32 dwAProp2a;					//0x138
	DWORD32 dwAPar2a;						//0x13C
	DWORD32 dwAMin2a;						//0x140
	DWORD32 dwAMax2a;						//0x144
	DWORD32 dwAProp2b;					//0x148
	DWORD32 dwAPar2b;						//0x14C
	DWORD32 dwAMin2b;						//0x150
	DWORD32 dwAMax2b;						//0x154
	DWORD32 dwAProp3a;					//0x158
	DWORD32 dwAPar3a;						//0x15C
	DWORD32 dwAMin3a;						//0x160
	DWORD32 dwAMax3a;						//0x164
	DWORD32 dwAProp3b;					//0x168
	DWORD32 dwAPar3b;						//0x16C
	DWORD32 dwAMin3b;						//0x170
	DWORD32 dwAMax3b;						//0x174
	DWORD32 dwAProp4a;					//0x178
	DWORD32 dwAPar4a;						//0x17C
	DWORD32 dwAMin4a;						//0x180
	DWORD32 dwAMax4a;						//0x184
	DWORD32 dwAProp4b;					//0x188
	DWORD32 dwAPar4b;						//0x18C
	DWORD32 dwAMin4b;						//0x190
	DWORD32 dwAMax4b;						//0x194
	DWORD32 dwAProp5a;					//0x198
	DWORD32 dwAPar5a;						//0x19C
	DWORD32 dwAMin5a;						//0x1A0
	DWORD32 dwAMax5a;						//0x1A4
	DWORD32 dwAProp5b;					//0x1A8
	DWORD32 dwAPar5b;						//0x1AC
	DWORD32 dwAMin5b;						//0x1B0
	DWORD32 dwAMax5b;						//0x1B4
};


struct SkillDescBIN //size=0x120=288  (source : fct of dll)
{
	BYTE	uk1[0x08];		//+00
	WORD	strNameID;		//+08
	WORD	strShortID;		//+0A
	WORD	strLongID;		//+0C
	WORD	strAltID;		//+0E
	BYTE	uk2[0x110];		//+10
};


struct SkillsBIN //size=0x23C (572)
{
	WORD	skillID;		//+00
	BYTE	uk1[0x0A];		//+02
	BYTE	charclass;		//+0C
	BYTE	uk2[0x08];		//+10
	WORD	itypea1;		//+18
	WORD	itypea2;		//+1A
	WORD	itypea3;		//+1C
	WORD	itypeb1;		//+1E
	WORD	itypeb2;		//+20
	WORD	itypeb3;		//+22
	WORD	etypea1;		//+24
	WORD	etypea2;		//+26
	WORD	etypeb1;		//+28
	WORD	etypeb2;		//+2A
	BYTE	uk3[0x100];		//+2C
	WORD	maxlvl;			//+12C
	BYTE	uk4[0x42];		//+12E
	int		skpoints;		//+170
	WORD	reqlevel;		//+174
	BYTE	uk5[0x1E];		//+176
	DWORD32	skilldesc;		//+194 (DWORD32 ?)
	BYTE	uk6[0xA4];		//+198
};

struct DifficultyLevelsBIN
{
	DWORD32	resistPenalty;	//+00
	BYTE	uk1[1];			//+04
};

struct SuperUniqueBIN
{
};

struct MonStatsBIN	//size=0x1A8 (424)
{
	BYTE	uk1[0x6];		//+00
	WORD	monsterNameID;	//+06
	BYTE	uk2[0x1A0];		//+08
};							//+1A8

struct ItemTypesBIN //size=0xE4 (228) (source : fct of dll)
{
	DWORD32	code;			//+00
	BYTE	uk1[0x11];		//+04
	BYTE	rare;			//+15
	BYTE	uk2[0x09];		//+16
	BYTE	staffmods;		//+1F
	BYTE	uk3[0xC4];		//+20
};							//+E4

struct AffixBIN //size=0x90 (144) (source : fct of dll) magicsuffix + magicprefix + automagic
{
	char	name[0x20];		//+00
	WORD	nameCode;		//+20
	WORD	version;		//+22
	DWORD32	mod1code;		//+24
	DWORD32	mod1param;		//+28
	DWORD32	mod1min;		//+2C
	DWORD32	mod1max;		//+30
	DWORD32	mod2code;		//+34
	DWORD32	mod2param;		//+38
	DWORD32	mod2min;		//+3C
	DWORD32	mod2max;		//+40
	DWORD32	mod3code;		//+44
	DWORD32	mod3param;		//+48
	DWORD32	mod3min;		//+4C
	DWORD32	mod3max;		//+50
	BYTE	spawnable;		//+54
	BYTE	uk1[0x1];		//+55
	WORD	transformcolor;	//+56
	DWORD32	level;			//+58
	DWORD32	group;			//+5C
	DWORD32	maxlevel;		//+60
	BYTE	rare;			//+64
	BYTE	levelreq;		//+65
	BYTE	classspecific;	//+66
	BYTE	classf;			//+67
	BYTE	classlevelreq;	//+68
	BYTE	uk2[0x1];		//+69
	WORD	itype1;			//+6A
	WORD	itype2;			//+6C
	WORD	itype3;			//+6E
	WORD	itype4;			//+70
	WORD	itype5;			//+72
	WORD	itype6;			//+74
	WORD	itype7;			//+76
	WORD	etype1;			//+78
	WORD	etype2;			//+7A
	WORD	etype3;			//+7C
	WORD	etype4;			//+7E
	WORD	etype5;			//+80
	BYTE	frequency;		//+82
	BYTE	uk3[0x1];		//+83
	DWORD32	divide;			//+84
	DWORD32	multiply;		//+88
	DWORD32	add;			//+8C
};

struct PropertiesBIN // size=0x2E (46) (source total : fct of dll)
{
	WORD	modcode;		//+00
	BYTE	set1;			//+02
	BYTE	set2;			//+03
	BYTE	set3;			//+04
	BYTE	set4;			//+05
	BYTE	set5;			//+06
	BYTE	set6;			//+07
	BYTE	set7;			//+08
	BYTE	uk1[0x1];		//+09

	WORD	val1;			//+0A
	WORD	val2;			//+0C
	WORD	val3;			//+0E
	WORD	val4;			//+10
	WORD	val5;			//+12
	WORD	val6;			//+14
	WORD	val7;			//+16

	BYTE	func1;			//+18
	BYTE	func2;			//+19
	BYTE	func3;			//+1A
	BYTE	func4;			//+1B
	BYTE	func5;			//+1C
	BYTE	func6;			//+1D
	BYTE	func7;			//+1E
	BYTE	uk2[0x1];		//+1F

	//D2C_Stat	stat1;			//+20
	//D2C_Stat	stat2;			//+22
	//D2C_Stat	stat3;			//+24
	//D2C_Stat	stat4;			//+26
	//D2C_Stat	stat5;			//+28
	//D2C_Stat	stat6;			//+2A
	//D2C_Stat	stat7;			//+2C

	WORD	stat1;			//+20
	WORD	stat2;			//+22
	WORD	stat3;			//+24
	WORD	stat4;			//+26
	WORD	stat5;			//+28
	WORD	stat6;			//+2A
	WORD	stat7;			//+2C

};

struct ItemStatCostBIN // size=0x144 (324) (source total : fct of dll) maxline = 0x1FF = 511
{
	DWORD32	statID;			//+00
	union					//+04
	{
		DWORD32	flags;
		struct
		{
			DWORD32 sendOther:1;			//0x00000001
			DWORD32 signedf:1;			//0x00000002
			DWORD32 damagerelated:1;		//0x00000004
			DWORD32 itemspecific:1;		//0x00000008
			DWORD32 direct:1;				//0x00000010
			DWORD32 fuk1:4;				//0x000001E0
			DWORD32 updateanimrate:1;		//0x00000200
			DWORD32 fmin:1;				//0x00000400
			DWORD32 fcallback:1;			//0x00000800
			DWORD32 saved:1;				//0x00001000
			DWORD32 cvssigned:1;			//0x00002000
			DWORD32 fuk2:18;				//0xFFFFC000
		};
	};
	BYTE	sendBits;		//+08
	BYTE	sendParamBits;	//+09
	BYTE	csvbits;		//+0A
	BYTE	csvparam;		//+0B
	DWORD32	divide;			//+0C
	DWORD32	multiply;		//+10
	DWORD32	add;			//+14
	BYTE	valshift;		//+18
	BYTE	saveBits;		//+19
	BYTE	saveBits109;	//+1A	//are only for conversion
	BYTE	uk2[0x1];		//+1B
	DWORD32	saveAdd;		//+1C
	DWORD32	saveAdd109;		//+20	//are only for conversion
	DWORD32	saveParamBits;	//+24
	BYTE	uk3[0x4];		//+28
	DWORD32	minaccr;		//+2C
	BYTE	encode;			//+30
	BYTE	uk4[0x1];		//+31
	WORD	maxstat;		//+32
	WORD	descpriority;	//+34
	BYTE	descfunc;		//+36
	BYTE	descval;		//+37
	WORD	descstrpos;		//+38
	WORD	descstrneg;		//+3A
	WORD	descstr2;		//+3C
	WORD	dgrp;			//+3E
	BYTE	dgrpfunc;		//+40
	BYTE	dgrpval;		//+41
	WORD	dgrpstrpos;		//+42
	WORD	dgrpstrneg;		//+44
	WORD	dgrpstr2;		//+46
	WORD	itemevent1;		//+48
	WORD	itemevent2;		//+4A
	WORD	itemeventfunc1;	//+4C
	WORD	itemeventfunc2;	//+4E
	BYTE	keepzero;		//+50
	BYTE	uk5[0x3];		//+51
	BYTE	op;				//+54
	BYTE	opParam;		//+55

	WORD	unkAlign;		//+56 (NEW: trying to expand this struct to the correct size of 0x144)

	WORD	opStat1;		//+58
	WORD	opStat2;		//+5A
	WORD	opStat3;		//+5C
	BYTE	uk6[0xE2];		//+5E
	DWORD32	stuff;			//+140
};

struct InventoryBIN // size=0xF0 (240) (source total : fct of dll)
{
	DWORD32	invLeft;		//+00
	DWORD32	invRight;		//+04
	DWORD32	invTop;			//+08
	DWORD32	invBottom;		//+0C
	BYTE	gridX;			//+10
	BYTE	gridY;			//+11
	BYTE	uk1[2];			//+12
	DWORD32	gridLeft;		//+14
	DWORD32	gridRight;		//+18
	DWORD32	gridTop;		//+1C
	DWORD32	gridBottom;		//+20
	BYTE	gridBoxWidth;	//+24
	BYTE	gridBoxHeight;	//+25
	BYTE	uk2[2];			//+26
	DWORD32	rArmLeft;		//+28
	DWORD32	rArmRight;		//+2C
	DWORD32	rArmTop;		//+30
	DWORD32	rArmBottom;		//+34
	BYTE	rArmWidth;		//+38
	BYTE	rArmHeight;		//+39
	BYTE	uk3[2];			//+3A
	DWORD32	torsoLeft;		//+3C
	DWORD32	torsoRight;		//+40
	DWORD32	torsoTop;		//+44
	DWORD32	torsoBottom;	//+48
	BYTE	torsoWidth;		//+4C
	BYTE	torsoHeight;	//+4D
	BYTE	uk4[2];			//+4E
	DWORD32	lArmLeft;		//+50
	DWORD32	lArmRight;		//+54
	DWORD32	lArmTop;		//+58
	DWORD32	lArmBottom;		//+5C
	BYTE	lArmWidth;		//+60
	BYTE	lArmHeight;		//+61
	BYTE	uk5[2];			//+62
	DWORD32	headLeft;		//+64
	DWORD32	headRight;		//+68
	DWORD32	headTop;		//+6C
	DWORD32	headBottom;		//+70
	BYTE	headWidth;		//+74
	BYTE	headHeight;		//+75
	BYTE	uk6[2];			//+76
	DWORD32	neckLeft;		//+78
	DWORD32	neckRight;		//+7C
	DWORD32	neckTop;		//+80
	DWORD32	neckBottom;		//+84
	BYTE	neckWidth;		//+88
	BYTE	neckHeight;		//+89
	BYTE	uk7[2];			//+8A
	DWORD32	rHandLeft;		//+8C
	DWORD32	rHandRight;		//+90
	DWORD32	rHandTop;		//+94
	DWORD32	rHandBottom;	//+98
	BYTE	rHandWidth;		//+9C
	BYTE	rHandHeight;	//+9D
	BYTE	uk8[2];			//+9E
	DWORD32	lHandLeft;		//+A0
	DWORD32	lHandRight;		//+A4
	DWORD32	lHandTop;		//+A8
	DWORD32	lHandBottom;	//+AC
	BYTE	lHandWidth;		//+B0
	BYTE	lHandHeight;	//+B1
	BYTE	uk9[2];			//+B2
	DWORD32	beltLeft;		//+B4
	DWORD32	beltRight;		//+B8
	DWORD32	beltTop;		//+BC
	DWORD32	beltBottom;		//+C0
	BYTE	beltWidth;		//+C4
	BYTE	beltHeight;		//+C5
	BYTE	uk10[2];		//+C6
	DWORD32	feetLeft;		//+C8
	DWORD32	feetRight;		//+CC
	DWORD32	feetTop;		//+D0
	DWORD32	feetBottom;		//+D4
	BYTE	feetWidth;		//+D8
	BYTE	feetHeight;		//+D9
	BYTE	uk11[2];		//+DA
	DWORD32	glovesLeft;		//+DC
	DWORD32	glovesRight;	//+E0
	DWORD32	glovesTop;		//+E4
	DWORD32	glovesBottom;	//+E8
	BYTE	glovesWidth;	//+EC
	BYTE	glovesHeight;	//+ED
	BYTE	uk12[2];		//+EE
};


struct DataTables//01EE6A20 * 01FDA2D0 //second comments=1.11
{
	BYTE			uk1[0xA78];			//+000
	MonStatsBIN*	monStats;			//+A78 //1.11 and 1.10
	BYTE			uk2[0x4];			//+A7C
	DWORD32			nbMonStats;			//+A80 //1.11 and 1.10
	BYTE			uk3[0x108];			//+A84
	SkillDescBIN*	skilldesc;			//+B8C
	BYTE			uk4[0x4];			//+B90
	DWORD32			nbSkilldesc;		//+B94
	SkillsBIN*		skills;				//+B98
	BYTE			uk5[0x4];			//+B9C
	DWORD32			nbSkills;			//+BA0
	int*			nbSkillsPerPlayer;	//+BA4
	int				maxSkillsPerPlayer;	//+BA8
	WORD*			playerSkills;		//+BAC
	BYTE			uk6[0x14];			//+BB0
	CharStatsBIN*	charStats;			//+BC4
	DWORD32			nbCharStats;		//+BC8
	ItemStatCostBIN* itemStatCost;		//+BCC
	BYTE			uk7[4];				//+BD0
	DWORD32			nbItemStatCosts;	//+BD4
	WORD*			statsDescPriority;	//+BD8
	DWORD32			nbStatsDescPriority;//+BDC
	BYTE			uk8[0x18];			//+BE0
	ItemTypesBIN*	itemTypes;			//+BF8
	DWORD32			nbItemTypes;		//+BFC
	BYTE			uk9[0x18];			//+C00
	SetItemsBIN*	setItems;			//+C18 //1.11 and 1.10
	DWORD32			nbSetItems;			//+C1C //1.11 and 1.10
	BYTE			uk10[0x4];			//+C20
	UniqueItemsBIN*	uniqueItems;		//+C24 //1.11 and 1.10
	DWORD32			nbUniqueItems;		//+C28 //1.11 and 1.10
	BYTE			uk11[0x2C];			//+C2C
	LevelsBIN*		levels;				//+C58
	DWORD32			nbLevels;			//+C5C
	BYTE			uk12[0x64];			//+C60
	CubeMainBIN*	cubemain;			//+CC4 //14C0 by 148 for 1.11
	DWORD32			nbCubemain;			//+CC8 //14C4 for 1.11
	DWORD32			nbInventory;		//+CCC
	InventoryBIN*	inventory;			//+CD0
	BYTE			uk13[0x04];			//+CD4
	DWORD32			nbItems;			//+CD8
	ItemsBIN*		items;				//+CDC
	ItemsBIN*		itemsBis;			//+CE0
	BYTE			uk14[0x1F8];		//+CDC
	DWORD32			nbRunes;			//+EDC
	RunesBIN*		runes;				//+EE0
};

/*
credit: BH slashdiablo project
sgptDataTables (SuperGlobalPointer aka a extern variable, sizeof = likely 0xD10)
Note: gptItemTables and other data table containers are not part of this, they are seperate structures
d2common_sgptDataTables + 0x000 - pPlayerClassTxt
d2common_sgptDataTables + 0x004 - pPlayerClassLink
d2common_sgptDataTables + 0x008 - pBodyLocsTxt
d2common_sgptDataTables + 0x00C - pBodyLocsLink
d2common_sgptDataTables + 0x010 - pStorePageTxt
d2common_sgptDataTables + 0x014 - pStorePageLink
d2common_sgptDataTables + 0x018 - pElemTypesTxt
d2common_sgptDataTables + 0x01C - pElemTypesLink
d2common_sgptDataTables + 0x020 - pHitClassTxt
d2common_sgptDataTables + 0x024 - pHitClassLink
d2common_sgptDataTables + 0x028 - pMonModeTxt
d2common_sgptDataTables + 0x02C - pMonModeLink
d2common_sgptDataTables + 0x030 - pPlrModeTxt
d2common_sgptDataTables + 0x034 - pPlrModeLink
d2common_sgptDataTables + 0x038 - pSkillCalcTxt
d2common_sgptDataTables + 0x03C - pSkillCalcLink
d2common_sgptDataTables + 0x040 - pSkillCalcCache
d2common_sgptDataTables + 0x044 - nSkillCalcCache
d2common_sgptDataTables + 0x048 - nSkillCalcCacheDelta
d2common_sgptDataTables + 0x04C - pSkillDescCalcCache
d2common_sgptDataTables + 0x050 - nSkillDescCalcCache
d2common_sgptDataTables + 0x054 - nSkillDescCalcCacheDelta
d2common_sgptDataTables + 0x058 - pMissCalcTxt
d2common_sgptDataTables + 0x05C - pMissCalcLink
d2common_sgptDataTables + 0x060 - pMissCalcCache
d2common_sgptDataTables + 0x064 - nMissCalcCache
d2common_sgptDataTables + 0x068 - nMissCalcCacheDelta
d2common_sgptDataTables + 0x06C - pSkillCodesBin - created from the first column of skills.txt
d2common_sgptDataTables + 0x070 - pSkillCodesLink
d2common_sgptDataTables + 0x074 - pEventsTxt
d2common_sgptDataTables + 0x078 - pEventsLink
d2common_sgptDataTables + 0x07C - pCompCodesTxt
d2common_sgptDataTables + 0x080 - pCompCodesLink
d2common_sgptDataTables + 0x084 - nCompCodes
d2common_sgptDataTables + 0x088 - pMonAiTxt
d2common_sgptDataTables + 0x08C - pMonAiLink
d2common_sgptDataTables + 0x090 - nMonAi
d2common_sgptDataTables + 0x094 - pItemLink - the actual item text files are linked to gptItemTables
d2common_sgptDataTables + 0x098 - pItemCalcCache
d2common_sgptDataTables + 0x09C - nItemCalcCache
d2common_sgptDataTables + 0x0A0 - nItemCalcCacheDelta
d2common_sgptDataTables + 0x0A4 - pPropertiesTxt
d2common_sgptDataTables + 0x0A8 - pPropertiesLink
d2common_sgptDataTables + 0x0AC - nProperties
d2common_sgptDataTables + 0x0B0 - pRunesLink
d2common_sgptDataTables + 0x0B4 - pHireDescTxt
d2common_sgptDataTables + 0x0B8 - pHireDescLink
d2common_sgptDataTables + 0x0BC - pStatesTxt
d2common_sgptDataTables + 0x0C0 - pStatesLink
d2common_sgptDataTables + 0x0C4 - nStates
d2common_sgptDataTables + 0x0C8 - pStateMaskFirst
d2common_sgptDataTables + 0x0CC - pStateMaskArray[40]
d2common_sgptDataTables + 0x16C - pProgressiveStates[arrSize] - list of states with progressive = true
d2common_sgptDataTables + 0x170 - nProgressiveStates
d2common_sgptDataTables + 0x174 - pCurseStates[arrSize] - list of states with curse = true
d2common_sgptDataTables + 0x178 - nCurseStates
d2common_sgptDataTables + 0x17C - pTransformStates[arrSize] - list of states with transform = true
d2common_sgptDataTables + 0x180 - nTransformStates
d2common_sgptDataTables + 0x184 - pActionStates[arrSize] - states with actions assigned
d2common_sgptDataTables + 0x188 - nActionStates
d2common_sgptDataTables + 0x18C - pColorStates[arrSize] - states that change color
d2common_sgptDataTables + 0x190 - nColorStates
d2common_sgptDataTables + 0x194 - pSoundCodesBin - created from the first column of sounds.txt, the rest is only found in D2Client.dll
d2common_sgptDataTables + 0x198 - pSoundCodesLink
d2common_sgptDataTables + 0x19C - nSoundCodes
d2common_sgptDataTables + 0x1A0 - pHirelingsTxt
d2common_sgptDataTables + 0x1A4 - nHirelings
d2common_sgptDataTables + 0x1A8 - HireNameListStart[256] - first entry of 256 lists of hireling names
d2common_sgptDataTables + 0x5A8 - HireNameListEnd[256] - last entry of 256 lists of hireling names
d2common_sgptDataTables + 0x9A8 - pNpcsTxt
d2common_sgptDataTables + 0x9AC - nNpcs
d2common_sgptDataTables + 0x9B0 - pColorsTxt
d2common_sgptDataTables + 0x9B4 - pColorsLink
d2common_sgptDataTables + 0x9B8 - pTreasureClassExLink
d2common_sgptDataTables + 0x9BC - pTreasureClassExTxt
d2common_sgptDataTables + 0x9C0 - nTreasureClassEx
d2common_sgptDataTables + 0x9C4 - pChestTreasureClassList[45]
d2common_sgptDataTables + 0xA78 - pMonStatsTxt
d2common_sgptDataTables + 0xA7C - pMonStatsLink
d2common_sgptDataTables + 0xA80 - nMonStats
d2common_sgptDataTables + 0xA84 - pMonSoundsTxt
d2common_sgptDataTables + 0xA88 - pMonSoundsLink
d2common_sgptDataTables + 0xA8C - nMonSounds
d2common_sgptDataTables + 0xA90 - pMonStats2Txt
d2common_sgptDataTables + 0xA94 - pMonStats2Link
d2common_sgptDataTables + 0xA98 - nMonStats2
d2common_sgptDataTables + 0xA9C - pMonPlaceTxt
d2common_sgptDataTables + 0xAA0 - pMonPlaceLink
d2common_sgptDataTables + 0xAA4 - nMonPlace
d2common_sgptDataTables + 0xAA8 - pMonPresetTxt
d2common_sgptDataTables + 0xAAC - pMonPresetActList[5] - first record for each act
d2common_sgptDataTables + 0xAC0 - nMonPresetEachAct[5] - count for # of records per act
d2common_sgptDataTables + 0xAD4 - pSuperUniquesTxt
d2common_sgptDataTables + 0xAD8 - pSuperUniquesLink
d2common_sgptDataTables + 0xADC - nSuperUniques
d2common_sgptDataTables + 0xAE0 - SuperUniqueHcIdxList[66] (66 words)
d2common_sgptDataTables + 0xB64 - pMissilesTxt
d2common_sgptDataTables + 0xB68 - pMissilesLink
d2common_sgptDataTables + 0xB6C - nMissiles
d2common_sgptDataTables + 0xB70 - pMonLvlTxt
d2common_sgptDataTables + 0xB74 - nMonLvl
d2common_sgptDataTables + 0xB78 - pMonSeqTxt
d2common_sgptDataTables + 0xB7C - pMonSeqLink
d2common_sgptDataTables + 0xB80 - nMonSeq
d2common_sgptDataTables + 0xB84 - pMonSequences - created from MonSeq.txt after reading it
d2common_sgptDataTables + 0xB88 - nMonSequences
d2common_sgptDataTables + 0xB8C - pSkillDescTxt
d2common_sgptDataTables + 0xB90 - pSkillDescLink
d2common_sgptDataTables + 0xB94 - nSkillDesc
d2common_sgptDataTables + 0xB98 - pSkillsTxt
d2common_sgptDataTables + 0xB9C - pSkillsLink
d2common_sgptDataTables + 0xBA0 - nSkills
d2common_sgptDataTables + 0xBA4 - pPlayerSkillCount[arrSize] - an array of player skill counts (all words)
d2common_sgptDataTables + 0xBA8 - nPlayerSkillCount
d2common_sgptDataTables + 0xBAC - pPlayerSkillList[arrSize] - the skill Ids (all words)
d2common_sgptDataTables + 0xBB0 - nPassiveSkillCount
d2common_sgptDataTables + 0xBB4 - pPassiveSkillList[arrSize] - the skill Ids (all words)
d2common_sgptDataTables + 0xBB8 - pOverlayTxt
d2common_sgptDataTables + 0xBBC - pOverlayLink
d2common_sgptDataTables + 0xBC0 - nOverlay
d2common_sgptDataTables + 0xBC4 - pCharStatsTxt
d2common_sgptDataTables + 0xBC8 - nCharStats
d2common_sgptDataTables + 0xBCC - pItemStatCostTxt
d2common_sgptDataTables + 0xBD0 - pItemStatCostLink
d2common_sgptDataTables + 0xBD4 - nItemStatCost
d2common_sgptDataTables + 0xBD8 - pOpStatNesting[arrSize]
d2common_sgptDataTables + 0xBDC - nOpStatNesting
d2common_sgptDataTables + 0xBE0 - pMonEquipTxt
d2common_sgptDataTables + 0xBE4 - nMonEquip
d2common_sgptDataTables + 0xBE8 - pPetTypesTxt
d2common_sgptDataTables + 0xBEC - pPetTypesLink
d2common_sgptDataTables + 0xBF0 - nPetTypes
d2common_sgptDataTables + 0xBF4 - pItemTypesLink
d2common_sgptDataTables + 0xBF8 - pItemTypesTxt
d2common_sgptDataTables + 0xBFC - nItemTypes
d2common_sgptDataTables + 0xC00 - nItemTypeNesting
d2common_sgptDataTables + 0xC04 - pItemTypeNesting[arrSize]
d2common_sgptDataTables + 0xC08 - pSetsLink
d2common_sgptDataTables + 0xC0C - pSetsTxt
d2common_sgptDataTables + 0xC10 - nSets
d2common_sgptDataTables + 0xC14 - pSetItemsLink
d2common_sgptDataTables + 0xC18 - pSetItemsTxt
d2common_sgptDataTables + 0xC1C - nSetItems
d2common_sgptDataTables + 0xC20 - pUniqueItemsLink
d2common_sgptDataTables + 0xC24 - pUniqueItemsTxt
d2common_sgptDataTables + 0xC28 - nUniqueItems
d2common_sgptDataTables + 0xC2C - pMonPropLink
d2common_sgptDataTables + 0xC30 - pMonPropTxt
d2common_sgptDataTables + 0xC34 - nMonProp
d2common_sgptDataTables + 0xC38 - pMonTypeLink
d2common_sgptDataTables + 0xC3C - pMonTypeTxt
d2common_sgptDataTables + 0xC40 - nMonType
d2common_sgptDataTables + 0xC44 - pMonTypeNesting[arrSize]
d2common_sgptDataTables + 0xC48 - nMonTypeNesting
d2common_sgptDataTables + 0xC4C - pMonUModLink
d2common_sgptDataTables + 0xC50 - pMonUModTxt
d2common_sgptDataTables + 0xC54 - nMonUMod
d2common_sgptDataTables + 0xC58 - pLevelsTxt
d2common_sgptDataTables + 0xC5C - nLevels
d2common_sgptDataTables + 0xC60 - pLvlDefsBin
d2common_sgptDataTables + 0xC64 - pLvlPrestTxt
d2common_sgptDataTables + 0xC68 - nLvlPrest
d2common_sgptDataTables + 0xC6C - ItemStatCostStuff[2] - related to opstats, stuff column (etc)
d2common_sgptDataTables + 0xC74 - pAnimTables (gptAnimTables)
d2common_sgptDataTables + 0xC78 - pExperienceTxt
d2common_sgptDataTables + 0xC7C - pDifficultyLevelsTxt
d2common_sgptDataTables + 0xC80 - nDifficultyLevels
d2common_sgptDataTables + 0xC84 - pExpFieldD2 - collision detection map
d2common_sgptDataTables + 0xC88 - ExpFieldRuntimeData[10]
d2common_sgptDataTables + 0xCB0 - pLvlSubExtraStuff[arrSize]
d2common_sgptDataTables + 0xCB4 - nLvlSubExtraStuff
d2common_sgptDataTables + 0xCB8 - pCharTemplateTxt
d2common_sgptDataTables + 0xCBC - nCharTemplate
d2common_sgptDataTables + 0xCC0 - pArenaTxt
d2common_sgptDataTables + 0xCC4 - pLvlTypesTxt
d2common_sgptDataTables + 0xCC8 - pWaypoints[arrSize]
d2common_sgptDataTables + 0xCCC - nWaypoints
d2common_sgptDataTables + 0xCD0 - nLvlTypes
d2common_sgptDataTables + 0xCD4 - pLvlWarpTxt
d2common_sgptDataTables + 0xCD8 - nLvlWarp
d2common_sgptDataTables + 0xCDC - pLvlMazeTxt
d2common_sgptDataTables + 0xCE0 - nLvlMaze
d2common_sgptDataTables + 0xCE4 - pLvlSubTxt
d2common_sgptDataTables + 0xCE8 - nLvlSub
d2common_sgptDataTables + 0xCEC - pLvlSubCache[arrSize]
d2common_sgptDataTables + 0xCF0 - three unused dwords here
d2common_sgptDataTables + 0xCFC - pMapCache[arrSize]
d2common_sgptDataTables + 0xD00 - nMapCache
d2common_sgptDataTables + 0xD04 - pCubeMainTxt
d2common_sgptDataTables + 0xD08 - nCubeMain
d2common_sgptDataTables + 0xD0C - bWriteBinFiles (BOOL)
*/
struct sgptDataTable {
	BYTE*	pPlayerClass;			//0x00
	DWORD32	dwPlayerClassRecords;	//0x04
	DWORD32*	pBodyLocs;		//0x08
	DWORD32	dwBodyLocsRecords;		//0x0C
	BYTE*	pStorePage;				//0x10
	DWORD32	dwStorePageRecords;		//0x14
	BYTE*	pElemTypes;				//0x18
	DWORD32	dwElemTypesRecords;		//0x1C
	BYTE*	pHitClass;				//0x20
	DWORD32	dwHitClassRecords;		//0x24
	BYTE*	pMonMode;				//0x28
	DWORD32	dwMonModeTxt;			//0x2C
	BYTE*	pPlrMode;				//0x30
	DWORD32	dwPlrModeRecords;		//0x34
	BYTE*	pSkillCalc;				//0x38
	DWORD32	dwSkillCalcRecords;		//0x3C
	BYTE*	pSkillCalcCache;		//0x40
	DWORD32	dwSkillCalcCacheRecs;	//0x44
	DWORD32	dwSkillCalcCacheDelta;	//0x48
	BYTE*	pSkillDescCalcCache;	//0x4C
	DWORD32	dwSkillDescCalcCacheRecs;//0x50
	DWORD32	dwSkillDescCalcCacheDelta;//0x54
	BYTE*	pMissCalc;				//0x58
	DWORD32	dwMissCalcRecords;		//0x5C
	BYTE*	pMissCalcCache;			//0x60
	DWORD32	dwMissCalcCacheRecs;	//0x64
	DWORD32	dwMissCalcCacheDelta;	//0x68
	BYTE*	pSkillCodes;			//0x6C
	DWORD32	dwSkillCodesRecs;		//0x70
	BYTE*	pEvents;				//0x74
	DWORD32	dwEventsRecs;			//0x78
	BYTE*	pCompCodes;				//0x7C
	DWORD32	dwCompCodesRecs;		//0x80
	DWORD32	dwCompCodes;			//0x84
	BYTE*	pMonAi;					//0x88
	DWORD32	dwMonAiRecs;			//0x8C
	DWORD32	dwMonAi;				//0x90
	BYTE*	pItem;					//0x94
	BYTE*	pItemCalcCache;			//0x98
	DWORD32	dwItemCalcCacheRecs;	//0x9C
	DWORD32	dwItemCalcCache;		//0xA0
	PropertiesBIN*	pPropertiesTxt;	//0xA4
	BYTE*	dwProperties;			//0xA8
	DWORD32	dwProportiesRecs;		//0xAC Max (exclusive) stat mod code (should be around 268)
	BYTE*	pRunes;					//0xB0
	BYTE*	pHireDescs;				//0xB4
	DWORD32	dwHireDescsRecs;		//0xB8
	DWORD32*	pStatesTxt;			//0xBC
	DWORD32	dwStatesTxtRecs;		//0xC0
	DWORD32	dwStates;				//0xC4
	BYTE*	pStateMaskFirst;		//0xC8
	BYTE*	pStateMaskArr[40];		//0xCC
	BYTE*	pProgressiveStates;		//0x16C
	DWORD32	dwProgressiveStatesRecs;//0x170
	BYTE*	pCurseStates;			//0x174
	DWORD32	dwCurseStatesRecs;		//0x178
	BYTE*	pTransStates;			//0x17C
	DWORD32	dwTransStatesRecs;		//0x180
	BYTE*	pActionStates;			//0x184
	DWORD32	dwActionStatesRecs;		//0x188
	BYTE*	pColorStates;			//0x18C
	DWORD32	dwColorStatesRecs;		//0x190
	BYTE*	pSoundCodes;			//0x194
	BYTE*	pSoundCodesTxt;			//0x198
	DWORD32	dwSoundCodesRecs;		//0x19C
	BYTE*	pHirelings;				//0x1A0
	DWORD32	dwHirelingsRecs;		//0x1A4
	DWORD32	HireNameStart[256];		//0x1A8
	DWORD32	HireNameEnd[256];		//0x5A8
	BYTE*	pNpcs;					//0x9A8
	DWORD32	dwNpcsRecs;				//0x9AC
	BYTE*	pColorsTxt;				//0x9B0
	BYTE*	pColors;				//0x9B4
	BYTE*	pTreasureClassEx;		//0x9B8
	BYTE*	pTreasureClassExTxt;	//0x9BC
	DWORD32	dwTreasureClassExRecs;	//0x9C0
	BYTE*	pChestTreasureClassLst[45];	//0x9C4
	MonStatsBIN* pMonStatsTxt;		//0xA78
	BYTE*	pMonStats;				//0xA7C
	DWORD32	dwMonStatsRecs;			//0xA80
	BYTE*	pMonSoundsTxt;			//0xA84
	BYTE*	pMonSounds;				//0xA88
	DWORD32	dwMonSoundsRecs;		//0xA8C
	BYTE*	pMonStats2Txt;			//0xA90
	BYTE*	pMonStats2;				//0xA94
	DWORD32	dwMonStats2Recs;		//0xA98
	BYTE*	pMonPlaceTxt;			//0xA9C
	BYTE*	pMonPlace;				//0xAA0
	DWORD32	dwMonPlaceRecs;			//0xAA4
	BYTE*	pMonPresetTxt;			//0xAA8
	BYTE*	pMonPresetActLst[5];	//0xAAC
	DWORD32	dwMonPresetActRecs[5];	//0xAC0
	BYTE*	pSuperUniquesTxt;		//0xAD4
	BYTE*	pSuperUniques;			//0xAD8
	DWORD32	dwSuperUniquesRecs;		//0xADC
	WORD	SuperUniqeIdxList[66];	//0xAE0
	DWORD32*	pMissilesTxt;	//0xB64
	BYTE*	pMissiles;				//0xB68
	DWORD32	dwMissilesRecs;			//0xB6C
	BYTE*	pMonLvl;				//0xB70
	DWORD32	dwMonLvlRecs;			//0xB74
	BYTE*	pMonSeqTxt;				//0xB78
	BYTE*	pMonSeq;				//0xB7C
	DWORD32	dwMonSeqRecs;			//0xB80
	BYTE*	pMonSequences;			//0xB84
	DWORD32	dwMonSequencesRecs;		//0xB88
	SkillDescBIN*	pSkillDescTxt;	//0xB8C
	BYTE*	pSkillDesc;				//0xB90
	DWORD32	dwSkillDescRecs;		//0xB94
	SkillsBIN* pSkillsTxt;			//0xB98
	BYTE*	pSkills;				//0xB9C
	DWORD32	dwSkillsRecs;			//0xBA0
	BYTE*	pPlayerSkillCount;		//0xBA4
	DWORD32	dwPlayerSkillCount;		//0xBA8
	BYTE*	pPlayerSkillList;		//0xBAC
	DWORD32	dwPassiveSkillCount;	//0xBB0
	BYTE*	pPasssiveSkillList;		//0xBB4
	BYTE*	pOverlayTxt;			//0xBB8
	BYTE*	pOverlay;				//0xBBC
	DWORD32	dwOverlayRecs;			//0xBC0
	CharStatsBIN*	pCharStatsTxt;	//0xBC4
	DWORD32	dwCharsStatsRecs;		//0xBC8
	ItemStatCostBIN* pItemStatCostTxt;//0xBCC
	BYTE*	pItemStatCost;			//0xBD0
	DWORD32	dwItemStatCostRecs;		//0xBD4 - max number of records in ItemStatCost.txt (exclusive, should be 359-ish)
	BYTE*	pOpStatNesting;			//0xBD8
	DWORD32	dwOpStatNestingRecs;	//0xBDC
	BYTE*	pMonEquip;				//0xBE0
	DWORD32	dwMonEquipRecs;			//0xBE4
	BYTE*	pPetTypesTxt;			//0xBE8
	BYTE*	pPetTypes;				//0xBEC
	DWORD32	dwPetTypesRecs;			//0xBF0
	BYTE*	pItemsType;				//0xBF4
	BYTE*	pItemsTypeTxt;			//0xBF8
	DWORD32	dwItemsTypeRecs;		//0xBFC
	DWORD32	dwItemsTypeNesting;		//0xC00
	BYTE*	pItemsTypeNesting;		//0xC04
	BYTE*	pSets;					//0xC08
	BYTE*	pSetsTxt;				//0xC0C
	DWORD32	dwSetsRecs;				//0xC10
	BYTE*	pSetItems;				//0xC14
	SetItemsBIN* pSetItemsTxt;		//0xC18
	DWORD32	dwSetItemsRecs;			//0xC1C
	BYTE*	pUniqueItems;			//0xC20
	UniqueItemsBIN*	pUniqueItemsTxt;//0xC24
	DWORD32	dwUniqItemsRecs;		//0xC28
	BYTE*	pMonProp;				//0xC2C
	BYTE*	pMonPropTxt;			//0xC30
	DWORD32	dwMonPropRecs;			//0xC34
	BYTE*	pMonType;				//0xC38
	BYTE*	pMonTypeTxt;			//0xC3C
	DWORD32	dwMonTypeRecs;			//0xC40
	BYTE*	pMonTypeNesting;		//0xC44
	DWORD32	dwMonTypeNestingRecs;	//0xC48
	BYTE*	pMonUMod;				//0xC4C
	BYTE*	pMonUModTxt;			//0xC50
	DWORD32	dwMonUModRecs;			//0xC54
	LevelsBIN*	pLevelsTxt;			//0xC58
	DWORD32	dwLevelsRecs;			//0xC5C
	BYTE*	pLvlDefs;				//0xC60
	BYTE*	pLvlPrest;				//0xC64
	DWORD32	dwLvlPrestRecs;			//0xC68
	DWORD32	ItemStatCostStuff[2];	//0xC6C
	BYTE*	pAnimTables;			//0xC74
	BYTE*	pExperience;			//0xC78
	DifficultyLevelsBIN* pDiffLvlsTxt;//0xC7C
	DWORD32	dwDiffLvlsRecs;			//0xC80
	DWORD32	_1;						//0xC84
	BYTE*	pCharTemp;				//0xC88
	DWORD32	dwCharTempRecs;			//0xC8C
	DWORD32* pArena;				//0xC90
	CubeMainBIN*	pCubeMain;		//0xC94
	DWORD32	dwCubeMainRecs;			//0xC98
	DWORD32   _2;						//0xC9C
	BYTE*	pLvlSubExtra;			//0xCA0
	BYTE*	pExpFieldD2;			//0xCA4
	DWORD32   ExpFieldData[5];		//0xCA8
	BYTE*	pLvlTypes;				//0xCBC
	BYTE*   pWaypoints;				//0xCC0
	DWORD32	dwWaypointsRecs;		//0xCC4
	DWORD32	dwLvlTypes;				//0xCC8
	BYTE*	pLvlWarp;				//0xCCC
	DWORD32	dwLvlWarpRecs;			//0xCD0
	DWORD32*	pLvlMaze;			//0xCD4
	DWORD32	dwLvlMazeRecs;			//0xCD8
	BYTE*	pLvlSub;				//0xCDC
	DWORD32	dwLvlSubRecs;			//0xCE0
	DWORD32   pLvlSubCache;			//0xCE4 aka sgpnTileSubsTypeStart
	DWORD32	_5[5];					//0xCE8
	BYTE*	pMapCache;				//0xCFC
	DWORD32	dwMapCacheRecs;			//0xD00
	DWORD32	_6[2];					//0xD04
	DWORD32*  pIgnoreList;            //0xD0C
};


/* NEXT NOT TESTED IN 1.10 (1.09b)

struct AffixTxt
{
    BYTE    mName[0x21];     // +00
    WORD    mVersion;        // +22
    DWORD32   mMod1code;       // +24
    DWORD32   mMod1param;      // +28
    DWORD32   mMod1min;        // +2c
    DWORD32   mMod1max;        // +30
    DWORD32   mMod2code;       // +34
    DWORD32   mMod2param;      // +38
    DWORD32   mMod2min;        // +3c
    DWORD32   mMod2max;        // +40
    DWORD32   mMod3code;       // +44
    DWORD32   mMod3param;      // +48
    DWORD32   mMod3min;        // +4c
    DWORD32   mMod3max;        // +50
    WORD    mSpawnable;      // +54
    WORD    mTransformcolor; // +56
    DWORD32   mLevel;          // +58
    DWORD32   mGroup;          // +5c
    DWORD32   mMaxlevel;       // +60
    BYTE    mRare;           // +64
    BYTE    mLevelreq;       // +65
    BYTE    mClassspecific;  // +66
    BYTE    mClass;          // +67
    BYTE    classlevelreq;   // +68
    BYTE    itype1;          // +69
    BYTE    itype2;          // +6a
    BYTE    itype3;          // +6b
    BYTE    itype4;          // +6c
    BYTE    itype5;          // +6d
    BYTE    itype6;          // +6e
    BYTE    itype7;          // +6f
    BYTE    etype1;          // +70
    BYTE    etype2;          // +71
    BYTE    etype3;          // +72
    BYTE    etype4;          // +73
    BYTE    etype5;          // +74
    DWORD32   frequency;       // +75
    DWORD32   mDivide;         // +79
    DWORD32   mMultiply;       // +7D
    DWORD32   mAdd;            // +81
};

struct AffixTxtTable
{
    DWORD32       mNbAffix;           // +00 = total affixes
    AffixTxt*   mStartTable;        // +04 = beginnig ptr
    AffixTxt*   mSuffixTable;       // +08 = suffix.txt ptr
    AffixTxt*   mPrefixTable;       // +0c = prefix.txt ptr
    AffixTxt*   mAutomagicTable;    // +10 = automagic.txt ptr
};
*/

//NEW. sizeof=0x48
struct RareAffixTable
{
	BYTE unk_0[0xC];	//0x0
	WORD wTableIndex;	//0xC
	WORD unk_E;			//0xE
	//BYTE unk_0[16];		//0x0
	WORD wItype1;		//0x10
	WORD wItype2;		//0x12
	WORD wItype3;		//0x14
	WORD wItype4;		//0x16
	WORD wItype5;		//0x18
	WORD wItype6;		//0x1A
	WORD wItype7;		//0x1C
	WORD wEtype1;		//0x1E
	WORD wEtype2;		//0x20
	WORD wEtype3;		//0x22
	WORD wEtype4;		//0x24
	char name[0x22];	//0x26
};

#pragma pack(pop)