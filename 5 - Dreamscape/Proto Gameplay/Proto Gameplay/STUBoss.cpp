#include "STUBoss.h"
#include "STUPlayer.hpp"

bool IsCenter = false;
bool CanShoot = false;
bool CanDash = false;

std::vector <Mine> MineVector;
std::vector <Bullet> BulletVector;

float bulletTimer = 0;
float alphaHeal = 0;

ParticuleManager pmBoss;

sf::Image attackMap;

std::vector <Mine>& GetMineVector()
{
	return MineVector;
}

std::vector <Bullet>& GetBulletVector()
{
	return BulletVector;
}

void Mine::UpdateMove(float _dt)
{
	pos.y += 200 * _dt;
}

void Bullet::Move(float _dt, Boss& _theBoss)
{

	bulletTimer += _dt;
	if (dir == GAUCHE)
	{
		if (_theBoss.Get_SecondPhase())
		{
			pos.x = _theBoss.Get_Pos().x + (decalage * 130) + bulletTimer - Easing::easeInQuad(moveTime.getElapsedTime().asSeconds(), 0, SCREEN_WIDTH, 5);
		}
		else
		{
			pos.x = _theBoss.Get_Pos().x + (decalage * 130) + bulletTimer - Easing::easeInQuad(moveTime.getElapsedTime().asSeconds(), 0, SCREEN_WIDTH, 3);
		}
	}
	else if (dir == DROITE)
	{
		if (_theBoss.Get_SecondPhase())
		{
			pos.x = _theBoss.Get_Pos().x + (decalage * 130) + bulletTimer - Easing::easeInQuad(moveTime.getElapsedTime().asSeconds(), 0, -SCREEN_WIDTH, 5);
		}
		else
		{
			pos.x = _theBoss.Get_Pos().x + (decalage * 130) + bulletTimer - Easing::easeInQuad(moveTime.getElapsedTime().asSeconds(), 0, -SCREEN_WIDTH, 3);
		}
	}
	pos.y = _theBoss.Get_Pos().y + Easing::easeOutQuad(moveTime.getElapsedTime().asSeconds(), 0, 1.5 * SCREEN_HEIGHT, 5);
}

/////////////////////////////////////////// Load Part ///////////////////////////////////////////////

void LoadMine(Boss& _theBoss)
{
	Mine mine;
	mine.Set_Pos(_theBoss.Get_Pos());
	mine.Set_Sprite(LoadSprite("Assets/BossFinal/Attack/Mine.png", true));
	MineVector.push_back(mine);
}

void LoadBullet(Boss& _theBoss, int random)
{
	int decalage = -2 + BulletVector.size() % 5;
	Bullet bullet;
	bullet.Set_Direction((BulletDirection)random);
	bullet.Set_Decalage(decalage);
	bullet.Set_Pos({ _theBoss.Get_Pos().x + (bullet.Get_Decalage() * 100) , _theBoss.Get_Pos().y + _theBoss.Get_Sprite().getTexture()->getSize().y / 2 });

	bullet.Set_Sprite(LoadSprite("Assets/BossFinal/Attack/bullet.png", true));
	BulletVector.push_back(bullet);
}

//////////////////////////////////////////// Update Part ////////////////////////////////////////////

void BossCenter(Boss& _theBoss, float _dt)
{
	sf::Vector2f posFinal;
	if (_theBoss.Get_CurrentAttack() == HealSpawn || _theBoss.Get_CurrentAttack() == ShootFan || _theBoss.Get_CurrentAttack() == DashAttack || _theBoss.Get_CurrentAttack() == ChangePhase)
	{
		posFinal = { (float)SCREEN_WIDTH / 2, (float)20 + _theBoss.Get_Sprite().getTexture()->getSize().y * 3 / 2 };
	}
	else
	{
		posFinal = { (float)SCREEN_WIDTH / 2, (float)100 + _theBoss.Get_Sprite().getTexture()->getSize().y * 3 / 2 };
	}

	sf::Vector2f director = posFinal - _theBoss.Get_Pos();

	int norme = sqrtf(director.x * director.x + director.y * director.y);

	if (norme > 5 && !IsCenter)
	{
		_theBoss.Set_X(_theBoss.Get_Pos().x + director.x / norme * (500 * _dt));
		_theBoss.Set_Y(_theBoss.Get_Pos().y + director.y / norme * (500 * _dt));
		CanShoot = false;
	}
	else if (norme <= 5)
	{
		IsCenter = true;
	}

	if (_theBoss.Get_CurrentAttack() == HealSpawn || _theBoss.Get_CurrentAttack() == ShootFan || _theBoss.Get_CurrentAttack() == DashAttack || _theBoss.Get_CurrentAttack() == ChangePhase)
	{
		IsCenter = false;
		if (norme <= 5)
		{
			CanShoot = true;
			CanDash = true;
		}
	}
}

