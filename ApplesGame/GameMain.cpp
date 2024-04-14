// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "Constans.h"

int main()
{
	using namespace ApplesGame;

	sf::sleep(sf::milliseconds(16));

	int seed = (int)time(nullptr);
	srand(seed);

	// окно
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples Game!");

	// game initialization
	Game game;
	InitGame(game);


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

		UpdateGame(game, deltaTime);
	
		window.clear();
		DrawGame(game, window);
		window.display();
	}
	
	DeinitializeGame(game);
	return 0;
}
