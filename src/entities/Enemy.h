#pragma once

#include <Arduboy2.h>   
#include "../utils/Constants.h"
#include "../utils/Stack.h"
#include "Item.h"
#include "BaseStack.h"

class Enemy : public BaseStack {

    private:

        Stance stance = Stance::Enemy_Walk_LH_01;
        Item item;

        uint16_t x = 0;
        int8_t y = 37;

    public:

        Stance getStance()                                  { return this->stance; }
        Item& getItem()                                     { return this->item; }

        uint16_t getX()                                     { return this->x; }
        int8_t getY()                                       { return this->y; }

        void setStance(Stance val)                          { this->stance = val; }

        void setX(uint16_t val)                             { this->x = val; }
        void setY(int8_t val)                               { this->y = val; }

        void init() {

        }



        // Other Utils ..

        Direction getDirection() {

            switch (this->getStance()) {

                // case Stance::Man_BK_Start ... Stance::Man_BK_End:
                // case Stance::Man_Rope_Start_LH_01 ... Stance::Man_Rope_Start_LH_07:
                // case Stance::Man_Rope_End_LH_01 ... Stance::Man_Rope_End_LH_06:
                // case Stance::Man_Rope_Start_RH_01 ... Stance::Man_Rope_Start_RH_07:
                // case Stance::Man_Rope_End_RH_01 ... Stance::Man_Rope_End_RH_06:
                //     return Direction::Backward;

                case Stance::Enemy_Walk_RH_00 ... Stance::Enemy_Walk_RH_03:
                case Stance::Enemy_Walk_Bow_RH_00 ... Stance::Enemy_Walk_Bow_RH_03:
                case Stance::Enemy_Fire_RH_00 ... Stance::Enemy_Fire_RH_12:
                    return Direction::Right;

                // case Stance::Man_FW_Start ... Stance::Man_FW_End:
                //     return Direction::Forward;

                case Stance::Enemy_Walk_LH_00 ... Stance::Enemy_Walk_LH_03:
                case Stance::Enemy_Walk_Bow_LH_00 ... Stance::Enemy_Walk_Bow_LH_03:
                case Stance::Enemy_Fire_LH_00 ... Stance::Enemy_Fire_LH_12:
                    return Direction::Left;         

                default:
                    return Direction::None;           

            }

        }

    	void update(uint8_t xLoc, uint8_t yLoc) {

            // switch (item.getItemType()) {

            //     case ItemType::Arrow_LH:
            //         break;
            // }

        }

};