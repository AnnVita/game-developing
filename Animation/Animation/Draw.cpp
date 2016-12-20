#include "stdafx.h"
#include "Shapes.h"
#include "Draw.h"

void DrawShapes(SShapes & shapes, sf::RenderWindow & window)
{
	window.clear(sf::Color(255, 255, 224));

	for (size_t i = 0; i < shapes.itemList.size(); ++i)
	{
		window.draw(shapes.itemList[i]);
	}
}