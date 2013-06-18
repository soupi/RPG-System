#pragma once

#include <string>

const float PRESS_INTERVAL = 1.f/3;
const sf::Vector2f PADDING = sf::Vector2f(20.f, 20.f);
const float ENEMY_ATTACK_INTERVAL = 1.f;

// for heroData
const unsigned BASE_HP = 200;
const unsigned EXTRA_LIVES = 0;
const unsigned LEARN_BULLET_ATTACK_LEVEL = 4;

// For Controller
const int WINDOW_W = 960;
const int WINDOW_H = 540; 
const unsigned FRAME_RATE = 60;

// for Tile
const unsigned TILE_SIZE = 32;
const unsigned SCRN_TILE_SIZE = 64;

const float DEFAULT_SPEED = 3.f*SCRN_TILE_SIZE; // three tiles per second
const float HERO_SPEED = DEFAULT_SPEED;

// for graphics
const float ANIMATION_SPEED = 0.2f;

enum DIRECTION {
	DOWN_DIR  = 0,
	LEFT_DIR  = 1,
	RIGHT_DIR = 2,
	UP_DIR	  = 3
};

// for dialogs
const unsigned TEXT_SPEED = 32; // letters per second

// for menu
const int BAD = -1;

// for attack
const int BASIC_ATTACK_POWER = 7;
const int BULLET_ATTACK_POWER = 5;

// for credits
const std::string CREDITS = "  THE WHITE STAR\n\nA game by Gil Mizrahi\n\n- Made as a final project in\n  OOP2 Class 2013\n  Hadassah College";