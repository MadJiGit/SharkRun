//
//  MusicData.cpp
//  TestGame
//
//  Created by Madji on 21.06.19.
//

#include "MusicData.hpp"

extern int global_var;

MusicData   *MusicData::_musicData;

MusicData::MusicData()
{

}
MusicData::~MusicData()
{
    
}

MusicData *MusicData::getInstance()
{
    if (!_musicData)
    {
        return nullptr;
    }
    else
    {
        return _musicData;
    }
}

MusicData *MusicData::getMusicData()
{
    if ( _musicData == nullptr )
    {
        _musicData = new MusicData();
        _musicData->initStats();
    }
 
    return _musicData;
}

void MusicData::initStats()
{
    
//    log( "row 49 MusicData, %d", ++global_var );
    
    
    _userData = UserData::getUserData();
    _dataStruct = _userData->getDataStruct();
    
    setTemporaryLevels();
    preloadGameMusic();
    preloadAllEffects();
    
//    log("MD row 59 TempML-%f TempEL-%f ", getTemporaryMusicLevel(), getTemporaryEffectsLevel());
    setGameMusicLevel( getTemporaryMusicLevel() );
    setGameEffectsLevel( getTemporaryEffectsLevel() );
    
}

void MusicData::setTemporaryLevels()
{
//    log("MD row 67 ML-%f EL-%f ", _dataStruct->ds_musicVolumeLevel, _dataStruct->ds_soundEffectsVolumeLevel);
    this->tempMusicLevel = _dataStruct->ds_musicVolumeLevel;
    this->tempEffectsLevel = _dataStruct->ds_soundEffectsVolumeLevel;
}

void MusicData::saveData()
{
    setTemporaryLevels();
    _userData->saveUserData();
}

void MusicData::saveMusicLevel( float data )
{
    _dataStruct->ds_musicVolumeLevel = data;
    saveData();
}

void MusicData::saveEffectsLevel( float data )
{
    _dataStruct->ds_soundEffectsVolumeLevel = data;
    saveData();
}

float MusicData::getTemporaryMusicLevel()
{
    return this->tempMusicLevel;
}

float MusicData::getTemporaryEffectsLevel()
{
    return this->tempEffectsLevel;
}

void MusicData::setGameEffectsLevel( float data )
{
//    log("row 102 - MusicData::setGameEffectsLevel %.2f", data );
    eatFishSound->setVolume( returnIdEatFishSound, ( data ) );
    earnStarSound->setVolume( returnIdEarnStarSound, ( data ) );
    earnHeartSound->setVolume( returnIdEarnHeartSound, ( data ) );
    hitBarrelSound->setVolume( returnIdHitBarrelSound, ( data ) );
    hitMineSound->setVolume( returnIdHitMineSound, ( data ) );
    sharkDiedSound->setVolume( returnIdSharkDiedSound, ( data ) );
    okButtonSound->setVolume( returnIdOkButtonSound, ( data ) );
    regularButtonSound->setVolume( returnIdRegularButtonSound, ( data ) );
    denyButtonSound->setVolume( returnIdDenyButtonSound, ( data ) );
    choseMenuSound->setVolume( returnIdChoseMenuSound, ( data ) );
    startClickButtonSound->setVolume( returnIdStartClickButtonSound, ( data ) );
    endClickButtonSound->setVolume( returnIdEndClickButtonSound, ( data ) );
    
}

void MusicData::setGameMusicLevel( float data )
{
//    log("row 120 MUSICDATA music level from file %f", data);
    gameMusic->setVolume( returnIdGameMusic, ( data ) );
//    log("row 122 MUSICDATA game music after set level from file %f", gameMusic->getVolume( returnIdGameMusic ));
}

void MusicData::preloadAllEffects()
{
    eatFishSound->preload( "eat_fish.wav" );
    earnStarSound->preload( "earn_star.wav" );
    earnHeartSound->preload( "earn_heart.wav" );
    hitBarrelSound->preload( "18400__inferno__waterxplo.wav" );
    hitMineSound->preload( "18400__inferno__waterxplo.wav" );
    sharkDiedSound->preload( "failure_trumpet.mp3" );
    okButtonSound->preload( "mouse_click.wav" );
    regularButtonSound->preload( "mouse_click.wav" );
    denyButtonSound->preload( "mouse_click.wav" );
    choseMenuSound->preload( "mouse_click.wav" );
    choseMenuSoundStart->preload( "menu_button_start.wav" );
    choseMenuSoundEnd->preload( "menu_button_end.wav" );
    startClickButtonSound->preload( "test_start.wav" );
    endClickButtonSound->preload( "test_end.wav" );
}

