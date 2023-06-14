#ifndef OBJECTS_H
#define OBJECTS_H

#pragma once

#include "SDLincludes.h"
#include "Texture.h"

namespace obj
{
	void setUp();

	//loads window objects.
	void loadObjects();
	
	//updates window objects positions.
	void updateObjects();

	//renders window objects on screen.
	void renderObjects();

	inline constexpr int fps{ 60 };
	inline double frameTime{};
	inline constexpr int level_width{ 1840 }, level_height{ 480 };
	
	void animation(double amount_of_frames, size_t nSprites);

	void endOfLoop();
}

namespace obj::events
{
	void keyDown(SDL_KeyboardEvent& key);

	void keyUp(SDL_KeyboardEvent& key);

	void mouseButtonDown(SDL_MouseButtonEvent& button);

	void mouseButtonUp(SDL_MouseButtonEvent& button);

	void mouseMotion(SDL_MouseMotionEvent& motion);

	void joyAxis(SDL_JoyAxisEvent& jaxis);

}

#endif // !OBJECTS_H
