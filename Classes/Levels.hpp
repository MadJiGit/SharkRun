//
//  Levels.hpp
//  TestGame-mobile
//
//  Created by Madji on 11.06.19.
//

#ifndef Levels_hpp
#define Levels_hpp

#pragma once
#include <stdio.h>
#include "Definitions.hpp"

struct enemyStruct
{
    // barrel - 1, mine - 2, submarine - 3, rocket - 4
    int         enemyType;
    float       spawnTime;
    float       speedMin;
    float       speedMax;
};

struct fishStruct
{
    // small - 1, medium - 2, star - 3, heart - 4
    
    float       fishSpawnTime;
    float       heartSpawnTime;
};

struct levelStruct
{
    int         levelNumber;
    int         oneStarPoint;
    int         twoStarsPoint;
    int         threeStarsPoint;
    int         passLevelPoints;
    int         passLevelTime;
};

struct enemyStat
{
    struct enemyStruct  enemy[4];
};

struct fishStat
{
    struct fishStruct  fish[1];
};

struct levelStat
{
    struct levelStruct  level[1];
};

extern struct enemyStat enemyData[];
extern struct fishStat fishData[];
extern struct levelStat levelData[];


#endif /* Levels_hpp */
