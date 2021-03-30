//
//  SharkLives.cpp
//  TestGame-mobile
//
//  Created by Madji on 18.07.19.
//

#include "SharkLives.hpp"

SharkLives *SharkLives::createSharkLives( UI *ui )
{
    SharkLives *sprite;
    sprite = new SharkLives;
    
    if ( sprite )
    {
        sprite->setUI( ui );
        sprite->init();
        ui->addChild( sprite );
        return sprite;
    }
    
    CC_SAFE_DELETE( sprite );
    
    return sprite = nullptr;
}

void SharkLives::setUI( UI *ui )
{
    this->ui = ui;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainScene.cpp\n");
}

bool SharkLives::init()
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    musicData = MusicData::getMusicData();
    
    loadGameData();
    sizeOfSharkLifesVector = defaultSharkLives;
    fillAllSharkLifesVector( sizeOfSharkLifesVector );

    
    setAllReturnTimes();
    startTimer();
    
    return true;
}

void SharkLives::loadGameData()
{
    gameData = GameData::getGameData();
    
    defaultSharkLives = gameData->getDefaultSharkLives();
    
    timeFirstLifeReturn = gameData->getFirstLifeLoseTimer();
    timeSecondLifeReturn = gameData->getSecondLifeLoseTimer();
    timeThirdLifeReturn = gameData->getThirdLifeLoseTimer();
    timeFourthLifeReturn = gameData->getFourthLifeLoseTimer();
    timeFifthLifeReturn = gameData->getFifthLifeLoseTimer();
}

void SharkLives::fillAllSharkLifesVector( int data )
{
    auto additionalLife1PosX = ( visibleSize.width + origin.x ) * 5/6;
    auto additionalLife1PosY = visibleSize.height + origin.y - ( visibleSize.height / 20 );
    for (int i = 0; i < data; i++) {
        auto hearth = Sprite::create( "hearth.png" );
        if ( hearth == nullptr )
        {
            problemLoading( "'hearth.png'" );
        }
        hearth->setScale( SHARK_SCALE_PARAM_ADDITIONAL_LIFE );
        hearth->setAnchorPoint( Vec2( 1.0, 0.5 ) );
        hearth->setPosition( Vec2( additionalLife1PosX - ( hearth->getContentSize().width * i * 1.15 ), additionalLife1PosY ) );
        allSharkLifes.pushBack( hearth );
        // SHOW ADD SHARK LIFES
        this->addChild( hearth, 1000 );
        hearth->setVisible( false );
    }

    displayAdditionalsSharkLifes( 0 );
}

void SharkLives::displayAdditionalsSharkLifes( int data )
{
    // SET INVISIBLE
    for ( int i = sizeOfSharkLifesVector - 1; i >= data; i-- ) {
        allSharkLifes.at( i )->setVisible( false );
    }
    
    // SET VISIBLE
    for ( int i = 0; i < data; i++ ) {
        allSharkLifes.at( i )->setVisible( true );
    }
    
}

void SharkLives::checkCurrentSharkLives()
{
    if ( getCurrentSharkLives() > 0 )
    {
        setCanPlayStatus( true );
    }
    else
    {
        setCanPlayStatus( false );
    }
}

void SharkLives::setCanPlayStatus( bool status )
{
    this->canPlay = status;
}

// call only one time
void SharkLives::setAllReturnTimes()
{
    long currentTime = getTimeStampInSeconds();
    firstTimeLivesCounter = 0;

    if ( timeFirstLifeReturn != MAX_TIME ){
        if ( (timeFirstLifeReturn - currentTime ) < 0 ){
            timeFirstLifeReturn = MAX_TIME;
            isExistFirstLife = true;
            firstTimeLivesCounter++;
        } else {
            isExistFirstLife = false;
        }
    } else {
        isExistFirstLife = true;
        firstTimeLivesCounter++;
    }
    if ( timeSecondLifeReturn != MAX_TIME ){
        if ( (timeSecondLifeReturn - currentTime ) < 0 ){
            timeSecondLifeReturn = MAX_TIME;
            isExistSecondLife = true;
            firstTimeLivesCounter++;
        } else {
            isExistSecondLife = false;
        }
    } else {
        isExistSecondLife = true;
        firstTimeLivesCounter++;
    }
    if ( timeThirdLifeReturn != MAX_TIME ){
        if ( (timeThirdLifeReturn - currentTime ) < 0 ){
            timeThirdLifeReturn = MAX_TIME;
            isExistThirdLife = true;
            firstTimeLivesCounter++;
        } else {
             isExistThirdLife = false;
        }
    } else {
        isExistThirdLife = true;
        firstTimeLivesCounter++;
    }
    if ( timeFourthLifeReturn != MAX_TIME ){
        if ( (timeFourthLifeReturn - currentTime ) < 0 ){
            timeFourthLifeReturn = MAX_TIME;
            isExistFourthLife = true;
            firstTimeLivesCounter++;
        } else {
            isExistFourthLife = false;
        }
    } else {
        isExistFourthLife = true;
        firstTimeLivesCounter++;
    }
    if ( timeFifthLifeReturn != MAX_TIME ){
        if ( (timeFifthLifeReturn - currentTime ) < 0 ){
            timeFifthLifeReturn = MAX_TIME;
            isExistFifthLife = true;
            firstTimeLivesCounter++;
        } else {
            isExistFifthLife = false;
        }
    } else {
        isExistFifthLife = true;
        firstTimeLivesCounter++;
    }
    
    setCurrentSharkLives( firstTimeLivesCounter );
    checkCurrentSharkLives();
    displayAdditionalsSharkLifes( firstTimeLivesCounter );
    if ( firstTimeLivesCounter < defaultSharkLives ) {
        startTimer();
    }

    saveData();
}



