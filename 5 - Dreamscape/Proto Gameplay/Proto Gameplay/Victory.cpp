#include "Victory.h"
#include "Easing.h"
#include "Collisions.h"

#define MAX_VICTORY_BG 4
#define MAX_VICTORY_BUTTON 2
#define TIME_SCROLL_EASING 4
#define TIME_ALPHA_BG_VICTORY 1

VictoryBackground victoryBg[MAX_VICTORY_BG];
VictoryButton victoryButton[MAX_VICTORY_BUTTON];

PtrFonct FonctionVictory[2];

float timer;
int currentButton;

GameState nextGameState;
sf::View victoryView;

void SetToLobby()
{
	nextGameState = LOBBY;
}

void SetToMenu()
{
	nextGameState = MENU;
}

void LoadVictory(void)
{
	victoryView.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

	FonctionVictory[0] = SetToMenu;
	FonctionVictory[1] = SetToLobby;

	for (int k = 0; k < MAX_VICTORY_BG; k++)
	{
		victoryBg[k].sprite = LoadSprite("Assets/Victory/bg/" + std::to_string(k + 1) + ".png", false);
		victoryBg[k].pos = { 0,0 - k * (float)(victoryBg[k].sprite.getTexture()->getSize().y * 3) };
		victoryBg[k].alpha = 255;
	}

	for (int k = 0; k < MAX_VICTORY_BUTTON; k++)
	{
		victoryButton[k].sprite[0] = LoadSprite("Assets/Victory/button/UnSelect/" + std::to_string(k + 1) + ".png", true);
		victoryButton[k].sprite[1] = LoadSprite("Assets/Victory/button/Select/" + std::to_string(k + 1) + ".png", true);
		victoryButton[k].pos = { (k + 1) * (float)(SCREEN_WIDTH / 3), 5 * (float)(SCREEN_HEIGHT / 6) };
		victoryButton[k].alpha = 0;
		victoryButton[k].selected = false;
		victoryButton[k].fonction = FonctionVictory[k];
	}

	currentButton = 0;
	timer = 0;
	nextGameState = VICTORY;
}

void MoveVictory(float _dt)
{
	static float sizeY = victoryBg[0].sprite.getTexture()->getSize().y * 3;

	if (nextGameState == VICTORY)
	{
		victoryBg[0].pos.y = Easing::easeInOutExpo(timer, 0, sizeY * (MAX_VICTORY_BG - 1), TIME_SCROLL_EASING);
	}
	else
	{
		victoryBg[0].pos.y = sizeY * (MAX_VICTORY_BG - 1) - Easing::easeInOutExpo(timer, 0, sizeY * (MAX_VICTORY_BG - 1), TIME_SCROLL_EASING);
	}


	for (int k = 1; k < MAX_VICTORY_BG; k++)
	{
		victoryBg[k].pos = { 0, victoryBg[k - 1].pos.y - sizeY };
	}
}


void UpdateVictoryButton(float _dt, sf::Vector2f _mousePos, Config _config)
{
	static float sizeX = victoryButton[0].sprite[0].getTexture()->getSize().x * 3;
	static float sizeY = victoryButton[0].sprite[0].getTexture()->getSize().y * 3;

	static sf::Clock waitTimer;

	if (timer >= TIME_SCROLL_EASING && nextGameState == VICTORY)
	{
		for (int k = 0; k < MAX_VICTORY_BUTTON; k++)
		{

			if (victoryButton[k].alpha < 254)
			{
				float tempAlpha;
				tempAlpha = Easing::easeOutCirc(timer - TIME_SCROLL_EASING, 0, 255, 2);

				victoryButton[k].alpha = tempAlpha >= 255 ? 255 : tempAlpha;
			}
			else
			{
				victoryButton[k].alpha = 255;

				if (_config == KEYBOARD)
				{
					sf::FloatRect hitBox = { victoryButton[k].pos.x - (sizeX / 2),victoryButton[k].pos.y - (sizeY / 2),0,0 };
					hitBox.width = sizeX;
					hitBox.height = sizeY;

					victoryButton[k].selected = false;
					if (Collisions::IsCollidingRectPoint(hitBox, _mousePos))
					{
						victoryButton[k].selected = true;

						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							victoryButton[k].fonction();
							timer = 0;
							currentButton = k;
						}
					}
				}
				else
				{
					if (waitTimer.getElapsedTime().asSeconds() > 0.2)
					{
						if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -50)
						{
							currentButton--;
							waitTimer.restart();
						}
						else if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 50)
						{
							currentButton++;
							waitTimer.restart();
						}
					}

					if (currentButton > MAX_VICTORY_BUTTON - 1)
					{
						currentButton = 0;
					}
					else if (currentButton < 0)
					{
						currentButton = MAX_VICTORY_BUTTON - 1;
					}

					if (currentButton == k)
					{
						victoryButton[k].selected = true;
					}
					else
					{
						victoryButton[k].selected = false;
					}

					if (sf::Joystick::isButtonPressed(0, (int)ControllerButton::A))
					{
						victoryButton[currentButton].fonction();
						timer = 0;
					}
				}
			}
		}
	}
	else if (nextGameState != VICTORY)
	{
		for (int k = 0; k < MAX_VICTORY_BUTTON; k++)
		{
			if (victoryButton[k].alpha > 1)
			{
				float tempAlpha;
				tempAlpha = 255 - Easing::easeOutCirc(timer, 0, 255, 1);

				victoryButton[k].alpha = tempAlpha <= 0 ? 0 : tempAlpha;
			}
			else
			{
				victoryButton[k].alpha = 0;
			}
		}
	}
}

void UpdateVictory(float _dt, sf::Vector2f _mousePos, GameState& _gameState, Config _config, bool& _transition, float& _noirAlpha)
{
	timer += _dt;
	MoveVictory(_dt);
	UpdateVictoryButton(_dt, _mousePos, _config);

	if (nextGameState != VICTORY)
	{
		if (timer > TIME_SCROLL_EASING)
		{
			_transition = true;

			if (_noirAlpha >= 254)
			{
				_transition = false;
				_gameState = nextGameState;
				LoadVictory();
			}
		}
	}
}

void DisplayVictory(sf::RenderWindow& _window)
{
	_window.setView(victoryView);

	for (int k = 0; k < MAX_VICTORY_BG; k++)
	{
		if (victoryBg[k].pos.y <= SCREEN_HEIGHT)
		{
			BlitSprite(victoryBg[k].sprite, victoryBg[k].pos, _window, { 3,3 }, 0, sf::Color(255, 255, 255, victoryBg[k].alpha));
		}
	}

	for (int k = 0; k < MAX_VICTORY_BUTTON; k++)
	{
		BlitSprite(victoryButton[k].sprite[victoryButton[k].selected], victoryButton[k].pos, _window, {3,3}, 0, sf::Color(255, 255, 255, victoryButton[k].alpha));
	}
}