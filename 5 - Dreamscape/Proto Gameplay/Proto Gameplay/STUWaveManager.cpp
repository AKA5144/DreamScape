#include "STUWaveManager.hpp"
#include "CreaMaths.h"
#include "STUEntities.hpp"
#include "ShootThemUp.hpp"
#include <fstream>

#define ANIM_MORT_FIRE 4
#define ANIM_MORT_GHOST 5
#define ANIM_MORT_CRISTAL 4

STUPlayer& playerPowerUp = GetPlayer();
STUGameState& gameStateInWave = GetSTUGameState();

sf::Sprite animDeadFire[ANIM_MORT_FIRE] =
{
	LoadSprite("Assets/Shoot Them Up/Ennemi/Willo/Dead/1.png",true),
	LoadSprite("Assets/Shoot Them Up/Ennemi/Willo/Dead/2.png",true),
	LoadSprite("Assets/Shoot Them Up/Ennemi/Willo/Dead/3.png",true),
	LoadSprite("Assets/Shoot Them Up/Ennemi/Willo/Dead/4.png",true)
};

sf::Sprite animDeadGhost[ANIM_MORT_GHOST] =
{
	LoadSprite("Assets/Shoot Them Up/Ennemi/Ghost/Dead/1.png",true),
	LoadSprite("Assets/Shoot Them Up/Ennemi/Ghost/Dead/2.png",true),
	LoadSprite("Assets/Shoot Them Up/Ennemi/Ghost/Dead/3.png",true),
	LoadSprite("Assets/Shoot Them Up/Ennemi/Ghost/Dead/4.png",true),
	LoadSprite("Assets/Shoot Them Up/Ennemi/Ghost/Dead/5.png",true)
};

sf::Sprite animDeadCristal[ANIM_MORT_CRISTAL] =
{
	LoadSprite("Assets/Shoot Them Up/Ennemi/Cristal/Dead/1.png",true),
	LoadSprite("Assets/Shoot Them Up/Ennemi/Cristal/Dead/2.png",true),
	LoadSprite("Assets/Shoot Them Up/Ennemi/Cristal/Dead/3.png",true),
	LoadSprite("Assets/Shoot Them Up/Ennemi/Cristal/Dead/4.png",true)
};

sf::Sprite* animDead[3] = { animDeadFire, animDeadGhost, animDeadCristal };
int animMax[3] = { ANIM_MORT_FIRE, ANIM_MORT_GHOST, ANIM_MORT_CRISTAL };

void WaveManager::AddEnnemie(STUEnnemiType _type, sf::Vector2f _pos, int _turn)
{
	Ennemie ennemi;

	ennemi.Init(_type, _pos, _turn);

	waveVector.push_back(ennemi);
}

void WaveManager::LoadWave(std::string _wave)
{
	waveVector.clear();
	currentTurn = 0;
	nextWave = true;

	std::fstream File("Assets/Shoot Them UP/Wave/ShootThemUp.txt", std::ios::in);
	File.seekg(0);//mise au debut du fichier
	while (!File.eof())
	{
		std::string temp;
		sf::Vector2f pos;
		int turn;
		File >> temp;
		if (temp == _wave)
		{
			File >> type1;
			numOfType1 = type1;
			for (int k = 0; k < type1; k++)
			{
				File >> temp;
				pos.x = stoi(temp);
				File >> temp;
				pos.y = stoi(temp);
				File >> temp;
				turn = stoi(temp);
				pos.x = (float)(rand() % SCREEN_WIDTH);

				AddEnnemie(FIRE, pos, turn);
			}
			File >> type2;
			numOfType2 = type2;
			for (int k = 0; k < type2; k++)
			{
				File >> temp;
				pos.x = stoi(temp);
				File >> temp;
				pos.y = stoi(temp);
				File >> temp;
				turn = stoi(temp);
				pos.x = SCREEN_WIDTH / 4 + rand() % SCREEN_WIDTH / 2;
				AddEnnemie(GHOST, pos, turn);
			}
			File >> type3;
			numOfType3 = type3;
			for (int k = 0; k < type3; k++)
			{
				File >> temp;
				pos.x = stoi(temp);
				File >> temp;
				pos.y = stoi(temp);
				File >> temp;
				turn = stoi(temp);
				pos.x = (float)(rand() % 1200) + 360;
				AddEnnemie(CRISTAL, pos, turn);
			}
		}
	}
	File.close();

	waveFont.loadFromFile("Assets/Shoot Them Up/Font/Monocraft.otf");
	waveText.setFont(waveFont);
	waveText.setString("Wave " + std::to_string(currentWave + 1));

	waveText.setCharacterSize(80);
	waveText.setOutlineThickness(3);
	waveText.setOutlineColor(sf::Color::Black);
	waveText.setPosition({ SCREEN_WIDTH,SCREEN_HEIGHT / 3 });
	textSpeed = -1000;
}

