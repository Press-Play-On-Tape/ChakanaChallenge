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

                    playGame_HandleMenu_LR(player, Direction::Right, Stance::Man_Start);
                    break;

                case Direction::Left:

                    playGame_HandleMenu_LR(player, Direction::Left, Stance::Man_LH_Start - Stance::Man_RH_Start);
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


void playGame_HandleMenu_LR(Player &player, Direction direction, Stance stanceOffset) {

    uint8_t tile = world.getTile_RelativeToPlayer(direction == Direction::Left ? -1 : 1, 0);
    uint8_t tile_1D = world.getTile_RelativeToPlayer(direction == Direction::Left ? -1 : 1, -2);
    uint8_t tile_3D = world.getTile_RelativeToPlayer(direction == Direction::Left ? -3 : 3, -2);

    if (world.isWaterTile(tile_1D) && world.isWaterTile(tile_3D) && player.getItem(menu.getY()).getItemType() == ItemType::LifeSaver) {
// Serial.print(tile_R1D);
// Serial.print(" ");
// Serial.println(tile_R3D);
        uint8_t itemIdx = world.getItem(ItemType::LifeSaver_Hidden);
// Serial.println(itemIdx);                            
        Item &item = world.getItem(itemIdx);
        item.setItemType(direction == Direction::Right ? ItemType::LifeSaver_InWater_RH : ItemType::LifeSaver_InWater_LH);
        item.setFrame(0);
        item.setCounter(0);
Serial.print("Dir ");
Serial.println((uint8_t)direction);        
// item.setX(world.getMiddleground() + 56 - 2 + (direction == Direction::Left, -150, 0));
item.setX(56 - 2 + (direction == Direction::Left, -50, 0));
Serial.println(item.getX());        
item.setY(16 + 4);     //SJH fix!                       
        // player.pushSequence(Stance::Man_Hammering_RH_00, Stance::Man_Hammering_RH_10);
        removeInventoryItem(GameState::PlayGame);

    }

    if (world.isWoodenBarrier(tile) && player.getItem(menu.getY()).getItemType() == ItemType::Hammer) {

        player.pushSequence(Stance::Man_Hammering_RH_00 + stanceOffset, Stance::Man_Hammering_RH_10 + stanceOffset);
        removeWorldandInventoryItem(ItemType::WoodenBarrier, GameState::PlayGame);

    }

    else if (world.isMysteryCrate(tile) && player.getItem(menu.getY()).getItemType() == ItemType::PinchBar) {

        player.pushSequence(Stance::Man_Levering_RH_00 + stanceOffset, Stance::Man_Levering_RH_10 + stanceOffset);
        removeWorldandInventoryItem(ItemType::MysteryCrate, GameState::PlayGame);

    }

    else if (world.isLockedDoor(tile) && player.getItem(menu.getY()).getItemType() == ItemType::Key1) {

        removeWorldandInventoryItem(ItemType::LockedDoor, GameState::PlayGame);

    }

    else if (player.getItem(menu.getY()).getItemType() == ItemType::Sword) {

        uint8_t enemySwordIdx = world.getClosestEnemy(EnemyType::SwordFighter);
        player.setEnemyIdx(enemySwordIdx);

        if (enemySwordIdx != 255) {

            Enemy &enemy = world.getEnemy(enemySwordIdx);

            player.push(Stance::Man_Sword_Stationary_RH + stanceOffset);
            menu.setDirection(direction);
            menu.setGameState(GameState::Play_Battle);

        }
        // removeInventoryItem(GameState::Play_Battle);

    }

}

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