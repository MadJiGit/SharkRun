//
//  WelcomeScene.cpp
//  TestGame
//
//  Created by Madji on 9.05.19.
//

#include "WelcomeScene.hpp"
#include "Definitions.hpp"

extern int global_var;

Scene *WelcomeScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = WelcomeScene::create();
    
    scene->addChild( layer );
    
    return scene;
}


bool WelcomeScene::init( )
{
    
    if ( !Layer::init() ) {
        return false;
    }
    
    DEBUG_INFO;
    loadGameData();

    loadMusicAndSoundEffects();
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    textSize = visibleSize.height / 13;
    textBoxSizeX = visibleSize.width / 4;
    textBoxSizeY = visibleSize.height / 12;
    
    delayTime = DelayTime::create( DEFAULT_DELAY_TIME );
    
    auto callBG = CallFunc::create( CC_CALLBACK_0( WelcomeScene::loadBg, this ) );
    auto seq = Sequence::create( callBG, delayTime, nullptr );
    this->runAction( seq );
    
    return true;
}

void WelcomeScene::loadGameData()
{
    gameData = GameData::getGameData();
}

void WelcomeScene::loadBg()
{
    this->logo = Sprite::create( "logo.png" );
//    this->background = Sprite::create( "welcome_bg_1.png" );
    this->background = Sprite::create( "beach_bg_all.png" );
//    this->background->setScale( COEFFICIENT_TO_SCALE_BACKGROUND_WELCOME_SCENE );
    
    this->logo->setPosition( Point ( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    this->background->setPosition( Point ( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    
    this->background->setOpacity( 0 );
    this->logo->setOpacity( 0 );
    this->addChild( this->background, - 2 );
    this->addChild( this->logo, - 1 );
    auto fadeIn = FadeIn::create( DEFAULT_DELAY_TIME );
    
    auto callLogo = CallFunc::create( CC_CALLBACK_0( WelcomeScene::logoGoUp, this ) );
    
    auto seq = Sequence::create( fadeIn, nullptr );
    auto seq2 = Sequence::create( delayTime, fadeIn, delayTime, callLogo, nullptr );
    
    this->background->runAction( seq );
    this->logo->runAction( seq2 );
   
}

void WelcomeScene::logoGoUp()
{
    auto scaleLogo = ScaleTo::create( TIME_TO_SCALE_LOGO, COEFFICIENT_TO_SCALE_LOGO );
    auto position = Vec2( visibleSize.width / 2 + origin.x, ( visibleSize.height / 2 + origin.y + ( visibleSize.height / 5 ) ) );
    auto moveUp = MoveTo::create( TIME_TO_MOVE_LOGO, position );
    auto mySpawn = Spawn::createWithTwoActions( moveUp, scaleLogo );
    
//    auto showWelcomeText = CallFunc::create( CC_CALLBACK_0( WelcomeScene::showText, this ) );
    auto checkUser = CallFunc::create( CC_CALLBACK_0( WelcomeScene::checkIfUserExist, this ) );
    
//    auto move = Sequence::create( mySpawn, delayTime, showWelcomeText, delayTime, checkUser, nullptr );
    auto move = Sequence::create( mySpawn, delayTime, checkUser, nullptr );
    this->logo->runAction( move );
    
}

/*
    Welcome screen TEXT if has username show it, else print just Welcome back!
 */

void WelcomeScene::showText()
{
    username = gameData->getUsername();
    std::string welcomeText = "Welcome";
    if ( 0 < strlen(username.c_str()) ) {
        welcomeText += " back, " + username;
    }
    
    welcomeText += "!";
    
    auto myLabel = Label::createWithTTF( welcomeText, FONT, textSize );
    myLabel->setColor( Color3B::BLUE );
    myLabel->setPosition( Vec2( visibleSize.width / 2 + origin.x, visibleSize.height / 3 + origin.y ) );
    myLabel->setAlignment( TextHAlignment::CENTER );
    
    this->addChild( myLabel );
    
}

/*
    If the user exists, this method checks for the existing username,
    if the username does not exist -> show a field to enter it.
 */
void WelcomeScene::checkIfUserExist()
{
    if ( false == gameData->getUserRegisterStatus() )
    {
        showEnterUsernameScreen();
    }
    else
    {
        username = gameData->getUsername();
        showText();
        loadButtons();
    }
}

void WelcomeScene::showEnterUsernameScreen()
{
    DEBUG_INFO
    editUsername = EditBox::create( Size ( textBoxSizeX, textBoxSizeY ), Scale9Sprite::create( "bg_default_yellow_1920_1080.png" ) );
    editUsername->setPosition( Vec2 ( visibleSize.width / 2 + origin.x, visibleSize.height / 3 + origin.y ) );
    editUsername->setFontSize( textSize );
    editUsername->setFontColor( Color3B::RED );
    editUsername->setPlaceHolder( "Enter Name" );
    editUsername->setFocused( true );
    editUsername->setTextHorizontalAlignment( TextHAlignment::CENTER );
    editUsername->setPlaceholderFontColor( Color3B::WHITE );
    editUsername->setMaxLength( 20 );
    
    editUsername->setReturnType( EditBox::KeyboardReturnType::DONE );
    editUsername->setInputMode( EditBox::InputMode::SINGLE_LINE );
    editUsername->setDelegate( this );
    
    this->addChild( editUsername, 500 );
    
    showOkButton();
    
}

void WelcomeScene::editBoxEditigDidBegin( EditBox *editBox )
{

}
void WelcomeScene::editBoxEditigDidEnd( EditBox *editBox )
{

}
void WelcomeScene::editBoxTextChanged( EditBox *editBox, const std::string &text )
{
    editUsername->detachWithIME();
    editBox->setTextHorizontalAlignment( TextHAlignment::CENTER );
    
    printf("%s\n", text.c_str());
    this->username = text;
}

void WelcomeScene::editBoxReturn( EditBox *editBox )
{
//    showOkButton();
}

void WelcomeScene::showOkButton()
{
    auto button = Button::create( "play_button_wm.png" );
    button->setZoomScale( - 0.1f );

    button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                playChoseMenuSound();
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                setUsername();
                break;
            default:
                break;
        }
    });

    button->setPosition( Vec2 (visibleSize.width / 2 + origin.x, editUsername->getPositionY() - button->getContentSize().height * 1.2 ) );

    this->addChild( button, 510 );
}

void WelcomeScene::setUsername()
{
    gameData->changeUsername( username );
    gameData->changeUserRegisterStatus( true );
    gameData->writeDataToUserData();
    
    goToMainMenuScene();
}

void WelcomeScene::loadButtons()
{
    auto callButton = CallFunc::create( CC_CALLBACK_0( WelcomeScene::showButtons, this ) );
    auto activeButton = CallFunc::create( CC_CALLBACK_0( WelcomeScene::activateButtons, this ) );
    
    auto seq = Sequence::create( callButton, activeButton,  nullptr );
    this->runAction( seq );
}

void WelcomeScene::showButtons()
{
    playButtonStart = Sprite::create( "play_button_wm.png" );
    closeButtonStart = Sprite::create( "close_button_wm.png" );
    playButtonStart->setScale( 0.01 );
    closeButtonStart->setScale( 0.01 );
    
    playButtonStart->setPosition( Point ( visibleSize.width / 2 + origin.x - this->playButtonStart->getContentSize().width * 0.5, ( visibleSize.height / 2 + origin.y  - ( visibleSize.height / 3 ) ) ) );
    closeButtonStart->setPosition( Point ( visibleSize.width / 2 + origin.x + this->closeButtonStart->getContentSize().width * 0.8, ( visibleSize.height / 2 + origin.y  - ( visibleSize.height / 3 ) ) ) );
    
    this->addChild( this->playButtonStart, - 1 );
    this->addChild( this->closeButtonStart, - 1 );
    
    auto scaleButtonOk = ScaleTo::create( TIME_TO_SCALE_PLAY_BUTTON, COEFFICIENT_TO_SCALE_PLAY_BUTTON );
    auto scaleButtonClose = ScaleTo::create( TIME_TO_SCALE_PLAY_BUTTON, COEFFICIENT_TO_SCALE_CLOSE_BUTTON );
    
    playButtonStart->runAction( scaleButtonOk );
    closeButtonStart->runAction( scaleButtonClose );
    
    this->removeChild( this->playButtonStart );
    this->removeChild( this->closeButtonStart );
    
}

void WelcomeScene::activateButtons()
{
    auto playButton = Button::create( "play_button_wm.png" );
    auto closeButton = Button::create( "close_button_wm.png" );
//    playButton->setScale( COEFFICIENT_TO_SCALE_PLAY_BUTTON );
//    closeButton->setScale( COEFFICIENT_TO_SCALE_CLOSE_BUTTON );
    playButton->setZoomScale( - 0.1f );
    closeButton->setZoomScale( - 0.1f );
    
    playButton->setPosition( Point ( visibleSize.width / 2 + origin.x - playButton->getContentSize().width * 0.5, ( visibleSize.height / 2 + origin.y  - ( visibleSize.height / 3 ) ) ) );
    closeButton->setPosition( Point ( visibleSize.width / 2 + origin.x + closeButton->getContentSize().width * 0.8, ( visibleSize.height / 2 + origin.y  - ( visibleSize.height / 3 ) ) ) );
    
    playButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                playButtonStartClick();
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                playButtonEndClick();
                goToMainMenuScene();
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
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                playButtonEndClick();
                exitGameScene();
                break;
            default:
                break;
        }
    });
    
    
    
    this->addChild( playButton, 510 );
    this->addChild( closeButton, 510 );
}

void WelcomeScene::goToMainMenuScene( )
{
    auto scene = MainMenuScene::createScene();
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME_BETWEEN_WELCOME_AND_MAIN_MENU_SCENES, scene ) );
}

void WelcomeScene::exitGameScene( )
{
    gameData->writeDataToUserData();
    
    Director::getInstance()->end();
    exit(TRANSITION_TIME_BETWEEN_SCENE * 3 );
}

void WelcomeScene::loadMusicAndSoundEffects()
{
    musicData = MusicData::getMusicData();
}
void WelcomeScene::playButtonStartClick()
{
    musicData->playButtonStartClickSound();
}
void WelcomeScene::playButtonEndClick()
{
    musicData->playButtonEndClickSound();
}
void WelcomeScene::playChoseMenuSound()
{
    musicData->playChoseMenuSound();
}
