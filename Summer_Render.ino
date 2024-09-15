// #include "src/utils/Enums.h"

// void renderPlayerCards(uint8_t currentPlane, uint8_t playerId, bool renderFirstCardOnly, bool renderWinners) {

//     if (game.players[playerId].getCard1().getValue() > 0) {

//         if (!renderWinners || game.players[playerId].getCard1().isWinningCard()) {

//             SpritesU::drawOverwriteFX(15, 48, Images::Cards_Bottom, game.players[playerId].getCard1().getCardIndex() + currentPlane);

//         }
//         else {

//             SpritesU::drawOverwriteFX(15, 48, Images::Cards_Bottom_Grey, game.players[playerId].getCard1().getCardIndex() + currentPlane);

//         }

//     }

//     if (game.players[playerId].getCard2().getValue() > 0) {

//         if (!renderWinners || game.players[playerId].getCard2().isWinningCard()) {

//             SpritesU::drawOverwriteFX(25, 48, Images::Cards_Bottom, game.players[playerId].getCard2().getCardIndex() + currentPlane);

//         }
//         else {

//             SpritesU::drawOverwriteFX(25, 48, Images::Cards_Bottom_Grey, game.players[playerId].getCard2().getCardIndex() + currentPlane);

//         }

//     }

// }


// void renderCards_WithActions(uint8_t currentPlane, bool renderWinners) {

//     if (game.gameCards[0].getValue() == 0) {

//         for (uint8_t i = 0; i < 5; ++i) {

//             SpritesU::drawOverwriteFX(19 + (i * 10), 17, Images::Cards_Bottom, (3 * 52) + currentPlane);

//         }

//     }
//     else {

//         uint8_t cardsVisible = 0;

//         for (uint8_t i = 3; i < 5; ++i) {

//             if (game.gameCards[i].getValue() != 0) {

//                 cardsVisible++;

//             }

//         }

//         for (uint8_t i = 0; i < 5; ++i) {

//             if (game.gameCards[i].getValue() == 0) break;

//             else {

//                 if (!renderWinners || game.gameCards[i].isWinningCard()) {
//                     SpritesU::drawOverwriteFX(30 - ((10 * cardsVisible) / 2) + (i * 10), 17, Images::Cards_Bottom, game.gameCards[i].getCardIndex() + currentPlane);
//                 }
//                 else {
//                     SpritesU::drawOverwriteFX(30 - ((10 * cardsVisible) / 2) + (i * 10), 17, Images::Cards_Bottom_Grey, game.gameCards[i].getCardIndex() + currentPlane);
//                 }

//             }

//         }

//     }

// }


// void renderCards(uint8_t currentPlane, bool showOpponentsCards, bool renderWinners, uint8_t winnerId) {

//     if (game.players[5].isPlaying() || game.players[5].getAction() != Action::None) {

//         switch (game.players[5].getAction()) {

//             case Action::Fold:
//                 SpritesU::drawOverwriteFX(49, - (6 - game.getHideCards()), Images::Hand_02_Top, currentPlane);
//                 SpritesU::drawOverwriteFX(52, game.getHideCards(), Images::Fold_Top, currentPlane);
//                 break;

//             case Action::Call:
//                 SpritesU::drawOverwriteFX(49, 0, Images::Hand_02_Top, currentPlane);
//                 SpritesU::drawOverwriteFX(52, 6, Images::Call_Top, currentPlane);
//                 break;

//             case Action::Raise:
//                 SpritesU::drawOverwriteFX(49, 0, Images::Hand_02_Top, currentPlane);
//                 SpritesU::drawOverwriteFX(51, 6, Images::Raise_Top, currentPlane);
//                 break;

//             case Action::Check:
//                 SpritesU::drawOverwriteFX(49, 0, Images::Hand_02_Top, currentPlane);
//                 SpritesU::drawOverwriteFX(50, 6, Images::Check_Top, currentPlane);
//                 break;

//             case Action::AllIn:
//                 SpritesU::drawOverwriteFX(49, 0, Images::Hand_02_Top, currentPlane);
//                 SpritesU::drawOverwriteFX(50, 6, Images::AllIn_Top, currentPlane);
//                 break;

//             default:

//                 if (showOpponentsCards) {

//                     if (!renderWinners || (winnerId == 5 && game.players[winnerId].getCard2().isWinningCard())) {

//                         SpritesU::drawOverwriteFX(59, -1, Images::Cards_Top, game.players[5].getCard2().getCardIndex() + currentPlane);

//                     }
//                     else {

//                         SpritesU::drawOverwriteFX(59, -1, Images::Cards_Top_Grey, game.players[5].getCard2().getCardIndex() + currentPlane);

//                     }

//                     if (!renderWinners || (winnerId == 5 && game.players[winnerId].getCard1().isWinningCard())) {

//                         SpritesU::drawOverwriteFX(49, -1, Images::Cards_Top, game.players[5].getCard1().getCardIndex() + currentPlane);
                    
