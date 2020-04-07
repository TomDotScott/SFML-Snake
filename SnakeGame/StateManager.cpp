#include "StateManager.h"

#include <iostream>

void StateManager::SetWindow(sf::RenderWindow* _window) {
	m_window = _window;
}

void StateManager::SetState(BaseState* _state) {
	if (m_state != nullptr) {
		m_state->Destroy();
		delete m_state;
	}
	m_state = _state;
	if (m_state != nullptr) {
		m_state->Initialize(*m_window, m_font, m_soundManager);
	}
}

void StateManager::Input(sf::Event& _event) const {
	switch (_event.type) {
	case sf::Event::KeyReleased:
		m_state->SetUpKey(_event.key.code == sf::Keyboard::Up ? true : false);
		m_state->SetDownKey(_event.key.code == sf::Keyboard::Down ? true : false);
		m_state->SetLeftKey(_event.key.code == sf::Keyboard::Left ? true : false);
		m_state->SetRightKey(_event.key.code == sf::Keyboard::Right ? true : false);
		m_state->SetWKey(_event.key.code == sf::Keyboard::W ? true : false);
		m_state->SetAKey(_event.key.code == sf::Keyboard::A ? true : false);
		m_state->SetSKey(_event.key.code == sf::Keyboard::S ? true : false);
		m_state->SetDKey(_event.key.code == sf::Keyboard::D ? true : false);
		m_state->SetEscapeKey(_event.key.code == sf::Keyboard::Escape ? true : false);
		m_state->SetSpaceKey(_event.key.code == sf::Keyboard::Space ? true : false);
		break;
	default:
		break;
	}
}

void StateManager::Update() const {
	if (m_state != nullptr) {
		m_state->Update();
	}
}

void StateManager::Render() const {
	if (m_state != nullptr) {
		m_state->Render(*m_window);
	}
}

StateManager::~StateManager() {
	if (m_state != nullptr) {
		m_state->Destroy();
	}
}
