#include <SFML\Graphics.hpp>

int main(int argc, char** argv[]) {

	//window constructor
	sf::RenderWindow window(sf::VideoMode(640, 480),"Game Window!");

	sf::RectangleShape rectangle(sf::Vector2f(120.f, 128.f));
	rectangle.setFillColor(sf::Color::Cyan);
	rectangle.setPosition(320, 240);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				// Close window button clicked.
				window.close();
			}
		}
		window.clear(sf::Color::Black);
		// Draw here.
		window.draw(rectangle);
		window.display();
	}
}