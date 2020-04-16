#pragma once
#include <array>

#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "Food.h"
#include "List.h"
#include "SoundManager.h"

//To deal with collisions in the game
/**
 * \brief The Types of collision in the game - Wall, Snake, Self, Food, and None
 */
enum class ECollisionType {
	eWall, eSnake, eSelf, eFood, eNone
};


/**
 * \brief The parent class for AI and Player snakes. Contains the core features needed to play the game
 */
class Snake : public Entity {
public:
	/**
	 * \brief Constructs a Snake object
	 * \param _soundManager Plays sound effects when triggered
	 * \param _foodArray The food on screen to help with collision
	 */
	explicit Snake(SoundManager& _soundManager, std::array<Food*, constants::k_foodAmount>& _foodArray);

	virtual void Update();


	/**
	 * \brief Renders each segment to the screen
	 * \param _window The game window
	 */
	void Render(sf::RenderWindow& _window) override final;

	/**
	 * \brief Grows the snake by a specified amount
	 * \param _amount The amount to grow by
	 */
	void Grow(const int _amount);

	/**
	 * \brief Shrinks the snake by a specified amount
	 * \param _amount The amount to shrink by
	 */
	void Shrink(const int _amount);

	/**
	 * \brief Deals with collisions of all types
	 * \param _collisionType The type of collision that has occured
	 */
	void Collision(const ECollisionType _collisionType);

	/**
	 * \return The co-ordinates of the head of the snake
	 */
	sf::Vector2f GetHeadPosition() const { return m_position; }

	/**
	 * \brief Calculates how much to shrink this snake and grow the other snake if a snake with Gobble Mode active has collided with it
	 * \param _gobbleSnakeHead The co-ordinates of the other snake's head
	 * \return The amount to shrink this snake by
	 */
	int FindGobblePoint(sf::Vector2f _gobbleSnakeHead) const;

	/**
	 * \return true if the snake is in Gobble Mode
	 */
	bool GetIsGobbleMode() const { return m_gobbleMode; }

	/**
	 * \brief Sets the Gobble Mode trigger on the snake
	 * \param _isGobbleMode The state of Gobble Mode
	 */
	void SetIsGobbleMode(const bool& _isGobbleMode) { m_gobbleMode = _isGobbleMode; }

	/**
	 * \return The current score of the snake
	 */
	int GetScore() const { return m_score; }


	/**
	 * \brief Sets the vector of snakes
	 * \param _otherSnakes The vector of snakes
	 */
	void SetOtherSnakes(std::vector<Snake*>& _otherSnakes) { m_otherSnakes = _otherSnakes; }


	/**
	 * \return true if the snake is dead
	 */
	bool IsDead() const { return m_dead; }

	/**
	 * \return The direction that the snake is moving in
	 */
	EDirection GetDirection() const { return m_direction; }

	/**
	 * \brief Checks collisions in 4 ways:\n 1. Collisions against Walls\n 2. Collisions against itself\n 3. Collisions against food\n 4. Collisions against other snakes
	 * \return the type of collision that occured
	 */
	ECollisionType CheckCollisions();

	/**
	 * \return The list of segments that make up the snake
	 */
	List GetSnakeSegments() const { return m_segments; }

	Food* GetLastFood() const { return m_lastFood; }
protected:
	/**
	 * \brief The last food that the snake collided with
	 */
	Food* m_lastFood{ nullptr };

	/**
	 * \brief Evaluates if a snake has collided with itself
	 * \return true if the snake has hit itself
	 */
	bool CheckCollisionsAgainstSelf() const;

	/**
	 * \brief Evaluates if a snake has collided with food
	 * \return true if the snake has hit food
	 */
	bool CheckCollisionsAgainstFood();

	/**
	 * \brief Evaluates if a snake has hit another snake
	 * \return true if the snake has hit another snake
	 */
	bool CheckCollisionsAgainstOtherSnakes();

	void Move() override;

	/**
	 * \brief The current direction that the snake is traveling in
	 */
	EDirection m_direction{ EDirection::eRight };

	/**
	 * \brief A doubly-linked list containing the segments that make up the snake
	 */
	List m_segments;

	/**
	 * \brief a trigger for whether Gobble Mode is active
	 */
	bool m_gobbleMode{ false };

	/**
	 * \brief A trigger for whether the snake is dead
	 */
	bool m_dead{ false };

	/**
	 * \brief The current score of the snake
	 */
	int m_score{ 0 };

	/**
	 * \brief Triggers sound effects for the snake
	 */
	SoundManager& m_soundManager;

	/**
	 * \brief A store of all of the other snakes on screen for collision detection
	 */
	std::vector<Snake*> m_otherSnakes;

	/**
	 * \brief A store of all of the food on screen for collision detection
	 */
	std::array<Food*, constants::k_foodAmount> m_food{};

	//The textures...
	sf::Texture m_headTexture;
	sf::Texture m_scaredTexture;
	sf::Texture m_bendTexture;
	sf::Texture m_bodyTexture;
	sf::Texture m_tailTexture;

	//For Gobble Mode
	sf::Texture m_gobbleHeadTexture;
	sf::Texture m_gobbleBendTexture;
	sf::Texture m_gobbleBodyTexture;
	sf::Texture m_gobbleTailTexture;
};