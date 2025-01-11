#ifndef ANIMATION_H
#define ANIMATION_H

#include "Common.h"

class AnimationManager
{
public:
	AnimationManager() { animEnded = false; currentSpriteID = 0;};
	~AnimationManager() {};

	static void Load();

	enum FrameType
	{
		INIT,
		ACTIVE,
		RECOVERY
	};

	void PlayAnimation(std::string _path, float _animDuration);
	void RestartAnimation() { currentSpriteID = 0; clock.restart(); animEnded = false; }

	const sf::Sprite GetCurrentSprite() { return m_currentAnimation.sprites[currentSpriteID].sprite; }
	const float GetAnimDuration() { return animDuration; }
	const float GetCurrentDuration() { return clock.getElapsedTime().asSeconds(); }
	const int GetCurrentFrame() { return currentSpriteID; }
	const FrameType GetCurrentFrameType();

	const bool HasEnded() { return animEnded; }

private:
	std::string currentAnim;
	sf::Clock clock;

	int currentSpriteID;
	float animDuration;
	bool animEnded;

	struct Sprite
	{
		sf::Sprite sprite;
		int ID;
	};

	struct Animation
	{
		std::string path;
		std::vector<Sprite> sprites;
		sf::Vector3i frameData;
	};

	static std::vector<Animation> m_animations;
	std::vector<Animation> m_animationsCopy;
	Animation m_currentAnimation;

	static void ProcessFolder(const std::string& folderPath);

	static bool CompareByNumber(const Sprite& a, const Sprite& b) { return a.ID < b.ID; }
};

void AnimationSprite(std::vector <sf::Sprite> _spriteTab, sf::Sprite& Currentsprite, float timer);

#endif