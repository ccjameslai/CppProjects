#include <sfml/Window.hpp>
#include <sfml/Graphics.hpp>
#include <iostream>
#include <sfml/System.hpp>

using namespace std;

int main() {
	
	sf::Font f;
	if (f.loadFromFile("BROADW.TTF") == false) {
		return EXIT_FAILURE;
	}
	sf::Text t("Hello SFML", f);
	t.setStyle(sf::Text::Bold | sf::Text::Italic);
	t.setFillColor(sf::Color::Cyan);

	size_t wordIndex = 100;
	sf::RenderWindow w(sf::VideoMode(400, 200), "Hello");

	float pos = t.findCharacterPos(wordIndex).x;
	float x = 0.05f;
	float y = 0.f;

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
		

		if (t.getPosition().x > 400) {
			t.setPosition(-1*pos, 0);
		}

		w.display();
	
		t.move(x, y);
	}
	
	return EXIT_SUCCESS;
}