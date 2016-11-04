#include "stdafx.h"
#include "snake.h"

void InitSnake(Snake & snake)
{
	sf::CircleShape bodyPart(CELL_SIZE / 2);
	bodyPart.setFillColor(sf::Color::White);
    bodyPart.setPosition(sf::Vector2f(CELL_SIZE * 3, CELL_SIZE * 3));

	snake.direction = Direction::NONE;
	for (size_t i = 0; i < INITIAL_NUMBER_OF_BODY_PARTS; ++i)
	{
		bodyPart.setPosition(i * CELL_SIZE, 0);
		snake.body.push_front(bodyPart);
	}
}

void InitEatableItems(EatableItems & eatableItems)
{
	eatableItems.normal.setRadius(CELL_SIZE / 2);
	eatableItems.normal.setPosition(CELL_SIZE * 3, CELL_SIZE * 3);
	eatableItems.normal.setFillColor(sf::Color::Green);

	eatableItems.bad.setRadius(CELL_SIZE / 2);
	eatableItems.bad.setPosition(CELL_SIZE * 4, CELL_SIZE * 4);
	eatableItems.bad.setFillColor(sf::Color::Red);

	eatableItems.reversive.setRadius(CELL_SIZE / 2);
	eatableItems.reversive.setPosition(CELL_SIZE * 8, CELL_SIZE * 8);
	eatableItems.reversive.setFillColor(sf::Color::Blue);

	eatableItems.big.setRadius(CELL_SIZE);
	eatableItems.big.setPosition(CELL_SIZE * 6, CELL_SIZE * 6);
	eatableItems.big.setFillColor(sf::Color::Green);
}

void InitWallList(WallList & walls)
{
	sf::RectangleShape upWall(sf::Vector2f(SCREEN_WIDTH - CELL_SIZE * 6, CELL_SIZE));
	upWall.setPosition(CELL_SIZE * 3, 0);

	sf::RectangleShape downWall(sf::Vector2f(SCREEN_WIDTH - CELL_SIZE * 6, CELL_SIZE));
	downWall.setPosition(CELL_SIZE * 3, SCREEN_HEIGHT - CELL_SIZE);

	sf::RectangleShape leftWall(sf::Vector2f(CELL_SIZE, SCREEN_HEIGHT - CELL_SIZE * CELL_SIZE * 2));
	leftWall.setPosition(0, CELL_SIZE * CELL_SIZE);

	sf::RectangleShape rightWall(sf::Vector2f(CELL_SIZE, SCREEN_HEIGHT - CELL_SIZE * CELL_SIZE * 2));
	rightWall.setPosition(SCREEN_WIDTH - CELL_SIZE, CELL_SIZE * CELL_SIZE);

	sf::RectangleShape centerVerticalWall(sf::Vector2f(CELL_SIZE, SCREEN_HEIGHT - CELL_SIZE * CELL_SIZE * 2));
	centerVerticalWall.setPosition(SCREEN_WIDTH / 2 , CELL_SIZE * CELL_SIZE);

	sf::RectangleShape centerHorizontalWall(sf::Vector2f(SCREEN_WIDTH - CELL_SIZE * CELL_SIZE * 2, CELL_SIZE));
	centerHorizontalWall.setPosition(CELL_SIZE * CELL_SIZE, SCREEN_HEIGHT / 2);
	
	walls.push_back(upWall);
	walls.push_back(downWall);
	walls.push_back(leftWall);
	walls.push_back(rightWall);
	walls.push_back(centerVerticalWall);
	walls.push_back(centerHorizontalWall);
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
		else if ((event.type == sf::Event::KeyPressed))
		{
			HandleSnakeKeyPress(event.key, snake);
		}
	}
}

bool HandleSnakeKeyPress(const sf::Event::KeyEvent & event, Snake & snake)
{
	bool handled = true;
	if ((event.code == sf::Keyboard::Up) && (snake.direction != Direction::DOWN))
		snake.direction = Direction::UP;
	else if ((event.code == sf::Keyboard::Down) && (snake.direction != Direction::UP))
		snake.direction = Direction::DOWN;
	else if ((event.code == sf::Keyboard::Left) && (snake.direction != Direction::RIGHT))
		snake.direction = Direction::LEFT;
	else if ((event.code == sf::Keyboard::Right) && (snake.direction != Direction::LEFT))
		snake.direction = Direction::RIGHT;
	else
		handled = false;
	return handled;
}

