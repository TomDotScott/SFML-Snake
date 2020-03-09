#include "Game.h"

Game::Game(sf::RenderWindow& window) : m_window(window) 
{
	m_playerSnake = new Snake();
	//populate the food array
	for (int i = 0; i < 5; ++i) {
		Food food;
		m_foodArray[i] = food;
	}
}

void Game::Update() {
	m_playerSnake->Update(m_window);
	for (Food food : m_foodArray) {
		food.Render(m_window);
	}
}

void Game::Input() {
	m_playerSnake->Input();
}