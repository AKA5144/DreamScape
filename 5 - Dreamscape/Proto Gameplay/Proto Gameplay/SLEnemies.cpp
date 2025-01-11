#include "SLEnemies.h"

void SLEnemy::Create(sf::Vector2f _pos, EnemyType _type)
{
	m_pos = _pos;
	m_type = _type;
	m_state = WANDERING;
	m_dir = DOWN;
	m_cooldown = 0;
	m_wanderingTimer = 0;

	switch (m_type)
	{
	case SLEnemy::ROSCASS:
		m_hp = 150;
		m_maxHP = m_hp;
		m_attackRange = 125;
		m_aggroRange = 200;
		m_visionAngle = 180;
		m_speed = 0;
		m_sprite = LoadSprite("Assets/Souls/Enemies/Roscass/Wandering/Down/1.png", true);
		break;

	case SLEnemy::FALKYN:
		m_hp = 200;
		m_maxHP = m_hp;
		m_attackRange = 40;
		m_aggroRange = 200;
		m_visionAngle = 90;
		m_speed = 200 / 2.f;
		m_sprite = LoadSprite("Assets/Souls/Enemies/Falkyn/Wandering/Down/0.png", true);
		break;
	}

	m_hitbox.width = 32;
	m_hitbox.height = 32;

	m_healthBar = ProportionalBar::Create(sf::Vector2f(m_pos.x, m_pos.y - m_hitbox.height / 4.f * 3), sf::Vector2f(32, 2), sf::Color::Green, sf::Color::Red, sf::Color(0, 0, 0, 64), 1, true);
}

void SLEnemy::Update(float _dt)
{
	UpdateInvincibility(_dt);
	UpdateCooldown(_dt);
	UpdateStates(_dt);

	UpdateDirection();

	m_fVector.x = (m_dir == RIGHT) - (m_dir == LEFT);
	m_fVector.y = (m_dir == DOWN) - (m_dir == UP);
	CreaMaths::ClampLength(m_fVector, 1);

	UpdateStateMachine(_dt);
	UpdateAttacks(_dt);

	m_hitbox.left = m_pos.x - m_hitbox.width / 2.f;
	m_hitbox.top = m_pos.y - m_hitbox.height / 2.f - 5 * (m_type == FALKYN);

	m_attackRangeHitbox = sf::FloatRect(m_pos.x - m_attackRange, m_pos.y - m_attackRange, m_attackRange * 2, m_attackRange * 2);

	if (m_hp < 0)
	{
		m_hp = 0;
	}

	sf::Vector2f HPBarPos(m_pos.x, m_pos.y - m_hitbox.height / 4.f * 3);
	for (int i = 0; i < 2; i++)
	{
		m_healthBar[i].setPosition(HPBarPos);
	}

	m_healthBar[1].setSize({ m_healthBar[0].getSize().x * (m_hp / (float)m_maxHP), m_healthBar[0].getSize().y });

	UpdateAnimation();
}

void SLEnemy::Display(sf::RenderWindow& _window)
{
	sf::Color enemyColor = sf::Color::White;
	if (m_initialInvincibilityTimer != 0)
	{
		enemyColor = sf::Color(255, 255 - (m_invincibilityTimer / m_initialInvincibilityTimer) * 255, 255 - (m_invincibilityTimer / m_initialInvincibilityTimer) * 255);
	}
	BlitSprite(m_sprite, m_pos, _window, m_sprite.getScale(), m_sprite.getRotation(), enemyColor);

	if (m_hp > 0)
	{
		for (int i = 0; i < 2; i++)
		{
			if (m_hp < m_maxHP)
			{
				_window.draw(m_healthBar[i]);
			}
		}
	}

	for (int i = 0; i < m_attacks.size(); i++)
	{
		_window.draw(m_attacks[i].sprite);
	}
}





