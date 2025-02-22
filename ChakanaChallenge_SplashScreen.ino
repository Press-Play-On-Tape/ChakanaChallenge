#include <Arduboy2.h>


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
#ifndef DEBUG

void splashScreen_Update() { 

    world.incFrameCount();

    if (titleCounter < 32) titleCounter++;   

    uint8_t justPressed = getJustPressedButtons();

    if (justPressed > 0 && titleCounter == 32) {
        
        #ifndef DEBUG_FIXED_RAND
            a.initRandomLFSRSeed();
        #else
            a.rnd = 0xACE1;
        #endif
        
        world.setGameState(GameState::Title_Init); 

    }
    
}


void splashScreen(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {
    
    currentPlane = a.currentPlane();
    uint8_t idx = static_cast<uint8_t>(world.getGameState()) - static_cast<uint8_t>(GameState::SplashScreen_Start);

    SpritesU::drawOverwriteFX(0, 0, Images::PPOT, (3 * idx) + currentPlane);

    if (world.getFrameCount() == 12) {

        idx = (idx + 1) % 4;
        world.setFrameCount(0);
        world.setGameState(static_cast<GameState>(static_cast<uint8_t>(GameState::SplashScreen_Start) + idx));

    }

    if (a.needsUpdate()) splashScreen_Update();

}

#else

void splashScreen(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {
    
    world.setGameState(GameState::Title_Init);

}

#endif