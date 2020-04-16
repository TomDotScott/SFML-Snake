#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "Constants.h"

/**
 * \brief Decides the current type of food. Can be Standard, Special or Gobble
 */
enum class EFoodType {
	eStandard, eSpecial, eGobble
};

/**
 * \brief Generates a Food object that can be eaten by the snakes
 */
class Food final : public Entity {
public:
	
	/**
	 * \brief Constructs the Food object
	 */
	Food();

	
	/**
	 * \brief Randomises the position and Type of the food
	 */
	void Randomise();

	
	/**
	 * \brief Renders the Food object to the screen
	 * \param _window The game screen
	 */
	void Render(sf::RenderWindow& _window) override final;

	/**
	 * \return The co-ordinates of the food 
	 */
	sf::Vector2f GetPosition() const { return m_position; }

	
	/**
	 * \return The amount that the food makes the snake grow by
	 */
	int GetGrowAmount() const {
		switch (m_type) {
		case EFoodType::eStandard:
			return constants::k_standardGrowAmount;
		case EFoodType::eSpecial:
			return constants::k_specialGrowAmount;
		case EFoodType::eGobble:
			return constants::k_gobbleGrowAmount;
		}
		return 0;
	}

	/**
	 * \return The type of food
	 */
	EFoodType GetType() const { return m_type; }

	friend bool operator==(const Food& _lhs, const Food& _rhs);

	friend bool operator!=(const Food& _lhs, const Food& _rhs);
private:
	//the textures
	sf::Texture m_standardTexture;
	sf::Texture m_specialTexture;
	sf::Texture m_gobbleTexture;

	/**
	 * \brief A store for the current type of food
	 */
	EFoodType m_type{ EFoodType::eStandard };
};


inline bool operator==(const Food& _lhs, const Food& _rhs) {
	return _lhs.GetType() == _rhs.GetType() && _lhs.GetPosition() == _rhs.GetPosition();
}

inline bool operator!=(const Food& _lhs, const Food& _rhs) {
	return !(_lhs == _rhs);
}

