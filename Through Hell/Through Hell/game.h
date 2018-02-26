#pragma once
/*Game class
 * This clas will hold all information for our main game loop
 */

#ifndef GAME_H
#define GAME_H

class Graphics;

class Game{

public:
	Game();
	~Game();

private:
	void gameLoop();
	void draw(Graphics &graphics);
	void update(float elapsedTime);
};
#endif