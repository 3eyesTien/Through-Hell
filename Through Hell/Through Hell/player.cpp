#include "player.h"
#include "graphics.h"

namespace player_constants
{
	
}

Player::Player(Graphics &graphics) 
{
	graphics.loadImage("Assets/aerial_knee_frames cut.png");
	this->setupAnimations();
	//AnimatedSprite(graphics, name of animation, screenX, screenY);
}

Player::Player(Graphics &graphics, float x, float y) : 
		AnimatedSprite(graphics, "Assets/aerial_knee_frames cut.png", 65, 3, 19, 36, 100, 100, 60) 
{
	graphics.loadImage("Assets/aerial_knee_frames cut.png");
	this->setupAnimations();	//Setup Player animations
//	this->playAnimation("");
	
	this->facing = RIGHT;
}

void Player::setupAnimations()
{
	this->addAnimation(3, "knee", 65, 3, 19, 36, Vector2(0, 0));//num frames, std::string name, source x, source y,  int width, int height, vector2 offset
}