//                     }
//                     else {

//                         SpritesU::drawOverwriteFX(49, -1, Images::Cards_Top_Grey, game.players[5].getCard1().getCardIndex() + currentPlane);

//                     }

//                 }
//                 else {
//                     SpritesU::drawOverwriteFX(49, 0, Images::Hand_02_Top, currentPlane);
//                     renderBets(5, currentPlane);
//                 }
//                 break;

//         }

//         if (frameCount % 8 == 0 && game.getHideCards() > 0 && game.players[5].getAction() != Action::None) {

//             game.setHideCards(game.getHideCards() - 1);

//             if (game.getHideCards() == 0) {

//                 game.players[5].setAction(Action::None);

//             }

//         }

//     }
//     else {

//         if (game.players[5].isInGame()) {
//             SpritesU::drawOverwriteFX(52, 0, Images::Fold_Top, currentPlane);
//         }
//         else {
//             SpritesU::drawOverwriteFX(52, 0, Images::Out_Top, currentPlane);
//         }

//     }


//     // Player 4

//     if (game.players[4].isPlaying() || game.players[4].getAction() != Action::None) {

//         switch (game.players[4].getAction()) {

//             case Action::Fold:
//                 SpritesU::drawOverwriteFX(16, - (6 - game.getHideCards()), Images::Hand_02_Top, currentPlane);
//                 SpritesU::drawOverwriteFX(19, game.getHideCards(), Images::Fold_Top, currentPlane);
//                 break;

//             case Action::Call:
//                 SpritesU::drawOverwriteFX(16, 0, Images::Hand_02_Top, currentPlane);
//                 SpritesU::drawOverwriteFX(19, 6, Images::Call_Top, currentPlane);
//                 break;

//             case Action::Raise:
//                 SpritesU::drawOverwriteFX(16, 0, Images::Hand_02_Top, currentPlane);
//                 SpritesU::drawOverwriteFX(18, 6, Images::Raise_Top, currentPlane);
//                 break;

//             case Action::Check:
//                 SpritesU::drawOverwriteFX(16, 0, Images::Hand_02_Top, currentPlane);
//                 SpritesU::drawOverwriteFX(17, 6, Images::Check_Top, currentPlane);
//                 break;

//             case Action::AllIn:
//                 SpritesU::drawOverwriteFX(16, 0, Images::Hand_02_Top, currentPlane);
//                 SpritesU::drawOverwriteFX(17, 6, Images::AllIn_Top, currentPlane);
//                 break;

//             default:

//                 if (showOpponentsCards) {

//                     if (!renderWinners || (winnerId == 4 && game.players[winnerId].getCard2().isWinningCard())) {

//                         SpritesU::drawOverwriteFX(26, -1, Images::Cards_Top, game.players[4].getCard2().getCardIndex() + currentPlane);

//                     }
//                     else {

//                         SpritesU::drawOverwriteFX(26, -1, Images::Cards_Top_Grey, game.players[4].getCard2().getCardIndex() + currentPlane);

//                     }

//                     if (!renderWinners || (winnerId == 4 && game.players[winnerId].getCard1().isWinningCard())) {

//                         SpritesU::drawOverwriteFX(16, -1, Images::Cards_Top, game.players[4].getCard1().getCardIndex() + currentPlane);

//                     }
//                     else {

//                         SpritesU::drawOverwriteFX(16, -1, Images::Cards_Top_Grey, game.players[4].getCard1().getCardIndex() + currentPlane);

//                     }

//                 }
//                 else {  

//                     SpritesU::drawOverwriteFX(16, 0, Images::Hand_02_Top, currentPlane);
//                     renderBets(4, currentPlane);

//                 }
//                 break;

//         }

//         if (frameCount % 8 == 0 && game.getHideCards() > 0 && game.players[4].getAction() != Action::None) {
            
//             game.setHideCards(game.getHideCards() - 1);

//             if (game.getHideCards() == 0) {

//                 game.players[4].setAction(Action::None);

//             }

//         }

//     }
//     else {

//         if (game.players[4].isInGame()) {
//             SpritesU::drawOverwriteFX(19, 0, Images::Fold_Top, currentPlane);
//         }
//         else {
//             SpritesU::drawOverwriteFX(19, 0, Images::Out_Top, currentPlane);
//         }

//     }

//     if (game.players[3].isPlaying() || game.players[3].getAction() != Action::None) {

//         switch (game.players[3].getAction()) {

//             case Action::Fold:
//                 SpritesU::drawOverwriteFX(-(6 - game.getHideCards()), 16, Images::Hand_02_Left, currentPlane);
//                 SpritesU::drawOverwriteFX(game.getHideCards(), 19, Images::Fold_Left, currentPlane);
//                 break;

//             case Action::Call:
//                 SpritesU::drawOverwriteFX(0, 16, Images::Hand_02_Left, currentPlane);
//                 SpritesU::drawOverwriteFX(6, 19, Images::Call_Left, currentPlane);
//                 break;

