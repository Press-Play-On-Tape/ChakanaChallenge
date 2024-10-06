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
        int16_t palm1 = -240;
        int16_t palm2 = -130;
        int16_t palm3 = 0;
        int16_t palm4 = 130;

        int8_t palm5 = 116;
        int8_t palm6 = 66;
        int8_t palm7 = -20;
        int8_t palm8 = -80;

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

        int16_t getPalm1()                       { return this->palm1; }
        int16_t getPalm2()                       { return this->palm2; }
        int16_t getPalm3()                       { return this->palm3; }
        int16_t getPalm4()                       { return this->palm4; }
        int16_t getPalm5()                       { return this->palm5; }
        int16_t getPalm6()                       { return this->palm6; }
        int16_t getPalm7()                       { return this->palm7; }
        int16_t getPalm8()                       { return this->palm8; }
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

        void setPalm1(int16_t val)               { this->palm1 = val; }
        void setPalm2(int16_t val)               { this->palm2 = val; }
        void setPalm3(int16_t val)               { this->palm3 = val; }
        void setPalm4(int16_t val)               { this->palm4 = val; }
        void setPalm5(int16_t val)               { this->palm5 = val; }
        void setPalm6(int16_t val)               { this->palm6 = val; }
        void setPalm7(int16_t val)               { this->palm7 = val; }
        void setPalm8(int16_t val)               { this->palm8 = val; }
        void setWave(int16_t val)                { this->wave = val; }
        void setBackground(int16_t val)          { this->background = val; }
        void setMiddleground(int16_t val)        { this->middleground = val; }
        void setWaveIdx(uint16_t val)            { this->waveIdx = val; }

    public:

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

                switch (this->boatDirection) {

                    case 0:
                        this->yBoat = this->yBoat - 2;
                        break;

                    case 1:
                        this->xBoat = this->xBoat + 1;
                        this->yBoat = this->yBoat - 2;
                        break;

                    case 2:
                        this->xBoat = this->xBoat + 2;
                        this->yBoat = this->yBoat - 2;
                        break;

                    case 3:
                        this->xBoat = this->xBoat + 2;
                        this->yBoat = this->yBoat + 1;
                        break;

                    case 4:
                        this->xBoat = this->xBoat + 2;      // Right
                        break;

                    case 5:
                        this->xBoat = this->xBoat + 2;
                        this->yBoat = this->yBoat + 1;
                        break;

                    case 6:
                        this->xBoat = this->xBoat + 2;
                        this->yBoat = this->yBoat + 2;
                        break;

                    case 7:
                        this->xBoat = this->xBoat + 1;
                        this->yBoat = this->yBoat + 2;
                        break;

                    case 8:
                        this->yBoat = this->yBoat + 2;      // Down
                        break;
             
                    case 9:
                        this->xBoat = this->xBoat - 1;
                        this->yBoat = this->yBoat + 2;
                        break;

                    case 10:
                        this->xBoat = this->xBoat - 2;
                        this->yBoat = this->yBoat + 2;
                        break;

                    case 11:
                        this->xBoat = this->xBoat - 2;
                        this->yBoat = this->yBoat + 1;
                        break;

                    case 12:
                        this->xBoat = this->xBoat - 2;      // Left
                        break;           
             
                    case 13:
                        this->xBoat = this->xBoat - 2;
                        this->yBoat = this->yBoat - 1;
                        break;

                    case 14:
                        this->xBoat = this->xBoat - 2;
                        this->yBoat = this->yBoat - 2;
                        break;

                    case 15:
                        this->xBoat = this->xBoat - 1;
                        this->yBoat = this->yBoat - 2;
                        break;


                }

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

            this->incPalm1(val);
            this->incPalm2(val);
            this->incPalm3(val);
            this->incPalm4(val);
            this->incWave(val);
            
        }

        void incBackground(int8_t val) {

            this->incPalm5(val);
            this->incPalm6(val);
            this->incPalm7(val);
            this->incPalm8(val);
            this->incBackgroundVal(val);

            this->x = this->x - val;

        }

        void incMiddleground(int8_t val) {

            // this->incPalm5(val);
            // this->incPalm6(val);
            // this->incPalm7(val);
            // this->incPalm8(val);
            // this->incBackgroundVal(val);

            this->middleground = this->middleground + val;

        }

        void incPalm1(int8_t val) {

            this->palm1 = this->palm1 + val;

            // if (this->palm1 <= -256) { 
                
            //     this->palm1 = this->palm1 + 512;
                
            // }
            // else if (this->palm1 >= 256) { 
                
            //     this->palm1 = this->palm1 - 512;

            // }

        }

        void incPalm2(int8_t val) {

            this->palm2 = this->palm2 + val;

            // if (this->palm2 <= -256) { 
                
            //     this->palm2 = this->palm2 + 512;
                
            // }
            // else if (this->palm2 >= 256) { 
                
            //     this->palm2 = this->palm2 - 512;

            // }

        }

        void incPalm3(int8_t val) {

            this->palm3 = this->palm3 + val;

            // if (this->palm3 <= -256) { 
                
            //     this->palm3 = this->palm3 + 512;
                
            // }
            // else if (this->palm3 >= 256) { 
                
            //     this->palm3 = this->palm3 - 512;

            // }

        }

        void incPalm4(int8_t val) {

            this->palm4 = this->palm4 + val;

            // if (this->palm4 <= -256) { 
                
            //     this->palm4 = this->palm4 + 512;
                
            // }
            // else if (this->palm4 >= 256) { 
                
            //     this->palm4 = this->palm4 - 512;

            // }

        }

        void incPalm5(int8_t val) {

            this->palm5 = this->palm5 + val;

        }

        void incPalm6(int8_t val) {

            this->palm6 = this->palm6 + val;

        }

        void incPalm7(int8_t val) {

            this->palm7 = this->palm7 + val;

        }

        void incPalm8(int8_t val) {

            this->palm8 = this->palm8 + val;

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

            // #ifdef DEBUG

                // DEBUG_PRINT(F("getTile(xOffset,yOffset) "));
                // DEBUG_PRINT(xOffset);
                // DEBUG_PRINT(" ");
                // DEBUG_PRINT(yOffset);
                // DEBUG_PRINT(" = ");
                // DEBUG_PRINTLN(mapData[yOffset][xOffset]);
                    
            // #endif

            // for (uint8_t i = 0; i < Constants::ItemCount; i++) {

            //     if (this->items[i].getItemType() != ItemType::None && this->items[i].getX() / 8 == xOffset && this->items[y].getY() / 8 == yOffset) {
            //         Serial.print((uint8_t)items[i].getItemType());
            //         Serial.print(" ");
            //         Serial.print(items[i].getX());
            //         Serial.print(" ");
            //         Serial.print(items[i].getY());
            //         Serial.print(" ");
            //         Serial.println(xOffset);
            //     }
            // }

            return mapData[yOffset][xOffset];

        }

        uint8_t getTile_RelativeToPlayer(int8_t xOffset, int8_t yOffset) {

            if (player.getLevel() + yOffset < 0) return 1;

            int16_t tileIdx = (-this->getMiddleground() + 65 + (xOffset * 8)) / 8;

            // #ifdef DEBUG

            //     DEBUG_PRINT(F("getTile(p,x,y) "));
            //     DEBUG_PRINT(xOffset);
            //     DEBUG_PRINT(" ");
            //     DEBUG_PRINT(yOffset);
            //     DEBUG_PRINT(" = ");
            //     DEBUG_PRINTLN(mapData[player.getLevel() + yOffset][tileIdx]);
                    
            // #endif

            return mapData[this->player.getLevel() + yOffset][tileIdx];

        }


        bool canWalkPastTile(uint8_t tile) {

            if (tile == 24) { 

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

            return tile == 0 || tile == 1 || tile == 7 /*stairs*/ || tile == 12 /*stairs*/ || tile == 13 /*rope lh*/ || 
                   tile == 14 /*rope rh*/ || tile == 16 /*Spring lh*/ || tile == 17 /*Spring rh*/ || tile == 23 /*Punji Invisible*/ ||
                   tile == 29 || tile == 30;
            
        }

        bool canWalkOnTile(uint8_t tile) {

            return tile == 1 || tile == 2 || tile == 9 || tile == 27 || tile == 28;
            
        }

        bool isPunjiTile(uint8_t tile) {

            return tile == 23;
            
        }

        bool canJumpUpOntoTile(uint8_t tile) {

            return tile == 1 || tile == 2;
            
        }

        bool isEmptyTile(uint8_t tile) {

            return tile == 0 || tile == 3 || tile == 29 || tile == 30;
            
        }

        bool isSpikeTile(uint8_t tile) {

            return tile == 3;
            
        }

        bool isStairTile_R1(uint8_t tile) {

            return tile == 4;
            
        }

        bool isStairTile_R_Half(uint8_t tile) {

            return tile == 6;
            
        }

        bool isStairTile_R2(uint8_t tile) {

            return tile == 5;
            
        }

        bool isStairTile_L1(uint8_t tile) {

            return tile == 10;
            
        }

        bool isStairTile_L_Half(uint8_t tile) {

            return tile == 11;
            
        }

        bool isStairTile_L2(uint8_t tile) {

            return tile == 9;
            
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

        bool isRopeTile(uint8_t tile) {

            return tile == 15;
            
        }

        // Spring ----------------------------------

        bool isSpringTile(uint8_t tile) {

            return tile == 16 || tile == 17;
            
        }

        bool isSpringTile_LH(uint8_t tile) {

            return tile == 16;
            
        }

        bool isSpringTile_RH(uint8_t tile) {

            return tile == 17;
            
        }

        // Slides ----------------------------------
        
        bool isSlideTile_LH(uint8_t tile) {

            return tile == 19;
            
        }

        bool isSlideTile_Full_LH(uint8_t tile) {

            return tile == 20;
            
        }
        
        bool isSlideTile_RH(uint8_t tile) {

            return tile == 21;
            
        }

        bool isSlideTile_Full_RH(uint8_t tile) {

            return tile == 22;
            
        }

        bool isWoodenBarrier(uint8_t tile) {

            return tile == 24;
            
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

            return tile == 29;
            
        }        

        bool isVineTile_RH(uint8_t tile) {

            return tile == 30;
            
        }       


        void updateEnemies() {

            for (uint8_t i  = 0; i < Constants::EnemyCount; i++) {

                Enemy &enemy = this->getEnemy(i);

                if (enemy.getX() == 0) continue;

                if (enemy.getCount() == 0 && random(0, 120) == 0) {

                    enemy.pushSequence(Stance::Enemy_Fire_LH_00, Stance::Enemy_Fire_LH_12);

                }

                if (enemy.getItem().getItemType() != ItemType::None) {
                    enemy.getItem().update();
                }

            }

        } 
};