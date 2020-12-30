#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <SFML/Graphics.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <httplib.h>
#include <time.h>

using namespace std;

string getCurrentTime();
void updateData(int, sf::Font, sf::Vector2f, int shift=0);
//void updateData(sf::Text&, int, sf::Font, sf::Vector2f, int shift=0);

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

	string timeString = getCurrentTime();
	
	sf::Font fontDate;
	if (!fontDate.loadFromFile("msjhbd.ttc")) {
		return EXIT_FAILURE;
	}

	sf::String updateDateString(L"上次更新於: ");

	sf::Text updateDateText(updateDateString + timeString, fontDate, 20);
	updateDateText.setPosition(spritePos.x, spritePos.y + 180);

	sf::Clock clock;
	const float updateTime = 60.0f;

	while (w.isOpen()) {
		w.setFramerateLimit(33);
		sf::Event evt;
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}
		}

		if (clock.getElapsedTime().asSeconds() > updateTime) {
			httplib::SSLClient client("api.covid19api.com");
			const string data = client.Get("/world/total")->body;

			nlohmann::json j = nlohmann::json::parse(data);

			confirmed = j["TotalConfirmed"];
			death = j["TotalDeaths"];
			recovered = j["TotalRecovered"];

			timeString = getCurrentTime();

			confirmedString = sf::String(std::to_string(confirmed));
			confirmedText = sf::Text(confirmedString, font);
			confirmedText.setPosition(textPos.x, textPos.y);

			deathString = sf::String(std::to_string(death));
			deathText = sf::Text(deathString, font);
			deathText.setPosition(textPos.x, textPos.y + 60);

			recoveredString = sf::String(std::to_string(recovered));
			recoveredText = sf::Text(recoveredString, font);
			recoveredText.setPosition(textPos.x, textPos.y + 120);

			updateDateText = sf::Text(updateDateString + timeString, fontDate, 20);
			updateDateText.setPosition(spritePos.x, spritePos.y + 180);

			clock.restart();
		}

		w.clear();

		w.draw(confirmedSprite);
		w.draw(deathSprite);
		w.draw(recoveredSprite);
		
		w.draw(confirmedText);
		w.draw(deathText);
		w.draw(recoveredText);
		w.draw(updateDateText);

		w.display();
	}

	return EXIT_SUCCESS;
}

string getCurrentTime() {
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	char buffer[80];

	strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", &newtime);
	return buffer;
}

//void updateData(sf::Text& text, int data, sf::Font font, sf::Vector2f pos, int shift) {
//	text = sf::Text(std::to_string(data), font);
//	text.setPosition(pos.x, pos.y + shift);
//}