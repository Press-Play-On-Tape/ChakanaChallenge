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


    {
        int8_t y = (yOffset - Constants::GroundY) / 4;

        for (uint8_t i = 0; i < 2; i++) {

            int16_t x = world.getBackground() + (i * 128);
            SpritesU::drawOverwriteFX(x, y - 8, Images::Background, currentPlane);    

        }

    }

    for (uint8_t i = 4; i < 8; i++) {    

        uint24_t palmIdx = FX::readIndexedUInt24(Images::PalmImages, i);
        SpritesU::drawPlusMaskFX(world.getPalm(i), 20 + yOffset - Constants::GroundY, palmIdx, currentPlane);

    }


    for (uint8_t y = 0; y < 16; y = y + 2) {

        for (uint8_t i = 18; i < Constants::Map_X_Count + 18; i = i + 2) {

            int16_t renderX = (i * 8) + world.getMiddleground() - 4;
            int16_t renderY = yOffset - (y * 8);

            if (renderY <= -16 || renderY > 64) continue;
            if (renderX <= -64 || renderX > 127) continue;

            uint8_t tile00 = world.getTile(i, y);
            uint8_t tile01 = world.getTile(i + 1, y);
            uint8_t tile10 = world.getTile(i, y + 1);
            uint8_t tile11 = world.getTile(i + 1, y + 1);

            uint24_t imgTile = 0;
            uint8_t frame = 0;

            if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Solid_Walkable && tile11 == Tiles::Solid_Walkable)                                 imgTile = Images::Crate_01;
            else if (tile00 == Tiles::Solid_2_Wide && tile01 == Tiles::Solid_2_Wide)                                                                                                            { imgTile = Images::Crate_01_02; i = i + 2; }
            else if (tile00 == Tiles::Solid_3_Wide && tile01 == Tiles::Solid_3_Wide)                                                                                                            { imgTile = Images::Crate_01_03; i = i + 4; }
            else if (tile00 == Tiles::Solid_4_Wide && tile01 == Tiles::Solid_4_Wide)                                                                                                            { imgTile = Images::Crate_01_04; i = i + 6; }

            if (imgTile == 0) {

                if (renderX <= -16 || renderX > 127) continue;

                // if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Blank && tile11 == Tiles::Blank)                                                         imgTile = Images::Crate_10;
                // else if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Spring_LH && tile11 == Tiles::Blank)                                                imgTile = Images::Crate_20;
                // else if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Blank && tile11 == Tiles::Spring_RH)                                                imgTile = Images::Crate_21;
                // else if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Blank && tile11 == Tiles::Solid_Walkable)                                           imgTile = Images::Crate_00;
                // else if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Blank && tile11 == Tiles::Solid_NonWalkable)                                     imgTile = Images::Crate_00;
                // else if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Blank && tile11 == Tiles::Solid_NonWalkable)                                     imgTile = Images::Crate_03;
                // else if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Solid_NonWalkable && tile11 == Tiles::Blank)                                        imgTile = Images::Crate_04;
                // else if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Solid_Walkable && tile11 == Tiles::Solid_Walkable)                                  imgTile = Images::Crate_05;
                // else if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Solid_Walkable && tile11 == Tiles::Blank)                                           imgTile = Images::Crate_02;
                if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Blank && tile11 == Tiles::Blank)                                                    imgTile = Images::Crate_10;
                else if (/*tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_Walkable && */ tile10 == Tiles::Spring_LH && tile11 == Tiles::Blank)                                           imgTile = Images::Crate_20;
                else if (/*tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_Walkable && */ tile10 == Tiles::Blank && tile11 == Tiles::Spring_RH)                                           imgTile = Images::Crate_21;
                else if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Blank && tile11 == Tiles::Solid_NonWalkable)                                     imgTile = Images::Crate_00;
                else if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Blank && tile11 == Tiles::Solid_NonWalkable)                                     imgTile = Images::Crate_03;
                else if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Solid_NonWalkable && tile11 == Tiles::Blank)                                        imgTile = Images::Crate_04;
                else if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Solid_Walkable && tile11 == Tiles::Solid_Walkable)                                  imgTile = Images::Crate_05;
                else if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Solid_Walkable && tile11 == Tiles::Blank)                                           imgTile = Images::Crate_02;

                // else if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Spikes && tile11 == Tiles::Spikes)                                            imgTile = Images::Spikes_Top;
                // else if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Blank && tile11 == Tiles::Solid_NonWalkable)                                  imgTile = Images::Crate_09;
                // else if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Solid_Walkable && tile11 == Tiles::Blank)                                        imgTile = Images::Crate_02;
                // else if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Blank && tile10 == Tiles::Solid_Walkable && tile11 == Tiles::Blank)                                                 imgTile = Images::Crate_06;
                else if (/*tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Spikes && */ tile11 == Tiles::Spikes)                                            imgTile = Images::Spikes_Top;
                else if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Blank && tile11 == Tiles::Solid_NonWalkable)                                  imgTile = Images::Crate_09;
                else if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Solid_Walkable && tile11 == Tiles::Blank)                                        imgTile = Images::Crate_02;
                else if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Blank && tile10 == Tiles::Solid_Walkable && tile11 == Tiles::Blank)                                                 imgTile = Images::Crate_06;


                // else if (tile00 == Tiles::Solid_Blocking && tile01 == Tiles::Solid_Blocking && tile10 == Tiles::Solid_Blocking && tile11 == Tiles::Solid_Blocking)                                  imgTile = Images::Crate_22;
                // else if (tile00 == Tiles::Blank && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Blank && tile11 == Tiles::Solid_NonWalkable)                                              imgTile = Images::Crate_07;
                // else if (tile00 == Tiles::Blank && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Blank && tile11 == Tiles::Solid_Walkable)                                                 imgTile = Images::Crate_07;
                // else if (tile00 == Tiles::Blank && tile01 == Tiles::Single_Stair_RH_Lower && tile10 == Tiles::Blank && tile11 == Tiles::Blank)                                                      imgTile = Images::Crate_11;
                // else if (tile00 == Tiles::Spikes && tile01 == Tiles::Spikes && tile10 == Tiles::Blank && tile11 == Tiles::Blank)                                                                    imgTile = Images::Spikes_Bottom;
                // else if (tile00 == Tiles::Single_Stair_LH_Lower && tile01 == Tiles::Blank && tile10 == Tiles::Blank && tile11 == Tiles::Blank)                                                      imgTile = Images::Crate_11a;
                else if (tile00 == Tiles::Solid_Blocking /*&& tile01 == Tiles::Solid_Blocking && tile10 == Tiles::Solid_Blocking && tile11 == Tiles::Solid_Blocking*/)                                  imgTile = Images::Crate_22;
                else if (tile00 == Tiles::Blank && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Blank && tile11 == Tiles::Solid_Walkable)                                                 imgTile = Images::Crate_07;
                else if (/*tile00 == Tiles::Blank && */tile01 == Tiles::Single_Stair_RH_Lower /*&& tile10 == Tiles::Blank && tile11 == Tiles::Blank*/)                                                      imgTile = Images::Crate_11;
                else if (tile00 == Tiles::Spikes /*&& tile01 == Tiles::Spikes && tile10 == Tiles::Blank && tile11 == Tiles::Blank*/)                                                                    imgTile = Images::Spikes_Bottom;
                else if (tile00 == Tiles::Single_Stair_LH_Lower /*&& tile01 == Tiles::Blank && tile10 == Tiles::Blank && tile11 == Tiles::Blank*/)                                                      imgTile = Images::Crate_11a;


                // ladders

                // else if (tile00 == Tiles::Ladder_Lower && tile01 == Tiles::Ladder_Lower && tile10 == Tiles::Ladder_Upper && tile11 == Tiles::Ladder_Upper)                                          imgTile = Images::Crate_13;
                // else if (tile00 == Tiles::Ladder_Lower && tile01 == Tiles::Ladder_Lower && tile10 == Tiles::Ladder_Middle && tile11 == Tiles::Ladder_Middle)                                        imgTile = Images::Crate_14;
                // else if (tile00 == Tiles::Ladder_Middle && tile01 == Tiles::Ladder_Middle && tile10 == Tiles::Ladder_Upper && tile11 == Tiles::Ladder_Upper)                                        imgTile = Images::Crate_15;
                // else if (tile00 == Tiles::Ladder_Middle && tile01 == Tiles::Ladder_Middle && tile10 == Tiles::Ladder_Middle && tile11 == Tiles::Ladder_Middle)                                      imgTile = Images::Crate_16;
                else if (tile00 == Tiles::Ladder_Lower  /*&& tile01 == Tiles::Ladder_Lower */ && tile10 == Tiles::Ladder_Upper  /*&& tile11 == Tiles::Ladder_Upper */)                                 imgTile = Images::Crate_13;
                else if (tile00 == Tiles::Ladder_Lower  /*&& tile01 == Tiles::Ladder_Lower */ && tile10 == Tiles::Ladder_Middle /*&& tile11 == Tiles::Ladder_Middle*/)                                 imgTile = Images::Crate_14;
                else if (tile00 == Tiles::Ladder_Middle /*&& tile01 == Tiles::Ladder_Middle*/ && tile10 == Tiles::Ladder_Upper  /*&& tile11 == Tiles::Ladder_Upper */)                                 imgTile = Images::Crate_15;
                else if (tile00 == Tiles::Ladder_Middle /*&& tile01 == Tiles::Ladder_Middle*/ && tile10 == Tiles::Ladder_Middle /*&& tile11 == Tiles::Ladder_Middle*/)                                 imgTile = Images::Crate_16;


                // Rope

                // else if (tile00 == Tiles::Rope_Support_LH && tile01 == Tiles::Blank && tile10 == Tiles::Rope_Support_LH && tile11 == Tiles::Rope)                                                imgTile = Images::Crate_17;
                // else if (tile00 == Tiles::Blank && tile01 == Tiles::Rope_Support_RH && tile10 == Tiles::Rope && tile11 == Tiles::Rope_Support_RH)                                                   imgTile = Images::Crate_18;
                // else if (tile00 == Tiles::Blank && tile01 == Tiles::Blank && tile10 == Tiles::Rope && tile11 == Tiles::Rope)                                                                        imgTile = Images::Crate_19;
                // else if (tile00 == Tiles::Rope && tile01 == Tiles::Rope && tile10 == Tiles::Blank && tile11 == Tiles::Blank)                                                                        imgTile = Images::Crate_23;
                else if (/*tile00 == Tiles::Rope_Support_LH && tile01 == Tiles::Blank && */ tile10 == Tiles::Rope_Support_LH && tile11 == Tiles::Rope)                                           imgTile = Images::Crate_17;
                else if (/*tile00 == Tiles::Blank && tile01 == Tiles::Rope_Support_RH && */ tile10 == Tiles::Rope && tile11 == Tiles::Rope_Support_RH)                                                   imgTile = Images::Crate_18;
                else if (/*tile00 == Tiles::Blank && tile01 == Tiles::Blank && */ tile10 == Tiles::Rope && tile11 == Tiles::Rope)                                                                        imgTile = Images::Crate_19;
                else if (tile00 == Tiles::Rope && tile01 == Tiles::Rope /*&& tile10 == Tiles::Blank && tile11 == Tiles::Blank*/)                                                                        imgTile = Images::Crate_23;


                // Stairs

                // else if (tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Single_Stair_RH_Upper_TL && tile11 == Tiles::Single_Stair_RH_Upper_TR)           imgTile = Images::Crate_08;
                // else if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Single_Stair_LH_Upper_TL && tile11 == Tiles::Single_Stair_LH_Upper_TR)           imgTile = Images::Crate_12;
                else if (/*tile00 == Tiles::Solid_Walkable && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Single_Stair_RH_Upper_TL && */ tile11 == Tiles::Single_Stair_RH_Upper_TR)           imgTile = Images::Crate_08;
                else if (/*tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_Walkable && tile10 == Tiles::Single_Stair_LH_Upper_TL && */ tile11 == Tiles::Single_Stair_LH_Upper_TR)           imgTile = Images::Crate_12;


                // Slide

                // else if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Blank && tile10 == Tiles::Slide_LH_Upper && tile11 == Tiles::Blank)                                                 imgTile = Images::Crate_24;
                // else if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Solid_Walkable && tile11 == Tiles::Slide_LH_Upper)                            imgTile = Images::Crate_28;
                // else if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Slide_LH_Full && tile10 == Tiles::Slide_LH_Full && tile11 == Tiles::Blank)                                          imgTile = Images::Crate_29;
                // else if (tile00 == Tiles::Blank && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Blank && tile11 == Tiles::Slide_RH_Upper)                                                 imgTile = Images::Crate_25;
                // else if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Slide_RH_Upper && tile11 == Tiles::Solid_Walkable)                            imgTile = Images::Crate_30;
                // else if (tile00 == Tiles::Slide_RH_Full && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Blank && tile11 == Tiles::Slide_RH_Full)                                          imgTile = Images::Crate_31;
                else if (/*tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Blank &&*/ tile10 == Tiles::Slide_LH_Upper && tile11 == Tiles::Blank)                                                 imgTile = Images::Crate_24;
                else if (/*tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_NonWalkable && */tile10 == Tiles::Solid_Walkable && tile11 == Tiles::Slide_LH_Upper)                            imgTile = Images::Crate_28;
                else if (/*tile00 == Tiles::Solid_NonWalkable && */tile01 == Tiles::Slide_LH_Full && tile10 == Tiles::Slide_LH_Full /*&& tile11 == Tiles::Blank*/)                                          imgTile = Images::Crate_29;
                else if (/*tile00 == Tiles::Blank && tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Blank && */ tile11 == Tiles::Slide_RH_Upper)                                                 imgTile = Images::Crate_25;
                else if (/*tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_NonWalkable && */ tile10 == Tiles::Slide_RH_Upper /*&& tile11 == Tiles::Solid_Walkable*/)                            imgTile = Images::Crate_30;
                else if (tile00 == Tiles::Slide_RH_Full /*&& tile01 == Tiles::Solid_NonWalkable && tile10 == Tiles::Blank */ && tile11 == Tiles::Slide_RH_Full)                                          imgTile = Images::Crate_31;

                // Vertical Vines

                // else if (tile00 == Tiles::Vine_Middle && tile01 == Tiles::Vine_Middle && tile10 == Tiles::Vine_Middle && tile11 == Tiles::Vine_Middle)                                              imgTile = Images::Crate_36;
                // else if (tile00 == Tiles::Vine_Lower && tile01 == Tiles::Vine_Lower && tile10 == Tiles::Vine_Middle && tile11 == Tiles::Vine_Middle)                                                imgTile = Images::Crate_37;
                // else if (tile00 == Tiles::Vine_Middle && tile01 == Tiles::Vine_Middle && tile10 == Tiles::Vine_Upper && tile11 == Tiles::Vine_Upper)                                                imgTile = Images::Crate_38;
                else if (tile00 == Tiles::Vine_Middle && tile01 == Tiles::Vine_Middle /*&& tile10 == Tiles::Vine_Middle && tile11 == Tiles::Vine_Middle*/)                                              imgTile = Images::Crate_36;
                else if (tile00 == Tiles::Vine_Lower && tile01 == Tiles::Vine_Lower /*&& tile10 == Tiles::Vine_Middle && tile11 == Tiles::Vine_Middle*/)                                                imgTile = Images::Crate_37;
                else if (tile00 == Tiles::Vine_Middle && tile01 == Tiles::Vine_Middle /*&& tile10 == Tiles::Vine_Upper && tile11 == Tiles::Vine_Upper*/)                                                imgTile = Images::Crate_38;

            }

            // Lever Portal
            // if (tile00 == 34 && tile01 == 34 && tile10 == 34 && tile11 == 34)     imgTile = Images::Crate_38; // SJH Should be commented out (no need for rendering).




            // Render image?

            if (imgTile != 0) {
                SpritesU::drawPlusMaskFX(renderX, renderY, imgTile, currentPlane);
            }
            else {


                // Rollers R then L

                frame = ((world.getFrameCount() % 24) / 6 * 3);

                if (world.isRollerTile_RH(tile00) && world.isRollerTile_RH(tile01) /*&& tile10 == Tiles::Blank && tile11 == Tiles::Blank*/) {
                    imgTile = Images::Crate_32;
                }

                else if (/*tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_NonWalkable &&*/ world.isRollerTile_RH(tile10) && world.isRollerTile_RH(tile11)) {
                    imgTile = Images::Crate_34;
                }

                else if (world.isRollerTile_LH(tile00) && world.isRollerTile_LH(tile01) /*&& tile10 == Tiles::Blank && tile11 == Tiles::Blank*/) {
                    imgTile = Images::Crate_33;
                }

                else if (/*tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_NonWalkable &&*/ world.isRollerTile_LH(tile10) && world.isRollerTile_LH(tile11)) {
                    imgTile = Images::Crate_35;
                }

                // if (world.isRollerTile_RH(tile00) && world.isRollerTile_RH(tile01) && tile10 == Tiles::Blank && tile11 == Tiles::Blank) {
                //     imgTile = Images::Crate_32;
                // }

                // else if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_NonWalkable && world.isRollerTile_RH(tile10) && world.isRollerTile_RH(tile11)) {
                //     imgTile = Images::Crate_34;
                // }

                // else if (world.isRollerTile_LH(tile00) && world.isRollerTile_LH(tile01) && tile10 == Tiles::Blank && tile11 == Tiles::Blank) {
                //     imgTile = Images::Crate_33;
                // }

                // else if (tile00 == Tiles::Solid_NonWalkable && tile01 == Tiles::Solid_NonWalkable && world.isRollerTile_LH(tile10) && world.isRollerTile_LH(tile11)) {
                //     imgTile = Images::Crate_35;
                // }

                if (imgTile != 0) {
                    SpritesU::drawPlusMaskFX(renderX, renderY, imgTile, frame + currentPlane);
                }

            }


            // Water

            if (imgTile == 0) {

                frame = ((world.getFrameCount() % 48) / 3 * 3);
                
                if (tile00 == Tiles::Water_Plain && tile01 == Tiles::Water_Plain /*&& tile10 == Tiles::Blank && tile11 == Tiles::Blank*/) {
                    imgTile = Images::Crate_39;
                }

                else if (tile00 == Tiles::Water_Bubbling_1 && tile01 == Tiles::Water_Bubbling_1 /*&& tile10 == Tiles::Blank && tile11 == Tiles::Blank*/) {
                    imgTile = Images::Crate_40;
                }

                else if (tile00 == Tiles::Water_Bubbling_2 && tile01 == Tiles::Water_Bubbling_2 /*&& tile10 == Tiles::Blank && tile11 == Tiles::Blank*/) {
                    imgTile = Images::Crate_41;
                }

                // if (tile00 == Tiles::Water_Plain && tile01 == Tiles::Water_Plain && tile10 == Tiles::Blank && tile11 == Tiles::Blank) {
                //     imgTile = Images::Crate_39;
                // }

                // else if (tile00 == Tiles::Water_Bubbling_1 && tile01 == Tiles::Water_Bubbling_1 && tile10 == Tiles::Blank && tile11 == Tiles::Blank) {
                //     imgTile = Images::Crate_40;
                // }

                // else if (tile00 == Tiles::Water_Bubbling_2 && tile01 == Tiles::Water_Bubbling_2 && tile10 == Tiles::Blank && tile11 == Tiles::Blank) {
                //     imgTile = Images::Crate_41;
                // }

                if (imgTile != 0) {
                    SpritesU::drawPlusMaskFX(renderX, renderY, imgTile, frame + currentPlane);
                }

            }

        }

    }

    for (uint8_t i = 0; i < Constants::ItemCount; i++) {

        Item &item = world.getItem(i);
        if (item.getItemType() == ItemType::Puff) break;

        int16_t renderX = item.getX() + world.getMiddleground() - 4;
        int16_t renderY = yOffset - item.getY();

        if (renderX <= -16 || renderX > 127) continue;
        if (renderY <= -16 || renderY > 127) continue;

        uint24_t imageIdx = FX::readIndexedUInt24(Images::ItemsIndex, static_cast<uint8_t>(item.getItemType()));
         
        uint8_t frame = item.getFrame();

        switch (item.getItemType()) {

            case ItemType::Key1:
            case ItemType::Anchor:
            case ItemType::PinchBar:
            case ItemType::TrapDoor:
            case ItemType::Potion:
                frame = item.getFrame() / 16;
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
            case ItemType::Chakana_Small:

                switch (item.getFrame()) {

                    case 3 ... 21:
                        frame = item.getFrame() / 3;
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

        if (imageIdx != 0) {
            
            SpritesU::drawPlusMaskFX(renderX, renderY, imageIdx, (frame * 3) + currentPlane);

        }

    }

    Stance stance = player.getStance();
    uint8_t stanceImg = getStanceImg(stance);

    switch (stance) {

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
                uint8_t frame = world.isSpringTile_LH(tile) ? 3 : 0;
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
                // uint8_t stanceImg = getStanceImg(stance);
                uint8_t x = FX::readIndexedUInt8(Constants::SwordLunge_Player, static_cast<uint8_t>(stance) - static_cast<uint8_t>(Stance::Man_Sword_Stationary_RH));
                renderPlayerAndHealth(stanceImg, 56 + x, yOffset - Constants::GroundY + player.getY(), player.getHealth(), currentPlane);
            }
            break;

        case Stance::Man_Sword_Stationary_LH:
        case Stance::Man_Sword_Lunge_LH_01 ... Stance::Man_Sword_Lunge_LH_06:
        case Stance::Man_Sword_Walk_LH_01 ... Stance::Man_Sword_Walk_LH_04:
        case Stance::Man_Sword_Walk_BK_LH_01 ... Stance::Man_Sword_Walk_BK_LH_04:
        case Stance::Man_Sword_StandingJump_LH_01 ... Stance::Man_Sword_StandingJump_LH_07:
            {
                // uint8_t stanceImg = getStanceImg(stance);
                uint8_t x = FX::readIndexedUInt8(Constants::SwordLunge_Player, static_cast<uint8_t>(stance) - static_cast<uint8_t>(Stance::Man_Sword_Stationary_LH));
                renderPlayerAndHealth(stanceImg, 56 - x, yOffset - Constants::GroundY + player.getY(), player.getHealth(), currentPlane);
            }
            break;

        default:
            {
                // uint8_t stanceImg = getStanceImg(stance);
                SpritesU::drawPlusMaskFX(56, yOffset - Constants::GroundY + player.getY(), Images::Player, (stanceImg * 3) + currentPlane);
            }
            break;
        
    }


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

    for (uint8_t i = 0; i < Constants::EnemyCount; i++) {

        Enemy &enemy = world.getEnemy(i);
        

        if (enemy.getX() > 0) {

            int16_t xEnemy = enemy.getX() + world.getMiddleground() - 4;
            int16_t xEnemyItem = enemy.getItem().getX() + world.getMiddleground();
            uint8_t yEnemy = yOffset - enemy.getY();
            uint8_t yEnemyItem = yOffset - enemy.getItem().getY();
            uint8_t stanceImg = getStanceImg(enemy.getStance());
            ItemType enemyItemType = enemy.getItem().getItemType();

            switch (enemy.getStance()) {

                case Stance::Enemy_Sword_Stationary_LH:
                case Stance::Enemy_Sword_Lunge_LH_01 ... Stance::Enemy_Sword_Lunge_LH_06:
                case Stance::Enemy_Sword_Walk_LH_01 ... Stance::Enemy_Sword_Walk_LH_04:
                case Stance::Enemy_Sword_Walk_BK_LH_01 ... Stance::Enemy_Sword_Walk_BK_LH_04:
                case Stance::Enemy_Sword_StandingJump_LH_01 ... Stance::Enemy_Sword_StandingJump_LH_07:
                    {
                        uint8_t x = FX::readIndexedUInt8(Constants::SwordLunge_Enemy, static_cast<uint8_t>(enemy.getStance()) - static_cast<uint8_t>(Stance::Enemy_Sword_Stationary_LH));
                        renderPlayerAndHealth(stanceImg, xEnemy - x, yEnemy, enemy.getHealth(), currentPlane);

                        if (enemyItemType == ItemType::Glint) {
                            renderGlint(xEnemyItem - 4, yEnemyItem, enemy.getItem().getFrame(), currentPlane);
                        }                        

                    }
                    break;

                case Stance::Enemy_Sword_Stationary_RH:
                case Stance::Enemy_Sword_Lunge_RH_01 ... Stance::Enemy_Sword_Lunge_RH_06:
                case Stance::Enemy_Sword_Walk_RH_01 ... Stance::Enemy_Sword_Walk_RH_04:
                case Stance::Enemy_Sword_Walk_BK_RH_01 ... Stance::Enemy_Sword_Walk_BK_RH_04:
                case Stance::Enemy_Sword_StandingJump_RH_01 ... Stance::Enemy_Sword_StandingJump_RH_07:
                    {
                        uint8_t x = FX::readIndexedUInt8(Constants::SwordLunge_Enemy, static_cast<uint8_t>(enemy.getStance()) - static_cast<uint8_t>(Stance::Enemy_Sword_Stationary_RH));
                        renderPlayerAndHealth(stanceImg, xEnemy - x, yEnemy, enemy.getHealth(), currentPlane);
                        
                        if (enemyItemType == ItemType::Glint) {
                            renderGlint(xEnemyItem + 15, yEnemyItem, enemy.getItem().getFrame(), currentPlane);
                        }                        

                    }
                    break;
                    
                default:
                    {
                        SpritesU::drawPlusMaskFX(xEnemy, yEnemy, Images::Enemy, (stanceImg * 3) + currentPlane);

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

                int8_t xOffset = 0;
                uint8_t frameOffset = 0;

                switch (player.getDirection()) {

                    case Direction::Left:
                   
                        xOffset = -4;
                        frameOffset = 4;
                        break;

                    case Direction::Right:
                        xOffset = 6;
                        break;

                }

                SpritesU::drawPlusMaskFX(xEnemyItem + xOffset, yEnemy + 2, Images::Sword_Wound, (((enemy.getSwordWound() / 3) + frameOffset) * 3) + currentPlane);

            }

        }

    }


    // Render a puff ?

    Item &item = world.getItem(world.getItem(ItemType::Puff));

    if (item.getFrame() < Constants::Puff_Max) {

        SpritesU::drawPlusMaskFX(item.getX() + world.getMiddleground() - 4, yOffset - item.getY(), Images::Item_02, (item.getFrame() / 16 * 3) +  currentPlane);

    }


    // Door RHS ..

    for (uint8_t i = 0; i < Constants::ItemCount; i++) {

        Item &item = world.getItem(i);

        if (item.getItemType() == ItemType::None) break;

        if (item.getItemType() == ItemType::LockedDoor && item.getFrame() == 4) {

            SpritesU::drawPlusMaskFX(item.getX() + world.getMiddleground() - 4 + 11, yOffset - item.getY(), Images::Item_09a, currentPlane);

        }

    }


    // Render waves and foreground ..

    if (world.getWaveIdx() != Constants::NoWaves) {
        SpritesU::drawOverwriteFX(world.getWave(), 55 + yOffset - Constants::GroundY, Images::Waves, ((world.getWaveIdx() / 64) * 3) + currentPlane);
        SpritesU::drawOverwriteFX(world.getWave() + 128, 55 + yOffset - Constants::GroundY, Images::Waves, ((world.getWaveIdx() / 64) * 3) + currentPlane);
    }

    if (world.getX() < 30) {
        // SpritesU::drawOverwriteFX(world.getWave(), 32, Images::Beach_LH, ((world.getWaveIdx() / 64) * 3) + currentPlane);
    }

    // Front palms  SJH should be enabled

    for (uint8_t i = 0; i < 2; i++) {
        uint24_t palmIdx = FX::readIndexedUInt24(Images::PalmImages, i);
        SpritesU::drawPlusMaskFX(world.getPalm(i) / 2, 10 + yOffset - Constants::GroundY, palmIdx, currentPlane);

    }







    // Render Menu -----------------------------------------------------------------------------------------------------

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

                                    renderInventoryPanelCursor(menu.getX() + 8, 1 + (menu.getY() * 8), currentPlane);
                                    // SpritesU::drawPlusMaskFX(menu.getX() + 8, 1 + (menu.getY() * 8), Images::InventoryPanel_Cursor, currentPlane);

                                }

                            }

                        }
                        else {

                            InventoryItem &item = player.getItem(i - 2);
                            if (item.getItemType() == ItemType::None)   break;
                            renderItem(item.getItemType(), menu.getX() + 13, -12 + ((i - menu.getTop()) * 18), currentPlane);

                            if (menu.getY() >= 2 && world.getFrameCount() % 64 < 32 && player.getItemCount() > 0) {

                                uint8_t y = -13 + ((menu.getY() - menu.getTop()) * 18);
                                renderItemCursor(menu.getX() + 12, y, currentPlane);

                            }
                            
                        }

                    }

                }
                else {

                    for (uint8_t i = menu.getTop(); i < menu.getTop() + 3; i++) {

                        InventoryItem &item = player.getItem(i - 2);
                        if (item.getItemType() == ItemType::None)   break;

                        uint8_t y = 6 + ((i - menu.getTop()) * 18);
                        renderItem(item.getItemType(), menu.getX() + 13, y, currentPlane);

                    }

                    if (world.getFrameCount() % 64 < 32 && player.getItemCount() > 0) {

                        uint8_t y = 5 + ((menu.getY() - menu.getTop()) * 18);
                        renderItemCursor(menu.getX() + 12, y, currentPlane);

                    }
                }
                break;

            case GameState::Inventory_Open_More_Reset:
            case GameState::Inventory_Open_More_Exit:

                SpritesU::drawPlusMaskFX(menu.getX(), 0,  Images::InventoryPanel, ((7 + player.getHealth()) * 3) + currentPlane);
                SpritesU::drawOverwriteFX(menu.getX() + 14, 32, Images::Numbers_5x3_3D_BW, (player.getChakanas() * 3) + currentPlane);
                SpritesU::drawOverwriteFX(menu.getX() + 11, 47,  Images::Hearts, ((player.getLives() - 1) * 3) + currentPlane);

                if (world.getFrameCount() % 64 < 32) {

                    renderInventoryPanelCursor(menu.getX() + 8, 1 + (world.getGameState() == GameState::Inventory_Open_More_Reset ? 0 : 8), currentPlane);
                    // SpritesU::drawPlusMaskFX(menu.getX() + 8, 1 + (world.getGameState() == GameState::Inventory_Open_More_Reset ? 0 : 8), Images::InventoryPanel_Cursor, currentPlane);

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
                                renderInventoryPanelCursor(menu.getX() + 8, y, currentPlane);
                                // SpritesU::drawPlusMaskFX(menu.getX() + 8, y, Images::InventoryPanel_Cursor, currentPlane);

                            }

                            break;
                    }

                    // if (world.getGameState() == GameState::Inventory_Open_Reset_0)                 y = 19;
                    // else if (world.getGameState() == GameState::Inventory_Open_Reset_1)            y = 27;
                    // else if (world.getGameState() == GameState::Inventory_Open_Reset_Exit_0)       y = 39;
                    // else if (world.getGameState() == GameState::Inventory_Open_Reset_Exit_1)       y = 47;
                    // else if (world.getGameState() == GameState::Inventory_Open_Exit_0)             y = 19;
                    // else if (world.getGameState() == GameState::Inventory_Open_Exit_1)             y = 27;

                    // if (y > 0) {
                    //     SpritesU::drawPlusMaskFX(menu.getX() + 8, y, Images::InventoryPanel_Cursor, currentPlane);
                    // }

                }
                
                break;

        }

    }

}

