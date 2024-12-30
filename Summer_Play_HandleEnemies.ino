#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"

void playGame_HandleEnemies_LaunchArrow(Enemy &enemy, Direction direction) {

    Item &item = enemy.getItem();
    item.setItemType(direction == Direction::Left ? ItemType::Arrow_LH : ItemType::Arrow_RH);
    item.setCounter(25 * 4);
    item.setX(enemy.getX());
    item.setY(enemy.getY() - 7);

}

void playGame_HandleEnemies_Trebochet_SetFrame(uint8_t idx, ItemType itemType) {

    FX::seekData(Constants::TrebochetImgs + idx);
    uint8_t frame = FX::readPendingUInt8();
    FX::readEnd();

    idx = world.getItem(itemType);
    Item &item = world.getItem(idx);
    item.setFrame(frame);

}

void playGame_HandleEnemies_SwordFighter(Player &player, Enemy &enemy, Stance stanceOffset, Stance stanceOffset2, uint16_t dist) {
            
    switch (dist) {
        
        // - Enemy to right of player -----------------------------------------------------------------------

        case 34 ... 8000:

            enemy.pushSequence(Stance::Enemy_Sword_Walk_RH_01 + stanceOffset, Stance::Enemy_Sword_Walk_RH_02 + stanceOffset);
            break;
        
        case 20 ... 33:

            if (a.randomLFSR(0, 5) == 0) {
                enemy.pushSequence(Stance::Enemy_Sword_Walk_RH_01 + stanceOffset, Stance::Enemy_Sword_Walk_RH_02 + stanceOffset);
            }

            break;

        case -5 ... 19:

            switch (player.getStance()) {

                case Stance::Man_Sword_Lunge_RH_01 ... Stance::Man_Sword_Lunge_RH_03:
                case Stance::Man_Sword_Lunge_LH_01 ... Stance::Man_Sword_Lunge_LH_03:

                    if (a.randomLFSR(0, 5) == 0) {

                        enemy.pushSequence(Stance::Enemy_Sword_Lunge_RH_05 + stanceOffset, Stance::Enemy_Sword_Lunge_RH_06 + stanceOffset);
                        player.pushSequence(Stance::Man_Sword_Lunge_LH_05 - stanceOffset2, Stance::Man_Sword_Lunge_LH_06 - stanceOffset2, true);

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

                            enemy.pushSequence(Stance::Enemy_Sword_Walk_BK_RH_01 + stanceOffset, Stance::Enemy_Sword_Walk_BK_RH_02 + stanceOffset);
                            enemy.pushSequence(Stance::Enemy_Sword_Lunge_RH_01 + stanceOffset, Stance::Enemy_Sword_Lunge_RH_06 + stanceOffset);
                            enemy.pushSequence(Stance::Enemy_Sword_Walk_RH_01 + stanceOffset, Stance::Enemy_Sword_Walk_RH_02 + stanceOffset);

                        }

                    }

                    break;

                case Stance::Man_Sword_Lunge_RH_04 ... Stance::Man_Sword_Lunge_RH_06:
                case Stance::Man_Sword_Lunge_LH_04 ... Stance::Man_Sword_Lunge_LH_06:
                
                    if (a.randomLFSR(0, 16) == 0) {

                        enemy.pushSequence(Stance::Enemy_Sword_Walk_BK_RH_01 + stanceOffset, Stance::Enemy_Sword_Walk_BK_RH_02 + stanceOffset);
                        enemy.pushSequence(Stance::Enemy_Sword_Lunge_RH_01 + stanceOffset, Stance::Enemy_Sword_Lunge_RH_06 + stanceOffset);
                        enemy.pushSequence(Stance::Enemy_Sword_Walk_RH_01 + stanceOffset, Stance::Enemy_Sword_Walk_RH_02 + stanceOffset);

                    }

                    break;

                default:

                    if (a.randomLFSR(0, 24) == 0) {

                        if (a.randomLFSR(0, 8) == 0) {
                            enemy.pushSequence(Stance::Enemy_Sword_Walk_BK_RH_01 + stanceOffset, Stance::Enemy_Sword_Walk_BK_RH_02 + stanceOffset);
                        }

                        enemy.pushSequence(Stance::Enemy_Sword_Walk_BK_RH_01 + stanceOffset, Stance::Enemy_Sword_Walk_BK_RH_02 + stanceOffset);
                        enemy.pushSequence(Stance::Enemy_Sword_Lunge_RH_01 + stanceOffset, Stance::Enemy_Sword_Lunge_RH_06 + stanceOffset);
                        enemy.pushSequence(Stance::Enemy_Sword_Walk_RH_01 + stanceOffset, Stance::Enemy_Sword_Walk_RH_02 + stanceOffset);

                    }

                    break;

            }

            break;

        case -12 ... -6:

            if (a.randomLFSR(0, 5) == 0) {

                enemy.pushSequence(Stance::Enemy_Sword_Walk_BK_RH_01 + stanceOffset, Stance::Enemy_Sword_Walk_BK_RH_02 + stanceOffset);

            }
            else  if (a.randomLFSR(0, 12) == 0) {

                enemy.pushSequence(Stance::Enemy_Sword_Walk_BK_RH_01 + stanceOffset, Stance::Enemy_Sword_Walk_BK_RH_02 + stanceOffset);
                enemy.pushSequence(Stance::Enemy_Sword_Lunge_RH_01 + stanceOffset, Stance::Enemy_Sword_Lunge_RH_06 + stanceOffset);
                enemy.pushSequence(Stance::Enemy_Sword_Walk_RH_01 + stanceOffset, Stance::Enemy_Sword_Walk_RH_02 + stanceOffset);

            }
            break;

        case -999 ... -13:

            enemy.push(Stance::Enemy_Sword_Stationary_LH - stanceOffset2);
            break;

        default:
            break;

    }

}


