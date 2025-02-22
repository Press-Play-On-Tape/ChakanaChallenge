#pragma once

// #include "Boat.h"
#include "../utils/Constants.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"


struct World {

    public:

        uint8_t mapData[Constants::Map_Y_Count][Constants::Map_X_Count];

    private:
        
        GameState gameState = GameState::SplashScreen_Start;
        GameState prevGameState = GameState::SplashScreen_Start;

        Player player;
        Enemy enemy[Constants::EnemyCount];
        Item items[Constants::ItemCount_Level];

        uint16_t portsVisited;
        uint16_t frameCount;
        uint16_t xMap;
        uint16_t yMap;
        uint16_t xBoat;
        uint16_t yBoat;
        BoatDirection boatDirection;
        uint8_t boatCounter;
        int16_t y = 0;

        uint8_t currentPort;
        uint8_t nextPort;
        uint8_t nextPortCost;

        int16_t wave = 0;
        int16_t palm[8];

        uint16_t waveIdx = 0;
        int16_t background = 0;
        int16_t middleground = 0;

        // Boat boat;

    public:

        GameState getGameState()                        { return this->gameState; }
        GameState getPrevGameState()                    { return this->prevGameState; }

        Item &getItem(uint8_t idx)                      { return this->items[idx]; }
        Player &getPlayer()                             { return this->player; }
        Enemy &getEnemy(uint8_t idx)                    { return this->enemy[idx]; }
        uint16_t getXMap()                              { return this->xMap; }
        uint16_t getYMap()                              { return this->yMap; }
        uint16_t getXBoat()                             { return this->xBoat; }
        uint16_t getYBoat()                             { return this->yBoat; }
        BoatDirection  getBoatDirection()               { return this->boatDirection; }
        uint8_t  getBoatCounter()                       { return this->boatCounter; }
        uint16_t getFrameCount()                        { return this->frameCount; }
        uint8_t  getCurrentPort()                       { return this->currentPort; }
        uint8_t  getNextPort()                          { return this->nextPort; }
        uint8_t  getNextPortCost()                      { return this->nextPortCost; }

        // int16_t getX()                                  { return this->x; }
        int16_t getY()                                  { return this->y; }

        int16_t getWave()                               { return this->wave; }
        int16_t getBackground()                         { return this->background; }
        int16_t getMiddleground()                       { return this->middleground; }
        uint16_t getWaveIdx()                           { return this->waveIdx; }

        // Boat& getBoat()                                 { return this->boat; }

        void setGameState(GameState val)                { this->gameState = val; }
        void setPrevGameState(GameState val)            { this->prevGameState = val; }

        void setXMap(uint16_t val)                      { this->xMap = val; }
        void setYMap(uint16_t val)                      { this->yMap = val; }
        void setXBoat(uint16_t val)                     { this->xBoat = val; }
        void setYBoat(uint16_t val)                     { this->yBoat = val; }
        void setBoatDirection(BoatDirection val)        { this->boatDirection = val; }
        void setBoatCounter(uint8_t val)                { this->boatCounter = val; }
        void setFrameCount(uint16_t val)                { this->frameCount = val; }
        void setCurrentPort(uint8_t val)                { this->currentPort = val; }
        void setNextPort(uint8_t val)                   { this->nextPort = val; }
        void setNextPortCost(uint8_t val)               { this->nextPortCost = val; }

        // void setX(int16_t val)                          { this->x = val; }
        void setY(int16_t val)                          { this->y = val; }

        void setWave(int16_t val)                       { this->wave = val; }
        void setBackground(int16_t val)                 { this->background = val; }
        void setMiddleground(int16_t val)               { this->middleground = val; }
        void setWaveIdx(uint16_t val)                   { this->waveIdx = val; }

    public:

        void init() {

            this->portsVisited = 0;
            this->frameCount = 0;
            this->xMap = 0;
            this->yMap = 0;
            this->xBoat = 14;
            this->yBoat = 6;
            this->boatDirection = BoatDirection::Down;
            this->boatCounter = 0;
            this->y = 0;

            this->currentPort = 255;
            this->nextPort = 255; 
            this->nextPortCost = 0;

        }

        void init_Level() {

            this->gameState = GameState::Play_Game;
            this->frameCount = 0;
            this->middleground = 0;
            this->background = -29;
            this->wave = -87;

            this->player.setY(Constants::GroundY);
            this->player.setStance(Stance::Man_Walk_RH_00);

        }

