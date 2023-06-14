#include "BoxObject.h"

BoxObject::BoxObject(b2BodyType bodyType, SDL_Renderer** renderer, const SDL_FRect& object, float restitution):
	Texture{ renderer },  
	m_object { object },
	m_angle{}
{
	if (bodyType == b2_dynamicBody)
	{
		b2BodyDef bd{};
		bd.type = bodyType;
		bd.position = convertToBox2dCoordinates();
		m_body = gworld->CreateBody(&bd);
		
		b2PolygonShape box{};
		box.SetAsBox( (m_object.w * pixelToMeters) / 2.0f - box.m_radius, (m_object.h * pixelToMeters) / 2.0f - box.m_radius );
		
		b2FixtureDef fixtureDef{};
		fixtureDef.density = 1.0f;
		fixtureDef.shape = &box;  
		fixtureDef.friction = 1.0f;
		fixtureDef.restitution = restitution;

		m_body->CreateFixture(&fixtureDef);
	}
	else if (bodyType == b2_staticBody)
	{
		b2BodyDef bd{};
		bd.position = convertToBox2dCoordinates();

		m_body = gworld->CreateBody(&bd);

		b2PolygonShape box{};
		box.SetAsBox( (m_object.w * pixelToMeters) / 2.0f - box.m_radius, (m_object.h * pixelToMeters) / 2.0f - box.m_radius);
  
		m_body->CreateFixture(&box, 0.0f);
	}
}

BoxObject::~BoxObject()
{
	gworld->DestroyBody(m_body);
}
const b2Vec2& BoxObject::convertToBox2dCoordinates() const
{
	static b2Vec2 newCoordinate{};
	newCoordinate.x = (m_object.x + m_object.w / 2.0f) * pixelToMeters - scaled_width / 2.0f;
	newCoordinate.y = (m_object.y + m_object.h / 2.0f) * pixelToMeters - scaled_height / 2.0f;
	return newCoordinate;
}
const b2Vec2& BoxObject::convertToBox2dCoordinates(const b2Vec2& position) const
{
	static b2Vec2 newCoordinate{};
	newCoordinate.x = (position.x + m_object.w / 2.0f) * pixelToMeters - scaled_width / 2.0f;
	newCoordinate.y = (position.y + m_object.h / 2.0f) * pixelToMeters - scaled_height / 2.0f;
	return newCoordinate;
}
const b2Vec2& BoxObject::convertToSDL2Coordinates(const b2Vec2& position) const
{
	static b2Vec2 newCoordinate{};
	newCoordinate.x = (scaled_width / 2.0f + position.x) * metersToPixels - m_object.w / 2;
	newCoordinate.y = (scaled_height / 2.0f + position.y) * metersToPixels - m_object.h / 2;
	return newCoordinate;
}

const SDL_FRect& BoxObject::getRect() const
{
	return m_object;
}

void BoxObject::update()
{
	m_angle = (m_body->GetAngle() * 180.0f) / pi_v<float>;
	b2Vec2 position = m_body->GetPosition();
	m_object.x = convertToSDL2Coordinates(position).x;
	m_object.y = convertToSDL2Coordinates(position).y; 
}

void BoxObject::render(SDL_Rect* sourceRect) const
{
	Texture::render(sourceRect, &m_object, m_angle, nullptr); 
}

void BoxObject::dump() const
{
	m_body->Dump();
}

void BoxObject::applyLinearVelocity(const b2Vec2& velocity)
{
	m_body->SetLinearVelocity(velocity);
}
void BoxObject::setTransform(const b2Vec2& position, float angle)
{
	angle = (m_body->GetAngle() * 180.0f) / pi_v<float>;
	m_body->SetTransform(convertToBox2dCoordinates(position), angle);
}
void BoxObject::applyForceCenter(const b2Vec2& force)
{
	m_body->ApplyForceToCenter(force, true);
}
void BoxObject::applyForce(const b2Vec2& force, PointInBox localPoint)
{
	switch (localPoint) 
	{
	case BoxObject::bottomLeft:
		m_body->ApplyForce(force, m_body->GetWorldPoint(vertices(0)), true);
		break;
	case BoxObject::bottomRight:
		m_body->ApplyForce(force, m_body->GetWorldPoint(vertices(1)), true);
		break;
	case BoxObject::topRight:
		m_body->ApplyForce(force, m_body->GetWorldPoint(vertices(2)), true);
		break;
	case BoxObject::topLeft:
		m_body->ApplyForce(force, m_body->GetWorldPoint(vertices(3)), true);
		break;
	default: 
		assert(false and "Not a valid point to apply force to in shape\n");
		break;
	}
}
void BoxObject::applyImpulseCenter(const b2Vec2& impulse)
{
	m_body->ApplyLinearImpulseToCenter(impulse, true);
}
void BoxObject::applyImpulse(const b2Vec2& force, PointInBox localPoint)
{
	switch (localPoint)
	{ 
	case BoxObject::topLeft:
		m_body->ApplyLinearImpulse(force, m_body->GetWorldPoint(vertices(0)), true);
		break;
	case BoxObject::topRight:
		m_body->ApplyLinearImpulse(force, m_body->GetWorldPoint(vertices(1)), true);
		break;
	case BoxObject::bottomRight:
		m_body->ApplyLinearImpulse(force, m_body->GetWorldPoint(vertices(2)), true);
		break;
	case BoxObject::bottomLeft:
		m_body->ApplyLinearImpulse(force, m_body->GetWorldPoint(vertices(3)), true);
		break;
	default:
		assert(false and "Not a valid point to apply linearImpulse to in shape\n");
		break;
	} 
}
void BoxObject::applyTorque(float torque)
{
	m_body->ApplyTorque(torque, true);
}
void BoxObject::applyAngularImpulse(float angularImpulse)
{
	m_body->ApplyAngularImpulse(angularImpulse, true);
}

const b2Vec2 BoxObject::vertices(int32 index)
{
	return { ((b2PolygonShape*)m_body->GetFixtureList()[0].GetShape())->GetVertex(index) };
}