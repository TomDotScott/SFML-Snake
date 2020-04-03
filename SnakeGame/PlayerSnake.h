#pragma once
#include "Snake.h"
class PlayerSnake :
	public Snake {
public:
	PlayerSnake();
	void SetDirection(const EDirection& _direction) { m_direction = _direction; }
};