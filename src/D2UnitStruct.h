#pragma once
#pragma pack(push, 1)
struct CBPlayerData;
struct CBItemData;
struct Unit;

/*=================================================================*/
/*  Skill Structure.                                               */
/*=================================================================*/

struct SkillData
{								//Offset from Code. (size = 0x3C or 0x40)
	SkillsBIN* ptSkillBin;		//+00
	SkillData* ptNextSkill;	//+04
	DWORD32	mode;           //+08
	DWORD32	uk1[3];         //+0C
	DWORD32	targetInfo;     //+18
	DWORD32	targetType;     //+1c
	DWORD32	targetUNID;     //+20
	DWORD32	uk2;            //+24
	DWORD32	slvl;           //+28
	DWORD32	slvlBonus;      //+2c
	DWORD32	uk3;            //+30
	int		state;          //+34 (-1 if index exist)
	DWORD32	param1;			//+38 (nb current charge)
	DWORD32	param2;			//+3C
};

struct Skills
{								//Offset from Code.
	DWORD32		gameRelated;	//+00
	SkillData*	ptFirstSkill;	//+04
	SkillData*	ptLeftSkill;	//+08
	SkillData*	ptRightSkill;	//+0c
    SkillData*	ptCurrentSkill;	//+10
};


/*=================================================================*/
/*   Unit Data Structure.                                          */
/*=================================================================*/

struct Position
{
	DWORD32 x;
	DWORD32 y;
};

struct Room//size=0x80
{
//ptRoom +48 0 = spawn new units (monster, objects e.tc), 1 = don't spawn any new units
	DWORD32	seed1;						//+00
	DWORD32	seed2;						//+04
	BYTE	uk8[0x1C];					//+08
	Room*	ptNearRooms;				//+24
	DWORD32	nbNearRooms;				//+28
	Unit*	unit;						//+2C
	BYTE	uk5[0x44];					//+30
	Room*	ptNextRoom;					//+74
	union
	{
		BYTE	flags;					//+78
		struct
		{
			BYTE isGenerated:1;
			BYTE isGenerated2:1;//???
		};
	};
};

struct ActMap//ptGame+BC size=0x60
{
	DWORD32	isNotManaged;
	DWORD32	uk4;
	DWORD32	uk8;//size = 0x488
	Room*	ptFirstRoom;
};

struct NetClient;
//ptGame : 04E4007C
struct Game
{                              			//Offset from Code.
	BYTE	uk1[0x18];					//+00
	DWORD32	_ptLock;					//+18 Unknown  
	DWORD32	memoryPool;					//+1C Memory Pool (??)  
	BYTE	uk2[0x4D];					//+20
	BYTE	difficultyLevel;			//+6D (Difficulty 0,1 or 2) (TODO: enum class Difficulty : BYTE {Normal, Nightmare, Hell} )
	WORD	unknown1;					//+6E Cube puts 4 here
	DWORD32	isLODGame;					//+70 (D2=0 LOD =1) (DWORD32 ?)
	BYTE	uk3[0x04];					//+71
	WORD	unknown2;					//+78
	BYTE	uk4[0x0E];					//+7A
	NetClient*	ptClient;				//+88
	BYTE	uk8C[0x30];					//+8C
	ActMap*	mapAct[5];					//+BC
	BYTE	ukD0[0x1024];				//+D0
	DWORD32*	game10F4;					//+10F4
	BYTE	uk6[0x28];					//+10F8
	Unit*	units[0xA00];				//+1120
	Unit*	roomtitles[0x200];			//+1B20
};
//WORD ptGame+28 game ID ?



struct Path //(8 dword)
{                              			//Offset from Code.		Size: 20
	WORD	uk1;						//+00
	WORD	mapx;						//+02
	WORD	uk2;						//+04
	WORD	mapy;						//+06
	DWORD32	uk3;						//+08
	DWORD32	x;							//+0C
	DWORD32	y;							//+10
	DWORD32	uk6;						//+14
	DWORD32	uk7;						//+18
	Room*	ptRoom;						//+1C
};


