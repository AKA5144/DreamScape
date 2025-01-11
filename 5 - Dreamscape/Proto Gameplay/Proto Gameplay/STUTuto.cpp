#include "STUTuto.hpp"
#include "ShootThemUp.hpp"
#include "KeyString.h"

STUGameState& gameStateInTuto = GetSTUGameState();

sf::Sprite TutoSprites;

float alpha = 255;
bool inGame;
float antiSpam;


void LoadSTUTuto(void)
{
	TutoSprites = LoadSprite("Assets/Shoot Them Up/Tuto/Tuto1.png", true);

	inGame = false;
	antiSpam = 0.0;

	alpha = 255;
}

void UpdateSTUTuto(float _dt, ControlsData*& m_controls)
{
	static sf::Clock easingClock;
	antiSpam += _dt;

	if (antiSpam > 1 && !inGame                                                                                                             )
	{
		// Boucle pour parcourir toutes les touches du clavier
		for (int key = 0; key < sf::Keyboard::KeyCount; ++key)
		{
			// Vérifie si la touche est enfoncée
			if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key)))
			{
				inGame = true;
				easingClock.restart();
				break;
			}
		}
		for (int k = 0; k < 11; k++)
		{
			if (sf::Joystick::isButtonPressed(0, k))
			{
				inGame = true;
				easingClock.restart();
				break;
			}
		}
	}
	else
	{
		alpha = 255;
	}

	if (inGame && alpha > 0)
	{
		alpha = 255 - Easing::easeInQuart(easingClock.getElapsedTime().asSeconds(), 0, 255, 1);
	}

	if (alpha <= 0)
	{
		inGame = false;
		antiSpam = 0.0;
		gameStateInTuto = STU_GAME;
	}
}

void DisplaySTUTuto(sf::RenderWindow& _window)
{
	BlitSprite(TutoSprites, { SCREEN_WIDTH/2,SCREEN_HEIGHT/2 }, _window, { 3,3 }, 0, sf::Color(255, 255, 255, alpha));
}