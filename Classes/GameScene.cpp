//
//  GameScene.cpp
//  TestGame
//
//  Created by Madji on 9.05.19.
//


#include "GameScene.hpp"

#define BARREL      0
#define MINE        1
#define SUBMARINE   2
#define ROCKET      3

int global_var = 0;

using namespace cocos2d;

Scene *GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
//    scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
    scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_NONE );
    
    scene->getPhysicsWorld()->setGravity( Vec2( 0, -0.9 ) );
    
    auto layer = GameScene::create();
    layer->SetPhysicsWorld( scene->getPhysicsWorld( ) );
    
    scene->addChild( layer );
    
    return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainScene.cpp\n");
}

bool GameScene::init( )
{
    if ( !Layer::init() ) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    setUI();
    
    musicData = MusicData::getMusicData();
    gameData = GameData::getGameData();
    
    currentLevel = gameData->getCurrentLevelNumber();
    timeNeedToPassLevel = levelData[currentLevel].level[0].passLevelTime;
    gameData->setCountdownTimerCounter( currentLevel );

    loadLevelData( currentLevel );

    if ( false == checkCanPlayGS() ) {
        watchAd();
    }
    
//    log("GS 59 level number %d", gameData->getCurrentLevelNumber() );
    
    spawnShark();
    createContactListener();
    setBackground();
    createEdgeBody();
    
    this->scheduleUpdate();
    
    return true;
    
}

bool GameScene::checkCanPlayGS()
{
    return ui->checkCanPlayBG();
}

void GameScene::watchAd()
{
    log("time for advertise movie");
//    background->increaseSharkLives();
}


void GameScene::saveUserData()
{
    ui->saveUserData();
}

void GameScene::getUserDataFromStruct()
{
    currentLevel = gameData->getCurrentLevelNumber();
//    log("GS 102 load current level num %d", currentLevel );
    loadLevelData( currentLevel );
    
}

void GameScene::loadLevelData( int levelNumber )
{
    float barrelSpawnTime = enemyData[levelNumber].enemy[BARREL].spawnTime;
    float mineSpawnTime = enemyData[levelNumber].enemy[MINE].spawnTime;
    float submarineSpawnTime = enemyData[levelNumber].enemy[SUBMARINE].spawnTime;
    float rocketSpawnTime = enemyData[levelNumber].enemy[ROCKET].spawnTime;
    
    barrelSpawnTime = enemyData[levelNumber].enemy[0].spawnTime;
    barrelSpeedMin = enemyData[levelNumber].enemy[0].speedMin;
    barrelSpeedMax = enemyData[levelNumber].enemy[0].speedMax;
    
    mineSpawnTime = enemyData[levelNumber].enemy[1].spawnTime;
    mineSpeedMin = enemyData[levelNumber].enemy[1].speedMin;
    mineSpeedMax = enemyData[levelNumber].enemy[1].speedMax;
    
//    float fishSpawnTime = fishData[levelNumber].fish[1].fishSpawnTime;
    float fishSpawnTime = fishData->fish[levelNumber].fishSpawnTime;
    float heartSpawnTime = fishData[levelNumber].fish[1].heartSpawnTime;
    pushEnemies( barrelSpawnTime, mineSpawnTime, submarineSpawnTime, rocketSpawnTime );
    
    pushFish( fishSpawnTime, heartSpawnTime );
}

void GameScene::pushEnemies( float spawnBarrelFrequency, float spawnMineFrequency, float spawnSubmarineFrequency, float spawnRocketFrequency )
{
    // PUSH BARRELS method
    schedule( schedule_selector( GameScene::spawnBarrel ), spawnBarrelFrequency * visibleSize.height );
    
    schedule( schedule_selector( GameScene::spawnMine ), spawnMineFrequency * visibleSize.height );
    
//    log("GS 159 spawn barrel time %f mine time %f", (spawnBarrelFrequency * visibleSize.height),  (spawnMineFrequency * visibleSize.height));
}

