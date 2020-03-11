#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& window) : m_window(window) 
{
	m_playerSnake = new PlayerSnake();
	//populate the food array
	for (int i = 0; i < 5; ++i) {
		Food food;
		m_foodArray[i] = food;
	}
	//populate the AISnake Vector
	for (int i = 0; i < m_AISnakeAmount; ++i) {
		std::cout << "AI SNAKE CREATED" << std::endl;
		m_AISnakes.push_back(new AISnake());
	}
}

void Game::CheckCollisions()
{
	//Check against Walls

	if (m_playerSnake->GetHeadPosition().x == m_leftWall.m_position.x ||
		m_playerSnake->GetHeadPosition().x == m_rightWall.m_position.x ||
		m_playerSnake->GetHeadPosition().y == m_topWall.m_position.y ||
		m_playerSnake->GetHeadPosition().y == m_bottomWall.m_position.y) {
		m_playerSnake->Collision(ECollisionType::eWall);
	}

	for (AISnake* aiSnake : m_AISnakes) {
		if (!aiSnake->GetIsDead()) {
			if (aiSnake->GetHeadPosition().x == m_leftWall.m_position.x ||
				aiSnake->GetHeadPosition().x == m_rightWall.m_position.x ||
				aiSnake->GetHeadPosition().y == m_topWall.m_position.y ||
				aiSnake->GetHeadPosition().y == m_bottomWall.m_position.y) {
				aiSnake->Collision(ECollisionType::eWall);
			}
		}
	}

	//Check Against Food
	for (Food& food : m_foodArray) {
		//only one collision can happen per snake
		for (AISnake* aiSnake : m_AISnakes) {
			if (!aiSnake->GetIsDead()) {
				if (food.GetPosition() == aiSnake->GetHeadPosition()) {
					aiSnake->Collision(food);
					food.Randomise();
					break;
				}
			}
		}
		//Check the player against food
		if (food.GetPosition() == m_playerSnake->GetHeadPosition()) {
			m_playerSnake->Collision(food);
			food.Randomise();
			break;
		}
	}
	//Check against other snakes
	for (sf::Vector2f& playerSegment : m_playerSnake->GetSnakeSegments()) {
		for (AISnake* aiSnake : m_AISnakes) {
			if (!aiSnake->GetIsDead()) {
				//Checks if an AI snake hits the player's body
				if (playerSegment == aiSnake->GetHeadPosition()) {
					aiSnake->Collision(ECollisionType::eSnake);
					return;
				}
				//Check if the player hits an AI Snake's body
				for (sf::Vector2f& aiSegment : aiSnake->GetSnakeSegments()) {
					if (aiSegment == m_playerSnake->GetHeadPosition()) {
						m_playerSnake->Collision(ECollisionType::eSnake);
						return;
					}
				}
			}
		}
	}
}

void Game::Update() {
	//std::cout << "SNAKE POSITION: " << m_playerSnake->GetPosition().x << " " << m_playerSnake->GetPosition().y << std::endl;
	for (Food& food : m_foodArray) {
		food.Render(m_window);
	}


	for (AISnake* aiSnake : m_AISnakes) {
		aiSnake->ChooseDirection();
		aiSnake->Update(m_window);
	}

	m_playerSnake->Update(m_window);

	//Draw the Walls
	m_window.draw(m_topWall.m_wall);
	m_window.draw(m_bottomWall.m_wall);
	m_window.draw(m_leftWall.m_wall);
	m_window.draw(m_rightWall.m_wall);

}

void Game::Input() {
	m_playerSnake->Input();
}