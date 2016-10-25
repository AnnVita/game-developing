#include "stdafx.h"
#include "snake.h"
#include "consts.h"

void Update(sf::Clock & clock, Snake & snake)
{
	const float elapsedTime = clock.getElapsedTime().asSeconds();
	clock.restart();
	UpdateSnake(snake, elapsedTime);
}

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::Clock clock;

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Snake", sf::Style::Close, settings);

	sf::RectangleShape SNAKE_BODY_PART(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	SNAKE_BODY_PART.setPosition(sf::Vector2f(0, 0));

	Snake snake;
	InitSnake(snake, SNAKE_BODY_PART);

	while (window.isOpen())
	{
		window.clear(sf::Color(25, 25, 112));

		HandleEventsQueue(window, snake);
		//CheckBonusCollision()
		Update(clock, snake);

		for (sf::RectangleShape & bodyElement : snake.body)
		{
			window.draw(bodyElement);
		}

		window.display();

	}

	return EXIT_SUCCESS;
}

