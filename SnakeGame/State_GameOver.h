#pragma once
#include "StateManager.h"

class State_GameOver final : public BaseState {
public:
	void Initialize(sf::RenderWindow* _window, sf::Font* _font) override;
	void Update(sf::RenderWindow* _window) override;
	void Render(sf::RenderWindow* _window) override;
	void Destroy(sf::RenderWindow* _window) override;
	~State_GameOver();
private:
	sf::Text* m_title{ nullptr };
	sf::Text* m_playAgain{ nullptr };
	sf::Text* m_quit{ nullptr };
	sf::Text* m_lastScore{ nullptr };
	sf::Text* m_highScore{ nullptr };
	sf::Font* m_font = { nullptr };

	int m_selected{ 0 };

	std::string m_lastScoreValue;
	std::string m_highScoreValue;


	bool m_upKey{ false };
	bool m_downKey{ false };
};

