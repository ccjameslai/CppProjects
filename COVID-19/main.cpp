#include <SFML/Graphics.hpp>

int main() {
	int confirmed = 100000;
	int death = 1000;

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

	sf::Sprite deadthSprite(deathTexture);
	deadthSprite.setPosition(15, 80);

	sf::Font font;
	if (!font.loadFromFile("SentyGoldenBell.ttf")) {
		return EXIT_FAILURE;
	}

	sf::String confirmedString(std::to_string(confirmed));
	sf::Text confirmedText(confirmedString, font);
	confirmedText.setPosition(200, 20);

	sf::String deadthString(std::to_string(death));
	sf::Text deadthText(deadthString, font);
	deadthText.setPosition(200, 80);

	while (w.isOpen()) {
		sf::Event evt;
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}
		}

		w.clear();
		w.draw(confirmedSprite);
		w.draw(deadthSprite);
		w.draw(confirmedText);
		w.draw(deadthText);
		w.display();
	}

	return EXIT_SUCCESS;
}