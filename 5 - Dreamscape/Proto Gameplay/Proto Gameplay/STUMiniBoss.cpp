#include "STUMiniBoss.hpp"
#include "STUEntities.hpp"
#include "ShootThemUp.hpp"
#include "STUScore.hpp"
#include "Altar.h"

WaveManager& WaveManagerBoss = GetWaveManager();
STUGameState& GameStateBoss = GetSTUGameState();
ShootManager& shootManagerInBoss = GetEnnemiShootManager();
ParticuleManager& PmBoss = GetParticuleManager();
STUPlayer& PlayerInBoss = GetPlayer();
STUScore& ScoreInBoss = GetScoreManager();

sf::FloatRect rectLaser;

void STUMiniBoss::Load(void)
{
	HP = MAX_STU_MINI_BOSS_HP;
	pos = { SCREEN_WIDTH / 2, 0 - (float)HeadSprite.getTexture()->getSize().y * 3 };

	hands[0].sprite = AnimHands[0][currentHeadSprite];
	hands[0].pos = { pos.x + hands[0].sprite.getTexture()->getSize().x * hands[0].scale.x, pos.y };

	hands[1].sprite = AnimHands[1][currentHeadSprite];
	hands[1].pos = { pos.x - hands[1].sprite.getTexture()->getSize().x * hands[1].scale.x, pos.y };

	hands[0].scale = { 4,4 };
	hands[1].scale = { 4,4 };

	hands[0].angle = 0;
	hands[1].angle = 0;

	IntroCoolDown = 3;
	actualAttack = NOTHING_STU_MINI_BOSS;
	actualPhase = ONE;

	bossAlpha = 255;
	isLaserVisible = false;

	relicPos = pos;

	rectLaser.left = 0;
	rectLaser.top = 0;
	rectLaser.height = 0;
	rectLaser.width = LaserSprite[0].getTexture()->getSize().x;

	bufferBossScream.loadFromFile("Assets/Shoot Them Up/Boss/bossScream.ogg");
	bossScream.setBuffer(bufferBossScream);
	bossScream.setLoop(false);

	RewardSTUText[0] = LoadText("Assets/Shoot Them Up/Font/Monocraft.otf", "Good job !",
		40, { SCREEN_WIDTH / 2,2 * (SCREEN_HEIGHT / 3) }, sf::Color::White, true);
	RewardSTUText[0].setOutlineColor(sf::Color::Black);
	RewardSTUText[0].setOutlineThickness(4);

	RewardSTUText[1] = LoadText("Assets/Shoot Them Up/Font/Monocraft.otf", "Return to the lobby to place the relic.",
		40, { SCREEN_WIDTH / 2,2 * (SCREEN_HEIGHT / 3) + (float)RewardSTUText[0].getCharacterSize() }, sf::Color::White, true);
	RewardSTUText[1].setOutlineColor(sf::Color::Black);
	RewardSTUText[1].setOutlineThickness(4);
}

void STUMiniBoss::SpawnEnnemi(void)
{
	float timer = cooldownAttack.getElapsedTime().asSeconds();

	if (timer > 1 && ennemyPos.size() == 0)
	{
		for (int k = 0; k < 3; k++)
		{
			sf::Vector2f tempPos;
			tempPos.x = 360 + ((float)(rand() % RAND_MAX) / RAND_MAX) * 1200;
			tempPos.y = ((float)(rand() % RAND_MAX) / RAND_MAX) * SCREEN_HEIGHT / 2;

			ennemyPos.push_back(tempPos);

			PmBoss.AddSpowner(tempPos);
		}
	}
	if (timer > 2 && ennemyPos.size() != 0)
	{
		for (int k = 0; k < 3; k++)
		{
			WaveManagerBoss.AddEnnemie((STUEnnemiType)(rand() % 3), ennemyPos[k], 0);
		}

		ennemyPos.clear();
		cooldownAttack.restart();
	}
}

