#pragma once
/* Sprite Class
* Holds all information for individual sprites
*/

#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include<string>

class Graphics;	//Forward declare Graphics

class Sprite {
public:
	Sprite();

	/* This is the constructor we'll be using most often
	* sourceX is the x position the spritesheet, sourceY is the y position
	* width and height are the width and height of the sprite we're extracting from the spritesheet
	* posX and posY is their spawn point on screen
	*/
	Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY);

	virtual ~Sprite();
	virtual void update();	//Virtual because we'll have some stuff, but it will be overridden in animated sprites
	void draw(Graphics &graphics, int x, int y);

	//Might need to make getter/setter methods here for sourceX, sourceY, width, height, etc ... graphics too?

protected:
	SDL_Rect sourceRect;		//Where ont he spritesheet to get the sprite from
	SDL_Texture* spriteSheet;	//The spritesheet we're getting the sprite from
	float x, y;					//x and y position on screen

private:

};
#endif

