#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "Constants.h"
#include <assert.h>

enum class EFoodType {
	eStandard, eSpecial, eGobble
};

class Food : public Entity {
public:
	Food();

	void Randomise();

	void Render(sf::RenderWindow& _window) override final;

	sf::Vector2f GetPosition() const { return m_position; }

	int GetGrowAmount() const {
		switch (m_type) {
		case EFoodType::eStandard:
			return constants::k_standardGrowAmount;
		case EFoodType::eSpecial:
			return constants::k_specialGrowAmount;
		case EFoodType::eGobble:
			return constants::k_gobbleGrowAmount;
		}

		assert(false);
		return 0;
	}

	EFoodType GetType() const { return m_type; }
private:
	//the textures
	sf::Texture m_standardTexture;
	sf::Texture m_specialTexture;
	sf::Texture m_gobbleTexture;

	EFoodType m_type{ EFoodType::eStandard };
};
