#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "Common.h"
#include "CreaMaths.h"

class Collisions
{
public:
	static bool IsCollidingRectPoint(sf::FloatRect _rect, sf::Vector2f _point);
	static bool IsCollidingRectRect(sf::FloatRect _r1, sf::FloatRect _r2);
	static bool IsCollidingRectSegment(const sf::FloatRect& _rect, const sf::Vector2f& _start, const sf::Vector2f& _vector);
	static bool IsCollidingCircleCircle(sf::Vector2f _c1Pos, sf::Vector2f _c2Pos, float _c1R, float _c2R);
	static bool IsCollidingCirclePoint(sf::Vector2f _circlePos, float _circleRadius, sf::Vector2f _point);
};

#endif