        uint8_t getYOffsetForRendering() {

            switch (player.getY()) {

                case 21 ... 37: 
                    return Constants::GroundY;

                case -53 ... 20:
                    return Constants::GroundY - player.getY() + 22;

                default:
                    return 112;

            }

        }

        void setPortVisited(uint8_t portId) {

            this->portsVisited = this->portsVisited | (1 << portId);

        }

        bool getPortVisited(uint8_t portId) {

            return (this->portsVisited & (1 << portId)) > 0;

        }

        bool allPortsComplete() {

            return (this->portsVisited == Constants::AllPortsComplete);

        }

        int16_t getPalm(uint8_t idx) { return this->palm[idx]; }

        int16_t setPalm(uint8_t idx, int16_t val) { this->palm[idx] = val; }

        void incFrameCount() {

            this->frameCount++;

        }

        void incGameState() {

            this->gameState++;

        }

        void decGameState() {

            this->gameState--;

        }

        bool absT(int8_t x) {
            return x < 0 ? -x : x;
        }

        uint8_t getBoatCoords_Offset() {

            uint8_t from = this->getNextPort();
            uint8_t to = this->getCurrentPort();

            if (from < 255 && to < 255) {

                return FX::readIndexedUInt8(Constants::PortOffsets, (to * 14) + from) + (absT(from - to) == 1 ? 2 : 0);

            }
            
            return 0;

        }

        boolean updateBoat() { // true - end of sequence

            if (this->frameCount % 4 == 0) {

                uint8_t offset = getBoatCoords_Offset();
                uint24_t boatCoords = FX::readIndexedUInt24(Constants::BoatCoords, (this->getCurrentPort() << 2) + offset);

                BoatMovement boatMovement;
                FX::seekData(boatCoords + (this->boatCounter * 3));
                FX::readObject(boatMovement);          
                FX::readEnd();

                if (boatMovement.x != 0 || boatMovement.y !=0) {

                    this->xBoat = this->xBoat + boatMovement.x;
                    this->yBoat = this->yBoat + boatMovement.y;
                    this->boatDirection = static_cast<BoatDirection>(boatMovement.direction);
                    this->boatCounter++;
                    return false;
                }

                return true;

            }

            return false;
        
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

            this->background += val;

            if (this->background == 128 || this->background == -128) {
                this->background = 0;
            }

        }

        bool incMiddleground(int8_t val) {

            // if (this->middleground + val > 0) {
            //     this->middleground = 0;
            //     return false;
            // }
            if (this->middleground + val <= -496) {
                this->middleground = -496;
                return false;
            }

            this->middleground = this->middleground + val;
            return true;

        }

        void incPalm(uint8_t idx, int8_t val) {

            this->palm[idx] = this->palm[idx] + val;

        }

        void incWave(int8_t val) {

            this->wave += val;
            this->wave = (wave + 256) % 512 - 256;

        }

        void setMap(Item &item) {
                            
            uint8_t x = (item.getX() - 144) >> 3;
            uint8_t y = item.getY() >> 3;

            #ifdef DEBUG_SET_MAP

                DEBUG_PRINT("C ");
                DEBUG_PRINT(item.getX());
                DEBUG_PRINT(" ");
                DEBUG_PRINT(item.getY());
                DEBUG_PRINT(" - ");
                DEBUG_PRINT(x);
                DEBUG_PRINT(" ");
                DEBUG_PRINTLN(y);

            #endif

            this->mapData[y][x] = 0;
            this->mapData[y][x + 1] = 0;
            this->mapData[y + 1][x] = 0;
            this->mapData[y + 1][x + 1] = 0;

        }

