#include "AISnake.h"

AISnake::AISnake(int playerNumber) : m_playerNumber(playerNumber) {
	int randomNumber = RandomRange(4, static_cast<int>(Constants::k_screenWidth - 100) / Constants::k_snakeBlockSize);
	if (randomNumber * 25 >= Constants::k_screenWidth - 100) {
		m_position.x = Constants::k_screenWidth - 100;
	}
	else {
		m_position.x = randomNumber * 25;
	}

	randomNumber = RandomRange(4, static_cast<int>(Constants::k_screenHeight - 100) / Constants::k_snakeBlockSize);
	if (randomNumber * 25 >= Constants::k_screenHeight - 100) {
		m_position.y = Constants::k_screenHeight - 100;
	}
	else {
		m_position.y = randomNumber * 25;
	}

	m_segments.push_back(sf::Vector2f(m_position.x, (m_position.y)));
	m_segments.push_back(sf::Vector2f(m_position.x - Constants::k_snakeBlockSize - 5, (m_position.y)));
	m_segments.push_back(sf::Vector2f(m_position.x - Constants::k_snakeBlockSize - 5, (m_position.y)));

	m_rectangle = sf::RectangleShape(sf::Vector2f(static_cast<float>(Constants::k_snakeBlockSize), static_cast<float>(Constants::k_snakeBlockSize)));
	m_rectangle.setFillColor(m_colour);
	m_rectangle.setPosition(m_position);
}

void AISnake::ChooseDirection() {
	const int randomChoice = RandomRange(0, 4);
	//Make sure they can't go out of bounds and can't kill themselves
	if (randomChoice == 0 && m_direction != EDirection::e_right) {
		if (m_position.x > 100) {
			m_direction = EDirection::e_left;
		}
	}
	if (randomChoice == 1 && m_direction != EDirection::e_left) {
		if(m_position.x < Constants::k_screenWidth - 100) {
			m_direction = EDirection::e_right;
		}
	}
	if (randomChoice == 2 && m_direction != EDirection::e_down) {
		if (m_position.y > 100) {
			m_direction = EDirection::e_up;
		}
	}
	else if (randomChoice == 3 && m_direction != EDirection::e_up) {
		if (m_position.y < Constants::k_screenHeight - 100) {
			m_direction = EDirection::e_down;
		}
	}
}

void AISnake::CheckCollision()
{
	if (!m_isDead) {
		//check each snake segment against other snake heads
		//and other snake heads against this snake's segments
		for (sf::Vector2f& segment : m_segments) {
			for (AISnake* otherSnake : m_otherSnakes) {
				if (!otherSnake->GetIsDead()) {
					//If another snake's head has hit this segment
					if (segment == otherSnake->GetHeadPosition()) {
						otherSnake->Collision(ECollisionType::e_snake);
						return;
					}
					//Check if this snake has hit another snake's body
					for (sf::Vector2f& otherSegment : otherSnake->GetSnakeSegments()) {
						if (otherSegment == m_position) {
							Collision(ECollisionType::e_snake);
							return;
						}
					}
					//If head-on collisions, they both die
					if (m_position == otherSnake->GetHeadPosition()) {
						Collision(ECollisionType::e_snake);
						otherSnake->Collision(ECollisionType::e_snake);
					}
				}
			}
		}
	}
}
