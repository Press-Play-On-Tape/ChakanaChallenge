#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"

bool leftDialogue = false;
bool centreMap = false;

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

                if (world.updateBoat()) {
                    world.setGameState(GameState::Play_Init);
                }

            }
            break;

        case GameState::Map:

            if (world.getFrameCount() % 4 == 0) {
                
                if (pressed & LEFT_BUTTON)          world.incXMap(-4);
                else if (pressed & RIGHT_BUTTON)    world.incXMap(4);
                if (pressed & DOWN_BUTTON)          world.incYMap(4);
                else if (pressed & UP_BUTTON)       world.incYMap(-4);

            }

            if (justPressed & A_BUTTON) {

                world.setNextPort(Constants::NoPort);
                Point pt;

                FX::seekData(Constants::Port_Coords);

                int16_t xMap = world.getXMap();
                int16_t yMap = world.getYMap();

                for (uint8_t i = 0; i < Constants::NoOfPorts; i++) {
                    
                    FX::readObject(pt);

                    if (pt.x > xMap && pt.x < xMap + 128 && pt.y > yMap && pt.y < yMap + 64) {

                        world.setNextPort(i);
                        break;

                    }

                }

                FX::readEnd();

                if (world.getNextPort() != Constants::NoPort) {

                    uint8_t fromPort = world.getCurrentPort() == 255 ? 0 : world.getCurrentPort() + 1;
                    uint8_t toPort = world.getNextPort() + 1;

                    if (toPort < fromPort) toPort = toPort + 14;
                    if (toPort - fromPort > 6) fromPort = fromPort + 14 + (fromPort == 0 ? 1 : 0);

                    FX::seekData(Constants::PortCosts + (fromPort * 29) + toPort);
                    world.setNextPortCost(FX::readPendingUInt8());
                    FX::readEnd();

                    world.setGameState(GameState::Map_ShowDialogue);
                    world.setFrameCount(0);

                    FX::seekDataArray(Constants::BeachDetails, world.getNextPort(), 0, 6);
                    uint16_t left = FX::readPendingUInt16();
                    FX::readEnd();

                    leftDialogue = (left == 0);
                    centreMap = false;

                }

            }

            if (justPressed & B_BUTTON) {
 
                #ifdef MAP_SHOW_PORTS_VISITED
                
                    world.setGameState(GameState::Map_ShowMenu_1);
                
                #else

                    world.setGameState(GameState::Map_ShowMenu);

                #endif

            }

            break;

        #ifdef MAP_SHOW_PORTS_VISITED

        case GameState::Map_ShowMenu_1:
        case GameState::Map_ShowMenu_2:
        case GameState::Map_ShowMenu_3:
        case GameState::Map_ShowMenu_4:

            if (justPressed & A_BUTTON) {

                world.incGameState();

            }

            if (justPressed & B_BUTTON) {

                world.setGameState(GameState::Map);

            }

            break;

        #else

        case GameState::Map_ShowMenu:

            if (justPressed & A_BUTTON) {

                world.incGameState();

            }

            if (justPressed & B_BUTTON) {

                world.setGameState(GameState::Map);

            }

            break;

        #endif
            
        case GameState::Map_ShowMenu_Back:

            if (justPressed & DOWN_BUTTON) {

                world.incGameState();

            }

            if (justPressed & A_BUTTON || justPressed & B_BUTTON) {

                world.setGameState(GameState::Map);

            }

            break;

        case GameState::Map_ShowMenu_Exit:

            if (justPressed & UP_BUTTON) {

                world.decGameState();

            }

            if (justPressed & A_BUTTON || justPressed & B_BUTTON) {

                world.setGameState(GameState::Map);

            }

            if (justPressed & A_BUTTON) {

                world.setGameState(GameState::Title_Init);

            }

            break;

        case GameState::Map_ShowDialogue:

            if ((justPressed & A_BUTTON) && !centreMap) {

                if (world.getCurrentPort() == world.getNextPort()) {

                    world.setGameState(GameState::Map);
                    world.setFrameCount(0);

                }
                else if (world.getPortVisited(world.getNextPort())) {

                    world.setGameState(GameState::Map);
                    world.setFrameCount(0);

                }
                else if (player.getChakanas() >= world.getNextPortCost()) {

                    world.setGameState(GameState::Map_MoveBoat);
                    world.setFrameCount(0);
                    player.setChakanas(player.getChakanas() - world.getNextPortCost());


                    // Swap port positions as we are about to move!

                    uint8_t port = world.getCurrentPort();
                    world.setCurrentPort(world.getNextPort());
                    world.setNextPort(port);


                    // Reposition boat ..

                    uint8_t offset = world.getBoatCoords_Offset();

                    FX::seekDataArray(Constants::BoatCoords_Start, (world.getCurrentPort() << 2) + offset, 0, 4);
                    world.setXBoat(FX::readPendingUInt16());
                    world.setYBoat(FX::readPendingUInt16() - 1);
                    world.setBoatCounter(0);
                    world.setBoatDirection(BoatDirection::Left);
                    FX::readEnd();

                }
                else {

                    world.decGameState();
                    world.setFrameCount(0);

                }

            }

            else if (justPressed & B_BUTTON) {

                world.decGameState();
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

                centreMap = false;
                if (xOffset > 16)  { world.incXMap(1);  centreMap = true; }       
                if (xOffset < -16) { world.incXMap(-1); centreMap = true; }
                if (yOffset > 6)   { world.incYMap(1);  centreMap = true; }
                if (yOffset < -6)  { world.incYMap(-1); centreMap = true; }

            }
            
            break;
        
    }

}

