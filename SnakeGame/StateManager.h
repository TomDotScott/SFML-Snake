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

	
};