struct Inventory
{                               		//Offset from Code.		Size: 30 à 40
	DWORD32	tag;						//+00	= 0x01020304
	BYTE	uk1[0x04];					//+04	=? 0
	Unit*	ptChar;						//+08
	Unit*	ptItem;						//+0C
	BYTE	uk2[0x10];					//+10
	Unit*	inventory1;					//+20
	BYTE	uk3[0x04];					//+24
	DWORD32	currentUsedSocket;			//+28 //Kingpin : a variable to know how many sockets that have added to item
	DWORD32	Inventory2C;				//+2C //one value
	DWORD32	Inventory30;				//+30
	void*	ptCorpse;					//+34
	BYTE	uk5[0x04];					//+38
	DWORD32	nextCorpseId;				//+3C //max = 15
	BYTE	uk6[0x04];					//+40
};

struct D2Stat
{
	WORD	index;
	D2C_Stat id; //check ISC.txt
	int		value;
};


struct Stats				//sizeof(Stats)=0x64
{
	DWORD32	nUnitId;				//+00
	Unit*	ptUnit;					//+04
	DWORD32	nUnitType;				//+08
	DWORD32	nItemNum;				//+0C
	union
	{
		DWORD32	flags;				//+10
		struct
		{
			DWORD32 fuk1:13;			//0x00001FFF
			DWORD32 isDisabled:1;		//0x00002000
			DWORD32 fuk2:17;			//0x7FFFC000
			DWORD32 dontUseBaseValue:1;//0x80000000
		};
	};
	DWORD32	id;						//+14
	DWORD32	uk18;					//+18
	BYTE	uk2[0x08];				//+1C
	D2Stat*	ptBaseStatsTable;		//+24
	WORD	nbBaseStats;			//+28
	WORD	sizeOfBaseStatsTable;	//+2A ??
	Stats*	ptStats;				//+2C
	BYTE	uk3[0x04];				//+30
	Stats*	ptItemStats;			//+34
	BYTE	uk4[0x04];				//+38
	Stats*	ptAffixStats;			//+3C
	Stats*	ptNextStats2;			//+40
	union
	{
		Unit*	ptChar;				//+44
		Unit*	ptItem;
	};

	D2Stat*	ptStatsTable;			//+48, crashes - do not use
	WORD	nbStats;				//+4C
	WORD	sizeOfStatsTable;		//+4E ??
	BYTE	uk5[0x8];				//+50
	BYTE*	unknow0;				//+58 (sizeof(*unknow0)=0x30 (calculated)
	DWORD32	unknow1;				//+5C (=0)
	DWORD32	unknow2;				//+60 (=0)
};


struct MonsterData					// sizeof(MonsterData)=0x60
{										//Offset from Code.
    BYTE	uk[0x16];					//+00
 	union {
		WORD	flags;					//+16
		struct {
			WORD	fuk1:1;
			WORD	isSuperUnique:1;
			WORD	isChampion:1;
			WORD	isUnique:1;
			WORD	fuk2:13;
		};
	};
   BYTE		uk1[0x0E];					//+18
   WORD		superUniqueID;				//+26
   void*	unknow1;					//+28
   BYTE		uk2[0x38];					//+28
};

struct ObjectData
{
	ObjectsBIN*	ptObjectsBIN;
	BYTE		levelID;
};
/*
Kingpin: struct MonsterData   
{  
     BYTE     uk1[0x13];          // +00  
     DWORD32     Flags;               // +14  
     DWORD32     uk2;               // +18  
     DWORD32     MinionOwnerID;     // +1C  
     BYTE     uk3[0x5];          // +20  
     WORD     SuperUniqueID;     // +26 Superunique ID of monster  
     D2Game*     ptGame;               // +28 ptGame  
};
*/

#define F2_ITEM_IS_IDENTIFIED 0x10 //or F_IS_IDENTIFIED ?

