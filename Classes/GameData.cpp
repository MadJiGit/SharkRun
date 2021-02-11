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

    GameData *GameData::getInstance()
    {
        if (!_gameData)
        {
            return nullptr;
        }
        else
        {
            return _gameData;
        }
    }

    void GameData::initStats()
    {
        timeCounter = 0;
        timerMinutes = 0;
        timerSeconds = 0;
        scoreCounter = 0;
        starsCounter = 0;
        fishCounter = 0;

        _userData = UserData::getUserData();

        getDataFromUserData();
        setCountdownTimerCounter( getCurrentLevelNumber() );
    }

    GameData *GameData::getGameData()
    {
        if ( _gameData == nullptr )
        {
            _gameData = new GameData();

            _gameData->initStats();
        }

        return _gameData;
    }

    /*
        Get level time for current level from LevelsData and set it to the display
     */
    void GameData::setCountdownTimerCounter( int levelNum ){
        countdownTimeCounter = levelData[levelNum].level[0].passLevelTime;
        countdownTimerCounterDefaultSec = countdownTimeCounter % 60;
        countdownTimerCounterDefaultMin = ( countdownTimeCounter / 60 ) % 60;
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
        return _userData->getDataStruct()->oneLevelData[levelNumber].ld_stars;
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
        DEBUG_INFO;
        printf("currentLevel = %d\n", currentLevel);
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
        writeDataToUserData();
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
    //    printf("GD 227 scoreCounter + score %d\n", score);
        scoreCounter += score;
        calculateStars();
    }

    // TIME stuffs

    int GameData::getTimerCounter()
    {
        return timeCounter;
    }

    void GameData::setTimerCounterToInitValue()
    {
    //    countdownTimeCounter = levelData[getCurrentLevelNumber()].level[0].passLevelTime;
        timerSeconds = countdownTimeCounter % 60;
        timerMinutes = ( countdownTimeCounter / 60 ) % 60;

    }

    void GameData::setTimerCounterToZero()
    {
        timeCounter = 0;
        timerSeconds = 0;
        timerMinutes = 0;
    }

    void GameData::decreaseTimerCounter()
    {
    //    countdownTimeCounter--;
        calculateTimeForText( countdownTimeCounter-- );
    }

    void GameData::increaseTimerCounter()
    {

        calculateTimeForText( timeCounter++ );
    }

    void GameData::calculateTimeForText( int time )
    {
        timerSeconds = time % 60;
        timerMinutes = ( time / 60 ) % 60;
    }

    int GameData::getTimerMinutes()
    {
    //    return timerMinutes;
        return ((countdownTimeCounter / 60 ) % 60);
    }

    int GameData::getTimerSeconds()
    {
    //    return timerSeconds;
        return timerSeconds = (countdownTimeCounter % 60);
    }

    void GameData::setDefaultSharkLives( int lives )
    {
    //    log("GD 243 def shark lives %d", lives);
        defaultSharkLives = lives;
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
        auto tempUserData = _userData->getUserData()->getDataStruct();

        setUsername( tempUserData->ds_username );
        setDefaultSharkLives( tempUserData->ds_defaultSharkLives );

        DEBUG_INFO;
        log("tempUserData->ds_currentLevel %d", tempUserData->ds_currentLevel);
        log("currentLevel befor set %d", currentLevel);
        setCurrentLevel( tempUserData->ds_currentLevel );
        log("currentLevel after set %d", currentLevel);

        setNumberOfLeftUpperLevel( tempUserData->ds_numberOfLeftUpperLevel );
        setLastLevelNumber( tempUserData->ds_maxLevel );
        setUserRegisterStatus( tempUserData->ds_isUserRegister );

        setFirstLifeLoseTimer( tempUserData->ds_timeFirstLifeLose );
        setSecondLifeLoseTimer( tempUserData->ds_timeSecondLifeLose );
        setThirdLifeLoseTimer( tempUserData->ds_timeThirdLifeLose );
        setFourthLifeLoseTimer( tempUserData->ds_timeFourthLifeLose );
        setFifthLifeLoseTimer( tempUserData->ds_timeFifthLifeLose );

        pointsForFirstStar = levelData[currentLevel].level[0].oneStarPoint;
        pointsForSecondStar = levelData[currentLevel].level[0].twoStarsPoint;
        pointsForThirdStar = levelData[currentLevel].level[0].threeStarsPoint;
        passLevelPoints = levelData[currentLevel].level[0].passLevelPoints;

    }

    void GameData::writeDataToUserData()
    {
        /*
        auto gameTimer = getTimerCounter();
        auto gameScore = getScoreCounter();
        auto earnedStars = getStarsCounter();

        DEBUG_INFO;
        printf("currentLevel = %d\n", currentLevel);
        printf("leftUpperLevel = %d\n", numberOfLeftUpperLevel);

        auto fishEaten = getFishCounter();
        auto _dataStruct = _userData->getDataStruct();

        if (_dataStruct->oneLevelData[currentLevel].ld_stars < earnedStars )
        {
            _dataStruct->oneLevelData[currentLevel].ld_stars = earnedStars;
            _dataStruct->oneLevelData[currentLevel].ld_score = gameScore;
            _dataStruct->oneLevelData[currentLevel].ld_playTime = gameTimer;
            _dataStruct->oneLevelData[currentLevel].ld_fishEaten = fishEaten;
        }
        else if ( _dataStruct->oneLevelData[currentLevel].ld_stars == earnedStars )
        {
            if ( _dataStruct->oneLevelData[currentLevel].ld_score < gameScore )
            {
                _dataStruct->oneLevelData[currentLevel].ld_score = gameScore;
                _dataStruct->oneLevelData[currentLevel].ld_playTime = gameTimer;
                _dataStruct->oneLevelData[currentLevel].ld_fishEaten = fishEaten;

            }
            else if ( _dataStruct->oneLevelData[currentLevel].ld_score == gameScore )
            {
                if ( _dataStruct->oneLevelData[currentLevel].ld_playTime > gameTimer )
                {
                    _dataStruct->oneLevelData[currentLevel].ld_playTime = gameTimer;
                    _dataStruct->oneLevelData[currentLevel].ld_fishEaten = fishEaten;
                }
                else if ( _dataStruct->oneLevelData[currentLevel].ld_playTime == gameTimer )
                {
                    if ( _dataStruct->oneLevelData[currentLevel].ld_fishEaten < fishEaten ) {
                        _dataStruct->oneLevelData[currentLevel].ld_fishEaten = fishEaten;
                    }
                }
            }
        }
    //
    //    log( "GD 386 GameData save data earned stars %d %d", earnedStars, _dataStruct->oneLevelData[currentLevel].ld_stars );
    //    log("GD row 362 GameData save data first %lu", getFirstLifeLoseTimer());
    //    log("GD row 363 GameData save data second %lu", getSecondLifeLoseTimer());

        _dataStruct->oneLevelData[currentLevel].ld_isUnlocked = true;
        _dataStruct->ds_levelsPlayed = getLevelsPlayed();
        _userData->setUsername( username );
        _dataStruct->ds_isUserRegister = getUserRegisterStatus();
    //    _dataStruct->ds_defaultSharkLives
        _dataStruct->ds_currentSharkLives = getCurrentSharkLives();
        _dataStruct->ds_currentLevel = getCurrentLevelNumber();
        _dataStruct->ds_numberOfLeftUpperLevel = getNumberOfLeftUpperLevel();
        _dataStruct->ds_timeFirstLifeLose = getFirstLifeLoseTimer();
        _dataStruct->ds_timeSecondLifeLose = getSecondLifeLoseTimer();
        _dataStruct->ds_timeThirdLifeLose = getThirdLifeLoseTimer();
        _dataStruct->ds_timeFourthLifeLose = getFourthLifeLoseTimer();
        _dataStruct->ds_timeFifthLifeLose = getFifthLifeLoseTimer();
        */
        _userData->saveUserData();
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
