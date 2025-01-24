#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"

uint8_t endOfLevel_Counter = 0;
uint8_t ignoreKeyPress = 0;

void playGame_Init() {

    Player &player = world.getPlayer();
    world.setGameState(GameState::Play_Game);
    world.setFrameCount(0);
    menu.reset();



    // Load Map Data ..
    {
        uint24_t levelStart = FX::readIndexedUInt24(Levels::Levels, world.getCurrentPort());

        for (uint8_t y = 0; y < Constants::Map_Y_Count; y++) {
                
            FX::seekDataArray(levelStart, y, 0, Constants::Map_X_Count_Full);            
            FX::readObject(world.mapData[Constants::Map_Y_Count - y - 1]);
            FX::readEnd();

        }

    }


    // Load Map Items ..
    {

        bool puffFound = false;

        uint24_t levelItemsStart = FX::readIndexedUInt24(Levels::Level_Items, world.getCurrentPort());
        FX::seekData(levelItemsStart);

        for (uint8_t i = 0; i < Constants::ItemCount; i++) {

            Item &item = world.getItem(i);

            if (!puffFound) {

                item.setItemType(static_cast<ItemType>(FX::readPendingUInt16()));

                item.setX(FX::readPendingUInt16());
                item.setY(FX::readPendingUInt16());
                item.setFrame(FX::readPendingUInt16());
                item.setData(FX::readPendingUInt16());
                item.setCounter(FX::readPendingUInt16());

                if (item.getItemType() == ItemType::Puff) {
                    puffFound = true;
                }
                
            }
            else {
                
                item.setItemType(ItemType::None);

            }

            player.getItem(i).setItemType(ItemType::None);

        }

        FX::readEnd();

    }


    // Load Map Enemies ..
    {

        uint24_t levelEnemiesStart = FX::readIndexedUInt24(Levels::Level_Enemies, world.getCurrentPort());
        FX::seekData(levelEnemiesStart);

        for (uint8_t i = 0; i < Constants::EnemyCount; i++) {

            Enemy &enemy = world.getEnemy(i);

            enemy.setEnemyType(static_cast<EnemyType>(FX::readPendingUInt16()));
            enemy.setX(FX::readPendingUInt16());
            enemy.setY(FX::readPendingUInt16());
            enemy.setStance(FX::readPendingUInt16());
            enemy.getItem().setItemType(static_cast<ItemType>(FX::readPendingUInt16()));

        }

        FX::readEnd();

    }


    // Load Player Starting Details ..
    {

        uint24_t Level_PlayerStart = FX::readIndexedUInt24(Levels::Level_PlayerStart, world.getCurrentPort());
        FX::seekData(Level_PlayerStart);

        world.setMiddleground(FX::readPendingUInt16());
        player.setY(Constants::GroundY - FX::readPendingUInt16());
        player.setStance(FX::readPendingUInt16());

        FX::readEnd();

    }

    world.setX(0);
    // world.setPalm1(-240);
    // world.setPalm2(-130);
    // world.setPalm3(0);
    // world.setPalm4(130);
    world.setPalm(0, -27);
    world.setPalm(1, 93);
    world.setPalm(2, 253);
    world.setPalm(3, 333);
    world.setPalm(4, 87);
    world.setPalm(5, 37);
    world.setPalm(6, -49);
    world.setPalm(7, -109);
    world.setWave(-87);

    world.setBackground(-29);

    player.addInventoryItem(ItemType::Sword);
    player.addInventoryItem(ItemType::Amulet);
    player.addInventoryItem(ItemType::Hammer);

    cookie.hasSavedGame = true;
    saveCookie(true);

}

