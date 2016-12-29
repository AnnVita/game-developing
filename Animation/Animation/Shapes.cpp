#include "stdafx.h"
#include "Shapes.h"

void InitShapes(SShapes & shapes, sf::RenderWindow & window)
{
	(void)window;

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
