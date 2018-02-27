/* AnimatedSprite class
 * Contains logic for animating sprite
 */

#include "animatedSprite.h"
#include "graphics.h"

AnimatedSprite::AnimatedSprite() {}

AnimatedSprite::AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float timeToUpdate) :
	Sprite(graphics, filePath, sourceX, sourceY, width, height, posX, posY),
	//Sprite(),
	frameIndex(0),
	timeToUpdate(timeToUpdate),
	visible(true),
	currentAnimationOnce(false),
	currentAnimation(""),
	timeElapsed(0)	// Initialize at 0. Sometimes when you don't it starts as a ridiculously high negative number
{}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset) {
	std::vector<SDL_Rect> rectangles;	//Tamp var to hold rectangles that have the sprites facing right

	//Add file i/o right here
	//Create animations and hitboxes from text scripts
	//Pseudo code:
	/*
	read filepath,
	load document with the name of the animation
	Scan the file for how many [Begin Frame] counts there are
	set int frames = [Begin Frame] count
	*/

	for (int i = 0; i < frames; i++)
	{
		/*The program should read through the text script starting at {Animation Name}.
		Do a do while() until [End Animation].
		For each [Begin Frame], it'll go through each line and record x, y, width, and height, time
		until it hits [End Frame]
		It'll create that SDL_Rect and push it onto the 'rectangles' vector.

		Sample script:
		{Animation Name} Iron-Knee
		[Begin Animation]
		[Begin Frame]
		x: 0
		y: 0
		width: 20
		height: 20
		time: 6		//Number of frames (MS or sec?) per second the frame lasts for
		Tag:	None
		Camera-Shake: None
		[End Frame]

		[Begin Frame]
		x: 0
		y: 0
		width: 20
		height: 20
		time: 1		//Number of frames (MS or sec?) per second the frame lasts for
		Tag: WALL-STICK, HARD-KNOCKDOWN
		//WALL-STICK should put the enemy in a WALL-STICK hurt state where they will stick to the camera edge instead of flying offscreen.
		//HARD-KNOCKDOWN should put the enemy in a hurt state where they will always take a second to get back up (no teching off the ground).  This should apply camera shake when they hit the ground.
		Camera-Shake:	Heavy
		[End Frame]
		[End Animation]
		*/

		SDL_Rect newRect = { (i + x) * width, y, width, height };
		rectangles.push_back(newRect);
	}

	this->animations.insert(std::pair<std::string, std::vector<SDL_Rect> >(name, rectangles));	// Pass in name and rectangles into pair map values respectively
	this->offsets.insert(std::pair<std::string, Vector2>(name, offset));
}

void AnimatedSprite::reverseAnimation(std::string animatedSprite, std::string reversedAnimation)
{
	std::vector<SDL_Rect> rectangles, rectReverse;
	rectangles = animations.at(animatedSprite);	//Copy values of animation rectangles from the animation map with the key (name) entered

	for (int i = rectangles.size() - 1; i >= 0; i-- )
	{
		rectReverse.push_back(rectangles.at(i));
	//	SDL_Rect newRect = rectangles.at(i);
	//	rectReverse.push_back(newRect);
	}

	this->animations.insert(std::pair<std::string, std::vector<SDL_Rect> >(reversedAnimation, rectReverse));
}

void AnimatedSprite::resetAnimations()
{
	this->animations.clear();
	this->offsets.clear();
}

void AnimatedSprite::playAnimation(std::string animation, bool once)
{
	this->currentAnimationOnce = once;
	if (this->currentAnimation != animation)	//Make sure the one that's about to be played isn't the one currently playing
	{
		this->currentAnimation = animation;
		this->frameIndex = 0;
	}
}

void AnimatedSprite::setVisible(bool visible)
{
	this->visible = visible;
}

void AnimatedSprite::stopAnimation()
{
	this->frameIndex = 0;
	this->animationDone(this->currentAnimation);
}

void AnimatedSprite::update(int elapsedTime)
{
	Sprite::update();

	this->timeElapsed += elapsedTime;
	if (this->timeElapsed > this->timeToUpdate)
	{
		this->timeElapsed -= this->timeToUpdate;

		if (this->frameIndex < this->animations[this->currentAnimation].size() - 1)	//If this isn't the final frame in the animation
		{
			this->frameIndex++;	//Continue to next frame
		}
		else
		{
			if (this->currentAnimationOnce == true)	// If the current animation has played out once
			{
				this->setVisible(false);
			}
			this->frameIndex = 1;	//Set it to 1 here because the first frame is for transition from idle.
									//I need to think about another way of doing this that doesn't feel so primitive
			this->animationDone(this->currentAnimation);
		}
	}
}

void AnimatedSprite::draw(Graphics &graphics, int x, int y, std::string facing)
{
	if (this->visible)
	{
		if (facing == "right")
		{
			SDL_Rect destinationRectangle;
			destinationRectangle.x = x + this->offsets[this->currentAnimation].x;
			destinationRectangle.y = y + this->offsets[this->currentAnimation].y;
			destinationRectangle.w = this->sourceRect.w * globals::SPRITE_SCALE;
			destinationRectangle.h = this->sourceRect.h * globals::SPRITE_SCALE;
		}
		else if (facing == "left")
		{
			SDL_Rect destinationRectangle;
			destinationRectangle.x = x + this->offsets[this->currentAnimation].x;
			destinationRectangle.y = y + this->offsets[this->currentAnimation].y;
			destinationRectangle.w = this->sourceRect.w * globals::SPRITE_SCALE;
			destinationRectangle.h = this->sourceRect.h * globals::SPRITE_SCALE;

			SDL_Rect sourceRect = this->animations[this->currentAnimation][this->frameIndex];
			graphics.blitSurface_MirroredHoriz(this->spriteSheet, &sourceRect, &destinationRectangle);
		}
	}
}