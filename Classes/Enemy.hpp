//
//  Enemy.hpp
//  TestGame
//
//  Created by Madji on 11.05.19.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#pragma once
#include <stdio.h>
#include "cocos2d.h"
#include "Definitions.hpp"
#include "GameScene.hpp"

using namespace cocos2d;

class Enemy : public Sprite
{
private:
    GameScene       *scene;
    Size            visibleSize;
    Vec2            origin;
    Sprite          *enemy;
    PhysicsBody     *enemyBody;
    Animation       *animation;
    
    Vector<SpriteFrame*> getAnimation(const char *format, int count);
    
public:
    
    void setScene( GameScene *scene );
    static Enemy *createEnemy( GameScene *scene );
    void initEnemy();
    
};

#endif /* Enemy_hpp */
