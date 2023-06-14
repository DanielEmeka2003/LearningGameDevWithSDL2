#include "gameLoop.h"

int main( [[maybe_unused]]int agrc, [[maybe_unused]]char* agrv[] )
{
	using sdl::globals::isRunning;

	isRunning = sdl::init();

	sdl::setUP();

	sdl::loadMedia();

	while (isRunning)
	{
		sdl::processInput();

		world::physicsSimulation();
		
		sdl::update();

		sdl::render(255, 255, 255);
	}
	
	sdl::LoopEnd();

#ifdef DUMP
	world::dump();
#endif // DUMP
	
	std::atexit(sdl::cleanup);
	sdl::cleanup();

	return EXIT_SUCCESS;
}


