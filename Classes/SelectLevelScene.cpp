//
//  SelectLevelScene.cpp
//  TestGame
//
//  Created by Madji on 9.05.19.
//

#include "SelectLevelScene.hpp"

extern int global_var;

using namespace cocos2d;

Scene *SelectLevelScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = SelectLevelScene::create();
    
    scene->addChild( layer );
    
    return scene;
}


bool SelectLevelScene::init( )
{
    
    if ( !Layer::init() ) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    loadGameData();
    loadMusicAndSoundEffects();
    
    setBackground();
    setButtons();
    
    loadCurrentLevelNumberFromGameData();
    loadMaxLevelNubmer();
    loadMaxPlayedLevel();
    DEBUG_INFO;
    printf("numberOfCurrentPlayedLevel %d\n", getCurrentLevel());
    showSixLevels( gameData->getNumberOfLeftUpperLevel() );
    checkButtonsStatus( getCurrentLevel() );
    
    setStars();
    
//    auto menuLayerWidth = menuLayer->getContentSize().width * SELECT_LEVEL_MENU_LAYER_SCALE;
//    auto menuLayerHeight = menuLayer->getContentSize().height * SELECT_LEVEL_MENU_LAYER_SCALE;
    auto menuLayerWidth = menuLayer->getContentSize().width;
    auto menuLayerHeight = menuLayer->getContentSize().height;

    auto defaultPosButtonsX = menuLayer->getPositionX();
    auto defaultPosButtonsY = menuLayer->getPositionY();
    
    
    leftButton->setPosition( Vec2( defaultPosButtonsX - ( menuLayerWidth / 2 - ( leftButton->getContentSize().width ) / 3 ),
                                        defaultPosButtonsY ) );
    
    rightButton->setPosition( Vec2( defaultPosButtonsX + ( menuLayerWidth / 2 - ( rightButton->getContentSize().width ) / 3 ),
                                        defaultPosButtonsY ) );
    
    backButton->setPosition( Vec2(
                                  defaultPosButtonsX,
                                  defaultPosButtonsY - ( menuLayerHeight / 2 ) + ( backButton->getContentSize().height ) / 3 ) );
    
    
    
    auto defaultPosLayerX = menuLayer->getPositionX();
    auto defaultPosLayerY = menuLayer->getPositionY();
    
    auto testLevelWidth = testLevel_1->getContentSize().width;
    auto testLevelHeight = testLevel_1->getContentSize().height;
    auto offsetX = testLevelWidth / 3;
    auto offsetY = testLevelHeight / 3;
    auto upperMiddleX = defaultPosLayerX;
    auto upperMiddleY = ( defaultPosLayerY + menuLayerHeight / 2 ) * 2 / 3 + offsetY;
    auto downMiddleX = defaultPosLayerX;
    auto downMiddleY = ( defaultPosLayerY - testLevelHeight / 2 ) - offsetY;
    
    testLevel_1->setPosition( Vec2( upperMiddleX - testLevelWidth - offsetX, upperMiddleY ) );
    testLevel_2->setPosition( Vec2( upperMiddleX, upperMiddleY ) );
    testLevel_3->setPosition( Vec2( upperMiddleX + testLevelWidth + offsetX, upperMiddleY ) );
    testLevel_4->setPosition( Vec2( downMiddleX - testLevelWidth - offsetX, downMiddleY ) );
    testLevel_5->setPosition( Vec2( downMiddleX, downMiddleY ) );
    testLevel_6->setPosition( Vec2( downMiddleX + testLevelWidth + offsetX, downMiddleY ) );
    
    menu = Menu::create ( testLevel_1, testLevel_2, testLevel_3, testLevel_4, testLevel_5, testLevel_6, nullptr );
    menu->setPosition( Point::ZERO );


    this->addChild( background, - 3 );
    this->addChild( menuLayer, - 2 );
    this->addChild( menu, 0 );
    
    this->addChild( backButton, 20 );
    this->addChild( leftButton, 20 );
    this->addChild( rightButton, 20 );

    
    return true;
    
}

