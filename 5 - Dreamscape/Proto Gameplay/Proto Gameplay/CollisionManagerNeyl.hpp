#ifndef COLLISION_MANAGER
#define COLLISION_MANAGER

#include "MapManagerNeyl.hpp"

bool IsCollideMap(sf::Vector2f _pos, Map map);
bool IsCollidePointMap(sf::Vector2f _pos, Map map);
bool IsCollidePointPlayerMap(sf::Vector2f _pos, Map map);
bool IsCollideBorder(sf::Vector2f _entityPos, sf::View& _view);
bool isCollidePointRectangle(sf::Vector2f point, sf::Sprite rect);
bool isCollidePointRectangleCentered(sf::Vector2f point, sf::Sprite rect);
bool IsCollidePointPlayerBreakMap(sf::Vector2f _pos, BreakMap& map);
bool isCollidingWithOrientedSprite(sf::Vector2f point, sf::Sprite sprite);


#endif // !COLLISION_MANAGER
