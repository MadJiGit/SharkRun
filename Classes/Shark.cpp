//
//  Shark.cpp
//  MyCppGame-mobile
//
//  Created by Madji on 24.04.19.
//

#include "Shark.hpp"
#include <iostream>

Shark *Shark::createShark( GameScene *scene )
{
    Shark       *sprite;
    sprite = new Shark();
    
    if ( sprite )
    {
        sprite->setScene( scene );
        sprite->initShark();
        sprite->setScale( SHARK_SCALE_PARAM );
        
        return sprite;
    }
    
    CC_SAFE_DELETE( sprite );
    
    return sprite = nullptr;
    
}

void Shark::setScene( GameScene *scene )
{
    this->scene = scene;
}

void Shark::initShark()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile( "shark_plist_new.plist" );
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    _constSharkPositionX = visibleSize.width / 3 + origin.x;
    gamePosition = Vec2( _constSharkPositionX, visibleSize.height / 2 + origin.y );
    
    this->setAnchorPoint( Vec2( 0.5, 0.5 ) );
    lastSharkGoToPosY = -1;
    maxScreenSizeY = visibleSize.height + origin.y;
    
    auto framesSwim = getAnimation( "Shark-%d.png", 9 );
    this->initWithSpriteFrame ( SpriteFrameCache::getInstance()->getSpriteFrameByName( "Shark-0.png" ) );
    
    MyBodyParser::getInstance()->parseJsonFile( "shark_last.json" );
    this->sharkBody = MyBodyParser::getInstance()->bodyFormJson( this, "Shark-0.png", PhysicsMaterial( 0.5, 0, 1 ) );
    
    this->sharkBody->setDynamic( true );
    this->sharkBody->setGravityEnable( false );
    this->sharkBody->setRotationEnable( false );
    this->setPhysicsBody( this->sharkBody );
    
    this->setPosition( Vec2( 0 - this->getContentSize().width, 0 + this->getContentSize().height / 2 ) );

    sharkHeadUp();
    moveUpTimeCounter = -1;
    this->isSharkOnGamePosition = false;
    
    // tag for contact begin method
    this->setTag( 100 );
    scene->addChild( this, 900 );
    
    
    animation = Animation::createWithSpriteFrames( framesSwim, 1.0f/8 );
    this->runAction( RepeatForever::create( Animate::create( animation ) ) );
    
    this->scheduleOnce(schedule_selector( Shark::moveSharkOnGamePosition ), TIME_TO_MOVE_SHARK_TO_GAME_POSITION );
    
    this->schedule( schedule_selector( Shark::pushBubble ), 1.1f );
    
}


void Shark::pushBubble( float dt )
{
    auto bubblePosX = this->getPositionX() + this->getContentSize().width / 6 ;
    bubble = Bubble::createBubble( bubblePosX, this->getPositionY() - this->getContentSize().height / 18, -1000 );
    int tag = (int)this->getPositionY() % 2 ? 901 : 899;
    scene->addChild( bubble, tag );
}


void Shark::sharkKilled( float x, float y )
{
    auto pos = Vec2( x, y );
    
    auto killedShark = Sprite::create();
    killedShark->initWithSpriteFrame ( SpriteFrameCache::getInstance()->getSpriteFrameByName( "Shark-10.png" ) );
    killedShark->setPosition( pos );
    scene->addChild( killedShark, 100 );
    
    auto move = MoveTo::create( 1.0f, Vec2( 0 - this->getContentSize().width, visibleSize.height / 2 ));
    auto rotate = RotateTo::create( 1, - 120 );
    auto spawn = Spawn::createWithTwoActions( move, rotate );
    auto callFaildScene = CallFunc::create([&]() { scene->goToYouFailedScene(); } );
    auto callremoveShark = CallFunc::create([&]() { this->removeShark(); } );
    auto seq = Sequence::create( spawn, callremoveShark, callFaildScene, nullptr );
    
    killedShark->runAction( seq );
    
}

void Shark::moveSharkOnGamePosition( float dt )
{
    auto blink = Blink::create(3, 5);
    auto moveForward = MoveTo::create( dt, gamePosition );
    auto spawn = Spawn::createWithTwoActions( blink, moveForward );
    auto seq = Sequence::create( spawn, nullptr );

    this->runAction( seq );
}

