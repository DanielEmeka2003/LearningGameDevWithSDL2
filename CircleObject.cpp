#include "CircleObject.h"

CircleObject::CircleObject(SDL_Renderer** renderer, const b2Vec2& position, float radius, float restitution):
	Texture{ renderer },
	m_position{ position },
	m_radius{ radius },
	m_angle{}
{
	b2BodyDef bd{};
	bd.type = b2_dynamicBody;
	bd.position = convertToBox2dCoordinates();

	m_body = gworld->CreateBody(&bd);

	b2CircleShape circle{};
	circle.m_radius = m_radius * pixelToMeters;
	circle.m_p.Set(0.0f, 0.0f);

	m_width = m_radius * 2;
	m_height = m_radius * 2;

	b2FixtureDef fd{};
	fd.shape = &circle;
	fd.density = 1.0f;
	fd.friction = 1.0f;
	fd.restitution = restitution;

	m_body->CreateFixture(&fd);
}
const b2Vec2& CircleObject::convertToBox2dCoordinates() const
{
	static b2Vec2 newCoordinate{};
	newCoordinate.x = (m_position.x) * pixelToMeters - scaled_width / 2.0f;
	newCoordinate.y = (m_position.y) * pixelToMeters - scaled_height / 2.0f;
	return newCoordinate;
}
const b2Vec2& CircleObject::convertToBox2dCoordinates(const b2Vec2& position) const
{
	static b2Vec2 newCoordinate{};
	newCoordinate.x = (position.x) * pixelToMeters - scaled_width / 2.0f;
	newCoordinate.y = (position.y) * pixelToMeters - scaled_height / 2.0f;
	return newCoordinate;
}
const b2Vec2& CircleObject::convertToSDL2Coordinates(const b2Vec2& position) const
{
	static b2Vec2 newCoordinate{};
	newCoordinate.x = (scaled_width / 2.0f + position.x) * metersToPixels;
	newCoordinate.y = (scaled_height / 2.0f + position.y) * metersToPixels;
	return newCoordinate;
}

void CircleObject::update()
{
	m_angle = (m_body->GetAngle() * 180.0f) / pi_v<float>;
	b2Vec2 position{ m_body->GetPosition() };
	m_position = convertToSDL2Coordinates(position);
}

void CircleObject::render() const
{
	SDL_FRect image{ (m_position.x - m_radius), (m_position.y - m_radius), m_width, m_height };
	Texture::render(nullptr, &image, m_angle, nullptr);
}

void CircleObject::dump() const
{
	m_body->Dump();
}

void CircleObject::applyLinearVelocity(const b2Vec2& velocity)
{
	m_body->SetLinearVelocity(velocity);
}
void CircleObject::setTransform(const b2Vec2& position, float angle)
{
	angle = (m_body->GetAngle() * 180.0f) / pi_v<float>;
	m_body->SetTransform(convertToBox2dCoordinates(position), angle);
}
void CircleObject::applyForceCenter(const b2Vec2& force)
{
	m_body->ApplyForceToCenter(force, true);
}
void CircleObject::applyImpulseCenter(const b2Vec2& impulse)
{
	m_body->ApplyLinearImpulseToCenter(impulse, true);
}
void CircleObject::applyTorque(float torque)
{
	m_body->ApplyTorque(torque, true);
}
void CircleObject::applyAngularImpulse(float angularImpulse)
{
	m_body->ApplyAngularImpulse(angularImpulse, true);
}