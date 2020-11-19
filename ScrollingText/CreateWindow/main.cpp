#include <sfml/Window.hpp>
#include <sfml/Graphics.hpp>
#include <iostream>
#include <sfml/System.hpp>
#include <cstdlib>
#include <fstream>

using namespace std;

int main() {
	
	sf::Font f;
	if (f.loadFromFile("BROADW.TTF") == false) {
		return EXIT_FAILURE;
	}

	sf::RenderWindow w(sf::VideoMode(1500, 200), "Hello");

	size_t wordIndex = 100;
	string text;
	
	ifstream ifs("content.txt", ifstream::in);
	getline(ifs, text);

	sf::Text t(text, f, 150);
	sf::Text t1(text, f, 150);
	
	float pos = t.findCharacterPos(wordIndex).x;

	t.setStyle(sf::Text::Bold | sf::Text::Italic);
	t.setFillColor(sf::Color(255, 255, 0));

	t1.setPosition(-1 * float(w.getSize().x), 0);
	t1.setStyle(sf::Text::Bold | sf::Text::Italic);
	t1.setFillColor(sf::Color::Green);

	sf::Vector2f vec2f(5.f, 5.f);
	sf::RectangleShape rect;
	rect.setFillColor(sf::Color(0, 0, 0));
	rect.setSize(vec2f);

	enum class SpeedMode {FAST, NORMAL, SLOW, FREE};
	enum class Direction {LEFT2RIGHT, RIGHT2LEFT};
	Direction direction = Direction::RIGHT2LEFT;	

	SpeedMode speedMode = SpeedMode::NORMAL;
	float speed = 0.1f * 20;
	float times = 2.f;

	while (w.isOpen()) {
		sf::Event evt;
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				std::cout << "close" << std::endl;
				w.close();
			}			
			
			if (evt.key.code == sf::Keyboard::Right) {
				direction = Direction::RIGHT2LEFT;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				direction = Direction::LEFT2RIGHT;
				speedMode = SpeedMode::FREE;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || 
				sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
				speed = 0.4f * 20;
				speedMode = SpeedMode::FREE;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
				speed = 0.2f * 20;
				speedMode = SpeedMode::FREE;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) {
				speed = 0.1f * 20;
				speedMode = SpeedMode::FREE;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) {
				speed = 0.05f * 20;
				speedMode = SpeedMode::FREE;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)) {
				speed = 0.025f * 20;
				speedMode = SpeedMode::FREE;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
				if (speed > 50.f) {
					speed = 50.f;
				}
				else {
					speed *= times;
				}
				speedMode = SpeedMode::FREE;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
				if (speed < 0.0125f) {
					speed = 0.0125f;
				}
				else {
					speed /= times;
				}
				speedMode = SpeedMode::FREE;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
				speedMode = SpeedMode::FAST;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				speedMode = SpeedMode::SLOW;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
				speedMode = SpeedMode::NORMAL;
			}
		}

		w.clear();
		w.draw(t);
		w.draw(t1);

		for (unsigned int i = 0; i < w.getSize().x; i += 8) {
			for (unsigned int j = 0; j < w.getSize().y; j += 8) {
				rect.setPosition(float(i), float(j));
				w.draw(rect);
			}
		}
		
		w.display();

		if (direction == Direction::RIGHT2LEFT) {
			if (t.getPosition().x > w.getSize().x) {
				t.setPosition(-1 * float(w.getSize().x), 0);
			}

			if (t1.getPosition().x > w.getSize().x) {
				t1.setPosition(-1 * float(w.getSize().x), 0);
			}

			if (speedMode == SpeedMode::FAST) {
				t.move(50.f, 0.f);
				t1.move(50.f, 0.f);
			}
			else if (speedMode == SpeedMode::SLOW) {
				t.move(0.1f, 0.f);
				t1.move(0.1f, 0.f);
			}
			else if (speedMode == SpeedMode::NORMAL) {
				t.move(2.f, 0.f);
				t1.move(2.f, 0.f);
			}
			else {
				t.move(speed, 0);
				t1.move(speed, 0);
			}
		}
		else {
			if (t.getPosition().x < -float(w.getSize().x)) {
				t.setPosition(float(w.getSize().x), 0);
			}

			if (t1.getPosition().x < -float(w.getSize().x)) {
				t1.setPosition(float(w.getSize().x), 0);
			}

			if (speedMode == SpeedMode::FAST) {
				t.move(-10.f, 0.f);
				t1.move(-10.f, 0.f);
			}
			else if (speedMode == SpeedMode::SLOW) {
				t.move(-0.1f, 0.f);
				t1.move(-0.1f, 0.f);
			}
			else if (speedMode == SpeedMode::NORMAL) {
				t.move(-2.f, 0.f);
				t1.move(-2.f, 0.f);
			}
			else {
				t.move(-speed, 0);
				t1.move(-speed, 0);
			}
		}

	}

	ifs.close();
	return EXIT_SUCCESS;
}