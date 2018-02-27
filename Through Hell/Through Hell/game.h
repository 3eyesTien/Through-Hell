#pragma once
/*Game class
 * This clas will hold all information for our main game loop
 */

#ifndef GAME_H
#define GAME_H

#include "sprite.h"

class Graphics;

class Game{

public:
	Game();
	~Game();

private:
	void gameLoop();
	void draw(Graphics &graphics);
	void update(float elapsedTime);
	Sprite sprite;
};
#endif