void BossMove(Boss& _theBoss, float _dt)
{
	static float a = 11;
	if (IsCenter && _theBoss.Get_CurrentAttack() != HealSpawn)
	{
		a += 1 * _dt;
		int posFinal = ((cos(a) + 1) * (600 - _theBoss.Get_Sprite().getTexture()->getSize().x * 3 / 2) + (360 + _theBoss.Get_Sprite().getTexture()->getSize().x * 3 / 2));

		_theBoss.Set_X(posFinal);
	}
	else if (!IsCenter)
	{
		a = 11;
	}
}

void DropMine(Boss& _theBoss)
{
	static int numberMine = 0;
	static float delayRequiert = 0;
	static sf::Clock delay;

	_theBoss.Set_IsAttack(true);

	if (numberMine == 0)
	{
		numberMine = 100;
	}

	if (numberMine % 15 == 0)
	{
		delayRequiert = 0.5;
	}
	else
	{
		delayRequiert = 0.1;

	}

	if (numberMine > 0 && delay.getElapsedTime().asSeconds() > delayRequiert)
	{
		LoadMine(_theBoss);
		numberMine--;
		delay.restart();
	}

	if (numberMine <= 0)
	{
		_theBoss.Set_IsAttack(false);
		_theBoss.Set_Cooldown(COOLDOWN);
	}
}

void DropMineFinal(Boss& _theBoss)
{
	static int numberMine = 0;
	static float delayRequiert = 0;
	static sf::Clock delay;
	int numberEnnemis = 3 + rand() % 2;


	if (numberMine == 0)
	{
		numberMine = 100;
	}

	if (numberMine % 15 == 0)
	{
		delayRequiert = 0.5;
	}
	else
	{
		delayRequiert = 0.1;
	}

	if (GetWaveManager().GetWaveVector().size() <= 0 && !_theBoss.Get_IsAttack())
	{
		for (int i = 0; i < numberEnnemis; i++)
		{
			int type = rand() % 3;

			sf::Vector2f tempPos;
			tempPos.x = 360 + ((float)(rand() % RAND_MAX) / RAND_MAX) * 1200;
			tempPos.y = ((float)(rand() % RAND_MAX) / RAND_MAX) * SCREEN_HEIGHT / 2;

			GetWaveManager().AddEnnemie((STUEnnemiType)type, tempPos, 0);
			pmBoss.AddSpowner(tempPos);
		}
		_theBoss.Set_IsAttack(true);
	}


	if (numberMine > 0 && delay.getElapsedTime().asSeconds() > delayRequiert)
	{
		LoadMine(_theBoss);
		numberMine--;
		delay.restart();
	}

	if (numberMine <= 0)
	{
		_theBoss.Set_IsAttack(false);
		_theBoss.Set_Cooldown(3);
	}

}

void UpdateMineDamage(Boss& _theBoss)
{
	static sf::Clock invincibility;

	for (int i = 0; i < MineVector.size(); i++)
	{
		sf::Vector2f distance = MineVector[i].Get_Pos() - GetPlayer().GetPos();
		int norme = sqrtf(distance.x * distance.x + distance.y * distance.y);
		if (norme < MineVector[i].Get_Sprite().getTexture()->getSize().x * 3 / 2)
		{
			if (invincibility.getElapsedTime().asSeconds() > 0.5 && !_theBoss.Get_IsInvinciblePlayer())
			{
				GetTotalPlayerHp() -= 20;
				invincibility.restart();
				PlayMineSound();
			}
			MineVector.erase(MineVector.begin() + i);
		}
	}

}

void UpdateMine(float _dt, Boss& _theBoss)
{
	for (int i = 0; i < MineVector.size(); i++)
	{
		MineVector[i].UpdateMove(_dt);
	}
	UpdateMineDamage(_theBoss);
}

