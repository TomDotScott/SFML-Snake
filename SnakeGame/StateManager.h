#pragma once
#include "SFML/Graphics.hpp"

//Every state needs to be able to do these 4 things
//If an object can't, it's not a state
class BaseState
{
public:
	virtual void Initialize(sf::RenderWindow* _window) = 0;
	virtual void Update(sf::RenderWindow* _window) = 0;
	virtual void Render(sf::RenderWindow* _window) = 0;
	virtual void Destroy(sf::RenderWindow* _window) = 0;
};


//StateManager keeps track of the current game state
class StateManager
{
public:
	StateManager();
	void SetWindow(sf::RenderWindow* _window);
	void SetState(BaseState* _state);
	void Update() const;
	void Render() const;
	~StateManager();
private:
	sf::RenderWindow* m_window;
	BaseState* m_state;
};

extern StateManager core_state;
extern bool quit_game;

