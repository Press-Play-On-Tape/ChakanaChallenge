#pragma once

#include "../utils/Constants.h"


struct World {

    public:

        uint8_t mapData[Constants::Map_Y_Count][Constants::Map_X_Count];

    private:
        
        GameState gameState = GameState::SplashScreen_Start;
        GameState prevGameState = GameState::SplashScreen_Start;

        uint16_t frameCount;


    public:

        GameState getGameState()                        { return this->gameState; }
        GameState getPrevGameState()                    { return this->prevGameState; }
        uint16_t getFrameCount()                        { return this->frameCount; }
        
        void setGameState(GameState val)                { this->gameState = val; }
        void setPrevGameState(GameState val)            { this->prevGameState = val; }
        void setFrameCount(uint16_t val)                { this->frameCount = val; }
      

    public:

        void init() {

        }

        void incFrameCount() {

            this->frameCount++;

        }

        void incGameState() {

            this->gameState++;

        }

        void decGameState() {

            this->gameState--;

        }

        

};
