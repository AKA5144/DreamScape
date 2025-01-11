#include "CreaMaths.h"

float CreaMaths::GetVectorLength(sf::Vector2f vector)
{
	return sqrtf(vector.x * vector.x + vector.y * vector.y);
}

float CreaMaths::GetSquaredLength(sf::Vector2f vector)
{
	return vector.x * vector.x + vector.y * vector.y;
}

float CreaMaths::DotProduct(sf::Vector2f v1, sf::Vector2f v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

sf::Vector2f CreaMaths::NormalizeVector(sf::Vector2f vector)
{
	float vectorLength = GetVectorLength(vector);

	if (vectorLength == 0.0f)
	{
		return sf::Vector2f(0, 0);
	}

	float newX = vector.x / vectorLength;
	float newY = vector.y / vectorLength;

	return sf::Vector2f(newX, newY);
}

sf::Vector2f CreaMaths::RotateVector(sf::Vector2f vector, float angle)
{
	float COS = cos(angle);
	float SIN = sin(angle);

	float newX = vector.x * COS - vector.y * SIN;
	float newY = vector.x * SIN + vector.y * COS;

	return sf::Vector2f(newX, newY);
}

float CreaMaths::DegreesToRadians(float angle)
{
	return angle * (float)PI / 180;
}

float CreaMaths::RadiansToDegrees(float angle)
{
	return angle * 180 / (float)PI;
}


sf::Vector2f CreaMaths::CreateVector(sf::Vector2f point1, sf::Vector2f point2)
{
	return (point2 - point1);
}

float CreaMaths::GetSquared(float val)
{
	return (val * val);
}

float CreaMaths::GetCubic(float val)
{
	return (val * val * val);
}

float CreaMaths::GetDistance(sf::Vector2f vect)
{
	return (sqrtf(vect.x * vect.x + vect.y * vect.y));
}

float CreaMaths::GetSquaredDistance(sf::Vector2f vect)
{
	return (vect.x * vect.x + vect.y * vect.y);
}

float CreaMaths::GetRandomFloat(float min, float max)
{
	return (rand() % (RAND_MAX + 1)) * (max - min) + min;
}

sf::Vector2f CreaMaths::GetNormalVector(sf::Vector2f vect)
{
	return { -vect.y, vect.x };
}

float CreaMaths::GetAngleBetween(sf::Vector2f vect1, sf::Vector2f vect2)
{
	return -1;
}

void CreaMaths::Clamp(float& val, float min, float max)
{
	if (val >= max)
		val = max;
	if (val <= min)
		val = min;
}

void CreaMaths::ClampLength(sf::Vector2f& vector, float maxLength)
{
	float vectorLength = sqrtf(vector.x * vector.x + vector.y * vector.y);

	if (vectorLength >= maxLength)
	{
		vector /= vectorLength;
		vector *= maxLength;
	}
}

bool CreaMaths::IsInBetween(float val, float min, float max)
{
	return (val >= min && val <= max);
}

bool CreaMaths::IsInVisionCone()
{
	return false;
}