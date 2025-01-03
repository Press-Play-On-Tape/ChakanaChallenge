#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"

void title_Init() {

    if (!cookie.hasSavedGame) {
        world.setGameState(GameState::Title_Start);
    }
    else {
        world.setGameState(GameState::Title_OptResume);
    }

}

void title_Update() {

    world.incFrameCount();

    uint8_t justPressed = getJustPressedButtons();
    uint8_t pressed = getPressedButtons();

    switch (world.getGameState()) {

        case GameState::Title_ShowCredits:

            if (justPressed & B_BUTTON || justPressed & A_BUTTON) {

                world.setGameState(GameState::Title_OptCredits);

            }

            break;
        
        case GameState::Title_Start:

            if (justPressed & A_BUTTON) {

                world.setGameState(GameState::Title_OptPlay);

            }

            break;

        case GameState::Title_OptPlay:

            if (justPressed & DOWN_BUTTON) {
                world.setGameState(GameState::Title_OptSound);
            }

            if (justPressed & A_BUTTON) {
                
                cookie.hasSavedGame = false;
                saveCookie(true);
                // prevGameState = GameState::Title_OptPlay;
                // world.setGameState(GameState::Play_Init);
                // world.setGameState(GameState::Map_Init);
                world.setGameState(GameState::PlayGame_Init);

            }

            break;
        
        case GameState::Title_OptResume:

            if (justPressed & DOWN_BUTTON) {
                world.setGameState(GameState::Title_OptPlay2);
            }

            if (justPressed & A_BUTTON) {

                world.setGameState(GameState::Play_Init);

            }

            break;
          
        case GameState::Title_OptPlay2:

            if (justPressed & UP_BUTTON) {
                world.setGameState(GameState::Title_OptResume);
            }

            if (justPressed & DOWN_BUTTON) {
                world.setGameState(GameState::Title_OptSound2);
            }

            if (justPressed & A_BUTTON) {

                cookie.hasSavedGame = false;
                saveCookie(true);
                world.setPrevGameState(GameState::Title_OptPlay2);
                world.setGameState(GameState::Play_Init);

            }

            break;

        case GameState::Title_OptSound:

            if (justPressed & UP_BUTTON) {
                world.setGameState(GameState::Title_OptPlay);
            }

            if (justPressed & DOWN_BUTTON) {
                world.setGameState(GameState::Title_OptCredits);
            }

            if (justPressed & A_BUTTON) {

                if (justPressed & A_BUTTON) {

                    soundSettings.setMusic(!soundSettings.getMusic());
                    if (soundSettings.getMusic()) {
                        playMusic();
                    }
                    else {
                        SynthU::stop();
                    }

                }

            }

            break;

        case GameState::Title_OptSound2:

            if (justPressed & UP_BUTTON) {
                world.setGameState(GameState::Title_OptPlay2);
            }

            if (justPressed & DOWN_BUTTON) {
                world.setGameState(GameState::Title_OptCredits);
            }

            if (justPressed & A_BUTTON) {

                if (justPressed & A_BUTTON) {

                    soundSettings.setMusic(!soundSettings.getMusic());
                    if (soundSettings.getMusic()) {
                        playMusic();
                    }
                    else {
                        SynthU::stop();
                    }

                }

            }

            break;
        
        case GameState::Title_OptCredits:

            if (justPressed & UP_BUTTON) {
                world.setGameState(GameState::Title_OptSound);
            }

            if (justPressed & A_BUTTON) {
                world.setGameState(GameState::Title_ShowCredits);
            }

            break;
        
    }

    if (titleCounter < 72) titleCounter++;

}

void title(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {
    
    if (a.needsUpdate()) title_Update();

    uint8_t currentPlane = a.currentPlane();

    switch (world.getGameState()) {

        case GameState::Title_Start:
            SpritesU::drawOverwriteFX(0, 0, Images::Title_Base, currentPlane);
            break;

        case GameState::Title_OptPlay ... GameState::Title_OptSound_Volume2:
            SpritesU::drawOverwriteFX(0, 0, Images::Title_Base, 3 + currentPlane);
            SpritesU::drawPlusMaskFX(64, 36, Images::Title_Options, (3 * (static_cast<uint8_t>(world.getGameState()) - static_cast<uint8_t>(GameState::Title_OptPlay))) + ((soundSettings.getMusic() ? 0 : 6) * 3)  + currentPlane);
            break;

        case GameState::Title_ShowCredits:
            SpritesU::drawOverwriteFX(0, 0, Images::Title_Base, (2 * 3) + currentPlane);
            break;

    }

    SpritesU::drawPlusMaskFX(20, 22, Images::Chakana, (((world.getFrameCount() / 8) % 12) * 3) + currentPlane);

}
