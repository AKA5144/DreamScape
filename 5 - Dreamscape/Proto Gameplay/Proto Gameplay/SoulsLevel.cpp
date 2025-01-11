#include "SoulsLevel.h"

SoulsLevel::SoulsLevel(sf::String _map)
{
	m_mapString = _map;

	m_hasLost = false;
	m_hasWon = false;

	m_map = new SLMap(32, _map);
	m_map->Init();

	m_tutorial = new SLTutorial(&m_camera, &m_player, m_map, &m_boss, _map);
	m_miniMap = new SLMinimap(_map, m_map, &m_player, m_tutorial);

	m_player.Init();
	m_player.SetPosition(m_map->GetTileCenter(m_map->GetPlayerTile()));


	if (m_mapString == "SoulsLevel")
	{
		m_boss.Load(&m_player);
		m_boss.SetPosition(m_map->GetTileCenter(m_map->GetBossTile()));
	}

	m_HUD.Init(m_player.GetStats());
	m_camera.Init(m_player.GetPosition());

	CreateEnemies();
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i].GetCollidedTilesTypeFunc(std::bind(&SLMap::GetCollidedTilesType, m_map, std::placeholders::_1, std::placeholders::_2));
	}

	SLSounds::Load();
}

void SoulsLevel::Update(float _dt, Config _config)
{
	if (!m_tutorial->GetPause())
	{
		m_player.Update(_config, _dt);

		UpdateLockMechanic();

		UpdatePlayerEnemiesCollisions();

		UpdateEnemies(_dt);

		if (m_mapString == "SoulsLevel")
		{
			if (m_tutorial->IsInBossFight())
			{
				m_boss.Update(_dt);
				UpdatePlayerBossCollision(_dt);
			}
		}

		UpdateMapCollisions(_dt);

		if (!m_player.GetLockedMode())
		{
			m_camera.SetSpeed(5.f);
			m_camera.SetDeadZone(30);
			m_camera.SetTarget(m_player.GetPosition());
		}

		CheckWinAndLossCondition();
	}

	m_HUD.Update(m_player.GetStats(), _dt, m_tutorial->GetCinematicMode());

	if (m_mapString == "SoulsLevel")
	{
		m_tutorial->Update(_dt, _config);
	}

	m_camera.Update(_dt);
}

