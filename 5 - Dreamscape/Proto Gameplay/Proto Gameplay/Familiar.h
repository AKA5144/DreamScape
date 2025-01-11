#ifndef FAMILIAR_HPP
#define FAMILIAR_HPP
#include "Common.h"
#include "Player.h"
#include "Particules.hpp"
#include "AnimText.h"

enum FamiliarState
{
	STATIC,
	FLY,
	INFO
};

class Familiar
{
public:
	void Set_X(float _x) { pos.x = _x; }
	void Set_Y(float _y) { pos.y = _y; }
	void Set_Pos(sf::Vector2f _pos) { pos = _pos; }
	void Set_Sprite(sf::Sprite _sprite) { currentSprite = _sprite; }
	void Set_State(FamiliarState _state) { state = _state; }
	void Set_CanMove(bool _canMove) { canMove = _canMove; }

	sf::Sprite Get_Sprite() const { return currentSprite; }
	sf::Vector2f Get_Pos() const { return pos; }
	FamiliarState Get_State() const { return state; }
	bool Get_IsCenter() { return IsCenter; }
	bool Get_CanMove() { return canMove; }

	void Fly(float _dt, Player& _player);
	void Info(float _dt, Player& _player);
	void UpdateState(Player& _player, float _dt);
	void UpdatePortalDistance(float _dt, Player& _player);

	void Load();
	void Update(float _dt, Player& _player);
	void Display(sf::RenderWindow& _window);

	bool followPlayer = false;

private:
	sf::Sprite currentSprite;
	sf::Vector2f pos;
	FamiliarState state;
	ParticuleManager particuleManager;
	bool IsCenter = false;
	bool canMove = false;
};

Familiar& Get_Familiar();

void LoadFamiliar();
void UpdateFamiliar(float _dt, Player& _player);
void DisplayFamiliar(sf::RenderWindow& _window);

#endif