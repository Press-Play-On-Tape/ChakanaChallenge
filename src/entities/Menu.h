#pragma once

#include <Arduboy2.h>
#include "../utils/Constants.h"
#include "../utils/Enums.h"

class Menu {

    private:

        uint8_t x = 128;
        uint8_t y = 0;
        uint8_t top = 0;

        Direction direction = Direction::None;
        GameState gameState = GameState::Inventory_Open;//SJH Necessary?


    public:

        uint8_t getX()                                  { return this->x; }
        uint8_t getY()                                  { return this->y; }
        uint8_t getTop()                                { return this->top; }
        Direction getDirection()                        { return this->direction; }
        GameState getGameState()                        { return this->gameState; }

        void setX(uint8_t val)                          { this->x = val; }
        void setY(uint8_t val)                          { this->y = val; }
        void setTop(uint8_t val)                        { this->top = val; }
        void setDirection(Direction val)                { this->direction = val; }
        void setGameState(GameState val)                { this->gameState = val; }

};
