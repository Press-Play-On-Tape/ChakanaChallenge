
#pragma once

#include <Arduboy2.h>
#include "../utils/Constants.h"
#include "../utils/Enums.h"

struct Item {

    private:

        ItemType itemType;
        uint16_t x;
        int8_t y;
        uint8_t frame;
        uint8_t counter;

    public:

        ItemType getItemType()                          { return this->itemType; }
        uint16_t getX()                                 { return this->x; }
        int8_t getY()                                   { return this->y; }
        uint8_t getFrame()                              { return this->frame; }
        uint8_t getCounter()                            { return this->counter; }

        void setItemType(ItemType val)                  { this->itemType = val; }
        void setX(uint16_t val)                         { this->x = val; }
        void setY(int8_t val)                           { this->y = val; }
        void setFrame(uint8_t val)                      { this->frame = val; }
        void setCounter(uint8_t val)                    { this->counter = val; }

        ItemAction update() {

            switch (this->itemType) {

                case ItemType::Key1:

                    this->frame++;
                    if (this->frame == 128) this->frame = 0;

                    if (this->counter > 0 && this->frame % 16 == 0) {

                        this->counter--;

                        if (this->counter == 0) {
                            return ItemAction::Remove_AddToInventory;
                        }

                    }

                    break;

                case ItemType::Puff:
                    if (this->frame < Constants::Puff_Max) this->frame++;
                    break;

            }

            return ItemAction::None;

        }

};