void playGame_HandleEnemies(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    Player &player = world.getPlayer();

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
            enemy.setX(enemy.getX() + b);
            FX::readEnd();

            // FX::seekData(Constants::xBackground + static_cast<uint16_t>(enemy.getStance()));
            // b = FX::readPendingUInt8();
            // world.incBackground(b);
            // FX::readEnd();

            switch (enemy.getEnemyType()) {

                case EnemyType::Archer:
                        
                    switch (newStance) {

                        case Stance::Enemy_Fire_LH_07:

                            playGame_HandleEnemies_LaunchArrow(enemy, Direction::Left);
                            break;

                        case Stance::Enemy_Fire_RH_07:

                            playGame_HandleEnemies_LaunchArrow(enemy, Direction::Right);
                            break;

                    }

                    break;

                case EnemyType::TrebochetOperator:

                    switch (newStance) {
                                
                        case Stance::Enemy_Trebochet_Release_LH_01 ... Stance::Enemy_Trebochet_Release_LH_04:
                        case Stance::Enemy_Trebochet_Release_LH_06 ... Stance::Enemy_Trebochet_Release_LH_14:
                            {
                                uint8_t idx = static_cast<uint8_t>(newStance) - static_cast<uint8_t>(Stance::Enemy_Trebochet_Release_LH_01);
                                playGame_HandleEnemies_Trebochet_SetFrame(idx, ItemType::Trebochet_Left);
                                
                            }
                            break;

                        case Stance::Enemy_Trebochet_Release_LH_05:
                            {
                                uint8_t idx = static_cast<uint8_t>(newStance) - static_cast<uint8_t>(Stance::Enemy_Trebochet_Release_LH_01);
                                playGame_HandleEnemies_Trebochet_SetFrame(idx, ItemType::Trebochet_Left);

                                Item &item = enemy.getItem();
                                uint8_t r = a.randomLFSR(static_cast<uint8_t>(0), static_cast<uint8_t>(3));
                                item.setItemType(static_cast<ItemType>(static_cast<uint8_t>(ItemType::Trebochet_Ball_Left_1) + r));
                                item.setCounter(20);
                                item.setX(enemy.getX() - 16);
                                item.setY(enemy.getY() + 10);

                            }
                            break;

                        case Stance::Enemy_Trebochet_Release_RH_01 ... Stance::Enemy_Trebochet_Release_RH_04:
                        case Stance::Enemy_Trebochet_Release_RH_06 ... Stance::Enemy_Trebochet_Release_RH_14:
                            {
                                uint8_t idx = static_cast<uint8_t>(newStance) - static_cast<uint8_t>(Stance::Enemy_Trebochet_Release_RH_01);
                                playGame_HandleEnemies_Trebochet_SetFrame(idx, ItemType::Trebochet_Right);
                                
                            }
                            break;

                        case Stance::Enemy_Trebochet_Release_RH_05:
                            {
                                uint8_t idx = static_cast<uint8_t>(newStance) - static_cast<uint8_t>(Stance::Enemy_Trebochet_Release_RH_01);
                                playGame_HandleEnemies_Trebochet_SetFrame(idx, ItemType::Trebochet_Right);

                                Item &item = enemy.getItem();
                                uint8_t r = a.randomLFSR(static_cast<uint8_t>(0), static_cast<uint8_t>(3));
                                item.setItemType(static_cast<ItemType>(static_cast<uint8_t>(ItemType::Trebochet_Ball_Right_1) + r));
                                item.setCounter(20);
                                item.setX(enemy.getX() + 28);
                                item.setY(enemy.getY() + 10);

                            }
                            break;

                    }

                    break;

                case EnemyType::SwordFighter:

                    switch (newStance) {
                                
                        case Stance::Enemy_Sword_Lunge_LH_03:
                        case Stance::Enemy_Sword_Lunge_RH_03:
                            {
                                if (player.getSwordWound() == 0 && playGame_EnemyStabsPlayer(player)) {

                                    player.decHealth(1);
                                    player.setSwordWound(12);

                                    if (player.getHealth() == 0) {

                                        int16_t dist = getDistanceBetween(enemy);
                                        player.clear();


                                        // Enemy puts away sword ..

                                        switch (enemy.getDirection()) {

                                            case Direction::Left:
                                                enemy.insert(Stance::Enemy_Walk_LH_00);
                                                break;

                                            case Direction::Right:
                                                enemy.insert(Stance::Enemy_Walk_RH_00);
                                                break;

                                        }


                                        // Player dies but whch direction does he fall?

                                        switch (dist) {

                                            case -999 ... 0:

                                                switch (player.getDirection()) {

                                                    case Direction::Left:

                                                        player.pushSequence(Stance::Man_Die_FWD_LH_01, Stance::Man_Die_FWD_LH_04);
                                                        break;

                                                    case Direction::Right:

                                                        player.pushSequence(Stance::Man_Die_BWD_RH_01, Stance::Man_Die_BWD_RH_04);
                                                        break;

                                                }

                                                break;

                                            case 1 ... 999:

                                                switch (player.getDirection()) {

                                                    case Direction::Left:

                                                        player.pushSequence(Stance::Man_Die_BWD_LH_01, Stance::Man_Die_BWD_LH_04);
                                                        break;

                                                    case Direction::Right:

                                                        player.pushSequence(Stance::Man_Die_FWD_RH_01, Stance::Man_Die_FWD_RH_04);
                                                        break;

                                                }

                                                break;

                                        }                                                

                                    }

                                }

                            }

                            break;

                    }

                    break;

            }

            FX::seekData(Constants::subsititueStance + (static_cast<uint16_t>(enemy.getStance()) * 2));
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

                case EnemyType::SwordFighter:
                    {
                        int16_t dist = getDistanceBetween(enemy);

                        switch (enemy.getDirection()) {

                            case Direction::Left:

                                playGame_HandleEnemies_SwordFighter(player, enemy, Stance::Man_LH_Start - Stance::Man_RH_Start, 0, -dist);
                                break;

                            case Direction::Right:

                                playGame_HandleEnemies_SwordFighter(player, enemy, 0, Stance::Man_LH_Start - Stance::Man_RH_Start, dist);
                                break;
                                
                        }

                    }

                    break;

                default:
                    break;

            }

        }

    }

}


