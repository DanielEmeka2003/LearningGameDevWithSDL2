#pragma once
#include "Texture.h"
#include "world.h"

class Joint: private world
{
	b2Vec2 m_positionA{};
	float m_radiusA{};
	b2Body* m_bodyA{};
	float m_angleA{};
	float m_widthA{};
	float m_heightA{};

	Texture m_textureA{};
	Texture m_textureB{};

	b2Body* m_bodyB{};
	float32 m_angleB{};
	SDL_FRect m_objectB{};

	b2RevoluteJoint* m_joint;


public:

	Joint(SDL_Renderer** renderer, const b2Vec2& position, float radius, const SDL_FRect& object);
	
	// Default constructor: does zero initialization of all member variables.
	Joint() = default;

	Joint(const Joint&) = default;
	Joint(Joint&&) = default;

	Joint& operator=(const Joint& copy) = default;
	Joint& operator=(Joint&& copy) = default;

private:
	const b2Vec2& convertToBox2dCoordinatesB() const;
	const b2Vec2& convertToBox2dCoordinatesB(const b2Vec2& position) const;
	const b2Vec2& convertToSDL2CoordinatesB(const b2Vec2& position) const;

	const b2Vec2& convertToBox2dCoordinatesA() const;
	const b2Vec2& convertToBox2dCoordinatesA(const b2Vec2& position) const;
	const b2Vec2& convertToSDL2CoordinatesA(const b2Vec2& position) const;

public:
	Joint& loadTextureA(std::string_view path, SDL_Color rgb = SDL_Color{ 255, 255, 255 });
	Joint& loadTextureB(std::string_view path, SDL_Color rgb = SDL_Color{ 255, 255, 255 });

	Joint& updateA();
	Joint& updateB();

	Joint& renderA() const;
	Joint& renderB() const;

	const b2Vec2 verticesB(int32 index);
};

