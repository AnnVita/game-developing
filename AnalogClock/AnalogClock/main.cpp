#include "stdafx.h"
#include "const.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <cmath>

const unsigned SCREEN_WIDTH = 800;
const unsigned SCREEN_HEIGHT = 600;
const unsigned CLOCK_CIRCLE_SIZE = 250;
const unsigned CLOCK_CIRCLE_THICKNESS = 10;
const unsigned NUM_OF_DOTS = 60;
const unsigned DIGITS_OFFSET = 40;
const unsigned DOTS_OFFSET = 10;
const unsigned NUM_OF_DIGITS = 12;
const unsigned FONT_SIZE = 30;
const unsigned HOUR_POSITION_FREQUENCY = 5;
const std::string MUSIC_FILE_ADRESS = "resources/clock-tick.wav";
const std::string BACKGROUND_FILE_ADRESS = "resources/clock-image.jpg";
const std::string FONT_FILE_ADRESS = "resources/kaushanscript.ttf";

struct AnalogClock
{
	sf::CircleShape mainCircle;
	sf::CircleShape centerCircle;
	sf::RectangleShape hourHand;
	sf::RectangleShape minuteHand;
	sf::RectangleShape secondsHand;
	sf::CircleShape dots[NUM_OF_DOTS];
	sf::Music clockTick;
	sf::Texture clockBackground;
	sf::Text digitsSignatures[NUM_OF_DIGITS];
	sf::Font digitsSignaturesFont;
};

sf::Vector2f GetWindowCenter(sf::RenderWindow & window);

bool IsHourTimePosition(size_t position);

void InitDots(sf::CircleShape dots[NUM_OF_DOTS], sf::RenderWindow & window);
void InitClock(AnalogClock & clock, sf::RenderWindow & window);
void InitDigitSignatures(sf::Text digit[NUM_OF_DIGITS], sf::Font & fontForSignature, const sf::Vector2f & windowCenter);
void InitMainCircle(sf::CircleShape & mainCircle, sf::RenderWindow & window);
void InitCenterCircle(sf::CircleShape & centerCircle, sf::Vector2f & windowCenter);
void InitHourHand(sf::RectangleShape & hourHand, sf::Vector2f & windowCenter);
void InitMinuteHand(sf::RectangleShape & minuteHand, sf::Vector2f & windowCenter);
void InitSecondsHand(sf::RectangleShape & secondsHand, sf::Vector2f & windowCenter);

void StartClockTicking(sf::Music & clockTick, const std::string & fileAdress);
void SetTexture(sf::CircleShape & subject, sf::Texture & background, const std::string & fileAdress);

float GetTimeAngle(const size_t circleDelimiter);

void HandleEventsQueue(sf::RenderWindow & window);
void SetHandsRotation(AnalogClock & clock);
void DisplayClock(AnalogClock & clock, sf::RenderWindow & window);

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Analog Clock", sf::Style::Close, settings);

	AnalogClock myClock;
	InitClock(myClock, window);
	StartClockTicking(myClock.clockTick, MUSIC_FILE_ADRESS);
	
	while (window.isOpen())
	{
		HandleEventsQueue(window);

		SetHandsRotation(myClock);

		DisplayClock(myClock, window);
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
	InitDigitSignatures(clock.digitsSignatures, clock.digitsSignaturesFont, windowCenter);

	InitMainCircle(clock.mainCircle, window);
	InitCenterCircle(clock.centerCircle, windowCenter);

	SetTexture(clock.mainCircle, clock.clockBackground, BACKGROUND_FILE_ADRESS);

	InitHourHand(clock.hourHand, windowCenter);
	InitMinuteHand(clock.minuteHand, windowCenter);
	InitSecondsHand(clock.secondsHand, windowCenter);
}

void InitDots(sf::CircleShape dots[NUM_OF_DOTS], sf::RenderWindow & window)
{
	size_t x, y;
	float angle = 0.0;
	const size_t dotsDrawRadius = CLOCK_CIRCLE_SIZE - DOTS_OFFSET;
	for (size_t i = 0; i < NUM_OF_DOTS; i++)
	{
		x = dotsDrawRadius * cos(angle);
		y = dotsDrawRadius * sin(angle);
		dots[i] = (IsHourTimePosition(i)) ? sf::CircleShape(5) : sf::CircleShape(3);
		dots[i].setFillColor(sf::Color (127, 255, 212));
		dots[i].setOrigin(dots[i].getGlobalBounds().width / 2, dots[i].getGlobalBounds().height / 2);
		dots[i].setPosition(x + window.getSize().x / 2, y + window.getSize().y / 2);

		angle += GetTimeAngle(NUM_OF_DOTS);
	}
}

