#include <SFML/Graphics.hpp>

int main() {
	const int fieldWidth = 10;
	const int fieldHeight = 20;

	sf::Texture texture;
	if (!texture.loadFromFile("blue.png")) {
		return EXIT_FAILURE;
	}

	const int blockWidth = texture.getSize().x;
	const int blockHeight = texture.getSize().y;

	const int windowWidth = fieldWidth * blockWidth;
	const int windowHeight = fieldHeight * blockHeight;

	sf::VideoMode mode(windowWidth, windowHeight);
	sf::RenderWindow w(mode, L"«XÃ¹´µ¤è¶ô");

	sf::Sprite block(texture);
	
	sf::Vector2i origin(fieldWidth / 2, 0);
	sf::Vector2i pos(origin);

	block.setPosition(float(pos.x * blockWidth), float(pos.y * blockHeight));

	enum class Action {
		MOVEDOWN,
		MOVELEFT,
		MOVERIGHT,
		HOLD,
	};
	

	sf::Clock clock;
	while (w.isOpen()) {
		sf::Event evt;
		
		Action action = Action::HOLD;

		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}

			if (evt.type == sf::Event::KeyPressed) {
				if (evt.key.code == sf::Keyboard::Down) {
					action = Action::MOVEDOWN;
				}

				if (evt.key.code == sf::Keyboard::Left) {
					action = Action::MOVELEFT;
				}

				if (evt.key.code == sf::Keyboard::Right) {
					action = Action::MOVERIGHT;
				}
			}
		}

		if (clock.getElapsedTime().asSeconds() >= 0.3f) {
			action = Action::MOVEDOWN;

			clock.restart();
		}

		sf::Vector2i nextPos(pos);

		switch (action) {
		case Action::MOVEDOWN:
			nextPos.y++;
			break;
		case Action::MOVELEFT:
			nextPos.x--;
			break;
		case Action::MOVERIGHT:
			nextPos.x++;
			break;
		case Action::HOLD:
			break;
		}

		if (nextPos.x >= 0 && nextPos.x < fieldWidth &&
			nextPos.y < fieldHeight) {
			pos = nextPos;
		}

		w.clear();
		block.setPosition(float(pos.x* blockWidth), float(pos.y* blockHeight));
		w.draw(block);
		w.display();
	}

	return EXIT_SUCCESS;
}