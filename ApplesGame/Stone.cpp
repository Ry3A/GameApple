#include "Stone.h"
#include "Game.h"

namespace ApplesGame {

	void InitStone(Stone& stone, const Game& game) {
		stone.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

		stone.sprite.setTexture(game.stoneTexture);
		SetSpriteSize(stone.sprite, STONE_SIZE, STONE_SIZE);
		SetSpriteRelativeOrigin(stone.sprite, 0.5f, 0.5f);
	}
}