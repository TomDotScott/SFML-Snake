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

