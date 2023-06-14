#include "joint.h"

Joint::Joint(SDL_Renderer** renderer, const b2Vec2& position, float radius, const SDL_FRect& object):
	m_textureA{ renderer }, m_textureB{ renderer }, m_positionA{ position }, m_radiusA{ radius }, m_objectB{ object }
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	b2FixtureDef fixtureDef;
	fixtureDef.density = 1;
	fixtureDef.friction = 1.0f;

	//Circle.....................
	bodyDef.position = convertToBox2dCoordinatesA();
	m_bodyA = gworld->CreateBody(&bodyDef);

	b2CircleShape circle{};
	circle.m_radius = m_radiusA * pixelToMeters;
	circle.m_p.Set(0.0f, 0.0f);

	m_widthA = m_radiusA * 2;
	m_heightA = m_radiusA * 2;

	fixtureDef.shape = &circle;
	m_bodyA->CreateFixture(&fixtureDef);

	//Box...........................
	bodyDef.position = convertToBox2dCoordinatesB();
	m_bodyB = gworld->CreateBody(&bodyDef);

	b2PolygonShape box{};
	box.SetAsBox((m_objectB.w * pixelToMeters) / 2.0f - box.m_radius, (m_objectB.h * pixelToMeters) / 2.0f - box.m_radius);

	fixtureDef.shape = &box;
	m_bodyB->CreateFixture(&fixtureDef);

	//Joint...................
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = m_bodyB;
	revoluteJointDef.bodyB = m_bodyA;
	revoluteJointDef.collideConnected = false;
	revoluteJointDef.localAnchorA = verticesB(3);
	revoluteJointDef.localAnchorB.Set(0, 0);
	revoluteJointDef.enableMotor = true;
	revoluteJointDef.maxMotorTorque = 5;  
	revoluteJointDef.motorSpeed = 360 * (pi_v<float> / 180);
	m_joint = (b2RevoluteJoint*)gworld->CreateJoint(&revoluteJointDef);

	//Circle.....................
	b2Body* m_bodyA = gworld->CreateBody(&bodyDef);

	fixtureDef.shape = &circle;
	m_bodyA->CreateFixture(&fixtureDef);

	revoluteJointDef.bodyB = m_bodyA;
	revoluteJointDef.localAnchorA = verticesB(2);
	m_joint = (b2RevoluteJoint*)gworld->CreateJoint(&revoluteJointDef);
}

const b2Vec2& Joint::convertToBox2dCoordinatesB() const
{
	static b2Vec2 newCoordinate{};
	newCoordinate.x = (m_objectB.x + m_objectB.w / 2.0f) * pixelToMeters - scaled_width / 2.0f;
	newCoordinate.y = (m_objectB.y + m_objectB.h / 2.0f) * pixelToMeters - scaled_height / 2.0f;
	return newCoordinate;
}
const b2Vec2& Joint::convertToBox2dCoordinatesB(const b2Vec2& position) const
{
	static b2Vec2 newCoordinate{};
	newCoordinate.x = (position.x + m_objectB.w / 2.0f) * pixelToMeters - scaled_width / 2.0f;
	newCoordinate.y = (position.y + m_objectB.h / 2.0f) * pixelToMeters - scaled_height / 2.0f;
	return newCoordinate;
}
const b2Vec2& Joint::convertToSDL2CoordinatesB(const b2Vec2& position) const
{
	static b2Vec2 newCoordinate{};
	newCoordinate.x = (scaled_width / 2.0f + position.x) * metersToPixels - m_objectB.w / 2;
	newCoordinate.y = (scaled_height / 2.0f + position.y) * metersToPixels - m_objectB.h / 2;
	return newCoordinate;
}

const b2Vec2& Joint::convertToBox2dCoordinatesA() const
{
	static b2Vec2 newCoordinate{};
	newCoordinate.x = (m_positionA.x) * pixelToMeters - scaled_width / 2.0f;
	newCoordinate.y = (m_positionA.y) * pixelToMeters - scaled_height / 2.0f;
	return newCoordinate;
}
const b2Vec2& Joint::convertToBox2dCoordinatesA(const b2Vec2& position) const
{
	static b2Vec2 newCoordinate{};
	newCoordinate.x = (position.x) * pixelToMeters - scaled_width / 2.0f;
	newCoordinate.y = (position.y) * pixelToMeters - scaled_height / 2.0f;
	return newCoordinate;
}
const b2Vec2& Joint::convertToSDL2CoordinatesA(const b2Vec2& position) const
{
	static b2Vec2 newCoordinate{};
	newCoordinate.x = (scaled_width / 2.0f + position.x) * metersToPixels;
	newCoordinate.y = (scaled_height / 2.0f + position.y) * metersToPixels;
	return newCoordinate;
}

Joint& Joint::loadTextureA(std::string_view path, SDL_Color rgb)
{
	m_textureA.loadTexture(path, rgb.r, rgb.g, rgb.b);
	return *this;
}
Joint& Joint::loadTextureB(std::string_view path, SDL_Color rgb)
{
	m_textureB.loadTexture(path, rgb.r, rgb.g, rgb.b);
	return *this;
}

Joint& Joint::updateA()
{
	m_angleA = (m_bodyA->GetAngle() * 180.0f) / pi_v<float>;
	b2Vec2 position{ m_bodyA->GetPosition() };
	m_positionA = convertToSDL2CoordinatesA(position);
	return *this;
}
Joint& Joint::updateB()
{
	m_angleB = (m_bodyB->GetAngle() * 180.0f) / pi_v<float>;
	b2Vec2 position = m_bodyB->GetPosition();
	m_objectB.x = convertToSDL2CoordinatesB(position).x;
	m_objectB.y = convertToSDL2CoordinatesB(position).y;
	return *this;
}

Joint& Joint::renderA() const
{
	SDL_FRect image{ (m_positionA.x - m_radiusA), (m_positionA.y - m_radiusA), m_widthA, m_heightA };
	m_textureA.render(nullptr, &image, m_angleA, nullptr);
	return const_cast<Joint&>(*this);
}
Joint& Joint::renderB() const
{
	m_textureB.render(nullptr, &m_objectB, m_angleB, nullptr);
	return const_cast<Joint&>(*this);
}

const b2Vec2 Joint::verticesB(int32 index)
{
	return { ((b2PolygonShape*)m_bodyB->GetFixtureList()[0].GetShape())->GetVertex(index) };
}