void SLEnemy::UpdateStates(float _dt)
{
	switch (m_state)
	{
	case SLEnemy::WANDERING:
	{
		if (m_type == ROSCASS)
		{
			if (CreaMaths::GetSquaredDistance(CreaMaths::CreateVector(m_pos, m_target)) < m_aggroRange * m_aggroRange)
			{
				if (!IsInVector(0, m_GetCollidedTilesType(m_pos, CreaMaths::CreateVector(m_pos, m_target))))
				{
					m_state = GAINED_AGGRO;
					m_sounds.PlaySFX("Roscass_GainedAggro", false, 100, m_pos);
				}
			}
		}
		else if (IsInVisionCone(m_target, m_visionAngle))
		{
			m_state = GAINED_AGGRO;
			m_sounds.PlaySFX("Falkyn_GainedAggro", false, 100, m_pos);
		}
		break;
	}

	case SLEnemy::AGGROING:
	{
		if (m_type == FALKYN)
		{
			if (CreaMaths::GetSquaredDistance(m_velocity) != 0)
				m_sounds.PlaySFX("Walk", false, 50, m_pos);
		}

		if (Collisions::IsCollidingRectPoint(m_attackRangeHitbox, m_target) && m_cooldown == 0)
		{
			m_state = ATTACKING;
		}

		if (CreaMaths::GetSquaredDistance(CreaMaths::CreateVector(m_pos, m_target)) > m_aggroRange * m_aggroRange || IsInVector(0, m_GetCollidedTilesType(m_pos, CreaMaths::CreateVector(m_pos, m_target))))
		{
			m_state = SEARCHING;
		}

		m_searchingTimer = 5.f;
		m_lastKnownTarget = m_target;

		break;
	}

	case SLEnemy::ATTACKING:
	{
		if (m_currentAnimation.HasEnded())
		{
			if (!Collisions::IsCollidingRectPoint(m_attackRangeHitbox, m_target))
			{
				m_state = AGGROING;
			}
			if (m_cooldown > 0)
			{
				m_state = AGGROING;
			}
		}
		break;
	}

	case SLEnemy::SEARCHING:
	{
		m_target = m_lastKnownTarget;

		if (m_type == FALKYN && CreaMaths::GetSquaredDistance(CreaMaths::CreateVector(m_pos, m_target)) >= 5.f * 5.f)
		{
			m_sounds.PlaySFX("Walk", false, 50, m_pos);
		}

		if (IsInVisionCone(m_playerPos, m_visionAngle))
		{
			m_state = AGGROING;
		}
		else
		{
			m_searchingTimer -= _dt;
			if (m_searchingTimer <= 0)
			{
				m_state = LOST_AGGRO;

				m_type == FALKYN ? m_sounds.PlaySFX("Falkyn_LostAggro", false, 100, m_pos) : m_sounds.PlaySFX("Roscass_LostAggro", false, 100, m_pos);
			}
		}
		break;
	}

	case SLEnemy::LOST_AGGRO:
	{
		if (m_currentAnimation.HasEnded())
		{
			m_state = WANDERING;
			m_visionAngle *= 1 / 1.5f;
			m_aggroRange -= 70;
		}
		break;
	}

	case SLEnemy::GAINED_AGGRO:
	{
		if (m_currentAnimation.HasEnded())
		{
			m_state = AGGROING;
			m_visionAngle *= 1.5f;
			m_aggroRange += 70;
		}
		break;
	}

	default:
		break;
	}
}

void SLEnemy::UpdateStateMachine(float _dt)
{
	if (m_state != WANDERING && m_state != LOST_AGGRO)
	{
		m_fVector = CreaMaths::CreateVector(m_pos, m_target);
		CreaMaths::ClampLength(m_fVector, 1);
	}

	switch (m_state)
	{
	case SLEnemy::WANDERING:
	{
		m_wanderingTimer += _dt;

		if (m_wanderingTimer >= 1.f)
		{
			Direction nextDir = m_dir;

			if (m_dir == RIGHT) nextDir = DOWN;
			if (m_dir == DOWN) nextDir = LEFT;
			if (m_dir == LEFT) nextDir = UP;
			if (m_dir == UP) nextDir = RIGHT;

			m_dir = nextDir;
			m_wanderingTimer -= 1.f;
		}
		break;
	}

	case SLEnemy::GAINED_AGGRO:
	{
		break;
	}

	case SLEnemy::AGGROING:
	{
		if (!Collisions::IsCollidingRectPoint(m_attackRangeHitbox, m_target))
		{
			m_velocity = m_fVector * m_speed * _dt;

			m_pos += m_velocity;
		}
		break;
	}

	case SLEnemy::ATTACKING:
	{
		switch (m_type)
		{
		case SLEnemy::ROSCASS:
			CreateAttack(TRIPLE_SHOT);
			break;

		case SLEnemy::FALKYN:
			CreateAttack(DEFAULT);
			break;
		}
		break;
	}

	case SLEnemy::SEARCHING:
	{
		m_velocity = m_fVector * m_speed * 0.75f * _dt;

		if (CreaMaths::GetSquaredLength(CreaMaths::CreateVector(m_pos, m_target)) <= 5.f * 5.f)
		{
			m_velocity = sf::Vector2f(0, 0);
		}

		m_pos += m_velocity;
		break;
	}

	case SLEnemy::LOST_AGGRO:
	{
		m_wanderingTimer = 0;
		break;
	}

	default:
		break;
	}
}

