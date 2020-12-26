#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main() {

	const string data = "{\"TotalConfirmed\": 79828488, \"TotalDeaths\" : 1750474, \"TotalRecovered\" : 44992928}";

	int confirmedPos = data.find(":") + 1;
	int confirmedEnd = data.find(",");
	string confirmed = data.substr(confirmedPos, confirmedEnd - confirmedPos);

	int deadthPos = data.find(":", confirmedEnd) + 1;
	int deadthEnd = data.find(",", deadthPos);
	string deadth = data.substr(deadthPos, deadthEnd - deadthPos);

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
	if (!font.loadFromFile("consola.ttf")) {
		return EXIT_FAILURE;
	}

	sf::String confirmedString(confirmed);
	sf::Text confirmedText(confirmedString, font);
	confirmedText.setPosition(200, 20);

	sf::String deadthString(deadth);
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