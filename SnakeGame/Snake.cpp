#include "Snake.h"
#include "SFML/Graphics.hpp"
#include "Constants.h"

Snake::Snake() {
	m_gobbleBendTexture.loadFromFile("Resources/Graphics/Snake_Gobble_Bend.png");
	m_gobbleBodyTexture.loadFromFile("Resources/Graphics/Snake_Gobble_Body.png");
	m_gobbleHeadTexture.loadFromFile("Resources/Graphics/Snake_Gobble_Head.png");
	m_gobbleTailTexture.loadFromFile("Resources/Graphics/Snake_Gobble_Tail.png");
}

void Snake::Update() {
	if (!IsDead()) {
		m_score += m_gobbleMode ? 2 : 1;
		Move();
	}
}

void Snake::Render(sf::RenderWindow& _window) {
	if (!m_dead) {
		if (!m_segments.IsEmpty()) {
			auto* currentNode = m_segments.GetHead();
			for (int i = 0; i < m_segments.Size(); ++i) {
				if (i == 0) {
					m_sprite.setTexture(m_gobbleMode ? m_gobbleHeadTexture : m_headTexture);
				} else if (i < m_segments.Size() - 1) {
					m_sprite.setTexture(m_gobbleMode ? m_gobbleBodyTexture : m_bodyTexture);
				}

				m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);

				EDirection previousNodeDirection = m_direction;

				if (currentNode->m_previousNode) {
					previousNodeDirection = currentNode->m_previousNode->m_direction;
				}

				//Change rotation depending on direction
				//Add bends at appropriate points
				switch (currentNode->m_direction) {
				case EDirection::e_left:
					if (previousNodeDirection != EDirection::e_left && i < m_segments.Size() - 1) {
						m_sprite.setTexture(m_gobbleMode ? m_gobbleBendTexture : m_bendTexture);

						m_sprite.setRotation(previousNodeDirection == EDirection::e_up ? 0.f : 90.f);

					} else {
						m_sprite.setRotation(90.f);
					}
					break;
				case EDirection::e_right:
					if (previousNodeDirection != EDirection::e_right && i < m_segments.Size() - 1) {
						m_sprite.setTexture(m_gobbleMode ? m_gobbleBendTexture : m_bendTexture);

						m_sprite.setRotation(previousNodeDirection == EDirection::e_up ? -90.f : 180.f);

					} else {
						m_sprite.setRotation(-90.f);
					}
					break;
				case EDirection::e_up:
					if (previousNodeDirection != EDirection::e_up && i < m_segments.Size() - 1) {
						m_sprite.setTexture(m_gobbleMode ? m_gobbleBendTexture : m_bendTexture);

						m_sprite.setRotation(previousNodeDirection == EDirection::e_left ? 180.f : 90.f);

					} else {
						m_sprite.setRotation(180.f);
					}
					break;
				case EDirection::e_down:
					if (previousNodeDirection != EDirection::e_down && i < m_segments.Size() - 1) {
						m_sprite.setTexture(m_gobbleMode ? m_gobbleBendTexture : m_bendTexture);

						m_sprite.setRotation(previousNodeDirection == EDirection::e_left ? -90.f : 0.f);

					} else {
						m_sprite.setRotation(0.f);
					}
					break;
				default:;
				}

				if (i == m_segments.Size() - 1) {
					m_sprite.setTexture(m_gobbleMode ? m_gobbleTailTexture : m_tailTexture);
					//make the tail follow the previous segment
					switch (previousNodeDirection) {
					case EDirection::e_left:
						m_sprite.setRotation(90.f);
						break;
					case EDirection::e_right:
						m_sprite.setRotation(-90.f);
						break;
					case EDirection::e_up:
						m_sprite.setRotation(180.f);
						break;
					case EDirection::e_down:
						m_sprite.setRotation(0.f);
						break;
					default:;
					}
				}
				m_sprite.setPosition(currentNode->m_position);
				_window.draw(m_sprite);
				currentNode = currentNode->m_nextNode;
			}
		}
	}
}

void Snake::Move() {
	switch (m_direction) {
	case EDirection::e_left:
		m_position.x -= (Constants::k_gameGridCellSize);
		break;
	case EDirection::e_right:
		m_position.x += (Constants::k_gameGridCellSize);
		break;
	case EDirection::e_up:
		m_position.y -= (Constants::k_gameGridCellSize);
		break;
	case EDirection::e_down:
		m_position.y += (Constants::k_gameGridCellSize);
		break;
	default:
		break;
	}

	CheckCollisions();
	m_segments.PopBack();
	m_segments.PushFront(sf::Vector2f(m_position.x, m_position.y), m_direction);
}

