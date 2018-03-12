#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Window.h"

class World
{
public:
	World(sf::Vector2u a_windSize);
	~World();

	int GetBlockSize();

	void RespawnApple();

	void Update(Snake& a_player);
	void Render(sf::RenderWindow& a_window);

private:
	sf::Vector2u m_windowSize;
	sf::Vector2i m_item;

	int m_blockSize;

	sf::CircleShape m_appleShape;
	sf::RectangleShape m_bounds[4];


};