        void update(bool completeWaves) {

            uint8_t removeItemIdx = Constants::NoItem;

            for (uint8_t i = 0; i < Constants::ItemCount_Level; i++) {

                Item &item = this->items[i];
                ItemType itemType = item.getItemType();
                bool addInventoryItem = false;

                if (itemType == ItemType::None) break;
                
                ItemAction action = item.update();
                bool doClearMap = false;

                switch (action) {

                    case ItemAction::Remove:
                        removeItemIdx = i;
                        break;

                    case ItemAction::HideCrate_ShowItem:
                        doClearMap = true;
                        item.setItemType(static_cast<ItemType>(item.getData()));
                        item.setFrame(0);
                        item.setCounter(0);
                        item.setData(0);
                        break;

                    case ItemAction::HideWoodenBarrier:                        
                        doClearMap = true;
                        break;

                    case ItemAction::Remove_AddToInventory:
                        addInventoryItem = true;
                        removeItemIdx = i;
                        break;

                    case ItemAction::ChangeToHidden:
                        addInventoryItem = true;
                        item.setItemType(static_cast<ItemType>(static_cast<uint8_t>(itemType) + 1));
                        break;

                }

                if (doClearMap) {
                    setMap(item);
                }

                if (addInventoryItem) {                        
                    player.addInventoryItem(itemType);
                }

                uint8_t yOffset = this->getYOffsetForRendering();
                // Rect playerRect = { 59, Constants::GroundY - player.getY() + 6, 10, 16 };
                Rect playerRect = { 59, yOffset - Constants::GroundY + player.getY(), 10, 16 };

                switch (item.getItemType()) {

                    case ItemType::SwingyThing:
                        {  

                            int8_t swingyThing_X = FX::readIndexedUInt8(Constants::swingyThing_X, item.getFrame());
                            int8_t swingyThing_Y = FX::readIndexedUInt8(Constants::swingyThing_Y, item.getFrame());

                            int16_t itemX = item.getX() + 6 + 2 + swingyThing_X;
                            int8_t itemY = yOffset - item.getY() + swingyThing_Y + 11;
                            uint8_t puffX = 0;

                            Rect itemRect = { itemX + this->getMiddleground() - 4, itemY, 16, 3 };

                            if (collide(playerRect, itemRect)) {

// Serial.print(playerRect.x);
// Serial.print(" ");
// Serial.print(playerRect.y);
// Serial.print(" ");
// Serial.print(playerRect.width);
// Serial.print(" ");
// Serial.print(playerRect.height);
// Serial.print(" - ");
// Serial.print(itemRect.x);
// Serial.print(" ");
// Serial.print(itemRect.y);
// Serial.print(" ");
// Serial.print(itemRect.width);
// Serial.print(" ");
// Serial.println(itemRect.height);
// DEBUG_BREAK

                                switch (player.getDirection()) {

                                    case Direction::Left:
                                        {
                                            switch (item.getFrame()) {

                                                case 0 ... 8:
                                     
                                                    player.pushSequence(Stance::Man_Die_FWD_LH_01, Stance::Man_Die_FWD_LH_04, true);
                                                    break;

                                                default:
                                         
                                                    puffX = itemRect.width;
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
                                 
                                                    player.pushSequence(Stance::Man_Die_BWD_RH_01, Stance::Man_Die_BWD_RH_04, true);
                                                    break;

                                                default:
                                           
                                                    puffX = itemRect.width;
                                                    player.pushSequence(Stance::Man_Die_FWD_RH_01, Stance::Man_Die_FWD_RH_04, true);
                                                    break;
                                                    
                                            }

                                        }

                                        break;

                                }

                                if (puffX != 0) {

                                    initPuff(itemX - 8 + puffX, itemY - 16);

                                }

                            }

                        }

                        break;

                }

            }

            if (removeItemIdx != Constants::NoItem) {
                this->removeItem(removeItemIdx);
            }


            // Increment waves ..

            if (this->waveIdx == Constants::NoWaves) return;

            this->waveIdx++;

            if (this->waveIdx >= 6 * 64) this->waveIdx = 0;

            if (completeWaves && this->waveIdx == 4 * 64) {

                this->waveIdx = Constants::NoWaves;

            }


        }

        void removeItem(uint8_t itemIdx) {

            for (uint8_t i = itemIdx; i < Constants::ItemCount_Level - 1; i++) {

                this->items[i].setItemType(items[i + 1].getItemType());
                this->items[i].setFrame(items[i + 1].getFrame());
                this->items[i].setX(items[i + 1].getX());
                this->items[i].setY(items[i + 1].getY());
                this->items[i].setData(items[i + 1].getData());
                this->items[i].setCounter(items[i + 1].getCounter());

            }

            this->items[Constants::ItemCount_Level - 1].setItemType(ItemType::None);

        }

        uint8_t getItem(ItemType itemType1, ItemType itemType2) {

            for (uint8_t i = 0; i < Constants::ItemCount_Level; i++) {

                if (this->items[i].getItemType() == itemType1) return i;
                if (this->items[i].getItemType() == itemType2) return i;

            }

            return Constants::NoItem;

        }

        uint8_t getItem(ItemType itemType) {

            for (uint8_t i = 0; i < Constants::ItemCount_Level; i++) {

                if (this->items[i].getItemType() == itemType) return i;

            }

            return Constants::NoItem;

        }

