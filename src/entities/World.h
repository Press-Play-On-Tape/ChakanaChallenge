#pragma once

#include "Boat.h"
#include "../utils/Constants.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"




struct World {

    private:

        Player player;
        Enemy enemy[Constants::EnemyCount];
        Item items[10];

        uint16_t xMap = 0;
        uint16_t yMap = 0;
        uint16_t xBoat = 14;
        uint16_t yBoat = 6;
        uint16_t boatIdx = 0;
        uint8_t boatDirection = 0;
        uint8_t boatCounter = 0;
        int16_t x = 0;
        int16_t y = 0;

        int16_t wave = 0;
        int16_t palm[8] = { -240, -130,0, 130, 116, 66, -20, -80 };
        // int16_t palm1 = -240;
        // int16_t palm2 = -130;
        // int16_t palm3 = 0;
        // int16_t palm4 = 130;

        // int8_t palm5 = 116;
        // int8_t palm6 = 66;
        // int8_t palm7 = -20;
        // int8_t palm8 = -80;

        uint16_t waveIdx = 0;
        int16_t background = 0;
        int16_t middleground = 0;

        Boat boat;

    public:

        Item &getItem(uint8_t idx)               { return this->items[idx]; }
        Player &getPlayer()                      { return this->player; }
        Enemy &getEnemy(uint8_t idx)             { return this->enemy[idx]; }
        uint16_t getXMap()                       { return this->xMap; }
        uint16_t getYMap()                       { return this->yMap; }
        uint16_t getXBoat()                      { return this->xBoat; }
        uint16_t getYBoat()                      { return this->yBoat; }
        uint8_t  getBoatDirection()              { return this->boatDirection; }
        uint8_t  getBoatCounter()                { return this->boatCounter; }
        uint16_t getBoatIdx()                    { return this->boatIdx; }

        int16_t getX()                           { return this->x; }
        int16_t getY()                           { return this->y; }

        // int16_t getPalm1()                       { return this->palm[0]; }
        // int16_t getPalm2()                       { return this->palm[1]; }
        // int16_t getPalm3()                       { return this->palm[2]; }
        // int16_t getPalm4()                       { return this->palm[3]; }
        // int16_t getPalm5()                       { return this->palm[4]; }
        // int16_t getPalm6()                       { return this->palm[5]; }
        // int16_t getPalm7()                       { return this->palm[6]; }
        // int16_t getPalm8()                       { return this->palm[7]; }
        int16_t getWave()                        { return this->wave; }
        int16_t getBackground()                  { return this->background; }
        int16_t getMiddleground()                { return this->middleground; }
        uint16_t getWaveIdx()                    { return this->waveIdx; }

        Boat& getBoat()                          { return this->boat; }

        void setXMap(uint16_t val)               { this->xMap = val; }
        void setYMap(uint16_t val)               { this->yMap = val; }
        void setXBoat(uint16_t val)              { this->xBoat = val; }
        void setYBoat(uint16_t val)              { this->yBoat = val; }
        void setBoatDirection(uint8_t val)       { this->boatDirection = val; }
        void setBoatIdx(uint16_t val)            { this->boatIdx = val; }
        void setBoatCounter(uint8_t val)         { this->boatCounter = val; }

        void setX(int16_t val)                   { this->x = val; }
        void setY(int16_t val)                   { this->y = val; }

        // void setPalm1(int16_t val)               { this->palm[0] = val; }
        // void setPalm2(int16_t val)               { this->palm[1] = val; }
        // void setPalm3(int16_t val)               { this->palm[2] = val; }
        // void setPalm4(int16_t val)               { this->palm[3] = val; }
        // void setPalm5(int16_t val)               { this->palm[4] = val; }
        // void setPalm6(int16_t val)               { this->palm[5] = val; }
        // void setPalm7(int16_t val)               { this->palm[6] = val; }
        // void setPalm8(int16_t val)               { this->palm[7] = val; }
        void setWave(int16_t val)                { this->wave = val; }
        void setBackground(int16_t val)          { this->background = val; }
        void setMiddleground(int16_t val)        { this->middleground = val; }
        void setWaveIdx(uint16_t val)            { this->waveIdx = val; }

    public:

