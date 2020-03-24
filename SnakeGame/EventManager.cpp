#include "EventManager.h"
EventManager::EventManager() : m_hasFocus(true)
{
	LoadBindings();
}

EventManager::~EventManager()
{
	for(auto& itr : m_bindings)
	{
		delete itr.second;
		itr.second = nullptr;
	}
}

//Check if there is a binding of the same name. If there isn't, it gets added to the bindings
bool EventManager::AddBinding(const Binding* _binding)
{
	if(m_bindings.find(_binding->m_name) != m_bindings.end())
	{
		return false;
	}
	return m_bindings.emplace(_binding->m_name, _binding).second;
}

//Check if there is a binding of the same name. If there is, it gets deleted
bool EventManager::RemoveBinding(const std::string& _name)
{
	auto itr = m_bindings.find(_name);
	if(itr == m_bindings.end())
	{
		return false;
	}
	delete itr->second;
	m_bindings.erase(itr);
	return true;
}

//Iterates through each binding and through each event in the binding 
void EventManager::HandleEvent(sf::Event& _event)
{
	//Handle SFML Events
	for(auto& binding : m_bindings)
	{
		Binding* bind = binding.second;
		for(auto& event : bind->m_events)
		{
			const auto sfmlEvent = static_cast<eEventType>(_event.type);
			if (event.first != sfmlEvent) { continue; }
			if(sfmlEvent == eEventType::eKeyUp || sfmlEvent == eEventType::eKeyDown)
			{
				if(event.second.m_code == _event.key.code)
				{
					//It's a matching keycode so increase the count
					if(bind->m_details.m_keyCode != -1)
					{
						bind->m_details.m_keyCode = event.second.m_code;
					}
					++(bind->m_eventCount);
					break;
				}
			}
		}
	}
}

void EventManager::Update()
{
	//only update if it's the active window
	if (!m_hasFocus) { return; }

	//iterate over bindings and events
	for(auto& b_itr : m_bindings)
	{
		Binding* bind = b_itr.second;
		for(auto& e_itr : bind->m_events)
		{
			//only interested in mouse and keyboard, as they need realtime input
			switch (e_itr.first)
			{
			case eEventType::Keyboard:
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(e_itr.second.m_code)))
				{
					if(bind->m_details.m_keyCode != -1)
					{
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->m_eventCount);
				}
				break;
			case eEventType::Mouse:
				if(sf::Mouse::isButtonPressed(sf::Mouse::Button(e_itr.second.m_code)))
				{
					if(bind->m_details.m_keyCode != -1)
					{
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->m_eventCount);
				}
				break;
			default: break;
			}
			if(bind->m_events.size() == bind->m_eventCount)
			{
				auto c_itr = m_callbacks.find(bind->m_name);
				if(c_itr != m_callbacks.end())
				{
					c_itr->second(&bind->m_details);
				}
			}
			bind->m_eventCount = 0;
			bind->m_details.Clear();
		}
	}
	
}