void map_RenderScrollMap(uint8_t scrollFrame) {

    SpritesU::drawPlusMaskFX(74, 0, Images::Scroll_Map, scrollFrame);

}

void map_RenderHearts(uint8_t lives, uint8_t chakanas) {

    SpritesU::drawOverwriteFX(93, 26,  Images::Hearts, lives);
    SpritesU::drawOverwriteFX(98, 15,  Images::Numbers_6x4_3D_BW, chakanas);

}

void map(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    if (a.needsUpdate()) map_Update();

    Player &player = world.getPlayer();

    uint8_t xInt = world.getXMap() / 192;
    int16_t xLeft = -(world.getXMap() - (xInt * 192));

    uint8_t yInt = world.getYMap() / 192;
    int16_t yTop = -(world.getYMap() - (yInt * 192));

    #ifndef DEBUG_RENDER_MAP

        for (uint8_t i = 0; i < 2; i++) {

            SpritesU::drawOverwriteFX(xLeft,       yTop + (i * 192), Images::Map, (((xInt + 0) + ((yInt + i) * 2)) * 3) + currentPlane);    
            SpritesU::drawOverwriteFX(xLeft + 192, yTop + (i * 192), Images::Map, (((xInt + 1) + ((yInt + i) * 2)) * 3) + currentPlane);    

        }

    #endif

    for (uint8_t i = 0; i < Constants::NoOfPorts; i++) {

        Point pt;

         if (world.getFrameCount() % 36 < 18) {

            FX::seekDataArray(Constants::Port_Coords, i, 0, 4);
            FX::readObject(pt);
            FX::readEnd();

            SpritesU::drawPlusMaskFX(pt.x - world.getXMap(), pt.y - world.getYMap(), Images::PortLocation, (world.getPortVisited(i) ? 3 : 0) + currentPlane);

        }

        #ifdef MAP_SHOW_PORT_NAMES
            
            if (world.getGameState() != GameState::Map_MoveBoat) {

                FX::seekDataArray(Constants::PortNames_Coords, i, 0, 4);
                FX::readObject(pt);
                FX::readEnd();

                SpritesU::drawPlusMaskFX(pt.x - world.getXMap(), pt.y - world.getYMap(), Images::PortNames_WB, ((i + (world.getPortVisited(i) ? 14 : 0)) * 3) + currentPlane);

            }

        #endif
    
    }

    SpritesU::drawPlusMaskFX(world.getXBoat() - world.getXMap(), world.getYBoat() - world.getYMap() - 1, Images::Boat_Small, (static_cast<uint8_t>(world.getBoatDirection()) * 3) + currentPlane);

        
    switch (world.getGameState()) {

        #ifdef MAP_SHOW_PORTS_VISITED

            case GameState::Map_ShowMenu_1:

                map_RenderScrollMap((player.getHealth() * 3) + currentPlane);
                map_RenderHearts(((player.getLives() - 1) * 3) + currentPlane, (player.getChakanas() * 3) + currentPlane);

                break;

            case GameState::Map_ShowMenu_2:
            case GameState::Map_ShowMenu_3:
            case GameState::Map_ShowMenu_4:
                {
                    uint8_t frame = static_cast<uint8_t>(world.getGameState()) - static_cast<uint8_t>(GameState::Map_ShowMenu_2);
                    map_RenderScrollMap(((frame + 16) * 3) + currentPlane);

                    for (uint8_t i = 0; i < 5; i++) {

                        uint8_t port = i + (frame * 5);

                        if (port == 14) break;

                        if (world.getPortVisited(port)) {

                            SpritesU::drawPlusMaskFX(86, 15 + (7 * i), Images::Checkbox, a.currentPlane());

                        }
                        
                    }

                }
                break;

            case GameState::Map_ShowMenu_Back:
            case GameState::Map_ShowMenu_Exit:

                map_RenderScrollMap((15 * 3) + currentPlane);

                if (world.getFrameCount() % 64 < 32) {

                    renderInventoryPanelCursor(90, 30 + ((static_cast<uint8_t>(world.getGameState()) - static_cast<uint8_t>(GameState::Map_ShowMenu_Back)) << 3));

                }
                
                break;

        #else

            case GameState::Map_ShowMenu:

                map_RenderScrollMap((player.getHealth() * 3) + currentPlane);
                map_RenderHearts((player.getChakanas() * 3) + currentPlane, (player.getChakanas() * 3) + currentPlane);

                break;

            case GameState::Map_ShowMenu_Back:
            case GameState::Map_ShowMenu_Exit:

                map_RenderScrollMap((15 * 3) + currentPlane);

                if (world.getFrameCount() % 64 < 32) {

                    renderInventoryPanelCursor(90, 30 + ((static_cast<uint8_t>(world.getGameState()) - static_cast<uint8_t>(GameState::Map_ShowMenu_Back)) << 3));

                }
                
                break;

        #endif

        case GameState::Map_ShowDialogue:
            {
                uint8_t frame = 0;
                uint8_t numberToShow = 67;
                uint8_t x = 0;
                uint8_t y = 0;

                if (world.getCurrentPort() == world.getNextPort()) {

                    frame = 5;

                }
                else if (world.getPortVisited(world.getNextPort())) {

                    frame = 4;

                }
                else if (player.getChakanas() < world.getNextPortCost()) {

                    numberToShow = world.getNextPortCost() - player.getChakanas();
                    frame = (numberToShow < 100 ? 2 : 3);
                    x = 13;
                    y = 27;

                }
                else {

                    numberToShow = world.getNextPortCost();
                    frame = (numberToShow < 100 ? 0 : 1);
                    x = 31;
                    y = 32;

                }

                SpritesU::drawPlusMaskFX(0 + (leftDialogue ? 0: 73), 0, Images::Scroll, (frame * 3) + currentPlane);

                #ifndef DEBUG

                if (frame <= 3) {

                    if (frame < 2) {
                        SpritesU::drawOverwriteFX(12 + (leftDialogue ? 0 : 73), 24, Images::PortNames, (world.getNextPort() * 3) + currentPlane);
                    }

                    renderNumber(numberToShow, x, y);

                }

                #endif

            }
            break;

        case GameState::Map_MoveBoat:

            break;
        
    }

}

#ifndef DEBUG

void renderNumber(uint8_t numberToShow, uint8_t x, uint8_t y) {

    uint24_t font = Images::Numbers_5x3_2D_BW;

    if (numberToShow < 100) {
        x = x + 2;
    }
    else {
        font = Images::Numbers_5x3_3D_BW;
    }

    SpritesU::drawOverwriteFX(x + (leftDialogue ? 0 : 73), y, font, (numberToShow * 3) + currentPlane);

}

#endif