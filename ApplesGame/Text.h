#pragma once
#include "SFML/Graphics.hpp"

namespace ApplesGame
{
	struct TextState
	{
		bool isGameOverTextVisible = false;

		sf::Text scoreText;
		sf::Text inputHintText;
		sf::Text gameOverText;
	};

	void InitText(TextState& textState, const sf::Font& font);
	void UpdateText(TextState& textState, const struct Game& game, float timeDelta);
	void DrawText(TextState& textState, sf::RenderWindow& window);
}
