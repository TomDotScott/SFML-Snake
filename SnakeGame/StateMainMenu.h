#pragma once
#include "StateManager.h"
class StateMainMenu final : public BaseState {
public:
	StateMainMenu(SoundManager& _soundManager) : BaseState(_soundManager){};
	void Initialize(sf::RenderWindow& _window, sf::Font& _font) override;
	void Update(sf::RenderWindow& _window) override;
	void Render(sf::RenderWindow& _window) override;
	void Destroy() override;
private:
	UIText m_title{ "Snake!", sf::Color::White,
		{static_cast<float>(constants::k_screenWidth) / 2.f, static_cast<float>(constants::k_screenHeight) / 5.f},
		m_font, 128 };

	UIText m_playSinglePlayer{ "1 Player", sf::Color::White,
		{static_cast<float>(constants::k_screenWidth) / 2, 450},
		m_font, constants::k_uiTextElement };

	UIText m_playTwoPlayer{ "2 Player", sf::Color::White,
		{m_playSinglePlayer.m_position.x, m_playSinglePlayer.m_position.y + 100},
		m_font, constants::k_uiTextElement };

	UIText m_quit{ "Quit", sf::Color::White,
	{m_playSinglePlayer.m_position.x, m_playSinglePlayer.m_position.y + 200},
		m_font, constants::k_uiTextElement };

	std::vector<UIText*> m_textToRender{
		&m_title, &m_playSinglePlayer, &m_playTwoPlayer, &m_quit
	};

	MenuBackground m_menuBackground;
	
	//deal with user selections
	int m_selected{ 0 };
};

