#ifndef BOSSSTAIRS_HPP
#define BOSSSTAIRS_HPP
#include "Common.h"
#include "Player.h"
#include "GameState.h"
#include "SonLobby.h"
#include "ShootThemUp.hpp"
#include "BossFinal.h"
#include "BossTemplate.h"
#include "Platformer.h"


class Stairs
{
public:
	void Set_X(float _x) { pos.x = _x; }
	void Set_Y(float _y) { pos.y = _y; }
	void Set_Pos(sf::Vector2f _pos) { pos = _pos; }
	void Set_Sprite(sf::Sprite _sprite) { sprite = _sprite; }

	sf::Vector2f Get_Pos() { return pos; }
	sf::Sprite Get_Sprite() { return sprite; }

	void UpdateStairsCollision(Player& _player);
	void DetectAnimation(Player& _player);

	
private:
	sf::Vector2f pos;
	sf::Sprite sprite;
};

void LoadStairs();
void UpdateStairs(float _dt, Player& _player, bool& _transition, GameState& _gameState, float& _noirAlpha, SoulsLevel*& m_soulsLevel, PlatformerData& _platformerData);
void DisplayStairs(sf::RenderWindow& _window);

#endif // !BOSSSTAIRS_HPP
