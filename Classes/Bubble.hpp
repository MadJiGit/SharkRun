//
//  Bubble.hpp
//  TestGame
//
//  Created by Madji on 11.05.19.
//

#ifndef Bubble_hpp
#define Bubble_hpp

#pragma once
#include <stdio.h>
#include "cocos2d.h"
#include "Definitions.hpp"
#include "GameScene.hpp"

using namespace cocos2d;

class Bubble : public Sprite
{
private:
    
    Sprite              *bubble;
    
    Size                visibleSize;
    Vec2                origin;
    
    
public:
    
    static Bubble *createBubble( float x, float y, float directionX );
    void initBubble( float x, float y, float directionX );
    
    void removeBubble();
    void moveRandom();
    void pushBubble( float x, float y, float direction );
    float randomNumberBetweenTwoNumbers( float first, float second );
    int randomNumberBetweenTwoNumbers( int first, int second );
   
};

#endif /* Bubble_hpp */
