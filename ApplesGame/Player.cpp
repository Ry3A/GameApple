#include "Player.h"
#include "Game.h"

namespace ApplesGame {

	void InitPlayer(Player& player, const Game& game) {
		player.position = { SCREEN_WIDTH / 2.f , SCREEN_HEIGHT / 2.f };
		player.speed = INITIAL_SPEED;
		player.direction = PlayerDirection::Right; //0 - Право, 1 - Верх, 2 - Лево, 3 - Низ

		player.sprite.setTexture(game.playerTexture);
		//SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);
	}

	void DrawPlayer(Player& player, sf::RenderWindow& window) {
		player.sprite.setPosition(player.position.x, player.position.y);
		switch (player.direction) {
		case PlayerDirection::Up: {
			SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
			player.sprite.setRotation(-90.f);
			break;
		}
		case PlayerDirection::Right: {
			SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
			player.sprite.setRotation(0.f);
			break;
		}
		case PlayerDirection::Down: {
			SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
			player.sprite.setRotation(90.f);
			break;
		}
		case PlayerDirection::Left: {
			SetSpriteSize(player.sprite, PLAYER_SIZE, -PLAYER_SIZE);
			player.sprite.setRotation(180.f);
			break;
		}
		}
		window.draw(player.sprite);
	}
}