void playGame_HandleGamePlay(Player &player, uint8_t pressed, uint8_t justPressed) {

    // #ifndef DEBUG

    player.stageSequence(Stance::None, Stance::None);
    Stance stance = player.getStance();
    
    if (justPressed & UP_BUTTON || pressed & UP_BUTTON) {

        switch (player.getDirection()) {

            case Direction::Backward:
                {
                    uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                    uint8_t tile_L = world.getTile_RelativeToPlayer(-1, 0);
                    uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);
                    uint8_t tile_R2 = world.getTile_RelativeToPlayer(2, 0);
                    uint8_t tile_U = world.getTile_RelativeToPlayer(0, 1);
                    uint8_t tile_U2 = world.getTile_RelativeToPlayer(0, 2);
                    uint8_t tile_RU = world.getTile_RelativeToPlayer(1, 1);
                    uint8_t tile_RU2 = world.getTile_RelativeToPlayer(1, 2);

                    if (world.isLadderTile_Upper(tile) && world.isLadderTile_Upper(tile_R)) {

                        if (justPressed & RIGHT_BUTTON || pressed & RIGHT_BUTTON) {
                            player.pushSequence(Stance::Man_ClimbLadder_BK_RH_UP_08, Stance::Man_ClimbLadder_BK_RH_UP_14);
                        }

                        else if (justPressed & LEFT_BUTTON || pressed & LEFT_BUTTON) {
                            player.pushSequence(Stance::Man_ClimbLadder_BK_LH_UP_08, Stance::Man_ClimbLadder_BK_LH_UP_14);
                        }

                        else if (stance == Stance::Man_ClimbLadder_BK_RH_UP_07 || stance == Stance::Man_ClimbLadder_BK_RH_DOWN_07) {
                            player.pushSequence(Stance::Man_ClimbLadder_BK_RH_UP_08, Stance::Man_ClimbLadder_BK_RH_UP_14);
                        }

                        else if (stance == Stance::Man_ClimbLadder_BK_LH_UP_07 || stance == Stance::Man_ClimbLadder_BK_LH_DOWN_07) {
                            player.pushSequence(Stance::Man_ClimbLadder_BK_LH_UP_08, Stance::Man_ClimbLadder_BK_LH_UP_14);
                        }

                    }
                    else if (world.isVerticalVine_Upper(tile_U) && world.isVerticalVine_Upper(tile_RU)) {

                        if ((justPressed & LEFT_BUTTON || pressed & LEFT_BUTTON) && world.isEmptyTile(tile_L)) {
                            player.setFalls(0);
                            player.pushSequence(Stance::Man_Vine_Exit_LH_01, Stance::Man_Vine_Exit_LH_08);
                        }

                        else if ((justPressed & RIGHT_BUTTON || pressed & RIGHT_BUTTON) && world.isEmptyTile(tile_R2)) {
                            player.setFalls(0);
                            player.pushSequence(Stance::Man_Vine_Exit_RH_01, Stance::Man_Vine_Exit_RH_08);
                        }

                    }
                    else if (world.isVerticalVine_Upper(tile_U2) && world.isVerticalVine_Upper(tile_RU2)) {

                        player.pushSequence(Stance::Man_ClimbLadder_BK_RH_UP_06, Stance::Man_ClimbLadder_BK_RH_UP_07);
                        player.pushSequence(Stance::Man_ClimbLadder_BK_RH_UP_06, Stance::Man_ClimbLadder_BK_RH_UP_07);

                    }
                    else if ((world.isLadderTile_Middle(tile) && world.isLadderTile_Middle(tile_R)) ||
                            (world.isVerticalVine_Middle(tile) && world.isVerticalVine_Middle(tile_R))) {

                        // Climb further up ..
                        if (stance == Stance::Man_ClimbLadder_BK_RH_UP_07 || stance == Stance::Man_ClimbLadder_BK_RH_DOWN_07) {

                            player.pushSequence(Stance::Man_ClimbLadder_BK_RH_UP_06, Stance::Man_ClimbLadder_BK_RH_UP_07);
                            player.pushSequence(Stance::Man_ClimbLadder_BK_RH_UP_06, Stance::Man_ClimbLadder_BK_RH_UP_07);
                            
                        }
                        
                        else if (stance == Stance::Man_ClimbLadder_BK_LH_UP_07 || stance == Stance::Man_ClimbLadder_BK_LH_DOWN_07) {

                            player.pushSequence(Stance::Man_ClimbLadder_BK_LH_UP_06, Stance::Man_ClimbLadder_BK_LH_UP_07);
                            player.pushSequence(Stance::Man_ClimbLadder_BK_LH_UP_06, Stance::Man_ClimbLadder_BK_LH_UP_07);
                            
                        }

                    }

                }
                break;

            case Direction::Right:
                {
                    uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                    uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);

                    if ((world.isLadderTile_Lower(tile) && world.isLadderTile_Lower(tile_R)) ||
                        (world.isVerticalVine_Lower(tile) && world.isVerticalVine_Lower(tile_R))) {

                        player.pushSequence(Stance::Man_ClimbLadder_BK_RH_UP_01, Stance::Man_ClimbLadder_BK_RH_UP_07);

                    }

                }
                break;

            case Direction::Left:
                {
                    uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                    uint8_t tile_L = world.getTile_RelativeToPlayer(-1, 0);

                    if ((world.isLadderTile_Lower(tile) && world.isLadderTile_Lower(tile_L)) ||
                        (world.isVerticalVine_Lower(tile) && world.isVerticalVine_Lower(tile_L))) {

                        player.pushSequence(Stance::Man_ClimbLadder_BK_LH_UP_01, Stance::Man_ClimbLadder_BK_LH_UP_07);

                    }

                }
                break;

            case Direction::Forward:
                {
                    uint8_t tile_L = world.getTile_RelativeToPlayer(-1, 0);
                    uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                    uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);

                    if ((world.isLadderTile_Lower(tile) && world.isLadderTile_Lower(tile_R)) ||
                        (world.isVerticalVine_Lower(tile) && world.isVerticalVine_Lower(tile_R))) {

                        player.pushSequence(Stance::Man_ClimbLadder_BK_RH_UP_01, Stance::Man_ClimbLadder_BK_RH_UP_07);

                    }
                    else if ((world.isLadderTile_Lower(tile) && world.isLadderTile_Lower(tile_L)) ||
                            (world.isVerticalVine_Lower(tile) && world.isVerticalVine_Lower(tile_L))) {

                        player.pushSequence(Stance::Man_ClimbLadder_BK_LH_UP_01, Stance::Man_ClimbLadder_BK_LH_UP_07);

                    }

                }
                break;
        }

    }

    else if (justPressed & DOWN_BUTTON || pressed & DOWN_BUTTON) {

        switch (player.getDirection()) {

            case Direction::Backward:
                {
                    uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                    uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);
                    uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                    uint8_t tile_D2 = world.getTile_RelativeToPlayer(0, -2);
                    uint8_t tile_RD = world.getTile_RelativeToPlayer(1, -1);

                    if (world.isLadderTile_Lower(tile_D) && world.isLadderTile_Lower(tile_RD)) {

                        if (justPressed & RIGHT_BUTTON || pressed & RIGHT_BUTTON) {
                            player.pushSequence(Stance::Man_ClimbLadder_BK_RH_DOWN_08, Stance::Man_ClimbLadder_BK_RH_DOWN_14);
                        }

                        else if (justPressed & LEFT_BUTTON || pressed & LEFT_BUTTON) {
                            player.pushSequence(Stance::Man_ClimbLadder_BK_LH_DOWN_08, Stance::Man_ClimbLadder_BK_LH_DOWN_14);
                        }

                        else if (stance == Stance::Man_ClimbLadder_BK_RH_UP_07 || stance == Stance::Man_ClimbLadder_BK_RH_DOWN_07) {
                            player.pushSequence(Stance::Man_ClimbLadder_BK_LH_DOWN_08, Stance::Man_ClimbLadder_BK_LH_DOWN_14);
                        }

                        else if (stance == Stance::Man_ClimbLadder_BK_LH_UP_07 || stance == Stance::Man_ClimbLadder_BK_LH_DOWN_07) {
                            player.pushSequence(Stance::Man_ClimbLadder_BK_RH_DOWN_08, Stance::Man_ClimbLadder_BK_RH_DOWN_14);
                        }
                        

                    }
                    else if (world.isVerticalVine_Lower(tile_D) && world.isVerticalVine_Lower(tile_RD)) {

                        if (world.isEmptyTile(tile_D2)) {
                            player.setFalls(0);
                            player.pushSequence(Stance::Man_Walk_FallMore_BK_01, Stance::Man_Walk_FallMore_BK_02);
                        }
                        else {
                                
                            if (justPressed & RIGHT_BUTTON || pressed & RIGHT_BUTTON) {
                                player.pushSequence(Stance::Man_ClimbLadder_BK_RH_DOWN_08, Stance::Man_ClimbLadder_BK_RH_DOWN_14);
                            }

                            else if (justPressed & LEFT_BUTTON || pressed & LEFT_BUTTON) {
                                player.pushSequence(Stance::Man_ClimbLadder_BK_LH_DOWN_08, Stance::Man_ClimbLadder_BK_LH_DOWN_14);
                            }

                            else if (stance == Stance::Man_ClimbLadder_BK_RH_UP_07 || stance == Stance::Man_ClimbLadder_BK_RH_DOWN_07) {
                                player.pushSequence(Stance::Man_ClimbLadder_BK_LH_DOWN_08, Stance::Man_ClimbLadder_BK_LH_DOWN_14);
                            }

                            else if (stance == Stance::Man_ClimbLadder_BK_LH_UP_07 || stance == Stance::Man_ClimbLadder_BK_LH_DOWN_07) {
                                player.pushSequence(Stance::Man_ClimbLadder_BK_RH_DOWN_08, Stance::Man_ClimbLadder_BK_RH_DOWN_14);
                            }

                        }
                        

                    }                            
                    else if ((world.isLadderTile_Middle(tile_D) && world.isLadderTile_Middle(tile_RD)) ||
                            (world.isVerticalVine_Middle(tile_D) && world.isVerticalVine_Middle(tile_RD))) {

                        if (stance == Stance::Man_ClimbLadder_BK_RH_UP_07 || stance == Stance::Man_ClimbLadder_BK_RH_DOWN_07) {

                            player.pushSequence(Stance::Man_ClimbLadder_BK_RH_DOWN_06, Stance::Man_ClimbLadder_BK_RH_DOWN_07);
                            player.pushSequence(Stance::Man_ClimbLadder_BK_RH_DOWN_06, Stance::Man_ClimbLadder_BK_RH_DOWN_07);
                            
                        }
                        
                        else if (stance == Stance::Man_ClimbLadder_BK_LH_UP_07 || stance == Stance::Man_ClimbLadder_BK_LH_DOWN_07) {

                            player.pushSequence(Stance::Man_ClimbLadder_BK_LH_DOWN_06, Stance::Man_ClimbLadder_BK_LH_DOWN_07);
                            player.pushSequence(Stance::Man_ClimbLadder_BK_LH_DOWN_06, Stance::Man_ClimbLadder_BK_LH_DOWN_07);
                            
                        }

                    }
                    else if (stance == Stance::Man_Rope_Start_RH_07 || stance == Stance::Man_Rope_Start_LH_07) {
                
                        player.setFalls(0);
                        player.push(Stance::Man_Walk_FallMore_BK_02);

                    }

                }
                break;

            case Direction::Right:
                {
                    uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                    uint8_t tile_RD = world.getTile_RelativeToPlayer(1, -1);

                    if ((world.isLadderTile_Upper(tile_D) && world.isLadderTile_Upper(tile_RD)) ||
                        (world.isVerticalVine_Upper(tile_D) && world.isVerticalVine_Upper(tile_RD))) {

                        player.pushSequence(Stance::Man_ClimbLadder_BK_RH_DOWN_01, Stance::Man_ClimbLadder_BK_RH_DOWN_07);

                    }

                }
                break;

            case Direction::Left:
                {
                    uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                    uint8_t tile_LD = world.getTile_RelativeToPlayer(-1, -1);

                    if ((world.isLadderTile_Upper(tile_LD) && world.isLadderTile_Upper(tile_D)) ||
                        (world.isVerticalVine_Upper(tile_LD) && world.isVerticalVine_Upper(tile_D))) {

                        player.pushSequence(Stance::Man_ClimbLadder_BK_LH_DOWN_01, Stance::Man_ClimbLadder_BK_LH_DOWN_07);

                    }

                }
                break;

            case Direction::Forward:
                {
                    uint8_t tile_LD = world.getTile_RelativeToPlayer(-1, -1);
                    uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                    uint8_t tile_RD = world.getTile_RelativeToPlayer(1, -1);

                    if ((world.isLadderTile_Upper(tile_D) && world.isLadderTile_Upper(tile_RD)) ||
                        (world.isVerticalVine_Upper(tile_D) && world.isVerticalVine_Upper(tile_RD))) {

                        player.pushSequence(Stance::Man_ClimbLadder_BK_RH_DOWN_01, Stance::Man_ClimbLadder_BK_RH_DOWN_07);

                    }

                    else if ((world.isLadderTile_Upper(tile_LD) && world.isLadderTile_Upper(tile_D)) ||
                        (world.isVerticalVine_Upper(tile_LD) && world.isVerticalVine_Upper(tile_D))) {

                        player.pushSequence(Stance::Man_ClimbLadder_BK_LH_DOWN_01, Stance::Man_ClimbLadder_BK_LH_DOWN_07);

                    }

                }
                break;

        }

    }

    else if (justPressed & LEFT_BUTTON || pressed & LEFT_BUTTON) {

        switch (player.getDirection()) {

            case Direction::Left:
                {
                
                    uint8_t tile_L = world.getTile_RelativeToPlayer(-1, 0);
                    uint8_t tile_LD = world.getTile_RelativeToPlayer(-1, -1);
                    uint8_t tile_LU = world.getTile_RelativeToPlayer(-1, 1);

                    if (world.isEmptyTile(tile_LD) && world.isEmptyTile(tile_L)) {

                        if (justPressed & A_BUTTON || pressed & A_BUTTON) { 

                            uint8_t tile_L2 = world.getTile_RelativeToPlayer(-2, 0);
                            uint8_t tile_L3 = world.getTile_RelativeToPlayer(-3, 0);
                            uint8_t tile_L2D = world.getTile_RelativeToPlayer(-2, -1);
                            uint8_t tile_L2D2 = world.getTile_RelativeToPlayer(-2, -2);
                            uint8_t tile_L3D = world.getTile_RelativeToPlayer(-3, -1);
                            uint8_t tile_L3D2 = world.getTile_RelativeToPlayer(-3, -2);

                            if (world.isVineTile_RH(tile_L) && (stance < Stance::Man_Vine_LH_01 || stance > Stance::Man_Vine_LH_20)) {

                                Item &item = world.getItem(world.getItem(ItemType::Swinging_Vine));

                                if ((item.getCounter() >= 144 && item.getCounter() < 208)) {

                                    item.setCounter(182);
                                    player.pushSequence(Stance::Man_Vine_LH_01, Stance::Man_Vine_LH_20, true);

                                }     
                                else {
                                  
                                    player.setFalls(0);
                                    player.pushSequence(Stance::Man_Walk_FallDown_LH_01, Stance::Man_Walk_FallDown_LH_06);

                                }

                            }
                            else if (world.isEmptyTile(tile_L) && world.isEmptyTile(tile_L2) && world.isEmptyTile(tile_L3) && 
                                world.isEmptyTile(tile_LD) && world.isEmptyTile(tile_L2D) && world.canWalkOnTile(tile_L3D)) {     

                                player.pushSequence(Stance::Man_WalkingJump_LH_25_01, Stance::Man_WalkingJump_LH_25_11);

                            }    
                            else if (world.isEmptyTile(tile_L) && world.isEmptyTile(tile_L2) && world.isEmptyTile(tile_L3) &&
                                    world.isEmptyTile(tile_LD) && world.isEmptyTile(tile_L2D) && world.isEmptyTile(tile_L3D) && !world.isEmptyTile(tile_L3D2)) {     

                                player.setFalls(0);
                                player.pushSequence(Stance::Man_WalkingJump_LH_1D_25_01, Stance::Man_WalkingJump_LH_1D_25_11);

                            }                     
                            else if (world.isEmptyTile(tile_L) && world.isEmptyTile(tile_L2) && world.isEmptyTile(tile_L3) &&
                                    world.isEmptyTile(tile_LD) && world.isEmptyTile(tile_L2D) && world.isEmptyTile(tile_L3D)) {     

                                if (world.isWaterTile(tile_L2D2)) {
                                    
                                    uint8_t itemIdx = world.getItem(ItemType::LifeSaver_InWater_RH, ItemType::LifeSaver_Dissolve_InWater_RH);

                                    if (itemIdx == Constants::NoItem) {

                                        player.pushSequence(Stance::Man_Die_Water_LH_02_01, Stance::Man_Die_Water_LH_02_07);
                                        player.pushSequence(Stance::Man_WalkingJump_LH_2D_25_01, Stance::Man_WalkingJump_LH_2D_25_09);

                                    }
                                    else {

                                        uint8_t tile_D2 = world.getTile_RelativeToPlayer(0, -2);

                                        if (tile_D2 == Tiles::Water_Plain) {

                                            player.pushSequence(Stance::Man_Walk_LH_03, Stance::Man_Walk_LH_04);
                                            player.pushSequence(Stance::Man_WalkingJump_LH_25_01, Stance::Man_WalkingJump_LH_25_11);
                                            player.pushSequence(Stance::Man_Walk_LH_01, Stance::Man_Walk_LH_02);

                                        }
                                        else {

                                            player.pushSequence(Stance::Man_WalkingJump_LH_25_01, Stance::Man_WalkingJump_LH_25_11);

                                        }

                                    }

                                }
                                else {
                                    player.setFalls(0);
                                    player.pushSequence(Stance::Man_WalkingJump_LH_2D_25_01, Stance::Man_WalkingJump_LH_2D_25_11);
                                }

                            }    

                        }
                        else {

                            uint8_t tile_L2 = world.getTile_RelativeToPlayer(-2, 0);
                            uint8_t tile_L3 = world.getTile_RelativeToPlayer(-3, 0);
                            uint8_t tile_L2D = world.getTile_RelativeToPlayer(-2, -1);
                            uint8_t tile_L3D = world.getTile_RelativeToPlayer(-3, -1);   
                            uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                            uint8_t tile_RU = world.getTile_RelativeToPlayer(1, 1);
                            uint8_t tile_U = world.getTile_RelativeToPlayer(0, 1);
                            uint8_t tile_LU = world.getTile_RelativeToPlayer(-1, 1);
                            uint8_t tile_L2U = world.getTile_RelativeToPlayer(-2, 1);

                            if (world.isStairTile_R_Half(tile_D) ) {

                                player.pushSequence(Stance::Man_DescendStairs_LH_Half_01, Stance::Man_DescendStairs_LH_Half_04);

                            }
                            else if (world.canWalkOnTile(tile_L2D) && world.isEmptyTile(tile_L2) && world.isEmptyTile(tile_L2U) && world.isEmptyTile(tile_U)) {

                                player.pushSequence(Stance::Man_WalkingJump_LH_2_01, Stance::Man_WalkingJump_LH_2_08);

                            }
                            else if (world.isRopeSupport(tile_RU) && world.isRopeTile(tile_U)) {

                                player.pushSequence(Stance::Man_Rope_Start_LH_01, Stance::Man_Rope_Start_LH_07);

                            } 
                            else {

                                player.setFalls(0);
                                player.pushSequence(Stance::Man_Walk_FallDown_LH_01, Stance::Man_Walk_FallDown_LH_06);

                            }

                        }

                    }
                    else {

                        uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                        uint8_t tile_U = world.getTile_RelativeToPlayer(0, 1);
                        uint8_t tile_L3D2 = world.getTile_RelativeToPlayer(-3, -2);

                        if (world.isVerticalVine_Upper(tile_L) || world.isVerticalVine_Middle(tile_L)) {
                            
                            player.setFalls(0);
                            player.pushSequence(Stance::Man_Vine_Entry_LH_01, Stance::Man_Vine_Entry_LH_08);

                        }
                        else if (world.isSlideTile_Full_RH(tile_LD) && world.canWalkOnTile(tile_L3D2)) {

                            player.setFalls(0);
                            player.pushSequence(Stance::Man_Slide_LH_Full_Land_01, Stance::Man_Slide_LH_Full_Land_13);

                        }
                        else if (world.isSlideTile_Full_RH(tile_LD) && !world.canWalkOnTile(tile_L3D2)) {

                            player.setFalls(0);
                            player.pushSequence(Stance::Man_Slide_LH_Full_01, Stance::Man_Slide_LH_Full_13);

                        }
                        else if (world.isSlideTile_Full_RH(tile_LD) && !world.isSlideTile_Full_RH(tile_L3D2)) {

                            player.setFalls(0);
                            player.pushSequence(Stance::Man_Slide_LH_Full_CanCont_01, Stance::Man_Slide_LH_Full_CanCont_12);

                        }
                        else if (world.isSlideTile_Full_RH(tile_LD) && !world.canWalkOnTile(tile_L3D2)) {

                            player.setFalls(0);
                            player.pushSequence(Stance::Man_Slide_LH_Full_01, Stance::Man_Slide_LH_Full_13);

                        }
                        else if (world.isSlideTile_RH(tile_LD)) {

                            player.setFalls(0);
                            player.pushSequence(Stance::Man_Slide_LH_01, Stance::Man_Slide_LH_11);

                        }
                        else if (world.isStairTile_L1(tile_L)) {

                            player.pushSequence(Stance::Man_ClimbStairs_LH_01, Stance::Man_ClimbStairs_LH_04);

                        }
                        else if (world.isStairTile_L_Half(tile_L)) {

                            player.pushSequence(Stance::Man_ClimbStairs_LH_Half_01, Stance::Man_ClimbStairs_LH_Half_04);

                        }
                        else if (world.isStairTile_L1(tile) || world.isStairTile_L_Half(tile)) {

                            player.pushSequence(Stance::Man_ClimbStairs_LH_05, Stance::Man_ClimbStairs_LH_08);

                        }
                        else if (world.isStairTile_R1(tile_LD) || world.isStairTile_R_Half(tile)) {  

                            player.pushSequence(Stance::Man_DescendStairs_LH_05, Stance::Man_DescendStairs_LH_08);

                        }
                        else if (world.isStairTile_R_Half(tile)) {  

                            player.pushSequence(Stance::Man_DescendStairs_LH_Half_01, Stance::Man_DescendStairs_LH_Half_04);

                        }
                        else if (world.isStairTile_R1(tile)) {  

                            player.pushSequence(Stance::Man_DescendStairs_LH_01, Stance::Man_DescendStairs_LH_04);

                        }   
#ifdef GAMBLE
                        else if (tile == Tiles::Poker || tile_L == Tiles::Poker) {

                            if (justPressed & A_BUTTON || pressed & A_BUTTON) {

                                world.setGameState(GameState::Play_Gamble_Select_Exit);

                            }
                            else if (tile_L != Tiles::Solid_Blocking && (world.canWalkPastTile(tile_L, Direction::Left) || player.getLevel() == 0)) {  

                                player.pushSequence(Stance::Man_Walk_LH_01, Stance::Man_Walk_LH_04);

                            }

                        }
    
#endif     

                        else if (tile_L != Tiles::Solid_Blocking && (world.canWalkPastTile(tile_L, Direction::Left) || player.getLevel() == 0)) {  

                            player.pushSequence(Stance::Man_Walk_LH_01, Stance::Man_Walk_LH_04);

                        }
                        else {

                            if (justPressed & A_BUTTON || pressed & A_BUTTON) {

                                if (!world.canWalkPastTile(tile_L) && world.isEmptyTile(tile_U)) {     

                                    player.pushSequence(Stance::Man_StandingJump_LH_UPandOver_01, Stance::Man_StandingJump_LH_UPandOver_06);

                                }                       
                                
                            }
                            else if (world.isStairTile_L1(tile_L) || world.isStairTile_L_Half(tile_L)) {

                                player.pushSequence(Stance::Man_ClimbStairs_LH_01, Stance::Man_ClimbStairs_LH_04);

                            }
                            else if (world.isStairTile_L2(tile_L)) {

                                player.pushSequence(Stance::Man_ClimbStairs_LH_05, Stance::Man_ClimbStairs_LH_08);

                            }

                        }       

                    }     

                }
                break;

            case Direction::Forward:
                player.push(Stance::Man_Walk_LH_00);
                break;

            case Direction::Backward:
                {
                    uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                    uint8_t tile_U = world.getTile_RelativeToPlayer(0, 1);
                    uint8_t tile_L = world.getTile_RelativeToPlayer(-1, 0);
                    uint8_t tile_LD = world.getTile_RelativeToPlayer(-1, -1);
                    uint8_t tile_L2 = world.getTile_RelativeToPlayer(-2, 0);
                    uint8_t tile_L2D = world.getTile_RelativeToPlayer(-2, -1);
                    uint8_t tile_L2U = world.getTile_RelativeToPlayer(-2, 1);
                    uint8_t tile_LU = world.getTile_RelativeToPlayer(-1, 1);
                    uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);

                    if (!world.canWalkPastTile(tile_LU) && !world.isRopeTile(tile_LU) && world.isRopeTile(tile_U)) {

                        // Do nothing ..

                    }   
                    else if ((world.isVerticalVine_Upper(tile) && world.isVerticalVine_Upper(tile_R)) ||
                            (world.isVerticalVine_Middle(tile) && world.isVerticalVine_Middle(tile_R))) {

                        if (world.isEmptyTile(tile_L)) {
                            player.setFalls(0);
                            player.pushSequence(Stance::Man_Vine_Exit_LH_01, Stance::Man_Vine_Exit_LH_08);
                        }
                        else { /* Do nothing, prevents a turn */}

                    }                            
                    else if (world.isRopeTile(tile_U) && world.isRopeTile(tile_LU) && world.isRopeSupport(tile_L2U)) {

                        player.pushSequence(Stance::Man_Rope_End_LH_01, Stance::Man_Rope_End_LH_06);

                    }   
                    else if (!world.isRopeSupport(tile_LU) && world.isRopeTile(tile_U)) {

                        player.pushSequence(Stance::Man_Rope_Start_LH_04, Stance::Man_Rope_Start_LH_07);

                    }     
                    else {

                        player.push(Stance::Man_Walk_LH_00);

                    } 

                }
                break;

            case Direction::Right:

                player.push(Stance::Man_Walk_FW_01);
                break;

        }

    }

    else if (justPressed & RIGHT_BUTTON || pressed & RIGHT_BUTTON) {

        switch (player.getDirection()) {

            case Direction::Right:
                {

                    uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);
                    uint8_t tile_RD = world.getTile_RelativeToPlayer(1, -1);

                    if (world.isEmptyTile(tile_RD) && world.isEmptyTile(tile_R)) {

                        if (justPressed & A_BUTTON || pressed & A_BUTTON) { 

                            uint8_t tile_R2 = world.getTile_RelativeToPlayer(2, 0);
                            uint8_t tile_R3 = world.getTile_RelativeToPlayer(3, 0);
                            uint8_t tile_R2D = world.getTile_RelativeToPlayer(2, -1);
                            uint8_t tile_R2D2 = world.getTile_RelativeToPlayer(2, -2);
                            uint8_t tile_R3D = world.getTile_RelativeToPlayer(3, -1);
                            uint8_t tile_R3D2 = world.getTile_RelativeToPlayer(3, -2);

                            if (world.isVineTile_LH(tile_R) && (stance < Stance::Man_Vine_RH_01 || stance > Stance::Man_Vine_RH_20)) {

                                Item &item = world.getItem(world.getItem(ItemType::Swinging_Vine));

                                if ((item.getCounter() >= 0 && item.getCounter() < 32) || (item.getCounter() >= 320 && item.getCounter() < 352)) {

                                    item.setCounter(6);
                                    player.pushSequence(Stance::Man_Vine_RH_01, Stance::Man_Vine_RH_20, true);

                                }     
                                else {

                                    player.setFalls(0);
                                    player.pushSequence(Stance::Man_Walk_FallDown_RH_01, Stance::Man_Walk_FallDown_RH_06);

                                }

                            }
                            else if (world.isEmptyTile(tile_R) && world.isEmptyTile(tile_R2) && world.isEmptyTile(tile_R3) &&
                                    world.isEmptyTile(tile_RD) && world.isEmptyTile(tile_R2D) && world.canWalkOnTile(tile_R3D)) {     

                                player.pushSequence(Stance::Man_WalkingJump_RH_25_01, Stance::Man_WalkingJump_RH_25_11);

                            }    
                            else if (world.isEmptyTile(tile_R) && world.isEmptyTile(tile_R2) && world.isEmptyTile(tile_R3) &&
                                    world.isEmptyTile(tile_RD) && world.isEmptyTile(tile_R2D) && world.isEmptyTile(tile_R3D) && !world.isEmptyTile(tile_R3D2)) {     

                                player.setFalls(0);
                                player.pushSequence(Stance::Man_WalkingJump_RH_1D_25_01, Stance::Man_WalkingJump_RH_1D_25_11);

                            }                     
                            else if (world.isEmptyTile(tile_R) && world.isEmptyTile(tile_R2) && world.isEmptyTile(tile_R3) &&
                                    world.isEmptyTile(tile_RD) && world.isEmptyTile(tile_R2D) && world.isEmptyTile(tile_R3D)) {     

                                if (world.isWaterTile(tile_R2D2)) {

                                    uint8_t itemIdx = world.getItem(ItemType::LifeSaver_InWater_RH, ItemType::LifeSaver_Dissolve_InWater_RH);

                                    if (itemIdx == Constants::NoItem) {

                                        player.pushSequence(Stance::Man_Die_Water_RH_02_01, Stance::Man_Die_Water_RH_02_07);
                                        player.pushSequence(Stance::Man_WalkingJump_RH_2D_25_01, Stance::Man_WalkingJump_RH_2D_25_09);

                                    }
                                    else {

                                        uint8_t tile_D2 = world.getTile_RelativeToPlayer(0, -2);

                                        if (tile_D2 == Tiles::Water_Plain) {
                                     
                                            player.pushSequence(Stance::Man_Walk_RH_03, Stance::Man_Walk_RH_04);
                                            player.pushSequence(Stance::Man_WalkingJump_RH_25_01, Stance::Man_WalkingJump_RH_25_11);
                                            player.pushSequence(Stance::Man_Walk_RH_01, Stance::Man_Walk_RH_02);

                                        }
                                        else {

                                            player.pushSequence(Stance::Man_WalkingJump_RH_25_01, Stance::Man_WalkingJump_RH_25_11);

                                        }

                                    }

                                }
                                else {
                                    player.setFalls(0);
                                    player.pushSequence(Stance::Man_WalkingJump_RH_2D_25_01, Stance::Man_WalkingJump_RH_2D_25_11);
                                }

                            }                     

                        }
                        else {
                   
                            uint8_t tile_U = world.getTile_RelativeToPlayer(0, 1);
                            uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                            uint8_t tile_LU = world.getTile_RelativeToPlayer(-1, 1);
                            uint8_t tile_R2U = world.getTile_RelativeToPlayer(2, 1);
                            uint8_t tile_R2 = world.getTile_RelativeToPlayer(2, 0);
                            uint8_t tile_R2D = world.getTile_RelativeToPlayer(2, -1);

                            if (world.isStairTile_L_Half(tile_D) ) {

                                player.pushSequence(Stance::Man_DescendStairs_RH_Half_01, Stance::Man_DescendStairs_RH_Half_04);

                            }
                            else if (world.canWalkOnTile(tile_R2D) && world.isEmptyTile(tile_R2) && world.isEmptyTile(tile_R2U) && world.isEmptyTile(tile_U)) {

                                player.pushSequence(Stance::Man_WalkingJump_RH_2_01, Stance::Man_WalkingJump_RH_2_08);

                            }
                            else if (world.isRopeSupport(tile_LU) && world.isRopeTile(tile_U)) {

                                player.pushSequence(Stance::Man_Rope_Start_RH_01, Stance::Man_Rope_Start_RH_07);

                            } 
                            else {

                                player.setFalls(0);
                                player.pushSequence(Stance::Man_Walk_FallDown_RH_01, Stance::Man_Walk_FallDown_RH_06);

                            }

                        }

                    }
                    else {

                        uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                        uint8_t tile_R3D2 = world.getTile_RelativeToPlayer(3, -2);

                        if (world.isVerticalVine_Upper(tile_R) || world.isVerticalVine_Middle(tile_R)) {

                            player.setFalls(0);
                            player.pushSequence(Stance::Man_Vine_Entry_RH_01, Stance::Man_Vine_Entry_RH_08);

                        }
                        else if (world.isSlideTile_Full_LH(tile_RD) && world.canWalkOnTile(tile_R3D2)) {

                            player.setFalls(0);
                            player.pushSequence(Stance::Man_Slide_RH_Full_Land_01, Stance::Man_Slide_RH_Full_Land_13);

                        }
                        else if (world.isSlideTile_Full_LH(tile_RD) && !world.isSlideTile_Full_LH(tile_R3D2)) {

                            player.setFalls(0);
                            player.pushSequence(Stance::Man_Slide_RH_Full_CanCont_01, Stance::Man_Slide_RH_Full_CanCont_12);

                        }
                        else if (world.isSlideTile_Full_LH(tile_RD) && !world.canWalkOnTile(tile_R3D2)) {

                            player.setFalls(0);
                            player.pushSequence(Stance::Man_Slide_RH_Full_01, Stance::Man_Slide_RH_Full_13);

                        }
                        else if (world.isSlideTile_LH(tile_RD)) {

                            player.setFalls(0);
                            player.pushSequence(Stance::Man_Slide_RH_01, Stance::Man_Slide_RH_11);

                        }
                        else if (world.isStairTile_R1(tile_R)) {

                            player.pushSequence(Stance::Man_ClimbStairs_RH_01, Stance::Man_ClimbStairs_RH_04);

                        }
                        else if (world.isStairTile_R_Half(tile_R)) {

                            player.pushSequence(Stance::Man_ClimbStairs_RH_Half_01, Stance::Man_ClimbStairs_RH_Half_04);

                        }
                        else if (world.isStairTile_R1(tile) || world.isStairTile_R_Half(tile)) {

                            player.pushSequence(Stance::Man_ClimbStairs_RH_05, Stance::Man_ClimbStairs_RH_08);

                        }
                        else if (world.isStairTile_L1(tile_RD) || world.isStairTile_L_Half(tile)) {  

                            player.pushSequence(Stance::Man_DescendStairs_RH_05, Stance::Man_DescendStairs_RH_08);

                        }
                        else if (world.isStairTile_L_Half(tile)) {  

                            player.pushSequence(Stance::Man_DescendStairs_RH_Half_01, Stance::Man_DescendStairs_RH_Half_04);

                        }
                        else if (world.isStairTile_L1(tile)) {  

                            player.pushSequence(Stance::Man_DescendStairs_RH_01, Stance::Man_DescendStairs_RH_04);

                        }   
#ifdef GAMBLE
                        else if (tile == Tiles::Poker || tile_R == Tiles::Poker) {

                            if (justPressed & A_BUTTON || pressed & A_BUTTON) {

                                world.setGameState(GameState::Play_Gamble_Select_Exit);

                            }
                            else if (tile_R != Tiles::Solid_Blocking && (world.canWalkPastTile(tile_R, Direction::Right) || player.getLevel() == 0)) {  

                                player.pushSequence(Stance::Man_Walk_RH_01, Stance::Man_Walk_RH_04);

                            }

                        }
    
#endif                                                         
                        else if (tile_R != Tiles::Solid_Blocking && (world.canWalkPastTile(tile_R, Direction::Right) || player.getLevel() == 0)) {  

                            player.pushSequence(Stance::Man_Walk_RH_01, Stance::Man_Walk_RH_04);

                        }
                        else {

                            if (justPressed & A_BUTTON || pressed & A_BUTTON) {

                                if (!world.canWalkPastTile(tile_R)) {     

                                    player.pushSequence(Stance::Man_StandingJump_RH_UPandOver_01, Stance::Man_StandingJump_RH_UPandOver_06);

                                }          

                            }
                            else if (world.isStairTile_R1(tile_R) || world.isStairTile_R_Half(tile_R)) {

                                player.pushSequence(Stance::Man_ClimbStairs_RH_01, Stance::Man_ClimbStairs_RH_04);

                            }
                            else if (world.isStairTile_R2(tile_R)) {

                                player.pushSequence(Stance::Man_ClimbStairs_RH_05, Stance::Man_ClimbStairs_RH_08);

                            }

                        }

                    }

                }                    
                break;

            case Direction::Forward:
                player.push(Stance::Man_Walk_RH_00);
                break;

            case Direction::Backward:
                {
                    uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                    uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);
                    uint8_t tile_U = world.getTile_RelativeToPlayer(0, 1);
                    uint8_t tile_RU = world.getTile_RelativeToPlayer(1, 1);
                    uint8_t tile_R2 = world.getTile_RelativeToPlayer(2, 0);
                    uint8_t tile_R2U = world.getTile_RelativeToPlayer(2, 1);
                    uint8_t tile_R2D = world.getTile_RelativeToPlayer(2, -1);

                    if (!world.canWalkPastTile(tile_RU) && !world.isRopeTile(tile_RU) && world.isRopeTile(tile_U)) {

                        // Do nothing ..

                    }   
                    else if ((world.isVerticalVine_Upper(tile) && world.isVerticalVine_Upper(tile_R)) ||
                            (world.isVerticalVine_Middle(tile) && world.isVerticalVine_Middle(tile_R))) {

                        if (world.isEmptyTile(tile_R2)) {
                            player.setFalls(0);
                            player.pushSequence(Stance::Man_Vine_Exit_RH_01, Stance::Man_Vine_Exit_RH_08);
                        }
                        else { /* Do nothing, prevents a turn */}

                    }
                    else if (world.isRopeTile(tile_U) && world.isRopeTile(tile_RU) && world.isRopeSupport(tile_R2U)) {

                        player.pushSequence(Stance::Man_Rope_End_RH_01, Stance::Man_Rope_End_RH_06);

                    }  
                    else if (world.isRopeTile(tile_U) && world.isRopeTile(tile_RU)) {

                        player.pushSequence(Stance::Man_Rope_Start_RH_04, Stance::Man_Rope_Start_RH_07);

                    }                                                                 
                    else {
        
                        player.push(Stance::Man_Walk_RH_00);

                    } 

                }
                break;

            case Direction::Left:
                player.push(Stance::Man_Walk_FW_01);
                break;

        }

    }

    else if (justPressed & A_BUTTON || pressed & A_BUTTON) {

        switch (player.getDirection()) {

            case Direction::Backward:

                switch (stance) {

                    case Stance::Man_ClimbLadder_BK_LH_UP_01 ... Stance::Man_ClimbLadder_BK_LH_UP_14:
                    case Stance::Man_ClimbLadder_BK_RH_UP_01 ... Stance::Man_ClimbLadder_BK_RH_UP_14:
                    case Stance::Man_ClimbLadder_BK_LH_DOWN_01 ... Stance::Man_ClimbLadder_BK_LH_DOWN_14:
                    case Stance::Man_ClimbLadder_BK_RH_DOWN_01 ... Stance::Man_ClimbLadder_BK_RH_DOWN_14:   
                    case Stance::Man_Rope_Start_LH_01 ... Stance::Man_Rope_Start_LH_07:
                    case Stance::Man_Rope_End_LH_01 ... Stance::Man_Rope_End_LH_06:
                    case Stance::Man_Rope_Start_RH_01 ... Stance::Man_Rope_Start_RH_07:
                    case Stance::Man_Rope_End_RH_01 ... Stance::Man_Rope_End_RH_06:
                        break;

                    default:

                        player.stageSequence(Stance::Man_StandingJump_BK_01, Stance::Man_StandingJump_BK_07); 
                        break;
                    
                }

                break;

            case Direction::Right:

                
                {
#ifdef GAMBLE
                    uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                    uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);

                    if (tile == Tiles::Poker || tile_R == Tiles::Poker) {

                        if (justPressed & A_BUTTON) {

                            world.setGameState(GameState::Play_Gamble_Select_Exit);

                        }

                    }
                    else {
                        playGame_HandleGamePlay_Basics(player, Stance::Man_Start);
                    }
    
#else   
                        playGame_HandleGamePlay_Basics(player, Stance::Man_Start);
   
#endif                    
                }                
                break;

            case Direction::Forward:
                {
                    uint8_t tile = world.getTile_RelativeToPlayer(0, 0);

                    if (tile == 0) {

                        player.stageSequence(Stance::Man_StandingJump_FW_01, Stance::Man_StandingJump_FW_07); 

                    }
                    else {

                        player.stageSequence(Stance::Man_StandingJump_FW_UP_01, Stance::Man_StandingJump_FW_UP_06); 

                    }

                }
                break;

            case Direction::Left:
                {
#ifdef GAMBLE
                    uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
                    uint8_t tile_L = world.getTile_RelativeToPlayer(-1, 0);

                    if (tile == Tiles::Poker || tile_L == Tiles::Poker) {

                        if (justPressed & A_BUTTON) {

                            world.setGameState(GameState::Play_Gamble_Select_Exit);

                        }

                    }
                    else {
                        playGame_HandleGamePlay_Basics(player, Stance::Man_LH_Start - Stance::Man_RH_Start);
                    }
    
#else   
                    playGame_HandleGamePlay_Basics(player, Stance::Man_LH_Start - Stance::Man_RH_Start);
   
#endif                    
                }
                break;

        }

    }

    // #endif
}