bool playGame_EnemyStabsPlayer(Player &player) {

    if (player.getEnemyIdx() == 255) {

        uint8_t enemyIdx = world.getClosestEnemy(EnemyType::SwordFighter);
        player.setEnemyIdx(enemyIdx);

        if (enemyIdx = 255) return false;

    }

    Enemy &enemy = world.getEnemy(player.getEnemyIdx());
    Rect playerRect = { 61, - Constants::GroundY + player.getY(), 6, 16 };

    if (enemy.getStance() == Stance::Enemy_Sword_Lunge_LH_03) {

        Point enemyPoint = { enemy.getX() + world.getMiddleground() - 10, - enemy.getY() + 12 };
        return collide(enemyPoint, playerRect);

    }

    if (enemy.getStance() == Stance::Enemy_Sword_Lunge_RH_03) {

        Point enemyPoint = { enemy.getX() + world.getMiddleground() + 17, - enemy.getY() + 12 };
        return collide(enemyPoint, playerRect);

    }

    return false;

}


bool playGame_PlayerStabsEnemy(Player &player) {

    Enemy &enemy = world.getEnemy(player.getEnemyIdx());
    Rect enemyRect = { enemy.getX() + world.getMiddleground(), - enemy.getY(), 6, 16 };

    if (enemy.getDirection() == Direction::Right) {

        enemyRect.x = enemyRect.x + 2;

    }
    
    if (player.getStance() == Stance::Man_Sword_Lunge_RH_03) {

        Point playerPoint = { 61 + 15, - Constants::GroundY + player.getY() + 12 };
        return collide(playerPoint, enemyRect);

    }

    if (player.getStance() == Stance::Man_Sword_Lunge_LH_03) {

        Point playerPoint = { 61 - 10, - Constants::GroundY + player.getY() + 12 };
        return collide(playerPoint, enemyRect);        

    }

    return false;

}

int16_t getDistanceBetween(Enemy &enemy) {

    return -world.getMiddleground() + 56 - enemy.getX();

}

int16_t getDistanceBetween(Player &player, EnemyType enemyType) {

    if (player.getEnemyIdx() == 255) {

        uint8_t enemyIdx = world.getClosestEnemy(enemyType);
        player.setEnemyIdx(enemyIdx);

    }

    if (player.getEnemyIdx() != 255) {

        Enemy &enemy = world.getEnemy(player.getEnemyIdx());
        return -world.getMiddleground() + 56 - enemy.getX();

    }
    else {

        return 9999;

    }

}