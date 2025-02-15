
#pragma once

#include <Arduboy2.h>
#include "../utils/Constants.h"
#include "../utils/Enums.h"

class Item {

    private:

        ItemType itemType;
        int16_t x;
        int8_t y;
        uint8_t frame;
        int16_t data;
        uint16_t counter;

    public:

        int16_t getX()                                  { return this->x; }
        int8_t getY()                                   { return this->y; }
        uint8_t getFrame()                              { return this->frame; }
        int16_t getData()                               { return this->data; }
        uint16_t getCounter()                           { return this->counter; }
        ItemType getItemType()                          { return this->itemType; }

        void setItemType(ItemType val)                  { this->itemType = val; }
        void setX(int16_t val)                          { this->x = val; }
        void setY(int8_t val)                           { this->y = val; }
        void setFrame(uint8_t val)                      { this->frame = val; }
        void setData(int16_t val)                       { this->data = val; }
        void setCounter(uint16_t val)                   { this->counter = val; }

        bool processItem() {

            this->frame++;

            if (this->counter > 0 && this->frame % 8 == 0) {

                this->counter--;

                if (this->counter == 0) {
                    return true;
                }

            }

            return false;

        }

        bool updateCounter(uint16_t maxVal) {

            this->counter++;

            if (this->counter == maxVal) {
                this->counter = 0;
                return true;
            }

            return false;

        }

        bool updateFrame(uint16_t maxVal) {

            this->frame++;

            if (this->frame == maxVal) {
                this->frame = 0;
                return true;
            }

            return false;

        }


