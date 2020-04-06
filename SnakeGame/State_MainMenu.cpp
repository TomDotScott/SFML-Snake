#include "State_MainMenu.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "State_Game.h"

void State_MainMenu::Initialize(sf::RenderWindow& _window, sf::Font& _font, SoundManager* _soundManager) {
	//initialise selected value to play the game
	m_selected = 0;

	//load the soundManager
	m_soundManager = _soundManager;
	
	//load the font and display text
	m_font = _font;
	
	/*MAIN TITLE TEXT*/
	m_title = new sf::Text("Snake!", m_font, 128U);
	//centre the text
	m_title->setOrigin(m_title->getGlobalBounds().width / 2, m_title->getGlobalBounds().height / 2);
	//set the position
	m_title->setPosition(static_cast<float>(_window.getSize().x) / 2, static_cast<float>(_window.getSize().y) / 5);

	/*PLAY TEXT*/
	m_play = new sf::Text("Play!", m_font, 32U);
	//centre the text
	m_play->setOrigin(m_play->getGlobalBounds().width / 2, m_play->getGlobalBounds().height / 2);
	//set the position
	m_play->setPosition(static_cast<float>(_window.getSize().x) / 2, static_cast<float>(_window.getSize().y) / 2);


	/*QUIT TEXT*/
	m_quit = new sf::Text("Quit!", m_font, 32U);
	//centre the text
	m_quit->setOrigin(m_quit->getGlobalBounds().width / 2, m_quit->getGlobalBounds().height / 2);
	//set the position
	m_quit->setPosition(static_cast<float>(_window.getSize().x) / 2, static_cast<float>(_window.getSize().y) / 1.5f);

	std::cout << "Initialised" << std::endl;
}


void State_MainMenu::Render(sf::RenderWindow& _window) {
	m_play->setFillColor(sf::Color::White);
	m_quit->setFillColor(sf::Color::White);

	if (m_selected == 0) {
		m_play->setFillColor(sf::Color::Red);
	} else if (m_selected == 1) {
		m_quit->setFillColor(sf::Color::Red);
	}

	//draw the text on screen
	_window.draw(*m_title);
	_window.draw(*m_play);
	_window.draw(*m_quit);
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
			//quit the game...
			quit_game = true;
		default:
			break;
		}
	}
}

State_MainMenu::~State_MainMenu() {
	delete m_title;
	delete m_play;
	delete m_quit;
}

void State_MainMenu::Destroy() {
	m_title = nullptr;
	m_play = nullptr;
	m_quit = nullptr;
	std::cout << "Destroyed" << std::endl;
}