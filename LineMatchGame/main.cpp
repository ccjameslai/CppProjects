#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

sf::Vector2f getPixelPosition(
	const sf::Vector2f& pos, 
	const sf::Vector2f& blocksize) {
	return sf::Vector2f(float(pos.x * blocksize.x), float(pos.y * blocksize.y));
}

int main() {
	const int fieldWidth = 6;
	const int fieldHeight = 10;

	srand(time(NULL));
	bool fieldState[fieldWidth][fieldHeight] = {};
	for (int y = fieldHeight - 1; y < fieldHeight; y++) {
		for (int k = 1; k < 3; k++) {
			fieldState[rand()%fieldWidth][y] = true;
		}
	}

	sf::Font font;
	font.loadFromFile("BROADW.TTF");

	sf::Text allClear(sf::String("All Clear"), font);
	sf::Text gameover(sf::String("Game Over"), font);


	sf::Texture blockTexture;
	blockTexture.loadFromFile("block.png");
	sf::Vector2f blocksize(blockTexture.getSize());

	sf::String title(L"簡易消行遊戲");
	sf::VideoMode mode(fieldWidth * blocksize.x, fieldHeight * blocksize.y);
	sf::RenderWindow w(mode , title);

	sf::Vector2f origin(fieldWidth / 2, 0);
	sf::Vector2f pos(origin);

	sf::Sprite block(blockTexture);
	block.setPosition(getPixelPosition(pos, blocksize));

	enum class Action {
		MoveLeft,
		MoveRight,
		MoveDown,
		Hold,
		Drop,
	};

	sf::Clock clock;
	bool isGameOver = false;
	while (w.isOpen())
	{
		Action action = Action::Hold;

		sf::Event evt;
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

				if (evt.key.code == sf::Keyboard::Space) {
					action = Action::Drop;
				}
			}		
		}

		if (isGameOver) {
			if (evt.key.code == sf::Keyboard::R) {

				isGameOver = false;
				
				for (int i = 0; i < fieldWidth; i++) {
					for (int j = 0; j < fieldHeight; j++) {
						fieldState[i][j] = false;
					}
				}

				block.setPosition(getPixelPosition(sf::Vector2f(origin), blocksize));

				for (int y = fieldHeight - 1; y < fieldHeight; y++) {
					for (int k = 1; k < 3; k++) {
						fieldState[rand() % fieldWidth][y] = true;
					}
				}
			}
			continue;
		}

		if (clock.getElapsedTime().asSeconds() >= 0.5f) {
			action = Action::MoveDown;
			clock.restart();
		}

		sf::Vector2f nextPos(pos);
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
		case (Action::Drop):
			for (int y = fieldHeight - 1; y > 0; y--) {
				if (fieldState[int(nextPos.x)][y]) {
					continue;
				}
				nextPos.y = y;
				break;
			}
			break;
		case (Action::Hold):
			break;
		}
		
		if (nextPos.x >= 0 && nextPos.x < fieldWidth &&
			nextPos.y < fieldHeight && fieldState[int(nextPos.x)][int(nextPos.y)] == false) {
			pos = nextPos;
		}
		else {
			if (nextPos.x < 0) {
				pos.x = nextPos.x + fieldWidth;
			}
			
			if (nextPos.x > fieldWidth-1) {
				pos.x = nextPos.x - fieldWidth;
			}

			if (action == Action::MoveDown) {
				fieldState[int(pos.x)][int(pos.y)] = true;

				bool isFull = true;
				for (int x = 0; x < fieldWidth; x++) {
					if (fieldState[x][int(pos.y)] == false) {
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

		w.clear();

		block.setPosition(getPixelPosition(pos, blocksize));
		w.draw(block);

		int cnt = 0;
		for (int x = 0; x < fieldWidth; x++) {
			for (int y = 0; y < fieldHeight; y++) {
				if (fieldState[x][y] == true) {
					cnt++;
					sf::Vector2f obstacle(x, y);
					block.setPosition(getPixelPosition(obstacle, blocksize));
					w.draw(block);
				}
			}
		}

		if (cnt == 0) {
			// w.close();
			allClear.setFillColor(sf::Color(125, 200, 75));
			sf::Vector2f middlePostion(int(fieldWidth / 5), int(fieldHeight / 3));
			allClear.setPosition(getPixelPosition(middlePostion, blocksize));
			w.draw(allClear);

			isGameOver = true;
		}
		else if (fieldState[fieldWidth / 2][0]) {
			gameover.setFillColor(sf::Color::Red);
			sf::Vector2f middlePostion(0.05, fieldHeight / 3);
			gameover.setPosition(getPixelPosition(middlePostion, blocksize));
			w.draw(gameover);

			isGameOver = true;
		}

		w.display();
	}

	return EXIT_SUCCESS;
}