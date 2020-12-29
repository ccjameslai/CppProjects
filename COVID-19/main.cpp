#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <SFML/Graphics.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <httplib.h>

using namespace std;

int main() {
	httplib::SSLClient client("api.covid19api.com");
	const string data = client.Get("/world/total")->body;

	nlohmann::json j = nlohmann::json::parse(data);

	int confirmed = j["TotalConfirmed"];
	int death = j["TotalDeaths"];

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

	sf::Font font;
	if (!font.loadFromFile("consola.ttf")) {
		return EXIT_FAILURE;
	}

	sf::String confirmedString(std::to_string(confirmed));
	sf::Text confirmedText(confirmedString, font);
	confirmedText.setPosition(200, 20);

	sf::String deathString(std::to_string(death));
	sf::Text deathText(deathString, font);
	deathText.setPosition(200, 80);

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
		w.draw(confirmedText);
		w.draw(deathText);
		w.display();
	}

	return EXIT_SUCCESS;
}