#ifndef STUBOSS_HPP
#define STUBOSS_HPP
#include "Common.h"
#include "BossTemplate.h"
#include "Lobby.h"
#include "STUEnnemie.hpp"
#include "Particules.hpp"

enum BulletDirection
{
	DROITE,
	GAUCHE
};

class Mine
{
public:
	void Set_X(float _x) { pos.x = _x; }
	void Set_Y(float _y) { pos.y = _y; }
	void Set_Pos(sf::Vector2f _pos) { pos = _pos; }
	void Set_Sprite(sf::Sprite _sprite) { sprite = _sprite; }
	void Set_IsDestroyed(bool _IsDestroyed) { IsDestroyed = _IsDestroyed; }

	sf::Vector2f Get_Pos() { return pos; }
	sf::Sprite Get_Sprite() { return sprite; }
	bool Get_IsDestroyed() { return IsDestroyed; }

	void UpdateMove(float _dt);

private:
	sf::Vector2f pos;
	sf::Sprite sprite;
	bool IsDestroyed = false;
};

class Bullet
{
public:
	void Set_X(float _x) { pos.x = _x; }
	void Set_Y(float _y) { pos.y = _y; }
	void Set_Pos(sf::Vector2f _pos) { pos = _pos; }
	void Set_Sprite(sf::Sprite _sprite) { sprite = _sprite; }
	void Set_Decalage(int _decalage) { decalage = _decalage; }
	void Set_Direction(BulletDirection _dir) { dir = _dir; }

	sf::Vector2f Get_Pos() { return pos; }
	sf::Sprite Get_Sprite() { return sprite; }
	sf::Clock Get_Time() { return moveTime; }
	int Get_Decalage() { return decalage; }
	BulletDirection Get_Direction() { return dir; }

	void Move(float _dt, Boss& _theBoss);

private:
	sf::Vector2f pos;
	sf::Sprite sprite;
	sf::Clock moveTime;
	int decalage = -2;
	BulletDirection dir;
};

void LoadSTUBoss();
void UpdateSTUBoss(float _dt, GameState& _gameState, Player& _player, Boss& _theBoss, bool& _transition, float _noirAlpha, ControlsData*& m_controls);
void DisplaySTUBoss(sf::RenderWindow& _window, Boss& _theBoss);

void DisplayHeal(sf::RenderWindow& _window, Boss& _theBoss);

std::vector <Mine>& GetMineVector();
std::vector <Bullet>& GetBulletVector();
#endif // !STUBOSS_HPP