//             case Action::Raise:
//                 SpritesU::drawOverwriteFX(0, 16, Images::Hand_02_Left, currentPlane);
//                 SpritesU::drawOverwriteFX(6, 18, Images::Raise_Left, currentPlane);
//                 break;

//             case Action::Check:
//                 SpritesU::drawOverwriteFX(0, 16, Images::Hand_02_Left, currentPlane);
//                 SpritesU::drawOverwriteFX(6, 17, Images::Check_Left, currentPlane);
//                 break;

//             case Action::AllIn:
//                 SpritesU::drawOverwriteFX(0, 16, Images::Hand_02_Left, currentPlane);
//                 SpritesU::drawOverwriteFX(6, 17, Images::AllIn_Left, currentPlane);
//                 break;

//             default:

//                 if (showOpponentsCards) {

//                     if (!renderWinners || (winnerId == 3 && game.players[winnerId].getCard2().isWinningCard())) {

//                         SpritesU::drawOverwriteFX(-1, 15, Images::Cards_Left, game.players[3].getCard2().getCardIndex() + currentPlane);

//                     }
//                     else {

//                         SpritesU::drawOverwriteFX(-1, 15, Images::Cards_Left_Grey, game.players[3].getCard2().getCardIndex() + currentPlane);

//                     }

//                     if (!renderWinners || (winnerId == 3 && game.players[winnerId].getCard1().isWinningCard())) {

//                         SpritesU::drawOverwriteFX(-1, 25, Images::Cards_Left, game.players[3].getCard1().getCardIndex() + currentPlane);

//                     }
//                     else {

//                         SpritesU::drawOverwriteFX(-1, 25, Images::Cards_Left_Grey, game.players[3].getCard1().getCardIndex() + currentPlane);

//                     }

//                 }
//                 else {   
                                
//                     SpritesU::drawOverwriteFX(0, 16, Images::Hand_02_Left, currentPlane);
//                     renderBets(3, currentPlane);

//                 }

//                 break;

//         }

//         if (frameCount % 8 == 0 && game.getHideCards() > 0 && game.players[3].getAction() != Action::None) {
            
//             game.setHideCards(game.getHideCards() - 1);

//             if (game.getHideCards() == 0) {

//                 game.players[3].setAction(Action::None);

//             }

//         }

//     }
//     else {

//         if (game.players[3].isInGame()) {
//             SpritesU::drawOverwriteFX(0, 19, Images::Fold_Left, currentPlane);
//         }
//         else {
//             SpritesU::drawOverwriteFX(0, 19, Images::Out_Left, currentPlane);
//         }

//     }

//     if (game.players[2].isPlaying() || game.players[2].getAction() != Action::None) {

//         switch (game.players[2].getAction()) {

//             case Action::Fold:
//                 renderPlayerCards(currentPlane, 2, false, false);
//                 SpritesU::drawOverwriteFX(19, 56 - game.getHideCards(), Images::Fold_Top, currentPlane);
//                 break;

//             case Action::Call:
//                 renderPlayerCards(currentPlane, 2, false, false);
//                 SpritesU::drawOverwriteFX(19, 40, Images::Call_Top, currentPlane);
//                 break;

//             case Action::Raise:
//                 renderPlayerCards(currentPlane, 2, false, false);
//                 SpritesU::drawOverwriteFX(18, 40, Images::Raise_Top, currentPlane);
//                 break;

//             case Action::Check:
//                 renderPlayerCards(currentPlane, 2, false, false);
//                 SpritesU::drawOverwriteFX(17, 40, Images::Check_Top, currentPlane);
//                 break;

//             case Action::AllIn:
//                 renderPlayerCards(currentPlane, 2, false, false);
//                 SpritesU::drawOverwriteFX(17, 40, Images::AllIn_Top, currentPlane);
//                 break;

//             default:
//                 renderPlayerCards(currentPlane, 2, false, renderWinners);

//                 if (!showOpponentsCards) {
//                     renderBets(2, currentPlane);
//                 }

//                 break;

//         }

//         if (frameCount % 8 == 0 && game.getHideCards() > 0 && game.players[2].getAction() != Action::None) {

//             game.setHideCards(game.getHideCards() - 1);

//             if (game.getHideCards() == 0) {

//                 game.players[2].setAction(Action::None);

//             }

//         }

//     }
//     else {

//         if (game.players[2].isInGame()) {
//             SpritesU::drawOverwriteFX(19, 56, Images::Fold_Top, currentPlane);
//         }
//         else {
//             SpritesU::drawOverwriteFX(19, 56, Images::Out_Top, currentPlane);
//         }

//     }

//     if (game.players[1].isPlaying() || game.players[1].getAction() != Action::None) {

//         switch (game.players[1].getAction()) {

//             case Action::Fold:
//                 SpritesU::drawOverwriteFX(49, 58 + (6 - game.getHideCards()), Images::Hand_02_Bottom, currentPlane);
//                 SpritesU::drawOverwriteFX(52, 56 - game.getHideCards(), Images::Fold_Top, currentPlane);
//                 break;

