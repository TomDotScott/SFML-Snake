#include "StateControls.h"
#include "StateManager.h"
#include "StateGame.h"
#include "StateGameOver.h"
#include "StateMainMenu.h"

void StateManager::OnCreate(sf::RenderWindow& _window, const sf::Font& _font, const EState& _state, const SoundManager& _soundManager) {
	m_font = _font;
	m_currentState = _state;
	m_soundManager = _soundManager;
	ChangeState(m_currentState, _window);
}

void StateManager::ChangeState(const EState& _state, sf::RenderWindow& _window, const bool _twoPlayer, const bool _playerWon) {
	m_currentState = _state;
	switch (_state) {
	case EState::eMainMenu:
		STATE_MANAGER.SetState(new StateMainMenu(m_soundManager), _window);
		break;

	case EState::eControlsMenu:
		STATE_MANAGER.SetState(new StateControls(m_soundManager), _window);
		break;

	case EState::eGame:
		STATE_MANAGER.SetState(new StateGame(m_soundManager, _twoPlayer), _window);
		break;

	case EState::eGameOver:
		STATE_MANAGER.SetState(new StateGameOver(m_soundManager, _twoPlayer, _playerWon), _window);
		break;

	default:;
	}
}


void StateManager::SetState(BaseState* _state, sf::RenderWindow& _window) {
	delete m_state;
	m_state = _state;
	if (m_state != nullptr) {
		m_state->OnCreate(_window, m_font);
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

void StateManager::Update(sf::RenderWindow& _window) const {
	if (m_state != nullptr) {
		m_state->Update(_window);
	}
}

void StateManager::Render(sf::RenderWindow& _window) const {
	if (m_state != nullptr) {
		m_state->Render(_window);
	}
}

StateManager::~StateManager() {
	delete m_state;
}
