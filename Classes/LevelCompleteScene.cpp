//
//  LevelCompleteScene.cpp
//  TestGame
//
//  Created by Madji on 9.05.19.
//

#include "LevelCompleteScene.hpp"

using namespace cocos2d;
using namespace cocos2d::ui;

LevelCompleteScene *LevelCompleteScene::createMenu( GameScene *scene )
{
    LevelCompleteScene   *sprite;
    sprite = new LevelCompleteScene();
    
    if ( sprite )
    {
        sprite->setScene( scene );
        scene->addChild( sprite );
        sprite->init();
        
        return sprite;
    }
    
    scene->removeChild( sprite );
    CC_SAFE_DELETE( sprite );
    return sprite = nullptr;
    
}


void LevelCompleteScene::setScene( GameScene *scene )
{
    this->scene = scene;
}

bool LevelCompleteScene::init()
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    loadData();
    stopGameMusic();
    setStarsEarned();
    createMenu();
    createButtons();
    createStars( getStarsEarned() );
    _gameData->resetStarsCounter();
    _gameData->resetFishCounterToZero();
    createLevelCompleteScene();
    
    return true;
}

void LevelCompleteScene::loadData()
{
    _musicData = MusicData::getMusicData();
    _gameData = GameData::getGameData();
}

void LevelCompleteScene::setStarsEarned()
{
    this->stars = getStarsEarned();
}


void LevelCompleteScene::createLevelCompleteScene()
{
    auto starsPosY = sceneLabel->getPositionY() + ( oneStar->getContentSize().height * 0.7 );
    
    auto buttonPosY = sceneLabel->getPositionY() - ( playButton->getContentSize().height * 1.7 );
    
    auto labelPosY = sceneLabel->getPositionY() - 30;
    
    oneStar->setPosition( Vec2( sceneLabel->getPositionX(), starsPosY ) );
//    twoStars->setPosition( Vec2( sceneLabel->getPositionX(), starsPosY ) );
//    threeStars->setPosition( Vec2( sceneLabel->getPositionX(), starsPosY ) );
    
    retryButton->setPosition( Vec2( sceneLabel->getPositionX() - ( retryButton->getContentSize().width * 1.5),  buttonPosY ) );
    playButton->setPosition( Vec2( visibleSize.width / 2, buttonPosY ) );
    menuButton->setPosition( Vec2( sceneLabel->getPositionX() + ( menuButton->getContentSize().width * 1.5 ), buttonPosY ) );
    
    
    gameTimer->setPosition( Point( sceneLabel->getPositionX(), labelPosY ) );
    fishEaten->setPosition( Point( sceneLabel->getPositionX(), labelPosY - visibleSize.height * SCORE_FONT_SIZE ) );
    gameScore->setPosition( Point( sceneLabel->getPositionX(), labelPosY - ( 2 * visibleSize.height * SCORE_FONT_SIZE ) ) );
    
    sceneMenu = Menu::create( gameScore, fishEaten, gameTimer, nullptr );
    
//    printf("LCS 90 play %f %f\n", playButton->getPositionX(), playButton->getPositionY() );
    
    scene->addChild( oneStar, 1300 );
//    scene->addChild( twoStars, 1300 );
//    scene->addChild( threeStars, 1300 );
    scene->addChild( sceneBg, 1200 );
    scene->addChild( sceneLabel, 1200 );
    scene->addChild( retryButton, 1300 );
    scene->addChild( menuButton, 1300 );
    scene->addChild( playButton, 1300 );
    
    sceneMenu->setPosition( Point::ZERO );
    
    scene->addChild( sceneMenu, 1300 );

}

void LevelCompleteScene::createStars( int stars )
{

#ifdef DEBUGING
    
    printf("LCS 112 stars %d\n", stars);
    
#endif
    
    if (stars > 2) {
        oneStar = Sprite::create("three_stars_lcm.png");
    } else if ( stars > 1 ){
        oneStar = Sprite::create("two_stars_lcm.png");
    } else if ( stars > 0 ) {
        oneStar = Sprite::create("one_star_lcm.png");
    } else {
        oneStar = Sprite::create("");
        printf("WARNING LCS 121 - oneStar is not created because earned points are not enough!!!!");
    }
    
    
//    oneStar = Sprite::create("one_star_lcm.png");
//    oneStar->setScale( LEVEL_COMPLETE_STAR_SCALE );
//    oneStar->setVisible( false );
    
//    twoStars = Sprite::create("two_stars_lcm.png");
//    twoStars->setScale( LEVEL_COMPLETE_STAR_SCALE );
//    twoStars->setVisible( false );
    
//    threeStars = Sprite::create("three_stars_lcm.png");
//    threeStars->setScale( LEVEL_COMPLETE_STAR_SCALE );
//    threeStars->setVisible( false );
    
//    setStarsVisible();
    
}

