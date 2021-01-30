//
//  YouFailedScene.cpp
//  TestGame
//
//  Created by Madji on 9.05.19.
//

#include "YouFailedMenu.hpp"

using namespace cocos2d;
using namespace cocos2d::ui;

YouFailedMenu *YouFailedMenu::createMenu( GameScene *scene )
{
    YouFailedMenu   *sprite;
    sprite = new YouFailedMenu();
    
    if ( sprite )
    {
        sprite->setScene( scene );
        scene->addChild( sprite );
        sprite->initFailedMenu();
        
        return sprite;
    }
    
    scene->removeChild( sprite );
    CC_SAFE_DELETE( sprite );
    return sprite = nullptr;
    
}


void YouFailedMenu::setScene( GameScene *scene )
{
    this->scene = scene;
}

bool YouFailedMenu::initFailedMenu()
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    loadData();
    createFailedMenu();
    
    return true;
}

void YouFailedMenu::loadData()
{
    _musicData = MusicData::getMusicData();
    _gameData = GameData::getGameData();
}


void YouFailedMenu::createFailedMenu()
{
    sceneBg = Sprite::create( "beach_bg_all.png" );
    sceneBg->setPosition( Point ( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
//    sceneBg->setScale( COEFFICIENT_TO_SCALE_BACKGROUND_WELCOME_SCENE );
    sceneBg->setColor( Color3B( 200, 200, 200 ) );
//    sceneBg->setOpacity( 200 );
    sceneLabel = Sprite::create( "failed_layer.png" );
//    sceneLabel->setScale( FAILD_MENU_LAYER_SCALE );
    sceneLabel->setPosition( Point ( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 50 ) );
    
    retryButton = cocos2d::ui::Button::create( "retry_button.png" );
    retryButton->addTouchEventListener( [=] ( Ref *sender , cocos2d::ui::Widget::TouchEventType type )
                                       {
                                           if ( cocos2d::ui::Widget::TouchEventType::BEGAN == type )
                                           {
                                               playButtonStartClick();
                                           }
                                           else if ( cocos2d::ui::Widget::TouchEventType::ENDED == type )
                                           {
                                               playButtonEndClick();
                                               goToRetryTestScene();
                                           }
                                           else if ( cocos2d::ui::Widget::TouchEventType::MOVED == type )
                                           {
                                           }
                                           else if ( cocos2d::ui::Widget::TouchEventType::CANCELED == type )
                                           {
                                           }
                                       }
                                       );

    exitButton = cocos2d::ui::Button::create( "menu_button.png" );
    exitButton->addTouchEventListener( [=] ( Ref *sender , cocos2d::ui::Widget::TouchEventType type )
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
                                          else if ( cocos2d::ui::Widget::TouchEventType::MOVED == type )
                                          {
                                          }
                                          else if ( cocos2d::ui::Widget::TouchEventType::CANCELED == type )
                                          {
                                          }
                                      }
                                      );
    retryButton->setZoomScale( - 0.1f );
    exitButton->setZoomScale( - 0.1f );
    
//    retryButton->setScale( FAILED_MENU_BUTTONS_SCALE );
//    exitButton->setScale( FAILED_MENU_BUTTONS_SCALE );
    
    gameTimerLabel = Label::createWithTTF( ( __String::createWithFormat( "TIME        %02d:%02d", getGameTimerMinutes() , getGameTimerSeconds() )->getCString() ), FONT , visibleSize.height * SCORE_FONT_SIZE );
    gameTimerLabel->setColor( Color3B::BLACK );
    gameTimer = MenuItemLabel::create( gameTimerLabel );
//    gameTimer->setAnchorPoint( Vec2( 0, 0 ) );
    gameTimerLabel->setHorizontalAlignment( TextHAlignment::LEFT );
    
    gameScoreLabel = Label::createWithTTF( ( __String::createWithFormat( "SCORE       %05d", getGameScore() )->getCString() ), FONT , visibleSize.height * SCORE_FONT_SIZE );
    gameScoreLabel->setColor( Color3B::BLACK );
    gameScore = MenuItemLabel::create( gameScoreLabel );
//    gameScore->setAnchorPoint( Vec2( 0, 0 ) );
    gameScoreLabel->setHorizontalAlignment( TextHAlignment::LEFT );
    
    
    auto posY = sceneLabel->getPositionY() - (( sceneLabel->getContentSize().height / 2 ) * 0.75);

    retryButton->setPosition( Vec2(visibleSize.width / 2 - retryButton->getContentSize().width/2,  posY ) );
    exitButton->setPosition( Vec2( visibleSize.width / 2 + exitButton->getContentSize().width, posY ) );
    
    gameTimer->setPosition( Point( sceneLabel->getPositionX(), sceneLabel->getPositionY() - ( 0.8 * visibleSize.height * SCORE_FONT_SIZE ) ) );
    gameScore->setPosition( Point( sceneLabel->getPositionX(), sceneLabel->getPositionY() - ( 1.8 * visibleSize.height * SCORE_FONT_SIZE ) ) );
    
    sceneMenu = Menu::create( gameTimer, gameScore, nullptr );
    
    scene->addChild( sceneBg, 1300 );
    scene->addChild( sceneLabel, 1400 );
    scene->addChild( retryButton, 1400 );
    scene->addChild( exitButton, 1400 );
    
    sceneMenu->setPosition( Point::ZERO );
    
    scene->addChild( sceneMenu, 1500 );

}

void YouFailedMenu::setVisible()
{
    this->sceneMenu->setVisible( true );
}

void YouFailedMenu::setInvisible()
{
    this->sceneMenu->setVisible( false );
}

void YouFailedMenu::playButtonStartClick()
{
    _musicData->playButtonStartClickSound();
}

void YouFailedMenu::playButtonEndClick()
{
    _musicData->playButtonEndClickSound();
}

void YouFailedMenu::goToRetryTestScene()
{
    fadeOutSprites();
    auto scene = GameScene::createScene();
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME_BETWEEN_SCENE, scene ) );
}