void STUMiniBoss::HandAttack(float _dt)
{
	float timer = cooldownAttack.getElapsedTime().asSeconds();
	static sf::Clock resizeTimer;
	static sf::Clock downTimer;
	static sf::Clock upTimer;

	if (timer > 0 && timer <= 2)
	{
		if (HandGrowing.getStatus() != sf::Sound::Playing)
			HandGrowing.play();

		//MAINS QUI GROSSISENT
		for (int k = 0; k < 2; k++)
		{
			hands[k].scale.x = 4 + Easing::easeInOutExpo(timer, 0, 4, 2);
			hands[k].scale.y = 4 + Easing::easeInOutExpo(timer, 0, 4, 2);

			k == 0 ?
				hands[k].pos.x = pos.x + hands[k].sprite.getTexture()->getSize().x * hands[k].scale.x :
				hands[k].pos.x = pos.x - hands[k].sprite.getTexture()->getSize().x * hands[k].scale.x;

			hands[k].pos.y = pos.y;
		}

		downTimer.restart();
	}
	else if (timer < 3)
	{

		if (actualPhase == ONE)
		{
			for (int k = 0; k < 2; k++)
			{
				hands[k].pos.y = pos.y + Easing::easeInExpo(downTimer.getElapsedTime().asSeconds(), 0, SCREEN_HEIGHT - pos.y, 1);

				//Collision//
				sf::Vector2f handPlayer = CreaMaths::CreateVector(PlayerInBoss.GetPos(), hands[k].pos);
				float dist = CreaMaths::GetDistance(handPlayer);
				float handHitBox = (hands[k].sprite.getTexture()->getSize().x * hands[k].scale.x) / 2;

				if (dist <= STU_PLAYER_HITBOX + handHitBox && PlayerInBoss.GetInvicibilityClock().getElapsedTime().asSeconds() > STU_PLAYER_INVICIBILITY)
				{
					PlayerInBoss.SetHp(PlayerInBoss.GetHp() - 1);
					PlayerInBoss.RestartClock();
				}
			}
		}
		else
		{
			for (int k = 0; k < 2; k++)
			{
				if (downTimer.getElapsedTime().asSeconds() < 0.5)
				{
					hands[k].pos.y = pos.y + Easing::easeInExpo(downTimer.getElapsedTime().asSeconds(), 0, SCREEN_HEIGHT - pos.y, 0.5);
				}
				else if (downTimer.getElapsedTime().asSeconds() < 0.75)
				{
					if (k == 0)
					{
						hands[k].angle = Easing::linear(downTimer.getElapsedTime().asSeconds(), 0, 90, 0.75);
					}
					else
					{
						hands[k].angle = 0 - Easing::linear(downTimer.getElapsedTime().asSeconds(), 0, 90, 0.75);
					}
				}
				else
				{
					if (k == 0)
					{
						hands[k].pos.x = (pos.x + hands[1].sprite.getTexture()->getSize().x * hands[1].scale.x) - Easing::easeInExpo(downTimer.getElapsedTime().asSeconds(), 0, 300, 1);
					}
					else
					{
						hands[k].pos.x = (pos.x - hands[1].sprite.getTexture()->getSize().x * hands[1].scale.x) + Easing::easeInExpo(downTimer.getElapsedTime().asSeconds(), 0, 300, 1);
					}
				}

				//Collision//
				sf::Vector2f handPlayer = CreaMaths::CreateVector(PlayerInBoss.GetPos(), hands[k].pos);
				float dist = CreaMaths::GetDistance(handPlayer);
				float handHitBox = (hands[k].sprite.getTexture()->getSize().x * hands[k].scale.x) / 2;

				if (dist <= STU_PLAYER_HITBOX + handHitBox && PlayerInBoss.GetInvicibilityClock().getElapsedTime().asSeconds() > STU_PLAYER_INVICIBILITY)
				{
					PlayerInBoss.SetHp(PlayerInBoss.GetHp() - 1);
					PlayerInBoss.RestartClock();
				}
			}
		}

		upTimer.restart();
	}
	else if (timer < 4)
	{
		if (HandSound.getStatus() != sf::Sound::Playing)
		{
			HandSound.play();
			ShakeSTU({ 10,10 }, 0.5);
		}

		if (actualPhase == ONE)
		{
			for (int k = 0; k < 2; k++)
			{
				hands[k].pos.y = SCREEN_HEIGHT - Easing::easeOutCubic(upTimer.getElapsedTime().asSeconds(), 0, SCREEN_HEIGHT - pos.y, 1);
			}
		}
		else
		{
			for (int k = 0; k < 2; k++)
			{
				if (upTimer.getElapsedTime().asSeconds() < 0.5)
				{
					if (k == 0)
					{
						hands[k].pos.x = (pos.x + hands[1].sprite.getTexture()->getSize().x * hands[1].scale.x) - 300 + Easing::easeOutExpo(upTimer.getElapsedTime().asSeconds(), 0, 300, 0.5);
						hands[k].angle = 90 - Easing::linear(upTimer.getElapsedTime().asSeconds(), 0, 90, 0.5);
					}
					else
					{
						hands[k].pos.x = (pos.x - hands[1].sprite.getTexture()->getSize().x * hands[1].scale.x) + 300 - Easing::easeOutExpo(upTimer.getElapsedTime().asSeconds(), 0, 300, 0.5);
						hands[k].angle = -90 + Easing::linear(upTimer.getElapsedTime().asSeconds(), 0, 90, 0.5);
					}
				}
				else
				{
					hands[k].pos.y = SCREEN_HEIGHT - Easing::easeOutCubic(upTimer.getElapsedTime().asSeconds() - 0.5, 0, SCREEN_HEIGHT - pos.y, 0.5);
				}

			}
		}

		resizeTimer.restart();
	}
	else
	{
		if (HandDecrease.getStatus() != sf::Sound::Playing)
			HandDecrease.play();

		for (int k = 0; k < 2; k++)
		{
			if (hands[k].scale.x > scale.x)
			{
				hands[k].scale.x = 8 - Easing::easeInOutExpo(resizeTimer.getElapsedTime().asSeconds(), 0, 4, 1.5);
				hands[k].scale.y = 8 - Easing::easeInOutExpo(resizeTimer.getElapsedTime().asSeconds(), 0, 4, 1.5);
			}

			k == 0 ?
				hands[k].pos.x = pos.x + hands[k].sprite.getTexture()->getSize().x * hands[k].scale.x :
				hands[k].pos.x = pos.x - hands[k].sprite.getTexture()->getSize().x * hands[k].scale.x;

			hands[k].pos.y = pos.y;
			hands[k].aceleration = 1;

			hands[k].angle = 0;
		}
	}
}

