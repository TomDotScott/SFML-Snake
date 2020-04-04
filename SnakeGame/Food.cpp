#include "Food.h"
#include "SFML/Graphics.hpp"
#include <iostream>

Food::Food() {
	m_type = eFoodType::e_standard;
	
	m_standardTexture.loadFromFile("Resources/Graphics/Food_Standard.png");
	m_specialTexture.loadFromFile("Resources/Graphics/Food_Special.png");
	m_gobbleTexture.loadFromFile("Resources/Graphics/Food_Gobble.png");

	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	
	Randomise();
}

void Food::Randomise() {
	//there will be 3 types of pickup. Standard, Special and Gobble Mode
	const int randomType{ RandomRange(0, 100) };
	//60% chance of being standard
	if (randomType <= 60) {
		m_type = eFoodType::e_standard;
	}
	//30% chance of being Special
	else if (randomType <= 90) {
		m_type = eFoodType::e_special;
	}
	//10% chance of being Gobble Mode
	else {
		m_type = eFoodType::e_gobble;
	}
	RandomisePosition();
}

void Food::Render(sf::RenderWindow& _window) {
	switch (m_type) {
	case eFoodType::e_standard:
		m_sprite.setTexture(m_standardTexture);
		break;
	case eFoodType::e_special:
		m_sprite.setTexture(m_specialTexture);
		break;
	case eFoodType::e_gobble:
		m_sprite.setTexture(m_gobbleTexture);
		break;
	default:
		break;
	}
	m_sprite.setPosition(m_position);
	_window.draw(m_sprite);
}