struct ItemData//size=0x74
{										//Offset from Code.
	DWORD32	quality;					//+00
	DWORD32	seedLow;					//+04
	DWORD32	seedHi;						//+08
	DWORD32	playerID;					//+0C #10734 / #10735 (PCInventory->ptPlayer->0C)
	DWORD32	seedStarting;				//+10
	DWORD32	flags1;						//+14
	union {
		DWORD32	flags2;					//+18 (used by d2common_10202 to apply ITEMFLAGs as outlined below)
		struct {
			DWORD32	fuk1:1;				//0x00000001
			DWORD32	isIndentified:1;	//0x00000002
			DWORD32	fuk2:2;				//0x0000000C
			DWORD32	isUnindentified:1;	//0x00000010
			DWORD32	fuk3:3;				//0x000000E0
			DWORD32	isBroken:1;			//0x00000100
			DWORD32	fuk4:2;				//0x00000600
			DWORD32	isSocketed:1;		//0x00000800
			DWORD32	fuk5:10;			//0x003FF000
			DWORD32	isEtheral:1;		//0x00400000
			DWORD32	fuk6:3;				//0x03800000
			DWORD32	isRuneword:1;		//0x04000000
			DWORD32	fuk7:1;				//0x08000000
			DWORD32	isPersonalized:1;	//0x10000000
			DWORD32	fuk8:3;				//0xE0000000
		};
	};
/*
ITEMFLAG_NEWITEM               = 0x00000001,  
ITEMFLAG_TAGETING               = 0x00000004,  
ITEMFLAG_UNIDENTIFIED               = 0x00000010,  
ITEMFLAG_QUANTITY               = 0x00000020,  
ITEMFLAG_Durability               = 0x00000100,  
ITEMFLAG_UNKNOWN2               = 0x00000400,  
ITEMFLAG_SOCKETED               = 0x00000800,  
ITEMFLAG_NON_SELLABLE               = 0x00001000,  
ITEMFLAG_NEWITEM2               = 0x00002000,  
ITEMFLAG_UNKNOWN3               = 0x00004000,  
ITEMFLAG_CHECKSECPRICE               = 0x00010000,  
ITEMFLAG_CHECKGAMBLEPRICE          = 0x00020000,  
ITEMFLAG_UNKNOWN4               = 0x00080000,  
ITEMFLAG_INDESTRUCTIBLE(ETHERAL) = 0x00400000,  
ITEMFLAG_UNKNOWN5               = 0x00800000,  
ITEMFLAG_FROMPLAYER               = 0x01000000,  
ITEMFLAG_RUNEWORD               = 0x04000000
*/
	DWORD32	guid1;						//+1C Global Unique ID 1  
	DWORD32	guid2;						//+20 Global Unique ID 2  
	DWORD32	guid3;						//+24 Global Unique ID 3  
	DWORD32	uniqueID;					//+28 items that are superior will use this field as an index to QualityItems.txt
	BYTE	ilvl;						//+2C
	BYTE	uk1[0x03];					//+2D
	WORD	version;					//+30 not sure what this is... looks like it's always set to 101?
	WORD	rarePrefix;					//+32
	WORD	rareSuffix;					//+34
	WORD	autoPref;					//+36 Automagix affix. this does not include staff mods. Refer to Armor.txt (auto prefix column). For staff mods, check ItemTypes.txt (staff mods column)
	WORD	prefix[3];					//+38 pretty sure this is specific for magic affixes for magic / rare / unique items only
	WORD	suffix[3];					//+3E pretty sure this is specific for magic affixes for magic / rare / unique items only
	BYTE	equipLoc;					//+44
    /*	emplacement si équipé
	*	00 = noequip/inBelt
	*   01 = head
	*	02 = neck
	*	03 = tors
	*	04 = rarm
	*	05 = larm
	*	06 = lrin
	*	07 = rrin
	*	08 = belt
	*	09 = feet
	*	0A = glov
	*	0B = ralt
	*	0C = lalt
*/
	BYTE	page;						//+45
    /*	page dans laquel se trouve l'item
    *	FF = mouse/equip/onEarth
    *	00 = inventory
    *   01 = cube
    *	04 = stash
    */
	BYTE	uk4[0x01];					//+46
	BYTE	ItemData3;					//+47 //D2Common10854 D2Common10853
	BYTE	pEarLevel;					//+48
	BYTE	varGfx;						//+49
	char	IName[0x12];				//+4A //inscribed/ear name  
	Inventory*	ptInventory;			//+5C
	Unit*	ptPrevItem;					//+60
	Unit*	ptNextItem;					//+64
	BYTE	uk8[0x01];					//+68
	BYTE	ItemData2;					//+69
	BYTE	uk9[0x0A];					//+6A
};


