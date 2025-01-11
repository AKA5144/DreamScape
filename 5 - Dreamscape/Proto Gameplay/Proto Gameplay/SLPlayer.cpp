#include "SLPlayer.h"

void SLPlayer::Init()
{
	m_sprite = LoadSprite("Assets/Souls/Player/Idle/Avec bonnet/Down/1.png", true);
	m_hatSprite = LoadSprite("Assets/Souls/Player/AttackSpe/hat.png", true);
	m_size = { 11, 24 };
	m_fVector = { 0, 0 };

	m_hp = 100;
	m_maxHP = m_hp;
	m_mana = 80;
	m_maxMana = m_mana;
	m_stamina = 50;
	m_maxStamina = m_stamina;

	m_speed = 200.f;
	m_rotation = 0;
	m_dir = LEFT;
	m_state = IDLE;

	m_hasHat = true;
	m_isInLockedMode = false;

	m_lockSprite = LoadSprite("Assets/Souls/Misc/lock.png", true);

	m_coolDownBar = ProportionalBar::Create(m_pos, sf::Vector2f(m_size.x, 2), sf::Color(222, 222, 222), sf::Color(158, 155, 151), sf::Color(165, 152, 130, 64), 1, true);
}

void SLPlayer::Update(Config _config, float _dt)
{
	UpdateAnimation();

	UpdateInvincibility(_dt);

	UseAbility(_config, _dt);

	if (m_state == ROLL && m_currentAnimation.GetCurrentFrameType() == AnimationManager::ACTIVE)
	{
		m_isInvincible = true;
	}

	UpdateStamina(_dt); // Keep after UseAbility()
	UpdateStates(_dt);

	Move(_config, _dt);
	m_hitbox = { m_pos.x - m_size.x / 2.f, m_pos.y, m_size.x, m_size.y / 2.f };

	UpdateCooldownBar(_dt);
	UpdateAttacks(_dt); // Keep after Move()

	m_lockHitbox = sf::FloatRect(m_pos.x - SCREEN_WIDTH / 3.f / 2.f, m_pos.y - SCREEN_HEIGHT / 3.f / 2.f, SCREEN_WIDTH / 3.f, SCREEN_HEIGHT / 3.f);

	if (m_isInLockedMode && m_state != ROLL && m_state != ATTACK && m_state != ATTACKSPE)
	{
		UpdateDirection();
	}

	if (m_hp <= 0)
	{
		m_hp = 0;
	}

	if (CreaMaths::GetSquaredDistance(m_fVector) == 0)
	{
		if (m_dir == RIGHT) m_fVector.x++;
		if (m_dir == LEFT) m_fVector.x--;
		if (m_dir == DOWN) m_fVector.y++;
		if (m_dir == UP) m_fVector.y--;
	}

	m_sounds.SetListenerPos(m_pos);
	m_sounds.SetListenerVolume(50);
}

void SLPlayer::Display(sf::RenderWindow& _window)
{
	sf::View camera = _window.getView();

	sf::Color playerColor = sf::Color::White;

	if (m_initialInvincibilityTimer != 0 && m_hit)
	{
		playerColor = sf::Color(255, 255 - (m_invincibilityTimer / m_initialInvincibilityTimer) * 255, 255 - (m_invincibilityTimer / m_initialInvincibilityTimer) * 255);
	}

	BlitSprite(m_sprite, m_pos, _window, { 1, 1 }, 0, playerColor);

	if (m_isInLockedMode)
	{
		BlitSprite(m_lockSprite, m_lockedPos, _window);
	}

	for (int i = 0; i < m_attacks.size(); i++)
	{
		if (m_attacks[i].type == SPECIAL)
		{
			_window.draw(m_attacks[i].sprite);
		}
	}

	if (m_cooldown > 0)
	{
		DisplayCooldownBar(_window);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SLPlayer::UpdateKeyboardInputs()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		m_fVector.y--;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_fVector.y++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		m_fVector.x--;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_fVector.x++;
	}

	if (m_state != ATTACK && m_state != ATTACKSPE && m_state != ROLL)
	{
		if (m_fVector.x != 0 || m_fVector.y != 0)
		{
			m_dirAngle = CreaMaths::RadiansToDegrees(atan2f(m_fVector.y, m_fVector.x));
			m_sounds.PlaySFX("Walk", true, 50);
		}

		if (m_fVector.x > 0)
			m_dir = RIGHT;
		else if (m_fVector.x < 0)
			m_dir = LEFT;
		else if (m_fVector.y > 0)
			m_dir = DOWN;
		else if (m_fVector.y < 0)
			m_dir = UP;
	}
}

