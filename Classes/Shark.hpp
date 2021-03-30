//
//  Shark.hpp
//  MyCppGame-mobile
//
//  Created by Madji on 24.04.19.
//

#ifndef Shark_hpp
#define Shark_hpp

#pragma once
#include <stdio.h>
#include "cocos2d.h"
#include "GameScene.hpp"
#include "MyBodyParser.hpp"
#include "Definitions.hpp"
#include "PhysicsShapeCache.hpp"
#include "Bubble.hpp"

class Bubble;
class GameScene;

using namespace cocos2d;

class Shark : public Sprite
{
private:
    
    GameScene                   *scene;
    Size                        visibleSize;
    Vec2                        origin;
    Shark                       *shark;
    PhysicsBody                 *sharkBody;
    Animation                   *animation;
    PhysicsShapeCache           *shapeCache;
    Bubble                      *bubble;

    Vector<SpriteFrame*>        getAnimation(const char *format, int count);
    
    EventListenerTouchOneByOne  *touchListener;
    
    Vec2                        gamePosition;
    float                       sharkMoveDuration;
    int                         additionalsLifes;
    float                       _constSharkPositionX;
    float                       maxScreenSizeY;
    float                       newDistance;
    float                       groundLevel;
    float                       lastSharkGoToPosY;
    void                        pushBubble( float dt );
    void                        update( float dt );
    
public:
    
    int                         moveUpTimeCounter;
    bool                        isFalling;
    bool                        isRising;
    void                        setScene( GameScene *scene );
    static                      Shark *createShark( GameScene *scene );
    bool                        onTouchBeganShark( Touch *touch, Event *event );
    bool                        onContactBegin( PhysicsContact &contact );
    bool                        isSharkOnGamePosition;
    void                        initShark();
    void                        initAnimation();
    void                        loadMusicAndSoundEffects();
    void                        playBackgroundMusic();
    void                        moveSharkOnGamePosition( float dt );
    void                        setCollision();
    void                        createTouchListener( bool condition );
    void                        unscheduleTouchListener();
    void                        sharkMoving();
    void                        sharkHeadUp();
    void                        sharkHeadDown();
    void                        sharkHeadZero();
    void                        setSharkOnGamePositionTrue();
    void                        sharkKilled( float x, float y );
    void                        actionForCollision(float x, float y);
    void                        removeShark();
    void                        sharkStopMoving( float dt );
    
};

#endif /* Shark_hpp */
