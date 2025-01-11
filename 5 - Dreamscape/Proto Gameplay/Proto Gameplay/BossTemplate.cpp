#include "BossTemplate.h"
#define BLACK_HOLE_FORCE 5000
#define SHAKECAM 5

sf::Text TimerSTU;
sf::Text TimerSOULS;
sf::Text TimerPARCOURS;

int totalPlayerHp = 100;

/////////////////////////////////////////// BLACKHOLE PART ////////////////////////////////////////////

void BlackHole::UpdateSignAlpha(float _dt)
{
	if (signTimer <= 1)
	{
		signTimer += _dt;
		signAlpha = Easing::linear(signTimer, 0, 255, 1);
	}
}

void BlackHole::UpdateRotation(float _dt)
{
	if (canDisplayHole)
	{
		rotation += 50 * _dt;
	}
	else
	{
		rotation = 0;
	}
}

void BlackHole::Reset()
{
	rotation = 0;
	canDisplayHole = false;
	canDisplaySign = false;
	signAlpha = 255;
	blackHoleScale = 0;
	signTimer = 0;
}

void BlackHole::UpdateAttraction(float _dt, SoulsLevel*& _soulsLevel, ParticuleManager& pm, Boss& _theBoss)
{
	sf::Vector2f director = pos - _soulsLevel->Get_Player().GetPosition();
	float norme = sqrtf(director.x * director.x + director.y * director.y);
	static sf::Clock delay;
	static float timer = 0;

	if (norme > 0)
	{
		director.x /= norme;
		director.y /= norme;

		if (blackHoleScale >= 1)
		{
			if (norme > 5)
			{
				_soulsLevel->Get_Player().SetPosition(_soulsLevel->Get_Player().GetPosition() + sf::Vector2f{ (director.x * BLACK_HOLE_FORCE * _dt) / (norme / 5), (director.y * BLACK_HOLE_FORCE * _dt) / (norme / 5) });
			}
			else
			{
				_soulsLevel->Get_Player().Set_Speed(0);
			}
			if (timer > 0.1)
			{
				pm.AddParticle((sf::Vector2i)pos, BLACK_HOLE_BOSS, 100, sf::Color::Magenta, 105);
				timer = 0;
			}
			timer += _dt;
		}

		if (norme < 50 && delay.getElapsedTime().asSeconds() > 4 && !_theBoss.Get_IsInvinciblePlayer())
		{
			timer = 0;
			GetTotalPlayerHp() -= 20;
			delay.restart();
		}
	}


}

void BlackHole::Load()
{
	sign = LoadSprite("Assets/BossFinal/Attack/BlackHole/Sign.png", true);
	blackHole = LoadSprite("Assets/BossFinal/Attack/BlackHole/Circle.png", true);
	pos = { 350 , 350 };
}

void BlackHole::Update(float _dt, SoulsLevel*& _soulsLevel, ParticuleManager& _pm, Boss& _theBoss)
{
	UpdateSignAlpha(_dt);
	UpdateRotation(_dt);
	UpdateAttraction(_dt, _soulsLevel, _pm, _theBoss);

	if (signAlpha < 255)
	{
		PlayGlyphSound();
	}
	if (signAlpha >= 254)
	{
		canDisplayHole = true;
		canDisplaySign = false;
	}
	if (canDisplayHole && blackHoleScale < 1)
	{
		PlayBlackHoleSound();
		blackHoleScale += _dt;
	}
}

void BlackHole::Display(sf::RenderWindow& _window)
{
	if (canDisplaySign)
	{
		BlitSprite(sign, pos, _window, { 1 , 1 }, 0, sf::Color(255, 255, 255, signAlpha));
	}
	if (canDisplayHole)
	{
		BlitSprite(blackHole, pos, _window, { blackHoleScale , blackHoleScale }, rotation);
	}
}

///////////////////////////////////////////// LASER PART //////////////////////////////////////////////