        int16_t getPalm(uint8_t idx) { return this->palm[idx]; }

        int16_t setPalm(uint8_t idx, int16_t val) { this->palm[idx] = val; }

        void startBoat() {

            this->boatIdx = 2;

        }

        uint8_t getBoatDirection4() {

            switch (this->boatDirection) {

                case 0:     
                case 1:     
                case 15:     
                    return 0;

                case 2 ... 6:     
                    return 1;

                case 7 ... 9:     
                    return 2;

                case 10 ... 14:
                    return 3;

                case 255:
                    return 2;

            }
            
        }

        void updateBoat() {

            if (this->boatCounter > 0) {

                uint8_t idx = static_cast<uint8_t>(this->boatDirection);
                
                FX::seekData(Constants::BoatCoords + (idx * 2));
                int8_t x = FX::readPendingUInt8();
                int8_t y = FX::readPendingUInt8();                
                FX::readEnd();

                this->xBoat = this->xBoat + x;
                this->yBoat = this->yBoat + y;
                this-boatCounter--;

            }
            else {

                uint8_t move = Constants::BoatMovements[this->boatIdx];
                
                if (move != 255) {
                    this->boatDirection = move;
                    this->boatIdx++;
                    this->boatCounter = Constants::BoatMovements[this->boatIdx];
                    this->boatIdx++;
                }
                else {

                    this->boatDirection = 255;
                }

            }
        }

        void incXBoatIdx() {

            this->boatIdx++;
            
        }

        void incXMap(int8_t val) {

            this->xMap = this->xMap + val;
            
        }

        void incYMap(int8_t val) {

            this->yMap = this->yMap + val;
            
        }

        void incForeground(int8_t val) {

            for (uint8_t i = 0; i < 3; i++) {
                this->incPalm(i, val);
            }

            this->incWave(val);
            
        }

        void incBackground(int8_t val) {

            for (uint8_t i = 4; i < 7; i++) {
                this->incPalm(i, val);
            }

            this->incBackgroundVal(val);
            this->x = this->x - val;

        }

        void incMiddleground(int8_t val) {

            this->middleground = this->middleground + val;

        }

        void incPalm(uint8_t idx, int8_t val) {

            this->palm[idx] = this->palm[idx] + val;

        }

        void incBackgroundVal(int8_t val) {

            this->background = this->background + val;

            if (this->background == -128) { 
                
                this->background = 0; 
                
            }
            else if (this->background == 128) { 
                
                background = 0; 

            }

        }

        void incWave(int8_t val) {

            this->wave = this->wave + val;

            if (this->wave <= -256) { 
                
                this->wave = this->wave + 256;
                
            }
            else if (this->wave >= 256) { 
                
                this->wave = this->wave - 256;

            }

        }

