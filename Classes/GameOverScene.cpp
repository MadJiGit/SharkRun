//
//  GameOverScene.cpp
//  TestGame
//
//  Created by Madji on 9.05.19.
//

#include "GameOverScene.hpp"

using namespace cocos2d;

Scene *GameOverScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GameOverScene::create();
    
    scene->addChild( layer );
    
    return scene;
}


bool GameOverScene::init( )
{
    
    if ( !Layer::init() ) {
        return false;
    }
    
    _musicData = MusicData::getMusicData();
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    
    setBackground();
    setReturnBack();
    setCloseButton();
    
    background->setPosition( Point ( visibleSize.width / 2 + origin.x,
                                    visibleSize.height / 2 + origin.y ) );
    returnBackLabel->setPosition( Point( (visibleSize.width / 2 - (returnBackLabel->getContentSize().width)*2),
                                        visibleSize.height / 2 - 50) );
    closeButton->setPosition( Point( (returnBackLabel->getPositionX() + (closeButton->getContentSize().width)*2),
                                    visibleSize.height / 2 - 50) );
    
    menu = Menu::create( returnBackLabel, closeButton, nullptr );
    menu->setPosition( Point::ZERO );
    
    this->addChild( background, - 2 );
    this->addChild( menu );
    
    
    return true;
     
}

void GameOverScene::setBackground()
{
//    background = Sprite::create( "bg_default_yellow_1920_1080.png" );
    background = Sprite::create( "beach_bg_all.png" );
    background->setScale( COEFFICIENT_TO_SCALE_BACKGROUND_WELCOME_SCENE * 1.1 );
}

void GameOverScene::setReturnBack()
{
    returnBackLabel = MenuItemImage::create( "yellow_left.png", "yellow_left_clicked.png", CC_CALLBACK_0( GameOverScene::returnBack, this ) );
    returnBackLabel->setScale( BUTTON_CLOSE_SCALE );
}

void GameOverScene::setCloseButton()
{
    closeButton = MenuItemImage::create( "red_close.png", "red_close_clicked.png", CC_CALLBACK_1( GameOverScene::exitGameScene, this ) );
    closeButton->setScale( BUTTON_CLOSE_SCALE );
}


void GameOverScene::returnBack()
{
    auto newGame = GameScene::createScene();
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME_BETWEEN_SCENE, newGame ) );
//    Director::getInstance()->popScene();
}

void GameOverScene::exitGameScene( Ref *sender )
{
    Director::getInstance()->end();
    exit(TRANSITION_TIME_BETWEEN_SCENE * 3 );
}
