#ifndef SL_PBARS_H
#define SL_PBARS_H

#include "Common.h"
#include "CreaMaths.h"

class ProportionalBar
{
public:
	static sf::RectangleShape* Create(sf::Vector2f _pos, sf::Vector2f _size, sf::Color _fillColorActive, sf::Color _fillColorPassive, sf::Color _outlineColor, float _outlineThiccness, bool _centered)
	{
		sf::RectangleShape* pBars = new sf::RectangleShape[2];

		for (int i = 0; i < 2; i++)
		{
			pBars[i].setSize(_size);
			pBars[i].setPosition(_pos);

			sf::Vector2f size = pBars[i].getSize();
			if (_centered)
				pBars[i].setOrigin(size/2.f);
		}

		pBars[0].setOutlineThickness(_outlineThiccness);
		pBars[0].setOutlineColor(_outlineColor);
		pBars[0].setFillColor(_fillColorPassive);
		pBars[1].setFillColor(_fillColorActive);

		return pBars;
	}
};

#endif