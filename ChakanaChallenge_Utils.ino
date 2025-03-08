#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"


uint8_t getJustPressedButtons() {

    a.pollButtons();
    return a.justPressedButtons();

}

uint8_t getPressedButtons() {

    return a.pressedButtons();

}



