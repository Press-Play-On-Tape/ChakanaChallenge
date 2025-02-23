#pragma once

#include <Arduboy2.h>   
#include "../utils/Constants.h"
#include "../utils/Stack.h"
#include "InventoryItem.h"

class Player {

    private:

        Stance stance = Stance::Man_Walk_BK_01;
        InventoryItem items[Constants::ItemCount_Player];

        int8_t y = Constants::GroundY;
        uint8_t falls;
        uint8_t itemCount;
        int8_t health;
        uint8_t enemyIdx;
        uint8_t wound;
        uint8_t chakanas;
        uint8_t lives;
		
        Stance fromStance = Stance::None;
        Stance toStance = Stance::None;
        
        Stack <Stance, Constants::StackSize_Player> stack;

    public:

        Stance getStance()                                  { return this->stance; }
        InventoryItem &getItem(uint8_t idx)                 { return this->items[idx]; }

        int8_t getY()                                       { return this->y; }
        uint8_t getFalls()                                  { return this->falls; }
        uint8_t getLevel()                                  { return (Constants::GroundY - y) >> 3; }
        uint8_t getItemCount()                              { return this->itemCount; }
        int8_t getHealth()                                  { return this->health; }
        uint8_t getEnemyIdx()                               { return this->enemyIdx; }
        uint8_t getWound()                                  { return this->wound; }
        uint8_t getChakanas()                               { return this->chakanas; }
        uint8_t getLives()                                  { return this->lives; }

        void setStance(Stance val)                          { this->stance = val; }

        void setY(int8_t val)                               { this->y = val; }
        void setFalls(uint8_t val)                          { this->falls = val; }
        void setItemCount(uint8_t val)                      { this->itemCount = val; }
        void setHealth(int8_t val)                          { this->health = val; }
        void setEnemyIdx(uint8_t val)                       { this->enemyIdx = val; }
        void setWound(uint8_t val)                          { this->wound = val; }
        void setChakanas(uint8_t val)                       { this->chakanas = val; }
        void setLives(uint8_t val)                          { this->lives = val; }

        void incY(int8_t val)                               { this->y = this->y + val; }
        void incFalls()                                     { this->falls++; }

        void init() {

            this->lives = 3;
            this->falls = 0;
            this->itemCount = 0;
            this->health = Constants::HealthMax;
            this->enemyIdx = Constants::NoEnemy;
            this->wound = 0;
            
            #ifdef DEBUG_LOTS_OF_CHAKANAS
            this->chakanas = 255;
            #else
            this->chakanas = 20;
            #endif

        }

        uint8_t getY_RelativeToGround() {

            return Constants::GroundY - this->y;

        }

        bool decHealth(uint8_t i) {

            this->health = this->health - i;
            return this->health <= 0;
            
        }

        void decWound(uint8_t i) {

            this->wound = this->wound - i;
            
        }


        // Invetory Methods ---------------------------------------

        void removeInventoryItem(uint8_t itemIdx) {

            for (uint8_t i = itemIdx; i < Constants::ItemCount_Player - 1; i++) {

                this->items[i].setItemType(items[i + 1].getItemType());

            }

            this->items[Constants::ItemCount_Player - 1].setItemType(ItemType::None);
            this->itemCount--;

        }

        void addInventoryItem(ItemType itemType) {

            for (uint8_t i = 0; i < Constants::ItemCount_Player - 1; i++) {

                if (this->items[i].getItemType() == ItemType::None) {

                    this->items[i].setItemType(itemType);
                    break;
                    
                }

            }

            this->itemCount++;

        }


        // Other Utils ..

        Direction getDirection() {

            switch (this->getStance()) {

                case Stance::Man_BK_Start ... Stance::Man_BK_End:
                case Stance::Man_Rope_Start_LH_01 ... Stance::Man_Rope_Start_LH_07:
                case Stance::Man_Rope_End_LH_01 ... Stance::Man_Rope_End_LH_06:
                case Stance::Man_Rope_Start_RH_01 ... Stance::Man_Rope_Start_RH_07:
                case Stance::Man_Rope_End_RH_01 ... Stance::Man_Rope_End_RH_06:
                    return Direction::Backward;

                case Stance::Man_Walk_RH_00 ... Stance::Man_Rope_Start_RH - 1:
                case Stance::Man_Rope_End_RH + 1 ... Stance::Man_RH_End:
                    return Direction::Right;

                case Stance::Man_FW_Start ... Stance::Man_FW_End:
                    return Direction::Forward;

                case Stance::Man_Walk_LH_00 ... Stance::Man_Rope_Start_LH - 1:
                case Stance::Man_Rope_End_LH + 1 ... Stance::Man_LH_End:
                    return Direction::Left;         

                default:
                    return Direction::None;           

            }

        }

    	void update() {

            // Housekeeping ..

            if (this->wound > 0) this->wound--;

        }

        bool canMoveLeft() {

            switch (this->stance) {

                case Stance::Man_ClimbLadder_BK_LH_DOWN_07:
                case Stance::Man_ClimbLadder_BK_RH_DOWN_07:
                case Stance::Man_ClimbLadder_BK_LH_UP_07:
                case Stance::Man_ClimbLadder_BK_RH_UP_07:
                    return false;

                default:
                    return true;
            }
            
        }

        bool canMoveRight() {

            switch (this->stance) {

                case Stance::Man_ClimbLadder_BK_LH_DOWN_07:
                case Stance::Man_ClimbLadder_BK_RH_DOWN_07:
                case Stance::Man_ClimbLadder_BK_LH_UP_07:
                case Stance::Man_ClimbLadder_BK_RH_UP_07:
                    return false;

                default:
                    return true;
            }
            
        }

        void incHealth(uint8_t val) {

            if (this->health + val <= Constants::HealthMax) {
                this->health  = this->health + val;
            }
            else {
                this->health = Constants::HealthMax;
            }

        }

        // Stack Methods ---------------------------------------
        
        bool isEmpty(void) {
            return this->stack.isEmpty();
        }

        Stance pop(void) {
            return this->stack.pop();
        }

      	uint8_t getCount(void) {
            return this->stack.getCount();
        }

        Stance & peek(void) {
            return this->stack.peek();
        }

        const Stance & peek(void) const {
            return this->stack.peek();
        }

        bool insert(const Stance & item) {
            return this->stack.insert(item);
        }

        void clear(void) {
            this->stack.clear();
        }

        bool push(Stance item) {
            return this->stack.push(static_cast<uint16_t>(item));
        }

        void insertSequence(Stance fromStance, Stance toStance) {

            for (uint16_t x = toStance; x >= fromStance; x--) {

                this->stack.insert(static_cast<uint16_t>(x));

            }

        }

        void pushSequence(Stance fromStance, Stance toStance) {

            this->pushSequence(fromStance, toStance, false);

        }

        void stageSequence(Stance fromStance, Stance toStance) {

            this->fromStance = fromStance;
            this->toStance = toStance;

        }

        bool commitSequence() {

            if (this->fromStance != Stance::None && this->toStance != Stance::None) {

                this->pushSequence(this->fromStance, this->toStance, false);
                this->fromStance = Stance::None;
                this->toStance = Stance::None;
                return true;

            }

            return false;

        }

        bool hasStagedSequence() {

            return this->fromStance != Stance::None && this->toStance != Stance::None;

        }

        void pushSequence(Stance fromStance, Stance toStance, bool clear) {

            if (clear) {

                this->stack.clear();
            }

            for (uint16_t x = toStance; x >= fromStance; x--) {

                this->stack.push(static_cast<uint16_t>(x));

            }

        }
};
