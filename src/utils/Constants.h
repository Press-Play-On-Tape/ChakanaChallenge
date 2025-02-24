#pragma once
#include "../../fxdata/fxdata.h"
#include "../../fxdata/images/Images.h"

#define DEBUG_PRINT    Serial.print
#define DEBUG_PRINTLN  Serial.println
#define DEBUG_BREAK    asm volatile("break\n");

#define _DEBUG
#define _DEBUG_SOUND
#define _DEBUG_DISABLE_PLAY
#define _DEBUG_HANDLE_MENUS
#define _DEBUG_LOCKED_DOOR
#define _DEBUG_RENDER_MAP
#define _DEBUG_SWORD
#define _DEBUG_NO_MENU
#define DEBUG_LOTS_OF_CHAKANAS


#ifdef DEBUG

    #define FALL_THROUGH_PORTAL

#else

	// Want to Keep !

	// 142 bytes
	#define MAP_SHOW_PORT_NAMES

	// 136 bytes
	#define MAP_SHOW_PORTS_VISITED

	// 216 bytes
	#define TRAP_DOOR

	// 208 bytes
	#define FALL_THROUGH_PORTAL

	// 242 bytes
	#define MULTIPLE_ITEMS

	// 102 bytes
	#define SHOW_SIGN

	// 46 Bytes
	#define RENDER_16X16

	// Not fussed!

	// 120 bytes
	#define _BOUNCEJUMP_3

	// 64 Bytes
	#define _RENDER_16X16_SECONDARY

#endif

#define AB_BUTTON 12

enum Tiles : uint8_t {

	Blank = 0,
	Solid_Walkable = 1,
	Solid_NonWalkable = 2,
	Solid_Blocking = 18,

	// --------------------------------------------------------------------------------------------
	/* Basic Shapes

	01, 01, 
	02, 02, 

	********   ********   
	********   ********   
	********   ********   
	********   ********  

	********   ********   
	********   ********   
	********   ********   
	********   ********      


	01, 00, 
	02, 00, 

	********   ........   
	********   ........   
	********   ........   
	********   ........  

	********   ........   
	********   ........   
	********   ........   
	********   ........      


	00, 01, 
	00, 02, 

	........   ********   
	........   ********   
	........   ********   
	........   ********  

	........   ********   
	........   ********   
	........   ********   
	........   ********      

	00, 00, 
	01, 01, 

	........   ........ 
	........   ........ 
	........   ........ 
	........   ........

	********   ********   
	********   ********   
	********   ********   
	********   ********      

	18, 18,   // You cannot walk past it.
	18, 18, 

	********   ********   
	.*******   *******.   
	********   ********   
	.*******   *******.  

	********   ********   
	.*******   *******.   
	********   ********   
	.*******   *******.      



	// --------------------------------------------------------------------------------------------
	/* Single Stair RH Upper

	04, 05, 
	02, 01, 

	........   ...*****   
	........   ...*****   
	......**   ********   
	......**   ********   

	********   ********   
	********   ********   
	********   ********   
	********   ********   

	*/
	Single_Stair_RH_Upper_TL = 4,
	Single_Stair_RH_Upper_TR = 5,

	/* Single Stair RH Lower

	00, 00, 
	00, 06, 

	........   ........ 
	........   ........ 
	........   ........ 
	........   ........ 

	........   ....****
	........   ....****
	........   ********
	........   ********

	*/
	Single_Stair_RH_Lower = 6,

	/* Single Stair LH Upper

	09, 10, 
	02, 01, 

	*****...   ........   
	*****...   ........   
	********   **......   
	********   **......   

	********   ********   
	********   ********   
	********   ********   
	********   ********   

	*/
	Single_Stair_LH_Upper_TL = 9,
	Single_Stair_LH_Upper_TR = 10,

	/* Single Stair LH Lower

	00, 00, 
	11, 00, 

	........   ........ 
	........   ........ 
	........   ........ 
	........   ........ 

	****....   ........   
	****....   ........   
	********   ........   
	********   ........   

	*/
	Single_Stair_LH_Lower = 11,


