#include "stdafx.h"
#include <iostream>
#include "snake.h"
#include "consts.h"

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

bool BadCollision(Snake & snake, WallList & walls)
{
	return ((HappenedCollisionWithBody(snake) || (HappenedCollisionWithWalls(snake, walls))) && (snake.direction != Direction::NONE));
}

void DrawEatableItems(const EatableItems & eatableItems, sf::RenderWindow & window)
{
	window.draw(eatableItems.normal);
	window.draw(eatableItems.bad);
	window.draw(eatableItems.reversive);
	window.draw(eatableItems.big);
}

void DrawWalls(const WallList & walls, sf::RenderWindow & window)
{
	for (sf::RectangleShape wall : walls)
	{
		window.draw(wall);
	}
}

void DrawSnake(const CircleList & snakeBody, sf::RenderWindow & window)
{
	for (sf::CircleShape bodyElement : snakeBody)
	{
		window.draw(bodyElement);
	}
}

void DrawWindowMessage(const WindowMessage & windowMessage, sf::RenderWindow & window)
{
	window.draw(windowMessage.background);
	window.draw(windowMessage.messageText);
}

void DrawGame(const Snake & snake, const EatableItems & eatableItems, const WallList & walls, sf::RenderWindow & window)
{
	DrawWalls(walls, window);
	DrawEatableItems(eatableItems, window);
	DrawSnake(snake.body, window);
}

void HandleCollisionsWithEatableItems(Snake & snake, EatableItems & eatableItems, const WallList & walls)
{
	FoodType foodCollisionType;
	if ((foodCollisionType = HappenedCollisionWithEatableItem(snake, eatableItems)) != FoodType::NONE)
	{
		switch (foodCollisionType)
		{
		case FoodType::NORMAL:
			eatableItems.normal.setPosition(GenerateRandomCoordinates(walls));
			IncreaseSnake(snake, SNAKE_USIAL_INCREASE);
			break;
		case FoodType::BAD:
			eatableItems.bad.setPosition(GenerateRandomCoordinates(walls));
			DecreaseSnake(snake, SNAKE_DECREASE);
			break;
		case FoodType::REVERSIVE:
			eatableItems.reversive.setPosition(GenerateRandomCoordinates(walls));
			ReverseSnake(snake);
			break;
		}
	}
}

std::string CreateGameOverString(const Snake & snake)
{
	return (GAME_OVER_MESSAGE + std::to_string(snake.body.size()));
}

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