void SLPlayer::UpdateControllerInputs()
{
	m_fVector.x = sf::Joystick::getAxisPosition(0, sf::Joystick::X) / 100;
	m_fVector.y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y) / 100;

	if (CreaMaths::IsInBetween(m_fVector.x, -0.3, 0.3))
	{
		m_fVector.x = 0;
	}
	if (CreaMaths::IsInBetween(m_fVector.y, -0.3, 0.3))
	{
		m_fVector.y = 0;
	}

	if (m_state != ATTACK && m_state != ATTACKSPE && m_state != ROLL)
	{
		if (m_fVector.x != 0 || m_fVector.y != 0)
		{
			m_dirAngle = CreaMaths::RadiansToDegrees(atan2f(m_fVector.y, m_fVector.x));

			m_sounds.PlaySFX("Walk", true, 50);
		}

		if (CreaMaths::GetSquaredLength(m_fVector) != 0)
		{
			if (CreaMaths::IsInBetween(m_dirAngle, -45, 45))
			{
				m_dir = RIGHT;
			}
			else if (m_dirAngle > 135 || m_dirAngle < -135)
			{
				m_dir = LEFT;
			}
			else if (CreaMaths::IsInBetween(m_dirAngle, 45, 135))
			{
				m_dir = DOWN;
			}
			else if (CreaMaths::IsInBetween(m_dirAngle, -135, -45))
			{
				m_dir = UP;
			}
		}
	}
}

