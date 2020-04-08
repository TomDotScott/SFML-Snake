#include "State_Game.h"
#include <fstream>
#include <cmath>
#include "AISnake.h"
#include "PlayerSnake.h"
#include "State_GameOver.h"

/*TODO
 *ADD 2 PLAYER FUNCTIONALITY
 *FIX PATH-FINDING
	*AI SNAKES STOP WRAPPING THEMSELVES UP
	*SOME SORT OF FORWARD-THINKING ALGORITHM
	*A* OR GREEDY BFS SEARCH
 */


 //BASESTATE METHODS
void State_Game::Initialize(sf::RenderWindow& _window, sf::Font& _font, SoundManager* _soundManager) {
	m_clock.restart();

	m_font = _font;

	//Load the fonts into the UI Text elements
	m_gobbleModeText.m_font = m_font;
	m_pausedText.m_font = m_font;
	m_clockText.m_font = m_font;

	if (!m_twoPlayer) {
		m_playerScore.m_font = m_font;
		m_CPU1Score.m_font = m_font;
		m_CPU2Score.m_font = m_font;
	} else {
		//Set up Player and Player2 fonts
	}

	m_highScoreText.m_font = m_font;

	SetHighScoreText();

	m_soundManager = _soundManager;

	m_soundManager->PlayMusic("music_game");

	if (!m_twoPlayer) {
		auto* playerSnake = new PlayerSnake();
		m_snakes.push_back(playerSnake);

		//populate the snake Vector
		for (int i = 0; i < Constants::k_AISnakeAmount; ++i) {
			m_snakes.push_back(new AISnake());
		}
	} else {
		//Set up 2 player snakes
	}

	//Initialise background texture
	m_grassTexture.loadFromFile("Resources/Graphics/Game_Background.png");
	m_grassSprite.setTexture(m_grassTexture);

	//Initialise Clock Texture
	m_clockTexture.loadFromFile("Resources/Graphics/Game_Clock.png");
	m_clockSprite.setTexture(m_clockTexture);
	m_clockSprite.setPosition(Constants::k_screenWidth - 175, m_clockText.m_position.y + 5);

	//populate the food array
	for (int i = 0; i < Constants::k_foodAmount; ++i) {
		Food* food = new Food();
		m_foodArray[i] = food;
	}

	if (!m_twoPlayer) {
		//make the snakes know where the food and other snakes are on the screen
		for (auto* snake : m_snakes) {
			for (auto* food : m_foodArray) {
				snake->SetFood(food);
				snake->SetSoundManager(m_soundManager);
			}

			for (auto* otherSnake : m_snakes) {
				if (snake != otherSnake) {
					snake->SetOtherSnake(otherSnake);
				}
			}
		}
	}
}

int State_Game::GetTimeRemaining() const {
	return 90 - static_cast<int>(floor(m_clock.getElapsedTime().asSeconds()));
}

void State_Game::Update() {
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

		m_clockText.SetString(std::to_string(GetTimeRemaining()));

		CheckWinningConditions();
	}
}

void State_Game::Render(sf::RenderWindow& _window) {

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

	//Draw the UI
	_window.draw(m_playerScore.m_text);
	_window.draw(m_CPU1Score.m_text);
	_window.draw(m_CPU2Score.m_text);
	_window.draw(m_highScoreText.m_text);

	if (m_gobble) {
		_window.draw(m_gobbleModeText.m_text);
	}

	if (m_paused) {
		_window.draw(m_pausedText.m_text);
	}


	_window.draw(m_clockSprite);
	_window.draw(m_clockText.m_text);
}

void State_Game::Destroy() {
	for (auto* food : m_foodArray) {
		food = nullptr;
	}

	for (auto* snake : m_snakes) {
		snake = nullptr;
	}
}

State_Game::State_Game(bool _twoPlayer) {
	m_twoPlayer = _twoPlayer ? true : false;
}

State_Game::~State_Game() {
	for (Food* food : m_foodArray) {
		delete food;
	}

	for (auto* snake : m_snakes) {
		delete snake;
	}
}


//GAME METHODS
void State_Game::CheckCollisions() {
	for (auto* currentSnake : m_snakes) {
		//only check collisions if the snake is alive
		if (!currentSnake->IsDead()) {
			//Check against Walls
			if (currentSnake->GetHeadPosition().x <= 0 ||
				currentSnake->GetHeadPosition().x > Constants::k_gameWidth + Constants::k_gameGridCellSize ||
				currentSnake->GetHeadPosition().y <= 0 ||
				currentSnake->GetHeadPosition().y > Constants::k_gameHeight + Constants::k_gameGridCellSize) {
				currentSnake->Collision(ECollisionType::e_wall);
				return;
			}
		}
	}
}


