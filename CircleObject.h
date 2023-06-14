#ifndef CIRCLEOBJECT_H
#define CIRCLEOBJECT_H

#pragma once

#include "SDLincludes.h"
#include "Box.h"
#include "world.h"
#include "Texture.h"

class CircleObject : private world, public Texture
{
	b2Vec2 m_position{};
	float m_radius{};
	b2Body* m_body{};
	float m_angle{};
	float m_width{};
	float m_height{};

	using Texture::getImageHeight;
	using Texture::getImageWidth;
	using Texture::render;
	using Texture::modulateColor;
	using Texture::setTransperancy;
	using Texture::loadTextImages;

public:
	// position: Position of the body.
	// radius: radius of the circle.
	// renderer: should only be used if you need to load images and is safe from any form of deallocation.
	CircleObject(SDL_Renderer** renderer, const b2Vec2& position, float radius, float restitution = 0.0f);

	// Default constructor: does zero initialization of all member variables.
	CircleObject() = default;

	CircleObject(const CircleObject&) = default;
	CircleObject(CircleObject&&) = default;

	CircleObject& operator=(const CircleObject& copy) = default;
	CircleObject& operator=(CircleObject&& copy) = default;

private:
	const b2Vec2& convertToBox2dCoordinates() const;
	const b2Vec2& convertToBox2dCoordinates(const b2Vec2& position) const;
	const b2Vec2& convertToSDL2Coordinates(const b2Vec2& position) const;
public:
	void update();
	// If renderer is specified.
	void render() const;
	void dump() const;

	void applyLinearVelocity(const b2Vec2& velocity);
	void setTransform(const b2Vec2& position, float angle);
	void applyForceCenter(const b2Vec2& force);
	void applyImpulseCenter(const b2Vec2& impulse);
	void applyTorque(float torque);
	void applyAngularImpulse(float angularImpulse);

	const char* getClassName() const override
	{
		return "CircleObject";
	}

};



#endif // !CIRCLEOBJECT_H
