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

    Player &player = world.getPlayer();
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

                if (pressed & LEFT_BUTTON) {

                    if (world.getXMap() > 0) world.incXMap(-4);

                }

                if (pressed & RIGHT_BUTTON) {

                    if (world.getXMap() < 256) world.incXMap(4);

                }

                if (pressed & DOWN_BUTTON) {

                    if (world.getYMap() < 308) world.incYMap(4);

                }

                if (pressed & UP_BUTTON) {

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
 
                world.setGameState(GameState::Map_ShowMenu_1);

            }

            break;

        case GameState::Map_ShowMenu_1:

            if (justPressed & A_BUTTON) {

                world.setGameState(GameState::Map_ShowMenu_2);

            }

            if (justPressed & B_BUTTON) {

                world.setGameState(GameState::Map);

            }

            break;

        case GameState::Map_ShowMenu_2:

            if (justPressed & DOWN_BUTTON) {

                world.setGameState(GameState::Map_ShowMenu_3);

            }

            if (justPressed & A_BUTTON || justPressed & B_BUTTON) {

                world.setGameState(GameState::Map_ShowMenu_1);

            }

            break;

        case GameState::Map_ShowMenu_3:

            if (justPressed & UP_BUTTON) {

                world.setGameState(GameState::Map_ShowMenu_2);

            }

            if (justPressed & B_BUTTON) {

                world.setGameState(GameState::Map_ShowMenu_1);

            }

            if (justPressed & A_BUTTON) {

                world.setGameState(GameState::Title_Init);

            }

            break;

        case GameState::Map_ShowDialogue:

            if (justPressed & A_BUTTON) {

                if (world.getCurrentPort() == world.getNextPort()) {

                    world.setGameState(GameState::Map);
                    world.setFrameCount(0);

                }
                else if (world.getPortVisited(world.getNextPort())) {

                    world.setGameState(GameState::Map);
                    world.setFrameCount(0);

                }
                else if (player.getChakanas() >= world.getNextPortCost() && world.getCurrentPort() != world.getNextPort()) {

                    world.setGameState(GameState::Map_MoveBoat);
                    world.setFrameCount(0);
                    player.setChakanas(player.getChakanas() - world.getNextPortCost());


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

    Player &player = world.getPlayer();
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


    for (uint8_t i = 0; i < 14; i++) {

         if (world.getFrameCount() % 36 < 18) {

            FX::seekDataArray(Constants::mapCoords, i, 0, 4);
            Point pt;
            FX::readObject(pt);
            FX::readEnd();

            SpritesU::drawPlusMaskFX(pt.x - world.getXMap(), pt.y - world.getYMap(), Images::Beach, currentPlane);

        }

        FX::seekDataArray(Constants::portNames_Coords, i, 0, 4);
        Point pt;
        FX::readObject(pt);
        FX::readEnd();

        SpritesU::drawPlusMaskFX(pt.x - world.getXMap(), pt.y - world.getYMap(), Images::PortNames_WB, (i * 3) + currentPlane);
    
    }

    SpritesU::drawPlusMaskFX(world.getXBoat() - world.getXMap(), world.getYBoat() - world.getYMap(), Images::Boat_Small, currentPlane);

    switch (world.getGameState()) {

        case GameState::Map_ShowMenu_1:

            SpritesU::drawPlusMaskFX(74, 0, Images::Scroll_Map, (player.getHealth() * 3) + currentPlane);
            SpritesU::drawOverwriteFX(98, 16,  Images::Numbers_6x4_3D_BW, (player.getChakanas() * 3) + currentPlane);

            break;

        case GameState::Map_ShowMenu_2:
        case GameState::Map_ShowMenu_3:
            
            SpritesU::drawPlusMaskFX(74, 0, Images::Scroll_Map,  (15 * 3) + currentPlane);

            if (world.getFrameCount() % 64 < 32) {

                SpritesU::drawPlusMaskFX(90, 6 + 24 + (static_cast<uint8_t>(world.getGameState()) - static_cast<uint8_t>(GameState::Map_ShowMenu_2)) * 8, Images::InventoryPanel_Cursor, currentPlane);

            }
            
            break;

        case GameState::Map_ShowDialogue:
            {
                uint8_t frame = 0;
                uint8_t numberToShow = 67;

                if (world.getCurrentPort() == world.getNextPort()) {

                    frame = 5;

                }
                else if (world.getPortVisited(world.getNextPort())) {

                    frame = 4;

                }
                else if (player.getChakanas() < world.getNextPortCost()) {

                    numberToShow = world.getNextPortCost() - player.getChakanas();
                    frame = (numberToShow < 100 ? 2 : 3);

                }
                else {

                    numberToShow = world.getNextPortCost();
                    frame = (numberToShow < 100 ? 0 : 1);

                }

                SpritesU::drawPlusMaskFX(0 + (leftDialogue ? 0: 73), 0, Images::Scroll, (frame * 3) + currentPlane);

                if (frame <= 3) {
                    SpritesU::drawOverwriteFX(12 + (leftDialogue ? 0 : 73), 23, Images::PortNames, (world.getNextPort() * 3) + currentPlane);
                    renderNumber(numberToShow, 31, 32, currentPlane);

                }

            }
            break;

        case GameState::Map_MoveBoat:

            SpritesU::drawPlusMaskFX(world.getXBoat() - world.getXMap(), world.getYBoat() - world.getYMap(), Images::Boat_Small, (static_cast<uint8_t>(world.getBoatDirection()) * 3) + currentPlane);
            break;
        
    }

}


void renderNumber(uint8_t numberToShow, uint8_t x, uint8_t y, uint8_t currentPlane) {

    if (numberToShow < 100) {
        SpritesU::drawOverwriteFX(x + 2 + (leftDialogue ? 0 : 73), y, Images::Numbers_5x3_2D_BW, (numberToShow * 3) + currentPlane);
    }
    else {
        SpritesU::drawOverwriteFX(x + (leftDialogue ? 0 : 73), y, Images::Numbers_5x3_3D_BW, (numberToShow * 3) + currentPlane);
    }

}