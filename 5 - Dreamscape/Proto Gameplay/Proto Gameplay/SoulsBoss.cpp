#include "SoulsBoss.h"

bool IsCenterSouls = false;
bool isCenterOnPlayer = false;
bool isCircleCenter = false;
Circle MainCircle;
static float compteur = 0;

struct ThornsStruct
{
	sf::Sprite sprite;
	sf::Vector2f pos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	float affichage = 0;
	float rotation = 0;
};

ThornsStruct thorns;
ThornsStruct rootFirst;

std::vector <HandFall> HandVector;

Root root;

ShieldCircle shield;
BlackHole blackHole;
Laser laser;
ParticuleManager pm;

////////////////////////////////////////// Load Part ///////////////////////////////////////////////

void HandFall::UpdateAnimation()
{
	sf::Vector2f director = shadowPos - handPos;
	norme = sqrtf(director.x * director.x + director.y * director.y);
	float distancePercent = norme / normeMax;

	alpha = 255 - (255 * distancePercent);
}

void HandFall::Load(sf::Vector2f _pos)
{
	hand = LoadSprite("Assets/BossFinal/Attack/Hand/5.png", true);
	shadow = LoadSprite("Assets/BossFinal/Attack/Hand/4.png", true);
	rotation = rand() % 360;
	shadowPos = _pos;
	handPos = { shadowPos.x , shadowPos.y - 500 + rand() % 250 };
	sf::Vector2f director = shadowPos - handPos;
	normeMax = sqrtf(director.x * director.x + director.y * director.y);
}

void HandFall::PlayerDamage(SoulsLevel*& _soulsLevel, Boss& _theBoss)
{
	sf::Vector2f distance = shadowPos - _soulsLevel->Get_Player().GetPosition();
	float norme = sqrtf(distance.x * distance.x + distance.y * distance.y);

	if (norme < shadow.getTexture()->getSize().x / 2 + _soulsLevel->Get_Player().GetSprite().getTexture()->getSize().x / 2)
	{
		if (GetTotalPlayerHp() > 0 && !_theBoss.Get_IsInvinciblePlayer())
		{
			GetTotalPlayerHp() -= 20;
		}
	}
}

void HandFall::UpdateFalling(float _dt, SoulsLevel*& _soulsLevel, Boss& _theBoss)
{
	sf::Vector2f director = shadowPos - handPos;
	if (norme != 0)
	{
		director.x /= norme;
		director.y /= norme;
	}

	if (!isFall)
	{
		if (norme > 8)
		{
			handPos.x += director.x * _dt * 500;
			handPos.y += director.y * _dt * 500;
		}
		else
		{
			handPos = shadowPos;
			timer += _dt;
			if (timer > 2)
			{
				isFall = true;
			}
		}
	}

	if (norme == 0)
	{
		director = { 0 , 1 };
		if (!isDamageDone)
		{
			PlayerDamage(_soulsLevel, _theBoss);
			PlayHandSound();
			isDamageDone = true;
		}
	}

	if (isFall)
	{
		normeMax = 800;
		handPos.x -= director.x * _dt * 500;
		handPos.y -= director.y * _dt * 500;
		if (norme > normeMax)
		{
			canErase = true;
		}
	}
}

void HandFall::Update(float _dt, SoulsLevel*& _soulsLevel, Boss& _theBoss)
{
	UpdateAnimation();
	UpdateFalling(_dt, _soulsLevel, _theBoss);
}

void LoadHand(SoulsLevel*& _soulsLevel)
{
	HandFall hand;
	sf::Vector2f playerPos = _soulsLevel->Get_Player().GetPosition();
	sf::Vector2f randomPos = { (playerPos.x - 50) + rand() % 100 , (playerPos.y - 50) + rand() % 100 };
	hand.Load(randomPos);
	HandVector.push_back(hand);
}

//////////////////////////////////////////// Update Part ////////////////////////////////////////////

