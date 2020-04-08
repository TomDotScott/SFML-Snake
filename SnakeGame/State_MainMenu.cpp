#include "State_MainMenu.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "State_Controls.h"
#include "State_Game.h"

void State_MainMenu::Initialize(sf::RenderWindow& _window, sf::Font& _font, SoundManager* _soundManager) {
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


void State_MainMenu::Render(sf::RenderWindow& _window) {
	m_playSinglePlayer.SetColour(sf::Color::White);
	m_playTwoPlayer.SetColour(sf::Color::White);
	m_quit.SetColour(sf::Color::White);

	if (m_selected == 0) {
		m_playSinglePlayer.SetColour(sf::Color::Red);
	} else if (m_selected == 1) {
		m_playTwoPlayer.SetColour(sf::Color::Red);
	} else {
		m_quit.SetColour(sf::Color::Red);
	}

	//draw the text on screen
	for (auto* textElement : m_textToRender) {
		_window.draw(textElement->m_text);
	}
}


void State_MainMenu::Update() {
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
		m_selected = 1;
	}

	//Select the option using SPACE
	if (m_spaceKey && !m_upKey && !m_downKey) {
		m_soundManager->PlaySFX("sfx_menu_select");
		m_spaceKey = false;
		switch (m_selected) {
		case 0:
			//Go to the controls state...
			core_state.SetState(new State_Controls());
			std::cout << "GOING TO THE CONTROLS MENU" << std::endl;
			break;
		case 1:
			core_state.SetState(new State_Game(true));
			std::cout << "PLAYING 2 PLAYER" << std::endl;
			break;
		case 2:
			quit_game = true;
			break;
		default:
			break;
		}
	}
}

void State_MainMenu::Destroy() {
	std::cout << "Destroyed" << std::endl;
}