#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
	sf::RenderWindow w(sf::VideoMode(642, 640), L"¤pµe®a");

	sf::CircleShape cursor(10);
	cursor.setFillColor(sf::Color::Black);
	cursor.setOrigin(10, 10);

	sf::RectangleShape rect(sf::Vector2f(10,10));
	rect.setFillColor(sf::Color::Black);

	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("background.png")) {
		return EXIT_FAILURE;
	}
	
	sf::Sprite backgroundSprite(backgroundTexture);
	backgroundSprite.setPosition(0, 40);

	sf::RenderTexture canvas;
	canvas.create(600, 560);
	canvas.clear(sf::Color::White);

	sf::Vector2f canvasOffset(20, 60);
	sf::Sprite canvasSprite(canvas.getTexture());
	canvasSprite.setPosition(canvasOffset);

	while (w.isOpen()) {
		sf::Event evt;
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}
		}

		sf::Vector2i mousePos = sf::Mouse::getPosition(w);

		cursor.setPosition(sf::Vector2f(mousePos) - canvasOffset);
		canvas.draw(cursor);
		canvas.display();

		w.clear(sf::Color::White);
		w.draw(backgroundSprite);
		w.draw(canvasSprite);
		w.draw(rect);
		cursor.setPosition(sf::Vector2f(mousePos));
		w.draw(cursor);
		w.display();
	}
}