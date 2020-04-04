#include "Entity.h"

#include "Constants.h"

Entity::Entity(sf::Color _color, sf::Vector2f _position)
	: m_colour(_color),
	m_position(_position) {
}


Entity::~Entity()
= default;

//Entity::Entity() = default;

void Entity::Move() {
	return;
}

void Entity::RandomisePosition() {
	//Find a random grid position

	m_colour = sf::Color(RandomRange(0, 255), RandomRange(0, 255), RandomRange(0, 255));

	//Choose Random Column
	int randomNumber{ RandomRange(2, Constants::k_gameGridColumns) };

	m_position.x = static_cast<float>((randomNumber * Constants::k_gameGridCellSize >= Constants::k_gameWidth
		? Constants::k_gameWidth
		: randomNumber * Constants::k_gameGridCellSize));

	//Choose random row
	randomNumber = RandomRange(2, Constants::k_gameGridRows);

	m_position.y = static_cast<float>((randomNumber * Constants::k_gameGridCellSize >= Constants::k_gameHeight
		? Constants::k_gameHeight
		: randomNumber * Constants::k_gameGridCellSize));

	m_sprite.setPosition(m_position);
}

int Entity::RandomRange(const int _min, const int _max) {
	return _min + rand() % ((_max + 1) - _min);
}