void UpdateSnake(Snake & snake, float elapsedTime)
{
	const float SNAKE_SPEED = CELL_SIZE; // pixels per second.
	const float step = SNAKE_SPEED;
	ProcessSnakeBody(snake);
	sf::Vector2f position = snake.body.front().getPosition();
	switch (snake.direction)
	{
		case Direction::UP:
			position.y = (snake.body.front().getPosition().y > 0) ? position.y - step : SCREEN_HEIGHT;
			break;
		case Direction::DOWN:
			position.y = (snake.body.front().getPosition().y < SCREEN_HEIGHT) ? position.y + step : 0;
			break;
		case Direction::LEFT:
			position.x = (snake.body.front().getPosition().x > 0) ? position.x - step : SCREEN_WIDTH;
			break;
		case Direction::RIGHT:
			position.x = (snake.body.front().getPosition().x < SCREEN_WIDTH - CELL_SIZE) ? position.x + step : 0;
			break;
		case Direction::NONE:
			break;
	}
	snake.body.front().setPosition(position);
}

void ProcessSnakeBody(Snake & snake)
{
	snake.body.pop_back();
	sf::CircleShape headDuplicate = snake.body.front();
	snake.body.push_front(headDuplicate);
}

bool HappenedCollisionWithBody(const Snake & snake)
{
	const sf::Vector2f headCoordinates = snake.body.front().getPosition();
	for (size_t i = 1; i < snake.body.size(); ++i)
	{
		if (headCoordinates == snake.body[i].getPosition())
			return true;
	}
	return false;
}

bool HappenedCollisionWithWalls(Snake & snake, WallList & walls)
{
	sf::Vector2f headCoordinates = snake.body.front().getPosition();
	const int headRadius = snake.body.front().getRadius();
	for (sf::RectangleShape & wall : walls)
	{
		if  (!(((headCoordinates.x < wall.getPosition().x) || (headCoordinates.x + headRadius > wall.getPosition().x + wall.getSize().x)) ||
			((headCoordinates.y < wall.getPosition().y) || (headCoordinates.y + headRadius > wall.getPosition().y + wall.getSize().y))))
			return true;
	}
	return false;
}

FoodType HappenedCollisionWithEatableItem(const Snake & snake, const EatableItems & eatableItems)
{
	const sf::Vector2f headCoordinates = snake.body.front().getPosition();
	if (headCoordinates == eatableItems.normal.getPosition())
		return FoodType::NORMAL;
	else if (headCoordinates == eatableItems.bad.getPosition())
		return FoodType::BAD;
	else if (headCoordinates == eatableItems.reversive.getPosition())
		return FoodType::REVERSIVE;
	else if (headCoordinates == eatableItems.big.getPosition())
		return FoodType::BIG;
	else
		return FoodType::NONE;
}


void IncreaseSnake(Snake & snake, const int addingAmount)
{
	sf::CircleShape tailDuplicate = snake.body.back();
	for (size_t i = 0; i < addingAmount; ++i)
	{
		snake.body.push_back(tailDuplicate);
	}
}

void DecreaseSnake(Snake & snake, const int deletingAmount)
{
	if (snake.body.size() > deletingAmount)
	{ 
		for (size_t i = 0; i < deletingAmount; ++i)
		{
			snake.body.pop_back();
		}
	}
}

void ReverseSnake(Snake & snake)
{
	std::reverse(snake.body.begin(), snake.body.end());
	switch (snake.direction)
	{
	case Direction::DOWN:
		snake.direction = Direction::UP;
		break; 
	case Direction::UP:
		snake.direction = Direction::DOWN;
		break;
	case Direction::LEFT:
		snake.direction = Direction::RIGHT;
		break;
	case Direction::RIGHT:
		snake.direction = Direction::LEFT;
		break;
	}
}

void DrawEatableItems(const EatableItems & eatableItems, sf::RenderWindow & window)
{
	window.draw(eatableItems.normal);
	window.draw(eatableItems.bad);
	window.draw(eatableItems.reversive);
	window.draw(eatableItems.big);
}