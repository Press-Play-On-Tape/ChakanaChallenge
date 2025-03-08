#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"

void processLadder_MoveLeft(Player &player, Tiles tile) {

    uint8_t start = 0;
    uint8_t end;

    if (world.getMiddleground() % 8 != 0) {

        if (world.isEmptyTile(tile)) {

            player.pushSequence(Stance::Man_Walk_FallDown_LH_01, Stance::Man_Walk_FallDown_LH_06);
            end = 1;
            player.setFalls(2);
}
        else {
            start = 2;
            end = 7;
        }

    }
    else {
        end = 3;
    }

    player.pushSequence(Stance::Man_Walk_LH_01 + start, Stance::Man_Walk_LH_01 + end);

}

void processLadder_MoveRight(Player &player, Tiles tile) {

    uint8_t start = 0;
    uint8_t end;

    if (world.getMiddleground() % 8 != 0) {

        if (world.isEmptyTile(tile)) {

            player.pushSequence(Stance::Man_Walk_FallDown_RH_01, Stance::Man_Walk_FallDown_RH_06);
            end = 1;
            player.setFalls(0);

        }
        else {
            start = 2;
            end = 7;
        }

    }
    else {
        end = 3;
    }

    player.pushSequence(Stance::Man_Walk_RH_01 + start, Stance::Man_Walk_RH_01 + end);

}