//void LevelCompleteScene::setStarsVisible()
//{
//    if ( stars == 2 )
//    {
//        twoStars->setOpacity( 20 );
//    }
//    else if ( stars == 1 )
//    {
//        twoStars->setOpacity( 20 );
//        threeStars->setOpacity( 20 );
//    }
//}

void LevelCompleteScene::createMenu()
{
    sceneBg = Sprite::create( "beach_bg_all.png" );
    sceneBg->setPosition( Point ( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    //sceneBg->setScale( COEFFICIENT_TO_SCALE_BACKGROUND_WELCOME_SCENE );
    sceneBg->setColor( Color3B( 200, 200, 200 ) );
    sceneBg->setOpacity( 200 );
    sceneLabel = Sprite::create( "level_complete_layer_lcm.png" );
    sceneLabel->setScale( LEVEL_COMPLETE_MENU_LAYER_SCALE );
    sceneLabel->setPosition( Point ( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 50 ) );
    
    
    gameScoreLabel = Label::createWithTTF( ( __String::createWithFormat( "SCORE           %05d", getGameScore() )->getCString() ), FONT , visibleSize.height * SCORE_FONT_SIZE );
    gameScoreLabel->setColor( Color3B::BLACK );
    gameScoreLabel->setAnchorPoint( Vec2( 0, 0 ) );
    gameScoreLabel->setHorizontalAlignment( TextHAlignment::LEFT );
    gameScore = MenuItemLabel::create( gameScoreLabel );
    
    fishEatenLabel = Label::createWithTTF( ( __String::createWithFormat( "FISH EATEN    %05d", getFishEaten() )->getCString() ), FONT , visibleSize.height * SCORE_FONT_SIZE );
    fishEatenLabel->setColor( Color3B::BLACK );
    fishEatenLabel->setAnchorPoint( Vec2( 0, 0 ) );
    fishEatenLabel->setHorizontalAlignment( TextHAlignment::LEFT );
    fishEaten = MenuItemLabel::create( fishEatenLabel );
    
    gameTimerLabel = Label::createWithTTF( ( __String::createWithFormat( "TIME       %02d:%02d", getGameTimerMinutes() , getGameTimerSeconds() )->getCString() ), FONT , visibleSize.height * SCORE_FONT_SIZE );
    gameTimerLabel->setColor( Color3B::BLACK );
    gameTimerLabel->setAnchorPoint( Vec2( 0, 0 ) );
    gameTimerLabel->setHorizontalAlignment( TextHAlignment::LEFT );
    gameTimer = MenuItemLabel::create( gameTimerLabel );
    
}
void LevelCompleteScene::createButtons()
{
    retryButton = cocos2d::ui::Button::create( "retry_button_lcm.png" );
    retryButton->addTouchEventListener( [=] ( Ref *sender , cocos2d::ui::Widget::TouchEventType type )
                                       {
                                           if ( cocos2d::ui::Widget::TouchEventType::BEGAN == type )
                                           {
                                               playButtonStartClick();
                                           }
                                           else if ( cocos2d::ui::Widget::TouchEventType::ENDED == type )
                                           {
                                               playButtonEndClick();
                                               goToRetryScene();
                                           }
//                                           else if ( cocos2d::ui::Widget::TouchEventType::MOVED == type )
//                                           {
//                                           }
//                                           else if ( cocos2d::ui::Widget::TouchEventType::CANCELED == type )
//                                           {
//                                           }
                                       }
                                       );
    
    menuButton = cocos2d::ui::Button::create( "menu_button_lcm.png" );
    menuButton->addTouchEventListener( [=] ( Ref *sender , cocos2d::ui::Widget::TouchEventType type )
                                      {
                                          if ( cocos2d::ui::Widget::TouchEventType::BEGAN == type )
                                          {
                                              playButtonStartClick();
                                          }
                                          else if ( cocos2d::ui::Widget::TouchEventType::ENDED == type )
                                          {
                                              playButtonEndClick();
                                              goToGameOverScene();
                                          }
//                                          else if ( cocos2d::ui::Widget::TouchEventType::MOVED == type )
//                                          {
//                                          }
//                                          else if ( cocos2d::ui::Widget::TouchEventType::CANCELED == type )
//                                          {
//                                          }
                                      }
                                      );
    
    playButton = cocos2d::ui::Button::create( "play_button_lcm.png" );
    playButton->addTouchEventListener( [=] ( Ref *sender , cocos2d::ui::Widget::TouchEventType type )
                                      {
                                          if ( cocos2d::ui::Widget::TouchEventType::BEGAN == type )
                                          {
                                              playButtonStartClick();
                                          }
                                          else if ( cocos2d::ui::Widget::TouchEventType::ENDED == type )
                                          {
                                              playButtonEndClick();
                                              goToNextLevel();
                                          }
//                                          else if ( cocos2d::ui::Widget::TouchEventType::MOVED == type )
//                                          {
//                                          }
//                                          else if ( cocos2d::ui::Widget::TouchEventType::CANCELED == type )
//                                          {
//                                          }
                                      }
                                      );
    retryButton->setZoomScale( - 0.1f );
    menuButton->setZoomScale( - 0.1f );
    playButton->setZoomScale( - 0.1f );
    
//    playButton->setScale( LEVEL_COMPLETE_MENU_PLAY_BUTTON_SCALE );
//    menuButton->setScale( LEVEL_COMPLETE_MENU_BUTTONS_SCALE );
//    retryButton->setScale( LEVEL_COMPLETE_MENU_BUTTONS_SCALE );
}

void LevelCompleteScene::setVisible()
{
    this->sceneMenu->setVisible( true );
}

void LevelCompleteScene::setInvisible()
{
    this->sceneMenu->setVisible( false );
}

void LevelCompleteScene::playButtonStartClick()
{
    _musicData->playButtonStartClickSound();
}

void LevelCompleteScene::playButtonEndClick()
{
    _musicData->playButtonEndClickSound();
}

void LevelCompleteScene::stopGameMusic()
{
    _musicData->stopGameMusic();
}

void LevelCompleteScene::pauseGameMusic()
{
    _musicData->pauseGameMusic();
}

void LevelCompleteScene::goToRetryScene()
{
    retryButton->setEnabled( false );
    menuButton->setEnabled( false );
    playButton->setEnabled( false );
    setInvisible();
    removeScene();
    
    auto scene = GameScene::createScene();
    
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME_BETWEEN_SCENE, scene ) );
}

