#pragma once

#include "MenuData.h"

void InitCredits(MenuData* _menuData);
void UpdateCredits(MenuData* _menuData, GameState& _gameState);
void DisplayCredits(MenuData* _menuData,sf::RenderWindow& window);

