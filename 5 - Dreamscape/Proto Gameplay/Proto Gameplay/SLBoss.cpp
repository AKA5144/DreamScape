#include "SLBoss.h"

void SLBoss::Load(SLPlayer* _player)
{
	m_player = _player;

	m_sprite = LoadSprite("Assets/Souls/Boss/Waiting/Down/0.png", true);

	m_hitbox = m_sprite.getGlobalBounds();
	m_bossRoom = { 60 * 32.f, 11 * 32.f, 18 * 32.f, 17 * 32.f };

	m_size = { m_hitbox.width, m_hitbox.height };

	m_dir = DOWN;
	m_state = WAITING;
	m_hp = 1500;
	m_maxHP = m_hp;
	m_reach = 65.f;

	m_healthOutline = LoadSprite("Assets/Souls/HUD/bossHPBar.png", true);
	m_healthBar = ProportionalBar::Create(sf::Vector2f(0, 0), sf::Vector2f(318, 4), sf::Color(182, 23, 17), sf::Color(128, 128, 128, 255), sf::Color(0, 0, 0, 64), 1, true);

	m_stateTimer = 0;
	m_stateTimerLimit = m_limitTimerGenerator(m_gen);

	m_ronceTimer = 0;
	m_ronceTimerLimit = m_limitTimerGenerator(m_gen);

	for (int i = 0; i < 3; i++)
	{
		m_preloadedStageAttackSprites[0][i] = LoadSprite(std::format("Assets/Souls/Boss/StageAttack/Vertical/{}.png", i), false);
		m_preloadedStageAttackSprites[1][i] = LoadSprite(std::format("Assets/Souls/Boss/StageAttack/Horizontal/{}.png", i), false);
	}

	LoadCombos();
}

void SLBoss::Update(float _dt)
{
	if (m_hp > 0)
	{
		m_stateTimer += _dt;
		UpdateInvincibility(_dt);

		m_posTargetVector = CreaMaths::CreateVector(m_pos, m_player->GetPosition());

		if (m_state != ATTACKING && m_state != TP)
		{
			UpdateDirection();
		}

		if (m_hp < m_maxHP / 2.f)
		{
			m_isInPhase2 = true;
		}

		if (m_isInPhase2)
		{
			m_ronceTimer += _dt;

			if (m_ronceTimer > m_ronceTimerLimit && m_stageAttacks.size() == 0)
			{
				m_ronceTimer = 0;
				m_ronceTimerLimit = m_limitTimerGenerator(m_gen);
				CreateStageAttack((Direction)(rand() % 4));
			}

			UpdateStageAttacks(_dt);
		}

		UpdateStateManager(); // Gère le changement de states
		UpdateStates(); // Gère le comportement du boss en fonction de son state

		UpdateMovements(_dt);

		for (int i = 0; i < m_attacks.size(); i++)
		{
			m_attacks[i].hitbox.left += m_velocity.x;
			m_attacks[i].hitbox.top += m_velocity.y;
		}

		UpdateHealthBar();
		UpdateAnimation();
	}
}

