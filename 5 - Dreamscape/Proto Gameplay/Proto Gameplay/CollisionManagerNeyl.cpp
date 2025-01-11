#include "CollisionManagerNeyl.hpp"

bool IsCollideMap(sf::Vector2f _pos, Map map)
{
	int r1Xmax = _pos.x + TILE_SIZE / 2.f;
	int r1Xmin = _pos.x - TILE_SIZE / 2.f;
	int r1Ymax = _pos.y + TILE_SIZE / 2.f;
	int r1Ymin = _pos.y - TILE_SIZE / 2.f;

	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			int r2Xmax = (j + 1) * TILE_SIZE;
			int r2Xmin = j * TILE_SIZE;
			int r2Ymax = (i + 1) * TILE_SIZE;
			int r2Ymin = i * TILE_SIZE;

			if (map[i][j] != NOTHING &&
				r1Xmax > r2Xmin &&
				r1Xmin < r2Xmax &&
				r1Ymax > r2Ymin &&
				r1Ymin < r2Ymax)
			{
				return 1;
			}
		}
	}
	return 0;
}

bool IsCollidePointMap(sf::Vector2f _pos, Map map)
{
	int tile_left = (int)(_pos.x / TILE_SIZE);
	int tile_top = (int)(_pos.y / TILE_SIZE);

	return (map[tile_top][tile_left] != NOTHING);

	/*int r1Xmax = _pos.x + TILE_SIZE / 2.f;
	int r1Xmin = _pos.x - TILE_SIZE / 2.f;
	int r1Ymax = _pos.y + TILE_SIZE / 2.f;
	int r1Ymin = _pos.y - TILE_SIZE / 2.f;

	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			int r2Xmax = (j + 1) * TILE_SIZE;
			int r2Xmin = j * TILE_SIZE;
			int r2Ymax = (i + 1) * TILE_SIZE;
			int r2Ymin = i * TILE_SIZE;

			if (map[i][j] != NOTHING &&
				_pos.x > r2Xmin &&
				_pos.x< r2Xmax &&
				_pos. > r2Ymin &&
				r1Ymin < r2Ymax)
			{
				return 1;
			}
		}
	}
	return 0;*/
}
bool IsCollidePointPlayerMap(sf::Vector2f _pos, Map map)
{
	int tile_left = (int)(_pos.x / TILE_SIZE);
	int tile_top = (int)(_pos.y / TILE_SIZE);

	return (map[tile_top][tile_left] != NOTHING);
}

bool IsCollidePointPlayerBreakMap(sf::Vector2f _pos, BreakMap& map)
{
	int tile_left = (int)(_pos.x / TILE_SIZE);
	int tile_top = (int)(_pos.y / TILE_SIZE);


	if (map[tile_top][tile_left] == BREAK)
	{
		return true;
	}
	else
		return false;
}

bool isCollidePointRectangle(sf::Vector2f point, sf::Sprite rect)
{
	return (point.x > rect.getPosition().x && point.x < rect.getPosition().x + rect.getGlobalBounds().width && point.y > rect.getPosition().y && point.y < rect.getPosition().y + rect.getGlobalBounds().height);
}
bool isCollidePointRectangleCentered(sf::Vector2f point, sf::Sprite rect)
{
	return (point.x > rect.getPosition().x - rect.getGlobalBounds().width / 2 && point.x < rect.getPosition().x + rect.getGlobalBounds().width / 2 && point.y > rect.getPosition().y - rect.getGlobalBounds().height / 2 && point.y < rect.getPosition().y + rect.getGlobalBounds().height / 2);
}

bool isCollidingWithOrientedSprite(sf::Vector2f point, sf::Sprite sprite)
{
	sf::FloatRect spriteBounds = sprite.getGlobalBounds();

	//Get the center point of the sprite
	sf::Vector2f spriteCenter(spriteBounds.left + spriteBounds.width / 2.f,
		spriteBounds.top + spriteBounds.height / 2.f);

	//Calculate the sprite's angle of rotation
	float rotation = sprite.getRotation();
	float angleRad = rotation * (3.14159265358979323846 / 180.f);

	//Calculate the four corners of the sprite
	sf::Vector2f corners[4];
	corners[0] = spriteCenter + sf::Vector2f(-spriteBounds.width / 2.f, -spriteBounds.height / 2.f);
	corners[1] = spriteCenter + sf::Vector2f(spriteBounds.width / 2.f, -spriteBounds.height / 2.f);
	corners[2] = spriteCenter + sf::Vector2f(spriteBounds.width / 2.f, spriteBounds.height / 2.f);
	corners[3] = spriteCenter + sf::Vector2f(-spriteBounds.width / 2.f, spriteBounds.height / 2.f);

	//Rotate the corners around the center of the sprite
	for (int i = 0; i < 4; i++)
	{
		sf::Vector2f rotatedCorner = corners[i] - spriteCenter;
		corners[i].x = rotatedCorner.x * cos(angleRad) - rotatedCorner.y * sin(angleRad);
		corners[i].y = rotatedCorner.x * sin(angleRad) + rotatedCorner.y * cos(angleRad);
		corners[i] += spriteCenter;
	}

	//Check if the point is inside the sprite's bounding box
	if (point.x < spriteBounds.left || point.x > spriteBounds.left + spriteBounds.width ||
		point.y < spriteBounds.top || point.y > spriteBounds.top + spriteBounds.height)
	{
		return false;
	}

	//Check if the point is inside the sprite's rotated rectangle
	if ((point - corners[0]).x * (corners[1] - corners[0]).y -
		(point - corners[0]).y * (corners[1] - corners[0]).x > 0.f)
	{
		return false;
	}
	if ((point - corners[1]).x * (corners[2] - corners[1]).y -
		(point - corners[1]).y * (corners[2] - corners[1]).x > 0.f)
	{
		return false;
	}
	if ((point - corners[2]).x * (corners[3] - corners[2]).y -
		(point - corners[2]).y * (corners[3] - corners[2]).x > 0.f)
	{
		return false;
	}
	if ((point - corners[3]).x * (corners[0] - corners[3]).y -
		(point - corners[3]).y * (corners[0] - corners[3]).x > 0.f)
	{
		return false;
	}

	return true;
}