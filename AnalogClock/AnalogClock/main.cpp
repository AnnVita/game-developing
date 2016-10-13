#include "stdafx.h"
#include "const.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <cmath>

const unsigned SCREEN_WIDTH = 800;
const unsigned SCREEN_HEIGHT = 600;
const unsigned CLOCK_CIRCLE_SIZE = 250;
const unsigned CLOCK_CIRCLE_THICKNESS = 2;
const unsigned NUM_OF_DOTS = 60;

struct AnalogClock
{
	sf::CircleShape mainCircle;
	sf::CircleShape centerCircle;
	sf::RectangleShape hourHand;
	sf::RectangleShape minuteHand;
	sf::RectangleShape secondsHand;
	sf::CircleShape dots[NUM_OF_DOTS];
};

sf::Vector2f GetWindowCenter(sf::RenderWindow & window);
void InitDots(sf::CircleShape dots[NUM_OF_DOTS], sf::RenderWindow & window);
void InitClock(AnalogClock & clock, sf::RenderWindow & window);
void InitMainCircle(sf::CircleShape & mainCircle, sf::RenderWindow & window);
void InitCenterCircle(sf::CircleShape & centerCircle, sf::Vector2f & windowCenter);
void InitHourHand(sf::RectangleShape & hourHand, sf::Vector2f & windowCenter);
void InitMinuteHand(sf::RectangleShape & minuteHand, sf::Vector2f & windowCenter);
void InitSecondsHand(sf::RectangleShape & secondsHand, sf::Vector2f & windowCenter);

int main()
{
	// Set multisampling level
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	// Create the window of the application
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Analog Clock", sf::Style::Close, settings);

	AnalogClock myClock;
	InitClock(myClock, window);
	// Create sound effect
	//	sf::Music clockTick;
	//	if (!clockTick.openFromFile("resources/clock-1.wav"))
	//		return EXIT_FAILURE;
	//	clockTick.setLoop(true);
	//	clockTick.play();

	// Use a part of SFML logo as clock brand
	//	sf::Texture clockBrand;
	//	if (!clockBrand.loadFromFile("resources/clock-brand.png"))
	//	{
	//		return EXIT_FAILURE;
	//	}

	/*	sf::Sprite clockBrandSprite;
	clockBrandSprite.setTexture(clockBrand);
	clockBrandSprite.setOrigin(clockBrandSprite.getTextureRect().left + clockBrandSprite.getTextureRect().width / 2.0f,
	clockBrandSprite.getTextureRect().top + clockBrandSprite.getTextureRect().height / 2.0f);

	clockBrandSprite.setPosition(window.getSize().x / 2, window.getSize().y - 100);


	// Create clock background
	sf::Texture clockImage;
	if (!clockImage.loadFromFile("resources/clock-image.png"))
	{
	return EXIT_FAILURE;
	}

	clockCircle.setTexture(&clockImage);
	clockCircle.setTextureRect(sf::IntRect(40, 0, 500, 500));
	*/
	while (window.isOpen())
	{
		// Handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Window closed: exit
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// Get system time
		std::time_t currentTime = std::time(NULL);

		struct tm * ptm = localtime(&currentTime);

		myClock.hourHand.setRotation(ptm->tm_hour * 30 + (ptm->tm_min / 2));
		myClock.minuteHand.setRotation(ptm->tm_min * 6 + (ptm->tm_sec / 12));
		myClock.secondsHand.setRotation(ptm->tm_sec * 6);

		// Clear the window
		window.clear(sf::Color::White);

		// Draw all parts of clock
		window.draw(myClock.mainCircle);

		for (int i = 0; i < NUM_OF_DOTS; i++)
		{
			window.draw(myClock.dots[i]);
		}

	//	window.draw(clockBrandSprite);
		window.draw(myClock.hourHand);
		window.draw(myClock.minuteHand);
		window.draw(myClock.secondsHand);
		window.draw(myClock.centerCircle);

		// Display things on screen
		window.display();
	}

	return EXIT_SUCCESS;
}

