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
#include "src/utils/Random.h"
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

#include "src/fonts/Font3x5.h"

#include <stdio.h>
#include <stdlib.h>
#include "time.h"

Cookie cookie;
Game &game = cookie.game;
SoundSettings &soundSettings = cookie.soundSettings;
GameState gameState = GameState::SplashScreen_Start;
GameState prevGameState = GameState::SplashScreen_Start;
uint16_t frameCount = 0;
uint8_t titleCounter = 0;

uint8_t optionsMenuIdx = 0;
uint8_t optionsTopMenuIdx = 2;
uint8_t optionsStartingBalance = 0;
uint8_t pauseMenu = 0;
Font3x5 font3x5 = Font3x5();

int8_t curPlayerIdx = -1;
uint16_t bButton = 0;
uint16_t raiseBy = 50;
uint8_t pressCount = 0;
World world;


Stance stanceOld = Stance::Man_Walk_RH_01;
// Stance stance = Stance::Man_Walk_RH_01;

#ifdef DEBUG_FIXED_RAND
uint16_t seed = 72;
#endif

Stack <Stance, Constants::StackSize> princeStack;


void setup() {

    a.boot();
    a.startGray();
    
    FX::begin(FX_DATA_PAGE, FX_SAVE_PAGE);
    FX::loadGameState((uint8_t*)&cookie, sizeof(cookie));
    #ifndef DEBUG_SOUND
    audioInit();
    setAudioOn();
    #endif

    world.getPlayer().setStack(&princeStack);

}

void loop() {

    FX::enableOLED();
    a.waitForNextPlane(BLACK);
    FX::disableOLED();

    Player &player = world.getPlayer();

    #ifdef DEBUG

        font3x5.setCursor(0, 0);
        font3x5.print((uint8_t)gameState);

    #endif

    if (player.getStance() != stanceOld) {
        printDetails();
        stanceOld = player.getStance();

    }
    switch (gameState) {

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

    DEBUG_PRINT("S");
    DEBUG_PRINT(player.getStance());
    DEBUG_PRINT(" X");
    DEBUG_PRINT(world.getX());
    DEBUG_PRINT(" y");
    DEBUG_PRINT(Constants::GroundY - player.getY());
    DEBUG_PRINT(" (");
    DEBUG_PRINT((Constants::GroundY - player.getY()) % 8);
    DEBUG_PRINT(") B");
    DEBUG_PRINT(world.getBackground());
    DEBUG_PRINT(" M");
    DEBUG_PRINT(world.getMiddleground());
    DEBUG_PRINT(" (");
    DEBUG_PRINT(world.getMiddleground() % 8);
    DEBUG_PRINT(") D");
    DEBUG_PRINT((uint8_t)player.getDirection());
    DEBUG_PRINT(" 1) ");
    DEBUG_PRINT(world.getTile_RelativeToPlayer(-2, 1));
    DEBUG_PRINT(" ");
    DEBUG_PRINT(world.getTile_RelativeToPlayer(-1, 1));
    DEBUG_PRINT(" ");
    DEBUG_PRINT(world.getTile_RelativeToPlayer(0, 1));
    DEBUG_PRINT(" ");
    DEBUG_PRINT(world.getTile_RelativeToPlayer(1, 1));
    DEBUG_PRINT(" ");
    DEBUG_PRINT(world.getTile_RelativeToPlayer(2, 1));
    DEBUG_PRINT(" - 0) ");
    DEBUG_PRINT(world.getTile_RelativeToPlayer(-2, 0));
    DEBUG_PRINT(" ");
    DEBUG_PRINT(world.getTile_RelativeToPlayer(-1, 0));
    DEBUG_PRINT(" ");
    DEBUG_PRINT(world.getTile_RelativeToPlayer(0, 0));
    DEBUG_PRINT(" ");
    DEBUG_PRINT(world.getTile_RelativeToPlayer(1, 0));
    DEBUG_PRINT(" ");
    DEBUG_PRINT(world.getTile_RelativeToPlayer(2, 0));
    DEBUG_PRINT(" - -1) ");
    DEBUG_PRINT(world.getTile_RelativeToPlayer(-2, -1));
    DEBUG_PRINT(" ");
    DEBUG_PRINT(world.getTile_RelativeToPlayer(-1, -1));
    DEBUG_PRINT(" ");
    DEBUG_PRINT(world.getTile_RelativeToPlayer(0, -1));
    DEBUG_PRINT(" ");
    DEBUG_PRINT(world.getTile_RelativeToPlayer(1, -1));
    DEBUG_PRINT(" ");
    DEBUG_PRINT(world.getTile_RelativeToPlayer(2, -1));
    DEBUG_PRINTLN(" ");
}