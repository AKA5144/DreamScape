#ifndef STUSHOOTMANAGER_HPP
#define STUSHOOTMANAGER_HPP

#include "Common.h"
#include "STUShoot.hpp"

#define MAX_EXPLODE_SHOT 4

struct explodeShot
{
	sf::Vector2f pos;
	float currentAnim = 0;
	float angle = rand() % 361;

	bool isFinish = false;
};

class ShootManager
{
public:
	ShootManager(){};
	~ShootManager(){};

	void AddShoot(sf::Vector2f _pos, float _speed, int _damage, STUShootType _who, ShootType _type);
	void AddShoot(sf::Vector2f _pos, sf::Vector2f _dir, float _angle, float _speed, int _damage, STUShootType _who, ShootType _type);
	void Update(float _dt);
	void Display(sf::RenderWindow& _window);

	std::vector<Shoot>& Vector(void) { return shootVector; }

private:

	std::vector<Shoot> shootVector;
	std::vector<explodeShot> animHitShot;

	sf::Sprite explodeSprite[MAX_EXPLODE_SHOT] =
	{
		LoadSprite("Assets/Shoot Them Up/Shoots/PlayerExplode/1.png",true),
		LoadSprite("Assets/Shoot Them Up/Shoots/PlayerExplode/2.png",true),
		LoadSprite("Assets/Shoot Them Up/Shoots/PlayerExplode/3.png",true),
		LoadSprite("Assets/Shoot Them Up/Shoots/PlayerExplode/4.png",true)
	};

	sf::Sound shotSound = LoadSound("Assets/Shoot Them Up/Player/Shot.ogg");

	void Collision(void);
};
#endif
