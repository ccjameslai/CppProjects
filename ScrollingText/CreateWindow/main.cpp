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

	sf::RenderWindow w(sf::VideoMode(400, 200), "Hello");

	size_t wordIndex = 100;

	sf::Text t("Hello SFML", f);
	sf::Text t1("Hello SFML", f);
	
	float pos = t.findCharacterPos(wordIndex).x;

	t.setStyle(sf::Text::Bold | sf::Text::Italic);
	t.setFillColor(sf::Color::White);

	t1.setPosition(-1 * float(w.getSize().x), 0);
	t1.setStyle(sf::Text::Bold | sf::Text::Italic);
	t1.setFillColor(sf::Color::Green);

	enum class Speed {FAST, SLOW};
	enum class Direction {LEFT2RIGHT, RIGHT2LEFT};

	//Speed speed = Speed::FAST;
	Direction direction = Direction::RIGHT2LEFT;

	vector<sf::Color> cv = { sf::Color::Blue, sf::Color::Cyan, sf::Color::Green, sf::Color::Magenta,
							sf::Color::White, sf::Color::Yellow, sf::Color::Red };

	float speed = 0.1f;
	float acc = 2.f;

	while (w.isOpen()) {
		sf::Event evt;
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				std::cout << "close" << std::endl;
				w.close();
			}			
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				direction = Direction::RIGHT2LEFT;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				direction = Direction::LEFT2RIGHT;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
				speed = 0.2f;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				speed = 0.02f;
			}
			cout << speed << endl;
		}

		w.clear();
		w.draw(t);
		w.draw(t1);

		w.display();

		if (direction == Direction::RIGHT2LEFT) {
			if (t.getPosition().x > w.getSize().x) {
				t.setPosition(-1 * float(w.getSize().x), 0);
			}

			if (t1.getPosition().x > w.getSize().x) {
				t1.setPosition(-1 * float(w.getSize().x), 0);
			}

			t.move(speed, 0);
			t1.move(speed, 0);
		}
		else {
			if (t.getPosition().x < -float(w.getSize().x)) {
				t.setPosition(float(w.getSize().x), 0);
			}

			if (t1.getPosition().x < -float(w.getSize().x)) {
				t1.setPosition(float(w.getSize().x), 0);
			}

			t.move(-speed, 0);
			t1.move(-speed, 0);
		}	
	}
	
	return EXIT_SUCCESS;
}