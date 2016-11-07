#include "stdafx.h"
#include "snake.h"
#include "consts.h"

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
		window.clear(sf::Color(25, 25, 112));

		HandleEventsQueue(window, snake);

		if ((snake.direction != Direction::NONE) && (snake.isAlive))
		    Update(clock, snake, timer);

		HandleCollisionsWithEatableItems(snake, eatableItems, walls);

		if (BadCollision(snake, walls))
		{
			SnakeDie(snake);
		}

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

void Update(sf::Clock & clock, Snake & snake, float & timer)
{
	const float elapsedTime = clock.getElapsedTime().asSeconds();
	timer += elapsedTime;
	clock.restart();
	if (timer > ITER_TIME)
	{
		timer = 0;
		UpdateSnake(snake, elapsedTime);
	}
}

std::string CreateGameOverString(const Snake & snake)
{
	return (GAME_OVER_MESSAGE + std::to_string(snake.body.size()));
}