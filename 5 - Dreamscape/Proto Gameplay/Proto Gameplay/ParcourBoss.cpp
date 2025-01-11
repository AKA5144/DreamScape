#include "ParcourBoss.h"
#define SHAKECAM 5

///////////////////////////////////////// Thunder Part ///////////////////////////////////////////////

Thunder thunder;
Warning warning;
BallBouncing bouncing;
ExplosionHitBox explosionHitBox;

std::vector <BallSliding> slidingBallVector;

void Warning::Load()
{
	sprite = LoadSprite("Assets/BossFinal/Attack/Platformer/Thunder/Thunder/Warning.png", true);
}

void Warning::Update(float _dt, PlatformerData& _platformerData)
{
	if (canMove)
	{
		pos.y = 320 - sprite.getTexture()->getSize().y / 2;
		pos.x = _platformerData.players.GetPosition().x;
	}
}

void Warning::Display(sf::RenderWindow& _window)
{
	if (canDisplay)
	{
		BlitSprite(sprite, pos, _window, { 1 , 1 }, 1, sf::Color(255, 255, 255, 50));
	}
}

void Thunder::Animation(float _dt)
{
	static sf::Clock cooldown;
	static int compteur = 0;
	float delay = 0.1 / spriteTab.size();

	if (cooldown.getElapsedTime().asSeconds() >= delay)
	{
		cooldown.restart();
		currentSprite = spriteTab[compteur];
		compteur++;
		if (compteur >= spriteTab.size())
		{
			compteur = 0;
		}
	}
}

void Thunder::Update(float _dt, sf::Vector2f _pos, Boss& _theBoss, Warning& _warning, bool& _isAnimationDone, PlatformerData& _platformerData)
{
	static float timer = 0;
	static bool DamageDone = false;
	timer += _dt;
	pos.x = _pos.x;
	pos.y = 320 - currentSprite.getTexture()->getSize().y / 2;

	canDisplay = true;
	_warning.canDisplay = false;
	if (timer <= 0.2)
	{
		affichageY = Easing::linear(timer, 0, 1, 0.2);
	}
	else
	{
		affichageY = 1;
		Animation(_dt);

		if (_platformerData.players.GetPosition().x > pos.x - currentSprite.getTexture()->getSize().x / 2 && _platformerData.players.GetPosition().x < pos.x + currentSprite.getTexture()->getSize().x / 2 && _platformerData.players.GetPosition().y > pos.y - currentSprite.getTexture()->getSize().y / 2 && _platformerData.players.GetPosition().y < pos.y + currentSprite.getTexture()->getSize().y / 2 && !_theBoss.Get_IsInvinciblePlayer())
		{
			if (!DamageDone)
			{
				GetTotalPlayerHp() -= 20;
				DamageDone = true;
			}
		}

		if (timer < 1)
		{
			PlayThunderSound();
			alpha = 255 - Easing::linear(timer, 0, 255, 1);
		}
		else
		{
			alpha = 0;
		}
	}

	currentSprite.setTextureRect({ 0 , 0 , (int)spriteTaille.x, (int)(spriteTaille.y) });

	if (alpha <= 0)
	{
		timer = 0;
		alpha = 255;
		_warning.canDisplay = false;
		_warning.canMove = true;
		_isAnimationDone = false;
		DamageDone = false;
		affichageY = 0;
		canDisplay = false;
		_theBoss.Set_Cooldown(1);
		_theBoss.Set_IsAttack(false);
		_theBoss.Set_CanChangeAttack(true);
	}
}

void Thunder::Display(sf::RenderWindow& _window)
{
	if (canDisplay)
	{
		BlitSprite(currentSprite, pos, _window, { 1 , 1 }, 0, sf::Color(255, 255, 255, alpha));
	}
}

void BallBouncing::UpdateLifeTime(float _dt)
{
	lifeTime -= _dt;
	if (lifeTime <= 0)
	{
		canDisplay = false;
	}
}

void BallBouncing::UpdateBorderCollision(float _dt, PlatformerData& _platformerData)
{
	if (pos.x - 25 < _platformerData.camera.GetView().getCenter().x - SCREEN_WIDTH / 6)
	{
		PlayBounceBall();
		director.x *= -1;
		pos.x = _platformerData.camera.GetView().getCenter().x - SCREEN_WIDTH / 6 + 26;
	}
	else if (pos.x + 25 > _platformerData.camera.GetView().getCenter().x + SCREEN_WIDTH / 6)
	{
		PlayBounceBall();
		director.x *= -1;
		pos.x = _platformerData.camera.GetView().getCenter().x + SCREEN_WIDTH / 6 - 26;
	}

	if (pos.y - 25 < _platformerData.camera.GetView().getCenter().y - SCREEN_HEIGHT / 6)
	{
		PlayBounceBall();
		director.y *= -1;
		pos.y = _platformerData.camera.GetView().getCenter().y - SCREEN_HEIGHT / 6 + 26;
	}
	else if (pos.y + 25 > 320)
	{
		PlayBounceBall();
		director.y *= -1;
		pos.y = 320 - 26;
	}

}