void BossCenterSouls(float _dt, SoulsLevel*& _soulsLevel, Boss& _theBoss)
{
	static sf::Vector2f pos[3] =
	{
		{350, 100},
		{150 , 300},
		{550 , 300}
	};
	static int random = rand() % 3;
	static bool canChangePos = true;

	if (_theBoss.Get_NeedMove() && _theBoss.Get_Hp() > 0)
	{
		if (canChangePos)
		{
			while (random == _theBoss.Get_CurrentPos())
			{
				random = rand() % 3;
			}
			canChangePos = false;
		}
		sf::Vector2f nextPos = pos[random];
		_theBoss.Set_CurrentPos(random);
		sf::Vector2f director = nextPos - _theBoss.Get_Pos();
		float norme = director.x * director.x + director.y * director.y;

		if (norme >= 5)
		{
			_theBoss.Set_Pos({ _theBoss.Get_Pos().x + director.x * _dt , _theBoss.Get_Pos().y + director.y * _dt });
		}
		else
		{
			canChangePos = true;
			_theBoss.Set_Pos({ nextPos });
			_theBoss.Set_NeedMove(false);
		}
	}
}

void ResetWorld(Boss& _theBoss)
{
	blackHole.Set_CanDisplayHole(false);
	blackHole.Set_CanDisplaySign(false);
	shield.Set_CanDisplay(false);
	laser.Set_CanDisplay(false);
	root.Set_CanDisplay(false);
}

void UpdateThornsDamage(SoulsLevel*& _soulsLevel, bool& _damageDone, Boss& _theBoss)
{
	sf::Vector2f playerCoord = _soulsLevel->Get_Player().GetPosition();
	sf::Vector2f thornsTexture = (sf::Vector2f)thorns.sprite.getTexture()->getSize();
	if (playerCoord.y < 350)
	{
		if (playerCoord.x > thorns.pos.x - thornsTexture.y && playerCoord.x < thorns.pos.x + thornsTexture.y && playerCoord.y > thorns.pos.y - thorns.sprite.getTextureRect().width && playerCoord.y < thorns.pos.y + thorns.sprite.getTextureRect().width)
		{
			if (!_damageDone)
			{
				if (GetTotalPlayerHp() > 0 && !_theBoss.Get_IsInvinciblePlayer())
				{ 
					GetTotalPlayerHp() -= 20;
				}
				_damageDone = true;
			}
		}
	}
	else if (playerCoord.x > thorns.pos.x - thorns.sprite.getTextureRect().width && playerCoord.x < thorns.pos.x + thorns.sprite.getTextureRect().width && playerCoord.y > thorns.pos.y - thornsTexture.y && playerCoord.y < thorns.pos.y + thornsTexture.y)
	{
		if (!_damageDone)
		{
			if (GetTotalPlayerHp() > 0 && !_theBoss.Get_IsInvinciblePlayer())
			{
				GetTotalPlayerHp() -= 20;
			}
			_damageDone = true;
		}
	}
}

void ThornsAttack(SoulsLevel*& _soulsLevel, float _dt, bool _OnLeft, Boss& _theBoss)
{
	static float timer = 0;
	static bool IsLock = false;
	static bool damageDone = false;

	_theBoss.Set_IsAttack(true);

	timer += _dt;

	if (_soulsLevel->Get_Player().GetPosition().y < 350 && !IsLock)
	{
		MainCircle.Set_CanDisplay(true);
		thorns.rotation = 90;
		MainCircle.Set_Pos({ _soulsLevel->Get_Player().GetPosition().x , 48 });
	}
	else if (_OnLeft && !IsLock)
	{
		MainCircle.Set_CanDisplay(true);
		thorns.rotation = 0;
		MainCircle.Set_Pos({ 48 , _soulsLevel->Get_Player().GetPosition().y });
	}
	else if (!IsLock)
	{
		MainCircle.Set_CanDisplay(true);
		thorns.rotation = 180;
		MainCircle.Set_Pos({ 623 , _soulsLevel->Get_Player().GetPosition().y });
	}

	if (timer > 1)
	{
		IsLock = true;
	}

	if (IsLock)
	{
		static float current = 0;
		current += _dt;
		thorns.pos = MainCircle.Get_Pos();
		if (current <= 0.5)
		{
			PlayThornSound();
			thorns.affichage = Easing::easeInQuint(current, 0, thorns.sprite.getTexture()->getSize().x, 0.5);
		}
		else if (current > 0.5 && current <= 1)
		{
			thorns.affichage = thorns.sprite.getTexture()->getSize().x - Easing::easeInQuint(current, 0, thorns.sprite.getTexture()->getSize().x, 1);
		}
		else if (current > 1)
		{
			MainCircle.Set_CanDisplay(false);
			current = 0;
			IsLock = false;
			_theBoss.Set_CanChangeAttack(true);
			_theBoss.Set_IsAttack(false);
			timer = 0;
			thorns.affichage = 0;
			_theBoss.Set_Cooldown(1);
			damageDone = false;
		}
	}
	UpdateThornsDamage(_soulsLevel, damageDone, _theBoss);
}

