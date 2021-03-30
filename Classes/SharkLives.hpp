//
//  SharkLives.hpp
//  TestGame-mobile
//
//  Created by Madji on 18.07.19.
//

#ifndef SharkLives_hpp
#define SharkLives_hpp

#pragma once
#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Definitions.hpp"
#include "GameData.hpp"
#include "UI.hpp"
#include "MusicData.hpp"

class GameData;
class UI;
class MusicData;

using namespace cocos2d;

class SharkLives : Sprite
{
private:
    
    UI                  *ui;
    GameData            *gameData;
    MusicData           *musicData;
    Sprite              *sharkLife_1, *sharkLife_2, *sharkLife_3, *sharkLife_4, *sharkLife_5;
    int                 defaultSharkLives;
    int                 currentSharkLives;
    void                getGameData();
    void                setUI( UI *ui );
    bool                init();
    
    float               defaultSharkLifePositionX;
    float               defaultSharkLifePositionY;
    
    Vector<Sprite*>     allSharkLifes;
    void                fillAllSharkLifesVector( int lives );
    int                 sizeOfSharkLifesVector;
    void                displayAdditionalsSharkLifes( int data );
    bool                isTimerIsRunning = false;
    
    long                timeFirstLifeReturn;
    long                timeSecondLifeReturn;
    long                timeThirdLifeReturn;
    long                timeFourthLifeReturn;
    long                timeFifthLifeReturn;
    
    bool                isExistFirstLife;
    bool                isExistSecondLife;
    bool                isExistThirdLife;
    bool                isExistFourthLife;
    bool                isExistFifthLife;
    
    void                playWinHeartSound();
    
    void                setCurrentSharkLives( int lives );
    
    void                manageSharkLives( int lives );
    void                checkLeftTimeForReturnLife();
    void                checkAreAllLivesAreVisible();
    void                calculateTimeToRefille();
    void                refille();
    
    Size                visibleSize;
    Vec2                origin;
    
    void                loadGameData();
    
    time_t              now;
    long                getTimeStampInSeconds();

    bool                canPlay;
    void                setCanPlayStatus( bool status );
    void                checkCurrentSharkLives();
    
    void                startTimer();
    void                stopTimer();
    void                updateSharkTimer( float dt );
    int                 timeCounter;
    
    void                setAllReturnTimes();
    
    void                saveData();
    
    int                 firstTimeLivesCounter;
    
    
public:
    
    static SharkLives   *createSharkLives( UI *ui );
    
    void                remove();
    
    int                 getCurrentSharkLives();
    void                decreaseCurrentSharkLives();
    void                increaseCurrentSharkLives();
    bool                getCanPlayStatus();
    bool                checkCanPlaySL();
    void                saveGameData();
    
};


#endif /* SharkLives_hpp */

