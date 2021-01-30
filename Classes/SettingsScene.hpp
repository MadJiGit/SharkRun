//
//  SettingsScene.hpp
//  TestGame
//
//  Created by Madji on 9.05.19.
//

#ifndef SettingsScene_hpp
#define SettingsScene_hpp

#pragma once

#include <stdio.h>
#include "cocos2d.h"
#include "MainMenuScene.hpp"
#include "GameScene.hpp"
#include "SimpleSlider.h"
#include "UserData.hpp"
#include "MusicData.hpp"

#include "ui/CocosGUI.h"

using namespace cocos2d;

class SettingsScene : public Layer
{
private:
    
    GameScene       *gameScene;
    Size            visibleSize;
    Vec2            origin;
    
    Sprite          *background, *menuLayer;
    
    Menu            *menu;
    Button          *closeButton, *okButton;
    
    Label           *musicVolumeLevelTextLabel, *soundEffectsVolumeLevelTextLabel, *percentMusicVolumeLabel, *percentSoundEffectsVolumeLabel;
    
    cocos2d::ui::Slider          *musicVolumeSlider, *soundEffectsVolumeSlider;
    
    float             loadMusicVolumeLevelFromFile, loadSoundEffectsVolumeLevelFromFile;
    
    UserData        *_userData;
    dataStruct      *_dataStruct;
    MusicData       *_musicData;
    
    void            setBackground();
    void            setButtons();
    void            setMusicVolumeSlider();
    void            setSoundEffectsVolumeSlider();
    void            setMusicVolumeLevel();
    void            setSoundEffectsVolumeLevel();
    
    void            displayMusicVolumeLevel( int data );
    void            displaySoundEffectsVolumeLevel( int data );
    
    void            exitSettingsScene( Ref *sender );
    void            saveSettingsScene( Ref *sender );
    
    void            loadMusicAndSoundEffects();
    void            playMusic();
    void            updateMusicVolumeLevel( float dt );
    void            updateEffectsVolumeLevel( float dt );
    void            playButtonStartClick();
    void            playButtonEndClick();
    void            pauseGameMusic();
    
public:
    
    static Scene    *createScene();
    
    virtual bool    init();
    
    void            removeMenu();
    
    CREATE_FUNC( SettingsScene );
};

#endif /* SettingsScene_hpp */
