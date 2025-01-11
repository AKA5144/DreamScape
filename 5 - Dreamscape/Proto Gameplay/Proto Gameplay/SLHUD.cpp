#include "SLHUD.h"

void SLHUD::Init(sf::Vector3i _maxStats)
{
	m_maxStats[HP] = _maxStats.x;
	m_maxStats[MANA] = _maxStats.y;
	m_maxStats[STAMINA] = _maxStats.z;

	for (int i = 0; i < 3; i++)
	{
		m_currentStats[i] = m_maxStats[i];
	}
	m_hpBar = ProportionalBar::Create(sf::Vector2f(0, 0), sf::Vector2f(150, 6), sf::Color(182, 23, 17), sf::Color(0, 0, 0, 64), sf::Color(0, 0, 0, 64), 1, false);
	m_manaBar = ProportionalBar::Create(sf::Vector2f(0, 0), sf::Vector2f(150 * m_maxStats[MANA] / m_maxStats[HP], 6), sf::Color(13, 78, 170), sf::Color(0, 0, 0, 64), sf::Color(0, 0, 0, 64), 1, false);
	m_staminaBar = ProportionalBar::Create(sf::Vector2f(0, 0), sf::Vector2f(150 * m_maxStats[STAMINA] / m_maxStats[HP], 6), sf::Color(22, 145, 59), sf::Color(0, 0, 0, 64), sf::Color(0, 0, 0, 64), 1, false);

	m_hpSprite = LoadSprite("Assets/Souls/HUD/hpBar.png", false);
	m_manaSprite = LoadSprite("Assets/Souls/HUD/manaBar.png", false);
	m_staminaSprite = LoadSprite("Assets/Souls/HUD/staminaBar.png", false);

	for (int i = 0; i < 2; i++)
	{
		m_focusEffect[i].setFillColor(sf::Color(0, 0, 0, 255));
		m_cinematicBars[i].setFillColor(sf::Color::Black);
	}
}

void SLHUD::Update(sf::Vector3i _currentStats, float _dt, bool _isInCinematicMode)
{
	m_currentStats[HP] = _currentStats.x;
	m_currentStats[MANA] = _currentStats.y;
	m_currentStats[STAMINA] = _currentStats.z;

	if (m_currentStats[HP] <= 0)
	{
		m_currentStats[HP] = 0;
	}

	m_hpBar[1].setSize({ m_hpBar[0].getSize().x * (m_currentStats[HP] / m_maxStats[HP]), m_hpBar[1].getSize().y });
	m_manaBar[1].setSize({ m_manaBar[0].getSize().x * (m_currentStats[MANA] / m_maxStats[MANA]), m_manaBar[1].getSize().y });
	m_staminaBar[1].setSize({ m_staminaBar[0].getSize().x * (m_currentStats[STAMINA] / m_maxStats[STAMINA]), m_staminaBar[1].getSize().y });

	for (int i = 0; i < 2; i++)
	{
		sf::Vector2f size = m_cinematicBars[i].getSize();

		if (_isInCinematicMode)
		{
			m_cinematicBars[i].setSize({ size.x, size.y + 200 * _dt });
		}
		else
		{
			m_cinematicBars[i].setSize({ size.x, size.y - 200 * _dt });
		}
	}
}

void SLHUD::Display(sf::RenderWindow& _window, bool _isPlayerInLockedMode)
{
	if (_isPlayerInLockedMode)
	{
		DisplayFocusEffect(_window);
	}

	DisplayStats(_window);
	DisplayCinematicBars(_window);
}






void SLHUD::DisplayFocusEffect(sf::RenderWindow& _window)
{
	sf::View camera = _window.getView();

	m_focusEffect[0].setPosition(camera.getCenter() - camera.getSize() / 2.f);
	m_focusEffect[1].setPosition(camera.getCenter().x - camera.getSize().x / 2.f, camera.getCenter().y + camera.getSize().y / 2.f - camera.getSize().y / 10.f);
	for (int i = 0; i < 2; i++)
	{
		m_focusEffect[i].setSize({ camera.getSize().x, camera.getSize().y / 10.f });
		_window.draw(m_focusEffect[i]);
	}
}

void SLHUD::DisplayStats(sf::RenderWindow& _window)
{
	sf::View camera = _window.getView();

	for (int i = 0; i < 2; i++)
	{
		m_hpBar[i].setPosition(camera.getCenter() - camera.getSize() / 2.f + sf::Vector2f(25, 25));
		m_manaBar[i].setPosition(m_hpBar[i].getPosition() + sf::Vector2f(0, m_hpBar[i].getSize().y * 1.5f));
		m_staminaBar[i].setPosition(m_manaBar[i].getPosition() + sf::Vector2f(0, m_manaBar[i].getSize().y * 1.5f));

		_window.draw(m_hpBar[i]);
		_window.draw(m_manaBar[i]);
		_window.draw(m_staminaBar[i]);

	}

	m_hpSprite.setPosition(m_hpBar[0].getPosition() - sf::Vector2f(8, 1));
	_window.draw(m_hpSprite);

	m_manaSprite.setPosition(m_manaBar[0].getPosition() - sf::Vector2f(8, 1));
	_window.draw(m_manaSprite);

	m_staminaSprite.setPosition(m_staminaBar[0].getPosition() - sf::Vector2f(8, 1));
	_window.draw(m_staminaSprite);
}

void SLHUD::DisplayCinematicBars(sf::RenderWindow& _window)
{
	sf::View camera = _window.getView();

	m_cinematicBars[0].setPosition(camera.getCenter() - camera.getSize() / 2.f);
	m_cinematicBars[1].setPosition(camera.getCenter().x - camera.getSize().x / 2.f, camera.getCenter().y + camera.getSize().y / 2.f);


	for (int i = 0; i < 2; i++)
	{
		m_cinematicBars[i].setSize({ camera.getSize().x, m_cinematicBars[i].getSize().y });

		if (m_cinematicBars[i].getSize().y >= camera.getSize().y / 6.f)
		{
			m_cinematicBars[i].setSize({ camera.getSize().x, camera.getSize().y / 6.f });
		}
		else if (m_cinematicBars[i].getSize().y <= 0)
		{
			m_cinematicBars[i].setSize({ camera.getSize().x, 0 });
		}

		m_cinematicBars[1].setOrigin(0, m_cinematicBars[1].getSize().y);
		_window.draw(m_cinematicBars[i]);
	}
}