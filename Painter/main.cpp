#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main() {
	sf::Font font;
	if (!font.loadFromFile("msjhbd.ttc")) {
		return EXIT_FAILURE;
	}

	sf::RenderWindow w(sf::VideoMode(642, 640), L"小畫家");

	enum class CursorSize {
		SMALL = 1,
		NORMAL = 2,
		LARGE = 4,
	};

	int cursorSize = int(CursorSize::NORMAL);

	sf::RectangleShape cursorR(sf::Vector2f(10, 10));
	cursorR.setFillColor(sf::Color::Black);
	cursorR.setOrigin(5, 5);

	sf::CircleShape cursorC(5);
	cursorC.setFillColor(sf::Color::Black);
	cursorC.setOrigin(5, 5);

	vector<sf::Shape*> cursors = {
		&cursorC,
		&cursorR,
	};

	enum class CursorType {
		CIRCLE,
		RECTANGLE,
	};
	
	int cursorType = int(CursorType::CIRCLE);
	
	sf::Shape* cursor = cursors[cursorType];
	
	vector<sf::Color> colors = {
		sf::Color::Black,
		sf::Color::Red,
		sf::Color(175,105,86),
		sf::Color::Blue,
		sf::Color::Yellow,
		sf::Color::Cyan,
		sf::Color::Magenta,
	};

	float swatchOffset = 20;
	vector<sf::RectangleShape> swatches;
	for (auto color : colors) {
		sf::RectangleShape swatch(sf::Vector2f(20,20));
		swatch.setFillColor(color);
		swatch.setOutlineColor(sf::Color(230,230,230));
		swatch.setOutlineThickness(2);
		swatch.setPosition(swatchOffset, 10);
		swatches.push_back(swatch);

		swatchOffset += 20;
	}

	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("background.png")) {
		return EXIT_FAILURE;
	}
	
	sf::Sprite backgroundSprite(backgroundTexture);
	backgroundSprite.setPosition(0, 40);

	sf::RenderTexture canvas;
	canvas.create(600, 560);
	canvas.clear(sf::Color::White);

	sf::Vector2f canvasOffset(20, 60);
	sf::Sprite canvasSprite(canvas.getTexture());
	canvasSprite.setPosition(canvasOffset);
	bool isSaved = false;

	while (w.isOpen()) {
		sf::Event evt;
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}

			if (evt.type == sf::Event::KeyPressed) {
				if (evt.key.code == sf::Keyboard::S) {
					canvas.getTexture().copyToImage().saveToFile("canvas.png");
					isSaved = true;
				}

				if (evt.key.code == sf::Keyboard::Num1) {
					cursorSize = int(CursorSize::SMALL);
				}

				if (evt.key.code == sf::Keyboard::Num2) {
					cursorSize = int(CursorSize::NORMAL);
				}

				if (evt.key.code == sf::Keyboard::Num3) {
					cursorSize = int(CursorSize::LARGE);
				}

				if (evt.key.code == sf::Keyboard::R) {
					cursorType = int(CursorType::RECTANGLE);
					cursor = cursors[cursorType];
				}

				if (evt.key.code == sf::Keyboard::C) {
					cursorType = int(CursorType::CIRCLE);
					cursor = cursors[cursorType];
				}
			}

			if (evt.type == sf::Event::MouseButtonPressed) {
				if (evt.mouseButton.button == sf::Mouse::Left) {
					for (const auto& s : swatches) {
						if (s.getGlobalBounds().
							contains(sf::Vector2f(evt.mouseButton.x, evt.mouseButton.y))){
							cursor->setFillColor(s.getFillColor());
						}
					}
				}
			}
		}

		sf::Vector2i mousePos = sf::Mouse::getPosition(w);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			cursor->setPosition(sf::Vector2f(mousePos) - canvasOffset);
			canvas.draw(*cursor);
			canvas.display();
		}

		w.clear(sf::Color::White);

		w.draw(backgroundSprite);
		w.draw(canvasSprite);

		for (const auto& s : swatches) {
			w.draw(s);
		}

		cursor->setPosition(sf::Vector2f(mousePos));
		
		sf::Text msg;
		if (isSaved) {
			sf::Clock clock;
			sf::Image image;
			if (image.loadFromFile("canvas.png")) {
				msg = sf::Text(sf::String(L"存檔成功"), font, 100);
			}
			else {
				msg = sf::Text(sf::String(L"存檔失敗"), font, 100);
			}

			msg.setFillColor(sf::Color::Black);
			msg.setPosition(sf::Vector2f(100, 200));
			w.draw(msg);
			w.display();

			while (clock.getElapsedTime().asSeconds() < 2.0f) {
				isSaved = false;
			}
			clock.restart();
		}

		cursor->setScale(sf::Vector2f(cursorSize, cursorSize));

		w.draw(*cursor);
		w.display();
	}

	return EXIT_SUCCESS;
}
