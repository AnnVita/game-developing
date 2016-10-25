#include "stdafx.h"
#include "snake.h"

void InitSnake(Snake & snake, sf::RectangleShape & bodyPart)
{
	snake.direction = Direction::NONE;
	for (size_t i = 0; i < INITIAL_NUMBER_OF_BODY_PARTS; ++i)
	{
		snake.body.push_front(bodyPart);
		snake.body.front().setPosition(0, 0);
	}
}

void HandleEventsQueue(sf::RenderWindow & window, Snake & snake)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			HandleSnakeKeyPress(event.key, snake);
		}
	}
}

bool HandleSnakeKeyPress(const sf::Event::KeyEvent & event, Snake & snake)
{
	bool handled = true;
	switch (event.code)
	{
	case sf::Keyboard::Up:
		snake.direction = Direction::UP;
		break;
	case sf::Keyboard::Down:
		snake.direction = Direction::DOWN;
		break;
	case sf::Keyboard::Left:
		snake.direction = Direction::LEFT;
		break;
	case sf::Keyboard::Right:
		snake.direction = Direction::RIGHT;
		break;
	default:
		handled = false;
		break;
	}
	return handled;
}

void UpdateSnake(Snake & snake, float elapsedTime)
{
	const float SNAKE_SPEED = 100.f; // pixels per second.
	const float step = SNAKE_SPEED * elapsedTime;
	ProcessSnakeBody(snake);
	sf::Vector2f position = snake.body.front().getPosition();
	switch (snake.direction)
	{
	case Direction::UP:
		if (snake.body.front().getPosition().y > 0)
		{
			position.y -= step;
		}
		break;
	case Direction::DOWN:
		if (snake.body.front().getPosition().y < SCREEN_HEIGHT - CELL_SIZE)
		{
			position.y += step;
		}
		break;
	case Direction::LEFT:
		if (snake.body.front().getPosition().x > 0)
		{
			position.x -= step;
		}
		break;
	case Direction::RIGHT:
		if (snake.body.front().getPosition().x < SCREEN_WIDTH - CELL_SIZE)
		{
			position.x += step;
		}
		break;
	case Direction::NONE:
		break;
	}
	snake.body.front().setPosition(position);
}

void ProcessSnakeBody(Snake & snake)
{
	/*snake.body.pop_back();
	sf::RectangleShape headDuplicate = snake.body.front();
	snake.body.push_front(headDuplicate);*/


}