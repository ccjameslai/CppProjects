#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <SFML/Graphics.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <httplib.h>
#include <time.h>

using namespace std;

int main() {
	httplib::SSLClient client("api.covid19api.com");
	const string data = client.Get("/world/total")->body;

	nlohmann::json j = nlohmann::json::parse(data);

	int confirmed = j["TotalConfirmed"];
	int death = j["TotalDeaths"];
	int recovered = j["TotalRecovered"];

	sf::RenderWindow w(sf::VideoMode(400, 240), L"COVID-19");

	sf::Texture confirmedTexture;
	if (!confirmedTexture.loadFromFile("confirmed.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture deathTexture;
	if (!deathTexture.loadFromFile("death.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture recoveredTexture;
	if (!recoveredTexture.loadFromFile("recovered.png")) {
		return EXIT_FAILURE;
	}

	sf::Vector2f spritePos(15, 20);
	sf::Vector2f textPos(220, 20);

	sf::Sprite confirmedSprite(confirmedTexture);
	confirmedSprite.setPosition(spritePos.x, spritePos.y);

	sf::Sprite deathSprite(deathTexture);
	deathSprite.setPosition(spritePos.x, spritePos.y + 60);

	sf::Sprite recoveredSprite(recoveredTexture);
	recoveredSprite.setPosition(spritePos.x, spritePos.y + 120);

	sf::Font font;
	if (!font.loadFromFile("consola.ttf")) {
		return EXIT_FAILURE;
	}

	sf::String confirmedString(std::to_string(confirmed));
	sf::Text confirmedText(confirmedString, font);
	confirmedText.setPosition(textPos.x, textPos.y);

	sf::String deathString(std::to_string(death));
	sf::Text deathText(deathString, font);
	deathText.setPosition(textPos.x, textPos.y + 60);

	sf::String recoveredString(std::to_string(recovered));
	sf::Text recoveredText(recoveredString, font);
	recoveredText.setPosition(textPos.x, textPos.y + 120);

	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	char buffer[80];
     
	sf::Font fontDate;
	if (!fontDate.loadFromFile("msjhbd.ttc")) {
		return EXIT_FAILURE;
	}

	strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", &newtime);

	sf::String updateDateString(L"上次更新於: ");

	sf::Text updateDateText(updateDateString + buffer, fontDate, 20);
	updateDateText.setPosition(spritePos.x, spritePos.y + 180);

	while (w.isOpen()) {
		w.setFramerateLimit(33);
		sf::Event evt;
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}
		}

		w.clear();

		w.draw(confirmedSprite);
		w.draw(deathSprite);
		w.draw(recoveredSprite);
		w.draw(updateDateText);

		w.draw(confirmedText);
		w.draw(deathText);
		w.draw(recoveredText);

		w.display();
	}

	return EXIT_SUCCESS;
}