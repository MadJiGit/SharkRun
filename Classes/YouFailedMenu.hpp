//
//  YouFailedScene.hpp
//  TestGame
//
//  Created by Madji on 9.05.19.
//

#ifndef YouFailedScene_hpp
#define YouFailedScene_hpp

#pragma once

#include <stdio.h>
#include "cocos2d.h"
#include "MainMenuScene.hpp"
#include "GameScene.hpp"
#include "ui/CocosGUI.h"
#include "MusicData.hpp"
#include "GameData.hpp"

class GameData;
using namespace cocos2d;

class YouFailedMenu : public Sprite
{
private:
    
    GameScene           *scene;
    Size                visibleSize;
    Vec2                origin;
    
    Label               *gameTimerLabel, *gameScoreLabel;
    
    MusicData           *_musicData;
    GameData            *_gameData;
    
//    MenuItemImage       *pauseButton, *retryButton, *exitButton;
    cocos2d::ui::Button *exitButton, *retryButton;
    MenuItemLabel       *gameTimer, *gameScore;
    Sprite              *sceneLabel, *sceneBg;
    
    Menu                *sceneMenu;
    
    
    int                 sec;
    int                 min;
    int                 score;
    bool                initFailedMenu();
    void                loadData();
    
    void                playButtonStartClick();
    void                playButtonEndClick();
    void                goToPlayAgain();
    void                goToGameOver();
    void                goToRetryTestScene();
    void                goToGameOverScene();
    int                 getGameTimerSeconds();
    int                 getGameTimerMinutes();
    int                 getGameScore();
    void                fadeOutSprites();
    void                deleteSprites();
    
public:
    
    static YouFailedMenu *createMenu( GameScene *scene );
    void setScene( GameScene *scene );
    
    void createFailedMenu();
    void setVisible();
    void setInvisible();
    void removeMenu();
    
    virtual void onExit();
    
    
//    CREATE_FUNC( YouFailedMenu );
};

#endif /* YouFailedScene_hpp */
