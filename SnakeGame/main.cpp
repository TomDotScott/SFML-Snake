/*
  Games Development with C++ GAV1031-N
  Snake ICA start project 
  
  Set up to use the SFML 2.5.1 64-bit API
    SFML documentation: https://www.sfml-dev.org/learn.php
*/

#include <iostream>

// SFML header file for graphics, there are also ones for Audio, Window, System and Network
#include <SFML/Graphics.hpp>
#include "Food.h"
#include "Game.h"
#include "Snake.h"
#include "Entity.h"
#include <vector>
#include <assert.h>
#include <time.h>


enum class EntityType 
{
	Player = 0,
	Enemy
};

int main()
{	
	//seed the random number generator
	std::srand((unsigned int)time(NULL));

	sf::Clock clock;

    // All SFML types and functions are contained in the sf namespace

    // Create an instance of the SFML RenderWindow type which represents the display
    // and initialise its size and title text
    sf::RenderWindow window(sf::VideoMode(800, 600), "C++ Snake ICA - Thomas Scott : W9036922");


	//Snake* snake = new Snake(sf::Color(255, 0, 0), sf::Vector2f(400, 300), 10, 10, sf::Vector2f(0.1, 0.1));

	Game* game = new Game(window);

    // We can still output to the console window
    std::cout << "SnakeGame: Starting" << std::endl;

    // Main loop that continues until we call window.close()
    while (window.isOpen())
    {
        // Handle any pending SFML events
        // These cover keyboard, mouse,joystick etc.
        sf::Event event;
        while (window.pollEvent(event))
        {
          switch(event.type)
          {
            case sf::Event::Closed:
              window.close();
            break;
          }
        }

		//input and collisions should be done outside of the game tick
		game->Input();
		

		while (clock.getElapsedTime() >= sf::milliseconds(500)) {

			// We must clear the window each time around the loop
			window.clear();
			game->CheckCollisions();
			game->Update();

			// Get the window to display its contents
			window.display();
			clock.restart();
		}


    }

    std::cout << "SnakeGame: Finished" << std::endl;

    return 0;
}
