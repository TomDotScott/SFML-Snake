#pragma once
#include "Snake.h"
#include "PlayerSnake.h"
#include "AISnake.h"
#include "Entity.h"
#include "Food.h"

struct Wall {
	float m_height, m_width;
	sf::Vector2f m_position;
	sf::RectangleShape m_wall;
	sf::Color m_colour = sf::Color::White;
	Wall(const float height, const float width, const sf::Vector2f position) : m_height(height), m_width(width), m_position(position) {
		m_wall = sf::RectangleShape(sf::Vector2f(width, height));
		m_wall.setFillColor(m_colour);
		m_wall.setPosition(m_position);
	}
};

class Game {
private:

	//the font for the UI
	sf::Font m_font;
	
	std::vector<Snake*> m_snakes;

	//The scores of the players
	std::vector<sf::Text> m_scores;

	//Gobble Mode text
	sf::Text m_gobbleModeText;
	
	Food* m_foodArray[5]; //C Array - C++ Array
	
	sf::RenderWindow& m_window;

	//TOP
	Wall m_topWall{ Wall(Constants::k_gridSize, Constants::k_screenWidth - 200, sf::Vector2f(0, 0)) };
	//LEFT
	Wall m_leftWall{ Wall(Constants::k_screenHeight, Constants::k_gridSize, sf::Vector2f(0, 0)) };
	//BOTTOM
	Wall m_bottomWall{ Wall(Constants::k_gridSize, Constants::k_screenWidth - 200, sf::Vector2f(0, Constants::k_screenHeight - Constants::k_gridSize)) };
	//RIGHT
	Wall m_rightWall{ Wall(Constants::k_screenHeight, Constants::k_gridSize, sf::Vector2f(Constants::k_screenWidth - 200 - Constants::k_gridSize, 0)) };

	//ensure that food doesn't overlap
	void RandomiseFood(Food* foodToRandomise);

	//Display the scores on screen
	void UpdateScores();
	
public:
	void Update();
	void Play();
	void Input() const;
	explicit Game(sf::RenderWindow& window, sf::Font& font);
	~Game();
	void CheckCollisions();
};