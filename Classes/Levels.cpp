//
//  Levels.cpp
//  TestGame-mobile
//
//  Created by Madji on 11.06.19.
//

#include "Levels.hpp"

struct enemyStat enemyData[] = {
    
        // default
    {{
        //type, time, speedMin, speedMax
        { 1, 0, 0, 0 }, // barrel,
        { 2, 0, 0, 0 }, // mine
        { 3, 0, 0, 0 }, // submarine
        { 4, 0, 0, 0 }, // rocket
    }},
        // level 1
    {{
        { 1, 1, 0, 0 },
        { 2, 0.020, 30, 30 },
        { 3, 0, 0, 0 },
        { 4, 0, 0, 0 },
    }},
    // level 2
    {{
        { 1, 1.0, 0, 0 },
        { 2, 0.018, 15, 15 },
        { 3, 0, 0, 0 },
        { 4, 0, 0, 0 },
    }},
    // level 3
    {{
        { 1, 1.0, 0, 0 },
        { 2, 0.018, 15, 15 },
        { 3, 0, 0, 0 },
        { 4, 0, 0, 0 },
    }},
    // level 4
    {{
        { 1, 0.021, 20, 20 },
        { 2, 0.017, 15, 15 },
        { 3, 0, 0, 0 },
        { 4, 0, 0, 0 },
    }},
    // level 5
    {{
        { 1, 0.0300, 20, 20 },
        { 2, 0.0300, 15, 15 },
        { 3, 0, 0, 0 },
        { 4, 0, 0, 0 },
    }},
    // level 6
    {{
        { 1, 0.055, 20, 20 },
        { 2, 0.045, 15, 15 },
        { 3, 0, 0, 0 },
        { 4, 0, 0, 0 },
    }},
    // level 7
    {{
        { 1, 0.055, 20, 20 },
        { 2, 0.045, 15, 15 },
        { 3, 0, 0, 0 },
        { 4, 0, 0, 0 },
    }},
    // level 8
    {{
        { 1, 0.055, 20, 20 },
        { 2, 0.045, 15, 15 },
        { 3, 0, 0, 0 },
        { 4, 0, 0, 0 },
    }},
    // level 9
    {{
        { 1, 0.055, 20, 20 },
        { 2, 0.045, 15, 15 },
        { 3, 0, 0, 0 },
        { 4, 0, 0, 0 },
    }},
    // level 10
    {{
        { 1, 0.055, 20, 20 },
        { 2, 0.045, 15, 15 },
        { 3, 0, 0, 0 },
        { 4, 0, 0, 0 },
    }},
    // level 11
    {{
        { 1, 0.055, 20, 20 },
        { 2, 0.045, 15, 15 },
        { 3, 0, 0, 0 },
        { 4, 0, 0, 0 },
    }},
    // level 12
    {{
        { 1, 0.055, 20, 20 },
        { 2, 0.045, 15, 15 },
        { 3, 0, 0, 0 },
        { 4, 0, 0, 0 },
    }},
    // level 13
    {{
        { 1, 0.055, 20, 20 },
        { 2, 0.045, 15, 15 },
        { 3, 0, 0, 0 },
        { 4, 0, 0, 0 },
    }},
    // level 14
    {{
        { 1, 0.055, 20, 20 },
        { 2, 0.045, 15, 15 },
        { 3, 0, 0, 0 },
        { 4, 0, 0, 0 },
    }},
    // level 15
    {{
        { 1, 0.055, 20, 20 },
        { 2, 0.045, 15, 15 },
        { 3, 0, 0, 0 },
        { 4, 0, 0, 0 },
    }},
    // level 16
    {{
        { 1, 0.055, 20, 20 },
        { 2, 0.045, 15, 15 },
        { 3, 0, 0, 0 },
        { 4, 0, 0, 0 },
    }},
    // level 17
    {{
        { 1, 0.055, 20, 20 },
        { 2, 0.045, 15, 15 },
        { 3, 0, 0, 0 },
        { 4, 0, 0, 0 },
    }},
    // level 18
    {{
        { 1, 0.055, 20, 20 },
        { 2, 0.045, 15, 15 },
        { 3, 0, 0, 0 },
        { 4, 0, 0, 0 },
    }},
    
};


