/*!
\file game.cpp
*/

#include "game.h"
#include <iostream>
Game::Game()
{
	//! World set
	m_pWorld = new b2World(m_bv2fGravity);
	//! Set size of new render window
	m_view.setSize(m_v2fViewSize);
	m_view.setCenter(sf::Vector2f(0.f, 5.f));

	//! Car + Tires
	m_car.createCar(m_pWorld, sf::Vector2f(0.f, 5.f), sf::Vector2f(.6f, .9f));
	//! Set the data of the car to be a pair so it can be used by the sensors
	m_car.setUserData(new std::pair<std::string, void *>(typeid(decltype(m_car)).name(), &m_car));
	
	//! Track construction
	m_beginnerTrack.createBeginnerTrack(m_pWorld);

	//! Set the contact listener for the world
	m_pWorld->SetContactListener(&m_collisions);

	//! Set the text for the hud
	hud.hudTxLaps.setString(std::to_string(m_car.m_iLaps));
}

void Game::update(float timestep, bool input, int gas, int turn)
{
	//! Update lap count
	hud.hudTxLaps.setString(std::to_string(m_car.m_iLaps));

	//! Update timer
	if (m_car.m_bRaceStarted)
	{
		hud.hudTxTime.setString(std::to_string(m_car.m_clCourseTime.getElapsedTime().asSeconds()));
	}

	//! Center the camera to the car
	m_view.setCenter(m_car.m_sfShape.getPosition());
	//! Update the world
	m_pWorld->Step(timestep, m_kiVelocityIterations, m_kiPositionIterations);
	//! update the car + tires
	m_car.update(input, gas, turn);
}

bool Game::hasGameFinished()
{
	return m_car.m_bCourseComplete;
}

void Game::gameFinish()
{
	std::cout << "Congratulations" << std::endl << "You finished in: " << m_car.fCourseTime << std::endl;
	for (int x = 0; x < m_car.m_iLaps; x++)
	{
		std::cout << "Lap " << x << " : " << m_car.m_afTimes[x] << std::endl;
	}
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	//! Set view
	target.setView(m_view);
	target.draw(m_beginnerTrack);
	target.draw(m_car);
	
	//hud
	if (!m_car.m_bCourseComplete)
	{
		target.setView(m_viewhud);
		target.draw(hud);

	}
	
}






