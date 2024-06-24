#ifndef TRACK_HEADER
#define TRACK_HEADER
/*!
\file track.h
*	\brief This file contains the definition of the track class
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "physicsObject.h"
#include <iostream>

/*! \class Track
* \brief Track is a class used to create an edge of a racetrack, track will be one of two tracks in a racetrack, either an inner or an outer track
* the size of the track chain shape is dynamic due to the way the array which holds the vertexes is set.
*/

class Track : public sf::VertexArray, public physicsObject
{
public:
	void createTrack(b2World * world, std::vector<b2Vec2> verticies, int vertexes) {
		
		b2BodyDef m_bodyDef;
		b2FixtureDef m_fixture;
		b2ChainShape m_shape;
		//! Array to hold each vertex in the chain
		b2Vec2 * m_chain = 0;
		
		
		if (m_chain != 0) {
			delete[] m_chain;
		}
		//! create chain as an array, allows me to give an array size from a value discovered at runtime
		m_chain = new b2Vec2[vertexes];

		
		setPrimitiveType(sf::LineStrip);

		//! Set each vertex in the shape
		for (int x = 0; x < vertexes; x++)
		{
			sf::Vertex vertex(sf::Vector2f(verticies[x].x, verticies[x].y), sf::Color::Red);
			append(vertex);
			m_chain[x] = verticies[x];
		}
		
		m_shape.CreateChain(m_chain, vertexes);

		
		m_body = world->CreateBody(&m_bodyDef);
		m_body->SetUserData(this);

		m_fixture.shape = &m_shape;
		m_fixture.friction = m_kfFriction;
		m_fixture.density = m_kfDensity;
		m_fixture.restitution = m_kfRestitution;

		m_body->CreateFixture(&m_fixture);
	}
	/**<
	*	Track constructor, used to create a track for a racetrack with modifyable values
	*	\param world Pointer used to reference the world when making the body
	*	\param verticies vertexes for the shape
	*	\param vertexes # of vertexes in the chain
	*/
};
#endif