        ItemAction update() {

            switch (this->getItemType()) {

                #ifdef TRAP_DOOR
                    
                    case ItemType::TrapDoor:

                        updateCounter(256);

                        switch (this->counter) {

                            case 0 ... 55:
                                this->frame = this->counter >> 3;
                                break;

                            default:
                                this->frame = 7;
                                break;

                        }

                        break;

                #endif

                case ItemType::Poker:

                    updateCounter(8 * 12);
                    this->frame = this->counter / 12;

                    break;

                case ItemType::Key1:
                case ItemType::PinchBar:
                case ItemType::Potion:
                case ItemType::Anchor:

                    updateFrame(128);

                    if (this->counter > 0 && this->frame % 16 == 0) {

                        this->counter--;

                        if (this->counter == 0) {
                            return ItemAction::Remove_AddToInventory;
                        }

                    }

                    break;

                case ItemType::Flame:

                    updateCounter(6 * 8);
                    this->frame = this->counter >> 3;

                    break;

                case ItemType::Chakana:

                    updateCounter(16 * 12);
                    this->frame = this->counter >> 4;

                    break;

                case ItemType::Punji:

                    if (this->counter > 0 && this->counter < (3 * 8) - 1) {

                        this->counter++;
                        this->frame = this->counter >> 3;

                    }
                    
                    break;
               

                case ItemType::Lever_Portal_Closed:
                case ItemType::Lever_Portal_Auto_Closed:

                    switch (this->frame) {

                        case 1 ... 8:

                            if (updateCounter(8)) {

                                if (updateFrame(9)) {
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

                            if (updateCounter(8)) {

                                if (updateFrame(9)) {
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

                    if (this->processItem()) return ItemAction::Remove_AddToInventory;
                    break;

                case ItemType::LifeSaver:
                case ItemType::LifeSaver_Dissolve:

                    if (this->processItem()) return ItemAction::ChangeToHidden;
                    break;

                case ItemType::Chakana_Small:

                    if (this->processItem()) return ItemAction::Remove;
                    break;

                case ItemType::LifeSaver_InWater_RH:
                case ItemType::LifeSaver_InWater_LH:

                    if (this->frame < 12) {

                        this->counter++;
                        this->frame = this->counter / 12;

                        if (this->frame == 12 && this->getItemType() == ItemType::LifeSaver_InWater_LH) {
                            this->setItemType(ItemType::LifeSaver_InWater_RH);
                            this->x = this->x - 16;
                        }

                    }

                    break;
                   
                case ItemType::LifeSaver_Dissolve_InWater_RH:
                case ItemType::LifeSaver_Dissolve_InWater_LH:

                    if (this->frame < 12) {

                        this->counter++;
                        this->frame = this->counter / 12;

                        if (this->frame == 12 && this->getItemType() == ItemType::LifeSaver_Dissolve_InWater_LH) {
                            this->setItemType(ItemType::LifeSaver_Dissolve_InWater_RH);
                            this->x = this->x - 16;
                        }

                    }
                    else {

                        this->counter++;

                        if (this->counter > 800) {
                            
                            if (this->frame < 19) {

                                this->frame = (this->counter - 800 + 144) / 12;

                            }
                            else {

                                this->setItemType(ItemType::LifeSaver_Dissolve_Hidden);

                            }

                        }

                    }

                    break;

                case ItemType::WoodenBarrier:

                    if (this->counter > 0 && this->counter < (7 * 32) - 1) {

                        this->counter++;
                        this->frame = this->counter / 32;
                        
                        if (this->counter == (7 * 32) - 1) {
                            return ItemAction::HideWoodenBarrier;
                        }

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

                case ItemType::Swinging_Vine:

                    if (this->counter < (22 * 16) - 1) {

                        this->counter++;

                        if (this->counter == (11 * 16)) {

                            this->frame = 10;

                        }
                        else if (this->counter >= (11 * 16)) {

                            this->frame = ((22 * 16) - this->counter) >> 4;

                        }
                        else {

                            this->frame = this->counter >> 4;

                        }

                    }
                    else {

                        this->counter = 0;

                    }                    
                    break;

                case ItemType::Arrow_LH:
                case ItemType::Arrow_RH: 
                    {
                        
                        int8_t direction = (this->itemType == ItemType::Arrow_LH) ? -1 : 1; 

                        this->setCounter(this->getCounter() - 4);
                        this->setX(this->getX() + (direction * 4));

                        if (this->getCounter() == 0) {
                            this->itemType = (this->itemType == ItemType::Arrow_LH) ? ItemType::Arrow_LH_Hidden : ItemType::Arrow_RH_Hidden;
                        }

                    }

                    break;
                
                // case ItemType::Trebochet_Ball_Left_1 ... ItemType::Trebochet_Ball_Left_3:

                //     if (this->counter > 0) {

                //         int8_t yOffset = FX::readIndexedUInt8(Constants::Ball_Y, this->getCounter());
                //         this->setCounter(this->getCounter() - 1);
                //         this->setY(this->getY() + yOffset);

                //         switch (this->itemType) {

                //             case ItemType::Trebochet_Ball_Left_1:
                //                 this->setX(this->getX() - 6);
                //                 break;

                //             case ItemType::Trebochet_Ball_Left_2:
                //                 this->setX(this->getX() - 6 - (this->counter % 2));
                //                 break;

                //             case ItemType::Trebochet_Ball_Left_3:
                //                 this->setX(this->getX() - 5);
                //                 break;
                                
                //         }

                //         if (this->counter == 0) {
                //             this->setX(this->getX() - 12);
                //         }

                //     }

                //     if (this->counter == 0) {

                //         this->frame++;

                //         if (this->frame == 9) {
                //             this->itemType = ItemType::Trebochet_Ball_Left_Hidden;
                //             this->frame = 0;
                //         }

                //     }

                //     break;

                // case ItemType::Trebochet_Ball_Right_1 ... ItemType::Trebochet_Ball_Right_3:

                //     if (this->counter > 0) {
                        
                //         int8_t yOffset = FX::readIndexedUInt8(Constants::Ball_Y, this->getCounter());
                //         this->setCounter(this->getCounter() - 1);
                //         this->setY(this->getY() + yOffset);

                //         switch (this->itemType) {

                //             case ItemType::Trebochet_Ball_Right_1:
                //                 this->setX(this->getX() + 6);
                //                 break;

                //             case ItemType::Trebochet_Ball_Right_2:
                //                 this->setX(this->getX() + 6 + (this->counter % 2));
                //                 break;

                //             case ItemType::Trebochet_Ball_Right_3:
                //                 this->setX(this->getX() + 5);
                //                 break;
                                
                //         }

                //         if (this->counter == 0) {
                //             this->setX(this->getX() + 4);
                //             this->frame = 8;
                //         }

                //     }

                //     if (this->counter == 0) {

                //         this->frame++;

                //         if (this->frame == 17) {
                //             this->itemType = ItemType::Trebochet_Ball_Right_Hidden;
                //             this->frame = 0;
                //         }

                //     }

                //     break;

                case ItemType::Trebochet_Ball_Left_1 ... ItemType::Trebochet_Ball_Left_3:
                case ItemType::Trebochet_Ball_Right_1 ... ItemType::Trebochet_Ball_Right_3: 
                    {
                            
                        bool isLeft = (this->itemType >= ItemType::Trebochet_Ball_Left_1 && this->itemType <= ItemType::Trebochet_Ball_Left_3);
                        int8_t direction = isLeft ? -1 : 1;  // -1 for left, 1 for right

                        if (this->counter > 0) {

                            int8_t yOffset = FX::readIndexedUInt8(Constants::Ball_Y, this->getCounter());
                            this->setCounter(this->getCounter() - 1);
                            this->setY(this->getY() + yOffset);

                            switch (this->itemType) {

                                case ItemType::Trebochet_Ball_Left_1:
                                case ItemType::Trebochet_Ball_Right_1:
                                    this->setX(this->getX() + (direction * 6));
                                    break;

                                case ItemType::Trebochet_Ball_Left_2:
                                case ItemType::Trebochet_Ball_Right_2:
                                    this->setX(this->getX() + (direction * (6 + (this->counter % 2))));
                                    break;

                                case ItemType::Trebochet_Ball_Left_3:
                                case ItemType::Trebochet_Ball_Right_3:
                                    this->setX(this->getX() + (direction * 5));
                                    break;

                            }

                            if (this->counter == 0) {

                                this->setX(this->getX() + (isLeft ? -12 : 4));
                                if (!isLeft) this->frame = 8;

                            }

                        }

                        if (this->counter == 0) {

                            this->frame++;
                            uint8_t frameLimit = isLeft ? 9 : 17;

                            if (this->frame == frameLimit) {
                                this->itemType = isLeft ? ItemType::Trebochet_Ball_Left_Hidden : ItemType::Trebochet_Ball_Right_Hidden;
                                this->frame = 0;
                            }

                        }

                    }

                    break;
                
                case ItemType::SwingyThing:
                case ItemType::SwingyThing_2:

                    if (updateCounter(16)) {
                        updateFrame(16);
                    }
                    
                    break;

            }

            return ItemAction::None;

        }

};
