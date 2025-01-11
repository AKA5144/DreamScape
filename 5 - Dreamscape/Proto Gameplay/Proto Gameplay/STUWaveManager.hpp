#ifndef STUWAVEMANAGER_HPP
#define STUWAVEMANAGER_HPP

#include <fstream>
#include <string>

#include "Common.h"
#include "STUEnnemie.hpp"


enum Waves
{
	FIRST,
	SECOND,
	THIRD
};

struct DeadAnim
{
	sf::Vector2f pos;
	float currentAnim = 0;
	float angle = 0;
	sf::Vector2f scale = { 3,3 };

	STUEnnemiType type;
	float alpha = 255;
	sf::Clock clock;

	bool isFinish = false;
};

class WaveManager
{
public:
	WaveManager() {};
	~WaveManager() {};

	std::string actualWave[4] = { "FIRST", "SECOND", "THIRD", "FOURTH" };

	void LoadWave(std::string _wave);
	void Update(float _dt, STUPlayer _player);
	void Display(sf::RenderWindow& _window);

	void AddEnnemie(STUEnnemiType _type, sf::Vector2f _pos, int _turn);

	std::vector<Ennemie>& GetWaveVector(void) { return waveVector; }
	int GetCurrentWave(void)const { return currentWave; }
	void SetCurrentWave(int _wave) { currentWave = _wave; }

	int GetCurrentTurn(void)const { return currentTurn; }

	int numOfType1;
	int numOfType2;
	int numOfType3;

	sf::Text waveText;
private:

	sf::Vector2f scale = { 3,3 };

	std::vector<Ennemie> waveVector;
	std::vector<DeadAnim> deadAnim;

	int type1;
	int type2;
	int type3;

	int currentTurn = 0;
	int currentWave = 0;

	bool nextWave = true;

	sf::Font waveFont;
	
	float textSpeed = -100;

	sf::Sound CristalDead = LoadSound("Assets/Shoot Them Up/Ennemi/Sounds/CristalDead.ogg");
	sf::Sound WilloDead = LoadSound("Assets/Shoot Them Up/Ennemi/Sounds/WilloDead.ogg");
	sf::Sound GhostDead = LoadSound("Assets/Shoot Them Up/Ennemi/Sounds/GhostDead.ogg");
	
	void VectorManager(void);
	void UpdateDeadAnim(float _dt);
};

#endif
