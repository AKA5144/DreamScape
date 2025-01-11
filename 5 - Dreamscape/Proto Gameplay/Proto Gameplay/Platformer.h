#ifndef PLATFORMER_HPP
#define PLATFORMER_HPP
#include "Common.h"
#include "MapManagerNeyl.hpp"
#include "PlayerNeyl.hpp"
#include "BossNeyl.h"
#include "Camera.h"
#include "MenuData.h"
#include "Player.h"

struct PlatformerData
{

	mapSprite mapSprite;
	sf::Clock clock;
	Map spriteMap;
	Map badMap;
	picMap picMap;
	AssetMap assetMap;
	backMap BackMap;
	BreakMap breakMap;
	PlayerPlatformer players;
	BossNeyl boss;
	Camera camera;
	sf::Vector2f cameraPos;
	sf::Music PlatformerMusic;
	sf::Music PlatformerMusic2;
	bool isPhase2Triggered = false;
	bool finalBoss = false;
	Map FinalBossMap;
	Map FinalBossBadMap;
	backMap FinalBossBackMap;
	AssetMap FinalBossAssetsMap;

	bool tutorial;
};

void InitPlatformer(PlatformerData& gameData);
void UpdatePlatformer(float elapsed, PlatformerData& gameData, sf::RenderWindow& _window, GameState& _gameState, bool& _transition, float _noirAlpha, ControlsData*& m_controls, Player& _player);
void DrawPlatformer(PlatformerData& gameData, sf::RenderWindow& _window);

int& Get_PlatformerHp();
sf::RectangleShape& Get_HpBar();
sf::Sprite& Get_PlayerHead();
sf::Text& Get_HpText();
#endif // !PLATFORMER_HPP
