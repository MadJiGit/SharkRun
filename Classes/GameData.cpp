    //
    //  GameData.cpp
    //  TestGame-mobile
    //
    //  Created by Madji on 18.07.19.
    //  CHANGED

    #pragma once
    #include "GameData.hpp"

#include "Levels.hpp"

    GameData   *GameData::_gameData;

    GameData::GameData()
    {

    }

    GameData::~GameData()
    {

    }

    void GameData::initStats()
    {
        DEBUG_INFO
        loadUserData();
        setInitialGamePlayValues();
    }

    GameData *GameData::getGameData()
    {
        DEBUG_INFO
        if ( _gameData == nullptr )
        {
            _gameData = new GameData();

            _gameData->initStats();
        }
        
        printf("_gameData address %p\n", _gameData);
        return _gameData;
    }

    LevelData GameData::getOneLevelDataByLevelNumber(int number)
    {
        return _gameData->userData->getOneLevelDataByLevelNumber(number);
    }

    void GameData::setInitialGamePlayValues()
    {
        DEBUG_INFO;
        setTimerCounter(0);
        setScoreCounter(0);
        setStarsCounter(0);
        setFishCounter(0);
        printf("musicVolumeLevel with address %p and value %f \n", _gameData->musicVolumeLevel, _gameData->musicVolumeLevel);
    }

    void GameData::loadUserData()
    {
        DEBUG_INFO;
        userData = UserData::getUserData();
        getDataFromUserData();
    }

    /*
        Load level points needed to pass the current level from Level Statistic
        When player hit points level is passed and player get 3 stars
     */
    int GameData::getToPassLevelPoints( int levelNumber )
    {
        return levelData[levelNumber].level[0].passLevelPoints;
    }

    /*
        Return earned stars, if there it is, for current level, to show them to display
     */
    int GameData::getEarnedStarsFromLevelsData( int levelNumber )
    {
    //    return _dataStruct->oneLevelData[levelNumber].ld_stars;
        return userData->getDataStruct()->oneLevelData[levelNumber].ld_stars;
    }

    /*
        Return current level
    */
    int GameData::getCurrentLevelNumber()
    {
        DEBUG_INFO;
        printf("currentLevel addrees %p and value %d\n", _gameData->currentLevel, _gameData->currentLevel);
        return _gameData->currentLevel;
    }

    /*
        Set current level
    */
    void GameData::setCurrentLevel( int levelNum )
    {
        DEBUG_INFO;
        printf("number = %d\n", levelNum);
        _gameData->currentLevel = levelNum;
        printf("currentLevel addrees %p and value %d\n", _gameData->currentLevel, _gameData->currentLevel);
    }

    /*
        Return which is MAX played level number.
        Needed for SelectLevel menu to show as unlocked levels.
     */
    int GameData::getLevelsPlayed()
    {
        return _gameData->levelsPlayed;
    }

    /*
        Update MAX played level number
     */
    void GameData::setLevelsPlayed( int levelNum )
    {
        _gameData->levelsPlayed = levelNum;
    }

    /*

     */
    void GameData::increaseLevelsPlayed( int levelNum )
    {
        if ( getLevelsPlayed() < levelNum )
        {
            setLevelsPlayed( levelNum );
        }
    }

    /*

     */
    void GameData::setLastLevelNumber( int levels )
    {
        _gameData->maxLevel = levels;
    }

    /*

     */
    int GameData::getLastLevelNumber()
    {
        return _gameData->maxLevel;
    }

    /*
      Get from LevelsData "numberOfLeftUpperLevel"
      This level number is needed for calculate SelectLevel menu's grid.
      The levels grid show 6 levels with some data and this method return
      level number for grid[0][0]
      */
    void GameData::setNumberOfLeftUpperLevel( int number )
    {
        DEBUG_INFO;
        printf("setNumberOfLeftUpperLevel = %d\n", number);
        _gameData->numberOfLeftUpperLevel = number;
    //    printf("number to pass = %d\n", number);
    //    numberOfLeftUpperLevel = number;
//        writeDataToUserData();
        printf("numberOfLeftUpperLevel after set = %d\n", _gameData->numberOfLeftUpperLevel);
    }

    /*
        Return grid[0][0] levels number (see GameData::setNumberOfLeftUpperLevel)
     */
    int GameData::getNumberOfLeftUpperLevel()
    {
        DEBUG_INFO;
        printf("numberOfLeftUpperLevel = %d\n", _gameData->numberOfLeftUpperLevel);
        return _gameData->numberOfLeftUpperLevel;
    }

    // SHARK stuffs

    int GameData::getCurrentSharkLives()
    {
        return _gameData->currentSharkLives;
    }

    void GameData::setCurrentSharkLives( int lives )
    {
        _gameData->currentSharkLives = lives;
    }

    void GameData::decreaseSharkLives()
    {
        _gameData->currentSharkLives -= 1;
    }

    void GameData::increaseSharkLives()
    {
        _gameData->currentSharkLives += 1;
    }

    int GameData::getDefaultSharkLives()
    {
        return _gameData->defaultSharkLives;
    }


    // FISH stuffs

    int GameData::getFishCounter()
    {
        return _gameData->fishCounter;
    }

    void GameData::setFishCounter( int fishes )
    {
        _gameData->fishCounter = fishes;
    }

    void GameData::increaseFishCounter()
    {
        _gameData->fishCounter++;
    }

    void GameData::resetFishCounterToZero()
    {
        _gameData->setFishCounter( 0 );
    }

    // STARS stuffs

    void  GameData::resetStarsCounter()
    {
        _gameData->setStarsCounter( 0 );
    }

    int GameData::getStarsCounter()
    {
        return _gameData->starsCounter;
    }

    void GameData::setStarsCounter( int stars )
    {
        _gameData->starsCounter = stars;
    }

    void GameData::calculateStars()
    {
        if ( getScoreCounter() >= _gameData->pointsForThirdStar ){

            setStarsCounter( 3 );

        } else if ( getScoreCounter() >= _gameData->pointsForSecondStar ){

            setStarsCounter( 2 );

        } else if ( getScoreCounter() >= _gameData->pointsForFirstStar ){

            setStarsCounter( 1 );

        } else {

            setStarsCounter( 0 );
        }
    }

    // SCORE stuffs
    
    void GameData::setScoreCounter(int value)
    {
        _gameData->scoreCounter = value;
    }

    int GameData::getScoreCounter()
    {
        return _gameData->scoreCounter;
    }

    void GameData::setScoreCounterToZero()
    {
        _gameData->scoreCounter = 0;
    }

    void GameData::increaseScore( int score )
    {
        _gameData->scoreCounter += score;
        calculateStars();
    }

    // TIME stuffs


    /*
        Get level time for current level from LevelsData and set it to the display
     */
    void GameData::setCountdownTimerCounter( int levelNum )
    {
        DEBUG_INFO;
        _gameData->countdownTimeCounter = levelData[levelNum].level[0].passLevelTime;
        _gameData->countdownTimerCounterDefaultSec = _gameData->countdownTimeCounter % 60;
        _gameData->countdownTimerCounterDefaultMin = ( _gameData->countdownTimeCounter / 60 ) % 60;
        
        log("countdownTimeCounter %d\n", _gameData->countdownTimeCounter);
    }
    
    void GameData::setTimerCounter(int value)
    {
        DEBUG_INFO;
        _gameData->timerCounter = value;
//        timerSeconds = value;
//        timerMinutes = value;
//        log("value %d\n", value);
//        log("timerCounter %d\n", this->timerCounter);
        log("timerCounter %d\n", getTimerCounter());
    }

    int GameData::getTimerCounter()
    {
        DEBUG_INFO;
        printf("gameData address %p\n", _gameData);
//        printf("timeerCounter address %p\n", timerCounter);
//        printf("timeerCounter value %d\n", timerCounter);

        return _gameData->timerCounter;
    }

    void GameData::setTimerCounterToInitValue()
    {
        DEBUG_INFO;
    //    countdownTimeCounter = levelData[getCurrentLevelNumber()].level[0].passLevelTime;
        
        setTimerCounter( levelData[_gameData->getCurrentLevelNumber()].level->passLevelTime );
        _gameData->timerSeconds = _gameData->countdownTimeCounter % 60;
        _gameData->timerMinutes = ( _gameData->countdownTimeCounter / 60 ) % 60;
        printf("timerSeconds value %d timerMinutes value %d\n", _gameData->timerSeconds, _gameData->timerMinutes);
    }

    void GameData::setTimerCounterToZero()
    {
        DEBUG_INFO;
        setTimerCounter(0);
        _gameData->timerSeconds = 0;
        _gameData->timerMinutes = 0;
    }

    void GameData::decreaseTimerCounter()
    {
        calculateTimeForText( _gameData->countdownTimeCounter-- );
    }

    void GameData::increaseTimerCounter()
    {

        calculateTimeForText( _gameData->timerCounter++ );
    }

    void GameData::calculateTimeForText( int time )
    {
        _gameData->timerSeconds = time % 60;
        _gameData->timerMinutes = ( time / 60 ) % 60;
    }

    int GameData::getTimerMinutes()
    {
        return ((_gameData->countdownTimeCounter / 60 ) % 60);
    }

    int GameData::getTimerSeconds()
    {
        return _gameData->timerSeconds = (_gameData->countdownTimeCounter % 60);
    }

    void GameData::setDefaultSharkLives( int lives )
    {
        _gameData->defaultSharkLives = lives;
    }

    /* Game Settigns */
    void GameData::setMusicVolumeLevel(float level)
    {
        DEBUG_INFO;
        printf("_gameData address %p\n", _gameData);
        _gameData->musicVolumeLevel = level;
        printf("musicVolumeLevel with address %p and value %f \n", _gameData->musicVolumeLevel, _gameData->musicVolumeLevel);
//        this->musicVolumeLevel = level;
//        printf("musicVolumeLevel with address %p and value %f \n", this->musicVolumeLevel, this->musicVolumeLevel);
//        _gameData->musicVolumeLevel = level;
//        printf("musicVolumeLevel with address %p and value %f \n", _gameData->musicVolumeLevel, _gameData->musicVolumeLevel);
        
    }

    float GameData::getMusicVolumeLevel()
    {
        DEBUG_INFO;
        printf("_gameData address %p\n", _gameData);
        printf("musicVolumeLevel with address %p and value %f \n", _gameData->musicVolumeLevel, _gameData->musicVolumeLevel);
        return _gameData->musicVolumeLevel;
    }

    void GameData::setSoundEffectsVolumeLevel(float level)
    {
        DEBUG_INFO;
        _gameData->soundEffectsVolumeLevel = level;
    }

    float GameData::getSoundEffectsVolumeLevel()
    {
        DEBUG_INFO;
        return _gameData->soundEffectsVolumeLevel;
    }

    // USER stuffs

    bool GameData::getUserRegisterStatus()
    {
        return _gameData->isUserRegister;
    }

    void GameData::setUserRegisterStatus( bool status )
    {
        _gameData->isUserRegister = status;
    }

    void GameData::changeUserRegisterStatus( bool newStatus )
    {
        setUserRegisterStatus( newStatus );
    }

    void GameData::setUsername( std::string name )
    {
        _gameData->username = name;
    }

    std::string GameData::getUsername()
    {
        return _gameData->username;
    }

    void GameData::changeUsername( std::string newName )
    {
        setUsername( newName );
    }

    // ADDITIONAL SHARK LIVES stuff

    void GameData::setFirstLifeLoseTimer( long time)
    {
        _gameData->timeFirstLifeLose = time;
    }
    void GameData::setSecondLifeLoseTimer( long time)
    {
        _gameData->timeSecondLifeLose = time;
    }
    void GameData::setThirdLifeLoseTimer( long time)
    {
        _gameData->timeThirdLifeLose = time;
    }
    void GameData::setFourthLifeLoseTimer( long time)
    {
        _gameData->timeFourthLifeLose = time;
    }
    void GameData::setFifthLifeLoseTimer( long time)
    {
        _gameData->timeFifthLifeLose = time;
    }

    long GameData::getFirstLifeLoseTimer()
    {
        return _gameData->timeFirstLifeLose;
    }
    long GameData::getSecondLifeLoseTimer()
    {
        return _gameData->timeSecondLifeLose;
    }
    long GameData::getThirdLifeLoseTimer()
    {
        return _gameData->timeThirdLifeLose;
    }
    long GameData::getFourthLifeLoseTimer()
    {
        return _gameData->timeFourthLifeLose;
    }
    long GameData::getFifthLifeLoseTimer()
    {
        return _gameData->timeFifthLifeLose;
    }

    void GameData::getDataFromUserData()
    {
        auto dataStruct = userData->getDataStruct();

        setDefaultSharkLives( dataStruct->ds_defaultSharkLives );

        DEBUG_INFO;
        log("dataStruct->ds_currentLevel %d", dataStruct->ds_currentLevel);
        log("currentLevel befor set %d", currentLevel);
        setCurrentLevel( dataStruct->ds_currentLevel );
        log("currentLevel after set %d", currentLevel);

        setNumberOfLeftUpperLevel( dataStruct->ds_numberOfLeftUpperLevel );
        log("dataStruct->ds_numberOfLeftUpperLevel %d", dataStruct->ds_numberOfLeftUpperLevel);
        setLastLevelNumber( dataStruct->ds_maxLevel );
        setUserRegisterStatus( dataStruct->ds_isUserRegister );

        setFirstLifeLoseTimer( dataStruct->ds_timeFirstLifeLose );
        setSecondLifeLoseTimer( dataStruct->ds_timeSecondLifeLose );
        setThirdLifeLoseTimer( dataStruct->ds_timeThirdLifeLose );
        setFourthLifeLoseTimer( dataStruct->ds_timeFourthLifeLose );
        setFifthLifeLoseTimer( dataStruct->ds_timeFifthLifeLose );

        pointsForFirstStar = levelData[currentLevel].level[0].oneStarPoint;
        pointsForSecondStar = levelData[currentLevel].level[0].twoStarsPoint;
        pointsForThirdStar = levelData[currentLevel].level[0].threeStarsPoint;
        passLevelPoints = levelData[currentLevel].level[0].passLevelPoints;
        
        setMusicVolumeLevel( dataStruct->ds_musicVolumeLevel );
        DEBUG_INFO;
        log("setMusicVolumeLevel( dataStruct->ds_musicVolumeLevel ) %f", dataStruct->ds_musicVolumeLevel);
        setSoundEffectsVolumeLevel( dataStruct->ds_soundEffectsVolumeLevel );
        log("setMusicVolumeLevel( dataStruct->ds_soundEffectsVolumeLevel ) %f", dataStruct->ds_soundEffectsVolumeLevel);
    }

    void GameData::writeDataToUserData()
    {
        DEBUG_INFO;
        userData->saveUserData();
    }

    long GameData::getTimeStampInSeconds()
    {
        return time(&now);
    }

     void GameData::printLongMax()
    {
    //    log( "GD row 383 print INT_MAX %d", INT_MAX );
    //    log( "GD row 384 print LONG_MAX %ld", LONG_MAX );
    //    log( "GD row 385 print LONG_MAX - MAX_TIME %ld", LONG_MAX - MAX_TIME );
    //    log( "GD row 386 print LONG_MAX - time&now %ld", LONG_MAX - getTimeStampInSeconds() );
    //    log( "GD row 387 print MAX_TIME - time&now %ld", MAX_TIME - getTimeStampInSeconds() );
    }
