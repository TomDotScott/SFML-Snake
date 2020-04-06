#pragma once
#include "StateManager.h"

class State_GameOver final : public BaseState {
public:
	void Initialize(sf::RenderWindow& _window, sf::Font& _font, SoundManager& _soundManager) override;
	void Update() override;
	void Render(sf::RenderWindow& _window) override;
	void Destroy() override;
	~State_GameOver();
private:
	sf::Text* m_title{ nullptr };
	sf::Text* m_playAgain{ nullptr };
	sf::Text* m_quit{ nullptr };
	sf::Text* m_lastScore{ nullptr };
	sf::Text* m_highScore{ nullptr };
	
	sf::Font m_font;

	int m_selected{ 0 };

	SoundManager m_soundManager;
	
	std::string m_lastScoreValue;
	std::string m_highScoreValue;
};

