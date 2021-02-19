    //
    //  GameData.cpp
    //  TestGame-mobile
    //
    //  Created by Madji on 18.07.19.
    //  CHANGED

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
    return userData->getDataStruct()->oneLevelData[levelNumber].ld_stars;
}

/*
    getter for current level
 */
int GameData::getCurrentLevelNumber()
{
    return _gameData->currentLevel;
}

/*
    setter for current level
 */
void GameData::setCurrentLevel( int levelNum )
{
    _gameData->currentLevel = levelNum;
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
    Pass levels counter
 */
void GameData::increaseLevelsPlayed( int levelNum )
{
    if ( getLevelsPlayed() < levelNum )
    {
        setLevelsPlayed( levelNum );
    }
}

/*
    That is used to unlock NEXT level when current level is pass successfuly
 */
void GameData::unlockLevel(int number )
{
    userData->unlockLevel(number);
}

/*
    Set last played level from user
 */
void GameData::setLastLevelNumber( int levels )
{
    _gameData->maxLevel = levels;
}

/*
    For future use
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
    _gameData->numberOfLeftUpperLevel = number;
}

/*
    Return grid[0][0] levels number (see GameData::setNumberOfLeftUpperLevel)
 */
int GameData::getNumberOfLeftUpperLevel()
{
    return _gameData->numberOfLeftUpperLevel;
}

    // SHARK stuffs

/*
    getter for current shark lives
 */
int GameData::getCurrentSharkLives()
{
    return _gameData->currentSharkLives;
}

/*
    setter for current shark lives
 */
void GameData::setCurrentSharkLives( int lives )
{
    _gameData->currentSharkLives = lives;
}

/*
    when user is lose shark lives
 */
void GameData::decreaseSharkLives()
{
    _gameData->currentSharkLives -= 1;
}

/*
    when time for return shark is pass
 */
void GameData::increaseSharkLives()
{
    _gameData->currentSharkLives += 1;
}

/*
    return default shark lives ( currently SHARK_ADDITIONAL_LIFE_COUNT )
 */
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
/*
    according to earned points and fixed points for one, two or three stars
    are calculated earned stars
 */
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
    _gameData->timerCounter = value;
}

int GameData::getTimerCounter()
{
    return _gameData->timerCounter;
}

/*
    For future use
 
    Each level has fixed points that the player must reach to pass the level
    But is not used for current version
 */
void GameData::setTimerCounterToInitValue()
{
    setTimerCounter( levelData[_gameData->getCurrentLevelNumber()].level->passLevelTime );
    _gameData->timerSeconds = _gameData->countdownTimeCounter % 60;
    _gameData->timerMinutes = ( _gameData->countdownTimeCounter / 60 ) % 60;
}

/*
    Clear time counter
 */
void GameData::setTimerCounterToZero()
{
    setTimerCounter(0);
    _gameData->timerSeconds = 0;
    _gameData->timerMinutes = 0;
}

/*
    Depending on the way you play, the time can be decreasing or increasing
 */
void GameData::decreaseTimerCounter()
{
    calculateTimeForText( _gameData->countdownTimeCounter-- );
}

/*
    Depending on the way you play, the time can be decreasing or increasing
 */
void GameData::increaseTimerCounter()
{
    
    calculateTimeForText( _gameData->timerCounter++ );
}

/*
    Convert time to seconds and minutes
 */
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
    _gameData->musicVolumeLevel = level;
}

float GameData::getMusicVolumeLevel()
{
    return _gameData->musicVolumeLevel;
}

void GameData::setSoundEffectsVolumeLevel(float level)
{
    _gameData->soundEffectsVolumeLevel = level;
}

float GameData::getSoundEffectsVolumeLevel()
{
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

/*
    The following methods are for set timestamp when player is lose a shark life
 */
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

/*
    Get data from file
 */
void GameData::getDataFromUserData()
{
    auto dataStruct = userData->getDataStruct();
    
    setDefaultSharkLives( dataStruct->ds_defaultSharkLives );
    setCurrentLevel( dataStruct->ds_currentLevel );
    
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
    setSoundEffectsVolumeLevel( dataStruct->ds_soundEffectsVolumeLevel );
}

/*
    Save data to file
 */
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
