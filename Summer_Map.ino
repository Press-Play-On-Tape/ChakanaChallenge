#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"



void map_Init() {

    gameState = GameState::Map;
    frameCount = 0;

}

void map_Update() {

    uint8_t pressed = getPressedButtons();
    uint8_t justPressed = getJustPressedButtons();
    frameCount++;

    switch (gameState) {

        case GameState::Map:

            if (frameCount % 4 == 0) {

                if (justPressed & LEFT_BUTTON || pressed & LEFT_BUTTON) {

                    if (world.getXMap() > 0) world.incXMap(-4);

                }

                if (justPressed & RIGHT_BUTTON || pressed & RIGHT_BUTTON) {

                    if (world.getXMap() < 256) world.incXMap(4);

                }

                if (justPressed & DOWN_BUTTON || pressed & DOWN_BUTTON) {

                    if (world.getYMap() < 308) world.incYMap(4);

                }

                if (justPressed & UP_BUTTON || pressed & UP_BUTTON) {

                    if (world.getYMap() > 0) world.incYMap(-4);

                }

                

                
            }


            if (justPressed & A_BUTTON) {

                gameState = GameState::Map_ShowDialogue;
                frameCount = 0;

            }


            break;

        case GameState::Map_ShowDialogue:

            if (justPressed & A_BUTTON) {

                world.startBoat();
                gameState = GameState::Map_MoveBoat;
                frameCount = 0;

            }

            if (justPressed & B_BUTTON) {

                gameState = GameState::Map;
                frameCount = 0;

            }

            break;

        case GameState::Map_MoveBoat:

            if (frameCount % 2 == 0) {

                world.updateBoat();
                if (world.getBoatDirection() == 255) {
                    gameState = GameState::Play_Init;

                }

            }
            break;
            
        
    }

}

void map(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    if (a.needsUpdate()) map_Update();

    uint8_t currentPlane = a.currentPlane();

    uint8_t xInt = world.getXMap() / 128;
    int16_t xLeft = -(world.getXMap() - (xInt * 128));

    uint8_t yInt = world.getYMap() / 64;
    int16_t yTop = -(world.getYMap() - (yInt * 64));

    for (uint8_t i = 0; i < 3; i++) {

        SpritesU::drawOverwriteFX(xLeft, yTop + (i * 64), Images::Map, ((xInt + ((yInt + i) * 3)) * 3) + currentPlane);    
        SpritesU::drawOverwriteFX(xLeft + 128, yTop + (i * 64), Images::Map, (((xInt + 1) + ((yInt + i) * 3)) * 3) + currentPlane);    
        SpritesU::drawOverwriteFX(xLeft + 256, yTop + (i * 64), Images::Map, (((xInt + 2) + ((yInt + i) * 3)) * 3) + currentPlane);    

    }

    if (frameCount % 36 < 18) {

        for (uint8_t i = 0; i < 14; i++) {

            FX::seekData(Constants::mapCoords + (i * 4));
            // uint16_t x = FX::readPendingUInt16();
            // uint16_t y = FX::readPendingUInt16();
            Point pt;
            FX::readObject(pt);
            FX::readEnd();

            SpritesU::drawPlusMaskFX(pt.x - world.getXMap(), pt.y - world.getYMap(), Images::Beach, currentPlane);

        }

    }

    switch (gameState) {

        case GameState::Map:
            SpritesU::drawPlusMaskFX(world.getXBoat() - world.getXMap(), world.getYBoat() - world.getYMap(), Images::Boat_Small, currentPlane);
            break;

        case GameState::Map_ShowDialogue:
            SpritesU::drawPlusMaskFX(0, 0, Images::Scroll, currentPlane);
            break;

        case GameState::Map_MoveBoat:
            SpritesU::drawPlusMaskFX((world.getXBoat() / 2) - world.getXMap(), (world.getYBoat() / 2) - world.getYMap(), Images::Boat_Small, (world.getBoatDirection4() * 3) + currentPlane);
            break;
        
    }

}

