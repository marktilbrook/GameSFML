#include "Window.h"


//default constructor
Window::Window() 
{ 
	Setup("Window", sf::Vector2u(640, 480)); 
}

Window::Window(const std::string& a_title, const sf::Vector2u& a_size)
{
	Setup(a_title, a_size);
}

Window::~Window()
{
	Destroy();
}

void Window::BeginDraw()
{
	m_window.clear(sf::Color::Black);
}

void Window::EndDraw()
{
	m_window.display();
}

void Window::Update()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::LostFocus)
		{
			m_isFocused = false;
			m_eventManager.SetFocus(false);
		}
		else if (event.type == sf::Event::GainedFocus)
		{
			m_isFocused = true;
			m_eventManager.SetFocus(true);
		}
		m_eventManager.HandleEvent(event);
	}
	m_eventManager.Update();
}

bool Window::IsDone()
{
	return m_isDone;
}

bool Window::IsFullScreen()
{
	return m_isFullScreen;
}

sf::Vector2u Window::GetWindowSize()
{
	return m_windowSize;
}

sf::RenderWindow * Window::GetRenderWindow()
{
	return &m_window; 
}



bool Window::IsFocused()
{
	return m_isFocused;
}

EventManager * Window::GetEventManager()
{
	return &m_eventManager;
}

void Window::ToggleFullScreen(EventDetails * a_details)
{
	m_isFullScreen = !m_isFullScreen;
	m_window.close();
	Create();
}

void Window::Close(EventDetails * a_details)
{
	m_isDone = true;
}

void Window::Draw(sf::Drawable & a_drawable)
{
	m_window.draw(a_drawable);
}

void Window::Setup(const std::string & a_title, const sf::Vector2u & a_size)
{
	m_windowTitle = a_title;
	m_windowSize = a_size;
	m_isFullScreen = false;
	m_isDone = false;
	m_isFocused = true;

	m_eventManager.AddCallback("Fullscreen_toggle",
		&Window::ToggleFullScreen, this);
	m_eventManager.AddCallback("Window_close",
		&Window::Close, this);

	Create();
}

void Window::Destroy()
{
	m_window.close();
}

void Window::Create()
{
	auto style = (m_isFullScreen ? sf::Style::Fullscreen
		: sf::Style::Default);
	m_window.create({ m_windowSize.x, m_windowSize.y,32 }, m_windowTitle, style);
}
