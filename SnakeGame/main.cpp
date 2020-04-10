// SFML header file for graphics, there are also ones for Audio, Window, System and Network
#include <SFML/Graphics.hpp>
#include <iostream>
#include "StateManager.h"
#include "Food.h"
#include "StateGame.h"
#include <assert.h>
#include <time.h>
#include "Constants.h"
#include "SoundManager.h"
#include "StateMainMenu.h"

bool QUIT_GAME;
StateManager STATE_MANAGER;

void game_loop(sf::RenderWindow& _window)
{
	// We must clear the window each time around the loop
	_window.clear();
	STATE_MANAGER.Update(_window);
	STATE_MANAGER.Render(_window);

	// Get the window to display its contents
	_window.display();
}


int main()
{
	SoundManager soundManager;
	
	// Initialise the resources needed for the states	
	sf::RenderWindow window(sf::VideoMode(constants::k_screenWidth, constants::k_screenHeight),"C++ Snake ICA - Thomas Scott : W9036922");
	
	//seed the random number generator
	std::srand(static_cast<unsigned int>(time(nullptr)));

	//Load in the font and make sure it has loaded properly
	sf::Font font;
	if (!font.loadFromFile("Resources/Graphics/gamefont.ttf"))
	{
		std::cout << "FILE COULDN'T BE LOADED" << std::endl;
		assert(false);
	}

	sf::Clock clock;

	STATE_MANAGER.Initialize(window, font, EState::eMainMenu, soundManager);

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event{};
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
			
			//Handle Input outside of the game loops
			STATE_MANAGER.Input(event);

		}
		if (STATE_MANAGER.GetCurrentState() == EState::eGame)
		{
			while (clock.getElapsedTime() >= sf::milliseconds(200)) {

				game_loop(window);
				clock.restart();
			}
		}
		else {
			game_loop(window);
		}
		if (QUIT_GAME) {
			window.close();
		}
	}
	std::cout << "Snake Game: Ended" << std::endl;
	return 0;
}