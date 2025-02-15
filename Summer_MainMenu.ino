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

void title_StartNewGame() {

    world.init();
    world.getPlayer().init();
    cookie.hasSavedGame = false;
    saveCookie(true);
    world.setGameState(GameState::Map_Init);

}

void title_SaveSoundSettings() {
    
    soundSettings.setMusic(!soundSettings.getMusic());
    if (soundSettings.getMusic()) {
        playMusic();
    }
    else {
        SynthU::stop();
    }

}
void title_Update() {

    world.incFrameCount();

    uint8_t justPressed = getJustPressedButtons();

    if (justPressed & A_BUTTON) {

        switch (world.getGameState()) {

            case GameState::Title_Start:

                world.setGameState(GameState::Title_OptPlay);
                break;

            case GameState::Title_OptPlay:
            case GameState::Title_OptPlay2:

                title_StartNewGame();
                break;

            case GameState::Title_ShowCredits:

                world.setGameState(GameState::Title_OptCredits);
                break;

            case GameState::Title_OptResume:

                FX::loadGameState((uint8_t*)&cookie, sizeof(cookie));
                menu.setX(128);
                break;

            case GameState::Title_OptSound:
            case GameState::Title_OptSound2:

                title_SaveSoundSettings();
                break;
                
            case GameState::Title_OptCredits:

                world.setGameState(GameState::Title_ShowCredits);
                break;

        }

    }
    else if (justPressed & DOWN_BUTTON) {

        switch (world.getGameState()) {

            case GameState::Title_OptPlay:
            case GameState::Title_OptPlay2:
            case GameState::Title_OptResume:
            case GameState::Title_OptSound:

                world.incGameState();
                break;

            case GameState::Title_OptSound2:

                world.setGameState(GameState::Title_OptCredits);
                break;

        }

    }
    else if (justPressed & UP_BUTTON) {

        switch (world.getGameState()) { 

            case GameState::Title_OptPlay2:
            case GameState::Title_OptSound:
            case GameState::Title_OptSound2:
            case GameState::Title_OptCredits:

                world.decGameState();
                break;

        }

    }

    if (titleCounter < 72) titleCounter++;

}

void title(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    uint8_t frame = 0;

    if (a.needsUpdate()) title_Update();

    currentPlane = a.currentPlane();

    #ifndef DEBUG

        switch (world.getGameState()) {

            case GameState::Title_OptPlay ... GameState::Title_OptSound_Volume2:

                frame = 1;
                break;

            case GameState::Title_ShowCredits:

                frame = 2;
                break;

        }

    #endif

    SpritesU::drawOverwriteFX(0, 0, Images::Title_Base, (3 * frame) + currentPlane);


    // Render Options ?

    if (frame == 1) {

        frame = (static_cast<uint8_t>(world.getGameState()) - static_cast<uint8_t>(GameState::Title_OptPlay)) + (soundSettings.getMusic() ? 0 : 6);
        SpritesU::drawPlusMaskFX(64, 36, Images::Title_Options, (3 * frame) + currentPlane);

    }

    SpritesU::drawPlusMaskFX(20, 22, Images::Chakana, (((world.getFrameCount() / 4) % 20) * 3) + currentPlane);

}