void Laser::UpdateAnimation()
{
	static sf::Clock cooldown;
	static int compteur = 0;
	static float delay = 0.16;

	if (scale < 1)
	{
		if (cooldown.getElapsedTime().asSeconds() >= delay)
		{
			cooldown.restart();
			currentSprite = spriteVector[compteur];
			compteur++;
			if (compteur >= spriteVector.size())
			{
				compteur = 0;
			}
		}
	}
	else
	{
		currentSprite = spriteVector[6];
	}
}

void Laser::LaserAnimation()
{
	static sf::Clock cooldown;
	static int compteur = 0;
	float delay = 0.1;

	if (cooldown.getElapsedTime().asSeconds() >= delay)
	{
		cooldown.restart();
		laserSprite = LaserSpriteVector[compteur];
		compteur++;
		if (compteur >= LaserSpriteVector.size())
		{
			compteur = 0;
		}
	}
}

void Laser::Load()
{
	for (int i = 0; i < 12; i++)
	{
		sf::Sprite temp = LoadSprite("Assets/BossFinal/Attack/Laser/Charge/" + std::to_string(i + 1) + ".png", true);
		spriteVector.push_back(temp);
	}
	currentSprite = spriteVector[0];
	pos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

	laserSprite = LoadSprite("Assets/BossFinal/Attack/Laser/Laser/1.png", true);

	for (int i = 0; i < 4; i++)
	{
		sf::Sprite temp = LoadSprite("Assets/BossFinal/Attack/Laser/Laser/" + std::to_string(i + 1) + ".png", true);
		LaserSpriteVector.push_back(temp);
	}
}

void Laser::RotateLaser(sf::Vector2f _pos)
{
	sf::Vector2f laserdir = CreaMaths::CreateVector(_pos, pos);
	angleLaser = 90 + CreaMaths::RadiansToDegrees(atan2f(laserdir.y, laserdir.x));
}

void Laser::Update(float _dt, Boss& _theBoss, sf::Vector2f _pos, Root& _root, SoulsLevel*& _soulsLevel)
{
	CanDisplay = true;
	UpdateAnimation();
	LaserAnimation();
	pos = _theBoss.Get_Pos();
	if (timer <= 3)
	{
		PlayLaserSound();
		scale = Easing::linear(timer, 0, 1, 3);
		timer += _dt;
	}
	else
	{
		scale = 1;
		if (current < 0.5)
		{
			affichageY = Easing::easeInQuint(current, 46, laserSprite.getTexture()->getSize().y, 0.5);
		}
		//Diminue l'alpha du laser après attaque
		if (alpha > 0)
		{
			alpha -= 100 * _dt;
			if (alpha < 0)
			{
				alpha = 0;
			}
		}
		else
		{
			alpha = 0;
			CanDisplay = false;
			_root.Retract(_soulsLevel, _dt);
		}
		current += _dt;
		RotateLaser(_pos);
	}
	laserSprite.setTextureRect({ 0, 0,(int)laserSprite.getTexture()->getSize().x, (int)affichageY });
}

void Laser::Display(sf::RenderWindow& _window)
{
	if (CanDisplay)
	{
		if (scale >= 1)
		{
			laserSprite.setOrigin({ 36 , 25 });
			BlitSprite(laserSprite, pos, _window, { 1 , 1 }, angleLaser, sf::Color(255, 255, 255, alpha));
		}
		else
		{
			BlitSprite(currentSprite, pos, _window, { scale , scale });
		}
	}
}

//////////////////////////////////////////// SHIELD PART /////////////////////////////////////////////

void ShieldCircle::Rotate(float _dt)
{
	rotation += 50 * _dt;
}

void ShieldCircle::UpdateAnimation(Boss& _theBoss)
{
	static sf::Clock cooldown;

	float delay = 0.2;


	if (!isShieldDone)
	{
		if (cooldown.getElapsedTime().asSeconds() >= delay)
		{
			cooldown.restart();
			sprite = spriteTab[compteur];
			compteur++;
			if (compteur >= spriteTab.size())
			{
				_theBoss.Set_IsInvincible(true);
				isShieldDone = true;
			}
		}
	}
}