//             case Action::Call:
//                 SpritesU::drawOverwriteFX(49, 58, Images::Hand_02_Bottom, currentPlane);
//                 SpritesU::drawOverwriteFX(52, 50, Images::Call_Top, currentPlane);
//                 break;

//             case Action::Raise:
//                 SpritesU::drawOverwriteFX(49, 58, Images::Hand_02_Bottom, currentPlane);
//                 SpritesU::drawOverwriteFX(51, 50, Images::Raise_Top, currentPlane);
//                 break;

//             case Action::Check:
//                 SpritesU::drawOverwriteFX(49, 58, Images::Hand_02_Bottom, currentPlane);
//                 SpritesU::drawOverwriteFX(50, 50, Images::Check_Top, currentPlane);
//                 break;

//             case Action::AllIn:
//                 SpritesU::drawOverwriteFX(49, 58, Images::Hand_02_Bottom, currentPlane);
//                 SpritesU::drawOverwriteFX(50, 50, Images::AllIn_Top, currentPlane);
//                 break;

//             default:

//                 if (showOpponentsCards) {

//                     if (!renderWinners || (winnerId == 1 && game.players[winnerId].getCard2().isWinningCard())) {

//                         SpritesU::drawOverwriteFX(48, 48, Images::Cards_Bottom, game.players[1].getCard2().getCardIndex() + currentPlane);

//                     }
//                     else {

//                         SpritesU::drawOverwriteFX(48, 48, Images::Cards_Bottom_Grey, game.players[1].getCard2().getCardIndex() + currentPlane);

//                     }

//                     if (!renderWinners || (winnerId == 1 && game.players[winnerId].getCard1().isWinningCard())) {

//                         SpritesU::drawOverwriteFX(58, 48, Images::Cards_Bottom, game.players[1].getCard1().getCardIndex() + currentPlane);
                    
//                     }
//                     else {

//                         SpritesU::drawOverwriteFX(58, 48, Images::Cards_Bottom_Grey, game.players[1].getCard1().getCardIndex() + currentPlane);

//                     }

//                 }
//                 else {   

//                     SpritesU::drawOverwriteFX(49, 58, Images::Hand_02_Bottom, currentPlane);
//                     renderBets(1, currentPlane);
                
//                 }

//                 break;

//         }

//         if (frameCount % 8 == 0 && game.getHideCards() > 0 && game.players[1].getAction() != Action::None) {

//             game.setHideCards(game.getHideCards() - 1);

//             if (game.getHideCards() == 0) {

//                 game.players[1].setAction(Action::None);

//             }

//         }

//     }
//     else {

//         if (game.players[1].isInGame()) {
//             SpritesU::drawOverwriteFX(52, 56, Images::Fold_Top, currentPlane);
//         }
//         else {
//             SpritesU::drawOverwriteFX(52, 56, Images::Out_Top, currentPlane);
//         }

//     }

//     if (game.players[0].isPlaying() || game.players[0].getAction() != Action::None) {

//         switch (game.players[0].getAction()) {

//             case Action::Fold:
//                 SpritesU::drawOverwriteFX(90 + (6 - game.getHideCards()), 16, Images::Hand_02_Right, currentPlane);
//                 SpritesU::drawOverwriteFX(82 + (6 - game.getHideCards()), 19, Images::Fold_Right, currentPlane);
//                 break;

//             case Action::Call:
//                 SpritesU::drawOverwriteFX(90, 16, Images::Hand_02_Right, currentPlane);
//                 SpritesU::drawOverwriteFX(82, 19, Images::Call_Right, currentPlane);
//                 break;

//             case Action::Raise:
//                 SpritesU::drawOverwriteFX(90, 16, Images::Hand_02_Right, currentPlane);
//                 SpritesU::drawOverwriteFX(82, 18, Images::Raise_Right, currentPlane);
//                 break;

//             case Action::Check:
//                 SpritesU::drawOverwriteFX(90, 16, Images::Hand_02_Right, currentPlane);
//                 SpritesU::drawOverwriteFX(82, 17, Images::Check_Right, currentPlane);
//                 break;

//             case Action::AllIn:
//                 SpritesU::drawOverwriteFX(90, 16, Images::Hand_02_Right, currentPlane);
//                 SpritesU::drawOverwriteFX(82, 17, Images::AllIn_Right, currentPlane);
//                 break;

//             default:

//                 if (showOpponentsCards) {

//                     if (!renderWinners || (winnerId == 0 && game.players[winnerId].getCard2().isWinningCard())) {

//                         SpritesU::drawOverwriteFX(80, 19, Images::Cards_Right, game.players[0].getCard2().getCardIndex() + currentPlane);

//                     }
//                     else {

//                         SpritesU::drawOverwriteFX(80, 19, Images::Cards_Right_Grey, game.players[0].getCard2().getCardIndex() + currentPlane);

