#include "StateManager.h"

#include <iostream>
//STATEMANAGER
StateManager::StateManager() {
	std::cout << "STATE MANAGER CREATED" << std::endl;
	m_state = nullptr;
	m_window = nullptr;
	m_font = nullptr;
}

void StateManager::SetWindow(sf::RenderWindow* _window) {
	m_window = _window;
}

void StateManager::SetState(BaseState* _state) {
	if (m_state != nullptr) {
		m_state->Destroy(m_window);
		delete m_state;
	}
	m_state = _state;
	if (m_state != nullptr) {
		m_state->Initialize(m_window, m_font);
	}
}

void StateManager::SetFont(sf::Font* _font) {
	m_font = _font;
}

void StateManager::Input(sf::Event& _event) const {
	switch (_event.type) {
	case sf::Event::KeyReleased:
		m_state->SetUpKey(_event.key.code == sf::Keyboard::Up ? true : false);
		m_state->SetDownKey(_event.key.code == sf::Keyboard::Down ? true : false);
		m_state->SetLeftKey(_event.key.code == sf::Keyboard::Left ? true : false);
		m_state->SetRightKey(_event.key.code == sf::Keyboard::Right ? true : false);
		m_state->SetEscapeKey(_event.key.code == sf::Keyboard::Escape ? true : false);
		m_state->SetSpaceKey(_event.key.code == sf::Keyboard::Space ? true : false);
		break;
	default:
		break;
	}
}

void StateManager::Update() const {
	if (m_state != nullptr) {
		m_state->Update(m_window);
	}
}

void StateManager::Render() const {
	if (m_state != nullptr) {
		m_state->Render(m_window);
	}
}

StateManager::~StateManager() {
	if (m_state != nullptr) {
		m_state->Destroy(m_window);
	}
}
