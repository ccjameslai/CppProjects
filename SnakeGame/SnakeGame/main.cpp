#include <sfml/Graphics.hpp>

int main() {
	sf::VideoMode mode(400, 300);
	sf::RenderWindow w(mode, L"³g¦Y³D");

	while (w.isOpen()) {
		sf::Event evt;
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}
		}

		w.display();
	}
	return EXIT_SUCCESS;
}