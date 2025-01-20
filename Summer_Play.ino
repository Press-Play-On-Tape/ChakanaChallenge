#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"

void play_Init() { 

    titleCounter = 0;
    world.setGameState(GameState::Play_BoatEnters);

}

void play_Update() {

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
    
}


void play(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    Player &player = world.getPlayer();
    if (a.needsUpdate()) play_Update();

    uint8_t currentPlane = a.currentPlane();

    SpritesU::drawOverwriteFX(0, 0, Images::BoatEnters, (titleCounter * 3) + currentPlane);    

}
