#include "Game.h"
#include <iostream>
/* TO DO
VIRTUAL SNAKE ON SNAKECOLLISION
UPDATE AND THEN RENDER
CHANGE VS SETTINGS
*/
Game::Game(sf::RenderWindow& window, sf::Font& font) : m_window(window), m_font(font) {
	auto* playerSnake = new PlayerSnake();
	m_snakes.push_back(playerSnake);

	//populate the food array
	for (auto& i : m_foodArray) {
		Food* food = new Food();
		i = food;
	}

	//populate the snake Vector
	for (int i = 0; i < Constants::k_AISnakeAmount; ++i) {
		std::cout << "AI SNAKE CREATED" << std::endl;
		m_snakes.push_back(new AISnake());
	}

	//populate the score UI
	for(unsigned int i = 0; i < m_snakes.size(); ++i)
	{
		sf::Text playerText;
		playerText.setFont(font);
		std::string textToDisplay = "Player";
		textToDisplay += std::to_string(i + 1) + ":";
		playerText.setString(textToDisplay);
		playerText.setFillColor(sf::Color::White);
		playerText.setCharacterSize(25);

		//Work out where they will be positioned
		playerText.setPosition(sf::Vector2f(Constants::k_screenWidth - 175, (i * Constants::k_gridSize) + 10));
		m_scores.push_back(playerText);
	}

	//configure Gobble mode text
	m_gobbleModeText.setFont(font);
	m_gobbleModeText.setString("GOBBLE MODE!");
	m_gobbleModeText.setCharacterSize(15);
	m_gobbleModeText.setFillColor(sf::Color::Yellow);
	m_gobbleModeText.setPosition(Constants::k_screenWidth - 175, Constants::k_screenHeight - 200);

	
	//make the snakes know where food is on the screen
	for (auto* snake : m_snakes)
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
	}

	for (auto* snake : m_snakes)
	{
		delete snake;
	}


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
			}
			//Check against other snakes
			for (auto* otherSnake : m_snakes) {
				if (!otherSnake->IsDead() && (otherSnake != currentSnake)) {
					//Check each segment of the snake against the heads of the other snakes
					for (auto& snakeSegment : currentSnake->GetSnakeSegments()) {
						if (snakeSegment == otherSnake->GetHeadPosition()) {
							otherSnake->Collision(ECollisionType::e_snake);
							return;
						}
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
						}
					}
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
		for (const Food* food : m_foodArray) {
			//make sure the food isn't getting compared to itself!
			if (*food != *foodToRandomise) {
				if (foodToRandomise->GetPosition() != food->GetPosition()) {
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

void Game::UpdateScores()
{
	for(unsigned int i = 0; i < m_snakes.size(); ++i)
	{
		std::string textToDisplay = "Player" + std::to_string(i + 1) + ":" + std::to_string(m_snakes[i]->GetScore());
		m_scores[i].setString(textToDisplay);
	}
}


void Game::Play()
{
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


		while (clock.getElapsedTime() >= sf::milliseconds(250)) {

			// We must clear the window each time around the loop
			m_window.clear();
			CheckCollisions();
			Update();

			// Get the window to display its contents
			m_window.display();
			clock.restart();
		}
	}

	std::cout << "SnakeGame: Finished" << std::endl;
}

void Game::Update() {
	bool gobble{ false };
	
	//GOBBLE MODE. After a random amount of time, stop Gobble Mode
	if (rand() % 25 == 0) {
		for (auto* snake : m_snakes) {
			if (!snake->IsDead() && snake->GetIsGobbleMode()) {
				std::cout << "GOBBLE MODE OVER" << std::endl;
				snake->SetIsGobbleMode(false);
				break;
			}
		}
	}

	for (Food* food : m_foodArray) {
		food->Render(m_window);
	}


	for (auto* snake : m_snakes)
	{
		if(snake->GetIsGobbleMode())
		{
			gobble = true;
		}
		snake->Update(m_window);
	}

	//Draw the Walls
	m_window.draw(m_topWall.m_wall);
	m_window.draw(m_bottomWall.m_wall);
	m_window.draw(m_leftWall.m_wall);
	m_window.draw(m_rightWall.m_wall);

	UpdateScores();
	//Draw the score UI
	for(const auto& score : m_scores)
	{
		m_window.draw(score);
		if(gobble)
		{
			m_window.draw(m_gobbleModeText);
		}
	}

}

void Game::Input() const
{
	//access the player's input function
	for (auto* snake : m_snakes)
	{
		auto* playerSnake = dynamic_cast<PlayerSnake*>(snake);
		if (playerSnake)
		{
			playerSnake->Input();
			return;
		}
	}
}