#include "Particules.hpp"
#include "STUEntities.hpp"
#include "CreaMaths.h"
#include "ShootThemUp.hpp"

STUPlayer& playerInParticules = GetPlayer();

sf::Sprite Rune[2] = {
	LoadSprite("Assets/Particules/Rune1.png", true),
	LoadSprite("Assets/Particules/Rune2.png", true)
};
float runeAngle = 0;
float runeTmax = 1.5;
float runeCurrent = runeTmax;

void ParticuleManager::AddParticle(sf::Vector2i _pos, ParticuleType _type, int _numberOfParticules,sf::Color _color,float _rayon)
{
	switch (_type)
	{
	case EXPLOSIONS:
		for (int k = 0; k < _numberOfParticules; k++)
		{
			Particule tempParticule;

			tempParticule.pos.x = _pos.x;
			tempParticule.pos.y = _pos.y;

			tempParticule.amplitude = cosf(((float)(rand() % RAND_MAX) / RAND_MAX) * 100);
			tempParticule.angle = ((float)(rand() % RAND_MAX) / RAND_MAX) * 360;
			tempParticule.fDeltaX = cosf(tempParticule.angle * (PI / 180)) * tempParticule.amplitude;
			tempParticule.fDeltaY = sinf(tempParticule.angle * (PI / 180)) * tempParticule.amplitude;

			tempParticule.speedMax = ((float)(rand() % RAND_MAX) / RAND_MAX) * (400 + rand() % 300);
			tempParticule.speed = tempParticule.speedMax;

			tempParticule.TTLMax = 1 + rand() % 4;
			tempParticule.currentTTL = tempParticule.TTLMax;

			tempParticule.rotation = ((float)(rand() % RAND_MAX) / RAND_MAX) * 360;

			tempParticule.type = _type;
			tempParticule.color = _color;

			particules.push_back(tempParticule);
		}
		break;
	case SMOG:

		for (int k = 0; k < _numberOfParticules; k++)
		{
			Particule tempParticule;

			tempParticule.pos.x = _pos.x + ((rand() % 30) - 15);
			tempParticule.pos.y = _pos.y + ((rand() % 30) - 15);
			tempParticule.fDeltaY = 1;
			tempParticule.fDeltaX = 0;
			tempParticule.angle = atan2f(tempParticule.fDeltaY, tempParticule.fDeltaX);
			tempParticule.speedMax = 300 + ((float)(rand() % RAND_MAX) / RAND_MAX) * 200;
			tempParticule.speed = tempParticule.speedMax;
			tempParticule.TTLMax = ((float)(rand() % RAND_MAX) / RAND_MAX) * 1;
			tempParticule.currentTTL = tempParticule.TTLMax;
			tempParticule.rotation = ((float)(rand() % RAND_MAX) / RAND_MAX) * 360;

			tempParticule.type = _type;
			tempParticule.color = _color;

			particules.push_back(tempParticule);
		}
		break;
	case HEAT:
		for (int k = 0; k < _numberOfParticules; k++)
		{
			Particule tempParticule;

			tempParticule.pos.x = _pos.x;
			tempParticule.pos.y = _pos.y;
			tempParticule.fDeltaY = 1;
			tempParticule.fDeltaX = ((float)(rand() % RAND_MAX) / RAND_MAX) * 1;
			tempParticule.angle = atan2f(tempParticule.fDeltaY, tempParticule.fDeltaX);
			tempParticule.speedMax = 50 + ((float)(rand() % RAND_MAX) / RAND_MAX) * 100;
			tempParticule.speed = tempParticule.speedMax;
			tempParticule.TTLMax = 0.5;
			tempParticule.currentTTL = tempParticule.TTLMax;
			tempParticule.rotation = ((float)(rand() % RAND_MAX) / RAND_MAX) * 360;

			tempParticule.type = _type;
			tempParticule.color = _color;

			particules.push_back(tempParticule);
		}
		break;
	case FINAL_BOSS_HAND:
		for (int k = 0; k < _numberOfParticules; k++)
		{
			Particule tempParticule;

			tempParticule.pos.x = _pos.x;
			tempParticule.pos.y = _pos.y;
			tempParticule.fDeltaY = 1;
			tempParticule.fDeltaX = ((float)(rand() % RAND_MAX) / RAND_MAX) * 1;
			tempParticule.angle = atan2f(tempParticule.fDeltaY, tempParticule.fDeltaX);
			tempParticule.speedMax = 10 + ((float)(rand() % RAND_MAX) / RAND_MAX) * 20;
			tempParticule.speed = tempParticule.speedMax;
			tempParticule.TTLMax = 2;
			tempParticule.currentTTL = tempParticule.TTLMax;
			tempParticule.rotation = 0;

			tempParticule.type = _type;
			tempParticule.color = _color;

			particules.push_back(tempParticule);
		}
		break;
	case BLACK_HOLE:

		for (int k = 0; k < _numberOfParticules; k++)
		{
			Particule tempParticule;

			tempParticule.pos.x = 360 + ((float)(rand() % RAND_MAX) / RAND_MAX) * 1200;
			tempParticule.pos.y = ((float)(rand() % RAND_MAX) / RAND_MAX) * SCREEN_HEIGHT;
			tempParticule.fDeltaY = -1 + ((float)(rand() % RAND_MAX) / RAND_MAX) * 2;
			tempParticule.fDeltaX = -1 + ((float)(rand() % RAND_MAX) / RAND_MAX) * 2;
			tempParticule.speedMax = 2;
			tempParticule.speed = tempParticule.speedMax;
			tempParticule.TTLMax = 3;
			tempParticule.currentTTL = tempParticule.TTLMax;

			tempParticule.type = _type;
			tempParticule.color = _color;

			sf::Vector2f tempDist = CreaMaths::CreateVector(tempParticule.pos, { SCREEN_WIDTH/2,SCREEN_HEIGHT/2 });

			if (CreaMaths::GetDistance(tempDist) < SCREEN_HEIGHT / 2)
			{
				particules.push_back(tempParticule);
			}
		}
		isExplode = false;
		runeAngle = 0;
		runeCurrent = runeTmax;
		if (BlackHoleChargeSound.getStatus() != sf::Sound::Playing)
		{
			BlackHoleChargeSound.play();
		}
		break;

	case BLACK_HOLE_BOSS:

		for (int k = 0; k < _numberOfParticules; k++)
		{
			Particule tempParticule;

			tempParticule.finalPos = (sf::Vector2f)_pos;

			tempParticule.pos.x = _pos.x + (- _rayon + ((float)(rand() % RAND_MAX) / RAND_MAX) * (_rayon * 2));
			tempParticule.pos.y = _pos.y + (- _rayon + ((float)(rand() % RAND_MAX) / RAND_MAX) * (_rayon * 2));
			tempParticule.fDeltaY = -1 + ((float)(rand() % RAND_MAX) / RAND_MAX) * 2;
			tempParticule.fDeltaX = -1 + ((float)(rand() % RAND_MAX) / RAND_MAX) * 2;
			tempParticule.speedMax = 1;
			tempParticule.speed = tempParticule.speedMax;
			tempParticule.TTLMax = 1.5;
			tempParticule.currentTTL = tempParticule.TTLMax;

			tempParticule.type = _type;
			tempParticule.color = _color;

			sf::Vector2f tempDist = CreaMaths::CreateVector(tempParticule.pos, tempParticule.finalPos);

			if (CreaMaths::GetDistance(tempDist) <= _rayon)
			{
				particules.push_back(tempParticule);
			}
		}
		break;
	case EARTH:
		for (int k = 0; k < _numberOfParticules; k++)
		{
			Particule tempParticule;

			tempParticule.pos.x = _pos.x;
			tempParticule.pos.y = _pos.y;

			tempParticule.angle = 0;
			tempParticule.fDeltaX = -1 + (((float)(rand() % RAND_MAX) / RAND_MAX) * 2);
			tempParticule.fDeltaY = -1 * (((float)(rand() % RAND_MAX) / RAND_MAX) * 2);

			tempParticule.speedMax = 300 + ((float)(rand() % RAND_MAX) / RAND_MAX) * 200;
			tempParticule.speed = tempParticule.speedMax;

			tempParticule.TTLMax = 1;
			tempParticule.currentTTL = tempParticule.TTLMax;

			tempParticule.rotation = ((float)(rand() % RAND_MAX) / RAND_MAX) * 360;

			tempParticule.type = _type;
			tempParticule.color = _color;

			particules.push_back(tempParticule);
		}
		break;
	default:
		break;
	}

	

}

