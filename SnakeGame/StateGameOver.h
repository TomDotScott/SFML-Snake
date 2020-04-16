#pragma once
#include "StateManager.h"

/**
 * \brief The GameOver State is displayed to the player when the game has ended
 */
class StateGameOver final : public BaseState {
public:
	/**
	 * \brief Constructs a StateGameOver object
	 * \param _soundManager A reference to the sound manager to play sound effects and music
	 * \param _isTwoPlayer true if the game is 2 player
	 * \param _playerWon true if the game was won in the last game
	 */
	explicit StateGameOver(SoundManager& _soundManager, const bool& _isTwoPlayer = false, const bool& _playerWon = false);
	/**
	 * \brief Called upon the creation of the object
	 * \param _window a reference to the game window
	 * \param _font the font that will be used in the game
	 */	
	void OnCreate(sf::RenderWindow& _window, sf::Font& _font) override;
	
	/**
	 * \brief Update is called once per game loop
	 * \param _window a reference to the game window
	 */
	void Update(sf::RenderWindow& _window) override;

	/**
	 * \brief Draws renderables to the window
	 * \param _window a reference to the game window
	 */
	void Render(sf::RenderWindow& _window) override;
private:
	/**
	 * \brief Works out who won the game and displays the result on screen
	 */
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

