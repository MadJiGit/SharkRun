//
//  Fish.cpp
//  TestGame
//
//  Created by Madji on 11.05.19.
//

#include "Fish.hpp"
#include <vector>

Fish *Fish::createFish( GameScene *scene )
{
    Fish  *sprite;
    sprite = new Fish();
    
    if ( sprite && sprite->initWithFile( "star_fish_yellow.png" ) ) {
        sprite->setScene( scene );
        sprite->initFish();
        
        return sprite;
    }
    
    CC_SAFE_DELETE( sprite );
    
    return sprite = nullptr;
}

void Fish::setScene( GameScene *scene )
{
    this->scene = scene;
}

bool Fish::initFish()
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    fillVectors();
    sizeOfFishVector = (int)fishVector.size();
    sizeOfIndexVector = (int)indexVector.size();
    
    auto randomIndexFirst = RandomHelper::random_int( 0, sizeOfIndexVector - 1);
    auto randomIndexSecond = indexVector.at( randomIndexFirst );
    randomFishIndex = RandomHelper::random_int( 0, randomIndexSecond - 1 );
    auto randomFish = fishVector.at( randomFishIndex );
    
    fishPoints = calcFishPoints( );
//    fishPoints = calcFishPoints( randomFishIndex );
    
    this->setSpriteFrame( randomFish->getSpriteFrame() );
    this->setScale( FISH_SCALE_PARAM );
    
//    int ranNum = RandomHelper::random_int( 0, (int)visibleSize.height );
//    float rndValue = (((float)arc4random()/0x100000000)*visibleSize.height);
//    float ran = ( ranNum * rndValue ) / 100;
    
    
    if ( randomIndexSecond % 3 == 0 && randomIndexSecond % 2 == 0)
    {
//        this->scaleX = -1;
        auto x = this->getScaleX();
        auto y = this->getScaleY();
        this->setScale( - x, y );
        positionStart = Vec2( 0 - origin.x, ( ( ( float ) arc4random() / 0x100000000 ) * visibleSize.height ) );
        positionFinish = Vec2( visibleSize.width + origin.x, ( ( ( float ) arc4random() / 0x100000000 ) * visibleSize.height ) );
    }
    else
    {
        positionStart = Vec2( visibleSize.width + origin.x, ( ( ( float ) arc4random() / 0x100000000 ) * visibleSize.height ) );
        positionFinish = Vec2( 0 - origin.x, ( ( ( float ) arc4random() / 0x100000000 ) * visibleSize.height ) );
    }

    
    this->setPosition( positionStart );
    
    auto timeToMove = RandomHelper::random_int( TIME_FISH_MOVE_MIN, TIME_FISH_MOVE_MAX );
    
    createPhyicsBody();
    // tag for contact begin method
    this->setTag( 88 );
    auto randomSceneTag = RandomHelper::random_int( FISH_SCENE_TAG_MIN, FISH_SCENE_TAG_MAX );
    
    scene->addChild( this, randomSceneTag );
    
    auto move = MoveTo::create( timeToMove, positionFinish );
    auto seq = Sequence::create( move, RemoveSelf::create(), nullptr );
    
    this->runAction( seq );
    
//    this->moveRandom();
    
//    float freq = bubbleFrequence();
//    this->schedule( schedule_selector( Fish::pushBubble ), freq );
    
    return true;
    
}

float Fish::bubbleFrequence()
{
    auto ranNum = RandomHelper::random_int( 1, 3 );
//    log( "row 98 FISH neshto %d", ranNum );
    auto neshto = 1 + ( ( float ) arc4random() / 0x100000000 ) * ranNum ;
    
//    log( "row 98 FISH neshto %f", neshto );
//    return ( ( float ) arc4random() / 0x100000000 ) * RandomHelper::random_int( 1, 3 ) ;
    return neshto;
}

void Fish::pushBubble( float dt )
{
//    log("row 111 bubble X %f Y %f", this->getPositionX(), this->getPositionY());
    bubble = Bubble::createBubble( this->getPositionX(), this->getPositionY(), 0 );
    this->addChild( bubble, 1000 );
}

int Fish::getPoints()
{
    return fishPoints;
}

int Fish::calcFishPoints( )
{
    int points = 0;
    
    if ( randomFishIndex > 5 )
    {
        points = 30;
    }
    else if ( randomFishIndex > 2 )
    {
        points = 20;
    }
    else
    {
        points = 10;
    }
    
    return points;
}

void Fish::createPhyicsBody()
{
    fishBody = PhysicsBody::createBox( this->getContentSize() * FISH_PHYSIC_PARAM );
    fishBody->setDynamic( false );
    fishBody->setRotationEnable( false );
    fishBody->setCategoryBitmask( CATEGORY_MASK_FISH );
    fishBody->setCollisionBitmask( COLLISION_MASK_FISH );
    fishBody->setContactTestBitmask( CONTACT_MASK_FISH );
    this->setPhysicsBody( fishBody );
}


void Fish::fillVectors()
{
    auto starFishYellow = Sprite::create( "star_fish_yellow.png" );
    auto starFishGreen = Sprite::create( "star_fish_green.png" );
    auto starFishRed = Sprite::create( "star_fish_red.png" );
    auto smallFishGreen = Sprite::create( "small_fish_green_left.png" );
    auto smallFishYellow = Sprite::create( "small_fish_yellow_left.png" );
    auto smallFishRed = Sprite::create( "small_fish_red_left.png" );
    auto mediumFishBrown = Sprite::create( "medium_fish_brown_left.png" );
    auto mediumFishPurple = Sprite::create( "medium_fish_purple_left.png" );
    auto mediumFishGreen = Sprite::create( "medium_fish_green_left.png" );
    
    
    fishVector.pushBack( smallFishRed );
    fishVector.pushBack( smallFishGreen );
    fishVector.pushBack( smallFishYellow );
    fishVector.pushBack( mediumFishBrown );
    fishVector.pushBack( mediumFishGreen );
    fishVector.pushBack( mediumFishPurple );
    fishVector.pushBack( starFishYellow );
    fishVector.pushBack( starFishGreen );
    fishVector.pushBack( starFishRed );
    
    indexVector = {3, 3, 3, 6, 6, 9};
}


void Fish::moveRandom()
{
    auto randomPoint = Vec2( rand() % 500, rand() % 1000 );

    auto moveTo = MoveTo::create( rand() % 5 + 1, randomPoint );
    auto delayTime = DelayTime::create( 0.5 );
    auto moveAgainFunc = CallFunc::create( [=](){ moveRandom(); } );

    auto actions = Sequence::create( moveTo, delayTime, moveAgainFunc, nullptr );

    this->runAction( actions );
}

void Fish::removeFish()
{
    RemoveSelf::create();
}
