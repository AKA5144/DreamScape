#include "STUEnnemie.hpp"
#include "CreaMaths.h"
#include "STUEntities.hpp"


ParticuleManager& Fx = GetParticuleManager();
STUPlayer& player= GetPlayer();
STUItems& itemsInEnnemi = GetItems();
STUScore& scoreInEnnemi = GetScoreManager();

ShootManager SmEnnemi;

#define GAMEZONE 1200
#define HUD_SIZE 360
#define HIGH_LIMIT 200
#define MAX_TYPE_ENNEMI 3
#define MAX_WILLO_ANIM 4
#define MAX_GHOST_ANIM 3
#define MAX_CRISTAL_ANIM 8

#define SPEED_POWER_UP 2


sf::Sprite willoAnim[MAX_WILLO_ANIM]
{
	LoadSprite("Assets/Shoot Them Up/Ennemi/Willo/1.png",true),
	LoadSprite("Assets/Shoot Them Up/Ennemi/Willo/2.png",true),
	LoadSprite("Assets/Shoot Them Up/Ennemi/Willo/3.png",true),
	LoadSprite("Assets/Shoot Them Up/Ennemi/Willo/4.png",true)
};

sf::Sprite ghostAnim[MAX_GHOST_ANIM]
{
	LoadSprite("Assets/Shoot Them Up/Ennemi/Ghost/Ghost1.png", true),
	LoadSprite("Assets/Shoot Them Up/Ennemi/Ghost/Ghost2.png", true),
	LoadSprite("Assets/Shoot Them Up/Ennemi/Ghost/Ghost3.png", true)
};

sf::Sprite cristalAnim[MAX_CRISTAL_ANIM]
{
	LoadSprite("Assets/Shoot Them Up/Ennemi/Cristal/1.png",true),
	LoadSprite("Assets/Shoot Them Up/Ennemi/Cristal/2.png",true),
	LoadSprite("Assets/Shoot Them Up/Ennemi/Cristal/3.png",true),
	LoadSprite("Assets/Shoot Them Up/Ennemi/Cristal/4.png",true),
	LoadSprite("Assets/Shoot Them Up/Ennemi/Cristal/5.png",true),
	LoadSprite("Assets/Shoot Them Up/Ennemi/Cristal/6.png",true),
	LoadSprite("Assets/Shoot Them Up/Ennemi/Cristal/7.png",true),
	LoadSprite("Assets/Shoot Them Up/Ennemi/Cristal/8.png",true)

};

sf::Sprite* ennemiSprite[MAX_TYPE_ENNEMI] =
{
	willoAnim,
	ghostAnim,
	cristalAnim
};

sf::Sound HitSoundMelee = LoadSound("Assets/Shoot Them UP/Player/Hit.ogg");

void Ennemie::Init(STUEnnemiType _type, sf::Vector2f _pos, int _turn)
{
	pos = _pos;
	type = _type;
	turn = _turn;

	state = MOVE;

	varCos.x = ((float)(rand() % RAND_MAX) / RAND_MAX) * 500;
	varCos.y = 1;

	attackCoolDown = 1 + ((float)(rand() % RAND_MAX) / RAND_MAX) * 2;

	switch (type)
	{
	case FIRE:
		HP = 4;
		break;
	case GHOST:
		HP = 5;
		break;
	case CRISTAL:
		HP = 6;
		break;
	default:
		break;
	}
}

