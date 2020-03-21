#include "Entity.h"

Entity::Entity(sf::Color color, sf::Vector2f position)
	: m_colour(color),
	m_position(position)
{
}


Entity::~Entity()
= default;

//Entity::Entity() = default;

void Entity::Move() {
	return;
}

int Entity::RandomRange(const int min, const int max) {
	return min + rand() % ((max + 1) - min);
}