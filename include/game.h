#ifndef GAME_HEADER
#define GAME_HEADER
/*!
\file game.h
* \brief This file contains the definition of the Game class
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "contactListener.h"
#include "car.h"
#include "hud.h"
#include "BeginnerTrack.h"

/*! \class Game
* \brief Game class, holds the b2World, controls all bodies within the world and the game itself
* is the main area of control for the game.
*/

class Game : public sf::Drawable {
private:

	//! Vector for the gravity of the world
	const b2Vec2 m_bv2fGravity = b2Vec2(0.f, 0.f);
	//! int for the amount of velocity iterations world will make for each step
	const int m_kiVelocityIterations = 8;
	//! int for the amount of position iterations world will make for each step
	const int m_kiPositionIterations = 4;
	//! pointer to the box2d world
	b2World * m_pWorld = nullptr;
	
	//! the main view for the game
	sf::View m_view;
	//! the view for the hud
	sf::View m_viewhud;
	//! vector to size the main view for the game
	sf::Vector2f m_v2fViewSize = sf::Vector2f(12.288f, 9.6f);

	//! Car
	Car m_car;
	//! Contact listener
	ContactListener m_collisions;
	//! Map/Racetrack
	BeginnerTrack m_beginnerTrack;
	//! Hud
	Hud hud;

public:
	//! Defualt constructor
	Game();

	//! bool to enable the end screen
	bool bEndScreen = false;
	
	void update(float timestep, bool input, int key, int turn);
	/**<
*	updates the game, calls each dynamic objects .update functions and steps through the world
*	\param timestep float for the amount of time the world will progress with the update
*	\param input bool control for whether the user is giving an input or not
*	\param key what direction the user wants to move the car
*	\param turn what direction the user wants to turn the car
	*/

	//! Checks if the course has been completed
	bool hasGameFinished();
	
	//! Runs when the game has finished
	void gameFinish();

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	/**<
	*	Virtual function used to draw all drawable objects that are in the class
	*/
};
#endif