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



