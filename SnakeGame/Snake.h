#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "Food.h"
#include "List.h"
#include "SoundManager.h"

//To deal with collisions in the game
enum class ECollisionType {
	e_wall, e_snake, e_self, e_food
};

//Each part of the snake is a position vector called a Segment
struct Segment {
	Segment(const int _x, const int _y) : x(_x), y(_y) {
		sf::Vector2i(_x, _y);
	}
	int x;
	int y;
};

class Snake : public Entity {
public:
	Snake();

	void Grow(const int _amount);

	void Shrink(const int _amount);

	virtual void Update();
	
	void CheckCollisions();
	
	void CheckCollisionsAgainstSelf();
	
	void CheckCollisionsAgainstFood();
	
	void CheckCollisionsAgainstOtherSnakes();

	//for colliding with other snakes, itself and walls
	void Collision(ECollisionType _collisionType);

	//For colliding with pickups
	void Collision(Food* _food);

	sf::Vector2f GetHeadPosition() const { return m_position; }

	int FindGobblePoint(sf::Vector2f _gobbleSnakeHead) const;

	bool GetIsGobbleMode() const { return m_gobbleMode; }

	int GetScore() const { return m_score; }

	void SetIsGobbleMode(const bool& _isGobbleMode) { m_gobbleMode = _isGobbleMode; }

	void SetSoundManager(SoundManager* _soundManager) { m_soundManager = _soundManager; }
	
	void SetFood(Food* _food) { m_food.push_back(_food); }

	void SetOtherSnake(Snake* _snake) { m_otherSnakes.push_back(_snake); }

	bool IsDead() const { return m_dead; }

	void Render(sf::RenderWindow& _window) override final;

	EDirection GetDirection() const { return m_direction; }

	List GetSnakeSegments() const { return m_segments; }
protected:

	sf::Color m_gobbleColour{ sf::Color::Yellow };
	sf::Color m_defaultColour{ sf::Color::Red };

	EDirection m_direction{ EDirection::e_right };

	sf::RectangleShape m_rectangle;

	List m_segments;

	bool m_gobbleMode{ false };

	bool m_dead{ false };
	
	void Move() override;

	int m_score{ 0 };

	//A store of all of the food on screen to help with decision making
	std::vector<Food*> m_food;

	//A store of all of the other snakes on screen to help with decision making
	std::vector<Snake*> m_otherSnakes;

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

	//For SFX
	SoundManager* m_soundManager;
};