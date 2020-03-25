#include "StateManager.h"

StateManager::StateManager()
{
	m_state = nullptr;
}

void StateManager::SetWindow(sf::RenderWindow* _window)
{
	m_window = _window;
}

void StateManager::SetState(BaseState* _state)
{
	if(m_state != nullptr)
	{
		m_state->Destroy(m_window);
	}
	m_state = _state;
	if(m_state != nullptr)
	{
		m_state->Initialize(m_window);
	}
}

void StateManager::Update() const
{
	if(m_state != nullptr)
	{
		m_state->Update(m_window);
	}
}

void StateManager::Render() const
{
	if(m_state != nullptr)
	{
		m_state->Render(m_window);
	}
}

StateManager::~StateManager()
{
	if(m_state != nullptr)
	{
		m_state->Destroy(m_window);
	}
}
