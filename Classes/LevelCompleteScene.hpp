//
//  LevelCompleteScene.hpp
//  TestGame
//
//  Created by Madji on 9.05.19.
//

#ifndef LevelCompleteScene_hpp
#define LevelCompleteScene_hpp

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

class LevelCompleteScene : public Sprite
{
private:
    
    GameScene           *scene;
    Size                visibleSize;
    Vec2                origin;
    
    Label               *gameScoreLabel, *fishEatenLabel, *gameTimerLabel;
    
    MusicData           *musicData;
    GameData            *gameData;
    
    cocos2d::ui::Button *retryButton, *menuButton, *playButton;
    MenuItemLabel       *gameScore, *fishEaten, *gameTimer;
    Sprite              *oneStar, *sceneBg, *sceneLabel;
//    Sprite              *twoStars, *threeStars;
    
    Menu                *sceneMenu;
    
    
    int                 sec;
    int                 min;
    int                 score;
    int                 fishes;
    int                 stars;
    bool                init();
    
    void                loadGameData();
    void                loadMusicData();
    
    void                playButtonStartClick();
    void                playButtonEndClick();
    void                stopGameMusic();
    void                pauseGameMusic();
    void                goToPlayAgain();
    void                goToGameOver();
    void                goToRetryScene();
    void                goToGameOverScene();
    void                goToNextLevel();
    int                 getGameTimerSeconds();
    int                 getGameTimerMinutes();
    int                 getGameScore();
    int                 getFishEaten();
    int                 getStarsEarned();
    void                setStarsEarned();
    void                fadeOutSprites();
    void                deleteSprites();
    void                setStarsVisible();
    
    void                createMenu();
    void                createButtons();
    void                createStars( int stars );
    
public:
    
    static              LevelCompleteScene *createMenu( GameScene *scene );
    void                setScene( GameScene *scene );
    
    void                createLevelCompleteScene();
    void                setVisible();
    void                setInvisible();
    void                removeScene();
    
    virtual void onExit();
    
    
//    CREATE_FUNC( LevelCompleteScene );
};

#endif /* LevelCompleteScene_hpp */
