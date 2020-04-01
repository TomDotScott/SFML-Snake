#include "AISnake.h"

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
	if (!m_dead && !m_hasMoved) {
		//if the snake is in its own way...
		//Make decisions based on the chosen food
		EDirection newDirection;

		if (m_foodList.Front().x < m_position.x && m_direction != EDirection::e_right) {
			//If the snake is blocking itself in it's current direction
			newDirection = EDirection::e_left;
			if (IsSelfInWay(newDirection))
			{

				//Is blocking on the left so must move up or down
				newDirection = EDirection::e_down;
				if (!IsSelfInWay(newDirection))
				{
					m_direction = EDirection::e_down;
					m_hasMoved = true;
				}
				else
				{
					m_direction = EDirection::e_up;
					m_hasMoved = true;
				}
			}
			else
			{
				m_direction = EDirection::e_left;
				m_hasMoved = true;
			}
		}
		else if (m_foodList.Front().x > m_position.x && m_direction != EDirection::e_left) {

			newDirection = EDirection::e_right;
			if (IsSelfInWay(newDirection))
			{

				//Is blocking on the right so must move up or down
				newDirection = EDirection::e_down;
				if (!IsSelfInWay(newDirection))
				{
					m_direction = EDirection::e_down;
					m_hasMoved = true;
				}
				else
				{
					m_direction = EDirection::e_up;
					m_hasMoved = true;
				}
			}
			else
			{
				m_direction = EDirection::e_right;
				m_hasMoved = true;
			}

		}
		else if (m_foodList.Front().y > m_position.y && m_direction != EDirection::e_up) {

			newDirection = EDirection::e_down;
			if (IsSelfInWay(newDirection))
			{

				//Is blocking on the down so must move left or right
				newDirection = EDirection::e_left;
				if (!IsSelfInWay(newDirection))
				{
					m_direction = EDirection::e_left;
					m_hasMoved = true;
				}
				else
				{
					m_direction = EDirection::e_right;
					m_hasMoved = true;
				}
			}
			else
			{
				m_direction = EDirection::e_down;
				m_hasMoved = true;
			}
		}
		else if (m_foodList.Front().y < m_position.y && m_direction != EDirection::e_down) {
			newDirection = EDirection::e_up;
			if (IsSelfInWay(newDirection))
			{

				//Is blocking on the up so must move left or right
				newDirection = EDirection::e_left;
				if (!IsSelfInWay(newDirection))
				{
					m_direction = EDirection::e_left;
					m_hasMoved = true;
				}
				else
				{
					m_direction = EDirection::e_right;
					m_hasMoved = true;
				}
			}
			else
			{
				m_direction = EDirection::e_up;
				m_hasMoved = true;
			}
		}
		//IF THE CLOSEST FOOD IS DIRECTLY BEHIND THEM, SNAKES GET CONFUSED...
		//if the y's are the same but the xes are different
		else if (m_foodList.Front().y == m_position.y
					&& m_foodList.Front().x != m_position.x
					&& m_direction == EDirection::e_up
					|| m_direction == EDirection::e_down) {
			newDirection = EDirection::e_left;
			//move left or right
			if(!IsSelfInWay(newDirection))
			{
				m_direction = EDirection::e_left;
				m_hasMoved = true;
			}else
			{
				m_direction = EDirection::e_right;
				m_hasMoved = true;
			}
		}
		//if the xes are the same but the ys are different
		else if (m_foodList.Front().x == m_position.x
					&& m_foodList.Front().y != m_position.y
					&& m_direction == EDirection::e_left
					|| m_direction == EDirection::e_right) {
			newDirection = EDirection::e_up;
			//move up or down
			if (!IsSelfInWay(newDirection))
			{
				m_direction = EDirection::e_up;
				m_hasMoved = true;
			}else
			{
				m_direction = EDirection::e_down;
				m_hasMoved = true;
			}
		}
	}
}

void AISnake::Update() {
	if (!m_dead) {
		m_hasMoved = false;
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
	if (IsSnakeInWay())
	{
		FindClosestFood();
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
			if (IsOverlapping(closestFood))
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
	for (auto* currentFood : m_food)
	{
		if (highestValueFood->GetGrowAmount() < currentFood->GetGrowAmount())
		{
			m_foodList.PushFront(currentFood->GetPosition());
			highestValueFood = currentFood;
		}
		//If their values are the same, then choose the one that is closer
		else if (highestValueFood->GetGrowAmount() == currentFood->GetGrowAmount() && !IsOverlapping(currentFood->GetPosition()))
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
			if (magnitudeOfSnakeToCurrentFood < magnitudeOfSnakeToCurrentHighestValueFood)
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

bool AISnake::IsOverlapping(sf::Vector2f _position) const
{
	auto* currentNode = m_segments.GetHead();
	for (int i = 0; i < m_segments.Size(); ++i)
	{
		if (currentNode->m_position == _position)
		{
			return true;
		}
		auto* nextNode = currentNode->m_nextNode;
		currentNode = nextNode;
	}
	return false;
}

bool AISnake::IsSnakeInWay() const
{
	for (auto* snake : m_otherSnakes)
	{
		//make sure the snake is alive
		if (!snake->IsDead()) {
			//If the x or y co-ordinates of the other snake's segments are the same as the chosen food, it is in the way
			auto* currentNode = snake->GetSnakeSegments().GetHead();
			for (int i = 0; i < snake->GetSnakeSegments().Size(); ++i)
			{
				const sf::Vector2f segmentPosition = currentNode->m_position;

				//Calculate distance between this snake and the other's segment
				const float deltaX = segmentPosition.x - m_position.x;
				const float deltaY = segmentPosition.y - m_position.y;

				//Only evaluate if close enough
				if (deltaX <= 3 * Constants::k_gridSize || deltaY <= 3 * Constants::k_gridSize) {
					if (currentNode->m_position.x == m_foodList.Front().x || currentNode->m_position.y == m_foodList.Front().y)
					{
						return true;
					}
				}
				auto* nextNode = currentNode->m_nextNode;
				currentNode = nextNode;
			}
		}
	}
	return false;
}

bool AISnake::IsSelfInWay(EDirection& _direction) const
{
	//Cycle through 2 grids in front of the snake and see if it overlaps
	switch (_direction) {
	case EDirection::e_left:
		if (IsOverlapping(sf::Vector2f(m_position.x - Constants::k_gridSize, m_position.y))
			/*|| IsOverlapping(sf::Vector2f(m_position.x - 2 * Constants::k_gridSize, m_position.y))*/)
		{
			return true;
		}
		break;
	case EDirection::e_right:
		if (IsOverlapping(sf::Vector2f(m_position.x + Constants::k_gridSize, m_position.y))
			/*|| IsOverlapping(sf::Vector2f(m_position.x + 2 * Constants::k_gridSize, m_position.y))*/)
		{
			return true;
		}
		break;
	case EDirection::e_up:
		if (IsOverlapping(sf::Vector2f(m_position.x, m_position.y - Constants::k_gridSize))
			/*|| IsOverlapping(sf::Vector2f(m_position.x, m_position.y - 2 * Constants::k_gridSize))*/)
		{
			return true;
		}
		break;
	case EDirection::e_down:
		if (IsOverlapping(sf::Vector2f(m_position.x, m_position.y + Constants::k_gridSize))
			/*|| IsOverlapping(sf::Vector2f(m_position.x, m_position.y + 2 * Constants::k_gridSize))*/)
		{
			return true;
		}
		break;
	default:
		return false;
	}
	return false;
}
