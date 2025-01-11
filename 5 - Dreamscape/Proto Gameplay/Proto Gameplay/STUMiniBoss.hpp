#ifndef STUMINIBOSS_HPP
#define STUMINIBOSS_HPP

#include "Common.h"
#include "GameState.h"
#include "Player.h"
#include "Particules.hpp"

#include "Easing.h"

#define MAX_STU_MINI_BOSS_HP 1000
#define MAX_LASER_SPRITE 5

enum STUMiniBossAttack
{
	NOTHING_STU_MINI_BOSS,
	ENNEMI_SPAWN,
	HAND,
	LASER,
	STU_MINI_BOSS_DEAD
};

enum StuMiniBossPhase
{
	ONE,
	TWO
};


struct Hand
{
	sf::Vector2f pos;
	int currentHandSprite = 0;
	float animeHandTimer = 0;
	float speed = 400;
	float aceleration = 1;
	float angle = 0;
	sf::Sprite sprite;
	sf::Vector2f scale = { 4,4 };
};

class STUMiniBoss
{
public:
	STUMiniBoss() {};
	~STUMiniBoss() {};

	void Load(void);
	void Update(float _dt, GameState& _gameState, Player& _player, bool& _transition, float& _noirAlpha);
	void Display(sf::RenderWindow& _window);

	bool Collide(sf::Vector2f _point, int _damage);

	int GetHp(void) const { return HP; }
	sf::Vector2f GetPos(void)const { return pos; }

private:
	sf::Vector2f pos;
	int HP = MAX_STU_MINI_BOSS_HP;
	sf::Clock invincibility;

	STUMiniBossAttack actualAttack;
	StuMiniBossPhase actualPhase;
	Hand hands[2];

	float IntroCoolDown;
	sf::Clock cooldownAttack;
	sf::Clock cooldownForm;

	ParticuleManager Pm;


	//Idle
	sf::Sprite AnimHeadOne[6] =
	{
		LoadSprite("Assets/Shoot Them Up/Boss/Idle1/Head/1.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Idle1/Head/2.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Idle1/Head/3.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Idle1/Head/4.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Idle1/Head/5.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Idle1/Head/6.png", true)
	};

	sf::Sprite AnimHeadTwo[4] =
	{
		LoadSprite("Assets/Shoot Them Up/Boss/Idle2/Head/1.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Idle2/Head/2.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Idle2/Head/3.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Idle2/Head/4.png", true),
	};
	int currentHeadSprite = 0;
	float animHeadTimer = 0;
	sf::Sprite HeadSprite = AnimHeadOne[currentHeadSprite];

	float bossAlpha = 255;
	sf::Vector2f scale = { 4,4 };

	sf::Sprite AnimHands[2][6] =
	{
		{
			LoadSprite("Assets/Shoot Them Up/Boss/Idle1/Left Hand/1.png", true),
			LoadSprite("Assets/Shoot Them Up/Boss/Idle1/Left Hand/2.png", true),
			LoadSprite("Assets/Shoot Them Up/Boss/Idle1/Left Hand/3.png", true),
			LoadSprite("Assets/Shoot Them Up/Boss/Idle1/Left Hand/4.png", true),
			LoadSprite("Assets/Shoot Them Up/Boss/Idle1/Left Hand/5.png", true),
			LoadSprite("Assets/Shoot Them Up/Boss/Idle1/Left Hand/6.png", true)
		}
		,
		{
			LoadSprite("Assets/Shoot Them Up/Boss/Idle1/Right Hand/1.png", true),
			LoadSprite("Assets/Shoot Them Up/Boss/Idle1/Right Hand/2.png", true),
			LoadSprite("Assets/Shoot Them Up/Boss/Idle1/Right Hand/3.png", true),
			LoadSprite("Assets/Shoot Them Up/Boss/Idle1/Right Hand/4.png", true),
			LoadSprite("Assets/Shoot Them Up/Boss/Idle1/Right Hand/5.png", true),
			LoadSprite("Assets/Shoot Them Up/Boss/Idle1/Right Hand/6.png", true)
		}
	};


	//Laser
	sf::Sprite AnimHeadLaser[8] =
	{
		LoadSprite("Assets/Shoot Them Up/Boss/Laser/Laser1.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Laser/Laser2.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Laser/Laser3.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Laser/Laser4.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Laser/Laser5.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Laser/Laser6.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Laser/Laser7.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Laser/Laser8.png", true),
	};

	sf::Sprite AnimLaserCharge[12] =
	{
		LoadSprite("Assets/Shoot Them Up/Boss/Laser/Charge/1.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Laser/Charge/2.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Laser/Charge/3.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Laser/Charge/4.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Laser/Charge/5.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Laser/Charge/6.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Laser/Charge/7.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Laser/Charge/8.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Laser/Charge/9.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Laser/Charge/10.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Laser/Charge/11.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Laser/Charge/12.png", true)
	};

	sf::Sprite LaserSprite[MAX_LASER_SPRITE] =
	{
	LoadSprite("Assets/Shoot Them Up/Boss/Laser/Laser/1.png", false),
	LoadSprite("Assets/Shoot Them Up/Boss/Laser/Laser/2.png", false),
	LoadSprite("Assets/Shoot Them Up/Boss/Laser/Laser/3.png", false),
	LoadSprite("Assets/Shoot Them Up/Boss/Laser/Laser/4.png", false),
	LoadSprite("Assets/Shoot Them Up/Boss/Laser/Laser/5.png", false),
	};
	float currentLaserSprite = 0;
	float currentChargeLaserAnim;
	float chargeScale;

	bool isLaserVisible;
	float alphaLaser;


	//Dead
	sf::Sprite DeadAnim[11] =
	{
		LoadSprite("Assets/Shoot Them Up/Boss/Death/1.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Death/2.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Death/3.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Death/4.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Death/5.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Death/6.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Death/7.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Death/8.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Death/9.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Death/10.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/Death/11.png", true)
	};
	sf::Vector2f deadPos;
	sf::Clock deadTimer;


	//magical circle
	sf::Sprite HandCircle = LoadSprite("Assets/Shoot Them Up/Boss/Magic Circle.png", true);
	float rotateCircle[2] = { 0,0 };


	std::vector<sf::Vector2f>ennemyPos;


	//Relic
	sf::Text RewardSTUText[2];
	sf::Sprite RelicSprite = LoadSprite("Assets/Shoot Them Up/Boss/Relic.png", true);
	sf::Vector2f relicPos;
	bool playerGetItem;


	//sounds
	sf::SoundBuffer bufferBossScream;
	sf::Sound bossScream;
	sf::Sound LaserSound = LoadSound("Assets/Shoot Them Up/Boss/LaserSound.ogg");
	sf::Sound HandGrowing = LoadSound("Assets/Shoot Them Up/Boss/HandGrowing.ogg");
	sf::Sound HandDecrease = LoadSound("Assets/Shoot Them Up/Boss/HandDecrease.ogg");
	sf::Sound HandSound = LoadSound("Assets/Shoot Them Up/Boss/HandSound.ogg");


	void SpawnEnnemi(void);
	void HandAttack(float _dt);
	void LaserAttack(float _dt);
	void ChangeForm(void);
	void UpdateAttacks(float _dt);
	void UpdateAnimPhase1(float _dt);
	void UpdateAnimPhase2(float _dt);
	void UpdateAnimLaser(float _dt);
	void UpdateDeadAnim(float _dt);
	void UpdateDead(float _dt, GameState& _gameState, Player& _player, bool& _transition, float& _noirAlpha);
};

#endif // !STUMINIBOSS_HPP

