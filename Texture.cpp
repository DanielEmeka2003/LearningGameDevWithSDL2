#include "Texture.h"


Texture::Texture(SDL_Renderer** renderer):
	m_texture{ nullptr }, m_renderer{ renderer }, m_path{}, m_imageWidth {}, m_imageHeight{}
{
	err.openFile();
}

Texture::Texture(std::string trueTypeFontPath, int fontSize, SDL_Renderer** renderer):
	m_textFont{}, m_trueTypeFontPath{ std::move(trueTypeFontPath) }, m_fontSize{ fontSize }, m_textRenderer{}
{
	m_renderer = renderer;
	err.openFile();
}

Texture::Texture(const Texture& source)
{
	deepCopy(source);
	err.openFile();
}

Texture::Texture(Texture&& source)
{
	moveObject(std::move(source));
	err.openFile();
}

Texture& Texture::operator=(const Texture& source)
{
	free();
	deepCopy(source);
	return *this;
}

Texture& Texture::operator=(Texture&& source)
{
	free();
	moveObject(std::move(source));
	return *this;
}

Texture::~Texture()
{
	free();
}

void Texture::loadTexture(std::string_view path, Uint8 r, Uint8 g, Uint8 b) const
{
	free();

	SDL_Texture* newTexture{ nullptr };

	SDL_Surface* temp{ IMG_Load(path.data()) };
	if (!temp)
	{
		const_cast<Error_file&>(err).InsertErrorMessageToFile() << "In object instance of class type " << getClassName()
			<< ": Unable to load surface from path in public member function loadTexture.\n\n";
		const_cast<Error_file&>(err).InsertErrorMessageToFile() << "Error from Sdl_image: " << IMG_GetError() << '\n';

		const_cast<Error_file&>(err).getErrorNotification();

		std::exit(1);
	}

	const_cast<float&>(m_imageWidth) = (float)temp->w;
	const_cast<float&>(m_imageHeight) = (float)temp->h;
	const_cast<std::string&>(m_path) = path;
	
					   
	SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format, r, g, b));
																	   
	newTexture = SDL_CreateTextureFromSurface(*m_renderer, temp);	   
	if (!newTexture)												   
	{
		const_cast<Error_file&>(err).InsertErrorMessageToFile() << "In object instance of class type " << getClassName()
			<< ": Unable to create texture from surface in public member function loadTexture\n";
		const_cast<Error_file&>(err).InsertErrorMessageToFile() << "Error from Sdl: " << SDL_GetError() << '\n';

		const_cast<Error_file&>(err).getErrorNotification();

		std::exit(1);
	}

	const_cast<SDL_Texture*&>(m_texture) = newTexture;

	SDL_FreeSurface(temp);
	
}

void Texture::loadTextImages(const RenderTTF& tR) const
{
	free();
	createTTF_Font();

	SDL_Texture* newTexture{ nullptr };

	SDL_Surface* temp{};

	switch (tR.type)
	{
	case RenderText::blended:
		temp = TTF_RenderText_Blended(m_textFont, tR.text.c_str(), tR.fg);
		break;
	case RenderText::blended_wrapped:
		temp = TTF_RenderText_Blended_Wrapped(m_textFont, tR.text.c_str(), tR.fg, tR.wrapLength);
		break;
	case RenderText::lcd:
		temp = TTF_RenderText_LCD(m_textFont, tR.text.c_str(), tR.fg, tR.bg);
		break;
	case RenderText::lcd_wrapped:
		temp = TTF_RenderText_LCD_Wrapped(m_textFont, tR.text.c_str(), tR.fg, tR.bg, tR.wrapLength);
		break;
	case RenderText::shaded:
		temp = TTF_RenderText_Shaded(m_textFont, tR.text.c_str(), tR.fg, tR.bg);
		break;
	case RenderText::shaded_wrapped:
		temp = TTF_RenderText_Shaded_Wrapped(m_textFont, tR.text.c_str(), tR.fg, tR.bg, tR.wrapLength);
		break;
	case RenderText::solid:
		temp = TTF_RenderText_Solid(m_textFont, tR.text.c_str(), tR.fg);
		break;
	case RenderText::solid_wrapped:
		temp = TTF_RenderText_Solid_Wrapped(m_textFont, tR.text.c_str(), tR.fg, tR.wrapLength);
		break;
	default:
		const_cast<Error_file&>(err).InsertErrorMessageToFile() << "In object instance of class type " << getClassName()
			<< ": Default case label reached in public member function loadTextImages.\n";

		const_cast<Error_file&>(err).getErrorNotification();

		std::exit(1);
		break;
	}

	if (!temp)
	{
		const_cast<Error_file&>(err).InsertErrorMessageToFile() << "In object instance of class type " << getClassName()
			<< ": Unable to load surface from TTF_Font in public member function loadTextImages\n\n";
		const_cast<Error_file&>(err).InsertErrorMessageToFile() << "Error from Sdl_ttf: " << TTF_GetError() << '\n';

		const_cast<Error_file&>(err).getErrorNotification();

		std::exit(1);
	}

	const_cast<float&>(m_imageWidth) = (float)temp->w;
	const_cast<float&>(m_imageHeight) = (float)temp->h;
	const_cast<RenderTTF&>(m_textRenderer) = tR;

	newTexture = SDL_CreateTextureFromSurface(*m_renderer, temp);
	if (!newTexture)
	{
		const_cast<Error_file&>(err).InsertErrorMessageToFile() << "In object instance of class type " << getClassName()
			<< ": Unable to create texture from surface in public member function loadTextImages\n\n";
		const_cast<Error_file&>(err).InsertErrorMessageToFile() << "Error from Sdl: " << SDL_GetError() << '\n';

		const_cast<Error_file&>(err).getErrorNotification();

		std::exit(1);
	}

	const_cast<SDL_Texture*&>(m_texture) = newTexture;

	SDL_FreeSurface(temp);
}

