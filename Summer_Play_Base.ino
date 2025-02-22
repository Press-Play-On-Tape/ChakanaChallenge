#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"

uint8_t endOfLevel_Counter = 0;
uint8_t ignoreKeyPress = 0;

void playGame_Init() {

    #ifndef DEBUG_DISABLE_PLAY

    Player &player = world.getPlayer();
    world.setGameState(GameState::Play_Game);
    world.setFrameCount(0);
    menu.reset();


    // Load Map Data ..
    {
        uint24_t levelStart = FX::readIndexedUInt24(Levels::Levels, world.getCurrentPort());

        for (uint8_t y = 0; y < Constants::Map_Y_Count; y++) {
                
            FX::seekDataArray(levelStart, y, 0, Constants::Map_X_Count_Full);            
            FX::readObject(world.mapData[Constants::Map_Y_Count - y - 1]);
            FX::readEnd();

        }

    }


    // Load Map Items ..
    {

        bool puffFound = false;

        uint24_t levelItemsStart = FX::readIndexedUInt24(Levels::Level_Items, world.getCurrentPort());
        FX::seekData(levelItemsStart);

        for (uint8_t i = 0; i < Constants::ItemCount_Level; i++) {

            Item &item = world.getItem(i);

            if (!puffFound) {

                item.setItemType(static_cast<ItemType>(FX::readPendingUInt16()));

                item.setX(FX::readPendingUInt16());
                item.setY(FX::readPendingUInt16());
                item.setFrame(FX::readPendingUInt16());
                item.setData(FX::readPendingUInt16());
                item.setCounter(FX::readPendingUInt16());

                if (item.getItemType() == ItemType::Puff) {
                    puffFound = true;
                }
                
            }
            else {
                
                item.setItemType(ItemType::None);

            }

            if (i < Constants::ItemCount_Player - 1) {

                player.getItem(i).setItemType(ItemType::None);

            }

        }

        FX::readEnd();

    }


    // Load Map Enemies ..
    {

        uint24_t levelEnemiesStart = FX::readIndexedUInt24(Levels::Level_Enemies, world.getCurrentPort());
        FX::seekData(levelEnemiesStart);

        for (uint8_t i = 0; i < Constants::EnemyCount; i++) {

            Enemy &enemy = world.getEnemy(i);

            enemy.setEnemyType(static_cast<EnemyType>(FX::readPendingUInt16()));
            enemy.setX(FX::readPendingUInt16());
            enemy.setY(FX::readPendingUInt16());
            enemy.setStance(FX::readPendingUInt16());
            enemy.getItem().setItemType(static_cast<ItemType>(FX::readPendingUInt16()));
            enemy.getItem().setData(FX::readPendingUInt16());

        }

        FX::readEnd();

    }



    world.setMiddleground(0);
    player.setY(Constants::GroundY);

    world.setPalm(0, -27);
    world.setPalm(1, 93);
    world.setPalm(2, 253);
    world.setPalm(3, 333);
    world.setPalm(4, 87);
    world.setPalm(5, 37);
    world.setPalm(6, -49);
    world.setPalm(7, -109);
    world.setWave(-87);

    world.setBackground(-29);
    player.setStance(Stance::Man_Walk_RH_00);

    player.addInventoryItem(ItemType::Sword);

    cookie.hasSavedGame = true;

    #ifndef DEBUG
    saveCookie(true);
    #endif

    #endif

}


void killPlayer(Player &player) {

    Stance startStance = (player.getDirection() == Direction::Left) ? Stance::Man_Die_Fall_LH_01 : Stance::Man_Die_Fall_RH_01;
    player.pushSequence(startStance, startStance + 3, true);

}


// void processLadder_MoveLeft(Player &player, Tiles tile) {

//     if (world.getMiddleground() % 8 != 0) {

//         if (world.isEmptyTile(tile)) {
//             player.pushSequence(Stance::Man_Walk_FallDown_LH_01, Stance::Man_Walk_FallDown_LH_06);
//             player.pushSequence(Stance::Man_Walk_LH_01, Stance::Man_Walk_LH_02);
//             player.setFalls(0);
//         }
//         else {
//             player.pushSequence(Stance::Man_Walk_LH_03, Stance::Man_Walk_LH_08);
//         }

//     }
//     else {
//         player.pushSequence(Stance::Man_Walk_LH_01, Stance::Man_Walk_LH_04);
//     }

// }

void processLadder_MoveLeft(Player &player, Tiles tile) {

    uint8_t start = 0;
    uint8_t end;

    if (world.getMiddleground() % 8 != 0) {

        if (world.isEmptyTile(tile)) {
            player.pushSequence(Stance::Man_Walk_FallDown_LH_01, Stance::Man_Walk_FallDown_LH_06);
            // player.pushSequence(Stance::Man_Walk_LH_01, Stance::Man_Walk_LH_02);
            end = 1;
            player.setFalls(0);
        }
        else {
            start = 2;
            end = 7;
            // player.pushSequence(Stance::Man_Walk_LH_03, Stance::Man_Walk_LH_08);
        }

    }
    else {
        // player.pushSequence(Stance::Man_Walk_LH_01, Stance::Man_Walk_LH_04);
        end = 3;
    }

    player.pushSequence(Stance::Man_Walk_LH_01 + start, Stance::Man_Walk_LH_01 + end);

}

// void processLadder_MoveRight(Player &player, Tiles tile) {

//     if (world.getMiddleground() % 8 != 0) {

//         if (world.isEmptyTile(tile)) {
//             player.pushSequence(Stance::Man_Walk_FallDown_RH_01, Stance::Man_Walk_FallDown_RH_06);
//             player.pushSequence(Stance::Man_Walk_RH_01, Stance::Man_Walk_RH_02);
//             player.setFalls(0);
//         }
//         else {
//             player.pushSequence(Stance::Man_Walk_RH_03, Stance::Man_Walk_RH_08);
//         }

//     }
//     else {
//         player.pushSequence(Stance::Man_Walk_RH_01, Stance::Man_Walk_RH_04);
//     }

// }
void processLadder_MoveRight(Player &player, Tiles tile) {

    uint8_t start = 0;
    uint8_t end;

    if (world.getMiddleground() % 8 != 0) {

        if (world.isEmptyTile(tile)) {
            player.pushSequence(Stance::Man_Walk_FallDown_RH_01, Stance::Man_Walk_FallDown_RH_06);
            // player.pushSequence(Stance::Man_Walk_RH_01, Stance::Man_Walk_RH_02);
            end = 1;
            player.setFalls(0);
        }
        else {
            // player.pushSequence(Stance::Man_Walk_RH_03, Stance::Man_Walk_RH_08);
            start = 2;
            end = 7;
        }

    }
    else {
        // player.pushSequence(Stance::Man_Walk_RH_01, Stance::Man_Walk_RH_04);
        end = 3;
    }

    player.pushSequence(Stance::Man_Walk_RH_01 + start, Stance::Man_Walk_RH_01 + end);

}


boolean isMidLadderOrVineStance_RH(Stance stance) {

    return stance == Stance::Man_ClimbLadder_BK_RH_UP_07 || stance == Stance::Man_ClimbLadder_BK_RH_DOWN_07 ||
           stance == Stance::Man_ClimbLadder_More_BK_RH_UP_04 || stance == Stance::Man_ClimbLadder_More_BK_RH_DOWN_04 ||
           stance == Stance::Man_Walk_RH_04 || stance == Stance::Man_RH_Start;

}

boolean isMidLadderOrVineStance_LH(Stance stance) {

    return stance == Stance::Man_ClimbLadder_BK_LH_UP_07 || stance == Stance::Man_ClimbLadder_BK_LH_DOWN_07 ||
           stance == Stance::Man_ClimbLadder_More_BK_LH_UP_04 || stance == Stance::Man_ClimbLadder_More_BK_LH_DOWN_04 ||
           stance == Stance::Man_Walk_LH_04 || stance == Stance::Man_LH_Start;

}

bool canClimbUp(uint8_t t1, uint8_t t2) {

    return (world.isLadderTile_Lower(t1) && world.isLadderTile_Lower(t2)) ||
           (world.isLadderTile_Middle(t1) && world.isLadderTile_Middle(t2)) ||
           (world.isVerticalVine_Lower(t1) && world.isVerticalVine_Lower(t2)) ||
           (world.isVerticalVine_Middle(t1) && world.isVerticalVine_Middle(t2));

};

bool canClimbUp_Upper(uint8_t t1, uint8_t t2) {

    return (world.isLadderTile_Upper(t1) && world.isLadderTile_Upper(t2)) ||
           (world.isVerticalVine_Upper(t1) && world.isVerticalVine_Upper(t2));

};

bool canClimbDown(uint8_t t1, uint8_t t2) {

    return (world.isLadderTile_Upper(t1) && world.isLadderTile_Upper(t2)) ||
           (world.isVerticalVine_Upper(t1) && world.isVerticalVine_Upper(t2));

};

