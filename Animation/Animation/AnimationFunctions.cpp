#include "stdafx.h"
#include "Shapes.h"
#include "AnimationFunctions.h"

void SyncRotateShapes(SShapes & shapes)
{
	for (size_t i = 0; i < shapes.itemList.size(); ++i)
	{
		shapes.itemList[i].rotate(3);
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
	for (size_t i = 0; (i < shapes.itemList.size()) && (shapes.itemList.back().getPosition() != stopCoordinates); ++i)
	{
		newPosition = shapes.itemList[i].getPosition();
		newPosition += moveCoordinates;
		shapes.itemList[i].setPosition(newPosition);
	}

	return !(((newPosition.x == stopCoordinates.x) && (moveCoordinates.x != 0)) || ((newPosition.y == stopCoordinates.y) && (moveCoordinates.y != 0)));
}

bool ChangeSize(SShapes & shapes, sf::Vector2f increase, sf::Vector2f stopSize)
{
	sf::Vector2f newSize;
	for (size_t i = 0; (i < shapes.itemList.size()) && (shapes.itemList.back().getSize() != stopSize); ++i)
	{
		newSize = shapes.itemList[i].getSize();
		newSize += increase;
		shapes.itemList[i].setSize(newSize);
	}
	return !(shapes.itemList.back().getSize() == stopSize);
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

bool ChangeCoordinatesByY(SShapes & shapes)
{
	sf::Vector2f moveParameters;
	for (size_t i = 0; i < shapes.itemList.size(); ++i)
	{
		moveParameters.x = (i == 0) ? 0.0f : 1.0f;
		moveParameters.y = 1;
		if (shapes.itemList[i].getPosition().x < shapes.itemList[0].getPosition().x)
		{
			shapes.itemList[i].move(moveParameters);
		}
	}
	return (shapes.itemList.back().getPosition().x != shapes.itemList.front().getPosition().x);
}

bool ChangeCoordinatesByX(SShapes & shapes)
{
	sf::Vector2f moveParameters(1, 1);
	for (size_t i = 0; i < shapes.itemList.size(); ++i)
	{
		if (shapes.itemList[i].getPosition().y < shapes.itemList.back().getPosition().y)
		{
			shapes.itemList[i].move(moveParameters);
		}
	}
	return (shapes.itemList.back().getPosition().y != shapes.itemList.front().getPosition().y);
}

bool ConfigurateLadder(SShapes & shapes)
{
	const float ladderHeight = MAIN_SIZE + DISTANCE;
	for (size_t i = 0; i < shapes.itemList.size(); ++i)
	{
		if (shapes.itemList[i].getPosition().y > SCREEN_SIZE - FRAME - ladderHeight * (i + 1))
		{
			shapes.itemList[i].move(sf::Vector2f(0, -1));
		}
	}
	return (shapes.itemList.back().getPosition().y != FRAME);
}

bool ToSinglePosition(SShapes & shapes)
{
	sf::Vector2f moveParameters;
	for (size_t i = 0; i < shapes.itemList.size(); ++i)
	{
		moveParameters.x = (i == shapes.itemList.size() - 1) ? 0.0f : -1.0f;
		moveParameters.y = -1;
		if (shapes.itemList[i].getPosition().x > shapes.itemList.back().getPosition().x)
		{
			shapes.itemList[i].move(moveParameters);
		}
	}
	return (shapes.itemList.back().getPosition() != shapes.itemList.front().getPosition());
}

bool ConfigurateInline(SShapes & shapes)
{
	sf::Vector2f moveParameters(1, 0);
	for (size_t i = 1; i < shapes.itemList.size(); ++i)
	{
		if (shapes.itemList[i].getPosition().x < shapes.itemList.front().getPosition().x + (MAIN_SIZE + DISTANCE)*i)
		{
			shapes.itemList[i].move(moveParameters);
		}
	}
	return (shapes.itemList.back().getPosition().x != shapes.itemList.front().getPosition().x + (MAIN_SIZE + DISTANCE) * (shapes.itemList.size() - 1));
}

void ProcessAnimation(SShapes & shapes)
{
	sf::Vector2f moveParameters(1, 0);
	sf::Vector2f sizeIncrease;
	sf::Vector2f stopCoordinates(SCREEN_SIZE - FRAME - MAIN_SIZE, SCREEN_SIZE);
	sf::Vector2f stopSize;

	switch (shapes.animationIndex)
	{
	case 0:
		if (!ChangeOpacity(shapes, -1, 100))
			++shapes.animationIndex;
		break;
	case 1:
		if (!ChangeCoordinatesByY(shapes))
			++shapes.animationIndex;
		break;
	case 2:
		ChangeOpacity(shapes, 1, 250);
		moveParameters = sf::Vector2f(-1, 0);
		stopCoordinates = sf::Vector2f(SCREEN_SIZE / 2, SCREEN_SIZE / 2);
		if (!MoveByLine(shapes, moveParameters, stopCoordinates))
			++shapes.animationIndex;
		break;
	case 3:
		sizeIncrease = sf::Vector2f(-0.5, -0.5);
		stopSize = sf::Vector2f(MAIN_SIZE - 20, MAIN_SIZE - 20);
		SyncRotateShapes(shapes);
		if (!ChangeSize(shapes, sizeIncrease, stopSize))
			++shapes.animationIndex;
		break;
	case 4:
		sizeIncrease = sf::Vector2f(0.5, 0.5);
		stopSize = sf::Vector2f(MAIN_SIZE, MAIN_SIZE);
		SyncRotateShapes(shapes);
		if (!ChangeSize(shapes, sizeIncrease, stopSize) && shapes.itemList.front().getRotation() == 0)
			++shapes.animationIndex;
		break;
	case 5:
		ChangeOpacity(shapes, -1, 100);
		moveParameters = sf::Vector2f(-1, 0);
		stopCoordinates = sf::Vector2f(FRAME, FRAME);
		if (!MoveByLine(shapes, moveParameters, stopCoordinates))
			++shapes.animationIndex;
		break;
	case 6:
		if (!ChangeCoordinatesByX(shapes))
			++shapes.animationIndex;
		break;
	case 7:
		if (!ConfigurateLadder(shapes))
			++shapes.animationIndex;
		break;
	case 8:
		SyncRotateShapes(shapes);
		sizeIncrease = sf::Vector2f(0.5, 0.5);
		stopSize = sf::Vector2f(MAIN_SIZE + 20, MAIN_SIZE + 20);
		if (!ChangeOpacity(shapes, 1, 250) && !ChangeSize(shapes, sizeIncrease, stopSize))
			++shapes.animationIndex;
		break;
	case 9:
		SyncRotateShapes(shapes);
		sizeIncrease = sf::Vector2f(-0.5, -0.5);
		stopSize = sf::Vector2f(MAIN_SIZE, MAIN_SIZE);
		if (!ChangeSize(shapes, sizeIncrease, stopSize) && shapes.itemList.front().getRotation() == 0)
			++shapes.animationIndex;
		break;
	case 10:
		if (!ToSinglePosition(shapes))
			++shapes.animationIndex;
		break;
	case 11:
		if (!ConfigurateInline(shapes))
			++shapes.animationIndex;
		break;
	case 12:
		shapes.animationIndex = 0;
		std::reverse(shapes.itemList.begin(), shapes.itemList.end());
		break;
	}
}