void SelectLevelScene::setStars()
{
    oneStar = Sprite::create( "one_star.png" );
    twoStars = Sprite::create( "two_stars.png" );
    threeStars = Sprite::create( "three_stars.png" );
}

void SelectLevelScene::showSixLevels(int firstLevelNumber)
{
    DEBUG_INFO;
    printf("first level number is %d\n", firstLevelNumber);

    
//    int i;
    
//    for( i = 0; i < 6; i++ )
//    {
//        auto levelData = gameData->getOneLevelDataByLevelNumber(first + i);
//        if ( true == levelData.ld_isUnlocked ){
//            singleScreenLevels[i] = MenuItemImage::create( "unlocked_level.png", "",
//                                                     CC_CALLBACK_0( SelectLevelScene::goToLevel, this, (first + i)));
//            setUnlockedLevel( singleScreenLevels[i], (first + i) );
//        } else {
//            singleScreenLevels[i] = MenuItemImage::create( "locked_level.png", "locked_level.png" );
//        }
//    }
    
    
    if ( true == gameData->getOneLevelDataByLevelNumber(firstLevelNumber).ld_isUnlocked ){
        testLevel_1 = MenuItemImage::create( "unlocked_level.png", "",
                                                 CC_CALLBACK_0( SelectLevelScene::goToLevel, this, firstLevelNumber ));
        setUnlockedLevel( testLevel_1, firstLevelNumber );
    } else {
        testLevel_1 = MenuItemImage::create( "locked_level.png", "locked_level.png" );
    }

    if ( true == gameData->getOneLevelDataByLevelNumber(firstLevelNumber+1).ld_isUnlocked ){
    testLevel_2 = MenuItemImage::create( "unlocked_level.png", "",
                                              CC_CALLBACK_0( SelectLevelScene::goToLevel, this, firstLevelNumber + 1 ));
        setUnlockedLevel( testLevel_2, (firstLevelNumber + 1) );
    } else {
        testLevel_2 = MenuItemImage::create( "locked_level.png", "locked_level.png" );
    }

    if ( true == gameData->getOneLevelDataByLevelNumber(firstLevelNumber+2).ld_isUnlocked ){
    testLevel_3 = MenuItemImage::create( "unlocked_level.png", "",
                                              CC_CALLBACK_0( SelectLevelScene::goToLevel, this, firstLevelNumber + 2 ));
        setUnlockedLevel( testLevel_3, (firstLevelNumber + 2) );
    } else {
        testLevel_3 = MenuItemImage::create( "locked_level.png", "locked_level.png" );
    }

    if ( true == gameData->getOneLevelDataByLevelNumber(firstLevelNumber+3).ld_isUnlocked ){
    testLevel_4 = MenuItemImage::create( "unlocked_level.png", "",
                                                  CC_CALLBACK_0( SelectLevelScene::goToLevel, this, firstLevelNumber + 3 ));
        setUnlockedLevel( testLevel_4, (firstLevelNumber + 3) );
    } else {
        testLevel_4 = MenuItemImage::create( "locked_level.png", "locked_level.png" );
    }

    if ( true == gameData->getOneLevelDataByLevelNumber(firstLevelNumber+4).ld_isUnlocked ){
    testLevel_5 = MenuItemImage::create( "unlocked_level.png", "",
                                              CC_CALLBACK_0( SelectLevelScene::goToLevel, this, firstLevelNumber + 4 ));
        setUnlockedLevel( testLevel_5, (firstLevelNumber + 4) );
    } else {
        testLevel_5 = MenuItemImage::create( "locked_level.png", "locked_level.png" );
    }

    if ( true == gameData->getOneLevelDataByLevelNumber(firstLevelNumber+5).ld_isUnlocked ){
        testLevel_6 = MenuItemImage::create( "unlocked_level.png", "",
                                              CC_CALLBACK_0( SelectLevelScene::goToLevel, this, firstLevelNumber + 5 ));
        setUnlockedLevel( testLevel_6, (firstLevelNumber + 5) );
    } else {
        testLevel_6 = MenuItemImage::create( "locked_level.png", "locked_level.png" );
    }
    
}

