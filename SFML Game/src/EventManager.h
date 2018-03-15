#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <sstream>
#include <iostream>


enum class EventType
{
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MButtonDown = sf::Event::MouseButtonPressed,
	MButtonUp = sf::Event::MouseButtonReleased,
	MouseWheel = sf::Event::MouseWheelMoved,
	WindowResized = sf::Event::Resized,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	MouseEntered = sf::Event::MouseEntered,
	MouseLeft = sf::Event::MouseLeft,
	Closed = sf::Event::Closed,
	TextEntered = sf::Event::TextEntered,
	Keyboard = sf::Event::Count + 1, Mouse, Joystick
};
struct EventInfo
{
	EventInfo() { m_code = 0; }
	EventInfo(int a_event) { m_code = a_event; }
	union 
	{
		int m_code;
	};
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct EventDetails
{
	EventDetails(const std::string& a_bindName) : m_name(a_bindName)
	{
		Clear();
	}
	
	std::string m_name;
	sf::Vector2i m_size;
	sf::Uint32 m_textEntered;

	sf::Vector2i m_mouse;
	int m_mouseWheelDelta;
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

struct Binding
{
	Binding(const std::string& a_name) : m_name(a_name), m_details(a_name), c(0){}

	void BindEvent(EventType a_type, EventInfo a_info = EventInfo())
	{
		m_events.emplace_back(a_type, a_info);
	}

	Events m_events;
	std::string m_name;
	int c; //count of events that are "happening"

	EventDetails m_details;
};

using Bindings = std::unordered_map<std::string, Binding*>;
using Callbacks = std::unordered_map<std::string, std::function<void(EventDetails*)>>;

class EventManager
{
public:
	EventManager();
	~EventManager();

	bool AddBinding(Binding* a_binding);
	bool RemoveBinding(std::string a_name);

	void SetFocus(const bool& a_focus);

	template<typename T>
	bool AddCallback(const std::string& a_name, void(T::*a_func)(EventDetails*), T* a_instance)
	{
		auto temp = std::bind(a_func, a_instance, std::placeholders::_1);
		return m_callbacks.emplace(a_name, temp).second;
	}

	void RemoveCallback(const std::string& a_name) 
	{
		m_callbacks.erase(a_name);
	}

	void HandleEvent(sf::Event& a_event);
	void Update();

	sf::Vector2i GetMousePos(sf::RenderWindow* a_window = nullptr)
	{
		return (a_window ? sf::Mouse::getPosition(*a_window) : sf::Mouse::getPosition());
	}


private:
	void LoadBindings();
	
	Bindings m_bindings;
	Callbacks m_callbacks;
	bool m_hasFocus;
};

