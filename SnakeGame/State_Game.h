#pragma once
#include "Snake.h"
#include "Food.h"
#include <array>
#include <utility>
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
	State_Game() = default;
	State_Game(bool _twoPlayer);
	
	~State_Game();

private:

	//If it is 2 player or single player mode
	bool m_twoPlayer{ false };

	std::string m_highScore;

	void SetHighScoreText();

	//the SoundManager
	SoundManager* m_soundManager{ nullptr };

	//the font for the UI
	sf::Font m_font;

	std::vector<Snake*> m_snakes;

	UIText m_pausedText{ "Paused", sf::Color::White,
		{ static_cast<float>(Constants::k_screenWidth) / 2.f, static_cast<float>(Constants::k_screenHeight) / 2.f },
		m_font, 128 };

	//The overall time remaining
	UIText m_clockText{ "90", sf::Color::White,
		{ Constants::k_gameGridCellSize * 2, Constants::k_gameGridCellSize }, m_font, Constants::k_gameGridCellSize };

	//Player Scores
	UIText m_playerScore{ "P1:", sf::Color(104, 136, 217),
		{ static_cast<float>(m_clockText.m_position.x + 5*Constants::k_gameGridCellSize), m_clockText.m_position.y},
		m_font, Constants::k_gameGridCellSize };

	UIText m_player2Score{ "P2:", sf::Color(245, 77, 56),
	{ static_cast<float>(m_playerScore.m_position.x + 120), m_clockText.m_position.y},
		m_font, Constants::k_gameGridCellSize };
	
	UIText m_CPU1Score{ "CPU1:", sf::Color(245, 77, 56),
	{ static_cast<float>(Constants::k_screenWidth) / 2.f + Constants::k_gameGridCellSize, m_playerScore.m_position.y},
		m_font, Constants::k_gameGridCellSize };

	UIText m_CPU2Score{ "CPU2:", sf::Color(245, 77, 56),
		{ static_cast<float>(Constants::k_screenWidth - 5*Constants::k_gameGridCellSize), m_CPU1Score.m_position.y},
		m_font, Constants::k_gameGridCellSize };

	UIText m_highScoreText{ "Hi-Score: ", sf::Color::White,
		{static_cast<float>(3 * Constants::k_gameGridCellSize), 2.5 * static_cast<float>(Constants::k_gameGridCellSize)},
		m_font, Constants::k_gameGridCellSize };
	
	//Gobble Mode text
	UIText m_gobbleModeText{ "Gobble Mode", sf::Color::Yellow,
		{ Constants::k_screenWidth - 120, m_highScoreText.m_position.y},
		m_font, Constants::k_gameGridCellSize };

	//The text that will always be on screen
	std::vector<UIText*> m_UItoRenderSinglePlayer{
		&m_clockText, &m_playerScore, &m_CPU1Score, &m_CPU2Score, &m_highScoreText
	};

	std::vector<UIText*> m_UItoRenderTwoPlayer{
		&m_clockText, &m_playerScore, &m_player2Score, &m_highScoreText
	};
	
	std::array<Food*, Constants::k_foodAmount> m_foodArray{};

	bool m_gobble{ false };
	bool m_paused{ false };

	//TOP
	Wall m_topWall{ Wall({0, 100}, "top_bottom_wall.png") };
	//LEFT
	Wall m_leftWall{ Wall({0, 100}, "left_right_wall.png") };
	//BOTTOM
	Wall m_bottomWall{ Wall({0, Constants::k_screenHeight - Constants::k_gameGridCellSize}, "top_bottom_wall.png") };
	//RIGHT
	Wall m_rightWall{ Wall({Constants::k_screenWidth - Constants::k_gameGridCellSize, 100}, "left_right_wall.png") };

	//ensure that food doesn't overlap
	void RandomiseFood(Food* _foodToRandomise);

	//Display the scores on screen
	void UpdateScores();

	void SaveScores();

	void GameOver();

	int GetTimeRemaining() const;

	void CheckWinningConditions();

	void EndGobbleMode();

	//Returns true if more than one snake is alive
	bool CheckIfStillAlive();

	//The Game Background
	sf::Sprite m_grassSprite;
	sf::Texture m_grassTexture;

	//The Clock icon
	sf::Sprite m_clockSprite;
	sf::Texture m_clockTexture;

	//The time remaining
	sf::Clock m_clock;
};