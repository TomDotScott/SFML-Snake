#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& window) : m_window(window)
{
	m_playerSnake = new PlayerSnake();
	//populate the food array
	for (auto& i : m_foodArray)
	{
		Food* food = new Food();
		i = food;
	}

	//populate the AISnake Vector
	for (int i = 0; i < m_AISnakeAmount; ++i) {
		std::cout << "AI SNAKE CREATED" << std::endl;
		m_AISnakes.push_back(new AISnake(i));
	}

	//Make each AI snake have a pointer to each other
	for (int snakePosition = 0; snakePosition < m_AISnakes.size(); ++snakePosition) {
		for (AISnake* aiSnakeToAdd : m_AISnakes) {
			if (snakePosition != aiSnakeToAdd->GetPlayerNumber()) {
				m_AISnakes[snakePosition]->SetOtherSnakes(aiSnakeToAdd);
				for (Food* food : m_foodArray)
				{
					aiSnakeToAdd->SetFood(food);
				}
			}
		}
	}
}

void Game::CheckCollisions()
{
	//Check player against Walls
	if (!m_playerSnake->GetIsDead() && (m_playerSnake->GetHeadPosition().x == m_leftWall.m_position.x ||
		m_playerSnake->GetHeadPosition().x == m_rightWall.m_position.x ||
		m_playerSnake->GetHeadPosition().y == m_topWall.m_position.y ||
		m_playerSnake->GetHeadPosition().y == m_bottomWall.m_position.y)) {
		m_playerSnake->Collision(ECollisionType::e_wall);
	}

	//Check Against Food
	for (Food* food : m_foodArray) {
		//only one collision can happen per snake
		for (AISnake* aiSnake : m_AISnakes) {
			if (!aiSnake->GetIsDead() && food->GetPosition() == aiSnake->GetHeadPosition()) {
				aiSnake->Collision(food);
				RandomiseFood(food);
				aiSnake->FindFood();
				return;
			}
		}
		//Check the player against food
		if (food->GetPosition() == m_playerSnake->GetHeadPosition()) {
			m_playerSnake->Collision(food);
			food->Randomise();
			for (AISnake* aiSnake : m_AISnakes) {
				aiSnake->FindFood();
			}
			return;
		}
	}
	//Check against other snakes
	for (AISnake* aiSnake : m_AISnakes) {
		for (sf::Vector2f& playerSegment : m_playerSnake->GetSnakeSegments()) {
			if (!aiSnake->GetIsDead() && !m_playerSnake->GetIsDead()) {//Checks if an AI snake hits the player's body
				if (playerSegment == aiSnake->GetHeadPosition()) {
					aiSnake->Collision(ECollisionType::e_snake);
					//return;
				}
				//Check if the player hits an AI Snake's body
				for (sf::Vector2f& aiSegment : aiSnake->GetSnakeSegments()) {
					if (aiSegment == m_playerSnake->GetHeadPosition()) {
						//If it's gobble mode, make sure not to kill the player on collision
						if (m_playerSnake->GetIsGobbleMode()) {
							const int growShrinkAmount{ aiSnake->FindGobblePoint(m_playerSnake->GetHeadPosition()) };
							m_playerSnake->Grow(growShrinkAmount);
							aiSnake->Shrink(growShrinkAmount);
							//return;
						}
						m_playerSnake->Collision(ECollisionType::e_snake);
						//return;
					}
				}
				//If head on collisions, then both die
				//If gobble mode, the snake eats the entire snake
				if (m_playerSnake->GetHeadPosition() == aiSnake->GetHeadPosition()) {
					if (m_playerSnake->GetIsGobbleMode()) {
						m_playerSnake->Grow((aiSnake->GetSnakeSegments().size()));
						aiSnake->Collision(ECollisionType::e_snake);
						//return;
					}
					m_playerSnake->Collision(ECollisionType::e_snake);
					aiSnake->Collision(ECollisionType::e_snake);
					//return;
				}
			}
		}
		//Check AI Collisions with Other snakes
		aiSnake->CheckCollision();
		//Check AI collisions with the Walls
		if (!aiSnake->GetIsDead() && (aiSnake->GetHeadPosition().x == m_leftWall.m_position.x ||
			aiSnake->GetHeadPosition().x == m_rightWall.m_position.x ||
			aiSnake->GetHeadPosition().y == m_topWall.m_position.y ||
			aiSnake->GetHeadPosition().y == m_bottomWall.m_position.y)) {
			aiSnake->Collision(ECollisionType::e_wall);
			//return;
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
		for(Food* food : m_foodArray)
		{
			//make sure the food isn't getting compared to itself!
			if(*food != *foodToRandomise)
			{
				if(foodToRandomise->GetPosition() != food->GetPosition())
				{
					isOverlapping = false;
					break;
				}
			}else
			{
				foodToRandomise->Randomise();
			}
		}
	}
}

void Game::Update() {
	//GOBBLE MODE. After a random amount of time, stop Gobble Mode
	if (rand() % 10 == 0)
	{
		//Check player first
		if (m_playerSnake->GetIsGobbleMode() && !m_playerSnake->GetIsDead()) {
			std::cout << "GOBBLE MODE OVER" << std::endl;

			m_playerSnake->SetIsGobbleMode(false);
		}
		else
		{
			//reset the AI snakes
			for (AISnake* aiSnake : m_AISnakes) {
				if (!aiSnake->GetIsDead() && aiSnake->GetIsGobbleMode()) {
					std::cout << "GOBBLE MODE OVER" << std::endl;

					aiSnake->SetIsGobbleMode(false);
				}
			}
		}
	}

	for (Food* food : m_foodArray) {
		food->Render(m_window);
	}


	for (AISnake* aiSnake : m_AISnakes) {
		//only move if alive
		if (!aiSnake->GetIsDead()) {
			aiSnake->ChooseDirection();
			aiSnake->Update(m_window);
		}
	}

	m_playerSnake->Update(m_window);

	//Draw the Walls
	m_window.draw(m_topWall.m_wall);
	m_window.draw(m_bottomWall.m_wall);
	m_window.draw(m_leftWall.m_wall);
	m_window.draw(m_rightWall.m_wall);

}

void Game::Input() const
{
	m_playerSnake->Input();
}