void SoulsLevel::Display(sf::RenderWindow& _window)
{
	_window.setView(m_camera.GetView());

	m_map->DisplayGround(_window);
	m_map->DisplayDecor(_window);

	for (unsigned int i = 0; i < m_onScreenEnemies.size(); i++)
	{
		m_shaders.AddLight(m_onScreenEnemies[i]->GetPosition(), 5);
		m_onScreenEnemies[i]->Display(_window);
		m_map->DisplayDecor(_window, true, m_onScreenEnemies[i]->GetPosition());
	}

	if (m_mapString == "SoulsLevel")
	{
		if (m_tutorial->IsInBossFight())
		{
			m_boss.Display(_window);
		}
	}

	m_player.Display(_window);

	m_map->DisplayDecor(_window, true, m_player.GetPosition());

	sf::Vector2i startingID = m_map->GetTileID(m_camera.GetView().getCenter() - m_camera.GetView().getSize() / 2.f);
	sf::Vector2i endID = m_map->GetTileID(m_camera.GetView().getCenter() + m_camera.GetView().getSize() / 2.f);

	SLMap::SLMAP_Decor decorMap = m_map->GetDecorMap();

	for (int i = startingID.x - 5; i < endID.x + 5; i++)
	{
		for (int j = startingID.y - 5; j < endID.y + 5; j++)
		{
			if (i < decorMap.size() && i >= 0 && j < decorMap[i].size() && j >= 0)
			{
				if (decorMap[i][j] >= (SLMap::DecorTiles)15)
				{
					m_shaders.AddLight(m_map->GetTileCenter(sf::Vector2i(i, j)), 2);
				}
			}
		}
	}

	if (m_mapString == "SoulsLevel")
	{
		m_shaders.AddLight(m_tutorial->GetSpiritPosition(), 2);
		m_shaders.AddLight(m_tutorial->GetGemPos(), 3);
	}

	m_shaders.AddLight(m_player.GetPosition(), 5);
	m_shaders.AddLight(m_boss.GetPosition(), 7);

	if (m_mapString == "SoulsLevel")
	{
		std::vector<sf::Vector2f> stageAttacks = m_boss.GetStageAttacksPos();
		std::vector<sf::Vector2f> bossAttacks = m_boss.GetAttacksPos();

		for (int i = 0; i < stageAttacks.size(); i++)
		{
			m_shaders.AddLight(stageAttacks[i], 0.5f);
		}

		for (int i = 0; i < bossAttacks.size(); i++)
		{
			m_shaders.AddLight(bossAttacks[i], 1.5f);
		}

		if (m_mapString == "SoulsLevel")
		{
			m_tutorial->Display(_window);
		}

		m_shaders.ApplyLights(_window);

		if (m_tutorial->IsInBossFight())
		{
			m_boss.DisplayHealthBar(_window);
		}
	}

	m_HUD.Display(_window, m_player.GetLockedMode());

	if (m_mapString != "SoulsBoss")
	{
		if (!m_tutorial->GetCinematicMode())
		{
			m_miniMap->Display(_window, m_player.GetFVector());
		}

		m_tutorial->DisplayPopUps(_window);
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////


void SoulsLevel::CreateEnemies()
{
	for (int i = 0; i < m_map->GetEnemyTiles().size(); i++)
	{
		SLEnemy tempEnemy;

		std::vector<sf::Vector2i> availableTiles = m_map->GetEnemyTiles();
		SLEnemy::EnemyType enemyType;

		if (m_map->GetTileTypeData(availableTiles[i]) == SLMap::DataTiles::ROSCASS)
		{
			enemyType = SLEnemy::ROSCASS;
		}
		else if (m_map->GetTileTypeData(availableTiles[i]) == SLMap::DataTiles::MELEE)
		{
			enemyType = SLEnemy::FALKYN;
		}

		tempEnemy.Create(m_map->GetTileCenter(availableTiles[i]), enemyType);
		m_enemies.push_back(tempEnemy);
	}
}

void SoulsLevel::UpdateMapCollisions(float _dt)
{
	sf::Vector2i playerTile = m_map->GetTileID(m_player.GetPosition());
	sf::Vector2i bossTile = m_map->GetTileID(m_boss.GetPosition());
	std::vector<sf::Vector2i> enemyTiles;

	for (int i = 0; i < m_enemies.size(); i++)
	{
		enemyTiles.push_back(m_map->GetTileID(m_enemies[i].GetPosition()));
	}

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			// Player
			sf::Vector2i tileID = playerTile + sf::Vector2i(i, j);

			SLMap::CollisionTiles tileType = m_map->GetTileTypeCollision(tileID);

			sf::FloatRect tileBounds = m_map->GetTileBounds(tileID);

			if (Collisions::IsCollidingRectRect(tileBounds, m_player.GetHitbox()) && (tileType == SLMap::CollisionTiles::WALL || tileType == SLMap::CollisionTiles::INVISIBLE_WALL))
			{
				if (m_boss.IsDashing())
				{
					m_player.SetVelocity(m_boss.GetVelocity());
					m_boss.CancelMovement();
					m_boss.CancelDashHitbox();
				}

				m_player.CancelMovement();
			}

			// Si le joueur sort de la map, le renvoie au spawn
			sf::Vector2i newTileID = m_map->GetTileID(m_player.GetPosition()) + sf::Vector2i(i, j);
			SLMap::CollisionTiles newTileType = m_map->GetTileTypeCollision(newTileID);
			sf::FloatRect newTileBounds = m_map->GetTileBounds(newTileID);

			if (newTileType == SLMap::CollisionTiles::DEATH_TILE && Collisions::IsCollidingRectRect(newTileBounds, m_player.GetHitbox()))
			{
				m_player.SetPosition(m_map->GetTileCenter(m_map->GetPlayerTile()));
				return;
			}

			// Collisions du bonnet du joueur
			for (int k = 0; k < m_player.GetAttackVector().size(); k++)
			{
				SLEntity::Attack& currentAttack = m_player.GetAttackVector()[k];

				if (m_map->GetTileTypeCollision(m_map->GetTileID(currentAttack.pos)) == SLMap::CollisionTiles::WALL || m_map->GetTileTypeCollision(m_map->GetTileID(currentAttack.pos)) == SLMap::CollisionTiles::INVISIBLE_WALL)
				{
					currentAttack.hitbox.left -= currentAttack.dirVec.x * currentAttack.speed * _dt;
					currentAttack.hitbox.top -= currentAttack.dirVec.y * currentAttack.speed * _dt;
					currentAttack.pos = sf::Vector2f(currentAttack.hitbox.left + currentAttack.hitbox.width / 2.f, currentAttack.hitbox.top + currentAttack.hitbox.height / 2.f);
					currentAttack.sprite.setPosition(currentAttack.pos);
				}
			}

			// Ennemis
			for (int k = 0; k < m_enemies.size(); k++)
			{
				tileID = enemyTiles[k] + sf::Vector2i(i, j);

				tileType = m_map->GetTileTypeCollision(tileID);
				tileBounds = m_map->GetTileBounds(tileID);

				if (Collisions::IsCollidingRectRect(tileBounds, m_enemies[k].GetHitbox()) && (tileType == SLMap::CollisionTiles::WALL || tileType == SLMap::CollisionTiles::INVISIBLE_WALL))
				{
					m_enemies[k].SetPosition(m_enemies[k].GetPosition() - m_enemies[k].GetVelocity());
				}

				// Collisions attaques (projectiles) des enemis
				for (int l = 0; l < m_enemies[k].GetAttackVector().size(); l++)
				{
					SLEnemy::Attack currentAttack = m_enemies[k].GetAttackVector()[l];

					if (m_map->GetTileTypeCollision(m_map->GetTileID(currentAttack.pos)) == SLMap::CollisionTiles::WALL || m_map->GetTileTypeCollision(m_map->GetTileID(currentAttack.pos)) == SLMap::CollisionTiles::INVISIBLE_WALL)
					{
						m_enemies[k].DeleteAttack(l);
					}
				}
			}

			// Boss
			tileID = bossTile + sf::Vector2i(i, j);

			tileType = m_map->GetTileTypeCollision(tileID);
			tileBounds = m_map->GetTileBounds(tileID);
			if (Collisions::IsCollidingRectRect(tileBounds, m_boss.GetHitbox()) && (tileType == SLMap::CollisionTiles::WALL || tileType == SLMap::CollisionTiles::INVISIBLE_WALL))
			{
				m_boss.CancelMovement();
				m_boss.CancelDashHitbox();
			}
		}
	}
}

