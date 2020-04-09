#pragma once
#include "SFML/Graphics.hpp"
#include "SoundManager.h"
#include "Constants.h"

//Tracks the current state of the game
//Has a global variable attached
enum class ECurrentState {
	eMainMenu, eControlsMenu, eGame, eGameOver
};

//Every state needs to be able to do these 4 things:
//*Initialize
//*Update
//*Render
//*Destroy
//If an object can't, it's not a state
class BaseState {
public:
	virtual ~BaseState() = default;

	virtual void Initialize(sf::RenderWindow& _window, sf::Font& _font, SoundManager* _soundManager) = 0;
	virtual void Update() = 0;
	virtual void Render(sf::RenderWindow& _window) = 0;
	virtual void Destroy() = 0;

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
	struct UIText {
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

		void SetString(const std::string& _newString) {
			m_string = _newString;
			m_text.setString(m_string);
		}

		void SetPosition(const sf::Vector2f& _newPosition) {
			m_position = _newPosition;
			m_text.setPosition(m_position);
		}

		void SetColour(const sf::Color& _colour) {
			m_colour = _colour;
			m_text.setFillColor(m_colour);
		}

		void SetFont(const sf::Font& _newFont) {
			m_font = _newFont;
			m_text.setFont(m_font);
			m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
		}
	};

	struct MenuBackground {
		MenuBackground() {
			//load the textures to display
			m_leftRightWall.loadFromFile("Resources/Graphics/left_right_wall.png");
			m_topBottomWall.loadFromFile("Resources/Graphics/top_bottom_wall.png");
			m_grass.loadFromFile("Resources/Graphics/Game_Background.png");
		}
		//To draw the walls and the background 
		sf::Texture m_leftRightWall, m_topBottomWall, m_grass;
		sf::Sprite m_spriteBG, m_spriteLR, m_spriteTB;
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

	SoundManager* m_soundManager{ nullptr };
	int m_selected{ 0 };
	sf::Font m_font;
};

//StateManager keeps track of the current game state
class StateManager {
public:
	~StateManager();

	void Input(sf::Event& _event) const;
	void Update() const;
	void Render() const;

	void SetWindow(sf::RenderWindow* _window);
	void SetState(BaseState* _state);
	void SetFont(const sf::Font& _font) { m_font = _font; }
	void SetSoundManager(SoundManager* _soundManager) { m_soundManager = _soundManager; }
private:
	sf::RenderWindow* m_window{ nullptr };
	BaseState* m_state{ nullptr };
	sf::Font m_font;
	SoundManager* m_soundManager{ nullptr };
};

extern StateManager CORE_STATE;
extern bool QUIT_GAME;
extern ECurrentState CURRENT_STATE;

