#ifndef	SETTINGS__H
#define SETTINGS__H

#include "common.h"
#include "MenuData.h"
#include "Controls.h"
#include "Menu.h"
#include "VideoSettings.h"
#include "SoundSettings.h"
class MenuData;

void InitSettings(MenuData* _menuData);

void UpdateSettings(MenuData* _gameData, sf::RenderWindow& _window, Config config, float _dt,GameState& _gameState);

void DisplaySettings(MenuData* _menuData, sf::RenderWindow& _window);
#endif

