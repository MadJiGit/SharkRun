//
//  Definitions.hpp
//  TestGame
//
//  Created by Madji on 9.05.19.
//

#ifndef Definitions_hpp
#define Definitions_hpp

// print some stuff for debuging
#define DEBUGING 1
#define USERISACTIVE 1

// Print debug flow
#if DEBUGING
static int debug_counter;
#define DEBUG_INFO printf("%d %s %d %s\n", debug_counter++, __FILE_NAME__, __LINE__, __FUNCTION__);
#else
#define DEBUG_INFO
#endif



#define MAX_TIME 2000000000
//
//// GAME SCENE
#define FONT "fonts/PassionOne-Regular.ttf"
#define FONT_ROBOTO "fonts/Roboto-Black.ttf"
#define SCORE_FONT_SIZE 0.06
//
//#define CUSTOM_DELTA_TIME 0.0167

// SCENE
#define DISPLAY_TIME_SCENE 2
#define TRANSITION_TIME_BETWEEN_SCENE 0.5
#define TRANSITION_TIME_BETWEEN_WELCOME_AND_MAIN_MENU_SCENES 0.0
#define SHARK_SCENE_TAG 100
#define BARREL_SCENE_TAG 95
#define FISH_SCENE_TAG_MIN 91
#define FISH_SCENE_TAG_MAX 99
#define MINE_SCENE_TAG 75

// MAIN MENU
#define COEFFICIENT_TO_SCALE_MAIN_MENU_LABEL 1.0
#define COEFFICIENT_TO_SCALE_MAIN_MENU_BUTTON 1.0
#define OFFSET_LABEL_Y 1.1
#define OFFSET_BUTTONS_X 1.2


// WELCOME
#define COEFFICIENT_TO_SCALE_BACKGROUND_WELCOME_SCENE 1.0
#define COEFFICIENT_TO_SCALE_LOGO 1.4
#define TIME_TO_SCALE_LOGO 2.5
#define TIME_TO_MOVE_LOGO 2.5
#define COEFFICIENT_TO_SCALE_PLAY_BUTTON 1.0
#define COEFFICIENT_TO_SCALE_CLOSE_BUTTON 1.0
#define TIME_TO_SCALE_PLAY_BUTTON 2
#define DEFAULT_DELAY_TIME 1.0f

// PAUSE MENU
#define PAUSE_MENU_BACKGROUND_SCALE 1.0
#define PAUSE_MENU_LAYER_SCALE 1.0
#define BUTTON_RESUME_SETTINGS_SCALE 1.0
#define BUTTON_RETRY_CHANGE_SCALE 1.0
#define BUTTON_CLOSE_SCALE 1.5
#define OFFSET_X_PARAM 20

// SETTINGS MENU
//#define SETTINGS_MENU_BUTTON_SCALE 1.0
//#define SETTINGS_MENU_BACKGROUND_SCALE 1.0
//#define SETTINGS_MENU_LAYER_SCALE 1.0
//#define SETTINGS_MENU_SLIDER_SCALE 1.0

// SELECT LEVELS MENU
#define SELECT_LEVEL_MENU_LAYER_SCALE 1
#define SELECT_LEVEL_LR_BUTTONS_SCALE 1
#define SELECT_LEVEL_BACK_BUTTON_SCALE 1
#define SELECT_LEVEL_MENU_BACKGROUND_SCALE 1

// YOU FAILD MENU
#define FAILD_MENU_BACKGROUND_SCALE 1.0
#define FAILD_MENU_LAYER_SCALE 1.0
#define FAILED_MENU_BUTTONS_SCALE 1.0

// LEVEL COMPLETE MENU
#define LEVEL_COMPLETE_MENU_BACKGROUND_SCALE 1
#define LEVEL_COMPLETE_MENU_LAYER_SCALE 1.05
#define LEVEL_COMPLETE_MENU_BUTTONS_SCALE 1
#define LEVEL_COMPLETE_MENU_PLAY_BUTTON_SCALE 1
#define LEVEL_COMPLETE_STAR_SCALE 1

// GAME SCENE
//#define TIME_FOR_UPDATE_BACKGROUND 1/50
#define SPEED_BACKGROUND_1 1.5
#define SPEED_BACKGROUND_2 3
#define SPEED_BACKGROUND_3 4.5
#define BOTTOM_POSITION 80

// UI
#define SCALE_PAUSE_BUTTON 1.0
#define STAR_SCALE_PARAM 1.0

