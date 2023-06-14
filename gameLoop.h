#ifndef GAMELOOP_H
#define GAMELOOP_H

#pragma once

#include "C:\Users\MIKE EMEKA\Documents\C++\includes.h"
#include "SDLincludes.h"
#include "world.h"

using namespace std::numbers;

#define CUSTOMCURSOR

namespace sdl::globals
{
	using WindowDimensions = int;

	inline SDL_Window* window{};
	inline SDL_Renderer* renderer{};
	inline SDL_Cursor* customCursor{};
	inline SDL_Joystick* joyStick_one{};

	inline constexpr WindowDimensions width{ 640 };
	inline constexpr WindowDimensions height{ 480 };

	inline bool isRunning{};
}

namespace sdl
{
	// Initializies sdl, renderer and creates window.
	// Returns false if sdl or renderer fails to initialize and also if window creation fails.
	bool init();

	// Sets up any stuff required.
	void setUP();

	// Loads Texture, Surface, animation and any other media related stuff.
	void loadMedia();

	// Handles input.
	void processInput();

	// Updates window objects status.
	void update();

	// Renders window objects.
	void render(uint8 r = 255, uint8 g = 255, uint8 b = 255);

	void LoopEnd();

	// Cleans up all global dymanic objects like global_surface, and other dynamic objects.
	void cleanup();
}



#endif // !UNIQUE_H
