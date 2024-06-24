#ifndef START_HEADER
#define START_HEADER
/*!
\file start.h
* \brief This file contains the definition of the Start class
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "physicsObject.h"

/*! \class Start
*	\brief Start is a sensor which is used as the start/finish line in the game
*/

class Start : public sf::RectangleShape, public physicsObject
{
public:

	void createStart(b2World * world, const sf::Vector2f& pos, const float& angle, const sf::Vector2f& size) {

		//! Create objects we need
		b2BodyDef m_bodyDef;
		b2PolygonShape m_shape;
		b2FixtureDef m_fixture;

		setPosition(pos);
		setSize(size);
		setOrigin(size * 0.5f);
		setFillColor(sf::Color::Yellow);
		setOutlineThickness(0.f);

		m_bodyDef.position.Set(pos.x, pos.y);
		m_bodyDef.angle = angle * DEG2RAD;

		m_body = world->CreateBody(&m_bodyDef);
		m_body->SetUserData(this);

		m_shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
		m_shape.m_radius = 0.f;

		m_fixture.shape = &m_shape;
		m_fixture.friction = m_kfFriction;
		m_fixture.density = m_kfDensity;
		m_fixture.restitution = m_kfRestitution;
		//! Set as sensor
		m_fixture.isSensor = true;

		m_body->CreateFixture(&m_fixture);

	}
	/**<
	*	Start constructor, used to create the start for a racetrack with modifyable values
	*	\param world Pointer used to reference the world when making the body
	*	\param world Pointer used to reference the world when making the body 
	*	\param pos	Position of the object
	*	\param size	Size of the object
	*/

};
#endif
