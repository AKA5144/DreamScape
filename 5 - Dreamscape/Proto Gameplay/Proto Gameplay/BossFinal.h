#ifndef BOSSFINAL_HPP
#define BOSSFINAL_HPP
#include "Common.h"
#include "SoulsBoss.h"
#include "ParcourBoss.h"
#include "STUBoss.h"
#include "BossFinalSound.h"
#include "Familiar.h"


void LoadBoss();
void UpdateBoss(float _dt, GameState& _gameState, Player& _player, bool& _transition, float _noirAlpha, Config _config, SoulsLevel*& _soulsLevel, PlatformerData& _platformerData, sf::RenderWindow& _window, ControlsData*& m_controls, SoulsLevel* m_soulsLevel);
void DisplayBoss(sf::RenderWindow& _window, SoulsLevel*& _soulsLevel, PlatformerData& _platformerData);

Boss& GetFinalBoss();

#endif // !BOSSFINAL_HPP
