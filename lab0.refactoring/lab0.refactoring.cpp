#include "stdafx.h"
#include <iostream>

static const float GRAVITY_ACCEL = 9.8;
static const float TIME_STEP = 0.1;

using namespace std;

float RequireMaxHeightFromUser();
float GetTimeBy(const float maxHeight);
float GetSpeedBy(const float time);
void InitTimeAndSpeedValues(float & time, float & speed);
void PrintHeight(const float time, const float speed);

int main(int, char *[])
{
	float maxHeightTime, speed;

	InitTimeAndSpeedValues(maxHeightTime, speed);
	bool needToPrintMaxHeight = true;
	printf("There are pairs of values time-height:\n");

	for (float currentTime = 0; currentTime < maxHeightTime * 2; currentTime += TIME_STEP)
	{
		if (currentTime > maxHeightTime && needToPrintMaxHeight)
		{
			needToPrintMaxHeight = false;
			PrintHeight(maxHeightTime, speed);
		}
		PrintHeight(currentTime, speed);
	}
	PrintHeight(maxHeightTime * 2, speed);

	return EXIT_SUCCESS;
}

float RequireMaxHeightFromUser()
{
	float MaxHeight;
	printf("Enter maximum jump height: ");
	if (0 <= scanf_s("%f", &MaxHeight))
	{
		printf("\n" "Expected positive floating-point number." "\n");
		EXIT_FAILURE;
	}
	return MaxHeight;
}

void InitTimeAndSpeedValues(float & time, float & speed)
{
	float maxHeight = RequireMaxHeightFromUser();

	time = GetTimeBy(maxHeight);
	printf("Time when height is maximum = %f\n", time);

	speed = GetSpeedBy(time);
}

float GetTimeBy(const float maxHeight)
{
	return sqrt(maxHeight * 2 / GRAVITY_ACCEL);
}

float GetSpeedBy(const float time)
{
	return (GRAVITY_ACCEL * time);
}

void PrintHeight(const float time, const float speed)
{
	float height = speed * time - 0.5 * GRAVITY_ACCEL * time * time;
	printf("time = %f, height= %f \n", time, height);
}