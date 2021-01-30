//
//  Barrel.hpp
//  TestGame
//
//  Created by Madji on 11.05.19.
//

#ifndef Barrel_hpp
#define Barrel_hpp

#pragma once
#include <stdio.h>
#include "cocos2d.h"
#include <vector>
#include "Shark.hpp"
#include "Definitions.hpp"
#include "GameScene.hpp"
#include "Bubble.hpp"

class GameScene;

using namespace cocos2d;

class Barrel : public Sprite
{
private:
    
    GameScene       *scene;
    Size            visibleSize;
    Vec2            origin;
    Sprite          *barrel;
    Bubble          *bubble;
    PhysicsBody     *barrelBody;
    Vector<Sprite*> barrelsVector;
    RepeatForever   *rotateForeverAction;
    RotateBy        *rotateByDeg;
    int             sizeOfBarrelsVector;
    int             getRandomIndexOfBarrelsVector;
    int             barrelStartPositionX;
    int             barrelStartPositionY;
    int             barrelRotationDirection;
    int             barrelRotationSpeed;
    
    void            pushBubble( float dt );
    bool            isBarrelOnTheGround;
    
public:
    
    void setScene( GameScene *scene );
    static Barrel *createBarrel( GameScene *scene );
    void initBarrel();
    void createPhysicsBody();
    int randomNumberBetweenTwoNumbers( int min, int max );
    int calculateSizeOfVector();
    
    void cancelRotation();
    
    void spawnBarrel( float timeMin, float timeMax );

    void fillVectorOfBarrels();
    void removeBarrel();
    
    void hitBarrel( float x, float y );
    
    void update( float dt );

};

#endif /* Barrel_hpp */
