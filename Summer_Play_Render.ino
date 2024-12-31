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
    // SpritesU::drawPlusMaskFX(world.getPalm(5), 20 + yOffset - Constants::GroundY, Images::Palm5, currentPlane);
    // SpritesU::drawPlusMaskFX(world.getPalm(6), 20 + yOffset - Constants::GroundY, Images::Palm6, currentPlane);
    // SpritesU::drawPlusMaskFX(world.getPalm(7), 20 + yOffset - Constants::GroundY, Images::Palm5, currentPlane);
    // SpritesU::drawPlusMaskFX(world.getPalm(8), 20 + yOffset - Constants::GroundY, Images::Palm6, currentPlane);


    for (uint8_t y = 0; y < 10; y = y + 2) {

        for (uint8_t i= 0; i < Constants::Map_X_Count - 1; i = i + 2) {

            uint8_t tile00 = world.getTile(i, y);
            uint8_t tile01 = world.getTile(i + 1, y);
            uint8_t tile10 = world.getTile(i, y + 1);
            uint8_t tile11 = world.getTile(i + 1, y + 1);

            uint24_t imgTile = 0;

            if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Blank && tile11 == Tiles::Blank)         imgTile = Images::Crate_10;
            if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Spring_LH && tile11 == Tiles::Blank)        imgTile = Images::Crate_20;
            if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Blank && tile11 == Tiles::Spring_RH)        imgTile = Images::Crate_21;
            if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Blank && tile11 == Tiles::Solid_Walkable)         imgTile = Images::Crate_00;
            if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Blank && tile11 == Tiles::Solid_NonWalkable)         imgTile = Images::Crate_00;
            if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Blank && tile11 == Tiles::Solid_NonWalkable)         imgTile = Images::Crate_09;
            if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Blank && tile11 == Tiles::Solid_NonWalkable)         imgTile = Images::Crate_03;
            if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Solid_Walkable && tile11 == Tiles::Solid_Walkable)         imgTile = Images::Crate_05;
            if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Solid_Walkable && tile11 == Tiles::Solid_Walkable)         imgTile = Images::Crate_01;
            if (tile00 == 18 && tile01 == 18 && tile10 == 18 && tile11 == 18)     imgTile = Images::Crate_22;
            if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Solid_Walkable && tile11 == Tiles::Blank)         imgTile = Images::Crate_02;
            if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Solid_Walkable && tile11 == Tiles::Blank)         imgTile = Images::Crate_02;
            if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Solid_NonWalkable && tile11 == Tiles::Blank)         imgTile = Images::Crate_04;
            if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Blank && tile10 == Tiles::Solid_NonWalkable && tile11 == Tiles::Blank)         imgTile = Images::Crate_06;
            if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Blank && tile10 == Tiles::Solid_Walkable && tile11 == Tiles::Blank)         imgTile = Images::Crate_06;
            if (tile00 == Tiles::Blank && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Blank && tile11 == Tiles::Solid_NonWalkable)         imgTile = Images::Crate_07;
            if (tile00 == Tiles::Blank && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Blank && tile11 == Tiles::Solid_Walkable)         imgTile = Images::Crate_07;
            if (tile00 == Tiles::Spikes && tile01 == Tiles::Spikes && tile10 == Tiles::Blank && tile11 == Tiles::Blank)         imgTile = Images::Spikes_Bottom;
            if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Spikes && tile11 == Tiles::Spikes)         imgTile = Images::Spikes_Top;
            // if (tile00 == 6 && tile01 == 5 && tile10 == Tiles::Blank && tile11 == Tiles::Blank)         imgTile = Images::Crate_11;
            if (tile00 == Tiles::Blank && tile01 == Tiles::Single_Stair_RH_Lower && tile10 == Tiles::Blank && tile11 == Tiles::Blank)         imgTile = Images::Crate_11;
            if (tile00 == Tiles::Single_Stair_LH_Lower && tile01 == Tiles::Blank && tile10 == Tiles::Blank && tile11 == Tiles::Blank)        imgTile = Images::Crate_11a;


            // ladders

            if (tile00 == Tiles::Ladder_Lower && tile01 == Tiles::Ladder_Lower && tile10 == Tiles::Ladder_Upper && tile11 == Tiles::Ladder_Upper)         imgTile = Images::Crate_13;
            if (tile00 == Tiles::Ladder_Lower && tile01 == Tiles::Ladder_Lower && tile10 == Tiles::Ladder_Middle && tile11 == Tiles::Ladder_Middle)       imgTile = Images::Crate_14;
            if (tile00 == Tiles::Ladder_Middle && tile01 == Tiles::Ladder_Middle && tile10 == Tiles::Ladder_Upper && tile11 == Tiles::Ladder_Upper)       imgTile = Images::Crate_15;
            if (tile00 == Tiles::Ladder_Middle && tile01 == Tiles::Ladder_Middle && tile10 == Tiles::Ladder_Middle && tile11 == Tiles::Ladder_Middle)     imgTile = Images::Crate_16;


            // Rope

            if (tile00 == Tiles::Rope_Support_LH && tile01 == Tiles::Blank && tile10 == Tiles::Rope_Support_LH && tile11 == Tiles::Rope)      imgTile = Images::Crate_17;
            if (tile00 == Tiles::Blank && tile01 == Tiles::Rope_Support_RH && tile10 == Tiles::Rope && tile11 == Tiles::Rope_Support_RH)      imgTile = Images::Crate_18;
            if (tile00 == Tiles::Blank && tile01 == Tiles::Blank && tile10 == Tiles::Rope && tile11 == Tiles::Rope)       imgTile = Images::Crate_19;
            if (tile00 == Tiles::Rope && tile01 == Tiles::Rope && tile10 == Tiles::Blank && tile11 == Tiles::Blank)       imgTile = Images::Crate_23;


            // Stairs

            if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Single_Stair_RH_Upper_TL && tile11 == Tiles::Single_Stair_RH_Upper_TR)          imgTile = Images::Crate_08;
            if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Single_Stair_LH_Upper_TL && tile11 == Tiles::Single_Stair_LH_Upper_TR)          imgTile = Images::Crate_12;


            // Slide

            if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Blank && tile10 == Tiles::Slide_LH_Upper && tile11 == Tiles::Blank)                                        imgTile = Images::Crate_24;
            if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Solid_Walkable && tile11 == Tiles::Slide_LH_Upper)                                    imgTile = Images::Crate_28;
            if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Slide_LH_Full && tile10 == Tiles::Slide_LH_Full && tile11 == Tiles::Blank)                                 imgTile = Images::Crate_29;
            if (tile00 == Tiles::Blank && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Blank && tile11 == Tiles::Slide_RH_Upper)                                        imgTile = Images::Crate_25;
            if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Slide_RH_Upper && tile11 == Tiles::Solid_Walkable)                                    imgTile = Images::Crate_30;
            if (tile00 == Tiles::Slide_RH_Full && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Blank && tile11 == Tiles::Slide_RH_Full)                                 imgTile = Images::Crate_31;

            // Vertical Vines

            if (tile00 == Tiles::Vine_Middle && tile01 == Tiles::Vine_Middle && tile10 == Tiles::Vine_Middle && tile11 == Tiles::Vine_Middle)     imgTile = Images::Crate_36;
            if (tile00 == Tiles::Vine_Lower && tile01 == Tiles::Vine_Lower && tile10 == Tiles::Vine_Middle && tile11 == Tiles::Vine_Middle)     imgTile = Images::Crate_37;
            if (tile00 == Tiles::Vine_Middle && tile01 == Tiles::Vine_Middle && tile10 == Tiles::Vine_Upper && tile11 == Tiles::Vine_Upper)     imgTile = Images::Crate_38;


            // Lever Portal
            // if (tile00 == 34 && tile01 == 34 && tile10 == 34 && tile11 == 34)     imgTile = Images::Crate_38; // SJH Should be commented out (no need for rendering).


            // Rollers R then L

            if (world.isRollerTile_RH(tile00) && world.isRollerTile_RH(tile01) && tile10 == Tiles::Blank && tile11 == Tiles::Blank) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_32, ((frameCount % 24) / 6 * 3) + currentPlane);
            }

            if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_NonWalkable && world.isRollerTile_RH(tile10) && world.isRollerTile_RH(tile11)) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_34, ((frameCount % 24) / 6 * 3) + currentPlane);
            }

            if (world.isRollerTile_LH(tile00) && world.isRollerTile_LH(tile01) && tile10 == Tiles::Blank && tile11 == Tiles::Blank) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_33, ((frameCount % 24) / 6 * 3) + currentPlane);
            }

            if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_NonWalkable && world.isRollerTile_LH(tile10) && world.isRollerTile_LH(tile11)) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_35, ((frameCount % 24) / 6 * 3) + currentPlane);
            }

            // Water

            if (tile00 == Tiles::Water_Plain && tile01 == Tiles::Water_Plain && tile10 == Tiles::Blank && tile11 == Tiles::Blank) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_39, ((frameCount % 48) / 3 * 3) + currentPlane);
            }

            if (tile00 == Tiles::Water_Bubbling_1 && tile01 == Tiles::Water_Bubbling_1 && tile10 == Tiles::Blank && tile11 == Tiles::Blank) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_40, ((frameCount % 48) / 3 * 3) + currentPlane);
            }

            if (tile00 == Tiles::Water_Bubbling_2 && tile01 == Tiles::Water_Bubbling_2 && tile10 == Tiles::Blank && tile11 == Tiles::Blank) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), Images::Crate_41, ((frameCount % 48) / 3 * 3) + currentPlane);
            }


            // Render image?

            if (imgTile != 0) {
                SpritesU::drawPlusMaskFX((i*8) + world.getMiddleground() - 4, yOffset - (y * 8), imgTile, currentPlane);
            }

        }

    }

    for (uint8_t i = 0; i < Constants::ItemCount; i++) {

        Item &item = world.getItem(i);
        if (item.getItemType() == ItemType::Puff) break;

        uint24_t imageIdx = 0;
        imageIdx = FX::readIndexedUInt24(Images::ItemsIndex, static_cast<uint8_t>(item.getItemType()));
         
        uint8_t frame = item.getFrame();

        switch (item.getItemType()) {

            case ItemType::Key1:
            case ItemType::Anchor:
            case ItemType::PinchBar:
            case ItemType::TrapDoor:
            case ItemType::Potion:
                frame = item.getFrame() / 16;
                break;

            case ItemType::WoodenBarrier:
                break;

            case ItemType::MysteryCrate:

                if (item.getFrame() >= 8) {
                    imageIdx = 0;
                }
                break;

            case ItemType::LifeSaver:
            case ItemType::LifeSaver_Dissolve:
                frame = item.getFrame() / 22;
                break;

            case ItemType::Hammer:
            case ItemType::Sword:
            case ItemType::Amulet:

                switch (item.getFrame()) {

                    case 3 ... 21:
                        frame = (item.getFrame() / 3);
                        break;

                    default:
                        frame = 0;
                        break;

                }

                break;

            case ItemType::Lever_LH:
            case ItemType::Lever_RH:

                switch (item.getFrame()) {

                    case 3 ... 21:
                        frame = (item.getFrame() / 3) + (item.getItemType() == ItemType::Lever_RH ? 8 : 0);
                        break;

                    default:
                        frame = 0 + (item.getItemType() == ItemType::Lever_RH ? 8 : 0);
                        break;

                }

                break;

            case ItemType::Lever_Portal_Closed:
            case ItemType::Lever_Portal_Open:
            case ItemType::Lever_Portal_Auto_Closed:
            case ItemType::Lever_Portal_Auto_Open:

                frame = 0;
                if (item.getFrame() > 0) frame = item.getFrame() - 1;

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

    // Front palms  SJH should be enabled

    // for (uint8_t i = 0; i < 4; i++) {

    //     SpritesU::drawPlusMaskFX(world.getPalm(i) / 2, 10 + yOffset - Constants::GroundY, Constants::PalmImages[i], currentPlane);

    // }






                    // a.drawRect(56 + 3, yOffset - Constants::GroundY + player.getY(), 10,16, WHITE);
                    // a.drawRect(world.getItem(0).getX() + world.getMiddleground() - 4 + 1, yOffset - world.getItem(0).getY() + 1, 14, 14, WHITE);


    // Render Menu -----------------------------------------------------------------------------------------------------

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

            uint24_t imageIdx = FX::readIndexedUInt24(Images::ItemsIndex, static_cast<uint8_t>(item.getItemType()));
            uint24_t imgFrame = FX::readIndexedUInt8(Images::InventoryFrame, static_cast<uint8_t>(item.getItemType()));
            SpritesU::drawPlusMaskFX(menu.getX() + 13, 6 + ((i - menu.getTop()) * 18), imageIdx, imgFrame + currentPlane);

        }

        if (frameCount % 64 < 32 && player.getItemCount() > 0) {

            SpritesU::drawPlusMaskFX(menu.getX() + 12, 5 + ((menu.getY() - menu.getTop()) * 18), Images::Cursor_00, currentPlane);
            SpritesU::drawPlusMaskFX(menu.getX() + 27, 5 + ((menu.getY() - menu.getTop()) * 18), Images::Cursor_01, currentPlane);

        }

    }

}


