#include "gameLoop.h"
#include "objects.h"
#include "error_file.h"

namespace sdl
{
	bool init()
	{
		Error_file err{ "C:/Users/MIKE EMEKA/Documents/SdlError/", true, "errorFile.txt" };
		err.openFile();
		

		if (SDL_Init(SDL_INIT_EVERYTHING))
		{
			err.InsertErrorMessageToFile() << "Problem initializing Sdl.\n\n";
			err.InsertErrorMessageToFile() << "Error from Sdl: " << SDL_GetError() << '\n';

			err.getErrorNotification();

			return false;
		}

		else if (TTF_Init())
		{
			err.InsertErrorMessageToFile() << "Problem initializing Sdl_ttf.\n\n";
			err.InsertErrorMessageToFile() << "Error from Sdl_ttf: " << TTF_GetError() << '\n';

			err.getErrorNotification();

			return false;
		}

		else if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048))
		{
			err.InsertErrorMessageToFile() << "Problem opening/initializing Sdl_mixer.\n\n";
			err.InsertErrorMessageToFile() << "Error from Sdl_mixer: " << Mix_GetError() << '\n';

			err.getErrorNotification();

			return false;
		}

		sdl::globals::window = 
			SDL_CreateWindow("Box2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sdl::globals::width, sdl::globals::height, SDL_WINDOW_SHOWN);
		if (!sdl::globals::window)
		{
			err.InsertErrorMessageToFile() << "Problem creating sdl_window(*).\n\n";
			err.InsertErrorMessageToFile() << "Error from Sdl: " << SDL_GetError() << '\n';

			err.getErrorNotification();

			return false;
		}

		sdl::globals::renderer = SDL_CreateRenderer(sdl::globals::window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (!sdl::globals::renderer)
		{
			err.InsertErrorMessageToFile() << "Problem creating Sdl_Renderer(*).\n\n";
			err.InsertErrorMessageToFile() << "Error from Sdl: " << SDL_GetError() << '\n';

			err.getErrorNotification();

			return false;
		}

		return true;
	}

	void setUP()
	{
#ifdef CUSTOMCURSOR
		SDL_Surface* surface{ IMG_Load("C:/Users/MIKE EMEKA/Downloads/images/icons8-minecraft-sword-40.png") };
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 255, 255));
		sdl::globals::customCursor = SDL_CreateColorCursor(surface, 35, 5);

		SDL_FreeSurface(surface);
#endif // CUSTOMCURSOR

#ifndef CUSTOMCURSOR
	sdl::globals::customCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
#endif // !CUSTOMCURSOR

		if (!sdl::globals::customCursor)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Problem from cursor creation: ", SDL_GetError(), sdl::globals::window);
		}
		SDL_SetCursor(sdl::globals::customCursor);


		if (SDL_NumJoysticks() < 1)
		{
			std::cerr << "Warning no joysticks connected\n";
		}
		else
		{
			if (!(sdl::globals::joyStick_one = SDL_JoystickOpen(0)))
			{
				std::cerr << "Unable to open JoyStick: " << SDL_GetError() << '\n';
			}
			
		}

		obj::setUp();
	}

	void loadMedia()
	{
		obj::loadObjects();
	}

	void processInput()
	{
		SDL_Event event{};

		while (SDL_PollEvent(&event))
		{
			using sdl::globals::isRunning;
			using namespace obj::events;

			switch (event.type)
			{
			case SDL_QUIT: isRunning = false; break;

			case SDL_KEYDOWN:
				keyDown(event.key); 
				break;
			case SDL_KEYUP:
				keyUp(event.key);
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouseButtonDown(event.button);
				break;
			case SDL_MOUSEBUTTONUP:
				mouseButtonUp(event.button);
				break;
			case SDL_MOUSEMOTION:
				mouseMotion(event.motion);
				break;
			case SDL_JOYAXISMOTION:
				joyAxis(event.jaxis);
				break;
				
			default: isRunning = true; break;
			}
		}
	}

	void update()
	{
		obj::updateObjects();
	}

	void render(uint8 r, uint8 g, uint8 b)
	{
		SDL_SetRenderDrawColor(sdl::globals::renderer, r, g, b, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(sdl::globals::renderer);
		
		obj::renderObjects(); 

		SDL_RenderPresent(sdl::globals::renderer);

	}

	void LoopEnd()
	{
		obj::endOfLoop();
	}

	void cleanup()
	{
		SDL_DestroyRenderer(sdl::globals::renderer);
		SDL_DestroyWindow(sdl::globals::window);
		SDL_FreeCursor(sdl::globals::customCursor);
		SDL_JoystickClose(sdl::globals::joyStick_one);

		SDL_Quit();
		Mix_Quit();
		//TTF_Quit();
		sdl::globals::renderer = nullptr;
		sdl::globals::window = nullptr;
		sdl::globals::customCursor = nullptr;
		sdl::globals::joyStick_one = nullptr;
	}



}