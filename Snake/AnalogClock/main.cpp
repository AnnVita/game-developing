#include "stdafx.h"
#include "const.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <cmath>
#include <list>

using RectangleList = std::list <sf::RectangleShape>;

const unsigned SCREEN_WIDTH = 1000;
const unsigned SCREEN_HEIGHT = 600;
const unsigned CELL_SIZE = 10;
const unsigned MOVE_STEP = 2;
const unsigned INITIAL_NUMBER_OF_BODY_PARTS = 4;
const unsigned PART_DISTANCE = 10;

void InitSnake(RectangleList & snake, sf::RectangleShape & bodyPart);
void HandleEventsQueue(sf::RenderWindow & window, RectangleList & snake, sf::Vector2f & coordinats);
void MoveSnake(RectangleList & snake, sf::Vector2f & coordinats);
void ProcessSnakeBody(RectangleList & snake);


int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::Vector2f coordinats(CELL_SIZE * 2, CELL_SIZE * 2);
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Snake", sf::Style::Close, settings);

	sf::RectangleShape SNAKE_BODY_PART(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	SNAKE_BODY_PART.setPosition(sf::Vector2f(0, 0));

	RectangleList snake;
	InitSnake(snake, SNAKE_BODY_PART);

	while (window.isOpen())
	{
		window.clear(sf::Color(25, 25, 112));

		HandleEventsQueue(window, snake, coordinats);

		for (sf::RectangleShape & bodyElement : snake)
		{
			window.draw(bodyElement);
		}

		window.display();
	}

	return EXIT_SUCCESS;
}

void HandleEventsQueue(sf::RenderWindow & window, RectangleList & snake, sf::Vector2f & coordinats)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}

	MoveSnake(snake, coordinats);
}

void MoveSnake(RectangleList & snake, sf::Vector2f & coordinats)
{
	if (((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A))) && (coordinats.x > 0))
	{
		ProcessSnakeBody(snake);
		snake.front().move(-static_cast<float>(CELL_SIZE + PART_DISTANCE), 0);
	}
	if (((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D))) && (coordinats.x < SCREEN_WIDTH - CELL_SIZE))
	{
		ProcessSnakeBody(snake);
		snake.front().move(static_cast<float>(1), 0);
	}
	if (((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W))) && (coordinats.y > 0))
	{
		ProcessSnakeBody(snake);
		snake.front().move(0, -static_cast<float>(CELL_SIZE + PART_DISTANCE));
	}
	if (((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S))) && (coordinats.y < SCREEN_HEIGHT - CELL_SIZE))
	{
		ProcessSnakeBody(snake);
		snake.front().move(0, static_cast<float>(CELL_SIZE + PART_DISTANCE));
	}
}

void InitSnake(RectangleList & snake, sf::RectangleShape & bodyPart)
{
	for (size_t i = 0; i <= 2; ++i)
	{
		snake.push_front(bodyPart);
		snake.front().move(CELL_SIZE * i + PART_DISTANCE * i, 0);
	}
}

void ProcessSnakeBody(RectangleList & snake)
{
	snake.pop_back();
	sf::RectangleShape headDublicate = snake.front();
	snake.push_front(headDublicate);
}