void playGame_HandleGamePlay(Player &player, uint8_t pressed, uint8_t justPressed) {

    #ifndef DEBUG_DISABLE_PLAY

    player.stageSequence(Stance::None, Stance::None);
    Stance stance = player.getStance();
    uint8_t justPressedOrPressed = pressed | justPressed;
    bool middleGroundMod8Equals0 = world.getMiddleground() % 8 == 0;

    if (justPressedOrPressed & UP_BUTTON) {

        switch (player.getDirection()) {

            case Direction::Backward:
                {
                
                    uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                    uint8_t tile_L = world.getTile_RelativeToPlayer(-1, 0);
                    uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);
                    uint8_t tile_R2 = world.getTile_RelativeToPlayer(2, 0);
                    uint8_t tile_U = world.getTile_RelativeToPlayer(0, 1);
                    uint8_t tile_U2 = world.getTile_RelativeToPlayer(0, 2);
                    uint8_t tile_RU = world.getTile_RelativeToPlayer(1, 1);
                    uint8_t tile_RU2 = world.getTile_RelativeToPlayer(1, 2);

                    if (world.isLadderTile_Upper(tile) && world.canWalkPastTile(tile_U2, Direction::Backward)) {

                        if (justPressedOrPressed & RIGHT_BUTTON || isMidLadderOrVineStance_RH(stance)) {
                            player.pushSequence(Stance::Man_ClimbLadder_BK_RH_UP_08, Stance::Man_ClimbLadder_BK_RH_UP_14);
                        }

                        else if (justPressedOrPressed & LEFT_BUTTON || isMidLadderOrVineStance_LH(stance)) {
                            player.pushSequence(Stance::Man_ClimbLadder_BK_LH_UP_08, Stance::Man_ClimbLadder_BK_LH_UP_14);
                        }

                    }
                    else if (world.isVerticalVine_Upper(tile_U)) {

                        if ((justPressedOrPressed & LEFT_BUTTON) && world.isEmptyTile(tile_L)) {
                            player.setFalls(0);
                            player.pushSequence(Stance::Man_Vine_Exit_LH_01, Stance::Man_Vine_Exit_LH_08);
                        }

                        else if ((justPressedOrPressed & RIGHT_BUTTON) && world.isEmptyTile(tile_R2)) {
                            player.setFalls(0);
                            player.pushSequence(Stance::Man_Vine_Exit_RH_01, Stance::Man_Vine_Exit_RH_08);
                        }

                    }
                    else if (world.isVerticalVine_Upper(tile_U2) && world.isVerticalVine_Upper(tile_RU2)) {

                        player.pushSequence(Stance::Man_ClimbLadder_More_BK_RH_UP_01, Stance::Man_ClimbLadder_More_BK_RH_UP_04);

                    }
                    else if ((world.isLadderTile_Middle(tile) && world.isLadderTile_Middle(tile_R)) ||
                            (world.isVerticalVine_CanClimbUp(tile) && world.isVerticalVine_CanClimbUp(tile_R))) {


                        // Climb further up ..

                        if (isMidLadderOrVineStance_RH(stance)) {

                            player.pushSequence(Stance::Man_ClimbLadder_More_BK_RH_UP_01, Stance::Man_ClimbLadder_More_BK_RH_UP_04);
                            
                        }
                        
                        else if (isMidLadderOrVineStance_LH(stance)) {  

                            player.pushSequence(Stance::Man_ClimbLadder_More_BK_LH_UP_01, Stance::Man_ClimbLadder_More_BK_LH_UP_04);
                            
                        }

                    }

                }
                break;

            // case Direction::Right:
            //     {
            //         uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
            //         uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);

            //         if ((world.isLadderTile_Lower(tile) && world.isLadderTile_Lower(tile_R)) ||
            //             (world.isLadderTile_Middle(tile) && world.isLadderTile_Middle(tile_R)) ||
            //             (world.isVerticalVine_Lower(tile) && world.isVerticalVine_Lower(tile_R)) ||
            //             (world.isVerticalVine_Middle(tile) && world.isVerticalVine_Middle(tile_R))) {

            //             if (middleGroundMod8Equals0) {
            //                 player.pushSequence(Stance::Man_ClimbLadder_BK_RH_UP_01, Stance::Man_ClimbLadder_BK_RH_UP_07);
            //             }
            //             else {
            //                 player.pushSequence(Stance::Man_ClimbLadder_More_BK_RH_UP_01, Stance::Man_ClimbLadder_More_BK_RH_UP_04);
            //             }

            //         }

            //     }
            //     break;

            // case Direction::Left:
            //     {
            //         uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
            //         uint8_t tile_L = world.getTile_RelativeToPlayer(-1, 0);
            //         uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);

            //         if ((world.isLadderTile_Lower(tile) && world.isLadderTile_Lower(tile_L)) ||
            //             (world.isLadderTile_Middle(tile) && world.isLadderTile_Middle(tile_R)) ||
            //             (world.isVerticalVine_Lower(tile) && world.isVerticalVine_Lower(tile_L)) ||
            //             (world.isVerticalVine_Middle(tile) && world.isVerticalVine_Middle(tile_R))) {
                            
            //             if (middleGroundMod8Equals0) {
            //                 player.pushSequence(Stance::Man_ClimbLadder_BK_LH_UP_01, Stance::Man_ClimbLadder_BK_LH_UP_07);
            //             }
            //             else {
            //                 player.pushSequence(Stance::Man_ClimbLadder_More_BK_LH_UP_01, Stance::Man_ClimbLadder_More_BK_LH_UP_04);
            //             }
                        
            //         }

            //     }
            //     break;

            case Direction::Right:
            case Direction::Left:
                {   
//                     Direction dir = player.getDirection();

//                     uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
//                     uint8_t tile_adj = world.getTile_RelativeToPlayer((dir == Direction::Right ? 1 : -1), 0);

//                     if (canClimbUp(tile, tile_adj)) {

//                         if (middleGroundMod8Equals0) {
//                             player.pushSequence(
//                                 (dir == Direction::Right) ? Stance::Man_ClimbLadder_BK_RH_UP_01 : Stance::Man_ClimbLadder_BK_LH_UP_01,
//                                 (dir == Direction::Right) ? Stance::Man_ClimbLadder_BK_RH_UP_07 : Stance::Man_ClimbLadder_BK_LH_UP_07);
//                         } 
//                         else {
//                             player.pushSequence(
//                                 (dir == Direction::Right) ? Stance::Man_ClimbLadder_More_BK_RH_UP_01 : Stance::Man_ClimbLadder_More_BK_LH_UP_01,
//                                 (dir == Direction::Right) ? Stance::Man_ClimbLadder_More_BK_RH_UP_04 : Stance::Man_ClimbLadder_More_BK_LH_UP_04);
//                         }

//                     }
                    Direction dir = player.getDirection();

                    uint8_t tile_L = world.getTile_RelativeToPlayer(-1, 0);
                    uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                    uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);

                    if (canClimbUp(tile, tile_R)) {

                        if (middleGroundMod8Equals0) {
                            player.pushSequence(Stance::Man_ClimbLadder_BK_RH_UP_01, Stance::Man_ClimbLadder_BK_RH_UP_07);
                        } 
                        else {
                            player.pushSequence(Stance::Man_ClimbLadder_More_BK_RH_UP_01, Stance::Man_ClimbLadder_More_BK_RH_UP_04);
                        }

                    }

                    else if (canClimbUp_Upper(tile_R, tile)) {

                        if (dir == Direction::Left) {
                            player.pushSequence(Stance::Man_ClimbLadder_BK_LH_UP_08, Stance::Man_ClimbLadder_BK_LH_UP_14);
                        } 
                        else {
                            player.pushSequence(Stance::Man_ClimbLadder_BK_RH_UP_08, Stance::Man_ClimbLadder_BK_RH_UP_14);
                        }

                    }

                }
                break;

            case Direction::Forward:
                {
                    uint8_t tile_L = world.getTile_RelativeToPlayer(-1, 0);
                    uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                    uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);

                    if ((world.isLadderTile_Lower(tile) && world.isLadderTile_Lower(tile_R)) ||
                        (world.isVerticalVine_Lower(tile) && world.isVerticalVine_Lower(tile_R))) {

                        player.pushSequence(Stance::Man_ClimbLadder_BK_RH_UP_01, Stance::Man_ClimbLadder_BK_RH_UP_07);

                    }
                    else if ((world.isLadderTile_Lower(tile) && world.isLadderTile_Lower(tile_L)) ||
                            (world.isVerticalVine_Lower(tile) && world.isVerticalVine_Lower(tile_L))) {

                        player.pushSequence(Stance::Man_ClimbLadder_BK_LH_UP_01, Stance::Man_ClimbLadder_BK_LH_UP_07);

                    }

                }
                break;
        }

    }

    else if (justPressedOrPressed & DOWN_BUTTON) {

        switch (player.getDirection()) {

            case Direction::Backward:
                {
                    uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                    uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);
                    uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                    uint8_t tile_D2 = world.getTile_RelativeToPlayer(0, -2);
                    uint8_t tile_RD = world.getTile_RelativeToPlayer(1, -1);

                    if (world.isLadderTile_Lower(tile_D) && world.isLadderTile_Lower(tile_RD)) {

                        if (justPressedOrPressed & RIGHT_BUTTON || isMidLadderOrVineStance_LH(stance)) {
                            player.pushSequence(Stance::Man_ClimbLadder_BK_RH_DOWN_08, Stance::Man_ClimbLadder_BK_RH_DOWN_14);
                        }

                        else if (justPressedOrPressed & LEFT_BUTTON || isMidLadderOrVineStance_RH(stance)) {
                            player.pushSequence(Stance::Man_ClimbLadder_BK_LH_DOWN_08, Stance::Man_ClimbLadder_BK_LH_DOWN_14);
                        }

                    }
                    else if (world.isVerticalVine_Lower(tile_D) && world.isVerticalVine_Lower(tile_RD)) {

                        if (world.isEmptyTile(tile_D2)) {
                            player.setFalls(0);
                            player.pushSequence(Stance::Man_Walk_FallMore_BK_01, Stance::Man_Walk_FallMore_BK_02);
                        }
                        else {
                                
                            if (justPressedOrPressed & RIGHT_BUTTON || isMidLadderOrVineStance_RH(stance)) {
                                player.pushSequence(Stance::Man_ClimbLadder_BK_RH_DOWN_08, Stance::Man_ClimbLadder_BK_RH_DOWN_14);
                            }

                            else if (justPressedOrPressed & LEFT_BUTTON || isMidLadderOrVineStance_LH(stance)) {
                                player.pushSequence(Stance::Man_ClimbLadder_BK_LH_DOWN_08, Stance::Man_ClimbLadder_BK_LH_DOWN_14);
                            }

                        }

                    }                            
                    else if ((world.isLadderTile_Middle(tile_D) && world.isLadderTile_Middle(tile_RD)) ||
                            (world.isVerticalVine_Middle(tile_D) && world.isVerticalVine_Middle(tile_RD))) {

                        if (isMidLadderOrVineStance_RH(stance)) {   
                            player.pushSequence(Stance::Man_ClimbLadder_More_BK_RH_DOWN_01, Stance::Man_ClimbLadder_More_BK_RH_DOWN_04);
                            
                        }

                        else if (isMidLadderOrVineStance_LH(stance)) {  

                            player.pushSequence(Stance::Man_ClimbLadder_More_BK_LH_DOWN_01, Stance::Man_ClimbLadder_More_BK_LH_DOWN_04);
                            
                        }

                    }
                    else if (stance == Stance::Man_Rope_Start_RH_07 || stance == Stance::Man_Rope_Start_LH_07) {
                
                        player.setFalls(0);
                        player.push(Stance::Man_Walk_FallMore_BK_02);

                    }

                }
                break;

            case Direction::Right:
            case Direction::Left:
                {
                    Direction dir = player.getDirection();
                    
                    uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                    uint8_t tile_RD = world.getTile_RelativeToPlayer(1, -1);
                    uint8_t tile_AdjD = world.getTile_RelativeToPlayer(dir == Direction::Right ? 1 : -1, -1);
                    uint8_t tile_Adj2D = world.getTile_RelativeToPlayer(dir == Direction::Right ? -1 : 1, -1);

                    if (canClimbDown(tile_D, tile_AdjD)) {

                        player.pushSequence(
                            (dir == Direction::Right) ? Stance::Man_ClimbLadder_BK_RH_DOWN_01 : Stance::Man_ClimbLadder_BK_LH_DOWN_01,
                            (dir == Direction::Right) ? Stance::Man_ClimbLadder_BK_RH_DOWN_07 : Stance::Man_ClimbLadder_BK_LH_DOWN_07);

                    }

                    else if (canClimbDown(tile_D, tile_Adj2D)) {

                        player.pushSequence(
                            (dir == Direction::Left) ? Stance::Man_ClimbLadder_BK_RH_DOWN_01 : Stance::Man_ClimbLadder_BK_LH_DOWN_01,
                            (dir == Direction::Left) ? Stance::Man_ClimbLadder_BK_RH_DOWN_07 : Stance::Man_ClimbLadder_BK_LH_DOWN_07);                       

                    }
                    else if (world.isLadderTile(tile_D) && world.isLadderTile(tile_RD)) {

                        if (middleGroundMod8Equals0) {
                           player.pushSequence(Stance::Man_ClimbLadder_BK_RH_DOWN_01, Stance::Man_ClimbLadder_BK_RH_DOWN_07);                            
                        } 
                        else {

                            player.pushSequence(
                                (dir == Direction::Right) ? Stance::Man_ClimbLadder_More_BK_RH_DOWN_01 : Stance::Man_ClimbLadder_More_BK_LH_DOWN_01,
                                (dir == Direction::Right) ? Stance::Man_ClimbLadder_More_BK_RH_DOWN_04 : Stance::Man_ClimbLadder_More_BK_LH_DOWN_04);
                        }

                    }

                }
                break;

            case Direction::Forward:
                {
                    uint8_t tile_LD = world.getTile_RelativeToPlayer(-1, -1);
                    uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                    uint8_t tile_RD = world.getTile_RelativeToPlayer(1, -1);

                    if ((world.isLadderTile_Upper(tile_D) && world.isLadderTile_Upper(tile_RD)) ||
                        (world.isVerticalVine_Upper(tile_D) && world.isVerticalVine_Upper(tile_RD))) {

                        player.pushSequence(Stance::Man_ClimbLadder_BK_RH_DOWN_01, Stance::Man_ClimbLadder_BK_RH_DOWN_07);

                    }

                    else if ((world.isLadderTile_Upper(tile_LD) && world.isLadderTile_Upper(tile_D)) ||
                        (world.isVerticalVine_Upper(tile_LD) && world.isVerticalVine_Upper(tile_D))) {

                        player.pushSequence(Stance::Man_ClimbLadder_BK_LH_DOWN_01, Stance::Man_ClimbLadder_BK_LH_DOWN_07);

                    }

                }
                break;

        }

    }

    else if (justPressedOrPressed & LEFT_BUTTON) {

        switch (player.getDirection()) {

            case Direction::Left:
                {
                
                    uint8_t tile_L = world.getTile_RelativeToPlayer(-1, 0);
                    uint8_t tile_L2 = world.getTile_RelativeToPlayer(-2, 0);
                    uint8_t tile_LD = world.getTile_RelativeToPlayer(-1, -1);
                    uint8_t tile_LU = world.getTile_RelativeToPlayer(-1, 1);

                    #ifdef FALL_THROUGH_PORTAL
                    if (world.isEmptyTile_XY(tile_LD, -1, -1) && world.isEmptyTile(tile_L)) {
                    #else
                    if (world.isEmptyTile(tile_LD) && world.isEmptyTile(tile_L)) {
                    #endif

                        if (justPressedOrPressed & A_BUTTON) { 

                            uint8_t tile_L2 = world.getTile_RelativeToPlayer(-2, 0);
                            uint8_t tile_L3 = world.getTile_RelativeToPlayer(-3, 0);
                            uint8_t tile_L2D = world.getTile_RelativeToPlayer(-2, -1);
                            uint8_t tile_L2D2 = world.getTile_RelativeToPlayer(-2, -2);
                            uint8_t tile_L3D = world.getTile_RelativeToPlayer(-3, -1);
                            uint8_t tile_L3D2 = world.getTile_RelativeToPlayer(-3, -2);

                            if (world.isVineTile_RH(tile_L) && (stance < Stance::Man_Vine_LH_01 || stance > Stance::Man_Vine_LH_20)) {

                                Item &item = world.getItem(world.getItem(ItemType::Swinging_Vine));

                                if ((item.getCounter() >= 144 && item.getCounter() < 208)) {

                                    item.setCounter(182);
                                    player.pushSequence(Stance::Man_Vine_LH_01, Stance::Man_Vine_LH_20, true);

                                }     
                                else {
                                  
                                    player.setFalls(0);
                                    player.pushSequence(Stance::Man_Walk_FallDown_LH_01, Stance::Man_Walk_FallDown_LH_06);

                                }

                            }

                            #ifdef FALL_THROUGH_PORTAL
                                else if (world.isEmptyTile(tile_L2) && world.isEmptyTile(tile_L3) && 
                                         world.isEmptyTile_XY(tile_L2D, -2, -1) && world.canWalkOnTile(tile_L3D)) {     

                                    player.pushSequence(Stance::Man_WalkingJump_LH_25_01, Stance::Man_WalkingJump_LH_25_11);

                                }    
                            #else
                                else if (world.isEmptyTile(tile_L2) && world.isEmptyTile(tile_L3) && 
                                         world.isEmptyTile(tile_L2D) && world.canWalkOnTile(tile_L3D)) {     

                                    player.pushSequence(Stance::Man_WalkingJump_LH_25_01, Stance::Man_WalkingJump_LH_25_11);

                                }    
                            #endif

                            else if (world.isEmptyTile(tile_L2) && world.isEmptyTile(tile_L3) &&
                                     world.isEmptyTile(tile_L2D) && world.isEmptyTile(tile_L3D) && !world.isEmptyTile(tile_L3D2)) {     

                                player.setFalls(0);
                                player.pushSequence(Stance::Man_WalkingJump_LH_1D_25_01, Stance::Man_WalkingJump_LH_1D_25_11);

                            }                     
                            else if (world.isEmptyTile(tile_L2) && world.isEmptyTile(tile_L3) &&
                                     world.isEmptyTile(tile_L2D) && world.isEmptyTile(tile_L3D)) {     

                                if (world.isWaterTile(tile_L2D2)) {
                                    
                                    uint8_t itemIdx = world.getItem(ItemType::LifeSaver_InWater_RH, ItemType::LifeSaver_Dissolve_InWater_RH);

                                    if (itemIdx == Constants::NoItem) {

                                        player.pushSequence(Stance::Man_Die_Water_LH_02_01, Stance::Man_Die_Water_LH_02_07);
                                        player.pushSequence(Stance::Man_WalkingJump_LH_2D_25_01, Stance::Man_WalkingJump_LH_2D_25_09);

                                    }
                                    else {

                                        uint8_t tile_D2 = world.getTile_RelativeToPlayer(0, -2);

                                        if (tile_D2 == Tiles::Water_Plain) {

                                            player.pushSequence(Stance::Man_Walk_LH_03, Stance::Man_Walk_LH_04);
                                            player.pushSequence(Stance::Man_WalkingJump_LH_25_01, Stance::Man_WalkingJump_LH_25_11);
                                            player.pushSequence(Stance::Man_Walk_LH_01, Stance::Man_Walk_LH_02);

                                        }
                                        else {

                                            player.pushSequence(Stance::Man_WalkingJump_LH_25_01, Stance::Man_WalkingJump_LH_25_11);

                                        }

                                    }

                                }
                                else {
                                    player.setFalls(0);
                                    player.pushSequence(Stance::Man_WalkingJump_LH_2D_25_01, Stance::Man_WalkingJump_LH_2D_25_11);
                                }

                            }    

                        }
                        else {

                            uint8_t tile_L2 = world.getTile_RelativeToPlayer(-2, 0);
                            uint8_t tile_L3 = world.getTile_RelativeToPlayer(-3, 0);
                            uint8_t tile_L2D = world.getTile_RelativeToPlayer(-2, -1);
                            uint8_t tile_L3D = world.getTile_RelativeToPlayer(-3, -1);   
                            uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                            uint8_t tile_RU = world.getTile_RelativeToPlayer(1, 1);
                            uint8_t tile_U = world.getTile_RelativeToPlayer(0, 1);
                            uint8_t tile_LU = world.getTile_RelativeToPlayer(-1, 1);
                            uint8_t tile_L2U = world.getTile_RelativeToPlayer(-2, 1);

                            if (world.isStairTile_R_Half(tile_D) ) {

                                player.pushSequence(Stance::Man_DescendStairs_LH_Half_01, Stance::Man_DescendStairs_LH_Half_04);

                            }
                            else if (world.canWalkOnTile(tile_L2D) && world.isEmptyTile(tile_L2) && world.isEmptyTile(tile_L2U) && world.isEmptyTile(tile_U)) {

                                player.pushSequence(Stance::Man_WalkingJump_LH_2_01, Stance::Man_WalkingJump_LH_2_08);

                            }
                            else if (world.isRopeSupport(tile_RU) && world.isRopeTile(tile_U)) {

                                player.pushSequence(Stance::Man_Rope_Start_LH_01, Stance::Man_Rope_Start_LH_07);

                            } 
                            else {

                                player.setFalls(0);
                                player.pushSequence(Stance::Man_Walk_FallDown_LH_01, Stance::Man_Walk_FallDown_LH_06);

                            }

                        }

                    }
                    else {

                        uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                        uint8_t tile_U = world.getTile_RelativeToPlayer(0, 1);
                        uint8_t tile_L3D2 = world.getTile_RelativeToPlayer(-3, -2);
                        uint8_t tile_L2D = world.getTile_RelativeToPlayer(-2, -1);

                        player.setFalls(0);

                        if (world.isVerticalVine_Upper(tile_L) || world.isVerticalVine_Middle(tile_L)) {
                            
                            player.setFalls(1);
                            player.pushSequence(Stance::Man_Vine_Entry_LH_01, Stance::Man_Vine_Entry_LH_08);

                        }
                        else if (world.isSlideTile_Full_RH(tile_LD) && world.canWalkOnTile(tile_L3D2)) {

                            player.pushSequence(Stance::Man_Slide_LH_Full_Land_01, Stance::Man_Slide_LH_Full_Land_13);

                        }
                        else if (world.isSlideTile_Full_RH(tile_LD) && !world.canWalkOnTile(tile_L3D2)) {

                            player.pushSequence(Stance::Man_Slide_LH_Full_01, Stance::Man_Slide_LH_Full_13);

                        }
                        else if (world.isSlideTile_Full_RH(tile_LD) && !world.isSlideTile_Full_RH(tile_L3D2)) {

                            player.pushSequence(Stance::Man_Slide_LH_Full_CanCont_01, Stance::Man_Slide_LH_Full_CanCont_12);

                        }
                        else if (world.isSlideTile_Full_RH(tile_LD) && !world.canWalkOnTile(tile_L3D2)) {

                            player.pushSequence(Stance::Man_Slide_LH_Full_01, Stance::Man_Slide_LH_Full_13);

                        }
                        else if (world.isSlideTile_RH(tile_LD)) {

                            player.pushSequence(Stance::Man_Slide_LH_01, Stance::Man_Slide_LH_11);

                        }
                        else if (world.isStairTile_L1(tile_L)) {

                            player.pushSequence(Stance::Man_ClimbStairs_LH_01, Stance::Man_ClimbStairs_LH_04);

                        }
                        else if (world.isStairTile_L_Half(tile_L)) {

                            player.pushSequence(Stance::Man_ClimbStairs_LH_Half_01, Stance::Man_ClimbStairs_LH_Half_04);

                        }
                        else if (world.isStairTile_L1(tile) || world.isStairTile_L_Half(tile)) {

                            player.pushSequence(Stance::Man_ClimbStairs_LH_05, Stance::Man_ClimbStairs_LH_08);

                        }
                        else if ((world.isStairTile_R1(tile_LD) || world.isStairTile_R_Half(tile)) && player.getY() < 37) {

                            player.pushSequence(Stance::Man_DescendStairs_LH_05, Stance::Man_DescendStairs_LH_08);

                        }
                        else if (world.isStairTile_R2(tile_LD)) {  

                            player.pushSequence(Stance::Man_DescendStairs_LH_01, Stance::Man_DescendStairs_LH_08);

                        }
                        else if (world.isStairTile_R_Half(tile) && player.getY() < 37) {  

                            player.pushSequence(Stance::Man_DescendStairs_LH_Half_01, Stance::Man_DescendStairs_LH_Half_04);

                        }
                        else if (world.isStairTile_R1(tile)) {  

                            player.pushSequence(Stance::Man_DescendStairs_LH_01, Stance::Man_DescendStairs_LH_04);

                        }   
                        else if (tile == Tiles::Poker || tile_L == Tiles::Poker) {

                            if (justPressedOrPressed & A_BUTTON) {

                                world.setGameState(GameState::Play_Gamble_Select_Open);
                                playGame_HandleMenu(GameState::Play_Gamble_Select_Exit);

                            }
                            else if (world.canWalkPastTile(tile_L, Direction::Left)) {  

                                player.pushSequence(Stance::Man_Walk_LH_01, Stance::Man_Walk_LH_04);

                            }

                        }
                        else if (world.isLadderTile(tile_L)) {
//Removed 8 Feb due to level 01.
                            // if (world.canWalkPastTile(tile_L2, Direction::Left)) {
                                processLadder_MoveLeft(player, tile_LD);
                            // }

                        }     
                        else if (world.canWalkPastTile(tile_L, Direction::Left)) {  

                            processLadder_MoveLeft(player, tile_L);

                        }   

                        #ifdef SHOW_SIGN

                            else if(world.isSignTile(tile_L)) {

                                world.setGameState(GameState::Show_Sign);
                                endOfLevel_Counter = 0;

                            }                        

                        #endif
                        else {

                            if (justPressedOrPressed & A_BUTTON) {

                                if (!world.canWalkPastTile(tile_L) && world.canWalkOnTile(tile_L) && world.isEmptyTile(tile_U)) {     

                                    player.pushSequence(Stance::Man_StandingJump_LH_UPandOver_01, Stance::Man_StandingJump_LH_UPandOver_06);

                                }                       
                                
                            }
                            else if (world.isStairTile_L1(tile_L) || world.isStairTile_L_Half(tile_L)) {

                                player.pushSequence(Stance::Man_ClimbStairs_LH_01, Stance::Man_ClimbStairs_LH_04);

                            }
                            else if (world.isStairTile_L2(tile_L)) {

                                player.pushSequence(Stance::Man_ClimbStairs_LH_05, Stance::Man_ClimbStairs_LH_08);

                            }

                        }       

                    }     

                }
                break;

            case Direction::Forward:
                player.push(Stance::Man_Walk_LH_00);
                break;

            case Direction::Backward:
                {
                    uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                    uint8_t tile_U = world.getTile_RelativeToPlayer(0, 1);
                    uint8_t tile_L = world.getTile_RelativeToPlayer(-1, 0);
                    uint8_t tile_LD = world.getTile_RelativeToPlayer(-1, -1);
                    uint8_t tile_L2 = world.getTile_RelativeToPlayer(-2, 0);
                    uint8_t tile_L2D = world.getTile_RelativeToPlayer(-2, -1);
                    uint8_t tile_L2U = world.getTile_RelativeToPlayer(-2, 1);
                    uint8_t tile_LU = world.getTile_RelativeToPlayer(-1, 1);
                    uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);

                    if (!world.canWalkPastTile(tile_LU) && !world.isRopeTile(tile_LU) && world.isRopeTile(tile_U)) {

                        // Do nothing ..

                    }   
                    else if ((world.isVerticalVine_Upper(tile) && world.isVerticalVine_Upper(tile_R)) ||
                            (world.isVerticalVine_Middle(tile) && world.isVerticalVine_Middle(tile_R))) {

                        if (world.isEmptyTile(tile_L)) {
                            player.setFalls(0);
                            player.pushSequence(Stance::Man_Vine_Exit_LH_01, Stance::Man_Vine_Exit_LH_08);
                        }
                        else { /* Do nothing, prevents a turn */}

                    }                            
                    else if (world.isRopeTile(tile_U) && world.isRopeTile(tile_LU) && world.isRopeSupport(tile_L2U)) {

                        player.pushSequence(Stance::Man_Rope_End_LH_01, Stance::Man_Rope_End_LH_06);

                    }   
                    else if (!world.isRopeSupport(tile_LU) && world.isRopeTile(tile_U)) {

                        player.pushSequence(Stance::Man_Rope_Start_LH_04, Stance::Man_Rope_Start_LH_07);

                    }     
                    //New
                    else if (world.canWalkPastTile(tile_L)) {

                        processLadder_MoveLeft(player, tile_LD);

                    }     
                    else {

                       player.push(Stance::Man_Walk_LH_00);

                    } 

                }
                break;

            case Direction::Right:

                player.push(Stance::Man_Walk_FW_01);
                break;

        }

    }

    // else if (justPressed & RIGHT_BUTTON || pressed & RIGHT_BUTTON) {
    else if (justPressedOrPressed & RIGHT_BUTTON) {

        switch (player.getDirection()) {

            case Direction::Right:
                {

                    uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);
                    uint8_t tile_R2 = world.getTile_RelativeToPlayer(2, 0);
                    uint8_t tile_R3 = world.getTile_RelativeToPlayer(3, 0);
                    uint8_t tile_RD = world.getTile_RelativeToPlayer(1, -1);

                    #ifdef FALL_THROUGH_PORTAL
                    if (world.isEmptyTile_XY(tile_RD, 1, -1) && world.isEmptyTile(tile_R)) {
                    #else
                    if (world.isEmptyTile(tile_RD) && world.isEmptyTile(tile_R)) {
                    #endif

                        if (justPressedOrPressed & A_BUTTON) { 

                            uint8_t tile_R2 = world.getTile_RelativeToPlayer(2, 0);
                            uint8_t tile_R3 = world.getTile_RelativeToPlayer(3, 0);
                            uint8_t tile_R2D = world.getTile_RelativeToPlayer(2, -1);
                            uint8_t tile_R2D2 = world.getTile_RelativeToPlayer(2, -2);
                            uint8_t tile_R3D = world.getTile_RelativeToPlayer(3, -1);
                            uint8_t tile_R3D2 = world.getTile_RelativeToPlayer(3, -2);

                            if (world.isVineTile_LH(tile_R) && (stance < Stance::Man_Vine_RH_01 || stance > Stance::Man_Vine_RH_20)) {

                                Item &item = world.getItem(world.getItem(ItemType::Swinging_Vine));

                                if ((item.getCounter() >= 0 && item.getCounter() < 32) || (item.getCounter() >= 320 && item.getCounter() < 352)) {

                                    item.setCounter(6);
                                    player.pushSequence(Stance::Man_Vine_RH_01, Stance::Man_Vine_RH_20, true);

                                }     
                                else {

                                    player.setFalls(0);
                                    player.pushSequence(Stance::Man_Walk_FallDown_RH_01, Stance::Man_Walk_FallDown_RH_06);

                                }

                            }

                            #ifdef FALL_THROUGH_PORTAL
                                else if (world.isEmptyTile(tile_R2) && world.isEmptyTile(tile_R3) &&
                                         world.isEmptyTile_XY(tile_R2D, 2, -1) && world.canWalkOnTile(tile_R3D)) {     

                                    player.pushSequence(Stance::Man_WalkingJump_RH_25_01, Stance::Man_WalkingJump_RH_25_11);

                                }    
                            #else
                                else if (world.isEmptyTile(tile_R2) && world.isEmptyTile(tile_R3) &&
                                         world.isEmptyTile(tile_R2D) && world.canWalkOnTile(tile_R3D)) {     

                                    player.pushSequence(Stance::Man_WalkingJump_RH_25_01, Stance::Man_WalkingJump_RH_25_11);

                                }    
                            #endif

                            else if (world.isEmptyTile(tile_R2) && world.isEmptyTile(tile_R3) &&
                                     world.isEmptyTile(tile_R2D) && world.isEmptyTile(tile_R3D) && !world.isEmptyTile(tile_R3D2)) {     

                                player.setFalls(0);
                                player.pushSequence(Stance::Man_WalkingJump_RH_1D_25_01, Stance::Man_WalkingJump_RH_1D_25_11);

                            }                     
                            else if (world.isEmptyTile(tile_R2) && world.isEmptyTile(tile_R3) &&
                                     world.isEmptyTile(tile_R2D) && world.isEmptyTile(tile_R3D)) {     

                                if (world.isWaterTile(tile_R2D2)) {

                                    uint8_t itemIdx = world.getItem(ItemType::LifeSaver_InWater_RH, ItemType::LifeSaver_Dissolve_InWater_RH);

                                    if (itemIdx == Constants::NoItem) {

                                        player.pushSequence(Stance::Man_Die_Water_RH_02_01, Stance::Man_Die_Water_RH_02_07);
                                        player.pushSequence(Stance::Man_WalkingJump_RH_2D_25_01, Stance::Man_WalkingJump_RH_2D_25_09);

                                    }
                                    else {

                                        uint8_t tile_D2 = world.getTile_RelativeToPlayer(0, -2);

                                        if (tile_D2 == Tiles::Water_Plain) {
                                     
                                            player.pushSequence(Stance::Man_Walk_RH_03, Stance::Man_Walk_RH_04);
                                            player.pushSequence(Stance::Man_WalkingJump_RH_25_01, Stance::Man_WalkingJump_RH_25_11);
                                            player.pushSequence(Stance::Man_Walk_RH_01, Stance::Man_Walk_RH_02);

                                        }
                                        else {

                                            player.pushSequence(Stance::Man_WalkingJump_RH_25_01, Stance::Man_WalkingJump_RH_25_11);

                                        }

                                    }

                                }
                                else {
                                    player.setFalls(0);
                                    player.pushSequence(Stance::Man_WalkingJump_RH_2D_25_01, Stance::Man_WalkingJump_RH_2D_25_11);
                                }

                            }                     

                        }
                        else {

                            uint8_t tile_U = world.getTile_RelativeToPlayer(0, 1);
                            uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                            uint8_t tile_LU = world.getTile_RelativeToPlayer(-1, 1);
                            uint8_t tile_R2U = world.getTile_RelativeToPlayer(2, 1);
                            uint8_t tile_R2 = world.getTile_RelativeToPlayer(2, 0);
                            uint8_t tile_R2D = world.getTile_RelativeToPlayer(2, -1);

                            if (world.isStairTile_L_Half(tile_D) ) {

                                player.pushSequence(Stance::Man_DescendStairs_RH_Half_01, Stance::Man_DescendStairs_RH_Half_04);

                            }
                            else if (world.canWalkOnTile(tile_R2D) && world.isEmptyTile(tile_R2) && world.isEmptyTile(tile_R2U) && world.isEmptyTile(tile_U)) {

                                player.pushSequence(Stance::Man_WalkingJump_RH_2_01, Stance::Man_WalkingJump_RH_2_08);

                            }
                            else if (world.isRopeSupport(tile_LU) && world.isRopeTile(tile_U)) {

                                player.pushSequence(Stance::Man_Rope_Start_RH_01, Stance::Man_Rope_Start_RH_07);

                            } 
                            else {

                                player.setFalls(0);
                                player.pushSequence(Stance::Man_Walk_FallDown_RH_01, Stance::Man_Walk_FallDown_RH_06);

                            }

                        }

                    }
                    else {

                        uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                        uint8_t tile_U = world.getTile_RelativeToPlayer(0, 1);
                        uint8_t tile_R3D2 = world.getTile_RelativeToPlayer(3, -2);
                        uint8_t tile_R2D = world.getTile_RelativeToPlayer(2, -1);

                        player.setFalls(0);

                        if (world.isVerticalVine_Upper(tile_R) || world.isVerticalVine_Middle(tile_R)) {

                            player.setFalls(1);
                            player.pushSequence(Stance::Man_Vine_Entry_RH_01, Stance::Man_Vine_Entry_RH_08);

                        }
                        else if (world.isSlideTile_Full_LH(tile_RD) && world.canWalkOnTile(tile_R3D2)) {

                            // player.setFalls(0);
                            player.pushSequence(Stance::Man_Slide_RH_Full_Land_01, Stance::Man_Slide_RH_Full_Land_13);

                        }
                        else if (world.isSlideTile_Full_LH(tile_RD) && !world.canWalkOnTile(tile_R3D2)) {
                            // player.setFalls(0);
                            player.pushSequence(Stance::Man_Slide_RH_Full_01, Stance::Man_Slide_RH_Full_13);

                        }
                        else if (world.isSlideTile_Full_LH(tile_RD) && !world.isSlideTile_Full_LH(tile_R3D2)) {

                            // player.setFalls(0);
                            player.pushSequence(Stance::Man_Slide_RH_Full_CanCont_01, Stance::Man_Slide_RH_Full_CanCont_12);

                        }
                        else if (world.isSlideTile_Full_RH(tile_RD) && !world.canWalkOnTile(tile_R3D2)) {

                            // player.setFalls(0);
                            player.pushSequence(Stance::Man_Slide_RH_Full_01, Stance::Man_Slide_RH_Full_13);

                        }
                        else if (world.isSlideTile_LH(tile_RD)) {

                            // player.setFalls(0);
                            player.pushSequence(Stance::Man_Slide_RH_01, Stance::Man_Slide_RH_11);

                        }
                        else if (world.isStairTile_R1(tile_R)) {

                            player.pushSequence(Stance::Man_ClimbStairs_RH_01, Stance::Man_ClimbStairs_RH_04);

                        }
                        else if (world.isStairTile_R_Half(tile_R)) {

                            player.pushSequence(Stance::Man_ClimbStairs_RH_Half_01, Stance::Man_ClimbStairs_RH_Half_04);

                        }
                        else if (world.isStairTile_R1(tile) || world.isStairTile_R_Half(tile)) {

                            player.pushSequence(Stance::Man_ClimbStairs_RH_05, Stance::Man_ClimbStairs_RH_08);

                        }
                        else if ((world.isStairTile_L1(tile_RD) || (world.isStairTile_L_Half(tile))) && player.getY() < 37) {  

                         player.pushSequence(Stance::Man_DescendStairs_RH_05, Stance::Man_DescendStairs_RH_08);

                        }
                        else if (world.isStairTile_L2(tile_RD)) {  //4, 6

                            player.pushSequence(Stance::Man_DescendStairs_RH_01, Stance::Man_DescendStairs_RH_08);

                        }                        
                        else if (world.isStairTile_L_Half(tile) && player.getY() < 37) {  

                            player.pushSequence(Stance::Man_DescendStairs_RH_Half_01, Stance::Man_DescendStairs_RH_Half_04);

                        }
                        else if (world.isStairTile_L1(tile)) {  

                            player.pushSequence(Stance::Man_DescendStairs_RH_01, Stance::Man_DescendStairs_RH_04);

                        }   
                        else if (tile == Tiles::Poker || tile_R == Tiles::Poker) {

                            if (justPressedOrPressed & A_BUTTON) {

                                world.setGameState(GameState::Play_Gamble_Select_Open);
                                playGame_HandleMenu(GameState::Play_Gamble_Select_Exit);

                            }
                            else if (world.canWalkPastTile(tile_R, Direction::Right)) {  

                                player.pushSequence(Stance::Man_Walk_RH_01, Stance::Man_Walk_RH_04);

                            }

                        }
                        else if (world.isLadderTile(tile_R)) {
           
                            if (world.getMiddleground() % 8 == 0 && world.canWalkPastTile(tile_R, Direction::Right)) {  

                                processLadder_MoveRight(player, tile_R);

                            }       
                            else if (world.canWalkPastTile(tile_R2, Direction::Right)) {

                                processLadder_MoveRight(player, tile_R2D);

                            }

                        }     
                        else if (world.canWalkPastTile(tile_R, Direction::Right)) {  

                            processLadder_MoveRight(player, tile_R);

                        }     

                        #ifdef SHOW_SIGN

                            else if(world.isSignTile(tile_R)) {

                                world.setGameState(GameState::Show_Sign);
                                endOfLevel_Counter = 0;

                            }

                        #endif                                                        
                        else {

                            if (justPressedOrPressed & A_BUTTON) {

                                if (!world.canWalkPastTile(tile_R) && world.canWalkOnTile(tile_R) && world.isEmptyTile(tile_U)) {     

                                    player.pushSequence(Stance::Man_StandingJump_RH_UPandOver_01, Stance::Man_StandingJump_RH_UPandOver_06);

                                }          

                            }
                            else if (world.isStairTile_R1(tile_R) || world.isStairTile_R_Half(tile_R)) {

                                player.pushSequence(Stance::Man_ClimbStairs_RH_01, Stance::Man_ClimbStairs_RH_04);

                            }
                            else if (world.isStairTile_R2(tile_R)) {

                                player.pushSequence(Stance::Man_ClimbStairs_RH_05, Stance::Man_ClimbStairs_RH_08);

                            }

                        }

                    }

                }                    
                break;

            case Direction::Forward:
                player.push(Stance::Man_Walk_RH_00);
                break;

            case Direction::Backward:
                {
                    uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                    uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);
                    uint8_t tile_U = world.getTile_RelativeToPlayer(0, 1);
                    uint8_t tile_RU = world.getTile_RelativeToPlayer(1, 1);
                    uint8_t tile_R2 = world.getTile_RelativeToPlayer(2, 0);
                    uint8_t tile_R2U = world.getTile_RelativeToPlayer(2, 1);
                    uint8_t tile_R2D = world.getTile_RelativeToPlayer(2, -1);

                    if (!world.canWalkPastTile(tile_RU) && !world.isRopeTile(tile_RU) && world.isRopeTile(tile_U)) {

                        // Do nothing ..

                    }   
                    else if ((world.isVerticalVine_Upper(tile) && world.isVerticalVine_Upper(tile_R)) ||
                            (world.isVerticalVine_Middle(tile) && world.isVerticalVine_Middle(tile_R))) {

                        if (world.isEmptyTile(tile_R2)) {
                            player.setFalls(1);
                            player.pushSequence(Stance::Man_Vine_Exit_RH_01, Stance::Man_Vine_Exit_RH_08);
                        }
                        else { /* Do nothing, prevents a turn */}

                    }
                    else if (world.isRopeTile(tile_U) && world.isRopeTile(tile_RU) && world.isRopeSupport(tile_R2U)) {

                        player.pushSequence(Stance::Man_Rope_End_RH_01, Stance::Man_Rope_End_RH_06);

                    }  
                    else if (world.isRopeTile(tile_U) && world.isRopeTile(tile_RU)) {

                        player.pushSequence(Stance::Man_Rope_Start_RH_04, Stance::Man_Rope_Start_RH_07);

                    }                                                                 
                    else {
        
                        player.push(Stance::Man_Walk_RH_00);

                    } 

                }
                break;

            case Direction::Left:
                player.push(Stance::Man_Walk_FW_01);
                break;

        }

    }

    else if (justPressedOrPressed & A_BUTTON) {

        switch (player.getDirection()) {

            case Direction::Backward:

                switch (stance) {

                    case Stance::Man_ClimbLadder_BK_LH_UP_01 ... Stance::Man_ClimbLadder_BK_LH_UP_14:
                    case Stance::Man_ClimbLadder_BK_RH_UP_01 ... Stance::Man_ClimbLadder_BK_RH_UP_14:
                    case Stance::Man_ClimbLadder_BK_LH_DOWN_01 ... Stance::Man_ClimbLadder_BK_LH_DOWN_14:
                    case Stance::Man_ClimbLadder_BK_RH_DOWN_01 ... Stance::Man_ClimbLadder_BK_RH_DOWN_14:   
                    case Stance::Man_Rope_Start_LH_01 ... Stance::Man_Rope_Start_LH_07:
                    case Stance::Man_Rope_End_LH_01 ... Stance::Man_Rope_End_LH_06:
                    case Stance::Man_Rope_Start_RH_01 ... Stance::Man_Rope_Start_RH_07:
                    case Stance::Man_Rope_End_RH_01 ... Stance::Man_Rope_End_RH_06:
                        break;

                    default:

                        player.stageSequence(Stance::Man_StandingJump_BK_01, Stance::Man_StandingJump_BK_07); 
                        break;
                    
                }

                break;

            case Direction::Right:
                {
                    uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                    uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);

                    if (tile == Tiles::Poker || tile_R == Tiles::Poker) {

                        if (justPressed & A_BUTTON) {

                            world.setGameState(GameState::Play_Gamble_Select_Open);
                            playGame_HandleMenu(GameState::Play_Gamble_Select_Exit);

                        }

                    }
                    else {
                        playGame_HandleGamePlay_Basics(player, Stance::Man_Start);
                    }
    
                }                
                break;

            case Direction::Forward:
                {
                    uint8_t tile = world.getTile_RelativeToPlayer(0, 0);

                    if (tile == 0) {

                        player.stageSequence(Stance::Man_StandingJump_FW_01, Stance::Man_StandingJump_FW_07); 

                    }
                    else {

                        player.stageSequence(Stance::Man_StandingJump_FW_UP_01, Stance::Man_StandingJump_FW_UP_06); 

                    }

                }
                break;

            case Direction::Left:
                {
                    uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                    uint8_t tile_L = world.getTile_RelativeToPlayer(-1, 0);

                    if (tile == Tiles::Poker || tile_L == Tiles::Poker) {

                        if (justPressed & A_BUTTON) {

                            world.setGameState(GameState::Play_Gamble_Select_Open);
                            playGame_HandleMenu(GameState::Play_Gamble_Select_Exit);

                        }

                    }
                    else {
                        playGame_HandleGamePlay_Basics(player, Constants::Player_Stance_Offset);
                    }

                }
                break;

        }

    }

    #endif
}

