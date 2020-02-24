#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"

enum EDirection : int
{
	eLeft, eRight, eUp, eDown
};

class Snake : public Entity
{
private:
	float m_height = 1;
	float m_width = 2;
	void Move();
	void Input();
	void Render(sf::RenderWindow& window);
	
	EDirection m_direction;

	sf::RectangleShape m_rectangle;
public:
	Snake(sf::Color colourToBe, sf::Vector2f vector, float heightToBe, float widthToBe, sf::Vector2f speedToBe);
	void Update(sf::RenderWindow& window);
};
