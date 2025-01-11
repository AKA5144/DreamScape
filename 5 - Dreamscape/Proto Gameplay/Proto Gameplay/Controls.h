#ifndef	CONTROLS__H
#define CONTROLS__H

#include "common.h"
#include "MenuData.h"



#include "KeyString.h"
class MenuData;
class Player;
void InitControls(MenuData* _menuData, Player& _player, ControlsData m_controls);

void ControlsUpdate(MenuData* _gameData, float _dt, Player& _player, ControlsData*& m_controls, Config config);

void DisplayControls(MenuData* _menuData, sf::RenderWindow& _window, ControlsData m_controls);
#endif