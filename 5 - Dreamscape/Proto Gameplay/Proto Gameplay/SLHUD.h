#ifndef SLHUD_H
#define SLHUD_H

#include "Common.h"
#include "ProportionalBars.h"

class SLHUD
{
public:
	void Init(sf::Vector3i _maxStats);
	void Update(sf::Vector3i _currentStats, float _dt, bool _isInCinematicMode);
	void Display(sf::RenderWindow& _window, bool _isPlayerInLockedMode);
private:

	enum Stats
	{
		HP,
		MANA,
		STAMINA
	};

	sf::RectangleShape* m_hpBar;
	sf::RectangleShape* m_manaBar;
	sf::RectangleShape* m_staminaBar;

	sf::Sprite m_hpSprite;
	sf::Sprite m_manaSprite;
	sf::Sprite m_staminaSprite;

	sf::RectangleShape m_focusEffect[2];
	sf::RectangleShape m_cinematicBars[2];

	int m_maxStats[3];
	float m_currentStats[3];

	void DisplayFocusEffect(sf::RenderWindow& _window);
	void DisplayStats(sf::RenderWindow& _window);
	void DisplayCinematicBars(sf::RenderWindow& _window);
};

#endif