//
//  UserData.cpp
//  TestGame-mobile
//
//  Created by Madji on 11.06.19.
//

#include "UserData.hpp"
#include "Definitions.hpp"


UserData        *UserData::_userData;

extern int global_var;

UserData::UserData()
{
    
}

UserData::~UserData()
{
    
}

UserData *UserData::getInstance()
{
    if (!_userData)
    {
        return nullptr;
    }
    else
    {
        return _userData;
    }
}

UserData *UserData::getUserData()
{
    if( _userData == nullptr )
    {
        _userData = new UserData();
        
        if ( _userData->loadDataFromFile() < 0 )
        {
            _userData->initStats();
            _userData->saveDataToFile();
        }
    }
    
    return _userData;
}


void UserData::initStats()
{

    memset(&_dataStruct, '\0', sizeof(_dataStruct));
    int i;
    
    for (i = 1; i <= ALL_LEVELS; i++ )
    {
        
        /*
         Need for tet only - simulate registered user, who is played a few levels
         */
#ifdef USERISACTIVE
        _dataStruct.oneLevelData[i].ld_levelNumber = i;
        _dataStruct.oneLevelData[i].ld_isUnlocked = true;
        _dataStruct.oneLevelData[i].ld_stars = 2;
        _dataStruct.oneLevelData[i].ld_fishEaten = 10;
        _dataStruct.oneLevelData[i].ld_score = 123;
        _dataStruct.oneLevelData[i].ld_playTime = 90;
#else
        _dataStruct.oneLevelData[i].ld_levelNumber = i;
        _dataStruct.oneLevelData[i].ld_isUnlocked = false;
        _dataStruct.oneLevelData[i].ld_stars = 0;
        _dataStruct.oneLevelData[i].ld_fishEaten = 0;
        _dataStruct.oneLevelData[i].ld_score = 0;
        _dataStruct.oneLevelData[i].ld_playTime = 0;
#endif
    }
    
    _dataStruct.oneLevelData[1].ld_isUnlocked = true;
    
    
    /*
     Need for tet only - simulate registered user, who is played a few levels
     */
#ifdef USERISACTIVE
    _dataStruct.ds_levelsPlayed = ALL_LEVELS;
    _dataStruct.ds_isUserRegister = true;
    this->setUsername( "alo" );
#else
    _dataStruct.ds_levelsPlayed = 0;
    _dataStruct.ds_isUserRegister = false;
    this->setUsername( "" );
#endif
    
    _dataStruct.ds_defaultSharkLives = 5;
    _dataStruct.ds_currentSharkLives = 5;
    _dataStruct.ds_currentLevel = 1;
    _dataStruct.ds_numberOfLeftUpperLevel = 1;
    _dataStruct.ds_maxLevel = ALL_LEVELS;
    _dataStruct.ds_soundEffectsVolumeLevel = ( 0.50f );
    _dataStruct.ds_musicVolumeLevel = ( 0.50f );
    _dataStruct.ds_lastSaveTime = now;
    _dataStruct.ds_timeFirstLifeLose = MAX_TIME;
    _dataStruct.ds_timeSecondLifeLose = MAX_TIME;
    _dataStruct.ds_timeThirdLifeLose = MAX_TIME;
    _dataStruct.ds_timeFourthLifeLose = MAX_TIME;
    _dataStruct.ds_timeFifthLifeLose = MAX_TIME;
    
    DEBUG_INFO;
    log("UD Current Level %d left upper level %d\n", _dataStruct.ds_currentLevel, _dataStruct.ds_numberOfLeftUpperLevel);
    
}


dataStruct *UserData::getDataStruct()
{
    return &_dataStruct;
}


int UserData::loadDataFromFile()
{
    

    DEBUG_INFO;
    
    /*
        Used for test only. Did not load data from file.
     */
    
    
    DEBUG_INFO;
    
    return -1;
    
    auto fileToSave = FileUtils::getInstance()->getWritablePath() + "sgud.db";
    
    FILE *f = fopen( fileToSave.c_str(), "rb" );
    if ( f == nullptr ) {
        return -1;
    }
    
    fread( &_dataStruct, sizeof( _dataStruct ), 1, f );
    
    fclose( f );
    
//    printData();
    
    return 0;
}


int UserData::saveDataToFile()
{
    auto fileToSave = FileUtils::getInstance()->getWritablePath() + "sgud.db";
    
    FILE *f;
    
    f = fopen( fileToSave.c_str(), "wb" );
    
    if ( f == nullptr ) {
        return  -1;
    }
    
    fwrite( &_dataStruct, sizeof( _dataStruct ), 1, f );
    
    fclose( f );
    
//    printData();
    
    return 0;
}

long UserData::getCurrentTimeInSeconds()
{
    return time(&now);
}

void UserData::setUsername( std::string data )
{
    
    if ( strlen(data.c_str()) == 0 ) {
        data = "";
    }
    
    strcpy( _dataStruct.ds_username, &data[0] );
    
}

void UserData::saveUserData()
{
    saveDataToFile();
}

/*
 Need for test only - print all saved data
 */
#ifdef USERISACTIVE

void UserData::printData()
{
    
    auto testStruct = getDataStruct();
    
    log("row 167 - UserData::printData EFFECTS %f", _dataStruct.ds_soundEffectsVolumeLevel );
    log("row 167 - UserData::printData MUSIC %f",_dataStruct.ds_musicVolumeLevel);
    
    log("row 226 UD username %s", testStruct->ds_username);
    std::cout << std::boolalpha << testStruct->ds_isUserRegister << std::endl;
    
    log("UD row 170 default shark lives %d", testStruct->ds_defaultSharkLives);
    log("UD row 185 current shark lives %d", testStruct->ds_currentSharkLives);
    log("UD row 186 time first %lu", testStruct->ds_timeFirstLifeLose);
    log("UD row 187 time second %lu", testStruct->ds_timeSecondLifeLose);
    log("UD row 188 time thidt %lu", testStruct->ds_timeThirdLifeLose);
    log("UD row 189 time fourth %lu", testStruct->ds_timeFourthLifeLose);
    log("UD row 190 time fifth %lu", testStruct->ds_timeFifthLifeLose);
    
    log("UD row 185 current shark lives %d", _dataStruct.ds_currentSharkLives);
    log("UD row 186 time first %lu", _dataStruct.ds_timeFirstLifeLose);
    log("UD row 187 time second %lu", _dataStruct.ds_timeSecondLifeLose);
    log("UD row 188 time thidt %lu", _dataStruct.ds_timeThirdLifeLose);
    log("UD row 189 time fourth %lu", _dataStruct.ds_timeFourthLifeLose);
    log("UD row 190 time fifth %lu", _dataStruct.ds_timeFifthLifeLose);
    log("UD row 191 ----------------------------------");
    log("UD row 192 music level %f", _dataStruct.ds_musicVolumeLevel);
    log("UD row 193 effect level %f", _dataStruct.ds_soundEffectsVolumeLevel);
    
    
}

#endif


