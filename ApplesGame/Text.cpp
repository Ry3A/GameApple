#include "Text.h"
#include "Game.h"
#include <string>

namespace ApplesGame {
	void InitText(TextState& textState, const sf::Font& font) {
		textState.scoreText.setFont(font);
		textState.scoreText.setCharacterSize(24);
		textState.scoreText.setFillColor(sf::Color::Yellow);


		textState.inputHintText.setFont(font);
		textState.inputHintText.setCharacterSize(24);
		textState.inputHintText.setFillColor(sf::Color::White);
		textState.inputHintText.setString("Use arrow keys to move, ESC to exit");
		textState.inputHintText.setOrigin(GetTextOrigin(textState.inputHintText, { 1.f, 0.f }));

		textState.isGameOverTextVisible = false;
		textState.gameOverText.setFont(font);
		textState.gameOverText.setCharacterSize(48);
		textState.gameOverText.setStyle(sf::Text::Bold);
		textState.gameOverText.setFillColor(sf::Color::Red);
		textState.gameOverText.setString("GAME OVER");
		textState.gameOverText.setOrigin(GetTextOrigin(textState.gameOverText, { 0.5f, 0.5f }));
	}

	void UpdateText(TextState& textState, const struct Game& game, float timeDelta) {
		textState.scoreText.setString("Apples eaten: " + std::to_string(game.numEatenApples));

		textState.isGameOverTextVisible = game.isGameFinished;
		sf::Color gameOverTextColor = (int)game.timeSinceGameFinish % 2 ? sf::Color::Red : sf::Color::Yellow;
		textState.gameOverText.setFillColor(gameOverTextColor);
	}

	void DrawText(TextState& textState, sf::RenderWindow& window) {
		textState.scoreText.setPosition(10.f, 10.f);
		window.draw(textState.scoreText);

		textState.inputHintText.setPosition(window.getSize().x - 10.f, 10.f);
		window.draw(textState.inputHintText);

		if (textState.isGameOverTextVisible)
		{
			textState.gameOverText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
			window.draw(textState.gameOverText);
		}
	}
}

