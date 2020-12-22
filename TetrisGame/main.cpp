#include <SFML/Graphics.hpp>
using namespace std;

int main() {
	const int fieldWidth = 10;
	const int fieldHeight = 20;

	enum class BlockType {
		None,
		O,
		I,
		L,
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

	sf::Texture greenTexture;
	if (!greenTexture.loadFromFile("green.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("background.png")) {
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

	map<BlockType, vector<vector<sf::Vector2i>>> shapes = {
		// shape O
		{
			BlockType::O,
			{
				{
					sf::Vector2i(0,0),
					sf::Vector2i(1,0),
					sf::Vector2i(0,-1),
					sf::Vector2i(1,-1)
				}
			}
		},
		// shape I
		{
			BlockType::I,
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
				}
			}
		},
		{
			BlockType::L,
			{
				{
					sf::Vector2i(0, -2),
					sf::Vector2i(0, -1),
					sf::Vector2i(0, 0),
					sf::Vector2i(1, 0),
				}
			}
		}
	};
	
	backgroundTexture.setRepeated(true);
	sf::Sprite backgroundSprite(
		backgroundTexture, 
		sf::IntRect(0, 0, windowWidth, windowHeight));

	BlockType currentType = BlockType(rand() % 2 + 1);
	vector<sf::Vector2i> currentShape;
	sf::Sprite currentSprite;
	int currentIndex = 0;

	map<BlockType, sf::Sprite> sprites = {
		{BlockType::I, sf::Sprite(yellowTexture)},
		{BlockType::O, sf::Sprite(blueTexture)},
	};

	enum class Action {
		MOVEDOWN,
		MOVELEFT,
		MOVERIGHT,
		HOLD,
		ROTATE,
	};
	
	sf::Clock clock;

	while (w.isOpen()) {
		sf::Event evt;

		currentShape = shapes[currentType][currentIndex];
		currentSprite = sprites[currentType];

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

				if (evt.key.code == sf::Keyboard::Up) {
					action = Action::ROTATE;
				}
			}
		}

		if (clock.getElapsedTime().asSeconds() >= 0.5f) {
			action = Action::MOVEDOWN;

			clock.restart();
		}

		sf::Vector2i nextPos(pos);
		int nextIndex = currentIndex;
		if (action == Action::ROTATE) {
			nextIndex = (nextIndex + 1) % shapes[currentType].size();
		}
		vector<sf::Vector2i> nextShape = shapes[currentType][nextIndex];

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

		// 檢查下一個位置是否合法
		int countEmpty = 0;
		for (auto s : nextShape) {
			sf::Vector2i np = nextPos + s;
			if (np.x >= 0 && np.x < fieldWidth &&
				np.y < fieldHeight &&
				(np.y < 0 || fieldState[np.x][np.y] == BlockType::None)) {
				countEmpty++;
			}
		}
		
		if (countEmpty == 4) {
			pos = nextPos;
			currentShape = nextShape;
			currentIndex = nextIndex;
		}
		else {
			if (action == Action::MOVEDOWN) {
				for (auto s : currentShape) {
					sf::Vector2i np = pos + s;
					if (np.y >= 0) {
						fieldState[np.x][np.y] = currentType;
					}
				}

				for (int y = 0; y < fieldHeight; y++) {
					bool isFull = true;
					for (int x = 0; x < fieldWidth; x++) {
						if (fieldState[x][y] == BlockType::None) {
							isFull = false;
						}
					}

					if (isFull) {
						for (int ty = y; ty > 0; ty--) {
							for (int x = 0; x < fieldWidth; x++) {
								fieldState[x][ty] = fieldState[x][ty-1];
							}
						}
						for (int x = 0; x < fieldWidth; x++) {
							fieldState[x][0] = BlockType::None;
						}
					}
				}

				pos = origin;
				currentType = BlockType(rand() % 2 + 1);
				currentIndex = 0;
			}
		}

		w.clear();


		w.draw(backgroundSprite);
		// 繪製場地
		for (int x = 0; x < fieldWidth; x++) {
			for (int y = 0; y < fieldHeight; y++) {
				if (fieldState[x][y] == BlockType::None) continue;
				
				sf::Sprite fieldBlock = sprites[fieldState[x][y]];

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