void HandFalling(SoulsLevel*& _soulsLevel, Boss& _theBoss)
{
	_theBoss.Set_IsAttack(true);
	static int numberHand = 0;
	static float delayRequiert = 0.5;
	static sf::Clock delay;

	if (numberHand == 0)
	{
		numberHand = 5 + rand() % 5;
	}

	if (numberHand > 0 && delay.getElapsedTime().asSeconds() > delayRequiert)
	{
		LoadHand(_soulsLevel);
		numberHand--;
		delay.restart();
	}

	if (numberHand <= 0)
	{
		_theBoss.Set_IsAttack(false);
		_theBoss.Set_CanChangeAttack(true);
		_theBoss.Set_Cooldown(1);
	}
}

void UpdateHand(float _dt, SoulsLevel*& _soulsLevel, Boss& _theBoss)
{
	for (int i = 0; i < HandVector.size(); i++)
	{
		HandVector[i].Update(_dt, _soulsLevel, _theBoss);
		if (HandVector[i].Get_CanErase())
		{
			HandVector.erase(HandVector.begin() + i);
		}
	}

}

void RootDamage(SoulsLevel*& _soulsLevel, bool& _damageDone, Boss& _theBoss)
{
	if (laser.Get_Affichage() > 50 && !_damageDone)
	{
		if (GetTotalPlayerHp() > 0 && !_theBoss.Get_IsInvinciblePlayer())
		{
			GetTotalPlayerHp() -= 20;
		}
		_damageDone = true;
	}
}

void RootFirstAnimation(float _dt, SoulsLevel*& _soulsLevel, Boss& _theBoss, float& _timer, bool& _damageDone)
{
	static float timer = 0;
	static float current = 0;
	timer += _dt;

	if (timer <= 0.5)
	{
		rootFirst.affichage = Easing::easeInQuint(timer, 0, rootFirst.sprite.getTexture()->getSize().y, 0.5);
		PlayRootSound();
	}

	if (root.Get_CanRetract())
	{
		if (current <= 0.5)
		{
			rootFirst.affichage = rootFirst.sprite.getTexture()->getSize().y - Easing::easeInQuint(current, 0, rootFirst.sprite.getTexture()->getSize().y, 0.5);
			current += _dt;
			PlayRootSound();
		}
		else
		{
			//reset de l'attaque
			rootFirst.affichage = 0;
			MainCircle.Set_CanDisplay(false);
			_theBoss.Set_Cooldown(1);
			_theBoss.Set_CanChangeAttack(true);
			isCenterOnPlayer = false;
			isCircleCenter = false;
			root.Set_CanRetract(false);
			root.Set_CanDisplay(false);
			root.Set_Cooldown(0);
			root.Set_IsAnimationDone(false);
			root.Set_Compteur(0);
			root.Set_IsPlayerTrapped(false);
			root.Set_CompteurDeload(5);
			root.Set_CooldownDeload(0);
			root.Set_Sprite(LoadSprite("Assets/BossFinal/Attack/Root/1.png", true));
			laser.Set_Affichage(35);
			laser.Set_Alpha(255);
			laser.Set_Angle(0);
			laser.Set_Scale(1);
			laser.Set_CanDisplay(false);
			laser.Set_Timer(0);
			laser.Set_Current(0);
			timer = 0;
			current = 0;
			_timer = 0;
			_damageDone = false;
			_soulsLevel->Get_Player().Set_Speed(200);
			_theBoss.Set_IsAttack(false);
		}
	}
}

