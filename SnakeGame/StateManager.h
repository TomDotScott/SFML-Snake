#pragma once
#include "SFML/Graphics.hpp"

//Tracks the current state of the game
//Has a global variable attached
enum class eCurrentState {
	e_MainMenu, e_Game, e_GameOver
};

//Every state needs to be able to do these 4 things:
//*Initialize
//*Update
//*Render
//*Destroy
//If an object can't, it's not a state
class BaseState {
public:
	virtual ~BaseState() = default;
	virtual void Initialize(sf::RenderWindow* _window, sf::Font* _font) = 0;
	virtual void Update(sf::RenderWindow* _window) = 0;
	virtual void Render(sf::RenderWindow* _window) = 0;
	virtual void Destroy(sf::RenderWindow* _window) = 0;

	void SetUpKey(const bool& _upKey) { m_upKey = _upKey; }
	void SetDownKey(const bool& _upKey) { m_upKey = _upKey; }
	void SetLeftKey(const bool& _upKey) { m_upKey = _upKey; }
	void SetRightKey(const bool& _upKey) { m_upKey = _upKey; }
	void SetEscapeKey(const bool& _upKey) { m_upKey = _upKey; }
	void SetSpaceKey(const bool& _upKey) { m_upKey = _upKey; }

protected:
	bool m_upKey = false;
	bool m_downKey = false;
	bool m_leftKey = false;
	bool m_rightKey = false;
	bool m_escapeKey = false;
	bool m_spaceKey = false;
};

//StateManager keeps track of the current game state
class StateManager {
public:
	StateManager();
	void SetWindow(sf::RenderWindow* _window);
	void SetState(BaseState* _state);
	void SetFont(sf::Font* _font);
	void Input(sf::RenderWindow* _window);
	void Update() const;
	void Render() const;
	~StateManager();
private:
	sf::RenderWindow* m_window{ nullptr };
	BaseState* m_state{ nullptr };
	sf::Font* m_font{ nullptr };
};

extern StateManager core_state;
extern bool quit_game;
extern eCurrentState current_state;

