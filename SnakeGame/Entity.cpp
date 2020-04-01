#include "Entity.h"

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

int Entity::RandomRange(const int _min, const int _max) {
	return _min + rand() % ((_max + 1) - _min);
}