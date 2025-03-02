#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"



// Function to determine player's death animation based on distance and direction
void playGame_applyDeathAnimation(Player& player, int16_t dist) {

    bool fallsForward = (dist <= 0);

    switch (player.getDirection()) {

        case Direction::Left:

            player.pushSequence(
                fallsForward ? Stance::Man_Die_FWD_LH_01 : Stance::Man_Die_BWD_LH_01,
                fallsForward ? Stance::Man_Die_FWD_LH_04 : Stance::Man_Die_BWD_LH_04
            );

            break;

        case Direction::Right:

            player.pushSequence(
                fallsForward ? Stance::Man_Die_BWD_RH_01 : Stance::Man_Die_FWD_RH_01,
                fallsForward ? Stance::Man_Die_BWD_RH_04 : Stance::Man_Die_FWD_RH_04
            );

            break;

        default:
            break;

    }
}

void playGame_SetGlint(Enemy &enemy) {

    if (enemy.getItem().getItemType() == ItemType::Glint_Hidden) {

        Item &glint = enemy.getItem();

        glint.setItemType(ItemType::Glint);
        glint.setX(enemy.getX() - 9);
        glint.setY(enemy.getY() + 1);
        glint.setFrame(0);

    }

}

void playGame_HandleEnemies_LaunchArrow(Enemy &enemy, Direction direction) {

    if (world.getGameState() == GameState::Play_Dead) return;

    Item &item = enemy.getItem();
    item.setItemType(direction == Direction::Left ? ItemType::Arrow_LH : ItemType::Arrow_RH);
    item.setCounter(item.getData() * 4);
    item.setX(enemy.getX());
    item.setY(enemy.getY() - 7);

}

void playGame_HandleEnemies_Trebochet_SetFrame(uint8_t idx, ItemType itemType) {

    uint8_t frame = FX::readIndexedUInt8(Constants::TrebochetImgs, idx);

    idx = world.getItem(itemType);
    Item &item = world.getItem(idx);
    item.setFrame(frame);

}

void launchTrebochetBall(Enemy &enemy, ItemType itemType) {

    Item &item = enemy.getItem();
    uint8_t r = a.randomLFSR(static_cast<uint8_t>(0), static_cast<uint8_t>(3));
    item.setItemType(static_cast<ItemType>(static_cast<uint8_t>(itemType) + r));
    item.setCounter(20);
    item.setData(120);
    item.setY(enemy.getY() + 8);

    if (itemType == ItemType::Trebochet_Ball_Left_1) {

        item.setX(enemy.getX() - 16);

    }
    else {

        item.setX(enemy.getX() + 28);

    }

}

