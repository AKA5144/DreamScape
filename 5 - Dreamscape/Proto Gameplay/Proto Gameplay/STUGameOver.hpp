#ifndef STUGAMEOVER_HPP

#include "Common.h"
#include "GameState.h"

void LoadSTUGameOver(void);
void UpdateSTUGameOver(float _dt, GameState& _gamestate, bool& _transition, float& _noirAlpha);
void DisplaySTUGameOver(sf::RenderWindow& _window);

#endif // !STUGAMEOVER_HPP

