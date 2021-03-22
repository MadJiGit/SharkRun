//
//  UI.cpp
//  TestGame
//
//  Created by Madji on 9.05.19.
//


#include "UI.hpp"


using namespace cocos2d;

UI *UI::createUI( GameScene *scene )
{
    DEBUG_INFO;
    UI *sprite;
    sprite = new UI();

    if ( sprite ) {
        sprite->autorelease();
        sprite->setScene( scene );
        sprite->init();

        return sprite;
    }

    CC_SAFE_DELETE( sprite );
    return sprite = nullptr;
}


void UI::setScene( GameScene *scene )
{
    this->scene = scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainScene.cpp\n");
}

bool UI::init( )
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

//    frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    
    loadGameData();
    loadMusicData();
    
    setUI();

//    setGameTimerToZero();
//    setGameTimerToInitValue();
    setGameTimerToInitValue();
    setScoreCounterToZero();
    setGameTimerLabel();
    setGameScoreLabel();
    setPauseButton();
    setLevelLabel();

    displayAdditionalSharkLives();

    this->scheduleUpdate();

    return true;

}

void UI::loadGameData()
{
    gameData = GameData::getGameData();
}

void UI::loadMusicData()
{
    musicData = MusicData::getMusicData();
}

// SHARK stuff

bool UI::checkCanPlayBG()
{
    return sharkLives->checkCanPlaySL();
}

void UI::displayAdditionalSharkLives()
{
    sharkLives = SharkLives::createSharkLives( this );
}

void UI::displayEarnedStars( int stars )
{
    
    for (int i = 0; i < stars; i++) {
//        auto starScaleParam = 0.65;
        auto star = Sprite::create( "star_earned.png" );
        if ( star == nullptr )
        {
            problemLoading( "'star_earned.png'" );
        }
//        star->setScale( STAR_SCALE_PARAM );
        star->setAnchorPoint( Vec2( 1, 0.5 ) );
//        auto additionalStarPosX = ( 120 + star->getContentSize().width  + ( star->getContentSize().width * 0.8 * i ) );
        auto additionalStarPosX = ( visibleSize.width + origin.x ) * 1/5 + ( star->getContentSize().width * 1.1 * i );
        auto additionalStarPosY = visibleSize.height + origin.y - ( visibleSize.height / 20 );
        star->setPosition( Vec2(  additionalStarPosX, additionalStarPosY ) );
        this->addChild( star, 1000 );
//        log("UI 98 star %d X %f Y %f", i, star->getPositionX(), star->getPositionY() );
//        auto additionalLife1PosX = ( visibleSize.width + origin.x ) * 3/4 + ( hearth->getContentSize().width * 1.5 * SHARK_SCALE_PARAM_ADDITIONAL_LIFE );
    }
}

void UI::decreaseSharkLives()
{
    sharkLives->decreaseCurrentSharkLives();
}

void UI::increaseSharkLives()
{
    sharkLives->increaseCurrentSharkLives();
}

void UI::setGameScoreLabel()
{
    tempScore = __String::createWithFormat( "%05d", getGameScoreCounter() );
    gameScoreLabel = Label::createWithTTF( tempScore->getCString(), FONT , visibleSize.height * SCORE_FONT_SIZE );
    gameScoreLabel->setColor( Color3B::WHITE );
//    gameScoreLabel->setPosition( Point( origin.x + visibleSize.width - ( visibleSize.width / 15 ),
//                                       visibleSize.height + origin.y - visibleSize.height / 20 ) );
    gameScoreLabel->setAnchorPoint( Vec2( 0.5, 0.5 ) );
    gameScoreLabel->setPosition( Point( ( ( origin.x + visibleSize.width ) * 9.4 / 10 ),
                                       visibleSize.height + origin.y - visibleSize.height / 20 ) );
    
//    log("SL 122 gameScoreLabel size X %f pos X %f", gameScoreLabel->getContentSize().width, gameScoreLabel->getPositionX() );

    this->addChild( gameScoreLabel, 1000 );
}

void UI::displayGameScore()
{
    gameScoreLabel->setString( __String::createWithFormat( "%05d", getGameScoreCounter() )->getCString() );
}


void UI::setGameTimerLabel()
{
    tempTimer = __String::createWithFormat( "%02d:%02d", getGameTimerMinutes(), getGameTimerSeconds() );
    gameTimerLabel = Label::createWithTTF( tempTimer->getCString(), FONT , visibleSize.height * SCORE_FONT_SIZE );
    gameTimerLabel->setColor( Color3B::WHITE );
    gameTimerLabel->setAnchorPoint( Vec2( 0.5, 0.5 ) );
    gameTimerLabel->setPosition( Point( origin.x + visibleSize.width / 2,
                                       visibleSize.height + origin.y - visibleSize.height / 20 ) );
    
//    log("SL 140 gameTimerLabel size X %f pos X %f", gameTimerLabel->getContentSize().width, gameTimerLabel->getPositionX() );

    this->addChild( gameTimerLabel, 1000 );
}

int UI::getFishCounter()
{
    return this->fishCounter;
}

void UI::setFishCounter( int fishes )
{
    this->fishCounter = fishes;
}

void UI::increaseFishCounter()
{
    this->fishCounter++;
}


void UI::displayGameTimer()
{
    gameTimerLabel->setString( __String::createWithFormat( "%02d:%02d", getGameTimerMinutes(), getGameTimerSeconds() )->getCString() );
}

