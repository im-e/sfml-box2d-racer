#ifndef RACETRACK_HEADER
#define RACETRACK_HEADER
/*!
\file racetrack.h
* \brief This file contains the definition of the Racetrack class
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "track.h"

/*! \class Racetrack
* \brief Racetrack is a class used to create a level which the player can race on, it does so by putting together
* two tracks.
*/

class Racetrack : public sf::Drawable
{
public:

	void createRacetrack(b2World * world, std::vector<b2Vec2> innerPos, std::vector<b2Vec2> outerPos);
	/**<
	*	Track constructor, used to create a track for a racetrack with modifyable values
	*	\param world Pointer used to reference the world when making the body
	*	\param innerPos vertexes for the inner Track
	*	\param outerPos vertexes for the outer Track
	*/

	
	Track InnerTrack;
	Track OuterTrack;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	/**<
	*	Virtual function used to draw all drawable objects that are in the class
	*/
};
#endif