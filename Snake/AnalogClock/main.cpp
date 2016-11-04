#include "stdafx.h"
#include <iostream>
#include "snake.h"
#include "consts.h"

static const float ITER_TIME = 0.1;

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

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::Clock clock;
	float timer = 0.0;

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Snake", sf::Style::Close, settings);

	EatableItems eatableItems;
	InitEatableItems(eatableItems);

	FoodType foodCollisionType;

	Snake snake;
	InitSnake(snake);

	WallList walls;
	InitWallList(walls);


	while (window.isOpen())
	{
		window.clear(sf::Color(25, 25, 112));

		HandleEventsQueue(window, snake);

		if (snake.direction != Direction::NONE)
		    Update(clock, snake, timer);

		if (HappenedCollisionWithBody(snake) && (snake.direction != Direction::NONE))
		{
			std::cout << "happened collision with BODY" << std::endl;
			snake.direction = Direction::NONE;
		}

		if (HappenedCollisionWithWalls(snake, walls) && (snake.direction != Direction::NONE))
		{
			std::cout << "happened collision with WALL" << std::endl;
			snake.direction = Direction::NONE;
		}

		if ((foodCollisionType = HappenedCollisionWithEatableItem(snake, eatableItems)) != FoodType::NONE)
		{
			switch (foodCollisionType)
			{
			case FoodType::NORMAL:
				eatableItems.normal.move(CELL_SIZE, CELL_SIZE);
				IncreaseSnake(snake, SNAKE_USIAL_INCREASE);
				break;
			case FoodType::BAD:
				eatableItems.bad.move(CELL_SIZE, CELL_SIZE);
				DecreaseSnake(snake, SNAKE_DECREASE);
				break;
			case FoodType::REVERSIVE:
				eatableItems.reversive.move(CELL_SIZE, CELL_SIZE);
				ReverseSnake(snake);
				break;
			case FoodType::BIG:
				eatableItems.big.move(CELL_SIZE, CELL_SIZE);
				IncreaseSnake(snake, SNAKE_BIG_INCREASE);
				break;
			}
		}

		DrawEatableItems(eatableItems, window);
		
		for (sf::RectangleShape & wall : walls)
		{
			window.draw(wall);
		}

		for (sf::CircleShape & bodyElement : snake.body)
		{
			window.draw(bodyElement);
		}

		window.display();

	}

	return EXIT_SUCCESS;
}

