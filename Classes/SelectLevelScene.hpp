//
//  SelectLevelScene.hpp
//  TestGame
//
//  Created by Madji on 9.05.19.
//

#ifndef SelectLevelScene_hpp
#define SelectLevelScene_hpp

#pragma once

#include <stdio.h>
#include "cocos2d.h"
#include "MainMenuScene.hpp"
#include "GameScene.hpp"
#include "SimpleSlider.h"
#include "MusicData.hpp"
#include "UserData.hpp"
#include "GameData.hpp"

#include "ui/CocosGUI.h"

class GameData;
class UserData;
struct dataStruct;

using namespace cocos2d;

class SelectLevelScene : public Layer
{
private:
    
    GameScene       *gameScene;
    Size            visibleSize;
    Vec2            origin;

    
    Sprite          *background, *menuLayer,  *oneStar, *twoStars, *threeStars, *threeStars_4, *oneStar_5, *twoStars_6;
    
    Menu            *menu;
    Button          *backButton, *leftButton, *rightButton;
    MenuItemImage   *emptyLevel, *lockedLevel, *testLevel_1, *testLevel_2, *testLevel_3, *testLevel_4, *testLevel_5, *testLevel_6;
    
    std::vector<cocos2d::MenuItemImage*> singleScreenLevels;
    MenuItemImage   *t_one_number, *t_double_number, *t_stars;
    
    int             numberOfLeftUpperLevel, numberOfCurrentPlayedLevel, maxLevelNumber, maxLevelPlayed;
    
    /* Data */
    GameData        *gameData;
    MusicData       *musicData;
    
    /* from GameData */
    void            loadGameData();
    void            loadCurrentLevelNumberFromGameData();
    void            loadLevelsStatsFromDbByLevelNumber( int number );
    void            loadEarnedStars( int level );
    bool            isTheLevelUnlocked( int level );
    void            setCurrentLevel(int number);
    int             getCurrentLevel();
    void            loadMaxLevelNubmer();
    void            loadMaxPlayedLevel();
    
    /* UserData */
    void            loadUserDataFromSelectedLevel( int level );

    void            loadMusicAndSoundEffects();
    
    void            setBackground();
    void            setStars();
    void            setButtons();
    void            setLockedLevel( int number );
    void            setUnlockedLevel( MenuItemImage *testLevelNum, int levelNumber );
    void            setLevelImageFirstNumber( int number );
    void            setLevelImageSecondNumber( int number );
    void            setLevelImageStars( int levelNumber );
    void            loadCurrentSix( int number );
    void            loadPreviousSix( int number );
    void            loadNextSix( int number );
    void            goToMainMenu();
    void            goBackToInvokeScene( Ref *sender );
    
    void            goToSelectedLevelScene();
    void            goToLevel( int number );
    bool            levelStats_isUnlocked;
    int             levelStats_levelNumber;
    int             levelStats_stars;
    int             levelStats_fishEaten;
    int             levelStats_score;
    int             levelStats_playTime;
    
    void            playButtonStartClick();
    void            playButtonEndClick();
    void            playChoseMenuSound();
    void            playChoseMenuSoundStart();
    void            playChoseMenuSoundEnd();
    
    void            checkButtonsStatus( int currentLevelNumber );
    
public:
    
    static Scene    *createScene();
    
    virtual bool    init();
    
    bool            isLevelUpdated = false;
    
    void            removeMenu();
    void            showSixLevels(int firstLevelNumber);
    
    CREATE_FUNC( SelectLevelScene );
};

#endif /* SelectLevelScene_hpp */
