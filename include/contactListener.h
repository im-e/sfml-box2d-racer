#ifndef CONTACTLISTENER_HEADER
#define CONTACTLISTENER_HEADER
/*!
\file contactListener.h
* \brief This file contains the definition of the ContactListener class
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "start.h"
#include "checkpoint.h"
#include "car.h"

/*! \class ContactListener
*	\brief The ContactListener class is used to manage and detect collisions between object in the game
*/

class ContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact);
	/**<
*	Runs when the 
*	\param contact b2contact for the collision between two objects
	*/
	void EndContact(b2Contact* contact);
	/**<
*	updates the game, calls each dynamic objects .update functions and steps through the world
*	\param contact b2contact for the collision between two objects
	*/
};
#endif