void GameScene::pushFish( float spawnFishFrequency, float spawnHeartFrequency )
{
    this->schedule( schedule_selector( GameScene::spawnFish ), spawnFishFrequency * visibleSize.height );
    // PUSH HEARTS method
//    schedule( schedule_selector( GameScene::spawnHeart ), spawnHeartFrequency * visibleSize.height );
}

void GameScene::setUI()
{
    ui = UI::createUI( this );
    this->addChild( ui, 1000 );
}


void GameScene::createContactListener()
{
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1( GameScene::onContactBegin, this );
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority( contactListener, this );
    
}

bool GameScene::onContactBegin( PhysicsContact &contact )
{
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    
    Fish    *fish_temp = nullptr;
    Barrel  *barrel_temp = nullptr;
    Mine    *mine_temp = nullptr;
    
    counter++;
    
    if ( ( a->getContactTestBitmask() == CONTACT_MASK_SHARK && b->getContactTestBitmask() == CONTACT_MASK_FISH )
        || ( b->getContactTestBitmask() == CONTACT_MASK_SHARK && a->getContactTestBitmask() == CONTACT_MASK_FISH ) ) {
        playEatFishSound();
        fish_temp = dynamic_cast<Fish*>(b->getNode());
        if ( fish_temp == nullptr ){
            fish_temp = dynamic_cast<Fish*>(a->getNode());
        }
        
        if ( fish_temp == nullptr ){
//            log("GS 202 ERROR at Class fish is nullptr after contact with shark");
        }
        else {
        addToGameScore( fish_temp->getPoints() );
            gameData->increaseFishCounter();
            fish_temp->removeFromParentAndCleanup( true );
    //        this->RemoveSprite( fish_temp );
    //        fish_temp->removeFish();
        }
    }
    else if ( ( a->getContactTestBitmask() == CONTACT_MASK_SHARK && b->getContactTestBitmask() == CONTACT_MASK_BARREL )
             || ( b->getContactTestBitmask() == CONTACT_MASK_SHARK && a->getContactTestBitmask() == CONTACT_MASK_BARREL ) ){
//        log("GS 215 %d ON CONTACT BEGIN SHARK 1", counter );
        barrel_temp = dynamic_cast<Barrel*>(b->getNode());
        if ( barrel_temp == nullptr ){
            barrel_temp = dynamic_cast<Barrel*>(a->getNode());
        }
        
        if ( barrel_temp == nullptr ){
//            log("GS 267 ERROR barrel is nullptr after contact with ground");
        }
        else {
            if ( false == isTheSharkDead ){
                isTheSharkDead = true;
                sharkKilled( a );
                hitBarrel( b );
            }
        }
    }

    else if ( ( a->getContactTestBitmask() == CONTACT_MASK_SHARK && b->getContactTestBitmask() == CONTACT_MASK_MINE )
             || ( b->getContactTestBitmask() == CONTACT_MASK_SHARK && a->getContactTestBitmask() == CONTACT_MASK_MINE ) ) {
        
        mine_temp = dynamic_cast<Mine*>(b->getNode());
        
        if ( mine_temp == nullptr ){
            mine_temp = dynamic_cast<Mine*>(a->getNode());
        }
        
        if ( mine_temp == nullptr ){
//            log("GS 239 ERROR at Class fish is nullptr after contact with shark");
        }
        else {
            if ( false == isTheSharkDead ){
                isTheSharkDead = true;
                sharkKilled( a );
                hitMine( b );
            }
        }

        mine_temp->removeFromParentAndCleanup( true );

    }
    else if ( ( b->getContactTestBitmask() == CONTACT_MASK_SHARK && a->getContactTestBitmask() == CONTACT_MASK_BACKGROUND ) ||  ( b->getContactTestBitmask() == CONTACT_MASK_BACKGROUND && a->getContactTestBitmask() == CONTACT_MASK_SHARK ) )
    {
//        log( "GS 249 shark contact ground");
//        shark->sharkHeadZero();
//        shark->sharkMoving();
//        shark->sharkFreeze();
//        shark->runAction( RotateTo::create( SHARK_HEAD_ZERO_TIME, SHARK_HEAD_ZERO ) );
        shark->moveUpTimeCounter = SHARK_REST_COUNTER;
    }
    else if ( ( a->getContactTestBitmask() == CONTACT_MASK_BARREL && b->getContactTestBitmask() == CONTACT_MASK_BACKGROUND ) ||  ( a->getContactTestBitmask() == CONTACT_MASK_BACKGROUND && b->getContactTestBitmask() == CONTACT_MASK_BARREL ) )
    {
        barrel_temp = dynamic_cast<Barrel*>(b->getNode());
        if ( barrel_temp == nullptr ){
            barrel_temp = dynamic_cast<Barrel*>(a->getNode());
        }
        
        if ( barrel_temp == nullptr ){
//            log("GS 267 ERROR barrel is nullptr after contact with ground");
        } else {
//        auto radius1 = barrel_temp->getRotation();
        barrel_temp->cancelRotation();
//        barrel_temp->setRotation( 360 - radius1 );
//        log("GS 273 radius1 %f", radius1);
//        this->barrelContact( barrel_temp );
        }
    }
    else
    {
//        log( "GS 279 error with collision method");
    }
    
    return true;
}

