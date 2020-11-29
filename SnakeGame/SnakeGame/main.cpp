#include <sfml/Graphics.hpp>
#include <iostream>

int main() {
	sf::Texture texture;
	if (!texture.loadFromFile("block.png")) {
		std::cout << "Texture not found!!" << std::endl;
	}
	
	sf::Sprite block(texture);
	sf::Vector2<float> blockSize(block.getGlobalBounds().width, block.getGlobalBounds().height);

	sf::Vector2<int> fieldSize(20, 15);
	sf::Vector2f head(3, 4);

	sf::VideoMode mode(blockSize.x * fieldSize.x, blockSize.y * fieldSize.y);
	sf::RenderWindow w(mode, L"³g¦Y³D");
	
	

	while (w.isOpen()) {
		sf::Event evt;
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}
		}

		block.setPosition(head.x * fieldSize.x, head.y * fieldSize.y);
		w.draw(block);

		/*for (int i = 0; i < fieldSize.x; i++) {
			for (int j = 0; j < fieldSize.y; j++) {
				sf::Vector2<float> pos(i * blockSize.x, j * blockSize.y);
				block.setPosition(pos);
				w.draw(block);
			}
		}*/

		w.display();
		
	}
	return EXIT_SUCCESS;
}