void LaserAttack(float _dt, SoulsLevel*& _soulsLevel, Boss& _theBoss)
{
	laser.Update(_dt, _theBoss, _soulsLevel->Get_Player().GetPosition(), root, _soulsLevel);
}

void AttackRoot(float _dt, SoulsLevel*& _soulsLevel, Boss& _theBoss)
{
	static float timer = 0;
	static bool damageDone = false;
	if (!_theBoss.Get_IsAttack())
	{
		_theBoss.Set_IsAttack(true);
	}

	//Centre le joueur dans la racine
	if (!isCenterOnPlayer)
	{
		root.Set_Pos(_soulsLevel->Get_Player().GetPosition());
		isCenterOnPlayer = true;
	}
	if (!isCircleCenter)
	{
		MainCircle.Set_Pos({ _soulsLevel->Get_Player().GetPosition().x - 15,_soulsLevel->Get_Player().GetPosition().y + root.Get_Sprite().getTexture()->getSize().y - 85 });
		MainCircle.Set_CanDisplay(true);
		rootFirst.pos = { MainCircle.Get_Pos().x , MainCircle.Get_Pos().y - rootFirst.sprite.getTexture()->getSize().y };
		isCircleCenter = true;
	}
	timer += _dt;

	if (timer >= 0.5 && !root.Get_CanRetract())
	{
		root.Set_CanDisplay(true);
		rootFirst.affichage = 0;
		root.UpdateAnimation(_soulsLevel, _dt, root);
	}
	RootFirstAnimation(_dt, _soulsLevel, _theBoss, timer, damageDone);
	RootDamage(_soulsLevel, damageDone, _theBoss);
	if (root.Get_IsPlayerTrapped())
	{
		LaserAttack(_dt, _soulsLevel, _theBoss);
		_soulsLevel->Get_Player().SetPosition({ root.Get_Pos() });
	}

}

void UpdateDistancePlayer(SoulsLevel*& _soulsLevel, Boss& _theBoss, float _dt)
{
	sf::Vector2f distance = _theBoss.Get_Pos() - _soulsLevel->Get_Player().GetPosition();
	float norme = sqrtf(distance.x * distance.x + distance.y * distance.y);

	norme < _theBoss.Get_Sprite().getTexture()->getSize().y * 1.5 ? compteur += _dt : compteur = 0;

	if (_theBoss.Get_NeedMove())
	{
		shield.Set_CanDisplay(true);
	}
	else
	{
		shield.Set_CanDisplay(false);
	}

	if (compteur >= 3)
	{
		_theBoss.Set_NeedMove(true);
	}
}

void AttackBlackHole(SoulsLevel*& _soulsLevel, Boss& _theBoss, float _dt)
{
	_theBoss.Set_IsAttack(true);
	static float timer = 0;

	if (!blackHole.Get_CanDisplaySign())
	{
		blackHole.Set_CanDisplaySign(true);
	}
	if (timer < 10)
	{
		blackHole.Update(_dt, _soulsLevel, pm, _theBoss);
		timer += _dt;
	}
	else
	{
		timer = 0;
		blackHole.Reset();
		_theBoss.Set_CanChangeAttack(true);
		_theBoss.Set_IsAttack(false);
		_theBoss.Set_Cooldown(1);
		_soulsLevel->Get_Player().Set_Speed(200);
	}
}

void IntelligenceAttackSouls(Boss& _theBoss)
{
	int random = 4 + rand() % 4;

	if (random == _theBoss.Get_CurrentAttack())
	{
		IntelligenceAttackSouls(_theBoss);
	}
	else
	{
		_theBoss.Set_CurrentAttack((BossAttack)random);
	}
	_theBoss.Set_CanChangeAttack(false);
}

