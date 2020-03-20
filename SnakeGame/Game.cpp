#include "Game.h"
#include <iostream>
/* TO DO
MAKE ARRAY OF SNAKE* INCLUDING THE PLAYER AND AI TO CLEAN UP COLLISIONS
VIRTUAL SNAKE ON SNAKE COLLISION
MOVE WINDOW INTO GAME
USE CONST INTO FUNCTIONS AND METHODS
UPDATE AND THEN RENDER
CHANGE VS SETTINGS
*/
Game::Game(sf::RenderWindow& window) : m_window(window) {
	//populate the food array
	for (auto& i : m_foodArray) {
		Food* food = new Food();
		i = food;
	}

	auto* playerSnake = new PlayerSnake();
	m_snakes.push_back(playerSnake);
	
	//populate the AISnakes in the vector
	for (int i = 0; i < Constants::k_AISnakeAmount; ++i) {
		std::cout << "AI SNAKE CREATED" << std::endl;
		m_snakes.push_back(new AISnake());
	}
}

Game::~Game() {
	for (Food* food : m_foodArray) {
		delete food;
		food = nullptr;
	}
	delete m_foodArray;

	for (auto* snake : m_snakes) {
		delete snake;
		snake = nullptr;
	}

	//m_AISnakes
}

void Game::Play() {
	sf::Clock clock;
	// We can still output to the console window
	std::cout << "SnakeGame: Starting" << std::endl;

	// Main loop that continues until we call window.close()
	while (m_window.isOpen()) {
		// Handle any pending SFML events
		// These cover keyboard, mouse,joystick etc.
		sf::Event event{};
		while (m_window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				m_window.close();
				break;
			default:
				break;
			}
		}

		//input and collisions should be done outside of the game tick
		Input();
		CheckCollisions();


		while (clock.getElapsedTime() >= sf::milliseconds(250)) {
			// We must clear the window each time around the loop
			m_window.clear();
			Update();

			// Get the window to display its contents
			m_window.display();
			clock.restart();
		}
	}

	std::cout << "SnakeGame: Finished" << std::endl;
}


void Game::CheckCollisions() {
	for (auto* snake : m_snakes) {
		//only check collisions if the snake is alive
		if (!snake->GetIsDead()) {
			//Check against Walls
			if (snake->GetHeadPosition().x == m_leftWall.m_position.x ||
				snake->GetHeadPosition().x == m_rightWall.m_position.x ||
				snake->GetHeadPosition().y == m_topWall.m_position.y ||
				snake->GetHeadPosition().y == m_bottomWall.m_position.y) {
				snake->Collision(ECollisionType::e_wall);
				return;
			}

			//Check Against Food
			for (auto* food : m_foodArray) {
				if (food->GetPosition() == snake->GetHeadPosition()) {
					snake->Collision(food);
					RandomiseFood(food);
					return;
				}
			}
		}
		//Check against other snakes
		for (auto* otherSnake : m_snakes) {
			if (!otherSnake->GetIsDead() && (otherSnake != snake)) {

				//Check each segment of the snake against the heads of the other snakes
				for (auto& snakeSegment : snake->GetSnakeSegments()) {
					if (snakeSegment == otherSnake->GetHeadPosition()) {
						otherSnake->Collision(ECollisionType::e_snake);
					}
					//Check if the snake has hit another snake's body
					for (auto& otherSegment : otherSnake->GetSnakeSegments()) {
						if (otherSegment == snake->GetHeadPosition()) {
							//If it's gobble mode, make sure not to kill the player on collision
							if (snake->GetIsGobbleMode()) {
								const int growShrinkAmount{ otherSnake->FindGobblePoint(snake->GetHeadPosition()) };
								snake->Grow(growShrinkAmount);
								otherSnake->Shrink(growShrinkAmount);
								return;
							}
							else {
								snake->Collision(ECollisionType::e_snake);
								return;
							}
						}
					}
					//If head on collisions, then both die
					//If gobble mode, the snake eats the entire snake
					if (snake->GetHeadPosition() == otherSnake->GetHeadPosition()) {
						if (snake->GetIsGobbleMode()) {
							snake->Grow((otherSnake->GetSnakeSegments().size()));
							otherSnake->Collision(ECollisionType::e_snake);
							return;
						}
						snake->Collision(ECollisionType::e_snake);
						otherSnake->Collision(ECollisionType::e_snake);
						return;
					}
				}
			}
		}
	}
}

void Game::RandomiseFood(Food* foodToRandomise)
{
	//Check that food doesn't spawn on top of each other
	bool isOverlapping = true;
	while (isOverlapping) {
		foodToRandomise->Randomise();
		//Check the randomised position
		for(const Food* food : m_foodArray) {
			//make sure the food isn't getting compared to itself!
			if(*food != *foodToRandomise) {
				if(foodToRandomise->GetPosition() != food->GetPosition()) {
					isOverlapping = false;
					break;
				}
			}
			else {
				foodToRandomise->Randomise();
			}
		}
	}
}

void Game::Update() {
	std::cout << m_snakes.size() << std::endl;

	//GOBBLE MODE. After a random amount of time, stop Gobble Mode
	if (rand() % 10 == 0) {
		for(auto* snake : m_snakes) {
			if (!snake->GetIsDead() && snake->GetIsGobbleMode()) {
				std::cout << "GOBBLE MODE OVER" << std::endl;
				snake->SetIsGobbleMode(false);
			}
		}
	}

	for (auto* food : m_foodArray) {
		food->Render(m_window);
	}

	for (auto* snake : m_snakes)
	{
		//only move if alive
		if (!snake->GetIsDead()) {
			snake->Update(m_window);
		}
	}

	//Draw the Walls
	m_window.draw(m_topWall.m_wall);
	m_window.draw(m_bottomWall.m_wall);
	m_window.draw(m_leftWall.m_wall);
	m_window.draw(m_rightWall.m_wall);

}

void Game::Input() const
{
	//m_snakes->Input();
}