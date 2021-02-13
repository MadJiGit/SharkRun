//
//  WelcomeScene.hpp
//  TestGame
//
//  Created by Madji on 9.05.19.
//

#ifndef WelcomeScene_hpp
#define WelcomeScene_hpp

#pragma once

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
#include "Definitions.hpp"
#include "MainMenuScene.hpp"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "UserData.hpp"
#include "AudioEngine.h"
#include "MusicData.hpp"
#include "GameData.hpp"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocos2d::experimental;

class WelcomeScene : public Layer, public EditBoxDelegate
{
    
private:
    
    Size            visibleSize;
    Vec2            origin;
    Sprite          *logo, *background;
    
    MenuItemImage   *playButton, *closeButton;
    Sprite          *playButtonStart, *closeButtonStart;
    
    Menu            *menu;
    
    UserData        *_userData;
    dataStruct      *_dataStruct;
    MusicData       *_musicData;
    GameData        *gameData;
    
    
    TextField       *textField;
    EditBox         *editUsername;
    
    DelayTime       *delayTime;
    
    std::string     username;
    
    int             textSize;
    int             textBoxSizeX;
    int             textBoxSizeY;
    
//    SimpleAudioEngine   *gameMusic;

    void loadMusicAndSoundEffects();
    void playButtonStartClick();
    void playButtonEndClick();
    void playChoseMenuSound();
    
    void loadBg();
    void logoGoUp();
    void showButtons();
    void showText();
    void activateButtons();
    
    void checkIfUserExist();
    void showEnterUsernameScreen();
    void loadButtons();
    void setUsername();
    
    void saveUsername();
    void showOkButton();
    
    void goToMainMenuScene();
    void exitGameScene();
    

    
public:
    
    virtual void editBoxEditigDidBegin( EditBox *editBox );
    virtual void editBoxEditigDidEnd( EditBox *editBox );
    virtual void editBoxTextChanged( EditBox *editBox, const std::string &text );
    virtual void editBoxReturn( EditBox *editBox );
    
    static Scene *createScene();
    
    virtual bool init();
    
    CREATE_FUNC( WelcomeScene );
    
};

#endif /* WelcomeScene_hpp */