void playGame_HandleEnemies(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    Player &player = world.getPlayer();

    for (uint8_t i = 0; i < Constants::EnemyCount; i++) {

        Enemy &enemy = world.getEnemy(i);

        if (enemy.getX() == 0) continue;

        if (!enemy.isEmpty()) {

            Point offset;
            uint16_t stance = enemy.pop();

            enemy.setStance(stance);

            StanceDetails stanceDetails;

            FX::seekData(Constants::StanceDetails + (static_cast<uint16_t>(stance) * 4));
            FX::readObject(stanceDetails);
            FX::readEnd();

            enemy.setY(enemy.getY() - stanceDetails.stanceY);
            enemy.setX(enemy.getX() + stanceDetails.middleground);

            switch (enemy.getEnemyType()) {

                case EnemyType::Archer:
                    {    
                        
                        switch (stance) {

                            case Stance::Enemy_Fire_LH_07:
                            case Stance::Enemy_Fire_RH_07:

                                playGame_HandleEnemies_LaunchArrow(enemy, stance == Stance::Enemy_Fire_LH_07 ? Direction::Left : Direction::Right);
                                break;

                        }

                    }

                    break;

                case EnemyType::TrebochetOperator:

                    switch (stance) {
                                
                        case Stance::Enemy_Trebochet_Release_LH_01 ... Stance::Enemy_Trebochet_Release_LH_14:
                            {
                                uint8_t idx = static_cast<uint8_t>(stance) - static_cast<uint8_t>(Stance::Enemy_Trebochet_Release_LH_01);
                                playGame_HandleEnemies_Trebochet_SetFrame(idx, ItemType::Trebochet_Left); 
                                
                                if (stance == Stance::Enemy_Trebochet_Release_LH_05) {
                                    launchTrebochetBall(enemy, ItemType::Trebochet_Ball_Left_1);
                                }

                            }
                            break;

                        case Stance::Enemy_Trebochet_Release_RH_01 ... Stance::Enemy_Trebochet_Release_RH_14:
                            {
                                uint8_t idx = static_cast<uint8_t>(stance) - static_cast<uint8_t>(Stance::Enemy_Trebochet_Release_RH_01);
                                playGame_HandleEnemies_Trebochet_SetFrame(idx, ItemType::Trebochet_Right);
                                
                                if (stance == Stance::Enemy_Trebochet_Release_RH_05) {
                                    launchTrebochetBall(enemy, ItemType::Trebochet_Ball_Right_1);
                                }

                            }
                            break;
                    }
                    
                    break;
                
                case EnemyType::SwordFighter:

                    switch (stance) {
                                
                        case Stance::Enemy_Sword_Lunge_LH_03:
                        case Stance::Enemy_Sword_Lunge_RH_03:
                            {
                                if (player.getWound() == 0 && playGame_EnemyStabsPlayer(player)) {

                                    player.setWound(12);

                                    uint8_t health = 0;

                                    switch (player.getStance()) {

                                        case Stance::Man_Sword_Start_RH ... Stance::Man_Sword_End_RH:
                                        case Stance::Man_Sword_Start_LH ... Stance::Man_Sword_End_LH:

                                            health = a.randomLFSR(1, 4);
                                            break;

                                        default:

                                            health = a.randomLFSR(3, 7);
                                            break;

                                    }

                                    if (player.decHealth(health)) {

                                        int16_t dist = getDistanceBetween(enemy);
                                        player.clear();


                                        // Enemy puts away sword ..

                                        enemy.insert(enemy.getDirection() == Direction::Left 
                                                    ? Stance::Enemy_Walk_LH_00 
                                                    : Stance::Enemy_Walk_RH_00);


                                        // Determine player's death animation

                                        playGame_applyDeathAnimation(player, dist);
                                          

                                    }

                                }

                            }

                            break;

                    }

                    break;

            }

            FX::seekData(Constants::SubsititueStance + (static_cast<uint16_t>(stance) * 2));
            uint16_t subsituteStance = FX::readPendingUInt16();
            FX::readEnd();

            if (subsituteStance != 65535) {
                enemy.setStance(subsituteStance);
            }


        }
        else {


            // Exit if player is dead ..

            if (player.getHealth() == 0)    break;
            if (enemy.getHealth() == 0)     continue;

            #ifdef DEBUG_ENEMY_SWORD
            DEBUG_PRINT("X ");
            DEBUG_PRINT(enemy.getX());
            DEBUG_PRINT(" ");
            DEBUG_PRINT(enemy.getX() - 56);
            DEBUG_PRINT(" ");
            DEBUG_PRINT(world.getMiddleground());
            DEBUG_PRINT(", Y ");
            DEBUG_PRINT(enemy.getY());
            DEBUG_PRINT(", Tiles ");
            #endif

            uint8_t tile_L = world.getTile_FromCoords(enemy.getX()  - 8, enemy.getY());
            uint8_t tile_R = world.getTile_FromCoords(enemy.getX()  + 16, enemy.getY());

            #ifdef DEBUG_ENEMY_SWORD
            DEBUG_PRINT(tile_L);
            DEBUG_PRINT(" ");
            DEBUG_PRINT(tile_R);
            DEBUG_PRINT(" - ");
            #endif

            switch (enemy.getEnemyType()) {

                case EnemyType::Archer:
                    {
                        uint16_t playerX = 64 - world.getMiddleground();

                        if (playerX > enemy.getX() && enemy.getStance() == Stance::Enemy_Fire_LH_12) {

                            enemy.setStance(Stance::Enemy_Fire_RH_12);
                        }
                        else if (playerX < enemy.getX() && enemy.getStance() == Stance::Enemy_Fire_RH_12) {

                            enemy.setStance(Stance::Enemy_Fire_LH_12);
                        }
                    
                    }

                    break;

                case EnemyType::SwordFighter:
                    {
                      
                        int16_t dist = getDistanceBetween(enemy);
                        bool isLeft = (enemy.getDirection() == Direction::Left);

                        #ifdef DEBUG_ENEMY_SWORD
                        if (isLeft) { DEBUG_PRINT(" Left "); } 
                        else        { DEBUG_PRINT(" Righ "); }
                        #endif

                        if (isLeft) {

                            if (tile_L == Tiles::Blank && 
                               ((dist >= -enemy.getItem().getData() && dist <= -38) || 
                                (dist >= -37 && dist <= -28 && a.randomLFSR(0, 5) == 0))) {

                                #ifdef DEBUG_ENEMY_SWORD
                                DEBUG_PRINT("LB");
                                #endif

                                enemy.pushSequence(Stance::Enemy_Sword_Walk_LH_01, Stance::Enemy_Sword_Walk_LH_02);

                            }
                            else if (dist >= -27 && dist <= -24) {

                                switch (player.getStance()) {

                                    case Stance::Man_Sword_Lunge_RH_01 ... Stance::Man_Sword_Lunge_RH_03:

                                        if (a.randomLFSR(0, 5) == 0) {

                                            #ifdef DEBUG_ENEMY_SWORD
                                            DEBUG_PRINT("LC1");
                                            #endif

                                            enemy.pushSequence(Stance::Enemy_Sword_Lunge_LH_05, Stance::Enemy_Sword_Lunge_LH_06);
                                            player.pushSequence(Stance::Man_Sword_Lunge_RH_05, Stance::Man_Sword_Lunge_RH_06, true);
                                            playGame_SetGlint(enemy);

                                        }
                                        else {
                                        
                                            if (tile_L == Tiles::Blank && tile_R == Tiles::Blank && a.randomLFSR(0, 16) == 0) {

                                                #ifdef DEBUG_ENEMY_SWORD
                                                DEBUG_PRINT("LC2");
                                                #endif

                                                enemy.pushSequence(Stance::Enemy_Sword_Walk_BK_LH_01, Stance::Enemy_Sword_Walk_BK_LH_02);
                                                enemy.pushSequence(Stance::Enemy_Sword_Lunge_LH_01, Stance::Enemy_Sword_Lunge_LH_06);
                                                enemy.pushSequence(Stance::Enemy_Sword_Walk_LH_01, Stance::Enemy_Sword_Walk_LH_02);
                                                
                                            }

                                        }

                                        break;

                                    case Stance::Man_Sword_Lunge_RH_04 ... Stance::Man_Sword_Lunge_RH_06:
                                    
                                        if (tile_L == Tiles::Blank && tile_R == Tiles::Blank && a.randomLFSR(0, 16) == 0) {

                                            #ifdef DEBUG_ENEMY_SWORD
                                            DEBUG_PRINT("LD");
                                            #endif

                                            enemy.pushSequence(Stance::Enemy_Sword_Walk_BK_LH_01, Stance::Enemy_Sword_Walk_BK_LH_02);
                                            enemy.pushSequence(Stance::Enemy_Sword_Lunge_LH_01, Stance::Enemy_Sword_Lunge_LH_06);
                                            enemy.pushSequence(Stance::Enemy_Sword_Walk_LH_01, Stance::Enemy_Sword_Walk_LH_02);

                                        }

                                        break;

                                    default:

                                        if (tile_L == Tiles::Blank && tile_R == Tiles::Blank && a.randomLFSR(0, 24) == 0) {

                                            #ifdef DEBUG_ENEMY_SWORD
                                            DEBUG_PRINT("LE");
                                            #endif

                                            if (a.randomLFSR(0, 4) == 0) {
                                                enemy.pushSequence(Stance::Enemy_Sword_Walk_BK_LH_01, Stance::Enemy_Sword_Walk_BK_LH_02);
                                            }

                                            enemy.pushSequence(Stance::Enemy_Sword_Walk_BK_LH_01, Stance::Enemy_Sword_Walk_BK_LH_02);
                                            enemy.pushSequence(Stance::Enemy_Sword_Lunge_LH_01, Stance::Enemy_Sword_Lunge_LH_06);
                                            enemy.pushSequence(Stance::Enemy_Sword_Walk_LH_01, Stance::Enemy_Sword_Walk_LH_02);

                                        }

                                        break;

                                }

                            }
                            else if (dist >= -23 && dist <= -4) {

                                if (tile_R == Tiles::Blank && a.randomLFSR(0, 5) == 0) {

                                    #ifdef DEBUG_ENEMY_SWORD
                                    DEBUG_PRINT("LF");
                                    #endif

                                    enemy.pushSequence(Stance::Enemy_Sword_Walk_BK_LH_01, Stance::Enemy_Sword_Walk_BK_LH_02);

                                }
                                else if (tile_L == Tiles::Blank && a.randomLFSR(0, 12) == 0) {

                                    #ifdef DEBUG_ENEMY_SWORD
                                    DEBUG_PRINT("LG");
                                    #endif

                                    enemy.pushSequence(Stance::Enemy_Sword_Walk_BK_LH_01, Stance::Enemy_Sword_Walk_BK_LH_02);
                                    enemy.pushSequence(Stance::Enemy_Sword_Lunge_LH_01, Stance::Enemy_Sword_Lunge_LH_06);
                                    enemy.pushSequence(Stance::Enemy_Sword_Walk_LH_01, Stance::Enemy_Sword_Walk_LH_02);

                                }

                            }
                            else if (dist >= -3 && dist <= 999) {

                                #ifdef DEBUG_ENEMY_SWORD
                                DEBUG_PRINT("LH");
                                #endif

                                enemy.push(Stance::Enemy_Sword_Stationary_RH);

                            }
                            else {

                                #ifdef DEBUG_ENEMY_SWORD
                                DEBUG_PRINT("LI");
                                #endif

                            }

                            #ifdef DEBUG_ENEMY_SWORD
                            DEBUG_PRINTLN("");
                            #endif

                        }
                        else {

                            if (tile_R == Tiles::Blank &&
                               ((dist >= 34 && dist <= enemy.getItem().getData()) ||    
                                (dist >= 20 && dist <= 33 && a.randomLFSR(0, 5) == 0))) {    

                                #ifdef DEBUG_ENEMY_SWORD
                                DEBUG_PRINT("RB");
                                #endif                                           

                                enemy.pushSequence(Stance::Enemy_Sword_Walk_RH_01, Stance::Enemy_Sword_Walk_RH_02);

                            }
                            else if (dist >= -5 && dist <= 19) {  

                                switch (player.getStance()) {

                                    case Stance::Man_Sword_Lunge_LH_01 ... Stance::Man_Sword_Lunge_LH_03:

                                        if (a.randomLFSR(0, 5) == 0) {

                                            #ifdef DEBUG_ENEMY_SWORD
                                            DEBUG_PRINT("RC1");
                                            #endif                                           

                                            enemy.pushSequence(Stance::Enemy_Sword_Lunge_RH_05, Stance::Enemy_Sword_Lunge_RH_06);
                                            player.pushSequence(Stance::Man_Sword_Lunge_LH_05, Stance::Man_Sword_Lunge_LH_06, true);
                                            playGame_SetGlint(enemy);

                                        }
                                        else {
                                        
                                            if (tile_L == Tiles::Blank && a.randomLFSR(0, 16) == 0) {

                                                #ifdef DEBUG_ENEMY_SWORD
                                                DEBUG_PRINT("RC2");
                                                #endif                                           

                                                enemy.pushSequence(Stance::Enemy_Sword_Walk_BK_RH_01, Stance::Enemy_Sword_Walk_BK_RH_02);
                                                enemy.pushSequence(Stance::Enemy_Sword_Lunge_RH_01, Stance::Enemy_Sword_Lunge_RH_06);
                                                enemy.pushSequence(Stance::Enemy_Sword_Walk_RH_01, Stance::Enemy_Sword_Walk_RH_02);
                                                
                                            }

                                        }

                                        break;

                                    case Stance::Man_Sword_Lunge_LH_04 ... Stance::Man_Sword_Lunge_LH_06:
                                    
                                        if (tile_L == Tiles::Blank && a.randomLFSR(0, 16) == 0) {

                                            #ifdef DEBUG_ENEMY_SWORD
                                            DEBUG_PRINT("RD");
                                            #endif                                              

                                            enemy.pushSequence(Stance::Enemy_Sword_Walk_BK_RH_01, Stance::Enemy_Sword_Walk_BK_RH_02);
                                            enemy.pushSequence(Stance::Enemy_Sword_Lunge_RH_01, Stance::Enemy_Sword_Lunge_RH_06);
                                            enemy.pushSequence(Stance::Enemy_Sword_Walk_RH_01, Stance::Enemy_Sword_Walk_RH_02);

                                        }

                                        break;

                                    default:

                                        if (tile_L == Tiles::Blank && tile_R == Tiles::Blank && a.randomLFSR(0, 24) == 0) {

                                            #ifdef DEBUG_ENEMY_SWORD
                                            DEBUG_PRINT("RE");
                                            #endif                                              

                                            if (a.randomLFSR(0, 4) == 0) {
                                                enemy.pushSequence(Stance::Enemy_Sword_Walk_BK_RH_01, Stance::Enemy_Sword_Walk_BK_RH_02);
                                            }

                                            enemy.pushSequence(Stance::Enemy_Sword_Walk_BK_RH_01, Stance::Enemy_Sword_Walk_BK_RH_02);
                                            enemy.pushSequence(Stance::Enemy_Sword_Lunge_RH_01, Stance::Enemy_Sword_Lunge_RH_06);
                                            enemy.pushSequence(Stance::Enemy_Sword_Walk_RH_01, Stance::Enemy_Sword_Walk_RH_02);

                                        }

                                        break;

                                }

                            }
                            else if (dist >= -12 && dist <= -6) {  

                                if (tile_R == Tiles::Blank && a.randomLFSR(0, 5) == 0) {

                                    #ifdef DEBUG_ENEMY_SWORD
                                    DEBUG_PRINT("RF");
                                    #endif                                              

                                    enemy.pushSequence(Stance::Enemy_Sword_Walk_BK_RH_01, Stance::Enemy_Sword_Walk_BK_RH_02);

                                }
                                else  if (tile_L == Tiles::Blank && a.randomLFSR(0, 12) == 0) {

                                    #ifdef DEBUG_ENEMY_SWORD
                                    DEBUG_PRINT("RG");
                                    #endif                                              

                                    enemy.pushSequence(Stance::Enemy_Sword_Walk_BK_RH_01, Stance::Enemy_Sword_Walk_BK_RH_02);
                                    enemy.pushSequence(Stance::Enemy_Sword_Lunge_RH_01, Stance::Enemy_Sword_Lunge_RH_06);
                                    enemy.pushSequence(Stance::Enemy_Sword_Walk_RH_01, Stance::Enemy_Sword_Walk_RH_02);

                                }

                            }
                            else if (dist >= -999 && dist <= -13) {  

                                #ifdef DEBUG_ENEMY_SWORD
                                DEBUG_PRINT("RH");
                                #endif 

                                enemy.push(Stance::Enemy_Sword_Stationary_LH);

                            }
                            else {

                                #ifdef DEBUG_ENEMY_SWORD
                                DEBUG_PRINT("RI");
                                #endif 

                            }

                            #ifdef DEBUG_ENEMY_SWORD
                            DEBUG_PRINTLN("");
                            #endif 
                            
                        }

                    }

                    break;

                case EnemyType::Guard_RH:
                case EnemyType::Guard_LH:

                    if (world.getFrameCount() % 48 == 0) {

                        EnemyType enemyType = enemy.getEnemyType();
                        enemy.setStance(enemy.getStance() == (enemyType == EnemyType::Guard_RH ? Stance::Enemy_Guard_RH_01 : Stance::Enemy_Guard_LH_01) 
                                        ? (enemyType == EnemyType::Guard_RH ? Stance::Enemy_Guard_RH_02 : Stance::Enemy_Guard_LH_02) 
                                        : (enemyType == EnemyType::Guard_RH ? Stance::Enemy_Guard_RH_01 : Stance::Enemy_Guard_LH_01)
                        );

                    }

                    break;

                default:
                    break;

            }

        }

    }

}