void ClearMine()
{
	for (int i = 0; i < MineVector.size(); i++)
	{
		if (MineVector[i].Get_Pos().y > SCREEN_HEIGHT + MineVector[i].Get_Sprite().getTexture()->getSize().y * 3 / 2)
		{
			MineVector.erase(MineVector.begin() + i);
		}
	}
}

void HealSpawnAttack(Boss& _theBoss, float _dt)
{
	int numberEnnemis = 3 + rand() % 2;

	if (GetWaveManager().GetWaveVector().size() <= 0 && !_theBoss.Get_IsAttack())
	{
		for (int i = 0; i < numberEnnemis; i++)
		{
			int type = rand() % 3;

			sf::Vector2f tempPos;
			tempPos.x = 360 + ((float)(rand() % RAND_MAX) / RAND_MAX) * 1200;
			tempPos.y = ((float)(rand() % RAND_MAX) / RAND_MAX) * SCREEN_HEIGHT / 2;

			GetWaveManager().AddEnnemie((STUEnnemiType)type, tempPos, 0);
			pmBoss.AddSpowner(tempPos);
		}
		_theBoss.Set_IsAttack(true);
	}

	if (GetWaveManager().GetWaveVector().size() > 0)
	{
		PlayRegenSound();
		if (_theBoss.Get_Hp() < _theBoss.Get_MaxHp())
		{
			_theBoss.Set_Hp(_theBoss.Get_Hp() + 10 * _dt);
		}

		static float a = 0;

		a += 2 * _dt;
		alphaHeal = 126 * (cos(a) + 1);
	}
	else
	{
		StopRegenSound();
		alphaHeal = 0;
	}

	if (GetWaveManager().GetWaveVector().size() <= 0)
	{
		alphaHeal = 0;
		_theBoss.Set_IsAttack(false);
		_theBoss.Set_Cooldown(COOLDOWN);
	}
}

void HealBoss(Boss& _theBoss, float _dt)
{
	if (_theBoss.Get_Hp() < _theBoss.Get_MaxHp() && _theBoss.Get_Hp() > 0)
	{
		_theBoss.Set_Hp(_theBoss.Get_Hp() + 250 * _dt);
	}
}

void ShootFanAttack(Boss& _theBoss, float _dt, int _random)
{
	static int numberBullet = 60;
	static sf::Clock delay;
	_theBoss.Set_IsAttack(true);

	sf::Vector2f posFinal = { (float)SCREEN_WIDTH / 2, (float)20 + _theBoss.Get_Sprite().getTexture()->getSize().y / 2 };
	sf::Vector2f director = posFinal - _theBoss.Get_Pos();
	int norme = sqrtf(director.x * director.x + director.y * director.y);

	if (CanShoot)
	{
		if (numberBullet > 0 && delay.getElapsedTime().asSeconds() > 0.2)
		{
			for (int i = 0; i < 5; i++)
			{
				LoadBullet(_theBoss, _random);
				numberBullet--;
				delay.restart();
			}
		}

		if (numberBullet <= 0 && BulletVector.size() <= 0)
		{
			bulletTimer = 0;
			_theBoss.Set_IsAttack(false);
			_theBoss.Set_Cooldown(COOLDOWN);
			numberBullet = 60;
		}
	}

}

void BulletDamage(Boss& _theBoss)
{
	static sf::Clock Invincibility;
	for (int i = 0; i < BulletVector.size(); i++)
	{
		sf::Vector2f distance = CreaMaths::CreateVector(GetPlayer().GetPos(), { BulletVector[i].Get_Pos().x + BulletVector[i].Get_Sprite().getTexture()->getSize().x * 3 / 2 , BulletVector[i].Get_Pos().y + BulletVector[i].Get_Sprite().getTexture()->getSize().y / 2 });

		int norme = CreaMaths::GetVectorLength(distance);

		if (norme <= STU_PLAYER_HITBOX + 8)
		{
			if (Invincibility.getElapsedTime().asSeconds() > 0.5 && !_theBoss.Get_IsInvinciblePlayer() && !_theBoss.Get_IsInvinciblePlayer())
			{
				GetTotalPlayerHp() -= 20;
				Invincibility.restart();
			}
			BulletVector.erase(BulletVector.begin() + i);
		}
	}
}