        void update(bool completeWaves) {

            uint8_t removeItemIdx = 255;

            for (uint8_t i = 0; i < Constants::ItemCount; i++) {

                Item &item = this->items[i];
                if (item.getItemType() == ItemType::None) break;
                
                ItemAction action = item.update();

                switch (action) {

                    case ItemAction::Remove:
                        removeItemIdx = i;
                        break;

                    case ItemAction::HideCrate_ShowItem:
                        this->items[i + 1].setItemType(static_cast<ItemType>(static_cast<uint8_t>(this->items[i + 1].getItemType()) - 1));
                        break;

                    case ItemAction::Remove_AddToInventory:
                        player.addInventoryItem(item.getItemType());
                        removeItemIdx = i;
                        break;

                    case ItemAction::ChangeToHidden:
                        player.addInventoryItem(item.getItemType());
                        item.setItemType(static_cast<ItemType>(static_cast<uint8_t>(item.getItemType()) + 1));
                        break;

                }

                uint8_t yOffset = Constants::GroundY;
                if (player.getY() < 5) yOffset = Constants::GroundY - player.getY();
                Rect playerRect = { 59, yOffset - Constants::GroundY + player.getY(), 10, 16 };
                
                switch (item.getItemType()) {

                    case ItemType::SwingyThing:
                        {  
                            int16_t itemX = item.getX() + 6 + 2 + Constants::swingyThing_X[item.getFrame()];
                            int8_t itemY = yOffset - item.getY() + Constants::swingyThing_Y[item.getFrame()] + 11;

                            Rect itemRect = { itemX + this->getMiddleground() - 4, itemY, 16, 3};

                            if (collide(playerRect, itemRect)) {

                                switch (player.getDirection()) {

                                    case Direction::Left:
                                        {
                                            switch (item.getFrame()) {

                                                case 0 ... 8:
                                     
                                                    initPuff(itemX - 8, itemY - 16);
                                                    player.pushSequence(Stance::Man_Die_FWD_LH_01, Stance::Man_Die_FWD_LH_04, true);
                                                    break;

                                                default:
                                         
                                                    initPuff(itemX - 8 + itemRect.width, itemY - 16);
                                                    player.pushSequence(Stance::Man_Die_BWD_LH_01, Stance::Man_Die_BWD_LH_04, true);
                                                    break;
                                                    
                                            }

                                        }

                                        break;

                                    case Direction::Right:
                                        {                                                
                                            item.setItemType(ItemType::SwingyThing_2);

                                            switch (item.getFrame()) {

                                                case 0 ... 8:
                                 
                                                    initPuff(itemX - 8, itemY - 16);
                                                    player.pushSequence(Stance::Man_Die_BWD_RH_01, Stance::Man_Die_BWD_RH_04, true);
                                                    break;

                                                default:
                                           
                                                    initPuff(itemX - 8 + itemRect.width, itemY - 16);
                                                    player.pushSequence(Stance::Man_Die_FWD_RH_01, Stance::Man_Die_FWD_RH_04, true);
                                                    break;
                                                    
                                            }

                                        }

                                        break;

                                }

                            }

                        }

                        break;

                }

            }

            if (removeItemIdx != 255) {
                this->removeItem(removeItemIdx);
            }

            if (this->waveIdx == Constants::NoWaves) return;

            this->waveIdx++;

            if (this->waveIdx >= 6 * 64) this->waveIdx = 0;

            if (completeWaves && this->waveIdx == 4 * 64) {

                this->waveIdx = Constants::NoWaves;

            }


        }

        void removeItem(uint8_t itemIdx) {

            for (uint8_t i = itemIdx; i < Constants::ItemCount - 1; i++) {

                this->items[i].setItemType(items[i + 1].getItemType());
                this->items[i].setFrame(items[i + 1].getFrame());
                this->items[i].setX(items[i + 1].getX());
                this->items[i].setY(items[i + 1].getY());
                this->items[i].setCounter(items[i + 1].getCounter());

            }

            this->items[Constants::ItemCount - 1].setItemType(ItemType::None);

        }

        uint8_t getItem(ItemType itemType) {

            for (uint8_t i = 0; i < Constants::ItemCount; i++) {

                if (this->items[i].getItemType() == itemType) return i;

            }

            return 255;

        }

        uint8_t getItem(uint16_t xOffset, int8_t yOffset) {

            for (uint8_t i = 0; i < Constants::ItemCount; i++) {

                if (this->items[i].getItemType() == ItemType::None) return 255;

                if (this->items[i].getItemType() != ItemType::None && this->items[i].getX() == xOffset && this->items[y].getY() == yOffset) {
                    return i;
                }
            }

            return 255;

        };

        uint8_t getTile(int8_t xOffset, int8_t yOffset) {

            #ifdef MAP_FROM_FX

                FX::seekData(Levels::mapData1 + (yOffset * numberOfTiles) + xOffset);
                uint8_t x = FX::readPendingUInt8();
                FX::readEnd();
                return x;

            #else

                // #ifdef DEBUG

                    // DEBUG_PRINT(F("getTile(xOffset,yOffset) "));
                    // DEBUG_PRINT(xOffset);
                    // DEBUG_PRINT(" ");
                    // DEBUG_PRINT(yOffset);
                    // DEBUG_PRINT(" = ");
                    // DEBUG_PRINTLN(mapData[yOffset][xOffset]);
                        
                // #endif

                return mapData[yOffset][xOffset];

            #endif

        }

