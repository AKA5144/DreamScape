#ifndef UPDATE__H
#define UPDATE__H

#include "common.h"
#include "MenuData.h"
#include "GameState.h"
#include "Player.h"
#include "Credits.h"
class MenuData;

void MenuUpdate(MenuData* _menuData, sf::RenderWindow& _window, GameState& _gameState, Config config, float _dt, Player& _player, ControlsData*& m_controls);

void PlayButtonSound(sf::Sound* _buttonSound, int& _actualButtonSound);


#endif
