#pragma once

#include <Arduboy2.h>   
#include "../utils/Constants.h"
#include "../utils/Stack.h"

class BaseStack {

    protected:

        Stack <Stance, Constants::StackSize>  *stack;
        
    public:

        Stack <Stance, Constants::StackSize>  * getStack()           { return this->stack; }

        void setStack(Stack <Stance, Constants::StackSize>  *val)    { this->stack = val; }


        Stance & peek(void) {
            return this->stack->peek();
        }

        const Stance & peek(void) const {
            return this->stack->peek();
        }

        bool insert(const Stance & item) {
            return this->stack->insert(item);
        }

        bool push(Stance item) {

            #if defined(DEBUG) && defined(DEBUG_STACK)
            DEBUG_PRINT(F("Stack count "));
            DEBUG_PRINTLN(this->stack->getCount());
            #endif

            return this->stack->push(static_cast<uint16_t>(item));
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

                    this->stack->insert(static_cast<uint16_t>(x));

                }

            }
            else {

                for (uint16_t x = toStance; x <= fromStance; x++) {

                    #if defined(DEBUG) && defined(DEBUG_STACK)
                    DEBUG_PRINT(x); 
                    DEBUG_PRINT(" ");                         
                    #endif

                    this->stack->insert(static_cast<uint16_t>(-x));
                }

            }

            #if defined(DEBUG) && defined(DEBUG_STACK)
            DEBUG_PRINT(F(", count "));
            DEBUG_PRINTLN(this->stack->getCount());
            #endif

        }

        void pushSequence(Stance fromStance, Stance toStance) {

            this->pushSequence(fromStance, toStance, false);

        }

        // void stageSequence(Stance fromStance, Stance toStance) {

        //     this->startSeqence = from ;

        // }

        void pushSequence(Stance fromStance, Stance toStance, bool clear) {

            if (clear) {

                this->stack->clear();
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

                    this->stack->push(static_cast<uint16_t>(x));

                }

            }
            else {

                for (uint16_t x = toStance; x <= fromStance; x++) {

                    #if defined(DEBUG) && defined(DEBUG_STACK)
                    DEBUG_PRINT(x); 
                    DEBUG_PRINT(" ");                         
                    #endif

                    this->stack->push(static_cast<uint16_t>(-x));
                }

            }

            #if defined(DEBUG) && defined(DEBUG_STACK)
            DEBUG_PRINT(F(", count "));
            DEBUG_PRINTLN(this->stack->getCount());
            #endif

        }

        Stance pop(void) {
            return this->stack->pop();
        }

        bool isEmpty(void) {
            return this->stack->isEmpty();
        }

    	bool isFull(void) {
            return this->stack->isFull();
        }

    	void clear(void) {
            this->stack->clear();
        }

    	bool contains(const Stance & item) {
            return this->stack->contains(item);
        }

      	uint8_t getCount(void) {
            return this->stack->getCount();
        }

};