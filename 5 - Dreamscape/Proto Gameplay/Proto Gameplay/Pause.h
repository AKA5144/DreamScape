#pragma once


#include "common.h"
#include "MenuData.h"
#include "GameState.h"
#include "Player.h"

void InitPause(MenuData* _menuData, Player& _player, ControlsData m_controls);

void UpdatePause(MenuData* _menuData, sf::RenderWindow& _window, Config config, float _dt,GameState& _gameState,bool& pause, Player& m_player);

void DisplayPause(MenuData* _menuData, sf::RenderWindow& _window, ControlsData m_controls);