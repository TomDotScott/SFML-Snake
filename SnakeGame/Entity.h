#pragma once
#include "SFML/Graphics.hpp"
class Entity {
public:
	//Makes this the default constructor
	explicit Entity(sf::Color _color = sf::Color::Red, sf::Vector2f _position = sf::Vector2f(0, 0));
	//setting the virtual function to 0 means it is a 'pure' virtual; an abstract class
	virtual void Render(sf::RenderWindow& window) = 0;
	virtual void Move(){};
protected:
	static int RandomRange(const int _min, const int _max);
	void RandomisePosition();

	sf::Color m_colour;
	sf::Vector2f m_position;
	sf::Sprite m_sprite;
};