bool collisionPointRectangle(sf::Vector2f point, double x1, double y1, double x2, double y2)
{
	return point.x >= x1 && point.x <= x2 && point.y >= y1 && point.y <= y2;
}

void STUMiniBoss::LaserAttack(float _dt)
{
	static int sizeX = LaserSprite[0].getTexture()->getSize().x * 3;
	static float X = pos.x - sizeX / 2;

	if (isLaserVisible && alphaLaser > 140)
	{
		if (collisionPointRectangle(PlayerInBoss.GetPos(), X, pos.y, X + sizeX, pos.y + rectLaser.height * 3))//changer le reste de la hitbox
		{
			if (PlayerInBoss.GetInvicibilityClock().getElapsedTime().asSeconds() > STU_PLAYER_INVICIBILITY * 4)
			{
				PlayerInBoss.SetHp(PlayerInBoss.GetHp() - 1);
				PlayerInBoss.RestartClock();
			}
		}
	}
}

void STUMiniBoss::ChangeForm(void)
{
	if (cooldownForm.getElapsedTime().asSeconds() > 5)
	{
		//anti spam same attack//
		STUMiniBossAttack lastAttack = actualAttack;
		while (actualAttack == lastAttack)
		{
			actualAttack = (STUMiniBossAttack)((rand() % 3) + 1);
		}

		isLaserVisible = false;
		cooldownForm.restart();
		cooldownAttack.restart();
	}

	if (HP <= MAX_STU_MINI_BOSS_HP / 2 && (int)cooldownForm.getElapsedTime().asSeconds() == 0)
	{
		actualPhase = TWO;
	}
}

