#pragma once

static const unsigned SCREEN_SIZE = 600;
static const float NUM_OF_SHAPES = 10;
static const float DISTANCE = 16;
static const float FRAME = 20;
static const float MAIN_SIZE = 40;
static const float ITER_TIME = 0.008f;
static const sf::Vector2f START_COORDINATES(20.0f, 20.0f);

struct SShapes
{
	std::deque<sf::RectangleShape> itemList;
	size_t animationIndex = 0;
	sf::Color color = sf::Color(255, 69, 0, 200);
};

void InitShapes(SShapes & shapes, sf::RenderWindow & window);