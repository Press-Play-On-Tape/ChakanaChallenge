#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"

void play_Init() { 
    
    #ifndef DEBUG

        titleCounter = 0;
        world.setGameState(GameState::Play_BoatEnters);

    #else

        world.setGameState(GameState::Play_Game_Init);

    #endif

}

void play_Update() {

    #ifndef DEBUG

    uint8_t justPressed = getJustPressedButtons();

    world.incFrameCount();

    if (world.getFrameCount() % 4 == 0) {

        titleCounter++;

        if (titleCounter == 91 ) {
            world.setGameState(GameState::Play_Game_Init);
        }

    }

    if (justPressed & A_BUTTON) {

        world.setGameState(GameState::Play_Game_Init);

    }

    #endif
    
}


void play(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    #ifndef DEBUG

    Player &player = world.getPlayer();
    if (a.needsUpdate()) play_Update();

    SpritesU::drawOverwriteFX(0, 0, Images::BoatEnters, (titleCounter * 3) + currentPlane);    

    #endif

}