void UpdateBullet(float _dt, Boss& _theBoss)
{
	for (int i = 0; i < BulletVector.size(); i++)
	{
		BulletVector[i].Move(_dt, _theBoss);
	}

	for (int i = 0; i < BulletVector.size(); i++)
	{
		if (BulletVector[i].Get_Pos().x < 340)
		{
			BulletVector.erase(BulletVector.begin() + i);
		}
		else if (BulletVector[i].Get_Pos().x > SCREEN_WIDTH - 340)
		{
			BulletVector.erase(BulletVector.begin() + i);
		}
	}
	BulletDamage(_theBoss);
}

void Dash(float _dt, Boss& _theBoss)
{
	static float timer = 0;
	static float posY = (float)20 + _theBoss.Get_Sprite().getTexture()->getSize().y * 3 / 2;

	if (CanDash)
	{
		_theBoss.Set_IsAttack(true);
		timer += _dt;
		if (timer < 1)
		{
			_theBoss.Set_Y(posY + Easing::easeInExpo(timer, 0, SCREEN_HEIGHT - _theBoss.Get_Sprite().getTexture()->getSize().y * 3 / 2, 1));
		}
		else
		{
			ShakeSTU({ 10 , 10 }, _dt);
			timer = 0;
			CanDash = false;
			_theBoss.Set_IsAttack(false);
			_theBoss.Set_Cooldown(COOLDOWN);
		}
	}


}

void IntelligenceAttack(Boss& _theBoss)
{
	static int random = 0;
	random = rand() % 4;

	if (_theBoss.Get_CurrentAttack() == (BossAttack)random)
	{
		IntelligenceAttack(_theBoss);
	}
	else
	{

		if (attackMap.getPixel(GetPlayer().GetPos().x, GetPlayer().GetPos().y) == sf::Color(255, 0, 0))
		{
			switch (random)
			{
			case 0:_theBoss.Set_CurrentAttack(DashAttack);
				break;
			case 1:_theBoss.Set_CurrentAttack(DashAttack);
				break;
			case 2:_theBoss.Set_CurrentAttack(HealSpawn);
				break;
			case 3:_theBoss.Set_CurrentAttack(MineDrop);
				break;
			}
		}
		else if (attackMap.getPixel(GetPlayer().GetPos().x, GetPlayer().GetPos().y) == sf::Color(0, 255, 0))
		{
			switch (random)
			{
			case 0:_theBoss.Set_CurrentAttack(DashAttack);
				break;
			case 1:_theBoss.Set_CurrentAttack(DashAttack);
				break;
			case 2:_theBoss.Set_CurrentAttack(MineDrop);
				break;
			case 3:_theBoss.Set_CurrentAttack(MineDrop);
				break;
			}
		}
		else if (attackMap.getPixel(GetPlayer().GetPos().x, GetPlayer().GetPos().y) == sf::Color(0, 0, 255))
		{
			switch (random)
			{
			case 0:_theBoss.Set_CurrentAttack(ShootFan);
				break;
			case 1:_theBoss.Set_CurrentAttack(ShootFan);
				break;
			case 2:_theBoss.Set_CurrentAttack(HealSpawn);
				break;
			case 3:_theBoss.Set_CurrentAttack(MineDrop);
				break;
			}
		}
		else
		{
			_theBoss.Set_CurrentAttack((BossAttack)random);
		}
	}
}

