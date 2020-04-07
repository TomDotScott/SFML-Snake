#pragma once
#include "StateManager.h"
class State_Controls :
	public BaseState {
public:
	void Initialize(sf::RenderWindow& _window, sf::Font& _font, SoundManager* _soundManager) override;
	void Update() override;
	void Render(sf::RenderWindow& _window) override;
	void Destroy() override;
private:
	sf::Sprite m_gameIcon;
	sf::Texture m_gobbleTexture, m_specialTexture, m_standardTexture;

	UIText m_textLine1to3{ "Use WASD or the Arrow keys to move your snake\nYou have 90 seconds to eat as much food as you can\nEating food gives you more points, but it also makes you grow!", sf::Color::White,
		{static_cast<float>(Constants::k_screenWidth) / 2.f, 100}, m_font, 16 };

	UIText m_textLine4to7{ "Gives you +10 points and grows you by 1 unit\n\nGives you + 30 points and grows you by 3 units\n\nGives you + 50 points and grows you by 5 units\n\nAlso grants you GOBBLE MODE. You earn DOUBLE points", sf::Color::White,
		{static_cast<float>(Constants::k_screenWidth) / 2.f + 25, m_textLine1to3.m_position.y + 100}, m_font, 16 };

	UIText m_textLine8toEnd{ "and you can eat other snakes\nBeware because if a CPU gets GOBBLE MODE, they will go\nout of their way to eat YOU", sf::Color::White,
		{static_cast<float>(Constants::k_screenWidth) / 2.f, m_textLine4to7.m_position.y + 100}, m_font, 16 };
	
	
	UIText m_play{ "Play", sf::Color::White,
		{static_cast<float>(Constants::k_screenWidth) / 2.f, 450 }, m_font, Constants::k_uiTextElement };
	
	UIText m_main{ "Main Menu", sf::Color::White,
		{static_cast<float>(Constants::k_screenWidth) / 2.f, 550 }, m_font, Constants::k_uiTextElement };

	std::vector<UIText*> m_textToRender{
		&m_textLine1to3, &m_textLine4to7, &m_textLine8toEnd, &m_play, &m_main
	};
};

