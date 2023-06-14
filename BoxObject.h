#ifndef BOXOBJECT_H
#define BOXOBJECT_H

#pragma once

#include "SDLincludes.h"
#include "Texture.h"
#include "world.h"

#include "C:\Users\MIKE EMEKA\Documents\C++\includes.h"
using namespace std::numbers;


class BoxObject: private world, public Texture
{
	b2Body* m_body{};
	float32 m_angle{};
	SDL_FRect m_object{};

	using Texture::getImageHeight;
	using Texture::getImageWidth;
	using Texture::render;
	using Texture::modulateColor;
	using Texture::setTransperancy;
	using Texture::loadTextImages;

public:
	// typeOfBody: kinematic, dynamic or static.
	// renderer: is safe from any form of deallocation.
	// object: refers to the quadilateral you wish to display.
	// restitution: refers to how bouncy you want your object, if dynamic, to be.
	BoxObject(b2BodyType bodyType, SDL_Renderer** renderer, const SDL_FRect& object, float restitution = 0.0f);

	// Default constructor, does zero initialization of all member variables
	BoxObject() = default;
	
	BoxObject(const BoxObject&) = default;
	BoxObject(BoxObject&&) = default;
	BoxObject& operator=(const BoxObject&) = default;
	BoxObject& operator=(BoxObject&&) = default;

	~BoxObject();

	enum PointInBox
	{
		bottomLeft, bottomRight, topRight, topLeft,
	};

private:
	const b2Vec2& convertToBox2dCoordinates() const;
	const b2Vec2& convertToBox2dCoordinates(const b2Vec2& position) const;
	const b2Vec2& convertToSDL2Coordinates(const b2Vec2& position) const;

public:
	// returns a const reference to the underlying rectangle.
	const SDL_FRect& getRect() const;

	// Updates object's position and velocity with other relations to object physics
	void update();
	void render(SDL_Rect* sourceRect = nullptr) const;
	void dump() const;

	void applyLinearVelocity(const b2Vec2& velocity);
	void setTransform(const b2Vec2& position, float angle);
	void applyForceCenter(const b2Vec2& force);
	void applyForce(const b2Vec2& force, PointInBox localPoint);
	void applyImpulseCenter(const b2Vec2& impulse);
	void applyImpulse(const b2Vec2& impulse, PointInBox localPoint);
	void applyTorque(float torque);
	void applyAngularImpulse(float angularImpulse);

	const b2Vec2 vertices(int32 index);

	const char* getClassName() const override
	{
		return "BoxObject";
	}

};



#endif // !BOXOBJECT_H
