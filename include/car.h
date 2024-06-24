#ifndef CAR_HEADER
#define CAR_HEADER
/*! 
\file car.h
* \brief This file contains the definition of the Car class
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "physicsObject.h"
#include "tire.h"
#include <iostream>

/*! \class Car
* \brief Car class is the definition for the player vehicle, the car. It is drawable as it contains the car's tires which need to be drawn
* and a physics object as it has a body which has a mass and a place in our game world.
* The car puts together all of the player(car) components together into one class which we can then use to control the player.
*/

class Car : public sf::Drawable, public physicsObject
{
private:
	//! Tire class which holds 4 individual tires
	Tire m_tires[4];
	//! Texture for the car body
	sf::Texture m_tex;
public:
	//! Shape for the car body
	sf::RectangleShape m_sfShape;
	
	//! Returns the b2body for car
	b2Body * getBody();
	//! Revolute joints for the front tires
	b2RevoluteJoint *frontRightJoint, *frontLeftJoint;

	//! Clock which holds the time for a single lap
	sf::Clock m_clLapTime;
	//! Clock which holds the time for a whole course
	sf::Clock m_clCourseTime;
	//! Current player lap count
	int m_iLaps;
	//! Bool which holds if the player has passed a checkpoint
	bool m_bCheckpointPassed;
	//! Bool which holds if the player has spawned
	bool m_bSpawned = true;
	//! Bool which holds if the player has completed the course
	bool m_bCourseComplete = false;
	//! Bool which holds if the race has started or not yet
	bool m_bRaceStarted = false;
	//! Array of floats which hold each individual lap time
	float m_afTimes[5];
	//! float which holds the finished course time
	float fCourseTime;

	void createCar(b2World * world, const sf::Vector2f & pos, const sf::Vector2f size);
	/**<
	*	Car constructor, used to put the car together with modifyable values
	*	\param world Pointer used to reference the world when making the body 
	*	\param pos	Position of the object
	*	\param size	Size of the object
	*/
	void update(bool input, int gas, int turn);
	/**<
	*	Car update function, called every frame to move the car's shape to match the visuals
	* and set the locking values for the joints
	*	\param input bool to signal if the user is currently making an input
	*	\param gas	which direction the player wants to go in
	*	\param turn which direction the player is turning
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	/**<
	*	Virtual function used to draw all drawable objects that are in the class
	*/

	void carCollidedWithFinish(bool collision);
	/**<
	*	Performs an action when the car collides with the start area
	*	\param collision will be true upon collision enter and false upon collision exit
	*/

	//! Sets m_bCheckpointPassed to true
	void carCollidedWithCheckpoint() { if (!m_bCheckpointPassed) m_bCheckpointPassed = true; }
};
#endif
