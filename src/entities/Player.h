#pragma once

#include <Arduboy2.h>   
#include "../utils/Constants.h"
#include "../utils/Stack.h"
#include "InventoryItem.h"
#include "BaseStack.h"

class Player : public BaseStack {

    private:

        Stance stance = Stance::Man_Walk_BK_01;
        InventoryItem items[Constants::ItemCount];

        uint8_t xSeq = 0;
        uint8_t ySeq = 0;
        uint8_t falling = 0;
        int8_t y = 37;
        uint8_t falls = 0;
        uint8_t itemCount = 0;
        uint8_t health = 12;
        uint8_t enemyIdx = 255;

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

        void incY(int8_t val)                               { this->y = this->y + val; }
        void incFalls()                                     { this->falls++; }

        void init() {

            this->health = 12;

        }

        void decHealth(uint8_t i) {

            this->health = this->health - i;
            
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

    	void update(uint8_t xLoc, uint8_t yLoc) {

            // Housekeeping ..

            // this->stack->update();

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

};