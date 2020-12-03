#include <sfml/Graphics.hpp>
#include <sfml/Window.hpp>
#include <iostream>
#include <vector>
#include <string>

int main() {
	sf::Texture texture;
	
	sf::Vector2<int> fieldSize(20, 15);

	if (!texture.loadFromFile("block.png")) {
		std::cout << "Texture not found!!" << std::endl;
		return EXIT_FAILURE;
	}

	sf::Font font;
	if (!font.loadFromFile("BROADW.TTF")) {
		return EXIT_FAILURE;
	}

	sf::Text t("score:", font);
	sf::Text s("0", font);
	s.setPosition(t.getLocalBounds().width + 5, 0);

	sf::Sprite block(texture);

	sf::Vector2<float> blockSize(
		block.getGlobalBounds().width, 
		block.getGlobalBounds().height);

	sf::Vector2i food(rand()% fieldSize.x, rand() % fieldSize.y);
	std::vector<sf::Vector2i> snake = { sf::Vector2i(3, 4) };

	srand(unsigned int(time(NULL)));

	sf::VideoMode mode(
		unsigned int (blockSize.x * fieldSize.x),
		unsigned int(blockSize.y * fieldSize.y));

	sf::RenderWindow w(mode, L"³g¦Y³D");
	
	enum class DIRECTION {UP, DOWN, LEFT, RIGHT};
	DIRECTION direction = DIRECTION::RIGHT;

	sf::Clock clock;
	bool isDead = false;
	int count = 0;

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

			if (head.x < 0 || head.x >= fieldSize.x ||
				head.y < 0 || head.y >= fieldSize.y) {
				isDead = true;
			}

			for (size_t i = 1; i < snake.size(); i++) {
				if (head == snake[i]) {
					isDead = true;
				}
			}

			if (!isDead) {
				snake.insert(snake.begin(), head);

				if (head == food) {
					count++;
					s.setString(std::to_string(count));
					
					food.x = rand() % fieldSize.x;
					food.y = rand() % fieldSize.y;
				}
				else {
					snake.pop_back();
				}
			}

			clock.restart();
		}

		if (isDead) {
			w.clear(sf::Color(255, 0, 0));

			if (evt.type == sf::Event::KeyPressed) {
				isDead = false;

				snake = { sf::Vector2i(
					(rand() % (fieldSize.x - 2)) + 1,
					(rand() % (fieldSize.y - 2)) + 1) };

				direction = DIRECTION(rand() % 4);

				count = 0;
				s.setString(std::to_string(count));
			}
		}
		else {
			w.clear();
		}

		w.draw(t);
		w.draw(s);
		
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