void SLEnemy::CreateAttack(int _type)
{
	switch (m_type)
	{
	case SLEnemy::ROSCASS:
	{
		if (_type == TRIPLE_SHOT)
		{
			if (m_currentAnimation.GetCurrentFrameType() == AnimationManager::ACTIVE)
			{
				if (!m_once)
				{
					m_once = true;

					m_sounds.PlaySFX("Roscass_Attack", false, 75, m_pos);

					sf::Vector2f posTargetVec = CreaMaths::CreateVector(m_pos, m_lastKnownTarget);
					CreaMaths::ClampLength(posTargetVec, 1);
					Attack tempAttack;

					tempAttack.sprite = LoadSprite("Assets/Souls/Enemies/Roscass/Attacking/Projectile.png", true);
					tempAttack.pos = m_pos;
					tempAttack.dirVec = posTargetVec;
					tempAttack.hitbox = { m_pos.x, m_pos.y, 8, 8 };
					tempAttack.speed = 500.f / 2;
					tempAttack.damage = 5;

					if (m_it < 2)
					{
						m_cooldown = 0.3f;
						m_it++;
					}
					else
					{
						m_cooldown = 3.f;
						m_it = 0;
					}

					m_attacks.push_back(tempAttack);
				}
			}
			else if (m_currentAnimation.GetCurrentFrameType() == AnimationManager::RECOVERY)
			{
				m_once = false;
			}
		}
		break;
	}

	case SLEnemy::FALKYN:
	{
		if (_type == DEFAULT)
		{
			if (m_currentAnimation.GetCurrentFrameType() == AnimationManager::ACTIVE)
			{
				if (!m_once)
				{
					m_once = true;
					m_sounds.PlaySFX("Falkyn_Attack", false, 100, m_pos);

					Attack tempAttack;

					tempAttack.pos = m_pos;
					tempAttack.hitbox = { m_pos.x, m_pos.y, 8, 8 };
					tempAttack.speed = 500.f / 2;
					tempAttack.damage = 10;

					tempAttack.hitbox.width = m_hitbox.width;
					tempAttack.hitbox.height = m_hitbox.width;

					tempAttack.hitbox.left = m_hitbox.left + (m_dir == RIGHT) * m_hitbox.width - (m_dir == LEFT) * m_hitbox.width;
					tempAttack.hitbox.top = m_hitbox.top + (m_dir == DOWN) * m_hitbox.height - (m_dir == UP) * m_hitbox.width;

					if (m_dir == UP || m_dir == DOWN)
					{
						tempAttack.hitbox.left -= tempAttack.hitbox.width / 2.f - m_hitbox.width / 2.f;
					}
					if (m_dir == LEFT || m_dir == RIGHT)
					{
						tempAttack.hitbox.top -= tempAttack.hitbox.height / 2.f - m_hitbox.height / 2.f;
					}

					m_cooldown = 1.f;

					m_attacks.push_back(tempAttack);
				}
			}
			else if (m_currentAnimation.GetCurrentFrameType() == AnimationManager::RECOVERY)
			{
				m_once = false;
			}
		}
		break;
	}
	}
}

void SLEnemy::UpdateAttacks(float _dt)
{
	for (int i = 0; i < m_attacks.size(); i++)
	{
		switch (m_type)
		{
		case SLEnemy::ROSCASS:
			m_attacks[i].pos += m_attacks[i].dirVec * m_attacks[i].speed * _dt;

			m_attacks[i].sprite.setPosition(m_attacks[i].pos);
			m_attacks[i].hitbox.left = m_attacks[i].pos.x - m_attacks[i].hitbox.width / 2.f;
			m_attacks[i].hitbox.top = m_attacks[i].pos.y - m_attacks[i].hitbox.height / 2.f;

			if (!m_attackRangeHitbox.contains(m_attacks[i].pos))
			{
				m_attacks.erase(m_attacks.begin() + i);
			}
			break;

		case SLEnemy::FALKYN:

			// Voir commentaires de SLPlayer.cpp, fonction UpdateAttacks() case AttackType::DEFAULT (sert à coller l'attaque de l'ennemi à sa hitbox même s'il se déplace)
			m_attacks[i].hitbox.left = m_hitbox.left + (m_dir == RIGHT) * m_hitbox.width - (m_dir == LEFT) * m_attacks[i].hitbox.width;
			m_attacks[i].hitbox.top = m_hitbox.top + (m_dir == DOWN) * m_hitbox.height - (m_dir == UP) * m_attacks[i].hitbox.height;

			if (m_dir == UP || m_dir == DOWN)
			{
				m_attacks[i].hitbox.left -= m_attacks[i].hitbox.width / 2.f - m_hitbox.width / 2.f;
			}
			if (m_dir == LEFT || m_dir == RIGHT)
			{
				m_attacks[i].hitbox.top -= m_attacks[i].hitbox.height / 2.f - m_hitbox.height / 2.f;
			}

			if (m_state != ATTACKING)
			{
				m_attacks.erase(m_attacks.begin() + i);
			}
			break;
		default:
			break;
		}
	}
}