        uint8_t getItem(int16_t xPos, uint8_t yPos) {

            for (uint8_t i = 0; i < Constants::ItemCount_Level; i++) {

                if (this->items[i].getItemType() == ItemType::Puff) {
                    break;
                }

                if (this->items[i].getX() == xPos && this->items[i].getY() == yPos) {
                    return i;
                }

            }

            return Constants::NoItem;

        };

        uint8_t getTile(int8_t xOffset, int8_t yOffset) {

            if (xOffset < 18) return Tiles::Blank;
            return mapData[yOffset][xOffset - 18];

        }

        uint8_t getTile_RelativeToPlayer(int8_t xOffset, int8_t yOffset) {

            if (player.getLevel() + yOffset < 0) return Tiles::Solid_Walkable;

            int16_t tileIdx = (-this->getMiddleground() + 65 + (xOffset << 3)) >> 3;

            if (tileIdx < 18) return Tiles::Blank;
            return mapData[this->player.getLevel() + yOffset][tileIdx - 18];

        }

        uint8_t getTile_FromCoords(int16_t xPosition, int8_t yPosition) {

            

            int16_t tileIdx = xPosition / 8;
// Serial.print("(Tile ");
// Serial.print(tileIdx);
// Serial.print(") ");
            if (tileIdx < 18) return Tiles::Blank;
            return mapData[yPosition >> 3][tileIdx - 18];

        }

        bool canWalkPastTile(uint8_t tile) {

            return canWalkPastTile(tile, Direction::None);

        }

        bool canWalkPastTile(uint8_t tile, Direction direction) {
            
            if (tile == Tiles::Solid_Blocking)                                          return false;
            else if (player.getLevel() == 0)                                            return true;
            else if (tile == Tiles::Solid_Walkable)                                     return false;
            else if (tile == Tiles::Poker)                                              return true;

            else if (tile == Tiles::Lever_Portal_LH) { 

                if (direction == Direction::Left) { 

                    return true;

                }

                if (direction != Direction::Left) { 

                    return this->getItem(ItemType::Lever_Portal_Open) < Constants::NoItem;
                    
                }

            }
            else if (tile == Tiles::Lever_Portal_Auto_LH) {
                
                if (direction == Direction::Left) { 

                    return true;

                }

                if (direction != Direction::Left) { 

                    return this->getItem(ItemType::Lever_Portal_Auto_Open) < Constants::NoItem;
                    
                }

            }
            else if (tile == Tiles::Lever_Portal_RH) {
                
                if (direction == Direction::Right) { 

                    return true;

                }

                if (direction != Direction::Right) { 

                    return this->getItem(ItemType::Lever_Portal_Open) < Constants::NoItem;
                    
                }

            }
            else if (tile == Tiles::Lever_Portal_Auto_RH) {

                if (direction == Direction::Right) { 

                    return true;

                }

                if (direction != Direction::Right) { 

                    return this->getItem(ItemType::Lever_Portal_Auto_Open) < Constants::NoItem;
                    
                }

            }
          
            else if (tile == Tiles::WoodenBarrier) { 

                return false; 
                
            }

            else if (tile == Tiles::Mystery_Crate) { 

                return false; 
                
            }

            #ifndef DEBUG_LOCKED_DOOR

                else if (tile == Tiles::LockedDoor) { 

                    uint8_t idx = this->getItem(ItemType::LockedDoor);

                    if (idx != Constants::NoItem) {
                        
                        Item &item = this->items[idx];
                        return item.getFrame() == 4;

                    }

                    return false; 
                    
                }

            #endif

            return tile == Tiles::Blank || /*tile == Tiles::Solid_Walkable ||*/ tile == Tiles::Ladder_Lower || tile == Tiles::Ladder_Middle || tile == Tiles::Rope_Support_LH /*rope lh*/ || 
                tile == Tiles::Rope_Support_RH /*rope rh*/ || tile == Tiles::Spring_LH || tile == Tiles::Spring_RH || tile == Tiles::Punji ||
                tile == Tiles::Swinging_Vine_LH || tile == Tiles::Swinging_Vine_RH || tile == Tiles::Vine_Lower;
            
        }

