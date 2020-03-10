#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& window) : m_window(window) 
{
	m_playerSnake = new Snake();
	//populate the food array
	for (int i = 0; i < 5; ++i) {
		Food food;
		m_foodArray[i] = food;
	}
}

void Game::CheckCollisions()
{
	for (Food& food : m_foodArray) {
		//only one collision can happen per snake
		if (food.GetPosition() == m_playerSnake->GetPosition()) {
			m_playerSnake->Collision("Food");
			food.RandomisePosition();
			return;
		}
	}
}

void Game::Update() {
	//std::cout << "SNAKE POSITION: " << m_playerSnake->GetPosition().x << " " << m_playerSnake->GetPosition().y << std::endl;
	for (Food& food : m_foodArray) {
		food.Render(m_window);
	}
	m_playerSnake->Update(m_window);

}

void Game::Input() {
	m_playerSnake->Input();
}