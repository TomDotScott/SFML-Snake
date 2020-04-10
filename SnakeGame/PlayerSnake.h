#pragma once
#include "Snake.h"
class PlayerSnake : public Snake {
public:
	explicit PlayerSnake(const std::string& _player, SoundManager& _soundManager);
	void SetDirection(const EDirection& _direction) { m_direction = _direction; }
};