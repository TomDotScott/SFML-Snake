#include "StateGame.h"
#include <fstream>
#include "AISnake.h"
#include "PlayerSnake.h"
#include "StateGameOver.h"
//BASESTATE METHODS
void StateGame::Initialize(sf::RenderWindow& _window, sf::Font& _font, SoundManager* _soundManager) {
	CURRENT_STATE = ECurrentState::eGame;
	m_clock.restart();

	m_font = _font;

	m_pausedText.SetFont(m_font);
	m_gobbleModeText.SetFont(m_font);

	if (m_twoPlayer) {
		//move the player1 text to the centre and the player 2 text to the far right
		m_playerScore.m_text.setPosition(static_cast<float>(constants::k_screenWidth) / 2 - constants::k_gameGridCellSize, constants::k_gameGridCellSize);
		m_player2Score.m_text.setPosition(static_cast<float>(constants::k_screenWidth) - 5 * constants::k_gameGridCellSize, constants::k_gameGridCellSize);

		//Set up 2 player snakes
		auto* player1Snake = new PlayerSnake("Player 1");
		m_snakes.push_back(player1Snake);

		auto* player2Snake = new PlayerSnake("Player 2");
		m_snakes.push_back(player2Snake);

		for (auto* text : m_UItoRenderTwoPlayer) {
			text->SetFont(m_font);
		}
	} else {
		auto* playerSnake = new PlayerSnake("Player 1");
		m_snakes.push_back(playerSnake);

		//populate the snake Vector
		for (int i = 0; i < constants::k_AISnakeAmount; ++i) {
			m_snakes.push_back(new AISnake());
		}

		for (auto* text : m_UItoRenderSinglePlayer) {
			text->SetFont(m_font);
		}
	}

	SetHighScoreText();

	m_soundManager = _soundManager;
	m_soundManager->PlayMusic("music_game");

	//Initialise background texture
	m_grassTexture.loadFromFile("Resources/Graphics/Game_Background.png");
	m_grassSprite.setTexture(m_grassTexture);
	m_grassSprite.setPosition(0, 120);

	//Initialise Clock Texture
	m_clockTexture.loadFromFile("Resources/Graphics/Game_Clock.png");
	m_clockSprite.setTexture(m_clockTexture);
	m_clockSprite.setPosition(10, m_clockText.m_position.y - 5);

	//populate the food array
	for (int i = 0; i < constants::k_foodAmount; ++i) {
		Food* food = new Food();
		m_foodArray[i] = food;
	}

	//make the snakes know where the food and other snakes are on the screen for collisions
	for (auto* snake : m_snakes) {
		for (auto* food : m_foodArray) {
			snake->SetFood(food);
		}

		for (auto* otherSnake : m_snakes) {
			if (snake != otherSnake) {
				snake->SetOtherSnake(otherSnake);
			}
		}
		snake->SetSoundManager(m_soundManager);

	}
}

int StateGame::TimeRemaining() const {
	return 90 - static_cast<int>(m_clock.getElapsedTime().asSeconds());
}

void StateGame::Update() {
	HandleInput();
	//only play the game if it is paused
	if (!m_paused) {
		m_gobble = false;

		CheckCollisions();

		for (auto* snake : m_snakes) {
			if (snake->GetIsGobbleMode()) {
				m_gobble = true;
			}
			snake->Update();
		}

		EndGobbleMode();

		UpdateScores();

		m_clockText.SetString(std::to_string(TimeRemaining()));

		CheckWinningConditions();
	}
}

void StateGame::Render(sf::RenderWindow& _window) {

	//Draw the background
	_window.draw(m_grassSprite);
	//Draw the food
	for (Food* food : m_foodArray) {
		food->Render(_window);
	}
	//Draw the snakes
	for (Snake* snake : m_snakes) {
		snake->Render(_window);
	}
	//Draw the Walls
	_window.draw(m_topWall.m_wall);
	_window.draw(m_bottomWall.m_wall);
	_window.draw(m_leftWall.m_wall);
	_window.draw(m_rightWall.m_wall);

	if (m_twoPlayer) {
		for (auto* uiElement : m_UItoRenderTwoPlayer) {
			_window.draw(uiElement->m_text);
		}
	} else {
		for (auto* uiElement : m_UItoRenderSinglePlayer) {
			_window.draw(uiElement->m_text);
		}
	}
	if (m_gobble) {
		_window.draw(m_gobbleModeText.m_text);
	}
	if (m_paused) {
		_window.draw(m_pausedText.m_text);
	}
	_window.draw(m_clockSprite);
	_window.draw(m_clockText.m_text);
}

