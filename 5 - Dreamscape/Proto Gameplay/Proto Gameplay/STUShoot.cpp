#include "STUShoot.hpp"
#include "STUEntities.hpp"
#include "ShootThemUp.hpp"
#include "BossFinal.h"
#include "CreaMaths.h"

sf::Sprite player = LoadSprite("Assets/Shoot Them UP/Shoots/PlayerShoot.png", true);
sf::Sprite cristalShot = LoadSprite("Assets/Shoot Them UP/Shoots/Cristal.png", true);
sf::Sprite ghostShot = LoadSprite("Assets/Shoot Them UP/Shoots/Ghost.png", true);

WaveManager& ennemies = GetWaveManager();
STUPlayer& playerUwU = GetPlayer();
STUMiniBoss& miniBossShoot = GetSTUMIniBoss();
Boss& finalBoss = GetFinalBoss();
STUGameState& STUGameStateInShoot = GetSTUGameState();

sf::Sound HitSoundShoot = LoadSound("Assets/Shoot Them UP/Player/Hit.ogg");

void Shoot::Collide(void)
{
	if (who == PLAYER)
	{
		for (int k = 0; k < ennemies.GetWaveVector().size(); k++)
		{
			if (ennemies.GetWaveVector()[k].GetTurn() == ennemies.GetCurrentTurn())
			{
				sf::Vector2f shotEnnemi = { ennemies.GetWaveVector()[k].GetPos().x - pos.x, ennemies.GetWaveVector()[k].GetPos().y - pos.y };
				int dist = CreaMaths::GetDistance(shotEnnemi);

				if (dist < 32 * 3 - player.getTexture()->getSize().x && ennemies.GetWaveVector()[k].GetHitClock().getElapsedTime().asSeconds() > 0.1)
				{
					ennemies.GetWaveVector()[k].GetHitClock().restart();
					ennemies.GetWaveVector()[k].SetHp(ennemies.GetWaveVector()[k].GetHp() - damage);

					isAlive = false;
				}
			}
		}

		if (miniBossShoot.Collide(pos,damage)&& STUGameStateInShoot == STU_MINI_BOSS)
		{
			isAlive = false;
		}

		if (STUGameStateInShoot == STU_BOSS && finalBoss.Get_CurrentAttack() != ChangePhase)
		{
			if (finalBoss.Collide(pos, damage))
			{
				isAlive = false;
			}
		}
		

	}
	else
	{
		for (int k = 0; k < ennemies.GetWaveVector().size(); k++)
		{
			for (int l = 0; l < GetEnnemiShootManager().Vector().size(); l++)
			{
				sf::Vector2f shotPlayer = { playerUwU.GetPos().x - pos.x,  playerUwU.GetPos().y - pos.y};
				int dist = CreaMaths::GetDistance(shotPlayer);

				if (dist <= STU_PLAYER_HITBOX && playerUwU.GetInvicibilityClock().getElapsedTime().asSeconds() > STU_PLAYER_INVICIBILITY)
				{
					isAlive = false;

					playerUwU.SetHp(playerUwU.GetHp() - 1);
					playerUwU.RestartClock();

					HitSoundShoot.play();
				}
			}

		}
	}
}

void Shoot::Update(float _dt)
{
	switch (type)
	{
	case LINE_SHOOT:
		if (who == PLAYER)
		{
			Dir.x = 0;
			Dir.y = -1;
		}
		else
		{
			Dir.x = 0;
			Dir.y = 1;
		}

		pos += {Dir.x* speed* _dt, Dir.y* _dt* speed};
		break;
	case WAVE_SHOOT:

		if (who == PLAYER)
		{
			Dir.x += 10 * _dt;
			Dir.y = -1;
		}
		else
		{
			Dir.x += 10 * _dt;
			Dir.y = 1;
		}

		pos += {cosf(Dir.x)* speed* _dt, Dir.y* _dt* speed};
		break;
	case SUN_SHOOT:
		pos.x += Dir.x * speed * _dt;
		pos.y += Dir.y * speed *  _dt;

		break;
	default:
		break;
	}

	if (pos.y < 0)
	{
		isAlive = false;
	}

	Collide();
}

void Shoot::Display(sf::RenderWindow& _window)
{
	switch (who)
	{
	case PLAYER:
		BlitSprite(player, pos, _window,{3,3});
		break;
	case ENNEMIE_GHOST:
		BlitSprite(ghostShot, pos, _window,{2,2});
		break;
	case ENNEMIE_CRISTAL:
		BlitSprite(cristalShot, pos, _window,{1.5,1.5},CreaMaths::RadiansToDegrees(angle));
		break;
	default:
		break;
	}
}