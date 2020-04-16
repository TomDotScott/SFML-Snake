#include "Snake.h"

#include "SFML/Graphics.hpp"
#include "Constants.h"

Snake::Snake(SoundManager& _soundManager, std::array<Food*, constants::k_foodAmount>& _foodArray) : m_soundManager(_soundManager), m_food(_foodArray) {
	m_gobbleBendTexture.loadFromFile("Resources/Graphics/Snake_Gobble_Bend.png");
	m_gobbleBodyTexture.loadFromFile("Resources/Graphics/Snake_Gobble_Body.png");
	m_gobbleHeadTexture.loadFromFile("Resources/Graphics/Snake_Gobble_Head.png");
	m_gobbleTailTexture.loadFromFile("Resources/Graphics/Snake_Gobble_Tail.png");
}

void Snake::Update() {
	if (!IsDead()) {
		m_score += m_gobbleMode ? 2 : 1;
		//If the snake has no segments left (is just a tail) then it is dead
		if (m_segments.Size() == 1) {
			m_dead = true;
		}
		Move();
	}
}

void Snake::Render(sf::RenderWindow& _window) {
	if (!m_dead) {
		if (!m_segments.IsEmpty()) {
			auto* currentNode = m_segments.Front();
			for (int i = 0; i < m_segments.Size(); ++i) {
				if (i == 0) {
					m_sprite.setTexture(m_gobbleMode ? m_gobbleHeadTexture : m_headTexture);
				} else if (i < m_segments.Size() - 1) {
					m_sprite.setTexture(m_gobbleMode ? m_gobbleBodyTexture : m_bodyTexture);
				}

				m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);

				EDirection previousNodeDirection = m_direction;

				if (currentNode->m_previousNode) {
					previousNodeDirection = currentNode->m_previousNode->m_data.second;
				}

				//Change rotation depending on direction
				//Add bends at appropriate points
				switch (currentNode->m_data.second) {
				case EDirection::eLeft:
					if (previousNodeDirection != EDirection::eLeft && i < m_segments.Size() - 1) {
						m_sprite.setTexture(m_gobbleMode ? m_gobbleBendTexture : m_bendTexture);

						m_sprite.setRotation(previousNodeDirection == EDirection::eUp ? 0.f : 90.f);

					} else {
						m_sprite.setRotation(90.f);
					}
					break;
				case EDirection::eRight:
					if (previousNodeDirection != EDirection::eRight && i < m_segments.Size() - 1) {
						m_sprite.setTexture(m_gobbleMode ? m_gobbleBendTexture : m_bendTexture);

						m_sprite.setRotation(previousNodeDirection == EDirection::eUp ? -90.f : 180.f);

					} else {
						m_sprite.setRotation(-90.f);
					}
					break;
				case EDirection::eUp:
					if (previousNodeDirection != EDirection::eUp && i < m_segments.Size() - 1) {
						m_sprite.setTexture(m_gobbleMode ? m_gobbleBendTexture : m_bendTexture);

						m_sprite.setRotation(previousNodeDirection == EDirection::eLeft ? 180.f : 90.f);

					} else {
						m_sprite.setRotation(180.f);
					}
					break;
				case EDirection::eDown:
					if (previousNodeDirection != EDirection::eDown && i < m_segments.Size() - 1) {
						m_sprite.setTexture(m_gobbleMode ? m_gobbleBendTexture : m_bendTexture);

						m_sprite.setRotation(previousNodeDirection == EDirection::eLeft ? -90.f : 0.f);

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
					case EDirection::eLeft:
						m_sprite.setRotation(90.f);
						break;
					case EDirection::eRight:
						m_sprite.setRotation(-90.f);
						break;
					case EDirection::eUp:
						m_sprite.setRotation(180.f);
						break;
					case EDirection::eDown:
						m_sprite.setRotation(0.f);
						break;
					default:;
					}
				}
				m_sprite.setPosition(currentNode->m_data.first);
				_window.draw(m_sprite);
				currentNode = currentNode->m_nextNode;
			}
		}
	}
}

void Snake::Move() {
	switch (m_direction) {
	case EDirection::eLeft:
		m_position.x -= (constants::k_gameGridCellSize);
		break;
	case EDirection::eRight:
		m_position.x += (constants::k_gameGridCellSize);
		break;
	case EDirection::eUp:
		m_position.y -= (constants::k_gameGridCellSize);
		break;
	case EDirection::eDown:
		m_position.y += (constants::k_gameGridCellSize);
		break;
	default:
		break;
	}
	m_segments.PopBack();
	m_segments.PushFront({ sf::Vector2f(m_position.x, m_position.y), m_direction });
}

void Snake::Grow(const int _amount) {
	for (int i{ 0 }; i < _amount; ++i) {
		m_segments.PushBack({ sf::Vector2f(m_position.x, m_position.y), m_direction });
	}
	m_score += (!m_gobbleMode ? 10 : 20) * _amount;
}

