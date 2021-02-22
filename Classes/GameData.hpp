    //
    //  GameData.hpp
    //  TestGame-mobile
    //
    //  Created by Madji on 18.07.19.
    //  CHANGED

    #ifndef GameData_hpp
    #define GameData_hpp

    #pragma once
    #include <stdio.h>
    #include "cocos2d.h"
    #include "ui/CocosGUI.h"
    #include "Definitions.hpp"
    #include "UserData.hpp"
    #include "SharkLives.hpp"

    class UserData;
    class SharkLives;
    struct dataStruct;
    struct LevelData;

    using namespace cocos2d;

    class GameData {
    private:
        
        static GameData     *_gameData;
        
        UserData            *userData;
        SharkLives          *sharkLives;
        
        /*
         Needed for time calculate:
         - lose lives time
         - game time duration
         - game timer
         */
        time_t              now;
        long                getTimeStampInSeconds();
        
        /* Var from UserData */
        std::string         username;
        int                 defaultSharkLives;
        int                 currentSharkLives;
        int                 levelsPlayed;
        int                 currentLevel;
        int                 numberOfLeftUpperLevel;
        int                 maxLevel;
        bool                isUserRegister;
        
        long                timeFirstLifeLose;
        long                timeSecondLifeLose;
        long                timeThirdLifeLose;
        long                timeFourthLifeLose;
        long                timeFifthLifeLose;
        
        /* Levels Data */
        void                loadUserData();
        int                 earnedStars;
        int                 scoreCounter;
        int                 fishCounter;
        int                 timerCounter;
        
        /* Level Statistic */
        int                 pointsForFirstStar;
        int                 pointsForSecondStar;
        int                 pointsForThirdStar;
        int                 passLevelPoints;
        
        /* Game Settings */
        float               musicVolumeLevel;
        float               soundEffectsVolumeLevel;
        
        /* Gameplay var */
        int                 starsCounter;
        int                 countdownTimeCounter;
        int                 timerSeconds;
        int                 timerMinutes;
        void                calculateTimeForText( int time );
        void                setStarsCounter( int stars );
        void                calculateStars();
        void                setLevelsPlayed( int levelNum );
        void                increaseLevelsPlayed( int levelNum );
           
        GameData();
        virtual             ~GameData();
        
        
    public:
    
        
        static GameData     *getGameData();
        void                initStats();
        
        /* from UserData */
        
        void                getDataFromUserData();  /* load all user data from UserData */
        LevelData           getOneLevelDataByLevelNumber(int number);
        std::string         getUsername();
        int                 getDefaultSharkLives();
        int                 getCurrentSharkLives();
        int                 getLevelsPlayed();
        int                 getCurrentLevelNumber();
        int                 getNumberOfLeftUpperLevel();
        int                 getLastLevelNumber();
        bool                getUserRegisterStatus();
        
        long                getFirstLifeLoseTimer();
        long                getSecondLifeLoseTimer();
        long                getThirdLifeLoseTimer();
        long                getFourthLifeLoseTimer();
        long                getFifthLifeLoseTimer();

        void                writeDataToUserData();
        void                setUsername( std::string name );
        void                setDefaultSharkLives( int lives );
        void                setCurrentSharkLives( int lives );
        void                setCurrentLevel( int levelNum );
        void                setNumberOfLeftUpperLevel( int number );
        void                setLastLevelNumber( int levels );
        void                setUserRegisterStatus( bool status );
        
        void                setFirstLifeLoseTimer( long time);
        void                setSecondLifeLoseTimer( long time);
        void                setThirdLifeLoseTimer( long time);
        void                setFourthLifeLoseTimer( long time);
        void                setFifthLifeLoseTimer( long time);
        void                unlockLevel(int number );
        
        
        /* Levels Data */
        int                 getEarnedStarsFromLevelsData( int levelNumber );
        bool                checkLevelIsUnlockedFromLevelsData( int number );
        
        
        /* Level Statistic */
        GameData            loadlevelStatsByNumber( int number );
        int                 getToPassLevelPoints( int levelNumber );

        void                changeUsername( std::string newName );
        void                changeUserRegisterStatus( bool newStatus );
        
        /* Game Play Settigns */
        void                setInitialGamePlayValues();
        void                setMusicVolumeLevel(float level);
        float               getMusicVolumeLevel();
        
        void                setSoundEffectsVolumeLevel(float level);
        float               getSoundEffectsVolumeLevel();
        
        /* time calculations */
        int                 countdownTimerCounterDefaultSec;
        int                 countdownTimerCounterDefaultMin;
        
        void                setTimerCounter( int value );
        void                setScoreCounter( int value );
        void                setScoreCounterToZero();
        
        int                 getTimerCounter();
        void                setCountdownTimerCounter( int levelNum );
        void                setTimerCounterToZero();
        void                setTimerCounterToInitValue();
        void                increaseTimerCounter();
        void                decreaseTimerCounter();
        int                 getCountdownTimerCounter();
        
        void                increaseScore( int score );
        int                 getTimerMinutes();
        int                 getTimerSeconds();
        int                 getScoreCounter();

        void                setFishCounter( int fishes );
        void                increaseFishCounter();
        int                 getFishCounter();
        void                resetFishCounterToZero();

        int                 getStarsCounter();
        void                resetStarsCounter();

        void                decreaseSharkLives();
        void                increaseSharkLives();
    };


    #endif /* GameData_hpp */
