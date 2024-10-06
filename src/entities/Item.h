
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
        uint16_t counter;

    public:

        uint16_t getX()                                 { return this->x; }
        int8_t getY()                                   { return this->y; }
        uint8_t getFrame()                              { return this->frame; }
        uint16_t getCounter()                           { return this->counter; }
        ItemType getItemType()                          { return this->itemType; }

        void setItemType(ItemType val)                  { this->itemType = val; }
        void setX(uint16_t val)                         { this->x = val; }
        void setY(int8_t val)                           { this->y = val; }
        void setFrame(uint8_t val)                      { this->frame = val; }
        void setCounter(uint16_t val)                   { this->counter = val; }

        ItemAction update() {

            switch (this->getItemType()) {

                case ItemType::Key1:
                case ItemType::PinchBar:
                case ItemType::Potion:
                case ItemType::Anchor:

                    this->frame++;
                    if (this->frame == 128) this->frame = 0;

                    if (this->counter > 0 && this->frame % 16 == 0) {

                        this->counter--;

                        if (this->counter == 0) {
                            return ItemAction::Remove_AddToInventory;
                        }

                    }

                    break;

                case ItemType::Flame:

                    this->counter++;
                    if (this->counter == (6 * 8))   this->counter = 0;

                    this->frame = this->counter / 8;

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

                case ItemType::LockedDoor:

                    if (this->counter > 0 && this->counter < (5 * 32) - 1) {

                        this->counter++;
                        this->frame = this->counter / 32;

                    }
                    
                    break;

                case ItemType::Puff:
                    if (this->frame < Constants::Puff_Max) this->frame++;
                    break;

                case ItemType::Vine:

                    if (this->counter < (22 * 16) - 1) {

                        this->counter++;

                        if (this->counter == (11 * 16)) {

                            this->frame = 10;

                        }
                        else if (this->counter >= (11 * 16)) {

                            this->frame = ((22 * 16) - this->counter) / 16;

                        }
                        else {

                            this->frame = this->counter / 16;

                        }

                    }
                    else {

                        this->counter = 0;

                    }                    
                    break;

                case ItemType::Arrow_LH:

                    this->setCounter(this->getCounter() - 4);
                    this->setX(this->getX() - 4);

                    if (this->getCounter() == 0) {
                        this->itemType = ItemType::None;
                    }

                    break;

                case ItemType::Arrow_RH:

                    this->setCounter(this->getCounter() + 4);
                    this->setX(this->getX() + 4);

                    if (this->getCounter() == 0) {
                        this->itemType = ItemType::None;
                    }

                    break;

            }

            return ItemAction::None;

        }

};
