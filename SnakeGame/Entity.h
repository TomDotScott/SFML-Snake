#pragma once
#include "SFML/Graphics.hpp"
class Entity
{
protected:
	sf::Color m_colour;
	sf::Vector2f m_position;
	sf::Vector2f m_speed;
public:
	//setting the virtual function to 0 means it is a 'pure' virtual
	//this means that the function can only be called by its children
	//so therefore an Entity cannot exist on its own; it needs to be Food or Snake
	virtual void Render(sf::RenderWindow& window) = 0;

	virtual void Move() = 0;
};
