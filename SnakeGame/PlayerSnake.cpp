#include "PlayerSnake.h"

PlayerSnake::PlayerSnake() {
	m_colour = sf::Color::Red;

	RandomisePosition();

	m_segments.PushBack(m_position);
	m_segments.PushBack(sf::Vector2f(m_position.x, (m_position.y)));
	m_segments.PushBack(sf::Vector2f(m_position.x - Constants::k_gameGridCellSize, (m_position.y)));


	//load the textures
	m_headTexture.loadFromFile("Resources/Graphics/Snake_Player_Head.png");
	m_bodyTexture.loadFromFile("Resources/Graphics/Snake_Player_Body.png");
	m_tailTexture.loadFromFile("Resources/Graphics/Snake_Player_Tail.png");
	m_deadTexture.loadFromFile("Resources/Graphics/Snake_Player_Dead.png");
}