#pragma once
#include "Snake.h"
#include "Food.h"
#include <array>
#include "StateManager.h"

/**
 * \brief The walls of the Game
 */
struct Wall {
	
	/**
	 * \brief Constructs a wall
	 * \param _position The position of the Wall
	 * \param _fileName The file name of the texture
	 */
	Wall(const sf::Vector2f _position, const std::string& _fileName) : m_position(_position) {
		m_texture.loadFromFile("Resources/Graphics/" + _fileName);
		m_wall.setTexture(m_texture);
		m_wall.setPosition(m_position);
	}
	sf::Vector2f m_position{};
	sf::Sprite m_wall{};
	sf::Texture m_texture{};
};


/**
 * \brief The Game State. This object controls all of the game methods for Single and Two Player modes
 */
class StateGame final : public BaseState {
public:
	/**
	 * \brief Constructs a Game State
	 * \param _soundManager A reference to the sound manager to play sounds and sound effects
	 * \param _twoPlayer true if the game is going to be two player
	 */
	explicit StateGame(SoundManager& _soundManager, const bool& _twoPlayer);

	/**
	 * \brief Destroys the Game State
	 */
	~StateGame();

	void OnCreate(sf::RenderWindow& _window, sf::Font& _font) override;
	void Update(sf::RenderWindow& _window) override;
	void Render(sf::RenderWindow& _window) override;

	
	/**
	 * \brief Deals with Input in the game
	 */
	void HandleInput();
	
	/**
	 * \brief Cycles through each game object and checks for collisions
	 */
	void CheckCollisions();
private:
	/**
	 * \brief Displays the HighScore in the game, reading from a text file
	 */
	void SetHighScoreText();

	
	//ensure that food doesn't overlap
	/**
	 * \brief Randomises food position and ensures that food isn't overlapping
	 * \param _foodToRandomise a pointer to the food object to be randomised
	 */
	void RandomiseFood(Food* _foodToRandomise);
	
	/**
	 * \brief Displays the scores on screen
	 */
	void UpdateScores();

	
	/**
	 * \brief Saves the scores to a text file
	 */
	void SaveScores();

	
	/**
	 * \brief Saves scores and changes to the Game Over State
	 * \param _window the window to be rendered to
	 */
	void GameOver(sf::RenderWindow& _window);

	/**
	 * \brief Checks each of the winning conditions to see whether the game has ended
	 * \param _window The window to be rendered to 
	 */
	void CheckWinningConditions(sf::RenderWindow& _window);

	/**
	 * \brief Ends Gobble Mode if gobble mode is active
	 */
	void EndGobbleMode();

	
	/**
	 * \brief Checks if any player is still alive
	 * \return true if more than 1 player is alive
	 */
	bool StillAlive();

	/**
	 * \brief Pauses the game
	 */
	void PauseGame();
	
	/**
	 * \brief A container for all of the snakes in the game
	 */
	std::vector<Snake*> m_snakes;

	/**
	 * \brief A container for all of the food in the game
	 */
	std::array<Food*, constants::k_foodAmount> m_foodArray{};

	
	bool m_gobble{ false };
	
	bool m_gobbleOnScreen{ false };
	
	bool m_paused{ false };

	//TOP
	Wall m_topWall{ Wall({0, 100}, "top_bottom_wall.png") };
	//LEFT
	Wall m_leftWall{ Wall({0, 100}, "left_right_wall.png") };
	//BOTTOM
	Wall m_bottomWall{ Wall({0, constants::k_screenHeight - constants::k_gameGridCellSize}, "top_bottom_wall.png") };
	//RIGHT
	Wall m_rightWall{ Wall({constants::k_screenWidth - constants::k_gameGridCellSize, 100}, "left_right_wall.png") };

	//The Game Background
	sf::Sprite m_grassSprite;
	sf::Texture m_grassTexture;

	//The Clock icon
	sf::Sprite m_clockSprite;
	sf::Texture m_clockTexture;

	//The time remaining
	sf::Clock m_clock;
	//If it is 2 player or single player mode
	bool m_twoPlayer{ false };

	float m_gameTimer{ 0.f };

	std::string m_highScore{ "0" };

	UIText m_pausedText{ "Paused", sf::Color::White,
		{ static_cast<float>(constants::k_screenWidth) / 2.f, static_cast<float>(constants::k_screenHeight) / 2.f },
		m_font, 128 };

	//The overall time remaining
	UIText m_clockText{ "90", sf::Color::White,
		{ constants::k_gameGridCellSize * 2, constants::k_gameGridCellSize }, m_font, constants::k_gameGridCellSize };

	//Player Scores
	UIText m_playerScore{ "P1:", sf::Color(104, 136, 217),
		{ static_cast<float>(m_clockText.m_position.x + 5 * constants::k_gameGridCellSize), m_clockText.m_position.y},
		m_font, constants::k_gameGridCellSize };

	UIText m_player2Score{ "P2:", sf::Color(245, 77, 56),
	{ static_cast<float>(m_playerScore.m_position.x + 120), m_clockText.m_position.y},
		m_font, constants::k_gameGridCellSize };

	UIText m_CPU1Score{ "CPU1:", sf::Color(245, 77, 56),
	{ static_cast<float>(constants::k_screenWidth) / 2.f + constants::k_gameGridCellSize, m_playerScore.m_position.y},
		m_font, constants::k_gameGridCellSize };

	UIText m_CPU2Score{ "CPU2:", sf::Color(245, 77, 56),
		{ static_cast<float>(constants::k_screenWidth - 5 * constants::k_gameGridCellSize), m_CPU1Score.m_position.y},
		m_font, constants::k_gameGridCellSize };

	UIText m_highScoreText{ "Hi-Score: ", sf::Color::White,
		{static_cast<float>(3 * constants::k_gameGridCellSize), 2.5 * static_cast<float>(constants::k_gameGridCellSize)},
		m_font, constants::k_gameGridCellSize };

	//Gobble Mode text
	UIText m_gobbleModeText{ "Gobble Mode", sf::Color::Yellow,
		{ constants::k_screenWidth - 120, m_highScoreText.m_position.y},
		m_font, constants::k_gameGridCellSize };

	//The text that will always be on screen
	std::vector<UIText*> m_UItoRenderSinglePlayer{
		&m_clockText, &m_playerScore, &m_CPU1Score, &m_CPU2Score, &m_highScoreText
	};

	std::vector<UIText*> m_UItoRenderTwoPlayer{
		&m_clockText, &m_playerScore, &m_player2Score, &m_highScoreText
	};
};