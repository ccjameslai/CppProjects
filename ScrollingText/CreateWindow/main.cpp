#include <sfml/Window.hpp>
#include <sfml/Graphics.hpp>
#include <iostream>
#include <sfml/System.hpp>

int main() {
	
	sf::Font f;
	if (f.loadFromFile("BROADW.TTF") == false) {
		return EXIT_FAILURE;
	}
	sf::Text t("Hello SFML", f);
	sf::RenderWindow w(sf::VideoMode(400, 200), "Hello");

	while (w.isOpen()) {
		sf::Event evt;
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				std::cout << "close" << std::endl;
				w.close();
			}
		}
		
		w.clear();
		w.draw(t);
		t.move(0.01, 0);
		w.display();
	}

	return EXIT_SUCCESS;
}