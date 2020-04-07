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

struct UIText {
	UIText(std::string _string, const sf::Color _colour, const sf::Vector2f _position, const sf::Font& _font, const int _size)
		: m_string(std::move(_string)), m_colour(_colour), m_position(_position), m_font(_font), m_characterSize(_size) {
		m_text = sf::Text(m_string, m_font, m_characterSize);
		m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
		m_text.setFillColor(m_colour);
		m_text.setPosition(m_position);
	}
	sf::Text m_text;
	std::string m_string;
	sf::Color m_colour;
	sf::Vector2f m_position;
	sf::Font m_font;
	int m_characterSize;

	void SetContent(const std::string& _newContent) {
		m_string = _newContent;
		m_text.setString(m_string);
	}
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
	//the SoundManager
	SoundManager* m_soundManager{ nullptr };

	//the font for the UI
	sf::Font m_font;

	std::vector<Snake*> m_snakes;

	//Gobble Mode text
	UIText m_gobbleModeText{ "Gobble Mode", sf::Color::Yellow,
		{ Constants::k_screenWidth - 175, 300},
		m_font, 25 };

	UIText m_pausedText{ "Paused", sf::Color::White,
		{ static_cast<float>(Constants::k_screenWidth) / 2.f, static_cast<float>(Constants::k_screenHeight) / 2.f },
		m_font, 128 };

	//The overall time remaining
	UIText m_clockText{ "90", sf::Color::White,
		{ Constants::k_screenWidth - 145, 25 }, m_font, 25 };

	//Player Scores
	UIText m_playerScore{ "Player:", sf::Color::Red,
		{ static_cast<float>(Constants::k_screenWidth - 175), 75},
		m_font, 25 };

	UIText m_CPU1Score{ "CPU1:", sf::Color::Blue,
	{ static_cast<float>(Constants::k_screenWidth - 175), 125},
		m_font, 25 };

	UIText m_CPU2Score{ "CPU2:", sf::Color::Blue,
	{ static_cast<float>(Constants::k_screenWidth - 175), 175},
		m_font, 25 };
	
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