//                     }

//                     if (!renderWinners || (winnerId == 0 && game.players[winnerId].getCard1().isWinningCard())) {

//                         SpritesU::drawOverwriteFX(80, 9, Images::Cards_Right, game.players[0].getCard1().getCardIndex() + currentPlane);

//                     }
//                     else {

//                         SpritesU::drawOverwriteFX(80, 9, Images::Cards_Right_Grey, game.players[0].getCard1().getCardIndex() + currentPlane);

//                     }

//                 }
//                 else {   

//                     SpritesU::drawOverwriteFX(90, 16, Images::Hand_02_Right, currentPlane);
//                     renderBets(0, currentPlane);

//                 }

//                 break;

//         }

//         if (frameCount % 8 == 0 && game.getHideCards() > 0 && game.players[0].getAction() != Action::None) {
       
//             game.setHideCards(game.getHideCards() - 1);

//             if (game.getHideCards() == 0) {

//                 game.players[0].setAction(Action::None);

//             }

//         }

//     }
//     else {

//         if (game.players[0].isInGame()) {
//             SpritesU::drawOverwriteFX(88, 19, Images::Fold_Right, currentPlane);
//         }
//         else {
//             SpritesU::drawOverwriteFX(88, 19, Images::Out_Right, currentPlane);
//         }

//     }

// }


// void renderCards_Dealing(uint8_t currentPlane) {

//     if (game.players[5].isPlaying() || game.players[5].getAction() != Action::None) {

//         if (game.players[5].getCard2().getValue() != 0) {
//             SpritesU::drawOverwriteFX(49, 0, Images::Hand_02_Top, currentPlane);
//         }
//         else {

//             if (game.players[5].getCard1().getValue() != 0) {
//                 SpritesU::drawOverwriteFX(49, 0, Images::Hand_01_Top, currentPlane);
//             }
                
//         }

//         renderBets(5, currentPlane);

//     }
//     else {

//         if (!game.players[5].isInGame()) {
//             SpritesU::drawOverwriteFX(52, 0, Images::Out_Top, currentPlane);
//         }

//     }


//     if (game.players[4].isPlaying() || game.players[4].getAction() != Action::None) {

//         if (game.players[4].getCard2().getValue() != 0) {
//             SpritesU::drawOverwriteFX(16, 0, Images::Hand_02_Top, currentPlane);
//         }
//         else {

//             if (game.players[4].getCard1().getValue() != 0) {
//                 SpritesU::drawOverwriteFX(16, 0, Images::Hand_01_Top, currentPlane);
//             }
                
//         }

//         renderBets(4, currentPlane);

//     }
//     else {

//         if (!game.players[4].isInGame()) {
//             SpritesU::drawOverwriteFX(19, 0, Images::Out_Top, currentPlane);
//         }

//     }


//     if (game.players[3].isPlaying() || game.players[3].getAction() != Action::None) {

//         if (game.players[3].getCard2().getValue() != 0) {
//             SpritesU::drawOverwriteFX(0, 16, Images::Hand_02_Left, currentPlane);
//         }
//         else {

//             if (game.players[3].getCard1().getValue() != 0) {
//                 SpritesU::drawOverwriteFX(0, 16, Images::Hand_01_Left, currentPlane);
//             }
                
//         }

//         renderBets(3, currentPlane);

//     }
//     else {

//         if (!game.players[3].isInGame()) {
//             SpritesU::drawOverwriteFX(0, 19, Images::Out_Left, currentPlane);
//         }

//     }


//     if (game.players[2].isPlaying() || game.players[2].getAction() != Action::None) {

//         if (game.players[2].getCard2().getValue() != 0) {
//             renderPlayerCards(currentPlane, 2, false, false);
//         }
//         else {

//             if (game.players[2].getCard1().getValue() != 0) {
//                 renderPlayerCards(currentPlane, 2, true, false);
//             }
                
//         }

//         renderBets(2, currentPlane);

//     }
//     else {

//         if (!game.players[2].isInGame()) {
//             SpritesU::drawOverwriteFX(22, 56, Images::Out_Top, currentPlane);
//         }

//     }


//     if (game.players[1].isPlaying() || game.players[1].getAction() != Action::None) {

//         if (game.players[1].getCard2().getValue() != 0) {
//             SpritesU::drawOverwriteFX(49, 58, Images::Hand_02_Bottom, currentPlane);
//         }
//         else {

//             if (game.players[1].getCard1().getValue() != 0) {
//                 SpritesU::drawOverwriteFX(49, 58, Images::Hand_01_Bottom, currentPlane);
//             }
                
//         }

//         renderBets(1, currentPlane);

//     }
//     else {

//         if (!game.players[1].isInGame()) {
//             SpritesU::drawOverwriteFX(52, 56, Images::Out_Top, currentPlane);
//         }

//     }


//     if (game.players[0].isPlaying() || game.players[0].getAction() != Action::None) {

