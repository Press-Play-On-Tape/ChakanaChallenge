#pragma once

#include <Arduboy2.h>
#include "../utils/Constants.h"
#include "../utils/Enums.h"

class Menu {

    private:

        uint8_t x;
        uint8_t y;
        uint8_t top;

        Direction direction = Direction::None;
        GameState gameState = GameState::Inventory_Open;


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

        void incX()                                     { this->x = this->x + 2; }
        void decX()                                     { if (this->x >= 2) this->x = this->x - 2; }
        void incY()                                     { this->y++; }
        void decY()                                     { if (this->y > 0) this->y--; }

        void reset() {

            x = 128;
            y = 0;
            top = 0;

            direction = Direction::None;
            gameState = GameState::Inventory_Open;

        }


};
