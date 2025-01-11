#ifndef CREAMATHS_H
#define CREAMATHS_H

#include "Common.h"
#include <math.h>

#define PI 3.1415926f

class CreaMaths
{
public:
	static float GetVectorLength(sf::Vector2f vector);
	static float GetSquaredLength(sf::Vector2f vector);
	static float DotProduct(sf::Vector2f v1, sf::Vector2f v2);
	static sf::Vector2f NormalizeVector(sf::Vector2f vector);
	static sf::Vector2f RotateVector(sf::Vector2f vector, float angle);
	static float DegreesToRadians(float angle);
	static float RadiansToDegrees(float angle);

	static sf::Vector2f CreateVector(sf::Vector2f point1, sf::Vector2f point2);
	static float GetSquared(float val);
	static float GetCubic(float val);
	static float GetDistance(sf::Vector2f vect);
	static float GetSquaredDistance(sf::Vector2f vect);
	static float GetRandomFloat(float min, float max);
	static sf::Vector2f GetNormalVector(sf::Vector2f vect);
	static float GetAngleBetween(sf::Vector2f vect1, sf::Vector2f vect2);
	static void Clamp(float& val, float min, float max);
	static void ClampLength(sf::Vector2f& vector, float maxLength);
	static bool IsInBetween(float val, float min, float max);
	static bool IsInVisionCone();
};

#endif