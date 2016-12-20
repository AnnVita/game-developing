#include "stdafx.h"
#include "Shapes.h"
#include "Draw.h"
#include "AnimationFunctions.h"

void HandleEventsQueue(sf::RenderWindow & window);

void Update(SShapes & shapes, sf::Clock & clock, float & timer, sf::RenderWindow & window);

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

	if (timer > ITER_TIME)
	{
		timer = 0;
		ProcessAnimation(shapes);
	}
}
