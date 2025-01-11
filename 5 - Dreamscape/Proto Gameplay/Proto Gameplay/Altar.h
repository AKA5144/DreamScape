#ifndef ATLAR_HPP
#define ALTAR_HPP
#include "Common.h"
#include "Player.h"
#include "sonLobby.h"
#include "Familiar.h"

class Totem
{
public:
	void Set_X(float _x) { pos.x = _x; }
	void Set_Y(float _y) { pos.y = _y; }
	void Set_Pos(sf::Vector2f _pos) { pos = _pos; }
	void Set_Sprite(sf::Sprite _sprite) { sprite = _sprite; }
	void Set_IsDisplay(bool _isDisplay) { IsDisplay = _isDisplay; }

	sf::Vector2f Get_Pos() { return pos; }
	sf::Sprite Get_Sprite() { return sprite; }
	bool Get_IsDisplay() { return IsDisplay; }

	void Display(sf::RenderWindow& _window);

private:
	sf::Vector2f pos;
	sf::Sprite sprite;
	bool IsDisplay;
};

class Altar
{
public:
	void Set_X(float _x) { pos.x = _x; }
	void Set_Y(float _y) { pos.y = _y; }
	void Set_Pos(sf::Vector2f _pos) { pos = _pos; }
	void Set_Sprite(sf::Sprite _sprite) { sprite = _sprite; }

	sf::Vector2f Get_Pos() { return pos; }
	sf::Sprite Get_Sprite() { return sprite; }

	void UpdateCollisionAltar(Player& _player);
	void UpdatePressEText(float _dt, Player& _player);


private:
	sf::Vector2f pos;
	sf::Sprite sprite;
};

void LoadAltar(Player& _player, std::string _font, sf::Sprite& _noir);
void UpdateAltar(float _dt, Player& _player, sf::Vector2f& _camCoord, bool& animation, float& _noirAlpha, bool& _transition);
void DisplayAltar(sf::RenderWindow& _window, Player& _player);

void UpdateTransition(float _dt, float& _noirAlpha, bool& _transition);

void SaveGame(Player& _player);
void LoadGame(Player& _player);

#endif
