#pragma once
#include "SFML/Graphics.hpp"
#include "SoundManager.h"
#include "Constants.h"
#include "BaseState.h"

//Tracks the current state of the game
//Has a global variable attached
enum class EState {
	eMainMenu, eControlsMenu, eGame, eGameOver
};

//StateManager keeps track of the current game state
class StateManager {
public:
	StateManager() = default;
	~StateManager();

	void ChangeState(sf::RenderWindow& _window, const EState& _state, const bool _twoPlayer = false, const bool _playerWon = false);

	void Initialize(sf::RenderWindow& _window, const sf::Font& _font, const EState& _state, const SoundManager& _soundManager);
	
	void Input(sf::Event& _event) const;
	void Update(sf::RenderWindow& _window) const;
	void Render(sf::RenderWindow& _window) const;

	EState GetCurrentState() const { return m_currentState; }
private:
	void SetState(BaseState* _state, sf::RenderWindow& _window);

	sf::Font m_font;
	EState m_currentState{ EState::eMainMenu };
	BaseState* m_state{ nullptr };
	SoundManager m_soundManager;
};

extern StateManager STATE_MANAGER;
extern bool QUIT_GAME;
