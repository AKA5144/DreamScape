#ifndef BOSSNEYL_H
#define BOSSNEYL_H
#include "Common.h"
#include "PlayerNeyl.hpp"


struct HandAttackStruct
{
	sf::Vector2f pos;
	float timer = 5;
	bool isSpawned;
};
enum BossNeylAnimationEye
{
	SPAWNING,
	CLOSING,
	OPENING,
	STILL,
	
};
enum BossNeylAnimationHand
{
	ATTACKING,
	CLIMBING

};
enum BossNeylAnimationGenie
{
	IDLEGENIE,
	SHIELD,
	CHARGE,
	ATTACKGENIE,
	DEATHGENIE,
	DEATHGENIEFINAL
};
enum BossNeylAnimationWall
{
	IDLEWALL
};
enum BossNeylAnimationWallHands
{
	IDLEHANDS
};
enum BossNeylAnimationEyes
{
	OPENEYE,
	ATTACKEYE,
	CHARGEYE,
	DEATHEYE,
	DEATHEYEFINAL
};
class BossNeyl
{
public:
	BossNeyl() {};
	~BossNeyl() {};
	void InitBossNeyl(sf::Vector2f camPos);
	void BossPhase(float dt, sf::Vector2f playerPos, sf::Vector2f camPos);
	void UpdateBossNeyl(float dt, sf::Vector2f playerPos, sf::Vector2f camPos);
	void UpdateBossNeylWall(sf::Vector2f camPos, sf::Vector2f camSize, float dt);
	void EyeShotBoss(float dt, sf::Vector2f playerPos, sf::Vector2f camPos);
	void EyeShot(float dt, sf::Vector2f playerPos);
	void UpdateBossGenie(float dt);
	void HandAttack(float dt, sf::Vector2f camPos);
	void HandAttackInit(sf::Vector2f camPos);

	void AddAnim(std::vector<sf::Sprite> _anim)
	{
		bossNeylAnim.push_back(_anim);
	}
	void AddAnimGenie(std::vector<sf::Sprite> _anim)
	{
		bossNeylAnimGenie.push_back(_anim);
	}
	void AddAnimWall(std::vector<sf::Sprite> _anim)
	{
		bossNeylAnimWall.push_back(_anim);
	}
	void AddAnimWallHands(std::vector<sf::Sprite> _anim)
	{
		bossNeylAnimWallHands.push_back(_anim);
	}
	void AddAnimGrabHands(std::vector<sf::Sprite> _anim)
	{
		bossNeylAnimHand.push_back(_anim);
	}
	void AddAnimLaser(std::vector<sf::Sprite> _anim)
	{
		bossNeylAnimLaser.push_back(_anim);
	}
	void AddAnimEye(std::vector<sf::Sprite> _anim)
	{
		bossNeylAnimEye.push_back(_anim);
	}
	void SetPosition(sf::Vector2f position)
	{
		pos = position;
	}
	void LooseHP()
	{
		if (curAnimGenie != SHIELD)
		{
			BossHP--;
			ShieldTiming = 5.f;
			BossHPSound.play();
		}

	}

	void Draw(sf::RenderWindow& _window, sf::Vector2f camPos);
	sf::Vector2f pos;
	sf::Vector2f posWall;
	sf::Vector2f randomPosEye;
	std::vector<std::vector<sf::Sprite>> bossNeylAnim;
	std::vector<std::vector<sf::Sprite>> bossNeylAnimWall;
	std::vector<std::vector<sf::Sprite>> bossNeylAnimWallEnd;
	std::vector<std::vector<sf::Sprite>> bossNeylAnimGenie;
	std::vector<std::vector<sf::Sprite>> bossNeylAnimWallHands;
	std::vector<std::vector<sf::Sprite>> bossNeylAnimHand;
	std::vector<std::vector<sf::Sprite>> bossNeylAnimLaser;
	std::vector<std::vector<sf::Sprite>> bossNeylAnimBossLaser;
	std::vector<std::vector<sf::Sprite>> bossNeylAnimEye;
	std::vector<std::vector<sf::Sprite>> bossNeylArtefact;
	std::vector<sf::Sprite> laserCollider;
	std::vector<sf::Sprite> laserCollider2;
	sf::Sprite laserColliderSprite;
	sf::Sprite irisSprite;
	sf::Sprite irisBossSprite;
	std::vector<sf::Sprite> bossLaserSprite;
	std::vector<sf::Sprite> bossLaserSprite2;
	std::vector<std::vector<std::vector<sf::Sprite>>> bossNeylAnimLaserTab;
	std::vector<std::vector<std::vector<sf::Sprite>>> bossNeylAnimLaserBossTab;
	std::vector<std::vector<std::vector<sf::Sprite>>> bossNeylAnimLaserBossTab2;
	std::vector<std::vector<std::vector<sf::Sprite>>> BossNeylAnimWallHandsTab;
	bool isPhase2Triggered = false;
	int BossHP = 3;
	unsigned char curAnimTile = 0;
	unsigned char curAnimTileWall = 0;
	int curAnimTileGenie = 0;
	unsigned char curAnimTileHand = 0;
	unsigned char curAnimTileLaser = 0;
	unsigned char curAnimTileBossLaser = 0;
	unsigned char curAnimTileArtefact = 0;
	unsigned char curAnimTileEyeBoss = 0;
	unsigned char curAnimTileWallHands[20];
	float curTime = 0;
	float ShieldTiming;
	bool Shield;
	float curTimeWall = 0;
	float curTimeArtefact = 0;
	float curTimeGenie = 0;
	float curTimeHand = 0;
	float curTimeEyeBoss = 0;
	float curTimeLaser = 0;
	float curTimeBossLaser = 0;
	float curTimeWallHands[20];
	float animDuration = 0.7f;
	float animDurationLaser = 0.33f;
	float animDurationBossLaser = 0.3f;
	float animDurationHand = 4.0f;
	float animDurationGenie = 1.f;
	float animDurationWallHands[20];
	float speedWallHands[20];
	float speed;
	float speedWall = 60.f;
	float BigEyeTimer;
	float spawnerTimer;
	bool isSpawned;
	float normeVector = 0;
	HandAttackStruct handAttack;
	BossNeylAnimationEye curAnim;
	BossNeylAnimationGenie curAnimGenie;
	BossNeylAnimationWall curAnimWall;
	BossNeylAnimationWallHands curAnimWallHands;
	BossNeylAnimationHand curAnimHand;
	BossNeylAnimationEyes curAnimEye;

	ParticuleManager pmDeath;
	sf::SoundBuffer BossHPSoundBuffer;
	sf::SoundBuffer laserSoundBuffer;
	sf::Sound BossHPSound;
	sf::Sound laserSound;
private:

	

};
#endif // !BOSSNEYL_H
