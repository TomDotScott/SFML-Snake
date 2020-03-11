#include "PlayerSnake.h"

PlayerSnake::PlayerSnake() {
	m_colour = sf::Color::Red;

	int randomNumber = RandomRange(4, (int)(Constants::kScreenWidth - 100) / Constants::kSnakeBlockSize);
	if (randomNumber * 25 >= Constants::kScreenWidth - 100) {
		m_position.x = Constants::kScreenWidth - 100;
	}
	else {
		m_position.x = randomNumber * 25;
	}

	randomNumber = RandomRange(4, (int)(Constants::kScreenHeight - 100) / Constants::kSnakeBlockSize);
	if (randomNumber * 25 >= Constants::kScreenHeight - 100) {
		m_position.y = Constants::kScreenHeight - 100;
	}
	else {
		m_position.y = randomNumber * 25;
	}


	m_segments.push_back(sf::Vector2i(m_position.x, (m_position.y)));
	m_segments.push_back(sf::Vector2i(m_position.x - Constants::kSnakeBlockSize - 5, (m_position.y)));
	m_segments.push_back(sf::Vector2i(m_position.x - Constants::kSnakeBlockSize - 5, (m_position.y)));



	m_rectangle = sf::RectangleShape(sf::Vector2f((float)Constants::kSnakeBlockSize, (float)Constants::kSnakeBlockSize));
	m_rectangle.setFillColor(m_colour);
	m_rectangle.setPosition(m_position);
}

void::PlayerSnake::Input() {
	//if the left arrow is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

		if (m_direction != EDirection::eRight)
		{
			m_direction = EDirection::eLeft;
		}
	}
	//right arrow
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (m_direction != EDirection::eLeft) m_direction = EDirection::eRight;
	}
	//if the up arrow is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (m_direction != EDirection::eDown) m_direction = EDirection::eUp;
	}
	//down arrow
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (m_direction != EDirection::eUp) m_direction = EDirection::eDown;
	}
}