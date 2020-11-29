#include <sfml/Graphics.hpp>

int main() {
	sf::VideoMode mode(400, 300);
	sf::RenderWindow w(mode, L"³g¦Y³D");
	sf::Texture texture;
	texture.loadFromFile("block.png");
	sf::Sprite image(texture);

	while (w.isOpen()) {
		sf::Event evt;
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}
		}

		w.draw(image);
		w.display();
		
	}
	return EXIT_SUCCESS;
}