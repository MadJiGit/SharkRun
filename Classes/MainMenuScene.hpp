//
//  MainMenuScene.hpp
//  TestGame
//
//  Created by Madji on 9.05.19.
//

#ifndef MainMenuScene_hpp
#define MainMenuScene_hpp

#pragma once

#include <stdio.h>
#include "cocos2d.h"
#include "Definitions.hpp"
#include "GameScene.hpp"
#include "MusicData.hpp"
#include "ui/CocosGUI.h"

class MusicData;

using namespace cocos2d;

class MainMenuScene : public Layer
{
    
private:
    
    GameScene       *gameScene;
    Size            visibleSize;
    Vec2            origin;
    Sprite          *background;
    
    MenuItemImage   *startGameLabel, *highScoreLabel, *settingsLabel;
    cocos2d::ui::Button          *questionButton, *joystickButton, *facebookButton;
    
    Menu            *menu;
    
    MusicData       *_musicData;
    
    void            setBackground();
    void            setStartGameLabel();
    void            setHighScoreLabel();
    void            setSettingsLabel();
    void            setQuestionButton();
    void            setGameButton();
    void            setFacebookButton();
    
    
    void            goToGameScene( Ref *sender );
    void            goToSettingsScene( Ref *sender );
    void            goToHighScoreScene( Ref *sender );
    void            goToQuestionButton();
    void            goToFacebookButton();
    void            goToControlGameButton();
    
    void            loadMusicAndSoundEffects();
    void            playBackgroundMusic();
    void            playButtonStartClick();
    void            playButtonEndClick();
    void            playChoseMenuSound();
    
public:
    
    static Scene    *createScene();
    
    virtual bool    init();
    
    CREATE_FUNC( MainMenuScene );
    
};

#endif /* MainMenuScene_hpp */
