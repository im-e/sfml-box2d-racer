/*! \mainpage Top down car simulation - Lilith Burgham - P17160111
* This is my submission for the 2d sports simulation assessment.
*
* Running the program will start the game and prompt you to press space to start.
*
* Once you press start, use the arrow keys to drive around the map.
*
* Complete 5 laps by going all the way around the track to try and get the fastest time.
*
* Once 5 laps have been completed the game will end and your total time, including individual lap time will be printed into the console.
*
*/

/*!
\file main.cpp
\brief Contains the entry point for the application
*/


#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "game.h"

//! defines how long a frame is
const float kfFrameTime = 1.f / 60.f;

//! Entry point for the application
void main() 
{
	//! Creation of the main video window
	sf::RenderWindow window(sf::VideoMode(1024, 800), "CW Starter");

	//! limit the framerate and enable vsync
	window.setFramerateLimit(300);
	window.setVerticalSyncEnabled(true);
	
	//! Game class
	Game game;
	//! Clock which holds how much time has passed in the program
	sf::Clock clock;
	//! int for controlling the car forwards and back
	int iGasInput = 0;
	//! int for controlling the car left and right
	int iTurnInput = 0;
	//! bool for controlling whether the user is inputting
	bool bInput = false;
	
	//! bool to control whether the game is currently running or not
	bool bRunGame = false;
	//! bool to control when the game starts
	bool bStartGame = false;
	//! bool to control when the game ends
	bool bGameOver = false;
	//! bool to control if the title screen needs to be shown
	bool bTitleScreen = true;

	//! Title screen shape
	sf::RectangleShape titleRect;
	//! Title screen texture
	sf::Texture titleTex;

	//! Shape attributes
	titleRect.setPosition(512, 400);
	titleRect.setSize(sf::Vector2f(600, 450));
	titleRect.setOrigin(sf::Vector2f((titleRect.getSize().x / 2), (titleRect.getSize().y / 2)));
	titleRect.setFillColor(sf::Color(255, 255, 255, 255));
	//! title texture loading
	if (!titleTex.loadFromFile(".\\assets\\textures\\title.png"))
	{
		std::cout << "title tex error" << std::endl;
	}
	//! apply smoothing and texture
	titleTex.setSmooth(true);
	titleRect.setTexture(&titleTex);

	//! while the window is open
	while (window.isOpen())
	{
		//! create event
		sf::Event event;
		//! poll event
		while (window.pollEvent(event))
		{
			//! if user closes window, close window
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				//! if user presses up
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					bInput = true;
					iGasInput = 0;
					//! Wheels can turn when car is moving
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					{
						iTurnInput = 1;
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					{
						iTurnInput = 2;
					}
				}
				//! if user presses down
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					bInput = true;
					iGasInput = 1;
					//! Wheels can turn when car is moving
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					{
						iTurnInput = 1;
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					{
						iTurnInput = 2;
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					if (bTitleScreen)
					{
						bStartGame = true;
					}
				}
			}
			//! if user releases key
			if (event.type == sf::Event::KeyReleased)
			{
				//! if up or down arent held
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					//! dont let the car turn
					bInput = false;
					iTurnInput = 0;
				}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					iTurnInput = 0;
				}
			}
		}
		//! Find out how much time has elapsed
		float m_fElapsedTime = clock.getElapsedTime().asSeconds(); 
		// If a frame has passed the update the physics
		if (m_fElapsedTime > kfFrameTime) 
		{

			//! Only check once the game has started
			if (bStartGame)
			{
				//! Check if game has ended 
				bRunGame = !game.hasGameFinished();
				bGameOver = game.hasGameFinished();
			}
			//! if game has ended
			if (!bRunGame && bGameOver)
			{
				//! end game
				game.gameFinish();
				bGameOver = false;
				bStartGame = false;
			}
			//! if game is running
			if (bRunGame) 
			{
				//!update the game
				game.update(kfFrameTime, bInput, iGasInput, iTurnInput);
			}

			clock.restart(); // restart the clock
		}

		//draw

		//! if the title screen needs to be drawn
		if (bTitleScreen) {
			window.clear(sf::Color(255, 255, 255, 0));
			window.draw(titleRect);
		}
		//! if the game has ended
		if (bGameOver)
		{
			window.clear(sf::Color(255, 255, 255, 225));
			window.draw(game);
		}
		//! if the game is running
		if (bRunGame) {
			window.clear(sf::Color(255, 255, 255, 255));
			window.draw(game);
		}
		window.display();
	}



}