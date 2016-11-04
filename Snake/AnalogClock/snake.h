#pragma once
#include "consts.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <cmath>
#include <deque>

using RectangleList = std::deque <sf::CircleShape>;
using WallList = std::deque <sf::RectangleShape>;

struct EatableItems
{
	sf::CircleShape normal;
	sf::CircleShape bad;
	sf::CircleShape reversive;
	sf::CircleShape big;
};

enum struct Direction
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum struct FoodType
{
	NONE,
	NORMAL,
	BAD,
	REVERSIVE,
	BIG
};

struct Snake
{
	RectangleList body;
	Direction direction;
};

void InitSnake(Snake & snake);
void InitEatableItems(EatableItems & eatableItems);
void InitWallList(WallList & walls);

void HandleEventsQueue(sf::RenderWindow & window, Snake & snake);
bool HandleSnakeKeyPress(const sf::Event::KeyEvent & event, Snake & snake);

void UpdateSnake(Snake & snake, float elapsedTime);
void ProcessSnakeBody(Snake & snake);

bool HappenedCollisionWithBody(const Snake & snake);
FoodType HappenedCollisionWithEatableItem(const Snake & snake, const EatableItems & eatableItems);
bool HappenedCollisionWithWalls(Snake & snake, WallList & walls);

void IncreaseSnake(Snake & snake, const int addingAmount);
void DecreaseSnake(Snake & snake, const int deletingAmount);
void ReverseSnake(Snake & snake);
void DrawEatableItems(const EatableItems & eatableItems, sf::RenderWindow & window);