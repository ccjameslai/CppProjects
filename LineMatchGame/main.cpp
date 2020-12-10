#include <SFML/Graphics.hpp>

int main() {
	unsigned int fieldWidth = 6;
	unsigned int fieldHeight = 10;

	sf::Texture blockTexture;
	blockTexture.loadFromFile("block.png");
	sf::Vector2i blocksize(blockTexture.getSize());

	sf::String title(L"簡易消行遊戲");
	sf::VideoMode mode(fieldWidth * blocksize.x, fieldHeight * blocksize.y);
	sf::RenderWindow w(mode , title);

	sf::Vector2f pos(0, 0);

	sf::Sprite block(blockTexture);
	block.setPosition(float(fieldWidth / 2 * blocksize.x), pos.y);

	sf::Clock clock;
	while (w.isOpen())
	{
		sf::Event evt;
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}
		}

		if (clock.getElapsedTime().asSeconds() >= 0.5f) {
			pos.y++;
			block.setPosition(float(fieldWidth / 2 * blocksize.x), pos.y * blocksize.y);

			clock.restart();
		}

		w.clear();
		w.draw(block);
		w.display();
	}

	return EXIT_SUCCESS;
}