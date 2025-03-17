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

    #ifdef DEBUG
    cookie.hasPlayedBefore = 1;
    #endif
}

void title_StartNewGame() {

    world.init();
    world.getPlayer().init();
    cookie.hasSavedGame = false;

    uint8_t i = static_cast<uint8_t>(world.getGameState()) - static_cast<uint8_t>(GameState::Title_Port_01);

    FX::seekData(Constants::Starting_Ports + (i * 6));
    world.setCurrentPort(FX::readPendingUInt16());
    world.setXMap(FX::readPendingUInt16());
    world.setYMap(FX::readPendingUInt16());
    FX::readEnd();

    world.getPlayer().setChakanas(i == 0 ? 20 : 25); 
    #ifdef DEBUG_LOTS_OF_CHAKANAS
    world.getPlayer().setChakanas(200); 
    #endif

    #ifndef DEBUG
    saveCookie();
    #endif
    
    world.setGameState(GameState::Map_Init);

}

void title_SaveSoundSettings() {
    
    #ifndef SOUND_SIMPLE

        soundSettings.setSounds(!soundSettings.getSounds());
        
        if (soundSettings.getSounds()) {
            playMusic();
        }
        else {
            SynthU::stop();
        }
        
    #else

        if (!soundSettings.getMusic() && !soundSettings.getSFX()) {

            soundSettings.setMusic(true);
            soundSettings.setSFX(true);

        }
        else if (!soundSettings.getMusic() && soundSettings.getSFX()) {

            soundSettings.setMusic(false);
            soundSettings.setSFX(false);

        }
        else if (soundSettings.getMusic() && soundSettings.getSFX()) {

            soundSettings.setMusic(false);
            soundSettings.setSFX(true);

        }
    
        if (soundSettings.getMusic()) {
            playMusic();
        }
        else {
            SynthU::stop();
        }

    #endif

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
                world.setGameState(GameState::Title_Intro_00);
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
                
            case GameState::Title_Intro_00:
            case GameState::Title_Intro_01:
            case GameState::Title_Intro_02:
                world.incGameState();
                break;

            case GameState::Title_Intro_03:
            
                world.setGameState(GameState::Title_Port_01);
                if (!cookie.hasPlayedBefore) {
                    title_StartNewGame();
                }
                break;

            case GameState::Title_Port_01 ... GameState::Title_Port_04:
                title_StartNewGame();
                break;

            default: break;

        }

    }
    else if (justPressed & B_BUTTON) {

        switch (world.getGameState()) {

            case GameState::Title_Intro_00:
            case GameState::Title_Intro_01:
            case GameState::Title_Intro_02:

                world.setGameState(GameState::Title_Port_01);
                if (!cookie.hasPlayedBefore) {
                    title_StartNewGame();
                }

                break;

            default: break;

        }

    }
    else if (justPressed & DOWN_BUTTON) {

        switch (world.getGameState()) {

            case GameState::Title_OptPlay:
            case GameState::Title_OptPlay2:
            case GameState::Title_OptResume:
            case GameState::Title_OptSound:
            case GameState::Title_Port_01:
            case GameState::Title_Port_02:
            case GameState::Title_Port_03:
                world.incGameState();
                break;

            default: break;

        }

    }
    else if (justPressed & UP_BUTTON) {

        switch (world.getGameState()) { 

            case GameState::Title_OptPlay2:
            case GameState::Title_OptSound:
            case GameState::Title_OptSound2:
            case GameState::Title_OptCredits:
            case GameState::Title_Port_02:
            case GameState::Title_Port_03:
            case GameState::Title_Port_04:

                world.decGameState();
                break;

            default: break;

        }

    }

    if (titleCounter < 72) titleCounter++;

}

void title(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    uint8_t frame = static_cast<uint8_t>(world.getGameState()) - static_cast<uint8_t>(GameState::Title_Start);

    #ifndef SOUND_SIMPLE
        
        if (world.getGameState() > GameState::Title_ShowCredits) {
            frame = frame + (soundSettings.getSounds() ? 0 : 6);
        }

        if (a.needsUpdate()) title_Update();

        SpritesU::drawOverwriteFX(0, 0, Images::Title_Base, (3 * frame) + currentPlane);
        SpritesU::drawPlusMaskFX(20, 22, Images::Chakana, (((world.getFrameCount() / 4) % 20) * 3) + currentPlane);

    #else

        switch (world.getGameState()) {

            case GameState::Title_ShowCredits ... GameState::Title_ShowCredits_Alt:
                frame = 1;
                break;

            case GameState::Title_OptPlay ... GameState::Title_OptSound_Volume2:

                if (!soundSettings.getMusic() && !soundSettings.getSFX()) {
                    frame = frame + (soundSettings.getMusic() ? 0 : 6);
                }
                else if (!soundSettings.getMusic() && soundSettings.getSFX()) {
                    frame = frame + (soundSettings.getMusic() ? 0 : 12);
                }

                break;

            case GameState::Title_Port_01 ... GameState::Title_Port_04:
            case GameState::Title_Intro_00 ... GameState::Title_Intro_03:
                
                frame = frame + 6;
                break;

            default: break;

        }

        if (a.needsUpdate()) title_Update();

        SpritesU::drawOverwriteFX(0, 0, Images::Title_Base, (3 * frame) + currentPlane);

        switch (world.getGameState()) {
    
            case GameState::Title_Intro_00 ... GameState::Title_Intro_03:
                break;

            default:
                SpritesU::drawPlusMaskFX(20, 22, Images::Chakana, (((world.getFrameCount() / 4) % 20) * 3) + currentPlane);
                break;

        }

    #endif

}