void STUMiniBoss::UpdateAttacks(float _dt)
{
	//Attend le debut de la vague
	if (IntroCoolDown <= 0)
	{
		if (actualAttack == NOTHING_STU_MINI_BOSS)
		{
			cooldownForm.restart();
			cooldownAttack.restart();

			actualAttack = (STUMiniBossAttack)((rand() % 3) +1);
		}
	}
	else
	{
		cooldownForm.restart();
		cooldownAttack.restart();
		IntroCoolDown -= _dt;
	}

	//Attacks//
	if (actualAttack != STU_MINI_BOSS_DEAD)
		ChangeForm();

	switch (actualAttack)
	{
	case NOTHING_STU_MINI_BOSS:
		pos.y += 150 * _dt;

		hands[0].pos.y = pos.y;
		hands[1].pos.y = pos.y;
		break;
	case ENNEMI_SPAWN:
		SpawnEnnemi();
		break;
	case HAND:
		HandAttack(_dt);
		break;
	case LASER:
		LaserAttack(_dt);
		break;
	default:
		break;
	}
}

void STUMiniBoss::UpdateAnimPhase1(float _dt)
{
	//head//
	animHeadTimer < 6 - 0.5 ? animHeadTimer += _dt * 6 : animHeadTimer -= 6 - 0.5;
	currentHeadSprite = (int)animHeadTimer;
	HeadSprite = AnimHeadOne[currentHeadSprite];

	//hands//
	for (int k = 0; k < 2; k++)
	{
		hands[k].animeHandTimer < 6 - 1 ? hands[k].animeHandTimer += _dt * 6 : hands[k].animeHandTimer -= 6 - 1;
		hands[k].currentHandSprite = (int)hands[k].animeHandTimer;

		hands[k].sprite = AnimHands[k][hands[k].currentHandSprite];
	}
}

void STUMiniBoss::UpdateAnimPhase2(float _dt)
{
	//head//
	animHeadTimer < 4 - 0.5 ? animHeadTimer += _dt * 4 : animHeadTimer -= 4 - 0.5;
	currentHeadSprite = (int)animHeadTimer;
	HeadSprite = AnimHeadTwo[currentHeadSprite];

	//hands//
	for (int k = 0; k < 2; k++)
	{
		hands[k].animeHandTimer < 6 - 1 ? hands[k].animeHandTimer += _dt * 6 : hands[k].animeHandTimer -= 6 - 1;
		hands[k].currentHandSprite = (int)hands[k].animeHandTimer;

		hands[k].sprite = AnimHands[k][hands[k].currentHandSprite];
	}
}

void STUMiniBoss::UpdateDeadAnim(float _dt)
{
	animHeadTimer < 11 - 0.5 ? animHeadTimer += _dt * 11 : animHeadTimer = 10;
	currentHeadSprite = (int)animHeadTimer;
	HeadSprite = DeadAnim[currentHeadSprite];
}

float easeInCircExp(double t, double b, double c, double d)
{
	t /= d;
	return c * exp(-3 * (1 - t)) + b;
}