void Ennemie::FireMove(float _dt, STUPlayer _player)
{
	sf::Vector2i tempParticulePos = { (int)pos.x,(int)pos.y };

	switch (state)
	{
	case WAIT:
		angle = atan2(_player.GetPos().x - pos.x, _player.GetPos().y - pos.y);

		dir = _player.GetPos() - pos;
		CreaMaths::ClampLength(dir, 1);//normalisation

		if (wait.getElapsedTime().asSeconds() > 1)
		{
			state = ATTACK;
		}
		break;
	case MOVE:

		if (pos.y < HIGH_LIMIT || pos.x > SCREEN_WIDTH / 2 + GAMEZONE / 2 || pos.x < SCREEN_WIDTH / 2 - GAMEZONE / 2)
		{
			angle = atan2((float)(SCREEN_WIDTH / 2) - pos.x, (float)(SCREEN_HEIGHT / 2) - pos.y);

			dir = { (float)(SCREEN_WIDTH / 2) - pos.x,(float)(SCREEN_HEIGHT / 2) - pos.y };
			CreaMaths::ClampLength(dir, 1);//normalisation

			pos.x += dir.x * speed * _dt;
			pos.y += dir.y * speed * _dt;
		}
		else
		{
			wait.restart();
			state = WAIT;
		}

		//particules effet feu
		Fx.AddParticle(tempParticulePos, SMOG, 1);

		break;
	case ATTACK:

		pos.x += dir.x * (speed * 8) * _dt;
		pos.y += dir.y * (speed * 8) * _dt;

		if (pos.y > SCREEN_HEIGHT + 100 || pos.x > SCREEN_WIDTH || pos.x < 0 || pos.y < -100)
		{
			pos.x = (float)(rand() % SCREEN_WIDTH);
			pos.y = -500;
			state = MOVE;
		}

		//particules effet feu
		Fx.AddParticle(tempParticulePos, SMOG, 1);
		break;
	case POWER_UP:

		angle = atan2((float)(SCREEN_WIDTH / 2) - pos.x, (float)(SCREEN_HEIGHT / 2) - pos.y);

		dir = { (float)(SCREEN_WIDTH / 2) - pos.x,(float)(SCREEN_HEIGHT / 2) - pos.y };
		//CreaMaths::ClampLength(dir, 1);//normalisation

		pos.x += SPEED_POWER_UP * dir.x * _dt;
		pos.y += SPEED_POWER_UP * dir.y * _dt;

		break;
	default:
		break;
	}

	int size = willoAnim[0].getTexture()->getSize().x * 3;
	sf::Vector2f ennemiPlayer = CreaMaths::CreateVector(pos, player.GetPos());

	if (CreaMaths::GetDistance(ennemiPlayer) < 16 + size && player.GetInvicibilityClock().getElapsedTime().asSeconds() > STU_PLAYER_INVICIBILITY)
	{
		player.SetHp(player.GetHp() - 1);
		player.RestartClock();
		HitSoundMelee.play();
	}
}

void Ennemie::GhostMove(float _dt)
{
	static bool goDown = true;
	sf::Vector2i tempParticulePos = { (int)pos.x,(int)pos.y };

	switch (state)
	{
	case WAIT:
		break;
	case MOVE:

		varCos.x += _dt * 1;
		pos.x += cos(varCos.x) * speed * _dt;

		pos.y += speed * _dt;

		if (pos.y > SCREEN_HEIGHT / 3)
		{
			state = ATTACK;
		}

		break;
	case ATTACK:
		varCos.x += _dt * 1;
		varCos.y += _dt * 2;

		pos.x += cos(varCos.x) * speed * _dt;
		goDown ? pos.y += cos(varCos.y) * (speed * 2) * _dt : pos.y -= cos(varCos.y) * speed * _dt;

		if (goDown && pos.y > 2 * SCREEN_HEIGHT / 3)
		{
			goDown = false;
		}
		else if (!goDown && pos.y < 0)
		{
			goDown = true;
		}

		if (wait.getElapsedTime().asSeconds() > attackCoolDown)
		{
			SmEnnemi.AddShoot(pos, 400, 1, ENNEMIE_GHOST, WAVE_SHOOT);
			attackCoolDown = 1 + ((float)(rand() % RAND_MAX) / RAND_MAX) * 2;
			wait.restart();
		}

		break;
	case POWER_UP:

		angle = atan2((float)(SCREEN_WIDTH / 2) - pos.x, (float)(SCREEN_HEIGHT / 2) - pos.y);

		dir = { (float)(SCREEN_WIDTH / 2) - pos.x,(float)(SCREEN_HEIGHT / 2) - pos.y };
		//CreaMaths::ClampLength(dir, 1);//normalisation

		pos.x += SPEED_POWER_UP * dir.x * _dt;
		pos.y += SPEED_POWER_UP * dir.y * _dt;

		break;
	default:
		break;
	}

	int sizex = ghostAnim[0].getTexture()->getSize().x * 3;
	int sizeY = ghostAnim[0].getTexture()->getSize().y * 3;


	//particules effet esprit
	Fx.AddParticle({ tempParticulePos.x - sizex/4, tempParticulePos.y + sizeY/4 }, HEAT, 1,sf::Color::White);
	Fx.AddParticle({ tempParticulePos.x - sizex / 8, tempParticulePos.y + sizeY/4}, HEAT, 1, sf::Color::White);
	Fx.AddParticle({ tempParticulePos.x, tempParticulePos .y + sizeY/4}, HEAT, 1, sf::Color::White);
	Fx.AddParticle({ tempParticulePos.x + sizex/4, tempParticulePos.y + sizeY/4 }, HEAT, 1, sf::Color::White);
	Fx.AddParticle({ tempParticulePos.x + sizex / 8, tempParticulePos.y + sizeY/4 }, HEAT, 1, sf::Color::White);
}