void BallBouncing::Load()
{
	for (int i = 1; i <= 4; i++)
	{
		sf::Sprite sprite = LoadSprite("Assets/BossFinal/Attack/Platformer/Bouncing Ball/" + std::to_string(i) + ".png", true);
		spriteTab.push_back(sprite);
	}
	currentSprite = spriteTab[0];
}

void BallBouncing::Update(float _dt, PlatformerData& _platformerData, Boss& _theBoss)
{
	static int compteur = 0;
	static sf::Clock cooldownDamage;

	if (canDisplay)
	{
		static sf::Clock cooldown;
		float delay = 0.5;

		if (cooldown.getElapsedTime().asSeconds() >= delay)
		{
			cooldown.restart();
			currentSprite = spriteTab[compteur];
			compteur++;
			if (compteur >= spriteTab.size())
			{
				compteur = 0;
			}
		}

		sf::Vector2f distance = pos - _platformerData.players.GetPosition();
		float norme = sqrtf(distance.x * distance.x + distance.y * distance.y);

		if (norme < currentSprite.getTexture()->getSize().x / 2 && cooldownDamage.getElapsedTime().asSeconds() > 1 && !_theBoss.Get_IsInvinciblePlayer())
		{
			GetTotalPlayerHp() -= 20;
			cooldownDamage.restart();
		}

		pos += {director.x * 500 * _dt, director.y * 500 * _dt};
		UpdateLifeTime(_dt);
		UpdateBorderCollision(_dt, _platformerData);
	}
	else
	{
		compteur = 0;
		lifeTime = 5;

	}
}

void BallBouncing::Display(sf::RenderWindow& _window)
{
	if (canDisplay)
	{
		BlitSprite(currentSprite, pos, _window);
	}
}

void BallSliding::UpdateAnimation(float _dt)
{
	if (cooldown.getElapsedTime().asSeconds() >= delay)
	{
		cooldown.restart();
		currentSprite = spriteTab[compteur];
		compteur++;
		if (compteur >= spriteTab.size())
		{
			compteur = 0;
		}
	}
}

void BallSliding::Load(PlatformerData& _platformerData, sf::Vector2f _pos)
{
	canDisplay = true;
	for (int i = 1; i <= 4; i++)
	{
		sf::Sprite sprite = LoadSprite("Assets/BossFinal/Attack/Platformer/Sliding Ball/" + std::to_string(i) + ".png", true);
		spriteTab.push_back(sprite);
	}
	currentSprite = spriteTab[0];

	if (slidingBallVector.size() % 2)
	{
		pos.x = _pos.x + SCREEN_WIDTH / 4 + currentSprite.getTexture()->getSize().x / 2;
		onLeft = false;
	}
	else
	{
		pos.x = _pos.x - SCREEN_WIDTH / 4 - currentSprite.getTexture()->getSize().x / 2;
		onLeft = true;
	}

	pos.y = 310 - (slidingBallVector.size() % 3) * currentSprite.getTexture()->getSize().y;

}

void BallSliding::Update(float _dt, PlatformerData& _platformerData, Boss& _theBoss)
{
	UpdateAnimation(_dt);

	onLeft ? pos.x += 100 * _dt : pos.x -= 100 * _dt;

	alpha < 254 ? alpha += _dt * 250 : alpha = 255;

	if (alpha > 255)
	{
		alpha = 255;
	}
	lifeTime -= _dt;

	if (lifeTime <= 0)
	{
		canDisplay = false;
	}

	sf::Vector2f distance = pos - _platformerData.players.GetPosition();
	float norme = sqrtf(distance.x * distance.x + distance.y * distance.y);

	if (norme < currentSprite.getTexture()->getSize().x / 2 && alpha >= 255 )
	{
		if (!_theBoss.Get_IsInvinciblePlayer())
		{
			GetTotalPlayerHp() -= 20;
		}
		isTouch = true;
	}

}

void BallSliding::Display(sf::RenderWindow& _window)
{
	if (canDisplay)
	{
		BlitSprite(currentSprite, pos, _window, { 1 , 1 }, 0, sf::Color(255, 255, 255, alpha));
	}
}