void STUMiniBoss::UpdateAnimLaser(float _dt)
{
	static sf::Clock currentTime1;

	if (!isLaserVisible)
	{
		animHeadTimer = 0;
		rectLaser.height = 0;

		//anim sprites
		currentChargeLaserAnim = 0;
		currentLaserSprite = 0;

		chargeScale = 0;
		currentTime1.restart();
		alphaLaser = 255;
		isLaserVisible = true;
		
		LaserSound.play();
	}
	else
	{
		//head//
		animHeadTimer < 8 - 0.5 ? animHeadTimer += _dt * 6 : animHeadTimer -= 8 - 0.5;
		currentHeadSprite = (int)animHeadTimer;
		HeadSprite = AnimHeadLaser[currentHeadSprite];


		if (currentTime1.getElapsedTime().asSeconds()>= 3.75)
		{
			if (rectLaser.height < 300)
			{
				rectLaser.height = 70 + Easing::easeInSine(currentTime1.getElapsedTime().asSeconds() - 3.75, 0, 230, 0.25);
			}
			
			ShakeSTU({ 5,5 }, 0.01);
			currentLaserSprite < MAX_LASER_SPRITE - 0.5 ? currentLaserSprite += _dt * 16 : currentLaserSprite -= MAX_LASER_SPRITE - 0.5;

			currentChargeLaserAnim = 0;
			chargeScale = 0;
		}
		else
		{
			currentChargeLaserAnim < 12 - 0.5 ? currentChargeLaserAnim += _dt * 8: currentChargeLaserAnim -= 12 - 0.5;//8

			chargeScale = Easing::linear(currentTime1.getElapsedTime().asSeconds(), 0, 3, 3.75);
		}
	}
	LaserSprite[(int)currentLaserSprite].setTextureRect((sf::IntRect)rectLaser);

	if (currentTime1.getElapsedTime().asSeconds() >= 4)
	{
		alphaLaser = 255 - Easing::easeInCubic(currentTime1.getElapsedTime().asSeconds()-4, 0, 255, 1);

		alphaLaser < 0 ? alphaLaser = 0 : alphaLaser = alphaLaser;
	}
}

bool STUMiniBoss::Collide(sf::Vector2f _point, int _damage)
{
	static sf::Vector2f headSize = { AnimHeadOne[0].getTexture()->getSize().x * scale.x,AnimHeadOne[0].getTexture()->getSize().y * scale.y };
	static sf::Vector2f handSize = { AnimHands[0][0].getTexture()->getSize().x * hands[0].scale.x, AnimHands[0][0].getTexture()->getSize().y * hands[0].scale.y };

	if (actualAttack != NOTHING_STU_MINI_BOSS && actualAttack != STU_MINI_BOSS_DEAD)
	{
		if (_point.x > pos.x - headSize.x / 2 && _point.x < pos.x + headSize.x / 2 && _point.y > pos.y - headSize.y / 2 && _point.y < pos.y + headSize.y / 2)
		{
			invincibility.restart();
			HP -= _damage;
			return true;
		}

		for (int k = 0; k < 2; k++)
		{
			if (_point.x > hands[k].pos.x - handSize.x / 2 && _point.x <  hands[k].pos.x + handSize.x / 2 && _point.y >  hands[k].pos.y - handSize.y / 2 && _point.y < hands[k].pos.y + handSize.y / 2)
			{
				invincibility.restart();
				HP -= _damage;
				return true;
			}
		}
	}

	return false;
}

void STUMiniBoss::UpdateDead(float _dt, GameState& _gameState, Player& _player, bool& _transition, float& _noirAlpha)
{
	playerGetItem = false;
	static bool bossExplosed = false;
	static sf::Clock alphaClock;
	static sf::Clock relicClock;
	static float handSize = hands[0].sprite.getTexture()->getSize().y*hands[0].scale.x;

	if (deadTimer.getElapsedTime().asSeconds() < 3)
	{
		pos.x = deadPos.x + (-3 + rand() % 6);
		pos.y = deadPos.y + (-3 + rand() % 6);

		for (int k = 0; k < 2; k++)
		{
			hands[k].pos.y = deadPos.y + Easing::easeOutBounce(deadTimer.getElapsedTime().asSeconds(), 0, SCREEN_HEIGHT - deadPos.y - handSize/2, 3);
		}

		alphaClock.restart();
		bossExplosed = false;
	}
	else
	{
		if (!bossExplosed)
		{
			pos = deadPos;
			Pm.BossExplosion((sf::Vector2i)pos, 500, sf::Color(96, 69, 213));
			bossExplosed = true;
		}
		
		if (bossAlpha > 1)
		{
			bossAlpha = 255 - Easing::easeOutQuart(alphaClock.getElapsedTime().asSeconds(), 0, 255, 4);
			relicClock.restart();
		}
		else
		{
			bossAlpha = 0;
		}
	}

	if (bossAlpha <= 5)
	{
		if (relicPos.y < SCREEN_HEIGHT / 2)
		{
			relicPos.y = pos.y + Easing::easeInOutBack(relicClock.getElapsedTime().asSeconds(), 0, SCREEN_HEIGHT / 2 - pos.y, 2);
		}
		else
		{
			playerGetItem = true;
		}
	}
	else
	{
		relicPos = pos;
		relicClock.restart();
	}

#pragma region transition
	// Boucle pour parcourir toutes les touches du clavier
	for (int key = 0; key < sf::Keyboard::KeyCount; ++key)
	{
		// Vérifie si la touche est enfoncée
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key)))
		{
			if (playerGetItem)
			{
				_transition = true;
			}
			break;
		}
	}
	for (int k = 0; k < 11; k++)
	{
		if (sf::Joystick::isButtonPressed(0, k))
		{
			if (playerGetItem)
			{
				_transition = true;
			}
			break;
		}
	}

	if (_noirAlpha >= 254)
	{
		ScoreInBoss.SaveHighScore();
		_gameState = LOBBY;
		shootManagerInBoss.Vector().clear();
		GetParticuleManager().GetVector().clear();
		WaveManagerBoss.SetCurrentWave(0);
		_player.Set_IsPurpleTotem(true);
		LoadSTU();
		Load();
		playerGetItem = false;
		SaveGame(_player);
		_transition = false;
	}
