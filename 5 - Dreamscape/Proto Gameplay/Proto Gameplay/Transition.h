#ifndef TRANSITION_H
#define TRANSITION_H

#include "Common.h"

class Transition
{
public:
	Transition() // Initialisation automatique de la transition (pas besoin de fonction Load)
	{
		m_noir = LoadSprite("Assets/Lobby/Divers/Transition.png", false);
		m_noir.setColor(sf::Color(0, 0, 0, 0));
		m_isEnded = false;
		m_timer = 0;
		m_animDuration = 0;
	}

	enum FadeType
	{
		FADE_IN,
		FADE_OUT
	};

	void Play(float _duration, FadeType _type); // Lance la transition seulement si la transition n'est pas en train de se jouer

	/////  A N'UTILISER QU'A LA SORTIE D'UN STATE  /////
	void ForcePlay(float _duration, FadeType _type); // Lance la transition dans tous les cas

	void Update(float _dt); // Update la transition
	const bool HasEnded() { return m_isEnded; } // Indique quand la transition s'est finie
	const bool IsPlaying() { return (m_animDuration != 0 && !m_isEnded); } // Indique si la transition est en train de se jouer

	void Display(sf::RenderWindow& _window);

private:
	sf::Sprite m_noir;

	float m_timer;
	float m_animDuration;
	bool m_isEnded;
	FadeType m_type;
};

#endif