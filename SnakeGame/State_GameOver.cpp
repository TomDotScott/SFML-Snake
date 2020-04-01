#include "State_GameOver.h"
#include <fstream>
#include <iostream>
#include "State_Game.h"
#include "State_MainMenu.h"


void State_GameOver::Initialize(sf::RenderWindow* _window, sf::Font* _font) {
	//initialise selected value to play the game
	m_selected = 0;

	//load the font to display text
	m_font = _font;

	//Load the highscore and the previous score to display onscreen
	std::string scores[2];
	std::ifstream file("Resources/Scores.txt");
	if (file.is_open()) {
		while (file >> m_lastScoreValue >> m_highScoreValue) {
			std::string lastScore = "Score: " + m_lastScoreValue;
			m_lastScore = new sf::Text(lastScore, *m_font, 32U);

			std::string highScore = "Highscore: " + m_highScoreValue;
			m_highScore = new sf::Text(highScore, *m_font, 32U);
		}
	} else {
		assert(false);
	}
	file.close();

	/*MAIN TITLE TEXT*/
	m_title = new sf::Text("Game Over", *m_font, 80U);
	//centre the text
	m_title->setOrigin(m_title->getGlobalBounds().width / 2, m_title->getGlobalBounds().height / 2);
	//set the position
	m_title->setPosition(static_cast<float>(_window->getSize().x) / 2.f, static_cast<float>(_window->getSize().y) / 5.f);

	/*THE HIGHSCORE*/
	m_highScore->setOrigin(m_highScore->getGlobalBounds().width / 2, m_highScore->getGlobalBounds().height / 2);
	m_highScore->setPosition(static_cast<float>(_window->getSize().x / 2.f), static_cast<float>(_window->getSize().y / 2.5f));

	/*THE SCORE*/
	m_lastScore->setOrigin(m_lastScore->getGlobalBounds().width / 2, m_lastScore->getGlobalBounds().height / 2);
	m_lastScore->setPosition(static_cast<float>(_window->getSize().x / 2.f), static_cast<float>(_window->getSize().y / 2.f));

	/*PLAY AGAIN TEXT*/
	m_playAgain = new sf::Text("Play Again", *m_font, 32U);
	//centre the text
	m_playAgain->setOrigin(m_playAgain->getGlobalBounds().width / 2, m_playAgain->getGlobalBounds().height / 2);
	//set the position
	m_playAgain->setPosition(static_cast<float>(_window->getSize().x) / 2, static_cast<float>(_window->getSize().y) / 1.5f);


	/*QUIT TEXT*/
	m_quit = new sf::Text("Quit To Title", *m_font, 32U);
	//centre the text
	m_quit->setOrigin(m_quit->getGlobalBounds().width / 2, m_quit->getGlobalBounds().height / 2);
	//set the position
	m_quit->setPosition(static_cast<float>(_window->getSize().x) / 2, static_cast<float>(_window->getSize().y) / 1.25f);

	std::cout << "Initialized" << std::endl;
}


void State_GameOver::Render(sf::RenderWindow* _window) {
	//wow i am actually stupid wtf
	m_playAgain->setFillColor(sf::Color::White);
	m_quit->setFillColor(sf::Color::White);

	if (m_selected == 0) {
		m_playAgain->setFillColor(sf::Color::Red);
	} else if (m_selected == 1) {
		m_quit->setFillColor(sf::Color::Red);
	}

	//draw the text on screen
	_window->draw(*m_title);
	_window->draw(*m_highScore);
	_window->draw(*m_lastScore);
	_window->draw(*m_playAgain);
	_window->draw(*m_quit);
}


void State_GameOver::Update(sf::RenderWindow* _window) {
	if (!m_upKey && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
		m_selected -= 1;
	}
	if (!m_downKey && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
		m_selected += 1;
	}
	//allow for cycling through options...
	if (m_selected > 1) {
		m_selected = 0;
	}

	if (m_selected < 0) {
		m_selected = 1;
	}

	//Select the option using SPACE
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		switch (m_selected) {
		case 0:
			//play the game...
			core_state.SetState(new State_Game());
			current_state = eCurrentState::e_Game;
			std::cout << "PLAYING SNAKE" << std::endl;
			break;
		case 1:
			//quit to titles...
			current_state = eCurrentState::e_MainMenu;
			core_state.SetState(new State_MainMenu());
		default:
			break;
		}
	}


	//detect whether the up arrow has been pressed or not...
	m_upKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);

	//same for Down Key
	m_downKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
}


void State_GameOver::Destroy(sf::RenderWindow* _window) {
	m_font = nullptr;
	m_title = nullptr;
	m_playAgain = nullptr;
	m_quit = nullptr;
	std::cout << "Destroyed" << std::endl;
}

State_GameOver::~State_GameOver() {
	m_font = nullptr;
	m_title = nullptr;
	m_playAgain = nullptr;
	m_quit = nullptr;
	delete this;
}
