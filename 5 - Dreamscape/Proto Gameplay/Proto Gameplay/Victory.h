#ifndef VICTORY_H
#define VICTORY_H

#include "Common.h"
#include "GameState.h"

typedef void (*PtrFonct)(void);

struct VictoryBackground
{
	sf::Sprite sprite;
	sf::Vector2f pos;
	float alpha;
};

struct VictoryButton
{
	sf::Sprite sprite[2];
	sf::Vector2f pos;
	float alpha;
	bool selected;

	PtrFonct fonction;
};

void LoadVictory(void);
void UpdateVictory(float _dt, sf::Vector2f _mousePos, GameState& _gameState, Config _config, bool& _transition, float& _noirAlpha);
void DisplayVictory(sf::RenderWindow& _window);
#endif