void SLPlayer::Move(Config _config, float _dt)
{
	if (m_state != ROLL)
	{
		// Reset forward vector
		m_fVector = { 0, 0 };

		// Inputs déplacements
		if (_config == KEYBOARD)
		{
			UpdateKeyboardInputs();
		}
		else if (_config == CONTROLLER)
		{
			UpdateControllerInputs();
		}
	}

	// The forward vector needs to keep a maximum norm of 1
	if (CreaMaths::GetSquaredLength(m_fVector) > 1)
	{
		CreaMaths::ClampLength(m_fVector, 1);
	}

	// Update the velocity
	if (m_state != ATTACK && m_state != ATTACKSPE && m_state != ROLL)
	{
		m_velocity = m_fVector * _dt * m_speed;

		if (m_fVector != sf::Vector2f(0, 0))
		{
			m_state = WALK;
		}
		else
		{
			m_state = IDLE;
		}
	}
	else if (m_state == ROLL)
	{
		m_fVector *= 1000.f;
		CreaMaths::ClampLength(m_fVector, 1);

		if (m_currentAnimation.GetCurrentFrame() < 3)
		{
			m_velocity = m_fVector * _dt * m_speed * 1.25f;
		}
		else
		{
			m_velocity = m_fVector * _dt * m_speed * 0.5f;
		}

		float angle = CreaMaths::RadiansToDegrees(atan2f(m_velocity.y, m_velocity.x));

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
	else if (m_state == ATTACK || m_state == ATTACKSPE)
	{
		if (CreaMaths::GetSquaredLength(m_fVector) == 0)
		{
			switch (m_dir)
			{
			case UP:
				m_dirAngle = -90;
				break;
			case DOWN:
				m_dirAngle = 90;
				break;
			case LEFT:
				m_dirAngle = -180;
				break;
			case RIGHT:
				m_dirAngle = 0;
				break;
			default:
				break;
			}
		}

		sf::Vector2f fVector = CreaMaths::RotateVector(sf::Vector2f(1, 0), CreaMaths::DegreesToRadians(m_dirAngle));
		CreaMaths::ClampLength(fVector, 1);

		m_velocity = fVector * m_speed * 0.2f * _dt;
	}

	// Update player pos
	m_pos += m_velocity;

	//if (CreaMaths::GetSquaredDistance(m_velocity) != 0)
	//{
	//	m_sounds.PlaySFX("Walk", true, 15);
	//}
}

void SLPlayer::UpdateStamina(float _dt)
{
	if (m_stamina < 0)
	{
		m_stamina = 0;
	}
	else
	{
		if (m_staminaClock.getElapsedTime().asSeconds() >= 1.f)
		{
			if (m_stamina + _dt * 50.f < m_maxStamina)
			{
				m_stamina += _dt * 50.f;
			}
			else
			{
				m_stamina = m_maxStamina;
			}
		}
	}
}

void SLPlayer::UpdateAnimation()
{
	float animDuration = 1; // La durée totale de l'animation (le temps nécessaire pour que l'animation se complète)
	switch (m_state)
	{
	case SLPlayer::IDLE:
		break;
	case SLPlayer::WALK:
		animDuration = 0.7f;
		break;
	case SLPlayer::ATTACK:
		animDuration = 0.35f;
		break;
	case SLPlayer::ROLL:
		animDuration = 0.65f;
		break;
	case SLPlayer::ATTACKSPE:
		animDuration = 0.4f;
		break;
	default:
		break;
	}

	// Entrer toutes les valeurs possibles de l'enum, impérativement dans l'ordre
	std::string bonnetPath[] = { "Sans bonnet", "Avec bonnet" };
	std::string statePath[] = { "Idle", "Walk", "Attack", "AttackSpe", "Roll" };
	std::string dirPath[] = { "Up", "Down", "Left", "Right" };

	std::string path;

	if (m_state == ATTACKSPE)
		path = "Assets/Souls/Player/" + statePath[m_state] + "/" + dirPath[m_dir] + "/";
	else
		path = "Assets/Souls/Player/" + statePath[m_state] + "/" + bonnetPath[m_hasHat] + "/" + dirPath[m_dir] + "/";

	m_currentAnimation.PlayAnimation(path, animDuration);

	if (!m_currentAnimation.HasEnded())
	{
		m_sprite = m_currentAnimation.GetCurrentSprite();
	}
}

void SLPlayer::UseAbility(Config _config, float _dt)
{
	bool isMoving = CreaMaths::GetSquaredLength(m_fVector) > 0;

	if (m_state == IDLE || m_state == WALK)
	{
		if (m_cooldown == 0)
		{
			// Attaque : Clic gauche ou X (manette)
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Joystick::isButtonPressed(0, (int)ControllerButton::X))
			{
				if (m_stamina > 5)
				{
					m_state = ATTACK;
					CreateAttack(AttackType::DEFAULT);
					m_cooldown = 0.35f;
					m_maxCooldown = m_cooldown;
					m_stamina -= 5;
					m_staminaClock.restart();

					m_sounds.PlaySFX("Player_MeleeAttack", true);
				}
			}

			// Attaque Spéciale : E (clavier) ou Y (manette)
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Joystick::isButtonPressed(0, (int)ControllerButton::Y))
			{
				if (m_hasHat)
				{
					if (m_mana > 10 && m_stamina > 10)
					{
						m_state = ATTACKSPE;
						CreateAttack(AttackType::SPECIAL);
						m_cooldown = 0.4f;
						m_maxCooldown = m_cooldown;
						m_mana -= 10;
						m_stamina -= 10;
						m_staminaClock.restart();

						m_hasHat = false;
					}
				}
			}

			// Roll : Shift gauche, A (manette) ou B (manette)
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Joystick::isButtonPressed(0, (int)ControllerButton::B) || sf::Joystick::isButtonPressed(0, (int)ControllerButton::A))
			{
				if (isMoving && m_stamina > 10)
				{
					m_state = ROLL;
					m_cooldown = 0.65f + 0.3f;
					m_invincibilityTimer = m_cooldown;
					m_initialInvincibilityTimer = m_cooldown;
					m_maxCooldown = m_cooldown;

					m_stamina -= 10;
					m_staminaClock.restart();

					m_sounds.PlaySFX("Player_Dodge", true);
				}
			}
		}
	}
}

