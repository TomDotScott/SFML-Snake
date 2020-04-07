#pragma once
#include "SFML/Graphics.hpp"
#include "SoundManager.h"
#include "Constants.h"

//Tracks the current state of the game
//Has a global variable attached
enum class eCurrentState {
	e_MainMenu, e_Game, e_GameOver
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
	void SetDownKey(const bool& _downKey) { m_downKey = _downKey; }
	void SetLeftKey(const bool& _leftKey) { m_leftKey = _leftKey; }
	void SetRightKey(const bool& _rightKey) { m_rightKey = _rightKey; }
	void SetEscapeKey(const bool& _escapeKey) { m_escapeKey = _escapeKey; }
	void SetSpaceKey(const bool& _spaceKey) { m_spaceKey = _spaceKey; }

protected:
	bool m_upKey = false;
	bool m_downKey = false;
	bool m_leftKey = false;
	bool m_rightKey = false;
	bool m_escapeKey = false;
	bool m_spaceKey = false;

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

		void SetColour(const sf::Color& _colour)
		{
			m_colour = _colour;
			m_text.setFillColor(m_colour);
		}

		void SetFont(const sf::Font& _newFont)
		{
			m_font = _newFont;
			m_text.setFont(m_font);
			m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
		}
	};
};

//StateManager keeps track of the current game state
class StateManager {
public:
	void SetWindow(sf::RenderWindow* _window);
	void SetState(BaseState* _state);
	void SetFont(const sf::Font& _font) { m_font = _font; }
	void SetSoundManager(SoundManager* _soundManager) { m_soundManager = _soundManager; }
	void Input(sf::Event& _event) const;
	void Update() const;
	void Render() const;
	~StateManager();
private:
	sf::RenderWindow* m_window = nullptr;
	BaseState* m_state = nullptr;
	sf::Font m_font;
	SoundManager* m_soundManager = nullptr;
};

extern StateManager core_state;
extern bool quit_game;
extern eCurrentState current_state;

