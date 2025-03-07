#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"


void playGame_HandleMenu(Player &player, uint8_t pressed, uint8_t justPressed) {

    #ifndef DEBUG_HANDLE_MENUS

    if (justPressed & A_BUTTON) {
                
        switch (world.getGameState()) {

            case GameState::Inventory_Open:     

                switch (menu.getY()) {

                    case 0:
                        world.setGameState(GameState::Inventory_Open_More_Reset);
                        break;

                    case 1:
                        playGame_HandleMenu(GameState::Inventory_Open);
                        break;
                        
                    default:

                        switch (player.getDirection()) {

                            case Direction::Right:

                                playGame_HandleMenu_LR(player, Direction::Right, Stance::Man_Start);
                                break;

                            case Direction::Left:

                                playGame_HandleMenu_LR(player, Direction::Left, Constants::Player_Stance_Offset);
                                break;

                        }

                        break;

                }

                break;

            #ifndef DEBUG

            case GameState::Inventory_Open_More_Reset:     
                world.setGameState(GameState::Inventory_Open_Reset_0);
                break;

            case GameState::Inventory_Open_More_Exit:     
                world.setGameState(GameState::Inventory_Open_Exit_0);
                break;

            case GameState::Inventory_Open_Exit_0:
                world.setGameState(GameState::Inventory_Open);
                break;

            case GameState::Inventory_Open_Exit_1:
                world.setGameState(GameState::Title_Init);
                break;

            case GameState::Inventory_Open_Reset_0:
                world.setGameState(GameState::Inventory_Open);
                break;

            case GameState::Inventory_Open_Reset_1:
                FX::loadGameState((uint8_t*)&cookie, sizeof(cookie));
                break;

            case GameState::Inventory_Open_Reset_Exit_0:
                world.setGameState(GameState::Inventory_Open);
                break;

            case GameState::Inventory_Open_Reset_Exit_1:
                world.setGameState(GameState::Title_Init);
                break;

            #endif

            default: break;

        }

    }
    else if (justPressed & UP_BUTTON) {
        
        switch (world.getGameState()) {

            case GameState::Inventory_Open:
                        
                if (menu.getTop() == 0) {

                    menu.decY();

                }
                else  if (menu.getTop() >= 2) {

                    if (menu.getY() - 1 == player.getItemCount()) {

                        menu.decY();

                    }
                    else {

                        menu.setTop(menu.getTop() - 1);
                        menu.decY();

                        if (menu.getY() == 2) {
                            menu.setTop(0);
                        }

                    }

                }

                break;

            case GameState::Inventory_Open_Exit_1:
            case GameState::Inventory_Open_Reset_1:
            case GameState::Inventory_Open_Reset_Exit_1:
            case GameState::Inventory_Open_More_Exit:  

                world.decGameState();
                break;

        }

    }
    else if (justPressed & DOWN_BUTTON) {

        switch (world.getGameState()) {

            case GameState::Inventory_Open:
                
                // Bottom item is already selected and cannot move ..
                if (menu.getY() == player.getItemCount() + 1) { }

                // Showing top 2 items and top row is selected, move down ..
                else if (menu.getTop() == 0 && menu.getY() == 0 && menu.getY() < player.getItemCount() + 2) {
                    menu.incY();
                }

                // Showing all 2 items ..
                else if (menu.getTop() == 0 && menu.getY() < player.getItemCount() - 1 && player.getItemCount() == 2) {
                    menu.incY();
                }

                // Showing top 2 items and top row is selected, move down ..
                else if (menu.getY() == 0) {
                    menu.incY();
                }
                // Showing top 2 items and top row is selected, move down ..
                else if (menu.getY() == 1 && player.getItemCount() > 1) {
                    menu.incY();
                }

                // Showing bottom 3 items and bottom 
                else if (menu.getTop() == player.getItemCount() - 1) {
                    menu.incY();
                }

                // Otherwise scroll top and selected down ..
                else {

                    if (menu.getY() == 2) {

                        menu.setY(3);

                        if (player.getItemCount() > 2) {
                            menu.setTop(2);
                        }
                        else {
                            menu.setTop(0);
                        }

                    }
                    else {

                        menu.setTop(menu.getTop() + 1);
                        menu.incY();
                        
                    }

                }

                break;

            case GameState::Inventory_Open_Exit_0:
            case GameState::Inventory_Open_Reset_0:
            case GameState::Inventory_Open_Reset_Exit_0:
            case GameState::Inventory_Open_More_Reset:  
                // world.setGameState(static_cast<GameState>(static_cast<uint8_t>(world.getGameState()) + 1));
                world.incGameState();
                break;

        }

    }

    #endif
    
}


