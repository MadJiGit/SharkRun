//
//  Mine.cpp
//  TestGame
//
//  Created by Madji on 11.05.19.
//

#include "Mine.hpp"
#include <vector>

Mine *Mine::createMine( GameScene *scene )
{
    Mine  *sprite;
    sprite = new Mine();
    
    if ( sprite && sprite->initWithFile( "mine_chain_blue.png" ) ) {
        sprite->setScene( scene );
        sprite->initMine();
        return sprite;
    }
    
    CC_SAFE_DELETE( sprite );
    
    return sprite = nullptr;
}

void Mine::setScene( GameScene *scene )
{
    this->scene = scene;
}

void Mine::initMine()
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    mineSize = this->getContentSize().height * MINE_SCALE_PARAM;
    
    createPhysicsBody();
    
    fillVectorOfMine();
    sizeOfMineVector = ( int )minesVector.size();
    
    auto getRandomIndexOfMineVector = RandomHelper::random_int( 0, sizeOfMineVector - 1 );
    auto randomMine = minesVector.at( getRandomIndexOfMineVector );
    this->setSpriteFrame( randomMine->getSpriteFrame() );
    this->setScale( MINE_SCALE_PARAM );
    this->setAnchorPoint( Vec2( 0.5, 1 ) );
    
    auto longChain = mineSize * LONG_CHAIN_PARAM;
    
//    auto mineStartPosX = visibleSize.width + ( mineSize * 2 ) + origin.x;
    auto mineStartPosX = visibleSize.width + 50 + origin.x;
//    log("row 54 MINE start X vis size %f origin %f mineStartPos %f ", visibleSize.width, origin.x, mineStartPosX);
//    log("MINE 55 mine content size width %f", this->getContentSize().width );
    auto minePositionY = RandomHelper::random_int( ( origin.y + ( this->getContentSize().width * 1.5 ) ) , ( visibleSize.height - origin.y - ( this->getContentSize().width * 1.5 ) ) );
    
    
    if ( minePositionY > visibleSize.height / 2 )
    {
        this->setRotation( 180 );
        
        if ( ( visibleSize.height - minePositionY ) > ( longChain) )
        {
            minePositionY = ( visibleSize.height - longChain );
        }
    }
    
    else if ( minePositionY > longChain )
    {
        minePositionY = longChain;
    }
    
    auto mineStartPosition = Vec2( mineStartPosX, minePositionY );
//    auto mineStartPosition = Vec2( 1100, minePositionY );

    this->setPosition( mineStartPosition );

    // tag for contact begin method
    this->setTag( 80 );

//    auto mineEndPosX = 0 - ( 50 ) - origin.x;

//     auto deltaLength = mineStartPosX + ( - ( mineEndPosX ) );
//    log("MINE 83 start X %f end X %f diff %f", mineStartPosX, mineEndPosX, deltaLength );
    
//    auto director = Director::getInstance();
//    auto animInter = director->getAnimationInterval();
//
//    auto mineEndPosition = Vec2( mineEndPosX, minePositionY );

//    auto mineAction = MoveTo::create( TIME_MINE_MOVE, mineEndPosition );
    //     auto mineStartPosX = visibleSize.width + 50 + origin.x; = 1278 + 50 + 0 = 1328
    //     auto mineEndPosX = 0 - ( 50 ) - origin.x; = - 50 = 50
    //     deltaLength = 1328 + 50 = 1378
   
//    auto deltaTime = deltaLength / 60;
//    log("Mine row 91 dt %f delta lenght %f anim inter %f", deltaTime, deltaLength, animInter );
    // 180 for 1 sec 4320 / 180 = 24 sec
    // size 1440 - lenght 1278
    // 1378 / 180 = 7.65
//    auto mineAction = MoveTo::create( 15, Vec2( 0, minePositionY) );
//    auto mineAction = MoveBy::create( deltaTime, Vec2( - deltaLength, 0 ) );

//    auto mineMove = Sequence::create( mineAction, RemoveSelf::create(), nullptr );

//    this->runAction( mineMove );
    
    scene->addChild( this, MINE_SCENE_TAG );
    

}

void Mine::update( float dt )
{
    if ( this->getPositionX() + this->getContentSize().width > 0 )
    {
        this->setPositionX( this->getPositionX() - 3 );
    }
    else
    {
        this->unscheduleUpdate();
        RemoveSelf::create();
    }
}


void Mine::createPhysicsBody()
{
    MyBodyParser::getInstance()->parseJsonFile( "mine_chain.json" );
    auto mineBody = MyBodyParser::getInstance()->bodyFormJson( this, "mine_chain_physics", PHYSICSBODY_MATERIAL_DEFAULT );

    mineBody->setDynamic( false );
    mineBody->setRotationEnable( false );
    mineBody->setCategoryBitmask( CATEGORY_MASK_MINE );
    mineBody->setCollisionBitmask( COLLISION_MASK_MINE );
    mineBody->setContactTestBitmask( CONTACT_MASK_MINE );
//    mineBody->setContactTestBitmask( CATEGORY_MASK_SHARK | CATEGORY_MASK_CHAIN );
    
    this->setPhysicsBody( mineBody );
}

void Mine::fillVectorOfMine()
{
    auto redMine = Sprite::create( "mine_chain_red.png" );
    auto blueMine = Sprite::create( "mine_chain_blue.png" );
    auto greenMine = Sprite::create( "mine_chain_green.png" );
    auto yellowMine = Sprite::create( "mine_chain_yellow.png" );

    minesVector.pushBack( redMine );
    minesVector.pushBack( blueMine );
    minesVector.pushBack( greenMine );
    minesVector.pushBack( yellowMine );

}

int Mine::randomNumberBetweenTwoNumbers( int max, int min )
{
    return rand( )%( ( max - min ) + 1 ) + min;
}

void Mine::removeMine()
{
    this->autorelease();
    this->removeFromParentAndCleanup( true );
}

void Mine::hitMine( float x, float y )
{
    
}