void StateGame::Destroy() {
	for (auto* food : m_foodArray) {
		food = nullptr;
	}

	for (auto* snake : m_snakes) {
		snake = nullptr;
	}
}

StateGame::StateGame(const bool& _twoPlayer) {
	m_twoPlayer = _twoPlayer ? true : false;
}

StateGame::~StateGame() {
	for (auto* food : m_foodArray) {
		food = nullptr;
	}

	for (auto* snake : m_snakes) {
		snake = nullptr;
	}
}


//GAME METHODS
void StateGame::CheckCollisions() {
	for (auto* currentSnake : m_snakes) {
		//only check collisions if the snake is alive
		if (!currentSnake->IsDead()) {
			//Check against Walls
			if (currentSnake->GetHeadPosition().x <= 0 ||
				currentSnake->GetHeadPosition().x > m_rightWall.m_position.x ||
				currentSnake->GetHeadPosition().y <= 100 + constants::k_gameGridCellSize ||
				currentSnake->GetHeadPosition().y > m_bottomWall.m_position.y) {
				currentSnake->Collision(ECollisionType::eWall);
				return;
			}
		}
	}
}


void StateGame::EndGobbleMode() {
	//GOBBLE MODE. After a random amount of time, stop Gobble Mode
	if (rand() % 25 == 0 && m_gobble) {
		for (auto* snake : m_snakes) {
			if (snake->GetIsGobbleMode()) {
				snake->SetIsGobbleMode(false);
				m_soundManager->PlaySFX("sfx_gobble_off");
			}
		}
	}
}

void StateGame::CheckWinningConditions() {
	if (!StillAlive() || TimeRemaining() == 0) {
		GameOver();
	}
}

void StateGame::RandomiseFood(Food* _foodToRandomise) {
	//Check that food doesn't spawn on top of each other
	bool isOverlapping{ true };
	while (isOverlapping) {
		_foodToRandomise->Randomise();
		//Check the randomised position
		for (const Food* food : m_foodArray) {
			//make sure the food isn't getting compared to itself!
			if (food != _foodToRandomise) {
				if (_foodToRandomise->GetPosition() == food->GetPosition()) {
					_foodToRandomise->Randomise();
				} else {
					isOverlapping = false;
					break;
				}
			}
		}
	}
}

void StateGame::UpdateScores() {
	if (!m_twoPlayer) {
		m_playerScore.SetString("P1: " + std::to_string(m_snakes[0]->GetScore()));
		m_CPU1Score.SetString("CPU1: " + std::to_string(m_snakes[1]->GetScore()));
		m_CPU2Score.SetString("CPU2: " + std::to_string(m_snakes[2]->GetScore()));
	} else {
		m_playerScore.SetString("P1: " + std::to_string(m_snakes[0]->GetScore()));
		m_player2Score.SetString("P2: " + std::to_string(m_snakes[1]->GetScore()));
	}
}

