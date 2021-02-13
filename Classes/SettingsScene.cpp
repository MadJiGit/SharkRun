//
//  SettingsScene.cpp
//  TestGame
//
//  Created by Madji on 9.05.19.
//

#include "SettingsScene.hpp"
#include "PopScene.hpp"

extern int global_var;

using namespace cocos2d;

Scene *SettingsScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = SettingsScene::create();
    
    scene->addChild( layer );
    
    return scene;
}


bool SettingsScene::init( )
{
    if ( !Layer::init() ) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    loadMusicAndSoundEffects();
    playMusic();
    
    
    setBackground();
    setButtons();
    setMusicVolumeSlider();
    setSoundEffectsVolumeSlider();
    setMusicVolumeLevel();
    setSoundEffectsVolumeLevel();
    
    
    auto defaultPosX = menuLayer->getPositionX();
    auto defaultPosY = menuLayer->getPositionY();
    
    closeButton->setPosition( Vec2( defaultPosX - ( ( menuLayer->getContentSize().width ) * 0.48 ), defaultPosY - ( menuLayer->getContentSize().height / 2 ) ) );
    okButton->setPosition( Vec2( defaultPosX + ( ( menuLayer->getContentSize().width ) * 0.48 ), defaultPosY - ( menuLayer->getContentSize().height / 2 ) ) );
    
    musicVolumeSlider->setPosition( Vec2( defaultPosX, defaultPosY + musicVolumeSlider->getContentSize().height * 1.5 ) );
    percentMusicVolumeLabel->setPosition( Vec2( defaultPosX, musicVolumeSlider->getPositionY() + musicVolumeSlider->getContentSize().height + percentMusicVolumeLabel->getContentSize().height ) );
    
    percentSoundEffectsVolumeLabel->setPosition( Vec2( defaultPosX, defaultPosY - ( percentSoundEffectsVolumeLabel->getContentSize().height ) ) );
    soundEffectsVolumeSlider->setPosition( Vec2( defaultPosX, percentSoundEffectsVolumeLabel->getPositionY() - percentSoundEffectsVolumeLabel->getContentSize().height - soundEffectsVolumeSlider->getContentSize().height ) );
    
//    closeButton->setPosition( Vec2( defaultPosX - ( ( menuLayer->getContentSize().width * SETTINGS_MENU_LAYER_SCALE ) / 2 ), defaultPosY - ( menuLayer->getContentSize().height * SETTINGS_MENU_LAYER_SCALE / 2 ) ) );
//    okButton->setPosition( Vec2( defaultPosX + ( ( menuLayer->getContentSize().width * SETTINGS_MENU_LAYER_SCALE ) / 2 ), defaultPosY - ( menuLayer->getContentSize().height * SETTINGS_MENU_LAYER_SCALE / 2 ) ) );
//
//    musicVolumeSlider->setPosition( Vec2( defaultPosX, defaultPosY + musicVolumeSlider->getContentSize().height * SETTINGS_MENU_SLIDER_SCALE * 1.5 ) );
//    percentMusicVolumeLabel->setPosition( Vec2( defaultPosX, musicVolumeSlider->getPositionY() + musicVolumeSlider->getContentSize().height * SETTINGS_MENU_SLIDER_SCALE + percentMusicVolumeLabel->getContentSize().height * SETTINGS_MENU_SLIDER_SCALE ) );
//
//    percentSoundEffectsVolumeLabel->setPosition( Vec2( defaultPosX, defaultPosY - ( percentSoundEffectsVolumeLabel->getContentSize().height * SETTINGS_MENU_SLIDER_SCALE ) ) );
//    soundEffectsVolumeSlider->setPosition( Vec2( defaultPosX, percentSoundEffectsVolumeLabel->getPositionY() - percentSoundEffectsVolumeLabel->getContentSize().height * SETTINGS_MENU_SLIDER_SCALE - soundEffectsVolumeSlider->getContentSize().height * SETTINGS_MENU_SLIDER_SCALE  ) );

    
    this->addChild( background, - 3 );
    this->addChild( menuLayer, - 2 );
    this->addChild( okButton, 10 );
    this->addChild( closeButton, 10 );
    this->addChild( percentSoundEffectsVolumeLabel , 10 );
    this->addChild( percentMusicVolumeLabel , 10 );
    this->addChild( musicVolumeSlider, 20 );
    this->addChild( soundEffectsVolumeSlider, 20 );
    
    
    return true;
    
}

void SettingsScene::loadMusicAndSoundEffects()
{
    musicData = MusicData::getMusicData();
}

void SettingsScene::playMusic()
{
    if ( false == musicData->returnIsGameMusicIsRunning() )
    {
        musicData->playGameMusic();
    }
    else
    {
        musicData->resumeGameMusic();
    }
}

void SettingsScene::setMusicVolumeSlider()
{
    musicVolumeSlider = Slider::create();
    musicVolumeSlider->loadBarTexture( "slider_empty_SM.png" );
    musicVolumeSlider->loadSlidBallTextures( "slider_button_SM.png" );
    musicVolumeSlider->loadProgressBarTexture( "slider_full_SM.png" );
    musicVolumeSlider->setPercent( musicData->getTemporaryMusicLevel() * 100 );
    musicVolumeSlider->setMaxPercent( 100 );
    musicVolumeSlider->setScale9Enabled( true );
    
    musicVolumeSlider->addTouchEventListener( [&]( Ref* sender, Widget::TouchEventType type ){
        switch ( type )
        {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                schedule( schedule_selector( SettingsScene::updateMusicVolumeLevel ) );
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                unschedule( schedule_selector( SettingsScene::updateMusicVolumeLevel ) );
                break;
            default:
                break;
        }
    });
}

