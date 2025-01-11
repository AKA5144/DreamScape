#include "LobbyManager.h"

////////////////////////////////////////// FONCTION SACREE ////////////////////////////////////////// 

void LoadLobbyManager(Player& _player, std::string _font, sf::Vector2f& camCoord, sf::Sprite& _noir)
{
	LoadLobby(_player, _font, camCoord);
	LoadAltar(_player, _font, _noir);
	LoadStairs();
	LoadFamiliar();
	LoadDialogue();
	LoadStars();
}

void UpdateLobbyManager(float _dt, Player& _player, GameState& _gameState, sf::Vector2f& camCoord, bool& animation, float& _noirAlpha, bool& _transition, SoulsLevel*& m_soulsLevel, PlatformerData& _platformerData)
{
	UpdateAltar(_dt, _player, camCoord, animation, _noirAlpha, _transition);
	UpdateLobby(_dt, _player, _gameState, camCoord, animation, _noirAlpha, _transition, m_soulsLevel);
	UpdateStairs(_dt, _player, _transition, _gameState, _noirAlpha, m_soulsLevel, _platformerData);
	UpdateFamiliar(_dt, _player);
	UpdateDialogue(_dt, animation);
	UpdateStars(_dt);
}

void DisplayLobbyManager(sf::RenderWindow& _window, Player& _player)
{
	DisplayLobby(_window, _player);
	DisplayStars(_window);
	DisplayStairs(_window);
	DisplayAltar(_window, _player);
	DisplayFamiliar(_window);
	DisplayBossInfo(_window, _player);
	DisplayDialogue(_window);
}