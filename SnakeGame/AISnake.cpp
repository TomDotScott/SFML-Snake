#include "AISnake.h"
#include <cmath>
#include <iostream>

//NEW ALGORITHM - MOVE TOWARDS THE FOOD WITH THE HIGHEST SCORE UNLESS ANOTHER SNAKE IS BLOCKING THE PATH

AISnake::AISnake() {
	m_defaultColour = sf::Color(sf::Color::Blue);

	int randomNumber{ RandomRange(4, static_cast<int>(Constants::k_screenWidth - 400) / Constants::k_snakeBlockSize) };

	m_position.x = static_cast<float>((randomNumber * Constants::k_gridSize >= Constants::k_screenWidth - 200 
					? Constants::k_screenWidth - 200 
					: randomNumber * Constants::k_gridSize));

	randomNumber = RandomRange(4, static_cast<int>(Constants::k_screenHeight - 100) / Constants::k_snakeBlockSize);
	
	m_position.y = static_cast<float>((randomNumber * Constants::k_gridSize >= Constants::k_screenHeight - 100 
					? Constants::k_screenHeight - 100 
					: randomNumber * Constants::k_gridSize));

	m_segments.PushBack(m_position);
	m_segments.PushBack(sf::Vector2f(m_position.x, (m_position.y)));
	m_segments.PushBack(sf::Vector2f(m_position.x - Constants::k_gridSize, (m_position.y)));

	m_rectangle = sf::RectangleShape(sf::Vector2f(static_cast<float>(Constants::k_snakeBlockSize), static_cast<float>(Constants::k_snakeBlockSize)));
	m_rectangle.setFillColor(m_colour);
	m_rectangle.setPosition(m_position);
}

void AISnake::ChooseDirection() {
	if (!m_dead) {
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

void AISnake::Update() {
	if (!m_dead) {
		m_score += 1;
		FindFood();
		ChooseDirection();
		Move();
	}
}

void AISnake::FindFood()
{
	//Find the highest food
	FindHighestFood();
	//if there is a snake in the way, revert to going to the closest
	if(IsSnakeInWay())
	{
		std::cout << "THERE'S A SNAKE IN MY WAY, I AM GOING TO MY CLOSEST FOOD" << std::endl;
		FindClosestFood();
	}
	//if there is a snake in the way, choose the first food that has nobody heading towards it
	if(IsSnakeInWay())
	{
		std::cout << "THERE'S A SNAKE IN MY WAY, I AM GOING TO FOOD THAT HAS NOBODY IN THE WAY" << std::endl;
		const int randomFood = RandomRange(0, Constants::k_foodAmount - 1);
		m_foodList.PushFront(m_food[randomFood]->GetPosition());
	}
}

void AISnake::FindClosestFood()
{
	//Clear the list of food positions
	m_foodList.Clear();

	sf::Vector2f closestFood = m_food[0]->GetPosition();

	m_foodList.PushFront(closestFood);

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
			if (IsFoodOverlapping(closestFood))
			{
				m_foodList.PopFront();
			}
		}
		//Otherwise, add to the end of the list
		else {
			m_foodList.PushBack(currentFoodPosition);
		}
	}
}

void AISnake::FindHighestFood()
{
	m_foodList.Clear();
	
	//Initialise the highest food to the first bit of food in the food vector
	Food* highestValueFood = m_food[0];

	//Make the highest the front of the list
	m_foodList.PushFront(highestValueFood->GetPosition());
	
	//Check to see if any food is higher value
	for(auto* currentFood : m_food)
	{
		if(highestValueFood->GetGrowAmount() < currentFood->GetGrowAmount())
		{
			m_foodList.PushFront(currentFood->GetPosition());
			highestValueFood = currentFood;
		}
		//If their values are the same, then choose the one that is closer
		else if(highestValueFood->GetGrowAmount() == currentFood->GetGrowAmount() && !IsFoodOverlapping(currentFood->GetPosition()))
		{
			const sf::Vector2f positionVectorOfSnakeToCurrentHighestValueFood = 
				sf::Vector2f(highestValueFood->GetPosition().x - m_position.x, highestValueFood->GetPosition().y - m_position.y);

			const sf::Vector2f positionVectorOfSnakeToCurrentFood =
				sf::Vector2f(currentFood->GetPosition().x - m_position.x, currentFood->GetPosition().y - m_position.y);

			const float magnitudeOfSnakeToCurrentHighestValueFood
				= positionVectorOfSnakeToCurrentHighestValueFood.x * positionVectorOfSnakeToCurrentHighestValueFood.x
				+ positionVectorOfSnakeToCurrentHighestValueFood.y * positionVectorOfSnakeToCurrentHighestValueFood.y;

			const float magnitudeOfSnakeToCurrentFood
				= positionVectorOfSnakeToCurrentFood.x * positionVectorOfSnakeToCurrentFood.x
				+ positionVectorOfSnakeToCurrentFood.y * positionVectorOfSnakeToCurrentFood.y;

			//If the current food is closer, then it goes to the front of the list
			if(magnitudeOfSnakeToCurrentFood < magnitudeOfSnakeToCurrentHighestValueFood)
			{
				m_foodList.PushFront(currentFood->GetPosition());
			}
		}
		else
		{
			m_foodList.PushBack(currentFood->GetPosition());
		}
	}	
}

bool AISnake::IsFoodOverlapping(sf::Vector2f _foodPosition) const
{
	auto* currentNode = m_segments.GetHead();
	for (int i = 0; i < m_segments.Size(); ++i)
	{
		if (currentNode->m_position == _foodPosition)
		{
			return true;
		}
	}
	return false;
}

bool AISnake::IsSnakeInWay() const
{
	for(auto* snake : m_otherSnakes)
	{
		//make sure the snake is alive
		if (!snake->IsDead()) {
			//If the x or y co-ordinates of the other snake's segments are the same as the chosen food, it is in the way
			if (snake->GetHeadPosition().x == m_foodList.Front().x || snake->GetHeadPosition().y == m_foodList.Front().y)
			{
				return true;
			}
		}
	}
	return false;
}