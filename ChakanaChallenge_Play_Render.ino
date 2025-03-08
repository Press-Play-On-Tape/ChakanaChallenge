#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"


void renderWorld() {

    Player &player = world.getPlayer();
    uint8_t yOffset = world.getYOffsetForRendering();


    // ____________________________________________________________________________________________________________________________________________________________________________________
    //
    // Render background ..

    {
        int8_t y = (yOffset - Constants::GroundY) / 4;

        for (int8_t i = -1; i < 2; i++) {

            int16_t x = world.getBackground() + (i * 128);
            SpritesU::drawOverwriteFX(x, y - 8, Images::Background, currentPlane);    

        }

    }


    // ____________________________________________________________________________________________________________________________________________________________________________________
    //
    // Render palms ..

    for (uint8_t i = 4; i < 8; i++) {    

        uint24_t palmIdx = FX::readIndexedUInt24(Images::PalmImages, i);
        SpritesU::drawPlusMaskFX(world.getPalm(i), 20 + yOffset - Constants::GroundY, palmIdx, currentPlane);

    }


    // ____________________________________________________________________________________________________________________________________________________________________________________
    //
    // Render foreground ..

    uint8_t xMin = 18;
    uint8_t xMax = Constants::Map_X_Count + 18;

    #ifndef sDEBUG_SWORD

        for (uint8_t y = 0; y < 16; y = y + 2) {

            int16_t renderY = yOffset - (y << 3);
            if (renderY <= -16 || renderY > 64) continue;

            for (uint8_t i = xMin; i < xMax; i = i + 2) {

                int16_t renderX = (i << 3) + world.getMiddleground() - 4;

                if (renderX <= -16)             { xMin = i + 2; continue; }
                if (renderX > menu.getX())      { xMax = i;     break; }

                uint8_t tile00 = world.getTile(i, y);
                uint8_t tile01 = world.getTile(i + 1, y);
                uint8_t tile10 = world.getTile(i, y + 1);
                uint8_t tile11 = world.getTile(i + 1, y + 1);

                uint24_t imgTile = 0;
                uint8_t frame = 0;

                if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Solid_Walkable && tile11 == Tiles::Solid_Walkable)         imgTile = Images::Crate_01;
                else if (tile00 == Tiles::Solid_Blocking)                                                                                                                   imgTile = Images::Crate_22;
                else if (tile00 == Tiles::Ladder_Lower && tile10 == Tiles::Ladder_Upper)                                                                                    imgTile = Images::Crate_13;
                else if (tile00 == Tiles::Ladder_Lower && tile10 == Tiles::Ladder_Middle)                                                                                   imgTile = Images::Crate_14;
                else if (tile00 == Tiles::Ladder_Middle && tile10 == Tiles::Ladder_Upper)                                                                                   imgTile = Images::Crate_15;
                else if (tile00 == Tiles::Ladder_Middle && tile10 == Tiles::Ladder_Middle)                                                                                  imgTile = Images::Crate_16;
                else if (tile00 == Tiles::Block_WithWeed)                                                                                                                   imgTile = Images::Crate_49;
                else if (tile00 == Tiles::Block_WithWeed_LH)                                                                                                                imgTile = Images::Crate_50;
                else if (tile00 == Tiles::Block_WithWeed_RH)                                                                                                                imgTile = Images::Crate_51;

                if (imgTile != 0) {
                    #ifdef RENDER_16X16
                    SpritesU::drawOverwriteFX(renderX, renderY, 16, 16, imgTile, currentPlane);
                    #else
                    SpritesU::drawOverwriteFX(renderX, renderY, imgTile, currentPlane);
                    #endif
                    continue;
                }

                else if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Blank && tile11 == Tiles::Blank)                            imgTile = Images::Crate_10;
                else if (tile00 == Tiles::Decorative_Triangle_LH)                                                                                                           imgTile = Images::Crate_42;
                else if (tile00 == Tiles::Decorative_Triangle_RH)                                                                                                           imgTile = Images::Crate_43;
                else if (tile00 == Tiles::Trebochet_To_RH)                                                                                                                  imgTile = Images::Crate_46;
                // else if (tile00 == Tiles::Trebochet_To_LH)                                                                                                                  imgTile = Images::Crate_47;
                else if (tile00 == Tiles::Weed)                                                                                                                             imgTile = Images::Crate_48;
                else if (tile10 == Tiles::Spring_LH && tile11 == Tiles::Blank)                                                                                              imgTile = Images::Crate_20;
                else if (tile10 == Tiles::Blank && tile11 == Tiles::Spring_RH)                                                                                              imgTile = Images::Crate_21;
                // else if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Blank && tile11 == Tiles::Solid_NonWalkable)             imgTile = Images::Crate_00;
                // else if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Blank && tile11 == Tiles::Solid_NonWalkable)             imgTile = Images::Crate_03;
                // else if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Solid_NonWalkable && tile11 == Tiles::Blank)                imgTile = Images::Crate_04;
                // else if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Solid_Walkable && tile11 == Tiles::Solid_Walkable)          imgTile = Images::Crate_05;
                // else if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Solid_Walkable && tile11 == Tiles::Blank)                   imgTile = Images::Crate_02;
                // else if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Blank && tile11 == Tiles::Solid_NonWalkable)          imgTile = Images::Crate_09;
                else if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Solid_Walkable && tile11 == Tiles::Blank)                imgTile = Images::Crate_02;
                else if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Blank && tile10 == Tiles::Solid_Walkable && tile11 == Tiles::Blank)                         imgTile = Images::Crate_06;
                else if (tile00 == Tiles::Blank && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Blank && tile11 == Tiles::Solid_Walkable)                         imgTile = Images::Crate_07;
                else if (tile00 == Tiles::Single_Stair_RH_Lower && tile11 == Tiles::Single_Stair_RH_Upper_TR)                                                               imgTile = Images::Crate_44;
                else if (tile01 == Tiles::Single_Stair_LH_Lower && tile10 == Tiles::Single_Stair_LH_Upper_TL)                                                               imgTile = Images::Crate_45;
                // else if (/*tile00 == Tiles::Blank && */tile01 == Tiles::Single_Stair_RH_Lower /*&& tile10 == Tiles::Blank && tile11 == Tiles::Blank*/)                      imgTile = Images::Crate_11;
                else if (tile00 == Tiles::Single_Stair_LH_Lower)                                                                                                            imgTile = Images::Crate_11a;
                else if (tile11 == Tiles::Spikes)                                                                                                                           imgTile = Images::Spikes_Top;
                else if (tile00 == Tiles::Spikes)                                                                                                                           imgTile = Images::Spikes_Bottom;
                else if (tile00 == Tiles::Sign_01)                                                                                                                          imgTile = Images::Crate_52;




                // Rope

                else if (tile10 == Tiles::Rope_Support_LH && tile11 == Tiles::Rope)                                                                                         imgTile = Images::Crate_17;
                else if (tile10 == Tiles::Rope && tile11 == Tiles::Rope_Support_RH)                                                                                         imgTile = Images::Crate_18;
                else if (tile10 == Tiles::Rope && tile11 == Tiles::Rope)                                                                                                    imgTile = Images::Crate_19;
                else if (tile00 == Tiles::Rope && tile01 == Tiles::Rope)                                                                                                    imgTile = Images::Crate_23;


                // Stairs

                else if (tile11 == Tiles::Single_Stair_RH_Upper_TR)                                                                                                         imgTile = Images::Crate_08;
                else if (tile11 == Tiles::Single_Stair_LH_Upper_TR)                                                                                                         imgTile = Images::Crate_12;


                // Slide

                else if (tile10 == Tiles::Slide_LH_Upper && tile11 == Tiles::Blank)                                                                                         imgTile = Images::Crate_24;
                else if (tile10 == Tiles::Solid_Walkable && tile11 == Tiles::Slide_LH_Upper)                                                                                imgTile = Images::Crate_28;
                else if (tile01 == Tiles::Slide_LH_Full && tile10 == Tiles::Slide_LH_Full)                                                                                  imgTile = Images::Crate_29;
                else if (tile11 == Tiles::Slide_RH_Upper)                                                                                                                   imgTile = Images::Crate_25;
                else if (tile10 == Tiles::Slide_RH_Upper)                                                                                                                   imgTile = Images::Crate_30;
                else if (tile00 == Tiles::Slide_RH_Full && tile11 == Tiles::Slide_RH_Full)                                                                                  imgTile = Images::Crate_31;


                // Vertical Vines

                else if (tile00 == Tiles::Vine_Middle && tile10 == Tiles::Vine_Middle)                                                                                      imgTile = Images::Crate_36;
                else if (tile00 == Tiles::Vine_Lower && tile01 == Tiles::Vine_Lower)                                                                                        imgTile = Images::Crate_37;
                else if (tile11 == Tiles::Vine_Upper)                                                                                                                       imgTile = Images::Crate_38;


                // Render image?

                if (imgTile != 0) {

                    #ifdef RENDER_16X16
                    SpritesU::drawPlusMaskFX(renderX, renderY, 16, 16, imgTile, currentPlane);
                    #else
                    SpritesU::drawPlusMaskFX(renderX, renderY, imgTile, currentPlane);
                    #endif

                }
                else {


                    // Rollers R then L
                    uint8_t yOffset = 0;

                    frame = ((world.getFrameCount() % 24) / 6 * 3);

                    if (world.isRollerTile_RH(tile00))                                                                                                                          { imgTile = Images::Crate_32; yOffset = 8; }
                    else if (world.isRollerTile_RH(tile10))                                                                                                                     { imgTile = Images::Crate_34; }
                    else if (world.isRollerTile_LH(tile00))                                                                                                                     { imgTile = Images::Crate_33; yOffset = 8; }
                    else if (world.isRollerTile_LH(tile10))                                                                                                                     { imgTile = Images::Crate_35; }

                    if (imgTile != 0) {
                        SpritesU::drawOverwriteFX(renderX, renderY + yOffset, imgTile, frame + currentPlane);
                    }

                }


                // Water

                if (imgTile == 0) {

                    frame = ((world.getFrameCount() % 48) / 3 * 3);
                    
                    if (tile00 == Tiles::Water_Plain && tile01 == Tiles::Water_Plain)                                                                                           imgTile = Images::Crate_39;
                    else if (tile00 == Tiles::Water_Bubbling_1 && tile01 == Tiles::Water_Bubbling_1)                                                                            imgTile = Images::Crate_40;
                    else if (tile00 == Tiles::Water_Bubbling_2 && tile01 == Tiles::Water_Bubbling_2)                                                                            imgTile = Images::Crate_41;

                    if (imgTile != 0) {
                        SpritesU::drawPlusMaskFX(renderX, renderY, imgTile, frame + currentPlane);
                    }

                }

            }

        }

    #endif


    // ____________________________________________________________________________________________________________________________________________________________________________________
    //
    // Rneder items ..

    for (uint8_t i = 0; i < Constants::ItemCount_Level; i++) {

        Item &item = world.getItem(i);
        if (item.getItemType() == ItemType::Puff) break;

        int16_t renderX = item.getX() + world.getMiddleground() - 4;
        int16_t renderY = yOffset - item.getY();

        if (renderX <= -48 || renderX > 127) continue;
        if (renderY <= -32 || renderY > 64) continue;

        uint24_t imageIdx = FX::readIndexedUInt24(Images::ItemsIndex, static_cast<uint8_t>(item.getItemType()));
         
        uint8_t frame = item.getFrame();

        switch (item.getItemType()) {

            #ifdef SHOW_ANCHOR
            case ItemType::Anchor:
            #endif
            case ItemType::Key1:
            case ItemType::PinchBar:
            case ItemType::Potion:
                frame = frame >> 4;
                break;

            case ItemType::MysteryCrate:
                if (frame >= 8) {
                    imageIdx = 0;
                }
                break;

            case ItemType::LifeSaver:
            case ItemType::LifeSaver_Dissolve:
                frame = frame / 22;
                break;

            case ItemType::Hammer:
            case ItemType::Sword:
            case ItemType::Amulet:
            case ItemType::Chakana_Small:

                switch (item.getFrame()) {

                    case 3 ... 21:
                        frame = frame / 3;
                        break;

                    default:
                        frame = 0;
                        break;

                }

                break;

            case ItemType::Lever_LH:
            case ItemType::Lever_RH:

                switch (frame) {

                    case 3 ... 21:
                        frame = (frame / 3) + (item.getItemType() == ItemType::Lever_RH ? 8 : 0);
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

        if (imageIdx != 0) {
            
            SpritesU::drawPlusMaskFX(renderX, renderY, imageIdx, (frame * 3) + currentPlane);

        }

    }


    // ____________________________________________________________________________________________________________________________________________________________________________________
    //
    // Render player ..

    Stance stance = player.getStance();
    uint8_t stanceImg = getStanceImg(stance);

    switch (stance) {

        #ifdef BOUNCEJUMP_3
        case Stance::Man_BounceJump_RH_3_03:
        case Stance::Man_BounceJump_RH_3_11:
        case Stance::Man_BounceJump_RH_3_25:
        #endif

        case Stance::Man_BounceJump_RH_4_03:
        case Stance::Man_BounceJump_RH_4_11:
        case Stance::Man_BounceJump_RH_4_25:

        #ifdef BOUNCEJUMP_3
        case Stance::Man_BounceJump_LH_3_03:
        case Stance::Man_BounceJump_LH_3_11:
        case Stance::Man_BounceJump_LH_3_25:
        #endif

        case Stance::Man_BounceJump_LH_4_03:
        case Stance::Man_BounceJump_LH_4_11:
        case Stance::Man_BounceJump_LH_4_25:
        case Stance::Man_Walk_FallLandSpring_BK_03:
        case Stance::Man_Walk_FallLandSpring_BK_15:
        case Stance::Man_Walk_FallLandSpring_BK_23:
        case Stance::Man_Walk_FallLandSpring_BK_24:
            {
                uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                uint8_t frame = world.isSpringTile_LH(tile) ? 0 : 3;
                SpritesU::drawPlusMaskFX(56, yOffset - Constants::GroundY + player.getY(), Images::Player_Bounce, frame + currentPlane);
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
                uint8_t x = FX::readIndexedUInt8(Constants::SwordLunge_Player, static_cast<uint8_t>(stance) - static_cast<uint8_t>(Stance::Man_Sword_Stationary_RH));
                renderPlayerAndHealth(stanceImg, 56 + x, yOffset - Constants::GroundY + player.getY(), player.getHealth());
            }
            break;

        case Stance::Man_Sword_Stationary_LH:
        case Stance::Man_Sword_Lunge_LH_01 ... Stance::Man_Sword_Lunge_LH_06:
        case Stance::Man_Sword_Walk_LH_01 ... Stance::Man_Sword_Walk_LH_04:
        case Stance::Man_Sword_Walk_BK_LH_01 ... Stance::Man_Sword_Walk_BK_LH_04:
        case Stance::Man_Sword_StandingJump_LH_01 ... Stance::Man_Sword_StandingJump_LH_07:
            {
                uint8_t x = FX::readIndexedUInt8(Constants::SwordLunge_Player, static_cast<uint8_t>(stance) - static_cast<uint8_t>(Stance::Man_Sword_Stationary_LH));
                renderPlayerAndHealth(stanceImg, 56 - x, yOffset - Constants::GroundY + player.getY(), player.getHealth());
            }
            break;

        default:
            {
               
                #ifdef RENDER_16X16
                SpritesU::drawPlusMaskFX(56, yOffset - Constants::GroundY + player.getY(), 16, 16, Images::Player, (stanceImg * 3) + currentPlane);
                #else
                SpritesU::drawPlusMaskFX(56, yOffset - Constants::GroundY + player.getY(), Images::Player, (stanceImg * 3) + currentPlane);
                #endif

            }
            break;
        
    }


    // Render Buzz?

    {
        uint16_t buzzCount = player.getBuzzCount();

        if (buzzCount > 0 && player.getHealth() > 0) {

            uint8_t frame = ((Constants::Buzz_Time - buzzCount) % 32) / 4;

            if (buzzCount < 32) frame = frame + 8;
            SpritesU::drawPlusMaskFX(56, yOffset - Constants::GroundY + player.getY() + 4, 16, 16, Images::Buzz, (frame * 3) + currentPlane);

        }

    }

    
    // ____________________________________________________________________________________________________________________________________________________________________________________
    //
    // Render wound if applicable ..

    if (player.getWound() != 0) {

        uint8_t enemyIdx = player.getEnemyIdx();

        if (enemyIdx != Constants::NoEnemy) {

            Enemy &enemy = world.getEnemy(enemyIdx);
            uint8_t frame = player.getWound() / 3;
            uint8_t y = yOffset - Constants::GroundY + player.getY() + 2;

            uint8_t xOffset = 0;
            uint8_t frameOffset = 0;
            
            switch (enemy.getDirection()) {

                case Direction::Left:
                    frameOffset = 4;
                    break;

                case Direction::Right:
                    xOffset = 11;
                    break;

            }

            SpritesU::drawPlusMaskFX(56 + xOffset, y, Images::Sword_Wound, ((frame + frameOffset) * 3) + currentPlane);

        }

    }


    // ____________________________________________________________________________________________________________________________________________________________________________________
    //
    // Render enemies ..

    for (uint8_t i = 0; i < Constants::EnemyCount; i++) {

        Enemy &enemy = world.getEnemy(i);
        
        if (enemy.getX() > 0) {

            int16_t xEnemy = enemy.getX() + world.getMiddleground() - 4;
            int16_t xEnemyItem = enemy.getItem().getX() + world.getMiddleground();
            int8_t yEnemy = yOffset - enemy.getY();
            uint8_t yEnemyItem = yOffset - enemy.getItem().getY();
            uint8_t stanceImg = getStanceImg(enemy.getStance());

            switch (enemy.getStance()) {

                case Stance::Enemy_Sword_Stationary_LH:
                case Stance::Enemy_Sword_Lunge_LH_01 ... Stance::Enemy_Sword_Lunge_LH_06:
                case Stance::Enemy_Sword_Walk_LH_01 ... Stance::Enemy_Sword_Walk_LH_04:
                case Stance::Enemy_Sword_Walk_BK_LH_01 ... Stance::Enemy_Sword_Walk_BK_LH_04:
                case Stance::Enemy_Sword_StandingJump_LH_01 ... Stance::Enemy_Sword_StandingJump_LH_07:
                    {
                        uint8_t x = FX::readIndexedUInt8(Constants::SwordLunge_Enemy, static_cast<uint16_t>(enemy.getStance()) - static_cast<uint16_t>(Stance::Enemy_Sword_Stationary_LH));
                        renderEnemyAndHealth(stanceImg, enemy.getX() + world.getMiddleground() - 4 - x, yOffset - enemy.getY(), enemy.getHealth());
                        // SpritesU::drawPlusMaskFX(enemy.getX() + world.getMiddleground() - 4 - x, yOffset - enemy.getY() - 5, Images::Health, ((Constants::HealthMax - enemy.getHealth()) * 3) + currentPlane);

                        // #ifdef RENDER_16X16_SECONDARY
                        // SpritesU::drawPlusMaskFX(enemy.getX() + world.getMiddleground() - 4 - x, yOffset - enemy.getY(), 16,16, Images::Enemy, (stanceImg * 3) + currentPlane);
                        // #else
                        // SpritesU::drawPlusMaskFX(enemy.getX() + world.getMiddleground() - 4 - x, yOffset - enemy.getY(), Images::Enemy, (stanceImg * 3) + currentPlane);
                        // #endif

                        if (enemy.getItem().getItemType() == ItemType::Glint) {
                            renderGlint(xEnemyItem - 4, yEnemyItem, enemy.getItem().getFrame());
                        }                        

                    }
                    break;

                case Stance::Enemy_Sword_Stationary_RH:
                case Stance::Enemy_Sword_Lunge_RH_01 ... Stance::Enemy_Sword_Lunge_RH_06:
                case Stance::Enemy_Sword_Walk_RH_01 ... Stance::Enemy_Sword_Walk_RH_04:
                case Stance::Enemy_Sword_Walk_BK_RH_01 ... Stance::Enemy_Sword_Walk_BK_RH_04:
                case Stance::Enemy_Sword_StandingJump_RH_01 ... Stance::Enemy_Sword_StandingJump_RH_07:
                    {
                        uint8_t x = FX::readIndexedUInt8(Constants::SwordLunge_Enemy, static_cast<uint16_t>(enemy.getStance()) - static_cast<uint16_t>(Stance::Enemy_Sword_Stationary_RH));
                        renderEnemyAndHealth(stanceImg, enemy.getX() + world.getMiddleground() - 4 - x, yOffset - enemy.getY(), enemy.getHealth());
                        // SpritesU::drawPlusMaskFX(enemy.getX() + world.getMiddleground() - 4 + x, yOffset - enemy.getY() - 5, Images::Health, ((Constants::HealthMax - enemy.getHealth()) * 3) + currentPlane);

                        // #ifdef RENDER_16X16_SECONDARY
                        // SpritesU::drawPlusMaskFX(enemy.getX() + world.getMiddleground() - 4 + x, yOffset - enemy.getY(), 16, 16, Images::Enemy, (stanceImg * 3) + currentPlane);
                        // #else
                        // SpritesU::drawPlusMaskFX(enemy.getX() + world.getMiddleground() - 4 + x, yOffset - enemy.getY(), Images::Enemy, (stanceImg * 3) + currentPlane);
                        // #endif
                        
                        if (enemy.getItem().getItemType() == ItemType::Glint) {
                            renderGlint(xEnemyItem + 15, yEnemyItem, enemy.getItem().getFrame());
                        }                        

                    }
                    break;
                    
                default:
                    {

                        #ifdef RENDER_16X16_SECONDARY
                        SpritesU::drawPlusMaskFX(xEnemy, yEnemy, Images::Enemy, 16, 16, (stanceImg * 3) + currentPlane);
                        #else
                        SpritesU::drawPlusMaskFX(xEnemy, yEnemy, Images::Enemy, (stanceImg * 3) + currentPlane);
                        #endif

                        ItemType enemyItemType = enemy.getItem().getItemType();

                        if (enemyItemType == ItemType::Arrow_RH || enemyItemType == ItemType::Arrow_LH) {
                            
                            uint8_t frame = (enemyItemType == ItemType::Arrow_LH ? 3 : 0);
                            SpritesU::drawPlusMaskFX(xEnemyItem - 4, yEnemyItem, Images::Arrow, frame + currentPlane);

                        }

                        else if ((enemyItemType >= ItemType::Trebochet_Ball_Left_1 && enemyItemType <= ItemType::Trebochet_Ball_Left_3) || 
                                 (enemyItemType >= ItemType::Trebochet_Ball_Right_1 && enemyItemType <= ItemType::Trebochet_Ball_Right_3)) {

                            SpritesU::drawPlusMaskFX(xEnemyItem - 4, yEnemyItem, Images::Trebochet_Ball, (enemy.getItem().getFrame() * 3) + currentPlane);

                        }
                        
                    }
                    break;
                
            }


            // Render Sword Wound if applicable ..

            if (enemy.getSwordWound() != 0) {

                int8_t xOffset;
                uint8_t frameOffset = 0;

                switch (player.getDirection()) {

                    case Direction::Left:
                   
                        xOffset = -1;
                        frameOffset = 4;
                        break;

                    case Direction::Right:
                        xOffset = 10;
                        break;

                }

                SpritesU::drawPlusMaskFX(xEnemy + xOffset, yEnemy + 2, Images::Sword_Wound, (((enemy.getSwordWound() / 3) + frameOffset) * 3) + currentPlane);

            }

        }

    }


    // Render a puff ?

    Item &item = world.getItem(world.getItem(ItemType::Puff));

    if (item.getFrame() < Constants::Puff_Max) {

        uint8_t frame = (item.getFrame() >> 4) + (item.getData() * 7);
        SpritesU::drawPlusMaskFX(item.getX() + world.getMiddleground() - 4, yOffset - item.getY(), Images::Item_02, (frame * 3) +  currentPlane);

    }


    // Door RHS ..

    for (uint8_t i = 0; i < Constants::ItemCount_Level; i++) {

        Item &item = world.getItem(i);

        if (item.getItemType() == ItemType::None) break;

        #ifndef DEBUG_LOCKED_DOOR
        if (item.getItemType() == ItemType::LockedDoor && item.getFrame() == 4) {

            SpritesU::drawPlusMaskFX(item.getX() + world.getMiddleground() - 4 + 11, yOffset - item.getY(), Images::Item_09a, currentPlane);

        }
        #endif

    }


    // ____________________________________________________________________________________________________________________________________________________________________________________
    //
    // Render palms, waves and foreground ..

    if (world.getWaveIdx() != Constants::NoWaves) {
        SpritesU::drawOverwriteFX(world.getWave(), 55 + yOffset - Constants::GroundY, Images::Waves, ((world.getWaveIdx() / 64) * 3) + currentPlane);
        SpritesU::drawOverwriteFX(world.getWave() + 128, 55 + yOffset - Constants::GroundY, Images::Waves, ((world.getWaveIdx() / 64) * 3) + currentPlane);
    }

    for (uint8_t i = 0; i < 2; i++) {

        uint24_t palmIdx = FX::readIndexedUInt24(Images::PalmImages, i);
        SpritesU::drawPlusMaskFX(world.getPalm(i) / 2, 10 + yOffset - Constants::GroundY, palmIdx, currentPlane);

    }


    // ____________________________________________________________________________________________________________________________________________________________________________________
    //
    // Render menu if open ..

    if (menu.getX() != 128) {

        uint8_t frame = 3;

        switch (world.getGameState()) {

            case GameState::Inventory_Open:
                    
                if (player.getItemCount() == 0) {

                    frame = 4;

                }
                else if (player.getItemCount() > 0 && player.getItemCount() <= 2) {

                    frame = 0;

                }
                else if (menu.getTop() == 0 && player.getItemCount() > 2) {
                        
                    frame = 1;

                }
                else if (menu.getTop() >= 2 && menu.getTop() + 1 == player.getItemCount()) {
                        
                    frame = 2;

                }

                SpritesU::drawPlusMaskFX(menu.getX(), 0,  Images::InventoryPanel, (frame * 3) + currentPlane);


                if (menu.getTop() == 0) {

                    for (uint8_t i = menu.getTop(); i < menu.getTop() + 4; i++) {

                        if (i <= 1) {

                            if (menu.getY() <= 1) {

                                if (world.getFrameCount() % 64 < 32) {

                                    renderInventoryPanelCursor(menu.getX() + 8, 1 + (menu.getY() << 3));

                                }

                            }

                        }
                        else {

                            InventoryItem &item = player.getItem(i - 2);
                            if (item.getItemType() == ItemType::None)   break;
                            renderItem(item.getItemType(), menu.getX() + 13, -12 + ((i - menu.getTop()) * 18));

                            if (menu.getY() >= 2 && world.getFrameCount() % 64 < 32 && player.getItemCount() > 0) {

                                uint8_t y = -13 + ((menu.getY() - menu.getTop()) * 18);
                                renderItemCursor(menu.getX() + 12, y);

                            }
                            
                        }

                    }

                }
                else {

                    for (uint8_t i = menu.getTop(); i < menu.getTop() + 3; i++) {

                        InventoryItem &item = player.getItem(i - 2);
                        if (item.getItemType() == ItemType::None)   break;

                        uint8_t y = 6 + ((i - menu.getTop()) * 18);
                        renderItem(item.getItemType(), menu.getX() + 13, y);

                    }

                    if (world.getFrameCount() % 64 < 32 && player.getItemCount() > 0) {

                        uint8_t y = 5 + ((menu.getY() - menu.getTop()) * 18);
                        renderItemCursor(menu.getX() + 12, y);

                    }
                    
                }

                break;

            case GameState::Inventory_Open_More_Reset:
            case GameState::Inventory_Open_More_Exit:

                SpritesU::drawPlusMaskFX(menu.getX(), 0, Images::InventoryPanel, ((7 + player.getHealth()) * 3) + currentPlane);
                SpritesU::drawOverwriteFX(menu.getX() + 14, 32, Images::Numbers_5x3_3D_BW, (player.getChakanas() * 3) + currentPlane);
                SpritesU::drawOverwriteFX(menu.getX() + 11, 47,  Images::Hearts, ((player.getLives() - 1) * 3) + currentPlane);

                if (world.getFrameCount() % 64 < 32) {

                    renderInventoryPanelCursor(menu.getX() + 8, 1 + (world.getGameState() == GameState::Inventory_Open_More_Reset ? 0 : 8));

                }

                break;

            default:

                frame = ((static_cast<uint8_t>(world.getGameState()) - static_cast<uint8_t>(GameState::Inventory_Open_Reset_0)) / 2) + 5;
                SpritesU::drawPlusMaskFX(menu.getX(), 0,  Images::InventoryPanel, (frame * 3) + currentPlane);

                if (world.getFrameCount() % 64 < 32) {

                    switch (world.getGameState()) {

                        case GameState::Inventory_Open_Reset_0 ... GameState::Inventory_Open_Exit_1:
                            {
                                uint8_t y = FX::readIndexedUInt8(Constants::InventoryCursorY, static_cast<uint8_t>(world.getGameState()) - static_cast<uint8_t>(GameState::Inventory_Open_Reset_0));
                                renderInventoryPanelCursor(menu.getX() + 8, y);

                            }

                            break;
                    }

                }
                
                break;

        }

    }

    #ifdef DEBUG_SWORD
    a.drawRect(playerX, playerY, 16, 6);
    a.drawRect(enemyX, enemyY, 1, 1);
    #endif

    #ifdef DEBUG_TREBOCHET
    a.drawRect(59, 0, 10, 16);
    a.drawRect(56, 13, 4, 4);
    #endif

}

uint8_t getStanceImg(Stance stance) {

    FX::seekData(Constants::StanceImgIdx + static_cast<uint16_t>(stance));
    uint8_t stanceImg = FX::readPendingUInt8();
    FX::readEnd();

    return stanceImg;

}

void renderItem(ItemType itemType, uint8_t x, uint8_t y) {

    uint24_t imageIdx = FX::readIndexedUInt24(Images::ItemsIndex, static_cast<uint8_t>(itemType));
    uint8_t imgFrame = FX::readIndexedUInt8(Images::InventoryFrame, static_cast<uint8_t>(itemType));
    SpritesU::drawPlusMaskFX(x, y, imageIdx, imgFrame + currentPlane);

}

void renderItemCursor(uint8_t x, uint8_t y) {

    SpritesU::drawPlusMaskFX(x, y, Images::Cursor, currentPlane);

}

void renderPlayerAndHealth(uint8_t stanceImg, uint8_t x, uint8_t y, uint8_t health) {

    SpritesU::drawPlusMaskFX(x, y, Images::Player, (stanceImg * 3) + currentPlane);
    SpritesU::drawPlusMaskFX(x - 1, y - 5, Images::Health, ((Constants::HealthMax - health) * 3) + currentPlane);

}

void renderEnemyAndHealth(uint8_t stanceImg, int16_t x, uint8_t y, uint8_t health) {

    SpritesU::drawPlusMaskFX(x, y - 5, Images::Health, ((Constants::HealthMax - health) * 3) + currentPlane);

    #ifdef RENDER_16X16_SECONDARY
    SpritesU::drawPlusMaskFX(x, y, 16,16, Images::Enemy, (stanceImg * 3) + currentPlane);
    #else
    SpritesU::drawPlusMaskFX(x, y, Images::Enemy, (stanceImg * 3) + currentPlane);
    #endif

}

void renderGlint(uint8_t x, uint8_t y, uint8_t frame) {

    SpritesU::drawPlusMaskFX(x, y, Images::Glint, (frame * 3) + currentPlane);

}

void renderChakanaBalance(uint8_t balance) {
                    
    SpritesU::drawOverwriteFX(menu.getX() + 15, 56, Images::Numbers_5x3_3D_BW, (balance * 3) + currentPlane);

}

void renderGamblePanel(uint8_t frame) {
    
    SpritesU::drawPlusMaskFX(menu.getX(), 0, Images::GamblePanel, (frame * 3) + currentPlane);

}

void renderInventoryPanelCursor(uint8_t x, uint8_t y) {

    SpritesU::drawPlusMaskFX(x, y, Images::InventoryPanel_Cursor, currentPlane);

}