void SoulsLevel::UpdatePlayerEnemiesCollisions()
{
	for (unsigned int i = 0; i < m_onScreenEnemies.size(); i++)
	{
		// Collisions attaques du joueur -> ennemis
		for (unsigned int j = 0; j < m_player.GetAttackVector().size(); j++)
		{
			SLPlayer::Attack currentAttack = m_player.GetAttackVector()[j];

			if ((currentAttack.type == SLPlayer::AttackType::DEFAULT && m_player.GetAnimationState() == AnimationManager::ACTIVE) || currentAttack.type == SLPlayer::SPECIAL)
			{
				if (Collisions::IsCollidingRectRect(currentAttack.hitbox, m_onScreenEnemies[i]->GetHitbox()) && !m_onScreenEnemies[i]->IsInvincible() && m_onScreenEnemies[i]->GetHP() > 0)
				{
					m_onScreenEnemies[i]->DecreaseHP(currentAttack.damage);
					m_onScreenEnemies[i]->SetInvincibilityTimer(0.35f);

					m_sounds.PlaySFX("Player_Hit", false, 100.f, m_player.GetPosition());

					if (m_onScreenEnemies[i]->GetState() == SLEnemy::WANDERING)
					{
						m_onScreenEnemies[i]->SetState(SLEnemy::GAINED_AGGRO);
					}
					else if (m_onScreenEnemies[i]->GetState() == SLEnemy::SEARCHING || m_onScreenEnemies[i]->GetState() == SLEnemy::LOST_AGGRO)
					{
						m_onScreenEnemies[i]->SetState(SLEnemy::AGGROING);
					}

					if (currentAttack.type != SLPlayer::AttackType::SPECIAL)
					{
						m_player.DeleteAttack(j);
					}
				}
			}
		}

		// Collions joueur -> ennemi (qu'il lui marche pas dessus)
		if (Collisions::IsCollidingRectRect(m_player.GetHitbox(), m_onScreenEnemies[i]->GetHitbox()) && m_onScreenEnemies[i]->GetHP() > 0)
		{
			m_player.CancelMovement();
		}

		//Collision attaques des ennemis -> joueur
		for (int j = 0; j < m_onScreenEnemies[i]->GetAttackVector().size(); j++)
		{
			if ((m_onScreenEnemies[i]->GetAnimationState() == AnimationManager::ACTIVE && m_onScreenEnemies[i]->GetType() == SLEnemy::FALKYN) || m_onScreenEnemies[i]->GetType() == SLEnemy::ROSCASS)
			{
				SLEnemy::Attack currentAttack = m_onScreenEnemies[i]->GetAttackVector()[j];
				if (Collisions::IsCollidingRectRect(currentAttack.hitbox, m_player.GetHitbox()) && !m_player.IsInvincible())
				{
					m_player.DecreaseHP(currentAttack.damage);
					m_player.SetInvincibilityTimer(0.5f);
					m_onScreenEnemies[i]->DeleteAttack(j);

					if (m_onScreenEnemies[i]->GetType() == SLEnemy::ROSCASS)
					{
						m_sounds.PlaySFX("Roscass_Hit", false, 100.f, m_player.GetPosition());
					}
					else
					{
						m_sounds.PlaySFX("Falkyn_Hit", false, 100.f, m_player.GetPosition());
					}
				}
			}
		}

		// Suppression de l'ennemi si il n'a plus d'HP
		if (m_onScreenEnemies[i]->GetHP() <= 0)
		{
			if (m_onScreenEnemies[i]->Kill())
			{
				if (m_onScreenEnemies[i]->GetType() == SLEnemy::FALKYN) m_player.RestoreHealth(20);
				else if (m_onScreenEnemies[i]->GetType() == SLEnemy::ROSCASS) m_player.RestoreMana(15);

				bool relock = false;
				if (GetEnemyID(m_onScreenEnemies[i]) == m_player.GetLockedEnemyID())
				{
					relock = true;
				}

				m_enemies.erase(m_enemies.begin() + GetEnemyID(m_onScreenEnemies[i]));
				GetOnScreenEnemies();

				if (relock)
				{
					m_player.SetLockedEnemyID(-1);
					LockEnemy();
				}
			}
		}
	}
}

