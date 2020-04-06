#pragma once
#include "StateManager.h"
class State_MainMenu final : public BaseState {
public:
	void Initialize(sf::RenderWindow& _window, sf::Font& _font, SoundManager* _soundManager) override;
	void Update() override;
	void Render(sf::RenderWindow& _window) override;
	void Destroy() override;
	~State_MainMenu();
private:
	SoundManager* m_soundManager{ nullptr };
	sf::Font m_font;
	sf::Text* m_title{ nullptr };
	sf::Text* m_play{ nullptr };
	sf::Text* m_quit{ nullptr };

	//deal with user selections
	int m_selected{ 0 };
};