void State_Game::EndGobbleMode() {
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

void State_Game::CheckWinningConditions() {
	if (!m_twoPlayer) {
		//If the player has died, end the game
		auto* playerSnake = dynamic_cast<PlayerSnake*>(m_snakes[0]);
		if ((m_snakes[0]->IsDead() && playerSnake) || !CheckIfStillAlive() || GetTimeRemaining() == 0) {
			GameOver();
		}
	} else {
		if (!CheckIfStillAlive() || GetTimeRemaining() == 0) {
			GameOver();
		}
	}
}

void State_Game::RandomiseFood(Food* _foodToRandomise) {
	//Check that food doesn't spawn on top of each other
	bool isOverlapping = true;
	while (isOverlapping) {
		_foodToRandomise->Randomise();
		//Check the randomised position
		for (const Food* food : m_foodArray) {
			//make sure the food isn't getting compared to itself!
			if (*food != *_foodToRandomise) {
				if (_foodToRandomise->GetPosition() != food->GetPosition()) {
					isOverlapping = false;
					break;
				} else {
					_foodToRandomise->Randomise();
				}
			} else {
				_foodToRandomise->Randomise();
			}
		}
	}
}

void State_Game::UpdateScores() {
	if (!m_twoPlayer) {
		m_playerScore.SetString("Player:" + std::to_string(m_snakes[0]->GetScore()));
		m_CPU1Score.SetString("CPU1:" + std::to_string(m_snakes[1]->GetScore()));
		m_CPU2Score.SetString("CPU2:" + std::to_string(m_snakes[2]->GetScore()));
	} else {
		//Update Player 1 and 2 Scores
	}
}

void State_Game::HandleInput() {
	//pause and un-pause the game if escape is pressed
	if (m_escapeKey) {
		m_soundManager->PlaySFX("sfx_menu_pause");
		m_paused = !m_paused;
		m_escapeKey = false;
	}
	if (!m_twoPlayer) {
		//There is only ever one player snake
		//If it can be cast to the PlayerSnake type then we have the player
		auto* playerSnake = dynamic_cast<PlayerSnake*>(m_snakes[0]);
		if (playerSnake) {
			if ((m_upKey && playerSnake->GetDirection() != EDirection::e_down) || (m_wKey && playerSnake->GetDirection() != EDirection::e_down)) {
				playerSnake->SetDirection(EDirection::e_up);
				m_upKey = false;
				m_wKey = false;
			}
			if ((m_downKey && playerSnake->GetDirection() != EDirection::e_up) || (m_sKey && playerSnake->GetDirection() != EDirection::e_up)) {
				playerSnake->SetDirection(EDirection::e_down);
				m_downKey = false;
				m_sKey = false;
			}
			if ((m_leftKey && playerSnake->GetDirection() != EDirection::e_right) || (m_aKey && playerSnake->GetDirection() != EDirection::e_right)) {
				playerSnake->SetDirection(EDirection::e_left);
				m_leftKey = false;
				m_aKey = false;
			}
			if ((m_rightKey && playerSnake->GetDirection() != EDirection::e_left) || (m_dKey && playerSnake->GetDirection() != EDirection::e_left)) {
				playerSnake->SetDirection(EDirection::e_right);
				m_rightKey = false;
			}
			return;
		}
	} else {
		//WASD for Player 1, Arrows for Player 2
	}
}

void State_Game::SetHighScoreText() {
	std::string score;

	//READ THE FILE
	std::ifstream infile("Resources/Scores.txt");
	if (!infile.is_open()) {
		assert(false);
	}
	infile >> score >> m_highScore;
	infile.close();

	m_highScoreText.SetString("Hi:" + m_highScore);
}

void State_Game::SaveScores() {
	std::string score;
	std::string highScore;

	//READ THE FILE
	std::ifstream infile("Resources/Scores.txt");
	if (!infile.is_open()) {
		assert(false);
	}
	infile >> score >> highScore;
	infile.close();

	//Check if the player has set a new highscore
	score = std::to_string(m_snakes[0]->GetScore());
	if ((highScore.empty()) || std::stoi(highScore) < std::stoi(score)) {
		highScore = score;
	}

	std::ofstream outfile("Resources/Scores.txt");
	if (!outfile.is_open()) {
		assert(false);
	}
	outfile << score << std::endl;
	outfile << highScore << std::endl;
	outfile.close();
}

void State_Game::GameOver() {
	SaveScores();
	current_state = eCurrentState::e_GameOver;
	core_state.SetState(new State_GameOver());
}

bool State_Game::CheckIfStillAlive() {
	int counter{ 0 };
	for (auto snake : m_snakes) {
		if (!snake->IsDead()) {
			++counter;
		}
	}
	if (counter > 1) {
		return true;
	} else {
		return false;
	}
}
