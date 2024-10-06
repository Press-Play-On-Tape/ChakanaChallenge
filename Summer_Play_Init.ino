#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"

int16_t enemy = -20;


void playGame_Init() {

    Player &player = world.getPlayer();
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


    for (uint8_t i = 0; i < Constants::ItemCount; i++) {

        Item &item = world.getItem(i);
        if (i == 2) {
            item.setItemType(ItemType::Puff);
            item.setX(128 + 16 - 32);
            item.setY(16);  
            item.setFrame(255);           
        }
        else if (i == 1) {
            item.setItemType(ItemType::Flame);
            item.setX(128);
            item.setY(16);            
        }
        // else if (i == 2) {
        //     item.setItemType(ItemType::PinchBar_Hidden);
        //     // item.setX(128 - 32 - 32);
        //     // item.setY(32);
        //     item.setX(128 + 64 + 48 - 32);
        //     item.setY(16);                        
        // }
        else if (i == 0) {
            item.setItemType(ItemType::Vine);
            item.setX(128 + 16 + 16  );
            item.setY(32);            
        }
        else {
            item.setItemType(ItemType::None);

        }

        player.getItem(i).setItemType(ItemType::None);


        // Item &item = world.getItem(i);
        // if (i == 0) {
        //     item.setItemType(ItemType::Puff);
        //     item.setX(128 + 16 - 32);
        //     item.setY(16);  
        //     item.setFrame(255);           
        // }
        // else {
        //     item.setItemType(ItemType::None);

        // }

        player.getItem(i).setItemType(ItemType::None);

    }

        player.getItem(0).setItemType(ItemType::Hammer);
        player.getItem(1).setItemType(ItemType::PinchBar);
        player.getItem(2).setItemType(ItemType::Amulet);
        player.getItem(3).setItemType(ItemType::Hammer);
        player.getItem(4).setItemType(ItemType::Key1);
        player.getItem(5).setItemType(ItemType::Amulet);

        player.setItemCount(6);


        // uint16_t waveCount = 0;
        // uint16_t background = 0;


    Enemy &enemy = world.getEnemy(0);
    enemy.setX(128 + 16);
    // enemy.setX(32);
    enemy.setY(16);
    enemy.setStance(Stance::Enemy_Walk_Bow_LH_00);

}


