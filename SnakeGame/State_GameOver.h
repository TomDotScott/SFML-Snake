#pragma once
#include "StateManager.h"

class State_GameOver final : public BaseState {
public:
	void Initialize(sf::RenderWindow& _window, sf::Font& _font, SoundManager* _soundManager) override;
	void Update() override;
	void Render(sf::RenderWindow& _window) override;
	void Destroy() override;
private:
	MenuBackground m_menuBackground;
	
	UIText m_title{ "Game Over", sf::Color::White,
		{static_cast<float>(Constants::k_screenWidth) / 2.f, static_cast<float>(Constants::k_screenHeight) / 5.f},
		m_font, 84 };

	UIText m_highScore{ "HiScore:", sf::Color::White,
		{static_cast<float>(Constants::k_screenWidth) / 2.f, static_cast<float>(Constants::k_screenHeight) / 2.5f},
		m_font, 32 };

	UIText m_lastScore{ "Score:", sf::Color::White,
		{static_cast<float>(Constants::k_screenWidth) / 2.f, static_cast<float>(Constants::k_screenHeight) / 2.f},
		m_font, 32 };

	UIText m_playAgain{ "Play Again", sf::Color::White,
	{static_cast<float>(Constants::k_screenWidth) / 2.f, static_cast<float>(Constants::k_screenHeight) / 1.5f},
		m_font, Constants::k_uiTextElement };
	
	UIText m_main{ "Main Menu", sf::Color::White,
	{static_cast<float>(Constants::k_screenWidth) / 2.f, static_cast<float>(Constants::k_screenHeight) / 1.25f},
		m_font, Constants::k_uiTextElement };

	std::vector<UIText*> m_textToRender{
		&m_title, &m_highScore, &m_lastScore, &m_playAgain, &m_main
	};

	std::string m_lastScoreValue;
	std::string m_highScoreValue;
};

