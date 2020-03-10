#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "Constants.h"


enum class eFoodType {
	eStandard, eSpecial, eGobble
};

class Food : public Entity
{
private:
	sf::CircleShape m_circle;
	
	int RandomRange(int min, int max);
	
	eFoodType m_type;
	
	void RandomisePosition();

public:
	Food();

	void Randomise();


	void Render(sf::RenderWindow& window);

	Food(sf::Color colour, sf::Vector2f position);

	sf::Vector2f GetPosition() { return m_position; }

	int GetGrowAmount() {
		switch (m_type)
		{
		case eFoodType::eStandard:
			return Constants::kStandardGrowAmount;
		case eFoodType::eSpecial:
			return Constants::kSpecialGrowAmount;
		case eFoodType::eGobble:
			return Constants::kGobbleGrowAmount;
		}
	}
};


