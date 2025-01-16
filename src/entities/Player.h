#pragma once

#include <Arduboy2.h>   
#include "../utils/Constants.h"
#include "../utils/Stack.h"
#include "InventoryItem.h"

class Player {

    private:

        Stance stance = Stance::Man_Walk_BK_01;
        InventoryItem items[Constants::ItemCount];

        uint8_t xSeq = 0;
        uint8_t ySeq = 0;
        uint8_t falling = 0;
        int8_t y = 37;
        uint8_t falls = 0;
        uint8_t itemCount = 0;
        uint8_t health = Constants::HealthMax;
        uint8_t enemyIdx = 255;
        uint8_t swordWound = 0;
        uint8_t chakanas = 200;
		
        Stance fromStance = Stance::None;
        Stance toStance = Stance::None;
        
        Stack <Stance, Constants::StackSize_Player> stack;

    public:

        Stance getStance()                                  { return this->stance; }
        InventoryItem &getItem(uint8_t idx)                 { return this->items[idx]; }

        uint8_t getXSeq()                                   { return this->xSeq; }
        uint8_t getYSeq()                                   { return this->ySeq; }
        uint8_t getFalling()                                { return this->falling; }
        int8_t getY()                                       { return this->y; }
        uint8_t getFalls()                                  { return this->falls; }
        uint8_t getLevel()                                  { return (37 - y) / 8; }
        uint8_t getItemCount()                              { return this->itemCount; }
        uint8_t getHealth()                                 { return this->health; }
        uint8_t getEnemyIdx()                               { return this->enemyIdx; }
        uint8_t getSwordWound()                             { return this->swordWound; }
        uint8_t getChakanas()                               { return this->chakanas; }

        void setStance(Stance val)                          { this->stance = val; }

        void setXSeq(uint8_t val)                           { this->xSeq = val; }
        void setYSeq(uint8_t val)                           { this->ySeq = val; }
        void setFalling(uint8_t val)                        { this->falling = val; }
        void incFalling()                                   { this->falling++; }
        void setY(int8_t val)                               { this->y = val; }
        void setFalls(uint8_t val)                          { this->falls = val; }
        void setItemCount(uint8_t val)                      { this->itemCount = val; }
        void setHealth(uint8_t val)                         { this->health = val; }
        void setEnemyIdx(uint8_t val)                       { this->enemyIdx = val; }
        void setSwordWound(uint8_t val)                     { this->swordWound = val; }
        void setChakanas(uint8_t val)                       { this->chakanas = val; }

        void incY(int8_t val)                               { this->y = this->y + val; }
        void incFalls()                                     { this->falls++; }

        void init() {

            this->health = 14;
            this->chakanas = 100;

        }

        void decHealth(uint8_t i) {

            this->health = this->health - i;
            
        }

        void decSwordWound(uint8_t i) {

            this->swordWound = this->swordWound - i;
            
        }


        // Invetory Methods ---------------------------------------

        void removeInventoryItem(uint8_t itemIdx) {

            for (uint8_t i = itemIdx; i < Constants::ItemCount - 1; i++) {

                this->items[i].setItemType(items[i + 1].getItemType());

            }

            this->items[Constants::ItemCount - 1].setItemType(ItemType::None);
            this->itemCount--;

        }

        void addInventoryItem(ItemType itemType) {

            for (uint8_t i = 0; i < Constants::ItemCount - 1; i++) {

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

            if (this->swordWound > 0) this->swordWound--;

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

            #if defined(DEBUG) && defined(DEBUG_STACK)
            DEBUG_PRINT(F("Stack count "));
            DEBUG_PRINTLN(this->stack.getCount());
            #endif

            return this->stack.push(static_cast<uint16_t>(item));
        }

        void insertSequence(Stance fromStance, Stance toStance) {

            #if defined(DEBUG) && defined(DEBUG_STACK)
            DEBUG_PRINT(F("Seq "));
            DEBUG_PRINT(toStance);
            DEBUG_PRINT(F(" to "));
            DEBUG_PRINT(fromStance);
            DEBUG_PRINT(F(" - "));  
            #endif
            
            if (fromStance < toStance) {

                for (uint16_t x = toStance; x >= fromStance; x--) {

                    #if defined(DEBUG) && defined(DEBUG_STACK)
                    DEBUG_PRINT(x); 
                    DEBUG_PRINT(" ");        
                    #endif

                    this->stack.insert(static_cast<uint16_t>(x));

                }

            }
            else {

                for (uint16_t x = toStance; x <= fromStance; x++) {

                    #if defined(DEBUG) && defined(DEBUG_STACK)
                    DEBUG_PRINT(x); 
                    DEBUG_PRINT(" ");                         
                    #endif

                    this->stack.insert(static_cast<uint16_t>(-x));
                }

            }

            #if defined(DEBUG) && defined(DEBUG_STACK)
            DEBUG_PRINT(F(", count "));
            DEBUG_PRINTLN(this->stack.getCount());
            #endif

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

            #if defined(DEBUG) && defined(DEBUG_STACK)
            DEBUG_PRINT(F("Seq "));
            DEBUG_PRINT(toStance);
            DEBUG_PRINT(F(" to "));
            DEBUG_PRINT(fromStance);
            DEBUG_PRINT(F(" - "));  
            #endif
            
            if (fromStance < toStance) {

                for (uint16_t x = toStance; x >= fromStance; x--) {

                    #if defined(DEBUG) && defined(DEBUG_STACK)
                    DEBUG_PRINT(x); 
                    DEBUG_PRINT(" ");        
                    #endif

                    this->stack.push(static_cast<uint16_t>(x));

                }

            }
            else {

                for (uint16_t x = toStance; x <= fromStance; x++) {

                    #if defined(DEBUG) && defined(DEBUG_STACK)
                    DEBUG_PRINT(x); 
                    DEBUG_PRINT(" ");                         
                    #endif

                    this->stack.push(static_cast<uint16_t>(-x));
                }

            }

            #if defined(DEBUG) && defined(DEBUG_STACK)
            DEBUG_PRINT(F(", count "));
            DEBUG_PRINTLN(this->stack->getCount());
            #endif

        }
};
