#include "State_Controls.h"
#include "State_MainMenu.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "State_Game.h"

void State_Controls::Initialize(sf::RenderWindow& _window, sf::Font& _font, SoundManager* _soundManager) {
	//initialise selected value to play the game
	m_selected = 0;

	m_soundManager = _soundManager;
	
	m_gobbleTexture.loadFromFile("Resources/Graphics/Food_Gobble.png");
	m_standardTexture.loadFromFile("Resources/Graphics/Food_Standard.png");
	m_specialTexture.loadFromFile("Resources/Graphics/Food_Special.png");

	//load the font and display text
	m_font = _font;

	for(auto* textElement : m_textToRender)
	{
		textElement->SetFont(m_font);
	}

	std::cout << "Initialised" << std::endl;
}


void State_Controls::Render(sf::RenderWindow& _window) {
	m_play.SetColour(sf::Color::White);
	m_main.SetColour(sf::Color::White);

	if (m_selected == 0) {
		m_play.SetColour(sf::Color::Red);
	} else if (m_selected == 1) {
		m_main.SetColour(sf::Color::Red);
	} 

	//draw the text on screen
	for (auto* textElement : m_textToRender) {
		_window.draw(textElement->m_text);
	}

	m_gameIcon.setPosition(68, 135);
	m_gameIcon.setTexture(m_standardTexture);
	_window.draw(m_gameIcon);

	m_gameIcon.setPosition(68, 170);
	m_gameIcon.setTexture(m_specialTexture);
	_window.draw(m_gameIcon);

	m_gameIcon.setPosition(68, 205);
	m_gameIcon.setTexture(m_gobbleTexture);
	_window.draw(m_gameIcon);

	m_gameIcon.setPosition(68, 235);
	m_gameIcon.setTexture(m_gobbleTexture);
	_window.draw(m_gameIcon);
}


void State_Controls::Update() {
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
			core_state.SetState(new State_Game());
			current_state = eCurrentState::e_Game;
			std::cout << "PLAYING SNAKE" << std::endl;
			break;
		case 1:
			//Go to the controls state...
			core_state.SetState(new State_MainMenu());
			std::cout << "GOING TO THE MAIN MENU" << std::endl;
			break;
		default:
			break;
		}
	}
}

void State_Controls::Destroy() {
	std::cout << "Destroyed" << std::endl;
}