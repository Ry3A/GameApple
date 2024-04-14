#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Math.h"
#include "Constans.h"
#include "Player.h"
#include "Apple.h"
#include "Stone.h"
#include "Text.h"

namespace ApplesGame {

	struct Game {
		Player player;
		Apple apples[NUM_APPLES];
		Stone stones[NUM_STONES];

		// glodal game data
		int numEatenApples = 0;
		//int scoreApples = 0;
		bool isGameFinished = false;
		float timeSinceGameFinish = 0.f;
		sf::RectangleShape background;
		TextState textState;
		sf::Sound sound;
		sf::Font font;


		// resources
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture stoneTexture;
		sf::SoundBuffer eatingSound;
		sf::SoundBuffer dieSound;
	};

	void RestartGame(Game& game);
	void InitGame(Game& game);
	void UpdateGame(Game& game, float deltaTime);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void DeinitializeGame(Game& game);
}