#pragma endregion
}

void STUMiniBoss::Update(float _dt, GameState& _gameState, Player& _player, bool& _transition, float& _noirAlpha)
{
	UpdateAttacks(_dt);

	if (actualAttack != LASER)
	{
		if (actualAttack != STU_MINI_BOSS_DEAD)
		{
			actualPhase == ONE ? UpdateAnimPhase1(_dt) : UpdateAnimPhase2(_dt);
		}
		else
		{
			UpdateDeadAnim(_dt);
		}
	}
	else
	{
		UpdateAnimLaser(_dt);
	}

	for (int k = 0; k < 2; k++)
	{
		rotateCircle[k] += (30 - (60 * k)) * _dt;
	}


	if (HP <= 0 && actualAttack != STU_MINI_BOSS_DEAD && actualAttack != HAND)
	{
		HP = 0;
		deadPos = pos;
		deadTimer.restart();
		actualAttack = STU_MINI_BOSS_DEAD;
		bossScream.play();

		WaveManagerBoss.GetWaveVector().clear();
	}

	if (actualAttack == STU_MINI_BOSS_DEAD)
	{

		UpdateDead(_dt, _gameState, _player, _transition, _noirAlpha);
		
	}

	Pm.UpdateParticule(_dt);
}

void STUMiniBoss::Display(sf::RenderWindow& _window)
{
	Pm.DrawParticule(_window);

	static sf::Color colorHit;
	invincibility.getElapsedTime().asSeconds() < 0.2 ? colorHit = sf::Color(255, 100, 100, bossAlpha) : colorHit = sf::Color(255, 255, 255, bossAlpha);

	if (HP <= 0)
		BlitSprite(RelicSprite, relicPos, _window, { 3,3 });

	BlitSprite(HeadSprite, pos, _window, scale, 0, colorHit);
	for (int k = 0; k < 2; k++)
	{
		BlitSprite(HandCircle, hands[k].pos, _window, hands[k].scale, rotateCircle[k], colorHit);
		BlitSprite(hands[k].sprite, hands[k].pos, _window, hands[k].scale, hands[k].angle, colorHit);
	}

	if (isLaserVisible && HP > 0)
	{
		BlitSprite(AnimLaserCharge[(int)currentChargeLaserAnim], { pos.x - 1, pos.y + 100 }, _window, { chargeScale,chargeScale }, 0, sf::Color(255, 255, 255, alphaLaser));

		BlitSprite(LaserSprite[(int)currentLaserSprite], {pos.x - (LaserSprite[0].getTexture()->getSize().x * 3) / 2 - 1, pos.y}, _window, {3,3}, 0, sf::Color(255, 255, 255, alphaLaser));
	}

	if (playerGetItem)
	{
		for (int k = 0; k < 2; k++)
		{
			_window.draw(RewardSTUText[k]);
		}
	}
}