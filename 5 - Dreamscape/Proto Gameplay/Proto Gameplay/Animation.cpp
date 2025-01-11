#include "Animation.h"

std::vector<AnimationManager::Animation> AnimationManager::m_animations;

//ChatGPT
bool CanConvertToInt(const std::string& str) {
	try {
		int convertedValue = std::stoi(str);
		return true;
	}
	catch (const std::exception& e) {
		return false;
	}
}

void AnimationManager::Load()
{
	std::ifstream registeredAnimations("Data/Animation/RegisteredAnimations.txt");
	std::string path;

	while (registeredAnimations >> path)
	{
		ProcessFolder(path);
	}

	for (int i = 0; i < m_animations.size(); i++)
	{
		std::ifstream frameDataFile(m_animations[i].path + "/FrameData.txt");

		if (frameDataFile.is_open())
		{
			frameDataFile >> m_animations[i].frameData.x;
			frameDataFile >> m_animations[i].frameData.y;
			frameDataFile >> m_animations[i].frameData.z;
			frameDataFile.close();
		}
		else
		{
			m_animations[i].frameData = { -1, -1, -1 };
		}

		//Fix l'ordre des frames
		std::sort(m_animations[i].sprites.begin(), m_animations[i].sprites.end(), CompareByNumber);
	}
}

void AnimationManager::PlayAnimation(std::string _path, float _animDuration)
{
	animEnded = false;

	if (m_animationsCopy.size() == 0)
	{
		m_animationsCopy.resize(m_animations.size());

		for (int i = 0; i < m_animations.size(); i++)
		{
			m_animationsCopy[i] = m_animations[i];
		}

		m_currentAnimation = m_animationsCopy[0];
	}

	if (m_currentAnimation.path != _path)
	{
		bool found = false;
		for (int i = 0; i < m_animationsCopy.size(); i++)
		{
			found = true;
			if (m_animationsCopy[i].path == _path)
			{
				m_currentAnimation = m_animationsCopy[i];
			}
		}

		if (!found)
			std::cout << "Could not find animation." << std::endl;


		animDuration = _animDuration;
		currentSpriteID = 0;
		clock.restart();
	}

	// Update de l'animation
	float tempsCourant = clock.getElapsedTime().asSeconds();

	if (tempsCourant >= animDuration)
	{
		clock.restart();
		tempsCourant = 0;
		animEnded = true;
	}

	currentSpriteID = m_currentAnimation.sprites.size() * (tempsCourant / animDuration);
}


const AnimationManager::FrameType AnimationManager::GetCurrentFrameType()
{
	FrameType frameState = INIT;
	if (m_currentAnimation.frameData.x != -1)
	{
		sf::Vector3i m_frameData = m_currentAnimation.frameData;

		if (currentSpriteID + 1 > m_frameData.x && currentSpriteID + 1 <= m_frameData.x + m_frameData.y)
		{
			frameState = ACTIVE;
		}
		else if (currentSpriteID + 1 > m_frameData.x + m_frameData.y && currentSpriteID + 1 <= m_frameData.x + m_frameData.y + m_frameData.z)
		{
			frameState = RECOVERY;
		}
	}
	return frameState;
}

void AnimationManager::ProcessFolder(const std::string& folderPath)
{
	for (const auto& entry : std::filesystem::directory_iterator(folderPath))
	{
		std::string filePath = entry.path().string();

		//////////////////////////////////////////////////// Replace le "\" par un "/"
		char charToReplace = '\\';
		char replacementChar = '/';

		std::size_t found = filePath.find(charToReplace);
		while (found != std::string::npos)
		{
			filePath.replace(found, 1, 1, replacementChar);
			found = filePath.find(charToReplace, found + 1);
		}
		////////////////////////////////////////////////////

		Animation newAnimation;
		newAnimation.path = folderPath + "/";
		m_animations.push_back(newAnimation);

		for (int i = 0; i < m_animations.size(); i++)
		{
			if (m_animations[i].path == newAnimation.path && i != m_animations.size() - 1)
			{
				m_animations.pop_back();
			}
		}

		if (entry.is_directory())
		{
			if (m_animations.size() > 0)
			{
				m_animations.pop_back();
			}

			ProcessFolder(filePath);
		}
		else if (entry.is_regular_file())
		{
			if (filePath.find(".png") != std::string::npos || filePath.find(".jpg") != std::string::npos)
			{
				Sprite sprite;
				sprite.sprite = LoadSprite(filePath, true);

				std::string tempString = filePath;
				tempString.erase(0, m_animations.back().path.length());
				tempString.erase(tempString.length() - 4, 4);

				if (CanConvertToInt(tempString))
				{
					sprite.ID = std::stoi(tempString);
				}

				m_animations.back().sprites.push_back(sprite);
			}
		}
	}
}










void AnimationSprite(std::vector <sf::Sprite> _spriteTab, sf::Sprite& Currentsprite, float time)
{
	static sf::Clock cooldown;
	static int compteur = 0;
	float delay = time / _spriteTab.size();

	if (cooldown.getElapsedTime().asSeconds() >= delay)
	{
		cooldown.restart();
		Currentsprite = _spriteTab[compteur];
		compteur++;
		if (compteur >= _spriteTab.size())
		{
			compteur = 0;
		}
	}
}