void playGame_HandlePlayerMovements(uint8_t pressed, Direction direction) {

    Player &player = world.getPlayer();
    Stance stance = player.getStance();

    int8_t xLeftOrRight =direction == Direction::Left ? -1 : 1;
    uint16_t stanceOffset = direction == Direction::Left ? Constants::Player_Stance_Offset : 0;

    uint8_t tile_F = world.getTile_RelativeToPlayer(xLeftOrRight, 0);
    uint8_t tile_F2 = world.getTile_RelativeToPlayer(2 * xLeftOrRight, 0);
    uint8_t tile_FD = world.getTile_RelativeToPlayer(xLeftOrRight, -1);
    uint8_t tile_FU = world.getTile_RelativeToPlayer(xLeftOrRight, 1);

    if (world.isEmptyTile_XY(tile_FD, xLeftOrRight, -1) && world.isEmptyTile(tile_F)) {

        if (pressed & A_BUTTON) { 

            uint8_t tile_F2 = world.getTile_RelativeToPlayer(2 * xLeftOrRight, 0);
            uint8_t tile_F3 = world.getTile_RelativeToPlayer(3 * xLeftOrRight, 0);
            uint8_t tile_F2D = world.getTile_RelativeToPlayer(2 * xLeftOrRight, -1);
            uint8_t tile_F2D2 = world.getTile_RelativeToPlayer(2 * xLeftOrRight, -2);
            uint8_t tile_F2D3 = world.getTile_RelativeToPlayer(2 * xLeftOrRight, -3);
            uint8_t tile_F3D = world.getTile_RelativeToPlayer(3 * xLeftOrRight, -1);
            uint8_t tile_F3D2 = world.getTile_RelativeToPlayer(3 * xLeftOrRight, -2);
            uint8_t tile_F3D3 = world.getTile_RelativeToPlayer(3 * xLeftOrRight, -3);
            uint8_t tile_F4D2 = world.getTile_RelativeToPlayer(4 * xLeftOrRight, -2);
            uint8_t tile_F4D3 = world.getTile_RelativeToPlayer(4 * xLeftOrRight, -3);

            #ifdef DEBUG_MOVEMENTS
                DEBUG_PRINT(tile_F2);
                DEBUG_PRINT(" ");
                DEBUG_PRINT(tile_F3);
                DEBUG_PRINT(" - ");
                DEBUG_PRINT(tile_F2D);
                DEBUG_PRINT(" ");
                DEBUG_PRINT(tile_F2D2);
                DEBUG_PRINT(" ");
                DEBUG_PRINT(tile_F2D3);
                DEBUG_PRINT(" - ");
                DEBUG_PRINT(tile_F3D);
                DEBUG_PRINT(" ");
                DEBUG_PRINT(tile_F3D2);
                DEBUG_PRINT(" ");
                DEBUG_PRINT(tile_F3D3);
                DEBUG_PRINT(" - ");
                DEBUG_PRINT(tile_F4D2);
                DEBUG_PRINT(" ");
                DEBUG_PRINT(tile_F4D3);
                DEBUG_PRINTLN(" ");
            #endif
                                                                                                // if (world.isVineTile_RH(tile_L) && (stance < Stance::Man_Vine_LH_01 || stance > Stance::Man_Vine_LH_20)) {
            // if (world.isVineTile_LH(tile_R) && (stance < Stance::Man_Vine_RH_01 || stance > Stance::Man_Vine_RH_20)) {
            if ((direction == Direction::Left  && world.isVineTile_RH(tile_F) && (stance < Stance::Man_Vine_LH_01 || stance > Stance::Man_Vine_LH_20)) ||
                (direction == Direction::Right && world.isVineTile_LH(tile_F) && (stance < Stance::Man_Vine_RH_01 || stance > Stance::Man_Vine_RH_20))) {

                Item &item = world.getItem(world.getItem(ItemType::Swinging_Vine));
                uint16_t counter = item.getCounter();

                if (direction == Direction::Left) {

                    if ((counter >= 144 && counter < 208)) {

                        item.setCounter(182);
                        player.pushSequence(Stance::Man_Vine_LH_01, Stance::Man_Vine_LH_20, true);

                    }     
                    else {

                        player.setFalls(0);
                        player.pushSequence(Stance::Man_Walk_FallDown_LH_01, Stance::Man_Walk_FallDown_LH_06);

                    }

                }
                else {

                    if ((counter >= 0 && counter < 32) || (counter >= 320 && counter < 352)) {

                        item.setCounter(6);
                        player.pushSequence(Stance::Man_Vine_RH_01, Stance::Man_Vine_RH_20, true);

                    }     
                    else {

                        player.setFalls(0);
                        player.pushSequence(Stance::Man_Walk_FallDown_RH_01, Stance::Man_Walk_FallDown_RH_06);

                    }

                }

            }
            else if (world.isEmptyTile(tile_F2) && world.isEmptyTile(tile_F3) && 
                        world.isEmptyTile_XY(tile_F2D, 2 * xLeftOrRight, -1) && world.canWalkOnTile(tile_F3D)) {     

                player.pushSequence(Stance::Man_WalkingJump_RH_25_01 + stanceOffset, Stance::Man_WalkingJump_RH_25_11 + stanceOffset);

            }    
            else if (world.isEmptyTile(tile_F2) && world.isEmptyTile(tile_F3) &&
                     world.isEmptyTile(tile_F2D) && world.isEmptyTile(tile_F3D) && !world.isEmptyTile(tile_F3D2)) {     

                player.setFalls(0);
                player.pushSequence(Stance::Man_WalkingJump_RH_1D_25_01 + stanceOffset, Stance::Man_WalkingJump_RH_1D_25_11 + stanceOffset);

            }                     
            else if (world.isEmptyTile(tile_F2) &&
                     world.isEmptyTile(tile_F2D) && world.isEmptyTile(tile_F3D)) {     

                if (world.isWaterTile(tile_F2D2)) {

                    uint8_t itemIdx = world.getItem(ItemType::LifeSaver_InWater_RH, ItemType::LifeSaver_Dissolve_InWater_RH);

                    if (itemIdx == Constants::NoItem) {

                        player.pushSequence(Stance::Man_Die_Water_RH_02_01 + stanceOffset, Stance::Man_Die_Water_RH_02_07 + stanceOffset);
                        player.pushSequence(Stance::Man_WalkingJump_RH_2D_25_01 + stanceOffset, Stance::Man_WalkingJump_RH_2D_25_09 + stanceOffset);

                    }
                    else {

                        uint8_t tile_D2 = world.getTile_RelativeToPlayer(0, -2);

                        if (tile_D2 == Tiles::Water_Plain) {

                            player.pushSequence(Stance::Man_Walk_RH_03 + stanceOffset, Stance::Man_Walk_RH_04 + stanceOffset);
                            player.pushSequence(Stance::Man_WalkingJump_RH_25_01 + stanceOffset, Stance::Man_WalkingJump_RH_25_11 + stanceOffset);
                            player.pushSequence(Stance::Man_Walk_RH_01 + stanceOffset, Stance::Man_Walk_RH_02 + stanceOffset);

                        }
                        else {

                            player.pushSequence(Stance::Man_WalkingJump_RH_25_01 + stanceOffset, Stance::Man_WalkingJump_RH_25_11 + stanceOffset);

                        }

                    }

                }
                else {
             
                    player.setFalls(0);

                    if (player.getLevel() != 2 && world.canWalkOnTile(tile_F3D3)) {

                        player.pushSequence(Stance::Man_WalkingJump_RH_2D_25_01 + stanceOffset, Stance::Man_WalkingJump_RH_2D_25_11 + stanceOffset);

                    }
                    else {
                        
                        player.pushSequence(Stance::Man_Walk_FallDown_RH_01 + stanceOffset, Stance::Man_Walk_FallDown_RH_06 + stanceOffset);

                    }

                }

            }    

        }
        else {

            uint8_t tile_F2 = world.getTile_RelativeToPlayer(2 * xLeftOrRight, 0);
            uint8_t tile_F3 = world.getTile_RelativeToPlayer(3 * xLeftOrRight, 0);
            uint8_t tile_F2D = world.getTile_RelativeToPlayer(2 * xLeftOrRight, -1);
            uint8_t tile_F3D = world.getTile_RelativeToPlayer(3 * xLeftOrRight, -1);   
            uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
            uint8_t tile_BU = world.getTile_RelativeToPlayer(-xLeftOrRight, 1);
            uint8_t tile_U = world.getTile_RelativeToPlayer(0, 1);
            uint8_t tile_FU = world.getTile_RelativeToPlayer(xLeftOrRight, 1);
            uint8_t tile_F2U = world.getTile_RelativeToPlayer(2 * xLeftOrRight, 1);

            #ifdef DEBUG_MOVEMENTS
                DEBUG_PRINT(tile_F2);
                DEBUG_PRINT(" ");
                DEBUG_PRINT(tile_F3);
                DEBUG_PRINT(" - ");
                DEBUG_PRINT(tile_F2D);
                DEBUG_PRINT(" ");
                DEBUG_PRINT(tile_F3D);
                DEBUG_PRINT(" ");
                DEBUG_PRINT(tile_D);
                DEBUG_PRINT(" ");
                DEBUG_PRINT(tile_BU);
                DEBUG_PRINT(" ");
                DEBUG_PRINT(tile_U);
                DEBUG_PRINT(" ");
                DEBUG_PRINT(tile_FU);
                DEBUG_PRINT(" ");
                DEBUG_PRINT(tile_F2U);
                DEBUG_PRINTLN(" ");
            #endif

            if ((direction == Direction::Left  && world.isStairTile_R_Half(tile_D)) ||
                (direction == Direction::Right && world.isStairTile_L_Half(tile_D))) {

                player.pushSequence(Stance::Man_DescendStairs_RH_Half_01 + stanceOffset, Stance::Man_DescendStairs_RH_Half_04 + stanceOffset);

            }
            else if (world.canWalkOnTile(tile_F2D) && world.isEmptyTile(tile_F2) && world.isEmptyTile(tile_F2U) && world.isEmptyTile(tile_U)) {

                player.pushSequence(Stance::Man_WalkingJump_RH_2_01 + stanceOffset, Stance::Man_WalkingJump_RH_2_08 + stanceOffset);

            }
            else if (world.isRopeSupport(tile_BU) && world.isRopeTile(tile_U)) {

                player.pushSequence(Stance::Man_Rope_Start_RH_01 + stanceOffset, Stance::Man_Rope_Start_RH_07 + stanceOffset);

            } 
            else {

                player.setFalls(2);
                player.pushSequence(Stance::Man_Walk_FallDown_RH_01 + stanceOffset, Stance::Man_Walk_FallDown_RH_06 + stanceOffset);

            }

        }

    }
    else {

        uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
        uint8_t tile_U = world.getTile_RelativeToPlayer(0, 1);
        uint8_t tile_F3D2 = world.getTile_RelativeToPlayer(3 * xLeftOrRight, -2);
        uint8_t tile_F2D = world.getTile_RelativeToPlayer(2 * xLeftOrRight, -1);

        player.setFalls(0);

        if (world.isVerticalVine_Upper(tile_F) || world.isVerticalVine_Middle(tile_F)) {
            
            player.setFalls(1);
            player.pushSequence(Stance::Man_Vine_Entry_RH_01 + stanceOffset, Stance::Man_Vine_Entry_RH_08 + stanceOffset);

        }
        else if ((direction == Direction::Left  && world.isSlideTile_Full_RH(tile_FD) && world.canWalkOnTile(tile_F3D2)) ||
                 (direction == Direction::Right && world.isSlideTile_Full_LH(tile_FD) && world.canWalkOnTile(tile_F3D2))) {

            player.pushSequence(Stance::Man_Slide_RH_Full_Land_01 + stanceOffset, Stance::Man_Slide_RH_Full_Land_13 + stanceOffset);

        }
        else if ((direction == Direction::Left  && world.isSlideTile_Full_RH(tile_FD) && !world.canWalkOnTile(tile_F3D2)) ||
                 (direction == Direction::Right && world.isSlideTile_Full_LH(tile_FD) && !world.canWalkOnTile(tile_F3D2))) {

            player.pushSequence(Stance::Man_Slide_RH_Full_01 + stanceOffset, Stance::Man_Slide_RH_Full_13 + stanceOffset);

        }
        else if ((direction == Direction::Left  && world.isSlideTile_Full_RH(tile_FD) && !world.isSlideTile_Full_RH(tile_F3D2)) ||
                 (direction == Direction::Right && world.isSlideTile_Full_LH(tile_FD) && !world.isSlideTile_Full_LH(tile_F3D2))) {

            player.pushSequence(Stance::Man_Slide_RH_Full_CanCont_01 + stanceOffset, Stance::Man_Slide_RH_Full_CanCont_12 + stanceOffset);

        }
        else if ((direction == Direction::Left  && world.isSlideTile_Full_RH(tile_FD) && !world.canWalkOnTile(tile_F3D2)) ||
                 (direction == Direction::Right && world.isSlideTile_Full_LH(tile_FD) && !world.canWalkOnTile(tile_F3D2))) {

            player.pushSequence(Stance::Man_Slide_RH_Full_01 + stanceOffset, Stance::Man_Slide_RH_Full_13 + stanceOffset);

        }
        else if ((direction == Direction::Left  && world.isSlideTile_RH(tile_FD)) ||
                 (direction == Direction::Right && world.isSlideTile_LH(tile_FD))) {

            player.pushSequence(Stance::Man_Slide_RH_01 + stanceOffset, Stance::Man_Slide_RH_11 + stanceOffset);

        }
        else if ((direction == Direction::Left  && world.isStairTile_L1(tile_F)) ||
                 (direction == Direction::Right && world.isStairTile_R1(tile_F))) {

            player.pushSequence(Stance::Man_ClimbStairs_RH_01 + stanceOffset, Stance::Man_ClimbStairs_RH_04 + stanceOffset);

        }
        else if ((direction == Direction::Left  && world.isStairTile_L_Half(tile_F)) ||
                 (direction == Direction::Right && world.isStairTile_R_Half(tile_F))) {

                    player.pushSequence(Stance::Man_ClimbStairs_RH_Half_01 + stanceOffset, Stance::Man_ClimbStairs_RH_Half_04 + stanceOffset);

        }
        else if ((direction == Direction::Left  && (world.isStairTile_L1(tile) || world.isStairTile_L_Half(tile))) ||
                 (direction == Direction::Right && (world.isStairTile_R1(tile) || world.isStairTile_R_Half(tile)))) {

            player.pushSequence(Stance::Man_ClimbStairs_RH_05 + stanceOffset, Stance::Man_ClimbStairs_RH_08 + stanceOffset);

        }
        else if ((direction == Direction::Left  && (world.isStairTile_R1(tile_FD) || world.isStairTile_R_Half(tile)) && player.getY() < 37) ||
                 (direction == Direction::Right && (world.isStairTile_L1(tile_FD) || world.isStairTile_L_Half(tile)) && player.getY() < 37)) {

            player.pushSequence(Stance::Man_DescendStairs_RH_05 + stanceOffset, Stance::Man_DescendStairs_RH_08 + stanceOffset);

        }
        else if ((direction == Direction::Left  && world.isStairTile_R2(tile_FD)) ||
                 (direction == Direction::Right && world.isStairTile_L2(tile_FD))) {

            player.pushSequence(Stance::Man_DescendStairs_RH_01 + stanceOffset, Stance::Man_DescendStairs_RH_08 + stanceOffset);

        }
        else if ((direction == Direction::Left  && world.isStairTile_R_Half(tile) && player.getY() < 37) ||
                 (direction == Direction::Right && world.isStairTile_L_Half(tile) && player.getY() < 37)) {

            player.pushSequence(Stance::Man_DescendStairs_RH_Half_01 + stanceOffset, Stance::Man_DescendStairs_RH_Half_04 + stanceOffset);

        }
        else if ((direction == Direction::Left  && world.isStairTile_R1(tile)) ||
                 (direction == Direction::Right && world.isStairTile_L1(tile))) {

            player.pushSequence(Stance::Man_DescendStairs_RH_01 + stanceOffset, Stance::Man_DescendStairs_RH_04 + stanceOffset);

        }   
        else if (tile == Tiles::Poker || tile_F == Tiles::Poker) {

            if (pressed & A_BUTTON) {

                world.setGameState(GameState::Play_Gamble_Select_Open);
                playGame_HandleMenu(GameState::Play_Gamble_Select_Exit);

            }
            else if (world.canWalkPastTile(tile_F, direction)) {  

                player.pushSequence(Stance::Man_Walk_RH_01 + stanceOffset, Stance::Man_Walk_RH_04 + stanceOffset);

            }

        }
        else if (world.isLadderTile(tile_F)) {

            if (direction == Direction::Left) {

                if (world.getMiddleground() % 8 == 0 && world.canWalkPastTile(tile_F, Direction::Right)) {  // <<<<SJH should be left??

                    processLadder_MoveLeft(player, tile_FD);

                }       
                else if (world.canWalkPastTile(tile_F2, Direction::Left)) {

                    processLadder_MoveLeft(player, tile_F);

                }

            }
            else {

                if (world.getMiddleground() % 8 == 0 && world.canWalkPastTile(tile_F, Direction::Right)) {  

                    processLadder_MoveRight(player, tile_F);

                }       
                else if (world.canWalkPastTile(tile_F2, Direction::Right)) {

                    processLadder_MoveRight(player, tile_F2D);

                }

            }

        }   
                        
        else if (direction == Direction::Left  && world.canWalkPastTile(tile_F, Direction::Left)) {  

            processLadder_MoveLeft(player, tile_FD);

        }             
        else if (direction == Direction::Right && world.canWalkPastTile(tile_F, Direction::Right)) {  

            processLadder_MoveRight(player, tile_FD);

        }                                    
        #ifdef SHOW_SIGN

            else if(world.isSignTile(tile_F)) {

                world.setGameState(GameState::Show_Sign);
                endOfLevel_Counter = 0;

            }                        

        #endif
        else {

            if (pressed & A_BUTTON) {

                if (!world.canWalkPastTile(tile_F) && world.canWalkOnTile(tile_F) && world.isEmptyTile(tile_U)) {     

                    player.pushSequence(Stance::Man_StandingJump_RH_UPandOver_01 + stanceOffset, Stance::Man_StandingJump_RH_UPandOver_06 + stanceOffset);

                }                       
                
            }
            else if ((direction == Direction::Left  && (world.isStairTile_L1(tile_F) || world.isStairTile_L_Half(tile_F))) ||
                     (direction == Direction::Right && (world.isStairTile_R1(tile_F) || world.isStairTile_R_Half(tile_F)))) {

                player.pushSequence(Stance::Man_ClimbStairs_RH_01 + stanceOffset, Stance::Man_ClimbStairs_RH_04 + stanceOffset);

            }
            else if ((direction == Direction::Left  && world.isStairTile_L2(tile_F)) ||
                     (direction == Direction::Right && world.isStairTile_R2(tile_F))) {

                player.pushSequence(Stance::Man_ClimbStairs_RH_05 + stanceOffset, Stance::Man_ClimbStairs_RH_08 + stanceOffset);

            }

        }       

    }   

}