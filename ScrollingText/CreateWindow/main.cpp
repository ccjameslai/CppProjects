#include <sfml/Window.hpp>
#include <sfml/Graphics.hpp>
#include <iostream>
#include <sfml/System.hpp>
#include <cstdlib>

using namespace std;

int main() {
	
	sf::Font f;
	if (f.loadFromFile("BROADW.TTF") == false) {
		return EXIT_FAILURE;
	}

	size_t wordIndex = 100;

	sf::Text t("Hello SFML", f);
	sf::Text t1("Hello SFML", f);
	
	float pos = t.findCharacterPos(wordIndex).x;

	//t.setStyle(sf::Text::Bold | sf::Text::Italic);
	t.setFillColor(sf::Color::White);

	t1.setPosition(-1 * pos, 0);
	//t1.setStyle(sf::Text::Bold | sf::Text::Italic);
	t1.setFillColor(sf::Color::Green);

	sf::RenderWindow w(sf::VideoMode(400, 200), "Hello");
	
	float x = 0.03f;
	float y = 0.f;

	bool isFirstRun = true;
	vector<sf::Color> cv = { sf::Color::Blue, sf::Color::Cyan, sf::Color::Green, sf::Color::Magenta,
							sf::Color::White, sf::Color::Yellow, sf::Color::Red };

	int min = 0;
	int max = cv.size();

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
		w.draw(t1);

		w.display();

		if (t.getPosition().x < (400 - pos) && t1.getPosition().x < 0) {
			t.move(x, y);
		}
		else if (t.getPosition().x >= (400 - pos) && t.getPosition().x <= (800 - pos)) {
			t1.move(x, y);
			t.move(x, y);
		}
		else if (t.getPosition().x > (800 - pos)) {
			t1.move(x, y);
			t.setPosition(-1 * pos, 0);
			t.setFillColor(cv[rand() % (max - min + 1) + min]);
		}

		if (t1.getPosition().x < (400 - pos) && t.getPosition().x < 0) {
			t1.move(x, y);
		}
		else if (t1.getPosition().x >= (400 - pos) && t1.getPosition().x <= (800 - pos)) {
			t1.move(x, y);
			t.move(x, y);
		}
		else if (t1.getPosition().x > (800 - pos)) {
			t.move(x, y);
			t1.setPosition(-1 * pos, 0);
			t.setFillColor(cv[rand() % (max - min + 1) + min]);
		}
	}
	
	return EXIT_SUCCESS;
}