        bool canWalkOnLifeSaver(uint8_t tile) {

            if (tile == Tiles::Water_Plain) {

                uint8_t idx = this->getItem(ItemType::LifeSaver_InWater_LH, ItemType::LifeSaver_InWater_RH);

                if (idx == Constants::NoItem) {

                    idx = this->getItem(ItemType::LifeSaver_Dissolve_InWater_LH, ItemType::LifeSaver_Dissolve_InWater_RH);

                }

                return idx != Constants::NoItem;

            }

            return false;

        }

        bool canWalkOnTile(uint8_t tile) {

            if (tile == Tiles::Water_Plain) {

                return canWalkOnLifeSaver(tile);

            }
            else {
    
                return tile == Tiles::Solid_Walkable || 
                    tile == Tiles::Single_Stair_LH_Upper_TL || 
                    tile == Tiles::Rollers_Left || tile == Tiles::Rollers_Right;

            }
            
        }

        bool isPunjiTile(uint8_t tile) {

            return tile == Tiles::Punji;
            
        }

        bool canJumpUpOntoTile(uint8_t tile) {

            return tile == Tiles::Solid_Walkable || tile == Tiles::Rollers_Left || tile == Tiles::Rollers_Right;

        }

        #ifdef FALL_THROUGH_PORTAL

        bool isEmptyTile(uint8_t tile) {

            return isEmptyTile_XY(tile, Constants::NoOffset, Constants::NoOffset);

        }

        bool isEmptyTile_XY(uint8_t tile, int8_t relX, int8_t relY) {

            if (relX != Constants::NoOffset) {

                if (tile == Tiles::Lever_Portal_LH || tile == Tiles::Lever_Portal_RH ||
                    tile == Tiles::Lever_Portal_Auto_LH || tile == Tiles::Lever_Portal_Auto_RH) {
                            
                    int16_t xItem = -this->getMiddleground() + 64 + (relX << 3);
                    uint8_t yItem = (this->player.getLevel() + relY - 1) * 8;

                    if (xItem % 16 != 0) xItem = xItem - 8;
                    if (yItem % 16 != 0) yItem = yItem + 8;
                    
                    uint8_t idx = this->getItem(xItem, yItem);

                    if (idx != Constants::NoItem) {

                        Item &item = this->getItem(idx);

                        switch (item.getItemType()) {

                            case ItemType::Lever_Portal_Open:
                            case ItemType::Lever_Portal_Auto_Open:
                                return true;

                        }

                    }
                    
                    return false;

                }

            }

            return tile == Tiles::Blank || tile == Tiles::Spikes || 
                   tile == Tiles::Swinging_Vine_LH || tile == Tiles::Swinging_Vine_RH || 
                   tile == Tiles::Vine_Lower ||
                   tile == Tiles::Water_Plain || tile == Tiles::Water_Bubbling_1 || 
                   tile == Tiles::Water_Bubbling_2 || tile == Tiles::Poker;
            
        }

        #else

        bool isEmptyTile(uint8_t tile) {

            return tile == Tiles::Blank || tile == Tiles::Spikes || 
                   tile == Tiles::Swinging_Vine_LH || tile == Tiles::Swinging_Vine_RH || 
                   tile == Tiles::Vine_Lower ||
                   tile == Tiles::Water_Plain || tile == Tiles::Water_Bubbling_1 || 
                   tile == Tiles::Water_Bubbling_2 || tile == Tiles::Poker;
            
        }

        #endif

        #ifdef SHOW_SIGN

        bool isSignTile(uint8_t tile) {

            return tile == Tiles::Sign_01;
            
        }

        #endif

        bool isSpikeTile(uint8_t tile) {

            return tile == Tiles::Spikes;
            
        }

        bool isWaterTile(uint8_t tile) {

            return tile == Tiles::Water_Plain || tile == Tiles::Water_Bubbling_1 || tile == Tiles::Water_Bubbling_2;
            
        }

        bool isStairTile_R1(uint8_t tile) {

            return tile == Tiles::Single_Stair_RH_Upper_TL;
            
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

        bool isLadderTile(uint8_t tile) {

            return tile == Tiles::Ladder_Lower || tile == Tiles::Ladder_Middle || tile == Tiles::Ladder_Upper;
            
        }

        bool isLadderTile_Lower(uint8_t tile) {

            return tile == Tiles::Ladder_Lower;
            
        }

        bool isLadderTile_Middle(uint8_t tile) {

            return tile == Tiles::Ladder_Middle;
            
        }

        bool isLadderTile_Upper(uint8_t tile) {

            return tile == Tiles::Ladder_Upper;
            
        }

        bool isRopeSupport(uint8_t tile) {

            return tile == Tiles::Rope_Support_LH || tile == Tiles::Rope_Support_RH;
            
        }

        // Vertical vine ---------------------------

        bool isVerticalVine_CanClimbUp(uint8_t tile) {

            return tile == Tiles::Vine_Lower || tile == Tiles::Vine_Middle;
            
        }

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

            return tile == Tiles::Rope;
            
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

            return tile == Tiles::WoodenBarrier;
            
        }

