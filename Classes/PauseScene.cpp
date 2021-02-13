//
//  PauseScene.cpp
//  TestGame
//
//  Created by Madji on 9.05.19.
//

#include "PauseScene.hpp"

extern int global_var;

using namespace cocos2d;

Scene *PauseScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = PauseScene::create();
    
    scene->addChild( layer );
    
    return scene;
}


bool PauseScene::init( )
{
    
    if ( !Layer::init() ) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    musicData = MusicData::getMusicData();
    
    setBackground();
    setMenuLayer();
    setResumeLabel();
    setRetryLabel();
    setChangeLabel();
    setSettingsLabel();
    setCloseButton();
 
    background->setPosition( Point ( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    menuLayer->setPosition( Point ( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 50 ) );
    
    
    auto resumeLabelX = visibleSize.width / 2 + origin.x;
    auto resumeLabelY = menuLayer->getPositionY() + resumeLabel->getContentSize().height;

    auto retryLabelX = resumeLabelX + OFFSET_X_PARAM;
    auto retryLabelY = resumeLabelY - ( retryLabel->getContentSize().height );
    
    auto changeLabelX = resumeLabelX + OFFSET_X_PARAM;
    auto changeLabelY = retryLabelY - ( changeLabel->getContentSize().height );
    
    auto settingsLabelX = resumeLabelX + OFFSET_X_PARAM / 2;
    auto settingsLabelY = changeLabelY - ( settingsLabel->getContentSize().height );
    
    auto closeLabelX = menuLayer->getPositionX() + menuLayer->getContentSize().width / 2 - closeButton->getContentSize().width / 2;
    auto closeLabelY = menuLayer->getPositionY() + menuLayer->getContentSize().height / 2 - closeButton->getContentSize().height;
    
    Vec2 deltaPosResume = Vec2( resumeLabelX, resumeLabelY );
    Vec2 deltaPosRetry = Vec2( retryLabelX, retryLabelY );
    Vec2 deltaPosChange = Vec2( changeLabelX, changeLabelY );
    Vec2 deltaPosSettings = Vec2( settingsLabelX, settingsLabelY );
    Vec2 deltaPosClose = Vec2( closeLabelX, closeLabelY );
    
   
    
    resumeLabel->setPosition( deltaPosResume );
    retryLabel->setPosition( deltaPosRetry );
    changeLabel->setPosition( deltaPosChange );
    settingsLabel->setPosition( deltaPosSettings );
    closeButton->setPosition( deltaPosClose );
    
    
    this->addChild( background, - 3 );
    this->addChild( menuLayer, - 2 );
    
    menu = Menu::create( resumeLabel, retryLabel, changeLabel, settingsLabel, closeButton, nullptr );
    menu->setPosition( Point::ZERO );

    this->addChild( menu, 1 );
    
    
    return true;
    
}

void PauseScene::setCloseButton()
{
    closeButton = MenuItemImage::create( "close_button_pm.png", "close_button_pm_clicked.png", CC_CALLBACK_1( PauseScene::exitGameScene, this ) );
//    closeButton->setScale( BUTTON_CLOSE_SCALE );
}

void PauseScene::setSettingsLabel()
{
    settingsLabel = MenuItemImage::create( "settings_layer_pm.png", "settings_layer_pm_clicked.png", CC_CALLBACK_1( PauseScene::goToSettings, this ) );
//    settingsLabel->setScale( BUTTON_RESUME_SETTINGS_SCALE );
}

void PauseScene::setChangeLabel()
{
    changeLabel = MenuItemImage::create( "change_level_layer_pm.png", "change_level_layer_pm_clicked.png", CC_CALLBACK_1( PauseScene::goToChangeLevel, this ) );
//    changeLabel->setScale( BUTTON_RETRY_CHANGE_SCALE );
}

void PauseScene::setRetryLabel()
{
    retryLabel = MenuItemImage::create( "restart_level_layer_pm.png", "restart_level_layer_pm_clicked.png", CC_CALLBACK_1( PauseScene::goToMainMenuScene, this ) );
//    retryLabel->setScale( BUTTON_RETRY_CHANGE_SCALE );
}

void PauseScene::setResumeLabel()
{
    resumeLabel = MenuItemImage::create( "resume_game_layer_pm.png", "resume_game_layer_pm_clicked.png", CC_CALLBACK_1( PauseScene::backToGameScene, this ) );
//    resumeLabel->setScale( BUTTON_RESUME_SETTINGS_SCALE );
}

void PauseScene::setMenuLayer()
{
    menuLayer = Sprite::create( "game_paused_menu_pm.png" );
//    menuLayer->setScale( PAUSE_MENU_LAYER_SCALE );
}


void PauseScene::setBackground()
{
    background = Sprite::create( "beach_bg_all.png" );
//    background->setScale( PAUSE_MENU_BACKGROUND_SCALE );
}

void PauseScene::goToChangeLevel( Ref *sender )
{
//    auto scene = SelectLevelScene::createScene();
//    Director::getInstance()->replaceScene( TransitionFade::create( TRANSITION_TIME_BETWEEN_SCENE, scene ) );
    DEBUG_INFO;
    Director::getInstance()->resume(); // don't know what hapens
    auto scene = SelectLevelScene::createScene();
    Director::getInstance()->pushScene( TransitionFade::create( TRANSITION_TIME_BETWEEN_SCENE, scene ) );
}

void PauseScene::goToSettings( Ref *sender )
{
    Director::getInstance()->resume(); // don't know what hapens
    auto scene = SettingsScene::createScene();
    Director::getInstance()->pushScene( TransitionFade::create( TRANSITION_TIME_BETWEEN_SCENE, scene ) );
//    Director::getInstance()->replaceScene( TransitionFade::create( TRANSITION_TIME_BETWEEN_SCENE, scene ) );
}

void PauseScene::goToMainMenuScene( Ref *sender )
{
    
    Director::getInstance()->resume();
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene( TransitionFade::create( TRANSITION_TIME_BETWEEN_SCENE, scene ) );
}

void PauseScene::backToGameScene( Ref *sender )
{
    resumeBackgroundMusic();
    Director::getInstance()->popScene();
}

void PauseScene::exitGameScene( Ref *sender )
{
    Director::getInstance()->resume();
    auto scene = GameOverScene::createScene();
    Director::getInstance()->pushScene( TransitionFade::create( TRANSITION_TIME_BETWEEN_SCENE, scene ) );
}

void PauseScene::resumeBackgroundMusic()
{
    musicData->resumeGameMusic();
}


void PauseScene::playBackgroundMusic()
{
    musicData->playGameMusic();
}
