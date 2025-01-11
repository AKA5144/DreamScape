#ifndef SOULSBOSS_HPP
#define SOULSBOSS_HPP
#include "Common.h"
#include "BossTemplate.h"
#include "SoulsLevel.h"

class HandFall
{
public:
	void Set_ShadowSprite(sf::Sprite _shadow) { shadow = _shadow; }
	void Set_HandSprite(sf::Sprite _hand) { hand = _hand; }
	void Set_HandPos(sf::Vector2f _pos) { handPos = _pos; }
	void Set_ShadowPos(sf::Vector2f _pos) { shadowPos = _pos; }
	void Set_Rotation(float _rotation) { rotation = _rotation; }
	void Set_Alpha(float _alpha) { alpha = _alpha; }

	sf::Sprite Get_ShadowSprite() { return shadow; }
	sf::Sprite Get_HandSprite() { return hand; }
	sf::Vector2f Get_HandPos() { return handPos; }
	sf::Vector2f Get_ShadowPos() { return shadowPos; }
	float Get_Rotation() { return rotation; }
	bool Get_CanErase() { return canErase; }
	float Get_Alpha() { return alpha; }

	void UpdateAnimation();
	void UpdateFalling(float _dt, SoulsLevel*& _soulsLevel, Boss& _theBoss);
	void PlayerDamage(SoulsLevel*& _soulsLevel, Boss& _theBoss);

	void Load(sf::Vector2f _pos);
	void Update(float _dt, SoulsLevel*& _soulsLevel, Boss& _theBoss);

private:
	sf::Sprite shadow;
	sf::Sprite hand;

	sf::Vector2f handPos;
	sf::Vector2f shadowPos;
	float timer = 0;
	float rotation = 0;
	float compteur = 0;
	float alpha = 255;
	float norme = 0;
	float normeMax;

	bool canErase = false;
	bool isFall = false;
	bool isDamageDone = false;
};

void LoadSoulsBoss();
void UpdateSoulsBoss(float _dt, Config _config, SoulsLevel*& _soulsLevel, GameState& _gameState, bool& _transition, float _noirAlpha, Player& _player, Boss& _theBoss);
void DisplaySoulsBoss(sf::RenderWindow& _window, SoulsLevel*& _soulsLevel, Boss& _theBoss);

#endif // !SOULSBOSS_HPP
