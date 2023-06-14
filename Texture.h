#ifndef TEXTURE_H
#define TEXTURE_H

#pragma once

#include "SDLincludes.h"
#include "C:\Users\MIKE EMEKA\Documents\C++\includes.h"
#include "error_file.h"

using namespace std::numbers;
namespace fs = std::filesystem;

	enum class RenderText
	{
		blended,
		blended_wrapped,
		lcd,
		lcd_wrapped,
		shaded,
		shaded_wrapped,
		solid,
		solid_wrapped,
	};

	struct RenderTTF
	{
		// Type of text rendering you want.
		RenderText type{};
		// Text you want to render.
		std::string text{};
		// Foreground Color.
		SDL_Color fg{};
		// Backgournd Color: If type == lcd or lcd_wrapped || type == shaded or shaded_wrapped.
		SDL_Color bg{};
		// If type is wrapped.
		Uint32 wrapLength{};
	};

	inline bool operator==(const SDL_Color& a, const SDL_Color& b)
	{
		return (a.r == b.r and a.b == b.b and a.g == b.g and a.a == b.a);
	}

	inline bool operator==(const RenderTTF& a, const RenderTTF& b)
	{
		return (a.type == b.type and a.text == b.text and a.fg == b.fg and a.bg == b.bg and a.wrapLength == b.wrapLength);
	}

class Texture
{
	SDL_Texture* m_texture{};
	std::string m_path{};
	
	SDL_Renderer** m_renderer{};
	
	TTF_Font* m_textFont{};
	std::string m_trueTypeFontPath{};
	int m_fontSize{};
	RenderTTF m_textRenderer{};

	Error_file err{ "C:/Users/MIKE EMEKA/Documents/TextureErrorFile/", true, "errorFile.txt" };

protected:
	float m_imageWidth{};
	float m_imageHeight{};

public:
	// Renderer to which would be used by each instance of the Texture class in public member functions such as loadTexture and renderF,e.t.c
	// Note: renderer would not be destroyed when the destructor is called, so as to prevent, pontential breakdown of the host renderer.
	Texture(SDL_Renderer** renderer);

	// Construstor that takes a TTF_Font, note this is to used solely for rendering text and nothing more.
	// only public member function loadTextImages and render are meant to be called, when this constructor is used.
	Texture(std::string trueTypeFontPath, int fontSize, SDL_Renderer** renderer);
	
	Texture() = default;
	Texture(const Texture& source);
	Texture(Texture&& source);
	Texture& operator=(const Texture& source);
	Texture& operator=(Texture&& source);

	virtual ~Texture();

	// path: directory to the image you wish to load.
	// rgb(Red, Green, Blue): colour to make transparent in the loaded image.
	void loadTexture(std::string_view path, Uint8 r = 255, Uint8 g = 255, Uint8 b = 255) const;

	void loadTextImages(const RenderTTF& tR) const;

	void render(const SDL_Rect* sourceRect, const SDL_FRect* destinationRect = nullptr, double angle = 0.0, const SDL_FPoint* center = nullptr, SDL_RendererFlip direction = SDL_FLIP_NONE) const;
	void render(int, const SDL_Rect* sourceRect, const SDL_Rect* destinationRect = nullptr, double angle = 0.0, const SDL_Point* center = nullptr, SDL_RendererFlip direction = SDL_FLIP_NONE) const;

	float getImageWidth() const;
	float getImageHeight() const;

	// Returns true if loadTexture() has not been called, false otherwise.  
	bool isEmpty() const;

	void modulateColor(Uint8 r = 255, Uint8 g = 255, Uint8 b = 255);

	void setTransperancy(SDL_BlendMode mode = SDL_BLENDMODE_NONE, Uint8 a = 255);

	virtual const char* getClassName() const
	{
		return "Texture";
	}

private:
	void free() const;
	void deepCopy(const Texture& source);
	void moveObject(Texture&& source);
	void createTTF_Font() const;
};

#endif // !TEXTURE_H
