#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"


void playGame_HandleMenu(Player &player, uint8_t pressed, uint8_t justPressed) {

    if (justPressed & A_BUTTON){//} || pressed & A_BUTTON) {

        if (player.getItemCount() != 0) {
                
            switch (player.getDirection()) {

                case Direction::Right:
                    {
                        uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);
                        uint8_t tile_R1D = world.getTile_RelativeToPlayer(1, -2);
                        uint8_t tile_R3D = world.getTile_RelativeToPlayer(3, -2);

                        if (world.isWaterTile(tile_R1D) && world.isWaterTile(tile_R3D) && player.getItem(menu.getY()).getItemType() == ItemType::LifeSaver) {
// Serial.print(tile_R1D);
// Serial.print(" ");
// Serial.println(tile_R3D);
                            uint8_t itemIdx = world.getItem(ItemType::LifeSaver_Hidden);
// Serial.println(itemIdx);                            
                            Item &item = world.getItem(itemIdx);
                            item.setItemType(ItemType::LifeSaver_InWater_RH);
                            item.setFrame(0);
                            item.setCounter(0);
item.setX(world.getMiddleground() + 56 - 2);
item.setY(16 + 4);     //SJH fix!                       
                            // player.pushSequence(Stance::Man_Hammering_RH_00, Stance::Man_Hammering_RH_10);
                            removeInventoryItem(GameState::PlayGame);

                        }

                        if (world.isWoodenBarrier(tile_R) && player.getItem(menu.getY()).getItemType() == ItemType::Hammer) {

                            player.pushSequence(Stance::Man_Hammering_RH_00, Stance::Man_Hammering_RH_10);
                            removeWorldandInventoryItem(ItemType::WoodenBarrier, GameState::PlayGame);

                        }

                        else if (world.isMysteryCrate(tile_R) && player.getItem(menu.getY()).getItemType() == ItemType::PinchBar) {

                            player.pushSequence(Stance::Man_Levering_RH_00, Stance::Man_Levering_RH_10);
                            removeWorldandInventoryItem(ItemType::MysteryCrate, GameState::PlayGame);

                        }

                        else if (world.isLockedDoor(tile_R) && player.getItem(menu.getY()).getItemType() == ItemType::Key1) {

                            removeWorldandInventoryItem(ItemType::LockedDoor, GameState::PlayGame);

                        }

                        else if (player.getItem(menu.getY()).getItemType() == ItemType::Sword) {

                            uint8_t enemySwordIdx = world.getClosestEnemy(EnemyType::SwordFighter);
                            player.setEnemyIdx(enemySwordIdx);

                            if (enemySwordIdx != 255) {

                                Enemy &enemy = world.getEnemy(enemySwordIdx);

                                player.push(Stance::Man_Sword_Stationary_RH);
                                menu.setDirection(Direction::Right);
                                menu.setGameState(GameState::Play_Battle);

                            }
                            // removeInventoryItem(GameState::Play_Battle);

                        }

                    }

                    break;

                case Direction::Left:
                    {
                        uint8_t tile_L = world.getTile_RelativeToPlayer(-1, 0);
                        uint8_t tile_L1D = world.getTile_RelativeToPlayer(-1, -2);
                        uint8_t tile_L3D = world.getTile_RelativeToPlayer(-3, -2);

                        if (world.isWaterTile(tile_L1D) && world.isWaterTile(tile_L3D) && player.getItem(menu.getY()).getItemType() == ItemType::LifeSaver) {
// Serial.print(tile_L1D);
// Serial.print(" ");
// Serial.println(tile_L3D);
                            uint8_t itemIdx = world.getItem(ItemType::LifeSaver_Hidden);
// Serial.println(itemIdx);                            
                            Item &item = world.getItem(itemIdx);
                            item.setItemType(ItemType::LifeSaver_InWater_LH);
                            item.setFrame(0);
                            item.setCounter(0);
item.setX(world.getMiddleground() + 56 - 2);
item.setY(16 + 4);                            
                            // player.pushSequence(Stance::Man_Hammering_RH_00, Stance::Man_Hammering_RH_10);
                            removeInventoryItem(GameState::PlayGame);

                        }

                        if (world.isWaterTile(tile_L1D) && world.isWaterTile(tile_L3D) && player.getItem(menu.getY()).getItemType() == ItemType::LifeSaver) {

                            player.pushSequence(Stance::Man_Hammering_LH_00, Stance::Man_Hammering_LH_10);
                            removeInventoryItem(GameState::PlayGame);

                        }

                        if (world.isWoodenBarrier(tile_L) && player.getItem(menu.getY()).getItemType() == ItemType::Hammer) {

                            player.pushSequence(Stance::Man_Hammering_LH_00, Stance::Man_Hammering_LH_10);
                            removeWorldandInventoryItem(ItemType::WoodenBarrier, GameState::PlayGame);

                        }

                        else if (world.isMysteryCrate(tile_L) && player.getItem(menu.getY()).getItemType() == ItemType::PinchBar) {

                            player.pushSequence(Stance::Man_Levering_LH_00, Stance::Man_Levering_LH_10);
                            removeWorldandInventoryItem(ItemType::MysteryCrate, GameState::PlayGame);

                        }

                        else if (world.isLockedDoor(tile_L) && player.getItem(menu.getY()).getItemType() == ItemType::Key1) {

                            removeWorldandInventoryItem(ItemType::LockedDoor, GameState::PlayGame);

                        }

                        else if (player.getItem(menu.getY()).getItemType() == ItemType::Sword) {

                            player.push(Stance::Man_Sword_Stationary_LH);
                            menu.setDirection(Direction::Right);
                            menu.setGameState(GameState::Play_Battle);

                        }

                    }

                    break;
            }

        }

    }
    else if (justPressed & UP_BUTTON) {

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
    else if (justPressed & DOWN_BUTTON) {

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
    
}


// void playGame_HandleMenu_LR(Direction direction, Stance stanceOffset)

void playGame_HandleMenu_OpenClose() {

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
                gameState = menu.getGameState();
            }

            break;

        default:
            break;

    }

}


void playGame_HandleMenu() {

    if (menu.getX() == 128) {

        menu.setGameState(gameState);
        menu.setDirection(Direction::Left);
        gameState = GameState::Inventory_Open;

    }
    else if (menu.getX() == 128 - 32) {

        gameState = GameState::Inventory_Open;
        menu.setDirection(Direction::Right);
        menu.setGameState(GameState::PlayGame);

    }
    
}