void playGame_HandleGamePlay_Basics(Player &player, Stance stanceOffset) {

    #ifndef DEBUG_DISABLE_PLAY

    uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
    uint8_t tile_U = world.getTile_RelativeToPlayer(0, 2);

    if (world.isEmptyTile(tile_U)) {

        if (world.canJumpUpOntoTile(tile)) {

            player.stageSequence(Stance::Man_StandingJump_RH_UP_01 + stanceOffset, Stance::Man_StandingJump_RH_UP_06 + stanceOffset); 

            if (tile == Tiles::Rollers_Left) {

                player.pushSequence(Stance::Man_Rollers_RH_01, Stance::Man_Rollers_RH_04);
                player.stageSequence(Stance::Man_StandingJump_RH_UP_01 + stanceOffset, Stance::Man_StandingJump_RH_UP_06 + stanceOffset); 

            }
            else if (tile == Tiles::Rollers_Right) {

                player.pushSequence(Stance::Man_Rollers_LH_01, Stance::Man_Rollers_LH_04);
                player.stageSequence(Stance::Man_StandingJump_RH_UP_01 + stanceOffset, Stance::Man_StandingJump_RH_UP_06 + stanceOffset); 

            }

            else {

                player.stageSequence(Stance::Man_StandingJump_RH_UP_01 + stanceOffset, Stance::Man_StandingJump_RH_UP_06 + stanceOffset); 

            }

        }
        else if (world.isSpringTile(tile)) {    

            #ifdef BOUNCEJUMP_3

            uint8_t tile_3U = world.getTile_RelativeToPlayer(0, 3);
            uint8_t tile_4U = world.getTile_RelativeToPlayer(0, 4);

            if (world.isRopeTile(tile_3U)) {

                player.stageSequence(Stance::Man_BounceJump_RH_3_01 + stanceOffset, Stance::Man_BounceJump_RH_3_32 + stanceOffset);

            }
            else if (world.isRopeTile(tile_4U)) {

                player.stageSequence(Stance::Man_BounceJump_RH_4_01 + stanceOffset, Stance::Man_BounceJump_RH_4_34 + stanceOffset);

            }

            #else

            uint8_t tile_4U = world.getTile_RelativeToPlayer(0, 4);

            if (world.isRopeTile(tile_4U)) {

                player.stageSequence(Stance::Man_BounceJump_RH_4_01 + stanceOffset, Stance::Man_BounceJump_RH_4_34 + stanceOffset);

            }
            
            #endif

        }   
        else {

            player.stageSequence(Stance::Man_StandingJump_RH_01 + stanceOffset, Stance::Man_StandingJump_RH_07 + stanceOffset); 

        }

    }
    else {

        player.stageSequence(Stance::Man_StandingJump_Small_RH_01 + stanceOffset, Stance::Man_StandingJump_Small_RH_03 + stanceOffset); 

    }

    #endif

}


