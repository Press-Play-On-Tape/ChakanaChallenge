#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"



// Stance stance = Stance::Man_Walk_RH_01;

// int16_t enemy = -20;



void play_Init() {

    Player &player = world.getPlayer();
    gameState = GameState::Play_BoatEnters;
    frameCount = 0;

    world.setX(0);
    // world.setPalm1(-240);
    // world.setPalm2(-130);
    // world.setPalm3(0);
    // world.setPalm4(140);

    world.setPalm1(60);
    world.setPalm2(180);
    world.setPalm3(340);
    world.setPalm4(420);


    world.setPalm5(116);
    world.setPalm6(66);
    world.setPalm7(-20);
    world.setPalm8(-80);

    world.setBackground(0);
    world.setWave(0);
    world.setWaveIdx(0);

    world.getBoat().setX(-82);
    player.setYSeq(22);

}

void play_Update() {


    Player &player = world.getPlayer();

    frameCount++;
    if (frameCount % 4 == 0) {

    uint8_t pressed = getPressedButtons();
    uint8_t justPressed = getJustPressedButtons();
    
    switch (gameState) {

        case GameState::Play_BoatEnters:

            world.getBoat().setX(world.getBoat().getX() + 2);

            if (world.getBoat().getX() == -10) {

                gameState = GameState::Play_PlayerJumps;
                player.pushSequence(Stance::Man_StandingJumpDown_RH_01, Stance::Man_StandingJumpDown_RH_09);
                player.pushSequence(Stance::Man_Walk_RH_01, Stance::Man_Walk_RH_04);
                player.setStance(Stance::Man_Walk_RH_01);
                player.setXSeq(36);
                player.setYSeq(22);

            }
            break;

        case GameState::Play_PlayerJumps:

            if (player.getCount() < 16 && world.getBoat().getX() > -82) {
            
                world.getBoat().setX(world.getBoat().getX() - 2);
                world.incForeground(-3);
                world.incBackground(-1);
            
            }

            if (!player.isEmpty()) {

                uint16_t newStance = player.pop();
                player.setStance(abs(newStance));
                player.setXSeq(player.getXSeq() + 1);

            }
            else {

                gameState = GameState::Play_PlayerCenters;
                player.setXSeq(16);
                player.setYSeq(Constants::GroundY);

                for (uint8_t i = 0l; i < 12; i++) {
                    player.pushSequence(Stance::Man_Walk_RH_01, Stance::Man_Walk_RH_04);
                }
                // player.pushSequence(Stance::Man_Walk_RH_01, Stance::Man_Walk_RH_04);
                // player.pushSequence(Stance::Man_Walk_RH_01, Stance::Man_Walk_RH_04);

                // player.pushSequence(Stance::Man_Walk_RH_01, Stance::Man_Walk_RH_04);
                // player.pushSequence(Stance::Man_Walk_RH_01, Stance::Man_Walk_RH_04);
                // player.pushSequence(Stance::Man_Walk_RH_01, Stance::Man_Walk_RH_04);

                // player.pushSequence(Stance::Man_Walk_RH_01, Stance::Man_Walk_RH_04);
                // player.pushSequence(Stance::Man_Walk_RH_01, Stance::Man_Walk_RH_04);
                // player.pushSequence(Stance::Man_Walk_RH_01, Stance::Man_Walk_RH_04);
                // player.pushSequence(Stance::Man_Walk_RH_01, Stance::Man_Walk_RH_04);

            }

            break;

        case GameState::Play_PlayerCenters:

            if (world.getBoat().getX()  > -82) {
            
                world.getBoat().setX(world.getBoat().getX() - 3);
                world.incForeground(-3);
                world.incBackground(-1);

            }

            if (!player.isEmpty()) {

                uint16_t newStance = player.pop();
                player.setStance(abs(newStance));
                player.setXSeq(player.getXSeq() + 1);

            }
            else {
                gameState = GameState::PlayGame;
//                gameState = GameState::PlayGame_Init;

            }

            break;


    }


    }
    
}


void play(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    Player &player = world.getPlayer();
    if (a.needsUpdate()) play_Update();

    uint8_t currentPlane = a.currentPlane();

    SpritesU::drawOverwriteFX(world.getBackground(), 0, Images::Background, currentPlane);    
    SpritesU::drawOverwriteFX(world.getBackground() + 128, 0, Images::Background, currentPlane);    

    SpritesU::drawPlusMaskFX(world.getPalm5(), 20, Images::Palm5, currentPlane);
    SpritesU::drawPlusMaskFX(world.getPalm6(), 20, Images::Palm6, currentPlane);
    SpritesU::drawPlusMaskFX(world.getPalm7(), 20, Images::Palm5, currentPlane);
    SpritesU::drawPlusMaskFX(world.getPalm8(), 20, Images::Palm6, currentPlane);

    FX::seekData(Constants::StanceImgIdx + static_cast<uint16_t>(player.getStance()));
    uint8_t stanceImg = FX::readPendingUInt8();
    FX::readEnd();

    FX::seekData(Constants::StanceY + static_cast<uint16_t>(player.getStance()));
    uint8_t stanceY = FX::readPendingUInt8();
    FX::readEnd();

    SpritesU::drawOverwriteFX(world.getWave(), 55, Images::Waves, ((world.getWaveIdx() / 64) * 3) + currentPlane);
    SpritesU::drawOverwriteFX(world.getWave() + 128, 55, Images::Waves, ((world.getWaveIdx() / 64) * 3) + currentPlane);
    SpritesU::drawOverwriteFX(world.getWave(), 32, Images::Beach_LH, ((world.getWaveIdx() / 64) * 3) + currentPlane);

    switch (gameState) {

        case GameState::Play_BoatEnters:
            SpritesU::drawPlusMaskFX(world.getBoat().getX(), -4, Images::Boat, currentPlane);
            SpritesU::drawPlusMaskFX(world.getBoat().getX() + 35, player.getYSeq(), Images::Player, (7 * 3) + currentPlane);
            break;

        case GameState::Play_PlayerJumps:
            SpritesU::drawPlusMaskFX(world.getBoat().getX(), -4, Images::Boat, currentPlane);
            SpritesU::drawPlusMaskFX(player.getXSeq() + world.getBoat().getX(), player.getYSeq() + stanceY, Images::Player, (stanceImg * 3) + currentPlane);
            break;

        case GameState::Play_PlayerCenters:
            SpritesU::drawPlusMaskFX(world.getBoat().getX(), -4, Images::Boat, currentPlane);
            SpritesU::drawPlusMaskFX(player.getXSeq(), player.getYSeq(), Images::Player, (stanceImg * 3) + currentPlane);
            break;


    }



    SpritesU::drawPlusMaskFX(world.getPalm1() / 2, 10, Images::Palm1, currentPlane);
    SpritesU::drawPlusMaskFX(world.getPalm2() / 2, 10, Images::Palm2, currentPlane);
    // SpritesU::drawPlusMaskFX(world.getPalm3() / 2, 10, Images::Palm3, currentPlane);
    SpritesU::drawPlusMaskFX(world.getPalm4() / 2, 10, Images::Palm4, currentPlane);


    world.update(false);


}