        uint8_t getTile_RelativeToPlayer(int8_t xOffset, int8_t yOffset) {

            if (player.getLevel() + yOffset < 0) return 1;

            int16_t tileIdx = (-this->getMiddleground() + 65 + (xOffset * 8)) / 8;

            #ifdef MAP_FROM_FX

                FX::seekData(Levels::mapData1 + ((this->player.getLevel() + yOffset) * numberOfTiles) + tileIdx);
                uint8_t x = FX::readPendingUInt8();
                FX::readEnd();
                return x;

            #else

                // #ifdef DEBUG

                //     DEBUG_PRINT(F("getTile(p,x,y) "));
                //     DEBUG_PRINT(xOffset);
                //     DEBUG_PRINT(" ");
                //     DEBUG_PRINT(yOffset);
                //     DEBUG_PRINT(" = ");
                //     DEBUG_PRINTLN(mapData[player.getLevel() + yOffset][tileIdx]);
                        
                // #endif

                return mapData[this->player.getLevel() + yOffset][tileIdx];

            #endif

        }

        bool canWalkPastTile(uint8_t tile) {

            return canWalkPastTile(tile, Direction::None);

        }

        bool canWalkPastTile(uint8_t tile, Direction direction) {
            
            if (tile == Tiles::Lever_Portal_LH && direction == Direction::Left) { 

                return true;

            }

            if (tile == Tiles::Lever_Portal_LH && direction == Direction::Right) { 

                for (uint8_t i = 0; i < Constants::ItemCount; i++) {
                    
                    Item &item = this->items[i];

                    if (item.getItemType() == ItemType::Lever_Portal_Open) {
                        
                        return true;

                    }

                }

                return false; 
                
            }
            
            if (tile == Tiles::Lever_Portal_RH && direction == Direction::Right) { 

                return true;

            }

            if (tile == Tiles::Lever_Portal_RH && direction == Direction::Left) { 

                for (uint8_t i = 0; i < Constants::ItemCount; i++) {
                    
                    Item &item = this->items[i];

                    if (item.getItemType() == ItemType::Lever_Portal_Open) {
                        
                        return true;

                    }

                }

                return false; 
                
            }
            
            if (tile == Tiles::Lever_Portal_Auto_LH && direction == Direction::Left) { 

                return true;

            }

            if (tile == Tiles::Lever_Portal_Auto_LH && direction == Direction::Right) { 

                for (uint8_t i = 0; i < Constants::ItemCount; i++) {
                    
                    Item &item = this->items[i];

                    if (item.getItemType() == ItemType::Lever_Portal_Auto_Open) {
                        
                        return true;

                    }

                }

                return false; 
                
            }

            if (tile == Tiles::Lever_Portal_Auto_RH && direction == Direction::Right) { 

                return true;

            }

            if (tile == Tiles::Lever_Portal_Auto_RH && direction == Direction::Left) { 

                for (uint8_t i = 0; i < Constants::ItemCount; i++) {
                    
                    Item &item = this->items[i];

                    if (item.getItemType() == ItemType::Lever_Portal_Auto_Open) {
                        
                        return true;

                    }

                }

                return false; 
                
            }

            if (tile == Tiles::WoddenBarrier) { 

                for (uint8_t i = 0; i < Constants::ItemCount; i++) {
                    
                    Item &item = this->items[i];

                    if (item.getItemType() == ItemType::WoodenBarrier) {
                        
                        return item.getCounter() == (7 * 32) - 1;

                    }

                }

                return false; 
                
            }

            if (tile == 25) { 

                for (uint8_t i = 0; i < Constants::ItemCount; i++) {
                    
                    Item &item = this->items[i];

                    if (item.getItemType() == ItemType::MysteryCrate) {
                        
                        return item.getFrame() == 8;

                    }

                }

                return false; 
                
            }

            if (tile == 26) { 

                for (uint8_t i = 0; i < Constants::ItemCount; i++) {
                    
                    Item &item = this->items[i];

                    if (item.getItemType() == ItemType::LockedDoor) {
                        
                        return item.getFrame() == 4;

                    }

                }

                return false; 
                
            }

            return tile == 0 || tile == 1 || tile == Tiles::Ladder_Lower || tile == Tiles::Ladder_Middle || tile == 13 /*rope lh*/ || 
                   tile == 14 /*rope rh*/ || tile == Tiles::Spring_LH || tile == Tiles::Spring_RH || tile == Tiles::Punji ||
                   tile == Tiles::Swinging_Vine_LH || tile == Tiles::Swinging_Vine_RH;
            
        }