void playGame_HandleJump(Player &player, uint8_t pressed) {

    #ifndef DEBUG_DISABLE_PLAY

    Stance stance = player.getStance();

    if (pressed & A_BUTTON) {

        switch (stance) {

            case Stance::Man_Walk_RH_01:
                {

                    uint8_t tile_D2 = world.getTile_RelativeToPlayer(0, -2);
                    uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);
                    uint8_t tile_RU = world.getTile_RelativeToPlayer(1, 1);
                    uint8_t tile_RD = world.getTile_RelativeToPlayer(1, -1);
                    uint8_t tile_R2D = world.getTile_RelativeToPlayer(2, -1);

                    if (tile_D2 == Tiles::Water_Plain) {

                        // Do nothing ..

                    }
                    else if (world.canJumpUpOntoTile(tile_R)) {

                        player.pushSequence(Stance::Man_WalkingJump_RH_UP_01, Stance::Man_WalkingJump_RH_UP_05, true); 

                    }
                    else if (world.isPunjiTile(tile_R)) {

                        player.pushSequence(Stance::Man_WalkingJump_RH_25_02, Stance::Man_WalkingJump_RH_25_11, true); 

                    }     
                    else if (world.canWalkPastTile(tile_R) && world.canWalkOnTile(tile_R2D)) {

                        player.pushSequence(Stance::Man_WalkingJump_RH_2_02, Stance::Man_WalkingJump_RH_2_08, true); 

                    }
                    else {

                        player.pushSequence(Stance::Man_WalkingJump_RH_02, Stance::Man_WalkingJump_RH_08, true); 

                    }

                }
                break;

            case Stance::Man_Rollers_RH_01:
            case Stance::Man_Rollers_Stand_RH_01:
            case Stance::Man_Rollers_Fall_RH_01:
                {
                    uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);
                    uint8_t tile_RD = world.getTile_RelativeToPlayer(1, -1);
                    uint8_t tile_R2D = world.getTile_RelativeToPlayer(2, -1);
                    uint8_t tile_R3D = world.getTile_RelativeToPlayer(3, -1);

                    if (world.isEmptyTile(tile_R) && world.isEmptyTile(tile_RD) && world.isEmptyTile(tile_R2D) && world.canWalkOnTile(tile_R3D)) {

                        player.pushSequence(Stance::Man_WalkingJump_RH_25_02, Stance::Man_WalkingJump_RH_25_11, true); 

                    }     
                    else if (world.isEmptyTile(tile_R) && world.canWalkOnTile(tile_RD) && world.canWalkOnTile(tile_R3D)) {

                        player.pushSequence(Stance::Man_WalkingJump_RH_2_02, Stance::Man_WalkingJump_RH_2_08, true); 

                    }     

                }
                break;

            case Stance::Man_Walk_LH_01:
                {                            
                    uint8_t tile_D2 = world.getTile_RelativeToPlayer(0, -2);
                    uint8_t tile_L = world.getTile_RelativeToPlayer(-1, 0);
                    uint8_t tile_LD = world.getTile_RelativeToPlayer(-1, -1);
                    uint8_t tile_L2D = world.getTile_RelativeToPlayer(-2, -1);

                    if (tile_D2 == Tiles::Water_Plain) {

                        // Do nothing ..

                    }
                    else if (world.canJumpUpOntoTile(tile_L)) {

                        player.pushSequence(Stance::Man_WalkingJump_LH_UP_01, Stance::Man_WalkingJump_LH_UP_05, true); 

                    }
                    else if (world.isPunjiTile(tile_L)) {

                        player.pushSequence(Stance::Man_WalkingJump_LH_25_02, Stance::Man_WalkingJump_LH_25_11, true); 

                    }
                    else if (world.canWalkPastTile(tile_L) && world.canWalkOnTile(tile_L2D)) {

                        player.pushSequence(Stance::Man_WalkingJump_LH_2_02, Stance::Man_WalkingJump_LH_2_08, true); 

                    }
                    else {

                        player.pushSequence(Stance::Man_WalkingJump_LH_02, Stance::Man_WalkingJump_LH_08, true); 

                    }

                }
                
                break;

            case Stance::Man_Rollers_LH_01:
            case Stance::Man_Rollers_Stand_LH_01:
            case Stance::Man_Rollers_Fall_LH_01:
                {
                    uint8_t tile_L = world.getTile_RelativeToPlayer(-1, 0);
                    uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                    uint8_t tile_LD = world.getTile_RelativeToPlayer(-1, -1);
                    uint8_t tile_L2D = world.getTile_RelativeToPlayer(-2, -1);

                    if (world.isEmptyTile(tile_L) && world.isEmptyTile(tile_D) && world.isEmptyTile(tile_LD) && world.canWalkOnTile(tile_L2D)) {

                        player.pushSequence(Stance::Man_WalkingJump_LH_25_02, Stance::Man_WalkingJump_LH_25_11, true); 

                    }     
                    else if (world.isEmptyTile(tile_L) && world.canWalkOnTile(tile_D) && world.canWalkOnTile(tile_LD)) {

                        player.pushSequence(Stance::Man_WalkingJump_LH_2_02, Stance::Man_WalkingJump_LH_2_08, true); 

                    }     

                }
                break;

            default:
                break;

        }

    }

    #endif

}

