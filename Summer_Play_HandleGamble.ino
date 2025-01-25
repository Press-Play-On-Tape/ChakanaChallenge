#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"

#ifdef GAMBLE

void playGame_HandleGamble(Player &player, uint8_t pressed, uint8_t justPressed) {

    if (justPressed & A_BUTTON) {
                
        switch (world.getGameState()) {

            case GameState::Play_Gamble_Select_Play:     

                if (player.getChakanas() >= 5) {

                    world.setGameState(GameState::Play_Gamble_Select_Spin);
                    player.setChakanas(player.getChakanas() - 5);
                    titleCounter = a.randomLFSR(0, 10);
                    titleCounter = (titleCounter < 2) ? 0 : 104;

                }
                else {

                    world.setGameState(GameState::Play_Game);

                }

                break;

            case GameState::Play_Gamble_Select_Exit:     
                a.pollButtons();
                world.setGameState(GameState::Play_Game);
                break;

            case GameState::Play_Gamble_Select_Win:     
            case GameState::Play_Gamble_Select_Lose:     
                world.setGameState(GameState::Play_Gamble_Select_Play);
                break;

            default: break;

        }

    }
    else if (justPressed & UP_BUTTON) {
        
        switch (world.getGameState()) {

            case GameState::Play_Gamble_Select_Play:
                world.setGameState(GameState::Play_Gamble_Select_Exit);
                break;

        }

    }
    else if (justPressed & DOWN_BUTTON) {

        switch (world.getGameState()) {

            case GameState::Play_Gamble_Select_Exit:

                if (player.getChakanas() >= 5) {
                    world.setGameState(GameState::Play_Gamble_Select_Play);
                }

                break;


        }

    }
    else if (justPressed & B_BUTTON) {

        switch (world.getGameState()) {

            case GameState::Play_Gamble_Select_Play:
            case GameState::Play_Gamble_Select_Exit:
                world.setGameState(GameState::Play_Game);
                break;

        }

    }
        
}
#endif