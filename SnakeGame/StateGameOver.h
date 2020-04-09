#pragma once
#include "StateManager.h"

class StateGameOver final : public BaseState {
public:
	explicit StateGameOver(const bool& _isTwoPlayer, const bool& _playerWon);
	void Initialize(sf::RenderWindow& _window, sf::Font& _font, SoundManager* _soundManager) override;
	void Update() override;
	void Render(sf::RenderWindow& _window) override;
	void Destroy() override;
private:
	void SetWinnerText();
	
	MenuBackground m_menuBackground;

	UIText m_gameOverText{ "Game Over", sf::Color::White,
		{static_cast<float>(constants::k_screenWidth) / 2.f, static_cast<float>(constants::k_screenHeight) / 5.f},
		m_font, 84 };

	//Will display which player wins!
	UIText m_winnerText{ "P1 Wins", sf::Color::White,
		{static_cast<float>(constants::k_screenWidth) / 2.f, static_cast<float>(constants::k_screenHeight) / 5.f},
		m_font, 84 };

	UIText m_highScore{ "HiScore:", sf::Color::White,
		{static_cast<float>(constants::k_screenWidth) / 2.f, static_cast<float>(constants::k_screenHeight) / 2.5f},
		m_font, 32 };
	
	UIText m_player1Score{ "P1 Score:", sf::Color::White,
		{static_cast<float>(constants::k_screenWidth) / 2.f, static_cast<float>(constants::k_screenHeight) / 2.f},
		m_font, 32 };

	UIText m_player2Score{ "P2 Score:", sf::Color(245, 77, 56),
		{static_cast<float>(constants::k_screenWidth) / 2.f, static_cast<float>(constants::k_screenHeight) / 2.f},
		m_font, 32 };

	UIText m_playAgain{ "Play Again", sf::Color::White,
	{static_cast<float>(constants::k_screenWidth) / 2.f, static_cast<float>(constants::k_screenHeight) / 1.5f},
		m_font, constants::k_uiTextElement };

	UIText m_main{ "Main Menu", sf::Color::White,
	{static_cast<float>(constants::k_screenWidth) / 2.f, static_cast<float>(constants::k_screenHeight) / 1.25f},
		m_font, constants::k_uiTextElement };

	std::vector<UIText*> m_textToRenderSinglePlayer{
		&m_gameOverText, &m_highScore, &m_player1Score, &m_playAgain, &m_main
	};

	std::vector<UIText*> m_textToRenderTwoPlayer{
		&m_winnerText, &m_player1Score, &m_player2Score, &m_playAgain, &m_main
	};

	std::string m_player1ScoreValue, m_player2ScoreValue, m_highScoreValue;

	bool m_twoPlayer{ false };
	bool m_playerWon{ false };
};