void YouFailedMenu::goToGameOverScene()
{
    fadeOutSprites();
    
    auto scene = GameOverScene::createScene( );
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME_BETWEEN_SCENE, scene ) );
}

int YouFailedMenu::getGameTimerSeconds()
{
    return _gameData->countdownTimerCounterDefaultSec;
}

int YouFailedMenu::getGameTimerMinutes()
{
    return _gameData->countdownTimerCounterDefaultMin;
}

int YouFailedMenu::getGameScore()
{
//    printf("YFM 196 getScoreCounter %d\n", _gameData->getScoreCounter());
    return _gameData->getScoreCounter();
}

void YouFailedMenu::removeMenu()
{
    deleteSprites();
}

void YouFailedMenu::fadeOutSprites()
{
    scene->unscheduleUpdate();
    _gameData->saveUserData();
    retryButton->setEnabled( false );
    exitButton->setEnabled( false );
    
//    FadeOut *fadeOut = FadeOut::create( 1.0f );
//    sceneMenu->runAction( fadeOut );
//    sceneBg->runAction( fadeOut );
//    sceneLabel->runAction( fadeOut );
//    retryButton->runAction( fadeOut );
//    exitButton->runAction( fadeOut );
    
    auto delayTime = DelayTime::create( 1.0f );
//    auto fun1 = CallFunc::create([&]() { this->setInvisible(); } );
    auto fun2 = CallFunc::create([&]() { this->removeMenu(); } );
    
//    auto seq = Sequence::create( delayTime, fun1, delayTime, fun2,  nullptr );
    auto seq = Sequence::create( delayTime, fun2,  nullptr );
    
    this->runAction( seq );
}

void YouFailedMenu::deleteSprites()
{
    scene->cocos2d::Node::removeChild( sceneMenu );
    scene->cocos2d::Node::removeChild( sceneBg );
    scene->cocos2d::Node::removeChild( sceneLabel );
    scene->cocos2d::Node::removeChild( retryButton );
    scene->cocos2d::Node::removeChild( exitButton );
}

void YouFailedMenu::onExit()
{
    RemoveSelf::create();
}
