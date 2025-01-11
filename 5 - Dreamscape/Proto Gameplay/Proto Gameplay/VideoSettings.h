#ifndef	VIDEOSETTINGS__H
#define VIDEOSETTINGS__H

#include "common.h"
#include "MenuData.h"
#include "KeyString.h"
class MenuData;

void InitVideoSettings(MenuData* _menuData);

void VideoSettingsUpdate(MenuData* _gameData, sf::RenderWindow& _window, float _dt);

void DisplayVideoSettings(MenuData* _menuData, sf::RenderWindow& _window);
#endif
#pragma once
