#pragma once

#include <Arduboy2.h>   
#include "../utils/Constants.h"
#include "../utils/Stack.h"
#include "Item.h"
#include "BaseStack.h"

class Enemy : public BaseStack {

    private:

        EnemyType enemyType = EnemyType::None;
        Stance stance = Stance::Enemy_Walk_LH_01;
        Item item;

        int16_t x = 0;
        int8_t y = 37;
        uint8_t health = 2;//Constants::HealthMax;
        uint8_t swordWound = 0;

    public:

        EnemyType getEnemyType()                            { return this->enemyType; }
        Stance getStance()                                  { return this->stance; }
        Item& getItem()                                     { return this->item; }

        int16_t getX()                                      { return this->x; }
        int8_t getY()                                       { return this->y; }
        uint8_t getHealth()                                 { return this->health; }
        uint8_t getSwordWound()                             { return this->swordWound; }

        void setEnemyType(EnemyType val)                    { this->enemyType = val; }
        void setStance(Stance val)                          { this->stance = val; }

        void setX(int16_t val)                              { this->x = val; }
        void setY(int8_t val)                               { this->y = val; }
        void setHealth(uint8_t val)                         { this->health = val; }
        void setSwordWound(uint8_t val)                     { this->swordWound = val; }

        void init() {

            this->health = 12;

        }

        void decHealth(uint8_t i) {

            this->health = this->health - i;

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
                case Stance::Enemy_Trebochet_Release_RH_01 ... Stance::Enemy_Trebochet_Release_RH_14:
                case Stance::Enemy_Sword_Start_RH ... Stance::Enemy_Sword_End_RH:
                    return Direction::Right;

                // case Stance::Man_FW_Start ... Stance::Man_FW_End:
                //     return Direction::Forward;

                case Stance::Enemy_Walk_LH_00 ... Stance::Enemy_Walk_LH_03:
                case Stance::Enemy_Walk_Bow_LH_00 ... Stance::Enemy_Walk_Bow_LH_03:
                case Stance::Enemy_Fire_LH_00 ... Stance::Enemy_Fire_LH_12:
                case Stance::Enemy_Trebochet_Release_LH_01 ... Stance::Enemy_Trebochet_Release_LH_14:
                case Stance::Enemy_Sword_Start_LH ... Stance::Enemy_Sword_End_LH:
                    return Direction::Left;         

                default:
                    return Direction::None;           

            }

        }

    	void update() {

            // Housekeeping ..

            if (this->swordWound > 0) this->swordWound--;

        }

};