void SoulsLevel::UpdatePlayerBossCollision(float _dt)
{
	// Collisions attaque boss -> joueur
	for (int j = 0; j < m_boss.GetAttackVector().size(); j++)
	{
		SLBoss::Attack currentAttack = m_boss.GetAttackVector()[j];
		if (Collisions::IsCollidingRectRect(currentAttack.hitbox, m_player.GetHitbox()) && !m_player.IsInvincible())
		{
			if (m_boss.GetFrameType() == AnimationManager::ACTIVE && !m_boss.GetPlayerHit()) // "!m_boss.GetPlayerHit()" : Si une attaque du boss a touché, elle ne peux pas mettre plusieurs fois des dégats au joueur
			{
				m_sounds.PlaySFX("Boss_Hit", false, 100.f, m_player.GetPosition());
				m_player.DecreaseHP(m_boss.GetAttackVector()[j].damage);
				m_player.SetInvincibilityTimer(0.5f);
				m_boss.SetPlayerHit();
			}
		}
	}

	// Collisions attaque joueur -> boss
	for (unsigned int j = 0; j < m_player.GetAttackVector().size(); j++)
	{
		SLPlayer::Attack currentAttack = m_player.GetAttackVector()[j];
		if (Collisions::IsCollidingRectRect(currentAttack.hitbox, m_boss.GetHitbox()) && !m_boss.IsInvincible())
		{
			m_boss.DecreaseHP(currentAttack.damage);
			m_boss.SetInvincibilityTimer(0.5f);
			m_sounds.PlaySFX("Player_Hit", false, 100.f, m_player.GetPosition());
			if (currentAttack.type != SLPlayer::AttackType::SPECIAL)
			{
				m_player.DeleteAttack(j);
			}
		}
	}

	// Collisions déplacements
	if (Collisions::IsCollidingRectRect(m_player.GetHitbox(), m_boss.GetHitbox()))
	{
		if (m_boss.IsDashing())
		{
			m_player.SetVelocity(m_player.GetVelocity() - m_boss.GetVelocity());
		}
		m_player.CancelMovement();
	}
}

