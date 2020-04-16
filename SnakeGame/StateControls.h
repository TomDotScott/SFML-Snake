#pragma once
#include "StateManager.h"

/**
 * \brief The StateControls Class is the Controls Screen that is shown to the player before playing the game in single player
 */
class StateControls : public BaseState {
public:
	/**
	 * \brief Constructs a StateControls object
	 * \param _soundManager A reference to the sound manager to play sound effects and music
	 */
	StateControls(SoundManager& _soundManager) : BaseState(_soundManager) {};

	/**
	 * \brief Called upon the creation of the object
	 * \param _window a reference to the game window
	 * \param _font the font that will be used in the game
	 */
	void OnCreate(sf::RenderWindow& _window, sf::Font& _font) override;

	/**
	 * \brief Update is called once per game loop
	 * \param _window a reference to the game window
	 */
	void Update(sf::RenderWindow& _window) override;

	/**
	 * \brief Draws renderables to the window
	 * \param _window a reference to the game window
	 */
	void Render(sf::RenderWindow& _window) override;
private:

	/**
	 * \brief FoodIcon is a container for the Food Icons that are displayed in the Controls Menu
	 */
	struct FoodIcon {
		/**
		 * \brief Constructs a FoodIcon object
		 * \param _texture A reference to the texture to be displayed
		 * \param _position The position of the FoodIcon
		 */
		FoodIcon(const sf::Texture& _texture, const sf::Vector2f& _position) : m_texture(_texture), m_position(_position) {
			m_sprite.setTexture(m_texture);
			m_sprite.setPosition(m_position);
		}

		/**
		 * \brief Sets the position of the FoodIcon
		 * \param _newPosition The new position of the FoodIcon object
		 */
		void SetPosition(const sf::Vector2f _newPosition) { m_sprite.setPosition(_newPosition); }

		/**
		 * \brief Draws the FoodIcon to the screen
		 * \param _window A reference to the game window
		 */
		void Render(sf::RenderWindow& _window) const {
			_window.draw(m_sprite);
		}

		sf::Sprite m_sprite;
		sf::Texture m_texture;
		sf::Vector2f m_position;
	};

	sf::Texture m_gobbleTexture, m_specialTexture, m_standardTexture;

	MenuBackground m_menuBackground;

	UIText m_textLine1to3{ "Use WASD or the Arrow keys to move your snake\n\nYou have 90 seconds to eat as much food as you can\n\nEating food gives you more points, but it also makes you grow!", sf::Color::White,
		{static_cast<float>(constants::k_screenWidth) / 2.f, 100}, m_font, 16 };

	UIText m_textLine4to7{ "Gives you +10 points and grows you by 1 unit\n\nGives you + 30 points and grows you by 3 units\n\nGives you + 50 points and grows you by 5 units\n\nAlso grants you GOBBLE MODE. You earn DOUBLE points", sf::Color::White,
		{static_cast<float>(constants::k_screenWidth) / 2.f + 25, m_textLine1to3.m_position.y + 132}, m_font, 16 };

	UIText m_textLine8toEnd{ "and you can eat other snakes\n\nBeware because if a CPU gets GOBBLE MODE, they will go\n\nout of their way to eat YOU", sf::Color::White,
		{static_cast<float>(constants::k_screenWidth) / 2.f, m_textLine4to7.m_position.y + 132}, m_font, 16 };


	UIText m_play{ "Play", sf::Color::White,
		{static_cast<float>(constants::k_screenWidth) / 2.f, 550 }, m_font, constants::k_uiTextElement };

	UIText m_main{ "Main Menu", sf::Color::White,
		{static_cast<float>(constants::k_screenWidth) / 2.f, 650 }, m_font, constants::k_uiTextElement };

	std::vector<UIText*> m_textToRender{
		&m_textLine1to3, &m_textLine4to7, &m_textLine8toEnd, &m_play, &m_main
	};
};