void SelectLevelScene::setUnlockedLevel( MenuItemImage *testlevelNum, int numberOfLevel )
{
    
    if ( numberOfLevel < 10) {
        setLevelImageFirstNumber( numberOfLevel );
        
        t_one_number->setPosition( Point( testlevelNum->getPositionX() + ( testlevelNum->getContentSize().width / 2 ), testlevelNum->getPositionY() + ( testlevelNum->getContentSize().height / 2 ) + ( t_one_number->getContentSize().height * 0.25 ) ) );
        testlevelNum->addChild(t_one_number, 2);
        
    } else {
        int firstNum = numberOfLevel / 10;
        int secondNum = numberOfLevel % 10;

        setLevelImageFirstNumber( firstNum );
        setLevelImageSecondNumber( secondNum );
        
        t_one_number->setPosition( Point( testlevelNum->getPositionX() + ( testlevelNum->getContentSize().width / 2 )
                                         - t_one_number->getContentSize().width * 0.55
                                           , testlevelNum->getPositionY() + ( testlevelNum->getContentSize().height / 2 ) + ( t_one_number->getContentSize().height * 0.25 ) ) );
        
        t_double_number->setPosition( Point( testlevelNum->getPositionX() + ( testlevelNum->getContentSize().width / 2 )
                                            + t_double_number->getContentSize().width * 0.55
                                            , testlevelNum->getPositionY() + ( testlevelNum->getContentSize().height / 2 ) + ( t_double_number->getContentSize().height * 0.25 ) ) );
        
        testlevelNum->addChild(t_one_number, 2);
        testlevelNum->addChild(t_double_number, 2);
    }

    setLevelImageStars( numberOfLevel );
  
    t_stars->setPosition(  Point( testlevelNum->getPositionX() + ( testlevelNum->getContentSize().width / 2 ), t_one_number->getPositionY() - ( ( t_stars->getContentSize().height ) * 1.25 ) ) );
//    testlevelNum->addChild(t_one_number, 2);
    testlevelNum->addChild(t_stars, 2);
}

void SelectLevelScene::setLevelImageFirstNumber( int levelNumber )
{
    switch ( levelNumber ) {
        case 0:
            t_one_number = MenuItemImage::create( "number_0.png", "number_0.png" );
            break;
        case 1:
            t_one_number = MenuItemImage::create( "number_1.png", "number_1.png" );
            break;
        case 2:
            t_one_number = MenuItemImage::create( "number_2.png", "number_2.png" );
            break;
        case 3:
            t_one_number = MenuItemImage::create( "number_3.png", "number_3.png" );
            break;
        case 4:
            t_one_number = MenuItemImage::create( "number_4.png", "number_4.png" );
            break;
        case 5:
            t_one_number = MenuItemImage::create( "number_5.png", "number_5.png" );
            break;
        case 6:
            t_one_number = MenuItemImage::create( "number_6.png", "number_6.png" );
            break;
        case 7:
            t_one_number = MenuItemImage::create( "number_7.png", "number_7.png" );
            break;
        case 8:
            t_one_number = MenuItemImage::create( "number_8.png", "number_8.png" );
            break;
        case 9:
            t_one_number = MenuItemImage::create( "number_9.png", "number_9.png" );
            break;
    }
    
}

void SelectLevelScene::setLevelImageSecondNumber( int levelNumber )
{
    switch ( levelNumber ) {
        case 0:
            t_double_number = MenuItemImage::create( "number_0.png", "number_0.png" );
            break;
        case 1:
            t_double_number = MenuItemImage::create( "number_1.png", "number_1.png" );
            break;
        case 2:
            t_double_number = MenuItemImage::create( "number_2.png", "number_2.png" );
            break;
        case 3:
            t_double_number = MenuItemImage::create( "number_3.png", "number_3.png" );
            break;
        case 4:
            t_double_number = MenuItemImage::create( "number_4.png", "number_4.png" );
            break;
        case 5:
            t_double_number = MenuItemImage::create( "number_5.png", "number_5.png" );
            break;
        case 6:
            t_double_number = MenuItemImage::create( "number_6.png", "number_6.png" );
            break;
        case 7:
            t_double_number = MenuItemImage::create( "number_7.png", "number_7.png" );
            break;
        case 8:
            t_double_number = MenuItemImage::create( "number_8.png", "number_8.png" );
            break;
        case 9:
            t_double_number = MenuItemImage::create( "number_9.png", "number_9.png" );
            break;
    }
    
}

