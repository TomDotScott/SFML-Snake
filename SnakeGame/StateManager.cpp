#include "StateManager.h"

#include <iostream>

StateManager::StateManager()
{
	std::cout << "STATE MANAGER CREATED" << std::endl;
	m_state = nullptr;
	m_window = nullptr;
	m_font = nullptr;
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
		m_state->Initialize(m_window, m_font);
	}
}

void StateManager::SetFont(sf::Font* _font)
{
	m_font = _font;
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
