//
//  GameScene.hpp
//  TestGame
//
//  Created by Madji on 9.05.19.
//

#ifndef GameScene_hpp
#define GameScene_hpp

#pragma once
#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
#include "PhysicsShapeCache.hpp"
#include "Definitions.hpp"
#include "Shark.hpp"
#include "Barrel.hpp"
#include "Explosion.hpp"
#include "Enemy.hpp"
#include "Fish.hpp"
#include "GameOverScene.hpp"
#include "Mine.hpp"
#include "PauseScene.hpp"
#include "YouFailedMenu.hpp"
#include "SettingsScene.hpp"
#include "Levels.hpp"
#include "UserData.hpp"
#include "UI.hpp"
#include "GameData.hpp"
#include "LevelCompleteScene.hpp"


class Shark;
class Barrel;
class Explosion;
class Enemy;
class Fish;
class Mine;
class PauseScene;
class YouFailedMenu;
class LevelCompleteScene;
class SelectLevelScene;
class SettingsScene;
class Levels;
class UserData;
class MusicData;
class UI;
class GameData;
class SharkLives;

using namespace cocos2d;
using namespace cocos2d::ui;

class GameScene : public Layer
{

private:
    
    void                SetPhysicsWorld( PhysicsWorld *world) { sceneWorld = world; };
    PhysicsWorld        *sceneWorld;
    PhysicsBody         *edgeBody;
    
    time_t              now;
    long                tempTime;
    
    Size                visibleSize;
    Vec2                origin;
    
    Sprite              *bg00,
                        *bg10, *bg20, *bg30,
                        *bg11, *bg21, *bg31,
                        *bg12, *bg22, *bg32,
                        *bg40, *bg41;
    
    Shark               *shark;
    Barrel              *barrel;
    Explosion           *explosion;
    Enemy               *enemy;
    Fish                *fish;
    Mine                *mine;
    YouFailedMenu       *failedMenu;
    SettingsScene       *settingsScene;
    UI                  *ui;
    LevelCompleteScene  *levelCompleteScene;
    SelectLevelScene    *selectLevelScene;
    
//    Button              *pauseButton;

    MusicData           *musicData;
    GameData            *gameData;
    
    std::string         playerName;

    bool                isGame = false;
    int                 levelsPlayed;
    int                 currentLevel;
    int                 timeNeedToPassLevel; // seconds
    int                 timerCountForUpdateFunction = 0;
    
    long                currentTimeInSeconds;
    
    int                 counter = 0;
    
    float               barrelSpeedMin;
    float               barrelSpeedMax;
    float               mineSpeedMin;
    float               mineSpeedMax;
    float               submarineSpeedMin;
    float               submarineSpeedMax;
    float               rocketSpeedMin;
    float               rocketSpeedMax;
    
    bool                isTheSharkDead = false;
    
    bool                playGameOrWatchAdvertise();
    
    void                loadGameData();
    void                loadMusicData();
    
    void                pushEnemies( float spawnBarrelFrequency,
                                    float spawnMineFrequency,
                                    float spawnSubmarineFrequency,
                                    float spawnRocketFrequency
                                    );
    void                pushFish( float spawnFishFrequency, float spawnHeartFrequency );
    void                spawnBarrel( float dt );
    void                spawnFish( float dt );
    void                spawnMine( float dt );
    void                sharkKilled( PhysicsBody *body);
    void                hitBarrel( PhysicsBody *body );
    void                hitMine( PhysicsBody *body );
    void                hitChain( PhysicsBody *body );
    
    void                PushExplosion();
    void                RemoveSprite( Sprite *sprite );
    
    bool                checkCanPlayGS();
    void                startTimer();
    void                loadLevelData( int levelNumber );
    void                saveUserData();
    
    void                loadMusicAndSoundEffects();
    void                playBackgroundMusic();
    void                pauseBackgroundMusic();
    void                resumeBackgroundMusic();
    void                stopBackgroundMusic();
    void                playButtonStartClick();
    void                playButtonEndClick();
    void                playEatFishSound();
    void                playEarnStarSound();
    void                playExplosionSound();
    void                playKillSharkSound();

    void                setBackground();
    void                createEdgeBody();
    void                addToGameScore( int points );
    void                barrelContact( Sprite *sprite );
    
    void                setUI();
    
    
public:
    
    static              Scene *createScene();
    void                spawnShark();
    virtual bool        init();
    
    void                watchAd();
    void                createContactListener();
    bool                onContactBegin( PhysicsContact &contact );
    void                createFailedMenu();
    void                goToYouFailedScene();
    void                retryGameLevel();
    void                goToGameOverScene();
    void                checkPassLevelConditions();
    void                goToLevelCompleteScene();
    void                update( float dt );
    
    CREATE_FUNC( GameScene );

};

#endif /* GameScene_hpp */