//         if (game.players[0].getCard2().getValue() != 0) {
//             SpritesU::drawOverwriteFX(90, 16, Images::Hand_02_Right, currentPlane);
//         }
//         else {

//             if (game.players[0].getCard1().getValue() != 0) {
//                 SpritesU::drawOverwriteFX(90, 16, Images::Hand_01_Right, currentPlane);
//             }
                
//         }

//         renderBets(0, currentPlane);

//     }
//     else {

//         if (!game.players[0].isInGame()) {
//             SpritesU::drawOverwriteFX(88, 19, Images::Out_Right, currentPlane);
//         }

//     }

// }



// void renderBets(uint8_t playerId, uint8_t currentPlane) {
    
//     renderBets(playerId, currentPlane, false);

// }

// void renderBets(uint8_t playerId, uint8_t currentPlane, bool suppressZero) {

//     BetImages betImage = BetImages::None;
//     uint8_t offset = 0;
    
//     switch (playerId) {

//         case 5:

//             offset = getBetWidth(game.players[5].getBet(), suppressZero);

//             if (game.getLargeBlindIdx() == 5)        { offset = offset + 9; betImage = BetImages::LargeBlinds; }
//             else if (game.getSmallBlindIdx() == 5)   { offset = offset + 6; betImage = BetImages::SmallBlinds; }
//             else if (game.getDealerIdx() == 5)       { offset = offset + 6; betImage = BetImages::Dealer; }

//             if (game.players[5].getBet() > 0 || !suppressZero) {

//                 font3x5.setCursor(62 - (offset / 2), 5);
//                 font3x5.print(game.players[5].getBet());

//             }

//             if (betImage != BetImages::None) {

//                 switch (betImage) {

//                     case BetImages::Dealer:
//                         SpritesU::drawPlusMaskFX(58 + (offset / 2), 6, Images::Dealer, currentPlane);
//                         break;

//                     case BetImages::SmallBlinds:
//                         SpritesU::drawPlusMaskFX(58 + (offset / 2), 6, Images::Blinds_Small, currentPlane);
//                         break;

//                     case BetImages::LargeBlinds:
//                         SpritesU::drawPlusMaskFX(55 + (offset / 2), 6, Images::Blinds_Large, currentPlane);
//                         break;

//                 }

//             }

//             break;

//         case 4:

//             offset = getBetWidth(game.players[4].getBet(), suppressZero);

//             if (game.getLargeBlindIdx() == 4)        { offset = offset + 9; betImage = BetImages::LargeBlinds; }
//             else if (game.getSmallBlindIdx() == 4)   { offset = offset + 6; betImage = BetImages::SmallBlinds; }
//             else if (game.getDealerIdx() == 4)       { offset = offset + 6; betImage = BetImages::Dealer; }

//             if (game.players[4].getBet() > 0 || !suppressZero) {

//                 font3x5.setCursor(29 - (offset / 2), 5);
//                 font3x5.print(game.players[4].getBet());

//             }

//             if (betImage != BetImages::None) {

//                 switch (betImage) {

//                     case BetImages::Dealer:
//                         SpritesU::drawPlusMaskFX(24 + (offset / 2), 6, Images::Dealer, currentPlane);
//                         break;

//                     case BetImages::SmallBlinds:
//                         SpritesU::drawPlusMaskFX(24 + (offset / 2), 6, Images::Blinds_Small, currentPlane);
//                         break;

//                     case BetImages::LargeBlinds:
//                         SpritesU::drawPlusMaskFX(22 + (offset / 2), 6, Images::Blinds_Large, currentPlane);
//                         break;

//                 }

//             }

//             break;

//         case 3:

//             offset = getBetWidth(game.players[3].getBet(), suppressZero);

//             if (game.getLargeBlindIdx() == 3)        { offset = offset + 9; betImage = BetImages::LargeBlinds; }
//             else if (game.getSmallBlindIdx() == 3)   { offset = offset + 6; betImage = BetImages::SmallBlinds; }
//             else if (game.getDealerIdx() == 3)       { offset = offset + 6; betImage = BetImages::Dealer; }

//             if (game.players[3].getBet() > 0 || !suppressZero) {

//                 font3x5L.setCursor(6, 28 - (offset / 2));
//                 font3x5L.print(game.players[3].getBet());

//             }

//             if (betImage != BetImages::None) {

//                 switch (betImage) {

//                     case BetImages::Dealer:
//                         SpritesU::drawPlusMaskFX(6, 24 + (offset / 2), Images::Dealer, currentPlane);
//                         break;

//                     case BetImages::SmallBlinds:
//                         SpritesU::drawPlusMaskFX(6, 24 + (offset / 2), Images::Blinds_Small, currentPlane);
//                         break;

//                     case BetImages::LargeBlinds:
//                         SpritesU::drawPlusMaskFX(6, 22 + (offset / 2), Images::Blinds_Large, 6 + currentPlane);
//                         break;

//                 }

//             }

//             break;

//         case 2:

//             offset = getBetWidth(game.players[2].getBet(), suppressZero);

