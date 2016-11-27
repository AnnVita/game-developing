#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <deque>

static const unsigned SCREEN_SIZE = 600;
static const unsigned NUM_OF_SHAPES = 10;
static const unsigned DISTANCE = 16;
static const unsigned FRAME = 20;
static const unsigned MAIN_SIZE = 40;
static const float ITER_TIME = 0.008f;
static const sf::Vector2f START_COORDINATES(FRAME, FRAME);

struct SShapes
{
	std::deque<sf::RectangleShape> itemList;
	size_t animationIndex = 0;
	sf::Color color = sf::Color(255, 69, 0, 200);
};

sf::Vector2f GetWindowCenter(sf::RenderWindow & window);
void HandleEventsQueue(sf::RenderWindow & window);
void InitShapes(SShapes & shapes, sf::RenderWindow & window);

void SyncRotateShapes(SShapes & shapes);
void AsyncRotateShapes(SShapes & shapes);
bool MoveByLine(SShapes & shapes, sf::Vector2f moveCoordinates, sf::Vector2f stopCoordinates);
bool ChangeSize(SShapes & shapes, sf::Vector2f increase, sf::Vector2f stopSize);
bool ChangeOpacity(SShapes & shapes, int changeSpeed, int stopOpacity);
bool ChangeCoordinates(SShapes & shapes);

void Update(SShapes & shapes, sf::Clock & clock, float & timer, sf::RenderWindow & window);

void DrawShapes(SShapes & shapes, sf::RenderWindow & window);

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE, SCREEN_SIZE), "Animation", sf::Style::Close, settings);
	SShapes myShapes;
	InitShapes(myShapes, window);

	sf::Clock clock;
	float timer = 0.0;

	while (window.isOpen())
	{
		HandleEventsQueue(window);
		
		Update(myShapes, clock, timer, window);

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
	sf::RectangleShape newRectangle;
	newRectangle.setPosition(START_COORDINATES);
	newRectangle.setFillColor(shapes.color);
	newRectangle.setSize(sf::Vector2f(MAIN_SIZE, MAIN_SIZE));

	for (size_t i = 0; i < NUM_OF_SHAPES; i++)
	{
		shapes.itemList.push_front(newRectangle);
		newRectangle.move(MAIN_SIZE + DISTANCE, 0);
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

void Update(SShapes & shapes, sf::Clock & clock, float & timer, sf::RenderWindow & window)
{
	const float elapsedTime = clock.getElapsedTime().asSeconds();
	timer += elapsedTime;
	clock.restart();
	sf::Vector2f moveSpeed(1, 0);
	sf::Vector2f sizeIncrease(0.1, 0.1);
	sf::Vector2f stopCoordinates(SCREEN_SIZE - FRAME - MAIN_SIZE, SCREEN_SIZE);
	if (timer > ITER_TIME)
	{
		timer = 0;

		switch (shapes.animationIndex)
		{
		case 0:
			if (!MoveByLine(shapes, moveSpeed, stopCoordinates))
				++shapes.animationIndex;
			break;
		case 1:
			if (!ChangeOpacity(shapes, -1, 100))
				++shapes.animationIndex;
			break;
		case 2:
			ChangeCoordinates(shapes);
			break;


		}
		/*MoveByLine(shapes, moveCoordinates, window);
		AsyncRotateShapes(shapes);
		ChangeSize(shapes, sizeIncrease, window);
		ChangeOpacity(shapes);
		ChangeCoordinates(shapes, window);*/
	}
	
}

void DrawShapes(SShapes & shapes, sf::RenderWindow & window)
{
	window.clear(sf::Color(255, 255, 224));

	for (size_t i = 0; i < shapes.itemList.size(); ++i)
	{
		window.draw(shapes.itemList[i]);
	}
}

void SyncRotateShapes(SShapes & shapes)
{
	for (size_t i = 0; i < shapes.itemList.size(); ++i)
	{
		shapes.itemList[i].rotate(2);
	}
}

void AsyncRotateShapes(SShapes & shapes)
{
	for (size_t i = 0; i < shapes.itemList.size(); ++i)
	{
		if (i % 2 == 0)
		{
			shapes.itemList[i].rotate(2);
		}
		else
		{
			shapes.itemList[i].rotate(-2);
		}
	}
}

bool MoveByLine(SShapes & shapes, sf::Vector2f moveCoordinates, sf::Vector2f stopCoordinates)
{
	sf::Vector2f newPosition;
	for (size_t i = 0; i < shapes.itemList.size(); ++i)
	{
		newPosition = shapes.itemList[i].getPosition();
		newPosition += moveCoordinates;
		shapes.itemList[i].setPosition(newPosition);
		if (((newPosition.x == stopCoordinates.x) && (moveCoordinates.x != 0)) || ((newPosition.y == stopCoordinates.y) && (moveCoordinates.y != 0)))
		{
			return false;
		}
	}
	
	return true;
}

bool ChangeSize(SShapes & shapes, sf::Vector2f increase, sf::Vector2f stopSize)
{
	sf::Vector2f newSize;
	for (size_t i = 0; i < shapes.itemList.size(); ++i)
	{
		newSize = shapes.itemList[i].getSize();
		newSize += increase;
		shapes.itemList[i].setSize(newSize);
	}

	if (((newSize.x == stopSize.x) && (increase.x != 0)) || ((newSize.y == stopSize.y) && (increase.y != 0)))
	{
		return false;
	}
	return true;
}

bool ChangeOpacity(SShapes & shapes, int changeSpeed, int stopOpacity)
{
	int currentOpacity;
	sf::Color newColor;
	for (size_t i = 0; i < shapes.itemList.size(); ++i)
	{
		currentOpacity = shapes.itemList[i].getFillColor().a;
		newColor = shapes.itemList[i].getFillColor();
		newColor.a = currentOpacity + changeSpeed;
		if (newColor.a == stopOpacity)
		{
			return false;
		}
		shapes.itemList[i].setFillColor(newColor);
	}
	return true;
}

bool ChangeCoordinates(SShapes & shapes)
{
	sf::Vector2f moveParameters;
	for (size_t i = 0; i < shapes.itemList.size(); ++i)
	{
		moveParameters.x = (i == 0) ? 0 : 1;
		moveParameters.y = 1;
		if (shapes.itemList[i].getPosition().x < shapes.itemList[0].getPosition().x)
		{
			shapes.itemList[i].move(moveParameters);
		}
	}
	return true;
}