void ExplosionHitBox::Reset()
{
	rotation = 0;
	alpha = 255;
	scale = 0;
	timer = 0;
	damageDone = false;
	attackEnd = false;
}

void ExplosionHitBox::Load()
{
	sprite = LoadSprite("Assets/BossFinal/Attack/Platformer/Explosion/hitBox.png", true);

}

void ExplosionHitBox::Update(Boss& _theBoss, PlatformerData& _platformerData, float _dt)
{
	sf::Vector2f newCamCenter;

	timer += _dt;

	if (timer <= 0.1)
	{
		scale = Easing::linear(timer, 0, 1.5, 0.1);
	}
	else
	{
		scale = 1.5;
	}

	if (scale > 0.5)
	{
		newCamCenter.x = _platformerData.camera.GetView().getCenter().x + (-SHAKECAM / 2 + (float)(rand() % (int)(SHAKECAM)));
		newCamCenter.y = _platformerData.camera.GetView().getCenter().y + (-SHAKECAM / 2 + (float)(rand() % (int)(SHAKECAM)));
		_platformerData.camera.GetView().setCenter(newCamCenter);
	}

	if (timer > 0.3 && alpha > 0)
	{
		alpha -= 500 * _dt;
	}

	if (alpha <= 0)
	{
		alpha = 0;
		attackEnd = true;
	}

	pos = _theBoss.Get_Pos();

	sf::Vector2f distance = pos - _platformerData.players.GetPosition();
	float norme = sqrtf(distance.x * distance.x + distance.y * distance.y);

	if (norme <= sprite.getTexture()->getSize().y / 2 * scale && !damageDone && !_theBoss.Get_IsInvinciblePlayer())
	{
		damageDone = true;
		GetTotalPlayerHp() -= 20;
	}

}

void ExplosionHitBox::Display(sf::RenderWindow& _window)
{
	BlitSprite(sprite, pos, _window, { scale, scale }, rotation, sf::Color(255, 255, 255, alpha));
}

////////////////////////////////////////// Load Part ////////////////////////////////////////////////



//////////////////////////////////////////// Update Part ////////////////////////////////////////////

void ResetWorld()
{
	slidingBallVector.clear();
	bouncing.Set_LifeTime(0);
}

void BossMove(float _dt, Boss& _theBoss, PlatformerData& _platformerData)
{
	if (!_theBoss.Get_IsAttack())
	{
		static bool needCenter = false;
		static float compteurX = 0;
		static float compteurY = 0;

		if (!needCenter)
		{
			compteurX += 1 * _dt;
			_theBoss.Set_X(_theBoss.Get_Pos().x + std::cos(compteurX) * 50 * _dt);
		}
		compteurY += 2 * _dt;
		_theBoss.Set_Y(_theBoss.Get_Pos().y + std::cos(compteurY) * 50 * _dt);


		sf::Vector2f distance = _platformerData.players.GetPosition() - _theBoss.Get_Pos();

		float norme = distance.x * distance.x + distance.y * distance.y;

		distance.x /= norme;
		distance.y /= norme;

		if (norme > 40000)
		{
			needCenter = true;
		}

		if (needCenter)
		{
			_theBoss.Set_X(_theBoss.Get_Pos().x + distance.x * 50000 * _dt);
		}

		if (norme < 12000)
		{
			needCenter = false;
		}
	}
}

void ThunderAttack(Boss& _theBoss, float _dt, PlatformerData& _platformerData)
{
	_theBoss.Set_IsAttack(true);

	static sf::Clock cooldown;
	static int compteur = 0;
	static bool isAnimationDone = false;
	static sf::Vector2f thunderPos;
	float delay = 0.1;
	warning.canDisplay = true;
	PlayWarningThunder();

	if (!isAnimationDone)
	{
		if (cooldown.getElapsedTime().asSeconds() >= delay)
		{
			cooldown.restart();
			_theBoss.Set_Sprite(_theBoss.spriteThunder[compteur]);
			compteur++;
			if (compteur >= _theBoss.spriteThunder.size())
			{
				isAnimationDone = true;
				compteur = 0;
			}
			else if (compteur >= _theBoss.spriteThunder.size() / 2)
			{
				if (warning.canMove)
				{
					thunderPos = _platformerData.players.GetPosition();
				}
				warning.canMove = false;
			}
		}
	}
	else
	{
		thunder.Update(_dt, thunderPos, _theBoss, warning, isAnimationDone, _platformerData);
	}
}

