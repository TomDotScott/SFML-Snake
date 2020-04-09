#include "PlayerSnake.h"

PlayerSnake::PlayerSnake(const std::string& _player) {
	RandomisePosition();

	m_segments.PushBack(m_position, m_direction);
	m_segments.PushBack(sf::Vector2f(m_position.x, (m_position.y)), m_direction);
	m_segments.PushBack(sf::Vector2f(m_position.x - constants::k_gameGridCellSize, (m_position.y)), m_direction);

	if (_player == "Player 1") {
		//load the textures
		m_headTexture.loadFromFile("Resources/Graphics/Snake_Player_Head.png");
		m_bendTexture.loadFromFile("Resources/Graphics/Snake_Player_Bend.png");
		m_bodyTexture.loadFromFile("Resources/Graphics/Snake_Player_Body.png");
		m_tailTexture.loadFromFile("Resources/Graphics/Snake_Player_Tail.png");
		m_scaredTexture.loadFromFile("Resources/Graphics/Snake_Player_Scared.png");
	} else {
		m_headTexture.loadFromFile("Resources/Graphics/Snake_AI_Head.png");
		m_bendTexture.loadFromFile("Resources/Graphics/Snake_AI_Bend.png");
		m_bodyTexture.loadFromFile("Resources/Graphics/Snake_AI_Body.png");
		m_tailTexture.loadFromFile("Resources/Graphics/Snake_AI_Tail.png");
		m_scaredTexture.loadFromFile("Resources/Graphics/Snake_AI_Scared.png");
	}
}
