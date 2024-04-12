// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const std::string RESOURCES_PATH = "Resources/";
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float INITIAL_SPEED = 100.f; // в секунду
const float PLAYER_SIZE = 20.f;
const float ACCELERATION = 20.f; // ускорение
const int NUM_APPLES = 20;
const int NUM_STONES = 5;
const float APPLE_SIZE = 15.f;
const float STONE_SIZE = 25.f;
const float PAUSE_LENGTH = 3.f;

struct Vector2D {
	float x = 0;
	float y = 0;
};

enum class PlayerDirection {
	Right = 0,
	Up,
	Left,
	Down
};

typedef Vector2D Position2D; //синоним типов

Position2D GetRandomPositionInScreen() {
	Position2D result;
	result.x = rand() / (float)RAND_MAX * SCREEN_WIDTH;
	result.y = rand() / (float)RAND_MAX * SCREEN_HEIGHT;
	return result;
}

bool IsRectangleCollide(Position2D rect1Position, Vector2D rect1Size, 
	Position2D rect2Position, Vector2D rect2Size) {
	float dx = fabs(rect1Position.x - rect2Position.x);
	float dy = fabs(rect1Position.y - rect2Position.y);
	return (dx <= (rect1Size.x + rect2Size.x) / 2.f &&
		dy <= (rect1Size.y + rect2Size.y) / 2.f);
}

bool IsCircleCollide(Position2D circle1Position, float circle1Radius,
	Position2D circle2Position, float circle2Radius) {
	float squareDistance = (circle1Position.x - circle2Position.x) *
		(circle1Position.x - circle2Position.x) +
		(circle1Position.y - circle2Position.y) *
		(circle1Position.y - circle2Position.y);
	float squareRadiusSum = (circle1Radius + circle2Radius) * (circle1Radius + circle2Radius);
	return squareDistance <= squareRadiusSum;

}

struct GameState {
	// player data
	Position2D playerPosition;
	float playerSpeed = INITIAL_SPEED;
	PlayerDirection playerDirection = PlayerDirection::Right;
	sf::RectangleShape playerShape;

	// apples data
	Position2D applesPositions[NUM_APPLES];
	sf::CircleShape applesShape[NUM_APPLES];

	// stones data
	Position2D stonePositions[NUM_STONES];
	sf::RectangleShape stoneShape[NUM_STONES];

	// glodal game data
	int numEatenApples = 0;
	bool isGameFinished = false;
	float timeSinceGameFinish = 0.f;
	sf::RectangleShape background;
};

void InitGame(GameState& gameState) {
	// расположение игрока
	gameState.playerPosition = { SCREEN_WIDTH / 2.f , SCREEN_HEIGHT / 2.f };
	gameState.playerSpeed = INITIAL_SPEED;
	gameState.playerDirection = PlayerDirection::Right; //0 - Право, 1 - Верх, 2 - Лево, 3 - Низ

	// форма игрока
	sf::RectangleShape playerShape;
	gameState.playerShape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
	gameState.playerShape.setFillColor(sf::Color::Blue);
	gameState.playerShape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);//центр игрока
	gameState.playerShape.setPosition(gameState.playerPosition.x, gameState.playerPosition.y);

	// яблочки
	for (int i = 0; i < NUM_APPLES; ++i) {
		gameState.applesPositions[i] = GetRandomPositionInScreen();

		gameState.applesShape[i].setRadius(APPLE_SIZE / 2.f);
		gameState.applesShape[i].setFillColor(sf::Color::Green);
		gameState.applesShape[i].setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);//центр яблочка
		gameState.applesShape[i].setPosition(gameState.applesPositions[i].x, gameState.applesPositions[i].y);
	}

	// камушки 
	for (int i = 0; i < NUM_STONES; ++i) {
		gameState.stonePositions[i] = GetRandomPositionInScreen();

		gameState.stoneShape[i].setSize(sf::Vector2f(STONE_SIZE, STONE_SIZE));
		gameState.stoneShape[i].setFillColor(sf::Color::Red);
		gameState.stoneShape[i].setOrigin(STONE_SIZE / 2.f, STONE_SIZE / 2.f);//центр яблочка
		gameState.stoneShape[i].setPosition(gameState.stonePositions[i].x, gameState.stonePositions[i].y);
	}

	gameState.numEatenApples = 0;
	gameState.isGameFinished = false;
	gameState.timeSinceGameFinish = 0;

	gameState.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	gameState.background.setFillColor(sf::Color::Black);
	gameState.background.setPosition(0.f, 0.f);
}

