#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"


void renderWorld(uint8_t currentPlane) {

    Player &player = world.getPlayer();

    uint8_t yOffset = Constants::GroundY;

    if (player.getY() < 5) yOffset = Constants::GroundY - player.getY();

    // SpritesU::drawOverwriteFX(world.getBackground() - 128, yOffset - Constants::GroundY, Images::Background, currentPlane);    
    // SpritesU::drawOverwriteFX(world.getBackground(), yOffset - Constants::GroundY, Images::Background, currentPlane);    
    // SpritesU::drawOverwriteFX(world.getBackground() + 128, yOffset - Constants::GroundY, Images::Background, currentPlane);    

    // SpritesU::drawOverwriteFX(world.getBackground() - 128, ((yOffset - Constants::GroundY) / 4) - 8, Images::Background_Above, currentPlane);    
    SpritesU::drawOverwriteFX(world.getBackground(), ((yOffset - Constants::GroundY) / 4) - 8, Images::Background_Above, currentPlane);    
    SpritesU::drawOverwriteFX(world.getBackground() + 128, ((yOffset - Constants::GroundY) / 4) - 8, Images::Background_Above, currentPlane);    

    // SpritesU::drawOverwriteFX(world.getBackground() - 128, (yOffset - Constants::GroundY)/4, Images::Background, currentPlane);    
    SpritesU::drawOverwriteFX(world.getBackground(), (yOffset - Constants::GroundY)/4, Images::Background, currentPlane);    
    SpritesU::drawOverwriteFX(world.getBackground() + 128, (yOffset - Constants::GroundY)/4, Images::Background, currentPlane);    

    for (uint8_t i = 4; i < 8; i++) {    
        SpritesU::drawPlusMaskFX(world.getPalm(i), 20 + yOffset - Constants::GroundY, Constants::PalmImages[i], currentPlane);
    }
    // SpritesU::drawPlusMaskFX(world.getPalm5(), 20 + yOffset - Constants::GroundY, Images::Palm5, currentPlane);
    // SpritesU::drawPlusMaskFX(world.getPalm6(), 20 + yOffset - Constants::GroundY, Images::Palm6, currentPlane);
    // SpritesU::drawPlusMaskFX(world.getPalm7(), 20 + yOffset - Constants::GroundY, Images::Palm5, currentPlane);
    // SpritesU::drawPlusMaskFX(world.getPalm8(), 20 + yOffset - Constants::GroundY, Images::Palm6, currentPlane);


    for (uint8_t y = 0; y < 10; y = y + 2) {

        for (uint8_t i= 0; i < numberOfTiles - 1; i = i + 2) {

            uint8_t tile00 = world.getTile(i, y);
            uint8_t tile01 = world.getTile(i + 1, y);
            uint8_t tile10 = world.getTile(i, y + 1);
            uint8_t tile11 = world.getTile(i + 1, y + 1);

            uint24_t imgTile = 0;

            if (tile00 == 1 && tile01 == 1 && tile10 == 0 && tile11 == 0)         imgTile = Images::Crate_10;
            if (tile00 == 1 && tile01 == 1 && tile10 == 16 && tile11 == 0)        imgTile = Images::Crate_20;
            if (tile00 == 1 && tile01 == 1 && tile10 == 0 && tile11 == 17)        imgTile = Images::Crate_21;
            if (tile00 == 1 && tile01 == 1 && tile10 == 0 && tile11 == 1)         imgTile = Images::Crate_00;
            if (tile00 == 1 && tile01 == 2 && tile10 == 0 && tile11 == 2)         imgTile = Images::Crate_00;
            if (tile00 == 2 && tile01 == 2 && tile10 == 0 && tile11 == 2)         imgTile = Images::Crate_09;
            if (tile00 == 1 && tile01 == 2 && tile10 == 0 && tile11 == 2)         imgTile = Images::Crate_03;
            if (tile00 == 1 && tile01 == 1 && tile10 == 1 && tile11 == 1)         imgTile = Images::Crate_05;
            if (tile00 == 2 && tile01 == 2 && tile10 == 1 && tile11 == 1)         imgTile = Images::Crate_01;
            if (tile00 == 18 && tile01 == 18 && tile10 == 18 && tile11 == 18)     imgTile = Images::Crate_22;
            if (tile00 == 2 && tile01 == 1 && tile10 == 1 && tile11 == 0)         imgTile = Images::Crate_02;
            if (tile00 == 1 && tile01 == 1 && tile10 == 1 && tile11 == 0)         imgTile = Images::Crate_02;
            if (tile00 == 1 && tile01 == 1 && tile10 == 2 && tile11 == 0)         imgTile = Images::Crate_04;
            if (tile00 == 2 && tile01 == 0 && tile10 == 2 && tile11 == 0)         imgTile = Images::Crate_06;
            if (tile00 == 0 && tile01 == 2 && tile10 == 0 && tile11 == 2)         imgTile = Images::Crate_07;
            if (tile00 == 3 && tile01 == 3 && tile10 == 0 && tile11 == 0)         imgTile = Images::Spikes;
            if (tile00 == 6 && tile01 == 5 && tile10 == 0 && tile11 == 0)         imgTile = Images::Crate_11;
            if (tile00 == 0 && tile01 == 6 && tile10 == 0 && tile11 == 0)         imgTile = Images::Crate_11;
            if (tile00 == 11 && tile01 == 0 && tile10 == 0 && tile11 == 0)        imgTile = Images::Crate_11a;


            // ladders

            if (tile00 == 7 && tile01 == 7 && tile10 == 8 && tile11 == 8)         imgTile = Images::Crate_13;
            if (tile00 == 7 && tile01 == 7 && tile10 == 12 && tile11 == 12)       imgTile = Images::Crate_14;
            if (tile00 == 12 && tile01 == 12 && tile10 == 8 && tile11 == 8)       imgTile = Images::Crate_15;
            if (tile00 == 12 && tile01 == 12 && tile10 == 12 && tile11 == 12)     imgTile = Images::Crate_16;


            // Rope

            if (tile00 == 13 && tile01 == 0 && tile10 == 13 && tile11 == 15)      imgTile = Images::Crate_17;
            if (tile00 == 0 && tile01 == 14 && tile10 == 15 && tile11 == 14)      imgTile = Images::Crate_18;
            if (tile00 == 0 && tile01 == 0 && tile10 == 15 && tile11 == 15)       imgTile = Images::Crate_19;
            if (tile00 == 15 && tile01 == 15 && tile10 == 0 && tile11 == 0)       imgTile = Images::Crate_23;


            // Stairs

            if (tile00 == 2 && tile01 == 2 && tile10 == 4 && tile11 == 5)         imgTile = Images::Crate_08;
            if (tile00 == 2 && tile01 == 2 && tile10 == 9 && tile11 == 10)        imgTile = Images::Crate_12;


            // Slide

            if (tile00 == 2 && tile01 == 0 && tile10 == 19 && tile11 == 0)        imgTile = Images::Crate_24;
            if (tile00 == 2 && tile01 == 2 && tile10 == 1 && tile11 == 19)        imgTile = Images::Crate_28;
            if (tile00 == 2 && tile01 == 20 && tile10 == 20 && tile11 == 0)       imgTile = Images::Crate_29;
            if (tile00 == 0 && tile01 == 2 && tile10 == 0 && tile11 == 21)        imgTile = Images::Crate_25;
            if (tile00 == 2 && tile01 == 2 && tile10 == 21 && tile11 == 1)        imgTile = Images::Crate_30;
            if (tile00 == 22 && tile01 == 2 && tile10 == 0 && tile11 == 22)       imgTile = Images::Crate_31;

            // Vertical Vines

            if (tile00 == 31 && tile01 == 31 && tile10 == 31 && tile11 == 31)     imgTile = Images::Crate_36;
            if (tile00 == 32 && tile01 == 32 && tile10 == 31 && tile11 == 31)     imgTile = Images::Crate_37;
            if (tile00 == 31 && tile01 == 31 && tile10 == 33 && tile11 == 33)     imgTile = Images::Crate_38;


            // Rollers R then L

            if (world.isRollerTile_RH(tile00) && world.isRollerTile_RH(tile01) && tile10 == 0 && tile11 == 0) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_32, ((frameCount % 24) / 6 * 3) + currentPlane);
            }

            if (tile00 == 2 && tile01 == 2 && world.isRollerTile_RH(tile10) && world.isRollerTile_RH(tile11)) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_34, ((frameCount % 24) / 6 * 3) + currentPlane);
            }

            if (world.isRollerTile_LH(tile00) && world.isRollerTile_LH(tile01) && tile10 == 0 && tile11 == 0) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_33, ((frameCount % 24) / 6 * 3) + currentPlane);
            }

            if (tile00 == 2 && tile01 == 2 && world.isRollerTile_LH(tile10) && world.isRollerTile_LH(tile11)) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_35, ((frameCount % 24) / 6 * 3) + currentPlane);
            }



            // Render image?

            if (imgTile != 0) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), imgTile, currentPlane);
            }

        }

    }

    for (uint8_t i = 0; i < Constants::ItemCount; i++) {

        Item &item = world.getItem(i);

        if (item.getItemType() == ItemType::None) break;

        uint24_t imageIdx = 0;
        uint8_t frame = item.getFrame();

        switch (item.getItemType()) {

            case ItemType::Key1:
                imageIdx = Images::Item_00;
                frame = item.getFrame() / 16;
                break;

            case ItemType::Anchor:
                imageIdx = Images::Item_11;
                frame = item.getFrame() / 16;
                break;

            case ItemType::PinchBar:
                imageIdx = Images::Item_08;
                frame = item.getFrame() / 16;
                break;

            case ItemType::WoodenBarrier:
                imageIdx = Images::Item_01;
                break;

            case ItemType::MysteryCrate:

                if (item.getFrame() < 8) {
                    imageIdx = Images::Item_07;
                }
                break;

            case ItemType::TrapDoor:
                imageIdx = Images::Item_03;
                frame = item.getFrame() / 16;
                break;

            case ItemType::Punji:
                imageIdx = Images::Item_04;
                break;

            case ItemType::Potion:
                imageIdx = Images::Item_10;
                frame = item.getFrame() / 16;
                break;

            case ItemType::LockedDoor:
                imageIdx = Images::Item_09;
                break;

            case ItemType::Hammer:

                switch (item.getFrame()) {

                    case 3 ... 21:
                        imageIdx = Images::Item_05;
                        frame = (item.getFrame() / 3);
                        break;

                    default:
                        imageIdx = Images::Item_05;
                        frame = 0;
                        break;

                }

                break;

            case ItemType::Lever_LH:
            case ItemType::Lever_RH:

                switch (item.getFrame()) {

                    case 3 ... 21:
                        imageIdx = Images::Item_19;
                        frame = (item.getFrame() / 3) + (item.getItemType() == ItemType::Lever_RH ? 8 : 0);
                        break;

                    default:
                        imageIdx = Images::Item_19;
                        frame = 0 + (item.getItemType() == ItemType::Lever_RH ? 8 : 0);
                        break;

                }

                break;

            case ItemType::Sword:

                switch (item.getFrame()) {

                    case 3 ... 21:
                        imageIdx = Images::Item_17;
                        frame = (item.getFrame() / 3);
                        break;

                    default:
                        imageIdx = Images::Item_17;
                        frame = 0;
                        break;

                }

                break;

            case ItemType::Chakana:
                imageIdx = Images::Item_18;
                frame = item.getFrame();
                break;

            // case ItemType::Lever:
            //     imageIdx = Images::Item_19;
            //     frame = item.getFrame();
            //     break;

            case ItemType::Vine:
                imageIdx = Images::Item_12;
                break;

            case ItemType::Flame:
                imageIdx = Images::Item_13;
                break;

            case ItemType::Trebochet_Left:
                imageIdx = Images::Item_14;
                break;

            case ItemType::Trebochet_Right:
                imageIdx = Images::Item_15;
                break;

            case ItemType::SwingyThing:
            case ItemType::SwingyThing_2:
                imageIdx = Images::Item_16;
                break;

            case ItemType::Amulet:

                switch (item.getFrame()) {

                    case 3 ... 21:
                        imageIdx = Images::Item_06;
                        frame = item.getFrame() / 3;
                        break;

                    default:
                        imageIdx = Images::Item_06;
                        frame = 0;
                        break;

                }

                break;

        }

        if (imageIdx != 0){
            
            SpritesU::drawPlusMaskFX(item.getX() + world.getMiddleground() - 4, yOffset - item.getY(), imageIdx, (frame * 3) + currentPlane);

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
                uint8_t tile = world.getTile_RelativeToPlayer(0, 0);

                if (world.isSpringTile_LH(tile)) {
                    SpritesU::drawPlusMaskFX(56, yOffset - Constants::GroundY + player.getY(), Images::Player_Bounce, currentPlane);
                }
                else {
                    SpritesU::drawPlusMaskFX(56, yOffset - Constants::GroundY + player.getY(), Images::Player_Bounce, 3 + currentPlane);
                }

            }
            break;

        case Stance::Man_Die_Fire_LH_12:
        case Stance::Man_Die_Fire_RH_12:
            // Do nothing
            break;

        case Stance::Man_Sword_Stationary_RH:
        case Stance::Man_Sword_Lunge_RH_01 ... Stance::Man_Sword_Lunge_RH_06:
        case Stance::Man_Sword_Walk_RH_01 ... Stance::Man_Sword_Walk_RH_04:
        case Stance::Man_Sword_Walk_BK_RH_01 ... Stance::Man_Sword_Walk_BK_RH_04:
        case Stance::Man_Sword_StandingJump_RH_01 ... Stance::Man_Sword_StandingJump_RH_07:
            {
                FX::seekData(Constants::StanceImgIdx + static_cast<uint16_t>(player.getStance()));
                uint8_t stanceImg = FX::readPendingUInt8();
                FX::readEnd();
                
                uint8_t x = Constants::swordLunge_Player[static_cast<uint8_t>(player.getStance()) - static_cast<uint8_t>(Stance::Man_Sword_Stationary_RH)];
                SpritesU::drawPlusMaskFX(56 + x, yOffset - Constants::GroundY + player.getY(), Images::Player, (stanceImg * 3) + currentPlane);

                SpritesU::drawPlusMaskFX(56 + x - 1, yOffset - Constants::GroundY + player.getY() - 5, Images::Health, ((Constants::HealthMax - player.getHealth()) * 3) + currentPlane);
                // SpritesU::drawPlusMaskFX(2, 58, Images::Health, currentPlane);

            }
            break;

        case Stance::Man_Sword_Stationary_LH:
        case Stance::Man_Sword_Lunge_LH_01 ... Stance::Man_Sword_Lunge_LH_06:
        case Stance::Man_Sword_Walk_LH_01 ... Stance::Man_Sword_Walk_LH_04:
        case Stance::Man_Sword_Walk_BK_LH_01 ... Stance::Man_Sword_Walk_BK_LH_04:
        case Stance::Man_Sword_StandingJump_LH_01 ... Stance::Man_Sword_StandingJump_LH_07:
            {
                FX::seekData(Constants::StanceImgIdx + static_cast<uint16_t>(player.getStance()));
                uint8_t stanceImg = FX::readPendingUInt8();
                FX::readEnd();
                
                uint8_t x = Constants::swordLunge_Player[static_cast<uint8_t>(player.getStance()) - static_cast<uint8_t>(Stance::Man_Sword_Stationary_LH)];
                SpritesU::drawPlusMaskFX(56 - x, yOffset - Constants::GroundY + player.getY(), Images::Player, (stanceImg * 3) + currentPlane);

                SpritesU::drawPlusMaskFX(56 - x + 2, yOffset - Constants::GroundY + player.getY() - 5, Images::Health, ((Constants::HealthMax - player.getHealth()) * 3) + currentPlane);
                // SpritesU::drawPlusMaskFX(2, 58, Images::Health, currentPlane);

            }
            break;

        default:
            {
                FX::seekData(Constants::StanceImgIdx + static_cast<uint16_t>(player.getStance()));
                uint8_t stanceImg = FX::readPendingUInt8();
                FX::readEnd();

                SpritesU::drawPlusMaskFX(56, yOffset - Constants::GroundY + player.getY(), Images::Player, (stanceImg * 3) + currentPlane);

                // SpritesU::drawPlusMaskFX(0,0, Images::Player, ((stanceImg + 10) * 3) + currentPlane);

            }
            break;
        
    }


    // Render Sword Wound if applicable ..

    if (player.getSwordWound() != 0) {

        uint8_t enemyIdx = player.getEnemyIdx();

        if (enemyIdx != 255) {

            Enemy &enemy = world.getEnemy(enemyIdx);

            switch (enemy.getDirection()) {

                case Direction::Left:
                    SpritesU::drawPlusMaskFX(56, yOffset - Constants::GroundY + player.getY() + 2, Images::Sword_Wound, (((player.getSwordWound() / 3) + 4) * 3) + currentPlane);
                    break;

                case Direction::Right:
                    SpritesU::drawPlusMaskFX(56 + 11, yOffset - Constants::GroundY + player.getY() + 2, Images::Sword_Wound, (((player.getSwordWound() / 3) ) * 3) + currentPlane);
                    break;

            }

        }

    }

    for (uint8_t i = 0; i < Constants::EnemyCount; i++) {

        Enemy &enemy = world.getEnemy(i);

        if (enemy.getX() > 0) {

            switch (enemy.getStance()) {

                case Stance::Enemy_Sword_Stationary_LH:
                case Stance::Enemy_Sword_Lunge_LH_01 ... Stance::Enemy_Sword_Lunge_LH_06:
                case Stance::Enemy_Sword_Walk_LH_01 ... Stance::Enemy_Sword_Walk_LH_04:
                case Stance::Enemy_Sword_Walk_BK_LH_01 ... Stance::Enemy_Sword_Walk_BK_LH_04:
                case Stance::Enemy_Sword_StandingJump_LH_01 ... Stance::Enemy_Sword_StandingJump_LH_07:
                    {
                        FX::seekData(Constants::StanceImgIdx + static_cast<uint16_t>(enemy.getStance()));
                        uint8_t stanceImg = FX::readPendingUInt8();
                        FX::readEnd();

                        uint8_t x = Constants::SwordLunge_Enemy[static_cast<uint8_t>(enemy.getStance()) - static_cast<uint8_t>(Stance::Enemy_Sword_Stationary_LH)];
                        SpritesU::drawPlusMaskFX(enemy.getX() + world.getMiddleground() - 4 - x, yOffset - enemy.getY() - 5, Images::Health, ((Constants::HealthMax - enemy.getHealth()) * 3) + currentPlane);
                        SpritesU::drawPlusMaskFX(enemy.getX() + world.getMiddleground() - 4 - x, yOffset - enemy.getY(), Images::Enemy, (stanceImg * 3) + currentPlane);
                        
                        if (enemy.getItem().getItemType() == ItemType::Glint) {
                            SpritesU::drawPlusMaskFX(enemy.getItem().getX() + world.getMiddleground() - 4, yOffset - enemy.getItem().getY(), Images::Glint, (enemy.getItem().getFrame() * 3) + currentPlane);
                        }                        

                    }
                    break;

                case Stance::Enemy_Sword_Stationary_RH:
                case Stance::Enemy_Sword_Lunge_RH_01 ... Stance::Enemy_Sword_Lunge_RH_06:
                case Stance::Enemy_Sword_Walk_RH_01 ... Stance::Enemy_Sword_Walk_RH_04:
                case Stance::Enemy_Sword_Walk_BK_RH_01 ... Stance::Enemy_Sword_Walk_BK_RH_04:
                case Stance::Enemy_Sword_StandingJump_RH_01 ... Stance::Enemy_Sword_StandingJump_RH_07:
                    {
                        FX::seekData(Constants::StanceImgIdx + static_cast<uint16_t>(enemy.getStance()));
                        uint8_t stanceImg = FX::readPendingUInt8();
                        FX::readEnd();

                        uint8_t x = Constants::SwordLunge_Enemy[static_cast<uint8_t>(enemy.getStance()) - static_cast<uint8_t>(Stance::Enemy_Sword_Stationary_RH)];
                        SpritesU::drawPlusMaskFX(enemy.getX() + world.getMiddleground() - 4 + x, yOffset - enemy.getY() - 5, Images::Health, ((Constants::HealthMax - enemy.getHealth()) * 3) + currentPlane);
                        SpritesU::drawPlusMaskFX(enemy.getX() + world.getMiddleground() - 4 + x, yOffset - enemy.getY(), Images::Enemy, (stanceImg * 3) + currentPlane);
                        
                        if (enemy.getItem().getItemType() == ItemType::Glint) {
                            SpritesU::drawPlusMaskFX(enemy.getItem().getX() + world.getMiddleground() + 15, yOffset - enemy.getItem().getY(), Images::Glint, (enemy.getItem().getFrame() * 3) + currentPlane);
                        }                        

                    }
                    break;
                    
                default:
                    {
                        FX::seekData(Constants::StanceImgIdx + static_cast<uint16_t>(enemy.getStance()));
                        uint8_t stanceImg = FX::readPendingUInt8();
                        FX::readEnd();

                        SpritesU::drawPlusMaskFX(enemy.getX() + world.getMiddleground() - 4, yOffset - enemy.getY(), Images::Enemy, (stanceImg * 3) + currentPlane);

                        if (enemy.getItem().getItemType() == ItemType::Arrow_RH) {

                            SpritesU::drawPlusMaskFX(enemy.getItem().getX() + world.getMiddleground() - 4, yOffset - enemy.getItem().getY(), Images::Arrow, currentPlane);

                        }

                        else if (enemy.getItem().getItemType() == ItemType::Arrow_LH) {

                            SpritesU::drawPlusMaskFX(enemy.getItem().getX() + world.getMiddleground() - 4, yOffset - enemy.getItem().getY(), Images::Arrow, 3 + currentPlane);

                        }

                        else if ((enemy.getItem().getItemType() >= ItemType::Trebochet_Ball_Left_1 && enemy.getItem().getItemType() <= ItemType::Trebochet_Ball_Left_3) || 
                                 (enemy.getItem().getItemType() >= ItemType::Trebochet_Ball_Right_1 && enemy.getItem().getItemType() <= ItemType::Trebochet_Ball_Right_3)) {

                            SpritesU::drawPlusMaskFX(enemy.getItem().getX() + world.getMiddleground() - 4, yOffset - enemy.getItem().getY(), Images::Trebochet_Ball, (enemy.getItem().getFrame() * 3) + currentPlane);

                        }
                        
                    }
                    break;
                
            }


            // Render Sword Wound if applicable ..

            if (enemy.getSwordWound() != 0) {

                switch (player.getDirection()) {

                    case Direction::Left:
                   
                        SpritesU::drawPlusMaskFX(enemy.getX() + world.getMiddleground() - 4, yOffset - enemy.getY() + 2, Images::Sword_Wound, (((enemy.getSwordWound() / 3) + 4) * 3) + currentPlane);
                        break;

                    case Direction::Right:
            
                        SpritesU::drawPlusMaskFX(enemy.getX() + world.getMiddleground() + 6, yOffset - enemy.getY()+ 2, Images::Sword_Wound, (((enemy.getSwordWound() / 3) ) * 3) + currentPlane);
                        break;

                }

            }

        }

    }

    // Render a puff ?

    Item &item = world.getItem(world.getItem(ItemType::Puff));

    if (item.getFrame() < Constants::Puff_Max) {

        SpritesU::drawPlusMaskFX(item.getX() + world.getMiddleground() - 4, yOffset - item.getY(), Images::Item_02, (item.getFrame() / 16 * 3) +  currentPlane);

    }

    for (uint8_t i = 0; i < Constants::ItemCount; i++) {

        Item &item = world.getItem(i);

        if (item.getItemType() == ItemType::None) break;

        if (item.getItemType() == ItemType::LockedDoor && item.getFrame() == 4) {

            SpritesU::drawPlusMaskFX(item.getX() + world.getMiddleground() - 4 + 11, yOffset - item.getY(), Images::Item_09a, currentPlane);

        }

    }


    // Render waves and foreground ..

    if (world.getWaveIdx() != Constants::NoWaves) {
        // SpritesU::drawOverwriteFX(world.getWave() - 128, 55 + yOffset - Constants::GroundY, Images::Waves, ((world.getWaveIdx() / 64) * 3) + currentPlane);
        SpritesU::drawOverwriteFX(world.getWave(), 55 + yOffset - Constants::GroundY, Images::Waves, ((world.getWaveIdx() / 64) * 3) + currentPlane);
        SpritesU::drawOverwriteFX(world.getWave() + 128, 55 + yOffset - Constants::GroundY, Images::Waves, ((world.getWaveIdx() / 64) * 3) + currentPlane);
    }

    if (world.getX() < 30) {
        // SpritesU::drawOverwriteFX(world.getWave(), 32, Images::Beach_LH, ((world.getWaveIdx() / 64) * 3) + currentPlane);
    }

    // Front palms

    // for (uint8_t i = 0; i < 4; i++) {

    //     SpritesU::drawPlusMaskFX(world.getPalm(i) / 2, 10 + yOffset - Constants::GroundY, Constants::PalmImages[i], currentPlane);

    // }






                    // a.drawRect(56 + 3, yOffset - Constants::GroundY + player.getY(), 10,16, WHITE);
                    // a.drawRect(world.getItem(0).getX() + world.getMiddleground() - 4 + 1, yOffset - world.getItem(0).getY() + 1, 14, 14, WHITE);



    if (menu.getX() != 128) {

        uint8_t frame = player.getItemCount() > 0 ? 0 : 4;

        if (player.getItemCount() > 3) {

            if (menu.getTop() + 3 == player.getItemCount()) {
                frame = 2;
            }
            else if (menu.getTop() == 0 ) {
                frame = 1;
            }
            else {
                frame = 3;
            }

        }

        SpritesU::drawPlusMaskFX(menu.getX(), 0,  Images::InventoryPanel, (frame * 3) + currentPlane);

        for (uint8_t i = menu.getTop(); i < menu.getTop() + 3; i++) {

            InventoryItem &item = player.getItem(i);
            if (item.getItemType() == ItemType::None)   break;

            uint24_t imgIndex = 0;
            uint24_t imgFrame = 0;

            switch (item.getItemType()) {

                case ItemType::Key1:
                    imgIndex = Images::Item_00;
                    break;

                case ItemType::PinchBar:
                    imgIndex = Images::Item_08;
                    break;

                case ItemType::Hammer:
                    imgIndex = Images::Item_05;
                    break;

                case ItemType::Amulet:
                    imgIndex = Images::Item_06;
                    break;

                case ItemType::Potion:
                    imgIndex = Images::Item_10;
                    imgFrame = 24;
                    break;

                case ItemType::Anchor:
                    imgIndex = Images::Item_11;
                    break;

                case ItemType::Sword:
                    imgIndex = Images::Item_17;
                    break;

            }

            if (imgIndex > 0) {

                SpritesU::drawPlusMaskFX(menu.getX() + 13, 6 + ((i - menu.getTop()) * 18), imgIndex, imgFrame + currentPlane);

            }

        }

        if (frameCount % 64 < 32 && player.getItemCount() > 0) {

            SpritesU::drawPlusMaskFX(menu.getX() + 12, 5 + ((menu.getY() - menu.getTop()) * 18), Images::Cursor_00, currentPlane);
            SpritesU::drawPlusMaskFX(menu.getX() + 27, 5 + ((menu.getY() - menu.getTop()) * 18), Images::Cursor_01, currentPlane);

        }

    }

    // SpritesU::drawPlusMaskFX(1, 1, Images::Health, currentPlane);

