//
//  UI.hpp
//  TestGame
//
//  Created by Madji on 9.05.19.
//

#ifndef UI_hpp
#define UI_hpp

#pragma once
#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Definitions.hpp"
#include "GameScene.hpp"
#include "Shark.hpp"
#include "GameData.hpp"
#include "MusicData.hpp"
#include "SharkLives.hpp"

class GameScene;
class SharkLives;
class GameData;
class MusicData;

using namespace cocos2d;

class UI : public Sprite
{

private:
    
    GameScene           *scene;
    Size                visibleSize;
    Size                frameSize;
    Vec2                origin;
    PhysicsBody         *edgeBody;
    
    GameData            *_gameData;
    MusicData           *_musicData;
    SharkLives          *sharkLives;
    
//    Sprite              *ui, *bgTest,
//                        *bg00, *bg40,
//                        *bg10, *bg20, *bg30,
//                        *bg11, *bg21, *bg31,
//                        *bg12, *bg22, *bg32;
    
    time_t              now;
    long                tempTime;
    
    
    Label               *gameScoreLabel, *gameTimerLabel, *failedTimerLabel, *failedScoreLabel, *levelLabel;
    
    __String            *tempScore, *tempTimer, *tempLevelNumber;

    cocos2d::ui::Button *pauseButton;
    
    int                 levelNumber;
    int                 gameScore;
    int                 earnedStars;
    int                 fishCounter;
    int                 currentSharkLifes;
    bool                firstStar = false;
    bool                secondStar = false;
    bool                thirdStar = false;
    
    
    void                setUI();
    void                createEdgeBody();
    
    void                setLevelLabel();
    void                displayLevelNumber();
    void                setGameTimerLabel();
    void                displayGameTimer();
    void                setGameScoreLabel();
    void                displayGameScore();
    
    void                playEarnStarSound();
    void                displayAdditionalSharkLives();
    
    void                setPauseButton();
    void                goToPauseScene( Ref *sender );
    void                playButtonStartClick();
    void                playButtonEndClick();
    void                pauseBackgroundMusic();
    
public:
    
    void setScene( GameScene *scene );
    static UI   *createUI( GameScene *scene );
    virtual bool        init();
    
    
    void                updateGameTimer( float dt );
    void                startTimer();
    void                stopTimer();
    void                setGameTimerToZero();
    void                setGameTimerToInitValue();
    int                 getGameTimerCounter();
    int                 getGameTimerSeconds();
    int                 getGameTimerMinutes();
    
    int                 getFishCounter();
    void                setFishCounter( int fishes );
    void                increaseFishCounter();
    
    void                setScoreCounterToZero();
    void                addPointsToGameScore( int points );
    int                 getGameScoreCounter();
    
    int                 getEarnedStars();
    void                displayEarnedStars( int stars );
    void                updateEarnedStars();
    
    void                update( float dt );
    
    int                 getCurrentSharkLifes();
    void                increaseSharkLives();
    void                decreaseSharkLives();
    
    bool                checkCanPlayBG();
    
    void                saveUserData();
    void                setPauseButtonCondition( bool condition );
    
    
    
};

#endif /* UI_hpp */
