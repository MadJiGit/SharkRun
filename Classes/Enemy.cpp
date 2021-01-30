//
//  Enemy.cpp
//  TestGame
//
//  Created by Madji on 11.05.19.
//

#include "Enemy.hpp"
#include <vector>

Enemy *Enemy::createEnemy( GameScene *scene )
{
    Enemy  *sprite;
    sprite = new Enemy();
    
//    && sprite->initWithSpriteFrame( SpriteFrameCache::getInstance()->getSpriteFrameByName( "Shark_1.png" ) )
    
    if ( sprite ) {
        sprite->setScene( scene );
        sprite->initEnemy();
        
        return sprite;
    }
    
    CC_SAFE_DELETE( sprite );
    
    return sprite = nullptr;
}

void Enemy::setScene( GameScene *scene )
{
    this->scene = scene;
}

void Enemy::initEnemy()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile( "Shark5.plist" );
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    auto frames = getAnimation("Shark_%1d.png", 9);
    this->initWithSpriteFrame( SpriteFrameCache::getInstance()->getSpriteFrameByName( "Shark_1.png" ) );
//    this->Sprite::createWithSpriteFrame( frames.front() );
    
    this->setScale( 0.55 );
    scene->addChild( this , 110 );
    
    animation = Animation::createWithSpriteFrames(frames, 1.0f/8 );
    this->runAction( RepeatForever::create( Animate::create( animation ) ) );
    
    auto move = MoveTo::create( 10, Vec2( 1100, 250 ) );
    auto resetPosition = MoveTo::create( 0, Vec2( -50, 250 ) );
    auto seq = Sequence::create( move, resetPosition, nullptr );
    
    this->runAction( RepeatForever::create( seq ) );

    
}


Vector<SpriteFrame*> Enemy::getAnimation(const char *format, int count)
{
    auto spritecache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames;
    char str[100];
    for(int i = 1; i <= count; i++)
    {
        sprintf(str, format, i);
        animFrames.pushBack(spritecache->getSpriteFrameByName(str));
    }
    return animFrames;
}