void ParticuleManager::AddSpowner(sf::Vector2f _pos)
{
	Spowner tempSpowner;
	tempSpowner.pos = _pos;

	spowners.push_back(tempSpowner);

	SpawnSound.play();
}

void ParticuleManager::BossExplosion(sf::Vector2i _pos, int _numberOfParticules, sf::Color _color)
{
	for (int k = 0; k < _numberOfParticules; k++)
	{
		Particule tempParticule;

		tempParticule.pos.x = _pos.x;
		tempParticule.pos.y = _pos.y;

		tempParticule.amplitude = cosf(((float)(rand() % RAND_MAX) / RAND_MAX) * 100);
		tempParticule.angle = ((float)(rand() % RAND_MAX) / RAND_MAX) * 360;
		tempParticule.fDeltaX = cosf(tempParticule.angle * (PI / 180)) * tempParticule.amplitude;
		tempParticule.fDeltaY = sinf(tempParticule.angle * (PI / 180)) * tempParticule.amplitude;

		tempParticule.speedMax = ((float)(rand() % RAND_MAX) / RAND_MAX) * (500 + rand() % 300);
		tempParticule.speed = tempParticule.speedMax;

		tempParticule.TTLMax = 8 + rand() % 5;
		tempParticule.currentTTL = tempParticule.TTLMax;

		tempParticule.rotation = ((float)(rand() % RAND_MAX) / RAND_MAX) * 360;

		tempParticule.type = EXPLOSIONS;
		tempParticule.color = _color;

		particules.push_back(tempParticule);
	}
}

