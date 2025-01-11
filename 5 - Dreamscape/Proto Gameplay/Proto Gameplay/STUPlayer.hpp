#ifndef STUPLAYER_HPP
#define STUPLAYER_HPP


#include "Common.h"
#include "STUTurret.hpp"
#include "MenuData.h"

#define TAILLE_BG 1200
#define STU_PLAYER_HITBOX 16
#define SPEEDMAX 800
#define STU_PLAYER_INVICIBILITY 0.5


class STUPlayer
{
public:
	//Fonctions principales//
	void Load(void);
	void Update(float _dt, ControlsData*& m_controls);
	void Display(sf::RenderWindow& _window);

	sf::Vector2f GetPos(void)const { return pos; }
	void Set_Pos(sf::Vector2f _pos) { pos = _pos; }

	int GetHp(void)const { return HP; }
	void SetHp(int _Hp) { HP = _Hp; }

	float GetPowerUp(void) const { return powerUp; }
	void SetPowerUp(float _powerUp) { powerUp = _powerUp; }

	bool GetPowerUpOnScreen(void) const { return powerUpOnScreen; }
	bool GetPowerUpLunched(void) const { return powerUplunched; }

	sf::Clock GetInvicibilityClock(void) { return invincibility; }
	void RestartClock(void) { invincibility.restart(); }

	std::vector<Turret> turretVector;
	int turretDist = 100;

private:

	sf::Vector2f scale = { 3,3 };

	sf::Vector2f pos;
	sf::CircleShape hitBox;
	bool showHitBox = false;
	float speed;
	bool powerUpOnScreen = false;
	bool powerUplunched = false;
	float powerUp = 100;

	int HP = 4;
	sf::Clock invincibility;


	float currentImage = 0;
	sf::Sprite playerSprite[4] =
	{
		LoadSprite("Assets/Shoot Them Up/Player/1.png", true),
		LoadSprite("Assets/Shoot Them Up/Player/2.png", true),
		LoadSprite("Assets/Shoot Them Up/Player/3.png", true),
		LoadSprite("Assets/Shoot Them Up/Player/4.png", true)
	};
	sf::Vector2f size = (sf::Vector2f)playerSprite[0].getTexture()->getSize();

	sf::Sound newTurretSound = LoadSound("Assets/Shoot Them Up/Player/NewTurret.ogg");

	//Fonctions secondaires//
	void Input(float _dt, ControlsData*& m_controls);
	void Collision(void);
	void CollisionItems(void);
	void UpdateTurrets(float _dt);
};

#endif // !STUPLAYER_HPP