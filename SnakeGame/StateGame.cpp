#include <fstream>
#include "AISnake.h"
#include "PlayerSnake.h"
#include "StateGame.h"
#include "StateGameOver.h"

StateGame::StateGame(SoundManager& _soundManager, const bool& _twoPlayer) : BaseState(_soundManager) {
	m_twoPlayer = _twoPlayer ? true : false;
}

StateGame::~StateGame() {
	if (!m_foodArray.empty()) {
		for (auto food : m_foodArray) {
			if (food) {
				delete food;
				food = nullptr;
			}
		}
	}
	if (!m_snakes.empty()) {
		for (auto snake : m_snakes) {
			if (snake) {
				delete snake;
				snake = nullptr;
			}
		}
	}
}

//BASESTATE METHODS
void StateGame::OnCreate(sf::RenderWindow& _window, sf::Font& _font) {
	m_clock.restart();
	m_font = _font;
	m_pausedText.SetFont(m_font);
	m_gobbleModeText.SetFont(m_font);

	//populate the food array
	for (int i = 0; i < constants::k_foodAmount; ++i) {
		//make sure there's only 1 gobble mode on screen
		Food* newFood = new Food();
		if (newFood->GetType() == EFoodType::eGobble && !m_gobbleOnScreen) {
			m_gobbleOnScreen = true;
		}
		if (m_gobbleOnScreen) {
			do {
				newFood->Randomise();
			} while (newFood->GetType() != EFoodType::eGobble);
		}
		m_foodArray[i] = newFood;

	}
	
	if (m_twoPlayer) {
		//move the player1 text to the centre and the player 2 text to the far right
		m_playerScore.m_text.setPosition(static_cast<float>(constants::k_screenWidth) / 2 - constants::k_gameGridCellSize, constants::k_gameGridCellSize);
		m_player2Score.m_text.setPosition(static_cast<float>(constants::k_screenWidth) - 5 * constants::k_gameGridCellSize, constants::k_gameGridCellSize);

		//Set up 2 player snakes
		auto* player1Snake = new PlayerSnake(EPlayer::ePlayerOne, m_soundManager, m_foodArray);
		m_snakes.push_back(player1Snake);

		auto* player2Snake = new PlayerSnake(EPlayer::ePlayerTwo, m_soundManager, m_foodArray);
		m_snakes.push_back(player2Snake);

		for (auto* text : m_UItoRenderTwoPlayer) {
			text->SetFont(m_font);
		}
	} else {
		auto* playerSnake = new PlayerSnake(EPlayer::ePlayerOne, m_soundManager, m_foodArray);
		m_snakes.push_back(playerSnake);

		//populate the snake Vector
		for (int i = 0; i < constants::k_AISnakeAmount; ++i) {
			m_snakes.push_back(new AISnake(m_soundManager, m_foodArray));
		}

		for (auto* text : m_UItoRenderSinglePlayer) {
			text->SetFont(m_font);
		}
	}

	SetHighScoreText();

	//Initialise background texture
	m_grassTexture.loadFromFile("Resources/Graphics/Game_Background.png");
	m_grassSprite.setTexture(m_grassTexture);
	m_grassSprite.setPosition(0, 120);

	//Initialise Clock Texture
	m_clockTexture.loadFromFile("Resources/Graphics/Game_Clock.png");
	m_clockSprite.setTexture(m_clockTexture);
	m_clockSprite.setPosition(10, m_clockText.m_position.y - 5);

	//make the snakes know where the food and other snakes are on the screen for collisions
	for (auto* snake : m_snakes) {
		snake->SetOtherSnakes(m_snakes);
	}
	m_soundManager.PlayMusic("music_game");
}

void StateGame::Update(sf::RenderWindow& _window) {
	HandleInput();
	//only play the game if it is paused
	if (!m_paused) {
		m_gobble = false;


		m_gameTimer += m_clock.restart().asSeconds();

		for (auto* snake : m_snakes) {
			if (snake->GetIsGobbleMode()) {
				//Make sure gobble doesn't continue if the snake is dead
				m_gobble = snake->IsDead() ? false : true;
			}
			snake->Update();
		}
		CheckCollisions();


		EndGobbleMode();

		UpdateScores();

		m_clockText.SetString(std::to_string(90 - static_cast<int>(m_gameTimer)));

		CheckWinningConditions(_window);
	}
}

void StateGame::Render(sf::RenderWindow& _window) {

	//Draw the background
	_window.draw(m_grassSprite);
	//Draw the food
	for (auto* food : m_foodArray) {
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

//GAME METHODS
void StateGame::CheckCollisions() {
	for (auto* snake : m_snakes) {
		//only check collisions if the snake is alive
		if (!snake->IsDead()) {
			//Check against Walls
			if (snake->GetHeadPosition().x <= 0 ||
				snake->GetHeadPosition().x > m_rightWall.m_position.x ||
				snake->GetHeadPosition().y <= 100 + constants::k_gameGridCellSize ||
				snake->GetHeadPosition().y > m_bottomWall.m_position.y) {
				snake->Collision(ECollisionType::eWall);
				return;
			}
			if(snake->CheckCollisions() == ECollisionType::eFood) {
				RandomiseFood(snake->GetLastFood());
			}
		}
	}
}


void StateGame::EndGobbleMode() {
	//GOBBLE MODE. After a random amount of time, stop Gobble Mode
	if (rand() % 100 == 0 && m_gobble) {
		for (auto* snake : m_snakes) {
			if (snake->GetIsGobbleMode()) {
				snake->SetIsGobbleMode(false);
				m_soundManager.PlaySFX("sfx_gobble_off");
			}
		}
	}
}

void StateGame::CheckWinningConditions(sf::RenderWindow& _window) {
	if (!StillAlive() || m_gameTimer >= 90) {
		GameOver(_window);
	}
}

void StateGame::RandomiseFood(Food* _foodToRandomise) {
	//Check that food doesn't spawn on top of each other
	bool isOverlapping{ true };
	while (isOverlapping) {
		_foodToRandomise->Randomise();
		//Check the randomised position
		for (auto food : m_foodArray) {
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
		PauseGame();
	}
	if (!m_paused) {
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
}

void StateGame::SetHighScoreText() {
	std::string score;

	//READ THE FILE
	std::ifstream infile("Resources/Scores.txt");
	infile >> score >> score >> m_highScore;
	infile.close();

	m_highScoreText.SetString("Hi-Score:" + m_highScore);
}

void StateGame::SaveScores() {
	std::string player1Score, player2Score, highScore;

	//READ THE FILE
	std::ifstream infile("Resources/Scores.txt");
	infile >> player1Score >> player2Score >> highScore;
	infile.close();

	//Check if the player has set a new highscore
	player1Score = std::to_string(m_snakes[0]->GetScore());
	if ((highScore.empty()) || std::stoi(highScore) < std::stoi(player1Score)) {
		highScore = player1Score;
	}

	std::ofstream outfile("Resources/Scores.txt");
	outfile << player1Score << std::endl;
	outfile << player2Score << std::endl;
	outfile << highScore << std::endl;
	outfile.close();
}

void StateGame::GameOver(sf::RenderWindow& _window) {
	SaveScores();
	STATE_MANAGER.ChangeState(EState::eGameOver,_window, m_twoPlayer, !m_snakes[0]->IsDead());
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

void StateGame::PauseGame() {
	m_clock.restart();
	m_soundManager.PlaySFX("sfx_menu_pause");
	m_paused = !m_paused;
	m_escapeKey = false;
}
