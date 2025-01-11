#ifndef DISPLAY__H
#define DISPLAY__H

#include "common.h"
#include "Settings.h"
#include "VideoSettings.h"
#include "SoundSettings.h"
#include "Controls.h"
#include "MenuData.h"
#include "Credits.h"


void MenuDisplay(MenuData* _gameData, sf::RenderWindow& _window, ControlsData m_controls);

#endif