void playGame_HandleSwordFight_Player(Player &player, uint8_t pressed, uint8_t justPressed) {

    #ifndef DEBUG_DISABLE_PLAY

    uint8_t justPressedOrPressed = pressed | justPressed;
    int16_t dist = getDistanceBetween(player, EnemyType::SwordFighter);
    
    uint16_t offset = 0;
    if (player.getDirection() == Direction::Left) offset = Constants::Player_Stance_Offset;

    if (justPressedOrPressed & A_BUTTON) {

        player.pushSequence(Stance::Man_Sword_StandingJump_RH_01 + offset, Stance::Man_Sword_StandingJump_RH_07 + offset);

    }

    else if (justPressedOrPressed & DOWN_BUTTON) {

        world.setGameState(GameState::Play_Game);
        player.setStance(Stance::Man_Walk_RH_00);

    }

    else if (justPressedOrPressed & B_BUTTON) {

        player.pushSequence(Stance::Man_Sword_Lunge_RH_01 + offset, Stance::Man_Sword_Lunge_RH_06 + offset);

    }

    else if (justPressedOrPressed & RIGHT_BUTTON) {

        switch (player.getDirection()) {

            case Direction::Left:
                
                if (dist > 0) {
                    player.pushSequence(Stance::Man_Sword_Walk_BK_LH_01, Stance::Man_Sword_Walk_BK_LH_02);
                }
                else {
                    player.push(Stance::Man_Sword_Stationary_RH);            
                }

                break;

            case Direction::Right:

                player.pushSequence(Stance::Man_Sword_Walk_RH_01, Stance::Man_Sword_Walk_RH_02);
                break;
                
        }

        

    }

    else if (justPressedOrPressed & LEFT_BUTTON) {

        switch (player.getDirection()) {

            case Direction::Left:

                player.pushSequence(Stance::Man_Sword_Walk_LH_01, Stance::Man_Sword_Walk_LH_02);
                break;

            case Direction::Right:

                if (dist < 0) {
                    player.pushSequence(Stance::Man_Sword_Walk_BK_RH_01, Stance::Man_Sword_Walk_BK_RH_02);
                }
                else {
                    player.push(Stance::Man_Sword_Stationary_LH);            
                }

                break;
                
        }

    }

    #endif

}