sf::Vector2f GetWindowCenter(sf::RenderWindow & window)
{
	return sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
}

void InitClock(AnalogClock & clock, sf::RenderWindow & window)
{
	sf::Vector2f windowCenter = GetWindowCenter(window);

	InitDots(clock.dots, window);
	InitMainCircle(clock.mainCircle, window);
	InitCenterCircle(clock.centerCircle, windowCenter);

	// Create hour, minute, and seconds hands
	InitHourHand(clock.hourHand, windowCenter);
	InitMinuteHand(clock.minuteHand, windowCenter);
	InitSecondsHand(clock.secondsHand, windowCenter);

}

void InitDots(sf::CircleShape dots[NUM_OF_DOTS], sf::RenderWindow & window)
{
	int x, y;
	float angle = 0.0;
	for (int i = 0; i < NUM_OF_DOTS; i++)
	{
		x = (CLOCK_CIRCLE_SIZE - 10) * cos(angle);
		y = (CLOCK_CIRCLE_SIZE - 10) * sin(angle);
		dots[i] = (i % 5 == 0) ? sf::CircleShape(3) : sf::CircleShape(1);
		dots[i].setFillColor(sf::Color::Black);
		dots[i].setOrigin(dots[i].getGlobalBounds().width / 2, dots[i].getGlobalBounds().height / 2);
		dots[i].setPosition(x + window.getSize().x / 2, y + window.getSize().y / 2);

		angle = angle + ((2 * M_PI) / NUM_OF_DOTS);
	}
}

void InitMainCircle(sf::CircleShape & mainCircle, sf::RenderWindow & window)
{
	mainCircle.setRadius(CLOCK_CIRCLE_SIZE);
	mainCircle.setPointCount(100);
	mainCircle.setOutlineThickness(CLOCK_CIRCLE_THICKNESS);
	mainCircle.setOutlineColor(sf::Color::Black);
	mainCircle.setOrigin(mainCircle.getGlobalBounds().width / 2, mainCircle.getGlobalBounds().height / 2);
	mainCircle.setPosition(window.getSize().x / 2 + CLOCK_CIRCLE_THICKNESS, window.getSize().y / 2 + CLOCK_CIRCLE_THICKNESS);
}

void InitCenterCircle(sf::CircleShape & centerCircle, sf::Vector2f & windowCenter)
{
	centerCircle.setRadius(10);
	centerCircle.setPointCount(100);
	centerCircle.setFillColor(sf::Color::Red);
	centerCircle.setOrigin(centerCircle.getGlobalBounds().width / 2, centerCircle.getGlobalBounds().height / 2);
	centerCircle.setPosition(windowCenter);
}

void InitHourHand(sf::RectangleShape & hourHand, sf::Vector2f & windowCenter)
{
	hourHand.setSize(sf::Vector2f(5, 180));
	hourHand.setFillColor(sf::Color::Black);
	hourHand.setOrigin(hourHand.getGlobalBounds().width / 2, hourHand.getGlobalBounds().height - 25);
	hourHand.setPosition(windowCenter);
}

void InitMinuteHand(sf::RectangleShape & minuteHand, sf::Vector2f & windowCenter)
{
	minuteHand.setSize(sf::Vector2f(3, 240));
	minuteHand.setFillColor(sf::Color::Black);
	minuteHand.setOrigin(minuteHand.getGlobalBounds().width / 2, minuteHand.getGlobalBounds().height - 25);
	minuteHand.setPosition(windowCenter);
}

void InitSecondsHand(sf::RectangleShape & secondsHand, sf::Vector2f & windowCenter)
{
	secondsHand.setSize(sf::Vector2f(2, 250));
	secondsHand.setFillColor(sf::Color::Red);
	secondsHand.setOrigin(secondsHand.getGlobalBounds().width / 2, secondsHand.getGlobalBounds().height - 25);
	secondsHand.setPosition(windowCenter);
}