void playGame_Update() {
    
    Player &player = world.getPlayer();

    frameCount++;
        
    if (frameCount % 4 == 0) {
    
        uint8_t pressed = getPressedButtons();
        uint8_t justPressed = getJustPressedButtons();

        if (player.isEmpty()) {

            if (justPressed & B_BUTTON || pressed & B_BUTTON) {
                           
                if (menu.getX() == 128) {
                    gameState = GameState::Inventory_Open;
                    menu.setDirection(Direction::Left);
                }
                else if (menu.getX() == 128 - 32) {
                    gameState = GameState::Inventory_Open;
                    menu.setDirection(Direction::Right);
                }

            }
            else if (gameState == GameState::Inventory_Open && (justPressed & A_BUTTON || pressed & A_BUTTON)) {

                if (player.getItemCount() != 0) {
                        
                    switch (player.getDirection()) {

                        case Direction::Right:
                            {
                                uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);

                                if (world.isWoodenBarrier(tile_R) && player.getItem(menu.getY()).getItemType() == ItemType::Hammer) {

                                    player.pushSequence(Stance::Man_Hammering_RH_00, Stance::Man_Hammering_RH_10);
                                    uint8_t woodenBarrier = world.getItem(ItemType::WoodenBarrier);
                                    world.getItem(woodenBarrier).setCounter(1);     
                                    menu.setDirection(Direction::Right);
                                    player.removeInventoryItem(menu.getY());

                                }

                                if (world.isMysteryCrate(tile_R) && player.getItem(menu.getY()).getItemType() == ItemType::PinchBar) {

                                    player.pushSequence(Stance::Man_Levering_RH_00, Stance::Man_Levering_RH_10);
                                    uint8_t mysteryCrate = world.getItem(ItemType::MysteryCrate);
                                    world.getItem(mysteryCrate).setCounter(1);     
                                    menu.setDirection(Direction::Right);
                                    player.removeInventoryItem(menu.getY());

                                }

                                if (world.isLockedDoor(tile_R) && player.getItem(menu.getY()).getItemType() == ItemType::Key1) {

                                    uint8_t lockedDoor = world.getItem(ItemType::LockedDoor);
                                    world.getItem(lockedDoor).setCounter(1);     
                                    menu.setDirection(Direction::Right);
                                    player.removeInventoryItem(menu.getY());

                                }

                            }

                            break;

                        case Direction::Left:
                            {
                                uint8_t tile_L = world.getTile_RelativeToPlayer(-1, 0);

                                if (world.isWoodenBarrier(tile_L) && player.getItem(menu.getY()).getItemType() == ItemType::Hammer) {

                                    player.pushSequence(Stance::Man_Hammering_LH_00, Stance::Man_Hammering_LH_10);
                                    uint8_t woodenBarrier = world.getItem(ItemType::WoodenBarrier);
                                    world.getItem(woodenBarrier).setCounter(1);     
                                    menu.setDirection(Direction::Right);
                                    player.removeInventoryItem(menu.getY());

                                }

                                if (world.isMysteryCrate(tile_L) && player.getItem(menu.getY()).getItemType() == ItemType::PinchBar) {

                                    player.pushSequence(Stance::Man_Levering_LH_00, Stance::Man_Levering_LH_10);
                                    uint8_t mysteryCrate = world.getItem(ItemType::MysteryCrate);
                                    world.getItem(mysteryCrate).setCounter(1);     
                                    menu.setDirection(Direction::Right);
                                    player.removeInventoryItem(menu.getY());

                                }

                                if (world.isLockedDoor(tile_L) && player.getItem(menu.getY()).getItemType() == ItemType::Key1) {

                                    uint8_t lockedDoor = world.getItem(ItemType::LockedDoor);
                                    world.getItem(lockedDoor).setCounter(1);     
                                    menu.setDirection(Direction::Right);
                                    player.removeInventoryItem(menu.getY());

                                }

                            }

                            break;
                    }

                }

            }
            else if (gameState == GameState::Inventory_Open && (justPressed & UP_BUTTON)) {

                // Showing top 3 items and can not move up ..
                if (menu.getTop() == 0 && menu.getY() == 0) { }

                // Showing top 3 items and can move up .. 
                else if (menu.getTop() == 0 && menu.getY() > 0 && menu.getY() < player.getItemCount()) {
                    menu.setY(menu.getY() - 1);
                }

                // Showing bottomn 3 items and bottom item is selected ..
                else if (menu.getTop() == player.getItemCount() - 3 && menu.getY() == player.getItemCount() - 1) {
                    menu.setY(menu.getY() - 1);
                }

                // Otherwise scroll top and selected up ..
                else {
                    menu.setTop(menu.getTop() - 1);
                    menu.setY(menu.getY() - 1);
                }
                
            }
            else if (gameState == GameState::Inventory_Open && (justPressed & DOWN_BUTTON)) {

                // Bottom item is already selected and cannot move ..
                if (menu.getY() == player.getItemCount() - 1) { }

                // Showing top 3 items and top row is selected, move down ..
                else if (menu.getTop() == 0 && menu.getY() == 0 && menu.getY() < player.getItemCount()) {
                    menu.setY(menu.getY() + 1);
                }

                // Showing all 3 items ..
                else if (menu.getTop() == 0 && menu.getY() < player.getItemCount() - 1 && player.getItemCount() == 3) {
                    menu.setY(menu.getY() + 1);
                }

                // Showing top 3 items and top row is selected, move down ..
                else if (menu.getTop() == 0 && menu.getY() < player.getItemCount()) {
                    menu.setTop(menu.getTop() + 1);
                    menu.setY(menu.getY() + 1);
                }

                // Showing bottom 3 items and bottom 
                else if (menu.getTop() == player.getItemCount() - 3) {
                    menu.setY(menu.getY() + 1);
                }

                // Otherwise scroll top and selected down ..
                else {
                    menu.setTop(menu.getTop() + 1);
                    menu.setY(menu.getY() + 1);
                }

            }

            else if (gameState == GameState::PlayGame && (justPressed & UP_BUTTON || pressed & UP_BUTTON)) {

                switch (player.getDirection()) {

                    case Direction::Backward:
                        {
                            uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                            uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);

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
                            uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                            uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);

                            if (world.isLadderTile_Lower(tile) && world.isLadderTile_Lower(tile_R)) {

                                player.pushSequence(Stance::Man_ClimbLadder_BK_RH_UP_01, Stance::Man_ClimbLadder_BK_RH_UP_07);

                            }

                        }
                        break;

                    case Direction::Left:
                        {
                            uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                            uint8_t tile_L = world.getTile_RelativeToPlayer(-1, 0);

                            if (world.isLadderTile_Lower(tile) && world.isLadderTile_Lower(tile_L)) {

                                player.pushSequence(Stance::Man_ClimbLadder_BK_LH_UP_01, Stance::Man_ClimbLadder_BK_LH_UP_07);

                            }

                        }
                        break;

                    case Direction::Forward:
                        {
                            uint8_t tile_L = world.getTile_RelativeToPlayer(-1, 0);
                            uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                            uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);

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

            else if (gameState == GameState::PlayGame && (justPressed & DOWN_BUTTON || pressed & DOWN_BUTTON)) {

                switch (player.getDirection()) {

                    case Direction::Backward:
                        {
                            uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                            uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);
                            uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                            uint8_t tile_RD = world.getTile_RelativeToPlayer(1, -1);

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
                            uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                            uint8_t tile_RD = world.getTile_RelativeToPlayer(1, -1);

                            if (world.isLadderTile_Upper(tile_D) && world.isLadderTile_Upper(tile_RD)) {

                                player.pushSequence(Stance::Man_ClimbLadder_BK_RH_DOWN_01, Stance::Man_ClimbLadder_BK_RH_DOWN_07);

                            }

                        }
                        break;

                    case Direction::Left:
                        {
                            uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                            uint8_t tile_LD = world.getTile_RelativeToPlayer(-1, -1);

                            if (world.isLadderTile_Upper(tile_LD) && world.isLadderTile_Upper(tile_D)) {

                                player.pushSequence(Stance::Man_ClimbLadder_BK_LH_DOWN_01, Stance::Man_ClimbLadder_BK_LH_DOWN_07);

                            }

                        }
                        break;

                    case Direction::Forward:
                        {
                            uint8_t tile_LD = world.getTile_RelativeToPlayer(-1, -1);
                            uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                            uint8_t tile_RD = world.getTile_RelativeToPlayer(1, -1);

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

            else if (gameState == GameState::PlayGame && (justPressed & LEFT_BUTTON || pressed & LEFT_BUTTON) && player.canMoveLeft()) {

                switch (player.getDirection()) {

                    case Direction::Left:
                        {
                           
                            uint8_t tile_L = world.getTile_RelativeToPlayer(-1, 0);
                            uint8_t tile_LD = world.getTile_RelativeToPlayer(-1, -1);

                            if (world.isEmptyTile(tile_LD) && world.isEmptyTile(tile_L)) {

                                if (justPressed & A_BUTTON || pressed & A_BUTTON) { 

                                    uint8_t tile_L2 = world.getTile_RelativeToPlayer(-2, 0);
                                    uint8_t tile_L3 = world.getTile_RelativeToPlayer(-3, 0);
                                    uint8_t tile_L2D = world.getTile_RelativeToPlayer(-2, -1);
                                    uint8_t tile_L3D = world.getTile_RelativeToPlayer(-3, -1);
                                    uint8_t tile_L3D2 = world.getTile_RelativeToPlayer(-3, -2);

                                    if (world.isVineTile_RH(tile_L) && (player.getStance() < Stance::Man_Vine_LH_01 || player.getStance() > Stance::Man_Vine_LH_20)) {

                                        Item &item = world.getItem(world.getItem(ItemType::Vine));

                                        if ((item.getCounter() >= 144 && item.getCounter() < 208)) {

                                            item.setCounter(182);
                                            player.clear();
                                            player.pushSequence(Stance::Man_Vine_LH_01, Stance::Man_Vine_LH_20);

                                        }     
                                        else {
                                            
                                            player.setFalls(0);
                                            player.pushSequence(Stance::Man_Walk_FallDown_LH_01, Stance::Man_Walk_FallDown_LH_06);

                                        }

                                    }
                                    else if (world.isEmptyTile(tile_L) && world.isEmptyTile(tile_L2) && world.isEmptyTile(tile_L3) && 
                                        world.isEmptyTile(tile_LD) && world.isEmptyTile(tile_L2D) && world.canWalkOnTile(tile_L3D)) {     

                                        player.pushSequence(Stance::Man_WalkingJump_LH_25_01, Stance::Man_WalkingJump_LH_25_11);

                                    }    
                                    else if (world.isEmptyTile(tile_L) && world.isEmptyTile(tile_L2) && world.isEmptyTile(tile_L3) &&
                                             world.isEmptyTile(tile_LD) && world.isEmptyTile(tile_L2D) && world.isEmptyTile(tile_L3D) && !world.isEmptyTile(tile_L3D2)) {     

                                        player.setFalls(0);
                                        player.pushSequence(Stance::Man_WalkingJump_LH_1D_25_01, Stance::Man_WalkingJump_LH_1D_25_11);

                                    }                     
                                    else if (world.isEmptyTile(tile_L) && world.isEmptyTile(tile_L2) && world.isEmptyTile(tile_L3) &&
                                             world.isEmptyTile(tile_LD) && world.isEmptyTile(tile_L2D) && world.isEmptyTile(tile_L3D)) {     

                                        player.setFalls(0);
                                        player.pushSequence(Stance::Man_WalkingJump_LH_2D_25_01, Stance::Man_WalkingJump_LH_2D_25_11);

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
                                uint8_t tile_R1 = world.getTile_RelativeToPlayer(1, 0);
                                uint8_t tile_L1 = world.getTile_RelativeToPlayer(-1, 0);
                                uint8_t tile_LU = world.getTile_RelativeToPlayer(-1, 1);
                                uint8_t tile_L2U = world.getTile_RelativeToPlayer(-2, 1);
                                uint8_t tile_L3D2 = world.getTile_RelativeToPlayer(-3, -2);


                                if (world.isSlideTile_Full_RH(tile_LD) && world.canWalkOnTile(tile_L3D2)) {

                                    player.setFalls(0);
                                    player.pushSequence(Stance::Man_Slide_LH_Full_Land_01, Stance::Man_Slide_LH_Full_Land_13);

                                }
                                else if (world.isSlideTile_Full_RH(tile_LD) && !world.canWalkOnTile(tile_L3D2)) {

                                    player.setFalls(0);
                                    player.pushSequence(Stance::Man_Slide_LH_Full_01, Stance::Man_Slide_LH_Full_13);

                                }
                                else if (world.isSlideTile_RH(tile_LD)) {

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
                            uint8_t tile_U = world.getTile_RelativeToPlayer(0, 1);
                            uint8_t tile_LU = world.getTile_RelativeToPlayer(-1, 1);
                            uint8_t tile_L2U = world.getTile_RelativeToPlayer(-2, 1);

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

            else if (gameState == GameState::PlayGame && (justPressed & RIGHT_BUTTON || pressed & RIGHT_BUTTON) && player.canMoveRight()) {

                switch (player.getDirection()) {

                    case Direction::Right:
                        {
                            uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);
                            uint8_t tile_RD = world.getTile_RelativeToPlayer(1, -1);

                            if (world.isEmptyTile(tile_RD) && world.isEmptyTile(tile_R)) {

                                if (justPressed & A_BUTTON || pressed & A_BUTTON) { 

                                    uint8_t tile_R2 = world.getTile_RelativeToPlayer(2, 0);
                                    uint8_t tile_R3 = world.getTile_RelativeToPlayer(3, 0);
                                    uint8_t tile_R2D = world.getTile_RelativeToPlayer(2, -1);
                                    uint8_t tile_R3D = world.getTile_RelativeToPlayer(3, -1);
                                    uint8_t tile_R3D2 = world.getTile_RelativeToPlayer(3, -2);

                                    if (world.isVineTile_LH(tile_R) && (player.getStance() < Stance::Man_Vine_RH_01 || player.getStance() > Stance::Man_Vine_RH_20)) {

                                        Item &item = world.getItem(world.getItem(ItemType::Vine));

                                        if ((item.getCounter() >= 0 && item.getCounter() < 32) || (item.getCounter() >= 320 && item.getCounter() < 352)) {

                                            item.setCounter(6);
                                            player.clear();
                                            player.pushSequence(Stance::Man_Vine_RH_01, Stance::Man_Vine_RH_20);

                                        }     
                                        else {

                                            player.setFalls(0);
                                            player.pushSequence(Stance::Man_Walk_FallDown_RH_01, Stance::Man_Walk_FallDown_RH_06);

                                        }

                                    }
                                    else if (world.isEmptyTile(tile_R) && world.isEmptyTile(tile_R2) && world.isEmptyTile(tile_R3) &&
                                             world.isEmptyTile(tile_RD) && world.isEmptyTile(tile_R2D) && world.canWalkOnTile(tile_R3D)) {     

                                        player.pushSequence(Stance::Man_WalkingJump_RH_25_01, Stance::Man_WalkingJump_RH_25_11);

                                    }    
                                    else if (world.isEmptyTile(tile_R) && world.isEmptyTile(tile_R2) && world.isEmptyTile(tile_R3) &&
                                             world.isEmptyTile(tile_RD) && world.isEmptyTile(tile_R2D) && world.isEmptyTile(tile_R3D) && !world.isEmptyTile(tile_R3D2)) {     

                                        player.setFalls(0);
                                        player.pushSequence(Stance::Man_WalkingJump_RH_1D_25_01, Stance::Man_WalkingJump_RH_1D_25_11);

                                    }                     
                                    else if (world.isEmptyTile(tile_R) && world.isEmptyTile(tile_R2) && world.isEmptyTile(tile_R3) &&
                                             world.isEmptyTile(tile_RD) && world.isEmptyTile(tile_R2D) && world.isEmptyTile(tile_R3D)) {     

                                        player.setFalls(0);
                                        player.pushSequence(Stance::Man_WalkingJump_RH_2D_25_01, Stance::Man_WalkingJump_RH_2D_25_11);

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

                                uint8_t tile_R2 = world.getTile_RelativeToPlayer(2, 0);
                                uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                                uint8_t tile_L = world.getTile_RelativeToPlayer(-1, 0);
                                uint8_t tile_LU = world.getTile_RelativeToPlayer(-1, 1);
                                uint8_t tile_RU = world.getTile_RelativeToPlayer(1, 1);
                                uint8_t tile_R2U = world.getTile_RelativeToPlayer(2, 1);
                                uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                                uint8_t tile_RD = world.getTile_RelativeToPlayer(1, -1);
                                uint8_t tile_R2D = world.getTile_RelativeToPlayer(2, -1);
                                uint8_t tile_R3D2 = world.getTile_RelativeToPlayer(3, -2);


                                if (world.isSlideTile_Full_LH(tile_RD) && world.canWalkOnTile(tile_R3D2)) {

                                    player.setFalls(0);
                                    player.pushSequence(Stance::Man_Slide_RH_Full_Land_01, Stance::Man_Slide_RH_Full_Land_13);

                                }
                                else if (world.isSlideTile_Full_LH(tile_RD) && !world.canWalkOnTile(tile_R3D2)) {

                                    player.setFalls(0);
                                    player.pushSequence(Stance::Man_Slide_RH_Full_01, Stance::Man_Slide_RH_Full_13);

                                }
                                else if (world.isSlideTile_LH(tile_RD)) {

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
                            uint8_t tile_U = world.getTile_RelativeToPlayer(0, 1);
                            uint8_t tile_RU = world.getTile_RelativeToPlayer(1, 1);
                            uint8_t tile_R2U = world.getTile_RelativeToPlayer(2, 1);

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

            else if (gameState == GameState::PlayGame && (justPressed & A_BUTTON || pressed & A_BUTTON)) {

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
                            uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                            uint8_t tile_U = world.getTile_RelativeToPlayer(0, 2);

                            if (world.isEmptyTile(tile_U)) {

                                if (world.canJumpUpOntoTile(tile)) {

                                    player.pushSequence(Stance::Man_StandingJump_RH_UP_01, Stance::Man_StandingJump_RH_UP_06); 

                                }
                                else if (world.isSpringTile(tile)) {    

                                    uint8_t tile_3U = world.getTile_RelativeToPlayer(0, 3);
                                    uint8_t tile_4U = world.getTile_RelativeToPlayer(0, 4);

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
                            uint8_t tile = world.getTile_RelativeToPlayer(0, 0);

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

                            uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                            uint8_t tile_U = world.getTile_RelativeToPlayer(0, 2);

                            if (world.isEmptyTile(tile_U)) {

                                if (world.canJumpUpOntoTile(tile)) {

                                    player.pushSequence(Stance::Man_StandingJump_LH_UP_01, Stance::Man_StandingJump_LH_UP_06); 

                                }
                                else if (world.isSpringTile(tile)) {     
                                    uint8_t tile_3U = world.getTile_RelativeToPlayer(0, 3);
                                    uint8_t tile_4U = world.getTile_RelativeToPlayer(0, 4);

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
                            uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);
                            uint8_t tile_RU = world.getTile_RelativeToPlayer(1, 1);
                            uint8_t tile_RD = world.getTile_RelativeToPlayer(1, -1);
                            uint8_t tile_R2D = world.getTile_RelativeToPlayer(2, -1);

                            if (world.canJumpUpOntoTile(tile_R)) {

                                player.clear();
                                player.pushSequence(Stance::Man_WalkingJump_RH_UP_01, Stance::Man_WalkingJump_RH_UP_05); 

                            }
                            else if (world.isPunjiTile(tile_R)) {

                                player.clear();
                                player.pushSequence(Stance::Man_WalkingJump_RH_25_02, Stance::Man_WalkingJump_RH_25_11); 

                            }     
                            else if (world.canWalkPastTile(tile_R) && world.canWalkOnTile(tile_R2D)) {
 
                                player.clear();
                                player.pushSequence(Stance::Man_WalkingJump_RH_2_02, Stance::Man_WalkingJump_RH_2_08); 

                            }
                            else {

                                player.clear();
                                player.pushSequence(Stance::Man_WalkingJump_RH_02, Stance::Man_WalkingJump_RH_08); 

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

                                player.clear();
                                player.pushSequence(Stance::Man_WalkingJump_RH_25_02, Stance::Man_WalkingJump_RH_25_11); 

                            }     
                            else if (world.isEmptyTile(tile_R) && world.canWalkOnTile(tile_RD) && world.canWalkOnTile(tile_R3D)) {

                                player.clear();
                                player.pushSequence(Stance::Man_WalkingJump_RH_2_02, Stance::Man_WalkingJump_RH_2_08); 

                            }     

                        }
                        break;

                    case Stance::Man_Walk_LH_01:
                        {                            
                            uint8_t tile_L = world.getTile_RelativeToPlayer(-1, 0);
                            uint8_t tile_LD = world.getTile_RelativeToPlayer(-1, -1);
                            uint8_t tile_L2D = world.getTile_RelativeToPlayer(-2, -1);

                            if (world.canJumpUpOntoTile(tile_L)) {

                                player.clear();
                                player.pushSequence(Stance::Man_WalkingJump_LH_UP_01, Stance::Man_WalkingJump_LH_UP_05); 

                            }
                            else if (world.isPunjiTile(tile_L)) {

                                player.clear();
                                player.pushSequence(Stance::Man_WalkingJump_LH_25_02, Stance::Man_WalkingJump_LH_25_11); 

                            }
                            else if (world.canWalkPastTile(tile_L) && world.canWalkOnTile(tile_L2D)) {

                                player.clear();
                                player.pushSequence(Stance::Man_WalkingJump_LH_2_02, Stance::Man_WalkingJump_LH_2_08); 

                            }
                            else {

                                player.clear();
                                player.pushSequence(Stance::Man_WalkingJump_LH_02, Stance::Man_WalkingJump_LH_08); 

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

                                player.clear();
                                player.pushSequence(Stance::Man_WalkingJump_LH_25_02, Stance::Man_WalkingJump_LH_25_11); 

                            }     
                            else if (world.isEmptyTile(tile_L) && world.canWalkOnTile(tile_D) && world.canWalkOnTile(tile_LD)) {

                                player.clear();
                                player.pushSequence(Stance::Man_WalkingJump_LH_2_02, Stance::Man_WalkingJump_LH_2_08); 

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

            FX::seekData(Constants::StanceY + static_cast<uint16_t>(player.getStance()));
            int8_t stanceY = FX::readPendingUInt8();
            player.setY(player.getY() - stanceY);
            FX::readEnd();

            FX::seekData(Constants::xForeground + static_cast<uint16_t>(player.getStance()));
            int8_t b = FX::readPendingUInt8();
            world.incForeground(b);
            FX::readEnd();

            FX::seekData(Constants::xMiddleground + static_cast<uint16_t>(player.getStance()));
            b = FX::readPendingUInt8();
            world.incMiddleground(b);
            FX::readEnd();

            FX::seekData(Constants::xBackground + static_cast<uint16_t>(player.getStance()));
            b = FX::readPendingUInt8();
            world.incBackground(b);
            FX::readEnd();


            // Has the player collided with an item?

            uint8_t yOffset = Constants::GroundY;
            if (player.getY() < 5) yOffset = Constants::GroundY - player.getY();
            Rect playerRect = { 59, yOffset - Constants::GroundY + player.getY(), 10, 16 };

            for (uint8_t i = 0; i < Constants::ItemCount; i++) {
              
                Item &item = world.getItem(i);

                
                // Can we skip this one?

                if (item.getItemType() == ItemType::MysteryCrate && item.getFrame() == 8) continue;



                // If the item is the 'puff' then we are at the last of the items, stop iterating ..

                if (item.getItemType() == ItemType::Puff) break;


                // Otherwise check if we have collided ..

                Rect itemRect = { item.getX() + world.getMiddleground() - 4 + 1, yOffset - item.getY() + 1, 14, 14 };

                if (collide(playerRect, itemRect)) {

                    Item &puff = world.getItem(world.getItem(ItemType::Puff));

                    switch (item.getItemType()) {

                        case ItemType::Key1:
                        case ItemType::PinchBar:
                        case ItemType::Hammer:
                        case ItemType::Amulet:
                        case ItemType::Potion:
                        case ItemType::Anchor:

                            if (item.getCounter() == 0) {

                                puff.setX(item.getX());
                                puff.setY(item.getY());
                                puff.setFrame(0);
                                item.setCounter(3);

                            }
                            break;

                        case ItemType::Punji:

                            if (item.getCounter() == 0) {
                                    
                                switch (player.getDirection()) {

                                    case Direction::Left:
                                        playerRect.width = 4;
                                        break;

                                    case Direction::Right:
                                        playerRect.x = playerRect.x + 8;
                                        playerRect.width = playerRect.width - 8;
                                        break;

                                }

                                itemRect = { item.getX() + world.getMiddleground() - 4 + 4, yOffset - item.getY() + 14, 8, 2 };

                                if (collide(playerRect, itemRect)) {

                                    item.setCounter(1);

                                    switch (player.getDirection()) {

                                        case Direction::Left:
                                            player.clear();
                                            player.pushSequence(Stance::Man_Die_Fall_LH_01, Stance::Man_Die_Fall_LH_04);
                                            break;

                                        case Direction::Right:
                                            player.clear();
                                            player.pushSequence(Stance::Man_Die_Fall_RH_01, Stance::Man_Die_Fall_RH_04);
                                            break;

                                    }

                                }

                            }

                            break;

                        case ItemType::Flame:
                            
                         // itemRect = { item.getX() + world.getMiddleground() - 4 + 1, yOffset - item.getY() + 1, 14, 14 };                            
                            itemRect = { item.getX() + world.getMiddleground() - 4 + 4, yOffset - item.getY() + 14, 8, 2 };

                            if (collide(playerRect, itemRect)) {

                                switch (player.getDirection()) {

                                    case Direction::Left:

                                        switch (player.getStance()) {

                                            case Stance::Man_WalkingJump_LH_2_08:
                                                {
                                                    uint8_t xPos = item.getX() + world.getMiddleground();

                                                    if (xPos == 56) {

                                                        player.clear();
                                                        player.pushSequence(Stance::Man_Die_Fire_LH_01, Stance::Man_Die_Fire_LH_12);
                                                        player.push(Stance::Man_Die_Fire_Adj_LH_02);

                                                    }
                                                    else if (xPos == 64) {

                                                        player.clear();
                                                        player.pushSequence(Stance::Man_Die_Fire_LH_01, Stance::Man_Die_Fire_LH_12);
                                                        player.push(Stance::Man_Die_Fire_Adj_LH_01);

                                                    }

                                                }
                                                break;

                                            case Stance::Man_Walk_LH_02:

                                                player.clear();
                                                player.pushSequence(Stance::Man_Die_Fire_LH_01, Stance::Man_Die_Fire_LH_12);
                                                player.pushSequence(Man_Walk_LH_03, Stance::Man_Walk_LH_06);

                                                break;


                                        }

                                        break;

                                    case Direction::Right:

                                        switch (player.getStance()) {

                                            case Stance::Man_WalkingJump_RH_2_08:
                                                {
                                                    uint8_t xPos = item.getX() + world.getMiddleground();

                                                    if (xPos == 56) {

                                                        player.clear();
                                                        player.pushSequence(Stance::Man_Die_Fire_RH_01, Stance::Man_Die_Fire_RH_12);
                                                        player.push(Stance::Man_Die_Fire_Adj_RH_01);

                                                    }
                                                    else if (xPos == 64) {

                                                        player.clear();
                                                        player.pushSequence(Stance::Man_Die_Fire_RH_01, Stance::Man_Die_Fire_RH_12);
                                                        player.push(Stance::Man_Die_Fire_Adj_RH_02);

                                                    }

                                                }
                                                break;

                                            case Stance::Man_Walk_RH_03:

                                                player.clear();
                                                player.pushSequence(Stance::Man_Die_Fire_RH_01, Stance::Man_Die_Fire_RH_12);
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

                    break;

                }

            }


            // Handle falling and other special actions ..

            switch (static_cast<Stance>(newStance)) {

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

                                if (player.getFalls() >= 3) {

                                    if (world.isSpringTile(tile_D)) {
                                    
                                        player.pushSequence(Stance::Man_Walk_FallLandSpring_BK_01, Stance::Man_Walk_FallLandSpring_BK_28);
                                    }
                                    else {

                                        player.pushSequence(Stance::Man_Die_Fall_RH_01, Stance::Man_Die_Fall_RH_04); 
                                        player.pushSequence(Stance::Man_Walk_FallLand_BK_01, Stance::Man_Walk_FallLand_BK_04);

                                    }

                                }
                                else if (world.isSpringTile(tile_D)) {

                                    player.pushSequence(Stance::Man_Walk_FallLandSpring_BK_01, Stance::Man_Walk_FallLandSpring_BK_28);

                                }                                
                                else if (world.isSpikeTile(tile_D)) {

                                    player.pushSequence(Stance::Man_Die_Fall_RH_01, Stance::Man_Die_Fall_RH_04); 
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
                case Stance::Man_Rollers_Fall_RH_04:
                    {
  
                        uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                        uint8_t tile_D2 = world.getTile_RelativeToPlayer(0, -2);

                        if (world.isEmptyTile(tile_D)) {

                            player.incFalls();

                            if (player.getFalls() < 3) {

                                if (world.isEmptyTile(tile_D2)) {                                    

                                    player.pushSequence(Stance::Man_Walk_FallMore_RH_01, Stance::Man_Walk_FallMore_RH_02); 

                                }
                                else {

                                    if (world.isSpikeTile(tile_D)) {

                                        player.pushSequence(Stance::Man_Die_Fall_RH_01, Stance::Man_Die_Fall_RH_04); 
                                        player.pushSequence(Stance::Man_Walk_FallLand_RH_01, Stance::Man_Walk_FallLand_RH_04);

                                    }
                                    else {

                                        player.pushSequence(Stance::Man_Walk_FallLand_RH_01, Stance::Man_Walk_FallLand_RH_04);

                                    } 

                                }

                            }
                            else {
                             
                                player.pushSequence(Stance::Man_Die_Fall_RH_01, Stance::Man_Die_Fall_RH_04); 
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
                case Stance::Man_Rollers_Fall_LH_04:
                    {
                           
                        uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                        uint8_t tile_D2 = world.getTile_RelativeToPlayer(0, -2);

                        if (world.isEmptyTile(tile_D)) {

                            player.incFalls();

                            if (player.getFalls() < 3) {

                                if (world.isEmptyTile(tile_D2)) {

                                    player.pushSequence(Stance::Man_Walk_FallMore_LH_01, Stance::Man_Walk_FallMore_LH_02); 

                                }
                                else {
                                    if (world.isSpikeTile(tile_D)) {

                                        player.pushSequence(Stance::Man_Die_Fall_LH_01, Stance::Man_Die_Fall_LH_04); 
                                        player.pushSequence(Stance::Man_Walk_FallLand_LH_01, Stance::Man_Walk_FallLand_LH_04); 

                                    }
                                    else {

                                        player.pushSequence(Stance::Man_Walk_FallLand_LH_01, Stance::Man_Walk_FallLand_LH_04); 

                                    }

                                }

                            }
                            else {

                                player.pushSequence(Stance::Man_Die_Fall_LH_01, Stance::Man_Die_Fall_LH_04); 
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
                        FX::seekData(Constants::subsititueStance + (static_cast<uint16_t>(player.getStance()) * 2));
                        uint16_t subsituteStance = FX::readPendingUInt16();
                        FX::readEnd();

                        if (subsituteStance != 65535) {
                            player.setStance(subsituteStance);
                        }

                    }
                    break;

            }

        }


        for (uint8_t i = 0; i < Constants::EnemyCount; i++) {

            Enemy &enemy = world.getEnemy(i);

            if (enemy.getX() == 0) continue;
                
            if (!enemy.isEmpty()) {

                Point offset;

                uint16_t newStance = enemy.pop();

                enemy.setStance(newStance);

                FX::seekData(Constants::StanceY + static_cast<uint16_t>(enemy.getStance()));
                int8_t stanceY = FX::readPendingUInt8();
                enemy.setY(enemy.getY() - stanceY);
                FX::readEnd();
               

                FX::seekData(Constants::xForeground + static_cast<uint16_t>(enemy.getStance()));
                int8_t b = FX::readPendingUInt8();
                world.incForeground(b);
                FX::readEnd();

                FX::seekData(Constants::xMiddleground + static_cast<uint16_t>(enemy.getStance()));
                b = FX::readPendingUInt8();
                world.incMiddleground(b);
                FX::readEnd();

                FX::seekData(Constants::xBackground + static_cast<uint16_t>(enemy.getStance()));
                b = FX::readPendingUInt8();
                world.incBackground(b);
                FX::readEnd();


                switch (newStance) {

                    case Stance::Enemy_Fire_LH_07:
                        {
                            Item &item = enemy.getItem();
                            item.setItemType(ItemType::Arrow_LH);
                            item.setCounter(25 * 4);
                            item.setX(enemy.getX());
                            item.setY(enemy.getY() - 7);
                        }
                        break;

                    case Stance::Enemy_Fire_RH_07:
                        {
                            Item &item = enemy.getItem();
                            item.setItemType(ItemType::Arrow_RH);
                            item.setCounter(25 * 4);
                            item.setX(enemy.getX());
                            item.setY(enemy.getY() - 7);
                        }
                        break;

                }

            }

        }

    }

    switch (menu.getDirection()) {

        case Direction::Left:

            if (menu.getX() > 128 - 32) {
                menu.setX(menu.getX() - 2);
            }
            else {
                menu.setDirection(Direction::None);
            }

            break;


        case Direction::Right:

            if (menu.getX() < 128) {
                menu.setX(menu.getX() + 2);
            }
            else {
                menu.setDirection(Direction::None);
                gameState = GameState::PlayGame;
            }

            break;

        default:
            break;
    }


    world.updateEnemies();

}


void playGame(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    Player &player = world.getPlayer();

    if (a.needsUpdate()) playGame_Update();

    uint8_t yOffset = Constants::GroundY;

    if (player.getY() < 5) yOffset = Constants::GroundY - player.getY();

    uint8_t currentPlane = a.currentPlane();

    renderWorld(currentPlane);

    world.update(true);


}
