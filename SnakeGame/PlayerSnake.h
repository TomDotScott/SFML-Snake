#pragma once
#include "Snake.h"
class PlayerSnake : public Snake {
public:
	explicit PlayerSnake(const std::string& _player);
	void SetDirection(const EDirection& _direction) { m_direction = _direction; }
};