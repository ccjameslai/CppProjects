#include <SFML/Graphics.hpp>
using namespace std;

int main() {
	const int fieldWidth = 10;
	const int fieldHeight = 20;

	enum class BlockType {
		None,
		O,
		I,
	};

	BlockType fieldState[fieldWidth][fieldHeight] = {};

	sf::Texture blueTexture;
	if (!blueTexture.loadFromFile("blue.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture yellowTexture;
	if (!yellowTexture.loadFromFile("yellow.png")) {
		return EXIT_FAILURE;
	}

	const int blockWidth = blueTexture.getSize().x;
	const int blockHeight = blueTexture.getSize().y;

	const int windowWidth = fieldWidth * blockWidth;
	const int windowHeight = fieldHeight * blockHeight;

	sf::VideoMode mode(windowWidth, windowHeight);
	sf::RenderWindow w(mode, L"俄羅斯方塊");
	
	sf::Vector2i origin(fieldWidth / 2, 0);
	sf::Vector2i pos(origin);

	vector<vector<vector<sf::Vector2i>>> shapes = {
		// shape O
		{
			{
				sf::Vector2i(0,0),
				sf::Vector2i(1,0),
				sf::Vector2i(0,-1),
				sf::Vector2i(1,-1)
			}
		},
		// shape I
		{
			{
				sf::Vector2i(-1,0),
				sf::Vector2i(0,0),
				sf::Vector2i(1,0),
				sf::Vector2i(2,0)
			},
			{
				sf::Vector2i(0,-2),
				sf::Vector2i(0,-1),
				sf::Vector2i(0,0),
				sf::Vector2i(0,1)
			},
		}
	};
		
	BlockType currentType = BlockType(rand() % 2 + 1);
	vector<sf::Vector2i> currentShape;
	sf::Sprite currentSprite;
	
	vector<sf::Sprite> sprites = {
		sf::Sprite(yellowTexture),
		sf::Sprite(blueTexture),
	};

	enum class Action {
		MOVEDOWN,
		MOVELEFT,
		MOVERIGHT,
		HOLD,
	};
	
	sf::Clock clock;

	while (w.isOpen()) {
		sf::Event evt;

		currentShape = shapes[int(currentType) - 1][0];
		currentSprite = sprites[int(currentType) - 1];

		Action action = Action::HOLD;

		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}

			if (evt.type == sf::Event::KeyPressed) {
				if (evt.key.code == sf::Keyboard::Down) {
					action = Action::MOVEDOWN;
				}

				if (evt.key.code == sf::Keyboard::Left) {
					action = Action::MOVELEFT;
				}

				if (evt.key.code == sf::Keyboard::Right) {
					action = Action::MOVERIGHT;
				}
			}
		}

		if (clock.getElapsedTime().asSeconds() >= 0.5f) {
			action = Action::MOVEDOWN;

			clock.restart();
		}

		sf::Vector2i nextPos(pos);

		switch (action) {
		case Action::MOVEDOWN:
			nextPos.y++;
			break;
		case Action::MOVELEFT:
			nextPos.x--;
			break;
		case Action::MOVERIGHT:
			nextPos.x++;
			break;
		case Action::HOLD:
			break;
		}

		int countEmpty = 0;
		for (auto s : currentShape) {
			sf::Vector2i np = nextPos + s;
			if (np.x >= 0 && np.x < fieldWidth &&
				np.y < fieldHeight &&
				(np.y < 0 || fieldState[np.x][np.y] == BlockType::None)) {
				countEmpty++;
			}
		}
		
		if (countEmpty == 4) {
			pos = nextPos;
		}
		else {
			if (action == Action::MOVEDOWN) {
				for (auto s : currentShape) {
					sf::Vector2i np = pos + s;
					if (np.y >= 0) {
						fieldState[np.x][np.y] = currentType;
					}
				}
				pos = origin;
				currentType = BlockType(rand() % 2 + 1);
			}
		}

		w.clear();

		// 繪製場地
		for (int x = 0; x < fieldWidth; x++) {
			for (int y = 0; y < fieldHeight; y++) {
				if (fieldState[x][y] == BlockType::None) continue;
				
				sf::Sprite fieldBlock = sprites[int(fieldState[x][y]) - 1];

				fieldBlock.setPosition(float(x* blockWidth), float(y* blockHeight));
				w.draw(fieldBlock);
			}
		}

		for (auto s : currentShape) {
			currentSprite.setPosition(float((pos.x + s.x)* blockWidth), float((pos.y + s.y)* blockHeight));
			w.draw(currentSprite);
		}
		
		w.display();
	}

	return EXIT_SUCCESS;
}