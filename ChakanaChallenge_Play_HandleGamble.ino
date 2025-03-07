#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"

void playGame_HandleGamble(Player &player, uint8_t justPressed) {

    #ifndef DEBUG 

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

                    playGame_HandleMenu(world.getGameState());

                }

                break;

            case GameState::Play_Gamble_Select_Exit:     
                a.pollButtons();
                playGame_HandleMenu(world.getGameState());
                break;

            case GameState::Play_Gamble_Select_Win:     
            case GameState::Play_Gamble_Select_Lose:     
                world.setGameState(GameState::Play_Gamble_Select_Play);
                break;

            default: break;

        }

    }
    else if (justPressed & UP_BUTTON) {
        
        if (world.getGameState() == GameState::Play_Gamble_Select_Play) {

            world.setGameState(GameState::Play_Gamble_Select_Exit);

        }

    }
    else if (justPressed & DOWN_BUTTON) {

        if (world.getGameState() == GameState::Play_Gamble_Select_Exit) {

            if (player.getChakanas() >= 5) {
                world.setGameState(GameState::Play_Gamble_Select_Play);
            }

        }

    }
    else if (justPressed & B_BUTTON) {

        switch (world.getGameState()) {

            case GameState::Play_Gamble_Select_Play:
            case GameState::Play_Gamble_Select_Exit:
                playGame_HandleMenu(world.getGameState());
                break;

        }

    }

    #endif
        
}
