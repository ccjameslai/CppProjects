#include <SFML/Graphics.hpp>

int main() {
	const int fieldWidth = 10;
	const int fieldHeight = 20;

	bool fieldState[fieldWidth][fieldHeight] = {};

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

		if (clock.getElapsedTime().asSeconds() >= 0.5f) {
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
			nextPos.y < fieldHeight && fieldState[nextPos.x][nextPos.y] == false) {
			pos = nextPos;
		}
		else {
			if (action == Action::MOVEDOWN) {
				fieldState[pos.x][pos.y] = true;
				pos = origin;
			}
		}

		w.clear();

		for (int x = 0; x < fieldWidth; x++) {
			for (int y = 0; y < fieldHeight; y++) {
				if (fieldState[x][y]) {
					block.setPosition(float(x * blockWidth), float(y * blockHeight));
					w.draw(block);
				}
			}
		}

		block.setPosition(float(pos.x* blockWidth), float(pos.y* blockHeight));
		
		w.draw(block);
		w.display();
	}

	return EXIT_SUCCESS;
}