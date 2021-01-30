//
//  Explosion.cpp
//  TestGame
//
//  Created by Madji on 11.05.19.
//

#include "Explosion.hpp"
#include <vector>

Explosion *Explosion::createExplosion( GameScene *scene )
{
    Explosion  *sprite;
    sprite = new Explosion();
    
    if ( sprite ) {
        sprite->setScene( scene );
        sprite->initExplosion();
        
        return sprite;
    }
    
    CC_SAFE_DELETE( sprite );
    
    return sprite = nullptr;
}

void Explosion::setScene( GameScene *scene )
{
    this->scene = scene;
}

void Explosion::initExplosion()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile( "explosion_1.plist" );
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    auto frames = getAnimation("explosion_%d.png", 8);
    this->initWithSpriteFrame( SpriteFrameCache::getInstance()->getSpriteFrameByName( "explosion_1.png" ) );
//    this->Sprite::createWithSpriteFrame( frames.front() );
    
    this->setScale( 2.0 );
    
    animation = Animation::createWithSpriteFrames(frames, 1.0f / 8 );
    this->runAction( RepeatForever::create( Animate::create( animation ) ) );
    
}

void Explosion::runExplosion(float x, float y)
{
    
    auto pos = Vec2( x, y );
    this->setPosition( pos );
    scene->addChild( this , 110 );

    auto delay = DelayTime::create( 1.0 );
    auto seq = Sequence::create(delay, RemoveSelf::create(),  nullptr);
    this->runAction( seq );
  
}

void Explosion::removeExplosion()
{
    this->autorelease();
    this->removeFromParentAndCleanup( true );
}


Vector<SpriteFrame*> Explosion::getAnimation(const char *format, int count)
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
