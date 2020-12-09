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

	sf::Sprite block(blockTexture);
	block.setPosition(fieldWidth / 2 * blocksize.x, 0);

	while (w.isOpen())
	{
		sf::Event evt;
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}
		}

		w.clear();
		w.draw(block);
		w.display();
	}

	return EXIT_SUCCESS;
}