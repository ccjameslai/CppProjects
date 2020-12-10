#include <SFML/Graphics.hpp>

sf::Vector2f getPixelPosition(
	const sf::Vector2i& pos, 
	const sf::Vector2i& blocksize) {
	return sf::Vector2f(float(pos.x * blocksize.x), float(pos.y * blocksize.y));
}

int main() {
	unsigned int fieldWidth = 9;
	unsigned int fieldHeight = 15;

	sf::Texture blockTexture;
	blockTexture.loadFromFile("block.png");
	sf::Vector2i blocksize(blockTexture.getSize());

	sf::String title(L"簡易消行遊戲");
	sf::VideoMode mode(fieldWidth * blocksize.x, fieldHeight * blocksize.y);
	sf::RenderWindow w(mode , title);

	sf::Vector2i pos(fieldWidth / 2, 0);

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
			nextPos.y < fieldHeight) {
			pos = nextPos;
		}

		block.setPosition(getPixelPosition(pos, blocksize));
		
		w.draw(block);
		w.display();
	}

	return EXIT_SUCCESS;
}