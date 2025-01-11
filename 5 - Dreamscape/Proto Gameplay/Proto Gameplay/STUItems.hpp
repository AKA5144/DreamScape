#ifndef STUITEMS_HPP
#define STUITEMS_HPP

#include "Common.h"

enum ItemType
{
	SIMPLE_S_ITEM,
	DOUBLE_S_ITEM,
	SIMPLE_W_ITEM,
	DOUBLE_W_ITEM
};

struct STUItem
{
	sf::Vector2f pos;
	ItemType type;
	bool isAlive = true;
};

class STUItems
{
public:

	void SpawnRandomItem(sf::Vector2f _pos);
	void UpdateItems(float _dt);
	void DisplayItems(sf::RenderWindow& _window);

	std::vector<STUItem>& GetVector(void) {return itemsVector;}

private:
	std::vector<STUItem> itemsVector;

	sf::Sprite spriteItems[4] =
	{
		LoadSprite("Assets/Shoot Them Up/Items/OneSimpleShot.png",true),
		LoadSprite("Assets/Shoot Them Up/Items/DoubleSimpleShot.png",true),
		LoadSprite("Assets/Shoot Them Up/Items/OneWaveShot.png",true),
		LoadSprite("Assets/Shoot Them Up/Items/DoubleWaveShot.png",true)
	};
};

#endif // !STUITEMS_HPP

