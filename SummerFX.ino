#define ABG_IMPLEMENTATION
#define ABG_TIMER1
#define ABG_SYNC_PARK_ROW
#define SPRITESU_IMPLEMENTATION

#include <ArduboyFX.h>  
#include <FixedPointsCommon.h>
#include "src/utils/ArduboyG.h"
#include "src/utils/Enums.h"
#include "src/utils/Constants.h"
#include "fxdata/fxdata.h"
#include "fxdata/images/Images.h"
#include "src/entities/Entities.h"
#include "src/utils/Stack.h"

#define SPRITESU_OVERWRITE
#define SPRITESU_PLUSMASK
#define SPRITESU_RECT
#define SPRITESU_FX

#include "src/utils/SpritesU.hpp"

extern ArduboyGBase_Config<ABG_Mode::L4_Triplane> a;
decltype(a) a;

#define SYNTHU_IMPLEMENTATION
#define SYNTHU_NUM_CHANNELS 4
#define SYNTHU_UPDATE_EVERY_N_FRAMES 3
#define SYNTHU_ENABLE_SFX 1
#define SYNTHU_FX_READDATABYTES_FUNC FX::readDataBytes
#include "src/utils/SynthU.hpp"
#define ABG_TIMER1

#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
ARDUBOY_NO_USB
#endif

Cookie cookie;
SoundSettings &soundSettings = cookie.soundSettings;
uint8_t titleCounter = 0;

World &world = cookie.world;
Menu menu;

Stance stanceOld = Stance::Man_Walk_RH_01;

#ifdef DEBUG_FIXED_RAND
uint16_t seed = 72;
#endif

// Stack <Stance, Constants::StackSize> playerStack;
// Stack <Stance, Constants::StackSize> enemyStack[Constants::EnemyCount];


void setup() {

    a.boot();
    a.startGray();
    
    FX::begin(FX_DATA_PAGE, FX_SAVE_PAGE);
    FX::loadGameState((uint8_t*)&cookie, sizeof(cookie));

    #ifndef DEBUG_SOUND
    audioInit();
    setAudioOn();
    #endif

    // world.getPlayer().setStack(&playerStack);

    // for (uint8_t i = 0; i < Constants::EnemyCount; i++) {
    //     world.getEnemy(i).setStack(&enemyStack[i]);
    // }

}

void loop() {

    FX::enableOLED();

    switch (world.getGameState()) {

        case GameState::PlayGame:
        case GameState::Inventory_Open:
        case GameState::Inventory_Open_Exit_0:
        case GameState::Inventory_Open_Exit_1:
        case GameState::Inventory_Open_Reset_0:
        case GameState::Inventory_Open_Reset_1:
        case GameState::Inventory_Open_Reset_Exit_0:
        case GameState::Inventory_Open_Reset_Exit_1:
        case GameState::Chakana_Open:
        case GameState::Play_Battle:
            a.waitForNextPlane(WHITE);
            break;

        default:
            a.waitForNextPlane(BLACK);
            break;
        
    }
    
    FX::disableOLED();

    Player &player = world.getPlayer();

    if (player.getStance() != stanceOld) {
        printDetails();
        stanceOld = player.getStance();

    }

    switch (world.getGameState()) {

        case GameState::SplashScreen_Start ... GameState::SplashScreen_End:
            splashScreen(a);
            break;

        case GameState::Title_Init:
            title_Init();
            [[fallthrough]];

        case GameState::Title_Start ... GameState::Title_End:
            title(a);
            break;

        case GameState::Play_Init:
            play_Init();
            [[fallthrough]];

        case GameState::Play:
        case GameState::Play_BoatEnters:
        case GameState::Play_PlayerJumps:
        case GameState::Play_PlayerCenters:
            play(a);
            break;

        case GameState::PlayGame_Init:
            playGame_Init();
            [[fallthrough]];

        case GameState::PlayGame:
        case GameState::Inventory_Open:
        case GameState::Inventory_Open_Exit_0:
        case GameState::Inventory_Open_Exit_1:
        case GameState::Inventory_Open_Reset_0:
        case GameState::Inventory_Open_Reset_1:
        case GameState::Inventory_Open_Reset_Exit_0:
        case GameState::Inventory_Open_Reset_Exit_1:
        case GameState::Chakana_Open:
        case GameState::Play_Battle:
            playGame(a);
            break;

        case GameState::Map_Init:
            map_Init();
            [[fallthrough]];

        case GameState::Map:
        case GameState::Map_ShowDialogue:
        case GameState::Map_MoveBoat:
            map(a);
            break;

    }

    #ifndef DEBUG_SOUND
    audioUpdate();
    #endif

}


