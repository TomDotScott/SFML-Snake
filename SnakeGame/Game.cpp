#include "Game.h"
Game::Game(sf::RenderWindow& window)
	: m_window(window) {
	m_playerSnake = new Snake(sf::Color::Red, sf::Vector2f(400, 300), 10, sf::Vector2f(0.1, 0.1));
}

void Game::Update() {
	m_playerSnake->Update(m_window);
}