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

	sf::Vector2i shape[4] = {
		sf::Vector2i(0,0),
		sf::Vector2i(1,0),
		sf::Vector2i(0,-1),
		sf::Vector2i(1,-1)
	};

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

		int countEmpty = 0;
		for (auto s : shape) {
			sf::Vector2i np = nextPos + s;
			if (np.x >= 0 && np.x < fieldWidth &&
				np.y < fieldHeight &&
				(np.y < 0 || fieldState[np.x][np.y] == false)) {
				countEmpty++;
			}
		}
		
		if (countEmpty == 4) {
			pos = nextPos;
		}
		else {
			if (action == Action::MOVEDOWN) {
				for (auto s : shape) {
					sf::Vector2i np = pos + s;
					if (np.y >= 0) {
						fieldState[np.x][np.y] = true;
					}
				}
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

		for (auto s : shape) {
			block.setPosition(float((pos.x + s.x)* blockWidth), float((pos.y + s.y)* blockHeight));
			w.draw(block);
		}
		
		w.display();
	}

	return EXIT_SUCCESS;
}