struct fishStat fishData[] = {
    // default
    {{
        { 0.0, 0.0 },
    }},
    // level 1
    {{
        { 0.0080, 0.0100 },
    }},
    // level 2
    {{
        { 0.0080, 0.0100 },
    }},
    // level 3
    {{
        { 0.0080, 0.0100 },
    }},
    // level 4
    {{
        { 0.0080, 0.0100 },
    }},
    // level 5
    {{
        { 0.0080, 0.0100 },
    }},
    // level 6
    {{
        { 0.0080, 0.0100 },
    }},
    // level 7
    {{
        { 0.0080, 0.0100 },
    }},
    // level 8
    {{
        { 0.0080, 0.0100 },
    }},
    // level 9
    {{
        { 0.0080, 0.0100 },
    }},
    // level 10
    {{
        { 0.0080, 0.0100 },
    }},
    // level 11
    {{
        { 0.0080, 0.0100 },
    }},
    // level 12
    {{
        { 0.0080, 0.0100 },
    }},
    // level 13
    {{
        { 0.0080, 0.0100 },
    }},
    // level 14
    {{
        { 0.0080, 0.0100 },
    }},
    // level 15
    {{
        { 0.0080, 0.0100 },
    }},
    // level 16
    {{
        { 0.0080, 0.0100 },
    }},
    // level 17
    {{
        { 0.0080, 0.0100 },
    }},
    // level 18
    {{
        { 0.0080, 0.0100 },
    }},
    // level 13
    {{
        { 0.0080, 0.0100 },
    }},
    // level 14
    {{
        { 0.0080, 0.0100 },
    }},
    // level 15
    {{
        { 0.0080, 0.0100 },
    }},
    // level 16
    {{
        { 0.0080, 0.0100 },
    }},
    // level 17
    {{
        { 0.0080, 0.0100 },
    }},
    // level 18
    {{
        { 0.0080, 0.0100 },
    }},
    // level 19
    {{
        { 0.0080, 0.0100 },
    }},
    // level 20
    {{
        { 0.0080, 0.0100 },
    }},
    // level 21
    {{
        { 0.0080, 0.0100 },
    }},
    // level 22
    {{
        { 0.0080, 0.0100 },
    }},
    // level 23
    {{
        { 0.0080, 0.0100 },
    }},
    // level 24
    {{
        { 0.0080, 0.0100 },
    }},
    // level 25
    {{
        { 0.0080, 0.0100 },
    }},
    // level 26
    {{
        { 0.0080, 0.0100 },
    }},
    // level 27
    {{
        { 0.0080, 0.0100 },
    }},
    // level 28
    {{
        { 0.0080, 0.0100 },
    }},
    // level 29
    {{
        { 0.0080, 0.0100 },
    }},
    // level 30
    {{
        { 0.0080, 0.0100 },
    }},

};


struct levelStat levelData[] = {
    // default
    /* level num,
                one star, two stars, three stars,
                                                pass level points, pass level time(sec)
     */
    
    {
        { 0, 0, 0, 0, 0, 0 },
    },
// 1 screen
    // level 1
    {{
        { 1, 50, 90, 130, 100, PASSLEVELTIME },
    }},
    // level 2
    {{
        { 2, 60, 100, 140, 120, PASSLEVELTIME },
    }},
    // level 3
    {{
        { 3, 70, 120, 180, 140, PASSLEVELTIME },
    }},
    // level 4
   {{
       { 4, 80, 130, 190, 160, PASSLEVELTIME },
   }},
    // level 5
   {{
       { 5, 20, 50, 200, 100, PASSLEVELTIME },
   }},
    // level 6
   {{
       { 6, 70, 120, 270, 170, PASSLEVELTIME },
   }},
    
// 2 screen
    // level 7
    {{
        { 7, 70, 120, 170, 170, PASSLEVELTIME },
    }},
    // level 8
    {{
        { 8, 70, 120, 170, 170, PASSLEVELTIME },
    }},
    // level 9
    {{
        { 9, 70, 120, 170, 170, PASSLEVELTIME },
    }},
    // level 10
    {{
        { 10, 70, 120, 170, 170, PASSLEVELTIME },
    }},
    // level 11
    {{
        { 11, 70, 120, 170, 170, PASSLEVELTIME },
    }},
    // level 12
    {{
        { 12, 70, 120, 170, 170, PASSLEVELTIME },
    }},
    
// 3 screen
    // level 13
    {{
        { 13, 70, 120, 170, 170, PASSLEVELTIME },
    }},
    // level 14
    {{
        { 14, 70, 120, 170, 170, PASSLEVELTIME },
    }},
    // level 15
    {{
        { 15, 70, 120, 170, 170, PASSLEVELTIME },
    }},
    // level 16
    {{
        { 16, 70, 120, 170, 170, PASSLEVELTIME },
    }},
    // level 17
    {{
        { 17, 70, 120, 170, 170, PASSLEVELTIME },
    }},
    // level 18
    {{
        { 18, 70, 120, 170, 170, PASSLEVELTIME },
    }},
 
// 4 screen
    // level 19
    {{
        { 19, 70, 120, 170, 170, PASSLEVELTIME },
    }},
    // level 20
    {{
        { 20, 70, 120, 170, 170, PASSLEVELTIME },
    }},
    // level 21
    {{
        { 21, 70, 120, 170, 170, PASSLEVELTIME },
    }},
    // level 22
    {{
        { 22, 70, 120, 170, 170, PASSLEVELTIME },
    }},
    // level 23
    {{
        { 23, 70, 120, 170, 170, PASSLEVELTIME },
    }},
    // level 24
    {{
        { 24, 70, 120, 170, 170, PASSLEVELTIME },
    }},
    
// 5 screen
    // level 25
    {{
        { 25, 70, 120, 170, 170, PASSLEVELTIME },
    }},
    // level 26
    {{
        { 26, 70, 120, 170, 170, PASSLEVELTIME },
    }},
    // level 27
    {{
        { 27, 70, 120, 170, 170, PASSLEVELTIME },
    }},
    // level 28
    {{
        { 28, 70, 120, 170, 170, PASSLEVELTIME },
    }},
    // level 29
    {{
        { 29, 70, 120, 170, 170, PASSLEVELTIME },
    }},
    // level 30
    {{
        { 30, 70, 120, 170, 170, PASSLEVELTIME },
    }},
        
// 6 screen
    
};
