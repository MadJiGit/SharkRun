//
//  Bubble.cpp
//  TestGame
//
//  Created by Madji on 11.05.19.
//

#include "Bubble.hpp"
#include <vector>

Bubble *Bubble::createBubble( float x, float y, float directionX )
{
    Bubble  *sprite;
    sprite = new Bubble();
    
    if ( sprite && sprite->initWithFile( "bubble.png" ) ) {

        sprite->initBubble( x, y, directionX );
        
        return sprite;
    }
    
    CC_SAFE_DELETE( sprite );
    
    return sprite = nullptr;
}


void Bubble::initBubble( float x, float y, float directionX )
{
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    this->setScale( 0.5 );
    
    this->setPosition( Vec2( x, y ) );
    float bubbleLifeTime = ( ( float ) arc4random() / 0x100000000 ) * 7;
    
    auto moveBubble = MoveBy::create( 9, Vec2( directionX, this->visibleSize.height + this->getContentSize().height ) );
    
//    auto delayTime = DelayTime::create( bubbleLifeTime );
    float time = 0.5;
    auto delayTimeBeforeFadeOut = DelayTime::create( bubbleLifeTime - 2.0f );
    auto delayTimeZoomIn = DelayTime::create( time );
    auto delayTimeZoomOut = DelayTime::create( time );
    auto zoomIn = ScaleTo::create( time, 1.1 );
    auto zoomOut = ScaleTo::create( time, 0.9 );
    
    auto fadeOut = FadeOut::create( 2.0f );
    
    auto seq = Sequence::create( moveBubble, delayTimeBeforeFadeOut, fadeOut, RemoveSelf::create(), nullptr );
    auto seq1 = Sequence::create( zoomIn, delayTimeZoomIn, zoomOut, delayTimeZoomOut, nullptr );
    
    this->runAction( seq );
    this->runAction( seq1 );
}

int Bubble::randomNumberBetweenTwoNumbers( int first, int second )
{
    return 0;
}