//             if (game.getLargeBlindIdx() == 2)        { offset = offset + 9; betImage = BetImages::LargeBlinds; }
//             else if (game.getSmallBlindIdx() == 2)   { offset = offset + 6; betImage = BetImages::SmallBlinds; }
//             else if (game.getDealerIdx() == 2)       { offset = offset + 6; betImage = BetImages::Dealer; }

//             renderPlayerCards(currentPlane, 2, false, false);

//             if (game.players[2].getBet() > 0 || !suppressZero) {

//                 font3x5.setCursor(29 - (offset / 2), 41);
//                 font3x5.print(game.players[2].getBet());

//             }

//             if (betImage != BetImages::None) {

//                 switch (betImage) {

//                     case BetImages::Dealer:
//                         SpritesU::drawPlusMaskFX(24 + (offset / 2), 42, Images::Dealer, currentPlane);
//                         break;

//                     case BetImages::SmallBlinds:
//                         SpritesU::drawPlusMaskFX(24 + (offset / 2), 42, Images::Blinds_Small, currentPlane);
//                         break;

//                     case BetImages::LargeBlinds:
//                         SpritesU::drawPlusMaskFX(22 + (offset / 2), 42, Images::Blinds_Large, currentPlane);
//                         break;

//                 }

//             }  

//             break;

//         case 1:

//             offset = getBetWidth(game.players[1].getBet(), suppressZero);

//             if (game.getLargeBlindIdx() == 1)        { offset = offset + 9; betImage = BetImages::LargeBlinds; }        
//             else if (game.getSmallBlindIdx() == 1)   { offset = offset + 6; betImage = BetImages::SmallBlinds; }
//             else if (game.getDealerIdx() == 1)       { offset = offset + 6; betImage = BetImages::Dealer; }

//             if (game.players[1].getBet() > 0 || !suppressZero) {

//                 font3x5.setCursor(62 - (offset / 2), 51);
//                 font3x5.print(game.players[1].getBet());

//             }

//             if (betImage != BetImages::None) {

//                 switch (betImage) {

//                     case BetImages::Dealer:
//                         SpritesU::drawPlusMaskFX(58 + (offset / 2), 52, Images::Dealer, currentPlane);
//                         break;

//                     case BetImages::SmallBlinds:
//                         SpritesU::drawPlusMaskFX(58 + (offset / 2), 52, Images::Blinds_Small, currentPlane);
//                         break;

//                     case BetImages::LargeBlinds:
//                         SpritesU::drawPlusMaskFX(55 + (offset / 2), 52, Images::Blinds_Large, currentPlane);
//                         break;

//                 }

//             }

//             break;

//         case 0:
        
//             offset = getBetWidth(game.players[0].getBet(), suppressZero);

//             if (game.getLargeBlindIdx() == 0)        { offset = offset + 9; betImage = BetImages::LargeBlinds; }        
//             else if (game.getSmallBlindIdx() == 0)   { offset = offset + 6; betImage = BetImages::SmallBlinds; }
//             else if (game.getDealerIdx() == 0)       { offset = offset + 6; betImage = BetImages::Dealer; }

//             if (game.players[0].getBet() > 0 || !suppressZero) {

//                 font3x5R.setCursor(84, 19 + (offset / 2));
//                 font3x5R.print(game.players[0].getBet());

//             }

//             if (betImage != BetImages::None) {

//                 switch (betImage) {

//                     case BetImages::Dealer:
//                         SpritesU::drawPlusMaskFX(84, 28 - (offset / 2), Images::Dealer, currentPlane);
//                         break;

//                     case BetImages::SmallBlinds:
//                         SpritesU::drawPlusMaskFX(84, 28 - (offset / 2), Images::Blinds_Small, currentPlane);
//                         break;

//                     case BetImages::LargeBlinds:
//                         SpritesU::drawPlusMaskFX(84, 27 - (offset / 2), Images::Blinds_Large, 6 + currentPlane);
//                         break;

//                 }

//             }

//             break;

//     }

// }


// void renderPot(uint8_t currentPlane, bool showPot) {


//     // Render HUD

//     bool blink = frameCount % 160 < 80;

//     uint8_t idx = 3 * optionsTopMenuIdx;
    

//     // Blink the current seat if the player has no money left!

//     if (game.players[optionsTopMenuIdx].isPlaying() && game.players[optionsTopMenuIdx].getMoney() == 0) {

//         if (blink) {
            
//             idx = 3 * (6 + optionsTopMenuIdx);

//         }

//     }

//     SpritesU::drawOverwriteFX(95, 0, Images::Options_Top, idx + currentPlane);


//     // Blink the remaining seats if the player has no money left!

//     for (uint8_t i = 0; i < 6; i++) {

//         if (optionsTopMenuIdx != i && game.players[i].isPlaying() && ((game.players[i].getMoney() == 0 && blink) || game.players[i].getMoney() > 0)) {

