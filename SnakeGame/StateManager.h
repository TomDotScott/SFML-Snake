#pragma once
#include "BaseState.h"
#include "Constants.h"
#include "SFML/Graphics.hpp"
#include "SoundManager.h"

/**
 * \brief Used to change state in the game
 */
enum class EState {
	eMainMenu, eControlsMenu, eGame, eGameOver
};


/**
 * \brief The StateManager class keeps track of the current state in the game and controls each of their functions
 */
class StateManager {
public:
	/**
	 * \brief Constructs a StateManager object
	 */
	StateManager() = default;
	
	/**
	 * \brief Destroys the StateManager
	 */
	~StateManager();

	/**
	 * \brief Changes the game state based on the enum passed in
	 * \param _state The state to change to 
	 * \param _window A reference to the game window
	 * \param _twoPlayer Whether the state should be initialised to 2 player (defaulted to false)
	 * \param _playerWon Whether the state should be initialised to the player winning (defaulted to false)
	 */
	void ChangeState(const EState& _state, sf::RenderWindow& _window, const bool _twoPlayer = false, const bool _playerWon = false);

	/**
	 * \brief Called upon the creation of the object
	 * \param _window a reference to the game window
	 * \param _font the font that will be used in the game
	 * \param _state The State to Initialise the State Manager into
	 * \param _soundManager A reference to the sound manager to play sound effects and music
	 */
	void OnCreate(sf::RenderWindow& _window, const sf::Font& _font, const EState& _state, const SoundManager& _soundManager);
	
	/**
	 * \brief Handles Input across all of the states
	 * \param _event A reference to the sf::Event so that Input is irrespective of the game loop
	 */
	void Input(sf::Event& _event) const;
	
	/**
	* \brief Update is called once per game loop. Calls the Update function from the Current State
	* \param _window a reference to the game window
	*/
	void Update(sf::RenderWindow& _window) const;

	/**
	 * \brief Draws renderables in the current state to the window
	 * \param _window a reference to the game window
	 */
	void Render(sf::RenderWindow& _window) const;

	/**
	 * \return the current state that the state manager is in
	 */
	EState GetCurrentState() const { return m_currentState; }
private:
	/**
	 * \brief Sets a new state for the game
	 * \param _state The state to switch to
	 * \param _window A reference to the game window
	 */
	void SetState(BaseState* _state, sf::RenderWindow& _window);

	sf::Font m_font;
	EState m_currentState{ EState::eMainMenu };
	BaseState* m_state{ nullptr };
	SoundManager m_soundManager;
};

extern StateManager STATE_MANAGER;
extern bool QUIT_GAME;
