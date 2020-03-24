#include "StateManager.h"
#include "State_Game.h"

//Using template to clean up code
//Maps _type to a function that returns a pointer to the newly allocated memory on the heap
template<class T>
void StateManager::RegisterState(const eStateType& _type)
{
	m_stateFactory[_type] = [this]() ->BaseState *
	{
		return new T(this);
	};
}

StateManager::StateManager(SharedContext* _shared) : m_shared(_shared)
{
	//Each State will have their own class
	RegisterState<State_MainMenu>(eStateType::e_MainMenu);
	RegisterState<State_Game>(eStateType::e_Game);
	RegisterState<State_Paused>(eStateType::e_Paused);
	RegisterState<State_GameOver>(eStateType::e_GameOver);
	RegisterState<State_Credits>(eStateType::e_Credits);
}

StateManager::~StateManager()
{
	//Because we localise the dynamic memory allocation of the states in this
	//class, it is imperative that we also free the memory appropriately. Iterating
	//over the states does just that
	for(auto& itr : m_states)
	{
		itr.second->OnDestroy();
		delete itr.second;
	}
}

void StateManager::Render()
{
	if (m_states.empty()) { return; }
	//Check if the states vector has at least one state
	if (m_states.back().second->IsTransparent() && m_states.size() > 1)
	{
		auto itr = m_states.end();
		while(itr != m_states.begin())
		{
			if(itr != m_states.end())
			{
				//Check the transparency flag
				if(!itr->second->IsTransparent())
				{
					break;
				}
			}
			--itr;
		}
		for(; itr != m_states.end(); ++itr)
		{
			//render from the bottom upward, allowing for multiple
			//states to be rendered at once, in order
			itr->second->Render();
		}
	}else
	{
		m_states.back().second->Render();
	}
}

//Same method as Render, but this time the Transcendence flag is checked
void StateManager::Update()
{
	if (m_states.empty()) { return; }
	if (m_states.back().second->IsTranscendent() && m_states.size() > 1)
	{
		auto itr = m_states.end();
		while (itr != m_states.begin())
		{
			if (itr != m_states.end())
			{
				if (!itr->second->IsTranscendent())
				{
					break;
				}
			}
			--itr;
		}
		for (; itr != m_states.end(); ++itr)
		{
			itr->second->Update();
		}
	}else
	{
		m_states.back().second->Update();
	}
}

//Iterate over the states until a state with that type is found
bool StateManager::HasState(const eStateType& _type)
{
	for(auto itr = m_states.begin(); itr != m_states.end(); ++itr)
	{
		if(itr->first == _type)
		{
			const auto removed = std::find(m_toRemove.begin(), m_toRemove.end(), _type);
			if(removed == m_toRemove.end())
			{
				return true;
			}
			return false;
		}
	}
	return false;
}

//Pushes back a state for later removal
void StateManager::Remove(const eStateType& _type)
{
	m_toRemove.push_back(_type);
}

//Iterate over the toRemove vector and calls RemoveState(), ensuring that the container is cleared
void StateManager::ProcessRequests()
{
	while(m_toRemove.begin() != m_toRemove.end())
	{
		RemoveState(*m_toRemove.begin());
		m_toRemove.erase(m_toRemove.begin());
	}
}

//Switches between states
void StateManager::SwitchTo(const eStateType& _type)
{
	//keep track of which state the game is in
	m_shared->currentState = _type;

	//find a state with the type that we want to switch to
	for(auto itr = m_states.begin(); itr != m_states.end(); ++itr)
	{
		if(itr->first == _type)
		{
			m_states.back().second->Deactivate();
			eStateType tempType = itr->first;
			BaseState* tempState = itr->second;
			m_states.erase(itr);
			m_states.emplace_back(tempType, tempState);
			tempState->Activate();
			return;
		}
	}
	//If a state with _type wasn't found...
	if (!m_states.empty()) { m_states.back().second->Deactivate(); }
	//...Then we have to create a state of that type
	CreateState(_type);
	m_states.back().second->Activate();
}

void StateManager::CreateState(const eStateType& _type)
{
	//make sure that a state of that type can be created
	const auto newState = m_stateFactory.find(_type);
	if (newState == m_stateFactory.end()) { return; }
	//if it can be created, a new state is made
	BaseState* state = newState->second();
	m_states.emplace_back(_type, state);
	//Make the state act as if it has just been created
	state->OnCreate();
}


//Iterate until that state type is found and then remove it from the m_states vector
void StateManager::RemoveState(const eStateType& _type)
{
	for (auto itr = m_states.begin(); itr != m_states.end(); ++itr)
	{
		if(itr->first == _type)
		{
			//prep the object for deletion
			itr->second->OnDestroy();
			delete itr->second;
			m_states.erase(itr);
			return;
		}
	}
}