void ShieldCircle::Load()
{
	for (int i = 0; i < 6; i++)
	{
		sf::Sprite temp = LoadSprite("Assets/BossFinal/Attack/Shield/" + std::to_string(i + 1) + ".png", true);
		spriteTab.push_back(temp);
	}
	sprite = spriteTab[0];
	rotation = 0;
}

void ShieldCircle::UpdateShield(float _dt, sf::Vector2f _pos, Boss& _theBoss)
{
	Rotate(_dt);
	pos = _pos;
	if (canDisplay)
	{
		UpdateAnimation(_theBoss);
	}
	else
	{
		_theBoss.Set_IsInvincible(false);
		sprite = spriteTab[0];
		compteur = 0;
		isShieldDone = false;
	}
}

void ShieldCircle::Display(sf::RenderWindow& _window)
{
	if (canDisplay)
	{
		BlitSprite(sprite, pos, _window, { 1 , 1 }, rotation);
	}
}

///////////////////////////////////////////// ROOT PART /////////////////////////////////////////////

void Root::Retract(SoulsLevel*& _soulsLevel, float _dt)
{
	float delay = 0.1;

	if (cooldownDeload >= 0)
	{
		cooldownDeload += _dt;
		if (cooldownDeload >= delay)
		{
			cooldownDeload = 0;
			currentSprite = spriteVector[compteurDeload];
			compteurDeload--;
			if (compteurDeload <= 0)
			{
				canDisplay = false;
				canRetract = true;
			}
		}
	}

	currentSprite.setOrigin(80, 85);
}

void Root::UpdateAnimation(SoulsLevel*& _soulsLevel, float _dt, Root& _root)
{
	float delay = 0.1;

	if (!isAnimationDone)
	{
		cooldown += _dt;
		if (cooldown >= delay)
		{
			cooldown = 0;
			currentSprite = spriteVector[compteur];
			compteur++;
			if (compteur >= spriteVector.size())
			{
				isAnimationDone = true;
			}
		}
	}

	currentSprite.setOrigin(80, 85);

	if (isAnimationDone)
	{
		sf::Vector2f distance = _soulsLevel->Get_Player().GetPosition() - pos;
		float norme = sqrtf(distance.x * distance.x + distance.y * distance.y);

		if (norme < 40 && !canRetract)
		{
			_soulsLevel->Get_Player().Set_Speed(0);
			isPlayerTrapped = true;
			currentSprite = spriteVector[5];
			currentSprite.setOrigin(80, 85);
		}
		else if (canRetract)
		{
			isPlayerTrapped = false;
		}

		if (!isPlayerTrapped)
		{
			_root.Retract(_soulsLevel, _dt);
		}
	}
}

void Root::Load()
{
	currentSprite = spriteVector[0];
	currentSprite.setOrigin(80, 85);
}

void Root::Display(sf::RenderWindow& _window)
{

	if (canDisplay && !canRetract)
	{
		BlitSprite(currentSprite, pos, _window);
	}
}

//////////////////////////////////////////// CIRCLE PART ////////////////////////////////////////////

void Circle::Rotate(float _dt)
{
	rotation += 50 * _dt;
}

void Circle::Load()
{
	sprite = LoadSprite("Assets/BossFinal/Boss/Circle/Circle base.png", true);
	rotation = 0;
}

void Circle::Update(float _dt)
{
	Rotate(_dt);
}

void Circle::Display(sf::RenderWindow& _window)
{
	if (canDisplay)
	{
		BlitSprite(sprite, pos, _window, { 1 , 1 }, rotation);
	}
}

///////////////////////////////////////////// BOSS PART /////////////////////////////////////////////