void SelectLevelScene::setLevelImageStars( int levelNumber )
{

    int starsNum = gameData->getOneLevelDataByLevelNumber(levelNumber).ld_stars;

    switch ( starsNum ) {
        case 0:
            t_stars = MenuItemImage::create( "", "" );
            break;
        case 1:
            t_stars = MenuItemImage::create( "one_star.png", "one_star.png" );
            break;
        case 2:
            t_stars = MenuItemImage::create( "two_stars.png", "two_stars.png" );
            break;
        case 3:
            t_stars = MenuItemImage::create( "three_stars.png", "three_stars.png" );
            break;
        default:
            t_stars = MenuItemImage::create( "", "" );
            break;
    }
    
}

void SelectLevelScene::setLockedLevel( int numberOfLevel )
{
    this->emptyLevel = MenuItemImage::create( "unlocked_level.png", "unlocked_level_clicked.png",
                                             CC_CALLBACK_0( SelectLevelScene::goToLevel, this, numberOfLevel ));
}

void SelectLevelScene::setButtons()
{
    backButton = Button::create( "back_arrow.png" );
    backButton->setZoomScale( - 0.1f );
    
    leftButton = Button::create( "left_arrow.png" );
    leftButton->setZoomScale( - 0.1f );
    leftButton->setEnabled( true );
    
    rightButton = Button::create( "right_arrow.png" );
    rightButton->setZoomScale( - 0.1f );
    rightButton->setEnabled( true );
    
    
    backButton->addTouchEventListener([&](Ref* sender,
                                          Widget::TouchEventType type){
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                playButtonStartClick();
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                playButtonEndClick();
                goBackToInvokeScene( this );
                break;
            default:
                break;
        }
    });
    
    leftButton->addTouchEventListener([&](Ref* sender,
                                          Widget::TouchEventType type){
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                playButtonStartClick();
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                playButtonEndClick();
                loadPreviousSix( gameData->getNumberOfLeftUpperLevel() );
                goToSelectedLevelScene();
                break;
            default:
                break;
        }
    });
    
    rightButton->addTouchEventListener([&](Ref* sender,
                                          Widget::TouchEventType type){
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                playButtonStartClick();
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                playButtonEndClick();
                loadNextSix( gameData->getNumberOfLeftUpperLevel() );
                goToSelectedLevelScene();
                break;
            default:
                break;
        }
    });
}

void SelectLevelScene::setBackground()
{
    background = Sprite::create( "beach_bg_all.png" );
    background->setPosition( Point ( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    
    menuLayer = Sprite::create( "select_level_menu.png" );
    menuLayer->setPosition( Point ( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 50 ) );
}

void SelectLevelScene::goToSelectedLevelScene()
{
    DEBUG_INFO;
    auto scene = SelectLevelScene::createScene();
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME_BETWEEN_SCENE, scene ) );
}

void SelectLevelScene::goBackToInvokeScene( Ref *sender )
{
    Director::getInstance()->popScene();
}

void SelectLevelScene::goToLevel( int number )
{
    DEBUG_INFO;
    printf("number = %d\n", number);
    gameData->setCurrentLevel( number );
    gameData->writeDataToUserData();
    
    playChoseMenuSound();
    
    auto scene = GameScene::createScene();
    
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME_BETWEEN_SCENE, scene ) );
    
}

void SelectLevelScene::loadCurrentSix( int number )
{
    checkButtonsStatus( number );
    int firstNum = abs( number / 6 );
    
    DEBUG_INFO;
    printf("number = %d firstNum %d\n", number, firstNum);
    printf("Before set _gameData->getNumberOfLeftUpperLevel() = %d\n", gameData->getNumberOfLeftUpperLevel());
   
}

