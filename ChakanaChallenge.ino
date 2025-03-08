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
// #include "src/utils/SynthU.hpp"
#define ABG_TIMER1

// #include <stdio.h>
// #include <stdlib.h>

#ifndef DEBUG
ARDUBOY_NO_USB
#endif

uint8_t titleCounter = 0;
uint8_t currentPlane;
World world;
// Menu &menu = cookie.menu;

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
    world.setGameState(GameState::SplashScreen_Start);

}

void loop() {

    FX::enableOLED();

    a.waitForNextPlane(WHITE);
    FX::disableOLED();

    currentPlane = a.currentPlane();

    switch (world.getGameState()) {

        #ifndef DEBUG_NO_MAIN_MENU
            
            case GameState::SplashScreen_Start ... GameState::SplashScreen_End:
                splashScreen(a);
                break;


        
        #endif

    }

    #ifndef DEBUG_SOUND
    audioUpdate();
    #endif

}
