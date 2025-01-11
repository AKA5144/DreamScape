#ifndef STUSHOOT_HPP
#define STUSHOOT_HPP

#include "Common.h"

enum STUShootType
{
	PLAYER,
	ENNEMIE_GHOST,
	ENNEMIE_CRISTAL
};

enum ShootType
{
	LINE_SHOOT,
	WAVE_SHOOT,
	SUN_SHOOT
};

class Shoot
{
public:
	Shoot() {};
	~Shoot() {};

	void Update(float _dt);
	void Display(sf::RenderWindow& _window);

	sf::Vector2f GetPos()const { return pos; }
	void SetPos(sf::Vector2f _pos) { pos = _pos; }

	float GetSpeed()const { return speed; }
	void SetSpeed(float _speed) { speed = _speed; }

	int GetDamage()const { return damage; }
	void SetDamage(int _damage) { damage = _damage; }

	STUShootType GetWho()const { return who; }
	void SetWho(STUShootType _who) { who = _who; }

	ShootType GetType()const { return type; }
	void SetType(ShootType _type) { type = _type; }

	bool GetIsAlive()const { return isAlive; }
	void SetIsAlive(bool _isAlive) { isAlive = _isAlive; }

	void SetDir(sf::Vector2f _dir) { Dir = _dir; }
	void SetAngle(float _angle) { angle = _angle; }
private:

	sf::Vector2f pos;
	float speed;
	float angle;
	int damage = 1;
	STUShootType who;
	ShootType type;
	bool isAlive = true;

	sf::Vector2f Dir = { 0 , -1 };

	void Collide(void);
};

#endif