#pragma once
#include "StateManager.h"

/**
 * \brief The StateMainMenu is the first menu that is displayed to the player 
 */
class StateMainMenu final : public BaseState {
public:
	/**
	 * \brief Constructs a MainMenu object
	 * \param _soundManager A reference to the sound manager to play sound effects and music
	 */
	StateMainMenu(SoundManager& _soundManager) : BaseState(_soundManager) {};

	/**
	 * \brief Called upon the creation of the object. Initialises State objects further than their respective Constructors
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
	UIText m_title{ "Snake!", sf::Color::White,
		{static_cast<float>(constants::k_screenWidth) / 2.f, static_cast<float>(constants::k_screenHeight) / 5.f},
		m_font, 128 };

	UIText m_playSinglePlayer{ "1 Player", sf::Color::White,
		{static_cast<float>(constants::k_screenWidth) / 2, 450},
		m_font, constants::k_uiTextElement };

	UIText m_playTwoPlayer{ "2 Player", sf::Color::White,
		{m_playSinglePlayer.m_position.x, m_playSinglePlayer.m_position.y + 100},
		m_font, constants::k_uiTextElement };

	UIText m_quit{ "Quit", sf::Color::White,
	{m_playSinglePlayer.m_position.x, m_playSinglePlayer.m_position.y + 200},
		m_font, constants::k_uiTextElement };

	//MUSIC LINK - https://youtu.be/0nO2lHSlXN0
	UIText m_copyright{ "All artwork made by Thomas Scott\nMusic is Royalty and Copyright Free by Paul Caveworks on Youtube",
	sf::Color::White,
	{constants::k_gameGridCellSize * 10 + 10, constants::k_screenHeight - 2 * constants::k_gameGridCellSize - 10},
	m_font, constants::k_gameGridCellSize / 2 };

	std::vector<UIText*> m_textToRender{
		&m_title, &m_playSinglePlayer, &m_playTwoPlayer, &m_quit, &m_copyright
	};

	MenuBackground m_menuBackground;

	//deal with user selections
	int m_selected{ 0 };
};