void UpdateGame(GameState& gameState, float deltaTime) {
	//update game state
	if (!gameState.isGameFinished) {
		// движения
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			gameState.playerDirection = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			gameState.playerDirection = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			gameState.playerDirection = PlayerDirection::Left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			gameState.playerDirection = PlayerDirection::Down;
		}


		// изменение состояния
		switch (gameState.playerDirection) {
		case PlayerDirection::Right: {
			gameState.playerPosition.x += gameState.playerSpeed * deltaTime;
			break;
		}
		case PlayerDirection::Up: {
			gameState.playerPosition.y -= gameState.playerSpeed * deltaTime;
			break;
		}
		case PlayerDirection::Left: {
			gameState.playerPosition.x -= gameState.playerSpeed * deltaTime;
			break;
		}
		case PlayerDirection::Down: {
			gameState.playerPosition.y += gameState.playerSpeed * deltaTime;
			break;
		}
		}


		for (int i = 0; i < NUM_APPLES; ++i) {			
			if (IsCircleCollide(gameState.playerPosition, PLAYER_SIZE / 2.f,
				gameState.applesPositions[i], APPLE_SIZE / 2.f)) {
				gameState.applesPositions[i] = GetRandomPositionInScreen();
				++gameState.numEatenApples;
				gameState.playerSpeed += ACCELERATION;
			}

		}

		for (int i = 0; i < NUM_STONES; ++i) {
			if (IsRectangleCollide(gameState.playerPosition, { PLAYER_SIZE ,PLAYER_SIZE }, 
				gameState.stonePositions[i], {STONE_SIZE, STONE_SIZE })) {
				gameState.isGameFinished = true;
				gameState.timeSinceGameFinish = 0.f;
			}
		}

		//об стенку
		if (gameState.playerPosition.x - PLAYER_SIZE / 2.f < 0.f || 
			gameState.playerPosition.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
			gameState.playerPosition.y - PLAYER_SIZE / 2.f < 0.f || 
			gameState.playerPosition.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT) {

			gameState.isGameFinished = true;
			gameState.timeSinceGameFinish = 0.f;
		}
	}
	else {
		if (gameState.timeSinceGameFinish <= PAUSE_LENGTH) {
			gameState.timeSinceGameFinish += deltaTime;
			gameState.background.setFillColor(sf::Color::Red);
		}
		else {
			gameState.background.setFillColor(sf::Color::Black);
			//перезапуск игрока
			gameState.playerPosition.x = SCREEN_WIDTH / 2.f;
			gameState.playerPosition.y = SCREEN_HEIGHT / 2.f;
			gameState.playerSpeed = INITIAL_SPEED;
			gameState.playerDirection = PlayerDirection::Right;
			//перезапуск яблок
			for (int i = 0; i < NUM_APPLES; ++i) {
				gameState.applesPositions[i] = GetRandomPositionInScreen();
			}
			//перезапуск камней
			for (int i = 0; i < NUM_STONES; ++i) {
				gameState.stonePositions[i] = GetRandomPositionInScreen();
			}
			//перезапуск состояния игры
			int numEatenApples = 0;
			gameState.isGameFinished = false;
			gameState.timeSinceGameFinish = 0.f;
		}
	}
}

void DrawGame(GameState& gameState, sf::RenderWindow& window) {
	window.draw(gameState.background);
	gameState.playerShape.setPosition(gameState.playerPosition.x, gameState.playerPosition.y);
	window.draw(gameState.playerShape);
	for (int i = 0; i < NUM_APPLES; ++i) {
		gameState.applesShape[i].setPosition(gameState.applesPositions[i].x, gameState.applesPositions[i].y);
		window.draw(gameState.applesShape[i]);
	}
	for (int i = 0; i < NUM_STONES; ++i) {
		gameState.stoneShape[i].setPosition(gameState.stonePositions[i].x, gameState.stonePositions[i].y);
		window.draw(gameState.stoneShape[i]);
	}
}

void DeinitializeGame(GameState& gameState) {}

int main()
{
	int seed = (int)time(nullptr);
	srand(seed);

	// окно
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples Game!");

	// game initialization
	GameState gameState;
	InitGame(gameState);


	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();


	while (window.isOpen()) {
		
		// время
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		//обработка событий
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				break;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				window.close();
				break;
			}
		}

		UpdateGame(gameState, deltaTime);
	
		window.clear();
		DrawGame(gameState, window);
		window.display();
	}
	
	DeinitializeGame(gameState);
	return 0;
}