void playGame_HandleGamePlay_Basics(Player &player, Stance stanceOffset) {

    uint8_t tile = world.getTile_RelativeToPlayer(0, 0);
    uint8_t tile_U = world.getTile_RelativeToPlayer(0, 2);

    if (world.isEmptyTile(tile_U)) {

        if (world.canJumpUpOntoTile(tile)) {

            player.stageSequence(Stance::Man_StandingJump_RH_UP_01 + stanceOffset, Stance::Man_StandingJump_RH_UP_06 + stanceOffset); 

            if (tile == Tiles::Rollers_Left) {

                player.pushSequence(Stance::Man_Rollers_RH_01, Stance::Man_Rollers_RH_04);
                player.stageSequence(Stance::Man_StandingJump_RH_UP_01 + stanceOffset, Stance::Man_StandingJump_RH_UP_06 + stanceOffset); 

            }
            else if (tile == Tiles::Rollers_Right) {

                player.pushSequence(Stance::Man_Rollers_LH_01, Stance::Man_Rollers_LH_04);
                player.stageSequence(Stance::Man_StandingJump_RH_UP_01 + stanceOffset, Stance::Man_StandingJump_RH_UP_06 + stanceOffset); 

            }

            else {

                player.stageSequence(Stance::Man_StandingJump_RH_UP_01 + stanceOffset, Stance::Man_StandingJump_RH_UP_06 + stanceOffset); 

            }

        }
        else if (world.isSpringTile(tile)) {    

            uint8_t tile_3U = world.getTile_RelativeToPlayer(0, 3);
            uint8_t tile_4U = world.getTile_RelativeToPlayer(0, 4);

            if (world.isRopeTile(tile_3U)) {

                player.stageSequence(Stance::Man_BounceJump_RH_33 + stanceOffset, Stance::Man_BounceJump_RH_34 + stanceOffset);
                player.stageSequence(Stance::Man_BounceJump_RH_01 + stanceOffset, Stance::Man_BounceJump_RH_30 + stanceOffset);

            }
            else if (world.isRopeTile(tile_4U)) {

                player.stageSequence(Stance::Man_BounceJump_RH_01 + stanceOffset, Stance::Man_BounceJump_RH_34 + stanceOffset);

            }

        }   
        else {

            player.stageSequence(Stance::Man_StandingJump_RH_01 + stanceOffset, Stance::Man_StandingJump_RH_07 + stanceOffset); 

        }

    }
    else {

        player.stageSequence(Stance::Man_StandingJump_Small_RH_01 + stanceOffset, Stance::Man_StandingJump_Small_RH_03 + stanceOffset); 

    }

}