//Find the point where a snake intersects and returns the position in the linked list.
//This point - the overall size will be the grow amount of the snake that collided with it
int Snake::FindGobblePoint(sf::Vector2f _gobbleSnakeHead) const {
	if (!m_dead) {
		int counter{ 0 };
		if (!m_segments.IsEmpty()) {
			auto* currentNode = m_segments.Back();
			for (int i = m_segments.Size(); i > 0; --i) {
				if (currentNode) {
					if (currentNode->m_data.first == _gobbleSnakeHead) {
						return counter;
					}
					currentNode = currentNode->m_previousNode;
					++counter;
				} else {
					return -1;
				}
			}
		}
	}return -1;
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
ECollisionType Snake::CheckCollisions() {
	if (CheckCollisionsAgainstSelf()) {
		Collision(ECollisionType::eSelf);
		return ECollisionType::eSelf;
	}
	if (CheckCollisionsAgainstFood()) {
		Collision(ECollisionType::eFood);
		return ECollisionType::eFood;
	}if (CheckCollisionsAgainstOtherSnakes()) {
		return ECollisionType::eSnake;
	}
	return ECollisionType::eNone;
}

bool Snake::CheckCollisionsAgainstSelf() const {
	if (m_direction != EDirection::eNone && !m_segments.IsEmpty()) {
		auto* currentNode = m_segments.Front();
		for (int i = 0; i < m_segments.Size(); ++i) {
			if (i != 0) {
				if (currentNode->m_data.first == m_position && !IsDead()) {
					return true;
				}
			}
			currentNode = currentNode->m_nextNode;
		}
	}

	return false;
}

bool Snake::CheckCollisionsAgainstFood() {
	//Check Against Food
	for (auto& food : m_food) {
		if (food->GetPosition() == m_position) {
			m_lastFood = food;
			return true;
		}
	}
	return false;
}

bool Snake::CheckCollisionsAgainstOtherSnakes() {
	//Check against other snakes
	for (auto* otherSnake : m_otherSnakes) {
		if (!otherSnake->IsDead() && otherSnake != this) {
			//Check each segment of THIS snake against the heads of the other snakes
			auto currentSegment = m_segments.Front();
			for (int i{ 0 }; i < m_segments.Size(); ++i) {
				if (currentSegment->m_data.first == otherSnake->GetHeadPosition()) {
					//if it's a head on collision then both snakes die
					if (m_position == currentSegment->m_data.first) {
						//If it's gobble mode, the entire other snake gets eaten
						if (m_gobbleMode) {
							Grow(static_cast<const int>((otherSnake->GetSnakeSegments().Size())));
							m_soundManager.PlaySFX("sfx_gobble_eat");
							otherSnake->Collision(ECollisionType::eSnake);
							return true;
						}
						Collision(ECollisionType::eSnake);
						otherSnake->Collision(ECollisionType::eSnake);
						return true;
					}
					otherSnake->Collision(ECollisionType::eSnake);
				}
				currentSegment = currentSegment->m_nextNode;
			}

			//Check if the snake has hit another snake's body
			auto otherSegment = otherSnake->GetSnakeSegments().Front();
			for (int i{ 0 }; i < otherSnake->GetSnakeSegments().Size(); ++i) {
				if (otherSegment->m_data.first == m_position) {
					//If it's gobble mode, make sure not to kill the player on collision
					if (m_gobbleMode) {
						const int growShrinkAmount{ otherSnake->FindGobblePoint(m_position) };
						if (growShrinkAmount != -1) {
							Grow(growShrinkAmount);
							m_soundManager.PlaySFX("sfx_gobble_eat");
							otherSnake->Shrink(growShrinkAmount);
							return true;
						}
					} else {
						Collision(ECollisionType::eSnake);
						return true;
					}
				}
				otherSegment = otherSegment->m_nextNode;
			}
		}
	}
	return false;
}

void Snake::Collision(const ECollisionType _collisionType) {
	if (!m_dead) {
		if (_collisionType == ECollisionType::eWall
			|| _collisionType == ECollisionType::eSnake
			|| _collisionType == ECollisionType::eSelf) {
			m_dead = true;
			m_gobbleMode = false;
			m_soundManager.PlaySFX("sfx_snake_death");
		}
		if (_collisionType == ECollisionType::eFood) {
			switch (m_lastFood->GetType()) {
			case EFoodType::eStandard:
				m_soundManager.PlaySFX("sfx_food_standard");
				break;

			case EFoodType::eSpecial:
				m_soundManager.PlaySFX("sfx_food_special");
				break;

			case EFoodType::eGobble:
				m_gobbleMode = true;
				m_soundManager.PlaySFX("sfx_gobble_on");
				break;

			}
			const int growAmount{ m_lastFood->GetGrowAmount() };
			Grow(growAmount);
		}
	}
}