void ExplosionAttack(Boss& _theBoss, float _dt, PlatformerData& _platformerData)
{
	static sf::Clock cooldown;
	static int compteur = 0;
	static bool isAnimationDone = false;
	static bool alphaSet = false;
	float delay = 0.3;
	_theBoss.Set_IsAttack(true);

	if (!isAnimationDone)
	{
		if (cooldown.getElapsedTime().asSeconds() >= delay)
		{
			cooldown.restart();
			_theBoss.Set_Sprite(_theBoss.spriteExplosionTP[compteur]);
			compteur++;
			if (compteur >= _theBoss.spriteExplosionTP.size())
			{
				isAnimationDone = true;
				compteur = 0;
				_theBoss.Set_Alpha(0);
				PlayDisparition();
			}
		}
	}

	if ((alphaSet || _theBoss.Get_Alpha() <= 0) && cooldown.getElapsedTime().asSeconds() >= 2)
	{

		static sf::Clock cooldown2;
		static int compteur2 = 0;
		static bool isAnimationDone2 = false;
		float delay2 = 0.1;

		if (!isAnimationDone2)
		{
			if (_theBoss.Get_Alpha() != 255 && cooldown2.getElapsedTime().asSeconds() >= delay2)
			{
				_theBoss.Set_Pos({ _platformerData.players.GetPosition().x , _platformerData.players.GetPosition().y - 30 });
				_theBoss.Set_Alpha(255);
				alphaSet = true;
				PlayApparition();
			}

			if (cooldown2.getElapsedTime().asSeconds() >= delay2)
			{
				cooldown2.restart();
				_theBoss.Set_Sprite(_theBoss.spriteExplosion[compteur2]);
				compteur2++;
				if (compteur2 >= _theBoss.spriteExplosion.size())
				{
					isAnimationDone2 = true;

				}
			}
		}
		else
		{
			explosionHitBox.Update(_theBoss, _platformerData, _dt);

			if (explosionHitBox.Get_AttackEnd())
			{
				explosionHitBox.Reset();
				alphaSet = false;
				compteur = 0;
				compteur2 = 0;
				isAnimationDone = false;
				isAnimationDone2 = false;
				_theBoss.Set_CanChangeAttack(true);
				_theBoss.Set_IsAttack(false);
			}

		}
	}
}

void BouncingBallAttack(Boss& _theBoss, float _dt, PlatformerData& _platformerData)
{
	_theBoss.Set_IsAttack(true);

	static bool posSet = false;
	if (!posSet)
	{
		bouncing.Set_Pos(_theBoss.Get_Pos());
		bouncing.Set_CanDisplay(true);
		bouncing.Set_Director({ (float)(100 - rand() % 200) / 100 , (float)(100 - rand() % 200) / 100 });
		posSet = true;
	}
	posSet = false;
	_theBoss.Set_CanChangeAttack(true);
	_theBoss.Set_IsAttack(false);
}

void SlidingBallAttack(Boss& _theBoss, float _dt, PlatformerData& _platformerData)
{
	static int numberBullet = 12;
	static sf::Clock delay;
	static bool posTarget = false;
	static sf::Vector2f pos;
	if (!posTarget)
	{
		pos = _platformerData.players.GetPosition();
		posTarget = true;
	}

	if (delay.getElapsedTime().asSeconds() >= 2 && numberBullet > 0)
	{
		for (int i = 0; i < 4; i++)
		{
			BallSliding ball;
			ball.Load(_platformerData, pos);
			slidingBallVector.push_back(ball);
			numberBullet--;
		}
		delay.restart();
	}

	if (numberBullet <= 0)
	{
		_theBoss.Set_IsAttack(false);
		_theBoss.Set_CanChangeAttack(true);
		_theBoss.Set_Cooldown(1);
		numberBullet = 12;
		posTarget = false;
	}

}

void IntelligenceAttackParcours(Boss& _theBoss)
{
	int random = 9 + rand() % 4;

	if (random == _theBoss.Get_CurrentAttack() || (random == BouncingBall && bouncing.Get_CanDisplay()) || (random == SlidingBall && slidingBallVector.size() > 0))
	{
		IntelligenceAttackParcours(_theBoss);
	}
	else
	{
		_theBoss.Set_CurrentAttack((BossAttack)random);
	}
	_theBoss.Set_CanChangeAttack(false);
}

