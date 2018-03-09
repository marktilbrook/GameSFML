#include <SFML\Graphics.hpp>

int main(int argc, char** argv[]) {

	//window constructor
	sf::RenderWindow window(sf::VideoMode(640, 480),"Game Window!");

	sf::Texture texture;
	if (!texture.loadFromFile("res/mushroom1.png"))
	{
		//handle loading error
	}

	sf::Sprite mushroom(texture);

	sf::Vector2u size = texture.getSize();
	mushroom.setOrigin(size.x / 2, size.y / 2);
	sf::Vector2f increment(0.4f, 0.4f);


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				// Close window button clicked.
				window.close();
			}
		}
		
		if ((mushroom.getPosition().x + (size.x / 2) >
			window.getSize().x && increment.x > 0) ||
			(mushroom.getPosition().x - (size.x / 2) < 0 &&
				increment.x < 0))
		{
			// Reverse the direction on X axis.
			increment.x = -increment.x;
		}
		if ((mushroom.getPosition().y + (size.y / 2) >
			window.getSize().y && increment.y > 0) ||
			(mushroom.getPosition().y - (size.y / 2) < 0 &&
				increment.y < 0))
		{
			increment.y = -increment.y;
		}

		mushroom.setPosition(mushroom.getPosition() + increment);
		window.clear(sf::Color::Black);
		// Draw here.
		window.draw(mushroom);
		window.display();
	}
}