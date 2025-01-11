#ifndef SOULS_LEVEL_H
#define SOULS_LEVEL_H

#include "Common.h"
#include "Camera.h"
#include "SLPlayer.h"
#include "SLMap.h"
#include "SLMiniMap.h"
#include "SLEnemies.h"
#include "SLHUD.h"
#include "SLShaders.h"
#include "SLBoss.h"
#include "SLTutorial.h"

class SoulsLevel
{
public:
	SoulsLevel(sf::String _map);
	~SoulsLevel() { delete m_map; }

	void Update(float _dt, Config _config);
	void Display(sf::RenderWindow& _window);

	const bool HasWon() { return m_hasWon; }
	const bool HasLost() { return m_hasLost; }

	SLPlayer& Get_Player() { return m_player; }
	Camera& Get_Camera() { return m_camera; }
	SLShaders& Get_Shader() { return m_shaders; }
	SLHUD& Get_HUD() { return m_HUD; }
private:
	Camera m_camera;

	SLMap* m_map;

	std::string m_mapString;
	
	SLPlayer m_player;
	std::vector<SLEnemy> m_enemies;
	std::vector<SLEnemy*> m_onScreenEnemies;
	SLBoss m_boss;
	
	SLMinimap* m_miniMap;
	SLHUD m_HUD;

	SLTutorial* m_tutorial;

	SLShaders m_shaders;
	SLSounds m_sounds;

	bool m_hasWon;
	bool m_hasLost;

	// Load
	void CreateEnemies();

	// Collisions
	void UpdateMapCollisions(float _dt);
	void UpdatePlayerEnemiesCollisions();
	void UpdatePlayerBossCollision(float _dt);

	// Ennemis
	void UpdateLockMechanic();
	void GetOnScreenEnemies();
	void LockEnemy();
	void SwitchTarget(sf::Vector2f _vectorJoystick);
	void CheckWinAndLossCondition();
	int GetEnemyID(SLEnemy* _enemyPtr);
	void UpdateEnemies(float _dt);
};

#endif