void Shark::setSharkOnGamePositionTrue()
{
//    log("S 123 setSharkOnGamePositionTrue");
    sharkHeadDown();
    this->isSharkOnGamePosition = true;
    this->createTouchListener( true );
    moveUpTimeCounter = SHARK_DOWN_COUNTER;
}

void Shark::setCollision()
{
    this->sharkBody->setCategoryBitmask( CATEGORY_MASK_SHARK );
    this->sharkBody->setCollisionBitmask( COLLISION_MASK_SHARK );
    this->sharkBody->setContactTestBitmask( CONTACT_MASK_SHARK );
}


void Shark::createTouchListener( bool condition )
{
    touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches( condition );
    touchListener->onTouchBegan = CC_CALLBACK_2( Shark::onTouchBeganShark, this );
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority( touchListener, this );
}

void Shark::unscheduleTouchListener()
{
    touchListener->setSwallowTouches( false );
}

bool Shark::onTouchBeganShark(Touch *touch, Event *event )
{
//    log("S 153 onTouchBeganShark");
    moveUpTimeCounter = SHARK_RISING_TIME_COUNTER;
    sharkHeadUp();
    
    return true;
}

Vector<SpriteFrame*> Shark::getAnimation(const char *format, int count)
{
    auto spriteCache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames;
    char str[100];
    for(int i = 1; i <= count; i++)
    {
        sprintf(str, format, i);
        animFrames.pushBack(spriteCache->getSpriteFrameByName(str));
    }
    return animFrames;
}


void Shark::sharkMoving()
{
    auto sharkCurrentPosY = this->getPositionY();
    if ( moveUpTimeCounter > 0 )
    {
        if ( ( sharkCurrentPosY + this->getContentSize().height / 3 ) < visibleSize.height + origin.x )
        {
//            this->setPositionY( sharkCurrentPosY + 15 );
            moveUpTimeCounter--;
            if ( moveUpTimeCounter > 8 )
            {
                this->setPositionY( sharkCurrentPosY + 18 );
            }
            else if ( moveUpTimeCounter > 0 )
            {
                this->setPositionY( sharkCurrentPosY + 15 );
                if ( moveUpTimeCounter == 2 )
                {
                    sharkHeadDown();
                }
            }
        } else {
            sharkHeadDown();
            moveUpTimeCounter = SHARK_DOWN_COUNTER;
        }
       
        
    }
    else if ( moveUpTimeCounter == SHARK_DOWN_COUNTER )
    {
//        sharkHeadDown();
        if ( sharkCurrentPosY > 150 ){
            this->setPositionY( sharkCurrentPosY - SHARK_FALLING_SPEED_I );
            
        }
        else if ( sharkCurrentPosY > 100 ){
            this->setPositionY( sharkCurrentPosY - SHARK_FALLING_SPEED_II );
            sharkHeadZero();
        }
        else if ( sharkCurrentPosY > 50 ){
            this->setPositionY( sharkCurrentPosY - SHARK_FALLING_SPEED_III );
        }
        else if ( sharkCurrentPosY > 0 ){
            this->setPositionY( sharkCurrentPosY - SHARK_FALLING_SPEED_IV );
        }
        else {
            moveUpTimeCounter = SHARK_REST_COUNTER;
        }
    }
}

void Shark::sharkHeadUp()
{
    this->runAction( RotateTo::create( SHARK_HEAD_UP_TIME, -SHARK_HEAD_ROTATION ) );
}

void Shark::sharkHeadDown()
{
    this->runAction( RotateTo::create( SHARK_HEAD_DOWN_TIME, SHARK_HEAD_ROTATION ) );
}

void Shark::sharkHeadZero()
{
    this->runAction( RotateTo::create( SHARK_HEAD_ZERO_TIME, SHARK_HEAD_ZERO ) );
}

void Shark::update( float dt )
{
    if( true == this->isSharkOnGamePosition )
    {
        sharkMoving();
    }
    else
    {
        if ( this->getPositionX() == gamePosition.x && this->getPositionY() == gamePosition.y )
        {
            setCollision();
            setSharkOnGamePositionTrue();
        }

    }
}


void Shark::removeShark()
{
    this->unscheduleUpdate();
    RemoveSelf::create();
}