void printDetails() {
    
    Player &player = world.getPlayer();

// for(uint8_t i = 0; i < 8;i++) {
//     Serial.print(world.getPalm(i));
//     Serial.print(" ");
// };
// Serial.println("");
// Serial.print(world.getWave());
//     Serial.print(" ");
// Serial.print(world.getBackground());
//     Serial.print(" ");
// Serial.println(world.getMiddleground());
// Serial.println(world.get);

    // DEBUG_PRINT("S");
    // DEBUG_PRINT(player.getStance());
    // DEBUG_PRINT(" y");
    // DEBUG_PRINT(Constants::GroundY - player.getY());
    // DEBUG_PRINT(" (");
    // DEBUG_PRINT((Constants::GroundY - player.getY()) % 8);
    // DEBUG_PRINT(") M");
    // DEBUG_PRINT(world.getMiddleground());
    // DEBUG_PRINT(" (");
    // DEBUG_PRINT(world.getMiddleground() % 8);
    // DEBUG_PRINT(")");
    // DEBUG_PRINTLN(" ");


    // DEBUG_PRINT("S");
    // DEBUG_PRINT(player.getStance());
    // DEBUG_PRINT(" X");
    // DEBUG_PRINT(world.getX());
    // DEBUG_PRINT(" y");
    // DEBUG_PRINT(Constants::GroundY - player.getY());
    // DEBUG_PRINT(" (");
    // DEBUG_PRINT((Constants::GroundY - player.getY()) % 8);
    // DEBUG_PRINT(") B");
    // DEBUG_PRINT(world.getBackground());
    // DEBUG_PRINT(" M");
    // DEBUG_PRINT(world.getMiddleground());
    // DEBUG_PRINT(" (");
    // DEBUG_PRINT(world.getMiddleground() % 8);
    // DEBUG_PRINT(") D");
    // DEBUG_PRINT((uint8_t)player.getDirection());
    // DEBUG_PRINT(" 1) ");
    // DEBUG_PRINT(world.getTile_RelativeToPlayer(-2, 1));
    // DEBUG_PRINT(" ");
    // DEBUG_PRINT(world.getTile_RelativeToPlayer(-1, 1));
    // DEBUG_PRINT(" ");
    // DEBUG_PRINT(world.getTile_RelativeToPlayer(0, 1));
    // DEBUG_PRINT(" ");
    // DEBUG_PRINT(world.getTile_RelativeToPlayer(1, 1));
    // DEBUG_PRINT(" ");
    // DEBUG_PRINT(world.getTile_RelativeToPlayer(2, 1));
    // DEBUG_PRINT(" - 0) ");
    // DEBUG_PRINT(world.getTile_RelativeToPlayer(-2, 0));
    // DEBUG_PRINT(" ");
    // DEBUG_PRINT(world.getTile_RelativeToPlayer(-1, 0));
    // DEBUG_PRINT(" ");
    // DEBUG_PRINT(world.getTile_RelativeToPlayer(0, 0));
    // DEBUG_PRINT(" ");
    // DEBUG_PRINT(world.getTile_RelativeToPlayer(1, 0));
    // DEBUG_PRINT(" ");
    // DEBUG_PRINT(world.getTile_RelativeToPlayer(2, 0));
    // DEBUG_PRINT(" - -1) ");
    // DEBUG_PRINT(world.getTile_RelativeToPlayer(-2, -1));
    // DEBUG_PRINT(" ");
    // DEBUG_PRINT(world.getTile_RelativeToPlayer(-1, -1));
    // DEBUG_PRINT(" ");
    // DEBUG_PRINT(world.getTile_RelativeToPlayer(0, -1));
    // DEBUG_PRINT(" ");
    // DEBUG_PRINT(world.getTile_RelativeToPlayer(1, -1));
    // DEBUG_PRINT(" ");
    // DEBUG_PRINT(world.getTile_RelativeToPlayer(2, -1));
    // DEBUG_PRINTLN(" ");


    // if (player.isEmpty()) {

    //     if ((Constants::GroundY - player.getY()) % 8 != 0 || (world.getMiddleground() % 8 != 0)) {

    //         DEBUG_BREAK

    //     }

    // }
    
}
