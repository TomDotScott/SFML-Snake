#pragma once
#include "Snake.h"
#include "Food.h"
#include <array>
#include "StateManager.h"

struct Wall {
	Wall(const sf::Vector2f _position, const std::string& _fileName) : m_position(_position) {
		m_texture.loadFromFile("Resources/Graphics/" + _fileName);
		m_wall.setTexture(m_texture);
		m_wall.setPosition(m_position);
	}
	sf::Vector2f m_position;
	sf::Sprite m_wall{};
	sf::Texture m_texture;
};

class State_Game final : public BaseState {
public:
	//BASESTATE METHODS
	void Initialize(sf::RenderWindow& _window, sf::Font& _font, SoundManager* _soundManager) override;
	void Update() override;
	void Render(sf::RenderWindow& _window) override;
	void Destroy() override;

	//GAME METHODS
	void HandleInput();
	void CheckCollisions();
	~State_Game();

private:
	//the game tick
	sf::Clock m_clock;

	//the SoundManager
	SoundManager* m_soundManager{ nullptr };

	//the font for the UI
	sf::Font m_font;

	std::vector<Snake*> m_snakes;

	//The scores of the players
	std::vector<sf::Text> m_scores;

	//Gobble Mode text
	sf::Text* m_gobbleModeText{ nullptr };
	sf::Text* m_pausedText{ nullptr };

	std::array<Food*, Constants::k_foodAmount> m_foodArray{};

	bool m_gobble{ false };
	bool m_paused{ false };

	//TOP
	Wall m_topWall{ Wall({0, 0}, "top_bottom_wall.png") };
	//LEFT
	Wall m_leftWall{ Wall({0, 0}, "left_right_wall.png") };
	//BOTTOM
	Wall m_bottomWall{ Wall({0, Constants::k_screenHeight - Constants::k_gameGridCellSize}, "top_bottom_wall.png") };
	//RIGHT
	Wall m_rightWall{ Wall({Constants::k_screenWidth - 200 - Constants::k_gameGridCellSize, 0}, "left_right_wall.png") };

	//ensure that food doesn't overlap
	void RandomiseFood(Food* _foodToRandomise);

	//Display the scores on screen
	void UpdateScores();

	void SaveScores();

	sf::Sprite m_grassSprite;
	sf::Texture m_grassTexture;
};