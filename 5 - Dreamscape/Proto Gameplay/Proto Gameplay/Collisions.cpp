#include "Collisions.h"

bool Collisions::IsCollidingRectPoint(sf::FloatRect _r, sf::Vector2f _p)
{
	return (_p.x >= _r.left &&
		_p.x < _r.left + _r.width &&
		_p.y >= _r.top &&
		_p.y < _r.top + _r.height);
}

bool Collisions::IsCollidingRectRect(sf::FloatRect _r1, sf::FloatRect _r2)
{
	return (_r1.left + _r1.width >= _r2.left &&
		_r1.left <= _r2.left + _r2.width &&
		_r1.top + _r1.height >= _r2.top &&
		_r1.top <= _r2.top + _r2.height);
}

bool Collisions::IsCollidingCirclePoint(sf::Vector2f _circlePos, float _circleRadius, sf::Vector2f _point)
{
    return CreaMaths::GetSquaredDistance(CreaMaths::CreateVector(_circlePos, _point)) < _circleRadius * _circleRadius;
}

bool Collisions::IsCollidingCircleCircle(sf::Vector2f _c1Pos, sf::Vector2f _c2Pos, float _c1R, float _c2R)
{
	sf::Vector2f vector(_c2Pos.x - _c1Pos.x, _c2Pos.y - _c1Pos.y);

	float distance = CreaMaths::GetSquaredLength(vector);
	float radiuses = _c1R + _c2R;

	if (distance < radiuses * radiuses)
	{
		return true;
	}
	return false;
}

bool Collisions::IsCollidingRectSegment(const sf::FloatRect& _rect, const sf::Vector2f& _start, const sf::Vector2f& _vector)
{
    // Calcule les coordonnées des coins du rectangle
    float left = _rect.left;
    float right = _rect.left + _rect.width;
    float top = _rect.top;
    float bottom = _rect.top + _rect.height;

    // Calcule les coordonnées des extrémités du segment
    sf::Vector2f end = _start + _vector;
    float startX = _start.x;
    float startY = _start.y;
    float endX = end.x;
    float endY = end.y;

    // Vérifie si le segment intersecte le rectangle
    if ((startX < left && endX < left) || (startX > right && endX > right)
        || (startY < top && endY < top) || (startY > bottom && endY > bottom))
    {
        // Le segment est entièrement en dehors du rectangle
        return false;
    }
    else
    {
        // Le segment peut être partiellement à l'intérieur du rectangle, vérifie plus précisément

        // Calcule l'intersection avec le bord gauche du rectangle
        if (_vector.x != 0)
        {
            float t = (left - startX) / _vector.x;
            if (t >= 0 && t <= 1 && startY + t * _vector.y >= top && startY + t * _vector.y <= bottom)
            {
                return true;
            }
        }

        // Calcule l'intersection avec le bord droit du rectangle
        if (_vector.x != 0)
        {
            float t = (right - startX) / _vector.x;
            if (t >= 0 && t <= 1 && startY + t * _vector.y >= top && startY + t * _vector.y <= bottom)
            {
                return true;
            }
        }

        // Calcule l'intersection avec le bord supérieur du rectangle
        if (_vector.y != 0)
        {
            float t = (top - startY) / _vector.y;
            if (t >= 0 && t <= 1 && startX + t * _vector.x >= left && startX + t * _vector.x <= right)
            {
                return true;
            }
        }

        // Calcule l'intersection avec le bord inférieur du rectangle
        if (_vector.y != 0)
        {
            float t = (bottom - startY) / _vector.y;
            if (t >= 0 && t <= 1 && startX + t * _vector.x >= left && startX + t * _vector.x <= right)
            {
                return true;
            }
        }

        // Aucune intersection trouvée
        return false;
    }
}