void SLPlayer::UpdateStates(float _dt)
{
	if (m_state == ATTACK || m_state == ATTACKSPE)
	{
		if (m_currentAnimation.HasEnded())
		{
			m_state = IDLE;
		}
	}
	if (m_state == ROLL)
	{
		if (m_currentAnimation.HasEnded())
		{
			m_state = IDLE;
		}
	}
}

void SLPlayer::UpdateDirection()
{
	sf::Vector2f playerTargetVec = CreaMaths::CreateVector(m_pos, m_lockedPos);

	if (Collisions::IsCollidingRectPoint(m_lockHitbox, m_lockedPos))
	{
		float angle = CreaMaths::RadiansToDegrees(atan2f(playerTargetVec.y, playerTargetVec.x));

		if (CreaMaths::IsInBetween(angle, -45, 45))
		{
			m_dir = RIGHT;
		}
		else if (angle > 135 || angle < -135)
		{
			m_dir = LEFT;
		}
		else if (CreaMaths::IsInBetween(angle, 45, 135))
		{
			m_dir = DOWN;
		}
		else if (CreaMaths::IsInBetween(angle, -135, -45))
		{
			m_dir = UP;
		}
	}
	else
	{
		m_isInLockedMode = false;
		m_lockedEnemyID = -1;
	}
}

void SLPlayer::UpdateCooldownBar(float _dt)
{
	UpdateCooldown(_dt);

	sf::Vector2f CDBarPos(m_pos.x, m_pos.y - m_size.y / 2.f - m_coolDownBar[0].getSize().y);
	for (int i = 0; i < 2; i++)
	{
		m_coolDownBar[i].setPosition(CDBarPos);
	}

	m_coolDownBar[1].setSize({ m_size.x * (m_cooldown / m_maxCooldown), m_coolDownBar[1].getSize().y });
}

void SLPlayer::CreateAttack(int _type)
{
	Attack tempAttack;

	tempAttack.type = (AttackType)_type;

	switch (_type)
	{
	case AttackType::DEFAULT:
		tempAttack.hitbox.width = m_hitbox.width * 2;
		tempAttack.hitbox.height = m_hitbox.height * 2;

		tempAttack.damage = 50;
		break;

	case AttackType::SPECIAL:

		tempAttack.sprite = m_hatSprite;

		tempAttack.hitbox.left = m_pos.x;
		tempAttack.hitbox.top = m_pos.y;

		tempAttack.hitbox.width = m_hatSprite.getTexture()->getSize().x;
		tempAttack.hitbox.height = m_hatSprite.getTexture()->getSize().y;
		if (!m_isInLockedMode)
		{
			if (CreaMaths::GetSquaredLength(m_velocity) == 0)
			{
				switch (m_dir)
				{
				case UP:
					tempAttack.dirVec = { 0, -1 };
					break;
				case DOWN:
					tempAttack.dirVec = { 0, 1 };
					break;
				case LEFT:
					tempAttack.dirVec = { -1, 0 };
					break;
				case RIGHT:
					tempAttack.dirVec = { 1, 0 };
					break;
				default:
					break;
				}
			}
			else
			{
				tempAttack.dirVec = m_velocity;
			}
		}
		else
		{
			tempAttack.dirVec = CreaMaths::CreateVector(m_pos, m_lockedPos);
		}
		CreaMaths::ClampLength(tempAttack.dirVec, 1);

		tempAttack.speed = 800.f;

		tempAttack.damage = 60;
		break;

	default:
		break;
	}
	m_attacks.push_back(tempAttack);
}

