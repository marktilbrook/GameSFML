#pragma once
#include <SFML/Graphics.hpp>

#include <vector>

struct SnakeSegment
{
	SnakeSegment(int x, int y) : position(x, y) {}
	sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;

enum class Direction
{
	None, Up, Down, Left, Right
};

class Snake
{
public:
	Snake(int a_blockSize);
	~Snake();

	//helper methods
	void SetDirection(Direction a_dir);
	Direction GetDirection();
	int GetSpeed();
	sf::Vector2i GetPosition();
	int GetLives();
	int GetScore();
	void IncreaseScore();
	bool HasLost();
	

	void Lose(); //handle losing here
	void ToggleLost();

	Direction GetPhysicalDirection();

	void Extend(); //make snake grow
	void Reset(); //reset to starting pos
	

	void Move(); //move method
	void Tick(); //update method
	void Cut(int a_segments); //method for cutting snake
	void Render(sf::RenderWindow& a_window);

private:
	void CheckCollision();

	SnakeContainer m_snakeBody; //segment vector
	int m_size; //size of graphics
	Direction m_dir; //current direction
	int m_speed;
	int m_lives;
	int m_score;
	bool m_lost;
	sf::RectangleShape m_bodyRect; //shape used in rendering
};

