#ifndef WORLD_H
#define WORLD_H

#pragma once

#include "Box2D.h"

// Next time use a struct for static
class world
{
	static inline const b2Vec2 gravity{ 0.0f, 9.8f };

	static constexpr float32 timeStep{ 1 / 60.0f };
	static constexpr int32 velocityIterations{ 8 };
	static constexpr int32 positionIterations{ 3 };
	static inline bool gravityFlag{ true };
	
protected:
	static inline auto gworld{ std::make_unique<b2World>(gravity) };

public:
	// Responsible for simulation.
	static void physicsSimulation()
	{
		gworld->Step(world::timeStep, world::velocityIterations, world::positionIterations);
	}
	// Turns off the gravity.
	static void turnOffGravity()
	{
		if (gravityFlag)
		{
			gworld->SetGravity(b2Vec2{ 0.0f, 0.0f });
			gravityFlag = false;
		}
	}
	// Turns on the gravity.
	static void turnOnGravity()
	{
		if (!gravityFlag)
		{
			gworld->SetGravity(b2Vec2{ 0.0f, 9.8f });
			gravityFlag = true;
		}
	}
	// dumps box2d world logfile data.
	static void dump()
	{
		gworld->Dump();
	}

protected:
	static constexpr float metersToPixels{ 30.0f };
	static constexpr float pixelToMeters{ 1 / metersToPixels };

	static constexpr float scaled_width{ 640 * pixelToMeters };
	static constexpr float scaled_height{ 480 * pixelToMeters };
};



#endif // !WORLD_H
