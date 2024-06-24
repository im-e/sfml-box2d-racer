#ifndef BEGINNERTRACK_HEADER
#define BEGINNERTRACK_HEADER

/*!
\file beginnerTrack.h
* \brief This file contains the definition of the beginnerTrack class
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "racetrack.h"

/*! \class BeginnerTrack
*	\brief BeginnerTrack is a class for the beginnerTrack level, it contains a racetrack which has a start and a checkpoint with a solid color background
*/

class BeginnerTrack : public sf::Drawable
{
private:
	//! racetrack class
	Racetrack m_racetrack;
	//! background for the track
	sf::RectangleShape m_bckShape;

public:

	//! start/finish line
	Start m_start[1];
	//! checkpoint
	Checkpoint m_checkpoint[1];

	
	void createBeginnerTrack(b2World* world)
	{
		m_start[0].createStart(world, sf::Vector2f(0.f, 5.f), 0.f, sf::Vector2f(7.f, 1.f));
		m_checkpoint[0].createCheckpoint(world, sf::Vector2f(7.f, 5.f), 0.f, sf::Vector2f(7.f, 1.f));

		m_bckShape.setSize(sf::Vector2f(14.f, 20.f));
		m_bckShape.setPosition(sf::Vector2f(-3.5f, -5.f));
		m_bckShape.setFillColor(sf::Color(128, 128, 128, 255));

		std::vector<b2Vec2>  vv2BeginnerInner;
		vv2BeginnerInner.push_back(b2Vec2(3.5f, 0.f));
		vv2BeginnerInner.push_back(b2Vec2(3.5f, 10.f));

		std::vector<b2Vec2>  vv2BeginnerOuter;
		vv2BeginnerOuter.push_back(b2Vec2(-3.5f, 0.f));
		vv2BeginnerOuter.push_back(b2Vec2(-3.5f, 15.f));
		vv2BeginnerOuter.push_back(b2Vec2(10.5f, 15.f));
		vv2BeginnerOuter.push_back(b2Vec2(10.5f, -5.f));
		vv2BeginnerOuter.push_back(b2Vec2(-3.5f, -5.f));
		vv2BeginnerOuter.push_back(b2Vec2(-3.5f, 0.f));

		for (Start& start : m_start) start.setUserData(new std::pair<std::string, void *>(typeid(decltype(start)).name(), &start));
		for (Checkpoint& checkpoint : m_checkpoint) checkpoint.setUserData(new std::pair<std::string, void *>(typeid(decltype(checkpoint)).name(), &checkpoint));

		m_racetrack.createRacetrack(world, vv2BeginnerInner, vv2BeginnerOuter);
	}
	/**<
	*	Track constructor, creates the track so it can be played on
	*	\param world Pointer used to reference the world when making the body
	*/

	void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw(m_bckShape);

		for (Start start : m_start) target.draw(start);
		for (Checkpoint checkpoint : m_checkpoint) target.draw(checkpoint);
		target.draw(m_racetrack);
	}
	/**<
	*	Virtual function used to draw all drawable objects that are in the class
	*/
};
#endif