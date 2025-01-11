#ifndef TIMEMANAGEMENT_HPP
#define TIMEMANAGEMENT_HPP

#include "SFML/Window.hpp"

class Timer
{
public:
	Timer();
	~Timer();

	static void Init();
	static void Update();
	static float GetTotalTime();
	static float GetDeltaTime();

private:
	static sf::Clock* gameClock;

	static float previousTime;
	static float currentTime;
};

#endif // !TIMEMANAGEMENT_HPP