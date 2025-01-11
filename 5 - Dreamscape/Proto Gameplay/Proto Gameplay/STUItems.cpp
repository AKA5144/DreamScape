#include "STUItems.hpp"

void STUItems::SpawnRandomItem(sf::Vector2f _pos)
{
	STUItem newItem;

	newItem.pos = _pos;
	newItem.type = (ItemType)(rand() % 4);

	itemsVector.push_back(newItem);
}

void STUItems::UpdateItems(float _dt)
{
	for (int k = 0; k < itemsVector.size(); k++)
	{
		itemsVector[k].pos.y += 200 * _dt;
	}
	
	for (int k = 0; k < itemsVector.size(); k++)
	{
		if (itemsVector[k].pos.y > SCREEN_HEIGHT)
		{
			itemsVector[k].isAlive = false;
		}
	}

	for (int k = 0; k < itemsVector.size(); k++)
	{
		if (itemsVector[k].isAlive == false)
		{
			itemsVector.erase(itemsVector.begin() + k);
		}
	}
}

void STUItems::DisplayItems(sf::RenderWindow& _window)
{
	for (int k = 0; k < itemsVector.size(); k++)
	{
		BlitSprite(spriteItems[itemsVector[k].type], itemsVector[k].pos, _window,{3,3});
	}
}