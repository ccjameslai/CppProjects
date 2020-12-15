#include <SFML/Graphics.hpp>

int main() {
	const int fieldWidth = 10;
	const int fieldHeight = 20;

	sf::Texture texture;
	if (!texture.loadFromFile("blue.png")) {
		return EXIT_FAILURE;
	}

	const int blockWidth = texture.getSize().x;
	const int blockHeight = texture.getSize().y;

	const int windowWidth = fieldWidth * blockWidth;
	const int windowHeight = fieldHeight * blockHeight;

	sf::VideoMode mode(windowWidth, windowHeight);
	sf::RenderWindow w(mode, L"«XÃ¹´µ¤è¶ô");

	sf::Sprite block(texture);
	
	while (w.isOpen()) {
		sf::Event evt;
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}
		}

		w.clear();
		w.draw(block);
		w.display();
	}

	return EXIT_SUCCESS;
}