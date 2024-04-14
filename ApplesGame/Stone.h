#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constans.h"
namespace ApplesGame {

	struct Stone {
		Position2D position;
		sf::Sprite sprite;
	};

	struct Game;

	void InitStone(Stone& stone, const Game& game);
}