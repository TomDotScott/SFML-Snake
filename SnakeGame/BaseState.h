#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include "Constants.h"
#include "SoundManager.h"

/**
 * \brief The BaseState Class is the parent class for all of the states in the game
 * It defines the behaviours that each state needs to have:
 * 1. Be created
 * 2. Update
 * 3. Render to the screen
 * It also contains all of the data needed for each state
 */
class BaseState {
public:
	/**
	 * \brief Constructs a BaseState object
	 * \param _soundManager A reference to the sound manager to play sound effects and music
	 */
	explicit BaseState(SoundManager& _soundManager) : m_soundManager(_soundManager){};
	
	/**
	 * \brief Destroys the BaseState object
	 */
	virtual ~BaseState() = default;

	
	/**
	 * \brief Called upon the creation of the object. Initialises State objects further than their respective Constructors
	 * \param _window a reference to the game window
	 * \param _font the font that will be used in the game
	 */
	virtual void OnCreate(sf::RenderWindow& _window, sf::Font& _font) = 0;
	
	/**
	 * \brief Update is called once per game loop
	 * \param _window a reference to the game window
	 */
	virtual void Update(sf::RenderWindow& _window) = 0;
	
	/**
	 * \brief Draws renderables to the window
	 * \param _window a reference to the game window
	 */
	virtual void Render(sf::RenderWindow& _window) = 0;

	
	void SetUpKey(const bool& _upKey) { m_upKey = _upKey; }
	void SetWKey(const bool& _wKey) { m_wKey = _wKey; }
	void SetDownKey(const bool& _downKey) { m_downKey = _downKey; }
	void SetSKey(const bool& _sKey) { m_sKey = _sKey; }
	void SetLeftKey(const bool& _leftKey) { m_leftKey = _leftKey; }
	void SetAKey(const bool& _aKey) { m_aKey = _aKey; }
	void SetRightKey(const bool& _rightKey) { m_rightKey = _rightKey; }
	void SetDKey(const bool& _dKey) { m_dKey = _dKey; }
	void SetEscapeKey(const bool& _escapeKey) { m_escapeKey = _escapeKey; }
	void SetSpaceKey(const bool& _spaceKey) { m_spaceKey = _spaceKey; }


protected:
	bool m_upKey{ false };
	bool m_wKey{ false };
	bool m_downKey{ false };
	bool m_sKey{ false };
	bool m_leftKey{ false };
	bool m_aKey{ false };
	bool m_rightKey{ false };
	bool m_dKey{ false };
	bool m_escapeKey{ false };
	bool m_spaceKey{ false };

	SoundManager& m_soundManager;
	int m_selected{ 0 };
	sf::Font m_font;
};

/**
 * \brief UIText is a container for the UI text that will be displayed in each State
 */
struct UIText {
	/**
	 * \brief Constructs a UIText object
	 * \param _string The string value of the UIText to display
	 * \param _colour The colour of the UIText to display
	 * \param _position The position of the UIText to display
	 * \param _font The font of the UIText to display
	 * \param _size The size of the UIText to display
	 */
	UIText(std::string _string, const sf::Color _colour, const sf::Vector2f _position, const sf::Font& _font, const int _size)
		: m_string(std::move(_string)), m_colour(_colour), m_position(_position), m_font(_font), m_characterSize(_size) {
		m_text = sf::Text(m_string, m_font, m_characterSize);
		m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
		m_text.setFillColor(m_colour);
		m_text.setPosition(m_position);
	}
	sf::Text m_text;
	std::string m_string;
	sf::Color m_colour;
	sf::Vector2f m_position;
	sf::Font m_font;
	int m_characterSize;

	/**
	 * \brief Sets the string value of the UIText
	 * \param _newString The new value to display on screen
	 */
	void SetString(const std::string& _newString) {
		m_string = _newString;
		m_text.setString(m_string);
	}

	/**
	 * \brief Sets the position of the UIText
	 * \param _newPosition The new position of the UIText
	 */
	void SetPosition(const sf::Vector2f& _newPosition) {
		m_position = _newPosition;
		m_text.setPosition(m_position);
	}

	/**
	 * \brief Sets the colour of the UIText
	 * \param _colour The new colour of the UIText
	 */
	void SetColour(const sf::Color& _colour) {
		m_colour = _colour;
		m_text.setFillColor(m_colour);
	}
	/**
	 * \brief Sets the font of the UIText
	 * \param _newFont The new font of the UIText
	 */
	void SetFont(const sf::Font& _newFont) {
		m_font = _newFont;
		m_text.setFont(m_font);
		m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
	}
};

/**
 * \brief The MenuBackground is a container object for the UI elements in the background of the various menus
 */
struct MenuBackground {
	/**
	 * \brief Constructs a MenuBackground object
	 */
	MenuBackground() {
		//load the textures to display
		m_leftRightWall.loadFromFile("Resources/Graphics/left_right_wall.png");
		m_topBottomWall.loadFromFile("Resources/Graphics/top_bottom_wall.png");
		m_grass.loadFromFile("Resources/Graphics/Game_Background.png");
	}
	//To draw the walls and the background 
	sf::Texture m_leftRightWall, m_topBottomWall, m_grass;
	sf::Sprite m_spriteBG, m_spriteLR, m_spriteTB;
	
	/**
	 * \brief Renders the menuBackground
	 * \param _window A reference to the game window
	 */
	void Render(sf::RenderWindow& _window) {
		//THE BACKGROUND
		m_spriteBG.setTexture(m_grass);
		m_spriteBG.setScale(1.5, 1.5);
		m_spriteBG.setPosition(0, 0);
		_window.draw(m_spriteBG);

		//LEFT AND RIGHT WALLS
		m_spriteLR.setTexture(m_leftRightWall);
		m_spriteLR.setScale(1.5, 1.5);
		m_spriteLR.setPosition(0, 0);
		_window.draw(m_spriteLR);

		m_spriteLR.setPosition(constants::k_screenWidth - 1.5 * constants::k_gameGridCellSize, 0);
		_window.draw(m_spriteLR);

		//TOP AND BOTTOM WALLS
		m_spriteTB.setTexture(m_topBottomWall);
		m_spriteTB.setScale(1.5, 1.5);
		m_spriteTB.setPosition(0, 0);
		_window.draw(m_spriteTB);

		m_spriteTB.setPosition(0, constants::k_screenHeight - 1.5 * constants::k_gameGridCellSize);
		_window.draw(m_spriteTB);
	}
};