void LevelCompleteScene::goToGameOverScene()
{
    fadeOutSprites();
    
    auto scene = GameOverScene::createScene( );
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME_BETWEEN_SCENE, scene ) );
}

void LevelCompleteScene::goToNextLevel()
{
    _gameData->setCurrentLevel( _gameData->getCurrentLevelNumber() + 1 );
    fadeOutSprites();
    
    auto scene = GameScene::createScene();
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME_BETWEEN_SCENE, scene ) );
}

int LevelCompleteScene::getGameTimerSeconds()
{
    return _gameData->countdownTimerCounterDefaultSec;
}

int LevelCompleteScene::getGameTimerMinutes()
{
    return _gameData->countdownTimerCounterDefaultMin;
}

int LevelCompleteScene::getGameScore()
{
    return _gameData->getScoreCounter();
}

int LevelCompleteScene::getFishEaten()
{
#ifdef DEBUGING
    printf("LCS 339 getFishCounter %d\n", _gameData->getFishCounter());
#endif
    return _gameData->getFishCounter();
}

int LevelCompleteScene::getStarsEarned()
{
#ifdef DEBUGING
    printf("LCS 340 getStarsEarned %d\n", _gameData->getStarsCounter());
#endif
    return _gameData->getStarsCounter();
}

void LevelCompleteScene::removeScene()
{
    deleteSprites();
}

void LevelCompleteScene::fadeOutSprites()
{
    scene->unscheduleUpdate();
    _gameData->writeDataToUserData();
    retryButton->setEnabled( false );
    menuButton->setEnabled( false );
    playButton->setEnabled( false );
    
    FadeOut *fadeOut = FadeOut::create( 1.0f );
    
    oneStar->runAction( fadeOut );
//    twoStars->runAction( fadeOut );
//    threeStars->runAction( fadeOut );
    sceneMenu->runAction( fadeOut );
    sceneBg->runAction( fadeOut );
    sceneLabel->runAction( fadeOut );
    retryButton->runAction( fadeOut );
    menuButton->runAction( fadeOut );
    playButton->runAction( fadeOut );
    
    
    auto delTime = DelayTime::create( 1.0f );
    auto fun1 = CallFunc::create([&]() { this->setInvisible(); } );
    auto fun2 = CallFunc::create([&]() { this->removeScene(); } );
    
    auto seq = Sequence::create( delTime, fun1, fun2, RemoveSelf::create(),  nullptr );
    
    this->runAction( seq );
    
}

void LevelCompleteScene::deleteSprites()
{
    scene->cocos2d::Node::removeChild( oneStar );
//    scene->cocos2d::Node::removeChild( twoStars );
//    scene->cocos2d::Node::removeChild( threeStars );
    scene->cocos2d::Node::removeChild( sceneMenu );
    scene->cocos2d::Node::removeChild( sceneBg );
    scene->cocos2d::Node::removeChild( sceneLabel );
    scene->cocos2d::Node::removeChild( retryButton );
    scene->cocos2d::Node::removeChild( menuButton );
    scene->cocos2d::Node::removeChild( playButton );
}

void LevelCompleteScene::onExit()
{
    RemoveSelf::create();
}
