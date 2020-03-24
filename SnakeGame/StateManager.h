#pragma once
#include <functional>

#include "SFML/Graphics.hpp"
#include "BaseState.h"
#include <unordered_map>

//an enum for all of the states in the game
enum class StateType
{
	MainMenu = 1, Game, Paused, GameOver, Credits
};

//Data that all of the states are going to need references to
struct SharedContext
{
	SharedContext() : m_window(nullptr) { }
	sf::RenderWindow* m_window;
};

//clean up code
using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
using TypeContainer = std::vector<StateType>;

//The unordered map will be here in order to map a specific state type to a specific function to generate that type
using StateFactory = std::unordered_map<StateType, std::function<BaseState* (void)>>;

class StateManager
{
public:
	StateManager(SharedContext* _shared);
	~StateManager();

	void Update();
	void Render();

	void ProcessRequests();

	SharedContext* GetContext();
	bool HasState(const StateType& _type);

	//Changes the current state to whatever is passed in to the function
	void SwitchTo(const StateType& _type);

	//Removes a state from the state stack
	void Remove(const StateType& _type);
private:
	//Methods
	void CreateState(const StateType& _type);
	void RemoveState(const StateType& _type);

	template<class T>;
	void RegisterState(const StateType& _type);

	//Members
	SharedContext* m_shared;
	StateContainer m_states;
	//We only want to remove states once they have been finished with
	TypeContainer m_toRemove;
	StateFactory m_stateFactory;
	
};
