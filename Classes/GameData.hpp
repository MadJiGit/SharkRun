//
//  GameData.hpp
//  TestGame-mobile
//
//  Created by Madji on 18.07.19.
//

#ifndef GameData_hpp
#define GameData_hpp

#pragma once
#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Definitions.hpp"
#include "UserData.hpp"
#include "SharkLives.hpp"

class UserData;
class SharkLives;
struct dataStruct;

using namespace cocos2d;

class GameData {
private:
    
    UserData            *_userData;
    dataStruct          *_dataStruct;
    
    static GameData     *_gameData;
    SharkLives          *sharkLives;
    
    time_t              now;
    long                getTimeStampInSeconds();
    
    int                 pointsForFirstStar, pointsForSecondStar, pointsForThirdStar;
    int                 passLevelPoints;
    int                 starsCounter, earnedStars;
    int                 scoreCounter;
    int                 fishCounter;
    int                 timeCounter;
    int                 countdownTimeCounter;
    int                 timerSeconds;
    int                 timerMinutes;
    int                 currentLevel;
    int                 numberOfLeftUpperLevel;
    int                 levelsPlayed;
    int                 maxLevel;
    int                 currentSharkLives;
    int                 defaultSharkLives;
    std::string         username;
    bool                isUserRegister;
    
    
    long                timeFirstLifeLose;
    long                timeSecondLifeLose;
    long                timeThirdLifeLose;
    long                timeFourthLifeLose;
    long                timeFifthLifeLose;
    
    void                calculateTimeForText( int time );
    
    void                setStarsCounter( int stars );
    void                calculateStars();
    
    void                getUserData();
    void                setUsername( std::string name );
    
    void                setLevelsPlayed( int levelNum );
    void                increaseLevelsPlayed( int levelNum );
    void                setDefaultSharkLives( int lives );
    void                setUserRegister( bool status );
    
    
public:
    
    GameData();
    virtual             ~GameData();
    
    static GameData     *getInstance();
    static GameData     *getGameData();
    
    void                initStats();
    
    void                setCurrentLevel( int levelNum );
    
    int                 getTimerCounter();
    int                 countdownTimerCounterDefaultSec;
    int                 countdownTimerCounterDefaultMin;
    void                setCountdownTimerCounter( int levelNum );
    void                setTimerCounterToZero();
    void                setTimerCounterToInitValue();
    void                increaseTimerCounter();
    void                decreaseTimerCounter();
    int                 getTimerMinutes();
    int                 getTimerSeconds();
    
    int                 getScoreCounter();
    void                setScoreCounterToZero();
    void                increaseScore( int score );
    
    void                setFishCounter( int fishes );
    void                increaseFishCounter();
    int                 getFishCounter();
    void                resetFishCounterToZero();
    
    int                 getStarsCounter();
    int                 getEarnedStarsFromDB( int levelNumber );
    int                 getToPassLevelPoints( int levelNumber );
    int                 getCurrentLevelNumber();
    int                 getLastLevelNumber();
    int                 getCurrentSharkLives();
    int                 getDefaultSharkLives();
    int                 getLevelsPlayed();
    int                 getNumberOfLeftUpperLevel();
    std::string         getUsername();
    void                decreaseSharkLives();
    void                increaseSharkLives();
    
    bool                getUserRegisterStatus();
    void                changeUsername( std::string newName );
    void                changeUserRegisterStatus( bool newStatus );
    
    void                setFirstLifeLoseTimer( long time);
    void                setSecondLifeLoseTimer( long time);
    void                setThirdLifeLoseTimer( long time);
    void                setFourthLifeLoseTimer( long time);
    void                setFifthLifeLoseTimer( long time);
    void                setCurrentSharkLives( int lives );
    void                setLastLevelNumber( int levels );
    void                setNumberOfLeftUpperLevel( int number );
    void                resetStarsCounter();
    
    long                getFirstLifeLoseTimer();
    long                getSecondLifeLoseTimer();
    long                getThirdLifeLoseTimer();
    long                getFourthLifeLoseTimer();
    long                getFifthLifeLoseTimer();
    
    bool                checkLevelIsUnlocked( int number );
    GameData            loadlevelStatsByNumber( int number );
    
    void                saveUserData();
    
    void                printLongMax();
    
};


#endif /* GameData_hpp */
