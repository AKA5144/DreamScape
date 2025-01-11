#ifndef STUENNEMIE_HPP
#define STUENNEMIE_HPP

#include "Common.h"
#include "STUPlayer.hpp"
#include "STUShootManager.hpp"


enum STUEnnemiType
{
	FIRE,
	GHOST,
	CRISTAL
};

enum STUEnnemiState
{
	WAIT,
	MOVE,
	ATTACK,
	POWER_UP
};

class Ennemie
{
public:
	Ennemie() {};
	~Ennemie() {};

	void Init(STUEnnemiType _type, sf::Vector2f _pos, int _turn);
	void Update(float _dt, STUPlayer _player);
	void Display(sf::RenderWindow& _window);

	sf::Vector2f GetPos()const { return pos; }
	void SetPos(sf::Vector2f _pos) { pos = _pos; }

	STUEnnemiType GetType()const { return type; }
	void SetType(STUEnnemiType _type) { type = _type; }

	bool OnScreen()const { return onScreen; }
	void SetOnScreen(bool _bool) { onScreen = _bool; }

	bool IsAlive()const { return isAlive; }
	void SetIsAlive(bool _bool) { isAlive = _bool; }

	bool Hit()const { return hit; }
	void SetHit(bool _bool) { hit = _bool; }

	int GetHp(void)const { return HP; }
	void SetHp(int _Hp) { HP = _Hp; }

	sf::Clock& GetHitClock() { return hitClock; }

	int GetTurn(void)const { return turn; }

	float GetAngle(void)const { return angle; }

	sf::Vector2f GetVarCos(void)const { return varCos; }

	sf::Vector2f varCos;

private:

	sf::Vector2f pos;
	sf::Vector2f dir;
	sf::Vector2f target;
	float speed = 200;
	float angle = 0;
	int HP = 4;
	STUEnnemiType type;
	STUEnnemiState state;
	int turn; //le groupe actuel d'ennemi a l'écran
	bool hit = false;
	sf::Clock hitClock;
	bool onScreen = true;
	bool isAlive = true;

	sf::Clock wait;
	sf::Clock attackClock;
	float attackCoolDown;


	//Animation
	float currentSprite = 0;

	void FireMove(float _dt, STUPlayer _player);
	void GhostMove(float _dt);
	void CristalMove(float _dt);
	void Anim(float _dt);
	void ScreenCollide(void);
};

ShootManager& GetEnnemiShootManager(void);

#endif