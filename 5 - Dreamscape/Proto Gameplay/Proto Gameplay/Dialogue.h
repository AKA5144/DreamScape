#ifndef DIALOGUE_HPP
#define DIALOGUE_HPP
#include "Common.h"
#include "AnimText.h"
#include "SonLobby.h"
#include "Familiar.h"

enum textType
{
	STORY_TEXT,
	PLATFORMER_TEXT,
	ACTION_RPG_TEXT,
	STU_TEXT
};

struct Dialogue
{
	sf::Sprite sprite;
	sf::Vector2f pos;
};

void InitDialogue(sf::Vector2f _pos, textType _dialogueType);

void LoadDialogue();
void UpdateDialogue(float _dt, bool& _animation);
void DisplayDialogue(sf::RenderWindow& _window);

textType& GetActualDialogueType(void);
bool CanGoInLevel(void);

#endif // !DIALOGUE_HPP