//             uint8_t xPos = FX::readIndexedUInt8(Images::Options_Top_Coords, i * 2);
//             uint8_t yPos = FX::readIndexedUInt8(Images::Options_Top_Coords, (i * 2) + 1);            
//             uint24_t imageIdx = FX::readIndexedUInt24(Images::Options_Top_Imgs, i);
//             SpritesU::drawPlusMaskFX(xPos, yPos, imageIdx, currentPlane);

//         }

//     }

//     if (showPot) {

//         uint8_t width = getBetWidth(game.getPrizePool());

//         SpritesU::drawPlusMaskFX(FX::readIndexedUInt8(Constants::Score_Panel_XPanelPos, width / 4), 32, Images::Score_Panel, FX::readIndexedUInt8(Constants::Score_Panel_Idx, width / 4) + currentPlane);

//         if (currentPlane < 3) {

            
//             font3x5.setCursor(FX::readIndexedUInt8(Constants::Score_Panel_XTextPos, width / 4), 33);
//             font3x5.print(game.getPrizePool());

//         }

//     }

//     if (currentPlane < 2) {

//         font3x5.setCursor(113 - (getBetWidth(game.players[optionsTopMenuIdx].getMoney()) / 2), 29);
//         font3x5.print(game.players[optionsTopMenuIdx].getMoney());

//     }

// }



// void renderOptions(uint8_t currentPlane, bool showOptions) {
    
//     const uint8_t NO_ACTIONS = 7;

//     if (showOptions) {

//         uint8_t idx = 0;
//         uint8_t humanId = game.getHumanId();

//         bool canCheck = game.players[humanId].getCanCheck();
//         bool canCall  = game.players[humanId].getCanCall();
//         bool canRaise = game.players[humanId].getCanRaise();
//         bool canAllIn = game.players[humanId].getCanAllIn();

//         if (!canCheck && !canCall && !canRaise && !canAllIn)    idx = 6;
//         if (!canCheck && !canCall && !canRaise &&  canAllIn)    idx = 3;
//         if (!canCheck && !canCall &&  canRaise && !canAllIn)    idx = NO_ACTIONS;
//         if (!canCheck && !canCall &&  canRaise &&  canAllIn)    idx = NO_ACTIONS;
//         if (!canCheck &&  canCall && !canRaise && !canAllIn)    idx = 2;
//         if (!canCheck &&  canCall && !canRaise &&  canAllIn)    idx = 4;
//         if (!canCheck &&  canCall &&  canRaise && !canAllIn)    idx = 1;
//         if (!canCheck &&  canCall &&  canRaise &&  canAllIn)    idx = NO_ACTIONS;

//         if ( canCheck && !canCall && !canRaise && !canAllIn)    idx = 6;
//         if ( canCheck && !canCall && !canRaise &&  canAllIn)    idx = 5;
//         if ( canCheck && !canCall &&  canRaise && !canAllIn)    idx = 0;
//         if ( canCheck && !canCall &&  canRaise &&  canAllIn)    idx = NO_ACTIONS;
//         if ( canCheck &&  canCall && !canRaise && !canAllIn)    idx = NO_ACTIONS;
//         if ( canCheck &&  canCall && !canRaise &&  canAllIn)    idx = 5;
//         if ( canCheck &&  canCall &&  canRaise && !canAllIn)    idx = 0;
//         if ( canCheck &&  canCall &&  canRaise &&  canAllIn)    idx = NO_ACTIONS;

//         if (canRaise && optionsMenuIdx == 2) {

//             idx = idx + 8;

//         }
        
//         SpritesU::drawOverwriteFX(95, 40, Images::Options, (idx * 9) + (3 * optionsMenuIdx) + currentPlane);
        

//     }
//     else {

//         SpritesU::drawOverwriteFX(95, 40, Images::Options, (7 * 9) + (3 * optionsMenuIdx) + currentPlane);

//     }

// }


// void renderGameUI(uint8_t currentPlane) {
    
//     renderGameUI(currentPlane, false);

// }

// void renderGameUI(uint8_t currentPlane, bool showOptions) {

//     renderCards_WithActions(currentPlane, false);
//     renderPlayerCards(currentPlane, game.getHumanId(), false, false);
//     renderCards(currentPlane, false, false, Constants::NoPlayer);
//     renderPot(currentPlane, true);
//     renderOptions(currentPlane, showOptions);

// }

// void renderAnteBlindsDeal(uint8_t currentPlane) {

//     renderCards_WithActions(currentPlane, false);
//     renderCards_Dealing(currentPlane);
//     renderPot(currentPlane, true);
//     renderOptions(currentPlane, false);

// }

// void renderGameOver(uint8_t currentPlane) {
            
//     renderCards_WithActions(currentPlane, true);
//     renderPlayerCards(currentPlane, game.getHumanId(), false, false);
//     renderCards(currentPlane, false, false, Constants::NoPlayer);
//     renderPot(currentPlane, true);
//     renderOptions(currentPlane, false);

// }