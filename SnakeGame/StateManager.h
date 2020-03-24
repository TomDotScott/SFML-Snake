#pragma once
#include <functional>

#include "SFML/Graphics.hpp"
#include "BaseState.h"
#include <unordered_map>

//predefine the state classes
class State_MainMenu;
class State_Paused;
class State_GameOver;
class State_Credits;

//an enum for all of the states in the game
enum class eStateType
{
	e_MainMenu = 1, e_Game, e_Paused, e_GameOver, e_Credits
};

//Data that all of the states are going to need references to
struct SharedContext
{
	SharedContext() : m_window(nullptr)	{	}

	sf::RenderWindow* m_window;
	eStateType currentState;
};

//clean up code
using StateContainer = std::vector<std::pair<eStateType, BaseState*>>;
using TypeContainer = std::vector<eStateType>;

//The unordered map will be here in order to map a specific state type to a specific function to generate that type
using StateFactory = std::unordered_map<eStateType, std::function<BaseState* (void)>>;

class StateManager
{
public:
	StateManager(SharedContext* _shared);
	~StateManager();

	void Update();
	void Render();

	void ProcessRequests();

	SharedContext* GetContext() const { return m_shared; }
	bool HasState(const eStateType& _type);

	//Changes the current state to whatever is passed in to the function
	void SwitchTo(const eStateType& _type);

	//Removes a state from the state stack
	void Remove(const eStateType& _type);
private:
	//Methods
	void CreateState(const eStateType& _type);
	void RemoveState(const eStateType& _type);

	template<class T>
	void RegisterState(const eStateType& _type);

	//Members
	SharedContext* m_shared;
	StateContainer m_states;
	//We only want to remove states once they have been finished with
	TypeContainer m_toRemove;
	StateFactory m_stateFactory;
	
};
