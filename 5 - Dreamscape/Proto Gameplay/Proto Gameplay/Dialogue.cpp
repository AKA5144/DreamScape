#include "Dialogue.h"
#define MARGE_DERREUR 44

#define MAX_CHARACTERS 500
#define CHARACTER_SIZE 22

#define MAX_TYPE_TEXT 2//nombre de theme differents

#define MAX_TEXT_STORY 4
#define MAX_TEXT_PLATFORMER 14//sans compter la premiere ligne
#define MAX_TEXT_ACTION 11
#define MAX_TEXT_STU 9

bool IsDialogue;

Dialogue barre;

AnimText* textStory[MAX_TEXT_STORY];
AnimText* textLevel[2];

AnimText** TabText[MAX_TYPE_TEXT] = { textStory, textLevel };

bool CanDisplayText = false;

textType actualDialogueType;
int actualDialogueLine;

bool canGoInLevel = false;

bool isPortalText = false;

void LoadText(sf::Vector2f _pos)
{
	sf::Vector2f finalPos = _pos;

	actualDialogueLine = 0;

	switch (actualDialogueType)
	{
	case STORY_TEXT:
		for (int k = 0; k < MAX_TEXT_STORY; k++)
		{
			textStory[k] = new AnimText;
			textStory[k]->SetCharacterSize(CHARACTER_SIZE);
			textStory[k]->SetTextLimit(MAX_CHARACTERS);
			textStory[k]->Init("Dialogue/FamiliarText.txt", finalPos, k + 1);
		}

		TabText[0] = textStory;
		break;
	case PLATFORMER_TEXT:
		for (int k = 0; k < 2; k++)
		{
			textLevel[k] = new AnimText;
			textLevel[k]->SetCharacterSize(CHARACTER_SIZE);
			textLevel[k]->SetTextLimit(MAX_CHARACTERS);
		}
		textLevel[0]->Init("Dialogue/PlatformerText.txt", finalPos, 2 + rand() % MAX_TEXT_PLATFORMER);
		textLevel[1]->Init("Dialogue/PlatformerText.txt", finalPos, 1);
		TabText[1] = textLevel;
		break;
	case ACTION_RPG_TEXT:
		for (int k = 0; k < 2; k++)
		{
			textLevel[k] = new AnimText;
			textLevel[k]->SetCharacterSize(CHARACTER_SIZE);
			textLevel[k]->SetTextLimit(MAX_CHARACTERS);
		}
		textLevel[0]->Init("Dialogue/ActionText.txt", finalPos, 2 + rand() % MAX_TEXT_ACTION);
		textLevel[1]->Init("Dialogue/ActionText.txt", finalPos, 1);
		TabText[1] = textLevel;
		break;
	case STU_TEXT:
		for (int k = 0; k < 2; k++)
		{
			textLevel[k] = new AnimText;
			textLevel[k]->SetCharacterSize(CHARACTER_SIZE);
			textLevel[k]->SetTextLimit(MAX_CHARACTERS);
		}
		textLevel[0]->Init("Dialogue/StuText.txt", finalPos, 2 + rand() % MAX_TEXT_STU);
		textLevel[1]->Init("Dialogue/StuText.txt", finalPos, 1);
		TabText[1] = textLevel;
		break;
	default:
		break;
	}


}

//fonction pour Débuter un dialogue
void InitDialogue(sf::Vector2f _pos, textType _dialogueType)
{
	actualDialogueType = _dialogueType;
	IsDialogue = true;
	canGoInLevel = false;
	LoadText(_pos);
}

void UpdateText(float _dt)
{
	static sf::Clock waitTimer;

	if (CanDisplayText)
	{
		actualDialogueType == STORY_TEXT ? isPortalText = false : isPortalText = true;
		TabText[isPortalText][actualDialogueLine]->Update(_dt);

		if (waitTimer.getElapsedTime().asSeconds() > 0.3 && (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Joystick::isButtonPressed(0, (int)ControllerButton::A)))
		{
			PlayDialogueSound();
			if (TabText[isPortalText][actualDialogueLine]->allDisplay)
			{
				actualDialogueLine++;

				if (actualDialogueType == STORY_TEXT)
				{
					if (actualDialogueLine == MAX_TEXT_STORY)
					{
						actualDialogueLine = 0;
						IsDialogue = false;

						for (int k = 0; k < MAX_TEXT_STORY; k++)
						{
							delete textStory[k];
						}
						Get_Familiar().Set_State(FLY);
						canGoInLevel = true;

					}
				}
				else
				{
					if (actualDialogueLine == 2)
					{
						actualDialogueLine = 0;
						IsDialogue = false;

						for (int k = 0; k < 2; k++)
						{
							delete textLevel[k];
						}

						canGoInLevel = true;
					}
				}
			}
			else
			{
				TabText[isPortalText][actualDialogueLine]->multiplicator = SKIP_MULTIPLICATOR;

			}
			waitTimer.restart();
		}
	}
}

void DisplayText(sf::RenderWindow& _window)
{
	if (CanDisplayText)
	{
		TabText[isPortalText][actualDialogueLine]->Draw(_window);
	}
}

void UpDialogue(float _dt, bool& _animation)
{
	if (IsDialogue)
	{
		_animation = true;
		sf::Vector2f finalPos = { SCREEN_WIDTH / 2 , SCREEN_HEIGHT - (float)(barre.sprite.getTexture()->getSize().y * 3) / 2 - MARGE_DERREUR };
		sf::Vector2f director = finalPos - barre.pos;
		int norme = sqrtf(director.x * director.x + director.y * director.y);

		if (norme > 1)
		{
			barre.pos.x += director.x * 4 * _dt;
			barre.pos.y += director.y * 4 * _dt;
			CanDisplayText = false;
		}
		else
		{
			CanDisplayText = true;
		}
	}
	else
	{
		sf::Vector2f finalPos = { SCREEN_WIDTH / 2 , (float)(SCREEN_HEIGHT + (float)(barre.sprite.getTexture()->getSize().y * 3) / 2 + MARGE_DERREUR) };
		sf::Vector2f director = finalPos - barre.pos;
		int norme = sqrtf(director.x * director.x + director.y * director.y);

		if (norme > 1)
		{
			barre.pos.x += director.x * 4 * _dt;
			barre.pos.y += director.y * 4 * _dt;
			CanDisplayText = false;
			_animation = false;
		}

	}
}

void LoadDialogue()
{
	barre.sprite = LoadSprite("Assets/Lobby/Divers/ChatBox.png", true);
	barre.pos = { SCREEN_WIDTH / 2 , (float)(SCREEN_HEIGHT + barre.sprite.getTexture()->getSize().y / 2 + MARGE_DERREUR) };

	sf::Vector2f posDialogue = { 45 * (SCREEN_WIDTH / 120) , SCREEN_HEIGHT - 180 };
	InitDialogue(posDialogue, STORY_TEXT);
}

void UpdateDialogue(float _dt, bool& _animation)
{
	UpDialogue(_dt, _animation);
	UpdateText(_dt);
}

void DisplayDialogue(sf::RenderWindow& _window)
{
	BlitSprite(barre.sprite, (sf::Vector2f)_window.mapPixelToCoords((sf::Vector2i)barre.pos), _window, { 4 , 3 }, 0, sf::Color(255, 255, 255, 190));
	DisplayText(_window);
}

textType& GetActualDialogueType(void)
{
	return actualDialogueType;
}

bool CanGoInLevel(void)
{
	return canGoInLevel;
}