void SLEnemy::UpdateDirection()
{
	if (m_state == SEARCHING || m_state == AGGROING)
	{
		float angle = CreaMaths::RadiansToDegrees(atan2f(m_fVector.y, m_fVector.x));

		if (m_type == ROSCASS && m_currentAnimation.HasEnded())
		{
			if (CreaMaths::IsInBetween(angle, -45, 45))
			{
				m_dir = RIGHT;
			}
			else if (CreaMaths::IsInBetween(angle, 45, 135))
			{
				m_dir = DOWN;
			}
			else if (CreaMaths::IsInBetween(angle, -135, -45))
			{
				m_dir = UP;
			}
			else
			{
				m_dir = LEFT;
			}
		}
		else if (m_type == FALKYN)
		{
			if (CreaMaths::IsInBetween(angle, -45, 45))
			{
				m_dir = RIGHT;
			}
			else if (CreaMaths::IsInBetween(angle, 45, 135))
			{
				m_dir = DOWN;
			}
			else if (CreaMaths::IsInBetween(angle, -135, -45))
			{
				m_dir = UP;
			}
			else
			{
				m_dir = LEFT;
			}
		}
	}
}

void SLEnemy::UpdateAnimation()
{
	float animDuration = 1; // La durée totale de l'animation (le temps nécessaire pour que l'animation se complète)

	switch (m_state)
	{
	case SLEnemy::WANDERING:
		break;
	case SLEnemy::GAINED_AGGRO:
		animDuration = 0.5f;
		break;
	case SLEnemy::AGGROING:
		break;
	case SLEnemy::ATTACKING:
		if (m_type == ROSCASS)
		{
			animDuration = 0.5f;
		}
		break;
	case SLEnemy::SEARCHING:
		break;
	case SLEnemy::LOST_AGGRO:
		animDuration = 0.5f;
		break;
	case SLEnemy::DYING:
		animDuration = 0.8f;
		break;
	default:
		break;
	}

	// Entrer toutes les valeurs possibles de l'enum, impérativement dans l'ordre
	std::string typePath[] = { "Roscass", "Falkyn" };
	std::string statePath[] = { "Wandering", "GainedAggro", "Aggroing", "Attacking", "Aggroing", "LostAggro", "Dying" };
	std::string dirPath[] = { "Up", "Down", "Left", "Right" };

	int state = m_state;

	if (CreaMaths::GetSquaredDistance(m_velocity) == 0.f && m_type == FALKYN && m_currentAnimation.HasEnded())
		state = WANDERING;

	std::string path = "Assets/Souls/Enemies/" + typePath[m_type] + "/" + statePath[state] + "/" + dirPath[m_dir] + "/";

	m_currentAnimation.PlayAnimation(path, animDuration);

	if (!m_currentAnimation.HasEnded())
	{
		m_sprite = m_currentAnimation.GetCurrentSprite();
	}
}

bool SLEnemy::IsInVisionCone(sf::Vector2f _pos, float _angle)
{
	sf::Vector2f posTargetVec = CreaMaths::CreateVector(m_pos, _pos);

	float angle = atan2f(posTargetVec.y, posTargetVec.x);
	float fDirAngle = atan2f(m_fVector.y, m_fVector.x);

	angle = CreaMaths::RadiansToDegrees(angle);
	fDirAngle = CreaMaths::RadiansToDegrees(fDirAngle);

	if (CreaMaths::GetSquaredDistance(posTargetVec) > m_aggroRange * m_aggroRange)
	{
		return false;
	}

	if (CreaMaths::GetSquaredDistance(posTargetVec) < m_hitbox.width * m_hitbox.width)
	{
		return true;
	}

	if (IsInVector(0, m_GetCollidedTilesType(m_pos, posTargetVec)) || IsInVector(2, m_GetCollidedTilesType(m_pos, posTargetVec)))
	{
		return false;
	}

	if (fDirAngle + _angle / 2.f > 180 && angle < 0)
	{
		angle += 360;
	}
	else if (fDirAngle - _angle / 2.f < -180 && angle > 0)
	{
		angle -= 360;
	}

	if (!CreaMaths::IsInBetween(angle, fDirAngle - _angle / 2.f, fDirAngle + _angle / 2.f))
	{
		return false;
	}

	return true;
}