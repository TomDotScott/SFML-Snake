#include "StateControls.h"
#include "StateMainMenu.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "StateGame.h"

void StateControls::Initialize(sf::RenderWindow& _window, sf::Font& _font, SoundManager* _soundManager) {
	CURRENT_STATE = ECurrentState::eControlsMenu;
	//initialise selected value to play the game
	m_selected = 0;

	m_soundManager = _soundManager;

	m_gobbleTexture.loadFromFile("Resources/Graphics/Food_Gobble.png");
	m_standardTexture.loadFromFile("Resources/Graphics/Food_Standard.png");
	m_specialTexture.loadFromFile("Resources/Graphics/Food_Special.png");

	//load the font and display text
	m_font = _font;

	for (auto* textElement : m_textToRender) {
		textElement->SetFont(m_font);
	}

	std::cout << "Initialised" << std::endl;
}


void StateControls::Render(sf::RenderWindow& _window) {
	m_menuBackground.Render(_window);

	m_play.SetColour(sf::Color::White);
	m_main.SetColour(sf::Color::White);

	if (m_selected == 0) {
		m_play.SetColour(sf::Color(245, 77, 56));
	} else if (m_selected == 1) {
		m_main.SetColour(sf::Color(245, 77, 56));
	}

	//draw the text on screen
	for (auto* textElement : m_textToRender) {
		_window.draw(textElement->m_text);
	}

	const GameIcon standard{ m_standardTexture, {68, 175} };
	standard.Render(_window);

	const GameIcon special{ m_specialTexture, {68, 208} };
	special.Render(_window);

	GameIcon gobble{ m_gobbleTexture, {68, 240} };
	gobble.Render(_window);

	gobble.SetPosition({ 68, 270 });
	gobble.Render(_window);
}


void StateControls::Update() {
	if (m_upKey && !m_downKey) {
		m_selected -= 1;
		m_soundManager->PlaySFX("sfx_menu_move");
		m_upKey = false;
	}

	if (m_downKey && !m_upKey) {
		m_selected += 1;
		m_soundManager->PlaySFX("sfx_menu_move");
		m_downKey = false;
	}

	//allow for cycling through options...
	if (m_selected > 1) {
		m_selected = 0;
	}

	if (m_selected < 0) {
		m_selected = 1;
	}

	//Select the option using SPACE
	if (m_spaceKey && !m_upKey && !m_downKey) {
		m_soundManager->PlaySFX("sfx_menu_select");
		m_spaceKey = false;
		switch (m_selected) {
		case 0:
			//play the game...
			CORE_STATE.SetState(new StateGame(false));
			CURRENT_STATE = ECurrentState::eGame;
			std::cout << "PLAYING SNAKE" << std::endl;
			break;
		case 1:
			//Go to the controls state...
			CORE_STATE.SetState(new StateMainMenu());
			std::cout << "GOING TO THE MAIN MENU" << std::endl;
			break;
		default:
			break;
		}
	}
}

void StateControls::Destroy() {
	std::cout << "Destroyed" << std::endl;
}