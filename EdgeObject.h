#ifndef EDGEOBJECT_H
#define EDGEOBJECT_H

#pragma once

#include "C:\Users\MIKE EMEKA\Documents\C++\includes.h"
using namespace std::numbers;

#include "world.h"
#include "SDLincludes.h"

class EdgeObject : private world
{
	using thickLine = bool;
	using thickness = std::uint8_t;

	b2Vec2 m_startpoint{};
	b2Vec2 m_endpoint{};
	b2Vec2 m_position{};
	b2Body* m_body{ nullptr };

public:
	// position: body's position, usually {0.0f, 0.0f}.
	// startpoint: edgeobject's startpoint.
	// endpoint: edgeobject's endpoint.
	EdgeObject(const b2Vec2& position, const b2Vec2& startpoint, const b2Vec2& endpoint);

	// Default constructor: does zero initialization of all member variables.
	EdgeObject() = default;

	EdgeObject(const EdgeObject&) = default;
	EdgeObject(EdgeObject&&) = default;

	EdgeObject& operator=(const EdgeObject&) = default;
	EdgeObject& operator=(EdgeObject&&) = default;

	void render(SDL_Renderer* renderer, uint8 r, uint8 g, uint8 b, thickLine flag = false, thickness width = 1.0f) const;
	void dump() const;

private:
	const b2Vec2& convertToBox2dCoordinates_startpoint() const;
	const b2Vec2& convertToBox2dCoordinates_endpoint() const;

	// Incase.
	const b2Vec2& convertToSDL2Coordinates_startpoint() const;
	// Incase.
	const b2Vec2& convertToSDL2Coordinates_endpoint() const;

};



#endif // !EDGEOBJECT_H