void GameScene::barrelContact( Sprite *sprite )
{
//    auto radius1 = sprite_temp->getRotation();
//    sprite->cancelRotation();
//    sprite->setRotation( 360 - radius1 );
//    log("GS 273 radius1 %f", radius1);
}

void GameScene::addToGameScore( int points )
{
    ui->addPointsToGameScore( points );
    
    /*
     This is logic for pass level depending on max earn score
     Levels->levelStat passLevelPoints
     
    if ( ui->getGameScoreCounter() > gameData->getToPassLevelPoints( currentLevel ) ){
        goToLevelCompleteScene();
    }
     */
}

void GameScene::checkPassLevelConditions()
{
    // if there is at least one earned star => pass level
    // else failed
    
//    printf("GS 297 earned stars %d\n", ui->getEarnedStars());
    
    isGame = false;
    
    if ( ui->getEarnedStars()){
        goToLevelCompleteScene();
    } else {
        goToYouFailedScene();
    }
}

void GameScene::goToGameOverScene()
{
    auto scene = GameOverScene::createScene( );
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME_BETWEEN_SCENE, scene ) );
}


void GameScene::goToYouFailedScene( )
{
    saveUserData();
    
    if ( true == checkCanPlayGS() )
    {
        ui->setPauseButtonCondition( false );
        failedMenu = YouFailedMenu::createMenu( this );
//        this->addChild( failedMenu, 1000 );
    }
    else
    {
        this->goToGameOverScene();
    }
    
}

void GameScene::goToLevelCompleteScene( )
{
    saveUserData();
    ui->stopTimer();
    shark->unscheduleTouchListener();
    shark->removeShark();
    this->removeChild( shark );
    ui->setPauseButtonCondition( false );
    levelCompleteScene = LevelCompleteScene::createMenu( this );
//    this->addChild( levelCompleteScene, 1000 );
}

void GameScene::retryGameLevel()
{
    ui->setPauseButtonCondition( true );
//    gameData->setCountdownTimerCounter( currentLevel );
    spawnShark();
}

void GameScene::spawnMine( float dt )
{
    mine = Mine::createMine( this );
    
}

void GameScene::spawnBarrel( float dt )
{
    barrel = Barrel::createBarrel( this );
    barrel->spawnBarrel( barrelSpeedMin, barrelSpeedMax );
}

void GameScene::spawnFish( float dt )
{
    fish = Fish::createFish( this );
}

void GameScene::PushExplosion()
{
    explosion = Explosion::createExplosion( this );
}

// SHARK STUFF

void GameScene::spawnShark()
{
    isTheSharkDead = false;
    shark = Shark::createShark( this );
    
    auto myDelay = DelayTime::create( 1.0f );
    auto myDelay2 = DelayTime::create( TIME_TO_MOVE_SHARK_TO_GAME_POSITION + 1 );
    auto playMusic = CallFunc::create( CC_CALLBACK_0( GameScene::playBackgroundMusic, this ) );
    auto startTime = CallFunc::create(CC_CALLBACK_0( GameScene::startTimer, this) );
    auto seq = Sequence::create( myDelay, playMusic, myDelay2, startTime, nullptr );
    
    this->runAction( seq );
    
}

