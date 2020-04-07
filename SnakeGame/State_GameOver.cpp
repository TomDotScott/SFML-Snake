#include "State_GameOver.h"
#include <fstream>
#include <iostream>
#include "State_Game.h"
#include "State_MainMenu.h"


void State_GameOver::Initialize(sf::RenderWindow& _window, sf::Font& _font, SoundManager* _soundManager) {
	//initialise selected value to play the game
	m_selected = 0;

	m_soundManager = _soundManager;
	
	//load the font to display text
	m_font = _font;

	
	
	//Load the highscore and the previous score to display onscreen
	std::ifstream file("Resources/Scores.txt");
	if (file.is_open()) {
		while (file >> m_lastScoreValue >> m_highScoreValue) {
			m_lastScore.SetString("Score:  " + m_lastScoreValue);
			m_highScore.SetString("Highscore:  " + m_highScoreValue);
		}
	} else {
		assert(false);
	}
	file.close();


	for (auto* text : m_textToRender) {
		text->SetFont(m_font);
	}
	
	std::cout << "Initialized" << std::endl;
}


void State_GameOver::Render(sf::RenderWindow& _window) {
	m_playAgain.SetColour(sf::Color::White);
	m_main.SetColour(sf::Color::White);

	if (m_selected == 0) {
		m_playAgain.SetColour(sf::Color::Red);
	} else if (m_selected == 1) {
		m_main.SetColour(sf::Color::Red);
	}

	for(auto text : m_textToRender)
	{
		_window.draw(text->m_text);
	}
}


void State_GameOver::Update() {
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
			//quit to titles...
			core_state.SetState(new State_MainMenu());
			current_state = eCurrentState::e_MainMenu;
			std::cout << "GOING BACK TO THE MAIN MENU" << std::endl;
			break;
		default:
			break;
		}
	}
}


void State_GameOver::Destroy() {
	
}