void playGame_HandleJump(Player &player, uint8_t pressed, uint8_t justPressed) {

    Stance stance = player.getStance();

    if (pressed & A_BUTTON) {

        switch (stance) {

            case Stance::Man_Walk_RH_01:
                {
                    uint8_t tile_D2 = world.getTile_RelativeToPlayer(0, -2);
                    uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);
                    uint8_t tile_RU = world.getTile_RelativeToPlayer(1, 1);
                    uint8_t tile_RD = world.getTile_RelativeToPlayer(1, -1);
                    uint8_t tile_R2D = world.getTile_RelativeToPlayer(2, -1);

                    if (tile_D2 == Tiles::Water_Plain) {

                        // Do nothing ..

                    }
                    else if (world.canJumpUpOntoTile(tile_R)) {

                        player.pushSequence(Stance::Man_WalkingJump_RH_UP_01, Stance::Man_WalkingJump_RH_UP_05, true); 

                    }
                    else if (world.isPunjiTile(tile_R)) {

                        player.pushSequence(Stance::Man_WalkingJump_RH_25_02, Stance::Man_WalkingJump_RH_25_11, true); 

                    }     
                    else if (world.canWalkPastTile(tile_R) && world.canWalkOnTile(tile_R2D)) {

                        player.pushSequence(Stance::Man_WalkingJump_RH_2_02, Stance::Man_WalkingJump_RH_2_08, true); 

                    }
                    else {

                        player.pushSequence(Stance::Man_WalkingJump_RH_02, Stance::Man_WalkingJump_RH_08, true); 

                    }

                }
                break;

            case Stance::Man_Rollers_RH_01:
            case Stance::Man_Rollers_Stand_RH_01:
            case Stance::Man_Rollers_Fall_RH_01:
                {
                    uint8_t tile_R = world.getTile_RelativeToPlayer(1, 0);
                    uint8_t tile_RD = world.getTile_RelativeToPlayer(1, -1);
                    uint8_t tile_R2D = world.getTile_RelativeToPlayer(2, -1);
                    uint8_t tile_R3D = world.getTile_RelativeToPlayer(3, -1);

                    if (world.isEmptyTile(tile_R) && world.isEmptyTile(tile_RD) && world.isEmptyTile(tile_R2D) && world.canWalkOnTile(tile_R3D)) {

                        player.pushSequence(Stance::Man_WalkingJump_RH_25_02, Stance::Man_WalkingJump_RH_25_11, true); 

                    }     
                    else if (world.isEmptyTile(tile_R) && world.canWalkOnTile(tile_RD) && world.canWalkOnTile(tile_R3D)) {

                        player.pushSequence(Stance::Man_WalkingJump_RH_2_02, Stance::Man_WalkingJump_RH_2_08, true); 

                    }     

                }
                break;

            case Stance::Man_Walk_LH_01:
                {                            
                    uint8_t tile_D2 = world.getTile_RelativeToPlayer(0, -2);
                    uint8_t tile_L = world.getTile_RelativeToPlayer(-1, 0);
                    uint8_t tile_LD = world.getTile_RelativeToPlayer(-1, -1);
                    uint8_t tile_L2D = world.getTile_RelativeToPlayer(-2, -1);

                    if (tile_D2 == Tiles::Water_Plain) {

                        // Do nothing ..

                    }
                    else if (world.canJumpUpOntoTile(tile_L)) {

                        player.pushSequence(Stance::Man_WalkingJump_LH_UP_01, Stance::Man_WalkingJump_LH_UP_05, true); 

                    }
                    else if (world.isPunjiTile(tile_L)) {

                        player.pushSequence(Stance::Man_WalkingJump_LH_25_02, Stance::Man_WalkingJump_LH_25_11, true); 

                    }
                    else if (world.canWalkPastTile(tile_L) && world.canWalkOnTile(tile_L2D)) {

                        player.pushSequence(Stance::Man_WalkingJump_LH_2_02, Stance::Man_WalkingJump_LH_2_08, true); 

                    }
                    else {

                        player.pushSequence(Stance::Man_WalkingJump_LH_02, Stance::Man_WalkingJump_LH_08, true); 

                    }

                }
                
                break;

            case Stance::Man_Rollers_LH_01:
            case Stance::Man_Rollers_Stand_LH_01:
            case Stance::Man_Rollers_Fall_LH_01:
                {
                    uint8_t tile_L = world.getTile_RelativeToPlayer(-1, 0);
                    uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                    uint8_t tile_LD = world.getTile_RelativeToPlayer(-1, -1);
                    uint8_t tile_L2D = world.getTile_RelativeToPlayer(-2, -1);

                    if (world.isEmptyTile(tile_L) && world.isEmptyTile(tile_D) && world.isEmptyTile(tile_LD) && world.canWalkOnTile(tile_L2D)) {

                        player.pushSequence(Stance::Man_WalkingJump_LH_25_02, Stance::Man_WalkingJump_LH_25_11, true); 

                    }     
                    else if (world.isEmptyTile(tile_L) && world.canWalkOnTile(tile_D) && world.canWalkOnTile(tile_LD)) {

                        player.pushSequence(Stance::Man_WalkingJump_LH_2_02, Stance::Man_WalkingJump_LH_2_08, true); 

                    }     

                }
                break;

            default:
                break;

        }

    }

}

