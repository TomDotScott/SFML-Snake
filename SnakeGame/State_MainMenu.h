#pragma once
#include "StateManager.h"
class State_MainMenu final : public BaseState
{
public:
	void Initialize(sf::RenderWindow* _window, sf::Font* _font) override;
	void Update(sf::RenderWindow* _window) override;
	void Render(sf::RenderWindow* _window) override;
	void Destroy(sf::RenderWindow* _window) override;
	~State_MainMenu();
private:
	sf::Font* m_font { nullptr };
	sf::Text* m_title { nullptr };
	sf::Text* m_play { nullptr };
	sf::Text* m_quit { nullptr };

	//deal with user selections
	int m_selected { 0 };
	//deal with user inputs
	bool m_upKey{ false };
	bool m_downKey{ false };
};

