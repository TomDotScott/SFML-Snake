#pragma once
#include "Snake.h"
#include "PlayerSnake.h"
#include "AISnake.h"
#include "Entity.h"
#include "Food.h"
#include <array>
#include "StateManager.h"

struct Wall {
	Wall(const float _height, const float _width, const sf::Vector2f _position) : m_height(_height), m_width(_width), m_position(_position) {
		m_wall = sf::RectangleShape(sf::Vector2f(_width, _height));
		m_wall.setFillColor(m_colour);
		m_wall.setPosition(m_position);
	}
	float m_height, m_width;
	sf::Vector2f m_position;
	sf::RectangleShape m_wall;
	sf::Color m_colour = sf::Color::White;
};

class State_Game : public BaseState {
public:
	//BASESTATE METHODS
	void Initialize(sf::RenderWindow* _window, sf::Font* _font) override;
	void Update(sf::RenderWindow* _window) override;
	void Render(sf::RenderWindow* _window) override;
	void Destroy(sf::RenderWindow* _window) override;

	//GAME METHODS
	void GetInput() const;
	void CheckCollisions();
	
private:
	//the game tick
	sf::Clock m_clock;
	
	//the font for the UI
	sf::Font m_font;
	
	std::vector<Snake*> m_snakes;

	//The scores of the players
	std::vector<sf::Text> m_scores;

	//Gobble Mode text
	sf::Text m_gobbleModeText;
	
	std::array<Food*, Constants::k_foodAmount> m_foodArray{};

	bool m_gobble{ false };
	
	//TOP
	Wall m_topWall{ Wall(Constants::k_gridSize, Constants::k_screenWidth - 200, sf::Vector2f(0, 0)) };
	//LEFT
	Wall m_leftWall{ Wall(Constants::k_screenHeight, Constants::k_gridSize, sf::Vector2f(0, 0)) };
	//BOTTOM
	Wall m_bottomWall{ Wall(Constants::k_gridSize, Constants::k_screenWidth - 200, sf::Vector2f(0, Constants::k_screenHeight - Constants::k_gridSize)) };
	//RIGHT
	Wall m_rightWall{ Wall(Constants::k_screenHeight, Constants::k_gridSize, sf::Vector2f(Constants::k_screenWidth - 200 - Constants::k_gridSize, 0)) };

	//ensure that food doesn't overlap
	void RandomiseFood(Food* _foodToRandomise);

	//Display the scores on screen
	void UpdateScores();

	void SaveScores();


};