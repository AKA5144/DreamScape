#include "Transition.h"

void Transition::Play(float _duration, FadeType _type)
{
	if (!IsPlaying())
	{
		m_animDuration = _duration;
		m_type = _type;
	}
}
void Transition::ForcePlay(float _duration, FadeType _type)
{
	m_isEnded = false;
	m_animDuration = _duration;
	m_type = _type;
}

void Transition::Update(float _dt)
{
	if (IsPlaying())
	{
		if (m_timer + _dt < m_animDuration)
		{
			m_isEnded = false;
			m_timer += _dt;

			if (m_type == FADE_IN)
				m_noir.setColor(sf::Color(0, 0, 0, 255 * (m_timer / m_animDuration)));
			else if (m_type == FADE_OUT)
				m_noir.setColor(sf::Color(0, 0, 0, 255 - 255 * (m_timer / m_animDuration)));
		}
		else
		{
			m_noir.setColor(sf::Color(0, 0, 0, 255));
			m_isEnded = true;
			m_timer = 0;
			m_animDuration = 0;
		}
	}
}

void Transition::Display(sf::RenderWindow& _window)
{
	sf::View camera = _window.getView();
	sf::Vector2f topLeftCorner(camera.getCenter() - camera.getSize() / 2.f);

	if (IsPlaying())
	{
		BlitSprite(m_noir, topLeftCorner, _window, m_noir.getScale(), m_noir.getRotation(), m_noir.getColor());
	}
}