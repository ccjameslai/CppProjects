#include <sfml/Window.hpp>
#include <iostream>

int main() {
	sf::Window w(sf::VideoMode(400, 200), "Hello");

	while (w.isOpen()) {
		sf::Event evt;
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				std::cout << "close" << std::endl;
				w.close();
			} else if (evt.type == sf::Event::Resized) {
				std::cout << "Resize" << std::endl;
			}

		}
	}

	return 0;
}