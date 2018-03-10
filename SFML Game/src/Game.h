#pragma once
#include <SFML\Graphics.hpp>
#include "Window.h"
class Game
{
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();

	Window* GetWindow();

private:
	void MovePlayer();
	Window m_window;

	sf::Texture m_texture;
	sf::Sprite m_player;

	sf::Vector2u m_size;
	sf::Vector2i m_increment;
};

