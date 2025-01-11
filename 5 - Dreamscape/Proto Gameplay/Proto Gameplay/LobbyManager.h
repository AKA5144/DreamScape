#ifndef LOBBYMANAGER_HPP
#define LOBBYMANAGER_HPP
#include "Common.h"
#include "Lobby.h"
#include "Altar.h"
#include "BossStairs.h"
#include "Familiar.h"
#include "Dialogue.h"
#include "Stars.h"

void LoadLobbyManager(Player& _player, std::string _font, sf::Vector2f& camCoord, sf::Sprite& _noir);
void UpdateLobbyManager(float _dt, Player& _player, GameState& _gameState, sf::Vector2f& camCoord, bool& animation, float& _noirAlpha, bool& _transition, SoulsLevel*& m_soulsLevel, PlatformerData& _platformerData);
void DisplayLobbyManager(sf::RenderWindow& _window, Player& _player);

#endif
