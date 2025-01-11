#ifndef LOBBY_HPP
#define LOBBY_HPP
#include "Common.h"
#include "Player.h"
#include "GameData.h"
#include "Familiar.h"
#include "Animation.h"

class PortalEffect
{
public:
	void Set_Pos(sf::Vector2f _pos) { pos = _pos; }
	void Set_Rotation(float _rotation) { rotation = _rotation; }
	void Set_Sprite(sf::Sprite _sprite) { sprite = _sprite; }

	sf::Vector2f Get_Pos() { return pos; }
	float Get_Rotation() { return rotation; }

	void Rotate(float _dt);
	void Display(sf::RenderWindow& _window);
private:
	sf::Sprite sprite;
	sf::Vector2f pos;
	float rotation = 0;

};

class Portal
{
public:
	void Set_Color(sf::Color _color) { color = _color; }
	void Set_Pos(sf::Vector2f _pos) { pos = _pos; }
	void Set_Sprite(sf::Sprite _sprite) { sprite = _sprite; }
	void Set_GameState(enum GameState _gameState) { gameState = _gameState; }
	void Set_SpriteVector(std::vector<sf::Sprite>& _spriteVector) { spriteVector = _spriteVector; }

	sf::Color Get_Color() { return color; }
	sf::Vector2f Get_Pos() { return pos; }
	sf::Sprite Get_Sprite() { return sprite; }
	enum GameState Get_GameState() { return gameState; }
	std::vector <sf::Sprite>& Get_SpriteVector() { return spriteVector; }

	void UpdateAnimation(float _dt);
	void Display(sf::RenderWindow& _window);

	PortalEffect effect;

private:
	sf::Color color;
	sf::Vector2f pos;
	sf::Clock cooldown;
	int compteur = 0;
	std::vector <sf::Sprite> spriteVector;
	sf::Sprite sprite;

	GameState gameState;
};

void LoadLobby(Player& _player, std::string _font, sf::Vector2f& camCoord);
void UpdateLobby(float _dt, Player& _player, GameState& _gameState, sf::Vector2f& camCoord, bool& animation, float& _noirAlpha, bool& _transition, SoulsLevel*& m_soulsLevel);
void DisplayLobby(sf::RenderWindow& _window, Player& _player);

static sf::View playerView;

void DisplayBossInfo(sf::RenderWindow& _window, Player& _player);

sf::Image& Get_ImageData();
#endif // !LOBBY_HPP