void playGame_HandleSwordFight_Player(Player &player, uint8_t pressed, uint8_t justPressed) {

     int16_t dist = getDistanceBetween(player, EnemyType::SwordFighter);

    if (justPressed & A_BUTTON || pressed & A_BUTTON) {

        switch (player.getDirection()) {

            case Direction::Left:

                player.pushSequence(Stance::Man_Sword_StandingJump_LH_01, Stance::Man_Sword_StandingJump_LH_07);
                break;

            case Direction::Right:

                player.pushSequence(Stance::Man_Sword_StandingJump_RH_01, Stance::Man_Sword_StandingJump_RH_07);
                break;

        }

    }

    else if (justPressed & DOWN_BUTTON || pressed & DOWN_BUTTON) {

        world.setGameState(GameState::Play_Game);
        player.setStance(Stance::Man_Walk_RH_00);

    }

    else if (justPressed & B_BUTTON || pressed & B_BUTTON) {

        switch (player.getDirection()) {

            case Direction::Left:

                player.pushSequence(Stance::Man_Sword_Lunge_LH_01, Stance::Man_Sword_Lunge_LH_06);
                break;

            case Direction::Right:

                player.pushSequence(Stance::Man_Sword_Lunge_RH_01, Stance::Man_Sword_Lunge_RH_06);
                break;

        }

    }

    else if (justPressed & RIGHT_BUTTON || pressed & RIGHT_BUTTON) {

        switch (player.getDirection()) {

            case Direction::Left:
                
                if (dist > 0) {
                    player.pushSequence(Stance::Man_Sword_Walk_BK_LH_01, Stance::Man_Sword_Walk_BK_LH_02);
                }
                else {
                    player.push(Stance::Man_Sword_Stationary_RH);            
                }

                break;

            case Direction::Right:

                player.pushSequence(Stance::Man_Sword_Walk_RH_01, Stance::Man_Sword_Walk_RH_02);
                break;
                
        }

        

    }

    else if (justPressed & LEFT_BUTTON || pressed & LEFT_BUTTON) {

        switch (player.getDirection()) {

            case Direction::Left:

                player.pushSequence(Stance::Man_Sword_Walk_LH_01, Stance::Man_Sword_Walk_LH_02);
                break;

            case Direction::Right:

                if (dist < 0) {
                    player.pushSequence(Stance::Man_Sword_Walk_BK_RH_01, Stance::Man_Sword_Walk_BK_RH_02);
                }
                else {
                    player.push(Stance::Man_Sword_Stationary_LH);            
                }

                break;
                
        }

    }

}