void UpdateBossSoulsAttack(float _dt, SoulsLevel*& _soulsLevel, Boss& _theBoss)
{
	if (!_theBoss.Get_IsAnimation() && _theBoss.Get_Hp() > 0)
	{
		//décrémente le cooldown du boss
		_theBoss.Set_Cooldown(_theBoss.Get_Cooldown() - _dt);

		static bool OnLeft = true;

		if (_theBoss.Get_CanChangeAttack() && !_theBoss.Get_IsAttack() && _theBoss.Get_Hp() > 0)
		{
			if (_soulsLevel->Get_Player().GetPosition().x > 350)
			{
				OnLeft = false;
			}
			else
			{
				OnLeft = true;
			}
			IntelligenceAttackSouls(_theBoss);
		}


		if (_theBoss.Get_Cooldown() <= 0 || _theBoss.Get_IsAttack())
		{
			if (_theBoss.Get_CurrentAttack() == Thorns)
			{
				ThornsAttack(_soulsLevel, _dt, OnLeft, _theBoss);
			}
			else if (_theBoss.Get_CurrentAttack() == BlackHoleAttack)
			{
				AttackBlackHole(_soulsLevel, _theBoss, _dt);
			}
			else if (_theBoss.Get_CurrentAttack() == Hand)
			{
				HandFalling(_soulsLevel, _theBoss);
			}
			else if (_theBoss.Get_CurrentAttack() == RootAttack)
			{
				AttackRoot(_dt, _soulsLevel, _theBoss);
			}
			else if (_theBoss.Get_CurrentAttack() == ChangePhase)
			{
				ResetWorld(_theBoss);
			}
		}
	}
}

void UpdateBossCollision(SoulsLevel*& _soulsLevel, Boss& _theBoss)
{
	if (Collisions::IsCollidingRectRect(_soulsLevel->Get_Player().GetHitbox(), _theBoss.Get_HitBox()))
	{
		_soulsLevel->Get_Player().SetPosition(_soulsLevel->Get_Player().GetPosition() - _soulsLevel->Get_Player().GetVelocity());
	}
}

void UpdateBossDamage(SoulsLevel*& _soulsLevel, Boss& _theBoss)
{
	if (!_theBoss.Get_IsInvincible())
	{
		for (unsigned int i = 0; i < _soulsLevel->Get_Player().GetAttackVector().size(); i++)
		{
			SLPlayer::Attack currentAttack = _soulsLevel->Get_Player().GetAttackVector()[i];
			if (Collisions::IsCollidingRectRect(currentAttack.hitbox, _theBoss.Get_HitBox()))
			{
				_theBoss.Set_Hp(_theBoss.Get_Hp() - currentAttack.damage / 10);
				_theBoss.RestartTouchClock();
				if (currentAttack.type == 0)
				{
					_soulsLevel->Get_Player().DeleteAttack(i);
				}
			}
		}
	}
}

void UpdateParticule(Boss& _theBoss, float _dt)
{
	sf::Vector2f posBoss = { _theBoss.Get_Pos().x - _theBoss.Get_Sprite().getTexture()->getSize().x / 2, _theBoss.Get_Pos().y - _theBoss.Get_Sprite().getTexture()->getSize().y / 2 };

	sf::Color color;

	switch (_theBoss.Get_CurrentAttack())
	{
	case RootAttack: color = sf::Color::Magenta;
		break;
	case Hand:color = sf::Color::Red;
		break;
	case Thorns:color = sf::Color::Green;
		break;
	case BlackHoleAttack:color = sf::Color(255, 106, 0);
		break;
	}
	if (_theBoss.Get_CurrentAttack() != ChangePhase || _theBoss.Get_Hp() > 0)
	{
		pm.AddParticle({ (int)posBoss.x + 4 ,(int)posBoss.y + 44 }, FINAL_BOSS_HAND, 1, color);
		pm.AddParticle({ (int)posBoss.x + 33 , (int)posBoss.y + 44 }, FINAL_BOSS_HAND, 1, color);
	}
	pm.UpdateParticule(_dt);
}