        bool isMysteryCrate(uint8_t tile) {

            return tile == 25;
            
        }

        bool isLockedDoor(uint8_t tile) {

            return tile == 26;
            
        }

        bool isRollerTile_RH(uint8_t tile) {

            return tile == Tiles::Rollers_Left;
            
        }

        bool isRollerTile_LH(uint8_t tile) {

            return tile == Tiles::Rollers_Right;
            
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

                        if (enemy.getCount() == 0 && a.randomLFSR(0, 140) == 0) {

                            const uint16_t diff = Stance::Enemy_Fire_LH_00 - Stance::Enemy_Fire_RH_00;
                            uint16_t stanceOffset = (enemy.getDirection() == Direction::Left ? diff : 0);
                            enemy.pushSequence(Stance::Enemy_Fire_RH_00 + stanceOffset, Stance::Enemy_Fire_RH_12 + stanceOffset);

                        }

                        break;

                    // case ItemType::Trebochet_Ball_Left_1 ... ItemType::Trebochet_Ball_Right_Hidden:

                    //     if (this->gameState != GameState::Play_Dead) {
                                
                    //         if (enemy.getCount() == 0 && a.randomLFSR(0, 120) == 0) {

                    //             switch (enemy.getDirection()) {

                    //                 case Direction::Left:
                    //                     enemy.pushSequence(Stance::Enemy_Trebochet_Release_LH_01, Stance::Enemy_Trebochet_Release_LH_14);
                    //                     break;

                    //                 case Direction::Right:
                    //                     enemy.pushSequence(Stance::Enemy_Trebochet_Release_RH_01, Stance::Enemy_Trebochet_Release_RH_14);
                    //                     break;

                    //             }

                    //         }

                    //     }

                    //     break;

                    case ItemType::Trebochet_Ball_Left_1 ... ItemType::Trebochet_Ball_Right_Hidden:

                        if (item.getData() > 0) item.setData(item.getData() - 1);

                        if (item.getData() == 0 && this->gameState != GameState::Play_Dead) {
                                
                            if (enemy.getCount() == 0 && a.randomLFSR(0, 40) == 0) {

                                const uint16_t diff = Stance::Enemy_Trebochet_Release_LH_01 - Stance::Enemy_Trebochet_Release_RH_01;
                                uint16_t stanceOffset = (enemy.getDirection() == Direction::Left ? diff : 0);
                                enemy.pushSequence(Stance::Enemy_Trebochet_Release_RH_01 + stanceOffset, Stance::Enemy_Trebochet_Release_RH_14 + diff);

                            }

                        }

                        break;

                }