void Texture::createTTF_Font() const
{
	const_cast<TTF_Font*&>(m_textFont) = TTF_OpenFont(m_trueTypeFontPath.c_str(), m_fontSize);
	
	if (!m_textFont)
	{
		const_cast<Error_file&>(err).InsertErrorMessageToFile() << "In object instance of class type " << getClassName()
			<< ": Unable to create TTF_Font in Texture constructor.\n\n";
		const_cast<Error_file&>(err).InsertErrorMessageToFile() << "Error from Sdl_ttf: " << TTF_GetError() << '\n';

		const_cast<Error_file&>(err).getErrorNotification();

		std::exit(1);
	}
}

void Texture::render(const SDL_Rect* sourceRect, const SDL_FRect* destinationRect, double angle, const SDL_FPoint* center, SDL_RendererFlip direction) const
{
	SDL_RenderCopyExF(*m_renderer, m_texture, sourceRect, destinationRect, angle, center, direction);
}
void Texture::render(int, const SDL_Rect* sourceRect, const SDL_Rect* destinationRect, double angle, const SDL_Point* center, SDL_RendererFlip direction) const
{
	SDL_RenderCopyEx(*m_renderer, m_texture, sourceRect, destinationRect, angle, center, direction);
}

float Texture::getImageWidth() const
{
	return m_imageWidth;
}
float Texture::getImageHeight() const
{
	return m_imageHeight;
}

bool Texture::isEmpty() const
{
	return m_texture == nullptr;
}

void Texture::modulateColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(m_texture, r, g, b);
}

void Texture::setTransperancy(SDL_BlendMode mode, Uint8 a)
{
	SDL_SetTextureBlendMode(m_texture, mode);
	SDL_SetTextureAlphaMod(m_texture, a);
}

void Texture::free() const
{
	if (m_texture)
	{
		SDL_DestroyTexture(m_texture);
		const_cast<SDL_Texture*&>(m_texture) = nullptr;
	}
	
	if (m_textFont)
	{
		TTF_CloseFont(m_textFont);
		const_cast<TTF_Font*&>(m_textFont) = nullptr;
	}
}
void Texture::deepCopy(const Texture& source)
{
	m_renderer = source.m_renderer;
	m_path = source.m_path;

	if ( m_path.empty() )
	{
		m_texture = {};
		m_imageWidth = {};
		m_imageHeight = {};
	}
	else
	{
		loadTexture(m_path);
	}

	// Different Constructor.

	m_trueTypeFontPath = source.m_trueTypeFontPath;
	m_fontSize = source.m_fontSize;

	if (m_textFont)
	{
		m_textRenderer = source.m_textRenderer;
		loadTextImages(m_textRenderer);
	}
	else
	{
		m_textFont = {};
		m_textRenderer = {};
		m_imageWidth = {};
		m_imageHeight = {};
	}
	
}
void Texture::moveObject(Texture&& source)
{
	m_renderer = source.m_renderer;

	m_texture = source.m_texture;
	source.m_texture = nullptr;
	
	m_textFont = source.m_textFont;
	source.m_textFont = nullptr;

	m_imageWidth = std::move(source.m_imageWidth);
	m_imageHeight = std::move(source.m_imageHeight);
	m_path = std::move(source.m_path);
	m_trueTypeFontPath = std::move(source.m_trueTypeFontPath);
	m_fontSize = std::move(source.m_fontSize);
	m_textRenderer = std::move(source.m_textRenderer);
}