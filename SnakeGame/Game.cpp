#include "Game.h"
#include <iostream>
/* TO DO
MAKE ARRAY OF SNAKE* INCLUDING THE PLAYER AND AI TO CLEAN UP COLLISIONS
VIRTUAL SNAKE ON SNAKE COLLISION
MOVE WINDOW INTO GAME
USE CONST INTO FUNCTIONS AND METHODS
UPDATE AND THEN RENDER
MAKE BRACKETS CONSISTENT
CHANGE VS SETTINGS
*/
Game::Game(sf::RenderWindow& window) : m_window(window) {
	m_playerSnake = new PlayerSnake();
	//populate the food array
	for (auto& i : m_foodArray) {
		Food* food = new Food();
		i = food;
	}

	//populate the AISnake Vector
	for (int i = 0; i < Constants::k_AISnakeAmount; ++i) {
		std::cout << "AI SNAKE CREATED" << std::endl;
		m_AISnakes.push_back(new AISnake(i));
	}

	//Make each AI snake have a pointer to each other
	for (unsigned int snakePosition{ 0 }; snakePosition < m_AISnakes.size(); ++snakePosition) {
		for (AISnake* aiSnakeToAdd : m_AISnakes) {
			if (snakePosition != static_cast<unsigned int>(aiSnakeToAdd->GetPlayerNumber())) {
				m_AISnakes[snakePosition]->SetOtherSnakes(aiSnakeToAdd);
				for (Food* food : m_foodArray) {
					aiSnakeToAdd->SetFood(food);
				}
			}
		}
	}

	for(auto* snake : m_snakes)
	{
		for (auto* food : m_foodArray)
		{
			snake->SetFood(food);
		}
	}
}

Game::~Game() {
	for (Food* food : m_foodArray) {
		delete food;
		food = nullptr;
	}
	delete m_foodArray;

	delete m_playerSnake;

	//m_AISnakes
}

