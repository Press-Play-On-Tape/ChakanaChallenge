#pragma once

#include <Arduboy2.h>   
#include "../utils/Constants.h"
#include "../utils/Stack.h"
#include "BaseEntity.h"
#include "BaseStack.h"

class Player : public BaseEntity, public BaseStack {

    private:
        
        uint8_t xSeq = 0;
        uint8_t ySeq = 0;
        uint8_t falling = 0;
        int8_t y = 37;
        // uint8_t level = 0;
        uint8_t falls = 0;

    public:

        uint8_t getXSeq()                           { return this->xSeq; }
        uint8_t getYSeq()                           { return this->ySeq; }
        uint8_t getFalling()                        { return this->falling; }
        int8_t getY()                               { return this->y; }
        uint8_t getFalls()                          { return this->falls; }
        uint8_t getLevel()                          { return (37 - y)/8; } //this->level; }

        void setXSeq(uint8_t val)                   { this->xSeq = val; }
        void setYSeq(uint8_t val)                   { this->ySeq = val; }
        void setFalling(uint8_t val)                { this->falling = val; }
        void incFalling()                           { this->falling++; }
        void setY(int8_t val)                       { this->y = val; }
        void setFalls(uint8_t val)                  { this->falls = val; }
        // void setLevel(uint8_t val)                  { this->level = val; }


        void incY(int8_t val)                       { this->y = this->y + val; }
        void incFalls()                             { this->falls++; }

        void init() {

        }

        Direction getDirection() {

            switch (this->getStance()) {

                case Stance::Man_BK_Start ... Stance::Man_BK_End:
                case Stance::Man_Rope_Start_LH_01 ... Stance::Man_Rope_Start_LH_06:
                case Stance::Man_Rope_End_LH_01 ... Stance::Man_Rope_End_LH_06:
                case Stance::Man_Rope_Start_RH_01 ... Stance::Man_Rope_Start_RH_06:
                case Stance::Man_Rope_End_RH_01 ... Stance::Man_Rope_End_RH_06:
                    return Direction::Backward;

                case Stance::Man_Walk_RH_00 ... Stance::Man_Walk_RH_04:
                case Stance::Man_ClimbStairs_RH_01 ... Stance::Man_ClimbStairs_RH_08:
                case Stance::Man_DescendStairs_RH_01 ... Stance::Man_DescendStairs_RH_08:
                case Stance::Man_Walk_FallDown_RH_01 ... Stance::Man_Walk_FallDown_RH_06:
                case Stance::Man_Walk_FallMore_RH_01 ... Stance::Man_Walk_FallMore_RH_02:
                case Stance::Man_Walk_FallLand_RH_01 ... Stance::Man_Walk_FallLand_RH_04:
                case Stance::Man_StandingJump_RH_01 ... Stance::Man_StandingJump_RH_07:
                case Stance::Man_StandingJump_Small_RH_01 ... Stance::Man_StandingJump_Small_RH_03:
                case Stance::Man_StandingJump_RH_UP_01 ... Stance::Man_StandingJump_RH_UP_06:
                case Stance::Man_StandingJump_RH_UPandOver_01 ... Stance::Man_StandingJump_RH_UPandOver_06:
                case Stance::Man_WalkingJump_RH_01 ... Stance::Man_WalkingJump_RH_08:
                case Stance::Man_WalkingJump_RH_2_01 ... Stance::Man_WalkingJump_RH_2_08:
                case Stance::Man_WalkingJump_RH_25_01 ... Stance::Man_WalkingJump_RH_25_11:
                case Stance::Man_WalkingJump_RH_1D_25_01 ... Stance::Man_WalkingJump_RH_1D_25_11:
                case Stance::Man_WalkingJump_RH_UP_01 ... Stance::Man_WalkingJump_RH_UP_05:
                case Stance::Man_Die_RH_01 ... Stance::Man_Die_RH_04:
                    return Direction::Right;

                case Stance::Man_FW_Start ... Stance::Man_FW_End:
                    return Direction::Forward;

                case Stance::Man_Walk_LH_00 ... Stance::Man_Walk_LH_04:
                case Stance::Man_ClimbStairs_LH_01 ... Stance::Man_ClimbStairs_LH_08:
                case Stance::Man_DescendStairs_LH_01 ... Stance::Man_DescendStairs_LH_08:
                case Stance::Man_Walk_FallDown_LH_01 ... Stance::Man_Walk_FallDown_LH_06:
                case Stance::Man_Walk_FallMore_LH_01 ... Stance::Man_Walk_FallMore_LH_02:
                case Stance::Man_Walk_FallLand_LH_01 ... Stance::Man_Walk_FallLand_LH_04:
                case Stance::Man_StandingJump_LH_01 ... Stance::Man_StandingJump_LH_07:
                case Stance::Man_StandingJump_Small_LH_01 ... Stance::Man_StandingJump_Small_LH_03:
                case Stance::Man_StandingJump_LH_UP_01 ... Stance::Man_StandingJump_LH_UP_06:
                case Stance::Man_StandingJump_LH_UPandOver_01 ... Stance::Man_StandingJump_LH_UPandOver_06:
                case Stance::Man_WalkingJump_LH_01 ... Stance::Man_WalkingJump_LH_08:
                case Stance::Man_WalkingJump_LH_2_01 ... Stance::Man_WalkingJump_LH_2_08:
                case Stance::Man_WalkingJump_LH_25_01 ... Stance::Man_WalkingJump_LH_25_11:
                case Stance::Man_WalkingJump_LH_1D_25_01 ... Stance::Man_WalkingJump_LH_1D_25_11:
                case Stance::Man_WalkingJump_LH_UP_01 ... Stance::Man_WalkingJump_LH_UP_05:
                case Stance::Man_Die_LH_01 ... Stance::Man_Die_LH_04:
                    return Direction::Left;                    

            }

        }

    	void update(uint8_t xLoc, uint8_t yLoc) {

            // Housekeeping ..

            // this->stack->update();

        }

        void pushSequence(uint16_t fromStance, uint16_t toStance) {

            BaseStack::pushSequence(fromStance, toStance, Stance::None);

        }

        void pushSequence(uint16_t fromStance, uint16_t toStance, uint16_t finalStance) {

            BaseStack::pushSequence(fromStance, toStance, finalStance);

        }

        void printStack() {
            this->stack->print();
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