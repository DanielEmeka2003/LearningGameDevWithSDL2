#include "TriangleObject.h"

TriangleObject::TriangleObject(b2BodyType bodyType, SDL_Renderer** renderer, const b2Vec2& postion, const Vertices& v, float restitution):
	Texture{ renderer },
	m_position{ postion },
	m_v{ v },
	m_angle{}
{
	calculateTriangleInfo();

	if (bodyType == b2_dynamicBody)
	{

		b2BodyDef bd{};
		bd.type = bodyType;
		bd.position = convertToBox2dCoordinates();
		m_body = gworld->CreateBody(&bd);

		b2PolygonShape triangle{};

		for (auto& i : m_v)
		{
			i *= pixelToMeters;
		}

		triangle.Set(m_v.data(), 3);

		b2FixtureDef fixtureDef{};
		fixtureDef.density = 1.0f;
		fixtureDef.shape = &triangle;
		fixtureDef.friction = 1.0f;
		fixtureDef.restitution = restitution;

		m_body->CreateFixture(&fixtureDef);
	}
	else if (bodyType == b2_staticBody)
	{
		b2BodyDef bd{};
		bd.position = convertToBox2dCoordinates();
		m_body = gworld->CreateBody(&bd);

		b2PolygonShape triangle{};

		for (auto& i : m_v)
		{
			i *= pixelToMeters;
		}

		triangle.Set(m_v.data(), 3);

		m_body->CreateFixture(&triangle, 0.0f);
	}
}

const b2Vec2& TriangleObject::convertToBox2dCoordinates() const
{
	static b2Vec2 newCoordinate{};
	newCoordinate.x = (m_position.x) * pixelToMeters - scaled_width / 2.0f;
	newCoordinate.y = (m_position.y) * pixelToMeters - scaled_height / 2.0f;
	return newCoordinate;
}
const b2Vec2& TriangleObject::convertToBox2dCoordinates(const b2Vec2& position) const
{
	static b2Vec2 newCoordinate{};
	newCoordinate.x = (position.x) * pixelToMeters - scaled_width / 2.0f;
	newCoordinate.y = (position.y) * pixelToMeters - scaled_height / 2.0f;
	return newCoordinate;
}
const b2Vec2& TriangleObject::convertToSDL2Coordinates(const b2Vec2& position) const
{
	static b2Vec2 newCoordinate{};
	newCoordinate.x = (scaled_width / 2.0f + position.x) * metersToPixels;
	newCoordinate.y = (scaled_height / 2.0f + position.y) * metersToPixels;
	return newCoordinate;
}

void TriangleObject::calculateTriangleInfo()
{
	{
		float x{ m_v.at(vertices::B).x - m_v.at(vertices::C).x };
		float y{ m_v.at(vertices::B).y - m_v.at(vertices::C).y };

		m_tInfo.a = std::sqrtf(std::powf(x, 2) + std::powf(y, 2));
	}
	{
		float x{ m_v.at(vertices::A).x - m_v.at(vertices::C).x };
		float y{ m_v.at(vertices::A).y - m_v.at(vertices::C).y };

		m_tInfo.b = std::sqrtf(std::powf(x, 2) + std::powf(y, 2));
	}
	{ 
		float x{ m_v.at(vertices::A).x - m_v.at(vertices::B).x };
		float y{ m_v.at(vertices::A).y - m_v.at(vertices::B).y };

		m_tInfo.c = std::sqrtf(std::powf(x, 2) + std::powf(y, 2));
	}

	m_tInfo.perimeter = m_tInfo.a + m_tInfo.b + m_tInfo.c;

	m_tInfo.semiPerimeter = m_tInfo.perimeter / 2;
	
	{ 
		float x{ (m_tInfo.semiPerimeter - m_tInfo.a) };
		float y{ (m_tInfo.semiPerimeter - m_tInfo.b) };
		float z{ (m_tInfo.semiPerimeter - m_tInfo.c) };

		m_tInfo.area = std::sqrtf(m_tInfo.semiPerimeter * (x * y * z));
	}

	m_tInfo.h_a = (2 * m_tInfo.area) / m_tInfo.a;
	m_tInfo.h_b = (2 * m_tInfo.area) / m_tInfo.b;
	m_tInfo.h_c = (2 * m_tInfo.area) / m_tInfo.c;
}

float TriangleObject::get_a()
{
	return m_tInfo.a;
}
float TriangleObject::get_b()
{
	return m_tInfo.b;
}
float TriangleObject::get_c()
{
	return m_tInfo.c;
}
float TriangleObject::get_h_a()
{
	return m_tInfo.h_a;
}
float TriangleObject::get_h_b()
{
	return m_tInfo.h_b;
}
float TriangleObject::get_h_c()
{
	return m_tInfo.h_c;
}
float TriangleObject::get_area()
{
	return m_tInfo.area;
}
float TriangleObject::get_perimeter()
{
	return m_tInfo.perimeter;
}
float TriangleObject::get_semiPerimeter()
{
	return m_tInfo.semiPerimeter;
}

void TriangleObject::update()
{
	m_angle = (m_body->GetAngle() * 180.0f) / pi_v<float>;
	b2Vec2 position = m_body->GetPosition();
	m_position = convertToSDL2Coordinates(position);
}

void TriangleObject::render(SDL_Rect* sourceRect) const
{
	SDL_FPoint c{ m_v[vertices::C].x, m_v[vertices::C].y };
	SDL_FRect image{ m_position.x, m_position.y, m_tInfo.c, m_tInfo.h_c };
	Texture::render(sourceRect, &image, m_angle, &c);
}

void TriangleObject::dump() const
{
	m_body->Dump();
}

void TriangleObject::applyLinearVelocity(const b2Vec2& velocity)
{
	m_body->SetLinearVelocity(velocity);
}
void TriangleObject::setTransform(const b2Vec2& position, float angle)
{
	angle = (m_body->GetAngle() * 180.0f) / pi_v<float>;
	m_body->SetTransform(convertToBox2dCoordinates(position), angle);
}
void TriangleObject::applyForceCenter(const b2Vec2& force)
{
	m_body->ApplyForceToCenter(force, true);
}
void TriangleObject::applyImpulseCenter(const b2Vec2& impulse)
{
	m_body->ApplyLinearImpulseToCenter(impulse, true);
}
void TriangleObject::applyTorque(float torque)
{
	m_body->ApplyTorque(torque, true);
}
void TriangleObject::applyAngularImpulse(float angularImpulse)
{
	m_body->ApplyAngularImpulse(angularImpulse, true);
}