void playGame_HandleMenu_LR(Player &player, Direction direction, Stance stanceOffset) {

    #ifndef DEBUG_HANDLE_MENUS

    uint8_t tile = world.getTile_RelativeToPlayer(direction == Direction::Left ? -1 : 1, 0);
    uint8_t tile_1D = world.getTile_RelativeToPlayer(direction == Direction::Left ? -1 : 1, -2);
    uint8_t tile_3D = world.getTile_RelativeToPlayer(direction == Direction::Left ? -3 : 3, -2);

    ItemType selectedItem = ItemType::None;

    if (menu.getY() >= 2) {
        selectedItem = player.getItem(menu.getY() - 2).getItemType();
    }

    #ifndef DEBUG

        if (world.isWaterTile(tile_1D) && world.isWaterTile(tile_3D) && 
            (selectedItem == ItemType::LifeSaver || selectedItem == ItemType::LifeSaver_Dissolve)) {

            ItemType hiddenType = (selectedItem == ItemType::LifeSaver) ? ItemType::LifeSaver_Hidden : ItemType::LifeSaver_Dissolve_Hidden;
            ItemType inWaterType = (direction == Direction::Right) 
                ? (selectedItem == ItemType::LifeSaver ? ItemType::LifeSaver_InWater_RH : ItemType::LifeSaver_Dissolve_InWater_RH)
                : (selectedItem == ItemType::LifeSaver ? ItemType::LifeSaver_InWater_LH : ItemType::LifeSaver_Dissolve_InWater_LH);

            uint8_t itemIdx = world.getItem(hiddenType);
            Item &item = world.getItem(itemIdx);
            item.setItemType(inWaterType);
            item.setFrame(0);
            item.setCounter(0);
            item.setX(-world.getMiddleground() + (direction == Direction::Left ? static_cast<uint16_t>(30) : static_cast<uint16_t>(70)));
            item.setY(40 - player.getY());   
            
            removeInventoryItem(GameState::Play_Game);

        }    
        else if (world.isWoodenBarrier(tile) && selectedItem == ItemType::Hammer) {
            
    #else

        if (world.isWoodenBarrier(tile) && selectedItem == ItemType::Hammer) {

    #endif


        player.pushSequence(Stance::Man_Hammering_RH_00 + stanceOffset, Stance::Man_Hammering_RH_10 + stanceOffset);
        removeWorldandInventoryItem(ItemType::WoodenBarrier, GameState::Play_Game);

    }

    else if (world.isMysteryCrate(tile) && selectedItem == ItemType::PinchBar) {

        player.pushSequence(Stance::Man_Levering_RH_00 + stanceOffset, Stance::Man_Levering_RH_10 + stanceOffset);
        removeWorldandInventoryItem(ItemType::MysteryCrate, GameState::Play_Game);

    }

    else if (selectedItem == ItemType::Amulet) {

        player.setBuzzCount(Constants::Buzz_Time);
        removeInventoryItem(GameState::Play_Game);

    }

    #ifndef DEBUG_LOCKED_DOOR

        else if (world.isLockedDoor(tile) && selectedItem == ItemType::Key1) {

            removeWorldandInventoryItem(ItemType::LockedDoor, GameState::Play_Game);

        }
    #endif

    else if (selectedItem == ItemType::Sword) {

        uint8_t enemySwordIdx = world.getClosestEnemy(EnemyType::SwordFighter);
        player.setEnemyIdx(enemySwordIdx);

        if (enemySwordIdx != 255) {

            Enemy &enemy = world.getEnemy(enemySwordIdx);

            player.push(Stance::Man_Sword_Stationary_RH + stanceOffset);
            menu.setDirection(direction);
            menu.setGameState(GameState::Play_Battle);
            removeInventoryItem(GameState::Play_Battle);

        }

    }

    
    else if (selectedItem == ItemType::Potion) {
    
        player.incHealth(5);
        removeInventoryItem(GameState::Play_Game);
        launchPuff(player);

    }

    #endif

}

void playGame_HandleMenu_OpenClose() {

    #ifndef DEBUG_HANDLE_MENUS

    switch (menu.getDirection()) {

        case Direction::Left:

            if (menu.getX() > 128 - 32) {
                menu.decX();
            }
            else {
                menu.setDirection(Direction::None);
            }

            break;


        case Direction::Right:

            if (menu.getX() < 128) {
                menu.incX();
            }
            else {
                menu.setDirection(Direction::None);
                world.setGameState(menu.getGameState());
            }

            break;

        default:
            break;

    }

    #endif

}


void playGame_HandleMenu(GameState gameState) {

    #ifndef DEBUG_HANDLE_MENUS

    if (menu.getX() == 128) {

        menu.setGameState(world.getGameState());
        menu.setDirection(Direction::Left);
        world.setGameState(gameState);
        menu.setX(126);//SJH

    }
    else if (menu.getX() == 128 - 32) {

        world.setGameState(gameState);
        menu.setDirection(Direction::Right);
        menu.setGameState(GameState::Play_Game);

    }

    #endif
    
}