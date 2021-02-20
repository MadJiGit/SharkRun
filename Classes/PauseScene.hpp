//
//  PauseScene.hpp
//  TestGame
//
//  Created by Madji on 9.05.19.
//

#ifndef PauseScene_hpp
#define PauseScene_hpp

#pragma once

#include <stdio.h>
#include "cocos2d.h"
#include "MainMenuScene.hpp"
#include "GameScene.hpp"
#include "SelectLevelScene.hpp"
#include "UserData.hpp"
#include "MusicData.hpp"


using namespace cocos2d;

class PauseScene : public Layer
{
private:
    
    GameScene       *gameScene;
    Size            visibleSize;
    Vec2            origin;
    
    MenuItemImage   *resumeLabel, *retryLabel, *changeLabel, *settingsLabel, *closeButton;
    
    Menu            *menu;
    
    Sprite          *background, *menuLayer;
    
    MusicData       *musicData;
    GameData        *gameData;
    
    bool            canPlay;
    
    void setBackground();
    void setMenuLayer();
    void setResumeLabel();
    void setRetryLabel();
    void setChangeLabel();
    void setSettingsLabel();
    void setCloseButton();
    
    void goToMainMenuScene( Ref *sender );
    void backToGameScene( Ref *sender );
    void goToGameScene( Ref *sender );
    void exitGameScene( Ref *sender );
    void goToSettings( Ref *sender );
    void goToChangeLevel( Ref *sender );
    
    void resumeBackgroundMusic();
    void playBackgroundMusic();
    
    
public:
    
    static Scene *createScene();
    
    virtual bool init();
    
    CREATE_FUNC( PauseScene );
};

#endif /* PauseScene_hpp */