void Boss::UpdateSwitchWorld(float _dt, bool& _transition, float _noirAlpha, SoulsLevel*& _soulsLevel, PlatformerData& _platformer)
{
	float timeLeft = randomTimer - timer;
	timer += _dt;

	if (!IsAttack)
	{
		if ((timer >= randomTimer && hp > 50) || isTpStart)
		{
			isTpStart = true;
			ShakeCamera(_dt, _soulsLevel, _platformer);
			PlayBossScream();
			currentAttack = ChangePhase;
			TransitionTP(timeLeft, _transition, _noirAlpha, timer, randomTimer);
		}
	}


	float decimal = timeLeft - (int)timeLeft;

	TimerSTU.setString(std::to_string((int)timeLeft) + "." + std::to_string((int)(decimal * 10)));
	TimerSOULS.setString(std::to_string((int)timeLeft) + "." + std::to_string((int)(decimal * 10)));
	TimerPARCOURS.setString(std::to_string((int)timeLeft) + "." + std::to_string((int)(decimal * 10)));


	if (timeLeft <= 0)
	{
		TimerSTU.setString(std::to_string(0) + "." + std::to_string(0));
		TimerSOULS.setString(std::to_string(0) + "." + std::to_string(0));
		TimerPARCOURS.setString(std::to_string(0) + "." + std::to_string(0));

	}
	static float color = 255;
	static float alpha = 0;

	if (timeLeft < 10)
	{
		alpha += 5 * _dt;
		color = 126 * (cosf(alpha) + 1);
		TimerSTU.setFillColor(sf::Color{ 255 , (sf::Uint8)color ,(sf::Uint8)color });
		TimerSOULS.setFillColor(sf::Color{ 255 , (sf::Uint8)color ,(sf::Uint8)color });
		TimerPARCOURS.setFillColor(sf::Color{ 255 , (sf::Uint8)color ,(sf::Uint8)color });
	}
	else
	{
		TimerSTU.setFillColor(sf::Color{ 255 , 255 ,255 });
		TimerSOULS.setFillColor(sf::Color{ 255 , 255 ,255 });
		TimerPARCOURS.setFillColor(sf::Color{ 255 , 255 ,255 });
	}
}

void Boss::GenerateNewWorld()
{
	int randomState = rand() % 3;

	if ((BossState)randomState == state)
	{
		GenerateNewWorld();
	}
	else if (needPlatformer)
	{
		state = BOSSPARCOUR;
		pos = { (float)1280, (float)200 };
		needPlatformer = false;
	}
	else if (needSTU)
	{
		state = BOSSSTU;
		pos = { (float)SCREEN_WIDTH / 2, (float)20 + Currentsprite.getTexture()->getSize().y * 3 / 2 };
		needSTU = false;
	}
	else if (needSouls)
	{
		state = BOSSSOULS;
		pos = { (float)350, (float)100 };
		needSouls = false;
	}
	else
	{
		state = (BossState)randomState;
		switch (state)
		{
		case BOSSSOULS:
			pos = { (float)350, (float)100 };
			break;
		case BOSSPARCOUR:
			pos = { (float)1280, (float)200 };
						break;
		case BOSSSTU:
			pos = { (float)SCREEN_WIDTH / 2, (float)20 + Currentsprite.getTexture()->getSize().y * 3 / 2 };
			break;
		}

		IsAnimation = false;
	}
}

bool Boss::Collide(sf::Vector2f _point, int _damage)
{
	if (hp > 0)
	{
		sf::Vector2f BossSize = { (float)Currentsprite.getTexture()->getSize().x * 3 , (float)Currentsprite.getTexture()->getSize().y * 3 };

		if (_point.x > pos.x - BossSize.x / 2 && _point.x < pos.x + BossSize.x / 2 && _point.y > pos.y - BossSize.y / 2 && _point.y < pos.y + BossSize.y / 2)
		{
			touch.restart();
			hp -= _damage;
			return true;
		}

		return false;
	}
}