void Snake::Grow(const int _amount) {
	for (int i{ 0 }; i < _amount; ++i) {
		m_segments.PushBack(sf::Vector2f(m_position.x, m_position.y), m_direction);
	}
	m_score += (!m_gobbleMode ? 10 : 20) * _amount;
}

//Find the point where a snake intersects and returns the position in the linked list.
//This point - the overall size will be the grow amount of the snake that collided with it
int Snake::FindGobblePoint(sf::Vector2f _gobbleSnakeHead) const {
	if (!m_dead) {
		int counter{ 0 };
		if (!m_segments.IsEmpty()) {
			auto* currentNode = m_segments.GetHead();
			while (currentNode->m_nextNode) {
				if (currentNode->m_position == _gobbleSnakeHead) {
					return counter;
				}
				currentNode = currentNode->m_nextNode;
				++counter;
			}
		}
	}
	return -1;
}

void Snake::Shrink(const int _amount) {
	if (!m_segments.IsEmpty()) {
		const int newSize = m_segments.Size() - _amount;
		while (m_segments.Size() != newSize) {
			m_segments.PopBack();
		}
	}
}

//check the snake's collisions
void Snake::CheckCollisions() {
	CheckCollisionsAgainstSelf();
	CheckCollisionsAgainstFood();
	CheckCollisionsAgainstOtherSnakes();
}

void Snake::CheckCollisionsAgainstSelf() {
	if (m_direction != EDirection::e_none && !m_segments.IsEmpty()) {
		auto* currentNode = m_segments.GetHead();
		for (int i = 0; i < m_segments.Size(); ++i) {
			if (currentNode->m_position == m_position && !IsDead()) {
				Collision(ECollisionType::e_self);
			}
			currentNode = currentNode->m_nextNode;
		}
	}
}

void Snake::CheckCollisionsAgainstFood() {
	//Check Against Food
	for (auto* food : m_food) {
		if (food->GetPosition() == m_position) {
			Collision(food);
			food->Randomise();
		}
	}
}

void Snake::CheckCollisionsAgainstOtherSnakes() {
	//Check against other snakes
	for (auto* otherSnake : m_otherSnakes) {
		if (!otherSnake->IsDead()) {
			//Check each segment of the current snake against the heads of the other snakes
			auto currentSegment = m_segments.GetHead();
			for (int i = 0; i < m_segments.Size(); ++i) {
				//Check each segment against the heads of the other snakes
				if (currentSegment->m_position == otherSnake->GetHeadPosition()) {
					//if it's a head on collision then both snakes die
					if (m_position == currentSegment->m_position) {
						//If it's gobble mode, the entire other snake gets eaten
						if (m_gobbleMode) {
							Grow(static_cast<const int>((otherSnake->GetSnakeSegments().Size())));
							otherSnake->Collision(ECollisionType::e_snake);
							return;
						}
						Collision(ECollisionType::e_snake);
						otherSnake->Collision(ECollisionType::e_snake);
						return;
					}
					otherSnake->Collision(ECollisionType::e_snake);
				}
				currentSegment = currentSegment->m_nextNode;
			}

			//Check if the snake has hit another snake's body
			auto otherSegment = otherSnake->GetSnakeSegments().GetHead();
			for (int i = 0; i < otherSnake->GetSnakeSegments().Size(); ++i) {
				if (otherSegment->m_position == m_position) {
					//If it's gobble mode, make sure not to kill the player on collision
					if (m_gobbleMode) {
						const int growShrinkAmount{ otherSnake->FindGobblePoint(m_position) };
						Grow(growShrinkAmount);
						otherSnake->Shrink(growShrinkAmount);
						return;
					} else {
						Collision(ECollisionType::e_snake);
						return;
					}
				}
				otherSegment = otherSegment->m_nextNode;
			}
		}
	}
}


void Snake::Collision(const ECollisionType _collisionType) {
	if (!m_dead) {
		if (_collisionType == ECollisionType::e_wall
			|| _collisionType == ECollisionType::e_snake
			|| _collisionType == ECollisionType::e_self) {
			m_dead = true;
		}
	}
}

void Snake::Collision(Food* _food) {
	switch (_food->GetType()) {
	case eFoodType::e_standard:
		m_soundManager.PlaySFX("sfx_food_standard");
		break;

	case eFoodType::e_special:
		m_soundManager.PlaySFX("sfx_food_special");
		break;

	case eFoodType::e_gobble:
		m_gobbleMode = true;
		m_soundManager.PlaySFX("sfx_gobble_on");
		break;

	}
	const int growAmount{ _food->GetGrowAmount() };
	Grow(growAmount);
}