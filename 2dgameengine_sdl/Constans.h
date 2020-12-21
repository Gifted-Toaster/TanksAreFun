#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL.h>

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

const unsigned int CONSOLE_WIDTH = 800;
const unsigned int CONSOLE_HEIGHT = 0;


// This should be defined from the script files map details (X*scale*size)
const unsigned int MAP_WIDTH = 1600;
const unsigned int MAP_HEIGHT = 1280;

const unsigned int FPS = 120;
const unsigned int FRAME_TARGET_TIME = 1000.0f / FPS;

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	DEFAULT
};

enum CollisionType {
	NO_COLLISION,
	PLAYER_ENEMY_COLLISION,
	PLAYER_PROJECTILE_COLLISION,
	ENEMY_PROJECTILE_COLLISION,
	PLAYER_VEGETATION_COLLISION,
	PLAYER_LEVEL_COMPLETE_COLLISION
};

enum ComponentType {
	TRANSFORM,
	COLLIDER,
	HEALTH,
	KEYBOARD,
	PROJECTILE_EMITTER,
	SPRITE,
	TEXTLABEL,
	TILE
};

/*
Enumerator type for button action
*/
enum ButtonType {
	START = 0,
	SETTINGS = 1,
	EXIT = 2
};

// For rendering
enum LayerType {
	TILEMAP_LAYER = 0,
	VEGETATION_LAYER = 1,
	OBSTACLE_LAYER = 2,
	ENEMY_LAYER = 3,
	PLAYER_LAYER = 4,
	PROJECTILE_LAYER = 5,
	UI_LAYER = 6
};

// csinalj egy egysegesitett entitytype-ot hogy ne nevszerint kelljen hivatkozni az 
// objektumokra a kodban, hiszen lehet tobbfele enemy is mint tank pl
enum EntityType {
	STATIC,
	DINAMIC
};

// Number of the layers
const unsigned int NUM_LAYERS = 7;

// Colors
const SDL_Color WHITE_COLOR = { 255 , 255 , 255 ,255 };
const SDL_Color GREEN_COLOR = { 0, 255 , 0 , 255 };

// LEVELS
enum Levels {
	MAIN_MENU = 0,
	LEVEL1 = 1,
	LEVEL2 = 2,
	LEVEL3 = 3
};

#endif