#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"

int16_t enemy = -20;

void playGame_Init() {

    gameState = GameState::PlayGame;
    frameCount = 0;

    world.setX(0);
    // world.setPalm1(-240);
    // world.setPalm2(-130);
    // world.setPalm3(0);
    // world.setPalm4(130);
    world.setPalm1(-100);
    world.setPalm2(-260);
    world.setPalm3(-320);
    world.setPalm4(-580);
    world.setPalm5(116);
    world.setPalm6(66);
    world.setPalm7(-20);
    world.setPalm8(-80);

    world.setBackground(0);

        // uint16_t waveCount = 0;
        // uint16_t background = 0;

}

void playGame_Update() {

    uint8_t pressed = getPressedButtons();
    uint8_t justPressed = getJustPressedButtons();

    frameCount++;
        
    if (frameCount % 4 == 0) {

        if (player.isEmpty()) {

            if (justPressed & UP_BUTTON || pressed & UP_BUTTON) {

                switch (player.getDirection()) {

                    case Direction::Backward:
                        {
                            uint8_t tile = world.getTile(player, 0, 0);
                            uint8_t tile_R = world.getTile(player, 1, 0);

                            if (world.isLadderTile_Upper(tile) && world.isLadderTile_Upper(tile_R)) {

                                if (justPressed & RIGHT_BUTTON || pressed & RIGHT_BUTTON) {
                                    player.pushSequence(Stance::Man_ClimbLadder_BK_RH_UP_08, Stance::Man_ClimbLadder_BK_RH_UP_14);
                                }

                                else if (justPressed & LEFT_BUTTON || pressed & LEFT_BUTTON) {
                                    player.pushSequence(Stance::Man_ClimbLadder_BK_LH_UP_08, Stance::Man_ClimbLadder_BK_LH_UP_14);
                                }

                                else if (player.getStance() == Stance::Man_ClimbLadder_BK_RH_UP_07 || player.getStance() == Stance::Man_ClimbLadder_BK_RH_DOWN_07) {
                                    player.pushSequence(Stance::Man_ClimbLadder_BK_RH_UP_08, Stance::Man_ClimbLadder_BK_RH_UP_14);
                                }

                                else if (player.getStance() == Stance::Man_ClimbLadder_BK_LH_UP_07 || player.getStance() == Stance::Man_ClimbLadder_BK_LH_DOWN_07) {
                                    player.pushSequence(Stance::Man_ClimbLadder_BK_LH_UP_08, Stance::Man_ClimbLadder_BK_LH_UP_14);
                                }

                            }
                            else if (world.isLadderTile_Middle(tile) && world.isLadderTile_Middle(tile_R)) {

                                // Climb further up ..
                                if (player.getStance() == Stance::Man_ClimbLadder_BK_RH_UP_07 || player.getStance() == Stance::Man_ClimbLadder_BK_RH_DOWN_07) {

                                    player.pushSequence(Stance::Man_ClimbLadder_BK_RH_UP_06, Stance::Man_ClimbLadder_BK_RH_UP_07);
                                    player.pushSequence(Stance::Man_ClimbLadder_BK_RH_UP_06, Stance::Man_ClimbLadder_BK_RH_UP_07);
                                    
                                }
                                
                                if (player.getStance() == Stance::Man_ClimbLadder_BK_LH_UP_07 || player.getStance() == Stance::Man_ClimbLadder_BK_LH_DOWN_07) {

                                    player.pushSequence(Stance::Man_ClimbLadder_BK_LH_UP_06, Stance::Man_ClimbLadder_BK_LH_UP_07);
                                    player.pushSequence(Stance::Man_ClimbLadder_BK_LH_UP_06, Stance::Man_ClimbLadder_BK_LH_UP_07);
                                    
                                }


                            }


                        }
                        break;

                    case Direction::Right:
                        {
                            uint8_t tile = world.getTile(player, 0, 0);
                            uint8_t tile_R = world.getTile(player, 1, 0);

                            if (world.isLadderTile_Lower(tile) && world.isLadderTile_Lower(tile_R)) {

                                player.pushSequence(Stance::Man_ClimbLadder_BK_RH_UP_01, Stance::Man_ClimbLadder_BK_RH_UP_07);

                            }

                        }
                        break;

                    case Direction::Left:
                        {
                            uint8_t tile = world.getTile(player, 0, 0);
                            uint8_t tile_L = world.getTile(player, -1, 0);

                            if (world.isLadderTile_Lower(tile) && world.isLadderTile_Lower(tile_L)) {

                                player.pushSequence(Stance::Man_ClimbLadder_BK_LH_UP_01, Stance::Man_ClimbLadder_BK_LH_UP_07);

                            }

                        }
                        break;

                    case Direction::Forward:
                        {
                            uint8_t tile_L = world.getTile(player, -1, 0);
                            uint8_t tile = world.getTile(player, 0, 0);
                            uint8_t tile_R = world.getTile(player, 1, 0);

                            if (world.isLadderTile_Lower(tile) && world.isLadderTile_Lower(tile_R)) {

                                player.pushSequence(Stance::Man_ClimbLadder_BK_RH_UP_01, Stance::Man_ClimbLadder_BK_RH_UP_07);

                            }

                            else if (world.isLadderTile_Lower(tile) && world.isLadderTile_Lower(tile_L)) {

                                player.pushSequence(Stance::Man_ClimbLadder_BK_LH_UP_01, Stance::Man_ClimbLadder_BK_LH_UP_07);

                            }

                        }
                        break;
                }

            }

            else if (justPressed & DOWN_BUTTON || pressed & DOWN_BUTTON) {

                switch (player.getDirection()) {

                    case Direction::Backward:
                        {
                            uint8_t tile = world.getTile(player, 0, 0);
                            uint8_t tile_R = world.getTile(player, 1, 0);
                            uint8_t tile_D = world.getTile(player, 0, -1);
                            uint8_t tile_RD = world.getTile(player, 1, -1);

                            if (world.isLadderTile_Lower(tile_D) && world.isLadderTile_Lower(tile_RD)) {

                                if (justPressed & RIGHT_BUTTON || pressed & RIGHT_BUTTON) {
                                    player.pushSequence(Stance::Man_ClimbLadder_BK_RH_DOWN_08, Stance::Man_ClimbLadder_BK_RH_DOWN_14);
                                }

                                else if (justPressed & LEFT_BUTTON || pressed & LEFT_BUTTON) {
                                    player.pushSequence(Stance::Man_ClimbLadder_BK_LH_DOWN_08, Stance::Man_ClimbLadder_BK_LH_DOWN_14);
                                }

                                else if (player.getStance() == Stance::Man_ClimbLadder_BK_RH_UP_07 || player.getStance() == Stance::Man_ClimbLadder_BK_RH_DOWN_07) {
                                    player.pushSequence(Stance::Man_ClimbLadder_BK_LH_DOWN_08, Stance::Man_ClimbLadder_BK_LH_DOWN_14);
                                }

                                else if (player.getStance() == Stance::Man_ClimbLadder_BK_LH_UP_07 || player.getStance() == Stance::Man_ClimbLadder_BK_LH_DOWN_07) {
                                    player.pushSequence(Stance::Man_ClimbLadder_BK_RH_DOWN_08, Stance::Man_ClimbLadder_BK_RH_DOWN_14);
                                }
                                

                            }
                            else if (world.isLadderTile_Middle(tile_D) && world.isLadderTile_Middle(tile_RD)) {
  
                                if (player.getStance() == Stance::Man_ClimbLadder_BK_RH_UP_07 || player.getStance() == Stance::Man_ClimbLadder_BK_RH_DOWN_07) {

                                    player.pushSequence(Stance::Man_ClimbLadder_BK_RH_DOWN_06, Stance::Man_ClimbLadder_BK_RH_DOWN_07);
                                    player.pushSequence(Stance::Man_ClimbLadder_BK_RH_DOWN_06, Stance::Man_ClimbLadder_BK_RH_DOWN_07);
                                    
                                }
                                
                                if (player.getStance() == Stance::Man_ClimbLadder_BK_LH_UP_07 || player.getStance() == Stance::Man_ClimbLadder_BK_LH_DOWN_07) {

                                    player.pushSequence(Stance::Man_ClimbLadder_BK_LH_DOWN_06, Stance::Man_ClimbLadder_BK_LH_DOWN_07);
                                    player.pushSequence(Stance::Man_ClimbLadder_BK_LH_DOWN_06, Stance::Man_ClimbLadder_BK_LH_DOWN_07);
                                    
                                }

                            }
                            else if (player.getStance() == Stance::Man_Rope_Start_RH_07 || player.getStance() == Stance::Man_Rope_Start_LH_07) {
                            
                                player.setFalls(0);
                                player.push(Stance::Man_Walk_FallMore_BK_02);

                            }

                        }
                        break;

                    case Direction::Right:
                        {
                            uint8_t tile_D = world.getTile(player, 0, -1);
                            uint8_t tile_RD = world.getTile(player, 1, -1);

                            if (world.isLadderTile_Upper(tile_D) && world.isLadderTile_Upper(tile_RD)) {

                                player.pushSequence(Stance::Man_ClimbLadder_BK_RH_DOWN_01, Stance::Man_ClimbLadder_BK_RH_DOWN_07);

                            }

                        }
                        break;

                    case Direction::Left:
                        {
                            uint8_t tile_D = world.getTile(player, 0, -1);
                            uint8_t tile_LD = world.getTile(player, -1, -1);

                            if (world.isLadderTile_Upper(tile_LD) && world.isLadderTile_Upper(tile_D)) {

                                player.pushSequence(Stance::Man_ClimbLadder_BK_LH_DOWN_01, Stance::Man_ClimbLadder_BK_LH_DOWN_07);

                            }

                        }
                        break;

                    case Direction::Forward:
                        {
                            uint8_t tile_LD = world.getTile(player, -1, -1);
                            uint8_t tile_D = world.getTile(player, 0, -1);
                            uint8_t tile_RD = world.getTile(player, 1, -1);

                            if (world.isLadderTile_Upper(tile_D) && world.isLadderTile_Upper(tile_RD)) {

                                player.pushSequence(Stance::Man_ClimbLadder_BK_RH_DOWN_01, Stance::Man_ClimbLadder_BK_RH_DOWN_07);

                            }

                            if (world.isLadderTile_Upper(tile_LD) && world.isLadderTile_Upper(tile_D)) {

                                player.pushSequence(Stance::Man_ClimbLadder_BK_LH_DOWN_01, Stance::Man_ClimbLadder_BK_LH_DOWN_07);

                            }

                        }
                        break;

                }

            }

            else if ((justPressed & LEFT_BUTTON || pressed & LEFT_BUTTON) && player.canMoveLeft()) {

                switch (player.getDirection()) {

                    case Direction::Left:
                        {
                            uint8_t tile_L = world.getTile(player, -1, 0);
                            uint8_t tile_LD = world.getTile(player, -1, -1);

                            if (world.isEmptyTile(tile_LD) && world.isEmptyTile(tile_L)) {

                                if (justPressed & A_BUTTON || pressed & A_BUTTON) {

                                    uint8_t tile_L2 = world.getTile(player, -2, 0);
                                    uint8_t tile_L3 = world.getTile(player, -3, 0);
                                    uint8_t tile_L2D = world.getTile(player, -2, -1);
                                    uint8_t tile_L3D = world.getTile(player, -3, -1);                                

                                    if (world.isEmptyTile(tile_L) && world.isEmptyTile(tile_L2) && world.isEmptyTile(tile_L3) &&
                                        world.isEmptyTile(tile_LD) && world.isEmptyTile(tile_L2D) && world.canWalkOnTile(tile_L3D)) {     

                                        player.pushSequence(Stance::Man_WalkingJump_LH_25_01, Stance::Man_WalkingJump_LH_25_11);

                                    }                     
                                    else if (world.isEmptyTile(tile_L) && world.isEmptyTile(tile_L2) && world.isEmptyTile(tile_L3) &&

                                        world.isEmptyTile(tile_LD) && world.isEmptyTile(tile_L2D) && world.isEmptyTile(tile_L3D)) {     
                                        player.setFalls(0);
                                        player.pushSequence(Stance::Man_WalkingJump_LH_1D_25_01, Stance::Man_WalkingJump_LH_1D_25_11);

                                    }                     

                                }
                                else {

                                    uint8_t tile_L2 = world.getTile(player, -2, 0);
                                    uint8_t tile_L3 = world.getTile(player, -3, 0);
                                    uint8_t tile_L2D = world.getTile(player, -2, -1);
                                    uint8_t tile_L3D = world.getTile(player, -3, -1);   
                                    uint8_t tile_D = world.getTile(player, 0, -1);
                                    uint8_t tile_RU = world.getTile(player, 1, 1);
                                    uint8_t tile_U = world.getTile(player, 0, 1);
                                    uint8_t tile_LU = world.getTile(player, -1, 1);
                                    uint8_t tile_L2U = world.getTile(player, -2, 1);

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

                                uint8_t tile = world.getTile(player, 0, 0);
                                uint8_t tile_U = world.getTile(player, 0, 1);
                                uint8_t tile_R1 = world.getTile(player, 1, 0);
                                uint8_t tile_L1 = world.getTile(player, -1, 0);
                                uint8_t tile_LU = world.getTile(player, -1, 1);
                                uint8_t tile_L2U = world.getTile(player, -2, 1);
                                uint8_t tile_L3D2 = world.getTile(player, -3, -2);


                                if (world.isSlideTile_Full_RH(tile_LD) && world.canWalkOnTile(tile_L3D2)) {
Serial.println("B1");
                                    player.setFalls(0);
                                    player.pushSequence(Stance::Man_Slide_LH_Full_Land_01, Stance::Man_Slide_LH_Full_Land_13);

                                }
                                else if (world.isSlideTile_Full_RH(tile_LD) && !world.canWalkOnTile(tile_L3D2)) {
Serial.println("B2");
                                    player.setFalls(0);
                                    player.pushSequence(Stance::Man_Slide_LH_Full_01, Stance::Man_Slide_LH_Full_13);

                                }
                                else if (world.isSlideTile_RH(tile_LD)) {
Serial.println("B3");
                                    player.setFalls(0);
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
                                else if (world.isStairTile_R1(tile_LD) || world.isStairTile_R_Half(tile)) {  

                                    player.pushSequence(Stance::Man_DescendStairs_LH_05, Stance::Man_DescendStairs_LH_08);

                                }
                                else if (world.isStairTile_R_Half(tile)) {  

                                    player.pushSequence(Stance::Man_DescendStairs_LH_Half_01, Stance::Man_DescendStairs_LH_Half_04);

                                }
                                else if (world.isStairTile_R1(tile)) {  

                                    player.pushSequence(Stance::Man_DescendStairs_LH_01, Stance::Man_DescendStairs_LH_04);

                                }                                    
                                else if (world.canWalkPastTile(tile_L) || player.getLevel() == 0) {  

                                    player.pushSequence(Stance::Man_Walk_LH_01, Stance::Man_Walk_LH_04);

                                }
                                else {

                                    if (justPressed & A_BUTTON || pressed & A_BUTTON) {

                                        if (!world.canWalkPastTile(tile_L) && world.isEmptyTile(tile_U)) {     
                                            
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
                            uint8_t tile_U = world.getTile(player, 0, 1);
                            uint8_t tile_LU = world.getTile(player, -1, 1);
                            uint8_t tile_L2U = world.getTile(player, -2, 1);

                            if (!world.canWalkPastTile(tile_LU) && !world.isRopeTile(tile_LU) && world.isRopeTile(tile_U)) {

                                // Do nothing ..

                            }   
                            else if (world.isRopeTile(tile_U) && world.isRopeTile(tile_LU) && world.isRopeSupport(tile_L2U)) {

                                player.pushSequence(Stance::Man_Rope_End_LH_01, Stance::Man_Rope_End_LH_06);

                            }   
                            else if (!world.isRopeSupport(tile_LU) && world.isRopeTile(tile_U)) {

                                player.pushSequence(Stance::Man_Rope_Start_LH_04, Stance::Man_Rope_Start_LH_07);

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

            else if ((justPressed & RIGHT_BUTTON || pressed & RIGHT_BUTTON) && player.canMoveRight()) {

                switch (player.getDirection()) {

                    case Direction::Right:
                        {
                            uint8_t tile_R = world.getTile(player, 1, 0);
                            uint8_t tile_RD = world.getTile(player, 1, -1);

                            if (world.isEmptyTile(tile_RD) && world.isEmptyTile(tile_R)) {
Serial.println("A");
                                if (justPressed & A_BUTTON || pressed & A_BUTTON) { 

                                    uint8_t tile_R2 = world.getTile(player, 2, 0);
                                    uint8_t tile_R3 = world.getTile(player, 3, 0);
                                    uint8_t tile_R2D = world.getTile(player, 2, -1);
                                    uint8_t tile_R3D = world.getTile(player, 3, -1);

                                    if (world.isEmptyTile(tile_R) && world.isEmptyTile(tile_R2) && world.isEmptyTile(tile_R3) 
                                       && world.isEmptyTile(tile_RD) && world.isEmptyTile(tile_R2D) && world.canWalkOnTile(tile_R3D)) {     

                                        player.pushSequence(Stance::Man_WalkingJump_RH_25_01, Stance::Man_WalkingJump_RH_25_11);

                                    }    
                                    else if (world.isEmptyTile(tile_R) && world.isEmptyTile(tile_R2) && world.isEmptyTile(tile_R3) &&
                                        world.isEmptyTile(tile_RD) && world.isEmptyTile(tile_R2D) && world.isEmptyTile(tile_R3D)) {     

                                        player.setFalls(0);
                                        player.pushSequence(Stance::Man_WalkingJump_RH_1D_25_01, Stance::Man_WalkingJump_RH_1D_25_11);

                                    }                     
              
                                }
                                else {
                                    
                                    uint8_t tile_U = world.getTile(player, 0, 1);
                                    uint8_t tile_D = world.getTile(player, 0, -1);
                                    uint8_t tile_LU = world.getTile(player, -1, 1);
                                    uint8_t tile_R2U = world.getTile(player, 2, 1);
                                    uint8_t tile_R2 = world.getTile(player, 2, 0);
                                    uint8_t tile_R2D = world.getTile(player, 2, -1);

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
Serial.println("B");

                                uint8_t tile_R2 = world.getTile(player, 2, 0);
                                uint8_t tile = world.getTile(player, 0, 0);
                                uint8_t tile_L = world.getTile(player, -1, 0);
                                uint8_t tile_LU = world.getTile(player, -1, 1);
                                uint8_t tile_RU = world.getTile(player, 1, 1);
                                uint8_t tile_R2U = world.getTile(player, 2, 1);
                                uint8_t tile_D = world.getTile(player, 0, -1);
                                uint8_t tile_RD = world.getTile(player, 1, -1);
                                uint8_t tile_R2D = world.getTile(player, 2, -1);
                                uint8_t tile_R3D2 = world.getTile(player, 3, -2);


                                if (world.isSlideTile_Full_LH(tile_RD) && world.canWalkOnTile(tile_R3D2)) {
Serial.println("B1");
                                    player.setFalls(0);
                                    player.pushSequence(Stance::Man_Slide_RH_Full_Land_01, Stance::Man_Slide_RH_Full_Land_13);

                                }
                                else if (world.isSlideTile_Full_LH(tile_RD) && !world.canWalkOnTile(tile_R3D2)) {
Serial.println("B2");
                                    player.setFalls(0);
                                    player.pushSequence(Stance::Man_Slide_RH_Full_01, Stance::Man_Slide_RH_Full_13);

                                }
                                else if (world.isSlideTile_LH(tile_RD)) {
Serial.println("B3");
                                    player.setFalls(0);
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
                                else if (world.isStairTile_L1(tile_RD) || world.isStairTile_L_Half(tile)) {  

                                    player.pushSequence(Stance::Man_DescendStairs_RH_05, Stance::Man_DescendStairs_RH_08);

                                }
                                else if (world.isStairTile_L_Half(tile)) {  

                                    player.pushSequence(Stance::Man_DescendStairs_RH_Half_01, Stance::Man_DescendStairs_RH_Half_04);

                                }
                                else if (world.isStairTile_L1(tile)) {  

                                    player.pushSequence(Stance::Man_DescendStairs_RH_01, Stance::Man_DescendStairs_RH_04);

                                }                                
                                else if (world.canWalkPastTile(tile_R) || player.getLevel() == 0) {  

                                    player.pushSequence(Stance::Man_Walk_RH_01, Stance::Man_Walk_RH_04);

                                }
                                else {

                                    if (justPressed & A_BUTTON || pressed & A_BUTTON) {

                                        if (!world.canWalkPastTile(tile_R)) {     
                        
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
                            uint8_t tile_U = world.getTile(player, 0, 1);
                            uint8_t tile_RU = world.getTile(player, 1, 1);
                            uint8_t tile_R2U = world.getTile(player, 2, 1);

                            if (!world.canWalkPastTile(tile_RU) && !world.isRopeTile(tile_RU) && world.isRopeTile(tile_U)) {

                                // Do nothing ..

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

            else if (justPressed & A_BUTTON || pressed & A_BUTTON) {

                switch (player.getDirection()) {

                    case Direction::Backward:

                        switch (player.getStance()) {

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
                                player.pushSequence(Stance::Man_StandingJump_BK_01, Stance::Man_StandingJump_BK_07); 
                                break;
                            
                        }

                        break;

                    case Direction::Right:
                        {
                            uint8_t tile = world.getTile(player, 0, 0);
                            uint8_t tile_U = world.getTile(player, 0, 2);

                            if (world.isEmptyTile(tile_U)) {

                                if (world.canJumpUpOntoTile(tile)) {

                                    player.pushSequence(Stance::Man_StandingJump_RH_UP_01, Stance::Man_StandingJump_RH_UP_06); 

                                }
                                else if (world.isSpringTile(tile)) {    

                                    uint8_t tile_3U = world.getTile(player, 0, 3);
                                    uint8_t tile_4U = world.getTile(player, 0, 4);

                                    if (world.isRopeTile(tile_3U)) {

                                        // player.pushSequence(Stance::Man_BounceJump_RH_01, Stance::Man_BounceJump_RH_34);
                                        player.pushSequence(Stance::Man_BounceJump_RH_33, Stance::Man_BounceJump_RH_34);
                                        player.pushSequence(Stance::Man_BounceJump_RH_01, Stance::Man_BounceJump_RH_30);

                                    }
                                    else if (world.isRopeTile(tile_4U)) {

                                        player.pushSequence(Stance::Man_BounceJump_RH_01, Stance::Man_BounceJump_RH_34);

                                    }

                                }   
                                else {
                                    player.pushSequence(Stance::Man_StandingJump_RH_01, Stance::Man_StandingJump_RH_07); 
                                }

                            }
                            else {
                                
                                player.pushSequence(Stance::Man_StandingJump_Small_RH_01, Stance::Man_StandingJump_Small_RH_03); 

                            }

                        }
                        break;

                    case Direction::Forward:
                        {
                            uint8_t tile = world.getTile(player, 0, 0);

                            if (tile == 0) {
                                player.pushSequence(Stance::Man_StandingJump_FW_01, Stance::Man_StandingJump_FW_07); 
                            }
                            else {
                                player.pushSequence(Stance::Man_StandingJump_FW_UP_01, Stance::Man_StandingJump_FW_UP_06); 
                            }
                        }
                        break;

                    case Direction::Left:
                        
                        {
                            uint8_t tile = world.getTile(player, 0, 0);
                            uint8_t tile_U = world.getTile(player, 0, 2);

                            if (world.isEmptyTile(tile_U)) {

                                if (world.canJumpUpOntoTile(tile)) {

                                    player.pushSequence(Stance::Man_StandingJump_LH_UP_01, Stance::Man_StandingJump_LH_UP_06); 

                                }
                                else if (world.isSpringTile(tile)) {     
                                    uint8_t tile_3U = world.getTile(player, 0, 3);
                                    uint8_t tile_4U = world.getTile(player, 0, 4);

                                    if (world.isRopeTile(tile_3U)) {

                                        player.pushSequence(Stance::Man_BounceJump_LH_33, Stance::Man_BounceJump_LH_34);
                                        player.pushSequence(Stance::Man_BounceJump_LH_01, Stance::Man_BounceJump_LH_30);

                                    }
                                    else if (world.isRopeTile(tile_4U)) {

                                        player.pushSequence(Stance::Man_BounceJump_LH_01, Stance::Man_BounceJump_LH_34);

                                    }

                                }                                   
                                else {

                                    player.pushSequence(Stance::Man_StandingJump_LH_01, Stance::Man_StandingJump_LH_07); 

                                }

                            }
                            else {
                                    player.pushSequence(Stance::Man_StandingJump_Small_LH_01, Stance::Man_StandingJump_Small_LH_03); 

                            }
                        }                        
                        break;

                }

            }

        }
        else {

            if (pressed & A_BUTTON) {

                switch (player.getStance()) {

                    case Stance::Man_Walk_RH_01:
                        {
                            uint8_t tile_R = world.getTile(player, 1, 0);

                            if (tile_R == 1) {
                                player.clear();
                                player.pushSequence(Stance::Man_WalkingJump_RH_UP_01, Stance::Man_WalkingJump_RH_UP_05); 
                            }
                            else {
                                player.clear();
                                player.pushSequence(Stance::Man_WalkingJump_RH_2_01, Stance::Man_WalkingJump_RH_2_08); 
                            }

                        }
                        break;

                    case Stance::Man_Walk_LH_01:
                        {
                            
                            uint8_t tile_L = world.getTile(player, -1, 0);

                            if (tile_L == 3) {
                                player.clear();
                                player.pushSequence(Stance::Man_WalkingJump_LH_UP_01, Stance::Man_WalkingJump_LH_UP_05); 
                            }
                            else {
                                player.clear();
                                player.pushSequence(Stance::Man_WalkingJump_LH_01, Stance::Man_WalkingJump_LH_08); 
                            }

                        }
                        
                        break;

                    default:
                        break;

                }

            }

        }

        if (!player.isEmpty()) {

            Point offset;

            uint16_t newStance = player.pop();
            player.setStance(newStance);

            int8_t stanceY = pgm_read_byte(&Constants::StanceY[static_cast<uint16_t>(player.getStance())]);
            player.setY(player.getY() - stanceY);

            world.incForeground(pgm_read_byte(&Constants::xForeground[static_cast<uint16_t>(player.getStance())]));
            world.incMiddleground(pgm_read_byte(&Constants::xMiddleground[static_cast<uint16_t>(player.getStance())]));
            world.incBackground(pgm_read_byte(&Constants::xBackground[static_cast<uint16_t>(player.getStance())]));

            switch (static_cast<Stance>(newStance)) {

                case Stance::Man_Walk_FallMore_BK_02:
                    {

                        uint8_t tile_D = world.getTile(player, 0, -1);
                        uint8_t tile_D2 = world.getTile(player, 0, -2);
  
                        if (world.isEmptyTile(tile_D) || world.isSpringTile(tile_D)) {

                            player.incFalls();

                            if (world.isEmptyTile(tile_D2) || world.isSpringTile(tile_D2)) {    
                            
                                player.pushSequence(Stance::Man_Walk_FallMore_BK_01, Stance::Man_Walk_FallMore_BK_02); 

                            }
                            else {

                                if (player.getFalls() >= 3) {

                                    if (world.isSpringTile(tile_D)) {
                                    
                                        player.pushSequence(Stance::Man_Walk_FallLandSpring_BK_01, Stance::Man_Walk_FallLandSpring_BK_28);
                                    }
                                    else {

                                        player.pushSequence(Stance::Man_Die_RH_01, Stance::Man_Die_RH_04); 
                                        player.pushSequence(Stance::Man_Walk_FallLand_BK_01, Stance::Man_Walk_FallLand_BK_04);

                                    }

                                }
                                else if (world.isSpringTile(tile_D)) {

                                    player.pushSequence(Stance::Man_Walk_FallLandSpring_BK_01, Stance::Man_Walk_FallLandSpring_BK_28);

                                }                                
                                else if (world.isSpikeTile(tile_D)) {

                                    player.pushSequence(Stance::Man_Die_RH_01, Stance::Man_Die_RH_04); 
                                    player.pushSequence(Stance::Man_Walk_FallLand_BK_01, Stance::Man_Walk_FallLand_BK_04);

                                }
                                else {

                                    player.pushSequence(Stance::Man_Walk_FallLand_BK_01, Stance::Man_Walk_FallLand_BK_04);
                                } 

                            }

                        }
                        else {

                            player.setStance(Stance::Man_Walk_RH_02); 

                        }

                    }
                    break;

                case Stance::Man_Walk_FallDown_RH_06:
                case Stance::Man_Walk_FallMore_RH_02:
                case Stance::Man_WalkingJump_RH_1D_25_11:
                case Stance::Man_Slide_RH_11:
                case Stance::Man_Slide_RH_Full_13:
                    {

                        uint8_t tile_D = world.getTile(player, 0, -1);
                        uint8_t tile_D2 = world.getTile(player, 0, -2);

                        if (world.isEmptyTile(tile_D)) {

                            player.incFalls();

                            if (player.getFalls() < 3) {

                                if (world.isEmptyTile(tile_D2)) {                                    
Serial.println("fall more a");
                                    player.pushSequence(Stance::Man_Walk_FallMore_RH_01, Stance::Man_Walk_FallMore_RH_02); 

                                }
                                else {

                                    if (world.isSpikeTile(tile_D)) {
Serial.println("fall more b");

                                        player.pushSequence(Stance::Man_Die_RH_01, Stance::Man_Die_RH_04); 
                                        player.pushSequence(Stance::Man_Walk_FallLand_RH_01, Stance::Man_Walk_FallLand_RH_04);

                                    }
                                    else {
Serial.println("fall more c");
Serial.println(tile_D);
Serial.println(tile_D2);
Serial.println((Constants::GroundY - player.getY()) % 8);
//                                         if ((Constants::GroundY - player.getY()) % 8 == 4) {
// Serial.println("fall more 1");
// //                                             player.pushSequence(Stance::Man_Walk_FallLand_RH_01, Stance::Man_Walk_FallLand_RH_04);
//                                            player.pushSequence(Stance::Man_Walk_FallMore_RH_01, Stance::Man_Walk_FallMore_RH_02); 
//                                         }
//                                         else {
Serial.println("fall more 2");
                                            player.pushSequence(Stance::Man_Walk_FallLand_RH_01, Stance::Man_Walk_FallLand_RH_04);
                                        // }

                                    } 

                                }

                            }
                            else {
Serial.println("fall more d");
                             
                                player.pushSequence(Stance::Man_Die_RH_01, Stance::Man_Die_RH_04); 
                                player.pushSequence(Stance::Man_Walk_FallMore_RH_01, Stance::Man_Walk_FallMore_RH_02); 

                            }

                        }
                        else {

                            player.setStance(Stance::Man_Walk_RH_02); 

                        }

                    }
                    break;

                case Stance::Man_Walk_FallDown_LH_06:
                case Stance::Man_Walk_FallMore_LH_02:
                case Stance::Man_WalkingJump_LH_1D_25_11:
                case Stance::Man_Slide_LH_11:
                case Stance::Man_Slide_LH_Full_13:                
                    {
                        uint8_t tile_D = world.getTile(player, 0, -1);
                        uint8_t tile_D2 = world.getTile(player, 0, -2);

                        if (world.isEmptyTile(tile_D)) {

                            player.incFalls();

                            if (player.getFalls() < 3) {

                                if (world.isEmptyTile(tile_D2)) {

                                    player.pushSequence(Stance::Man_Walk_FallMore_LH_01, Stance::Man_Walk_FallMore_LH_02); 

                                }
                                else {
                                    if (world.isSpikeTile(tile_D)) {

                                        player.pushSequence(Stance::Man_Die_LH_01, Stance::Man_Die_LH_04); 
                                        player.pushSequence(Stance::Man_Walk_FallLand_LH_01, Stance::Man_Walk_FallLand_LH_04); 

                                    }
                                    else {

                                        player.pushSequence(Stance::Man_Walk_FallLand_LH_01, Stance::Man_Walk_FallLand_LH_04); 

                                    }

                                }

                            }
                            else {

                                player.pushSequence(Stance::Man_Die_LH_01, Stance::Man_Die_LH_04); 
                                player.pushSequence(Stance::Man_Walk_FallMore_LH_01, Stance::Man_Walk_FallMore_LH_02); 

                            }

                        }
                        else {

                            player.setStance(Stance::Man_Walk_LH_02); 

                        }

                    }
                    break;

                default:
                    {
                        uint16_t subsituteStance = pgm_read_word(&Constants::subsititueStance[player.getStance()]);

                        if (subsituteStance != 65535) {
                            player.setStance(subsituteStance);
                        }

                    }
                    break;

            }

        }

    }

    player.update(0, 0);
    

}


void playGame(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    // waveCount++;
    // if (waveCount >= 7 * 64) waveCount = 0;

    if (a.needsUpdate()) playGame_Update();


    uint8_t yOffset = Constants::GroundY;

    if (player.getY() < 5) yOffset = Constants::GroundY - player.getY();




    uint8_t currentPlane = a.currentPlane();

    // SpritesU::drawOverwriteFX(world.getBackground() - 128, yOffset - Constants::GroundY, Images::Background, currentPlane);    
    // SpritesU::drawOverwriteFX(world.getBackground(), yOffset - Constants::GroundY, Images::Background, currentPlane);    
    // SpritesU::drawOverwriteFX(world.getBackground() + 128, yOffset - Constants::GroundY, Images::Background, currentPlane);    

    // SpritesU::drawOverwriteFX(world.getBackground() - 128, ((yOffset - Constants::GroundY) / 4) - 8, Images::Background_Above, currentPlane);    
    SpritesU::drawOverwriteFX(world.getBackground(), ((yOffset - Constants::GroundY) / 4) - 8, Images::Background_Above, currentPlane);    
    SpritesU::drawOverwriteFX(world.getBackground() + 128, ((yOffset - Constants::GroundY) / 4) - 8, Images::Background_Above, currentPlane);    

    // SpritesU::drawOverwriteFX(world.getBackground() - 128, (yOffset - Constants::GroundY)/4, Images::Background, currentPlane);    
    SpritesU::drawOverwriteFX(world.getBackground(), (yOffset - Constants::GroundY)/4, Images::Background, currentPlane);    
    SpritesU::drawOverwriteFX(world.getBackground() + 128, (yOffset - Constants::GroundY)/4, Images::Background, currentPlane);    
    
    SpritesU::drawPlusMaskFX(world.getPalm5(), 20 + yOffset - Constants::GroundY, Images::Palm5, currentPlane);
    SpritesU::drawPlusMaskFX(world.getPalm6(), 20 + yOffset - Constants::GroundY, Images::Palm6, currentPlane);
    SpritesU::drawPlusMaskFX(world.getPalm7(), 20 + yOffset - Constants::GroundY, Images::Palm5, currentPlane);
    SpritesU::drawPlusMaskFX(world.getPalm8(), 20 + yOffset - Constants::GroundY, Images::Palm6, currentPlane);


    for (uint8_t y = 0; y < 10; y = y + 2) {

        for (uint8_t i= 0; i < numberOfTiles - 1; i = i + 2) {

            uint8_t tile00 = world.getTile(i, y);
            uint8_t tile01 = world.getTile(i + 1, y);
            uint8_t tile10 = world.getTile(i, y + 1);
            uint8_t tile11 = world.getTile(i + 1, y + 1);

            if (tile00 == 1 && tile01 == 1 & tile10 == 0 & tile11 == 0) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_10, currentPlane);
            }

            if (tile00 == 1 && tile01 == 1 & tile10 == 16 & tile11 == 0) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_20, currentPlane);
            }

            if (tile00 == 1 && tile01 == 1 & tile10 == 0 & tile11 == 17) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_21, currentPlane);
            }

            if (tile00 == 1 && tile01 == 1 & tile10 == 0 & tile11 == 1) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_00, currentPlane);
            }
            if (tile00 == 1 && tile01 == 2 & tile10 == 0 & tile11 == 2) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_00, currentPlane);
            }
            if (tile00 == 2 && tile01 == 2 & tile10 == 0 & tile11 == 2) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_09, currentPlane);
            }

            if (tile00 == 1 && tile01 == 2 & tile10 == 0 & tile11 == 2) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_03, currentPlane);
            }
            if (tile00 == 1 && tile01 == 1 & tile10 == 1 & tile11 == 1) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_05, currentPlane);
            }
            if (tile00 == 2 && tile01 == 2 & tile10 == 1 & tile11 == 1) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_01, currentPlane);
            }
            if (tile00 == 18 && tile01 == 18 & tile10 == 18 & tile11 == 18) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_22, currentPlane);
            }
            if (tile00 == 2 && tile01 == 1 & tile10 == 1 & tile11 == 0) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_02, currentPlane);
            }
            if (tile00 == 1 && tile01 == 1 & tile10 == 1 & tile11 == 0) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_02, currentPlane);
            }
            if (tile00 == 1 && tile01 == 1 & tile10 == 2 & tile11 == 0) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_04, currentPlane);
            }
            if (tile00 == 2 && tile01 == 0 & tile10 == 2 & tile11 == 0) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_06, currentPlane);
            }
            if (tile00 == 0 && tile01 == 2 & tile10 == 0 & tile11 == 2) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_07, currentPlane);
            }

            if (tile00 == 3 && tile01 == 3 & tile10 == 0 & tile11 == 0) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8) + 8, Images::Spikes, currentPlane);
            }

            if (tile00 == 2 && tile01 == 2 & tile10 == 4 & tile11 == 5) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_08, currentPlane);
            }

            if (tile00 == 6 && tile01 == 5 & tile10 == 0 & tile11 == 0) {//mnot sure
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_11, currentPlane);
            }

            if (tile00 == 0 && tile01 == 6 & tile10 == 0 & tile11 == 0) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_11, currentPlane);
            }

            if (tile00 == 11 && tile01 == 0 & tile10 == 0 & tile11 == 0) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_11a, currentPlane);
            }


            // ladders

            if (tile00 == 7 && tile01 == 7 & tile10 == 8 & tile11 == 8) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_13, currentPlane);
            }

            if (tile00 == 7 && tile01 == 7 & tile10 == 12 & tile11 == 12) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_14, currentPlane);
            }

            if (tile00 == 12 && tile01 == 12 & tile10 == 8 & tile11 == 8) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_15, currentPlane);
            }

            if (tile00 == 12 && tile01 == 12 & tile10 == 12 & tile11 == 12) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_16, currentPlane);
            }

            // Rope

            if (tile00 == 13 && tile01 == 0 & tile10 == 13 & tile11 == 15) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_17, currentPlane);
            }

            if (tile00 == 0 && tile01 == 14 & tile10 == 15 & tile11 == 14) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_18, currentPlane);
            }

            if (tile00 == 0 && tile01 == 0 & tile10 == 15 & tile11 == 15) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_19, currentPlane);
            }

            if (tile00 == 15 && tile01 == 15 & tile10 == 0 & tile11 == 0) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_23, currentPlane);
            }


            // Stairs

            if (tile00 == 2 && tile01 == 2 & tile10 == 9 & tile11 == 10) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_12, currentPlane);
            }

            // Slide

            if (tile00 == 2 && tile01 == 0 & tile10 == 19 & tile11 == 0) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_24, currentPlane);
            }

            if (tile00 == 2 && tile01 == 2 & tile10 == 1 & tile11 == 19) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_28, currentPlane);
            }

            if (tile00 == 2 && tile01 == 20 & tile10 == 20 & tile11 == 0) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_29, currentPlane);
            }

            if (tile00 == 0 && tile01 == 2 & tile10 == 0 & tile11 == 21) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_25, currentPlane);
            }

            if (tile00 == 2 && tile01 == 2 & tile10 == 21 & tile11 == 1) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_30, currentPlane);
            }

            if (tile00 == 22 && tile01 == 2 & tile10 == 0 & tile11 == 22) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_31, currentPlane);
            }
        }

    }






    switch (player.getStance()) {

        case Stance::Man_BounceJump_RH_03:
        case Stance::Man_BounceJump_RH_11:
        case Stance::Man_BounceJump_RH_25:
        case Stance::Man_BounceJump_LH_03:
        case Stance::Man_BounceJump_LH_11:
        case Stance::Man_BounceJump_LH_25:
        case Stance::Man_Walk_FallLandSpring_BK_03:
        case Stance::Man_Walk_FallLandSpring_BK_15:
        case Stance::Man_Walk_FallLandSpring_BK_23:
        case Stance::Man_Walk_FallLandSpring_BK_24:
            {
                uint8_t tile = world.getTile(player, 0, 0);

                if (world.isSpringTile_LH(tile)) {
                    SpritesU::drawPlusMaskFX(56, yOffset - Constants::GroundY + player.getY(), Images::Player_Bounce, currentPlane);
                }
                else {
                    SpritesU::drawPlusMaskFX(56, yOffset - Constants::GroundY + player.getY(), Images::Player_Bounce, 3 + currentPlane);
                }

            }
            break;

        default:
            {
                uint8_t stanceImg = pgm_read_byte(&Constants::StanceImgIdx[static_cast<uint16_t>(player.getStance())]);
                SpritesU::drawPlusMaskFX(56, yOffset - Constants::GroundY + player.getY(), Images::Player, (stanceImg * 3) + currentPlane);
            }
            break;
        
    }

    if (world.getWaveIdx() != Constants::NoWaves) {
        // SpritesU::drawOverwriteFX(world.getWave() - 128, 55 + yOffset - Constants::GroundY, Images::Waves, ((world.getWaveIdx() / 64) * 3) + currentPlane);
        SpritesU::drawOverwriteFX(world.getWave(), 55 + yOffset - Constants::GroundY, Images::Waves, ((world.getWaveIdx() / 64) * 3) + currentPlane);
        SpritesU::drawOverwriteFX(world.getWave() + 128, 55 + yOffset - Constants::GroundY, Images::Waves, ((world.getWaveIdx() / 64) * 3) + currentPlane);
    }

    if (world.getX() < 30) {
        // SpritesU::drawOverwriteFX(world.getWave(), 32, Images::Beach_LH, ((world.getWaveIdx() / 64) * 3) + currentPlane);
    }

    // Front palms
    SpritesU::drawPlusMaskFX(world.getPalm1() / 2, 10 + yOffset - Constants::GroundY, Images::Palm1, currentPlane);
    // SpritesU::drawPlusMaskFX(world.getPalm2() / 2, 10 + yOffset - Constants::GroundY, Images::Palm2, currentPlane);
    SpritesU::drawPlusMaskFX(world.getPalm3() / 2, 10 + yOffset - Constants::GroundY, Images::Palm3, currentPlane);
    // SpritesU::drawPlusMaskFX(world.getPalm4() / 2, 10 + yOffset - Constants::GroundY, Images::Palm4, currentPlane);


    world.update(true);


}