///////////////////////////////////////////// Draw Part /////////////////////////////////////////////

void DisplayCircle(sf::RenderWindow& _window)
{
	MainCircle.Display(_window);
	BlitSprite(thorns.sprite, thorns.pos, _window, { 1 , 1 }, thorns.rotation);
}

void DisplayRoot(sf::RenderWindow& _window)
{
	root.Display(_window);
	BlitSprite(rootFirst.sprite, rootFirst.pos, _window, { 1 , 1 }, 180);
}

////////////////////////////////////////// FONCTION SACREE ////////////////////////////////////////// 

void LoadSoulsBoss()
{
	thorns.sprite = LoadSprite("Assets/BossFinal/Attack/Thorns.png", false);
	thorns.sprite.setOrigin({ 0 , (float)thorns.sprite.getTexture()->getSize().y / 2 });
	rootFirst.sprite = LoadSprite("Assets/BossFinal/Attack/Root/Origin.png", false);
	rootFirst.sprite.setOrigin({ (float)rootFirst.sprite.getTexture()->getSize().x / 2 , (float)rootFirst.sprite.getTexture()->getSize().y });
	MainCircle.Load();
	root.Load();
	shield.Load();
	laser.Load();
	blackHole.Load();
}

void UpdateSoulsBoss(float _dt, Config _config, SoulsLevel*& _soulsLevel, GameState& _gameState, bool& _transition, float _noirAlpha, Player& _player, Boss& _theBoss)
{
	_soulsLevel->Update(_dt, _config);
	_soulsLevel->Get_Shader().AddLight(_theBoss.Get_Pos(), 5);
	UpdateBossSoulsAttack(_dt, _soulsLevel, _theBoss);
	BossCenterSouls(_dt, _soulsLevel, _theBoss);
	MainCircle.Update(_dt);
	thorns.sprite.setTextureRect({ 0 , 0, (int)thorns.affichage, (int)thorns.sprite.getTexture()->getSize().y });
	rootFirst.sprite.setTextureRect({ 0 , 0, (int)rootFirst.sprite.getTexture()->getSize().x , (int)rootFirst.affichage });
	UpdateBossCollision(_soulsLevel, _theBoss);
	UpdateHand(_dt, _soulsLevel, _theBoss);
	shield.UpdateShield(_dt, _theBoss.Get_Pos(), _theBoss);
	UpdateBossDamage(_soulsLevel, _theBoss);
	UpdateDistancePlayer(_soulsLevel, _theBoss, _dt);
	UpdateParticule(_theBoss, _dt);
}

void DisplaySoulsBoss(sf::RenderWindow& _window, SoulsLevel*& _soulsLevel, Boss& _theBoss)
{
	_soulsLevel->Display(_window);
	blackHole.Display(_window);
	_theBoss.Display(_window);
	_theBoss.DisplayHealInfo(_window);
	DisplayCircle(_window);
	if (_theBoss.Get_Hp() > 0)
	{
		pm.DrawParticule(_window);
	}
	for (int i = 0; i < HandVector.size(); i++)
	{
		BlitSprite(HandVector[i].Get_ShadowSprite(), HandVector[i].Get_ShadowPos(), _window, { 1 , 1 }, HandVector[i].Get_Rotation(), sf::Color(255, 255, 255, HandVector[i].Get_Alpha()));
	}
	_soulsLevel->Get_Player().Display(_window);
	if (_theBoss.Get_Hp() > 0)
	{
		shield.Display(_window);
	}
	DisplayRoot(_window);
	for (int i = 0; i < HandVector.size(); i++)
	{
		BlitSprite(HandVector[i].Get_HandSprite(), HandVector[i].Get_HandPos(), _window, { 1 , 1 }, HandVector[i].Get_Rotation());
	}
	laser.Display(_window);
	_soulsLevel->Get_Shader().ApplyLights(_window);
	_soulsLevel->Get_HUD().Display(_window, _soulsLevel->Get_Player().GetLockedMode());

}