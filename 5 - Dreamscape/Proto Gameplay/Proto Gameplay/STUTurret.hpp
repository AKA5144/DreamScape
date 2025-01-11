#ifndef STUTURRET_HPP
#define STUTURRET_HPP

#include "Common.h"
#include "STUShootManager.hpp"


enum TurretType
{
	SIMPLE_LINE,
	DOUBLE_LINE,
	SIMPLE_WAVE,
	DOUBLE_WAVE
};

class Turret
{
public:
	Turret() {};
	~Turret() {};

	void Update(sf::Vector2f _point, float _dt, bool _rotate);
	void Display(sf::RenderWindow& _window);

	sf::Vector2f GetPos()const { return pos; }
	void SetPos(sf::Vector2f _pos) { pos = _pos; }

	sf::Clock GetTimer()const { return attackTimer; }
	void restartClock() { attackTimer.restart(); }

	sf::Vector2f GetVectorFromPlayer()const { return VectorFromPlayer; }
	void SetVectorFromPlayer(sf::Vector2f _pos) { VectorFromPlayer = _pos; }

	TurretType GetType()const { return type; }
	void SetType(TurretType _type) { type = _type; }

	float GetCoolDown()const { return cooldown; }
	void SetCoolDown(float _cooldown) { cooldown = _cooldown; }

	void SetSpeedAngle(float _angle) { SpeedAngle = _angle; }

private:

	sf::Vector2f pos;
	sf::Clock attackTimer;
	float cooldown = 0.1;
	sf::Vector2f VectorFromPlayer;
	float SpeedAngle = 0.00f;//Sens direct
	TurretType type;

	ShootManager Sm;

	float animTimer = 0;
	int currentSprite = 0;
	sf::Sprite sprite;

	void UpdateAnim(float _dt);
	void Move(sf::Vector2f _point, float _dt, bool _rotate);
	void Shot(float _dt);
};

#endif