void SettingsScene::setSoundEffectsVolumeSlider()
{
    soundEffectsVolumeSlider = Slider::create();
    soundEffectsVolumeSlider->loadBarTexture( "slider_empty_SM.png" );
    soundEffectsVolumeSlider->loadSlidBallTextures( "slider_button_SM.png" );
    soundEffectsVolumeSlider->loadProgressBarTexture( "slider_full_SM.png" );
    soundEffectsVolumeSlider->setPercent( musicData->getTemporaryEffectsLevel() * 100 );
    soundEffectsVolumeSlider->setMaxPercent( 100 );
    
    soundEffectsVolumeSlider->addTouchEventListener([&] (Ref* sender, Widget::TouchEventType type ){
        switch ( type )
        {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                schedule( schedule_selector( SettingsScene::updateEffectsVolumeLevel ) );
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                unschedule( schedule_selector( SettingsScene::updateEffectsVolumeLevel ) );
                break;
            case cocos2d::ui::Widget::TouchEventType::MOVED:
                break;
            default:
                break;
        }
    });
}

void SettingsScene::updateMusicVolumeLevel( float dt )
{
    displayMusicVolumeLevel( musicVolumeSlider->getPercent() );
    musicData->setGameMusicLevel( musicVolumeSlider->getPercent() / 100.0f );
}

void SettingsScene::updateEffectsVolumeLevel( float dt )
{
    displaySoundEffectsVolumeLevel( soundEffectsVolumeSlider->getPercent() );
    musicData->setGameEffectsLevel( soundEffectsVolumeSlider->getPercent() / 100.0f );
}

void SettingsScene::setButtons()
{
    okButton = Button::create( "ok_button_SM.png" );
    closeButton = Button::create( "close_button_SM.png" );
    okButton->setZoomScale( - 0.1f );
    closeButton->setZoomScale( - 0.1f );
    
    okButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                playButtonStartClick();
                saveSettingsScene( this );
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                playButtonEndClick();
                break;
            default:
                break;
        }
    });
    
    closeButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                playButtonStartClick();
                exitSettingsScene( this );
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                playButtonEndClick();
                break;
            default:
                break;
        }
    });
}

void SettingsScene::setBackground()
{
    background = Sprite::create( "beach_bg_all.png" );
    background->setPosition( Point ( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    
    menuLayer = Sprite::create( "settings_menu_SM.png" );
    menuLayer->setPosition( Point ( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 80 ) );

}

void SettingsScene::setSoundEffectsVolumeLevel()
{
    percentSoundEffectsVolumeLabel = Label::createWithTTF( ( __String::createWithFormat( "Sounds %d", soundEffectsVolumeSlider->getPercent() )->getCString() ), FONT , visibleSize.height * SCORE_FONT_SIZE );
    percentSoundEffectsVolumeLabel->setColor( Color3B::BLACK );
}

void SettingsScene::displaySoundEffectsVolumeLevel( int level )
{
    percentSoundEffectsVolumeLabel->setString(__String::createWithFormat( "Sounds %d", level )->getCString() );
}

void SettingsScene::setMusicVolumeLevel()
{
    percentMusicVolumeLabel = Label::createWithTTF( ( __String::createWithFormat( "Music %d", musicVolumeSlider->getPercent() )->getCString() ), FONT , visibleSize.height * SCORE_FONT_SIZE );
    percentMusicVolumeLabel->setColor( Color3B::BLACK );
}

void SettingsScene::displayMusicVolumeLevel( int level )
{
    percentMusicVolumeLabel->setString(__String::createWithFormat( "Music %d", level)->getCString() );
}

void SettingsScene::saveSettingsScene( Ref *sender )
{
    musicData->saveMusicLevel( musicVolumeSlider->getPercent() / 100.0f );
    musicData->saveEffectsLevel( soundEffectsVolumeSlider->getPercent() / 100.0f );
//    pauseGameMusic();
//    Director::getInstance()->popScene();
    cocos2d::Director::getInstance()->pushScene(
             pop_scene_with<cocos2d::TransitionFlipX>::create(TRANSITION_TIME_BETWEEN_SCENE, cocos2d::TransitionScene::Orientation::RIGHT_OVER)
        );
}


void SettingsScene::exitSettingsScene( Ref *sender )
{
//    musicData->pauseGameMusic();
//    Director::getInstance()->popScene();
//    cocos2d::Director::getInstance()->pushScene(
//                                                pop_scene_with<cocos2d::TransitionFlipX>::create(TRANSITION_TIME_BETWEEN_SCENE, cocos2d::TransitionScene::Orientation::RIGHT_OVER)
    
    cocos2d::Director::getInstance()->pushScene(
                                                pop_scene_with<cocos2d::TransitionFlipX>::create(TRANSITION_TIME_BETWEEN_SCENE, cocos2d::TransitionScene::Orientation::RIGHT_OVER)
                                                
    );
}

void SettingsScene::playButtonStartClick()
{
    musicData->playButtonStartClickSound();
}

void SettingsScene::playButtonEndClick()
{
    musicData->playButtonEndClickSound();
}

void SettingsScene::pauseGameMusic()
{
//    musicData->pauseGameMusic();
}

void SettingsScene::removeMenu()
{
    this->removeChild( background );
    this->removeChild( menuLayer );
    this->removeChild( menu );
    this->removeChild( closeButton );
    this->removeChild( okButton );
    this->removeChild( musicVolumeLevelTextLabel );
    this->removeChild( soundEffectsVolumeLevelTextLabel );
    this->removeChild( percentMusicVolumeLabel );
    this->removeChild( percentSoundEffectsVolumeLabel );
    this->removeChild( musicVolumeSlider );
    this->removeChild( soundEffectsVolumeSlider );
}