struct NetClient
{
	DWORD32	clientID;					//+00
	BYTE	uk1[0x06];					//+04
	union {								//+0A
		WORD	flag;
		struct {
			WORD f1:1;
			WORD f2:1;
			WORD isHardCoreGame:1;
		};
	};
	BYTE	uk2[0x170];					//+0C
	BYTE*	savefile;					//+17C
	DWORD32	finalSize;					//+180
	DWORD32	counter;					//+184
	DWORD32	currentSize;				//+188
	BYTE	uk3[0x1C];					//+18C
	Game*	ptGame;						//+1A8
	//+1A8 is ptGame
	//+4A8 ptNextClient
/*
Kingpin: ptPclient  
+16C is either act or unit type 
+170 Active UniqueID for player 
+174 Active ptPlayer on Client 
+1a8 ptGame 
+1b4 Current or next ptRoom  
*/
};
/*
struct PlayerData
{
	char		name[0x10];				//+00 (size min 0x08 max 0x11)
	BYTE		uk1[0x8C];				//+10
	NetClient*	ptNetClient;			//+9C
};
*/
struct PlayerData   
{  
	char		name[0x10];				//+00	Player Name  
	void*		ptQuest[3];				//+10	Quest Pointers for each difficulty  
	BYTE		uk1[0x18];				//+1C		//before : 0x14
	void*		ptArenaUnit;			//+34	ptArena for the Unit  
	BYTE		uk2[0x4];				//+38		//before : 0x7
	WORD		MPSourcePortalUniqueID;	//+3C	Source Portal Unique_ID  
	BYTE		uk3[0x2];				//+3E
	WORD		MPDestPortalUniqueID;	//+40	Destination Portal Unique_ID  
	BYTE		uk4[0x06];				//+42  
	BYTE		ptObjectUnID;			//+48	Object UniqueID for TownPortals       
	BYTE		uk5[0x53];				//+49  
	NetClient*	ptNetClient;			//+9C	ptClient  
};


#define F1_IS_SPAWNED 0x10 //or F_IS_IDENTIFIED ?
#define F2_IS_LOD 0x2000000
struct Unit
{										//Offset from Code.		Size: 0xF4+4
	DWORD32		nUnitType;				//+00
	union{
		DWORD32			nPlayerClass;
		DWORD32			nTxtFileNo;         
    };									//+04
	DWORD32		nUnitId;				//+08
	DWORD32		nItemNum;				//+0C
	DWORD32		CurrentAnim;			//+10
	union{
		MonsterData*	ptMonsterData;
		ObjectData*		ptObjectData;
		ItemData*		ptItemData;
		PlayerData*		ptPlayerData;
	};									//+14
	BYTE		act;					//+18
	BYTE		uk12[3];				//+19
	void*		ptAct;					//+1C
	DWORD32		SeedLow;				//+20
	DWORD32		SeedHi;					//+24
	DWORD32		SeedStarting;			//+28
	Path*		path;					//+2C
	BYTE		uk1[0x08];				//+30
	Path*		ptPos;					//+38
	DWORD32		animSpeed;				//+3C
	BYTE		uk2[0x04];				//+40
	DWORD32		curFrame;				//+44
	DWORD32		remainingFrame;			//+48
	WORD		animSpeedW;				//+4C
	BYTE		actionFlag;				//+4E
	BYTE		uk3[0x1];				//+4F
	void*		ptAnimData;				//+50
	BYTE		uk4[0x08];				//+54
	Stats*		ptStats;				//+5C
	Inventory*	ptInventory;		    //+60
	BYTE		uk5[0x1C];				//+64
	Game*		ptGame;					//+80
	BYTE		uk6[0x24];				//+84
	Skills*		ptSkills;				//+A8
	void*		ptCombatData;			//+AC
	BYTE		uk7[0x08];				//+B0
	DWORD32		itemCode;				//+B8 for an item being dropped by this unit
	BYTE		uk8[0x08];				//+BC
	DWORD32		flags1;					//+C4
	union{
		DWORD32		flags2;				//+C8	//flags
		struct{
			DWORD32	ukf1:25;
			DWORD32	isLod:1;
		};
	};
	BYTE		uk9[0x04];				//+CC
	DWORD32		clientId;				//+D0
	BYTE		uk10[0x0C];				//+D4
	Unit*		ptFirstMonster;			//+E0
	Unit*		Unit1;					//+E4
	Unit*		Unit2;					//+E8
	BYTE		uk11[0x08];				//+EC
	union{
		CBPlayerData*	ptCBPlayerData;
		CBItemData*		ptCBItemData;
		void*			ptCBData;
	};									//+F4
};
#pragma pack(pop)