uint8_t getStanceImg(Stance stance) {

    FX::seekData(Constants::StanceImgIdx + static_cast<uint16_t>(stance));
    uint8_t stanceImg = FX::readPendingUInt8();
    FX::readEnd();

    return stanceImg;

}

void renderItem(ItemType itemType, uint8_t x, uint8_t y, uint8_t currentPlane) {

    uint24_t imageIdx = FX::readIndexedUInt24(Images::ItemsIndex, static_cast<uint8_t>(itemType));
    uint24_t imgFrame = FX::readIndexedUInt8(Images::InventoryFrame, static_cast<uint8_t>(itemType));
    SpritesU::drawPlusMaskFX(x, y, imageIdx, imgFrame + currentPlane);

}

void renderItemCursor(uint8_t x, uint8_t y, uint8_t currentPlane) {

    SpritesU::drawPlusMaskFX(x, y, Images::Cursor, currentPlane);

}

void renderPlayerAndHealth(uint8_t stanceImg, uint8_t x, uint8_t y, uint8_t health, uint8_t currentPlane) {

    SpritesU::drawPlusMaskFX(x, y, Images::Player, (stanceImg * 3) + currentPlane);
    SpritesU::drawPlusMaskFX(x - 1, y - 5, Images::Health, ((Constants::HealthMax - health) * 3) + currentPlane);

}

void renderGlint(uint8_t x, uint8_t y, uint8_t frame, uint8_t currentPlane) {

    SpritesU::drawPlusMaskFX(x, y, Images::Glint, (frame * 3) + currentPlane);

}

void renderChakanaBalance(uint8_t balance, uint8_t currentPlane){
                    
    SpritesU::drawOverwriteFX(menu.getX() + 15, 56, Images::Numbers_5x3_3D_BW, (balance * 3) + currentPlane);

}

void renderGamblePanel(uint8_t frame, uint8_t currentPlane) {
    
    SpritesU::drawPlusMaskFX(menu.getX(), 0, Images::GamblePanel, (frame * 3) + currentPlane);

}

void renderInventoryPanelCursor(uint8_t x, uint8_t y, uint8_t currentPlane) {

    SpritesU::drawPlusMaskFX(x, y, Images::InventoryPanel_Cursor, currentPlane);

}