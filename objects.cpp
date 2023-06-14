#include "C:\Users\MIKE EMEKA\Documents\C++\includes.h"
#include "objects.h"
#include "world.h"
#include "BoxObject.h"
#include "EdgeObject.h"
#include "CircleObject.h"
#include "gameLoop.h"
#include "audio.h"
#include "sdltimer.h"
#include "TriangleObject.h"
#include "joint.h"

	// Texture...
	static Texture gBackground{ &sdl::globals::renderer };
	static Texture gDisplayTimerText{ "C:/Users/MIKE EMEKA/Downloads/images/07558_CenturyGothic.ttf", 30, &sdl::globals::renderer };
	static TriangleObject gTriangleTest{};
	static BoxObject gBox{ b2_dynamicBody, &sdl::globals::renderer, SDL_FRect{0, 0, 30, 30} };
	static std::array<EdgeObject, 4> corners{}; 

	//Rect...
	static SDL_Rect gCamera{0, 0, sdl::globals::width, sdl::globals::height};

	// Audio....
	
	
	// Struct Text Render...
	static RenderTTF gTimerText{}; 

	// Joy Stick axis....
	
	// String Stream....
	static std::ostringstream gStringTimerText{};

	// Timer....
	static Sdltimer timer{}; 

namespace obj
{
	void setUp()
	{
		using namespace sdl::globals;

		// Struct Render Text...
		{
			gTimerText.type = RenderText::blended;
			gTimerText.fg = SDL_Color{ 255, 255, 255 };
		}
		
		// Texture...
		{
			corners.at(0) = { EdgeObject{b2Vec2{0, 0}, b2Vec2{0, 0}, b2Vec2{0, height}} };
			corners.at(1) = { EdgeObject{b2Vec2{0, 0}, b2Vec2{0, height}, b2Vec2{width, height}} };
			corners.at(2) = { EdgeObject{b2Vec2{0, 0}, b2Vec2{width, height}, b2Vec2{width, 0}} };
			corners.at(3) = { EdgeObject{b2Vec2{0, 0}, b2Vec2{width, 0}, b2Vec2{0, 0}} };

			std::array<b2Vec2, 3> triangleVertices{};
			triangleVertices[TriangleObject::vertices::B].Set(0, 0);
			triangleVertices[TriangleObject::vertices::A].Set(40, 0);
			triangleVertices[TriangleObject::vertices::C].Set(0, 40);

			gTriangleTest = TriangleObject{ b2_dynamicBody, &renderer, b2Vec2{300, 0}, triangleVertices };
		}

		// Audio....
		{
			
		}
	}

	void textureLoading(Texture& t, std::string p, Uint8 r = 255, Uint8 g = 255, Uint8 b = 255)
	{
		t.loadTexture(p, r, g, b);
	}

	void loadObjects()
	{
		// Text Textures...
		{
			
		}

		// Textures...
		{
			const char path[]{ "C:/Users/MIKE EMEKA/Downloads/images/rightTriangle.png" };

			textureLoading(gTriangleTest, path);
			textureLoading(gBackground, "C:/Users/MIKE EMEKA/Downloads/images/bg3.jpg");
			textureLoading(gBox, "C:/Users/MIKE EMEKA/Downloads/images/box.bmp");

		}

		// Audio...
		{
			

		}
	}

	void updateObjects()
	{
		// Textures.....
		{
			gTriangleTest.update();
			gBox.update();
		}

		// Rect...
		{
			if (gCamera.x > level_width - gCamera.w)
				gCamera.x = 0;
		}

		// Animation.....
		{
			frameTime++;
		}

		// String Stream....
		{
			gStringTimerText.str("");
			gStringTimerText << std::setprecision(10) << "Seconds: " << timer.getSeconds<int>();
		}

		timer.startTimer();
		
		// Text Textures......
		{
			gTimerText.text = gStringTimerText.str().c_str();
			gDisplayTimerText.loadTextImages(gTimerText);
		}
	}

	void renderObjects()
	{
		SDL_Rect dstR{};

		// Textures.....
		{
			gBackground.render(3, &gCamera);
			gTriangleTest.render();
			gBox.render();
		}

		// Rect......
		{
			gCamera.x += 5;

		}

		// Text Textures....
		{
			dstR = { 0, 0, static_cast<int>(gDisplayTimerText.getImageWidth()), static_cast<int>(gDisplayTimerText.getImageHeight()) };
			gDisplayTimerText.render(2, nullptr, &dstR);
		}
	}

	void animation(double amount_of_frames, size_t nSprites)
	{
		if (fps / frameTime == amount_of_frames)
		{
			frameTime = 0;

			static size_t index{};
			++index;
			if (index == nSprites)
			{
				index = 0;
			}
			

		}
		
	}
	
	void endOfLoop()
	{
		
	}
}

namespace obj::events
{
	void keyDown(SDL_KeyboardEvent& key)
	{
		if (key.repeat == 0)
		{
			switch (key.keysym.sym)
			{
			case SDLK_b:
				gTriangleTest.applyAngularImpulse(4);
				break;
			
			default:
				break;
			}
		}

		switch (key.keysym.sym)
		{
		case SDLK_t:
			gTriangleTest.applyAngularImpulse(4);
			break;
		case SDLK_q:
			gBox.applyImpulse(b2Vec2{ -2.4f, 0.f }, BoxObject::PointInBox::topLeft);
			break;
		case SDLK_w:
			gBox.applyImpulse(b2Vec2{ 2.4f, 0.f }, BoxObject::PointInBox::topRight);
			break;
		case SDLK_a:
			gBox.applyImpulse(b2Vec2{ -2.4f, 0.f }, BoxObject::PointInBox::bottomLeft);
			break;
		case SDLK_s:
			gBox.applyImpulse(b2Vec2{ 2.4f, 0.f }, BoxObject::PointInBox::bottomRight);
			break;
		default:
			break;
		}
	}
	void keyUp(SDL_KeyboardEvent& key)
	{

	}
	void mouseButtonDown(SDL_MouseButtonEvent& button)
	{
		
	}
	void mouseButtonUp(SDL_MouseButtonEvent& button)
	{
	}
	void mouseMotion(SDL_MouseMotionEvent& motion)
	{

	}
	void joyAxis(SDL_JoyAxisEvent& jaxis)
	{
		if (jaxis.which == 0)
		{
			if (jaxis.axis == 0)
			{
				if (jaxis.value > 0)
				{
					std::cout << "x pos\n";
					gBox.applyImpulse(b2Vec2{ 3.4f, 0.f }, BoxObject::PointInBox::topRight);
				}
				else if (jaxis.value < 0)
				{
					std::cout << "\nx neg\n";
					gBox.applyImpulse(b2Vec2{ 3.4f, 0.f }, BoxObject::PointInBox::topLeft);
				}
				
			}
			else if (jaxis.axis == 1)
			{
				if (jaxis.value > 0)
				{
					
				}
				else if (jaxis.value < 0)
				{
					
				}
				
			}
			
		} 
	}

}
