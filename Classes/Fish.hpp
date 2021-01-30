//
//  Fish.hpp
//  TestGame
//
//  Created by Madji on 11.05.19.
//

#ifndef Fish_hpp
#define Fish_hpp

#pragma once
#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Definitions.hpp"
#include "GameScene.hpp"
#include "Bubble.hpp"

class Bubble;

using namespace cocos2d;

class Fish : public Sprite
{
private:
    GameScene           *scene;
    Sprite              *fish;
    PhysicsBody         *fishBody;
    Bubble              *bubble;
    
    Size                visibleSize;
    Vec2                origin;
   
    Vector<Sprite*>     fishVector;
    std::vector<int>    indexVector;
    Vec2                positionStart;
    Vec2                positionFinish;
    
    int                 sizeOfFishVector;
    int                 sizeOfIndexVector;
    int                 fishPoints;
    int                 randomFishIndex;
    
    void                pushBubble( float dt );
    float               bubbleFrequence();
    
    
public:
    
    static Fish *createFish( GameScene *scene );
    
    void setScene( GameScene *scene );
    bool initFish();
    void fillVectors();
    void removeFish();
    void createPhyicsBody();
    void hitFish( float x, float y );
    void moveRandom();
   
  
    
    int calculateSizeOfVector();
    int calcFishPoints();
    int getPoints();
};

#endif /* Fish_hpp */
