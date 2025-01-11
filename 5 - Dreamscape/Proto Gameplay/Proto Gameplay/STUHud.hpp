#ifndef STUHUD_HPP
#define STUHUD_HPP

#include "Common.h"
#include "STUEntities.hpp"
#include "Easing.h"

class STUHud
{
public:
	void Load(void);
	void Update(float _dt);
	void Display(sf::RenderWindow& _window);

	void SetComboAngle(float _angle) { combo.setRotation(_angle); }

private:

	sf::Font font;

	std::string string;
	std::string tips;

	sf::Text waveCapacityText;
	sf::Text currentWaveText;
	sf::Text numOfEnemies;
	sf::Text hpText;
	sf::Text powerUpText;
	sf::Text scoreTemp;
	sf::Text scoreFinal;
	sf::Text combo;
	sf::Text highScore;

	sf::Text tipsText;

	float currentHeart;
	
	sf::Sprite spriteHUD[2] = {
		LoadSprite("Assets/Shoot Them Up/HUD/HUDBar/HUD Left.png", false),
		LoadSprite("Assets/Shoot Them Up/HUD/HUDBar/HUD Right.png", false)
	};
	sf::Sprite spriteTips = LoadSprite("Assets/Shoot Them Up/HUD/Tips/Tips.png", true);

	
	sf::Sprite powerUp[2] =
	{
		LoadSprite("Assets/Shoot Them Up/HUD/PowerUp/PowerUpBase.png", false),
		LoadSprite("Assets/Shoot Them Up/HUD/PowerUp/PowerUpFull.png", false)
	};
	float powerUpSizeX = powerUp[0].getTexture()->getSize().x*3;
	float powerUpSizeY = powerUp[0].getTexture()->getSize().y*3;

	sf::Sprite BossHp[2] =
	{
		LoadSprite("Assets/Shoot Them Up/Boss/HP/Void.png", true),
		LoadSprite("Assets/Shoot Them Up/Boss/HP/Full.png", true)
	};

	sf::Sprite heartAnim[8] =
	{
		LoadSprite("Assets/Shoot Them Up/HUD/HP/HP1.png", true),
		LoadSprite("Assets/Shoot Them Up/HUD/HP/HP2.png", true),
		LoadSprite("Assets/Shoot Them Up/HUD/HP/HP3.png", true),
		LoadSprite("Assets/Shoot Them Up/HUD/HP/HP4.png", true),
		LoadSprite("Assets/Shoot Them Up/HUD/HP/HP5.png", true),
		LoadSprite("Assets/Shoot Them Up/HUD/HP/HP6.png", true),
		LoadSprite("Assets/Shoot Them Up/HUD/HP/HP7.png", true),
		LoadSprite("Assets/Shoot Them Up/HUD/HP/HP8.png", true)

	};
	float heartSizeY = heartAnim[0].getTexture()->getSize().y * 3;

	float bossHpAlpha;

	WaveManager& HudWave = GetWaveManager();
	STUPlayer& Player = GetPlayer();
	STUScore& ScoreManger = GetScoreManager();

	void UpdateText(void);
	void UpdatePowerUp(float _dt);
	void UpdateHPBoss(float _dt);

	void LoadTips(int _num);
};

#endif