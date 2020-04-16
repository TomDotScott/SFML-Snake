#pragma once
#include "SFML/Graphics.hpp"

/**
 * \brief The Entity Parent Class. Anything interactive in the game is a member of this class
 */
class Entity {
public:
	/**
	 * \brief Constructs an entity
	 * \param _position The position of the entity in the world-space
	 */
	explicit Entity(sf::Vector2f _position = sf::Vector2f(0, 0));
	
	/**
	 * \brief Destroys the Entity
	 */
	virtual ~Entity() = default;
	
	/**
	 * \brief Renders the Entity to the screen
	 * \param window The window to render to;
	 */
	virtual void Render(sf::RenderWindow& window) = 0;
	virtual void Move(){}
protected:
	/**
	 * \brief A random number generator within a range (inclusive)
	 * \param _min The minimum number
	 * \param _max The maximum number
	 * \return 
	 */
	static int RandomRange(const int _min, const int _max);
	
	/**
	 * \brief Randomises the position of the Entity on screen
	 */
	void RandomisePosition();

	/**
	 * \brief The Entity's position in world-space
	 */
	sf::Vector2f m_position;

	
	/**
	 * \brief The sprite
	 */
	sf::Sprite m_sprite;
};

