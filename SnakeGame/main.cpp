// SFML header file for graphics, there are also ones for Audio, Window, System and Network
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Food.h"
#include "State_Game.h"
#include "Snake.h"
#include "Entity.h"
#include <vector>
#include <assert.h>
#include <time.h>
#include "Constants.h"

int main() {	
	//seed the random number generator
	std::srand(static_cast<unsigned int>(time(NULL)));

    sf::RenderWindow window(sf::VideoMode(Constants::k_screenWidth, Constants::k_screenHeight), "C++ Snake ICA - Thomas Scott : W9036922");

	//Load in the font and make sure it has loaded properly
	sf::Font font;
	if (!font.loadFromFile("Resources/Graphics/gamefont.ttf"))
	{
		assert(false);
	}

	//Snake* snake = new Snake(sf::Color(255, 0, 0), sf::Vector2f(400, 300), 10, 10, sf::Vector2f(0.1, 0.1));

	State_Game* game = new State_Game(window, font);

	game->Play();

    return 0;
}
