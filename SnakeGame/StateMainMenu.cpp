#include "StateMainMenu.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "StateControls.h"
#include "StateGame.h"

void StateMainMenu::Initialize(sf::RenderWindow& _window, sf::Font& _font, SoundManager* _soundManager) {
	CURRENT_STATE = ECurrentState::eMainMenu;
	
	//initialise selected value to play the game
	m_selected = 0;

	//load the soundManager
	m_soundManager = _soundManager;

	m_soundManager->StopMusic();
	
	//load the font and display text
	m_font = _font;

	for (auto text : m_textToRender) {
		text->SetFont(m_font);
	}

	std::cout << "Initialised" << std::endl;
}


void StateMainMenu::Render(sf::RenderWindow& _window) {
	m_menuBackground.Render(_window);
	
	//THE TEXT
	m_playSinglePlayer.SetColour(sf::Color::White);
	m_playTwoPlayer.SetColour(sf::Color::White);
	m_quit.SetColour(sf::Color::White);

	if (m_selected == 0) {
		m_playSinglePlayer.SetColour(sf::Color(245, 77, 56));
	} else if (m_selected == 1) {
		m_playTwoPlayer.SetColour(sf::Color(245, 77, 56));
	} else {
		m_quit.SetColour(sf::Color(245, 77, 56));
	}

	//draw the text on screen
	for (auto* textElement : m_textToRender) {
		_window.draw(textElement->m_text);
	}
}


void StateMainMenu::Update() {
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
	if (m_selected > 2) {
		m_selected = 0;
	}

	if (m_selected < 0) {
		m_selected = 2;
	}

	//Select the option using SPACE
	if (m_spaceKey && !m_upKey && !m_downKey) {
		m_soundManager->PlaySFX("sfx_menu_select");
		m_spaceKey = false;
		switch (m_selected) {
		case 0:
			//Go to the controls state...
			CORE_STATE.SetState(new StateControls());
			std::cout << "GOING TO THE CONTROLS MENU" << std::endl;
			break;
		case 1:
			CORE_STATE.SetState(new StateGame(true));
			std::cout << "PLAYING 2 PLAYER" << std::endl;
			break;
		case 2:
			QUIT_GAME = true;
			break;
		default:
			break;
		}
	}
}

void StateMainMenu::Destroy() {
	std::cout << "Destroyed" << std::endl;
}