	// --------------------------------------------------------------------------------------------
	/* Ladders

	7 is steps lower.
	8 is steps upper.
	12 is steps middle    

	Ladder Single Level

	08, 08,
	07, 07,

	Ladder Two Level

	08, 08,
	12, 12,
	12, 12,
	07, 07,

	Ladder Three Level

	08, 08,
	12, 12,
	12, 12,
	12, 12,
	12, 12,
	07, 07,

	*/

	Ladder_Lower = 7,
	Ladder_Upper = 8,
	Ladder_Middle = 12,


	// --------------------------------------------------------------------------------------------
	/* Vines

	31 is vine middle.
	32 is vine bottom.
	33 is steps top    
		
	Vine Two Level

	33, 33,
	31, 31,
	31, 31,
	32, 32,

	Vine Three Level

	33, 33,
	31, 31,
	31, 31,
	31, 31,
	31, 31,
	32, 32,

	*/

	Vine_Lower = 32,
	Vine_Upper = 33,
	Vine_Middle = 31,


	/* Swinging Vine


	Typical:

	00, 00,   00, 00,   00, 00,   00, 00,   00, 00, 
	00, 00,   29, 00,   00, 00,   00, 30,   00, 00,

	01, 01,   00, 00,   00, 00,   00, 00,   01, 01,
	02, 02,   00, 00,   00, 00,   00, 00,   02, 02, 

	No image, place ItemType::Swinging_Vine in same location.
	*/

	Swinging_Vine_LH = 29,
	Swinging_Vine_RH = 30,



	// --------------------------------------------------------------------------------------------
	/* Ropes

	13 is rope support LH.
	14 is rope support RH.
	15 is rope.

	16 Spring LH
	17 Spring LH


	Typical Layout

	13, 15,    15, 15,    15, 14,
	13, 00,    00, 00,    00, 14, 

	*/

	Rope_Support_LH = 13,
	Rope_Support_RH = 14,
	Rope = 15,

	/* Spring LH

	16, 00, 
	01, 01, 

	*/
	Spring_LH = 16,


	/* Spring LH

	00, 17, 
	01, 01, 

	*/
	Spring_RH = 17,


	// --------------------------------------------------------------------------------------------
	/*  Slide LH Upper

	19, 00,
	02, 00, 

	**         ........
	****       ........
	******     ........
	********   ........

	********   ........
	********   ........
	********   ........
	********   ........

	OR

	01, 19,
	02, 02,

	********   **     
	********   ****    
	********   ******    
	********   ********  

	********   ********   
	********   ********   
	********   ********   
	********   ********   


	*/
	Slide_LH_Upper = 19,

	/* Slide LH Full

	20, 00,
	02, 20, 

	**         ........
	****       ........
	******     ........
	********   ........

	********   ........
	********   **......
	********   ****....
	********   ******..

	*/
	Slide_LH_Full = 20,

	/* Slide RH Upper

	00, 21,
	00, 02, 

	........         **
	........       ****
	........     ******
	........   ********   

	........   ********
	........   ********
	........   ********
	........   ********

	OR

	21, 01,
	02, 02,

	      **   ********
		****   ********
      ******   ********
	********   ********   

	********   ********
	********   ********
	********   ********
	********   ******** 


	*/
	Slide_RH_Upper = 21,

	/* Slide RH Full

	00, 22,
	22, 02, 

	........         **
	........       ****
	........     ******
	........   ********  

	......**   ********
	....****   ********
	..******   ********
	********   ******** 

	*/
	Slide_RH_Full = 22,


	// --------------------------------------------------------------------------------------------

	/* Spikes

	00, 00,
	03, 03, 

	........   ........
	........   ........
	........   ........
	........   ........

	..*....*   ...*....
	..*....*   ...*....
	.***..**   *.***...
	********   ********

	OR

	03, 03, 
	02, 02, 

	..*....*   ...*....
	..*....*   ...*....
	.***..**   *.***...
	********   ********

	********   ********
	********   ********
	********   ********
	********   ******** 

	*/
	Spikes = 3,

