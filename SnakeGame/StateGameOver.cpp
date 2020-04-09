#include "StateGameOver.h"
#include <fstream>
#include <iostream>
#include "StateGame.h"
#include "StateMainMenu.h"


StateGameOver::StateGameOver(const bool& _isTwoPlayer, const bool& _playerWon) : m_twoPlayer(_isTwoPlayer), m_playerWon(_playerWon){}

void StateGameOver::Initialize(sf::RenderWindow& _window, sf::Font& _font, SoundManager* _soundManager) {
	CURRENT_STATE = ECurrentState::eGameOver;

	//initialise selected value to play the game
	m_selected = 0;

	m_soundManager = _soundManager;

	//load the font to display text
	m_font = _font;

	//Load the highscore and the previous score to display onscreen
	std::ifstream file("Resources/Scores.txt");
	if (file.is_open()) {
		while (file >> m_player1ScoreValue >> m_player2ScoreValue >> m_highScoreValue) {
			m_player1Score.SetString((m_twoPlayer ? "P1:  " : "Score:  ") + m_player1ScoreValue);
			m_player2Score.SetString("P2: " + m_player2ScoreValue);
			m_highScore.SetString("Highscore:  " + m_highScoreValue);
		}
	} else {
		assert(false);
	}
	file.close();

	if (m_twoPlayer) {
		SetWinnerText();
		m_player1Score.SetPosition({ static_cast<float>(constants::k_screenWidth) / 2.f, static_cast<float>(constants::k_screenHeight) / 2.5f });
		m_player1Score.SetColour(sf::Color::Blue);
		for (auto uiText : m_textToRenderTwoPlayer) {
			uiText->SetFont(m_font);
		}
	} else {
		m_gameOverText.SetString(m_playerWon ? "You Won!" : "Game Over");
		for (auto* text : m_textToRenderSinglePlayer) {
			text->SetFont(m_font);
		}
	}

	std::cout << "Initialized" << std::endl;
}


void StateGameOver::Render(sf::RenderWindow& _window) {
	m_menuBackground.Render(_window);

	m_playAgain.SetColour(sf::Color::White);
	m_main.SetColour(sf::Color::White);

	if (m_selected == 0) {
		m_playAgain.SetColour(sf::Color(245, 77, 56));
	} else if (m_selected == 1) {
		m_main.SetColour(sf::Color(245, 77, 56));
	}

	if (m_twoPlayer) {
		for (auto uiText : m_textToRenderTwoPlayer) {
			_window.draw(uiText->m_text);
		}
	} else {
		for (auto uiText : m_textToRenderSinglePlayer) {
			_window.draw(uiText->m_text);
		}
	}
}


void StateGameOver::Update() {
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
			if (m_twoPlayer) {
				CORE_STATE.SetState(new StateGame(true));
			} else {
				CORE_STATE.SetState(new StateGame(false));
			}
			std::cout << "PLAYING SNAKE" << std::endl;
			break;
		case 1:
			//quit to titles...
			CORE_STATE.SetState(new StateMainMenu());
			std::cout << "GOING BACK TO THE MAIN MENU" << std::endl;
			break;
		default:
			break;
		}
	}
}


void StateGameOver::Destroy() {}

void StateGameOver::SetWinnerText() {
	if (std::stoi(m_player1ScoreValue) == std::stoi(m_player2ScoreValue)) {
		m_winnerText.SetString("Draw!");
	} else {
		if (std::stoi(m_player1ScoreValue) < std::stoi(m_player2ScoreValue)) {
			m_winnerText.SetString("P2 Wins!");
			m_winnerText.SetColour(m_player2Score.m_colour);
		} else {
			m_winnerText.SetString("P1 Wins!");
			m_winnerText.SetColour(m_player1Score.m_colour);
		}
	}
}