void ParticuleManager::UpdateParticule(float _dt)
{
	for (int k = 0; k < particules.size(); k++)
	{
		float vectorX = 0;
		float vectorY = 0;
		sf::Vector2f Dir;
		float norme = 0;

		float fGrav = 0;

		particules[k].currentTTL -= _dt;

		switch (particules[k].type)
		{
		case EXPLOSIONS:

			if (particules[k].type == EXPLOSIONS)
			{
				//Diminution de la vitesse
				particules[k].speed = particules[k].speedMax * powf((particules[k].currentTTL / particules[k].TTLMax), 15);

				//Déplacement de la particule
				particules[k].pos.x -= particules[k].fDeltaX * particules[k].speed * _dt;
				particules[k].pos.y -= particules[k].fDeltaY * particules[k].speed * _dt;

				if (particules[k].currentTTL < 0)
				{
					particules[k].isAlive = false;
				}
			}
			break;
		case SMOG:

			if (particules[k].currentTTL < 0)
			{
				particules[k].isAlive = false;
			}

			break;

		case HEAT:
			//Déplacement de la particule
			particules[k].fDeltaX += _dt * 10;
			particules[k].pos.x -= cos(particules[k].fDeltaX) * particules[k].speed * _dt;
			particules[k].pos.y -= particules[k].fDeltaY * particules[k].speed/2 * _dt;

			if (particules[k].currentTTL < 0)
			{
				particules[k].isAlive = false;
			}
			break;
		case FINAL_BOSS_HAND:
			//Déplacement de la particule
			particules[k].fDeltaX += _dt * 15;
			particules[k].pos.x -= cos(particules[k].fDeltaX) * particules[k].speed * _dt;
			particules[k].pos.y -= particules[k].fDeltaY * particules[k].speed / 2 * _dt;

			if (particules[k].currentTTL < 0)
			{
				particules[k].isAlive = false;
			}
			break;

		case BLACK_HOLE:
			//Déplacement de la particule

			//Déterminer le vecteur jusqu'au trou noir
			vectorX = (SCREEN_WIDTH / 2) - particules[k].pos.x;
			vectorY = (SCREEN_HEIGHT / 2) - particules[k].pos.y;
			norme = sqrtf((vectorX * vectorX) + (vectorY * vectorY));

			//Normaliser pour avoir la direction seulement
			vectorX /= norme;
			vectorY /= norme;

			//Calculer la valeur de gravité
			fGrav = 50.0f / sqrtf(norme);

			//Application à la vitesse
			if (particules[k].currentTTL > particules[k].TTLMax / 2)
			{
				particules[k].fDeltaX -= vectorX * (fGrav * 300) * _dt;
				particules[k].fDeltaY -= vectorY * (fGrav * 300) * _dt;

				particules[k].speed = (particules[k].speedMax/2) * ((particules[k].currentTTL - (particules[k].TTLMax / 2)) / (particules[k].TTLMax / 2)) * (norme /100);
				
			}
			else
			{
				if (!isExplode && BlackHoleExplodeSound.getStatus() != sf::Sound::Playing)
				{
					BlackHoleExplodeSound.play();
					ShakeSTU({ 8,8 }, 0.5);
				}

				isExplode = true;
				particules[k].fDeltaX += vectorX * (fGrav*300) * _dt;
				particules[k].fDeltaY += vectorY * (fGrav * 300) * _dt;

				particules[k].speed = particules[k].speedMax/10;
			}


			particules[k].pos.x -= particules[k].fDeltaX * particules[k].speed * _dt;
			particules[k].pos.y -= particules[k].fDeltaY * particules[k].speed * _dt;

			if (particules[k].currentTTL < 0)
			{
				particules[k].isAlive = false;
				isExplode = false;
			}
			break;

		case BLACK_HOLE_BOSS:
			//Déplacement de la particule

			//Déterminer le vecteur jusqu'au trou noir
			Dir = CreaMaths::CreateVector(particules[k].pos, particules[k].finalPos);
			norme = CreaMaths::GetDistance(Dir);

			//Normaliser pour avoir la direction seulement
			vectorX /= norme;
			vectorY /= norme;

			//Calculer la valeur de gravité
			fGrav = 50.0f / sqrtf(norme);

			particules[k].pos += Dir * particules[k].speed * _dt;

			if (particules[k].currentTTL < 0)
			{
				particules[k].isAlive = false;
				isExplode = false;
			}
			break;
		case EARTH:
			particules[k].currentTTL -= _dt;

			//Déplacement de la particule
			particules[k].fDeltaY += _dt * 10;
			particules[k].pos.y += particules[k].fDeltaY * particules[k].speed * _dt;
			particules[k].pos.x += particules[k].fDeltaX * particules[k].speed * _dt;

			if (particules[k].currentTTL < 0)
			{
				particules[k].isAlive = false;
			}
			break;
		default:
			break;
		}
	}

	for (int k = 0; k < particules.size(); k++)
	{
		if (!particules[k].isAlive)
		{
			particules.erase(particules.begin() + k);
		}
	}

	runeAngle += 70 * _dt;

	if (playerInParticules.GetPowerUpOnScreen() && runeCurrent > 0.01)
	{
		runeCurrent -= _dt;
	}


	//SpownerBoss//
	for (int k = 0; k < spowners.size(); k++)
	{
		spowners[k].angle += _dt * 75 * (1 + spowners[k].rotation * -2);
		spowners[k].alpha -= _dt * 200;

		if (spowners[k].alpha < 5)
		{
			spowners.erase(spowners.begin() + k);
		}
	}
}