void Ennemie::CristalMove(float _dt)
{
	sf::Vector2f vectorToTarget;
	sf::Vector2f upVector = {0,-1};

	switch (state)
	{
	case WAIT:
		vectorToTarget = { target.x - pos.x,target.y - pos.y };

		pos.x += dir.x * (speed*4)*_dt;
		pos.y += dir.y * (speed*4)*_dt;

		if (CreaMaths::GetDistance(vectorToTarget) < 100)
		{
			wait.restart();
			state = ATTACK;
		}

		break;
	case MOVE:

		target.x = 360 + rand() % 1200;
		target.y = rand() %(SCREEN_HEIGHT/2);

		dir = { target.x - pos.x,target.y - pos.y };
		CreaMaths::ClampLength(dir, 1);//normalisation

		state = WAIT;
		break;
	case ATTACK:
		angle += 10 * _dt;
		upVector = CreaMaths::RotateVector(upVector, angle);

		if (attackClock.getElapsedTime().asSeconds() > 0.1)
		{
			SmEnnemi.AddShoot(pos, upVector,angle, 400, 1, ENNEMIE_CRISTAL, SUN_SHOOT);
			attackClock.restart();
		}

		if (wait.getElapsedTime().asSeconds() > 2)
		{
			state = MOVE;
		}
		break;
	case POWER_UP:

		angle = atan2((float)(SCREEN_WIDTH / 2) - pos.x, (float)(SCREEN_HEIGHT / 2) - pos.y);

		dir = { (float)(SCREEN_WIDTH / 2) - pos.x,(float)(SCREEN_HEIGHT / 2) - pos.y };
		//CreaMaths::ClampLength(dir, 1);//normalisation

		pos.x += SPEED_POWER_UP * dir.x * _dt;
		pos.y += SPEED_POWER_UP * dir.y * _dt;

		break;
	default:
		break;
	}
}

void Ennemie::ScreenCollide(void)
{
	if (pos.x > HUD_SIZE && pos.x < HUD_SIZE + TAILLE_BG && pos.y > 0 && pos.y < SCREEN_HEIGHT)
	{
		onScreen = true;
	}
	else
	{
		onScreen = false;
	}

}

void Ennemie::Anim(float _dt)
{
	switch (type)
	{
	case FIRE:
		currentSprite < MAX_WILLO_ANIM - 1 ? currentSprite += _dt * 8 : currentSprite -= MAX_WILLO_ANIM - 1;
		break;
	case GHOST:
		currentSprite < MAX_GHOST_ANIM - 1 ? currentSprite += _dt * 6 : currentSprite -= MAX_GHOST_ANIM - 1;
		break;
	case CRISTAL:
		currentSprite < MAX_CRISTAL_ANIM - 1 ? currentSprite += _dt * 8 : currentSprite -= MAX_CRISTAL_ANIM - 1;
		break;
	}
}

