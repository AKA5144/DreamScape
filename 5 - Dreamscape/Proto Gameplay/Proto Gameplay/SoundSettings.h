#ifndef	SOUNDSETTINGS__H
#define SOUNDSETTINGS__H

#include "common.h"
#include "MenuData.h"
#include "KeyString.h"
class MenuData;

void InitSoundSettings(MenuData* _menuData);
void SoundSettingsUpdate(MenuData* _gameData, sf::RenderWindow& _window, float _dt);
void DisplaySoundSettings(MenuData* _menuData, sf::RenderWindow& _window);
#endif