void ParticuleManager::DrawParticule(sf::RenderWindow& _window)
{
	//SpownerBoss//
	for (int k = 0; k < spowners.size(); k++)
	{
		BlitSprite(SpownerSprite, spowners[k].pos, _window, { 3,3 }, spowners[k].angle, sf::Color(255, 255, 255, spowners[k].alpha));
	}

	for (auto particule = particules.begin(); particule != particules.end(); particule++)
	{
		float diff;
		float angle;
		static float alpha=255;
		sf::Color color;

		switch (particule->type)
		{
		case EXPLOSIONS:
			diff = (particule->currentTTL / particule->TTLMax) + 0.1;
			angle = particule->angle;

			BlitSpriteAdd(etincelleSprite, particule->pos, _window, { particule->speed / 50 ,  particule->speed / 100 }, angle, particule->color);
			break;
		case SMOG:

			particule->color.a = 255 * (particule->currentTTL / particule->TTLMax);

			BlitSprite(etincelleSprite, particule->pos, _window, { 1.5,1.5 }, particule->rotation, particule->color);
			break;
		case HEAT:

			alpha < 0 ? alpha = 0 : alpha = 255 * (particule->currentTTL / particule->TTLMax);
			particule->color.a = alpha;

			BlitSpriteAdd(etincelleSprite, particule->pos, _window, { 1 ,  1 }, 0, particule->color);
			break;
		case FINAL_BOSS_HAND:

			alpha = 255 * (particule->currentTTL / particule->TTLMax);
			alpha < 0 ? particule->color.a = 0 : particule->color.a = alpha;

			BlitSpriteAdd(etincelleSprite, particule->pos, _window, { 1 ,  1 }, 0, particule->color);
			break;
		case BLACK_HOLE:

			alpha < 0 ? alpha = 0 : alpha = 255 * (particule->currentTTL / particule->TTLMax);
			particule->color.a = alpha;
			BlitSpriteAdd(etincelleSprite, particule->pos, _window, { 4 ,  4 }, 0, particule->color);
			break;
		case BLACK_HOLE_BOSS:
			alpha = 255 * (particule->currentTTL / particule->TTLMax);
			alpha < 0 ? particule->color.a = 0 : particule->color.a = alpha;

			BlitSpriteAdd(etincelleSprite, particule->pos, _window, { 1 ,  1 }, 0, particule->color);
			break;
		case EARTH:
			BlitSprite(earthSprite, particule->pos, _window, { 1,1 }, particule->rotation, particule->color);
			break;
		default:
			break;
		}
	}

	if (playerInParticules.GetPowerUpLunched())
	{
		BlitSprite(Rune[0], {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, _window, {3,3}, runeAngle);
	}
	if (playerInParticules.GetPowerUpOnScreen())
	{
		sf::Color runeColor = sf::Color(255, 255, 255);
		runeColor.a < 5 ? runeColor.a = 0 : runeColor.a =  255 * (runeCurrent / runeTmax);

		BlitSprite(Rune[1], { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, _window, { 3,3 }, runeAngle, runeColor);
	}
}

