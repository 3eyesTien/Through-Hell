/* Sprite class
* Holds all information for individual sprites
*/

#include "sprite.h"
#include "graphics.h"
#include "globals.h"

Sprite::Sprite(){}

Sprite::Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY) : x(posX), y(posY)
{
	this->sourceRect.x = sourceX;
	this->sourceRect.y = sourceY;
	this->sourceRect.w = width;
	this->sourceRect.h = height;

	this->spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
	if (this->spriteSheet == NULL)
	{
		printf("\nError: Unable to load image\n");
	}
}

Sprite::~Sprite() {}

void Sprite::draw(Graphics &graphics, int x, int y)
{
	//An SDL_Rect defines a rectangular area of the screen.  
	//It is used by SDL_BlitSurface() to define blitting regions and by several other video functions.
	SDL_Rect destinationRectangle = { x, y, this->sourceRect.w * globals::SPRITE_SCALE, this->sourceRect.h * globals::SPRITE_SCALE };	//Draw onto the screen at this x and y with the width and height of the source rectangle

	graphics.blitSurface(this->spriteSheet, &this->sourceRect, &destinationRectangle);	//Blit the drawing onto the surface
}

void Sprite::update()
{

}