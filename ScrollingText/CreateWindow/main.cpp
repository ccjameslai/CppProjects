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

	float x = 0.01;
	float y = 0.0;

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
		w.display();
		if (t.getPosition().x > 400) {
			x = 0.01;
			t.setPosition(0, 0);
		}
		t.move(x, y);
	}

	return EXIT_SUCCESS;
}