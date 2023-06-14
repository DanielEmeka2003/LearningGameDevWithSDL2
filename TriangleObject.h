#ifndef TRIANGLEOBJECT_H
#define TRIANGLEOBJECT_H

#pragma once

#include "SDLincludes.h"
#include "Texture.h"
#include "world.h"

#include "C:\Users\MIKE EMEKA\Documents\C++\includes.h"
using namespace std::numbers;

struct TriangleInfo
{
	float a{}, b{}, c{};
	float area{};
	float perimeter{};
	float semiPerimeter{};
	float h_a{}, h_b{}, h_c{};
};

class TriangleObject: private world, public Texture
{
	using Vertices = std::array<b2Vec2, 3>;

	TriangleInfo m_tInfo{};
	b2Body* m_body{ nullptr };
	float32 m_angle{};
	b2Vec2 m_position{};
	Vertices m_v{};

	using Texture::getImageHeight;
	using Texture::getImageWidth;
	using Texture::render;
	using Texture::modulateColor;
	using Texture::setTransperancy;
	using Texture::loadTextImages;

public:

	TriangleObject(b2BodyType bodyType, SDL_Renderer** renderer, const b2Vec2& postion, const Vertices& v, float restitution = 0.0f);

	// Default constructor, does zero initialization of all member variables
	TriangleObject() = default;

	TriangleObject(const TriangleObject&) = default;
	TriangleObject(TriangleObject&&) = default;
	TriangleObject& operator=(const TriangleObject&) = default;
	TriangleObject& operator=(TriangleObject&&) = default;

private:
	const b2Vec2& convertToBox2dCoordinates() const;
	const b2Vec2& convertToBox2dCoordinates(const b2Vec2& position) const;
	const b2Vec2& convertToSDL2Coordinates(const b2Vec2& position) const;

	void calculateTriangleInfo();

public:
	enum vertices: size_t
	{
		B, A, C,
	};

	float get_a();
	float get_b();
	float get_c();
	float get_h_a();
	float get_h_b();
	float get_h_c();
	float get_area();
	float get_perimeter();
	float get_semiPerimeter();

	// Updates object's position and velocity with other relations to object physics
	void update();
	void render(SDL_Rect* sourceRect = nullptr) const;
	void dump() const;

	void applyLinearVelocity(const b2Vec2& velocity);
	void setTransform(const b2Vec2& position, float angle);
	void applyForceCenter(const b2Vec2& force);
	void applyImpulseCenter(const b2Vec2& impulse);
	void applyTorque(float torque);
	void applyAngularImpulse(float angularImpulse);

	const char* getClassName() const override
	{
		return "TriangleObject";
	}
};



#endif // !TRIANGLEOBJECT_H
