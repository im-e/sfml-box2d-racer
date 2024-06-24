#ifndef HUD_HEADER
#define HUD_HEADER
/*! 
\file hud.h
* \brief This file contains the definition of the Hud class
*/

#include <SFML/Graphics.hpp>

/*! \class Hud
* \brief Hud is a class which contains all visual elements for the heads up display
*/
class Hud : public sf::Drawable
{
public:
	//! Default Constructor
	Hud();

	//! Font for text
	sf::Font hudFont; 

	//! Vector of Vector2fs for each vertex in the lap background shape
	std::vector<sf::Vector2f> hudBgLapPoints;
	//! Shape for the lap Background
	sf::ConvexShape hudBgLaps; 
	//! Text for the lap Label
	sf::Text hudTxLapsLabel;
	//! Text label for the players lap count
	sf::Text hudTxLaps;

	//! Vector of Vector2fs for each vertex in the lap background shape
	std::vector<sf::Vector2f> hudBgTimePoints;
	//! Shape for the Timer background
	sf::ConvexShape hudBgTime;
	//! Text for the timer
	sf::Text hudTxTime;

	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	/**<
	*	Virtual function used to draw all drawable objects that are in the class
	*/
};
#endif