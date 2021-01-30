//
//  Mine.hpp
//  TestGame
//
//  Created by Madji on 11.05.19.
//

#ifndef Mine_hpp
#define Mine_hpp

#pragma once
#include <stdio.h>
#include "cocos2d.h"
#include <vector>
#include "Shark.hpp"
#include "Definitions.hpp"
#include "GameScene.hpp"

class GameScene;

using namespace cocos2d;

class Mine : public Sprite
{
private:
    
    GameScene       *scene;
    Size            visibleSize;
    Vec2            origin;
    Sprite          *mine;
    Vector<Sprite*> minesVector;
    
    int             sizeOfMineVector;
    float           mineSize;
    
public:
    
    void setScene( GameScene *scene );
    static Mine *createMine( GameScene *scene );
    void initMine();
    void createPhysicsBody();
    int randomNumberBetweenTwoNumbers( int max, int min );
    int calculateSizeOfVector();

    void fillVectorOfMine();
    void removeMine();
    
    void hitMine( float x, float y );
    
    void update( float dt );

};

#endif /* Mine_hpp */
