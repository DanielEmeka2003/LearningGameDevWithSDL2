#include "EdgeObject.h"

EdgeObject::EdgeObject(const b2Vec2& position, const b2Vec2& startpoint, const b2Vec2& endpoint) :
	m_startpoint{ startpoint },
	m_endpoint{ endpoint },
	m_position{ position }
{
	b2BodyDef bd{};
	bd.type = b2_staticBody;
	bd.position = m_position;

	m_body = gworld->CreateBody(&bd);

	b2EdgeShape edgeshape{}; 
	edgeshape.Set(convertToBox2dCoordinates_startpoint(), convertToBox2dCoordinates_endpoint());

	m_body->CreateFixture(&edgeshape, 0.0f);
}

void EdgeObject::render(SDL_Renderer* renderer, uint8 r, uint8 g, uint8 b, thickLine flag, thickness width) const
{
	if (!flag)
	{
		SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLineF(renderer, m_startpoint.x, m_startpoint.y, m_endpoint.x, m_endpoint.y);
	}
	else
	{
		thickLineRGBA(renderer, (Sint16)m_startpoint.x, (Sint16)m_startpoint.y, (Sint16)m_endpoint.x, (Sint16)m_endpoint.y, width, r, b, g, SDL_ALPHA_OPAQUE);
	}
}

void EdgeObject::dump() const
{
	m_body->Dump();
}

const b2Vec2& EdgeObject::convertToBox2dCoordinates_startpoint() const
{
	static b2Vec2 newCoordinate{};
	newCoordinate.x = m_startpoint.x * pixelToMeters - scaled_width / 2.0f;
	newCoordinate.y = m_startpoint.y * pixelToMeters - scaled_height / 2.0f;
	return newCoordinate;
}
const b2Vec2& EdgeObject::convertToBox2dCoordinates_endpoint() const
{
	static b2Vec2 newCoordinate{};
	newCoordinate.x = m_endpoint.x * pixelToMeters - scaled_width / 2.0f;
	newCoordinate.y = m_endpoint.y * pixelToMeters - scaled_height / 2.0f;
	return newCoordinate;
}

const b2Vec2& EdgeObject::convertToSDL2Coordinates_startpoint() const
{
	static b2Vec2 newCoordinate{};
	auto edgeshape{ (b2EdgeShape*)m_body->GetFixtureList()->GetShape() }; 
	newCoordinate.x = (scaled_width / 2.0f + edgeshape->m_vertex1.x) * metersToPixels;
	newCoordinate.y = (scaled_height / 2.0f + edgeshape->m_vertex1.y) * metersToPixels;

	return newCoordinate;
}
const b2Vec2& EdgeObject::convertToSDL2Coordinates_endpoint() const
{
	static b2Vec2 newCoordinate{};
	auto edgeshape{ (b2EdgeShape*)m_body->GetFixtureList()->GetShape() };
	newCoordinate.x = (scaled_width / 2.0f + edgeshape->m_vertex2.x) * metersToPixels;
	newCoordinate.y = (scaled_height / 2.0f + edgeshape->m_vertex2.y) * metersToPixels;

	return newCoordinate;
}