void InitDigitSignatures(sf::Text digit[NUM_OF_DIGITS], sf::Font & fontForSignature, const sf::Vector2f & windowCenter)
{
	if (!fontForSignature.loadFromFile(FONT_FILE_ADRESS))
	{
		exit(EXIT_FAILURE);
	}

	float angle = 0;

	sf::Text text("", fontForSignature, FONT_SIZE);
	text.setFillColor(sf::Color (127, 255, 212));
	sf::Vector2f digitPosition(0, 0);

	for (size_t i = 0; i < NUM_OF_DOTS; ++i)
	{
		digitPosition.x = (CLOCK_CIRCLE_SIZE - DIGITS_OFFSET) * cos(angle - M_PI / 3);
		digitPosition.y = (CLOCK_CIRCLE_SIZE - DIGITS_OFFSET) * sin(angle - M_PI / 3);
		if (IsHourTimePosition(i))
		{
			text.setString(std::to_string(i / HOUR_POSITION_FREQUENCY + 1));
			digit[i / HOUR_POSITION_FREQUENCY] = text;
			sf::Vector2f positionText(digitPosition + windowCenter);
			digit[i / HOUR_POSITION_FREQUENCY].setPosition(positionText.x, positionText.y - digit[i / HOUR_POSITION_FREQUENCY].getGlobalBounds().height / 2.f);
			digit[i / HOUR_POSITION_FREQUENCY].setOrigin(digit[i / HOUR_POSITION_FREQUENCY].getGlobalBounds().width / 2.f, digit[i / HOUR_POSITION_FREQUENCY].getGlobalBounds().height / 2.f);
		}
		angle += GetTimeAngle(NUM_OF_DOTS);
	}
}

bool IsHourTimePosition(size_t position)
{
	return (position % HOUR_POSITION_FREQUENCY == 0);
}

float GetTimeAngle(const size_t circleDelimiter)
{
	return ((2 * M_PI) / NUM_OF_DOTS);
}

void InitMainCircle(sf::CircleShape & mainCircle, sf::RenderWindow & window)
{
	mainCircle.setRadius(CLOCK_CIRCLE_SIZE);
	mainCircle.setPointCount(100);
	mainCircle.setOutlineThickness(CLOCK_CIRCLE_THICKNESS);
	mainCircle.setOutlineColor(sf::Color (32, 178, 170));
	mainCircle.setOrigin(mainCircle.getGlobalBounds().width / 2, mainCircle.getGlobalBounds().height / 2);
	mainCircle.setPosition(window.getSize().x / 2 + CLOCK_CIRCLE_THICKNESS, window.getSize().y / 2 + CLOCK_CIRCLE_THICKNESS);
}

void SetTexture(sf::CircleShape & subject, sf::Texture & background, const std::string & fileAdress)
{
	if (!background.loadFromFile(fileAdress))
	{
		exit(EXIT_FAILURE);
	}

	subject.setTexture(&background);
	subject.setTextureRect(sf::IntRect(40, 0, 500, 500));
}

void InitCenterCircle(sf::CircleShape & centerCircle, sf::Vector2f & windowCenter)
{
	centerCircle.setRadius(10);
	centerCircle.setPointCount(100);
	centerCircle.setFillColor(sf::Color (127, 255, 212));
	centerCircle.setOrigin(centerCircle.getGlobalBounds().width / 2, centerCircle.getGlobalBounds().height / 2);
	centerCircle.setPosition(windowCenter);
}

void InitHourHand(sf::RectangleShape & hourHand, sf::Vector2f & windowCenter)
{
	hourHand.setSize(sf::Vector2f(5, 180));
	hourHand.setFillColor(sf::Color (32, 178, 170));
	hourHand.setOrigin(hourHand.getGlobalBounds().width / 2, hourHand.getGlobalBounds().height - 25);
	hourHand.setPosition(windowCenter);
}

void InitMinuteHand(sf::RectangleShape & minuteHand, sf::Vector2f & windowCenter)
{
	minuteHand.setSize(sf::Vector2f(3, 240));
	minuteHand.setFillColor(sf::Color (32, 178, 170));
	minuteHand.setOrigin(minuteHand.getGlobalBounds().width / 2, minuteHand.getGlobalBounds().height - 25);
	minuteHand.setPosition(windowCenter);
}

void InitSecondsHand(sf::RectangleShape & secondsHand, sf::Vector2f & windowCenter)
{
	secondsHand.setSize(sf::Vector2f(2, 250));
	secondsHand.setFillColor(sf::Color (127, 255, 212));
	secondsHand.setOrigin(secondsHand.getGlobalBounds().width / 2, secondsHand.getGlobalBounds().height - 25);
	secondsHand.setPosition(windowCenter);
}

void StartClockTicking(sf::Music & clockTick, const std::string & fileAdress)
{
	if (!clockTick.openFromFile(MUSIC_FILE_ADRESS))
	{
		exit(EXIT_FAILURE);
	}
	clockTick.setLoop(true);
	clockTick.play();
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

void SetHandsRotation(AnalogClock & clock)
{
	time_t currentTime = time(NULL);
	tm * ptm = new tm();
	localtime_s(ptm, &currentTime);

	clock.hourHand.setRotation(static_cast<float>(ptm->tm_hour * 30 + (ptm->tm_min / 2)));
	clock.minuteHand.setRotation(static_cast<float>(ptm->tm_min * 6 + (ptm->tm_sec / 12)));
	clock.secondsHand.setRotation(static_cast<float>(ptm->tm_sec * 6));
}

void DisplayClock(AnalogClock & clock, sf::RenderWindow & window)
{
	window.clear(sf::Color (25, 25, 112));
	window.draw(clock.mainCircle);

	for (size_t i = 0; i < NUM_OF_DOTS; ++i)
	{
		window.draw(clock.dots[i]);
		if (i % 5 == 0)
		{
			window.draw(clock.digitsSignatures[i / 5]);
		}
	}

	window.draw(clock.hourHand);
	window.draw(clock.minuteHand);
	window.draw(clock.secondsHand);
	window.draw(clock.centerCircle);

	window.display();
}