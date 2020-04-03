#include "PlayerSnake.h"

PlayerSnake::PlayerSnake() {
	m_colour = sf::Color::Red;

	int randomNumber{ RandomRange(4, static_cast<int>(Constants::k_screenWidth - 400) / Constants::k_snakeBlockSize) };

	if (randomNumber * Constants::k_gridSize >= Constants::k_screenWidth - 200) {
		m_position.x = static_cast<float>(Constants::k_screenWidth - 200);
	} else {
		m_position.x = static_cast<float>(randomNumber * Constants::k_gridSize);
	}

	randomNumber = RandomRange(4, static_cast<int>(Constants::k_screenHeight - 100) / Constants::k_snakeBlockSize);
	if (randomNumber * Constants::k_gridSize >= Constants::k_screenHeight - 100) {
		m_position.y = static_cast<float>(Constants::k_screenHeight - 100);
	} else {
		m_position.y = static_cast<float>(randomNumber * Constants::k_gridSize);
	}

	m_segments.PushBack(m_position);
	m_segments.PushBack(sf::Vector2f(m_position.x, (m_position.y)));
	m_segments.PushBack(sf::Vector2f(m_position.x - Constants::k_gridSize, (m_position.y)));

	m_rectangle = sf::RectangleShape(sf::Vector2f(static_cast<float>(Constants::k_snakeBlockSize), static_cast<float>(Constants::k_snakeBlockSize)));
	m_rectangle.setFillColor(m_colour);
	m_rectangle.setPosition(m_position);
}
