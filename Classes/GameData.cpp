    //
    //  GameData.cpp
    //  TestGame-mobile
    //
    //  Created by Madji on 18.07.19.
    //  CHANGED

    #include "GameData.hpp"

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
        setMusicVolumeLevel(0.0f);
        setSoundEffectsVolumeLevel(0.0f);
        printf("musicVolumeLevel with address %p and value %f \n", this->musicVolumeLevel, this->musicVolumeLevel);
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
        return currentLevel;
    }

    /*
        Set current level
    */
    void GameData::setCurrentLevel( int levelNum )
    {
        DEBUG_INFO;
        printf("number = %d\n", levelNum);
        currentLevel = levelNum;
        printf("currentLevel addrees %p and value %d\n", currentLevel, currentLevel);
    }

    /*
        Return which is MAX played level number.
        Needed for SelectLevel menu to show as unlocked levels.
     */
    int GameData::getLevelsPlayed()
    {
        return levelsPlayed;
    }

    /*
        Update MAX played level number
     */
    void GameData::setLevelsPlayed( int levelNum )
    {
         levelsPlayed = levelNum;
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
        maxLevel = levels;
    }

    /*

     */
    int GameData::getLastLevelNumber()
    {
        return maxLevel;
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
        numberOfLeftUpperLevel = number;
    //    printf("number to pass = %d\n", number);
    //    numberOfLeftUpperLevel = number;
//        writeDataToUserData();
        printf("numberOfLeftUpperLevel after set = %d\n", numberOfLeftUpperLevel);
    }

    /*
        Return grid[0][0] levels number (see GameData::setNumberOfLeftUpperLevel)
     */
    int GameData::getNumberOfLeftUpperLevel()
    {
        DEBUG_INFO;
        printf("numberOfLeftUpperLevel = %d\n", numberOfLeftUpperLevel);
        return numberOfLeftUpperLevel;
    }

    // SHARK stuffs

    int GameData::getCurrentSharkLives()
    {
        return currentSharkLives;
    }

    void GameData::setCurrentSharkLives( int lives )
    {
        currentSharkLives = lives;
    }

    void GameData::decreaseSharkLives()
    {
        currentSharkLives -= 1;
    }

    void GameData::increaseSharkLives()
    {
        currentSharkLives += 1;
    }

    int GameData::getDefaultSharkLives()
    {
        return defaultSharkLives;
    }


    // FISH stuffs

    int GameData::getFishCounter()
    {
        return fishCounter;
    }

    void GameData::setFishCounter( int fishes )
    {
        fishCounter = fishes;
    }

    void GameData::increaseFishCounter()
    {
    //    printf("GD 160 fishCounter before %d\n", fishCounter);
        fishCounter++;
    //    printf("GD 160 fishCounter after %d\n", fishCounter);
    }

    void GameData::resetFishCounterToZero()
    {
        setFishCounter( 0 );
    }

    // STARS stuffs

    void  GameData::resetStarsCounter()
    {
        setStarsCounter( 0 );
    }

    int GameData::getStarsCounter()
    {
        return starsCounter;
    }

    void GameData::setStarsCounter( int stars )
    {
        starsCounter = stars;
    }

    void GameData::calculateStars()
    {
        if ( getScoreCounter() >= pointsForThirdStar ){

            setStarsCounter( 3 );

        } else if ( getScoreCounter() >= pointsForSecondStar ){

            setStarsCounter( 2 );

        } else if ( getScoreCounter() >= pointsForFirstStar ){

            setStarsCounter( 1 );

        } else {

            setStarsCounter( 0 );
        }
    }

    // SCORE stuffs
    
    void GameData::setScoreCounter(int value)
    {
        scoreCounter = value;
    }

    int GameData::getScoreCounter()
    {
        return scoreCounter;
    }

    void GameData::setScoreCounterToZero()
    {
        scoreCounter = 0;
    }

    void GameData::increaseScore( int score )
    {
        scoreCounter += score;
        calculateStars();
    }

    // TIME stuffs


    /*
        Get level time for current level from LevelsData and set it to the display
     */
    void GameData::setCountdownTimerCounter( int levelNum )
    {
        DEBUG_INFO;
        countdownTimeCounter = levelData[levelNum].level[0].passLevelTime;
        countdownTimerCounterDefaultSec = countdownTimeCounter % 60;
        countdownTimerCounterDefaultMin = ( countdownTimeCounter / 60 ) % 60;
        
        log("countdownTimeCounter %d\n", countdownTimeCounter);
    }
    
    void GameData::setTimerCounter(int value)
    {
        DEBUG_INFO;
        timerCounter = value;
        timerSeconds = value;
        timerMinutes = value;
        log("timerCounter %d\n", getTimerCounter());
    }

    int GameData::getTimerCounter()
    {
        DEBUG_INFO;
//        log("countdownTimeCounter %d\n", countdownTimeCounter);
//        log("timeCounter %d\n", (timerCounter - countdownTimeCounter));
        return timerCounter;
//        return 0;
    }

    void GameData::setTimerCounterToInitValue()
    {
        DEBUG_INFO;
    //    countdownTimeCounter = levelData[getCurrentLevelNumber()].level[0].passLevelTime;
        timerSeconds = countdownTimeCounter % 60;
        timerMinutes = ( countdownTimeCounter / 60 ) % 60;

    }

    void GameData::setTimerCounterToZero()
    {
        DEBUG_INFO;
        setTimerCounter(0);
        timerSeconds = 0;
        timerMinutes = 0;
    }

    void GameData::decreaseTimerCounter()
    {
        calculateTimeForText( countdownTimeCounter-- );
    }

    void GameData::increaseTimerCounter()
    {

        calculateTimeForText( timerCounter++ );
    }

    void GameData::calculateTimeForText( int time )
    {
        timerSeconds = time % 60;
        timerMinutes = ( time / 60 ) % 60;
    }

    int GameData::getTimerMinutes()
    {
        return ((countdownTimeCounter / 60 ) % 60);
    }

    int GameData::getTimerSeconds()
    {
        return timerSeconds = (countdownTimeCounter % 60);
    }

    void GameData::setDefaultSharkLives( int lives )
    {
        defaultSharkLives = lives;
    }

    /* Game Settigns */
    void GameData::setMusicVolumeLevel(float level)
    {
        DEBUG_INFO;
        musicVolumeLevel = level;
        printf("musicVolumeLevel with address %p and value %f \n", musicVolumeLevel, musicVolumeLevel);
        this->musicVolumeLevel = level;
        printf("musicVolumeLevel with address %p and value %f \n", this->musicVolumeLevel, this->musicVolumeLevel);
        _gameData->musicVolumeLevel = level;
        printf("musicVolumeLevel with address %p and value %f \n", _gameData->musicVolumeLevel, _gameData->musicVolumeLevel);
        
    }

    float GameData::getMusicVolumeLevel()
    {
        DEBUG_INFO;
        printf("_gameData address %p\n", _gameData);
        printf("musicVolumeLevel with address %p and value %f \n", this->musicVolumeLevel, this->musicVolumeLevel);
        return musicVolumeLevel;
    }

    void GameData::setSoundEffectsVolumeLevel(float level)
    {
        DEBUG_INFO;
        soundEffectsVolumeLevel = level;
    }

    float GameData::getSoundEffectsVolumeLevel()
    {
        DEBUG_INFO;
        return soundEffectsVolumeLevel;
    }

    // USER stuffs

    bool GameData::getUserRegisterStatus()
    {
        return isUserRegister;
    }

    void GameData::setUserRegisterStatus( bool status )
    {
        isUserRegister = status;
    }

    void GameData::changeUserRegisterStatus( bool newStatus )
    {
        setUserRegisterStatus( newStatus );
    }

    void GameData::setUsername( std::string name )
    {
        username = name;
    }

    std::string GameData::getUsername()
    {
        return username;
    }

    void GameData::changeUsername( std::string newName )
    {
        setUsername( newName );
    }

    // ADDITIONAL SHARK LIVES stuff

    void GameData::setFirstLifeLoseTimer( long time)
    {
        timeFirstLifeLose = time;
    }
    void GameData::setSecondLifeLoseTimer( long time)
    {
        timeSecondLifeLose = time;
    }
    void GameData::setThirdLifeLoseTimer( long time)
    {
        timeThirdLifeLose = time;
    }
    void GameData::setFourthLifeLoseTimer( long time)
    {
        timeFourthLifeLose = time;
    }
    void GameData::setFifthLifeLoseTimer( long time)
    {
        timeFifthLifeLose = time;
    }

    long GameData::getFirstLifeLoseTimer()
    {
        return timeFirstLifeLose;
    }
    long GameData::getSecondLifeLoseTimer()
    {
        return timeSecondLifeLose;
    }
    long GameData::getThirdLifeLoseTimer()
    {
        return timeThirdLifeLose;
    }
    long GameData::getFourthLifeLoseTimer()
    {
        return timeFourthLifeLose;
    }
    long GameData::getFifthLifeLoseTimer()
    {
        return timeFifthLifeLose;
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
