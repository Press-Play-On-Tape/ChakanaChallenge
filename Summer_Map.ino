#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"

bool leftDialogue = false;

void map_Init() {

    world.setGameState(GameState::Map);
    world.setFrameCount(0);

}

void map_Update() {

    uint8_t pressed = getPressedButtons();
    uint8_t justPressed = getJustPressedButtons();
    world.incFrameCount();

    switch (world.getGameState()) {

        case GameState::Map_MoveBoat:

            if (world.getFrameCount() % 2 == 0) {

                world.updateBoat();

                if (world.getBoatDirection() == BoatDirection::None) {
                    world.setGameState(GameState::Play_Init);
                }

            }
            break;

        case GameState::Map:

            if (world.getFrameCount() % 4 == 0) {

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

                world.setNextPort(255);
                Point pt;

                FX::seekData(Constants::mapCoords);

                for (uint8_t i = 0; i < 14; i++) {
                    
                    FX::readObject(pt);

                    if (abs(pt.x - world.getXMap()) < 128 && abs(pt.y - world.getYMap()) < 64) {
// && world.getCurrentPort() != i
                        world.setNextPort(i);
                        break;

                    }

                }

                FX::readEnd();

                if (world.getNextPort() != 255) {

                    uint8_t from = world.getCurrentPort() == 255 ? 0 : world.getCurrentPort() + 1;
                    uint8_t toPort = world.getNextPort() + 1;

                    FX::seekData(Constants::PortCosts + (from * 15) + toPort);
                    world.setNextPortCost(FX::readPendingUInt8());
                    FX::readEnd();

                    world.setGameState(GameState::Map_ShowDialogue);
                    world.setFrameCount(0);

                    FX::seekDataArray(Constants::BeachDetails, world.getNextPort(), 0, 6);
                    uint16_t left = FX::readPendingUInt16();
                    FX::readEnd();

                    leftDialogue = (left == 0);

                }

            }

            if (justPressed & B_BUTTON) {
            
                Point pt = { 0, 0 };

                if (world.getCurrentPort() != 255) {

                    FX::seekDataArray(Constants::BeachDetails, world.getCurrentPort(), 0, 6);
                    FX::readObject(pt);
                    FX::readEnd();

                }
                
                world.setXMap(pt.x);
                world.setYMap(pt.y);

            }

            break;

        case GameState::Map_ShowDialogue:

            if (justPressed & A_BUTTON) {

                if (world.getChakanas() >= world.getNextPortCost() && world.getCurrentPort() != world.getNextPort()) {

                    world.setGameState(GameState::Map_MoveBoat);
                    world.setFrameCount(0);
                    world.setChakanas(world.getChakanas() - world.getNextPortCost());


                    // Swap port positions as we are about to move!

                    uint8_t port = world.getCurrentPort();
                    world.setCurrentPort(world.getNextPort());
                    world.setNextPort(port);


                    // Reposition boat ..

                    uint8_t offset = 0;

                    if (world.getCurrentPort() < 255 && world.getNextPort() < 255 && world.getCurrentPort() < world.getNextPort()) offset = 1;

                    #ifdef DEBUG_BOATS
                    DEBUG_PRINT("Position Boat ");
                    DEBUG_PRINT(world.getCurrentPort());
                    DEBUG_PRINT(" ");
                    DEBUG_PRINT(world.getNextPort());
                    DEBUG_PRINT(" ");
                    DEBUG_PRINTLN(offset? 1 : 0);
                    #endif

                    FX::seekDataArray(Constants::BoatCoords_Start, (world.getCurrentPort() * 2) + offset, 0, 4);
                    world.setXBoat(FX::readPendingUInt16());
                    world.setYBoat(FX::readPendingUInt16());
                    world.setBoatCounter(0);
                    world.setBoatDirection(BoatDirection::Left);
                    FX::readEnd();

                    #ifdef DEBUG_BOATS
                    DEBUG_PRINT(world.getXBoat());
                    DEBUG_PRINT(",");
                    DEBUG_PRINTLN(world.getYBoat());
                    #endif
                    
                }
                else {

                    world.setGameState(GameState::Map);
                    world.setFrameCount(0);

                }

            }

            else if (justPressed & B_BUTTON) {

                world.setGameState(GameState::Map);
                world.setFrameCount(0);

            }
            else {

                Point pt;

                FX::seekDataArray(Constants::BeachDetails, world.getNextPort(), 0, 6);
                uint16_t left = FX::readPendingUInt16();
                FX::readObject(pt);
                FX::readEnd();

                leftDialogue = (left == 0);

                int16_t xOffset = pt.x - world.getXMap();
                int16_t yOffset = pt.y - world.getYMap();

                if (xOffset > 20)  world.incXMap(1);
                if (xOffset < -20) world.incXMap(-1);
                if (yOffset > 12)  world.incYMap(1);
                if (yOffset < -12) world.incYMap(-1);

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

    if (world.getFrameCount() % 36 < 18) {

        for (uint8_t i = 0; i < 14; i++) {

            FX::seekDataArray(Constants::mapCoords, i, 0, 4);
            Point pt;
            FX::readObject(pt);
            FX::readEnd();

            SpritesU::drawPlusMaskFX(pt.x - world.getXMap(), pt.y - world.getYMap(), Images::Beach, currentPlane);

            // FX::seekData(Constants::portNames_Coords + (i * 4));
            // pt;
            // FX::readObject(pt);
            // FX::readEnd();

            // SpritesU::drawPlusMaskFX(pt.x - world.getXMap(), pt.y - world.getYMap(), Images::PortNames_WB, (i * 3) + currentPlane);

        }

    }

    switch (world.getGameState()) {

        case GameState::Map:
            
            SpritesU::drawPlusMaskFX(world.getXBoat() - world.getXMap(), world.getYBoat() - world.getYMap(), Images::Boat_Small, currentPlane);

            for (uint8_t i = 0; i < 14; i++) {

                FX::seekDataArray(Constants::portNames_Coords, i, 0, 4);
                Point pt;
                FX::readObject(pt);
                FX::readEnd();

                SpritesU::drawPlusMaskFX(pt.x - world.getXMap(), pt.y - world.getYMap(), Images::PortNames_WB, (i * 3) + currentPlane);

            }
            
            break;

        case GameState::Map_ShowDialogue:
            {
                uint8_t frame = 0;
                uint8_t numberToShow = 67;

                if (world.getCurrentPort() == world.getNextPort()) {

                    frame = 4;
                    SpritesU::drawPlusMaskFX(0 + (leftDialogue ? 0: 73), 0, Images::Scroll, (frame * 3) + currentPlane);

                }
                else if (world.getChakanas() < world.getNextPortCost()) {

                    numberToShow = world.getNextPortCost() - world.getChakanas();
                    frame = (numberToShow < 100 ? 2 : 3);

                    SpritesU::drawPlusMaskFX(0 + (leftDialogue ? 0: 73), 0, Images::Scroll, (frame * 3) + currentPlane);

                    if (numberToShow < 100) {
                        SpritesU::drawOverwriteFX(15 + (leftDialogue ? 0 : 73), 27, Images::Numbers_5x3_2D_BW, (numberToShow * 3) + currentPlane);
                    }
                    else {
                        SpritesU::drawOverwriteFX(13 + (leftDialogue ? 0 : 73), 27, Images::Numbers_5x3_3D_BW, (numberToShow * 3) + currentPlane);
                    }

                }
                else {

                    numberToShow = world.getNextPortCost();
                    frame = (numberToShow < 100 ? 0 : 1);

                    SpritesU::drawPlusMaskFX(0 + (leftDialogue ? 0: 73), 0, Images::Scroll, (frame * 3) + currentPlane);
                    SpritesU::drawOverwriteFX(12 + (leftDialogue ? 0 : 73), 23, Images::PortNames, (world.getNextPort() * 3) + currentPlane);

                    if (numberToShow < 100) {
                        SpritesU::drawOverwriteFX(33 + (leftDialogue ? 0 : 73), 32, Images::Numbers_5x3_2D_BW, (numberToShow * 3) + currentPlane);
                    }
                    else {
                        SpritesU::drawOverwriteFX(31 + (leftDialogue ? 0 : 73), 32, Images::Numbers_5x3_3D_BW, (numberToShow * 3) + currentPlane);
                    }

                }

            }
            break;

        case GameState::Map_MoveBoat:
            // SpritesU::drawPlusMaskFX((world.getXBoat() / 2) - world.getXMap(), (world.getYBoat() / 2) - world.getYMap(), Images::Boat_Small, (static_cast<uint8_t>(world.getBoatDirection()) * 3) + currentPlane);
            SpritesU::drawPlusMaskFX(world.getXBoat() - world.getXMap(), world.getYBoat() - world.getYMap(), Images::Boat_Small, (static_cast<uint8_t>(world.getBoatDirection()) * 3) + currentPlane);
            break;
        
    }

}