void Boss::BossAnimation()
{
	if (hp > 0)
	{
		if (currentAttack == ChangePhase)
		{

		}
		else if (!IsAttack)
		{
			AnimationSprite(tabVectorSprite[SecondPhase][state], Currentsprite, 1);
		}
		else if (currentAttack != Lightning && currentAttack != Explosion)
		{
			AnimationSprite(tabVectorSprite[SecondPhase][state], Currentsprite, 1);
		}
	}
	else
	{
		static sf::Clock cooldown;
		static int compteur = 0;
		float delay = 0.1;

		switch (state)
		{
		case BOSSSOULS:
			if (!isAnimationDeathDone)
			{
				if (cooldown.getElapsedTime().asSeconds() >= delay)
				{
					cooldown.restart();
					Currentsprite = spriteTabDeathSouls[compteur];
					compteur++;
					if (compteur >= spriteTabDeathSouls.size())
					{
						isAnimationDeathDone = true;
						alpha = 0;
					}
				}
			}
			break;
		case BOSSSTU:
			if (!isAnimationDeathDone)
			{
				if (cooldown.getElapsedTime().asSeconds() >= delay)
				{
					cooldown.restart();
					Currentsprite = spriteTabDeathSTU[compteur];
					compteur++;
					if (compteur >= spriteTabDeathSTU.size())
					{
						isAnimationDeathDone = true;
						alpha = 0;
					}
				}
			}
			break;
		case BOSSPARCOUR:
			if (!isAnimationDeathDone)
			{
				if (cooldown.getElapsedTime().asSeconds() >= delay)
				{
					cooldown.restart();
					Currentsprite = spriteTabDeathSTU[compteur];
					compteur++;
					if (compteur >= spriteTabDeathSTU.size())
					{
						isAnimationDeathDone = true;
						alpha = 0;
					}
				}
			}
			break;
		}
		PlayBossDeath();
	}
}

void Boss::Reset()
{
	hp = maxHp;
	cooldown = 5;
	IsAttack = false;
	pos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	timer = 0;
	randomTimer = 45 + rand() % 15;
}

void Boss::PlayerCollide()
{
	sf::Vector2f BossSize = { (float)Currentsprite.getTexture()->getSize().x * 3 , (float)Currentsprite.getTexture()->getSize().y * 3 };
	static sf::Clock Invincibility;

	if (GetPlayer().GetPos().x > pos.x - BossSize.x / 2 && GetPlayer().GetPos().x < pos.x + BossSize.x / 2 && GetPlayer().GetPos().y > pos.y - BossSize.y / 2 && GetPlayer().GetPos().y < pos.y + BossSize.y / 2)
	{
		if (Invincibility.getElapsedTime().asSeconds() > 2 && !isInvinciblePlayer)
		{
			totalPlayerHp -= 20;
			Invincibility.restart();
		}
	}

}

void Boss::TransitionTP(float timeLeft, bool& _transition, float _noirAlpha, float& _timer, float& _randomTimer)
{
	static sf::Clock wait;
	static sf::Clock cooldown;
	static int compteur = 0;
	static float delay = 0.75;
	static bool isAnimationDone = false;

	if (state != BOSSSOULS)
	{
		if (compteur < spriteTabTpSTU.size())
		{
			IsAnimation = true;
			if (cooldown.getElapsedTime().asSeconds() >= delay)
			{
				cooldown.restart();
				Currentsprite = spriteTabTpSTU[compteur];
				compteur++;
				if (compteur >= spriteTabTpSTU.size())
				{
					isAnimationDone = true;
				}
			}
		}
	}
	else
	{
		if (compteur < spriteTabTpSouls.size())
		{
			IsAnimation = true;
			if (cooldown.getElapsedTime().asSeconds() >= delay)
			{
				cooldown.restart();
				Currentsprite = spriteTabTpSouls[compteur];
				compteur++;
				if (compteur >= spriteTabTpSouls.size())
				{
					isAnimationDone = true;
				}
			}
		}
	}

	if (isAnimationDone)
	{
		PlayChangeWorld();
		_transition = true;
		wait.restart();
		cooldown.restart();
	}

	if (_noirAlpha >= 254)
	{
		_transition = false;
		GenerateNewWorld();
		_timer = 0;
		newPhaseTime.restart();
		_randomTimer = 45 + (rand() % 15);
		IsAttack = false;
		canChangeAttack = true;
		isAnimationDone = false;
		compteur = 0;
		IsAnimation = false;
		isTpStart = false;
	}
}

