#ifndef VIDEO_H
#define VIDEO_H

#include "Common.h"
#include <sfeMovie/Movie.hpp>

class Video
{
public:
	Video() {};
	~Video() {};

	void Load(std::string _mediaFile, std::string _musicFile)
	{
		hasSound = true;
		if (!video.openFromFile(_mediaFile))
		{
			std::cout << "Video doesn't work" << std::endl;
			return;
		}

		if (!videoSound.openFromFile(_musicFile))
		{
			std::cout << "Music doesn't work" << std::endl;
			return;
		}
		video.fit(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	// Surdéfinition pour les vidéos sans son
	void Load(std::string _mediaFile)
	{
		hasSound = false;
		if (!video.openFromFile(_mediaFile))
		{
			std::cout << "Video doesn't work" << std::endl;
			return;
		}
		video.fit(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	void Play()
	{

		video.play();
		if (hasSound)
		{
			videoSound.play();
		}
	};

	void Update() { video.update(); }

	void Draw(sf::RenderWindow* _window) { _window->draw(video); };

	const bool KeyPressedIntro()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (hasSound)
			{
				videoSound.stop();
			}

			video.stop();
			return true;
		}
		return false;
	};

	const int GetState() { return video.getStatus(); }

	void SetOrigin(sf::Vector2f _origin) { video.setOrigin(_origin); }
	void Fit(sf::FloatRect _bounds) { video.fit(_bounds); }

	const sf::Vector2f GetSize() { return video.getSize(); }

private:
	sfe::Movie video;
	std::string path;
	sf::Music videoSound;

	bool hasSound;
};

#endif