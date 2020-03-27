#include "AISnake.h"
#include <cmath>
#include <iostream>

AISnake::AISnake() {
	m_defaultColour = sf::Color(sf::Color::Blue);

	int randomNumber{ RandomRange(4, static_cast<int>(Constants::k_screenWidth - 400) / Constants::k_snakeBlockSize) };

	if (randomNumber * Constants::k_gridSize >= Constants::k_screenWidth - 200) {
		m_position.x = static_cast<float>(Constants::k_screenWidth - 200);
	}
	else {
		m_position.x = static_cast<float>(randomNumber * Constants::k_gridSize);
	}

	randomNumber = RandomRange(4, static_cast<int>(Constants::k_screenHeight - 100) / Constants::k_snakeBlockSize);
	if (randomNumber * Constants::k_gridSize >= Constants::k_screenHeight - 100) {
		m_position.y = static_cast<float>(Constants::k_screenHeight - 100);
	}
	else {
		m_position.y = static_cast<float>(randomNumber * Constants::k_gridSize);
	}

	m_segments.PushBack(m_position);
	m_segments.PushBack(sf::Vector2f(m_position.x, (m_position.y)));
	m_segments.PushBack(sf::Vector2f(m_position.x - Constants::k_gridSize, (m_position.y)));

	m_rectangle = sf::RectangleShape(sf::Vector2f(static_cast<float>(Constants::k_snakeBlockSize), static_cast<float>(Constants::k_snakeBlockSize)));
	m_rectangle.setFillColor(m_colour);
	m_rectangle.setPosition(m_position);
}

void AISnake::ChooseDirection() {
	if (!m_dead) {
		FindFood();

		//Make decisions based on the closest food
		if (m_foodList.Front().x < m_position.x && m_direction != EDirection::e_right) {
			m_direction = EDirection::e_left;
		}
		else if (m_foodList.Front().x > m_position.x && m_direction != EDirection::e_left) {
			m_direction = EDirection::e_right;
		}
		else if (m_foodList.Front().y > m_position.y && m_direction != EDirection::e_up) {
			m_direction = EDirection::e_down;
		}
		else if (m_foodList.Front().y < m_position.y && m_direction != EDirection::e_down) {
			m_direction = EDirection::e_up;
		}
	}
}

void AISnake::Update(sf::RenderWindow& _window) {
	if (!m_dead) {
		m_score += 1;
		ChooseDirection();
		Move();
		//Render(_window);
	}
}

void AISnake::FindFood()
{
	//Clear the list of food positions
	m_foodList.Clear();
	
	sf::Vector2f closestFood = m_food[0]->GetPosition();
	
	m_foodList.PushFront(closestFood);

	//Vector AB = b - a
	//Magnitude = x^2 + y^2

	sf::Vector2f positionVectorOfSnakeToFood = 
		sf::Vector2f(closestFood.x - m_position.x, closestFood.y - m_position.y);
	
	float magnitudeOfClosestFood = positionVectorOfSnakeToFood.x * positionVectorOfSnakeToFood.x
		+ positionVectorOfSnakeToFood.y * positionVectorOfSnakeToFood.y;
	

	//Find the food that it is closest to
	for (Food* currentFood : m_food) {
		const sf::Vector2f currentFoodPosition{ currentFood->GetPosition() };
		
		//see if the current piece of food is closer by working out the magnitude of the vectors
		positionVectorOfSnakeToFood = 
			sf::Vector2f(currentFoodPosition.x - m_position.x, currentFoodPosition.y - m_position.y);

		const float magnitudeOfCurrentFood = positionVectorOfSnakeToFood.x * positionVectorOfSnakeToFood.x
			+ positionVectorOfSnakeToFood.y * positionVectorOfSnakeToFood.y;
		
		//If the current piece of food's magnitude is closer than the previous closest piece, it is closer
		if (magnitudeOfCurrentFood < magnitudeOfClosestFood) {
			
			//reset the closest food
			closestFood = currentFoodPosition;
			magnitudeOfClosestFood = magnitudeOfCurrentFood;
			m_foodList.PushFront(closestFood);

			//check that the closest food isn't in any of the segments
			
			auto* currentNode = m_segments.GetHead();
			for(int i = 0; i < m_segments.Size(); ++i)
			{
				if(currentNode->m_position == closestFood)
				{
					m_foodList.PopFront();
				}
			}
			
			/*for(const sf::Vector2f& segment : m_segments) {
				if(segment == closestFood) {
					m_foodList.pop_front();
				}
			}*/
			
		}
		m_foodList.PushBack(currentFoodPosition);
	}
	
}