void Boss::DecreaseHp(float _damage)
{
	hp -= _damage;
	if (hp < 0)
	{
		hp = 0;
	}
}

void Boss::ShakeCamera(float _dt, SoulsLevel*& _soulsLevel, PlatformerData& _platformer)
{
	sf::Vector2f newCamCenter;

	switch (state)
	{
	case BOSSSOULS:
		newCamCenter.x = _soulsLevel->Get_Camera().Get_Pos().x + (-SHAKECAM + (float)(rand() % (int)(SHAKECAM * 2)));
		newCamCenter.y = _soulsLevel->Get_Camera().Get_Pos().y + (-SHAKECAM + (float)(rand() % (int)(SHAKECAM * 2)));
		_soulsLevel->Get_Camera().GetView().setCenter(newCamCenter);
		break;
	case BOSSSTU:
		ShakeSTU({ SHAKECAM , SHAKECAM }, 0.1);
		break;
	case BOSSPARCOUR:
		newCamCenter.x = _platformer.camera.GetView().getCenter().x + (-SHAKECAM / 2 + (float)(rand() % (int)(SHAKECAM)));
		newCamCenter.y = _platformer.camera.GetView().getCenter().y + (-SHAKECAM / 2 + (float)(rand() % (int)(SHAKECAM)));
		_platformer.camera.GetView().setCenter(newCamCenter);

		break;
	}
}

void Boss::DisplayHealInfo(sf::RenderWindow& _window)
{
	BlitSprite(LifeBarreEmpty, LifeBarrePos, _window, { scale , scale });
	BlitSprite(LifeBarreFull, LifeBarrePos, _window, { scale , scale });
}

void Boss::Load()
{
	Currentsprite = LoadSprite("Assets/BossFinal/Boss/Idle/STU/1STU.png", true);
	LifeBarreEmpty = LoadSprite("Assets/BossFinal/LifeBarre/LifeEmpty.png", true);
	LifeBarreFull = LoadSprite("Assets/BossFinal/LifeBarre/LifeFull.png", true);
	LifeBarreHeal = LoadSprite("Assets/BossFinal/LifeBarre/LifeHeal.png", true);
	shadowBoss = LoadSprite("Assets/BossFinal/Boss/shadow.png", true);
	TimerSTU = LoadText("Assets/Font/Monocraft.otf", "50.0", 50, { SCREEN_WIDTH / 2, 50 }, sf::Color::White, true);
	TimerSOULS = LoadText("Assets/Font/Monocraft.otf", "50.0", 30, { SCREEN_WIDTH / 2, 50 }, sf::Color::White, true);
	TimerPARCOURS = LoadText("Assets/Font/Monocraft.otf", "50.0", 17, { SCREEN_WIDTH / 2, 50 }, sf::Color::White, true);
	state = (BossState)(rand() % 3);

	switch (state)
	{
	case BOSSSOULS:	pos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	break;
	case BOSSSTU:	pos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	break;
	case BOSSPARCOUR:	pos = { 1280, 200 };
	break;

	}

	for (int i = 1; i <= 6; i++)
	{
		sf::Sprite sprite = LoadSprite("Assets/BossFinal/Attack/Platformer/Thunder/Charge/" + std::to_string(i) + ".png", true);
		spriteThunder.push_back(sprite);
	}

	for (int i = 1; i <= 7; i++)
	{
		sf::Sprite sprite = LoadSprite("Assets/BossFinal/Attack/Platformer/Explosion/Charge/" + std::to_string(i) + ".png", true);
		spriteExplosionTP.push_back(sprite);
	}

	for (int i = 1; i <= 11; i++)
	{
		sf::Sprite sprite = LoadSprite("Assets/BossFinal/Attack/Platformer/Explosion/Explosion/" + std::to_string(i) + ".png", true);
		spriteExplosion.push_back(sprite);
	}

	for (int i = 1; i <= 26; i++)
	{
		sf::Sprite sprite = LoadSprite("Assets/BossFinal/Boss/Death/Souls/" + std::to_string(i) + ".png", true);
		spriteTabDeathSouls.push_back(sprite);
		sprite = LoadSprite("Assets/BossFinal/Boss/Death/STU/" + std::to_string(i) + ".png", true);
		spriteTabDeathSTU.push_back(sprite);
	}
}

