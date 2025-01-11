#include "STUPlayer.hpp"
#include "STUEntities.hpp"
#include "CreaMaths.h"
#include "ShootThemUp.hpp"

STUGameState& gameStateInPlayer = GetSTUGameState();
ParticuleManager& FxPlayer = GetParticuleManager();
STUItems& ItemsInPlayer = GetItems();
STUScore& ScoreInPlayer = GetScoreManager();

void STUPlayer::Load(void)
{
	pos.x = SCREEN_WIDTH / 2;
	pos.y = SCREEN_HEIGHT - 200;

	speed = SPEEDMAX;
	HP = 5;
	powerUp = 100;

	hitBox.setRadius(STU_PLAYER_HITBOX);
	hitBox.setOrigin({ STU_PLAYER_HITBOX,STU_PLAYER_HITBOX });
	hitBox.setPosition(pos);
	hitBox.setFillColor(sf::Color(255, 0, 0, 200));

	turretVector.clear();

	Turret turret;

	float angle = -90;
	angle *= 3.14 / 180;

	turret.SetVectorFromPlayer({ (float)(turretDist * cos(angle)), (float)(turretDist * sin(angle)) });

	turret.SetPos(turret.GetPos() + turret.GetVectorFromPlayer());

	turret.SetType(SIMPLE_LINE);
	turret.SetCoolDown(0.2);

	turretVector.push_back(turret);

}

void STUPlayer::Input(float _dt, ControlsData*& m_controls)
{
	if (sf::Keyboard::isKeyPressed(m_controls->keyBinding[KEYUP]))
	{
		pos.y -= speed * _dt;
	}
	else if (sf::Keyboard::isKeyPressed(m_controls->keyBinding[KEYDOWN]))
	{
		pos.y += speed * _dt;
	}

	if (sf::Keyboard::isKeyPressed(m_controls->keyBinding[KEYLEFT]))
	{
		pos.x -= speed * _dt;
	}
	else if (sf::Keyboard::isKeyPressed(m_controls->keyBinding[KEYRIGHT]))
	{
		pos.x += speed * _dt;
	}

	//Manette//
	static sf::Vector2f m_fVector;
	m_fVector.x = sf::Joystick::getAxisPosition(0, sf::Joystick::X) / 100;
	m_fVector.y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y) / 100;

	if (CreaMaths::IsInBetween(m_fVector.x, -0.15, 0.15))
	{
		m_fVector.x = 0;
	}
	if (CreaMaths::IsInBetween(m_fVector.y, -0.15,0.15))
	{
		m_fVector.y = 0;
	}
	pos += CreaMaths::NormalizeVector(m_fVector) * speed * _dt;


	if (sf::Keyboard::isKeyPressed(m_controls->keyBinding[KEYABILITY2]) || sf::Joystick::isButtonPressed(0, (int)m_controls->controllerBinding[0]))
	{
		showHitBox = true;
		speed = 2 * SPEEDMAX / 4;
	}
	else
	{
		showHitBox = false;
		speed = SPEEDMAX;
	}

	if (powerUp >= 100 && (sf::Keyboard::isKeyPressed(m_controls->keyBinding[KEYABILITY1]) || sf::Joystick::isButtonPressed(0, (int)m_controls->controllerBinding[1])))
	{
		FxPlayer.AddParticle({ SCREEN_WIDTH, SCREEN_HEIGHT }, BLACK_HOLE, 500, sf::Color(177, 26, 150));
		powerUp = 0;
		powerUplunched = true;

	}
}

void STUPlayer::Collision(void)
{
	if (pos.x - size.x / 2 < SCREEN_WIDTH / 2 - TAILLE_BG / 2)
	{
		pos.x = SCREEN_WIDTH / 2 - TAILLE_BG / 2 + size.x / 2;
	}

	if (pos.x + size.x / 2 > SCREEN_WIDTH / 2 + TAILLE_BG / 2)
	{
		pos.x = SCREEN_WIDTH / 2 + TAILLE_BG / 2 - size.x / 2;
	}

	if (pos.y - size.y / 2 < 0)
	{
		pos.y = 0 + size.y / 2;
	}

	if (pos.y + size.y / 2 > SCREEN_HEIGHT)
	{
		pos.y = SCREEN_HEIGHT - size.y / 2;
	}
}

void STUPlayer::CollisionItems(void)
{
	for (int k = 0; k < ItemsInPlayer.GetVector().size(); k++)
	{
		if (CreaMaths::GetDistance(CreaMaths::CreateVector(ItemsInPlayer.GetVector()[k].pos, pos)) < STU_PLAYER_HITBOX * 3)
		{
			Turret turret;

			switch (ItemsInPlayer.GetVector()[k].type)
			{
			case SIMPLE_S_ITEM:

				turret.SetType(SIMPLE_LINE);
				turret.SetCoolDown(0.2);
				break;
			case DOUBLE_S_ITEM:

				turret.SetType(DOUBLE_LINE);
				turret.SetCoolDown(0.5);
				break;
			case SIMPLE_W_ITEM:

				turret.SetType(SIMPLE_WAVE);
				turret.SetCoolDown(0.5);
				break;
			case DOUBLE_W_ITEM:

				turret.SetType(DOUBLE_WAVE);
				turret.SetCoolDown(0.8);
				break;
			default:
				break;
			}

			turretVector.push_back(turret);
			for (int k = 0; k < turretVector.size(); k++)
			{
				float angle = k * (360 / turretVector.size());
				angle *= 3.14 / 180;

				turretVector[k].SetSpeedAngle(0.00f);

				turretVector[k].SetVectorFromPlayer({ (float)(turretDist * cos(angle)), (float)(turretDist * sin(angle)) });

				turretVector[k].SetPos(turretVector[k].GetPos() + turretVector[k].GetVectorFromPlayer());

			}

			ItemsInPlayer.GetVector()[k].isAlive = false;
	
			newTurretSound.play();
		}

	}
}

void STUPlayer::UpdateTurrets(float _dt)
{
	bool _rotate = false;

	turretVector.size() > 1 ? _rotate = true : _rotate = false;
	
	for (int k = 0; k < turretVector.size(); k++)
	{
		turretVector[k].Update(pos, _dt, _rotate);
	}
}

void STUPlayer::Update(float _dt, ControlsData*& m_controls)
{
	hitBox.setPosition(pos);
	Input(_dt, m_controls);
	Collision();
	CollisionItems();
	UpdateTurrets(_dt);

	if (FxPlayer.isExplode)
	{
		powerUpOnScreen = true;
		powerUplunched = false;
	}
	else
	{
		powerUpOnScreen = false;
	}

	if (powerUp > 100)
	{
		powerUp = 100;
	}

	currentImage < 3.5 ? currentImage += 5 * _dt : currentImage = 0;

	if (HP <= 0)
	{
		ScoreInPlayer.SaveHighScore();
		gameStateInPlayer = STU_GAME_OVER;
	}
}

void STUPlayer::Display(sf::RenderWindow& _window)
{
	static sf::Color feedBackPlayer;
	invincibility.getElapsedTime().asSeconds() < STU_PLAYER_INVICIBILITY ? feedBackPlayer = sf::Color(255, 25, 25, 255) : feedBackPlayer = sf::Color::White;


	BlitSprite(playerSprite[(int)currentImage], pos, _window, scale, 0, feedBackPlayer);

	if (showHitBox)
	{
		_window.draw(hitBox);
	}

	for (int k = 0; k < turretVector.size(); k++)
	{
		turretVector[k].Display(_window);
	}
}