void playGame_Update(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {
    
    Player &player = world.getPlayer();

    world.incFrameCount();
        
    if (world.getFrameCount() % 4 == 0) {
    
        uint8_t pressed = getPressedButtons();
        uint8_t justPressed = getJustPressedButtons();

        if (player.isEmpty()) {

            switch (world.getGameState()) {
                
                case GameState::Inventory_Open:

                    if (justPressed & B_BUTTON) {
                        playGame_HandleMenu();
                    }
                    else {
                        playGame_HandleMenu(player, pressed, justPressed);
                    }

                    break;
                
                case GameState::Inventory_Open_More_Reset:
                case GameState::Inventory_Open_More_Exit:
                case GameState::Inventory_Open_Exit_0:
                case GameState::Inventory_Open_Exit_1:
                case GameState::Inventory_Open_Reset_0:
                case GameState::Inventory_Open_Reset_1:
                case GameState::Inventory_Open_Reset_Exit_0:
                case GameState::Inventory_Open_Reset_Exit_1:

                    if (justPressed & B_BUTTON) {
                        world.setGameState(GameState::Inventory_Open);
                    }
                    else {
                        playGame_HandleMenu(player, pressed, justPressed);
                    }

                    break;

                case GameState::Play_Game:

                    if (justPressed & B_BUTTON) {
                        playGame_HandleMenu();
                    }
                    else {

                        if (ignoreKeyPress == 0) {
                            playGame_HandleGamePlay(player, pressed, justPressed);          
                        }

                    }

                    break;

                case GameState::Chakana_Open:

                    if (justPressed & A_BUTTON || justPressed & B_BUTTON) {
                        player.setChakanas(player.getChakanas() + titleCounter);
                        world.setGameState(GameState::Map_Init);
                        world.setPortVisited(world.getCurrentPort());
                    }

                    break;

                case GameState::Play_Dead:

                    if (justPressed & A_BUTTON || justPressed & B_BUTTON) {

                        if (player.getLives() > 1) {

                            FX::loadGameState((uint8_t*)&cookie, sizeof(cookie));
                            player.setHealth(Constants::HealthMax);
                            player.setLives(player.getLives() - 1);

                        }
                        else {

                            cookie.hasSavedGame = false;
                            world.setGameState(GameState::Title_Init);

                        }

                        saveCookie(true);

                    }

                    break;

                case GameState::Play_Battle:

                    playGame_HandleSwordFight_Player(player, pressed, justPressed);          
                    break;

                #ifdef GAMBLE
                case GameState::Play_Gamble_Select_Exit ... GameState::Play_Gamble_End:
                    playGame_HandleGamble(player, pressed, justPressed);
                    pressed = 0;
                    justPressed = 0;
                    break;
                #endif

            }

        }
        else {

            switch (world.getGameState()) {

                case GameState::Play_Game:
                    playGame_HandleJump(player, pressed, justPressed);
                    break;

            }

        }

        if (!player.isEmpty() || player.hasStagedSequence()) {

            Point offset;
            uint16_t stance = player.getStance();;

            if (!player.isEmpty()) {

                stance = playGame_PopEntry(player);

            }


            // Has the player collided with an item?

            uint8_t yOffset = Constants::GroundY;
            if (player.getY() < 5) yOffset = Constants::GroundY - player.getY();
            Rect playerRect = { 59, yOffset - Constants::GroundY + player.getY(), 10, 16 };

            for (uint8_t i = 0; i < Constants::ItemCount; i++) {
          
                Item &item = world.getItem(i);

                
                // Can we skip this one?

                if (item.getItemType() == ItemType::MysteryCrate && item.getFrame() == 8) continue;


                // If the item is the 'puff' then we are at the last of the items, stop iterating ..

                if (item.getItemType() == ItemType::Puff) break;


                // Otherwise check if we have collided ..

                Rect itemRect = { item.getX() + world.getMiddleground() - 4 + 1, yOffset - item.getY() + 1, 14, 14 };
                Item &puff = world.getItem(world.getItem(ItemType::Puff));

                switch (item.getItemType()) {

                    case ItemType::Chakana_Small:

                        if (collide(playerRect, itemRect)) {

                            if (item.getCounter() == 0) {

                                puff.setX(item.getX());
                                puff.setY(item.getY());
                                puff.setFrame(0);
                                item.setCounter(3);
                                player.setChakanas(player.getChakanas() + item.getData());

                            }

                        }
                        break;

                    case ItemType::Key1:
                    case ItemType::PinchBar:
                    case ItemType::Hammer:
                    case ItemType::Amulet:
                    case ItemType::Potion:
                    case ItemType::Anchor:
                    case ItemType::Sword:
                    case ItemType::LifeSaver:
                    case ItemType::LifeSaver_Dissolve:

                        if (collide(playerRect, itemRect)) {

                            if (item.getCounter() == 0) {

                                puff.setX(item.getX());
                                puff.setY(item.getY());
                                puff.setFrame(0);
                                item.setCounter(3);

                            }

                        }
                        break;

                    case ItemType::Chakana:

                        if (collide(playerRect, itemRect) &&  world.getGameState() != GameState::Chakana_Open) {                        

                            ignoreKeyPress = 16;
                            player.stageSequence(Stance::None, Stance::None);

                            world.setGameState(GameState::Chakana_Open);
                            endOfLevel_Counter = 0;
                            titleCounter = a.randomLFSR(15, 30);
                            
                        }
                        break;

                    case ItemType::Lever_LH:
                    case ItemType::Lever_RH:

                        if (collide(playerRect, itemRect) && (justPressed & A_BUTTON)) {                        

                            ignoreKeyPress = 16;
                            player.stageSequence(Stance::None, Stance::None);

                            if (item.getItemType() == ItemType::Lever_LH)  {

                                item.setItemType(ItemType::Lever_RH);

                            }
                            else {

                                item.setItemType(ItemType::Lever_LH);

                            }

                            for (uint8_t x = 0; x < 15; x++) {

                                if (item.getData() & (1<<x)) {

                                    Item &item2 = world.getItem(i + x + 1);

                                    switch (item2.getItemType()) {

                                        case ItemType::Lever_Portal_Closed:
                                        case ItemType::Lever_Portal_Auto_Closed:
                                            item2.setFrame(1);
                                            item2.setCounter(0);
                                            break;

                                        default:
                                            item2.setFrame(8);
                                            item2.setCounter(0);
                                            break;

                                    }

                                }

                            }
                            
                        }
                        break;

                    case ItemType::Punji:
                                
                        switch (player.getDirection()) {

                            case Direction::Left:
                                playerRect.width = 4;
                                break;

                            case Direction::Right:
                                playerRect.x = playerRect.x + 8;
                                playerRect.width = playerRect.width - 8;
                                break;

                        }

                        itemRect = { item.getX() + world.getMiddleground() - 4 + 4, yOffset - item.getY() + 14, 8, 2 };

                        if (item.getCounter() == 0 && collide(playerRect, itemRect)) {

                            item.setCounter(1);

                            switch (player.getDirection()) {

                                case Direction::Left:
                                    player.pushSequence(Stance::Man_Die_Fall_LH_01, Stance::Man_Die_Fall_LH_04, true);
                                    break;

                                case Direction::Right:
                                    player.pushSequence(Stance::Man_Die_Fall_RH_01, Stance::Man_Die_Fall_RH_04, true);
                                    break;

                            }

                        }

                        break;

                    case ItemType::Flame:
                        
                        itemRect = { item.getX() + world.getMiddleground() - 4 + 4, yOffset - item.getY() + 14, 8, 2 };

                        if (collide(playerRect, itemRect)) {

                            switch (player.getDirection()) {

                                case Direction::Left:

                                    switch (stance) {

                                        case Stance::Man_WalkingJump_LH_2_08:
                                            {
                                                uint8_t xPos = item.getX() + world.getMiddleground();

                                                if (xPos == 56) {

                                                    player.pushSequence(Stance::Man_Die_Fire_LH_01, Stance::Man_Die_Fire_LH_12, true);
                                                    player.push(Stance::Man_Die_Fire_Adj_LH_02);

                                                }
                                                else if (xPos == 64) {

                                                    player.pushSequence(Stance::Man_Die_Fire_LH_01, Stance::Man_Die_Fire_LH_12, true);
                                                    player.push(Stance::Man_Die_Fire_Adj_LH_01);

                                                }

                                            }
                                            break;

                                        case Stance::Man_Walk_LH_02:

                                            player.pushSequence(Stance::Man_Die_Fire_LH_01, Stance::Man_Die_Fire_LH_12, true);
                                            player.pushSequence(Man_Walk_LH_03, Stance::Man_Walk_LH_06);

                                            break;


                                    }

                                    break;

                                case Direction::Right:

                                    switch (stance) {

                                        case Stance::Man_WalkingJump_RH_2_08:
                                            {
                                                uint8_t xPos = item.getX() + world.getMiddleground();

                                                if (xPos == 56) {

                                                    player.pushSequence(Stance::Man_Die_Fire_RH_01, Stance::Man_Die_Fire_RH_12, true);
                                                    player.push(Stance::Man_Die_Fire_Adj_RH_01);

                                                }
                                                else if (xPos == 64) {

                                                    player.pushSequence(Stance::Man_Die_Fire_RH_01, Stance::Man_Die_Fire_RH_12, true);
                                                    player.push(Stance::Man_Die_Fire_Adj_RH_02);

                                                }

                                            }
                                            break;

                                        case Stance::Man_Walk_RH_03:

                                            player.pushSequence(Stance::Man_Die_Fire_RH_01, Stance::Man_Die_Fire_RH_12, true);
                                            player.pushSequence(Man_Walk_RH_04, Stance::Man_Walk_RH_06);

                                            break;

                                    }

                                    break;

                            }

                        }

                        break;

                    default:
                        break;

                }

            }


            // If a sequence has been staged then commit it now (and adjust the players position etc ..

            if (player.commitSequence()) {

                stance = playGame_PopEntry(player);

            }


            // Handle falling and other special actions ..

            switch (static_cast<Stance>(stance)) {

                case Stance::Man_Walk_RH_04:
                case Stance::Man_Walk_LH_04:
                case Stance::Man_WalkingJump_LH_08:
                case Stance::Man_WalkingJump_RH_08:
                case Stance::Man_Rollers_RH_04:
                case Stance::Man_Rollers_LH_04:
                case Stance::Man_WalkingJump_LH_25_11:
                case Stance::Man_WalkingJump_RH_25_11:
                case Stance::Man_WalkingJump_LH_2_08:
                case Stance::Man_WalkingJump_RH_2_08:
                    {
                  
                        uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                        uint8_t tile_RD = world.getTile_RelativeToPlayer(1, -1);
                        uint8_t tile_LD = world.getTile_RelativeToPlayer(-1, -1);

                        if (world.isRollerTile_RH(tile_D) && world.isRollerTile_RH(tile_RD)) {

                            player.pushSequence(Stance::Man_Rollers_RH_01, Stance::Man_Rollers_RH_04);

                        }
                        else if (world.isRollerTile_LH(tile_D) && world.isRollerTile_LH(tile_LD)) {

                            player.pushSequence(Stance::Man_Rollers_LH_01, Stance::Man_Rollers_LH_04);

                        }

                        else if (world.isRollerTile_RH(tile_D) && world.canWalkOnTile(tile_RD)) {

                            player.pushSequence(Stance::Man_Rollers_Stand_RH_01, Stance::Man_Rollers_Stand_RH_04);

                        }
                        else if (world.isRollerTile_LH(tile_D) && world.canWalkOnTile(tile_LD)) {

                            player.pushSequence(Stance::Man_Rollers_Stand_LH_01, Stance::Man_Rollers_Stand_LH_04);

                        }

                        else if (world.isRollerTile_RH(tile_D) && world.isEmptyTile(tile_RD)) {

                            player.setFalls(0);
                            player.pushSequence(Stance::Man_Rollers_Fall_RH_01, Stance::Man_Rollers_Fall_RH_04);

                        }
                        else if (world.isRollerTile_LH(tile_D) && world.isEmptyTile(tile_LD)) {

                            player.setFalls(0);
                            player.pushSequence(Stance::Man_Rollers_Fall_LH_01, Stance::Man_Rollers_Fall_LH_04);
                            
                        }

                    }
                    break;

                case Stance::Man_Walk_FallMore_BK_02:
                    {
                           
                        uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                        uint8_t tile_D2 = world.getTile_RelativeToPlayer(0, -2);
  
                        if (world.isEmptyTile(tile_D) || world.isSpringTile(tile_D)) {

                            player.incFalls();

                            if (world.isEmptyTile(tile_D2) || world.isSpringTile(tile_D2)) {    
                            
                                player.pushSequence(Stance::Man_Walk_FallMore_BK_01, Stance::Man_Walk_FallMore_BK_02); 

                            }
                            else {

                                if (player.getFalls() >= 3) {

                                    if (world.isSpringTile(tile_D)) {
                                    
                                        player.pushSequence(Stance::Man_Walk_FallLandSpring_BK_01, Stance::Man_Walk_FallLandSpring_BK_28);
                                    }
                                    else {

                                        player.pushSequence(Stance::Man_Die_Fall_RH_01, Stance::Man_Die_Fall_RH_04); 
                                        player.pushSequence(Stance::Man_Walk_FallLand_BK_01, Stance::Man_Walk_FallLand_BK_04);

                                    }

                                }
                                else if (world.isSpringTile(tile_D)) {

                                    player.pushSequence(Stance::Man_Walk_FallLandSpring_BK_01, Stance::Man_Walk_FallLandSpring_BK_28);

                                }                                
                                else if (world.isSpikeTile(tile_D)) {

                                    player.pushSequence(Stance::Man_Die_Fall_RH_01, Stance::Man_Die_Fall_RH_04); 
                                    player.pushSequence(Stance::Man_Walk_FallLand_BK_01, Stance::Man_Walk_FallLand_BK_04);

                                }
                                else if (world.isWaterTile(tile_D)) {

///SJH Need graphics for this!
                                    player.pushSequence(Stance::Man_Die_Fall_RH_01, Stance::Man_Die_Fall_RH_04); 
                                    player.pushSequence(Stance::Man_Walk_FallLand_BK_01, Stance::Man_Walk_FallLand_BK_04);

                                }
                                else {

                                    if (world.getMiddleground() % 8 == 4 || world.getMiddleground() % 8 == -4) {

                                        player.pushSequence(Stance::Man_Walk_RH_03, Stance::Man_Walk_RH_04);

                                    }

                                    player.pushSequence(Stance::Man_Walk_FallLand_BK_01, Stance::Man_Walk_FallLand_BK_04);
    
                                } 

                            }

                        }
                        else {

                            player.setStance(Stance::Man_Walk_RH_02); 

                        }

                    }
                    break;

                case Stance::Man_Slide_RH_Full_Cont_08:       
                case Stance::Man_Slide_RH_Full_CanCont_12:       
                case Stance::Man_Slide_RH_Full_CanCont_13:       
                case Stance::Man_Slide_RH_Full_13:       
                    {
                        uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                        uint8_t tile_RD2 = world.getTile_RelativeToPlayer(1, -2);

                        if (tile_D == Tiles::Slide_LH_Full && tile_RD2 == Tiles::Slide_LH_Full) {

                            player.clear();
                            player.pushSequence(Stance::Man_Slide_RH_Full_Cont_01, Stance::Man_Slide_RH_Full_Cont_08);
                            break;

                        }

                    }

                    [[fallthrough]];

                case Stance::Man_Walk_FallDown_RH_06:
                case Stance::Man_Walk_FallMore_RH_02:
                case Stance::Man_WalkingJump_RH_1D_25_11:
                case Stance::Man_Slide_RH_11:
                case Stance::Man_Rollers_Fall_RH_04:
                case Stance::Man_Vine_Exit_RH_08:
                    {

                        uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                        uint8_t tile_D2 = world.getTile_RelativeToPlayer(0, -2);

                        if (world.isEmptyTile(tile_D)) {

                            player.incFalls();

                            if (player.getFalls() < 3) {

                                if (world.isEmptyTile(tile_D2)) {                                    

                                    player.pushSequence(Stance::Man_Walk_FallMore_RH_01, Stance::Man_Walk_FallMore_RH_02); 

                                }
                                else if (world.isSpikeTile(tile_D)) {

                                    player.pushSequence(Stance::Man_Die_Fall_RH_01, Stance::Man_Die_Fall_RH_04); 
                                    player.pushSequence(Stance::Man_Walk_FallLand_RH_01, Stance::Man_Walk_FallLand_RH_04);

                                }
                                else if (world.isWaterTile(tile_D)) {

                                    player.pushSequence(Stance::Man_Die_Water_RH_01, Stance::Man_Die_Water_RH_07); 

                                }
                                else {

                                    player.pushSequence(Stance::Man_Walk_FallLand_RH_01, Stance::Man_Walk_FallLand_RH_04);

                                } 

                            }
                            else {
                             
                                player.pushSequence(Stance::Man_Die_Fall_RH_01, Stance::Man_Die_Fall_RH_04); 
                                player.pushSequence(Stance::Man_Walk_FallMore_RH_01, Stance::Man_Walk_FallMore_RH_02); 

                            }

                        }
                        else {

                            player.setStance(Stance::Man_Walk_RH_02); 

                        }

                    }
                    break;

                case Stance::Man_Slide_LH_Full_Cont_08:       
                case Stance::Man_Slide_LH_Full_CanCont_12:       
                case Stance::Man_Slide_LH_Full_CanCont_13:       
                case Stance::Man_Slide_LH_Full_13:       
                    {

                        uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                        uint8_t tile_LD2 = world.getTile_RelativeToPlayer(-1, -2);

                        if (tile_D == Tiles::Slide_RH_Full && tile_LD2 == Tiles::Slide_RH_Full) {

                            player.clear();
                            player.pushSequence(Stance::Man_Slide_LH_Full_Cont_01, Stance::Man_Slide_LH_Full_Cont_08);
                            break;

                        }

                    }

                    [[fallthrough]];

                case Stance::Man_Walk_FallDown_LH_06:
                case Stance::Man_Walk_FallMore_LH_02:
                case Stance::Man_WalkingJump_LH_1D_25_11:
                case Stance::Man_Slide_LH_11:
                case Stance::Man_Rollers_Fall_LH_04:
                case Stance::Man_Vine_Exit_LH_08:
                    {
                           
                        uint8_t tile_D = world.getTile_RelativeToPlayer(0, -1);
                        uint8_t tile_D2 = world.getTile_RelativeToPlayer(0, -2);

                        if (world.isEmptyTile(tile_D)) {

                            player.incFalls();

                            if (player.getFalls() < 3) {

                                if (world.isEmptyTile(tile_D2)) {

                                    player.pushSequence(Stance::Man_Walk_FallMore_LH_01, Stance::Man_Walk_FallMore_LH_02); 

                                }
                                else if (world.isSpikeTile(tile_D)) {

                                    player.pushSequence(Stance::Man_Die_Fall_LH_01, Stance::Man_Die_Fall_LH_04); 
                                    player.pushSequence(Stance::Man_Walk_FallLand_LH_01, Stance::Man_Walk_FallLand_LH_04); 

                                }
                                else if (world.isWaterTile(tile_D)) {

                                    player.pushSequence(Stance::Man_Die_Water_LH_01, Stance::Man_Die_Water_LH_07);                                    

                                }                                    
                                else {

                                    player.pushSequence(Stance::Man_Walk_FallLand_LH_01, Stance::Man_Walk_FallLand_LH_04); 

                                }

                            }
                            else {

                                player.pushSequence(Stance::Man_Die_Fall_LH_01, Stance::Man_Die_Fall_LH_04); 
                                player.pushSequence(Stance::Man_Walk_FallMore_LH_01, Stance::Man_Walk_FallMore_LH_02); 

                            }

                        }
                        else {

                            player.setStance(Stance::Man_Walk_LH_02); 

                        }

                    }
                    break;

                        
                case Stance::Man_Sword_Lunge_LH_03:
                case Stance::Man_Sword_Lunge_RH_03:
                    {
                        Enemy &enemy = world.getEnemy(player.getEnemyIdx());

                        if (enemy.getSwordWound() == 0 && playGame_PlayerStabsEnemy(player)) {

                            enemy.decHealth(1);
                            enemy.setSwordWound(12);

                            if (enemy.getHealth() > 0) {
                                    
                                switch (enemy.getDirection()) {

                                    case Direction::Left:
                                  
                                        enemy.insertSequence(Stance::Enemy_Sword_Walk_BK_LH_01, Stance::Enemy_Sword_Walk_BK_LH_04);
                                        break;

                                    case Direction::Right:
                                   
                                        enemy.insertSequence(Stance::Enemy_Sword_Walk_BK_RH_01, Stance::Enemy_Sword_Walk_BK_RH_04);
                                        break;
                                    
                                }      

                            }
                            else {

                                int16_t dist = getDistanceBetween(enemy);
                                world.setGameState(GameState::Play_Game);

                                player.removeInventoryItem(menu.getY());
                                menu.decY();
                                enemy.clear();

                                // player puts away sword ..

                                switch (player.getDirection()) {

                                    case Direction::Left:
                                        player.insert(Stance::Man_Walk_LH_00);
                                        break;

                                    case Direction::Right:
                                        player.insert(Stance::Man_Walk_RH_00);
                                        break;

                                }


                                // Player dies but whch direction does he fall?

                                switch (dist) {

                                    case -999 ... 0:

                                        switch (enemy.getDirection()) {

                                            case Direction::Left:

                                                enemy.pushSequence(Stance::Enemy_Die_BWD_LH_01, Stance::Enemy_Die_BWD_LH_13);
                                                break;

                                            case Direction::Right:

                                                enemy.pushSequence(Stance::Enemy_Die_FWD_RH_01, Stance::Enemy_Die_FWD_RH_13);
                                                break;

                                        }

                                        break;

                                    case 1 ... 999:

                                        switch (enemy.getDirection()) {

                                            case Direction::Left:

                                                enemy.pushSequence(Stance::Enemy_Die_FWD_LH_01, Stance::Enemy_Die_FWD_LH_13);
                                                break;

                                            case Direction::Right:

                                                enemy.pushSequence(Stance::Enemy_Die_BWD_RH_01, Stance::Enemy_Die_BWD_RH_13);
                                                break;

                                        }

                                        break;

                                }   


                            }                      

                        }

                    }

                    break;

                case Stance::Man_Die_Fire_LH_12:
                case Stance::Man_Die_Fire_RH_12:
                case Stance::Man_Die_Arrow_FallForward_LH_04:
                case Stance::Man_Die_Arrow_FallForward_RH_04:
                case Stance::Man_Die_Arrow_FallBackward_LH_04:
                case Stance::Man_Die_Arrow_FallBackward_RH_04:
                case Stance::Man_Die_Fall_LH_04:
                case Stance::Man_Die_Fall_RH_04:
                case Stance::Man_Die_Water_LH_07:
                case Stance::Man_Die_Water_RH_07:
                case Stance::Man_Die_Water_LH_02_07:
                case Stance::Man_Die_Water_RH_02_07:
                case Stance::Man_Die_BWD_LH_04:
                case Stance::Man_Die_BWD_RH_04:
                case Stance::Man_Die_FWD_LH_04:
                case Stance::Man_Die_FWD_RH_04:

                    player.setHealth(0);
                    world.setGameState(GameState::Play_Dead);
                    endOfLevel_Counter = 0;

                    break;

                default:
                    {
                        FX::seekData(Constants::SubsititueStance + (static_cast<uint16_t>(stance) * 2));
                        uint16_t subsituteStance = FX::readPendingUInt16();
                        FX::readEnd();

                        if (subsituteStance != 65535) {
                            player.setStance(subsituteStance);
                        }

                    }
                    break;

            }

        }

        playGame_HandleEnemies(a);

    }

    playGame_HandleMenu_OpenClose();
    world.updateEnemies(a);
    player.update();


    // End of level?

    if (endOfLevel_Counter < 14 && world.getFrameCount() % 2 == 0) {

        endOfLevel_Counter++;

    }


    // Housekeeping ..

    if (ignoreKeyPress > 0) {
        ignoreKeyPress--;
    }

}

uint16_t playGame_PopEntry(Player &player) {

    uint16_t stance = player.pop();

    player.setStance(stance);

    StanceDetails stanceDetails;

    FX::seekData(Constants::StanceDetails + (static_cast<uint16_t>(stance) * 4));
    FX::readObject(stanceDetails);
    FX::readEnd();

    player.setY(player.getY() - stanceDetails.stanceY);
    world.incForeground(stanceDetails.foreground);
    world.incMiddleground(stanceDetails.middleground);
    world.incBackground(stanceDetails.background);

    return stance;

}

void playGame(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    Player &player = world.getPlayer();

    if (a.needsUpdate()) playGame_Update(a);

    uint8_t yOffset = Constants::GroundY;

    if (player.getY() < 5) yOffset = Constants::GroundY - player.getY();

    uint8_t currentPlane = a.currentPlane();

    renderWorld(currentPlane);

    switch (world.getGameState()) {

        case GameState::Chakana_Open:

            SpritesU::drawPlusMaskFX(36, 0, Images::EndOfLevel, (endOfLevel_Counter * 3) + currentPlane);

            if (endOfLevel_Counter == 13) {
                SpritesU::drawOverwriteFX(63, 37, Images::Numbers_6x4_2D_BW, (titleCounter * 3) + currentPlane);
            }

            break;

        case GameState::Play_Dead:
            SpritesU::drawPlusMaskFX(36, 0, Images::EndOfLife, ((endOfLevel_Counter + (player.getLives() == 1 ? 16 : 0)) * 3) + currentPlane);
            break;

        #ifdef GAMBLE

        case GameState::Play_Gamble_Select_Exit ... GameState::Play_Gamble_Select_Play:
            renderGamblePanel(player.getChakanas() >= 5 ? 0 : 13, currentPlane);

            if (player.getChakanas() >= 5) {
                // SpritesU::drawPlusMaskFX(128 - 32, 0, Images::GamblePanel, ((player.getChakanas() >= 5 ? 0 : 12) * 3) + currentPlane);
                renderInventoryPanelCursor(104, 1 + (static_cast<uint8_t>(world.getGameState()) - static_cast<uint8_t>(GameState::Play_Gamble_Select_Exit)) * 8, currentPlane);
                // SpritesU::drawPlusMaskFX(104, 1 + (static_cast<uint8_t>(world.getGameState()) - static_cast<uint8_t>(GameState::Play_Gamble_Select_Exit)) * 8, Images::InventoryPanel_Cursor, currentPlane);
                renderChakanaBalance(player.getChakanas(), currentPlane);
            }
            break;

        case GameState::Play_Gamble_Select_Spin:
            {
                uint8_t frame = FX::readIndexedUInt8(Constants::GambleFrames, titleCounter);

                if (frame != 255) {

                    renderGamblePanel(1 + frame, currentPlane);
                    // SpritesU::drawPlusMaskFX(128 - 32, 0, Images::GamblePanel, ((1 + frame) * 3) + currentPlane);

                    if (currentPlane == 2) {
                        titleCounter++;
                    }

                    break;

                }
                else {

                    if (titleCounter > 104) {  

                        titleCounter = 0;
                        world.setGameState(GameState::Play_Gamble_Select_Lose);

                    }
                    else {

                        world.setGameState(GameState::Play_Gamble_Select_Win);
                        titleCounter = 20 + (a.randomLFSR(1, 10) * 5);
                        player.setChakanas(player.getChakanas() + titleCounter);

                    }

                }

            }

            [[fallthrough]];

        case GameState::Play_Gamble_Select_Win:
            {
                uint8_t frame = (world.getFrameCount() % 48) < 24;
                renderGamblePanel(11 + frame, currentPlane);
                // SpritesU::drawPlusMaskFX(128 - 32, 0, Images::GamblePanel, ((11 + frame) * 3) + currentPlane);

                if (frame == 0) {
                    SpritesU::drawOverwriteFX(107, 13, Images::Numbers_5x3_2D_BW, (titleCounter * 3) + currentPlane);
                }

                renderChakanaBalance(player.getChakanas(), currentPlane);

            }
            break;

        case GameState::Play_Gamble_Select_Lose:
            {
                uint8_t frame = (world.getFrameCount() % 48) < 24;
                renderGamblePanel(9 + frame, currentPlane);
                // SpritesU::drawPlusMaskFX(128 - 32, 0, Images::GamblePanel, ((9 + frame) * 3) + currentPlane);
                renderChakanaBalance(player.getChakanas(), currentPlane);

            }
            break;

        #endif

        default:    break;

    }

    world.update(true);


}



void removeInventoryItem(GameState gameState) {

    menu.setDirection(Direction::Right);
    menu.setGameState(gameState);

    world.getPlayer().removeInventoryItem(menu.getY() - 2);
    menu.setTop(0);
    menu.setY(0);    

}

void removeWorldandInventoryItem(ItemType itemType, GameState gameState) {

    if (itemType != ItemType::None) {

        uint8_t item = world.getItem(itemType);
        world.getItem(item).setCounter(1);  

    }

    menu.setDirection(Direction::Right);
    menu.setGameState(gameState);

    world.getPlayer().removeInventoryItem(menu.getY() - 2);
    menu.setTop(0);
    menu.setY(0);

}