void GameScene::startTimer()
{
    ui->startTimer();
    isGame = true;
}

void GameScene::sharkKilled( PhysicsBody *a )
{
    stopBackgroundMusic();

    ui->stopTimer();
    ui->decreaseSharkLives();
    
    Node *node = a->getNode();
    
    auto x = node->getPositionX();
    auto y = node->getPositionY();
    
    auto pushExpl = CallFunc::create( [&]() { PushExplosion(); } );
    auto runExpl = CallFunc::create( [=]() { explosion->runExplosion( x, y ); } );
    auto sharkKill = CallFunc::create( [=]() { shark->sharkKilled( x, y ); } );
    auto nodeInvisible = CallFunc::create( [=] () { node->setVisible( false ); } );
    auto nodeRemove = CallFunc::create( [=] () { this->removeChild( a->getNode() ); } );
    auto spawn = Spawn::create( pushExpl, runExpl, nullptr );

    auto seq = Sequence::create( spawn, nodeInvisible, nodeRemove, sharkKill, nullptr );
    this->runAction( seq );
    
    playKillSharkSound();

}

void GameScene::hitBarrel( PhysicsBody *a )
{
    
    playExplosionSound();
    
    Node *node = a->getNode();
    
    auto x = node->getPositionX();
    auto y = node->getPositionY();
    
    barrel->hitBarrel( x, y );
    
    node->setVisible( false );
    this->removeChild( a->getNode() );
    
}

void GameScene::hitMine( PhysicsBody *a )
{
    playExplosionSound();
    
    Node *node = a->getNode();
    
    auto x = node->getPositionX();
    auto y = node->getPositionY();
    
    mine->hitMine( x, y );
    
    node->setVisible( false );
    this->removeChild( a->getNode() );
    
}

void GameScene::update( float dt )
{
    
    if ( isGame && !ui->getGameTimerSeconds() ) {
        checkPassLevelConditions();
    }
    
    if ( selectLevelScene != NULL && !selectLevelScene->isLevelUpdated ) {

        DEBUG_INFO;

        selectLevelScene->showSixLevels();
        selectLevelScene->isLevelUpdated = true;
    }
    
    int offset1 = SPEED_BACKGROUND_1;
    int offset2 = SPEED_BACKGROUND_2;
    int offset3 = SPEED_BACKGROUND_3;
    
    bg10->setPositionX( bg10->getPositionX() - offset1 );
    if ( ( bg10->getPositionX() + bg10->getContentSize().width / 2 ) < 0 ) {
        bg10->setPositionX( bg12->getPositionX() + bg12->getContentSize().width - offset1 );
    }
    
    bg11->setPositionX( bg11->getPositionX()  - offset1 );
    if (( bg11->getPositionX() + bg11->getContentSize().width / 2 ) < 0 ) {
        bg11->setPositionX( bg10->getPositionX() + bg10->getContentSize().width - offset1 );
    }
    
    bg12->setPositionX( bg12->getPositionX() - offset1 );
    if (( bg12->getPositionX() + bg12->getContentSize().width / 2 ) < 0 ) {
        bg12->setPositionX( bg11->getPositionX() + bg11->getContentSize().width - offset1 );
    }
    
    
    
    bg20->setPositionX( bg20->getPositionX() - offset2 );
    if (( bg20->getPositionX() + bg20->getContentSize().width / 2 ) < 0 ) {
        bg20->setPositionX( bg22->getPositionX() + bg22->getContentSize().width - offset2 );
    }
    
    bg21->setPositionX( bg21->getPositionX() - offset2 );
    if (( bg21->getPositionX() + bg21->getContentSize().width / 2 ) < 0 ) {
        bg21->setPositionX( bg20->getPositionX() + bg20->getContentSize().width - offset2 );
    }
    
    bg22->setPositionX( bg22->getPositionX() - offset2 );
    if (( bg22->getPositionX() + bg22->getContentSize().width / 2 ) < 0 ) {
        bg22->setPositionX( bg21->getPositionX() + bg21->getContentSize().width - offset2 );
    }
    
    
    
    bg30->setPositionX( bg30->getPositionX() - offset3 );
    if (( bg30->getPositionX() + bg30->getContentSize().width / 2 ) < 0 ) {
        bg30->setPositionX( bg32->getPositionX() + bg32->getContentSize().width - offset3 );
    }
    
    bg31->setPositionX( bg31->getPositionX() - offset3 );
    if (( bg31->getPositionX() + bg31->getContentSize().width / 2 ) < 0 ) {
        bg31->setPositionX(bg30->getPositionX() + bg30->getContentSize().width - offset3 );
    }
    
    bg32->setPositionX( bg32->getPositionX() - offset3 );
    if (( bg32->getPositionX() + bg32->getContentSize().width / 2 ) < 0 ) {
        bg32->setPositionX( bg31->getPositionX() + bg31->getContentSize().width - offset3 );
    }
}