void SLBoss::Display(sf::RenderWindow& _window)
{
	if (m_hp > 0)
	{
		for (int i = 0; i < m_attacks.size(); i++)
		{
			if (m_attacks[i].sprite.getTexture() != nullptr)
			{
				_window.draw(m_attacks[i].sprite);
			}
		}

		DisplayStageAttacks(_window);

		sf::Color enemyColor = sf::Color::White;
		if (m_initialInvincibilityTimer != 0)
		{
			enemyColor = sf::Color(255, 255 - (m_invincibilityTimer / m_initialInvincibilityTimer) * 255, 255 - (m_invincibilityTimer / m_initialInvincibilityTimer) * 255);
		}
		m_sprite.setPosition(m_pos);
		m_sprite.setColor(enemyColor);
		_window.draw(m_sprite);

		sf::Color color = sf::Color::White;

		if (GetFrameType() == AnimationManager::INIT) color = sf::Color::Green;
		else if (GetFrameType() == AnimationManager::ACTIVE) color = sf::Color::Red;
		else if (GetFrameType() == AnimationManager::RECOVERY) color = sf::Color::Blue;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

void SLBoss::UpdateDirection()
{
	sf::Vector2f posTargetVector = CreaMaths::CreateVector(m_pos, m_player->GetPosition());
	float angle = CreaMaths::RadiansToDegrees(atan2f(posTargetVector.y, posTargetVector.x));

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

void SLBoss::UpdateAnimation()
{
	float animDuration = 1.f; // La durée totale de l'animation (le temps nécessaire pour que l'animation se complète)

	switch (m_state)
	{
	case SLBoss::WAITING:
		animDuration = 1.f;
		break;

	case SLBoss::RUSHING:
		animDuration = 0.5f;
		break;

	case SLBoss::BAITING:
		break;

	case SLBoss::TP:
		animDuration = 1.5f;
		break;

	case SLBoss::ATTACKING:
		switch (m_lastAttack)
		{
		case SLBoss::SLASH_RIGHT:
			animDuration = 1.5f;
			break;

		case SLBoss::SLASH_LEFT:
			animDuration = 1.5f;
			break;

		case SLBoss::ESTOC:
			animDuration = 0.8f;
			break;

		case SLBoss::BLOOM_CLOSE:
			animDuration = 1.f;
			break;

		case SLBoss::BLOOM_RANGE:
			animDuration = 1.f;
			break;

		case SLBoss::BLOOM_NUKE:
			animDuration = 1.f;
			break;

		case SLBoss::BOMB:
			animDuration = 1.f;
			break;

		case SLBoss::DASH:
			animDuration = 0.4f;
			break;

		case SLBoss::DEEP_ESTOC:
			animDuration = 1.1f;
			break;

		default:
			break;
		}
		break;

	case SLBoss::RECOVERING:
		break;

	case SLBoss::CHASING:
		animDuration = 0.75f;
		break;
	default:
		break;
	}

	// Entrer toutes les valeurs possibles de l'enum, impérativement dans l'ordre
	std::string statePath[NUMBER_OF_STATES] = { "Waiting", "Rushing", "Baiting", "TP", "Attacking", "Recovering", "Chasing" };
	std::string attackPath[NUMBER_OF_ATTACKS] = { "Slash_Right","Slash_Left", "Estoc", "Bloom_Close", "Bloom_Range", "Bloom_Nuke", "Bomb", "Dash", "Deep_Estoc" };
	std::string dirPath[] = { "Up", "Down", "Left", "Right" };

	std::string path;

	if (m_state != ATTACKING)
		path = "Assets/Souls/Boss/" + statePath[m_state] + "/" + dirPath[m_dir] + "/";
	else
		path = "Assets/Souls/Boss/" + statePath[m_state] + "/" + attackPath[m_lastAttack] + "/" + dirPath[m_dir] + "/";

	m_currentAnimation.PlayAnimation(path, animDuration);

	if (!m_currentAnimation.HasEnded())
	{
		m_sprite = m_currentAnimation.GetCurrentSprite();

		for (int i = 0; i < m_attacks.size(); i++)
		{
			if (m_attacks[i].type == BOMB || m_attacks[i].type == BLOOM_RANGE || m_attacks[i].type == BLOOM_NUKE || m_attacks[i].type == BLOOM_CLOSE)
			{
				m_attacks[i].anim.PlayAnimation("Assets/Souls/Boss/Attacking/" + attackPath[m_attacks[i].type] + "/Projectile/", animDuration);
				m_attacks[i].sprite = m_attacks[i].anim.GetCurrentSprite();
				m_attacks[i].sprite.setPosition(m_attacks[i].pos);
			}
		}
	}
}

void SLBoss::UpdateHealthBar()
{
	if (m_hp <= 0) m_hp = 0;

	m_healthBar[1].setSize({ m_healthBar[0].getSize().x * (m_hp / (float)m_maxHP), m_healthBar[0].getSize().y });
}

void SLBoss::DisplayHealthBar(sf::RenderWindow& _window)
{
	sf::View camera = _window.getView();
	sf::Vector2f HPBarPos(camera.getCenter().x, camera.getCenter().y + camera.getSize().y / 2.f - camera.getSize().y / 8.f);

	for (int i = 0; i < 2; i++)
	{
		m_healthBar[i].setPosition(HPBarPos);
		_window.draw(m_healthBar[i]);

		m_healthOutline.setPosition(HPBarPos);
		_window.draw(m_healthOutline);
	}
}

void SLBoss::UpdateStateManager()
{
	if (m_stateTimer > m_stateTimerLimit && m_currentAnimation.HasEnded())
	{
		switch (m_state)
		{
		case SLBoss::WAITING:
		{
			int randState = rand() % 4;
			int randAtk;

			switch (randState)
			{
			case 0:
				randAtk = rand() % 3;
				switch (randAtk)
				{
				case 0:
					CreateAttack(BLOOM_RANGE);
					break;

				case 1:
					CreateAttack(BLOOM_NUKE);
					break;

				case 2:
					CreateAttack(DASH);
					break;
				}
				break;

			case 1:
				SetState(CHASING);
				break;

			case 2:
				SetState(RUSHING);
				break;

			case 3:
				SetState(TP);
				break;
			}
			break;
		}

		case SLBoss::RUSHING:
		{
			CreateAttack(GetRandomAttack());
			break;
		}

		case SLBoss::CHASING:
		{
			int randState = rand() % 2;
			int randAtk;

			switch (randState)
			{
			case 0:
				randAtk = rand() % 3;
				switch (randAtk)
				{
				case 0:
					CreateAttack(BLOOM_RANGE);
					break;

				case 1:
					CreateAttack(BLOOM_NUKE);
					break;

				case 2:
					CreateAttack(DASH);
					break;
				}
				break;

			case 1:
				SetState(RUSHING);
				break;
			}
			break;
		}

		case SLBoss::BAITING:
		{
			CreateAttack(GetRandomAttack());
			break;
		}

		default:
			break;
		}
	}
}

void SLBoss::UpdateStates()
{
	int randState;
	int randAttack;

	switch (m_state)
	{
	case SLBoss::WAITING:
	{
		m_speed = 25.f;
		break;
	}

	case SLBoss::RUSHING:
	{
		m_speed = 300.f;

		if (IsPlayerInRange())
		{
			randState = rand() % 2;
			switch (randState)
			{
			case 0:
				CreateAttack(GetRandomAttack());
				break;

			case 1:
				SetState(BAITING);
				break;
			}
		}
		break;
	}

	case SLBoss::BAITING:
	{
		m_speed = 5.f;
		if (m_hasDodged)
		{
			m_speed = -500.f * (1 - (m_stateTimer / 0.2f));
		}

		if (m_player->GetState() == SLPlayer::ATTACK)
		{
			if (!m_hasDodged)
			{
				m_hasDodged = true;
				m_stateTimer = 0;
			}

		}
		else if (m_player->GetState() == SLPlayer::ROLL)
		{
			CreateAttack(DASH);
		}

		if (m_hasDodged && m_stateTimer > 0.2f)
		{
			m_hasDodged = false;
			CreateAttack(DASH);
		}

		if (CreaMaths::GetSquaredDistance(m_posTargetVector) > (m_reach * 2) * (m_reach * 2) && !m_hasDodged)
		{
			randState = rand() % 2;
			switch (randState)
			{
			case 0:
				randAttack = rand() % 3;
				switch (randAttack)
				{
				case 0:
					CreateAttack(BLOOM_RANGE);
					break;

				case 1:
					CreateAttack(BLOOM_NUKE);
					break;

				case 2:
					CreateAttack(DASH);
					break;
				}
				break;

			case 1:
				SetState(CHASING);
				break;
			}
		}
		break;
	}

	case SLBoss::TP:
	{
		m_speed = 0.f;

		if (m_currentAnimation.GetCurrentFrame() == 7)
		{
			if (!m_hasDodged)
			{
				m_randomRangeX = { m_player->GetPosition().x - 100.f, m_player->GetPosition().x + 100.f };
				m_randomRangeY = { m_player->GetPosition().y - 100.f, m_player->GetPosition().y + 100.f };

				if (m_randomRangeX.x - m_hitbox.width / 2.f < m_bossRoom.left) m_randomRangeX.x = m_bossRoom.left + m_hitbox.width / 2.f;
				if (m_randomRangeX.y + m_hitbox.width / 2.f > m_bossRoom.left + m_bossRoom.width) m_randomRangeX.y = m_bossRoom.left + m_bossRoom.width - m_hitbox.width / 2.f;
				if (m_randomRangeY.x - m_hitbox.height / 2.f < m_bossRoom.top) m_randomRangeY.x = m_bossRoom.top + m_hitbox.height / 2.f;
				if (m_randomRangeY.y + m_hitbox.height / 2.f > m_bossRoom.top + m_bossRoom.height) m_randomRangeY.y = m_bossRoom.top + m_bossRoom.height - m_hitbox.height / 2.f;

				m_randX = std::uniform_real_distribution<float>(m_randomRangeX.x, m_randomRangeX.y);
				m_randY = std::uniform_real_distribution<float>(m_randomRangeY.x, m_randomRangeY.y);

				do
				{
					m_randPos = { m_randX(m_gen), m_randY(m_gen) };
					m_pos = m_randPos;
					m_hitbox.left = m_pos.x - m_hitbox.width / 2.f;
					m_hitbox.top = m_pos.y - m_hitbox.height / 2.f;

				} while (m_player->GetHitbox().intersects(m_hitbox));

				m_hasDodged = true;
			}
		}
		else if (m_currentAnimation.HasEnded())
		{
			m_hasDodged = false;

			randState = rand() % 3;
			switch (randState)
			{
			case 0:
				randAttack = rand() % 3;
				switch (randAttack)
				{
				case 0:
					CreateAttack(BLOOM_RANGE);
					break;
				case 1:
					CreateAttack(BLOOM_NUKE);
					break;
				case 2:
					CreateAttack(DASH);
					break;
				}
				break;

			case 1:
				SetState(CHASING);
				break;

			case 2:
				SetState(RUSHING);
				break;
			}
		}
		break;
	}

	case SLBoss::ATTACKING:
	{
		if (m_lastAttack == DASH)
		{
			m_speed = 500.f;
		}
		else
		{
			m_speed = 0.f;
		}

		UpdateCombo();
		break;
	}

	case SLBoss::RECOVERING:
	{
		m_speed = 0.f;

		break;
	}

	case SLBoss::CHASING:
	{
		m_speed = 100.f;
		if (IsPlayerInRange())
		{
			CreateAttack(GetRandomAttack());
		}
		break;
	}

	default:
		break;
	}
}

void SLBoss::SetState(int _state)
{
	m_stateTimer = 0;
	m_stateTimerLimit = m_limitTimerGenerator(m_gen);
	m_state = (State)_state;
}

void SLBoss::UpdateMovements(float _dt)
{
	m_fVector = m_posTargetVector;
	m_reach = 65.f;

	if (m_state == ATTACKING && m_lastAttack == DASH)
	{
		m_fVector = m_dashDirVec;
		m_reach = 0;
	}

	CreaMaths::ClampLength(m_fVector, 1);

	if (CreaMaths::GetSquaredDistance(m_posTargetVector) > m_reach * m_reach || m_hasDodged)
	{
		m_velocity = m_fVector * m_speed * _dt;
	}
	else
	{
		m_velocity = { 0, 0 };
	}

	m_pos += m_velocity;

	m_hitbox.left = m_pos.x - m_hitbox.width / 2.f;
	m_hitbox.top = m_pos.y - m_hitbox.height / 2.f;
}

int SLBoss::GetRandomAttack()
{
	int random = rand() % NUMBER_OF_ATTACKS;

	return random;
}

void SLBoss::CreateAttack(int _type)
{
	UpdateDirection();
	SetState(ATTACKING);

	m_dashDirVec = m_posTargetVector;
	m_playerHit = false;

	Attack tempAttack;
	tempAttack.type = _type;
	m_lastAttack = (BossAttack)_type;

	for (int i = 0; i < 1 + 2 * (_type == BLOOM_NUKE); i++)
	{
		tempAttack.hitbox = GetAttackHitbox(_type);

		switch (_type)
		{
		case SLBoss::SLASH_RIGHT:
			tempAttack.damage = 5.f;
			break;
		case SLBoss::SLASH_LEFT:
			tempAttack.damage = 5.f;
			break;
		case SLBoss::ESTOC:
			tempAttack.damage = 10.f;
			break;
		case SLBoss::BLOOM_CLOSE:
			tempAttack.damage = 20.f;
			break;
		case SLBoss::BLOOM_RANGE:
			tempAttack.damage = 15.f;
			break;
		case SLBoss::BLOOM_NUKE:
			tempAttack.damage = 5.f;
			break;
		case SLBoss::BOMB:
			tempAttack.damage = 20.f;
			break;
		case SLBoss::DASH:
			tempAttack.damage = 10.f;
			break;
		case SLBoss::DEEP_ESTOC:
			tempAttack.damage = 15.f;
			break;
		default:
			tempAttack.damage = 0;
			break;
		}

		tempAttack.pos = sf::Vector2f(tempAttack.hitbox.left + tempAttack.hitbox.width / 2.f, tempAttack.hitbox.top + tempAttack.hitbox.height / 2.f);

		m_attacks.push_back(tempAttack);
	}
}

void SLBoss::LoadCombos()
{
	// -1 = combo ender
	m_availableAttacks[SLASH_RIGHT] = { SLASH_LEFT, ESTOC, BLOOM_CLOSE, BOMB, DEEP_ESTOC };
	m_availableAttacks[SLASH_LEFT] = { SLASH_RIGHT, ESTOC, BLOOM_CLOSE, BOMB, DEEP_ESTOC };
	m_availableAttacks[ESTOC] = { DEEP_ESTOC, (BossAttack)-1 };
	m_availableAttacks[BLOOM_CLOSE] = { DEEP_ESTOC, (BossAttack)-1 };
	m_availableAttacks[BLOOM_RANGE] = { BOMB, DASH, (BossAttack)-1 };
	m_availableAttacks[BLOOM_NUKE] = { (BossAttack)-1 };
	m_availableAttacks[BOMB] = { (BossAttack)-1 };
	m_availableAttacks[DASH] = { SLASH_LEFT, SLASH_RIGHT, ESTOC, DEEP_ESTOC, BLOOM_RANGE, BLOOM_CLOSE };
	m_availableAttacks[DEEP_ESTOC] = { BOMB, DASH, (BossAttack)-1 };

	m_nextAttack[SLASH_RIGHT] = SLASH_LEFT;
	m_nextAttack[SLASH_LEFT] = SLASH_RIGHT;
	m_nextAttack[ESTOC] = DEEP_ESTOC;
	m_nextAttack[BLOOM_CLOSE] = DASH;
	m_nextAttack[BLOOM_RANGE] = DASH;
	m_nextAttack[BLOOM_NUKE] = (BossAttack)-1;
	m_nextAttack[BOMB] = (BossAttack)-1;
	m_nextAttack[DASH] = DEEP_ESTOC;
	m_nextAttack[DEEP_ESTOC] = DASH;
}

void SLBoss::UpdateCombo()
{
	if (m_currentAnimation.HasEnded())
	{
		m_attacks.clear();

		if (!m_playerHit)
		{
			int random = rand() % m_availableAttacks[m_lastAttack].size();

			if (m_availableAttacks[m_lastAttack][random] == (BossAttack)-1)
			{
				EndCombo();
			}
			else
			{
				CreateAttack(m_availableAttacks[m_lastAttack][random]);
			}
		}
		else
		{
			if (m_nextAttack[m_lastAttack] == (BossAttack)-1)
			{
				EndCombo();
			}
			else
			{
				CreateAttack(m_nextAttack[m_lastAttack]);
			}
		}
	}
}

void SLBoss::EndCombo()
{
	int randState = rand() % 4;
	int randAtk;

	switch (randState)
	{
	case 0:
		SetState(WAITING);
		break;
	case 1:
		SetState(CHASING);
		break;
	case 2:
		SetState(RUSHING);
		break;
	case 3:
		SetState(ATTACKING);
		if (IsPlayerInRange())
		{
			CreateAttack(GetRandomAttack());
		}
		else
		{
			randAtk = rand() % 3;
			switch (randAtk)
			{
			case 0:
				CreateAttack(DASH);
				break;
			case 1:
				CreateAttack(BLOOM_RANGE);
				break;
			case 2:
				CreateAttack(BLOOM_NUKE);
				break;
			}
		}
		break;
	}
}

sf::FloatRect SLBoss::GetAttackHitbox(int _type)
{
	sf::FloatRect hitbox;
	bool intersected = false;

	switch (_type)
	{
	case SLBoss::SLASH_RIGHT:
		if (m_dir == UP || m_dir == DOWN)
		{
			hitbox.height = m_hitbox.height / 4.f;
			hitbox.width = m_hitbox.width / 1.5f;
		}
		else
		{
			hitbox.height = m_hitbox.width / 1.5f;
			hitbox.width = m_hitbox.height / 4.f;
		}

		switch (m_dir)
		{
		case DOWN:
			hitbox.top = m_pos.y + m_hitbox.height / 2.f;
			hitbox.left = m_pos.x - hitbox.width;
			break;

		case UP:
			hitbox.top = m_pos.y - m_hitbox.height / 2.f - hitbox.height;
			hitbox.left = m_pos.x;
			break;

		case LEFT:
			hitbox.top = m_pos.y - hitbox.height;
			hitbox.left = m_pos.x - m_hitbox.width / 2.f - hitbox.width;
			break;

		case RIGHT:
			hitbox.top = m_pos.y;
			hitbox.left = m_pos.x + m_hitbox.width / 2.f;
			break;
		}
		break;

	case SLBoss::SLASH_LEFT:
		if (m_dir == UP || m_dir == DOWN)
		{
			hitbox.height = m_hitbox.height / 4.f;
			hitbox.width = m_hitbox.width / 1.5f;
		}
		else
		{
			hitbox.height = m_hitbox.width / 1.5f;
			hitbox.width = m_hitbox.height / 4.f;
		}

		switch (m_dir)
		{
		case DOWN:
			hitbox.top = m_pos.y + m_hitbox.height / 2.f;
			hitbox.left = m_pos.x;
			break;

		case UP:
			hitbox.top = m_pos.y - m_hitbox.height / 2.f - hitbox.height;
			hitbox.left = m_pos.x - hitbox.width;
			break;

		case LEFT:
			hitbox.top = m_pos.y;
			hitbox.left = m_pos.x - m_hitbox.width / 2.f - hitbox.width;
			break;

		case RIGHT:
			hitbox.top = m_pos.y - hitbox.height;
			hitbox.left = m_pos.x + m_hitbox.width / 2.f;
			break;
		}
		break;

	case SLBoss::ESTOC:
		if (m_dir == UP || m_dir == DOWN)
		{
			hitbox.width = m_hitbox.width / 4.f;
			hitbox.height = m_hitbox.height / 2.f;
		}
		else
		{
			hitbox.width = m_hitbox.height / 2.f;
			hitbox.height = m_hitbox.width / 4.f;
		}
		switch (m_dir)
		{
		case DOWN:
			hitbox.top = m_pos.y + m_hitbox.height / 2.f;
			hitbox.left = m_pos.x - hitbox.width / 2.f;
			break;
		case UP:
			hitbox.top = m_pos.y - m_hitbox.height / 2.f - hitbox.height;
			hitbox.left = m_pos.x - hitbox.width / 2.f;
			break;
		case LEFT:
			hitbox.top = m_pos.y - hitbox.height / 2.f;
			hitbox.left = m_pos.x - m_hitbox.width / 2.f - hitbox.width;
			break;
		case RIGHT:
			hitbox.top = m_pos.y - hitbox.height / 2.f;
			hitbox.left = m_pos.x + m_hitbox.width / 2.f;
			break;
		}
		break;

	case SLBoss::BLOOM_CLOSE:
		hitbox.height = m_hitbox.height + m_hitbox.width / 4.f * 2.f;
		hitbox.width = m_hitbox.width + m_hitbox.width / 4.f * 2.f;

		hitbox.left = m_pos.x - m_hitbox.width / 2.f - m_hitbox.width / 4.f;
		hitbox.top = m_pos.y - m_hitbox.height / 2.f - m_hitbox.width / 4.f;
		break;

	case SLBoss::BLOOM_RANGE:
		hitbox.height = m_hitbox.height + m_hitbox.width / 4.f * 2.f;
		hitbox.width = m_hitbox.width + m_hitbox.width / 4.f * 2.f;

		hitbox.top = m_player->GetPosition().y - m_hitbox.height / 2.f - m_hitbox.width / 4.f;
		hitbox.left = m_player->GetPosition().x - m_hitbox.width / 2.f - m_hitbox.width / 4.f;
		break;

	case SLBoss::BLOOM_NUKE:
		hitbox.height = m_hitbox.height / 2.f;
		hitbox.width = m_hitbox.width / 2.f;

		m_randomRangeX = { m_player->GetPosition().x - 100.f, m_player->GetPosition().x + 100.f };
		m_randomRangeY = { m_player->GetPosition().y - 100.f, m_player->GetPosition().y + 100.f };

		if (m_randomRangeX.x - hitbox.width / 2.f < m_bossRoom.left) m_randomRangeX.x = m_bossRoom.left + hitbox.width / 2.f;
		if (m_randomRangeX.y + hitbox.width / 2.f > m_bossRoom.left + m_bossRoom.width) m_randomRangeX.y = m_bossRoom.left + m_bossRoom.width - hitbox.width / 2.f;
		if (m_randomRangeY.x - hitbox.height / 2.f < m_bossRoom.top) m_randomRangeY.x = m_bossRoom.top + hitbox.height / 2.f;
		if (m_randomRangeY.y + hitbox.height / 2.f > m_bossRoom.top + m_bossRoom.height) m_randomRangeY.y = m_bossRoom.top + m_bossRoom.height - hitbox.height / 2.f;

		m_randX = std::uniform_real_distribution<float>(m_randomRangeX.x, m_randomRangeX.y);
		m_randY = std::uniform_real_distribution<float>(m_randomRangeY.x, m_randomRangeY.y);

		do
		{
			intersected = false;

			m_randPos = { m_randX(m_gen), m_randY(m_gen) };
			hitbox.left = m_randPos.x - hitbox.width / 2.f;
			hitbox.top = m_randPos.y - hitbox.height / 2.f;

			for (int i = 0; i < m_attacks.size(); i++)
			{
				if (hitbox.intersects(m_attacks[i].hitbox) || hitbox.intersects(m_hitbox))
				{
					intersected = true;
				}
			}
		} while (intersected);


		break;

	case SLBoss::BOMB:
		hitbox.top = m_player->GetPosition().y - m_hitbox.height / 4.f;
		hitbox.height = m_hitbox.height / 2.f;
		hitbox.left = m_player->GetPosition().x - m_hitbox.width / 4.f;
		hitbox.width = m_hitbox.width / 2.f;
		break;

	case SLBoss::DASH:
		hitbox = m_hitbox;
		break;

	case SLBoss::DEEP_ESTOC:
		if (m_dir == UP || m_dir == DOWN)
		{
			hitbox.width = m_hitbox.width / 4.f;
			hitbox.height = m_hitbox.height;
		}
		else
		{
			hitbox.width = m_hitbox.height;
			hitbox.height = m_hitbox.width / 4.f;
		}
		switch (m_dir)
		{
		case DOWN:
			hitbox.top = m_pos.y + m_hitbox.height / 2.f;
			hitbox.left = m_pos.x - hitbox.width / 2.f;
			break;
		case UP:
			hitbox.top = m_pos.y - m_hitbox.height / 2.f - hitbox.height;
			hitbox.left = m_pos.x - hitbox.width / 2.f;
			break;
		case LEFT:
			hitbox.top = m_pos.y - hitbox.height / 2.f;
			hitbox.left = m_pos.x - m_hitbox.width / 2.f - hitbox.width;
			break;
		case RIGHT:
			hitbox.top = m_pos.y - hitbox.height / 2.f;
			hitbox.left = m_pos.x + m_hitbox.width / 2.f;
			break;
		}
		break;

	default:
		hitbox = m_hitbox;
		break;
	}

	return hitbox;
}

void SLBoss::CancelDashHitbox()
{
	for (int i = 0; i < m_attacks.size(); i++)
	{
		if (m_attacks[i].type == DASH)
		{
			m_attacks[i].hitbox.left -= m_velocity.x;
			m_attacks[i].hitbox.top -= m_velocity.y;
		}
	}
}

void SLBoss::CreateStageAttack(Direction _type)
{
	StageAttack tempStageAttack;

	tempStageAttack.dir = _type;
	float numberOfSprites = (m_bossRoom.width * (_type == LEFT || _type == RIGHT) + m_bossRoom.height * (_type == UP || _type == DOWN)) / 32.f;

	for (int i = 0; i < numberOfSprites; i++)
	{
		RonceSprite tempSprite;
		bool horizontal = (_type == LEFT || _type == RIGHT);
		bool reverse = (_type == RIGHT || _type == DOWN);
		int type;

		if (i == 0)	type = reverse ? START : END;
		else if (i == numberOfSprites - 1) type = reverse ? END : START;
		else type = MIDDLE;

		tempSprite.type = (RonceSpriteType)type;
		tempSprite.sprite = m_preloadedStageAttackSprites[horizontal][type];
		tempSprite.sprite.setScale(1 - (_type == LEFT) * 2, 1 - (_type == DOWN) * 2);

		tempSprite.pos = sf::Vector2f(m_bossRoom.left, m_bossRoom.top);

		tempStageAttack.sprites.push_back(tempSprite);
	}

	tempStageAttack.initTimer = 0;
	tempStageAttack.mescouillesFloat = 0;

	m_stageAttacks.push_back(tempStageAttack);
}

void SLBoss::UpdateStageAttacks(float _dt)
{
	for (int i = 0; i < m_stageAttacks.size(); i++)
	{
		Direction dir = m_stageAttacks[i].dir;

#pragma region Position
		if (m_stageAttacks[i].initTimer < 1.f)
		{
			if (dir == DOWN || dir == UP)
			{
				m_stageAttacks[i].sprites[0].pos.x = m_player->GetPosition().x - 16.f;
				if (dir == DOWN)
					m_stageAttacks[i].sprites[0].pos.y = m_bossRoom.top + 32.f;

				for (int j = 1; j < m_stageAttacks[i].sprites.size(); j++)
				{
					m_stageAttacks[i].sprites[j].pos = m_stageAttacks[i].sprites[0].pos;
					m_stageAttacks[i].sprites[j].pos.y += 32.f * j;
				}
			}
			else
			{
				m_stageAttacks[i].sprites[0].pos.y = m_player->GetPosition().y - 16.f;
				if (dir == LEFT)
					m_stageAttacks[i].sprites[0].pos.x = m_bossRoom.left + 32.f;

				for (int j = 1; j < m_stageAttacks[i].sprites.size(); j++)
				{
					m_stageAttacks[i].sprites[j].pos = m_stageAttacks[i].sprites[0].pos;
					m_stageAttacks[i].sprites[j].pos.x += 32.f * j + 32.f * (dir == DOWN);
				}
			}
		}
#pragma endregion

#pragma region Hitbox
		int startID = (m_stageAttacks[i].sprites.size() - 1) * (dir == LEFT || dir == UP);
		m_stageAttacks[i].hitbox.left = m_stageAttacks[i].sprites[startID].pos.x;
		m_stageAttacks[i].hitbox.top = m_stageAttacks[i].sprites[startID].pos.y + (dir == UP) * 32.f - (dir == DOWN) * 32.f;

		if (dir == UP || dir == DOWN)
		{
			m_stageAttacks[i].hitbox.width = 32.f;
			if (dir == UP)
				m_stageAttacks[i].hitbox.height = -m_stageAttacks[i].mescouillesFloat;
			else
				m_stageAttacks[i].hitbox.height = m_stageAttacks[i].mescouillesFloat;
		}
		else
		{
			m_stageAttacks[i].hitbox.height = 32.f;
			if (dir == LEFT)
				m_stageAttacks[i].hitbox.width = -m_stageAttacks[i].mescouillesFloat;
			else
				m_stageAttacks[i].hitbox.width = m_stageAttacks[i].mescouillesFloat;

		}
#pragma endregion

#pragma region Collisions

		if (m_stageAttacks[i].hitbox.intersects(m_player->GetHitbox()))
		{
			if (!m_player->IsInvincible())
			{
				m_player->DecreaseHP(5);
				m_player->SetInvincibilityTimer(0.5f);
			}

			m_player->CancelMovement();
			if (m_stageAttacks[i].hitbox.intersects(m_player->GetHitbox()))
			{
				sf::Vector2f velocity;

				if (dir == RIGHT) velocity.x = 1;
				else if (dir == LEFT) velocity.x = -1;
				else if (dir == UP) velocity.y = -1;
				else if (dir == DOWN) velocity.y = 1;

				m_player->SetVelocity(sf::Vector2f(-velocity.y, velocity.x));
				m_player->CancelMovement();
			}
		}

#pragma endregion

#pragma region Etat
		std::string orientation = "Horizontal";
		if (m_stageAttacks[i].dir == UP || m_stageAttacks[i].dir == DOWN) orientation = "Vertical";

		std::string anim = "InAnim";
		if (m_stageAttacks[i].isRetracted) anim = "OutAnim";
		m_ronceAnimation.PlayAnimation("Assets/Souls/Boss/StageAttack/" + orientation + "/" + anim + "/", 0.5f);

		if (m_stageAttacks[i].isRetracted)
		{
			if (m_ronceAnimation.HasEnded())
			{
				m_stageAttacks.erase(m_stageAttacks.begin() + i);
			}
			else
			{
				int startID = 0 + (m_stageAttacks[i].sprites.size() - 1) * (m_stageAttacks[i].dir == LEFT || m_stageAttacks[i].dir == UP);
				sf::Vector2f initialScale = m_stageAttacks[i].sprites[startID].sprite.getScale();

				m_stageAttacks[i].sprites[startID].sprite = m_ronceAnimation.GetCurrentSprite();
				m_stageAttacks[i].sprites[startID].sprite.setPosition(m_stageAttacks[i].sprites[startID].pos);
				m_stageAttacks[i].sprites[startID].sprite.setScale(initialScale);
				m_stageAttacks[i].sprites[startID].sprite.setOrigin(0, 0);
			}
		}

		m_stageAttacks[i].initTimer += _dt;

		if (m_stageAttacks[i].initTimer < 0.5f)
		{
			m_ronceAnimation.RestartAnimation();
		}
		else
		{
			m_stageAttacks[i].initTimer = 1.f;

			if (!m_stageAttacks[i].isDeploying)
			{
				int startID = 0 + (m_stageAttacks[i].sprites.size() - 1) * (m_stageAttacks[i].dir == LEFT || m_stageAttacks[i].dir == UP);

				sf::Vector2f initialScale = m_stageAttacks[i].sprites[startID].sprite.getScale();

				for (int j = 0; j < m_stageAttacks[i].sprites.size(); j++)
				{
					m_stageAttacks[i].sprites[j].sprite.setTextureRect(sf::IntRect(0, 0, 0, 32));
				}
				m_stageAttacks[i].sprites[startID].sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

				if (m_ronceAnimation.HasEnded())
				{
					m_stageAttacks[i].isDeploying = true;
					m_ronceAnimation.RestartAnimation();
				}
				else
				{
					m_stageAttacks[i].sprites[startID].sprite = m_ronceAnimation.GetCurrentSprite();
					m_stageAttacks[i].sprites[startID].sprite.setPosition(m_stageAttacks[i].sprites[startID].pos);
					m_stageAttacks[i].sprites[startID].sprite.setScale(initialScale);
					m_stageAttacks[i].sprites[startID].sprite.setOrigin(0, 0);
				}
			}
		}

		if (m_stageAttacks[i].isDeploying && !m_stageAttacks[i].isDeployed)
		{
			m_stageAttacks[i].mescouillesFloat += _dt * 800.f;
			float mescouillesCopy = m_stageAttacks[i].mescouillesFloat;

			if (dir == RIGHT || dir == DOWN)
			{
				for (int j = 1; j < m_stageAttacks[i].sprites.size(); j++)
				{
					if (mescouillesCopy > 32)
					{
						m_stageAttacks[i].sprites[j].sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
					}
					else if (mescouillesCopy > 0)
					{
						if (dir == RIGHT)
							m_stageAttacks[i].sprites[j].sprite.setTextureRect(sf::IntRect(0, 0, mescouillesCopy, 32));
						else
							m_stageAttacks[i].sprites[j].sprite.setTextureRect(sf::IntRect(0, 0, 32, mescouillesCopy));
					}

					mescouillesCopy -= 32.f;
				}
			}
			else
			{
				for (int j = m_stageAttacks[i].sprites.size() - 2; j >= 0; j--)
				{
					if (mescouillesCopy > 32)
					{
						m_stageAttacks[i].sprites[j].sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
					}
					else if (mescouillesCopy > 0)
					{
						if (dir == LEFT)
							m_stageAttacks[i].sprites[j].sprite.setTextureRect(sf::IntRect(0, 0, mescouillesCopy, 32));
						else
							m_stageAttacks[i].sprites[j].sprite.setTextureRect(sf::IntRect(0, 0, 32, mescouillesCopy));
					}

					mescouillesCopy -= 32.f;
				}
			}

			if (dir == RIGHT || dir == LEFT)
			{
				if (m_stageAttacks[i].mescouillesFloat >= m_bossRoom.width)
				{
					m_stageAttacks[i].isDeployed = true;
					m_stageAttacks[i].mescouillesFloat = m_bossRoom.width;
				}
			}
			else
			{
				if (m_stageAttacks[i].mescouillesFloat >= m_bossRoom.height)
				{
					m_stageAttacks[i].isDeployed = true;
					m_stageAttacks[i].mescouillesFloat = m_bossRoom.height;
				}
			}
		}

		if (m_stageAttacks[i].isDeployed)
		{
			m_stageAttacks[i].idleTimer += _dt;

			if (m_stageAttacks[i].idleTimer >= 1.5f)
			{
				if (m_stageAttacks[i].mescouillesFloat > 0)
				{
					m_stageAttacks[i].mescouillesFloat -= _dt * 800.f;
					float mescouillesCopy = m_stageAttacks[i].mescouillesFloat;
					if (dir == RIGHT || dir == DOWN)
					{
						for (int j = 1; j < m_stageAttacks[i].sprites.size(); j++)
						{
							m_stageAttacks[i].sprites[j].sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
							if (mescouillesCopy > 32)
							{
								m_stageAttacks[i].sprites[j].sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
							}
							else if (mescouillesCopy > 0)
							{
								if (dir == RIGHT)
									m_stageAttacks[i].sprites[j].sprite.setTextureRect(sf::IntRect(0, 0, mescouillesCopy, 32));
								else
									m_stageAttacks[i].sprites[j].sprite.setTextureRect(sf::IntRect(0, 0, 32, mescouillesCopy));
							}

							mescouillesCopy -= 32.f;
						}
					}
					else
					{
						for (int j = m_stageAttacks[i].sprites.size() - 2; j >= 0; j--)
						{
							m_stageAttacks[i].sprites[j].sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
							if (mescouillesCopy > 32)
							{
								m_stageAttacks[i].sprites[j].sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
							}
							else if (mescouillesCopy > 0)
							{
								if (dir == LEFT)
									m_stageAttacks[i].sprites[j].sprite.setTextureRect(sf::IntRect(0, 0, mescouillesCopy, 32));
								else
									m_stageAttacks[i].sprites[j].sprite.setTextureRect(sf::IntRect(0, 0, 32, mescouillesCopy));
							}

							mescouillesCopy -= 32.f;
						}
					}
				}
				else
				{
					if (!m_stageAttacks[i].isRetracted)
					{
						m_ronceAnimation.RestartAnimation();
					}
					m_stageAttacks[i].isRetracted = true;
				}
			}
		}
		else
		{
			m_stageAttacks[i].idleTimer = 0;
		}
#pragma endregion

	}
}

void SLBoss::DisplayStageAttacks(sf::RenderWindow& _window)
{
	for (int i = 0; i < m_stageAttacks.size(); i++)
	{
		for (int j = 0; j < m_stageAttacks[i].sprites.size(); j++)
		{
			if (m_stageAttacks[i].initTimer < 1.f)
			{
				m_stageAttacks[i].sprites[j].sprite.setColor(sf::Color(255, 255, 255, 96));
			}
			else
			{
				m_stageAttacks[i].sprites[j].sprite.setColor(sf::Color::White);
			}

			m_stageAttacks[i].sprites[j].sprite.setPosition(m_stageAttacks[i].sprites[j].pos);
			_window.draw(m_stageAttacks[i].sprites[j].sprite);
		}
	}
}

const std::vector<sf::Vector2f> SLBoss::GetStageAttacksPos()
{
	std::vector<sf::Vector2f> pos;

	for (int i = 0; i < m_stageAttacks.size(); i++)
	{
		for (int j = 0; j < m_stageAttacks[i].sprites.size(); j++)
		{
			pos.push_back(m_stageAttacks[i].sprites[j].pos);
		}
	}

	return pos;
}

const std::vector<sf::Vector2f> SLBoss::GetAttacksPos()
{
	std::vector<sf::Vector2f> pos;

	for (int i = 0; i < m_attacks.size(); i++)
	{
		if (m_attacks[i].type == BOMB || m_attacks[i].type == BLOOM_CLOSE || m_attacks[i].type == BLOOM_RANGE || m_attacks[i].type == BLOOM_NUKE)
		{
			pos.push_back(m_attacks[i].pos);
		}
	}

	return pos;
}