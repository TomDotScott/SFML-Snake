#include "AISnake.h"
#include <cmath>
#include <iostream>

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

	m_rectangle = sf::RectangleShape(sf::Vector2f(static_cast<float>(Constants::k_snakeBlockSize), static_cast<float>(Constants::k_snakeBlockSize)));
	m_rectangle.setFillColor(m_colour);
	m_rectangle.setPosition(m_position);
}

void AISnake::ChooseDirection() {
	FindClosestFood();
	
	std::cout << "MY CLOSEST FOOD IS AT " << m_foodList.front().x << " " << m_foodList.front().y << std::endl;
	std::cout << "I AM AT " << m_position.x << " " << m_position.y << std::endl;

	//If the x positions are the same, move up or down to account for it
	if(m_closestFood.x == m_position.x)
	{
		std::cout << "FOOD IS ON THE SAME X AS ME!" << std::endl;
		m_direction = m_position.y <= static_cast<float>(Constants::k_screenHeight) / 2 ? EDirection::e_down : EDirection::e_up;
		return;
	}
	//If the y positions are the same, move left or right to account for it
	if (m_closestFood.y == m_position.y)
	{
		std::cout << "FOOD IS ON THE SAME Y AS ME!" << std::endl;
		m_direction = m_position.x <= static_cast<float>(Constants::k_screenWidth) / 2 ? EDirection::e_right : EDirection::e_left;
		return;
	}

	//Make decisions based on the closest food
	if (m_foodList.front().x < m_position.x && m_direction != EDirection::e_right)
	{
		m_direction = EDirection::e_left;

	}
	if (m_foodList.front().x > m_position.x && m_direction != EDirection::e_left)
	{
		m_direction = EDirection::e_right;

	}
	if (m_foodList.front().y > m_position.y && m_direction != EDirection::e_up)
	{
		m_direction = EDirection::e_down;

	}
	if (m_foodList.front().y < m_position.y && m_direction != EDirection::e_down)
	{
		m_direction = EDirection::e_up;

	}
	
	switch (m_direction) { case EDirection::e_none: break;
	case EDirection::e_left:
		std::cout << "I AM MOVING LEFT" << std::endl;

		break;
	case EDirection::e_right:
		std::cout << "I AM MOVING RIGHT" << std::endl;
		break;
	case EDirection::e_up:
		std::cout << "I AM MOVING UP" << std::endl;
		break;
	case EDirection::e_down:
		std::cout << "I AM MOVING DOWN" << std::endl;
		break;
	default: ;
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
							if (m_gobbleMode) {
								const int growShrinkAmount{ otherSnake->FindGobblePoint(m_position) };
								Grow(growShrinkAmount);
								Shrink(growShrinkAmount);
								return;
							}
							Collision(ECollisionType::e_snake);
							return;
						}
					}
					//If head-on collisions, they both die
					if (m_position == otherSnake->GetHeadPosition()) {
						if (m_gobbleMode) {
							Grow((otherSnake->GetSnakeSegments().size()));
							otherSnake->Collision(ECollisionType::e_snake);
							return;
						}
						Collision(ECollisionType::e_snake);
						otherSnake->Collision(ECollisionType::e_snake);
					}
				}
			}
		}
		CheckCollisionAgainstSelf();
	}
}

void AISnake::FindClosestFood()
{
	//Clear the list of food positions
	m_foodList.clear();
	
	sf::Vector2f closestFood = m_food[0]->GetPosition();
	
	m_foodList.push_front(closestFood);
	
	float magnitudeOfClosestFood = sqrt((closestFood.x * closestFood.x)
		+ (closestFood.y * closestFood.y));

	//Find the food that it is closest to
	for (Food* currentFood : m_food)
	{
		const sf::Vector2f currentFoodPosition = currentFood->GetPosition();
		//see if the current piece of food is closer by working out the magnitude of the vectors
		const float magnitudeOfCurrentFood = sqrt((currentFoodPosition.x * currentFoodPosition.x)
			+ (currentFoodPosition.y * currentFoodPosition.y));
		//If the current piece of food's magnitude is closer than the previous closest piece, it is closer
		if (magnitudeOfCurrentFood < magnitudeOfClosestFood)
		{
			//reset the closest food
			closestFood = currentFoodPosition;
			magnitudeOfClosestFood = magnitudeOfCurrentFood;
			m_foodList.push_front(closestFood);
		}
		m_foodList.push_back(currentFoodPosition);
	}
}

void AISnake::CheckCollisionAgainstSelf()
{
	if (!m_isDead) {
		int counter{ 0 };
		for (sf::Vector2f& segment : m_segments)
		{
			if (segment == m_position && counter != 0)
			{
				Collision(ECollisionType::e_self);
			}
			++counter;
		}
	}
}