<<<<<<< Updated upstream
void Game::CheckCollisions() {
	//Check player against Walls
	if (!m_playerSnake->GetIsDead() && (m_playerSnake->GetHeadPosition().x == m_leftWall.m_position.x ||
		m_playerSnake->GetHeadPosition().x == m_rightWall.m_position.x ||
		m_playerSnake->GetHeadPosition().y == m_topWall.m_position.y ||
		m_playerSnake->GetHeadPosition().y == m_bottomWall.m_position.y)) {
		m_playerSnake->Collision(ECollisionType::e_wall);
	}

	//Check Against Food
	for (Food* food : m_foodArray) {
		//only one collision can happen per snake
		for (AISnake* aiSnake : m_AISnakes) {
			if (!aiSnake->GetIsDead() && food->GetPosition() == aiSnake->GetHeadPosition()) {
				aiSnake->Collision(food);
				RandomiseFood(food);
				aiSnake->FindFood();
				return;
			}
		}
		//Check the player against food
		if (food->GetPosition() == m_playerSnake->GetHeadPosition()) {
			m_playerSnake->Collision(food);
			food->Randomise();
			for (AISnake* aiSnake : m_AISnakes) {
				aiSnake->FindFood();
=======
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

		while (clock.getElapsedTime() >= sf::milliseconds(250)) {
			// We must clear the window each time around the loop
			m_window.clear();
			Update();

			// Get the window to display its contents
			m_window.display();
			clock.restart();
		}
		
		//input and collisions should be done outside of the game tick
		Input();
		CheckCollisions();
	}

	std::cout << "SnakeGame: Finished" << std::endl;
}


void Game::CheckCollisions() {
	for (auto* currentSnake : m_snakes) {
		//only check collisions if the snake is alive
		if (!currentSnake->IsDead()) {
			//Check against Walls
			if (currentSnake->GetHeadPosition().x == m_leftWall.m_position.x ||
				currentSnake->GetHeadPosition().x == m_rightWall.m_position.x ||
				currentSnake->GetHeadPosition().y == m_topWall.m_position.y ||
				currentSnake->GetHeadPosition().y == m_bottomWall.m_position.y) {
				currentSnake->Collision(ECollisionType::e_wall);
				return;
			}

			//Check Against Food
			for (auto* food : m_foodArray) {
				if (food->GetPosition() == currentSnake->GetHeadPosition()) {
					currentSnake->Collision(food);
					RandomiseFood(food);
					return;
				}
>>>>>>> Stashed changes
			}
			return;
		}
<<<<<<< Updated upstream
	}
	//Check against other snakes
	for (AISnake* aiSnake : m_AISnakes) {
		for (sf::Vector2f& playerSegment : m_playerSnake->GetSnakeSegments()) {
			if (!aiSnake->GetIsDead() && !m_playerSnake->GetIsDead()) {//Checks if an AI snake hits the player's body
				if (playerSegment == aiSnake->GetHeadPosition()) {
					aiSnake->Collision(ECollisionType::e_snake);
					//return;
				}
				//Check if the player hits an AI Snake's body
				for (sf::Vector2f& aiSegment : aiSnake->GetSnakeSegments()) {
					if (aiSegment == m_playerSnake->GetHeadPosition()) {
						//If it's gobble mode, make sure not to kill the player on collision
						if (m_playerSnake->GetIsGobbleMode()) {
							const int growShrinkAmount{ aiSnake->FindGobblePoint(m_playerSnake->GetHeadPosition()) };
							m_playerSnake->Grow(growShrinkAmount);
							aiSnake->Shrink(growShrinkAmount);
							//return;
=======
		//Check against other snakes
		for (auto* otherSnake : m_snakes) {
			if (!otherSnake->IsDead() && (otherSnake != currentSnake)) {
				//Check each segment of the snake against the heads of the other snakes
				for (auto& snakeSegment : currentSnake->GetSnakeSegments()) {
					if (snakeSegment == otherSnake->GetHeadPosition()) {
						otherSnake->Collision(ECollisionType::e_snake);
						return;
					}
					//Check if the snake has hit another snake's body
					for (auto& otherSegment : otherSnake->GetSnakeSegments()) {
						if (otherSegment == currentSnake->GetHeadPosition()) {
							//If it's gobble mode, make sure not to kill the player on collision
							if (currentSnake->GetIsGobbleMode()) {
								const int growShrinkAmount{ otherSnake->FindGobblePoint(currentSnake->GetHeadPosition()) };
								currentSnake->Grow(growShrinkAmount);
								otherSnake->Shrink(growShrinkAmount);
								return;
							}
							else {
								currentSnake->Collision(ECollisionType::e_snake);
								return;
							}
>>>>>>> Stashed changes
						}
						m_playerSnake->Collision(ECollisionType::e_snake);
						//return;
					}
<<<<<<< Updated upstream
				}
				//If head on collisions, then both die
				//If gobble mode, the snake eats the entire snake
				if (m_playerSnake->GetHeadPosition() == aiSnake->GetHeadPosition()) {
					if (m_playerSnake->GetIsGobbleMode()) {
						m_playerSnake->Grow((aiSnake->GetSnakeSegments().size()));
						aiSnake->Collision(ECollisionType::e_snake);
						//return;
=======
					//If head on collisions, then both die
					//If gobble mode, the snake eats the entire snake
					if (currentSnake->GetHeadPosition() == otherSnake->GetHeadPosition()) {
						if (currentSnake->GetIsGobbleMode()) {
							currentSnake->Grow((otherSnake->GetSnakeSegments().size()));
							otherSnake->Collision(ECollisionType::e_snake);
							return;
						}
						//currentSnake->Collision(ECollisionType::e_snake);
						//otherSnake->Collision(ECollisionType::e_snake);
						return;
>>>>>>> Stashed changes
					}
					m_playerSnake->Collision(ECollisionType::e_snake);
					aiSnake->Collision(ECollisionType::e_snake);
					//return;
				}
			}
		}
		//Check AI Collisions with Other snakes
		aiSnake->CheckCollision();
		//Check AI collisions with the Walls
		if (!aiSnake->GetIsDead() && (aiSnake->GetHeadPosition().x == m_leftWall.m_position.x ||
			aiSnake->GetHeadPosition().x == m_rightWall.m_position.x ||
			aiSnake->GetHeadPosition().y == m_topWall.m_position.y ||
			aiSnake->GetHeadPosition().y == m_bottomWall.m_position.y)) {
			aiSnake->Collision(ECollisionType::e_wall);
			//return;
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
	//GOBBLE MODE. After a random amount of time, stop Gobble Mode
	if (rand() % 10 == 0) {
<<<<<<< Updated upstream
		//Check player first
		if (m_playerSnake->GetIsGobbleMode() && !m_playerSnake->GetIsDead()) {
			std::cout << "GOBBLE MODE OVER" << std::endl;

			m_playerSnake->SetIsGobbleMode(false);
		}
		else {
			//reset the AI snakes
			for (AISnake* aiSnake : m_AISnakes) {
				if (!aiSnake->GetIsDead() && aiSnake->GetIsGobbleMode()) {
					std::cout << "GOBBLE MODE OVER" << std::endl;

					aiSnake->SetIsGobbleMode(false);
				}
=======
		for(auto* snake : m_snakes) {
			if (!snake->IsDead() && snake->GetIsGobbleMode()) {
				std::cout << "GOBBLE MODE OVER" << std::endl;
				snake->SetIsGobbleMode(false);
>>>>>>> Stashed changes
			}
		}
	}

	for (Food* food : m_foodArray) {
		food->Render(m_window);
	}


	for (AISnake* aiSnake : m_AISnakes) {
		//only move if alive
<<<<<<< Updated upstream
		if (!aiSnake->GetIsDead()) {
			aiSnake->ChooseDirection();
			aiSnake->Update(m_window);
=======
		if (!snake->IsDead()) {
			snake->Update(m_window);
>>>>>>> Stashed changes
		}
	}

	m_playerSnake->Update(m_window);

	//Draw the Walls
	m_window.draw(m_topWall.m_wall);
	m_window.draw(m_bottomWall.m_wall);
	m_window.draw(m_leftWall.m_wall);
	m_window.draw(m_rightWall.m_wall);

}

void Game::Input() const
{
<<<<<<< Updated upstream
	m_playerSnake->Input();
=======
	//access the player's input function
	for(auto* snake : m_snakes)
	{
		auto* playerSnake = dynamic_cast<PlayerSnake*>(snake);
		if(playerSnake)
		{
			playerSnake->Input();
		}
	}
>>>>>>> Stashed changes
}