void StateGame::HandleInput() {
	//pause and un-pause the game if escape is pressed
	if (m_escapeKey) {
		m_soundManager->PlaySFX("sfx_menu_pause");
		m_paused = !m_paused;
		m_escapeKey = false;
	}
	if (!m_twoPlayer) {
		//There is only ever one player snake
		//If it can be cast to the PlayerSnake type then we have the player
		auto* playerSnake{ dynamic_cast<PlayerSnake*>(m_snakes[0]) };
		if (playerSnake) {
			if ((m_upKey && playerSnake->GetDirection() != EDirection::eDown) || (m_wKey && playerSnake->GetDirection() != EDirection::eDown)) {
				playerSnake->SetDirection(EDirection::eUp);
				m_upKey = false;
				m_wKey = false;
			}
			if ((m_downKey && playerSnake->GetDirection() != EDirection::eUp) || (m_sKey && playerSnake->GetDirection() != EDirection::eUp)) {
				playerSnake->SetDirection(EDirection::eDown);
				m_downKey = false;
				m_sKey = false;
			}
			if ((m_leftKey && playerSnake->GetDirection() != EDirection::eRight) || (m_aKey && playerSnake->GetDirection() != EDirection::eRight)) {
				playerSnake->SetDirection(EDirection::eLeft);
				m_leftKey = false;
				m_aKey = false;
			}
			if ((m_rightKey && playerSnake->GetDirection() != EDirection::eLeft) || (m_dKey && playerSnake->GetDirection() != EDirection::eLeft)) {
				playerSnake->SetDirection(EDirection::eRight);
				m_rightKey = false;
				m_dKey = false;
			}
			return;
		}
	} else {
		auto* playerSnake{ dynamic_cast<PlayerSnake*>(m_snakes[0]) };

		if (m_wKey && playerSnake->GetDirection() != EDirection::eDown) {
			playerSnake->SetDirection(EDirection::eUp);
			m_wKey = false;
		}
		if (m_sKey && playerSnake->GetDirection() != EDirection::eUp) {
			playerSnake->SetDirection(EDirection::eDown);
			m_sKey = false;
		}
		if (m_aKey && playerSnake->GetDirection() != EDirection::eRight) {
			playerSnake->SetDirection(EDirection::eLeft);
			m_aKey = false;
		}
		if (m_dKey && playerSnake->GetDirection() != EDirection::eLeft) {
			playerSnake->SetDirection(EDirection::eRight);
			m_dKey = false;
		}

		auto* player2Snake{ dynamic_cast<PlayerSnake*>(m_snakes[1]) };
		//WASD for Player 1, Arrows for Player 2
		if ((m_upKey && player2Snake->GetDirection() != EDirection::eDown)) {
			player2Snake->SetDirection(EDirection::eUp);
			m_upKey = false;
		}
		if ((m_downKey && player2Snake->GetDirection() != EDirection::eUp)) {
			player2Snake->SetDirection(EDirection::eDown);
			m_downKey = false;
		}
		if ((m_leftKey && player2Snake->GetDirection() != EDirection::eRight)) {
			player2Snake->SetDirection(EDirection::eLeft);
			m_leftKey = false;
		}
		if ((m_rightKey && player2Snake->GetDirection() != EDirection::eLeft)) {
			player2Snake->SetDirection(EDirection::eRight);
			m_rightKey = false;
		}
	}
}

void StateGame::SetHighScoreText() {
	std::string score;

	//READ THE FILE
	std::ifstream infile("Resources/Scores.txt");
	if (!infile.is_open()) {
		assert(false);
	}
	infile >> score >> score >> m_highScore;
	infile.close();

	m_highScoreText.SetString("Hi-Score:" + m_highScore);
}

void StateGame::SaveScores() {
	std::string player1Score, player2Score, highScore;

	//READ THE FILE
	std::ifstream infile("Resources/Scores.txt");
	if (!infile.is_open()) {
		assert(false);
	}
	infile >> player1Score >> player2Score >> highScore;
	infile.close();

	//Check if the player has set a new highscore
	player1Score = std::to_string(m_snakes[0]->GetScore());
	if ((highScore.empty()) || std::stoi(highScore) < std::stoi(player1Score)) {
		highScore = player1Score;
	}

	std::ofstream outfile("Resources/Scores.txt");
	if (!outfile.is_open()) {
		assert(false);
	}
	outfile << player1Score << std::endl;
	outfile << player2Score << std::endl;
	outfile << highScore << std::endl;
	outfile.close();
}

void StateGame::GameOver() {
	SaveScores();
	CORE_STATE.SetState(new StateGameOver(m_twoPlayer ? true : false, !m_snakes[0]->IsDead()));
}

bool StateGame::StillAlive() {
	int counter{ 0 };
	for (auto* snake : m_snakes) {
		if (!snake->IsDead()) {
			counter++;
		}
	}
	return counter == 1 ? false : true;
}
