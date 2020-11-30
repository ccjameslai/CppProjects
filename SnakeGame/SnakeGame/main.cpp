#include <sfml/Graphics.hpp>
#include <iostream>
#include <vector>

int main() {
	sf::Texture texture;
	
	sf::Vector2<int> fieldSize(20, 15);

	if (!texture.loadFromFile("block.png")) {
		std::cout << "Texture not found!!" << std::endl;
		return EXIT_FAILURE;
	}

	sf::Sprite block(texture);

	sf::Vector2<float> blockSize(
		block.getGlobalBounds().width, 
		block.getGlobalBounds().height);

	sf::Vector2i food(rand()% fieldSize.x, rand() % fieldSize.y);
	std::vector<sf::Vector2i> snake = { sf::Vector2i(3, 4) };

	srand(time(NULL));

	sf::VideoMode mode(
		unsigned int (blockSize.x * fieldSize.x),
		unsigned int(blockSize.y * fieldSize.y));

	sf::RenderWindow w(mode, L"³g¦Y³D");
	
	enum class DIRECTION {UP, DOWN, LEFT, RIGHT};
	DIRECTION direction = DIRECTION::RIGHT;

	sf::Clock clock;
	bool isDead = false;

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

		if (clock.getElapsedTime().asSeconds() >= 0.4f) {
			sf::Vector2i head = snake[0];

			if (direction == DIRECTION::RIGHT) {
				head.x++;
			}
			if (direction == DIRECTION::LEFT) {
				head.x--;
			}
			if (direction == DIRECTION::DOWN) {
				head.y++;
			}
			if (direction == DIRECTION::UP) {
				head.y--;
			}

			if (head.x < 0 || head.x > fieldSize.x ||
				head.y < 0 || head.y > fieldSize.y) {
				isDead = true;
			}
			
			snake.insert(snake.begin(), head);

			if (!isDead) {
				if (head == food) {
					std::cout << "Eaten" << std::endl;
				}
				else {
					snake.pop_back();
				}
			}

			clock.restart();
		}

		if (isDead) {
			w.clear(sf::Color(255, 0, 0));
		}
		else {
			w.clear();
		}
		
		
		for (auto body : snake) {
			sf::Vector2f blockPos(body.x * blockSize.x, body.y * blockSize.y);
			block.setPosition(blockPos);
			w.draw(block);
		}
		
		sf::Vector2f foodPos(food.x * blockSize.x, food.y * blockSize.y);
		block.setPosition(foodPos);
		w.draw(block);

		w.display();
		
	}
	return EXIT_SUCCESS;
}