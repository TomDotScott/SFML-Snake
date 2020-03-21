#include "Game.h"
#include <iostream>
/* TO DO
MAKE DESTRUCTORS
VIRTUAL SNAKE ON SNAKECOLLISION
UPDATE AND THEN RENDER
CHANGE VS SETTINGS
*/
Game::Game(sf::RenderWindow& window) : m_window(window) {

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

	for (auto* snake : m_snakes)
	{
		for (auto* food : m_foodArray)
		{
			snake->SetFood(food);
		}
	}
}

Game::~Game() {
	for (Food* food : m_foodArray) {
		delete food;
	}
	delete m_foodArray;

	for(auto* snake : m_snakes)
	{
		delete snake;
	}

	
}

void Game::CheckCollisions() {
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

void Game::RandomiseFood(Food* foodToRandomise)
{
	//Check that food doesn't spawn on top of each other
	bool isOverlapping = true;
	while (isOverlapping) {
		foodToRandomise->Randomise();
		//Check the randomised position
		for (const Food* food : m_foodArray) {
			//make sure the food isn't getting compared to itself!
			if (*food != *foodToRandomise) {
				if (foodToRandomise->GetPosition() != food->GetPosition()) {
					isOverlapping = false;
					break;
				}
			}
			else {
				foodToRandomise->Randomise();
			}
		}
	}
}

void Game::Update() {
	//GOBBLE MODE. After a random amount of time, stop Gobble Mode
	if (rand() % 10 == 0) {
		for (auto* snake : m_snakes) {
			if (!snake->IsDead() && snake->GetIsGobbleMode()) {
				std::cout << "GOBBLE MODE OVER" << std::endl;
				snake->SetIsGobbleMode(false);
			}
		}
	}

	for (Food* food : m_foodArray) {
		food->Render(m_window);
	}


	for(auto* snake : m_snakes)
	{
		snake->Update(m_window);
	}

	//Draw the Walls
	m_window.draw(m_topWall.m_wall);
	m_window.draw(m_bottomWall.m_wall);
	m_window.draw(m_leftWall.m_wall);
	m_window.draw(m_rightWall.m_wall);

}

void Game::Input() const
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