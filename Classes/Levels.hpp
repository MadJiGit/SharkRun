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
    int         enemyType;          /* barrel - 1, mine - 2, submarine - 3, rocket - 4 */
    float       spawnTime;          /* time to push the next enemy */
    float       speedMin;           /* min speed of sprite */
    float       speedMax;           /* max speed of sprite */
};

struct fishStruct
{
    /* small - 1, medium - 2, star - 3, heart - 4 */
    float       fishSpawnTime;      /* time to push the next fish */
    float       heartSpawnTime;     /* time to push heart */
};

struct levelStruct
{
    int         levelNumber;
    int         oneStarPoint;       /*  points to win first star */
    int         twoStarsPoint;      /*  points to win second star */
    int         threeStarsPoint;    /*  points to win third star */
    int         passLevelPoints;    /*  earned points to pass the level */
    int         passLevelTime;      /*  needed played time to pass the level */
};

struct enemyStat
{
    struct enemyStruct  enemy[4];
};

struct fishStat
{
    /* at the moment use only data for spawn fish [1] */
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
