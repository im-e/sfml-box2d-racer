#ifndef TIRE_HEADER
#define TIRE_HEADER
/*!
\file tire.h
*	\brief This file contains the definition of the tire class
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "physicsObject.h"

/*! \class Tire
* \brief Tire is a class which contains the functions for creation and the transformation of the tires that will be connected to the car
*/

class Tire : public sf::RectangleShape, public physicsObject
{
public:

	//! Texture for the wheels
	sf::Texture m_tex;

	//! float for the wheels max speed
	float m_fMaxSpeed;
	//! float for the force that is applied to each wheel per update
	float m_fPower;
	//! float for the force that is used to turn the wheels each update
	float m_fTurnPower;
	//! float to control how much the wheels will skid
	float m_fSkiddingImpulse;
	//! float to control the drag upon each wheel
	float m_fDrag;

	void createTire(b2World * world, const sf::Vector2f size, const sf::Vector2f pos);
	/**<
	*	Tire constructor, used to put each tire together with modifyable values
	*	\param world Pointer used to reference the world when making the body
	*	\param pos	Position of the object
	*	\param size	Size of the object
	*/
	void setProperties(float maxForward, float power, float turn, float skid, float drag);
	/**<
	*	Part of the tires construction, used to set each property of every tire
	*	\param maxFoward float for the wheels max speed
	*	\param power float for the force that is applied to each wheel per update
	*	\param turn float for the force that is used to turn the wheels each update
	*	\param skid float to control how much the wheels will skid
	*	\param drag float to control the drag upon each wheel
	*/
	//! updates the physics of the tires when called
	void updatePhysics();

	void updateControls(int tire, bool input, int gas, int turn);
	/**<
	*	Tire update, controls the movement of the body when a player makes an input
	*	\param tire which tire is being moved
	*	\param bool is the user inputting
	*	\param gas is the player moving forward or backward
	*	\param turn is the player moving left or right
	*/


	//! returns the velocity of the object over the horizontal
	b2Vec2 getLateralVelocity();
	//! returns the velocity of the object over the vertical
	b2Vec2 getForwardVelocity();

	//! returns the body of the shape
	b2Body * getBody();

	

};
#endif