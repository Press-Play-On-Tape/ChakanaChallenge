#pragma once

#include <Arduboy2.h>   
#include "../utils/Constants.h"
#include "../utils/Stack.h"
#include "Item.h"

class Enemy {

    private:

        EnemyType enemyType = EnemyType::None;
        Stance stance = Stance::Enemy_Walk_LH_01;
        Item item;

        int16_t x = 0;
        int8_t y = 37;
        uint8_t health = Constants::HealthMax;
        uint8_t swordWound = 0;

        Stack <Stance, Constants::StackSize_Enemy> stack;

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

                case Stance::Enemy_Walk_RH_00 ... Stance::Enemy_Walk_RH_03:
                case Stance::Enemy_Walk_Bow_RH_00 ... Stance::Enemy_Walk_Bow_RH_03:
                case Stance::Enemy_Fire_RH_00 ... Stance::Enemy_Fire_RH_12:
                case Stance::Enemy_Trebochet_Release_RH_01 ... Stance::Enemy_Trebochet_Release_RH_14:
                case Stance::Enemy_Sword_Start_RH ... Stance::Enemy_Sword_End_RH:
                    return Direction::Right;

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

        void pushSequence(Stance fromStance, Stance toStance, bool clear) {

            if (clear) {

                this->stack.clear();
            }

            for (uint16_t x = toStance; x >= fromStance; x--) {

                this->stack.push(static_cast<uint16_t>(x));

            }

        }
};
