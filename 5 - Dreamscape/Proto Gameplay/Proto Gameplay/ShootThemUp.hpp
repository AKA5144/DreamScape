#ifndef SHOOTTHEMUP_HPP
#define SHOOTTHEMUP_HPP

#include <string>
#include "Common.h"
#include "STUEntities.hpp"
#include "STUMiniBoss.hpp"
#include "STUHud.hpp"
#include "STUTuto.hpp"
#include "STUGameOver.hpp"



#define BG_MAX1 2
#define BG_MAX2 3
#define BG_MAX3 3
#define BG_MAX4 3
#define BG_MAX5 3

struct STUgameData
{
	sf::View viewGame;
	sf::View viewHud;

	float shakeTimer = 0;
	sf::Vector2f shakePower = {0,0};

	sf::Vector2f scaleBg = { 3,3 };

	sf::Sprite backGround1[BG_MAX1];
	sf::Sprite backGround2[BG_MAX2];
	sf::Sprite backGround3[BG_MAX3];
	sf::Sprite backGround4[BG_MAX4];
	sf::Sprite backGround5[BG_MAX5];

	sf::Vector2f bg1Pos[2];
	sf::Vector2f bg2Pos[2];
	sf::Vector2f bg3Pos[2];
	sf::Vector2f bg4Pos[2];
	sf::Vector2f bg5Pos[2];


	int bg1[2], bg2[2] ,bg3[2],bg4[2],bg5[2];

	EntitiesManager Em;
	STUMiniBoss MiniBoss;
	ShootManager Sm;
	STUHud Hud;
};

enum STUGameState
{
	STU_TUTO,
	STU_GAME,
	STU_MINI_BOSS,
	STU_BOSS,
	STU_GAME_OVER,
	STU_VICTORY
};


void LoadSTU(void);
void UpdateSTU(float _dt, GameState& _gameState, Player& _player, bool& _transition, float& _noirAlpha, ControlsData*& m_controls);
void DisplaySTU(sf::RenderWindow& _window);

void DisplayBg(sf::RenderWindow& _window);

STUGameState& GetSTUGameState(void);
STUMiniBoss& GetSTUMIniBoss(void);
STUgameData& GetSTUGameData(void);
STUHud& GetSTUHud(void);
bool& GetWait(void);

sf::View& GetGameView(void);
sf::View& GetHudView(void);
void ShakeSTU(sf::Vector2f _shake, float _time);
#endif
