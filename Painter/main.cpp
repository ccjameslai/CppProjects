#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main() {
	sf::RenderWindow w(sf::VideoMode(642, 640), L"¤pµe®a");

	sf::CircleShape cursor(10);
	cursor.setFillColor(sf::Color::Black);
	cursor.setOrigin(10, 10);

	
	vector<sf::Color> colors = {
		sf::Color::Black,
		sf::Color::Red,
		sf::Color(175,105,86),
		sf::Color::Blue,
		sf::Color::Yellow,
		sf::Color::Cyan,
		sf::Color::Magenta,
	};

	float swatchOffset = 20;
	vector<sf::RectangleShape> swatches;
	for (auto color : colors) {
		sf::RectangleShape swatch(sf::Vector2f(20,20));
		swatch.setFillColor(color);
		swatch.setOutlineColor(sf::Color(230,230,230));
		swatch.setOutlineThickness(2);
		swatch.setPosition(swatchOffset, 10);
		swatches.push_back(swatch);

		swatchOffset += 20;
	}

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

			if (evt.type == sf::Event::MouseButtonPressed) {
				if (evt.mouseButton.button == sf::Mouse::Left) {
					for (const auto& s : swatches) {
						if (s.getGlobalBounds().
							contains(sf::Vector2f(evt.mouseButton.x, evt.mouseButton.y))){
							cursor.setFillColor(s.getFillColor());
						}
					}
				}
			}
		}

		sf::Vector2i mousePos = sf::Mouse::getPosition(w);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			cursor.setPosition(sf::Vector2f(mousePos) - canvasOffset);
			canvas.draw(cursor);
			canvas.display();
		}

		w.clear(sf::Color::White);
		w.draw(backgroundSprite);
		w.draw(canvasSprite);

		for (const auto& s : swatches) {
			w.draw(s);
		}

		cursor.setPosition(sf::Vector2f(mousePos));
		w.draw(cursor);
		w.display();
	}
}