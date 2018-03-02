/*Player class
 * Holds all information for the player
 */
#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "animatedSprite.h"
#include "globals.h"

class Graphics;

class Player : public AnimatedSprite
{
	Player(Graphics &graphics);
	Player(Graphics &graphics, float x, float y);

	void update(float elapsedTime);
	void draw(Graphics &graphics);
	
	virtual void animationDone(std::string currentAnimation);
	void animationDone(std::string currentAnimation, bool done);
	virtual void setupAnimations();

private:
	float dx, dy;

	Direction facing;
};
#endif