#pragma once
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <functional> //defines std::function and std::bind

//enumeration table to store the events that will happen in the game
enum class eEventType
{
	eKeyDown = sf::Event::KeyPressed,
	eKeyUp = sf::Event::KeyReleased,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	MouseEntered = sf::Event::MouseEntered,
	MouseLeft = sf::Event::MouseLeft,
	Closed = sf::Event::Closed,
	Keyboard = sf::Event::Count + 1,
	Mouse,
};

struct EventInfo
{
	EventInfo() { m_code = 0; }
	EventInfo(int _event) { m_code = _event; }
	union
	{
		int m_code;
	};
};

//Set up a data type to deal with events
struct EventDetails
{
	EventDetails(const std::string _bindName) : m_name(_bindName)
	{
		Clear();
	}
	std::string m_name;

	sf::Vector2i m_size;
	sf::Uint32 m_textEntered;
	sf::Vector2i m_mouse;
	int m_mouseWheelDelta;

	//Single KeyCode
	int m_keyCode;

	void Clear()
	{
		m_size = sf::Vector2i(0, 0);
		m_textEntered = 0;
		m_mouse = sf::Vector2i(0, 0);
		m_mouseWheelDelta = 0;
		m_keyCode = -1;
	}
};

//Holds all the event data
struct Binding
{
	Binding(const std::string& _name) : m_name(_name), m_details(_name), m_eventCount(0){}

	void BindEvent(eEventType _type, EventInfo _info = EventInfo())
	{
		m_events.emplace_back(_type, _info);
	}

	std::vector<std::pair<eEventType, EventInfo>> m_events;
	std::string m_name;
	int m_eventCount;

	EventDetails m_details;
};

class EventManager
{
public:
	EventManager();
	~EventManager();

	bool AddBinding(const Binding* _binding);
	bool RemoveBinding(const std::string& _name);
	void SetFocus(const bool& _focus);

	template<class T>
	bool AddCallBack(const std::string& _name, void(T::*_func)(EventDetails*), T* _instance)
	{
		auto temp = std::bind(_func, _instance, std::placeholders::_1);
		return m_callbacks.emplace(_name, temp).second;
	}

	void RemoveCallback(const std::string& _name)
	{
		m_callbacks.erase(_name);
	}

	void HandleEvent(sf::Event& _event);

	void Update();

	sf::Vector2i GetMousePosition(sf::RenderWindow* _window = nullptr) const
	{
		return (_window ? sf::Mouse::getPosition(*_window) : sf::Mouse::getPosition());
	}
	
private:
	void LoadBindings();

	std::unordered_map<std::string, Binding*> m_bindings;
	
	std::unordered_map<std::string, std::function<void(EventDetails*)>> m_callbacks;

	bool m_hasFocus;
};

