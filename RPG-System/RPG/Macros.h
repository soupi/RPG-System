#pragma once

const float PRESS_INTERVAL = 1.f/3;


// For Controller
const int WINDOW_W = 960;
const int WINDOW_H = 540; 
const unsigned FRAME_RATE = 60;

// for Tile
const unsigned TILE_SIZE = 32;
const unsigned SCRN_TILE_SIZE = 64;

const float HERO_SPEED = 250.f;
const float DEFAULT_SPEED = 3.f*SCRN_TILE_SIZE; // three tiles per second

// for graphics
const float ANIMATION_SPEED = 0.2f;

enum DIRECTION {
	DOWN_DIR  = 0,
	LEFT_DIR  = 1,
	RIGHT_DIR = 2,
	UP_DIR	  = 3
};