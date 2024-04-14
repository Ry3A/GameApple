#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constans.h"

namespace ApplesGame {

	struct Apple {
		Position2D position;
		sf::Sprite sprite;
	};

	struct Game;
	void InitApple(Apple& apple, const Game& game);
}