void MusicData::unloadAllEffects()
{
    eatFishSound->stop( returnIdEatFishSound );
    earnStarSound->stop( returnIdEarnStarSound );
    earnHeartSound->stop( returnIdEarnHeartSound );
    hitBarrelSound->stop( returnIdHitBarrelSound );
    hitMineSound->stop( returnIdHitMineSound );
    sharkDiedSound->stop( returnIdSharkDiedSound );
    okButtonSound->stop( returnIdOkButtonSound );
    regularButtonSound->stop( returnIdRegularButtonSound );
    denyButtonSound->stop( returnIdDenyButtonSound );
    choseMenuSound->stop( returnIdChoseMenuSound );
    choseMenuSoundStart->stop( returnIdChoseMenuSoundStart );
    choseMenuSoundEnd->stop( returnIdChoseMenuSoundEnd );
    startClickButtonSound->stop( returnIdStartClickButtonSound );
    endClickButtonSound->stop( returnIdEndClickButtonSound );
    
    eatFishSound->end();
    earnStarSound->end();
    earnHeartSound->end();
    hitBarrelSound->end();
    hitMineSound->end();
    sharkDiedSound->end();
    okButtonSound->end();
    regularButtonSound->end();
    denyButtonSound->end();
    choseMenuSound->end();
    choseMenuSoundStart->end();
    choseMenuSoundEnd->end();
    startClickButtonSound->end();
    endClickButtonSound->end();
    
}

void MusicData::preloadGameMusic()
{
    gameMusic->preload( "game_music.wav" );
}

void MusicData::unloadGameMusic()
{
    gameMusic->end();
}

void MusicData::playGameMusic()
{
//    log( "row 189 GAMEMUSIC tempMusicLevel %f", getTemporaryMusicLevel() );
    if (false == isGameMusicIsRunning) {
        isGameMusicIsRunning = true;
        returnIdGameMusic = gameMusic->AudioEngine::play2d( "game_music.wav", true, getTemporaryMusicLevel() );
    }
}

void MusicData::playButtonStartClickSound()
{
    returnIdStartClickButtonSound = startClickButtonSound->AudioEngine::play2d( "test_start.wav", false, getTemporaryEffectsLevel() );
}
void MusicData::playButtonEndClickSound()
{
    returnIdEndClickButtonSound = endClickButtonSound->AudioEngine::play2d( "test_end.wav", false, getTemporaryEffectsLevel() );
}

void MusicData::pauseGameMusic()
{
//    gameMusic->pause( returnIdGameMusic );
}

void MusicData::resumeGameMusic()
{
//    gameMusic->resume( returnIdGameMusic );
}

void MusicData::stopGameMusic()
{
    isGameMusicIsRunning = false;
    gameMusic->stop( returnIdGameMusic );
}

void MusicData::playEatFishSound()
{
    returnIdEatFishSound = eatFishSound->AudioEngine::play2d( "eat_fish.wav", false, getTemporaryEffectsLevel() );
}

void MusicData::playEarnStarSound()
{
    returnIdEarnStarSound = earnStarSound->AudioEngine::play2d( "earn_star.wav", false, getTemporaryEffectsLevel() );
}

void MusicData::playEarnHeartSound()
{
    returnIdEarnHeartSound = earnHeartSound->AudioEngine::play2d( "earn_heart.wav", false, getTemporaryEffectsLevel() );
}

void MusicData::playSharkDiedSound()
{
    sharkDiedSound->AudioEngine::play2d( "failure_trumpet.mp3", false, getTemporaryEffectsLevel() );
}

void MusicData::playHitMineSound()
{
    sharkDiedSound->AudioEngine::play2d( "18400__inferno__waterxplo.wav", false, getTemporaryEffectsLevel() );
}

void MusicData::playHitBarrelSound()
{
    sharkDiedSound->AudioEngine::play2d( "18400__inferno__waterxplo.wav", false, getTemporaryEffectsLevel() );
}

void MusicData::playChoseMenuSound()
{
    returnIdChoseMenuSound = choseMenuSound->AudioEngine::play2d( "button-28.wav", false, getTemporaryEffectsLevel() );
}

void MusicData::playChoseMenuSoundStart()
{
    returnIdChoseMenuSoundStart = choseMenuSound->AudioEngine::play2d( "menu_button_start.wav", false, getTemporaryEffectsLevel() );
}

void MusicData::playChoseMenuSoundEnd()
{
    returnIdChoseMenuSoundEnd = choseMenuSound->AudioEngine::play2d( "menu_button_end.wav", false, getTemporaryEffectsLevel() );
}

bool MusicData::returnIsGameMusicIsRunning()
{
    return isGameMusicIsRunning;
}