void Ennemie::Update(float _dt, STUPlayer _player)
{
	float spawnRandom;
	ScreenCollide();

	static sf::Clock luckControl;
	static bool forceItem = false;

	if (luckControl.getElapsedTime().asSeconds() > 10)
	{
		forceItem = true;
	}

	switch (type)
	{
	case FIRE:
		FireMove(_dt, _player);
		//delete ennemies
		if (HP <= 0)
		{
			isAlive = false;
			sf::Vector2i temp = { (int)pos.x, (int)pos.y };
			Fx.AddParticle(temp, EXPLOSIONS, 100);
			scoreInEnnemi.AddScore(10) ;

			if(!player.GetPowerUpOnScreen() && !player.GetPowerUpLunched())
			player.SetPowerUp(player.GetPowerUp() + 10);

			spawnRandom = rand() % 10;
			if (spawnRandom == 0 || forceItem)
			{
				itemsInEnnemi.SpawnRandomItem(pos);
				forceItem = false;
				luckControl.restart();
			}
		}
		break;
	case GHOST:
		GhostMove(_dt);
		//delete ennemies
		if (HP <= 0)
		{
			isAlive = false;
			sf::Vector2i temp = { (int)pos.x, (int)pos.y };
			Fx.AddParticle(temp, EXPLOSIONS, 100,sf::Color::White);
			scoreInEnnemi.AddScore(20);

			if (!player.GetPowerUpOnScreen() && !player.GetPowerUpLunched())
				player.SetPowerUp(player.GetPowerUp() + 10);

			spawnRandom = rand() % 10;
			if (spawnRandom == 0 || forceItem)
			{
				itemsInEnnemi.SpawnRandomItem(pos);
				forceItem = false;
				luckControl.restart();
			}
		}
		break;
	case CRISTAL:
		CristalMove(_dt);
		//delete ennemies
		if (HP <= 0)
		{
			isAlive = false;
			sf::Vector2i temp = { (int)pos.x, (int)pos.y };
			Fx.AddParticle(temp, EXPLOSIONS, 100,sf::Color::Red);
			scoreInEnnemi.AddScore(30);

			if (!player.GetPowerUpOnScreen() && !player.GetPowerUpLunched())
				player.SetPowerUp(player.GetPowerUp() + 10);

			spawnRandom = rand() % 10;
			if (spawnRandom == 0 || forceItem)
			{
				itemsInEnnemi.SpawnRandomItem(pos);
				forceItem = false;
				luckControl.restart();
			}
		}
		break;
	}

	Anim(_dt);

	//hit
	hitClock.getElapsedTime().asSeconds() > 0.1 ? hit = false : hit = true;

	if (player.GetPowerUpOnScreen() && onScreen)
	{
		HP = 0;
	}

	if (player.GetPowerUpLunched() && onScreen)
	{
		state = POWER_UP;
	}
}

void Ennemie::Display(sf::RenderWindow& _window)
{
	sf::Color color;
	static sf::Vector2f scale = { 3,3 };
	static float ghostScaleX;

	switch (type)
	{
	case FIRE:

		hit ? color = sf::Color(255, 100, 100, 255) : color = sf::Color::White;

		BlitSprite(ennemiSprite[FIRE][(int)currentSprite], pos, _window, scale, -angle * 180 / PI, color);
		break;
	case GHOST:
		hit ? color = sf::Color(255, 100, 100, 255) : color = sf::Color::White;

		cos(varCos.x) < 0 ? ghostScaleX = 3 : ghostScaleX = -3;

		BlitSprite(ennemiSprite[GHOST][(int)currentSprite], pos, _window, { ghostScaleX, scale.y }, 0, color);
		break;
	case CRISTAL:
		hit ? color = sf::Color(255, 100, 100, 255) : color = sf::Color::White;

		BlitSprite(ennemiSprite[CRISTAL][(int)currentSprite], pos, _window, scale, 0, color);
		break;
	}
}

ShootManager& GetEnnemiShootManager(void)
{
	return SmEnnemi;
}