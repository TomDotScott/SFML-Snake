#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "Constants.h"
#include <assert.h>


enum class eFoodType {
	e_standard, e_special, e_gobble
};

class Food : public Entity {
public:
	Food();

	~Food();

	void Randomise();

	void Render(sf::RenderWindow& _window) override;

	Food(sf::Color _colour, sf::Vector2f _position);

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

	int GetID() const { return m_id; }

	eFoodType GetType() const { return m_type; }
private:
	sf::CircleShape m_circle;

	int m_id = RandomRange(0, 1000000);

	eFoodType m_type;

	void RandomisePosition();


};

inline bool operator==(const Food& _lhs, const Food& _rhs) {
	/* do actual comparison */
	if (_lhs.GetID() == _rhs.GetID()) {
		return true;
	}
	return false;
}

inline bool operator!=(const Food& _lhs, const Food& _rhs) { return !(_lhs == _rhs); }
