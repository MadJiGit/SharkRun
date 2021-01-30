//
//  GameData.cpp
//  TestGame-mobile
//
//  Created by Madji on 18.07.19.
//

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
    this->timeCounter = 0;
    this->timerMinutes = 0;
    this->timerSeconds = 0;
    this->scoreCounter = 0;
    this->starsCounter = 0;
    this->fishCounter = 0;
    
    _userData = UserData::getUserData();
    _dataStruct = _userData->getDataStruct();
    
    getUserData();
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

void GameData::setCountdownTimerCounter( int levelNum ){
    this->countdownTimeCounter = levelData[levelNum].level[0].passLevelTime;
    this->countdownTimerCounterDefaultSec = this->countdownTimeCounter % 60;
    this->countdownTimerCounterDefaultMin = ( this->countdownTimeCounter / 60 ) % 60;
}

int GameData::getToPassLevelPoints( int levelNumber )
{
    return levelData[levelNumber].level[0].passLevelPoints;
}

int GameData::getEarnedStarsFromDB( int levelNumber )
{
//    printf("GD 80 try to get _dataStruct->oneLevelData[levelNumber].ld_stars\n");
//    printf("GD 81 print level number %d\n", levelNumber);
    return _dataStruct->oneLevelData[levelNumber].ld_stars;
}

int GameData::getCurrentLevelNumber()
{
    return this->currentLevel;
}

void GameData::setCurrentLevel( int levelNum )
{
    this->currentLevel = levelNum;
}

int GameData::getLevelsPlayed()
{
    return this->levelsPlayed;
}

void GameData::setLevelsPlayed( int levelNum )
{
     this->levelsPlayed = levelNum;
}

void GameData::increaseLevelsPlayed( int levelNum )
{
    if ( getLevelsPlayed() < levelNum )
    {
        setLevelsPlayed( levelNum );
    }
}

void GameData::setLastLevelNumber( int levels )
{
    this->maxLevel = levels;
}

int GameData::getLastLevelNumber()
{
    return this->maxLevel;
}

void GameData::setNumberOfLeftUpperLevel( int number )
{
    this->numberOfLeftUpperLevel = number;
}

int GameData::getNumberOfLeftUpperLevel()
{
    return this->numberOfLeftUpperLevel;
}

// SHARK stuffs

int GameData::getCurrentSharkLives()
{
    return this->currentSharkLives;
}

void GameData::setCurrentSharkLives( int lives )
{
    this->currentSharkLives = lives;
}

void GameData::decreaseSharkLives()
{
    this->currentSharkLives -= 1;
}

void GameData::increaseSharkLives()
{
    this->currentSharkLives += 1;
}

int GameData::getDefaultSharkLives()
{
    return this->defaultSharkLives;
}


// FISH stuffs

int GameData::getFishCounter()
{
    return this->fishCounter;
}

void GameData::setFishCounter( int fishes )
{
    this->fishCounter = fishes;
}

void GameData::increaseFishCounter()
{
//    printf("GD 160 fishCounter before %d\n", this->fishCounter);
    this->fishCounter++;
//    printf("GD 160 fishCounter after %d\n", this->fishCounter);
}

void GameData::resetFishCounterToZero()
{
    this->setFishCounter( 0 );
}

// STARS stuffs

void  GameData::resetStarsCounter()
{
    this->setStarsCounter( 0 );
}

int GameData::getStarsCounter()
{
    return this->starsCounter;
}

void GameData::setStarsCounter( int stars )
{
    this->starsCounter = stars;
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
    return this->scoreCounter;
}

void GameData::setScoreCounterToZero()
{
    this->scoreCounter = 0;
}

void GameData::increaseScore( int score )
{
//    printf("GD 227 scoreCounter + score %d\n", score);
    this->scoreCounter += score;
    calculateStars();
}

// TIME stuffs

int GameData::getTimerCounter()
{
    return this->timeCounter;
}

void GameData::setTimerCounterToInitValue()
{
//    this->countdownTimeCounter = levelData[getCurrentLevelNumber()].level[0].passLevelTime;
    timerSeconds = this->countdownTimeCounter % 60;
    timerMinutes = ( this->countdownTimeCounter / 60 ) % 60;
    
}

void GameData::setTimerCounterToZero()
{
    this->timeCounter = 0;
    this->timerSeconds = 0;
    this->timerMinutes = 0;
}

