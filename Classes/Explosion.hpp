//
//  Explosion.hpp
//  TestGame
//
//  Created by Madji on 11.05.19.
//

#ifndef Explosion_hpp
#define Explosion_hpp

#pragma once
#include <stdio.h>
#include "cocos2d.h"
#include "Definitions.hpp"
#include "GameScene.hpp"

class GameScene;

using namespace cocos2d;

class Explosion : public Sprite
{
private:
    GameScene       *scene;
    Size            visibleSize;
    Vec2            origin;
    Sprite          *explosion;
    PhysicsBody     *explosionBody;
    Animation       *animation;
    
    Vector<SpriteFrame*> getAnimation(const char *format, int count);
    
public:
    
    void setScene( GameScene *scene );
    static Explosion *createExplosion( GameScene *scene );
    void initExplosion();
    
    void runExplosion( float x, float y );
    
    void removeExplosion();
    
};

#endif /* Explosion_hpp */
