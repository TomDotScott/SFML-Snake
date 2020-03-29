// SFML header file for graphics, there are also ones for Audio, Window, System and Network
#include <SFML/Graphics.hpp>
#include <iostream>
#include "StateManager.h"
#include "Food.h"
#include "State_Game.h"
#include "Snake.h"
#include "Entity.h"
#include <vector>
#include <assert.h>
#include <time.h>
#include "Constants.h"
#include "List.h"
#include "State_MainMenu.h"

StateManager core_state;
bool quit_game;
eCurrentState current_state;

void GameLoop(sf::RenderWindow& _window)
{
	// We must clear the window each time around the loop
	_window.clear();
	core_state.Update();
	core_state.Render();

	// Get the window to display its contents
	_window.display();
}


int main()
{
	// Initialise the resources needed for the states	
	sf::RenderWindow window(sf::VideoMode(Constants::k_screenWidth, Constants::k_screenHeight), "C++ Snake ICA - Thomas Scott : W9036922");

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

	core_state.SetWindow(&window);

	core_state.SetFont(&font);

	core_state.SetState(new State_MainMenu());
	current_state = eCurrentState::e_MainMenu;

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
		}
		if (current_state == eCurrentState::e_Game)
		{
			while (clock.getElapsedTime() >= sf::milliseconds(250)) {

				GameLoop(window);
				clock.restart();
			}
		}
		else {
			GameLoop(window);
		}

		if (quit_game) {
			window.close();
		}
	}

	std::cout << "Snake Game: Ended" << std::endl;
	
	return 0;
}