void Boss::Update(float _dt, bool& _transition, float _noirAlpha, GameState& _gameState, SoulsLevel*& _soulsLevel, PlatformerData& _platformer)
{
	static bool isDone = false;
	UpdateSwitchWorld(_dt, _transition, _noirAlpha, _soulsLevel, _platformer);
	LifeBarrePos = { pos.x , (float)(pos.y - Currentsprite.getTexture()->getSize().y * scale / 1.8) };
	LifeBarreFull.setTextureRect({ 0 , 0, (int)(LifeBarreFull.getTexture()->getSize().x * (hp / maxHp)), (int)LifeBarreFull.getTexture()->getSize().y });
	LifeBarreHeal.setTextureRect({ 0 , 0, (int)(LifeBarreFull.getTexture()->getSize().x * (hp / maxHp)), (int)LifeBarreFull.getTexture()->getSize().y });
	shadowPos = { pos.x , pos.y + Currentsprite.getTexture()->getSize().y / 2 };

	PlayerCollide();
	hitBox = { pos.x - (float)Currentsprite.getTexture()->getSize().x / 2 ,pos.y - (float)Currentsprite.getTexture()->getSize().y / 2, (float)Currentsprite.getTexture()->getSize().x, (float)Currentsprite.getTexture()->getSize().y };

	if (hp < maxHp / 2 && !IsAttack && !SecondPhase)
	{
		SecondPhase = true;
	}

	if (hp < 0)
	{
		hp = 0;
		canChangeAttack = false;
	}
	waitingForAttack -= _dt;

	if (waitingForAttack <= 0 && !isDone)
	{
		IsAttack = false;
		canChangeAttack = true;
		isDone = true;
	}

	BossAnimation();

	if (currentAttack == ChangePhase)
	{
		isInvincible = true;
	}
}

void Boss::Display(sf::RenderWindow& _window)
{
	if (touch.getElapsedTime().asSeconds() >= 0.3)
	{
		if (state == BOSSSOULS)
		{
			BlitSprite(shadowBoss, shadowPos, _window, { scale , scale }, 0, sf::Color(255, 255, 255, 180));
		}
		BlitSprite(Currentsprite, pos, _window, { scale , scale }, 0, sf::Color(255, 255, 255, alpha));
	}
	else
	{
		if (state == BOSSSOULS)
		{
			BlitSprite(shadowBoss, shadowPos, _window, { scale , scale }, 0, sf::Color(255, 100, 100, 180));
		}
		BlitSprite(Currentsprite, pos, _window, { scale , scale }, 0, sf::Color(255, 100, 100, alpha));
	}


	TimerSOULS.setPosition(_window.mapPixelToCoords({ SCREEN_WIDTH / 2, 50 }));
	TimerPARCOURS.setPosition(_window.mapPixelToCoords({ SCREEN_WIDTH / 2, 50 }));
	TimerSTU.setPosition(_window.mapPixelToCoords({ SCREEN_WIDTH / 2, 50 }));

	switch (state)
	{
	case BOSSSOULS:	//_window.draw(TimerSOULS);
		scale = 1;
		break;
	case BOSSPARCOUR:	//_window.draw(TimerPARCOURS);
		scale = 1;
		break;
	case BOSSSTU:	//_window.draw(TimerSTU);
		scale = 3;
		break;
	}
}

void UpdateInvincibility(Boss& _theBoss)
{
}

int& GetTotalPlayerHp()
{
	return totalPlayerHp;
}