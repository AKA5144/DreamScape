#ifndef PARTICULES_HPP
#define PARTICULES_HPP

#include "Common.h"
#include <vector>

#define MAX_PARTICULES 1000
#define MAX_SPRITE_SMOG 9
#define PI 3.141592653589793238f

enum ParticuleType
{
	EXPLOSIONS,
	SMOG,
	HEAT,
	FINAL_BOSS_HAND,
	BLACK_HOLE,
	BLACK_HOLE_BOSS,
	EARTH

};

struct Particule
{
	sf::Vector2f pos;
	sf::Vector2f finalPos;
	float TTLMax;
	float currentTTL;
	float rotation;
	float fDeltaY;
	float fDeltaX;
	float angle;
	float amplitude;
	float speedMax;
	float speed;

	sf::Color color;

	bool isAlive = true;
	ParticuleType type;

	int currentSprite;
};

struct Spowner
{
	sf::Vector2f pos;
	float angle = rand() % 361;
	bool rotation = rand() % 2;
	float alpha = 255;
};

class ParticuleManager
{
public:

	ParticuleManager() {};
	~ParticuleManager() {};

	void AddParticle(sf::Vector2i _pos, ParticuleType _type, int _numberOfParticules, sf::Color color = { 112, 255, 243 },float _rayon = 10);
	void AddSpowner(sf::Vector2f _pos);
	void BossExplosion(sf::Vector2i _pos, int _numberOfParticules, sf::Color _color);
	void UpdateParticule(float _dt);
	void DrawParticule(sf::RenderWindow& _window);

	std::vector<Particule>& GetVector(void) { return particules; }

	bool isExplode;
private:



	sf::Sprite etincelleSprite = LoadSprite("Assets/Particules/etincelle.png", true);
	sf::Sprite fireSprite[MAX_SPRITE_SMOG + 1] = {
LoadSprite("Assets/Particules/flamme/flamme0.png", true),
LoadSprite("Assets/Particules/flamme/flamme1.png", true),
LoadSprite("Assets/Particules/flamme/flamme2.png", true),
LoadSprite("Assets/Particules/flamme/flamme3.png", true),
LoadSprite("Assets/Particules/flamme/flamme4.png", true),
LoadSprite("Assets/Particules/flamme/flamme5.png", true),
LoadSprite("Assets/Particules/flamme/flamme6.png", true),
LoadSprite("Assets/Particules/flamme/flamme7.png", true),
LoadSprite("Assets/Particules/flamme/flamme8.png", true),
LoadSprite("Assets/Particules/flamme/flamme9.png", true),
	};
	sf::Sprite earthSprite = LoadSprite("Assets/Particules/earth.png", true);

	std::vector<Particule>particules;


	std::vector<Spowner>spowners;
	sf::Sprite SpownerSprite = LoadSprite("Assets/Shoot Them Up/Boss/Spowner.png", true);


	sf::Sound BlackHoleChargeSound = LoadSound("Assets/Particules/Sounds/PowerUpCharge.ogg");
	sf::Sound BlackHoleExplodeSound = LoadSound("Assets/Particules/Sounds/PowerUpExplode.ogg");
	sf::Sound SpawnSound = LoadSound("Assets/Particules/Sounds/Spawn.ogg");
};

#endif
