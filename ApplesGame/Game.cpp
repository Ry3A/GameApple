#include "Game.h"
#include "Text.h"
#include <cassert>
#include <SFML/Audio.hpp>

namespace ApplesGame {

	void RestartGame(Game& game) {
		// игрок
		InitPlayer(game.player, game);

		// яблочки
		for (int i = 0; i < NUM_APPLES; ++i) {
			InitApple(game.apples[i], game);
		}

		// камушки 
		for (int i = 0; i < NUM_STONES; ++i) {
			InitStone(game.stones[i], game);
		}

		game.numEatenApples = 0;
		game.isGameFinished = false;
		game.timeSinceGameFinish = 0;
	}

	void InitGame(Game& game) {
		assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png"));
		assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
		assert(game.stoneTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));
		assert(game.eatingSound.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"));
		assert(game.dieSound.loadFromFile(RESOURCES_PATH + "\\Death.wav"));
		assert(game.font.loadFromFile(RESOURCES_PATH + "\\Fonts\\Roboto-Regular.ttf"));


		game.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		game.background.setFillColor(sf::Color::Black);
		game.background.setPosition(0.f, 0.f);
		InitText(game.textState, game.font);


		RestartGame(game);
	}

	void UpdateGame(Game& game, float deltaTime) {
		//update game state
		if (!game.isGameFinished) {
			// движения
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				game.player.direction = PlayerDirection::Right;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				game.player.direction = PlayerDirection::Up;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				game.player.direction = PlayerDirection::Left;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				game.player.direction = PlayerDirection::Down;
			}


			// изменение состояния
			switch (game.player.direction) {
			case PlayerDirection::Right: {
				game.player.position.x += game.player.speed * deltaTime;
				break;
			}
			case PlayerDirection::Up: {
				game.player.position.y -= game.player.speed * deltaTime;
				break;
			}
			case PlayerDirection::Left: {
				game.player.position.x -= game.player.speed * deltaTime;
				break;
			}
			case PlayerDirection::Down: {
				game.player.position.y += game.player.speed * deltaTime;
				break;
			}
			}


			for (int i = 0; i < NUM_APPLES; ++i) {
				if (IsCircleCollide(game.player.position, PLAYER_SIZE / 2.f,
					game.apples[i].position, APPLE_SIZE / 2.f)) {
					game.apples[i].position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
					game.sound.setBuffer(game.eatingSound);
					game.sound.play();
					++game.numEatenApples;
					game.player.speed += ACCELERATION;
				}

			}

			for (int i = 0; i < NUM_STONES; ++i) {
				if (IsRectangleCollide(game.player.position, { PLAYER_SIZE ,PLAYER_SIZE },
					game.stones[i].position, { STONE_SIZE, STONE_SIZE })) {
					game.isGameFinished = true;
					game.sound.setBuffer(game.dieSound);
					game.sound.play();
					game.timeSinceGameFinish = 0.f;
				}
			}

			//об стенку
			if (game.player.position.x - PLAYER_SIZE / 2.f < 0.f ||
				game.player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
				game.player.position.y - PLAYER_SIZE / 2.f < 0.f ||
				game.player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT) {

				game.isGameFinished = true;
				game.sound.setBuffer(game.dieSound);
				game.sound.play();
				game.timeSinceGameFinish = 0.f;
			}
		}
		else {
			if (game.timeSinceGameFinish <= PAUSE_LENGTH) {
				game.timeSinceGameFinish += deltaTime;
				game.background.setFillColor(sf::Color::Red);
			}
			else {
				game.background.setFillColor(sf::Color::Black);
				RestartGame(game);
			}
		}
		UpdateText(game.textState, game, deltaTime);
	}

	void DrawGame(Game& game, sf::RenderWindow& window) {
		window.draw(game.background);
		DrawPlayer(game.player, window);
		for (int i = 0; i < NUM_APPLES; ++i) {
			game.apples[i].sprite.setPosition(game.apples[i].position.x, game.apples[i].position.y);
			window.draw(game.apples[i].sprite);
		}
		for (int i = 0; i < NUM_STONES; ++i) {
			game.stones[i].sprite.setPosition(game.stones[i].position.x, game.stones[i].position.y);
			window.draw(game.stones[i].sprite);
		}
		DrawText(game.textState, window);
	}

	void DeinitializeGame(Game& game) {}
}
