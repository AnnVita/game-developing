#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

static const unsigned SCREEN_WIDTH = 1000;
static const unsigned SCREEN_HEIGHT = 600;
static const unsigned NUM_OF_SHAPES = 8;
static const unsigned MAIN_CIRCLE_RADIUS = 200;
static const unsigned MAIN_WIDTH = 60;
static const unsigned MAIN_HEIGHT = 60;

struct SShapes
{
	sf::RectangleShape itemList[NUM_OF_SHAPES];
	size_t animationIndex = 0;
	unsigned int circleRadius = MAIN_CIRCLE_RADIUS;
	unsigned int width = MAIN_WIDTH;
	unsigned int height = MAIN_HEIGHT;
	sf::Color color = sf::Color::Cyan;
	float rotationAngle = 0.0;
};

sf::Vector2f GetWindowCenter(sf::RenderWindow & window);
void HandleEventsQueue(sf::RenderWindow & window);
void InitShapes(SShapes & shapes, sf::RenderWindow & window);

void RotateShapes(SShapes & shapes);
void MoveByCircle(SShapes & shapes, sf::RenderWindow & window);
void MoveByLine(SShapes & shapes, sf::RenderWindow & window);

void Update(SShapes & shapes, sf::RenderWindow & window);

void DrawShapes(SShapes & shapes, sf::RenderWindow & window);

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Animation", sf::Style::Close, settings);
	SShapes myShapes;
	InitShapes(myShapes, window);

	while (window.isOpen())
	{
		HandleEventsQueue(window);
		
		Update(myShapes, window);

		DrawShapes(myShapes, window);
		window.display();
	}
    return 0;
}

sf::Vector2f GetWindowCenter(sf::RenderWindow & window)
{
	return sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
}

void InitShapes(SShapes & shapes, sf::RenderWindow & window)
{
	size_t x, y;
	for (size_t i = 0; i < NUM_OF_SHAPES; i++)
	{
		x = shapes.circleRadius * cos(shapes.rotationAngle);
		y = shapes.circleRadius * sin(shapes.rotationAngle);

		shapes.itemList[i].setPosition(x + window.getSize().x / 2, y + window.getSize().y / 2);
		shapes.itemList[i].setSize(sf::Vector2f(shapes.width, shapes.height));
		shapes.itemList[i].setFillColor(shapes.color);

		shapes.rotationAngle += ((2 * M_PI) / NUM_OF_SHAPES);
	}
}

void HandleEventsQueue(sf::RenderWindow & window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Update(SShapes & shapes, sf::RenderWindow & window)
{
	RotateShapes(shapes);
	//MoveByCircle(shapes, window);
}

void DrawShapes(SShapes & shapes, sf::RenderWindow & window)
{
	window.clear(sf::Color(25, 25, 112));

	for (size_t i = 0; i < NUM_OF_SHAPES; ++i)
	{
		window.draw(shapes.itemList[i]);
	}
}

void RotateShapes(SShapes & shapes)
{
	for (size_t i = 0; i < NUM_OF_SHAPES; i++)
	{
		shapes.itemList[i].rotate(10);
	}
}

void MoveByCircle(SShapes & shapes, sf::RenderWindow & window)
{
	size_t x, y;
	for (size_t i = 0; i < NUM_OF_SHAPES; i++)
	{
		x = shapes.circleRadius * cos(shapes.rotationAngle);
		y = shapes.circleRadius * sin(shapes.rotationAngle);

		shapes.itemList[i].setPosition(x + window.getSize().x / 2, y + window.getSize().y / 2);

		shapes.rotationAngle += 2;
		if (shapes.rotationAngle > 6.2f)
		{
			shapes.rotationAngle = 0;
		}
	}
}