void SelectLevelScene::loadPreviousSix( int number )
{
    DEBUG_INFO;
    int firstLevelNumber = gameData->getNumberOfLeftUpperLevel() - 6;
    if( firstLevelNumber <= 1 ){
        firstLevelNumber = 1;
    }
    gameData->setNumberOfLeftUpperLevel( firstLevelNumber );
    showSixLevels(firstLevelNumber);
}

void SelectLevelScene::loadNextSix( int number )
{
    DEBUG_INFO;
    int firstLevelNumber = gameData->getNumberOfLeftUpperLevel() + 6;
    if( firstLevelNumber >= gameData->getLastLevelNumber() ){
        firstLevelNumber = gameData->getLastLevelNumber();
    }
    gameData->setNumberOfLeftUpperLevel( firstLevelNumber );
    showSixLevels(firstLevelNumber);
}

void SelectLevelScene::checkButtonsStatus( int currentLevelNumber )
{
    if ( gameData->getNumberOfLeftUpperLevel() == 1 )
    {
        leftButton->setEnabled( false );
    }
    else
    {
        leftButton->setEnabled( true );
    }
    
    if ( false == gameData->getOneLevelDataByLevelNumber(gameData->getNumberOfLeftUpperLevel() + 5).ld_isUnlocked )
    {
        rightButton->setEnabled( false );
    }
    else
    {
        if ( currentLevelNumber + 6 > maxLevelNumber )
        {
            rightButton->setEnabled( false );
        }
        else
        {
            rightButton->setEnabled( true );
        }
    }
}

void SelectLevelScene::loadMaxPlayedLevel()
{
    maxLevelPlayed = gameData->getLevelsPlayed();
}

void SelectLevelScene::loadMaxLevelNubmer()
{
    maxLevelNumber = gameData->getLastLevelNumber();
    DEBUG_INFO;
    log("setMaxLevelNumber %d", maxLevelNumber);
}

void SelectLevelScene::goToMainMenu()
{
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene( TransitionFade::create( TRANSITION_TIME_BETWEEN_SCENE, scene ) );
}

void SelectLevelScene::setCurrentLevel(int number)
{
    this->numberOfCurrentPlayedLevel = number;
}

int SelectLevelScene::getCurrentLevel()
{
    DEBUG_INFO;
    log("numberOfCurrentPlayedLevel %d\n", numberOfCurrentPlayedLevel);
    return numberOfCurrentPlayedLevel;
}

void SelectLevelScene::loadGameData()
{
    DEBUG_INFO;
    gameData = GameData::getGameData();
}

void SelectLevelScene::loadCurrentLevelNumberFromGameData()
{
    DEBUG_INFO;
    log("gameData->getCurrentLevelNumber() %d\n", gameData->getCurrentLevelNumber());
    setCurrentLevel(gameData->getCurrentLevelNumber());
}

void SelectLevelScene::loadMusicAndSoundEffects()
{
    musicData = MusicData::getMusicData();
}

void SelectLevelScene::playChoseMenuSound()
{
    musicData->playChoseMenuSound();
}

void SelectLevelScene::playChoseMenuSoundStart()
{
    musicData->playChoseMenuSoundStart();
}

void SelectLevelScene::playChoseMenuSoundEnd()
{
    musicData->playChoseMenuSoundEnd();
}

void SelectLevelScene::playButtonStartClick()
{
    musicData->playButtonStartClickSound();
}
void SelectLevelScene::playButtonEndClick()
{
    musicData->playButtonEndClickSound();
}

void SelectLevelScene::loadUserDataFromSelectedLevel( int level )
{
//    auto levelStatsFromDB = userData->getDataStruct()->oneLevelData[level];
    auto levelStatsFromDB = gameData->getOneLevelDataByLevelNumber(level);
    
    levelStats_isUnlocked = levelStatsFromDB.ld_isUnlocked;
    levelStats_levelNumber = levelStatsFromDB.ld_levelNumber;
    levelStats_stars = levelStatsFromDB.ld_stars;
    levelStats_fishEaten = levelStatsFromDB.ld_fishEaten;
    levelStats_score = levelStatsFromDB.ld_score;
    levelStats_playTime = levelStatsFromDB.ld_playTime;
    
}
