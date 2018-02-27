/*Game class
* This clas will hold all information for our main game loop
*/

#include "game.h"
#include "graphics.h"
#include "sprite.h"

#include <SDL.h>
#include <algorithm>

namespace {
	const int FPS = 60;							//Frames per second
	const int MAX_FRAME_TIME = 6 * 1000 / FPS;	//The max amount of time a frame is allowed to last on screen
}

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}

Game::~Game()
{

}

void Game::gameLoop()
{
	Graphics graphics;
	SDL_Event event;
	this->sprite = Sprite(graphics, "Assets/aerial_knee_frames cut.png", 65, 3, 19, 36, 100, 100);

	/*Gets number of milliseconds since the SDL library was initialized.
	 *This is our clock that we use to reference the change in time (delta time)
	 *This will be set every frame
	*/
	int LAST_UPDATE_TIME = SDL_GetTicks();

	//Start the game loop
	while (true)
	{
		const int CURRENT_TIME_MS = SDL_GetTicks();
		
		//This LAST_UPDATE_TIME subtracted from CURRENT_TIME_MS will show how long it took to process the frame in the game loop
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
		
		//Do the frame updates to the game
		//Scales the timing so that the physics will work the same no matter the speed of your computer
		this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));

		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		this->draw(graphics);
	}
}

void Game::draw(Graphics &graphics)
{
	graphics.clear();
	this->sprite.draw(graphics, 100, 100);
	graphics.flip();	//flip() the surface/buffer to reveal the drawn frame
}

void Game::update(float elapsedTime)
{

}