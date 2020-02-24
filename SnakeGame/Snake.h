#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"

class Snake : public Entity
{
private:
	float m_height = 1;
	float m_width = 2;
	sf::RectangleShape m_rectangle;
public:
	void Render(sf::RenderWindow& window);
	Snake(sf::Color colourToBe, sf::Vector2f vector, float heightToBe, float widthToBe, sf::Vector2f speedToBe);
	void Move();
	void Update();
};