void UpdateBossParoursAttack(float _dt, Boss& _theBoss, PlatformerData& _platformerData)
{
	if (!_theBoss.Get_IsAnimation() && _theBoss.Get_Hp() > 0)
	{
		//décrémente le cooldown du boss
		_theBoss.Set_Cooldown(_theBoss.Get_Cooldown() - _dt);

		//Choisis une attaque si le boss ne fait rien
		if (_theBoss.Get_CanChangeAttack() && !_theBoss.Get_IsAttack() && _theBoss.Get_Hp() > 0)
		{
			IntelligenceAttackParcours(_theBoss);
		}

		//Update l'attaque choisis
		if (_theBoss.Get_Cooldown() <= 0 || _theBoss.Get_IsAttack())
		{
			if (_theBoss.Get_CurrentAttack() == Lightning)
			{
				ThunderAttack(_theBoss, _dt, _platformerData);
			}
			else if (_theBoss.Get_CurrentAttack() == Explosion)
			{
				ExplosionAttack(_theBoss, _dt, _platformerData);
			}
			else if (_theBoss.Get_CurrentAttack() == BouncingBall)
			{
				BouncingBallAttack(_theBoss, _dt, _platformerData);
			}
			else if (_theBoss.Get_CurrentAttack() == SlidingBall)
			{
				SlidingBallAttack(_theBoss, _dt, _platformerData);
			}
			else if (_theBoss.Get_CurrentAttack() == ChangePhase)
			{
				ResetWorld();
			}
		}
	}
}

void UpdateBossDamageParcours(Boss& _theBoss, float _dt, PlatformerData& _platformerData)
{
	sf::Vector2f BossSize = { (float)_theBoss.Get_Sprite().getTexture()->getSize().x , (float)_theBoss.Get_Sprite().getTexture()->getSize().y };
	static sf::Clock invincibility;

	if (_platformerData.players.dashing)
	{
		if (_platformerData.players.GetPosition().x > _theBoss.Get_Pos().x - BossSize.x / 2 && _platformerData.players.GetPosition().x < _theBoss.Get_Pos().x + BossSize.x / 2 && _platformerData.players.GetPosition().y > _theBoss.Get_Pos().y - BossSize.y / 2 && _platformerData.players.GetPosition().y < _theBoss.Get_Pos().y + BossSize.y / 2)
		{
			if (invincibility.getElapsedTime().asSeconds() >= 2)
			{
				_theBoss.RestartTouchClock();
				_theBoss.DecreaseHp(50);
				invincibility.restart();
			}
		}
	}
}

///////////////////////////////////////////// Draw Part /////////////////////////////////////////////



////////////////////////////////////////// FONCTION SACREE ////////////////////////////////////////// 

void LoadParcoursBoss()
{
	warning.Load();
	bouncing.Load();
	explosionHitBox.Load();
}

void UpdateParcoursBoss(float _dt, PlatformerData& _platformerData, sf::RenderWindow& _window, GameState& _gameState, bool& _transition, float _noirAlpha, ControlsData*& m_controls, Boss& _theBoss, Player& _player)
{
	UpdatePlatformer(_dt, _platformerData, _window, _gameState, _transition, _noirAlpha, m_controls, _player);
	BossMove(_dt, _theBoss, _platformerData);
	UpdateBossParoursAttack(_dt, _theBoss, _platformerData);
	warning.Update(_dt, _platformerData);
	bouncing.Update(_dt, _platformerData, _theBoss);

	for (int i = 0; i < slidingBallVector.size(); i++)
	{
		slidingBallVector[i].Update(_dt, _platformerData, _theBoss);
	}

	for (int i = 0; i < slidingBallVector.size(); i++)
	{
		if (!slidingBallVector[i].Get_CanDisplay() || slidingBallVector[i].Get_IsTouch())
		{
			slidingBallVector.erase(slidingBallVector.begin() + i);
		}
	}
	UpdateBossDamageParcours(_theBoss, _dt, _platformerData);

}

void DisplayParcoursBoss(sf::RenderWindow& _window, PlatformerData& _platformerData, Boss& _theBoss)
{
	DrawPlatformer(_platformerData, _window);
	explosionHitBox.Display(_window);
	warning.Display(_window);
	thunder.Display(_window);
	bouncing.Display(_window);
	for (int i = 0; i < slidingBallVector.size(); i++)
	{
		slidingBallVector[i].Display(_window);
	}

	Get_HpText().setPosition((sf::Vector2f)_window.mapPixelToCoords({ 200 , 75 }));
	Get_PlayerHead().setPosition((sf::Vector2f)_window.mapPixelToCoords({ 100 , 75 }));

	_window.draw(Get_HpText());
	_window.draw(Get_PlayerHead());

	_theBoss.DisplayHealInfo(_window);
}

std::vector <BallSliding>& Get_SlidingVector()
{
	return slidingBallVector;
}