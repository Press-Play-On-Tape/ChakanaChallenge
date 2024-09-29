
#pragma once

#include <Arduboy2.h>
#include "../utils/Constants.h"
#include "../utils/Enums.h"

// class Item : public InventoryItem {
class Item {

    private:

        ItemType itemType;
        uint16_t x;
        int8_t y;
        uint8_t frame;
        uint8_t counter;

    public:

        uint16_t getX()                                 { return this->x; }
        int8_t getY()                                   { return this->y; }
        uint8_t getFrame()                              { return this->frame; }
        uint8_t getCounter()                            { return this->counter; }
        ItemType getItemType()                          { return this->itemType; }

        void setItemType(ItemType val)                  { this->itemType = val; }
        void setX(uint16_t val)                         { this->x = val; }
        void setY(int8_t val)                           { this->y = val; }
        void setFrame(uint8_t val)                      { this->frame = val; }
        void setCounter(uint8_t val)                    { this->counter = val; }

        ItemAction update() {

            switch (this->getItemType()) {

                case ItemType::Key1:
                case ItemType::PinchBar:

                    this->frame++;
                    if (this->frame == 128) this->frame = 0;

                    if (this->counter > 0 && this->frame % 16 == 0) {

                        this->counter--;

                        if (this->counter == 0) {
                            return ItemAction::Remove_AddToInventory;
                        }

                    }

                    break;
                
                case ItemType::Punji:

                    if (this->counter > 0 && this->counter < (3 * 8) - 1) {

                        this->counter++;
                        this->frame = this->counter / 8;

                    }
                    
                    break;
                
                case ItemType::Hammer:
                case ItemType::Amulet:

                    this->frame++;

                    if (this->counter > 0 && this->frame % 8 == 0) {

                        this->counter--;

                        if (this->counter == 0) {
                            return ItemAction::Remove_AddToInventory;
                        }

                    }

                    break;

                case ItemType::WoodenBarrier:

                    if (this->counter > 0 && this->counter < (7 * 32) - 1) {

                        this->counter++;
                        this->frame = this->counter / 32;

                    }
                    
                    break;

                case ItemType::MysteryCrate:

                    if (this->counter > 0 && this->counter < (8 * 24)) {

                        this->counter++;
                        this->frame = this->counter / 24;

                        if (this->counter == (8 * 24)) {
                            return ItemAction::HideCrate_ShowItem;
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