void SLPlayer::UpdateAttacks(float _dt)
{
	for (int i = 0; i < m_attacks.size(); i++)
	{
		switch (m_attacks[i].type)
		{
		case AttackType::DEFAULT:

			// L'origine est en haut à gauche, si on tape à droite ou en bas, on décale de la hitbox du joueur, sinon on décale de la taille de la hitbox de l'attaque
			m_attacks[i].hitbox.left = m_hitbox.left + (m_dir == RIGHT) * m_hitbox.width - (m_dir == LEFT) * m_attacks[i].hitbox.width;
			m_attacks[i].hitbox.top = m_hitbox.top + (m_dir == DOWN) * m_hitbox.height - (m_dir == UP) * m_attacks[i].hitbox.height;

			// Centrage du coup (l'origine est toujours en haut à gauche)
			if (m_dir == UP || m_dir == DOWN)
			{
				m_attacks[i].hitbox.left -= m_attacks[i].hitbox.width / 2.f - m_hitbox.width / 2.f;
			}
			if (m_dir == LEFT || m_dir == RIGHT)
			{
				m_attacks[i].hitbox.top -= m_attacks[i].hitbox.height / 2.f - m_hitbox.height / 2.f;
			}

			if (m_state != ATTACK)
			{
				m_attacks.erase(m_attacks.begin() + i);
			}
			break;

		case AttackType::SPECIAL:

			if (m_state != ATTACKSPE)
			{

				if (m_attacks[i].speed >= -2000)
				{
					m_attacks[i].speed -= _dt * 1200;
				}
				else
				{
					DeleteAttack(i);
					m_hasHat = true;
				}

				if (m_attacks[i].speed < 0)
				{
					sf::Vector2f hatPlayerPos = CreaMaths::CreateVector(m_pos, m_attacks[i].pos);
					m_attacks[i].dirVec = hatPlayerPos;
					CreaMaths::ClampLength(m_attacks[i].dirVec, 1);
					if (CreaMaths::GetSquaredDistance(hatPlayerPos) < 15 * 15)
					{
						DeleteAttack(i);
						m_hasHat = true;
					}
				}
				else
				{
					m_sounds.PlaySFX("Player_RangeAttack", true, 80);
				}

				m_attacks[i].hitbox.left += m_attacks[i].dirVec.x * m_attacks[i].speed * _dt;
				m_attacks[i].hitbox.top += m_attacks[i].dirVec.y * m_attacks[i].speed * _dt;

				m_attacks[i].pos = sf::Vector2f(m_attacks[i].hitbox.left + m_attacks[i].hitbox.width / 2.f, m_attacks[i].hitbox.top + m_attacks[i].hitbox.height / 2.f);

				m_attacks[i].sprite.setPosition(m_attacks[i].pos);
				m_attacks[i].sprite.setRotation(m_attacks[i].sprite.getRotation() + _dt * -1800);
			}
			else
			{
				m_attacks[i].hitbox.left = m_pos.x;
				m_attacks[i].hitbox.top = m_pos.y;
			}

			break;

		default:
			break;
		}
	}
}

void SLPlayer::DisplayCooldownBar(sf::RenderWindow& _window)
{
	for (unsigned int i = 0; i < 2; i++)
	{
		_window.draw(m_coolDownBar[i]);
	}
}

void SLPlayer::MoveTo(sf::Vector2f _target, float _speed, float _dt)
{
	m_state = WALK;
	static sf::Clock clocc;

	m_fVector = CreaMaths::CreateVector(m_pos, _target);
	CreaMaths::ClampLength(m_fVector, 1);

	m_velocity = m_fVector * _speed * _dt;

	m_pos += m_velocity;

	if (clocc.getElapsedTime().asSeconds() > 0.7f)
	{
		m_sounds.PlaySFX("Walk", true, 50);
		clocc.restart();
	}

	ForceUpdateDirection();
	UpdateAnimation();
}

void SLPlayer::ForceIdle()
{
	m_state = IDLE;
	UpdateAnimation();
}

void SLPlayer::ForceUpdateDirection()
{
	float angle = CreaMaths::RadiansToDegrees(atan2f(m_fVector.y, m_fVector.x));

	if (CreaMaths::IsInBetween(angle, -45, 45))
	{
		m_dir = RIGHT;
		m_fVector = { 1, 0 };
	}
	else if (angle > 135 || angle < -135)
	{
		m_dir = LEFT;
		m_fVector = { -1, 0 };
	}
	else if (CreaMaths::IsInBetween(angle, 45, 135))
	{
		m_dir = DOWN;
		m_fVector = { 0, 1 };
	}
	else if (CreaMaths::IsInBetween(angle, -135, -45))
	{
		m_dir = UP;
		m_fVector = { 0, -1 };
	}
}