void SoulsLevel::CheckWinAndLossCondition()
{
	if (m_player.GetHP() <= 0)
	{
		m_hasLost = true;
	}

	sf::Vector2i playerTile = m_map->GetTileID(m_player.GetPosition());

	if (m_tutorial->HasWon())
	{
		m_hasWon = true;
	}
}

void SoulsLevel::GetOnScreenEnemies()
{
	m_onScreenEnemies.clear();
	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		sf::Vector2f enemyPos = m_enemies[i].GetPosition();
		sf::Vector2f enemySize = m_enemies[i].GetSize();

		if (enemyPos.x + enemySize.x / 2.f >= m_camera.GetBounds().left - m_camera.GetBounds().width / 2.f
			&& enemyPos.x - enemySize.x / 2.f <= m_camera.GetBounds().left + m_camera.GetBounds().width * 1.5f
			&& enemyPos.y + enemySize.y / 2.f >= m_camera.GetBounds().top - m_camera.GetBounds().height / 2.f
			&& enemyPos.y - enemySize.y / 2.f <= m_camera.GetBounds().top + m_camera.GetBounds().height * 1.5f)
		{
			m_onScreenEnemies.push_back(&m_enemies[i]);
		}
	}
}

void SoulsLevel::LockEnemy()
{
	int enemyID = -1;
	float min = FLT_MAX;

	for (int i = 0; i < m_onScreenEnemies.size(); i++)
	{
		m_onScreenEnemies[i]->SetLockedStatus(false);
		sf::Vector2f playerEnemyVec = CreaMaths::CreateVector(m_player.GetPosition(), m_onScreenEnemies[i]->GetPosition());
		float distanceToPlayer = CreaMaths::GetSquaredLength(playerEnemyVec);

		sf::Vector2f enemyPos = m_onScreenEnemies[i]->GetPosition();
		sf::Vector2f enemySize = m_onScreenEnemies[i]->GetSize();

		if (distanceToPlayer < min && Collisions::IsCollidingRectPoint(m_player.GetLockHitbox(), m_onScreenEnemies[i]->GetPosition()))
		{
			min = distanceToPlayer;
			enemyID = i;
		}
	}

	if (enemyID == -1)
	{
		m_player.SetLockedMode(false);
		m_player.SetLockedEnemyID(-1);
	}
	else
	{
		m_player.SetLockedMode(true);
		m_player.SetLockedEnemyID(GetEnemyID(m_onScreenEnemies[enemyID]));
		m_player.SetLockedTarget(m_enemies[m_player.GetLockedEnemyID()].GetPosition());
		m_onScreenEnemies[enemyID]->SetLockedStatus(true);
		m_sounds.PlaySFX("Player_Lock", true);
	}
}

