#include "SLSounds.h"

std::vector<SLSounds::Sound> SLSounds::m_soundsList;

void SLSounds::Load()
{
	std::string folderPath = "Assets/Souls/Sounds/";

	for (const auto& entry : std::filesystem::directory_iterator(folderPath))
	{
		std::string filePath = entry.path().string();

		if (filePath.find(".wav") != std::string::npos || filePath.find(".ogg") != std::string::npos)
		{
			Sound tempSound;
			tempSound.name = filePath;
			tempSound.sound = LoadSound(filePath);

			m_soundsList.push_back(tempSound);
		}
	}
}

void SLSounds::PlaySFX(std::string _name, bool _relativeToListener, float _volume, sf::Vector2f _pos)
{
	if (m_playingSounds.size() == 0)
	{
		m_playingSounds = m_soundsList;
	}

	std::string path = "Assets/Souls/Sounds/";
	path += _name;
	path += ".wav";

	for (int i = 0; i < m_playingSounds.size(); i++)
	{
		if (m_playingSounds[i].name == path)
		{
			m_playingSounds[i].sound.setRelativeToListener(_relativeToListener);
			m_playingSounds[i].sound.setPosition(_pos.x, _pos.y, 0.f);
			m_playingSounds[i].sound.setMinDistance(SOUND_MINMUM_DISTANCE);
			m_playingSounds[i].sound.setAttenuation(SOUND_ATTENUATION);
			m_playingSounds[i].sound.setVolume(_volume);

			if (m_playingSounds[i].sound.getStatus() != sf::Sound::Playing)
			{
				m_playingSounds[i].sound.play();
			}
		}
	}
}