#include "Game.h"



Game::Game() : m_window("Game2", sf::Vector2u(800,600))
{
	//set up of class members
	if (!m_texture.loadFromFile("res/mushroom1.png"))
	{
		//handle loading error
	}
	
	m_player.setTexture(m_texture);
	
	m_size = m_texture.getSize();

	m_increment = sf::Vector2i(4, 4);
	m_player.setOrigin(m_size.x / 2, m_size.y / 2);
}

//destructor can remain empty for now!
Game::~Game()
{
}

void Game::HandleInput(){}

void Game::Update()
{
	m_window.Update(); //updates window events
	MovePlayer();
}

void Game::Render()
{
	m_window.BeginDraw(); //clears window
	m_window.Draw(m_player);
	m_window.EndDraw(); //display
}

Window* Game::GetWindow()
{
	return &m_window;
}

void Game::MovePlayer()
{
	sf::Vector2u a_windSize = m_window.GetWindowSize();
	sf::Vector2u a_textSize = m_texture.getSize();
	if ((m_player.getPosition().x >
		a_windSize.x - a_textSize.x && m_increment.x> 0) ||
		(m_player.getPosition().x < 0 && m_increment.x< 0)) {
		m_increment.x = -m_increment.x;
	}
	if ((m_player.getPosition().y >
		a_windSize.y - a_textSize.y && m_increment.y> 0) ||
		(m_player.getPosition().y < 0 && m_increment.y< 0)) {
		m_increment.y = -m_increment.y;
	}

	m_player.setPosition(m_player.getPosition().x + m_increment.x,
		m_player.getPosition().y + m_increment.y);
}








