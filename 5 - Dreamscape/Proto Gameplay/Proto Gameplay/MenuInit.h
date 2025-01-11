#ifndef INIT__H
#define INIT__H

#include "common.h"
#include "Settings.h"
#include "VideoSettings.h"
#include "SoundSettings.h"
#include "Controls.h"
#include "MenuData.h"
#include "Player.h"
#include "Credits.h"

class MenuData;

void MenuInit(MenuData* _gameData, Player& _player, ControlsData m_controls);

#endif