                switch (item.getItemType()) {

                    // case ItemType::Arrow_LH:
                    //     {
                    //         enemy.getItem().update();

                    //         uint8_t yOffset = Constants::GroundY;
                    //         if (player.getY() < 5) yOffset = Constants::GroundY - player.getY();

                    //         Rect playerRect = { 59, yOffset - Constants::GroundY + player.getY(), 10, 16 };
                    //         Rect arrowRect = { enemy.getItem().getX() + this->getMiddleground() - 4 + 1, yOffset - enemy.getItem().getY() + 1, 9, 3 };
                            
                    //         if (collide(playerRect, arrowRect)) {

                    //             enemy.getItem().setItemType(ItemType::None);

                    //             switch (this->player.getDirection()) {

                    //                 case Direction::Right:
                    //                     this->player.pushSequence(Stance::Man_Die_Arrow_FallBackward_RH_01, Stance::Man_Die_Arrow_FallBackward_RH_04, true);
                    //                     break;

                    //                 case Direction::Left:
                    //                     this->player.pushSequence(Stance::Man_Die_Arrow_FallForward_LH_01, Stance::Man_Die_Arrow_FallForward_LH_04, true);
                    //                     break;
                                        
                    //             }

                    //         }

                    //     }

                    //     break;

                    // case ItemType::Arrow_RH:
                    //     {
                    //         enemy.getItem().update();

                    //         uint8_t yOffset = Constants::GroundY;
                    //         if (player.getY() < 5) yOffset = Constants::GroundY - player.getY();

                    //         Rect playerRect = { 59, yOffset - Constants::GroundY + player.getY(), 10, 16 };
                    //         Rect arrowRect = { enemy.getItem().getX() + this->getMiddleground() - 4 + 1, yOffset - enemy.getItem().getY() + 1, 9, 3 };
                            
                    //         if (collide(playerRect, arrowRect)) {

                    //             enemy.getItem().setItemType(ItemType::None);

                    //             switch (this->player.getDirection()) {

                    //                 case Direction::Right:
                    //                     this->player.pushSequence(Stance::Man_Die_Arrow_FallForward_RH_01, Stance::Man_Die_Arrow_FallForward_RH_04, true);
                    //                     break;

                    //                 case Direction::Left:
                    //                     this->player.pushSequence(Stance::Man_Die_Arrow_FallBackward_LH_01, Stance::Man_Die_Arrow_FallBackward_LH_04, true);
                    //                     break;
                                        
                    //             }

                    //         }

                    //     }

                    //     break;

                    case ItemType::Arrow_LH:
                    case ItemType::Arrow_RH:
                        {
                            enemy.getItem().update();

                            Rect playerRect = { 59, player.getY(), 10, 16 };
                            Rect arrowRect = { enemy.getItem().getX() + this->getMiddleground() - 4 + 1, Constants::GroundY - enemy.getItem().getY() - 1, 9, 3 };

                            #ifdef ARROW

                            DEBUG_PRINT(playerRect.x);
                            DEBUG_PRINT(" ");
                            DEBUG_PRINT(playerRect.y);
                            DEBUG_PRINT(" - ");
                            DEBUG_PRINT(arrowRect.x);
                            DEBUG_PRINT(" ");
                            DEBUG_PRINTLN(arrowRect.y);

                            #endif

                            if (collide(playerRect, arrowRect)) {

                                if (this->player.getHealth() < 4) {

                                    Stance stance;

                                    bool isArrowTravellingRight = (item.getItemType() == ItemType::Arrow_RH);
                                    bool isPlayerFacingRight = (this->player.getDirection() == Direction::Right);

                                    if (isArrowTravellingRight) {

                                        stance = isPlayerFacingRight ? Stance::Man_Die_Arrow_FallForward_RH_01 : Stance::Man_Die_Arrow_FallBackward_LH_01;

                                    } else {

                                        stance = isPlayerFacingRight ? Stance::Man_Die_Arrow_FallBackward_RH_01 : Stance::Man_Die_Arrow_FallForward_LH_01;
                                        
                                    }

                                    enemy.getItem().setItemType(static_cast<ItemType>(static_cast<uint8_t>(enemy.getItem().getItemType()) + 1));
                                    this->player.pushSequence(stance, stance + 3, true);

                                }
                                else {

                                    this->player.setWound(12);
                                    this->player.setEnemyIdx(0);

                                    if (item.getItemType() == ItemType::Arrow_LH) {

                                        enemy.getItem().setItemType(ItemType::Arrow_LH_Hidden);

                                    }
                                    else {

                                        enemy.getItem().setItemType(ItemType::Arrow_RH_Hidden);

                                    }

                                    this->player.setHealth(this->player.getHealth() - 4);

                                }

                            }

                        }

                        break;


                    // case ItemType::Trebochet_Ball_Left_1 ... ItemType::Trebochet_Ball_Left_3:
                    //     {
                    //         enemy.getItem().update(); 

                    //         // uint8_t yOffset = this->getYOffsetForRendering();
                    //         // Rect playerRect = { 59, yOffset - Constants::GroundY + player.getY(), 10, 16 };
                    //         // Rect trebochetRect = { enemy.getItem().getX() + this->getMiddleground() - 4, yOffset - enemy.getItem().getY(), 4, 4 };
                    //         Rect playerRect = { 59, Constants::GroundY - player.getY(), 10, 16 };
                    //         // Rect trebochetRect = { enemy.getItem().getX() + this->getMiddleground() - 4, enemy.getItem().getY(), 4, 4 };
                    //         Rect trebochetRect = { enemy.getItem().getX() + this->getMiddleground() - 3, enemy.getItem().getY(), 4, 4 };
                          
                    //         if (collide(playerRect, trebochetRect)) {

                    //             enemy.getItem().setItemType(ItemType::Trebochet_Ball_Left_Hidden);
                    //             enemy.getItem().setFrame(0);
                    //             item.setCounter(3);

                    //             this->initPuff(item.getX(), item.getY());
                    //             Stance stance = 0;

                    //             switch (this->player.getDirection()) {

                    //                 case Direction::Right:
                    //                     stance = Stance::Man_Die_BWD_RH_01;
                    //                     // this->player.pushSequence(Stance::Man_Die_BWD_RH_01, Stance::Man_Die_BWD_RH_04, true);
                    //                     break;

                    //                 case Direction::Left:
                    //                     stance = Stance::Man_Die_FWD_LH_01;
                    //                     // this->player.pushSequence(Stance::Man_Die_FWD_LH_01, Stance::Man_Die_FWD_LH_04, true);
                    //                     break;
                                        
                    //             }

                    //             this->player.pushSequence(stance, stance + 3, true);

                    //         }                            

                    //     }
                    //     break;   

                    // case ItemType::Trebochet_Ball_Right_1 ... ItemType::Trebochet_Ball_Right_3:
                    //     {
                    //         enemy.getItem().update(); 

                    //         // uint8_t yOffset = this->getYOffsetForRendering();
                    //         // Rect playerRect = { 59, yOffset - Constants::GroundY + player.getY(), 10, 16 };
                    //         // Rect trebochetRect = { enemy.getItem().getX() + this->getMiddleground() - 4, yOffset - enemy.getItem().getY(), 4, 4 };
                    //         Rect playerRect = { 59, Constants::GroundY - player.getY(), 10, 16 };
                    //         Rect trebochetRect = { enemy.getItem().getX() + this->getMiddleground() - 4, enemy.getItem().getY(), 4, 4 };
                            
                    //         if (collide(playerRect, trebochetRect)) {

                    //             enemy.getItem().setItemType(ItemType::Trebochet_Ball_Right_Hidden);
                    //             enemy.getItem().setFrame(0);
                    //             item.setCounter(3);
                    //             Stance stance = 0;

                    //             this->initPuff(item.getX(), item.getY());

                    //             switch (this->player.getDirection()) {

                    //                 case Direction::Right:
                    //                     stance = Stance::Man_Die_FWD_RH_01;
                    //                     // this->player.pushSequence(Stance::Man_Die_FWD_RH_01, Stance::Man_Die_FWD_RH_04, true);
                    //                     break;

                    //                 case Direction::Left:
                    //                     stance = Stance::Man_Die_BWD_LH_01;
                    //                     // this->player.pushSequence(Stance::Man_Die_BWD_LH_01, Stance::Man_Die_BWD_LH_04, true);
                    //                     break;
                                        
                    //             }

                    //             this->player.pushSequence(stance, stance + 3, true);

                    //         }                            

                    //     }
                    //     break;  



                    case ItemType::Trebochet_Ball_Left_1 ... ItemType::Trebochet_Ball_Left_3:
                    case ItemType::Trebochet_Ball_Right_1 ... ItemType::Trebochet_Ball_Right_3:
                        {
                            ItemType itemType = item.getItemType();
                            enemy.getItem().update();

                            Rect playerRect = { 59, Constants::GroundY - player.getY(), 10, 16 };
                            int xOffset = (itemType >= ItemType::Trebochet_Ball_Left_1) ? -3 : -4;
                            Rect trebochetRect = { enemy.getItem().getX() + this->getMiddleground() + xOffset, enemy.getItem().getY(), 4, 4 };
                            
                            if (collide(playerRect, trebochetRect)) {
                                
                                ItemType hiddenType = (itemType >= ItemType::Trebochet_Ball_Left_1) ?
                                    ItemType::Trebochet_Ball_Left_Hidden : ItemType::Trebochet_Ball_Right_Hidden;
                                
                                enemy.getItem().setItemType(hiddenType);
                                enemy.getItem().setFrame(0);
                                item.setCounter(3);
                                this->initPuff(item.getX(), item.getY());
                                
                                Stance stance = (this->player.getDirection() == Direction::Right) ?
                                    ((itemType >= ItemType::Trebochet_Ball_Left_1) ? Stance::Man_Die_BWD_RH_01 : Stance::Man_Die_FWD_RH_01) :
                                    ((itemType >= ItemType::Trebochet_Ball_Left_1) ? Stance::Man_Die_FWD_LH_01 : Stance::Man_Die_BWD_LH_01);
                                
                                this->player.pushSequence(stance, stance + 3, true);

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
