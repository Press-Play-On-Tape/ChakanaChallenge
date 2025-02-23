
#pragma once

#include <Arduboy2.h>
#include "../utils/Constants.h"
#include "../utils/Enums.h"

struct InventoryItem {

    private:

        ItemType itemType = ItemType::None;

    public:

        ItemType getItemType()                          { return this->itemType; }

        void setItemType(ItemType val)                  { this->itemType = val; }

};