	/* Lever Portal

	34, 35,
	34, 35,

	No image, place ItemType::Lever_Portal_Closed or ItemType::Lever_Portal_Open in same location.

	*/
	Lever_Portal_LH = 34,
	Lever_Portal_RH = 35,


	/* Lever Portal Auto Close

	36, 37,
	36, 37,

	No image, place ItemType::Lever_Portal_Auto_Closed or ItemType::Lever_Portal_Auto_Open in same location.

	*/
	Lever_Portal_Auto_LH = 36,
	Lever_Portal_Auto_RH = 37,


	/* Punji Pit

	00, 00, 
	23, 23,

	No image, place ItemType::Punji in same location.

	*/
	Punji = 23,


	/* Wooden Barrier

	24, 24, 
	24, 24,

	No image, place ItemType::WoodenBarrier in same location.

	*/
	WoodenBarrier = 24,


	/* Water

	38 Plain Water
	39 Bubbling Water 1
	40 Bubbling Water 1

	39, 39,   38, 38,   40, 40, 
	39, 39,   38, 38,   40, 40,

	*/
	Water_Plain = 38,
	Water_Bubbling_1 = 39,
	Water_Bubbling_2 = 40,


	/* Mystery Crate

	25, 25,
	25, 25,

	No image, place ItemType::MysteryCrate in same location.

	*/
	Mystery_Crate = 25,

	/* Locked Door

	26, 26,
	26, 26,

	No image, place ItemType::LockedDoor in same location.

	*/
	LockedDoor = 26,


	/* Rollers Right

	0,  0,
	27, 27,

	or

	27, 27, 
	2,  2,

	*/
	Rollers_Right = 27,


	/* Rollers Left

	0,  0,
	28, 28,

	or

	28, 28, 
	2,  2,

	*/
	Rollers_Left = 28,

	/* Poker

	41, 41,
	41, 41,

	*/
	Poker = 41,


	Decorative_Triangle_LH = 42,
	Decorative_Triangle_RH = 43,

	Trebochet_To_RH = 46,
	Trebochet_To_LH = 47,

	Weed = 48,
	Block_WithWeed = 49,
	Block_WithWeed_LH = 50,
	Block_WithWeed_RH = 51,
	Sign_01 = 52,
	Flame = 53,

};


namespace Constants {

    #ifdef DEBUG
    constexpr uint8_t Map_X_Count_Full = 50;
    constexpr uint8_t Map_X_Count = 24;
    constexpr uint8_t Map_Y_Count = 16;
    #else
    constexpr uint8_t Map_X_Count_Full = 50;
    constexpr uint8_t Map_X_Count = 50;
    constexpr uint8_t Map_Y_Count = 16;
    #endif

    constexpr uint8_t NoPlayer = 255;
    constexpr uint8_t NoItem = 255;
    constexpr uint8_t NoDirection = 255;
    constexpr uint16_t NoWaves = 29999;
    constexpr uint8_t NoEnemy = 255;
    constexpr uint8_t NoPort = 255;
    constexpr int8_t NoOffset = 100;

    constexpr uint8_t HealthMax = 14;
    constexpr uint8_t NoOfPorts = 14;

    constexpr uint8_t EnemyCount = 4;
    constexpr uint8_t ItemCount_Level = 15;
    constexpr uint8_t ItemCount_Player = 5;

    constexpr uint8_t StackSize_Enemy = 14;
    constexpr uint8_t StackSize_Player = 35;

    constexpr uint8_t GroundY = 37;
    constexpr uint8_t Puff_Max = 7 * 16;
    constexpr uint8_t Glint_Max = 8;

    constexpr uint8_t GamblePanel_Win = 11;
    constexpr uint8_t GamblePanel_Lose = 9;
    constexpr uint16_t AllPortsComplete = 16383;

};


