#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

sf::Vector2f getPixelPosition(
	const sf::Vector2i& pos, 
	const sf::Vector2i& blocksize) {
	return sf::Vector2f(float(pos.x * blocksize.x), float(pos.y * blocksize.y));
}

int main() {
	const int fieldWidth = 9;
	const int fieldHeight = 15;

	bool fieldState[fieldWidth][fieldHeight] = {};
	for (int y = 3; y < fieldHeight; y++) {
		for (int k = 1; k < 3; k++) {
			fieldState[rand()%fieldWidth][y] = true;
		}
	}


	sf::Texture blockTexture;
	blockTexture.loadFromFile("block.png");
	sf::Vector2i blocksize(blockTexture.getSize());

	sf::String title(L"簡易消行遊戲");
	sf::VideoMode mode(fieldWidth * blocksize.x, fieldHeight * blocksize.y);
	sf::RenderWindow w(mode , title);

	sf::Vector2i origin(fieldWidth / 2, 0);
	sf::Vector2i pos(origin);

	sf::Sprite block(blockTexture);
	block.setPosition(getPixelPosition(pos, blocksize));

	enum class Action {
		MoveLeft,
		MoveRight,
		MoveDown,
		Hold
	};

	sf::Clock clock; 
	while (w.isOpen())
	{
		sf::Event evt;
		Action action = Action::Hold;

		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}

			if (evt.type == sf::Event::KeyPressed) {
				if (evt.key.code == sf::Keyboard::Left) {
					action = Action::MoveLeft;
				}

				if (evt.key.code == sf::Keyboard::Right) {
					action = Action::MoveRight;
				}

				if (evt.key.code == sf::Keyboard::Down) {
					action = Action::MoveDown;
				}
			}		
		}

		if (clock.getElapsedTime().asSeconds() >= 0.5f) {
			action = Action::MoveDown;
			clock.restart();
		}

		w.clear();

		sf::Vector2i nextPos(pos);
		switch (action) {
		case (Action::MoveDown):
			nextPos.y++;
			break;
		case (Action::MoveLeft):
			nextPos.x--;
			break;
		case (Action::MoveRight):
			nextPos.x++;
			break;
		case (Action::Hold):
			break;
		}
		
		if (nextPos.x >= 0 && nextPos.x < fieldWidth &&
			nextPos.y < fieldHeight && fieldState[nextPos.x][nextPos.y] == false) {
			pos = nextPos;
		}
		else {
			if (action == Action::MoveDown) {
				if (pos.x < 0) {
					pos.x = 0;
				}
				if (pos.x > 8) {
					pos.x = 8;
				}
				fieldState[pos.x][pos.y] = true;

				bool isFull = true;
				for (int x = 0; x < fieldWidth; x++) {
					if (fieldState[x][pos.y] == false) {
						isFull = false;
					}
				}

				if (isFull) {
					for (int y = pos.y; y > 0; y--) {
						for (int x = 0; x < fieldWidth; x++) {
							fieldState[x][y] = fieldState[x][y-1];
						}
					}

					for (int x = 0; x < fieldWidth; x++) {
						fieldState[x][0] = false;
					}
				}

				pos = origin;
			}
		}

		block.setPosition(getPixelPosition(pos, blocksize));
		w.draw(block);

		for (int x = 0; x < fieldWidth; x++) {
			int cnt = 0;
			for (int y = 0; y < fieldHeight; y++) {
				if (fieldState[x][y] == true) {
					cnt++;
					sf::Vector2i obstacle(x, y);
					block.setPosition(getPixelPosition(obstacle, blocksize));
					w.draw(block);
				}
			}
		}

		w.display();
	}

	return EXIT_SUCCESS;
}