void GameScene::playBackgroundMusic()
{
    musicData->playGameMusic();
}
void GameScene::pauseBackgroundMusic()
{
    musicData->pauseGameMusic();
}
void GameScene::resumeBackgroundMusic()
{
    musicData->resumeGameMusic();
}
void GameScene::stopBackgroundMusic()
{
    musicData->stopGameMusic();
}
void GameScene::playButtonStartClick()
{
    musicData->playButtonStartClickSound();
}
void GameScene::playButtonEndClick()
{
    musicData->playButtonEndClickSound();
}
void GameScene::playEatFishSound()
{
    musicData->playEatFishSound();
}
void GameScene::playExplosionSound()
{
    musicData->playHitMineSound();
}
void GameScene::playKillSharkSound()
{
    musicData->playSharkDiedSound();
}

void GameScene::createEdgeBody()
{
//    edgeBody = PhysicsBody::createEdgeBox( visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3 );
    edgeBody = PhysicsBody::createBox(Size(visibleSize.width, 20), PHYSICSBODY_MATERIAL_DEFAULT, Vec2(0, -visibleSize.height/2 ));
    edgeBody->setDynamic( false );
    edgeBody->setCategoryBitmask( CATEGORY_MASK_BACKGROUND );
    edgeBody->setCollisionBitmask( COLLISION_MASK_BACKGROUND );
    edgeBody->setContactTestBitmask( CONTACT_MASK_BACKGROUND );
    
    auto edgeNode = Node::create();
    edgeNode->setPosition( Vec2( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    edgeNode->setPhysicsBody( edgeBody );
    
    this->addChild( edgeNode );
}

void GameScene::setBackground()
{
    bg00 = Sprite::create( "bg_0_2160_1080.png" );
    bg10 = Sprite::create( "bg_1_1920_1080.png" );
    bg11 = Sprite::create( "bg_1_1920_1080.png" );
    bg12 = Sprite::create( "bg_1_1920_1080.png" );
    bg20 = Sprite::create( "bg_2_1920_1080.png" );
    bg21 = Sprite::create( "bg_2_1920_1080.png" );
    bg22 = Sprite::create( "bg_2_1920_1080.png" );
    bg30 = Sprite::create( "bg_3_1920_1080.png" );
    bg31 = Sprite::create( "bg_3_1920_1080.png" );
    bg32 = Sprite::create( "bg_3_1920_1080.png" );
    bg40 = Sprite::create( "deep_sea_ground.png" );
    bg41 = Sprite::create( "deep_sea_ground.png" );

    bg00->setScale(1.5);
    
    bg00->setAnchorPoint( Vec2( 0.5, 0.5 ) );
    bg10->setAnchorPoint( Vec2( 0.5, 0.5 ) );
    bg11->setAnchorPoint( Vec2( 0.5, 0.5 ) );
    bg12->setAnchorPoint( Vec2( 0.5, 0.5 ) );
    bg20->setAnchorPoint( Vec2( 0.5, 0.5 ) );
    bg21->setAnchorPoint( Vec2( 0.5, 0.5 ) );
    bg22->setAnchorPoint( Vec2( 0.5, 0.5 ) );
    bg30->setAnchorPoint( Vec2( 0.5, 0.5 ) );
    bg31->setAnchorPoint( Vec2( 0.5, 0.5 ) );
    bg32->setAnchorPoint( Vec2( 0.5, 0.5 ) );
    bg40->setAnchorPoint( Vec2( 0.5, 0.5 ) );
    bg41->setAnchorPoint( Vec2( 0.5, 0.5 ) );
    
    if( bg00 == nullptr ) {
        problemLoading( "'bg_0_2160_1080.png'" );
    }
    if( bg10 == nullptr || bg11 == nullptr || bg12 == nullptr ){
        problemLoading( "'bg_1_2160_1080.png'" );
    }
    if( bg20 == nullptr || bg21 == nullptr || bg22 == nullptr ){
        problemLoading( "'bg_2_2160_1080.png'" );
    }
    if( bg30 == nullptr || bg31 == nullptr || bg32 == nullptr ){
        problemLoading( "'bg_3_2160_1080.png'" );
    }
    if( bg40 == nullptr || bg41 == nullptr ){
        problemLoading( "'deep_sea_ground.png'" );
    }
    
    
    bg00->setPosition( Vec2( visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y ) );
    
    bg10->setPosition( Vec2( visibleSize.width/2 + origin.x, bg10->getContentSize().height/2 + origin.y ) );
    bg11->setPosition( Vec2( ( bg10->getPositionX() + bg10->getContentSize().width ),
                            bg11->getContentSize().height/2 + origin.y ) );
    bg12->setPosition( Vec2( ( bg11->getPositionX() + bg11->getContentSize().width ),
                            bg12->getContentSize().height/2 + origin.y ) );
    
    bg20->setPosition( Vec2( visibleSize.width/2 + origin.x, bg20->getContentSize().height/2 + origin.y ) );
    bg21->setPosition( Vec2( ( bg20->getPositionX() + bg21->getContentSize().width ),
                            bg21->getContentSize().height/2 + origin.y ) );
    bg22->setPosition( Vec2( ( bg21->getPositionX() + bg22->getContentSize().width ),
                            bg22->getContentSize().height/2 + origin.y ) );
    
    bg30->setPosition( Vec2( visibleSize.width/2 + origin.x, bg30->getContentSize().height/2 + origin.y ) );
    bg31->setPosition( Vec2( ( bg30->getPositionX() + bg31->getContentSize().width ),
                            bg31->getContentSize().height/2 + origin.y ) );
    bg32->setPosition( Vec2( ( bg31->getPositionX() + bg32->getContentSize().width ),
                            bg32->getContentSize().height/2 + origin.y ) );
    bg40->setPosition( Vec2( visibleSize.width/2 - bg40->getContentSize().width, bg40->getContentSize().height + origin.y - BOTTOM_POSITION ) );
    bg41->setPosition( Vec2( bg40->getPositionX() + bg40->getContentSize().width, bg41->getContentSize().height - BOTTOM_POSITION ) );
    
    this->addChild( bg00, - 100 );
    this->addChild( bg10, - 90 );
    this->addChild( bg11, - 90 );
    this->addChild( bg12, - 90 );
    this->addChild( bg20, - 80 );
    this->addChild( bg21, - 80 );
    this->addChild( bg22, - 80 );
    this->addChild( bg30, - 70 );
    this->addChild( bg31, - 70 );
    this->addChild( bg32, - 70 );
    this->addChild( bg40, 76 );
    this->addChild( bg41, 76 );
    
    //    bg00->setVisible(true);
    //    bg10->setVisible(true);
    //    bg11->setVisible(true);
    //    bg12->setVisible(true);
    //    bg20->setVisible(true);
    //    bg21->setVisible(true);
    //    bg22->setVisible(true);
    //    bg30->setVisible(true);
    //    bg31->setVisible(true);
    //    bg32->setVisible(true);
    //    bg40->setVisible(true);
    //    bg41->setVisible(true);
}