        bool canWalkOnTile(uint8_t tile) {

            return tile == Tiles::Solid_1 || tile == Tiles::Solid_2 || tile == Tiles::Single_Stair_LH_Upper_TL || tile == 27 || tile == 28;
            
        }

        bool isPunjiTile(uint8_t tile) {

            return tile == Tiles::Punji;
            
        }

        bool canJumpUpOntoTile(uint8_t tile) {

            return tile == Tiles::Solid_1 || tile == Tiles::Solid_2;
            
        }

        bool isEmptyTile(uint8_t tile) {

            return tile == Tiles::Blank || tile == Tiles::Spikes || tile == Tiles::Swinging_Vine_LH || tile == Tiles::Swinging_Vine_RH || tile == Tiles::Water_Plain || tile == Tiles::Water_Bubbling_1 || tile == Tiles::Water_Bubbling_2;
            
        }

        bool isSpikeTile(uint8_t tile) {

            return tile == Tiles::Spikes;
            
        }

        bool isWaterTile(uint8_t tile) {

            return tile == Tiles::Water_Plain || tile == Tiles::Water_Bubbling_1 || tile == Tiles::Water_Bubbling_2;
            
        }

        bool isStairTile_R1(uint8_t tile) {

            return tile == 4;
            
        }

        bool isStairTile_R_Half(uint8_t tile) {

            return tile == Tiles::Single_Stair_RH_Lower;
            
        }

        bool isStairTile_R2(uint8_t tile) {

            return tile == Tiles::Single_Stair_RH_Upper_TR;
            
        }

        bool isStairTile_L1(uint8_t tile) {

            return tile == Tiles::Single_Stair_LH_Upper_TR;
            
        }

        bool isStairTile_L_Half(uint8_t tile) {

            return tile == Tiles::Single_Stair_LH_Lower;
            
        }

        bool isStairTile_L2(uint8_t tile) {

            return tile == Tiles::Single_Stair_LH_Upper_TL;
            
        }

        bool isLadderTile_Lower(uint8_t tile) {

            return tile == 7;
            
        }

        bool isLadderTile_Middle(uint8_t tile) {

            return tile == 12;
            
        }

        bool isLadderTile_Upper(uint8_t tile) {

            return tile == 8;
            
        }

        bool isRopeSupport(uint8_t tile) {

            return tile == 13 || tile == 14;
            
        }

        // Vertical vine ---------------------------

        bool isVerticalVine_Lower(uint8_t tile) {

            return tile == Tiles::Vine_Lower;
            
        }

        bool isVerticalVine_Middle(uint8_t tile) {

            return tile == Tiles::Vine_Middle;
            
        }

        bool isVerticalVine_Upper(uint8_t tile) {

            return tile == Tiles::Vine_Upper;
            
        }

        bool isRopeTile(uint8_t tile) {

            return tile == 15;
            
        }

        // Spring ----------------------------------

        bool isSpringTile(uint8_t tile) {

            return tile == Tiles::Spring_LH || tile == Tiles::Spring_RH;
            
        }

        bool isSpringTile_LH(uint8_t tile) {

            return tile == Tiles::Spring_LH;
            
        }

        bool isSpringTile_RH(uint8_t tile) {

            return tile == Tiles::Spring_RH;
            
        }

        // Slides ----------------------------------
        
        bool isSlideTile_LH(uint8_t tile) {

            return tile == Tiles::Slide_LH_Upper;
            
        }

        bool isSlideTile_Full_LH(uint8_t tile) {

            return tile == Tiles::Slide_LH_Full;
            
        }
        
        bool isSlideTile_RH(uint8_t tile) {

            return tile == 21;
            
        }

        bool isSlideTile_Full_RH(uint8_t tile) {

            return tile == 22;
            
        }

        bool isWoodenBarrier(uint8_t tile) {

            return tile == Tiles::WoddenBarrier;
            
        }

        bool isMysteryCrate(uint8_t tile) {

            return tile == 25;
            
        }

        bool isLockedDoor(uint8_t tile) {

            return tile == 26;
            
        }

        bool isRollerTile_RH(uint8_t tile) {

            return tile == 27;
            
        }