void WaveManager::VectorManager(void)
{
	int num1 = 0;
	int num2 = 0;
	int num3 = 0;
	for (int k = 0; k < waveVector.size(); k++)
	{
		switch (waveVector[k].GetType())
		{
		case FIRE:
			num1++;
			if (waveVector[k].GetHp() <= 0 && !nextWave)
			{
				WilloDead.play();
			}
			break;
		case GHOST:
			num2++;
			if (waveVector[k].GetHp() <= 0 && !nextWave)
			{
				GhostDead.play();
			}
			break;
		case CRISTAL:
			num3++;
			if (waveVector[k].GetHp() <= 0 && !nextWave)
			{
				CristalDead.play();
			}
			break;
		default:
			break;
		}

		if (!waveVector[k].IsAlive())
		{
			
			DeadAnim temp;
			temp.pos = waveVector[k].GetPos();
			if (waveVector[k].GetType() == FIRE)
			{
				temp.angle = CreaMaths::RadiansToDegrees(-waveVector[k].GetAngle());
			}
			else
			{
				temp.angle = 0;
			}
			cos(waveVector[k].varCos.x) < 0 ? temp.scale.x = 3 : temp.scale.x = -3;
			temp.type = waveVector[k].GetType();

			deadAnim.push_back(temp);

			waveVector.erase(waveVector.begin() + k);
		}
	}
	numOfType1 = num1;
	numOfType2 = num2;
	numOfType3 = num3;

}

void WaveManager::UpdateDeadAnim(float _dt)
{
	for (int k = 0; k < deadAnim.size(); k++)
	{
		float time = deadAnim[k].clock.getElapsedTime().asSeconds();

		if (deadAnim[k].currentAnim <= animMax[deadAnim[k].type])
		{
			deadAnim[k].currentAnim = Easing::linear(time, 0, animMax[deadAnim[k].type], 0.4);
		}

		deadAnim[k].alpha = 255 - Easing::easeInExpo(time, 0, 255, 0.4);
		CreaMaths::Clamp(deadAnim[k].alpha, 0, 255);

		if (deadAnim[k].currentAnim >= animMax[deadAnim[k].type])
		{
			deadAnim[k].currentAnim = animMax[deadAnim[k].type] - 1;
			deadAnim[k].isFinish = true;
		}
	}

	for (int k = 0; k < deadAnim.size(); k++)
	{
		if (deadAnim[k].isFinish)
		{
			deadAnim.erase(deadAnim.begin() + k);
		}
	}
}

void WaveManager::Update(float _dt, STUPlayer _player)
{
	VectorManager();
	GetEnnemiShootManager().Update(_dt);

	if (!nextWave && GetSTUGameState() != STU_BOSS)
	{
		int scan = 0;

		for (int k = 0; k < waveVector.size(); k++)
		{
			if (waveVector[k].GetTurn() == currentTurn)
			{
				waveVector[k].Update(_dt, _player);
				scan++;
			}
		}

		scan == 0 && scan < 100 && GetSTUGameState() != STU_MINI_BOSS ? currentTurn++ : scan = 0;

		if (waveVector.size() == 0 && !playerPowerUp.GetPowerUpOnScreen() && GetSTUGameState() != STU_MINI_BOSS)
		{
			if (GetSTUGameState() != STU_BOSS)//pas de changement de vague
				currentWave < 3 ? currentWave++ : GetSTUGameState() = STU_MINI_BOSS;

			currentTurn = 0;

			if (GetSTUGameState() != STU_MINI_BOSS && GetSTUGameState() != STU_BOSS)
			{
				LoadWave(actualWave[currentWave]);
			}
			else if (GetSTUGameState() == STU_MINI_BOSS)
			{
				nextWave = true;
				waveText.setString("BOSS");
				waveText.setCharacterSize(90);
				waveText.setPosition({ SCREEN_WIDTH,SCREEN_HEIGHT / 3 });
				textSpeed = -1000;
			}
			else if (GetSTUGameState() == STU_BOSS)
			{
				nextWave = false;
				waveText.setString("EH LE BOSS");
				waveText.setCharacterSize(90);
				waveText.setPosition({ SCREEN_WIDTH,SCREEN_HEIGHT / 3 });
				textSpeed = -6000;
			}

		}
	}
	else if (GetSTUGameState() == STU_BOSS)
	{
		for (int k = 0; k < waveVector.size(); k++)
		{
			waveVector[k].Update(_dt, _player);
		}
	}
	else
	{
		//Update Wave Text between waves
		textSpeed += _dt * 460;

		waveText.setPosition({ waveText.getPosition().x - abs(textSpeed) * _dt, waveText.getPosition().y });
		if (waveText.getGlobalBounds().left + waveText.getGlobalBounds().width < 0)
		{
			nextWave = false;
		}
	}

	UpdateDeadAnim(_dt);
}

void WaveManager::Display(sf::RenderWindow& _window)
{
	GetEnnemiShootManager().Display(_window);

	for (int k = 0; k < waveVector.size(); k++)
	{
		if (waveVector[k].GetTurn() == currentTurn)
		{
			waveVector[k].Display(_window);
		}
	}

	for (int k = 0; k < deadAnim.size(); k++)
	{
		BlitSprite(animDead[deadAnim[k].type][(int)deadAnim[k].currentAnim], deadAnim[k].pos, _window, deadAnim[k].scale, deadAnim[k].angle,sf::Color(255,255,255, deadAnim[k].alpha));
	}
	_window.draw(waveText);
}