// {
//     Item &item = world.getItem(0);
//     a.drawRect(item.getX() + world.getMiddleground() - 4 + 6 + Constants::swingyThing_X[item.getFrame()], yOffset - item.getY() + Constants::swingyThing_Y[item.getFrame()] + 11, 20, 3 , WHITE);
// a.drawRect(59, yOffset - Constants::GroundY + player.getY(), 10, 16, WHITE);
    // Serial.println(item.getFrame());
// }


/*
    if (player.getEnemyIdx() != 255) {

        Enemy &enemy = world.getEnemy(player.getEnemyIdx());
        Rect playerRect = { 61, yOffset - Constants::GroundY + player.getY(), 6, 16 };
        Rect enemyRect = { enemy.getX() + world.getMiddleground(), yOffset - enemy.getY(), 6, 16 };

        if (enemy.getDirection() == Direction::Right) {
            enemyRect.x = enemyRect.x + 2;
        }
        
        a.drawRect(playerRect.x, playerRect.y, playerRect.width, playerRect.height , WHITE);
        a.drawRect(enemyRect.x, enemyRect.y, enemyRect.width, enemyRect.height , WHITE);

        if (player.getStance() == Stance::Man_Sword_Lunge_RH_03 && player.getDirection() == Direction::Right) {
            a.drawLine(playerRect.x + 14, playerRect.y + 10, playerRect.x + 14, playerRect.y + 14, LIGHT_GRAY);
            a.drawLine(playerRect.x + 12, playerRect.y + 12, playerRect.x + 16, playerRect.y + 12, LIGHT_GRAY);
            Point playerPoint = { playerRect.x + 15, playerRect.y + 12 };
        }

        if (player.getStance() == Stance::Man_Sword_Lunge_LH_03 && player.getDirection() == Direction::Left) {
            a.drawLine(playerRect.x - 9, playerRect.y + 10, playerRect.x - 9, playerRect.y + 14, LIGHT_GRAY);
            a.drawLine(playerRect.x - 11, playerRect.y + 12, playerRect.x - 7, playerRect.y + 12, LIGHT_GRAY);
            Point playerPoint = { playerRect.x - 9, playerRect.y + 12 };
        }

        if (enemy.getStance() == Stance::Enemy_Sword_Lunge_LH_03 && enemy.getDirection() == Direction::Left) {
            a.drawLine(enemyRect.x - 9, enemyRect.y + 10, enemyRect.x - 9, enemyRect.y + 14, LIGHT_GRAY);
            a.drawLine(enemyRect.x - 11, enemyRect.y + 12, enemyRect.x - 7, enemyRect.y + 12, LIGHT_GRAY);
            Point enemyPoint = { enemyRect.x - 9, enemyRect.y + 12 };
        }

        if (enemy.getStance() == Stance::Enemy_Sword_Lunge_RH_03 && enemy.getDirection() == Direction::Right) {
            a.drawLine(enemyRect.x + 14, enemyRect.y + 10, enemyRect.x + 14, enemyRect.y + 14, LIGHT_GRAY);
            a.drawLine(enemyRect.x + 12, enemyRect.y + 12, enemyRect.x + 16, enemyRect.y + 12, LIGHT_GRAY);
            Point enemyPoint = { enemyRect.x - 9, enemyRect.y + 12 };
        }

    }
*/

}


