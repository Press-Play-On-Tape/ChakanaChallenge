#include "src/utils/ArduboyG.h"
#include "src/utils/SynthU.hpp"

static MusicSong current_song;
static MusicSong current_song_bkp;

void audioUpdate() {

    if (!SynthU::update()) {
        
        playMusic();

    }

    auto v = soundSettings.getVolume();

    if (SynthU::playingSFX()) {

        SynthU::setVolume(v > 6 ? v - 6 : 0);
        SynthU::setVolumeSFX(v);

    }
    else {

        SynthU::setVolume(v);

    }

}

void audioInit() {

    SynthU::setup();
    SynthU::setVolume(soundSettings.getVolume());
    SynthU::setVolumeSFX(soundSettings.getVolume());

}

void setAudioOn() {
    
    Arduboy2Audio::on();

}

void setAudioOff() {

    Arduboy2Audio::off();
    SynthU::stop();

}

bool isAudioEnabled() {

    return Arduboy2Audio::enabled();

}

MusicSong getSongPlaying() {

    return current_song;

}


void playSong(MusicSong song) {

    current_song = song;

    if (soundSettings.getMusic() && isAudioEnabled()) {

        uint24_t musicStart = FX::readIndexedUInt24(Music::Songs, static_cast<uint8_t>(song));
        SynthU::play(musicStart);

    }

}

void playSFX(MusicSFX sfx) {

    if (soundSettings.getSFX() && isAudioEnabled()) {

        uint24_t sfxStart = FX::readIndexedUInt24(Music::SFXs, static_cast<uint8_t>(sfx));
        SynthU::playSFX(sfxStart);

    }

}

void stopMusic() {

    SynthU::stop();

}

void stopSFX() {

    SynthU::stopSFX();

}

bool isSFXPlaying() {

    return SynthU::playingSFX();

}

bool isSongPlaying() {

    return SynthU::playing();

}

void playMusic() {
 
    playSong(current_song);

}

