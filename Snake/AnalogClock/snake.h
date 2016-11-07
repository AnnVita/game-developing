#pragma once
#include "consts.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <cmath>
#include <deque>
#include <string> 

static const std::string FONT_FILE_ADRESS = "resources/montserrat.ttf";
static const std::string GAME_OVER_MESSAGE = "Game Over :( \n You snake length == ";

using CircleList = std::deque <sf::CircleShape>;
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
	REVERSIVE
};

struct Snake
{
	CircleList body;
	Direction direction;
	bool isAlive;
};

struct WindowMessage
{
	sf::RectangleShape background;
	sf::Font textFont;
	sf::Text messageText;
};

void InitGame(Snake & snake, EatableItems & eatableItems, WallList & walls);
void InitSnake(Snake & snake);
void InitWallList(WallList & walls);
void InitEatableItems(EatableItems & eatableItems, const WallList & walls);
void InitGameOverMessage(WindowMessage & gameOverMessage);

void HandleEventsQueue(sf::RenderWindow & window, Snake & snake);
bool HandleSnakeKeyPress(const sf::Event::KeyEvent & event, Snake & snake);

void UpdateSnake(Snake & snake, float elapsedTime);
void ProcessSnakeBody(Snake & snake);

bool BadCollision(Snake & snake, WallList & walls);
bool HappenedCollisionWithBody(const Snake & snake);
bool HappenedCollisionWithWalls(Snake & snake, WallList & walls);
void SnakeDie(Snake & snake);

void HandleCollisionsWithEatableItems(Snake & snake, EatableItems & eatableItems, const WallList & walls);
FoodType HappenedCollisionWithEatableItem(const Snake & snake, const EatableItems & eatableItems);
void IncreaseSnake(Snake & snake, const int addingAmount);
void DecreaseSnake(Snake & snake, const int deletingAmount);
void ReverseSnake(Snake & snake);

sf::Vector2f GenerateRandomCoordinates(const WallList & walls);
bool IsInsideWall(const sf::Vector2f & comparingItem, const WallList & walls);
bool BadCollision(Snake & snake, WallList & walls);

void DrawWindowMessage(const WindowMessage & windowMessage, sf::RenderWindow & window);
void DrawGame(const Snake & snake, const EatableItems & eatableItems, const WallList & walls, sf::RenderWindow & window);
void DrawEatableItems(const EatableItems & eatableItems, sf::RenderWindow & window);
void DrawWalls(const WallList & walls, sf::RenderWindow & window);
void DrawSnake(const CircleList & snakeBody, sf::RenderWindow & window);