//
//  Barrel.cpp
//  TestGame
//
//  Created by Madji on 11.05.19.
//

#include "Barrel.hpp"
#include <vector>

Barrel *Barrel::createBarrel( GameScene *scene )
{
    Barrel  *sprite;
    sprite = new Barrel();
    
    if ( sprite && sprite->initWithFile( "barrel_grey.png" ) ) {
        sprite->setScene( scene );
        sprite->initBarrel();
        
        return sprite;
    }
    
    CC_SAFE_DELETE( sprite );
    
    return sprite = nullptr;
}

void Barrel::setScene( GameScene *scene )
{
    this->scene = scene;
}

void Barrel::initBarrel()
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    fillVectorOfBarrels();
    this->sizeOfBarrelsVector = (int)this->barrelsVector.size();
    
//    this->getRandomIndexOfBarrelsVector = randomNumberBetweenTwoNumbers( 0, this->sizeOfBarrelsVector - 1 );
    this->getRandomIndexOfBarrelsVector = RandomHelper::random_int( 0, this->sizeOfBarrelsVector - 1 );
    
    auto randomBarrel = this->barrelsVector.at( this->getRandomIndexOfBarrelsVector );
    this->setSpriteFrame( randomBarrel->getSpriteFrame() );
//    this->setScale( BARREL_SCALE_PARAM );
    
    createPhysicsBody();
    isBarrelOnTheGround = true;
    
    
    this->barrelStartPositionX = RandomHelper::random_int( MINIMUM_WIDTH_BAREL_POSITION_X, MAXIMUM_WIDTH_BAREL_POSITION_X );
    this->barrelStartPositionY = RandomHelper::random_int( MINIMUM_WIDTH_BAREL_POSITION_Y, MAXIMUM_WIDTH_BAREL_POSITION_Y );
    
    this->barrelRotationDirection = 1;
    if ( ( this->getRandomIndexOfBarrelsVector + 1 ) % 2 != 0 ) {
        barrelRotationDirection = - 1;
    }
    
//    auto barrelStartPosition = Point( ( this->barrelStartPositionX + origin.x ),
//                                     ( visibleSize.height + this->getContentSize().height + origin.y ) );
    auto barrelStartPosition = Point( ( this->barrelStartPositionX + origin.x ),
                                     ( this->barrelStartPositionY + origin.y ) );
    
    this->setPosition( barrelStartPosition );
    
    this->setTag( 99 );
    scene->addChild( this, BARREL_SCENE_TAG );
}

void Barrel::spawnBarrel( float timeMin, float timeMax )
{
    barrelRotationSpeed = RandomHelper::random_int( DEFAULT_BARREL_ROTATION_SPEED_MIN, DEFAULT_BARREL_ROTATION_SPEED_MAX );
//    log("B 83 spawn BARREL");
    rotateByDeg = RotateBy::create( barrelRotationSpeed, barrelRotationDirection * DEFAULT_BARREL_ROTATION_DEGREE );
    this->runAction( rotateByDeg );
    
    this->schedule( schedule_selector( Barrel::pushBubble ), 1.1f );
}

void Barrel::pushBubble( float dt )
{
    bubble = Bubble::createBubble( this->getPositionX(), this->getPositionY(), 0 );
    int tag = (int)this->getPositionY() % 2 ? 901 : 899;
    scene->addChild( bubble, tag );
}

void Barrel::cancelRotation()
{
//    log("B 119 cancel rotation");
    this->getPhysicsBody()->setVelocity( Vec2( 0, 0) );
    this->stopAction( rotateByDeg );
    isBarrelOnTheGround = true;
}

void Barrel::createPhysicsBody()
{
    barrelBody = PhysicsBody::createBox( this->getContentSize() * BARREL_PHYSIC_PARAM, PhysicsMaterial( 0.9, 0.0, 0.8 ) );
    
    barrelBody->setDynamic( true );
    barrelBody->setGravityEnable( false );
    barrelBody->setRotationEnable( true );
    barrelBody->setCategoryBitmask( CATEGORY_MASK_BARREL );
    barrelBody->setCollisionBitmask( COLLISION_MASK_BARREL );
    barrelBody->setContactTestBitmask( CONTACT_MASK_BARREL );
    this->setPhysicsBody( barrelBody );
}

void Barrel::fillVectorOfBarrels()
{
    auto redBarrel = Sprite::create( "barrel_red.png" );
    auto blueBarrel = Sprite::create( "barrel_blue.png" );
    auto greyBarrel = Sprite::create( "barrel_grey.png" );
    auto yellowBarrel = Sprite::create( "barrel_yellow.png" );
    
    barrelsVector.pushBack( redBarrel );
    barrelsVector.pushBack( blueBarrel );
    barrelsVector.pushBack( greyBarrel );
    barrelsVector.pushBack( yellowBarrel );

}

int Barrel::randomNumberBetweenTwoNumbers( int min, int max )
{
//    return rand( )%( ( max - min ) + 1 ) + min;
    
    return RandomHelper::random_int( min, max );
}

void Barrel::removeBarrel()
{
//    log("B 164 remove barrel here");
    this->unscheduleUpdate();
//    this->autorelease();
    this->removeFromParentAndCleanup( true );
}

void Barrel::hitBarrel( float x, float y )
{
    
    auto pos = Vec2( x, y );
    
    auto hittedBarrel = Sprite::create( "barrel_grey.png" );
    hittedBarrel->setPosition( pos );
//    hittedBarrel->setScale( BARREL_SCALE_PARAM );
    scene->addChild( hittedBarrel, 100 );
    
    auto move = MoveTo::create( 1.5, Vec2( 900, 600 ));
    auto rotate = RotateTo::create( 1.5, - 180 );
    auto scale = ScaleTo::create( 2.0, 1 );
    auto spawn = Spawn::createWithTwoActions( move, rotate );
    auto spawn2 = Spawn::createWithTwoActions( scale, spawn );
    auto seq2 = Sequence::create( spawn2, RemoveSelf::create(), nullptr );
    
    hittedBarrel->runAction( seq2 );
    
}

void Barrel::update( float dt )
{
//    log("B 191 barrel X %f Y %f", this->getPositionX(), this->getPositionY() );
    if ( isBarrelOnTheGround == true )
    {
        this->setPosition( Vec2( this->getPositionX() - SPEED_BACKGROUND_1, this->getPositionY() - 1 ) );
    }
    if ( this->getPositionY() < ( 0 - this->getContentSize().height ) ||
        this->getPositionX() < ( 0 - this->getContentSize().width ) ) {
//        log("B 197 remove barrel here");
        this->removeBarrel();
//        RemoveSelf::create();
    }
}
