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
	//Check Against Food
	for (Food& food : m_foodArray) {
		//only one collision can happen per snake
		for (AISnake* aiSnake : m_AISnakes) {
			if (food.GetPosition() == aiSnake->GetPosition()) {
				aiSnake->Collision(food);
				food.Randomise();
				break;
			}
		}
		//Check the player
		if (food.GetPosition() == m_playerSnake->GetPosition()) {
			m_playerSnake->Collision(food);
			food.Randomise();
			break;
		}
	}
	//Check Against other Snakes
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

}

void Game::Input() {
	m_playerSnake->Input();
}