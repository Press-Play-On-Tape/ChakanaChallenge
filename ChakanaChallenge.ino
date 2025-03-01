#define ABG_IMPLEMENTATION
#define ABG_TIMER1
#define ABG_SYNC_PARK_ROW
#define SPRITESU_IMPLEMENTATION

#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
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
#define SYNTHU_NUM_CHANNELS 2
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
uint8_t currentPlane;
World &world = cookie.world;
Menu &menu = cookie.menu;

#ifdef DEBUG_FIXED_RAND
uint16_t seed = 72;
#endif

#ifdef DEBUG_SWORD
int8_t playerX;
int8_t playerY;
int8_t enemyX;
int8_t enemyY;
#endif


void setup() {

    a.boot();
    a.startGray();
    
    FX::begin(FX_DATA_PAGE, FX_SAVE_PAGE);
    FX::loadGameState((uint8_t*)&cookie, sizeof(cookie));
    world.setGameState(GameState::SplashScreen_Start);

    #ifndef DEBUG_SOUND
    audioInit();
    setAudioOn();
    #endif


    #ifdef DEBUG_NO_MENU
    world.init();
    world.getPlayer().init();
    world.setCurrentPort(0);
    world.setGameState(GameState::Play_Game_Init);
    cookie.hasSavedGame = false;    
    #endif
}

void loop() {

    FX::enableOLED();

    a.waitForNextPlane(WHITE);
    FX::disableOLED();

    Player &player = world.getPlayer();
    currentPlane = a.currentPlane();

    switch (world.getGameState()) {

        #ifndef DEBUG_NO_MENU
            
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

            case GameState::Play_BoatEnters:
            case GameState::Play_PlayerJumps:
            case GameState::Play_PlayerCenters:
            case GameState::Play:
                play(a);
                break;
        
        #endif

        case GameState::Play_Game_Init:
            playGame_Init();
            [[fallthrough]];

        case GameState::Play_Battle:
        case GameState::Play_Dead:
        case GameState::PlayGame_Start ... GameState::PlayGame_End:
        case GameState::Play_Gamble_Start ... GameState::Play_Gamble_End:
            playGame(a);
            break;

        #ifndef DEBUG_NO_MENU

            case GameState::Map_Init:
                map_Init();
                [[fallthrough]];

            case GameState::Map ... GameState::Map_MoveBoat:
                map(a);
                break;

        #endif

    }

    #ifndef DEBUG_SOUND
    audioUpdate();
    #endif

}
