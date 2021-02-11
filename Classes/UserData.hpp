//
//  UserData.hpp
//  TestGame-mobile
//
//  Created by Madji on 11.06.19.
//

#ifndef UserData_hpp
#define UserData_hpp

#pragma once

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
#include "GameData.hpp"
#include "Definitions.hpp"

class GameData;

using namespace cocos2d;

struct levelsData
{       
    bool                ld_isUnlocked; 
    
    int                 ld_levelNumber;
    int                 ld_stars;
    int                 ld_fishEaten;
    int                 ld_score;
    
    int                 ld_playTime;
};

struct dataStruct
{
    levelsData          oneLevelData[ALL_LEVELS];
    
    char                ds_username[20];
    int                 ds_defaultSharkLives;
    int                 ds_currentSharkLives; /* This number is used to logic for shark lives loses */
    int                 ds_levelsPlayed;    /* Needed to show max unlocked level into SelectLevelScene levels grid */
    int                 ds_currentLevel;
    int                 ds_numberOfLeftUpperLevel; /* This number is used to show last seen grid with levels in SelectLevelScene */
    int                 ds_maxLevel;
    
    float               ds_soundEffectsVolumeLevel;
    float               ds_musicVolumeLevel;
    long                ds_lastSaveTime; /* This time is used to calculate how much time passed since last game and if needed to return shark lives  */
    
    bool                ds_isUserRegister;
    
    /* This time records are needed to caclulate when to return shark lives */
    long                ds_timeFirstLifeLose;
    long                ds_timeSecondLifeLose;
    long                ds_timeThirdLifeLose;
    long                ds_timeFourthLifeLose;
    long                ds_timeFifthLifeLose;
    
};

class UserData
{
    
private:
    
    time_t now;
    
    static UserData     *_userData;
    dataStruct          _dataStruct;
    GameData            *_gameData;
    
    long                currentTimeInSeconds;
    long                getCurrentTimeInSeconds();
    int                 saveDataToFile();
    
    
public:
    
    UserData();
    virtual ~UserData();
    
    static  UserData    *getInstance();
    static  UserData    *getUserData();
    
    void                initStats();
    dataStruct          *getDataStruct();
    int                 loadDataFromFile();
    void                setUsername( std::string data );
    void                printData();
//    void                saveUserData();
    void                saveUserData();
};


#endif /* UserData_hpp */
