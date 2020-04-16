#pragma once
#include "Snake.h"

/**
 * \brief The State of the PlayerSnake; whether it is P1 (controlled by WASD) or P2 (controlled by the arrow keys)
 */
enum class EPlayer {
	ePlayerOne, ePlayerTwo
};

/**
 * \brief Generates a player-controlled snake that can be
 */
class PlayerSnake final : public Snake {
public:
	/**
	 * \brief Constructs a PlayerSnake object
	 * \param _player The state of the player; if it is P1 or P2
	 * \param _soundManager Plays sound effects when triggered
	 * \param _foodArray The food on screen to help with collision
	 */
	explicit PlayerSnake(const EPlayer _player, SoundManager& _soundManager, std::array<Food*, constants::k_foodAmount>& _foodArray);

	/**
	 * \brief Sets the direction of the PlayerSnake
	 * \param _direction The direction to move in
	 */
	void SetDirection(const EDirection& _direction) { m_direction = _direction; }
};