void SoulsLevel::UpdateLockMechanic()
{
	// Lock : Ctrl gauche ou R3
	static bool lockKeyDown = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Joystick::isButtonPressed(0, (int)ControllerButton::R3))
	{
		if (!lockKeyDown)
		{
			lockKeyDown = true;

			if (m_tutorial->IsInBossFight())
			{
				if (m_player.GetLockedMode())
				{
					m_player.SetLockedMode(false);
				}
				else
				{
					if (Collisions::IsCollidingRectPoint(m_player.GetLockHitbox(), m_boss.GetPosition()))
					{
						m_player.SetLockedMode(true);
						m_player.SetLockedTarget(m_boss.GetPosition());
						m_sounds.PlaySFX("Player_Lock", true);
					}
				}
			}
			else
			{
				if (m_player.GetLockedMode())
				{
					m_player.SetLockedMode(false);
					m_player.SetLockedEnemyID(-1);
				}
				else
				{
					m_player.SetLockedMode(true);
					LockEnemy();
				}
			}
		}
	}
	else
	{
		lockKeyDown = false;
	}

	if (m_player.GetLockedMode())
	{
		// Changement de target
		static bool switched = false;

		sf::Vector2f rightJoystick(sf::Joystick::getAxisPosition(0, sf::Joystick::U) / 100.f, sf::Joystick::getAxisPosition(0, sf::Joystick::V) / 100.f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) rightJoystick = { 0,-1 };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) rightJoystick = { 0, 1 };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) rightJoystick = { -1, 0 };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) rightJoystick = { 1, 0 };

		if ((abs(rightJoystick.x) > 0.3 || abs(rightJoystick.y) > 0.3))
		{
			if (!switched)
			{
				switched = true;
				SwitchTarget(rightJoystick);
			}
		}
		else
		{
			switched = false;
		}

		if (m_tutorial->IsInBossFight())
		{
			m_camera.SetTarget(m_player.GetPosition() + CreaMaths::CreateVector(m_player.GetPosition(), m_boss.GetPosition()) / 2.f);
			m_player.SetLockedTarget(m_boss.GetPosition());
		}
		else
		{
			m_player.SetLockedTarget(m_enemies[m_player.GetLockedEnemyID()].GetPosition());
			m_camera.SetTarget(m_player.GetPosition() + CreaMaths::CreateVector(m_player.GetPosition(), m_enemies[m_player.GetLockedEnemyID()].GetPosition()) / 2.f);
		}
		m_camera.SetDeadZone(10);
	}
}

void SoulsLevel::SwitchTarget(sf::Vector2f _vectorJoystick)
{
	int lockedEnemyID = m_player.GetLockedEnemyID();

	float min = FLT_MAX;
	float newTargetID = -1;

	for (int i = 0; i < m_onScreenEnemies.size(); i++)
	{
		if (GetEnemyID(m_onScreenEnemies[i]) != lockedEnemyID)
		{
			if (Collisions::IsCollidingRectPoint(m_player.GetLockHitbox(), m_onScreenEnemies[i]->GetPosition()))
			{
				sf::Vector2f oldToNewTargetVector = CreaMaths::CreateVector(m_enemies[lockedEnemyID].GetPosition(), m_onScreenEnemies[i]->GetPosition());

				if (CreaMaths::DotProduct(_vectorJoystick, oldToNewTargetVector) > 0)
				{
					if (CreaMaths::GetSquaredDistance(oldToNewTargetVector) < min)
					{
						min = CreaMaths::GetSquaredDistance(oldToNewTargetVector);
						newTargetID = i;
					}
				}
			}
		}
	}

	if (newTargetID >= 0)
	{
		m_player.SetLockedTarget(m_onScreenEnemies[newTargetID]->GetPosition());
		m_player.SetLockedEnemyID(GetEnemyID(m_onScreenEnemies[newTargetID]));
	}
}

int SoulsLevel::GetEnemyID(SLEnemy* _enemyPtr)
{
	auto it = std::find_if(m_enemies.begin(), m_enemies.end(), [&](const SLEnemy& enemy)
		{
			return &enemy == _enemyPtr;
		});

	if (it != m_enemies.end())
	{
		return std::distance(m_enemies.begin(), it);
	}
	else
	{
		return -1;
	}
}

void SoulsLevel::UpdateEnemies(float _dt)
{
	GetOnScreenEnemies();

	for (int i = 0; i < m_onScreenEnemies.size(); i++)
	{
		sf::Vector2f playerEnemyVector = CreaMaths::CreateVector(m_player.GetPosition(), m_onScreenEnemies[i]->GetPosition());

		m_onScreenEnemies[i]->Update(_dt);
		m_onScreenEnemies[i]->SetPlayerPos(m_player.GetPosition());
		m_onScreenEnemies[i]->SetTarget(m_player.GetHitboxCenter());

		if (GetEnemyID(m_onScreenEnemies[i]) != m_player.GetLockedEnemyID())
			m_onScreenEnemies[i]->SetLockedStatus(false);
		else
			m_onScreenEnemies[i]->SetLockedStatus(true);

	}
}