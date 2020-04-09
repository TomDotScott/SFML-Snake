#include "AISnake.h"

AISnake::AISnake() {
	RandomisePosition();

	m_segments.PushBack(m_position, m_direction);
	m_segments.PushBack(sf::Vector2f(m_position.x, (m_position.y)), m_direction);
	m_segments.PushBack(sf::Vector2f(m_position.x - constants::k_gameGridCellSize, (m_position.y)), m_direction);

	//load the textures
	m_headTexture.loadFromFile("Resources/Graphics/Snake_AI_Head.png");
	m_bendTexture.loadFromFile("Resources/Graphics/Snake_AI_Bend.png");
	m_bodyTexture.loadFromFile("Resources/Graphics/Snake_AI_Body.png");
	m_tailTexture.loadFromFile("Resources/Graphics/Snake_AI_Tail.png");
	m_scaredTexture.loadFromFile("Resources/Graphics/Snake_AI_Scared.png");
}

void AISnake::ChooseDirection() {
	if (!m_dead && !m_hasMoved) {
		//if the snake is in its own way...
		//Make decisions based on the chosen food
		EDirection newDirection;

		if (m_targetList.Front().x < m_position.x && m_direction != EDirection::eRight) {
			//If the snake is blocking itself in it's current direction
			newDirection = EDirection::eLeft;
			if (IsSelfInWay(newDirection)) {
				//Is blocking on the left so must move up or down
				newDirection = EDirection::eDown;
				if (!IsSelfInWay(newDirection)) {
					m_direction = EDirection::eDown;
					m_hasMoved = true;
				} else {
					m_direction = EDirection::eUp;
					m_hasMoved = true;
				}
			} else {
				m_direction = EDirection::eLeft;
				m_hasMoved = true;
			}
		} else if (m_targetList.Front().x > m_position.x && m_direction != EDirection::eLeft) {

			newDirection = EDirection::eRight;
			if (IsSelfInWay(newDirection)) {

				//Is blocking on the right so must move up or down
				newDirection = EDirection::eDown;
				if (!IsSelfInWay(newDirection)) {
					m_direction = EDirection::eDown;
					m_hasMoved = true;
				} else {
					m_direction = EDirection::eUp;
					m_hasMoved = true;
				}
			} else {
				m_direction = EDirection::eRight;
				m_hasMoved = true;
			}

		} else if (m_targetList.Front().y > m_position.y && m_direction != EDirection::eUp) {

			newDirection = EDirection::eDown;
			if (IsSelfInWay(newDirection)) {

				//Is blocking on the down so must move left or right
				newDirection = EDirection::eLeft;
				if (!IsSelfInWay(newDirection)) {
					m_direction = EDirection::eLeft;
					m_hasMoved = true;
				} else {
					m_direction = EDirection::eRight;
					m_hasMoved = true;
				}
			} else {
				m_direction = EDirection::eDown;
				m_hasMoved = true;
			}
		} else if (m_targetList.Front().y < m_position.y && m_direction != EDirection::eDown) {
			newDirection = EDirection::eUp;
			if (IsSelfInWay(newDirection)) {

				//Is blocking on the up so must move left or right
				newDirection = EDirection::eLeft;
				if (!IsSelfInWay(newDirection)) {
					m_direction = EDirection::eLeft;
					m_hasMoved = true;
				} else {
					m_direction = EDirection::eRight;
					m_hasMoved = true;
				}
			} else {
				m_direction = EDirection::eUp;
				m_hasMoved = true;
			}
		}
		//IF THE CLOSEST FOOD IS DIRECTLY BEHIND THEM, SNAKES GET CONFUSED...
		//if the y's are the same but the xes are different
		else if (m_targetList.Front().y == m_position.y
			&& m_targetList.Front().x != m_position.x
			&& (m_direction == EDirection::eUp || m_direction == EDirection::eDown)) {
			newDirection = EDirection::eLeft;
			//move left or right
			if (!IsSelfInWay(newDirection)) {
				m_direction = EDirection::eLeft;
				m_hasMoved = true;
			} else {
				m_direction = EDirection::eRight;
				m_hasMoved = true;
			}
		}
		//if the xes are the same but the ys are different
		else if (m_targetList.Front().x == m_position.x
			&& m_targetList.Front().y != m_position.y
			&& (m_direction == EDirection::eLeft || m_direction == EDirection::eRight)) {
			newDirection = EDirection::eUp;
			//move up or down
			if (!IsSelfInWay(newDirection)) {
				m_direction = EDirection::eUp;
				m_hasMoved = true;
			} else {
				m_direction = EDirection::eDown;
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

void AISnake::FindFood() {
	//If it's gobble mode, move towards the closest snake
	if (m_gobbleMode) {
		FindClosestSnake();
	} else {
		//Find the highest food
		FindHighestFood();
		//if there is a snake in the way, revert to going to the closest
		if (IsSnakeInWay()) {
			FindClosestFood();
		}
	}
}


void AISnake::FindClosestFood() {
	//Clear the list of food positions
	m_targetList.Clear();

	sf::Vector2f closestFood = m_food[0]->GetPosition();

	m_targetList.PushFront(closestFood, m_direction);

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
			m_targetList.PushFront(closestFood, EDirection::eNone);

			//check that the closest food isn't in any of the segments
			if (IsOverlapping(closestFood)) {
				m_targetList.PopFront();
			}
		}
		//Otherwise, add to the end of the list
		else {
			m_targetList.PushBack(currentFoodPosition, EDirection::eNone);
		}
	}
}

void AISnake::FindClosestSnake() {
	//Clear the list of food positions
	m_targetList.Clear();

	sf::Vector2f closestSnake = m_otherSnakes[0]->GetHeadPosition();

	m_targetList.PushFront(closestSnake, EDirection::eNone);

	sf::Vector2f positionVectorOfSnakeToOtherSnake =
		sf::Vector2f(closestSnake.x - m_position.x, closestSnake.y - m_position.y);

	float magnitudeOfClosestFood = positionVectorOfSnakeToOtherSnake.x * positionVectorOfSnakeToOtherSnake.x
		+ positionVectorOfSnakeToOtherSnake.y * positionVectorOfSnakeToOtherSnake.y;


	//Find the food that it is closest to
	for (auto* snake : m_otherSnakes) {
		const sf::Vector2f currentSnakePosition{ snake->GetHeadPosition() };

		//see if the current piece of food is closer by working out the magnitude of the vectors
		positionVectorOfSnakeToOtherSnake =
			sf::Vector2f(closestSnake.x - m_position.x, currentSnakePosition.y - m_position.y);

		const float magnitudeOfCurrentFood = positionVectorOfSnakeToOtherSnake.x * positionVectorOfSnakeToOtherSnake.x
			+ positionVectorOfSnakeToOtherSnake.y * positionVectorOfSnakeToOtherSnake.y;

		//If the current piece of food's magnitude is closer than the previous closest piece, it is closer
		if (magnitudeOfCurrentFood < magnitudeOfClosestFood) {

			//reset the closest food
			closestSnake = currentSnakePosition;
			magnitudeOfClosestFood = magnitudeOfCurrentFood;
			m_targetList.PushFront(closestSnake, EDirection::eNone);
		}
		//Otherwise, add to the end of the list
		else {
			m_targetList.PushBack(currentSnakePosition, EDirection::eNone);
		}
	}
}


void AISnake::FindHighestFood() {
	m_targetList.Clear();

	//Initialise the highest food to the first bit of food in the food vector
	Food* highestValueFood = m_food[0];

	//Make the highest the front of the list
	m_targetList.PushFront(highestValueFood->GetPosition(), EDirection::eNone);

	//Check to see if any food is higher value
	for (auto* currentFood : m_food) {
		if (highestValueFood->GetGrowAmount() < currentFood->GetGrowAmount()) {
			m_targetList.PushFront(currentFood->GetPosition(), EDirection::eNone);
			highestValueFood = currentFood;
		}
		//If their values are the same, then choose the one that is closer
		else if (highestValueFood->GetGrowAmount() == currentFood->GetGrowAmount() && !IsOverlapping(currentFood->GetPosition())) {
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
			if (magnitudeOfSnakeToCurrentFood < magnitudeOfSnakeToCurrentHighestValueFood) {
				m_targetList.PushFront(currentFood->GetPosition(), EDirection::eNone);
			}
		} else {
			m_targetList.PushBack(currentFood->GetPosition(), EDirection::eNone);
		}
	}
}

bool AISnake::IsOverlapping(sf::Vector2f _position) const {
	auto* currentNode = m_segments.GetHead();
	for (int i = 0; i < m_segments.Size(); ++i) {
		if (currentNode->m_position == _position) {
			return true;
		}
		auto* nextNode = currentNode->m_nextNode;
		currentNode = nextNode;
	}
	return false;
}

bool AISnake::IsSnakeInWay() const{
	for (auto* snake : m_otherSnakes) {
		//make sure the snake is alive
		if (!snake->IsDead()) {
			//If the x or y co-ordinates of the other snake's segments are the same as the chosen food, it is in the way
			auto* currentNode = snake->GetSnakeSegments().GetHead();
			for (int i = 0; i < snake->GetSnakeSegments().Size(); ++i) {
				const sf::Vector2f segmentPosition = currentNode->m_position;

				//Calculate distance between this snake and the other's segment
				const float deltaX = segmentPosition.x - m_position.x;
				const float deltaY = segmentPosition.y - m_position.y;

				//Only evaluate if close enough
				if (deltaX == constants::k_gameGridCellSize || deltaY == constants::k_gameGridCellSize) {
					if (currentNode->m_position.x == m_targetList.Front().x || currentNode->m_position.y == m_targetList.Front().y) {
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

bool AISnake::IsSelfInWay(EDirection& _direction) const {
	//Cycle through the grid in front of the snake and see if it overlaps
	if ((_direction == EDirection::eLeft && IsOverlapping(sf::Vector2f(m_position.x - constants::k_gameGridCellSize, m_position.y)))
		|| (_direction == EDirection::eRight && IsOverlapping(sf::Vector2f(m_position.x + constants::k_gameGridCellSize, m_position.y)))
		|| (_direction == EDirection::eUp && IsOverlapping(sf::Vector2f(m_position.x, m_position.y - constants::k_gameGridCellSize)))
		|| (_direction == EDirection::eDown && IsOverlapping(sf::Vector2f(m_position.x, m_position.y + constants::k_gameGridCellSize)))) {
		return true;
	}
	return false;
}