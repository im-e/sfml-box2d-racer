#include "hud.h"
#include <iostream>

/*! \file hud.h
* \brief This file contains the definition of the Hud class
*/

Hud::Hud()
{	//! load in font
	if (!hudFont.loadFromFile(".\\assets\\fonts\\enhanced_dot_digital-7.ttf"))	
	{	//!if the font fails to load
		std::cout << "Font Error" << std::endl;			//!< output error
	}

	//! set points for hud shapes 
	hudBgLapPoints.push_back(sf::Vector2f(318, 0));
	hudBgLapPoints.push_back(sf::Vector2f(218, 0));
	hudBgLapPoints.push_back(sf::Vector2f(268, 50));
	hudBgLapPoints.push_back(sf::Vector2f(368, 50));
	hudBgTimePoints.push_back(sf::Vector2f(640, 70));
	hudBgTimePoints.push_back(sf::Vector2f(384, 70));
	hudBgTimePoints.push_back(sf::Vector2f(318, 0));
	hudBgTimePoints.push_back(sf::Vector2f(706, 0));
	
	//! Set point count to size of the vector
	hudBgLaps.setPointCount(hudBgLapPoints.size());
	//! For each point in the vector
	for (int x = 0; x < hudBgLapPoints.size(); x++)
	{
		//! Assign to shape
		hudBgLaps.setPoint(x, hudBgLapPoints[x]);
	}
	//! Shape properties
	hudBgLaps.setFillColor(sf::Color(100, 100, 100));
	//! Set point count to size of the vector
	hudBgTime.setPointCount(hudBgTimePoints.size());
	//! For each point in the vector
	for (int x = 0; x < hudBgTimePoints.size(); x++)
	{
		//! Assign to shape
		hudBgTime.setPoint(x, hudBgTimePoints[x]);
	}
	//! Shape properties
	hudBgTime.setFillColor(sf::Color(170, 170, 170));


	//! Text properties
	hudTxLapsLabel.setFont(hudFont);
	hudTxLapsLabel.setPosition(245, -5);
	hudTxLapsLabel.setCharacterSize(28);
	hudTxLapsLabel.setFillColor(sf::Color(0, 0, 0, 255));
	hudTxLapsLabel.setString("Lap:");	
	
	hudTxLaps.setFont(hudFont); 
	hudTxLaps.setPosition(300, 0);		
	hudTxLaps.setCharacterSize(42);		
	hudTxLaps.setFillColor(sf::Color(0, 0, 0, 255));	

	hudTxTime.setFont(hudFont);
	hudTxTime.setFillColor(sf::Color(0, 0, 0, 255));
	hudTxTime.setPosition(450, 10);
	hudTxTime.setCharacterSize(34);

}

void Hud::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//! Draw every render target
	target.draw(hudBgLaps);
	target.draw(hudBgTime);
	target.draw(hudTxLapsLabel, states);
	target.draw(hudTxLaps, states);			
	target.draw(hudTxTime);
	
}