int UI::getGameScoreCounter()
{
    return gameData->getScoreCounter();
}

void UI::addPointsToGameScore( int points )
{
//    printf("UI 165 increaseScore with %d", points);
    gameData->increaseScore( points );
    
    if ( false == thirdStar ){
        updateEarnedStars();
    }

}

void UI::setScoreCounterToZero()
{
    gameData->setScoreCounterToZero();
}

void UI::startTimer()
{
    this->schedule( schedule_selector( UI::updateGameTimer ), 1.0f );
}

void UI::stopTimer()
{
    this->unschedule( schedule_selector( UI::updateGameTimer ) );
}

void UI::updateGameTimer( float dt )
{
    gameData->decreaseTimerCounter();
}

void UI::setGameTimerToInitValue()
{
    DEBUG_INFO;
    gameData->setTimerCounterToInitValue();
}

void UI::setGameTimerToZero()
{
    DEBUG_INFO;
    gameData->setTimerCounterToZero();
}

int UI::getGameTimerSeconds()
{
    return gameData->getTimerSeconds();
}
int UI::getGameTimerMinutes()
{
    return gameData->getTimerMinutes();
}

int UI::getGameTimerCounter()
{
    return gameData->getTimerCounter();
}

int UI::getEarnedStars()
{
    return gameData->getStarsCounter();
}

void UI::updateEarnedStars()
{
    int stars = getEarnedStars();
//    log("UI 214 earned stars %d", stars);
    if ( false == thirdStar && stars == 3 )
    {
//        log("UI 218 earned THIRD star");
        playEarnStarSound();
        displayEarnedStars( stars );
        thirdStar = true;
    }
    else if ( false == secondStar && stars == 2 )
    {
//        log("UI 225 earned SECOND star");
        playEarnStarSound();
        displayEarnedStars( stars );
        secondStar = true;
    }
    else if ( false == firstStar && stars == 1 )
    {
//        log("UI 218 earned FIRST star");
        playEarnStarSound();
        displayEarnedStars( stars );
        firstStar = true;
    }

}

void UI::clearEarnedStars( )
{
    gameData->resetStarsCounter();
}

void UI::update( float dt )
{
    displayGameTimer();
    displayGameScore();
}

void UI::playEarnStarSound()
{
    musicData->playEarnStarSound();
}

void UI::setUI( )
{

}

void UI::setLevelLabel()
{
//    CCLabelTTF* cycleLabel1 = CCLabelTTF::create(" ", "Roboto Thin", 80);
    tempLevelNumber = __String::createWithFormat( "Lv %02d", gameData->getCurrentLevelNumber() );
    levelLabel = Label::createWithTTF( tempLevelNumber->getCString() , FONT , visibleSize.height * SCORE_FONT_SIZE );
    levelLabel->setColor( Color3B::RED );
    levelLabel->setPosition(Point( gameTimerLabel->getPositionX() - (gameTimerLabel->getContentSize().width)*1.3, gameTimerLabel->getPositionY() ));
    
    
    this->addChild( levelLabel, 1000 );
    
    displayLevelNumber();
    
}

void UI::displayLevelNumber()
{
    levelLabel->setString( __String::createWithFormat( "Lv %02d", gameData->getCurrentLevelNumber() )->getCString() );
}

void UI::saveUserData()
{
    DEBUG_INFO;
    this->sharkLives->saveGameData();
}

void UI::setPauseButton()
{
    pauseButton = cocos2d::ui::Button::create( "blue_pause.png" );
    pauseButton->setScale( SCALE_PAUSE_BUTTON );
    pauseButton->setZoomScale( - 0.1f );
    pauseButton->setAnchorPoint( Vec2( 0.5, 0.5 ) );
    pauseButton->setPosition( Vec2( ( ( origin.x + visibleSize.width ) * 0.5 / 10 ) - ( pauseButton->getContentSize().width / 2 * SCALE_PAUSE_BUTTON ), visibleSize.height - ( visibleSize.height / 20 ) + origin.y ) );
    pauseButton->addTouchEventListener( [=] ( Ref *sender , cocos2d::ui::Widget::TouchEventType type )
                                       {
                                           if ( cocos2d::ui::Widget::TouchEventType::BEGAN == type )
                                           {
                                               playButtonStartClick();
                                           }
                                           else if ( cocos2d::ui::Widget::TouchEventType::ENDED == type )
                                           {
                                               playButtonEndClick();
                                               UI::goToPauseScene( scene );
                                           }
                                           else if ( cocos2d::ui::Widget::TouchEventType::MOVED == type )
                                           {
                                           }
                                           else if ( cocos2d::ui::Widget::TouchEventType::CANCELED == type )
                                           {
                                           }
                                       }
                                       );
    
    this->addChild( pauseButton, 1200 );
}

void UI::playButtonStartClick()
{
    musicData->playButtonStartClickSound();
}
void UI::playButtonEndClick()
{
    musicData->playButtonEndClickSound();
}
void UI::pauseBackgroundMusic()
{
    musicData->pauseGameMusic();
}

void UI::goToPauseScene( Ref *sender )
{
    DEBUG_INFO;
    pauseBackgroundMusic();
    saveUserData();
    auto pauseScene = PauseScene::createScene();
    Director::getInstance( )->pushScene( TransitionFade::create( TRANSITION_TIME_BETWEEN_SCENE, pauseScene ) );
}

void UI::setPauseButtonCondition( bool condition )
{
    pauseButton->setEnabled( condition );
}
