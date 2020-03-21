#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "Constants.h"
#include <assert.h>


enum class eFoodType {
	e_standard, e_special, e_gobble
};

class Food : public Entity {
private:
	sf::CircleShape m_circle;

	eFoodType m_type;

	int m_id{ RandomRange(0, 1000) };
	
	void RandomisePosition();

public:
	Food();

	~Food();
	
	void Randomise();

	int GetID() const { return m_id; }

	void Render(sf::RenderWindow& window) override;

	Food(sf::Color colour, sf::Vector2f position);

	sf::Vector2f GetPosition() const { return m_position; }

	int GetGrowAmount() const {
		switch (m_type) {
		case eFoodType::e_standard:
			return Constants::k_standardGrowAmount;
		case eFoodType::e_special:
			return Constants::k_specialGrowAmount;
		case eFoodType::e_gobble:
			return Constants::k_gobbleGrowAmount;
		}

		assert(false);
		return 0;
	}

	eFoodType GetType() const { return m_type; }
};

inline bool operator==(const Food& lhs, const Food& rhs) {
	/* do actual comparison */
	if(lhs.GetID() == rhs.GetID())
	{
		return true;
	}
	return false;
}

inline bool operator!=(const Food& lhs, const Food& rhs) { return !(lhs == rhs); }