void UpdateBossAttack(float _dt, Boss& _theBoss)
{
	if (!_theBoss.Get_IsAnimation())
	{
		static int bulletDir = 0;
		if (_theBoss.Get_NewPhaseTime().getElapsedTime().asSeconds() > 2)
		{
			_theBoss.Set_Cooldown(_theBoss.Get_Cooldown() - _dt);

			if (_theBoss.Get_Cooldown() <= 0 && !_theBoss.Get_IsAttack() && !_theBoss.Get_CurrentAttack() != ChangePhase && _theBoss.Get_Hp() > 0)
			{
				if (GetPlayer().GetPos().x < SCREEN_WIDTH / 2)
				{
					bulletDir = 1;
				}
				else
				{
					bulletDir = 0;
				}
				IntelligenceAttack(_theBoss);
			}

			if (_theBoss.Get_Cooldown() <= 0 || _theBoss.Get_IsAttack())
			{
				if (_theBoss.Get_CurrentAttack() == MineDrop)
				{
					if (_theBoss.Get_Hp() < _theBoss.Get_MaxHp() / 2 && _theBoss.Get_SecondPhase())
					{
						DropMineFinal(_theBoss);
					}
					else
					{
						DropMine(_theBoss);
					}
				}
				else if (_theBoss.Get_CurrentAttack() == HealSpawn)
				{
					if (_theBoss.Get_Hp() < _theBoss.Get_MaxHp() / 2 && _theBoss.Get_SecondPhase())
					{
						HealSpawnAttack(_theBoss, _dt);
						ShootFanAttack(_theBoss, _dt, bulletDir);
					}
					else
					{
						HealSpawnAttack(_theBoss, _dt);
					}
				}
				else if (_theBoss.Get_CurrentAttack() == ShootFan)
				{
					ShootFanAttack(_theBoss, _dt, bulletDir);
				}
				else if (_theBoss.Get_CurrentAttack() == DashAttack)
				{
					Dash(_dt, _theBoss);
				}
				else if (_theBoss.Get_CurrentAttack() == ChangePhase)
				{
					MineVector.clear();
					BulletVector.clear();
				}
			}

			if (!_theBoss.Get_IsAttack())
			{
				alphaHeal = 0;
			}
		}
	}
}

///////////////////////////////////////////// Draw Part /////////////////////////////////////////////

void DisplayMine(sf::RenderWindow& _window)
{
	for (int i = 0; i < MineVector.size(); i++)
	{
		BlitSprite(MineVector[i].Get_Sprite(), MineVector[i].Get_Pos(), _window, { 3 , 3 });
	}
}

void DisplayBullet(sf::RenderWindow& _window)
{
	for (int i = 0; i < BulletVector.size(); i++)
	{
		BlitSprite(BulletVector[i].Get_Sprite(), BulletVector[i].Get_Pos(), _window, { 3 , 3 });
	}
}

void DisplayHeal(sf::RenderWindow& _window, Boss& _theBoss)
{
	BlitSprite(_theBoss.Get_HealBarre(), _theBoss.Get_BarrePos(), _window, { _theBoss.Get_Scale() , _theBoss.Get_Scale() }, 0, sf::Color(255, 255, 255, alphaHeal));
}

////////////////////////////////////////// FONCTION SACREE //////////////////////////////////////////

void LoadSTUBoss()
{
	attackMap.loadFromFile("Assets/BossFinal/Attack/pixel map.png");
	for (int i = 0; i < 3; i++)
	{
		Turret turret;

		turret.SetType(SIMPLE_LINE);
		turret.SetCoolDown(0.2);

		GetPlayer().turretVector.push_back(turret);

		for (int k = 0; k < GetPlayer().turretVector.size(); k++)
		{
			float angle = k * (360 / GetPlayer().turretVector.size());
			angle *= 3.14 / 180;

			GetPlayer().turretVector[k].SetSpeedAngle(0.00f);

			GetPlayer().turretVector[k].SetVectorFromPlayer({ (float)(GetPlayer().turretDist * cos(angle)), (float)(GetPlayer().turretDist * sin(angle)) });

			GetPlayer().turretVector[k].SetPos(GetPlayer().turretVector[k].GetPos() + GetPlayer().turretVector[k].GetVectorFromPlayer());

		}
	}
}

void UpdateSTUBoss(float _dt, GameState& _gameState, Player& _player, Boss& _theBoss, bool& _transition, float _noirAlpha, ControlsData*& m_controls)
{
	UpdateSTU(_dt, _gameState, _player, _transition, _noirAlpha, m_controls);
	BossCenter(_theBoss, _dt);
	BossMove(_theBoss, _dt);
	UpdateBossAttack(_dt, _theBoss);
	UpdateMine(_dt, _theBoss);
	UpdateBullet(_dt, _theBoss);
	ClearMine();
	pmBoss.UpdateParticule(_dt);
}

void DisplaySTUBoss(sf::RenderWindow& _window, Boss& _theBoss)
{
	DisplayBg(_window);
	DisplayMine(_window);
	_theBoss.DisplayHealInfo(_window);
	pmBoss.DrawParticule(_window);
	GetSTUGameData().Em.DrawEntities(_window);
	DisplayBullet(_window);
	_window.setView(GetHudView());
	GetSTUGameData().Hud.Display(_window);
	playerView.reset({ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT });
	_window.setView(playerView);
}