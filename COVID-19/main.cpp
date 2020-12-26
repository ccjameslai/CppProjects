#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow w(sf::VideoMode(400, 160), L"COVID-19");

	sf::Texture confirmedTexture;
	if (!confirmedTexture.loadFromFile("confirmed.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture deathTexture;
	if (!deathTexture.loadFromFile("death.png")) {
		return EXIT_FAILURE;
	}

	sf::Sprite confirmedSprite(confirmedTexture);
	confirmedSprite.setPosition(15, 20);

	sf::Sprite deathSprite(deathTexture);
	deathSprite.setPosition(15, 80);


	while (w.isOpen()) {
		sf::Event evt;
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}
		}

		w.clear();
		w.draw(confirmedSprite);
		w.draw(deathSprite);
		w.display();
	}

	return EXIT_SUCCESS;
}