#include "stdafx.h"
#include "snake.h"
#include "consts.h"
const sf::Color BACKGROUND_COLOR = sf::Color(25, 25, 112);

void Update(sf::Clock & clock, Snake & snake, float & timer);
std::string CreateGameOverString(const Snake & snake);

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::Clock clock;
	float timer = 0.0;

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Snake", sf::Style::Close, settings);

	EatableItems eatableItems;
	Snake snake;
    WallList walls;
	InitGame(snake, eatableItems, walls);

	WindowMessage gameOverMessage;
	InitGameOverMessage(gameOverMessage);

	while (window.isOpen())
	{
		window.clear(BACKGROUND_COLOR);

		HandleEventsQueue(window, snake);

	    Update(clock, snake, timer);

		HandleCollisionsWithEatableItems(snake, eatableItems, walls);

		if (BadCollision(snake, walls))
			KillSnake(snake);

		DrawGame(snake, eatableItems, walls, window);

		if (!snake.isAlive)
		{
			gameOverMessage.messageText.setString(CreateGameOverString(snake));
			DrawWindowMessage(gameOverMessage, window);
		}

		window.display();
	}

	return EXIT_SUCCESS;
}

void Update(sf::Clock & clock, Snake & snake, float & gameTime)
{
	if ((snake.direction != Direction::NONE) && (snake.isAlive))
	{
		const float elapsedTime = clock.getElapsedTime().asSeconds();
		gameTime += elapsedTime;
		clock.restart();
		if (gameTime > ITER_TIME)
		{
			gameTime = 0;
			UpdateSnake(snake);
		}
	}
}

std::string CreateGameOverString(const Snake & snake)
{
	return (GAME_OVER_MESSAGE + std::to_string(snake.body.size()));
}