#ifndef SLSOUNDS_H
#define SLSOUNDS_H

#include "Common.h"

#define SOUND_MINMUM_DISTANCE 250
#define SOUND_ATTENUATION 1

class SLSounds
{
public:
	struct Sound
	{
		sf::Sound sound;
		std::string name;
	};

	static void Load();
	static std::vector<Sound> m_soundsList;

	void PlaySFX(std::string _name, bool _relativeToListener, float volume = 100.f, sf::Vector2f _pos = sf::Vector2f(0, 0));
	void SetListenerPos(sf::Vector2f _pos) { m_listener.setPosition(_pos.x, _pos.y, 0.f); }
	void SetListenerVolume(float _volume) { m_listener.setGlobalVolume(_volume); }

	void ClearVector() { m_playingSounds.clear(); m_playingSounds.shrink_to_fit(); }
private:
	sf::Listener m_listener;

	std::vector<Sound> m_playingSounds;
};

#endif