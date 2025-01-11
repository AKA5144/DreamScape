#include "TimeManagementNeyl.hpp"

sf::Clock* Timer::gameClock = 0;

float Timer::previousTime = 0;
float Timer::currentTime = 0;

Timer::Timer()
{

}

Timer::~Timer()
{
	delete gameClock;
}

void Timer::Init()
{
	gameClock = new sf::Clock();
}

void Timer::Update()
{
	previousTime = currentTime;
	currentTime = GetTotalTime();
}

float Timer::GetTotalTime()
{
	return gameClock->getElapsedTime().asSeconds();
}

float Timer::GetDeltaTime()
{
	return currentTime - previousTime;
}