// SHARK
#define TIME_TO_MOVE_SHARK_TO_GAME_POSITION 2
#define SHARK_SCALE_PARAM 1.3
#define SPEED_SHARK_TO_GAME_POSITION
#define SHARK_FALLING_SPEED_I 8
#define SHARK_FALLING_SPEED_II 6
#define SHARK_FALLING_SPEED_III 4
#define SHARK_FALLING_SPEED_IV 2
#define SHARK_RISING_TIME_COUNTER 10
#define SHARK_DOWN_COUNTER 0
#define SHARK_REST_COUNTER -1
#define SHARK_MOVE_DURATION_DEFAULT 0.50
#define SHARK_HEAD_UP_TIME 0.25
#define SHARK_HEAD_DOWN_TIME 0.40
#define SHARK_HEAD_ZERO_TIME 0.40
#define SHARK_HEAD_ROTATION 10.00
#define SHARK_HEAD_ZERO 0.00
#define SHARK_ADDITIONAL_LIFE_COUNT 5
#define SHARK_SCALE_PARAM_ADDITIONAL_LIFE 1.0

// ADDITIONALS SHARK LIFES - 300 - 600 - 900 - 1200 - 1500
#define TIME_FOR_RETURN_FIRST_SHARK_LIVE_IN_SECONDS 30
#define TIME_FOR_RETURN_SECOND_SHARK_LIVE_IN_SECONDS 60
#define TIME_FOR_RETURN_THIRD_SHARK_LIVE_IN_SECONDS 90
#define TIME_FOR_RETURN_FOURTH_SHARK_LIVE_IN_SECONDS 120
#define TIME_FOR_RETURN_FIFTH_SHARK_LIVE_IN_SECONDS 150


// COLLISION shark number is
#define CATEGORY_MASK_SHARK         1       //  0000 0001
#define CATEGORY_MASK_BACKGROUND    2       //  0000 0010
#define CATEGORY_MASK_BARREL        4       //  0000 0100
#define CATEGORY_MASK_FISH          8       //  0000 1000
#define CATEGORY_MASK_MINE          16      //  0001 0000
#define CATEGORY_MASK_CHAIN         32      //  0010 0000

#define COLLISION_MASK_SHARK        2       //  background
#define COLLISION_MASK_BACKGROUND   5       //  shark & barrel
#define COLLISION_MASK_BARREL       6       //  background & barrel
#define COLLISION_MASK_FISH         0
#define COLLISION_MASK_MINE         0

#define CONTACT_MASK_SHARK          30      //  background & barrel & fish & mine
#define CONTACT_MASK_BACKGROUND     5       //  shark & barrel
#define CONTACT_MASK_BARREL         3       //  shark & background
#define CONTACT_MASK_FISH           9       //  shark & fish
#define CONTACT_MASK_MINE           1       //  shark

// BARREL
#define MINIMUM_WIDTH_BAREL_POSITION_X 1200
#define MAXIMUM_WIDTH_BAREL_POSITION_X 2300
#define MINIMUM_WIDTH_BAREL_POSITION_Y 1200
#define MAXIMUM_WIDTH_BAREL_POSITION_Y 1900
#define BARREL_FINISH_OFFSET 40
//#define DEFAULT_FALLING_BARREL_SPEED  0.0050
//#define TIME_BARREL_MOVE_DOWN  20.0
#define DEFAULT_BARREL_ROTATION_DEGREE 720
#define DEFAULT_BARREL_ROTATION_SPEED_MAX 60.0
#define DEFAULT_BARREL_ROTATION_SPEED_MIN 30.0
#define PUSH_BARREL_FREQUENCY 0.0500
#define BARREL_SCALE_PARAM 1.0
#define BARREL_PHYSIC_PARAM 0.8

// FISH
#define FISH_SCALE_PARAM 1.0
#define TIME_FISH_MOVE_MIN 5.0 // 15.0 default
#define TIME_FISH_MOVE_MAX 15.0 // 45.0 default
#define PUSH_FISH_FREQUENCY 0.0080
#define FISH_PHYSIC_PARAM 0.8

// MINE
#define PUSH_MINE_FREQUENCY 0.0200
#define MINE_SCALE_PARAM 1.0
//#define TIME_MINE_MOVE 30.0
#define MINE_PHYSIC_DIVIDE_PARAM 3.5
#define LONG_CHAIN_PARAM 0.65

// BUTTONS


// LEVELS
#define ALL_LEVELS 48

// STARS POINTS
#define ONE_STAR_POINTS 20
#define TWO_STARS_POINTS 70
#define THREE_STARS_POINTS 120


#endif /* Definitions_hpp */