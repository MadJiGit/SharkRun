//
//  GameOverScene.hpp
//  TestGame
//
//  Created by Madji on 9.05.19.
//

#ifndef GameOverScene_hpp
#define GameOverScene_hpp

#pragma once

#include <stdio.h>
#include "cocos2d.h"
#include "MainMenuScene.hpp"
#include "GameScene.hpp"
#include "MusicData.hpp"

using namespace cocos2d;

class GameOverScene : public Layer
{
private:
    
    Size            visibleSize;
    Vec2            origin;
    MenuItemImage   *closeButton, *mainMenuLabel, *gameMenuLabel, *returnBackLabel;
    
    Sprite          *background;
    Menu            *menu;
    MusicData       *musicData;
    
    void setBackground();
    void setReturnBack();
    void setMainMenuLabel();
    void setGameMenuLabel();
    void setCloseButton();
    
    void returnBack();
    void goToMainMenuScene( Ref *sender );
    void goToGameScene( Ref *sender );
    void exitGameScene( Ref *sender );
    
public:
    
    static Scene *createScene( );
    virtual bool init( );
    
    CREATE_FUNC( GameOverScene );
};

#endif /* GameOverScene_hpp */
