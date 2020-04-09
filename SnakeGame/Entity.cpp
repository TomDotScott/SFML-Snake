#include "Entity.h"

#include "Constants.h"

Entity::Entity(sf::Color _color, sf::Vector2f _position)
	: m_colour(_color),
	m_position(_position) {
}

void Entity::RandomisePosition() {
	//Find a random grid position
	//Choose Random Column
	int randomNumber{ RandomRange(2, constants::k_gameGridColumns - 1) };

	m_position.x = static_cast<float>((randomNumber * constants::k_gameGridCellSize >= constants::k_gameWidth
		? constants::k_gameWidth
		: randomNumber * constants::k_gameGridCellSize));

	//Choose random row
	randomNumber = RandomRange(6, constants::k_gameGridRows - 1);

	m_position.y = static_cast<float>((randomNumber * constants::k_gameGridCellSize >= constants::k_gameHeight
		? constants::k_gameHeight
		: randomNumber * constants::k_gameGridCellSize));

	m_sprite.setPosition(m_position);
}

int Entity::RandomRange(const int _min, const int _max) {
	return _min + rand() % ((_max + 1) - _min);
}