bool playGame_EnemyStabsPlayer(Player &player) {

    if (player.getEnemyIdx() == Constants::NoEnemy) {

        uint8_t enemyIdx = world.getClosestEnemy(EnemyType::SwordFighter);
        player.setEnemyIdx(enemyIdx);

        if (enemyIdx = Constants::NoEnemy) return false;

    }

    Enemy &enemy = world.getEnemy(player.getEnemyIdx());
    Stance stance = enemy.getStance();
    Rect playerRect = { 61, - Constants::GroundY + player.getY(), 6, 16 };

    Point enemyPoint;
    enemyPoint = { enemy.getX() + world.getMiddleground() + (stance == Stance::Enemy_Sword_Lunge_LH_03 ? -10 : 17), - enemy.getY() + 12 };

    #ifdef DEBUG_SWORD
        playerX = playerRect.x;
        playerY = playerRect.y;
        enemyX = enemyPoint.x;
        enemyY = enemyPoint.y;
    #endif

    if (player.getBuzzCount() > 0) {

        player.setBuzzCount(0);
        return false;

    }
    
    return collide(enemyPoint, playerRect);

}


bool playGame_PlayerStabsEnemy(Player &player) {

    Enemy &enemy = world.getEnemy(player.getEnemyIdx());
    Rect enemyRect = { enemy.getX() + world.getMiddleground(), - enemy.getY(), 6, 16 };

    if (enemy.getDirection() == Direction::Right) {

        enemyRect.x = enemyRect.x + 2;

    }

    Point playerPoint = { 61 + (player.getStance() == Stance::Man_Sword_Lunge_RH_03 ? 15 : -10), - Constants::GroundY + player.getY() + 12 };
    return collide(playerPoint, enemyRect);

 }


int16_t getDistanceBetween(Enemy &enemy) {

    return -world.getMiddleground() + 56 - enemy.getX();

}


int16_t getDistanceBetween(Player &player, EnemyType enemyType) {

    if (player.getEnemyIdx() == Constants::NoEnemy) {

        uint8_t enemyIdx = world.getClosestEnemy(enemyType);
        player.setEnemyIdx(enemyIdx);

    }

    if (player.getEnemyIdx() != Constants::NoEnemy) {
    
        Enemy &enemy = world.getEnemy(player.getEnemyIdx());
        return -world.getMiddleground() + 56 - enemy.getX();

    }
    else {

        return 9999;

    }

}