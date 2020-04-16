#pragma once
#include "Snake.h"
/**
 * \brief Generates an AI Snake that uses an adapted version of Dijkstra's algorithm to find its way to food on the screen
 */
class AISnake final : public Snake {
public:
	/**
	 * \brief Constructs an AI snake to play the Snake Game
	 * \param _soundManager Plays sound effects when triggered
	 * \param _foodArray The array of the food on screen to help with collision and path-finding
	 */
	explicit AISnake(SoundManager& _soundManager, std::array<Food*, constants::k_foodAmount>& _foodArray);

	void Update() override;
	
	/**
	 * \brief Changes direction of the snake based on two factors:\n 1.The snake's position compared to its chosen target destination,\n 2.If there is another snake or a wall directly in its way
	 */
	void ChooseDirection();
private:
	/**
	 * \brief The path-finding algorithm considers 4 things:\n 1. The closest food\n 2. The food with the highest point value\n 3. If there is a preemptive snake blocking its path\n 4. If it's gobble mode, the closest snake
	 */
	void FindTarget();

	/**
	 * \brief Finds the closest food to the snake and sets it as the target to move towards
	 */
	void FindClosestFood();

	/**
	 * \brief Finds the closest snake to the snake and sets it as the target to move toward
	 */
	void FindClosestSnake();

	/**
	 * \brief Finds the food with the highest point value and sets it as the target to move towards
	 */
	void FindHighestFood();

	/**
	 * \brief Checks if an item is in the same position as one of the segments of the snake
	 * \param _position the position onscreen to evaluate
	 * \return true if the item is overlapping with one the AI Snake's segments
	 */
	bool IsOverlapping(sf::Vector2f _position) const;

	/**
	 * \brief Checks if there is a snake in the way to the food
	 * \return true if there is a snake on the same x or y axis as this snake
	 */
	bool IsSnakeInWay() const;
	
	/**
	 * \brief Check if the snake's body is in the way to allow the snake to make tight turns
	 * \param _direction The current direction the snake is traveling in
	 * \return true if the snake is blocking its own path
	 */
	bool IsSelfInWay(EDirection& _direction) const;

	//True if the AI has made a decision
	bool m_hasMoved{ false };

	//The front of the list is target the snake is going to move toward
	List m_targetList{};
};