void GameData::decreaseTimerCounter()
{
//    this->countdownTimeCounter--;
    calculateTimeForText( this->countdownTimeCounter-- );
}

void GameData::increaseTimerCounter()
{
    
    calculateTimeForText( this->timeCounter++ );
}

void GameData::calculateTimeForText( int time )
{
    timerSeconds = time % 60;
    timerMinutes = ( time / 60 ) % 60;
}

int GameData::getTimerMinutes()
{
//    return this->timerMinutes;
    return ((this->countdownTimeCounter / 60 ) % 60);
}

int GameData::getTimerSeconds()
{
//    return this->timerSeconds;
    return timerSeconds = (this->countdownTimeCounter % 60);
}

void GameData::setDefaultSharkLives( int lives )
{
//    log("GD 243 def shark lives %d", lives);
    this->defaultSharkLives = lives;
}

// USER stuffs

bool GameData::getUserRegisterStatus()
{
    return this->isUserRegister;
}

void GameData::setUserRegister( bool status )
{
    this->isUserRegister = status;
}

void GameData::changeUserRegisterStatus( bool newStatus )
{
    setUserRegister( newStatus );
}

void GameData::setUsername( std::string name )
{
    this->username = name;
}

std::string GameData::getUsername()
{
    return this->username;
}

void GameData::changeUsername( std::string newName )
{
    setUsername( newName );
}

// ADDITIONAL SHARK LIVES stuff

void GameData::setFirstLifeLoseTimer( long time)
{
    this->timeFirstLifeLose = time;
}
void GameData::setSecondLifeLoseTimer( long time)
{
    this->timeSecondLifeLose = time;
}
void GameData::setThirdLifeLoseTimer( long time)
{
    this->timeThirdLifeLose = time;
}
void GameData::setFourthLifeLoseTimer( long time)
{
    this->timeFourthLifeLose = time;
}
void GameData::setFifthLifeLoseTimer( long time)
{
    this->timeFifthLifeLose = time;
}

long GameData::getFirstLifeLoseTimer()
{
    return this->timeFirstLifeLose;
}
long GameData::getSecondLifeLoseTimer()
{
    return this->timeSecondLifeLose;
}
long GameData::getThirdLifeLoseTimer()
{
    return this->timeThirdLifeLose;
}
long GameData::getFourthLifeLoseTimer()
{
    return this->timeFourthLifeLose;
}
long GameData::getFifthLifeLoseTimer()
{
    return this->timeFifthLifeLose;
}

void GameData::getUserData()
{
    auto tempUserData = _userData->getUserData()->getDataStruct();
    
    setCurrentLevel( tempUserData->ds_currentLevel );
    setCurrentSharkLives( tempUserData->ds_currentSharkLives );
//    log("GD 329 default shark lives %d", tempUserData->ds_defaultSharkLives );
    setDefaultSharkLives( tempUserData->ds_defaultSharkLives );
    setUsername( tempUserData->ds_username );
    setUserRegister( tempUserData->ds_isUserRegister );
    setFirstLifeLoseTimer( tempUserData->ds_timeFirstLifeLose );
    setSecondLifeLoseTimer( tempUserData->ds_timeSecondLifeLose );
    setThirdLifeLoseTimer( tempUserData->ds_timeThirdLifeLose );
    setFourthLifeLoseTimer( tempUserData->ds_timeFourthLifeLose );
    setFifthLifeLoseTimer( tempUserData->ds_timeFifthLifeLose );
    setLastLevelNumber( tempUserData->ds_maxLevel );
    
    pointsForFirstStar = levelData[currentLevel].level[0].oneStarPoint;
    pointsForSecondStar = levelData[currentLevel].level[0].twoStarsPoint;
    pointsForThirdStar = levelData[currentLevel].level[0].threeStarsPoint;
    passLevelPoints = levelData[currentLevel].level[0].passLevelPoints;

#ifdef DEBUGING
    log("GD 342 points FS %d points SS %d points TS %d", pointsForFirstStar, pointsForSecondStar, pointsForThirdStar );
#endif
}

void GameData::saveUserData()
{
    auto gameTimer = getTimerCounter();
    auto gameScore = getScoreCounter();
    auto earnedStars = getStarsCounter();
    
#ifdef DEBUGING
    printf("GD 373 earnedStars %d\n", earnedStars);
#endif
    
    auto fishEaten = getFishCounter();
    
#ifdef DEBUGING
    printf("GD 376 earnedStars %d\n", earnedStars);
#endif
    
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
