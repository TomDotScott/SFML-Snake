#include "State_Game.h"
#include <fstream>
#include "AISnake.h"
#include "PlayerSnake.h"
#include "State_GameOver.h"

/*TODO
 *ADD WINNING CONDITIONS FROM THE SPEC
	*GAME LASTS FOR 90 SECONDS
	*GAME ENDS IF ONLY 1 SNAKE LEFT
 *MAKE UI NICER ON THE EYES
 *FIX PATH-FINDING
	*AI SNAKES STOP WRAPPING THEMSELVES UP
	*SOME SORT OF FORWARD-THINKING ALGORITHM
	*A* OR GREEDY BFS SEARCH

 */


 //BASESTATE METHODS
void State_Game::Initialize(sf::RenderWindow& _window, sf::Font& _font, SoundManager* _soundManager) {
	m_font = _font;

	//Load the fonts into the UI Text elements
	m_gobbleModeText.m_font = m_font;
	m_pausedText.m_font = m_font;
	m_clockText.m_font = m_font;
	
	m_soundManager = _soundManager;

	m_soundManager->PlayMusic("music_game");

	auto* playerSnake = new PlayerSnake();
	m_snakes.push_back(playerSnake);

	//populate the food array
	for (int i = 0; i < Constants::k_foodAmount; ++i) {
		Food* food = new Food();
		m_foodArray[i] = food;
	}


	//populate the snake Vector
	for (int i = 0; i < Constants::k_AISnakeAmount; ++i) {
		m_snakes.push_back(new AISnake());
	}


	//populate the score UI
	for (unsigned int i = 0; i < m_snakes.size(); ++i) {
		UIText playerText("Player" + std::to_string(i + 1) + ":", sf::Color::White,
			{ static_cast<float>(Constants::k_screenWidth - 175), static_cast<float>((i * Constants::k_gameGridCellSize) + 10) },
			m_font, 24);
		m_scores.push_back(playerText);
	}

	//Initialise background texture
	m_grassTexture.loadFromFile("Resources/Graphics/Game_Background.png");
	m_grassSprite.setTexture(m_grassTexture);

	//Initialise Clock Texture
	m_clockTexture.loadFromFile("Resources/Graphics/Game_Clock.png");
	m_clockSprite.setTexture(m_clockTexture);
	m_clockSprite.setPosition(Constants::k_screenWidth - 175, 100);

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

		CheckWinningConditions();
	}
}

void State_Game::Render(sf::RenderWindow& _window) {

	//Draw the background
	_window.draw(m_grassSprite);

	//Render the food
	for (Food* food : m_foodArray) {
		food->Render(_window);
	}

	//Render the snakes
	for (Snake* snake : m_snakes) {
		snake->Render(_window);
	}

	//Draw the Score UI
	
	for (auto& score : m_scores)
	{
		_window.draw(score.m_text);
	}

	if (m_gobble) {
		_window.draw(m_gobbleModeText.m_text);
	}

	if (m_paused) {
		_window.draw(m_pausedText.m_text);
	}


	_window.draw(m_clockSprite);
	_window.draw(m_clockText.m_text);
	
	//Draw the Walls
	_window.draw(m_topWall.m_wall);
	_window.draw(m_bottomWall.m_wall);
	_window.draw(m_leftWall.m_wall);
	_window.draw(m_rightWall.m_wall);
}

void State_Game::Destroy() {
	for (auto* food : m_foodArray) {
		food = nullptr;
	}

	for (auto* snake : m_snakes) {
		snake = nullptr;
	}
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

void State_Game::CheckWinningConditions()
{
	//If the player has died, end the game
	auto* playerSnake = dynamic_cast<PlayerSnake*>(m_snakes[0]);
	if (m_snakes[0]->IsDead() && playerSnake) {
		current_state = eCurrentState::e_GameOver;
		core_state.SetState(new State_GameOver());
	}
	//else, end the game if only the player is still alive
	else if (!CheckIfStillAlive()) {
		SaveScores();
		current_state = eCurrentState::e_GameOver;
		core_state.SetState(new State_GameOver());
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
	for (unsigned int i = 0; i < m_snakes.size(); ++i) {
		m_scores[i].SetContent("Player" + std::to_string(i + 1) + ":" + std::to_string(m_snakes[i]->GetScore()));
	}
}

void State_Game::HandleInput() {
	//pause and un-pause the game if escape is pressed
	if (m_escapeKey) {
		m_soundManager->PlaySFX("sfx_menu_pause");
		m_paused = !m_paused;
		m_escapeKey = false;
	}
	//access the player's input function
	for (auto* snake : m_snakes) {
		//There is only ever one player snake
		//If it can be cast to the PlayerSnake type then we have the player
		auto* playerSnake = dynamic_cast<PlayerSnake*>(snake);
		if (playerSnake) {
			if (m_upKey && playerSnake->GetDirection() != EDirection::e_down) {
				playerSnake->SetDirection(EDirection::e_up);
				m_upKey = false;
			}
			if (m_downKey && playerSnake->GetDirection() != EDirection::e_up) {
				playerSnake->SetDirection(EDirection::e_down);
				m_downKey = false;
			}
			if (m_leftKey && playerSnake->GetDirection() != EDirection::e_right) {
				playerSnake->SetDirection(EDirection::e_left);
				m_leftKey = false;
			}
			if (m_rightKey && playerSnake->GetDirection() != EDirection::e_left) {
				playerSnake->SetDirection(EDirection::e_right);
				m_rightKey = false;
			}
			return;
		}
	}
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
