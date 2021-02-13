//
//  MainMenuScene.cpp
//  TestGame
//
//  Created by Madji on 9.05.19.
//

#include "MainMenuScene.hpp"

extern int global_var;

using namespace cocos2d;

Scene *MainMenuScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = MainMenuScene::create();
    
    scene->addChild( layer );
    
    return scene;
}


bool MainMenuScene::init()
{
    
//    log( "row 27 MainMenuScene, %d", ++global_var );
    
    if ( !Layer::init() ) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    loadMusicAndSoundEffects();
    
    setBackground();
    setStartGameLabel();
    setSettingsLabel();
    setHighScoreLabel();
    setGameButton();
    setQuestionButton();
    setFacebookButton();
    
    auto pointXLayer = ( visibleSize.width / 2 + origin.x );
    auto pointYLayer = ( visibleSize.height / 2 );
    
    auto pointXButton = ( visibleSize.width / 15 );
    auto pointYButton = ( visibleSize.height / 10 + origin.y );
    
    
    startGameLabel->setPosition( Vec2( pointXLayer, pointYLayer ) );
    highScoreLabel->setPosition( Vec2( pointXLayer + 15, startGameLabel->getPositionY() - startGameLabel->getContentSize().height * COEFFICIENT_TO_SCALE_MAIN_MENU_LABEL * OFFSET_LABEL_Y ) );
    settingsLabel->setPosition( Vec2( pointXLayer + 20, highScoreLabel->getPositionY() - highScoreLabel->getContentSize().height * COEFFICIENT_TO_SCALE_MAIN_MENU_LABEL * OFFSET_LABEL_Y ) );
   
    questionButton->setPosition( Vec2( pointXButton + ( questionButton->getContentSize().width * COEFFICIENT_TO_SCALE_MAIN_MENU_BUTTON ), pointYButton ) );
    joystickButton->setPosition( Vec2( questionButton->getPositionX() + ( joystickButton->getContentSize().width ) * COEFFICIENT_TO_SCALE_MAIN_MENU_BUTTON * OFFSET_BUTTONS_X, pointYButton ) );
    
    facebookButton->setPosition( Vec2( visibleSize.width + origin.x - pointXButton - facebookButton->getContentSize().width * COEFFICIENT_TO_SCALE_MAIN_MENU_BUTTON, pointYButton ) );
    
    menu = Menu::create( startGameLabel, highScoreLabel, settingsLabel, nullptr );
    menu->setPosition( Point::ZERO );
    
    this->addChild( menu, 1);
    this->addChild( background, - 10 );
    this->addChild( questionButton, 100 );
    this->addChild( joystickButton, 100 );
    this->addChild( facebookButton, 100 );
    
    return true;
    
}

void MainMenuScene::setQuestionButton()
{
    questionButton = Button::create( "question_button_mm.png" );
    questionButton->setScale( COEFFICIENT_TO_SCALE_MAIN_MENU_BUTTON );
    questionButton->setZoomScale( - 0.1f );
    questionButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                playButtonStartClick();
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                playButtonEndClick();
                break;
            default:
                break;
        }
    });
}


void MainMenuScene::setGameButton()
{
    joystickButton = Button::create( "game_button_mm.png" );
    joystickButton->setScale( COEFFICIENT_TO_SCALE_MAIN_MENU_BUTTON );
    joystickButton->setZoomScale( - 0.1f );
    joystickButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                playButtonStartClick();
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                playButtonEndClick();
                goToControlGameButton();
                break;
            default:
                break;
        }
    });
    
}

void MainMenuScene::setFacebookButton()
{
    facebookButton = Button::create( "fb_button_mm.png" );
    facebookButton->setScale( COEFFICIENT_TO_SCALE_MAIN_MENU_BUTTON );
    facebookButton->setZoomScale( - 0.1f );
    facebookButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                playButtonStartClick();
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                playButtonEndClick();
                goToFacebookButton();
                break;
            default:
                break;
        }
    });
}

void MainMenuScene::setStartGameLabel()
{
    startGameLabel = MenuItemImage::create( "start_game_label_mm.png", "start_game_label_mm_clicked.png", CC_CALLBACK_1( MainMenuScene::goToGameScene, this ) );
    startGameLabel->setScale( COEFFICIENT_TO_SCALE_MAIN_MENU_LABEL );
}

void MainMenuScene::setHighScoreLabel()
{
    highScoreLabel = MenuItemImage::create( "highscore_label_mm.png", "highscore_label_mm_clicked.png", CC_CALLBACK_1( MainMenuScene::goToHighScoreScene, this ) );
    highScoreLabel->setScale( COEFFICIENT_TO_SCALE_MAIN_MENU_LABEL * 0.95 );
}

void MainMenuScene::setSettingsLabel()
{
    settingsLabel = MenuItemImage::create( "settings_label_mm.png", "settings_label_mm_clicked.png", CC_CALLBACK_1( MainMenuScene::goToSettingsScene, this ) );
    settingsLabel->setScale( COEFFICIENT_TO_SCALE_MAIN_MENU_LABEL * 0.95 );
}

void MainMenuScene::setBackground()
{
    background = Sprite::create( "bg_main_menu_mm.png" );
    background->setPosition( Vec2 ( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
}


void MainMenuScene::goToGameScene( Ref *sender )
{
    playChoseMenuSound();
    
    auto scene = GameScene::createScene();
    
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME_BETWEEN_SCENE, scene ) );
}

void MainMenuScene::goToHighScoreScene( Ref *sender )
{
    playChoseMenuSound();
}

void MainMenuScene::goToSettingsScene( Ref *sender )
{
    playChoseMenuSound();
    auto scene = SettingsScene::createScene();

    Director::getInstance( )->pushScene( TransitionFade::create( TRANSITION_TIME_BETWEEN_SCENE, scene ) );
}

void MainMenuScene::goToQuestionButton()
{
    CCLOG("question");
}

void MainMenuScene::goToControlGameButton()
{
    
    CCLOG("joystick");
//    auto scene = GameScene::createScene();
//
//    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME_BETWEEN_SCENE, scene ) );
}

void MainMenuScene::goToFacebookButton()
{
    
    CCLOG("facebook");
//    auto scene = GameScene::createScene();
//
//    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME_BETWEEN_SCENE, scene ) );
}


void MainMenuScene::loadMusicAndSoundEffects()
{
//    log("row 85 MainMenuScene::loadMusicAndSoundEffects" );
    musicData = MusicData::getMusicData();
}

void MainMenuScene::playBackgroundMusic()
{
//    log("row 91 MainMenuScene::playBackgroundMusic" );
    //    musicData->playGameMusic();
}

void MainMenuScene::playChoseMenuSound()
{
//    log("row 97 MainMenuScene::playChoseMenuSound" );
    musicData->playChoseMenuSound();
}

void MainMenuScene::playButtonStartClick()
{
    musicData->playButtonStartClickSound();
}
void MainMenuScene::playButtonEndClick()
{
    musicData->playButtonEndClickSound();
}

