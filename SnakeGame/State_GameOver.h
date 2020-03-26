#pragma once
#include "StateManager.h"
class State_GameOver : public BaseState
{
public:
	void Initialize(sf::RenderWindow* _window, sf::Font* _font) override;
	void Update(sf::RenderWindow* _window) override;
	void Render(sf::RenderWindow* _window) override;
	void Destroy(sf::RenderWindow* _window) override;
};

