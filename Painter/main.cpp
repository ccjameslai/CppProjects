#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
	sf::RenderWindow w(sf::VideoMode(642, 640), L"¤pµe®a");

	sf::CircleShape cursor(10);
	cursor.setFillColor(sf::Color::Black);
	
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("background.png")) {
		return EXIT_FAILURE;
	}
	
	sf::Sprite backgroundSprite(backgroundTexture);
	backgroundSprite.setPosition(0, 40);

	sf::Vector2f shift(10, 10);
	while (w.isOpen()) {
		sf::Event evt;
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}
		}

		sf::Vector2i mousePos = sf::Mouse::getPosition(w);
		cursor.setPosition(sf::Vector2f(mousePos) - shift);
		
		
		w.clear(sf::Color::White);
		w.draw(backgroundSprite);
		w.draw(cursor);
		w.display();
	}
}