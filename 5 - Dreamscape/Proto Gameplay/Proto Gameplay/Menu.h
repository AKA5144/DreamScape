#ifndef MENU__H
#define MENU__H

#include "common.h"
#include "MenuData.h"
#include "GameState.h"
#include "Player.h"
class MenuData;

void MainMenuUpdate(MenuData* _gameData, sf::RenderWindow& _window, GameState& _gameState, Config config, float _dt, Player& _player);
#endif
#pragma once