void SharkLives::decreaseCurrentSharkLives()
{
    if ( getCurrentSharkLives() > 0 )
    {
        this->currentSharkLives -= 1;
    }
    
    checkCurrentSharkLives();
    calculateTimeToRefille();
    displayAdditionalsSharkLifes( getCurrentSharkLives() );
    
}

void SharkLives::increaseCurrentSharkLives()
{
    if ( getCurrentSharkLives() < defaultSharkLives )
    {
        this->currentSharkLives += 1;
        playWinHeartSound();
        saveData();
    }
    
    checkCurrentSharkLives();
    displayAdditionalsSharkLifes( getCurrentSharkLives() );
}

void SharkLives::calculateTimeToRefille()
{
    DEBUG_INFO;
    int timeForOneLife = 0;
    long tempTime = getTimeStampInSeconds();
    
    if ( false == isExistFifthLife )
    {
        timeForOneLife = 6 * 30;
    }
    else if ( false == isExistFourthLife )
    {
        timeForOneLife = 5 * 30;
    }
    else if ( false == isExistThirdLife )
    {
        timeForOneLife = 4 * 30;
    }
    else if ( false == isExistSecondLife )
    {
        timeForOneLife = 3 * 30;
    }
    else if ( false == isExistFirstLife )
    {
        timeForOneLife = 2 * 30;
    }
    else
    {
        timeForOneLife = 1 * 30;
    }
        
    
    if ( true == isExistFirstLife )
    {
        isExistFirstLife = false;
        timeFirstLifeReturn = tempTime + timeForOneLife;
    }
    else if ( true == isExistSecondLife )
    {
        isExistSecondLife = false;
        timeSecondLifeReturn = tempTime + timeForOneLife;
    }
    else if ( true == isExistThirdLife )
    {
        isExistThirdLife = false;
        timeThirdLifeReturn = tempTime + timeForOneLife;
    }
    else if ( true == isExistFourthLife )
    {
        isExistFourthLife = false;
        timeFourthLifeReturn = tempTime + timeForOneLife;
    }
    else if ( true == isExistFifthLife )
    {
        isExistFifthLife = false;
        timeFifthLifeReturn = tempTime + timeForOneLife;
    }
    
    saveData();
    
}


void SharkLives::setCurrentSharkLives( int lives )
{
    this->currentSharkLives = lives;
}

int SharkLives::getCurrentSharkLives()
{
    return this->currentSharkLives;
}

bool SharkLives::getCanPlayStatus()
{
    return this->canPlay;
}

bool SharkLives::checkCanPlaySL()
{
    return getCanPlayStatus();
}

long SharkLives::getTimeStampInSeconds()
{
    return time(&now);
}


void SharkLives::startTimer()
{
    isTimerIsRunning = true;
    this->schedule( schedule_selector( SharkLives::updateSharkTimer ), 1.0f );
}

void SharkLives::stopTimer()
{
    isTimerIsRunning = false;
    this->unschedule( schedule_selector( SharkLives::updateSharkTimer ) );
    timeCounter = 0;
}

void SharkLives::updateSharkTimer( float dt )
{
    long currentTime = getTimeStampInSeconds();

//    log("----------------------------------------------------------------------");
//    log("SL row 436  first  time diff %ld", timeFirstLifeReturn - currentTime );
//    log("SL row 437  second time diff %ld",  timeSecondLifeReturn - currentTime );
//    log("SL row 438  third  time diff %ld",  timeThirdLifeReturn - currentTime );
//    log("SL row 439  fourth time diff %ld",  timeFourthLifeReturn - currentTime );
//    log("SL row 440  fifth  time diff %ld",  timeFifthLifeReturn - currentTime );
//    log("----------------------------------------------------------------------");
    
    
    if ( timeFirstLifeReturn < currentTime ) {
        timeFirstLifeReturn = MAX_TIME;
        isExistFirstLife = true;
        increaseCurrentSharkLives();
    }
    if ( timeSecondLifeReturn < currentTime ){
        timeSecondLifeReturn = MAX_TIME;
        isExistSecondLife = true;
        increaseCurrentSharkLives();
    }
    if ( timeThirdLifeReturn < currentTime ){
        timeThirdLifeReturn = MAX_TIME;
        isExistThirdLife = true;
        increaseCurrentSharkLives();
    }
    if ( timeFourthLifeReturn < currentTime ){
        timeFourthLifeReturn = MAX_TIME;
        isExistFourthLife = true;
        increaseCurrentSharkLives();
    }
    if ( timeFifthLifeReturn < currentTime ){
        timeFifthLifeReturn = MAX_TIME;
        isExistFifthLife = true;
        increaseCurrentSharkLives();

    }
}

void SharkLives::playWinHeartSound()
{
    musicData->playEarnHeartSound();
}

void SharkLives::saveGameData()
{
    DEBUG_INFO;
    this->saveData();
}

void SharkLives::saveData()
{
    DEBUG_INFO;
    gameData->setFirstLifeLoseTimer( timeFirstLifeReturn );
    gameData->setSecondLifeLoseTimer( timeSecondLifeReturn );
    gameData->setThirdLifeLoseTimer( timeThirdLifeReturn );
    gameData->setFourthLifeLoseTimer( timeFourthLifeReturn );
    gameData->setFifthLifeLoseTimer( timeFifthLifeReturn );
    gameData->setCurrentSharkLives( getCurrentSharkLives() );
    gameData->writeDataToUserData();
}
