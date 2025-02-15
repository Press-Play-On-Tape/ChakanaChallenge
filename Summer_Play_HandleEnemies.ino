#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"

void playGame_HandleEnemies_LaunchArrow(Enemy &enemy, Direction direction) {

    if (world.getGameState() == GameState::Play_Dead) return;

    Item &item = enemy.getItem();
    item.setItemType(direction == Direction::Left ? ItemType::Arrow_LH : ItemType::Arrow_RH);
    item.setCounter(25 * 4);
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


void playGame_HandleEnemies_SwordFighter(Player &player, Enemy &enemy, Stance stanceOffset, Stance stanceOffset2, int16_t dist) {

    #ifndef DEBUG

    switch (dist) {
        
        // - Enemy to right of player -----------------------------------------------------------------------

        case 34 ... 8000:
            enemy.pushSequence(Stance::Enemy_Sword_Walk_RH_01 + stanceOffset2, Stance::Enemy_Sword_Walk_RH_02 + stanceOffset2);
            break;
        
        case 20 ... 33:

            if (a.randomLFSR(0, 5) == 0) {
                enemy.pushSequence(Stance::Enemy_Sword_Walk_RH_01 + stanceOffset2, Stance::Enemy_Sword_Walk_RH_02 + stanceOffset2);
            }

            break;

        case -5 ... 19:

            switch (player.getStance()) {

                case Stance::Man_Sword_Lunge_RH_01 ... Stance::Man_Sword_Lunge_RH_03:
                case Stance::Man_Sword_Lunge_LH_01 ... Stance::Man_Sword_Lunge_LH_03:

                    if (a.randomLFSR(0, 5) == 0) {

                        enemy.pushSequence(Stance::Enemy_Sword_Lunge_RH_05 + stanceOffset2, Stance::Enemy_Sword_Lunge_RH_06 + stanceOffset2);
                        player.pushSequence(Stance::Man_Sword_Lunge_RH_05 + stanceOffset, Stance::Man_Sword_Lunge_RH_06 + stanceOffset, true);

                        if (enemy.getItem().getItemType() == ItemType::Glint_Hidden) {

                            Item &glint = enemy.getItem();

                            glint.setItemType(ItemType::Glint);
                            glint.setX(enemy.getX() - 9);
                            glint.setY(enemy.getY() + 1);
                            glint.setFrame(0);
                        }

                    }
                    else {
                    
                        if (a.randomLFSR(0, 16) == 0) {

                            enemy.pushSequence(Stance::Enemy_Sword_Walk_BK_RH_01 + stanceOffset2, Stance::Enemy_Sword_Walk_BK_RH_02 + stanceOffset2);
                            enemy.pushSequence(Stance::Enemy_Sword_Lunge_RH_01 + stanceOffset2, Stance::Enemy_Sword_Lunge_RH_06 + stanceOffset2);
                            enemy.pushSequence(Stance::Enemy_Sword_Walk_RH_01 + stanceOffset2, Stance::Enemy_Sword_Walk_RH_02 + stanceOffset2);
                            // enemy_PushSeqWalkLungeWalk(enemy, stanceOffset2);


                        }

                    }

                    break;

                case Stance::Man_Sword_Lunge_RH_04 ... Stance::Man_Sword_Lunge_RH_06:
                case Stance::Man_Sword_Lunge_LH_04 ... Stance::Man_Sword_Lunge_LH_06:
                
                    if (a.randomLFSR(0, 16) == 0) {

                        enemy.pushSequence(Stance::Enemy_Sword_Walk_BK_RH_01 + stanceOffset2, Stance::Enemy_Sword_Walk_BK_RH_02 + stanceOffset2);
                        enemy.pushSequence(Stance::Enemy_Sword_Lunge_RH_01 + stanceOffset2, Stance::Enemy_Sword_Lunge_RH_06 + stanceOffset2);
                        enemy.pushSequence(Stance::Enemy_Sword_Walk_RH_01 + stanceOffset2, Stance::Enemy_Sword_Walk_RH_02 + stanceOffset2);
                        // enemy_PushSeqWalkLungeWalk(enemy, stanceOffset2);

                    }

                    break;

                default:

                    if (a.randomLFSR(0, 24) == 0) {

                        if (a.randomLFSR(0, 8) == 0) {
                            enemy.pushSequence(Stance::Enemy_Sword_Walk_BK_RH_01 + stanceOffset2, Stance::Enemy_Sword_Walk_BK_RH_02 + stanceOffset2);
                        }

                        enemy.pushSequence(Stance::Enemy_Sword_Walk_BK_RH_01 + stanceOffset2, Stance::Enemy_Sword_Walk_BK_RH_02 + stanceOffset2);
                        enemy.pushSequence(Stance::Enemy_Sword_Lunge_RH_01 + stanceOffset2, Stance::Enemy_Sword_Lunge_RH_06 + stanceOffset2);
                        enemy.pushSequence(Stance::Enemy_Sword_Walk_RH_01 + stanceOffset2, Stance::Enemy_Sword_Walk_RH_02 + stanceOffset2);
                        // enemy_PushSeqWalkLungeWalk(enemy, stanceOffset2);

                    }

                    break;

            }

            break;

        case -12 ... -17:

            if (a.randomLFSR(0, 5) == 0) {

                enemy.pushSequence(Stance::Enemy_Sword_Walk_BK_RH_01 + stanceOffset2, Stance::Enemy_Sword_Walk_BK_RH_02 + stanceOffset2);

            }
            else  if (a.randomLFSR(0, 12) == 0) {

                enemy.pushSequence(Stance::Enemy_Sword_Walk_BK_RH_01 + stanceOffset2, Stance::Enemy_Sword_Walk_BK_RH_02 + stanceOffset2);
                enemy.pushSequence(Stance::Enemy_Sword_Lunge_RH_01 + stanceOffset2, Stance::Enemy_Sword_Lunge_RH_06 + stanceOffset2);
                enemy.pushSequence(Stance::Enemy_Sword_Walk_RH_01 + stanceOffset2, Stance::Enemy_Sword_Walk_RH_02 + stanceOffset2);
                // enemy_PushSeqWalkLungeWalk(enemy, stanceOffset2);

            }
            break;

        case -999 ... -18:

           enemy.push(Stance::Enemy_Sword_Stationary_LH - stanceOffset2);
            break;

        default:
            break;

    }

    #endif
    
}

// void enemy_PushSeqWalkLungeWalk(Enemy& enemy, Stance stanceOffset2) {

//     enemy.pushSequence(Stance::Enemy_Sword_Walk_BK_RH_01 + stanceOffset2, Stance::Enemy_Sword_Walk_BK_RH_02 + stanceOffset2);
//     enemy.pushSequence(Stance::Enemy_Sword_Lunge_RH_01 + stanceOffset2, Stance::Enemy_Sword_Lunge_RH_06 + stanceOffset2);
//     enemy.pushSequence(Stance::Enemy_Sword_Walk_RH_01 + stanceOffset2, Stance::Enemy_Sword_Walk_RH_02 + stanceOffset2);
    
//}


void playGame_HandleEnemies(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    Player &player = world.getPlayer();

    for (uint8_t i = 0; i < Constants::EnemyCount; i++) {

        Enemy &enemy = world.getEnemy(i);

        if (enemy.getX() == 0) continue;
            
        if (!enemy.isEmpty()) {

            Point offset;
            uint16_t stance = enemy.pop();

            enemy.setStance(stance);

            // FX::seekData(Constants::StanceDetails + (static_cast<uint16_t>(stance) * 4));
            // int8_t stanceY = FX::readPendingUInt8();
            // enemy.setY(enemy.getY() - stanceY);

            // int8_t b = FX::readPendingUInt8();
            // world.incForeground(b);

            // b = FX::readPendingUInt8();
            // enemy.setX(enemy.getX() + stanceDetails.middleground);
            // FX::readEnd();

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

                                    player.decHealth(1);
                                    player.setWound(12);

                                    if (player.getHealth() == 0) {

                                        // int16_t dist = getDistanceBetween(enemy);
                                        // player.clear();

                                        // // Enemy puts away sword ..

                                        // switch (enemy.getDirection()) {

                                        //     case Direction::Left:
                                        //         enemy.insert(Stance::Enemy_Walk_LH_00);
                                        //         break;

                                        //     case Direction::Right:
                                        //         enemy.insert(Stance::Enemy_Walk_RH_00);
                                        //         break;

                                        //     default: break;

                                        // }
                                        int16_t dist = getDistanceBetween(enemy);
                                        player.clear();
                                        Stance stanceSingle = 0;
                                        Stance stanceDouble = 0;

                                        // Enemy puts away sword ..

                                        switch (enemy.getDirection()) {

                                            case Direction::Left:
                                                stanceSingle = Stance::Enemy_Walk_LH_00;
                                                break;

                                            case Direction::Right:
                                                stanceSingle = Stance::Enemy_Walk_RH_00;
                                                break;

                                            default: break;

                                        }

                                        if (stance != 0) {
                                            enemy.insert(stanceSingle);
                                        }


                                        // Player dies but whch direction does he fall?

                                        // switch (dist) {

                                        //     case -999 ... 0:

                                        //         switch (player.getDirection()) {

                                        //             case Direction::Left:
                                        //                 player.pushSequence(Stance::Man_Die_FWD_LH_01, Stance::Man_Die_FWD_LH_04);
                                        //                 break;

                                        //             case Direction::Right:

                                        //                 player.pushSequence(Stance::Man_Die_BWD_RH_01, Stance::Man_Die_BWD_RH_04);
                                        //                 break;

                                        //             default: break;

                                        //         }

                                        //         break;

                                        //     case 1 ... 999:

                                        //         switch (player.getDirection()) {

                                        //             case Direction::Left:

                                        //                 player.pushSequence(Stance::Man_Die_BWD_LH_01, Stance::Man_Die_BWD_LH_04);
                                        //                 break;

                                        //             case Direction::Right:

                                        //                 player.pushSequence(Stance::Man_Die_FWD_RH_01, Stance::Man_Die_FWD_RH_04);
                                        //                 break;

                                        //             default: break;

                                        //         }

                                        //         break;

                                        // }                                                
                                        switch (dist) {

                                            case -999 ... 0:

                                                switch (player.getDirection()) {

                                                    case Direction::Left:

                                                        stanceSingle = Stance::Man_Die_FWD_LH_01;
                                                        stanceDouble = Stance::Man_Die_FWD_LH_04;
                                                        break;

                                                    case Direction::Right:

                                                        stanceSingle = Stance::Man_Die_BWD_RH_01;
                                                        stanceDouble = Stance::Man_Die_BWD_RH_04;
                                                        break;

                                                    default: break;

                                                }

                                                break;

                                            case 1 ... 999:

                                                switch (player.getDirection()) {

                                                    case Direction::Left:

                                                        stanceSingle = Stance::Man_Die_BWD_LH_01;
                                                        stanceDouble = Stance::Man_Die_BWD_LH_04;
                                                        break;

                                                    case Direction::Right:

                                                        stanceSingle = Stance::Man_Die_FWD_RH_01;
                                                        stanceDouble = Stance::Man_Die_FWD_RH_04;
                                                        break;

                                                    default: break;

                                                }

                                                break;

                                        }   

                                        if (stanceDouble != 0) {
                                            
                                            player.pushSequence(stanceSingle, stanceDouble);

                                        }

                                    }

                                }

                            }

                            break;

                    }

                    break;

                // case EnemyType::Guard_RH:

                //     if (world.getFrameCount() % 32 > 16) {

                //         enemy.setStance(enemy.getStance() == Stance::Enemy_Guard_RH_01 ? Stance::Enemy_Guard_RH_02 : Stance::Enemy_Guard_RH_01);

                //     }
                //     break;

                // case EnemyType::Guard_LH:

                //     if (world.getFrameCount() % 32 > 16) {

                //         enemy.setStance(enemy.getStance() == Stance::Enemy_Guard_LH_01 ? Stance::Enemy_Guard_LH_02 : Stance::Enemy_Guard_LH_01);

                //     }
                //     break;


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

            if (player.getHealth() == 0) break;

            switch (enemy.getEnemyType()) {

                // case EnemyType::SwordFighter:
                //     {
                //         int16_t dist = getDistanceBetween(enemy);

                //         switch (enemy.getDirection()) {

                //             case Direction::Left:

                //                 playGame_HandleEnemies_SwordFighter(player, enemy, 0, Stance::Enemy_LH_Start - Stance::Enemy_RH_Start, -dist);
                //                 break;

                //             case Direction::Right:

                //                 playGame_HandleEnemies_SwordFighter(player, enemy, Constants::Player_Stance_Offset, 0, dist);
                //                 break;
                                
                //             default: break;
                        
                //         }

                //     }

                //     break;

                case EnemyType::SwordFighter:
                    {
                        int16_t dist = getDistanceBetween(enemy);
                        bool isLeftOrRight = false;
                        Stance stanceOffset1;
                        Stance stanceOffset2;

                        switch (enemy.getDirection()) {

                            case Direction::Left:
                                isLeftOrRight = true;
                                stanceOffset1 = 0;
                                stanceOffset2 = Constants::Player_Stance_Offset;
                                dist = -dist;
                                // playGame_HandleEnemies_SwordFighter(player, enemy, 0 Stance::Enemy_LH_Start - Stance::Enemy_RH_Start, -dist);
                                break;

                            case Direction::Right:
                                isLeftOrRight = true;
                                stanceOffset1 = Constants::Player_Stance_Offset;
                                stanceOffset2 = 0;
                                // playGame_HandleEnemies_SwordFighter(player, enemy, Constants::Player_Stance_Offset, 0, dist);
                                break;
                                
                            default: break;

                        }

                        if (isLeftOrRight) {

                            playGame_HandleEnemies_SwordFighter(player, enemy, stanceOffset1, stanceOffset2, dist);

                        }

                    }

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


// bool playGame_EnemyStabsPlayer(Player &player) {

//     if (player.getEnemyIdx() == Constants::NoEnemy) {

//         uint8_t enemyIdx = world.getClosestEnemy(EnemyType::SwordFighter);
//         player.setEnemyIdx(enemyIdx);

//         if (enemyIdx = Constants::NoEnemy) return false;

//     }

//     Enemy &enemy = world.getEnemy(player.getEnemyIdx());
//     Stance stance = enemy.getStance();
//     Rect playerRect = { 61, - Constants::GroundY + player.getY(), 6, 16 };

//     if (stance == Stance::Enemy_Sword_Lunge_LH_03) {

//         Point enemyPoint = { enemy.getX() + world.getMiddleground() - 10, - enemy.getY() + 12 };
//         return collide(enemyPoint, playerRect);

//     }

//     if (stance == Stance::Enemy_Sword_Lunge_RH_03) {

//         Point enemyPoint = { enemy.getX() + world.getMiddleground() + 17, - enemy.getY() + 12 };
//         return collide(enemyPoint, playerRect);

//     }

//     return false;

// }

bool playGame_EnemyStabsPlayer(Player &player) {

    if (player.getEnemyIdx() == Constants::NoEnemy) {

        uint8_t enemyIdx = world.getClosestEnemy(EnemyType::SwordFighter);
        player.setEnemyIdx(enemyIdx);

        if (enemyIdx = Constants::NoEnemy) return false;

    }

    Enemy &enemy = world.getEnemy(player.getEnemyIdx());
    Stance stance = enemy.getStance();

    if (!(stance == Stance::Enemy_Sword_Lunge_LH_03) && !(stance == Stance::Enemy_Sword_Lunge_RH_03)) {
        return false;
    }

    Point enemyPoint;
    Rect playerRect = { 61, - Constants::GroundY + player.getY(), 6, 16 };

    if (player.getStance() == Stance::Man_Sword_Lunge_RH_03) {

        enemyPoint = { enemy.getX() + world.getMiddleground() - 10, - enemy.getY() + 12 };

     }

    if (player.getStance() == Stance::Man_Sword_Lunge_LH_03) {

        enemyPoint = { enemy.getX() + world.getMiddleground() - 10, - enemy.getY() + 12 };

    }

    return collide(enemyPoint, playerRect);

 }



// bool playGame_PlayerStabsEnemy(Player &player) {

//     Enemy &enemy = world.getEnemy(player.getEnemyIdx());
//     Rect enemyRect = { enemy.getX() + world.getMiddleground(), - enemy.getY(), 6, 16 };

//     if (enemy.getDirection() == Direction::Right) {

//         enemyRect.x = enemyRect.x + 2;

//     }
    
//     if (player.getStance() == Stance::Man_Sword_Lunge_RH_03) {

//         Point playerPoint = { 61 + 15, - Constants::GroundY + player.getY() + 12 };
//         return collide(playerPoint, enemyRect);

//     }

//     if (player.getStance() == Stance::Man_Sword_Lunge_LH_03) {

//         Point playerPoint = { 61 - 10, - Constants::GroundY + player.getY() + 12 };
//         return collide(playerPoint, enemyRect);        

//     }

//     return false;

// }


bool playGame_PlayerStabsEnemy(Player &player) {

    Enemy &enemy = world.getEnemy(player.getEnemyIdx());
    Rect enemyRect = { enemy.getX() + world.getMiddleground(), - enemy.getY(), 6, 16 };

    if (enemy.getDirection() == Direction::Right) {

        enemyRect.x = enemyRect.x + 2;

    }

    if (!(player.getStance() == Stance::Man_Sword_Lunge_LH_03) && !(player.getStance() == Stance::Man_Sword_Lunge_RH_03)) {
        return false;
    }

    Point playerPoint;

    if (player.getStance() == Stance::Man_Sword_Lunge_RH_03) {

        playerPoint = { 61 + 15, - Constants::GroundY + player.getY() + 12 };

     }

    if (player.getStance() == Stance::Man_Sword_Lunge_LH_03) {

        playerPoint = { 61 - 10, - Constants::GroundY + player.getY() + 12 };

    }

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