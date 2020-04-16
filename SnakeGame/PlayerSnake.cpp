#include "PlayerSnake.h"

PlayerSnake::PlayerSnake(EPlayer _player, SoundManager& _soundManager, std::array<Food*, constants::k_foodAmount>& _foodArray) : Snake(_soundManager, _foodArray) {
	RandomisePosition();

	m_segments.PushBack({ m_position, m_direction });
	m_segments.PushBack({ sf::Vector2f(m_position.x, (m_position.y)), m_direction });
	m_segments.PushBack({sf::Vector2f(m_position.x - constants::k_gameGridCellSize, (m_position.y)), m_direction});

	switch (_player) {
		case EPlayer::ePlayerOne:
			m_headTexture.loadFromFile("Resources/Graphics/Snake_Player_Head.png");
			m_bendTexture.loadFromFile("Resources/Graphics/Snake_Player_Bend.png");
			m_bodyTexture.loadFromFile("Resources/Graphics/Snake_Player_Body.png");
			m_tailTexture.loadFromFile("Resources/Graphics/Snake_Player_Tail.png");
		break;

		case EPlayer::ePlayerTwo:
			m_headTexture.loadFromFile("Resources/Graphics/Snake_AI_Head.png");
			m_bendTexture.loadFromFile("Resources/Graphics/Snake_AI_Bend.png");
			m_bodyTexture.loadFromFile("Resources/Graphics/Snake_AI_Body.png");
			m_tailTexture.loadFromFile("Resources/Graphics/Snake_AI_Tail.png");
		break;

		default: break;
	}
}
