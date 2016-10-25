#pragma once
#include "consts.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <cmath>
#include <deque>

using RectangleList = std::deque <sf::RectangleShape>;

enum struct Direction
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct Snake
{
	RectangleList body;
	Direction direction;
};

void InitSnake(Snake & snake, sf::RectangleShape & bodyPart);
void HandleEventsQueue(sf::RenderWindow & window, Snake & snake);
bool HandleSnakeKeyPress(const sf::Event::KeyEvent & event, Snake & snake);
void UpdateSnake(Snake & snake, float elapsedTime);
void ProcessSnakeBody(Snake & snake);