#include "Game.h"
Game::Game() {
	m_playerSnake = new Snake(sf::Color(255, 0, 0), sf::Vector2f(400, 300), 10, 10, sf::Vector2f(0.1, 0.1));
}

void Game::Update(sf::RenderWindow& window) {
	m_playerSnake->Update(window);
}