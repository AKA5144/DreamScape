#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "Player.h"
#include "GameState.h"
#include "ShootThemUp.hpp"
#include "SonLobby.h"
#include "BossFinal.h"
#include "LobbyManager.h"
#include "SoulsLevel.h"
#include "MenuDisplay.h"
#include "MenuInit.h"
#include "MenuUpdate.h"
#include "Platformer.h"
#include "Transition.h"
#include "Victory.h"
#include "Pause.h"
#include "Video.h"

class GameData
{
public:
	
	void Init();
	void Update();
	void Display();
	void Event();

	sf::RenderWindow m_window;
	sf::Clock m_deltaTime;

	Config m_config = KEYBOARD;

	void Set_GameState(enum GameState _gamestate) { gameState = _gamestate; }
	GameState Get_GameState() { return gameState; }

	sf::Keyboard::Key keyBinding[6] = { sf::Keyboard::Key::Z,sf::Keyboard::Key::S,sf::Keyboard::Key::Q,sf::Keyboard::Key::D,sf::Keyboard::Key::Space,sf::Keyboard::Key::LAlt };


	Player Get_Player() { return m_player; }

	std::string Get_Font() { return font; }

	sf::Vector2f camCoord;

	bool animation = false;
	
	Transition m_transition;

	bool transition = false;
	float noirAlpha = 0;
	sf::Sprite Noir;

	ControlsData* m_controls = new ControlsData;
private:
	GameState gameState = MENU;

	Player m_player;
	MenuData menuData;
	PlatformerData platformerData;
	SoulsLevel* m_soulsLevel;
	sf::Cursor m_cursor;
	float m_dt;
	Video video;

	std::string font = "Assets/Font/Monocraft.otf";

	void UpdateShooterLevel();
	void UpdateSoulsLevel();
	void UpdatePlatformerLevel();
};

#endif