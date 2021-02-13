//
//  MusicData.hpp
//  TestGame
//
//  Created by Madji on 21.06.19.
//

#ifndef MusicData_hpp
#define MusicData_hpp

#pragma once
#include <stdio.h>
#include "AudioEngine.h"
#include "UserData.hpp"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocos2d::experimental;

class UserData;
class GameData;
struct dataStruct;

class MusicData
{
private:
    
    static  MusicData   *_musicData;
    
    GameData            *gameData;
    
    float               musicLevelFromFile;
    float               effectsLevelFromFile;
    
    float               tempMusicLevel, tempEffectsLevel;

//    SimpleAudioEngine   *gameMusic;
//    SimpleAudioEngine   *eatFishSound;
//    SimpleAudioEngine   *earnStarSound;
//    SimpleAudioEngine   *hitBarrelSound;
//    SimpleAudioEngine   *hitMineSound;
//    SimpleAudioEngine   *sharkDiedSound;
//    SimpleAudioEngine   *okButtonSound;
//    SimpleAudioEngine   *regularButtonSound;
//    SimpleAudioEngine   *denyButtonSound;
//    SimpleAudioEngine   *choseMenuSound;
//    SimpleAudioEngine   *startClickButtonSound;
//    SimpleAudioEngine   *endClickButtonSound;
    
    AudioEngine   *gameMusic;
    AudioEngine   *eatFishSound;
    AudioEngine   *earnStarSound;
    AudioEngine   *earnHeartSound;
    AudioEngine   *hitBarrelSound;
    AudioEngine   *hitMineSound;
    AudioEngine   *sharkDiedSound;
    AudioEngine   *okButtonSound;
    AudioEngine   *regularButtonSound;
    AudioEngine   *denyButtonSound;
    AudioEngine   *choseMenuSound;
    AudioEngine   *choseMenuSoundStart;
    AudioEngine   *choseMenuSoundEnd;
    AudioEngine   *startClickButtonSound;
    AudioEngine   *endClickButtonSound;
    
    int           returnIdGameMusic;
    int           returnIdEatFishSound;
    int           returnIdEarnStarSound;
    int           returnIdEarnHeartSound;
    int           returnIdHitBarrelSound;
    int           returnIdHitMineSound;
    int           returnIdSharkDiedSound;
    int           returnIdOkButtonSound;
    int           returnIdRegularButtonSound;
    int           returnIdDenyButtonSound;
    int           returnIdChoseMenuSound;
    int           returnIdChoseMenuSoundStart;
    int           returnIdChoseMenuSoundEnd;
    int           returnIdStartClickButtonSound;
    int           returnIdEndClickButtonSound;
    
    bool          isGameMusicIsRunning = false;
    
    AudioProfile     *audioProfileTest;
    
    void setTemporaryLevels();
    void saveData();
    
    MusicData();
    virtual ~MusicData();
    
public:

    
    static MusicData    *getMusicData();

    void initStats();
    
    void preloadGameMusic();
    void playGameMusic();
    void pauseGameMusic();
    void resumeGameMusic();
    void stopGameMusic();
    void unloadGameMusic();
    
    float getTemporaryMusicLevel();
    void setGameMusicLevel( float data );
    
    void playEatFishSound();
    void playEarnStarSound();
    void playEarnHeartSound();
    void playHitBarrelSound();
    void playHitMineSound();
    void playSharkDiedSound();
    void playOkButtonSound();
    void playRegularButtonSound();
    void playDenyButtonSound();
    void playChoseMenuSound();
    void playChoseMenuSoundStart();
    void playChoseMenuSoundEnd();
    void playButtonStartClickSound();
    void playButtonEndClickSound();
    
    bool returnIsGameMusicIsRunning();
    
    void preloadAllEffects();
    void unloadAllEffects();
    float getTemporaryEffectsLevel();
    void setGameEffectsLevel( float data );
    
    void saveMusicLevel( float data );
    void saveEffectsLevel( float data );
    
};

#endif /* MusicData_hpp */
