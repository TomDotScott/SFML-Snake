#include "State_Game.h"
#include <iostream>
/* TO DO
 STATES!:
 * START MENU
 * PAUSE MENU
 * GAME-OVER MENU
TIDY UP AND DO PROPER UI
HIGH-SCORE SAVING
MAKE SNAKES AWARE OF OTHER SNAKES IN PATH-FINDING
CLEAR UP WARNINGS
*/

//BASESTATE METHODS
void State_Game::Initialize(sf::RenderWindow* _window, sf::Font* _font)
{
	m_font = *_font;
	
	auto* playerSnake = new PlayerSnake();
	m_snakes.push_back(playerSnake);

	//populate the food array
	for (auto& i : m_foodArray) {
		Food* food = new Food();
		i = food;
	}

	//populate the snake Vector
	for (int i = 0; i < Constants::k_AISnakeAmount; ++i) {
		std::cout << "AI SNAKE CREATED" << std::endl;
		m_snakes.push_back(new AISnake());
	}

	//populate the score UI
	for (unsigned int i = 0; i < m_snakes.size(); ++i)
	{
		sf::Text playerText;
		playerText.setFont(m_font);
		std::string textToDisplay = "Player";
		textToDisplay += std::to_string(i + 1) + ":";
		playerText.setString(textToDisplay);
		playerText.setFillColor(sf::Color::White);
		playerText.setCharacterSize(25);

		//Work out where they will be positioned
		playerText.setPosition(sf::Vector2f(Constants::k_screenWidth - 175, (i * Constants::k_gridSize) + 10));
		m_scores.push_back(playerText);
	}

	//configure Gobble mode text
	m_gobbleModeText.setFont(m_font);
	m_gobbleModeText.setString("GOBBLE MODE!");
	m_gobbleModeText.setCharacterSize(15);
	m_gobbleModeText.setFillColor(sf::Color::Yellow);
	m_gobbleModeText.setPosition(Constants::k_screenWidth - 175, Constants::k_screenHeight - 200);


	//make the snakes know where food is on the screen
	for (auto* snake : m_snakes)
	{
		for (auto* food : m_foodArray)
		{
			snake->SetFood(food);
		}
	}
}

void State_Game::Update(sf::RenderWindow* _window) {
	m_gobble = false;

	Input();
	CheckCollisions();
	
	for (auto* snake : m_snakes)
	{
		if (snake->GetIsGobbleMode())
		{
			m_gobble = true;
		}
		snake->Update(*_window);
	}
	
	//GOBBLE MODE. After a random amount of time, stop Gobble Mode
	if (rand() % 25 == 0 && m_gobble) {
		for (auto* snake : m_snakes) {
			if (!snake->IsDead() && snake->GetIsGobbleMode()) {
				std::cout << "GOBBLE MODE OVER" << std::endl;
				snake->SetIsGobbleMode(false);
				break;
			}
		}
	}

	UpdateScores();
}

void State_Game::Render(sf::RenderWindow* _window)
{
	for (Food* food : m_foodArray) {
		food->Render(*_window);
	}
	
	//Draw the score UI
	for (const auto& score : m_scores)
	{
		_window->draw(score);
		if (m_gobble)
		{
			_window->draw(m_gobbleModeText);
		}
	}

	//Draw the Walls
	_window->draw(m_topWall.m_wall);
	_window->draw(m_bottomWall.m_wall);
	_window->draw(m_leftWall.m_wall);
	_window->draw(m_rightWall.m_wall);
}

void State_Game::Destroy(sf::RenderWindow* _window)
{
	for (Food* food : m_foodArray) {
		delete food;
	}

	for (auto* snake : m_snakes)
	{
		delete snake;
	}
}


//GAME METHODS
void State_Game::CheckCollisions() {
	for (auto* currentSnake : m_snakes) {
		//only check collisions if the snake is alive
		if (!currentSnake->IsDead()) {
			//Check against Walls
			if (currentSnake->GetHeadPosition().x == m_leftWall.m_position.x ||
				currentSnake->GetHeadPosition().x == m_rightWall.m_position.x ||
				currentSnake->GetHeadPosition().y == m_topWall.m_position.y ||
				currentSnake->GetHeadPosition().y == m_bottomWall.m_position.y) {
				currentSnake->Collision(ECollisionType::e_wall);
				return;
			}

			//Check Against Food
			for (auto* food : m_foodArray) {
				if (food->GetPosition() == currentSnake->GetHeadPosition()) {
					currentSnake->Collision(food);
					RandomiseFood(food);
					return;
				}
			}
			//Check against other snakes
			for (auto* otherSnake : m_snakes) {
				if (!otherSnake->IsDead() && (otherSnake != currentSnake)) {
					//Check each segment of the snake against the heads of the other snakes
					for (auto& snakeSegment : currentSnake->GetSnakeSegments()) {
						if (snakeSegment == otherSnake->GetHeadPosition()) {
							otherSnake->Collision(ECollisionType::e_snake);
							return;
						}
					}
					//Check if the snake has hit another snake's body
					for (auto& otherSegment : otherSnake->GetSnakeSegments()) {
						if (otherSegment == currentSnake->GetHeadPosition()) {
							//If it's gobble mode, make sure not to kill the player on collision
							if (currentSnake->GetIsGobbleMode()) {
								const int growShrinkAmount{ otherSnake->FindGobblePoint(currentSnake->GetHeadPosition()) };
								currentSnake->Grow(growShrinkAmount);
								otherSnake->Shrink(growShrinkAmount);
								return;
							}
							else {
								currentSnake->Collision(ECollisionType::e_snake);
								return;
							}
						}
					}
					//If head on collisions, then both die
					//If gobble mode, the snake eats the entire snake
					if (currentSnake->GetHeadPosition() == otherSnake->GetHeadPosition()) {
						if (currentSnake->GetIsGobbleMode()) {
							currentSnake->Grow((otherSnake->GetSnakeSegments().size()));
							otherSnake->Collision(ECollisionType::e_snake);
							return;
						}
						//currentSnake->Collision(ECollisionType::e_snake);
						//otherSnake->Collision(ECollisionType::e_snake);
						return;
					}
				}
			}
		}
	}
}

void State_Game::RandomiseFood(Food* _foodToRandomise)
{
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
				}
			}
			else {
				_foodToRandomise->Randomise();
			}
		}
	}
}

void State_Game::UpdateScores()
{
	for(unsigned int i = 0; i < m_snakes.size(); ++i)
	{
		std::string textToDisplay = "Player" + std::to_string(i + 1) + ":" + std::to_string(m_snakes[i]->GetScore());
		m_scores[i].setString(textToDisplay);
	}
}

void State_Game::Input() const
{
	//access the player's input function
	for (auto* snake : m_snakes)
	{
		auto* playerSnake = dynamic_cast<PlayerSnake*>(snake);
		if (playerSnake)
		{
			playerSnake->Input();
			return;
		}
	}
}