        bool isRollerTile_LH(uint8_t tile) {

            return tile == 28;
            
        }        

        bool isVineTile_LH(uint8_t tile) {

            return tile == Tiles::Swinging_Vine_LH;
            
        }        

        bool isVineTile_RH(uint8_t tile) {

            return tile == Tiles::Swinging_Vine_RH;
            
        }       


        void updateEnemies(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

            for (uint8_t i  = 0; i < Constants::EnemyCount; i++) {

                Enemy &enemy = this->getEnemy(i);

                if (enemy.getX() == 0) continue;
                enemy.update();

                Item &item = enemy.getItem();

                switch (item.getItemType()) {

                    case ItemType::Arrow_LH ... ItemType::Arrow_RH_Hidden:

                        if (enemy.getCount() == 0 && a.randomLFSR(0, 120) == 0) {

                            switch (enemy.getDirection()) {

                                case Direction::Left:
                                    enemy.pushSequence(Stance::Enemy_Fire_LH_00, Stance::Enemy_Fire_LH_12);
                                    break;

                                case Direction::Right:
                                    enemy.pushSequence(Stance::Enemy_Fire_RH_00, Stance::Enemy_Fire_RH_12);
                                    break;

                            }

                        }

                        break;

                    case ItemType::Trebochet_Ball_Left_1 ... ItemType::Trebochet_Ball_Right_Hidden:

                        if (enemy.getCount() == 0 && a.randomLFSR(0, 120) == 0) {

                            switch (enemy.getDirection()) {

                                case Direction::Left:
                                    enemy.pushSequence(Stance::Enemy_Trebochet_Release_LH_01, Stance::Enemy_Trebochet_Release_LH_14);
                                    break;

                                case Direction::Right:
                                    enemy.pushSequence(Stance::Enemy_Trebochet_Release_RH_01, Stance::Enemy_Trebochet_Release_RH_14);
                                    break;

                            }

                        }

                        break;

                }

                switch (item.getItemType()) {

                    case ItemType::Arrow_LH:
                        {
                            enemy.getItem().update();

                            uint8_t yOffset = Constants::GroundY;
                            if (player.getY() < 5) yOffset = Constants::GroundY - player.getY();

                            Rect playerRect = { 59, yOffset - Constants::GroundY + player.getY(), 10, 16 };
                            Rect arrowRect = { enemy.getItem().getX() + this->getMiddleground() - 4 + 1, yOffset - enemy.getItem().getY() + 1, 9, 3 };
                            
                            if (collide(playerRect, arrowRect)) {

                                enemy.getItem().setItemType(ItemType::None);

                                switch (this->player.getDirection()) {

                                    case Direction::Right:
                                        this->player.pushSequence(Stance::Man_Die_Arrow_FallBackward_RH_01, Stance::Man_Die_Arrow_FallBackward_RH_04, true);
                                        break;

                                    case Direction::Left:
                                        this->player.pushSequence(Stance::Man_Die_Arrow_FallForward_LH_01, Stance::Man_Die_Arrow_FallForward_LH_04, true);
                                        break;
                                        
                                }

                            }

                        }

                        break;

                    case ItemType::Arrow_RH:
                        {
                            enemy.getItem().update();

                            uint8_t yOffset = Constants::GroundY;
                            if (player.getY() < 5) yOffset = Constants::GroundY - player.getY();

                            Rect playerRect = { 59, yOffset - Constants::GroundY + player.getY(), 10, 16 };
                            Rect arrowRect = { enemy.getItem().getX() + this->getMiddleground() - 4 + 1, yOffset - enemy.getItem().getY() + 1, 9, 3 };
                            
                            if (collide(playerRect, arrowRect)) {

                                enemy.getItem().setItemType(ItemType::None);

                                switch (this->player.getDirection()) {

                                    case Direction::Right:
                                        this->player.pushSequence(Stance::Man_Die_Arrow_FallForward_RH_01, Stance::Man_Die_Arrow_FallForward_RH_04, true);
                                        break;

                                    case Direction::Left:
                                        this->player.pushSequence(Stance::Man_Die_Arrow_FallBackward_LH_01, Stance::Man_Die_Arrow_FallBackward_LH_04, true);
                                        break;
                                        
                                }

                            }

                        }

                        break;
                    
                    case ItemType::Trebochet_Ball_Left_1 ... ItemType::Trebochet_Ball_Left_3:
                    // case ItemType::Trebochet_Ball_Right_1 ... ItemType::Trebochet_Ball_Right_3:
                        {
                            enemy.getItem().update(); 

                            uint8_t yOffset = Constants::GroundY;
                            if (player.getY() < 5) yOffset = Constants::GroundY - player.getY();

                            Rect playerRect = { 59, yOffset - Constants::GroundY + player.getY(), 10, 16 };
                            Rect trebochetRect = { enemy.getItem().getX() + this->getMiddleground() - 4, yOffset - enemy.getItem().getY(), 4, 4 };
                            
                            if (collide(playerRect, trebochetRect)) {

                                enemy.getItem().setItemType(ItemType::Trebochet_Ball_Left_Hidden);
                                enemy.getItem().setFrame(0);
                                item.setCounter(3);

                                this->initPuff(item.getX(), item.getY());

                                switch (this->player.getDirection()) {

                                    case Direction::Right:
                                        this->player.pushSequence(Stance::Man_Die_BWD_RH_01, Stance::Man_Die_BWD_RH_04, true);
                                        break;

                                    case Direction::Left:
                                        this->player.pushSequence(Stance::Man_Die_FWD_LH_01, Stance::Man_Die_FWD_LH_04, true);
                                        break;
                                        
                                }

                            }                            

                        }
                        break;   

                    // case ItemType::Trebochet_Ball_Left_1 ... ItemType::Trebochet_Ball_Left_3:
                    case ItemType::Trebochet_Ball_Right_1 ... ItemType::Trebochet_Ball_Right_3:
                        {
                            enemy.getItem().update(); 

                            uint8_t yOffset = Constants::GroundY;
                            if (player.getY() < 5) yOffset = Constants::GroundY - player.getY();

                            Rect playerRect = { 59, yOffset - Constants::GroundY + player.getY(), 10, 16 };
                            Rect trebochetRect = { enemy.getItem().getX() + this->getMiddleground() - 4, yOffset - enemy.getItem().getY(), 4, 4 };
                            
                            if (collide(playerRect, trebochetRect)) {

                                enemy.getItem().setItemType(ItemType::Trebochet_Ball_Right_Hidden);
                                enemy.getItem().setFrame(0);
                                item.setCounter(3);

                                this->initPuff(item.getX(), item.getY());

                                switch (this->player.getDirection()) {

                                    case Direction::Right:
                                        this->player.pushSequence(Stance::Man_Die_FWD_RH_01, Stance::Man_Die_FWD_RH_04, true);
                                        break;

                                    case Direction::Left:
                                        this->player.pushSequence(Stance::Man_Die_BWD_LH_01, Stance::Man_Die_BWD_LH_04, true);
                                        break;
                                        
                                }

                            }                            

                        }
                        break;  

                    case ItemType::Glint:
                        enemy.getItem().update(); 
                        break;

                }

            }

        } 

        bool collide(Rect rect1, Rect rect2) {

            return !(rect2.x                >= rect1.x + rect1.width  ||
                        rect2.x + rect2.width  <= rect1.x                ||
                        rect2.y                >= rect1.y + rect1.height ||
                        rect2.y + rect2.height <= rect1.y);

        }

        bool initPuff(uint16_t x, int8_t y) {

            Item &puff = this->getItem(this->getItem(ItemType::Puff));
            puff.setX(x);
            puff.setY(y);
            puff.setFrame(0);
        }


        uint8_t getClosestEnemy(EnemyType enemyType) {
            
            int16_t dist = 16000;
            uint8_t idx = 255;

            for (uint8_t i = 0; i < Constants::EnemyCount; i++) {

                Enemy &enemy = this->enemy[i];

                if (enemy.getEnemyType() == EnemyType::None) break;

                int16_t dist_Test = -this->getMiddleground() + 56 - enemy.getX();

                if (dist_Test < 0) dist_Test = dist_Test * -1;

                if (dist_Test < dist) {

                    dist = dist_Test;
                    idx = i;

                }

            }

            return idx;

        }
};