void playGame_Update(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {
    
    #ifndef DEBUG_DISABLE_PLAY

    Player &player = world.getPlayer();

    world.incFrameCount();
        
    if (world.getFrameCount() % 4 == 0) {
    
        uint8_t pressed = getPressedButtons();
        uint8_t justPressed = getJustPressedButtons();

        if (player.isEmpty()) {

            switch (world.getGameState()) {
                
                #ifdef SHOW_SIGN

                case GameState::Show_Sign:

                    if (justPressed & B_BUTTON) {
                        playGame_HandleMenu(GameState::Inventory_Open);
                    }

                    break;

                #endif

                case GameState::Inventory_Open:

                    if (justPressed & B_BUTTON) {
                        playGame_HandleMenu(GameState::Inventory_Open);
                    }
                    else {
                        playGame_HandleMenu(player, pressed, justPressed);
                    }

                    break;
                
                case GameState::Inventory_Open_More_Reset:
                case GameState::Inventory_Open_More_Exit:
                case GameState::Inventory_Open_Exit_0:
                case GameState::Inventory_Open_Exit_1:
                case GameState::Inventory_Open_Reset_0:
                case GameState::Inventory_Open_Reset_1:
                case GameState::Inventory_Open_Reset_Exit_0:
                case GameState::Inventory_Open_Reset_Exit_1:

                    if (justPressed & B_BUTTON) {
                        world.setGameState(GameState::Inventory_Open);
                    }
                    else {
                        playGame_HandleMenu(player, pressed, justPressed);
                    }

                    break;

                case GameState::Play_Game:

                    if (justPressed & B_BUTTON) {
                        playGame_HandleMenu(GameState::Inventory_Open);
                    }
                    else {

                        if (ignoreKeyPress == 0) {
                            playGame_HandleGamePlay(player, pressed, justPressed);          
                        }

                    }

                    break;

                case GameState::Chakana_Open:

                    // if (justPressed & A_BUTTON || justPressed & B_BUTTON) {
                    if (justPressed & AB_BUTTON) {

                        if (world.allPortsComplete()) {

                            cookie.hasSavedGame = false;
                            #ifndef DEBUG
                            saveCookie(true);
                            #endif
                            world.setGameState(GameState::Title_Init);

                        }
                        else {

                            player.setChakanas(player.getChakanas() + titleCounter);
                            world.setGameState(GameState::Map_Init);

                        }

                    }

                    break;

                case GameState::Play_Dead:

                    // if (justPressed & A_BUTTON || justPressed & B_BUTTON) {
                    if (justPressed & AB_BUTTON) {

                        if (player.getLives() > 1) {

                            FX::loadGameState((uint8_t*)&cookie, sizeof(cookie));
                            player.setHealth(Constants::HealthMax);
                            player.setLives(player.getLives() - 1);

                        }
                        else {

                            cookie.hasSavedGame = false;
                            world.setGameState(GameState::Title_Init);

                        }

                        #ifndef DEBUG
                        saveCookie(true);
                        #endif

                    }

                    break;

                case GameState::Play_Battle:

                    playGame_HandleSwordFight_Player(player, pressed, justPressed);          
                    break;

                case GameState::Play_Gamble_Select_Exit ... GameState::Play_Gamble_End:

                    playGame_HandleGamble(player, justPressed);
                    pressed = 0;
                    justPressed = 0;
                    break;

            }


            // Check for the trapdoor ..

            #ifdef TRAP_DOOR

                Rect playerRect = { 59, Constants::GroundY - player.getY(), 10, 16 };

                for (uint8_t i = 0; i < Constants::ItemCount_Level; i++) {
            
                    Item &item = world.getItem(i);


                    // If the item is the 'puff' then we are at the last of the items, stop iterating ..

                    if (item.getItemType() == ItemType::Puff) break;


                    // If not a trap door then skip ..

                    if (item.getItemType() != ItemType::TrapDoor) continue;


                    // Otherwise check if we have collided ..

                    Rect itemRect = { item.getX() + world.getMiddleground() - 4 + 1, item.getY() + 1, 14, 14 };

                    if (item.getFrame() != 7) {

                        itemRect = { item.getX() + world.getMiddleground() - 4 + 3, item.getY() + 1, 10, 2 };

                        if (item.getData() == 0 && collide(playerRect, itemRect)) {

                            item.setData(1);
                            killPlayer(player);

                        }

                    }

                }

            #endif

        }
        else {

            switch (world.getGameState()) {

                case GameState::Play_Game:
                    playGame_HandleJump(player, pressed);
                    break;

            }

        }

        if (!player.isEmpty() || player.hasStagedSequence()) {

            Point offset;
            uint16_t stance = player.getStance();;

            if (!player.isEmpty()) {

                stance = playGame_PopEntry(player);

            }


            // Has the player collided with an item?

            for (uint8_t i = 0; i < Constants::ItemCount_Level; i++) {
          
                Rect playerRect = { 59, Constants::GroundY - player.getY(), 10, 16 };
                Item &item = world.getItem(i);

                
                // Can we skip this one?

//                if (item.getItemType() == ItemType::MysteryCrate && item.getFrame() == 8) continue;
                if (item.getItemType() == ItemType::MysteryCrate){//SJH revet to above/
                    if (item.getFrame() == 8) continue;
                }


                // If the item is the 'puff' then we are at the last of the items, stop iterating ..

                if (item.getItemType() == ItemType::Puff) break;


                // Otherwise check if we have collided ..

                Rect itemRect = { item.getX() + world.getMiddleground() - 4 + 1, item.getY() + 1, 14, 14 };

                switch (item.getItemType()) {

                    case ItemType::Chakana_Small:

                        if (collide(playerRect, itemRect)) {

                            if (item.getCounter() == 0) {

                                launchPuff(item);
                                player.setChakanas(player.getChakanas() + item.getData());

                            }

                        }
                        break;

                    case ItemType::Key1:
                    case ItemType::PinchBar:
                    case ItemType::Hammer:
                    case ItemType::Amulet:
                    case ItemType::Potion:
                    case ItemType::Anchor:
                    case ItemType::Sword:
                    case ItemType::LifeSaver:
                    case ItemType::LifeSaver_Dissolve:

                        if (collide(playerRect, itemRect)) {

                            if (item.getCounter() == 0) {

                                launchPuff(item);

                            }

                        }
                        break;

                    case ItemType::Chakana:

                        itemRect.y = itemRect.y + 8;
                        itemRect.height = 2;
                        
                        if (collide(playerRect, itemRect) &&  world.getGameState() != GameState::Chakana_Open) {                        

                            ignoreKeyPress = 16;
                            player.stageSequence(Stance::None, Stance::None);

                            world.setGameState(GameState::Chakana_Open);
                            world.setPortVisited(world.getCurrentPort());
                            endOfLevel_Counter = 0;
                            titleCounter = a.randomLFSR(15, 30);
                            
                        }
                        break;

                    case ItemType::Lever_LH:
                    case ItemType::Lever_RH:

                        if (collide(playerRect, itemRect) && (justPressed & A_BUTTON)) {                        

                            ignoreKeyPress = 16;
                            player.stageSequence(Stance::None, Stance::None);

                            if (item.getItemType() == ItemType::Lever_LH)  {

                                item.setItemType(ItemType::Lever_RH);

                            }
                            else {

                                item.setItemType(ItemType::Lever_LH);

                            }

                            for (uint8_t x = 0; x < 15; x++) {

                                if (item.getData() & (1<<x)) {

                                    Item &item2 = world.getItem(i + x + 1);

                                    switch (item2.getItemType()) {

                                        case ItemType::Lever_Portal_Closed:
                                            item2.setFrame(1);
                                            item2.setCounter(0);
                                            break;

                                        case ItemType::Lever_Portal_Auto_Closed:
                                            item2.setFrame(1);
                                            item2.setCounter(0);
                                            break;

                                        default:
                                            item2.setFrame(8);
                                            item2.setCounter(0);
                                            break;

                                    }

                                }

                            }
                            
                        }
                        break;

                    case ItemType::Punji:
                            
                        if ((player.getStance() >= Stance::Man_WalkingJump_LH_25_01 && player.getStance() <= Stance::Man_WalkingJump_LH_25_11) ||
                            (player.getStance() >= Stance::Man_WalkingJump_RH_25_01 && player.getStance() <= Stance::Man_WalkingJump_RH_25_11)) {

                                // Do nothing. 
                        }
                        else {
                            
                            switch (player.getDirection()) {

                                case Direction::Left:
                                    playerRect.width = 1;
                                    break;

                                case Direction::Right:
                                    playerRect.x = playerRect.x + 8;
                                    playerRect.width = 1;//playerRect.width - 8;
                                    break;

                            }

                            playerRect.width = 1;
                            itemRect = { item.getX() + world.getMiddleground() - 4 + 4, item.getY() + 1, 8, 2 };

                            if (item.getCounter() == 0 && collide(playerRect, itemRect)) {

                                item.setCounter(1);
                                killPlayer(player);

                                // switch (player.getDirection()) {

                                //     case Direction::Left:
                                //         player.pushSequence(Stance::Man_Die_Fall_LH_01, Stance::Man_Die_Fall_LH_04, true);
                                //         break;

                                //     case Direction::Right:
                                //         player.pushSequence(Stance::Man_Die_Fall_RH_01, Stance::Man_Die_Fall_RH_04, true);
                                //         break;

                                // }

                            }

                        }

                        break;

                    case ItemType::Flame:
                        
                        itemRect = { item.getX() + world.getMiddleground() - 4 + 4, item.getY() + 14, 8, 2 };

                        if (collide(playerRect, itemRect)) {

                            switch (player.getDirection()) {

                                case Direction::Left:

                                    player.pushSequence(Stance::Man_Die_Fire_LH_01, Stance::Man_Die_Fire_LH_12, true);

                                    switch (stance) {

                                        case Stance::Man_WalkingJump_LH_2_08:
                                            {
                                                uint8_t xPos = item.getX() + world.getMiddleground();

                                                if (xPos == 56) {

                                                    player.push(Stance::Man_Die_Fire_Adj_LH_02);

                                                }
                                                else if (xPos == 64) {

                                                    player.push(Stance::Man_Die_Fire_Adj_LH_01);

                                                }

                                            }
                                            break;

                                        case Stance::Man_Walk_LH_02:

                                            player.pushSequence(Man_Walk_LH_03, Stance::Man_Walk_LH_06);

                                            break;


                                    }

                                    break;

                                case Direction::Right:

                                    switch (stance) {

                                        player.pushSequence(Stance::Man_Die_Fire_RH_01, Stance::Man_Die_Fire_RH_12, true);

                                        case Stance::Man_WalkingJump_RH_2_08:
                                            {
                                                uint8_t xPos = item.getX() + world.getMiddleground();

                                                if (xPos == 56) {

                                                    player.push(Stance::Man_Die_Fire_Adj_RH_01);

                                                }
                                                else if (xPos == 64) {

                                                    player.push(Stance::Man_Die_Fire_Adj_RH_02);

                                                }

                                            }
                                            break;

                                        case Stance::Man_Walk_RH_03:

                                            // player.pushSequence(Stance::Man_Die_Fire_RH_01, Stance::Man_Die_Fire_RH_12, true);
                                            player.pushSequence(Man_Walk_RH_04, Stance::Man_Walk_RH_06);

                                            break;

                                    }

                                    break;

                            }

                        }

                        break;

                    default:
                        break;

                }

            }


            // If a sequence has been staged then commit it now (and adjust the players position etc ..

            if (player.commitSequence()) {

                stance = playGame_PopEntry(player);

            }


            // Handle falling and other special actions ..

            switch (static_cast<Stance>(stance)) {

                case Stance::Man_Walk_FallLand_LH_03_Puff:
                case Stance::Man_Walk_FallLand_RH_03_Puff:
                    launchPuffLand(player);
                    break;

                case Stance::Man_Walk_RH_08:
                case Stance::Man_Walk_LH_08:
                case Stance::Man_Walk_RH_04:
                case Stance::Man_Walk_LH_04:
                case Stance::Man_WalkingJump_LH_08:
                case Stance::Man_WalkingJump_RH_08:
                case Stance::Man_Rollers_RH_04:
                case Stance::Man_Rollers_LH_04:
                case Stance::Man_WalkingJump_LH_25_11:
                case Stance::Man_WalkingJump_RH_25_11:
                case Stance::Man_WalkingJump_LH_2_08:
                case Stance::Man_WalkingJump_RH_2_08:
                    {
                  
                        uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                        uint8_t tile_RD = world.getTile_RelativeToPlayer(1, -1);
                        uint8_t tile_LD = world.getTile_RelativeToPlayer(-1, -1);

                        if (world.isRollerTile_RH(tile_D) && world.isRollerTile_RH(tile_RD)) {

                            player.pushSequence(Stance::Man_Rollers_RH_01, Stance::Man_Rollers_RH_04);

                        }
                        else if (world.isRollerTile_LH(tile_D) && world.isRollerTile_LH(tile_LD)) {

                            player.pushSequence(Stance::Man_Rollers_LH_01, Stance::Man_Rollers_LH_04);

                        }

                        else if (world.isRollerTile_RH(tile_D) && world.canWalkOnTile(tile_RD)) {

                            player.pushSequence(Stance::Man_Rollers_Stand_RH_01, Stance::Man_Rollers_Stand_RH_04);

                        }
                        else if (world.isRollerTile_LH(tile_D) && world.canWalkOnTile(tile_LD)) {

                            player.pushSequence(Stance::Man_Rollers_Stand_LH_01, Stance::Man_Rollers_Stand_LH_04);

                        }

                        else if (world.isRollerTile_RH(tile_D) && world.isEmptyTile(tile_RD)) {

                            player.setFalls(0);
                            player.pushSequence(Stance::Man_Rollers_Fall_RH_01, Stance::Man_Rollers_Fall_RH_04);

                        }
                        else if (world.isRollerTile_LH(tile_D) && world.isEmptyTile(tile_LD)) {

                            player.setFalls(0);
                            player.pushSequence(Stance::Man_Rollers_Fall_LH_01, Stance::Man_Rollers_Fall_LH_04);
                            
                        }

                    }
                    break;

                case Stance::Man_Walk_FallMore_BK_02:
                    {
                           
                        uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                        uint8_t tile_D2 = world.getTile_RelativeToPlayer(0, -2);
  
                        if (world.isEmptyTile(tile_D) || world.isSpringTile(tile_D)) {

                            player.incFalls();

                            if (world.isEmptyTile(tile_D2) || world.isSpringTile(tile_D2)) {    
                            
                                player.pushSequence(Stance::Man_Walk_FallMore_BK_01, Stance::Man_Walk_FallMore_BK_02); 

                            }
                            else {

//                                 if (player.getFalls() >= 3) {

//                                     if (world.isSpringTile(tile_D)) {
                                    
//                                         player.pushSequence(Stance::Man_Walk_FallLandSpring_BK_01, Stance::Man_Walk_FallLandSpring_BK_28);
//                                     }
//                                     else {

//                                         player.pushSequence(Stance::Man_Die_Fall_RH_01, Stance::Man_Die_Fall_RH_04); 
//                                         player.pushSequence(Stance::Man_Walk_FallLand_BK_01, Stance::Man_Walk_FallLand_BK_04);

//                                     }

//                                 }
//                                 else if (world.isSpringTile(tile_D)) {

//                                     player.pushSequence(Stance::Man_Walk_FallLandSpring_BK_01, Stance::Man_Walk_FallLandSpring_BK_28);

//                                 }                                
//                                 else if (world.isSpikeTile(tile_D)) {

//                                     player.pushSequence(Stance::Man_Die_Fall_RH_01, Stance::Man_Die_Fall_RH_04); 
//                                     player.pushSequence(Stance::Man_Walk_FallLand_BK_01, Stance::Man_Walk_FallLand_BK_04);

//                                 }
//                                 else if (world.isWaterTile(tile_D)) {

// ///SJH Need graphics for this!
//                                     player.pushSequence(Stance::Man_Die_Fall_RH_01, Stance::Man_Die_Fall_RH_04); 
//                                     player.pushSequence(Stance::Man_Walk_FallLand_BK_01, Stance::Man_Walk_FallLand_BK_04);

//                                 }
//                                 else {

//                                     if (!world.getMiddleground() % 8 != 0) {
                                    
//                                         player.pushSequence(Stance::Man_Walk_RH_03, Stance::Man_Walk_RH_04);

//                                     }

//                                     player.pushSequence(Stance::Man_Walk_RH_03, Stance::Man_Walk_RH_04);
//                                     player.pushSequence(Stance::Man_Walk_FallLand_BK_01, Stance::Man_Walk_FallLand_BK_04);
    
//                                 } 

                                if (world.isSpringTile(tile_D)) {

                                    player.pushSequence(Stance::Man_Walk_FallLandSpring_BK_01, Stance::Man_Walk_FallLandSpring_BK_28);

                                }                                
                                else if (world.isSpikeTile(tile_D) || world.isWaterTile(tile_D)) {

///SJH Need graphics for this!
                                    player.pushSequence(Stance::Man_Die_Fall_RH_01, Stance::Man_Die_Fall_RH_04); 
                                    player.pushSequence(Stance::Man_Walk_FallLand_BK_01, Stance::Man_Walk_FallLand_BK_04);

                                }
                                else {

                                    switch (player.getFalls()) {

                                        case 0 ... 2:

                                            if (world.getMiddleground() % 8 != 0) {
                                            
                                                player.pushSequence(Stance::Man_Walk_RH_03, Stance::Man_Walk_RH_04);

                                            }

                                            player.pushSequence(Stance::Man_Walk_FallLand_BK_01, Stance::Man_Walk_FallLand_BK_04); 

                                            break;

                                        case 3:

                                            if (world.getMiddleground() % 8 != 0) {
                                            
                                                player.pushSequence(Stance::Man_Walk_RH_03, Stance::Man_Walk_RH_04);

                                            }

                                            player.decHealth(2);
                                            player.pushSequence(Stance::Man_Walk_FallLand_BK_01_Puff, Stance::Man_Walk_FallLand_BK_04_Puff); 

                                            break;

                                        default:

                                            player.pushSequence(Stance::Man_Die_Fall_RH_01, Stance::Man_Die_Fall_RH_04); 
                                            player.pushSequence(Stance::Man_Walk_FallLand_BK_01, Stance::Man_Walk_FallLand_BK_04);
                                            break;

                                    }

                                } 

                            }

                        }
                        else {

                            player.setStance(Stance::Man_Walk_RH_02); 

                        }

                    }
                    break;

                case Stance::Man_Slide_RH_Full_Cont_08:       
                case Stance::Man_Slide_RH_Full_CanCont_12:       
                case Stance::Man_Slide_RH_Full_CanCont_13:       
                case Stance::Man_Slide_RH_Full_13:       
                    {
                        uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                        uint8_t tile_RD2 = world.getTile_RelativeToPlayer(1, -2);

                        if (tile_D == Tiles::Slide_LH_Full && tile_RD2 == Tiles::Slide_LH_Full) {

                            player.clear();
                            player.pushSequence(Stance::Man_Slide_RH_Full_Cont_01, Stance::Man_Slide_RH_Full_Cont_08);
                            break;

                        }

                    }

                    [[fallthrough]];

                case Stance::Man_Walk_FallDown_RH_06:
                case Stance::Man_Walk_FallMore_RH_02:
                case Stance::Man_WalkingJump_RH_1D_25_11:
                case Stance::Man_Slide_RH_11:
                case Stance::Man_Rollers_Fall_RH_04:
                case Stance::Man_Vine_Exit_RH_08:
                    {

                        uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                        uint8_t tile_D2 = world.getTile_RelativeToPlayer(0, -2);

                        // if (world.isEmptyTile(tile_D)) {

                        //     player.incFalls();

                        //     if (player.getFalls() < 3) {

                        //         if (world.isEmptyTile(tile_D2)) {                                    

                        //             player.pushSequence(Stance::Man_Walk_FallMore_RH_01, Stance::Man_Walk_FallMore_RH_02); 

                        //         }
                        //         else if (world.isSpikeTile(tile_D)) {

                        //             player.pushSequence(Stance::Man_Die_Fall_RH_01, Stance::Man_Die_Fall_RH_04); 
                        //             player.pushSequence(Stance::Man_Walk_FallLand_RH_01, Stance::Man_Walk_FallLand_RH_04);

                        //         }
                        //         else if (world.isWaterTile(tile_D)) {

                        //             player.pushSequence(Stance::Man_Die_Water_RH_01, Stance::Man_Die_Water_RH_07); 

                        //         }
                        //         else {

                        //             player.pushSequence(Stance::Man_Walk_FallLand_RH_01, Stance::Man_Walk_FallLand_RH_04);

                        //         } 

                        //     }
                        //     else {
                             
                        //         player.pushSequence(Stance::Man_Die_Fall_RH_01, Stance::Man_Die_Fall_RH_04); 
                        //         player.pushSequence(Stance::Man_Walk_FallMore_RH_01, Stance::Man_Walk_FallMore_RH_02); 
                        //         player.setFalls(0);

                        //     }

                        // }
                        // else {

                        //     player.setStance(Stance::Man_Walk_RH_02); 

                        // }

                        #ifdef FALL_THROUGH_PORTAL
                        if (world.isEmptyTile_XY(tile_D, 0, -1)) {
                        #else
                        if (world.isEmptyTile(tile_D)) {
                        #endif

                            #ifdef FALL_THROUGH_PORTAL
                                if (world.isEmptyTile_XY(tile_D2, 0, -2)) {

                                    player.pushSequence(Stance::Man_Walk_FallMore_RH_01, Stance::Man_Walk_FallMore_RH_02); 
                                    player.incFalls();

                                }
                            #else
                                if (world.isEmptyTile(tile_D2)) {

                                    player.pushSequence(Stance::Man_Walk_FallMore_RH_01, Stance::Man_Walk_FallMore_RH_02); 
                                    player.incFalls();

                                }
                            #endif

                            else if (world.isSpikeTile(tile_D)) {

                                player.pushSequence(Stance::Man_Die_Fall_RH_01, Stance::Man_Die_Fall_RH_04); 
                                player.pushSequence(Stance::Man_Walk_FallLand_RH_01, Stance::Man_Walk_FallLand_RH_04); 

                            }
                            else if (world.isWaterTile(tile_D)) {

                                player.pushSequence(Stance::Man_Die_Water_RH_01, Stance::Man_Die_Water_RH_07);                                    

                            }                                    
                            else {

                                switch (player.getFalls()) {

                                    case 0 ... 2:
                                        player.pushSequence(Stance::Man_Walk_FallLand_RH_01, Stance::Man_Walk_FallLand_RH_04); 
                                        break;

                                    case 3:
                                        player.decHealth(2);
                                        player.pushSequence(Stance::Man_Walk_FallLand_RH_01_Puff, Stance::Man_Walk_FallLand_RH_04_Puff); 
                                        break;

                                    default:
                                        player.pushSequence(Stance::Man_Die_Fall_RH_01, Stance::Man_Die_Fall_RH_04); 
                                        player.pushSequence(Stance::Man_Walk_FallMore_RH_01, Stance::Man_Walk_FallMore_RH_02); 
                                        break;

                                }

                            }

                        }
                        else {

                            player.setStance(Stance::Man_Walk_RH_02); 

                        }

                    }
                    break;

                case Stance::Man_Slide_LH_Full_Cont_08:       
                case Stance::Man_Slide_LH_Full_CanCont_12:       
                case Stance::Man_Slide_LH_Full_CanCont_13:       
                case Stance::Man_Slide_LH_Full_13:       
                    {

                        uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                        uint8_t tile_LD2 = world.getTile_RelativeToPlayer(-1, -2);

                        if (tile_D == Tiles::Slide_RH_Full && tile_LD2 == Tiles::Slide_RH_Full) {

                            player.clear();
                            player.pushSequence(Stance::Man_Slide_LH_Full_Cont_01, Stance::Man_Slide_LH_Full_Cont_08);
                            break;

                        }

                    }

                    [[fallthrough]];

                case Stance::Man_Walk_FallDown_LH_06:
                case Stance::Man_Walk_FallMore_LH_02:
                case Stance::Man_WalkingJump_LH_1D_25_11:
                case Stance::Man_Slide_LH_11:
                case Stance::Man_Rollers_Fall_LH_04:
                case Stance::Man_Vine_Exit_LH_08:
                    {
                           
                        uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                        uint8_t tile_D2 = world.getTile_RelativeToPlayer(0, -2);
                            
                        #ifdef FALL_THROUGH_PORTAL    
                        if (world.isEmptyTile_XY(tile_D, 0, -1)) {
                        #else
                        if (world.isEmptyTile(tile_D)) {
                        #endif

                            #ifdef FALL_THROUGH_PORTAL    
                                if (world.isEmptyTile_XY(tile_D2, 0, -2)) {

                                    player.pushSequence(Stance::Man_Walk_FallMore_LH_01, Stance::Man_Walk_FallMore_LH_02); 
                                    player.incFalls();

                                }
                            #else
                                if (world.isEmptyTile(tile_D2)) {

                                    player.pushSequence(Stance::Man_Walk_FallMore_LH_01, Stance::Man_Walk_FallMore_LH_02); 
                                    player.incFalls();

                                }
                            #endif

                            else if (world.isSpikeTile(tile_D)) {

                                player.pushSequence(Stance::Man_Die_Fall_LH_01, Stance::Man_Die_Fall_LH_04); 
                                player.pushSequence(Stance::Man_Walk_FallLand_LH_01, Stance::Man_Walk_FallLand_LH_04); 

                            }
                            else if (world.isWaterTile(tile_D)) {

                                player.pushSequence(Stance::Man_Die_Water_LH_01, Stance::Man_Die_Water_LH_07);                                    

                            }                                    
                            else {

                                switch (player.getFalls()) {

                                    case 0 ... 2:
                                        player.pushSequence(Stance::Man_Walk_FallLand_LH_01, Stance::Man_Walk_FallLand_LH_04); 
                                        break;

                                    case 3:
                                        player.decHealth(2);
                                        player.pushSequence(Stance::Man_Walk_FallLand_LH_01_Puff, Stance::Man_Walk_FallLand_LH_04_Puff); 
                                        break;

                                    default:
                                        player.pushSequence(Stance::Man_Die_Fall_LH_01, Stance::Man_Die_Fall_LH_04); 
                                        player.pushSequence(Stance::Man_Walk_FallMore_LH_01, Stance::Man_Walk_FallMore_LH_02); 
                                        break;

                                }

                            }

                        }
                        else {

                            player.setStance(Stance::Man_Walk_LH_02); 

                        }

                    }
                    break;

                        
                case Stance::Man_Sword_Lunge_LH_03:
                case Stance::Man_Sword_Lunge_RH_03:
                    {
                        Enemy &enemy = world.getEnemy(player.getEnemyIdx());
                        uint8_t tile_L = world.getTile_FromCoords(enemy.getX(), enemy.getY());
                        uint8_t tile_R = world.getTile_FromCoords(enemy.getX() + 16, enemy.getY());

                        if (enemy.getSwordWound() == 0 && playGame_PlayerStabsEnemy(player)) {

                            enemy.decHealth(1);
                            enemy.setSwordWound(12);

                            if (enemy.getHealth() > 0) {
                                    
                                switch (enemy.getDirection()) {

                                    case Direction::Left:

                                        #ifdef DEBUG_ENEMY_SWORD
                                        DEBUG_PRINT("X LH");
                                        #endif 

                                        if (tile_R == Tiles::Blank) {
                                            enemy.insertSequence(Stance::Enemy_Sword_Walk_BK_LH_01, Stance::Enemy_Sword_Walk_BK_LH_04);
                                        }
                                        break;

                                    case Direction::Right:

                                        #ifdef DEBUG_ENEMY_SWORD
                                        DEBUG_PRINT("X RH");
                                        #endif 
                                   
                                        if (tile_L == Tiles::Blank) {
                                            enemy.insertSequence(Stance::Enemy_Sword_Walk_BK_RH_01, Stance::Enemy_Sword_Walk_BK_RH_04);
                                        }
                                        break;
                                    
                                }      

                            }
                            else {

                                int16_t dist = getDistanceBetween(enemy);
                                world.setGameState(GameState::Play_Game);

                                player.removeInventoryItem(menu.getY());
                                menu.decY();
                                enemy.clear();

                                // player puts away sword ..

                                switch (player.getDirection()) {

                                    case Direction::Left:
                                        player.insert(Stance::Man_Walk_LH_00);
                                        break;

                                    case Direction::Right:
                                        player.insert(Stance::Man_Walk_RH_00);
                                        break;

                                }


                                // Enemy dies but whch direction does he fall?

                                switch (dist) {

                                    case -999 ... 0:

                                        switch (enemy.getDirection()) {

                                            case Direction::Left:

                                                enemy.pushSequence(Stance::Enemy_Die_BWD_LH_01, Stance::Enemy_Die_BWD_LH_13);
                                                break;

                                            case Direction::Right:

                                                enemy.pushSequence(Stance::Enemy_Die_FWD_RH_01, Stance::Enemy_Die_FWD_RH_13);
                                                break;

                                        }

                                        break;

                                    case 1 ... 999:

                                        switch (enemy.getDirection()) {

                                            case Direction::Left:

                                                enemy.pushSequence(Stance::Enemy_Die_FWD_LH_01, Stance::Enemy_Die_FWD_LH_13);
                                                break;

                                            case Direction::Right:

                                                enemy.pushSequence(Stance::Enemy_Die_BWD_RH_01, Stance::Enemy_Die_BWD_RH_13);
                                                break;

                                        }

                                        break;

                                }   


                            }                      

                        }

                    }

                    break;

                case Stance::Man_Die_Fire_LH_12:
                case Stance::Man_Die_Fire_RH_12:
                case Stance::Man_Die_Arrow_FallForward_LH_04:
                case Stance::Man_Die_Arrow_FallForward_RH_04:
                case Stance::Man_Die_Arrow_FallBackward_LH_04:
                case Stance::Man_Die_Arrow_FallBackward_RH_04:
                case Stance::Man_Die_Fall_LH_04:
                case Stance::Man_Die_Fall_RH_04:
                case Stance::Man_Die_Water_LH_07:
                case Stance::Man_Die_Water_RH_07:
                case Stance::Man_Die_Water_LH_02_07:
                case Stance::Man_Die_Water_RH_02_07:
                case Stance::Man_Die_BWD_LH_04:
                case Stance::Man_Die_BWD_RH_04:
                case Stance::Man_Die_FWD_LH_04:
                case Stance::Man_Die_FWD_RH_04:

                    player.setHealth(0);
                    world.setGameState(GameState::Play_Dead);
                    endOfLevel_Counter = 0;

                    break;

                default:
                    {
                        FX::seekData(Constants::SubsititueStance + (static_cast<uint16_t>(stance) * 2));
                        uint16_t subsituteStance = FX::readPendingUInt16();
                        FX::readEnd();

                        if (subsituteStance != 65535) {
                            player.setStance(subsituteStance);
                        }

                    }
                    break;

            }

        }

        playGame_HandleEnemies(a);

    }

    playGame_HandleMenu_OpenClose();
    world.updateEnemies(a);
    player.update();


    // End of level?

    if (endOfLevel_Counter < 14 && world.getFrameCount() % 2 == 0) {

        endOfLevel_Counter++;

    }


    // Housekeeping ..

    if (ignoreKeyPress > 0) {
        ignoreKeyPress--;
    }

    #endif

}

uint16_t playGame_PopEntry(Player &player) {

    #ifndef DEBUG_DISABLE_PLAY
    uint16_t stance = player.pop();

    player.setStance(stance);

    StanceDetails stanceDetails;

    FX::seekData(Constants::StanceDetails + (static_cast<uint16_t>(stance) * 4));
    FX::readObject(stanceDetails);
    FX::readEnd();

    player.setY(player.getY() - stanceDetails.stanceY);
    
    if (world.incMiddleground(stanceDetails.middleground)) {
        world.incForeground(stanceDetails.foreground);
        world.incBackground(stanceDetails.background);
    }

    return stance;

    #endif

}

void playGame(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    #ifndef DEBUG_DISABLE_PLAY

    Player &player = world.getPlayer();

    if (a.needsUpdate()) playGame_Update(a);

    uint8_t yOffset = world.getYOffsetForRendering();
    currentPlane = a.currentPlane();

    renderWorld();

    switch (world.getGameState()) {

        case GameState::Chakana_Open:
            {
                uint8_t frame = (world.allPortsComplete() ? 16 : 0) + endOfLevel_Counter;

                SpritesU::drawPlusMaskFX(36, 0, Images::EndOfLevel, (frame * 3) + currentPlane);

                if (frame < 16 && endOfLevel_Counter > 12) {
                    SpritesU::drawOverwriteFX(63, 37, Images::Numbers_6x4_2D_BW, (titleCounter * 3) + currentPlane);
                }
                
            }

            break;

        case GameState::Play_Dead:
            SpritesU::drawPlusMaskFX(36, 0, Images::EndOfLife, ((endOfLevel_Counter + (player.getLives() == 1 ? 16 : 0)) * 3) + currentPlane);
            break;

        #ifdef SHOW_SIGN
            case GameState::Show_Sign:
                SpritesU::drawPlusMaskFX(36, 0, Images::EndOfLevel, ((endOfLevel_Counter + 32) * 3) + currentPlane);
                world.setXMap(endOfLevel_Counter);
                break;            
        #endif

        case GameState::Play_Gamble_Select_Exit ... GameState::Play_Gamble_Select_Play:

            renderGamblePanel(player.getChakanas() >= 5 ? 0 : 13);

            if (player.getChakanas() >= 5) {

                renderInventoryPanelCursor(menu.getX() + 8, 1 + ((static_cast<uint8_t>(world.getGameState()) - static_cast<uint8_t>(GameState::Play_Gamble_Select_Exit)) << 3));
                renderChakanaBalance(player.getChakanas());

            }
            break;

        case GameState::Play_Gamble_Select_Spin:
            {
                uint8_t frame = FX::readIndexedUInt8(Constants::GambleFrames, titleCounter);

                if (frame != 255) {

                    renderGamblePanel(1 + frame);

                    if (currentPlane == 2) {
                        titleCounter++;
                    }

                    break;

                }
                else {

                    if (titleCounter > 104) {  

                        titleCounter = 0;
                        world.setGameState(GameState::Play_Gamble_Select_Lose);

                    }
                    else {

                        world.setGameState(GameState::Play_Gamble_Select_Win);
                        titleCounter = 10 + (a.randomLFSR(1, 8) * 5);
                        player.setChakanas(player.getChakanas() + titleCounter);

                    }

                }

            }

            [[fallthrough]];

        case GameState::Play_Gamble_Select_Win:
        case GameState::Play_Gamble_Select_Lose:
            {
                uint8_t frame = ((world.getGameState() == GameState::Play_Gamble_Select_Win) ? Constants::GamblePanel_Win : Constants::GamblePanel_Lose);
                frame = frame + ((world.getFrameCount() % 48) < 24);

                renderGamblePanel(frame);

                if (frame == Constants::GamblePanel_Win) {
                    SpritesU::drawOverwriteFX(107, 13, Images::Numbers_5x3_2D_BW, (titleCounter * 3) + currentPlane);
                }

                renderChakanaBalance(player.getChakanas());

            }
            break;

        default:    break;

    }

    world.update(true);

    #endif

}

void removeInventoryItem(GameState gameState) {

    removeWorldandInventoryItem(ItemType::None, gameState);

}

#ifdef MULTIPLE_ITEMS
    
    void removeWorldandInventoryItem(ItemType itemType, GameState gameState) {

        if (itemType != ItemType::None) {

            int16_t xPos = -world.getMiddleground() + 56 + (world.getPlayer().getDirection() == Direction::Left ? -8 : 16);
            if (xPos % 16 != 0) xPos = xPos + (world.getPlayer().getDirection() == Direction::Left ? 8 : -8);

            uint8_t yPos = 37 - world.getPlayer().getY();
            if (yPos % 16 != 0) yPos = yPos - 8;

            uint8_t itemIdx = world.getItem(xPos, yPos);

            if (itemIdx != Constants::NoItem) {

                Item &item = world.getItem(itemIdx);

                if (item.getItemType() == itemType) {
                    item.setCounter(1); 
                    world.setMap(item); 
                }

            }

        }

        menu.setDirection(Direction::Right);
        menu.setGameState(gameState);

        world.getPlayer().removeInventoryItem(menu.getY() - 2);
        menu.setTop(0);
        menu.setY(0);

    }

#else

    void removeWorldandInventoryItem(ItemType itemType, GameState gameState) {

        if (itemType != ItemType::None) {

            uint8_t item = world.getItem(itemType);
            world.getItem(item).setCounter(1);  

        }

        menu.setDirection(Direction::Right);
        menu.setGameState(gameState);

        world.getPlayer().removeInventoryItem(menu.getY() - 2);
        menu.setTop(0);
        menu.setY(0);

    }

#endif

void launchPuff(Item &item) {

    Item &puff = world.getItem(world.getItem(ItemType::Puff));

    puff.setX(item.getX());
    puff.setY(item.getY());
    puff.setFrame(0);
    puff.setData(0);
    item.setCounter(3);

}

void launchPuff(Player &player) {

    Item &puff = world.getItem(world.getItem(ItemType::Puff));

    puff.setX(-world.getMiddleground() + 56 + 4);
    puff.setY(Constants::GroundY - player.getY());

    puff.setFrame(0);
    puff.setData(1);

}

void launchPuffLand(Player &player) {

    Item &puff = world.getItem(world.getItem(ItemType::Puff));

    puff.setX(-world.getMiddleground() + 56 + 4);
    puff.setY(Constants::GroundY - player.getY());

    puff.setFrame(0);
    puff.setData(2);

}