
#pragma once

#include <Arduboy2.h>
#include "../utils/Constants.h"
#include "../utils/Enums.h"

constexpr uint8_t ball_X[20] = { 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 };
// constexpr int8_t ball_Y[20] = { 0, -6, -5, -4,         -4,  -3,  -3, -3, -1, 0, 0, 1,    2,  2, 3,   4,  5, 5, 7, 8 };
constexpr int8_t ball_Y[20] = { 0, -8, -6, -5,         -4,  -3,  -2, -1, 0, 0, 0, 0,    0,  0, 1,   2,  3, 4, 4, 5 };

class Item {

    private:

        ItemType itemType;
        uint16_t x;
        int8_t y;
        uint8_t frame;
        int16_t data;
        uint16_t counter;

    public:

        uint16_t getX()                                 { return this->x; }
        int8_t getY()                                   { return this->y; }
        uint8_t getFrame()                              { return this->frame; }
        int16_t getData()                               { return this->data; }
        uint16_t getCounter()                           { return this->counter; }
        ItemType getItemType()                          { return this->itemType; }

        void setItemType(ItemType val)                  { this->itemType = val; }
        void setX(uint16_t val)                         { this->x = val; }
        void setY(int8_t val)                           { this->y = val; }
        void setFrame(uint8_t val)                      { this->frame = val; }
        void setData(int16_t val)                       { Serial.println(val); this->data = val; }
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

                case ItemType::Chakana:

                    this->counter++;
                    if (this->counter == (16 * 12))   this->counter = 0;

                    this->frame = this->counter / 16;

                    break;

                // case ItemType::Lever:

                //     this->counter++;
                //     if (this->counter == (2 * 8))   this->counter = 0;

                //     this->frame = this->counter / 8;

                //     break;

                case ItemType::Punji:

                    if (this->counter > 0 && this->counter < (3 * 8) - 1) {

                        this->counter++;
                        this->frame = this->counter / 8;

                    }
                    
                    break;
               

                case ItemType::Lever_Portal_Closed:
                case ItemType::Lever_Portal_Auto_Closed:

                    switch (this->frame) {

                        case 1 ... 8:

                            this->counter++;

                            if (this->counter == 8) {

                                this->counter = 0;
                                this->frame++;

                                if (this->frame == 9) {
                                    this->itemType++;
                                }

                            }

                            break;

                        default: break;

                    }
                    
                    break;       

                case ItemType::Lever_Portal_Open:
                case ItemType::Lever_Portal_Auto_Open:

                    switch (this->frame) {
                        
                        case 1 ... 8:

                            this->counter++;

                            if (this->counter == 8) {

                                this->counter = 0;
                                this->frame--;

                                if (this->frame == 0) {
                                    this->itemType--;
                                }

                            }
                            break;
                        
                        case 9:

                            this->counter++;

                            if (this->counter == this->data && this->itemType == ItemType::Lever_Portal_Auto_Open) {
                                this->counter = 0;
                                this->frame = 8;
                            }
                            break;

                        default: break;

                    }
                    
                    break;  

                case ItemType::Hammer:
                case ItemType::Amulet:
                case ItemType::Sword:
                case ItemType::Lever_LH:
                case ItemType::Lever_RH:

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

                case ItemType::Glint:
                    if (this->frame < Constants::Glint_Max - 1) {
                        this->frame++;
                    }
                    else {
                        this->itemType = ItemType::Glint_Hidden;
                    }
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

                case ItemType::Trebochet_Ball_Left_1 ... ItemType::Trebochet_Ball_Left_3:

                    if (this->counter > 0) {

                        this->setCounter(this->getCounter() - 1);
                        this->setY(this->getY() + ball_Y[this->getCounter()]);

                        switch (this->itemType) {

                            case ItemType::Trebochet_Ball_Left_1:
                                this->setX(this->getX() - 6);
                                break;

                            case ItemType::Trebochet_Ball_Left_2:
                                this->setX(this->getX() - 6 - (this->counter % 2));
                                break;

                            case ItemType::Trebochet_Ball_Left_3:
                                this->setX(this->getX() - 5);
                                break;
                                
                        }

                        if (this->counter == 0) {
                            this->setX(this->getX() - 12);
                        }

                    }

                    if (this->counter == 0) {

                        this->frame++;

                        if (this->frame == 9) {
                            this->itemType = ItemType::Trebochet_Ball_Left_Hidden;
                            this->frame = 0;
                        }

                    }

                    break;

                case ItemType::Trebochet_Ball_Right_1 ... ItemType::Trebochet_Ball_Right_3:

                    if (this->counter > 0) {

                        this->setCounter(this->getCounter() - 1);
                        this->setY(this->getY() + ball_Y[this->getCounter()]);

                        switch (this->itemType) {

                            case ItemType::Trebochet_Ball_Right_1:
                                this->setX(this->getX() + 6);
                                break;

                            case ItemType::Trebochet_Ball_Right_2:
                                this->setX(this->getX() + 6 + (this->counter % 2));
                                break;

                            case ItemType::Trebochet_Ball_Right_3:
                                this->setX(this->getX() + 5);
                                break;
                                
                        }

                        if (this->counter == 0) {
                            this->setX(this->getX() + 4);
                            this->frame = 8;
                        }

                    }

                    if (this->counter == 0) {

                        this->frame++;

                        if (this->frame == 17) {
                            this->itemType = ItemType::Trebochet_Ball_Right_Hidden;
                            this->frame = 0;
                        }

                    }

                    break;

                case ItemType::SwingyThing:
                case ItemType::SwingyThing_2:

                    this->counter++;

                    if (this->counter == 16) {
                        this->counter = 0;
                        this->frame++;
                        if (this->frame == 16) this->frame = 0;
                    }
                    
                    break;

            }

            return ItemAction::None;

        }

};
