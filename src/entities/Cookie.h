#pragma once

#include <ArduboyFX.h>  
#include "../utils/Constants.h"

struct Cookie {

    bool hasSavedGame;
    bool hasPlayedBefore;
    SoundSettings soundSettings;
    World world;
    Menu menu;

};
