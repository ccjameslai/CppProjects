#include <sfml/Graphics.hpp>
#include <iostream>

int main() {
	sf::Texture texture;
	if (!texture.loadFromFile("block.png")) {
		std::cout << "Texture not found!!" << std::endl;
	}
	
	sf::Sprite snake(texture);
	sf::Sprite food = snake;

	sf::Vector2<float> blockSize(snake.getGlobalBounds().width, snake.getGlobalBounds().height);
	sf::Vector2<int> fieldSize(20, 15);

	sf::Vector2f headPos(3, 4);

	srand(time(NULL));
	sf::Vector2f foodPos(rand()%fieldSize.x, rand()%fieldSize.y);

	sf::VideoMode mode(
		unsigned int (blockSize.x * fieldSize.x),
		unsigned int(blockSize.y * fieldSize.y));

	sf::RenderWindow w(mode, L"³g¦Y³D");
	
	enum class DIRECTION {UP, DOWN, LEFT, RIGHT};
	DIRECTION direction = DIRECTION::RIGHT;

	sf::Clock clock;

	while (w.isOpen()) {
		sf::Event evt;
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}

			if (evt.type == sf::Event::KeyPressed) {
				if (evt.key.code == sf::Keyboard::Up) {
					direction = DIRECTION::UP;
				}
				if (evt.key.code == sf::Keyboard::Down) {
					direction = DIRECTION::DOWN;
				}
				if (evt.key.code == sf::Keyboard::Left) {
					direction = DIRECTION::LEFT;
				}
				if (evt.key.code == sf::Keyboard::Right) {
					direction = DIRECTION::RIGHT;
				}
			}
		}

		w.clear();

		if (clock.getElapsedTime().asSeconds() > 0.4f) {
			if (headPos == foodPos) {
				std::cout << "Eaten" << std::endl;
			}

			if (direction == DIRECTION::RIGHT) {
				headPos.x++;
			}
			if (direction == DIRECTION::LEFT) {
				headPos.x--;
			}
			if (direction == DIRECTION::DOWN) {
				headPos.y++;
			}
			if (direction == DIRECTION::UP) {
				headPos.y--;
			}
			
			clock.restart();
		}
		
		snake.setPosition(headPos.x * blockSize.x, headPos.y * blockSize.y);
		food.setPosition(foodPos.x * blockSize.x, foodPos.y * blockSize.y);

		w.draw(snake);
		w.draw(food);

		w.display();
		
	}
	return EXIT_SUCCESS;
}