#include "SLTutorial.h"

SLTutorial::SLTutorial(Camera* _camera, SLPlayer* _player, SLMap* _map, SLBoss* _boss, std::string _mapString)
{
	m_shader.loadFromFile("Assets/Souls/Shaders/blur.frag", sf::Shader::Fragment);
	m_shader.setUniform("screenSize", sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	m_shader.setUniform("intensity", 6.f);

	m_currentEvent = INITIAL_ANIM;
	m_door = 0;

	m_map = _map;
	m_player = _player;
	m_camera = _camera;
	m_boss = _boss;

	m_desatShader.loadFromFile("Assets/Souls/Shaders/desaturate.frag", sf::Shader::Fragment);
	m_desatShader.setUniform("saturation", 0.2f);

	m_bossSprite = LoadSprite("Assets/Souls/Boss/Activating/0.png", true);
	m_gemSprite = LoadSprite("Assets/Souls/Misc/Gem.png", true);

	m_evilSpirit = LoadSprite("Assets/Souls/Misc/evilSpirit.png", true);
	m_evilSpirit.setColor(sf::Color::Transparent);
	m_spirit.sprite = LoadSprite("Assets/Souls/Misc/spirit.png", true);
	m_spirit.state = WAITING;
	m_spirit.amplitude = 25;
	m_spirit.speed = 2.5f;
	m_spirit.movementSpeed = 200.f;

	m_pause = false;
	m_timer = 0;

	m_tileList[INITIAL_ANIM] = sf::Vector2f(129, 67);
	m_tileList[NORMAL_ATTACK] = sf::Vector2f(129, 67);
	m_tileList[DODGE] = sf::Vector2f(129, 67);
	m_tileList[HUD] = sf::Vector2f(129, 67);
	m_tileList[SPECIAL_ATTACK] = sf::Vector2f(117, 67);
	m_tileList[LOCK] = sf::Vector2f(103, 67);
	m_tileList[SWITCH_TARGET] = sf::Vector2f(95.5f, 78);
	m_tileList[SHROOMS] = sf::Vector2f(69, 65);
	m_tileList[BOSS_CORRIDOR] = sf::Vector2f(69, 42);

	m_champiTiles[0] = sf::Vector2f(36, 63);
	m_champiTiles[1] = sf::Vector2f(13, 113);
	m_champiTiles[2] = sf::Vector2f(119, 168);

	sf::Sprite sprite(LoadSprite("Assets/Souls/Map/15.png", true));
	sf::Vector2u size = sprite.getTexture()->getSize();
	sprite.setOrigin(size.x / 2.f, size.y);

	for (int i = 0; i < 3; i++)
	{
		m_champiSprite[i] = sprite;
	}

	InitRonces(_mapString);

	for (int i = 0; i < NUMBER_OF_EVENTS; i++)
	{
		if (i != INITIAL_ANIM && i != SHROOMS && i != BOSS_CORRIDOR && i != BOSS_END)
		{
			m_popUp[i][KEYBOARD] = LoadSprite(std::format("Assets/Souls/Tutorial/PopUps/Keyboard/tuto{}.png", i), true);
			m_popUp[i][CONTROLLER] = LoadSprite(std::format("Assets/Souls/Tutorial/PopUps/Controller/tuto{}.png", i), true);

			m_popUp[i][KEYBOARD].setScale(0, 0);
			m_popUp[i][CONTROLLER].setScale(0, 0);

			InitVideoPreviews(i);
		}

		m_tileList[i] *= 32.f;
		m_tileList[i] += sf::Vector2f(16, 16);

		if (i < 3)
		{
			m_champiTiles[i] *= 32.f;
			m_champiTiles[i] += sf::Vector2f(16, 16);
		}
	}

	m_spirit.pos = m_tileList[m_currentEvent];
	m_spirit.onScreenPos = m_spirit.pos;
	m_spirit.target = m_spirit.pos;

	m_musicVolume = 25.f;

	m_currentTheme.openFromFile("Assets/Souls/Sounds/BGM/Level.wav");
	m_currentTheme.setLoop(true);
	m_currentTheme.setVolume(m_musicVolume);
	m_currentTheme.play();

	m_windowContent.create(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_windowSprite.setTexture(m_windowContent);
}

void SLTutorial::Update(float _dt, Config _config)
{
	m_activeTargets.clear();
	if (m_currentEvent != BOSS_END)
	{
		m_activeTargets.push_back(m_spirit.pos);
	}

	m_currentConfig = _config;

	if (m_currentEvent == SHROOMS && m_door == 5)
	{
		UpdateShroomStates();
	}

	PlayCinematic(_dt);

	m_skippable = false;

	if (m_player->GetHP() <= 0)
	{
		m_currentTheme.stop();
	}

	m_currentTheme.setVolume(m_musicVolume);
}

void SLTutorial::Display(sf::RenderWindow& _window)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < m_ronces[i].sprites.size(); j++)
		{
			m_ronces[i].sprites[j].sprite.setPosition(m_ronces[i].sprites[j].pos);
			_window.draw(m_ronces[i].sprites[j].sprite);
		}

		m_champiSprite[i].setPosition(m_champiTiles[i].x, m_champiTiles[i].y + 16.f);
		_window.draw(m_champiSprite[i]);
	}

	if (m_currentEvent >= BOSS_CORRIDOR && !m_isInBossFight)
	{
		if (m_currentEvent == BOSS_CORRIDOR)
		{
			m_bossSprite.setPosition(sf::Vector2f(69 * 32.f + 16, 14 * 32.f + 16));
		}

		_window.draw(m_bossSprite, &m_desatShader);
	}

	if (m_currentEvent == BOSS_END && m_door >= 4)
	{
		_window.draw(m_gemSprite);
	}

	for (int i = 0; i < 5; i++)
	{
		_window.draw(m_pieux[i]);
	}

	_window.draw(m_spirit.sprite);
	_window.draw(m_evilSpirit);
}

void SLTutorial::DisplayPopUps(sf::RenderWindow& _window)
{
	m_windowContent.update(_window);

	if (m_currentEvent == DODGE || m_currentEvent == HUD)
	{
		m_pause = true;
	}

	if (m_currentEvent != INITIAL_ANIM && m_currentEvent != BOSS_CORRIDOR && m_currentEvent != SHROOMS)
	{
		if (m_pause)
		{
			DisplayTutorialPopUp(_window);
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////


void SLTutorial::ToggleNextEvent()
{
	if (m_currentEvent < NUMBER_OF_EVENTS)
	{
		m_currentEvent = EventList(m_currentEvent + 1);
	}

	m_pause = false;
	m_isInCinematicMode = false;
	m_spirit.pos = m_spirit.onScreenPos;
	m_door = 0;
	m_timer = 0;
}

void SLTutorial::UpdateSpiritMovement(float _dt)
{
	static sf::Clock movementClock;
	sf::Vector2f posTargetVec = CreaMaths::CreateVector(m_spirit.pos, m_spirit.target);
	sf::Vector2f velocity2(0, 0);

	m_spirit.velocity = sf::Vector2f(0, 0);

	if (CreaMaths::GetSquaredDistance(posTargetVec) < 2 * 2)
	{
		if (m_spirit.state == FOLLOWING)
		{
			movementClock.restart();
			m_spirit.speed = 2.5f;
			m_spirit.amplitude = 25.f;
		}

		m_spirit.state = WAITING;
	}
	else
	{
		if (m_spirit.state == WAITING)
		{
			m_spirit.pos = m_spirit.onScreenPos;
			m_spirit.speed = 3.5f;
			m_spirit.amplitude = 15.f;
		}

		m_spirit.state = FOLLOWING;
	}

	if (m_spirit.state == WAITING)
	{
		m_spirit.pos = m_spirit.target;

		m_spirit.velocity.x = sinf(movementClock.getElapsedTime().asSeconds() * m_spirit.speed) * m_spirit.amplitude;
		m_spirit.velocity.y = sinf(movementClock.getElapsedTime().asSeconds() * m_spirit.speed * 2.f) * m_spirit.amplitude / 2.5f;

		m_spirit.velocity.x *= (1 * posTargetVec.x > 0) - (1 * posTargetVec.x <= 0);
		m_spirit.velocity.y *= (1 * posTargetVec.y > 0) - (1 * posTargetVec.y <= 0);
	}
	else if (m_spirit.state == FOLLOWING)
	{
		sf::Vector2f forwardVector = CreaMaths::CreateVector(m_spirit.pos, m_spirit.target);
		CreaMaths::ClampLength(forwardVector, 1);

		m_spirit.velocity = forwardVector * m_spirit.movementSpeed * _dt;

		m_spirit.pos += m_spirit.velocity;

		m_spirit.velocity.x = sinf(movementClock.getElapsedTime().asSeconds() * m_spirit.speed) * m_spirit.amplitude * -forwardVector.y;
		m_spirit.velocity.y = sinf(movementClock.getElapsedTime().asSeconds() * m_spirit.speed) * m_spirit.amplitude * forwardVector.x;
	}

	m_spirit.onScreenPos = m_spirit.pos + m_spirit.velocity;
	m_spirit.sprite.setPosition(m_spirit.onScreenPos);
}

void SLTutorial::DisplayTutorialPopUp(sf::RenderWindow& _window)
{
	float scale = 1.f;
	float maxTime = 0.5f;
	float timer = m_easingsClock.getElapsedTime().asSeconds();
	m_skippable = false;

	if (timer <= maxTime)
	{
		scale = Easing::easeOutQuint(timer, 0, 1, maxTime);
	}
	else
	{
		m_skippable = true;
	}

	if (m_currentEvent == DODGE || m_currentEvent == HUD)
	{
		scale = 1.f;
	}

	m_windowSprite.setPosition(_window.getView().getCenter() - _window.getView().getSize() / 2.f);
	m_windowSprite.setScale(_window.getView().getSize().x / _window.getSize().x, _window.getView().getSize().y / _window.getSize().y);
	m_windowSprite.setColor(sf::Color(255, 255, 255, scale));

	m_shader.setUniform("intensity", 6.f * scale);
	_window.draw(m_windowSprite, &m_shader);

	m_popUp[m_currentEvent][m_currentConfig].setPosition(_window.getView().getCenter());
	m_popUp[m_currentEvent][m_currentConfig].setScale(sf::Vector2f(scale, scale));

	//fond noir
	sf::Image image;
	image.create(m_popUp[m_currentEvent][m_currentConfig].getGlobalBounds().width, m_popUp[m_currentEvent][m_currentConfig].getGlobalBounds().height, sf::Color::Black);

	sf::Texture texture;
	texture.loadFromImage(image);

	sf::Sprite sprite(texture);
	sprite.setPosition(m_popUp[m_currentEvent][m_currentConfig].getPosition());
	sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);

	_window.draw(sprite);

	// Preview vidéo
	if (scale == 1.f)
	{
		m_previewVideos[m_currentEvent].Update();
		if (m_previewVideos[m_currentEvent].GetState() != sfe::Playing)
		{
			m_previewVideos[m_currentEvent].Play();
		}

		sf::FloatRect videoBounds = m_popUp[m_currentEvent][m_currentConfig].getGlobalBounds();

		videoBounds.width = 139.f;
		videoBounds.height = 126.f;

		videoBounds.left += 26.f + videoBounds.width / 2.f;
		videoBounds.top += 70.f + videoBounds.height / 2.f;

		videoBounds.width = m_popUp[m_currentEvent][m_currentConfig].getGlobalBounds().width;

		m_previewVideos[m_currentEvent].Fit(videoBounds);

		m_previewVideos[m_currentEvent].SetOrigin(sf::Vector2f(videoBounds.width / 2.f, videoBounds.height / 2.f));
		m_previewVideos[m_currentEvent].Draw(&_window);
	}

	_window.draw(m_popUp[m_currentEvent][m_currentConfig]);
}

void SLTutorial::PlayCinematic(float _dt)
{
	if (!(m_currentEvent == INITIAL_ANIM && m_door == 2) && m_currentEvent != BOSS_END)
		UpdateSpiritMovement(_dt);

	if (m_currentEvent != BOSS_CORRIDOR)
		m_spirit.target = m_tileList[m_currentEvent];

	sf::Vector2f playerTileVector = CreaMaths::CreateVector(m_tileList[m_currentEvent], m_player->GetPosition());
	sf::Vector2f spiritTargetVector = CreaMaths::CreateVector(m_spirit.pos, m_spirit.target);

	float triggerDistance = 25.f;

	if (m_currentEvent != INITIAL_ANIM && m_currentEvent != SHROOMS && m_currentEvent != BOSS_CORRIDOR && m_currentEvent != BOSS_END)
	{
		if (IsCollidingTriggerTile())
		{
			if (!m_pause)
			{
				if (m_currentEvent != DODGE && m_currentEvent != HUD)
				{
					m_sounds.PlaySFX("PopUp", true);
				}
				m_easingsClock.restart();
				m_pause = true;
			}

			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::F) || sf::Joystick::isButtonPressed(0, (int)ControllerButton::A)) && m_skippable)
			{
				m_easingsClock.restart();
				if (m_currentEvent != NORMAL_ATTACK && m_currentEvent != DODGE)
				{
					OverWriteTrigger();
				}

				m_sounds.PlaySFX("Clic", true);
				ToggleNextEvent();
			}
		}
	}
	else if (m_currentEvent == INITIAL_ANIM)
	{
		m_spirit.target = m_spirit.pos;
		m_player->ForceIdle();

		sf::Vector2f posTargetVec = CreaMaths::CreateVector(m_spirit.pos, m_spirit.target);
		sf::Vector2f spiritPlayerVec = CreaMaths::CreateVector(m_spirit.onScreenPos, m_player->GetPosition());

		switch (m_door)
		{
		case 0:
			m_isInCinematicMode = true;
			m_timer += _dt;

			if (m_timer > 1.f)
			{
				m_door++;
			}
			break;

		case 1:
			m_spirit.target = m_player->GetPosition() - sf::Vector2f(32, 0);
			posTargetVec = CreaMaths::CreateVector(m_spirit.pos, m_spirit.target);

			if (CreaMaths::GetSquaredDistance(posTargetVec) < 2 * 2)
			{
				m_door++;
				m_timer = 0;
			}
			break;

		case 2:
			CreaMaths::ClampLength(spiritPlayerVec, 1);

			m_timer += _dt;
			m_spirit.onScreenPos.x -= -spiritPlayerVec.y * _dt * m_spirit.movementSpeed;
			m_spirit.onScreenPos.y -= spiritPlayerVec.x * _dt * m_spirit.movementSpeed;

			m_spirit.sprite.setPosition(m_spirit.onScreenPos);

			if (m_timer > 1.15f)
			{
				m_door++;
			}
			break;

		case 3:
			m_spirit.target = m_tileList[INITIAL_ANIM];
			posTargetVec = CreaMaths::CreateVector(m_spirit.pos, m_spirit.target);
			m_camera->SetTarget(m_spirit.pos);

			if (CreaMaths::GetSquaredDistance(posTargetVec) < 2 * 2)
			{
				ToggleNextEvent();
			}
			break;
		}
	}
	else if (m_currentEvent == SHROOMS)
	{
		bool atLeastOneActive = false;
		static float scale = 1.f;
		sf::IntRect textureRect;
		int ronceID = -1;
		static float champiScale = 1.f;

		sf::Vector2f mescouillesFor;

		switch (m_door)
		{
		case 0:
			if (IsCollidingTriggerTile())
			{
				m_isInCinematicMode = true;
				OverWriteTrigger();

				m_camera->SetDeadZone(5.f);
				m_camera->SetSpeed(3.5f);

				m_door++;
			}
			break;

		case 5:
			m_isInCinematicMode = false;
			atLeastOneActive = false;
			m_timer = 0;

			m_activeTargets.clear();
			for (int i = 0; i < 3; i++)
			{
				if (m_ronces[i].active)
				{
					atLeastOneActive = true;
					m_activeTargets.push_back(m_champiTiles[i]);
				}
			}

			if (!atLeastOneActive)
			{
				ToggleNextEvent();
			}
			break;

		case 6:
			m_isInCinematicMode = true;

			if (m_easingsClock.getElapsedTime().asSeconds() < 1.f)
			{
				champiScale = 0.5f + Easing::easeOutElastic(m_easingsClock.getElapsedTime().asSeconds(), 0, 0.5f, 1.5f);
				m_champiSprite[m_ronceToRetract].setScale(1, champiScale);
			}
			else
			{
				m_champiSprite[m_ronceToRetract].setScale(1, 1);
				sf::Vector2i invertedTile(m_ronces[m_ronceToRetract].tileList[2].y, m_ronces[m_ronceToRetract].tileList[2].x);
				m_camera->SetTarget(m_map->GetTileCenter(invertedTile));
				m_camera->SetDeadZone(5.f);

				m_door++;
			}
			break;

		case 7:
			m_timer += _dt;

			if (m_timer > 0.5f)
			{
				if (m_camera->IsOnTarget())
				{
					m_sounds.PlaySFX("Ronces", true);

					m_door++;
				}
			}

			break;

		case 8:
			if (m_ronces[m_ronceToRetract].dir == 0)
			{
				mescouillesFor.x = m_ronces[m_ronceToRetract].sprites.size();
				mescouillesFor.y = -1;
			}
			else if (m_ronces[m_ronceToRetract].dir == 1)
			{
				mescouillesFor.x = 0;
				mescouillesFor.y = m_ronces[m_ronceToRetract].sprites.size();
			}

			for (int i = mescouillesFor.x; m_ronces[m_ronceToRetract].dir ? i < mescouillesFor.y : i > mescouillesFor.y; i += m_ronces[m_ronceToRetract].dir - !m_ronces[m_ronceToRetract].dir)
			{
				textureRect = m_ronces[m_ronceToRetract].sprites[i].sprite.getTextureRect();

				if (m_ronces[m_ronceToRetract].sprites[i].sprite.getScale().x != 0)
				{
					ronceID = i;
					break;
				}
			}

			if (m_ronces[m_ronceToRetract].anim.HasEnded())
			{
				for (int i = 0; i < m_ronces[m_ronceToRetract].sprites.size(); i++)
					m_ronces[m_ronceToRetract].sprites[i].sprite.setScale(0, 0);

				scale = 1.f;
				m_isInCinematicMode = false;
				m_door = 5;
			}
			else
			{
				if (scale <= 0.f)
				{
					scale = 1.f;
					m_ronces[m_ronceToRetract].sprites[ronceID].sprite.setScale(0, 0);
				}

				scale -= _dt * 5.f;

				if (m_ronces[m_ronceToRetract].sprites[ronceID].type != START)
				{
					textureRect = m_ronces[m_ronceToRetract].sprites[ronceID].sprite.getTextureRect();

					textureRect.width = 32.f;
					textureRect.height = 32.f;

					textureRect.width *= scale;

					m_ronces[m_ronceToRetract].sprites[ronceID].sprite.setTextureRect(textureRect);
				}
				else
				{
					m_ronces[m_ronceToRetract].anim.PlayAnimation("Assets/Souls/Boss/StageAttack/Horizontal/OutAnim/", 0.75f);
					m_ronces[m_ronceToRetract].sprites[ronceID].sprite = m_ronces[m_ronceToRetract].anim.GetCurrentSprite();

					if (m_ronces[m_ronceToRetract].dir == 1)
					{
						m_ronces[m_ronceToRetract].sprites[ronceID].sprite.setScale(-1, 1);
						m_ronces[m_ronceToRetract].sprites[ronceID].sprite.setOrigin(32, 0);
					}
					else
					{
						m_ronces[m_ronceToRetract].sprites[ronceID].sprite.setScale(1, 1);
						m_ronces[m_ronceToRetract].sprites[ronceID].sprite.setOrigin(0, 0);
					}

					if (m_ronces[m_ronceToRetract].anim.HasEnded())
					{
						m_ronces[m_ronceToRetract].sprites[ronceID].sprite.setScale(0, 0);
					}
				}
			}
			break;
		}

		if (m_door > 0 && m_door < 5)
		{
			if (m_door < 4)
			{
				m_camera->SetTarget(m_champiTiles[m_door - 1]);
			}
			else
			{
				m_camera->SetTarget(m_player->GetPosition());
			}

			if (m_camera->IsOnTarget())
			{
				m_timer += _dt;

				if (m_timer > 0.5f)
				{
					m_door++;
					m_timer = 0;

				}
			}
		}

		if (m_door > 4)
		{
			m_spirit.target = m_tileList[BOSS_CORRIDOR];
		}
	}
	else if (m_currentEvent == BOSS_CORRIDOR)
	{
		sf::Vector2f targetTile = sf::Vector2f(69 * 32.f + 16, 23 * 32.f + 16);
		float speed = 2.f;
		if (m_door > 0)
		{
			if (m_door < 5)
			{
				m_musicVolume -= _dt * 5.f;
				if (m_musicVolume < 0)
				{
					m_musicVolume = 0;
				}
			}
			else
			{
				m_musicVolume = 100.f;
			}
		}

		switch (m_door)
		{
		case 0:
			m_spirit.target = m_tileList[m_currentEvent];
			if (IsCollidingTriggerTile())
			{
				m_isInCinematicMode = true;
				OverWriteTrigger();
				m_spirit.target = sf::Vector2f(69 * 32.f + 16, 19 * 32.f + 16);
				m_door++;
			}
			break;

		case 1:
			m_player->MoveTo(targetTile, m_player->GetSpeed() / 2.f, _dt);
			m_camera->SetTarget(m_player->GetPosition() + sf::Vector2f(0, -100));
			m_camera->SetDeadZone(5.f);
			if (CreaMaths::GetSquaredDistance(CreaMaths::CreateVector(targetTile, m_player->GetPosition())) < triggerDistance * triggerDistance)
			{
				m_door++;
				m_easingsClock.restart();
			}
			break;

		case 2:
			if (m_easingsClock.getElapsedTime().asSeconds() < 2.5f)
			{
				speed = Easing::easeInQuint(m_easingsClock.getElapsedTime().asSeconds(), 0, 2, 2.5f);

				m_evilSpirit.setPosition(m_spirit.onScreenPos);
				m_spirit.sprite.setColor(sf::Color(255, 255, 255, 255 - 255 * (speed / 3.f)));
				m_evilSpirit.setColor(sf::Color(255, 255, 255, 255 * (speed / 3.f)));

				m_spirit.speed = 2.5f + speed;
			}
			else
			{
				m_evilSpirit.setColor(sf::Color::Transparent);
				m_spirit.sprite = m_evilSpirit;
				m_spirit.sprite.setColor(sf::Color::White);
				m_timer = 0;
				m_door++;
			}
			break;

		case 3:
			m_timer += _dt;
			if (m_timer > 0.5)
			{
				m_camera->SetTarget(m_spirit.pos + CreaMaths::CreateVector(m_spirit.pos, sf::Vector2f(69 * 32.f + 16, 16 * 32.f + 16.f)));
				m_camera->SetSpeed(2.f);
				m_timer = 0;
				if (m_camera->IsOnTarget())
				{
					m_door++;
				}
			}
			break;

		case 4:
			m_spirit.amplitude = 5.f;
			m_spirit.speed = 7.5f;
			m_spirit.movementSpeed = 75.f;
			m_spirit.target = sf::Vector2f(69 * 32.f + 16, 14 * 32.f + 16);

			if (CreaMaths::GetSquaredDistance(CreaMaths::CreateVector(sf::Vector2f(69 * 32.f + 16, 14 * 32.f + 16), m_spirit.pos)) < 64 * 64)
			{
				m_timer += _dt;
				if (m_timer < 1.f)
				{
					m_spirit.sprite.setColor(sf::Color(255, 255, 255, 255 - 255 * m_timer / 1.f));
				}
				else
				{
					m_spirit.sprite.setColor(sf::Color::Transparent);
					m_door++;

					m_currentTheme.openFromFile("Assets/Souls/Sounds/BGM/Boss.wav");
					m_currentTheme.setLoop(true);
					m_musicVolume = 100.f;
					m_currentTheme.play();
				}
			}
			break;

		case 5:
			m_bossAnimation.PlayAnimation("Assets/Souls/Boss/Activating/", 1.5f);

			if (m_bossAnimation.HasEnded())
			{
				m_door++;
				m_timer = 0;
			}
			else
			{
				m_desatShader.setUniform("saturation", 0.2f + (m_bossAnimation.GetCurrentDuration() / m_bossAnimation.GetAnimDuration()) * 0.8f);
				m_bossSprite = m_bossAnimation.GetCurrentSprite();
			}
			break;

		case 6:
			m_timer += _dt;
			if (m_timer > 0.5f)
			{
				m_door++;
				m_camera->SetTarget(sf::Vector2f(69 * 32.f + 16, 28 * 32.f + 16));
				m_camera->SetSpeed(3.f);
				m_camera->SetDeadZone(10.f);
			}
			break;

		case 7:
			if (m_camera->IsOnTarget())
			{
				m_pieuxAnimation.PlayAnimation("Assets/Souls/Tutorial/Ronces/Pieux/", 0.4f);

				if (m_pieuxAnimation.HasEnded())
				{
					for (int i = 0; i < 5; i++)
					{
						m_map->OverWriteCollision(sf::Vector2i(67 + i, 28), SLMap::CollisionTiles::INVISIBLE_WALL);
					}

					m_isInBossFight = true;
					ToggleNextEvent();
				}
				else
				{
					for (int i = 0; i < 5; i++)
					{
						m_pieux[i] = m_pieuxAnimation.GetCurrentSprite();
						m_pieux[i].setPosition(sf::Vector2f(67 * 32.f + 16 + 32 * i, 28 * 32.f + 16));
					}
				}
			}
			break;

		}

		if (m_door > 1)
		{
			m_player->ForceIdle();
		}
	}
	else if (m_currentEvent == BOSS_END)
	{
		sf::Vector2f spiritDirVec = CreaMaths::CreateVector(m_spirit.pos, sf::Vector2f(69 * 32.f + 16, 19 * 32.f + 16));
		sf::Vector2f gemPos;
		float offset;
		static sf::Clock clocc;

		if (m_door > 0 && m_door < 3)
		{
			m_musicVolume -= _dt * 20.f;
			if (m_musicVolume < 0)
			{
				m_musicVolume = 0.f;
			}
		}

		switch (m_door)
		{
		case 0:
			if (m_boss->GetHP() <= 0)
			{
				m_isInBossFight = false;
				m_isInCinematicMode = true;
				m_camera->SetTarget(m_boss->GetPosition());
				m_camera->SetDeadZone(10.f);
				m_door++;
			}
			break;

		case 1:
			m_bossAnimation.PlayAnimation("Assets/Souls/Boss/Dying/", 1.f);
			m_player->ForceIdle();

			if (!m_bossAnimation.HasEnded())
			{
				m_bossSprite = m_bossAnimation.GetCurrentSprite();
				m_bossSprite.setPosition(m_boss->GetPosition());
				m_desatShader.setUniform("saturation", 1.f - (m_bossAnimation.GetCurrentDuration() / m_bossAnimation.GetAnimDuration()) * 0.8f);
			}
			else
			{
				m_spirit.pos = m_boss->GetPosition();
				m_spirit.sprite.setPosition(m_boss->GetPosition());
				m_spirit.movementSpeed = 30.f;
				m_easingsClock.restart();
				m_door++;
			}
			break;

		case 2:
			CreaMaths::ClampLength(spiritDirVec, 1);
			m_spirit.velocity = spiritDirVec * _dt * m_spirit.movementSpeed * abs(sinf(m_easingsClock.getElapsedTime().asSeconds()));

			m_spirit.pos += m_spirit.velocity;
			m_spirit.sprite.setPosition(m_spirit.pos);
			m_camera->SetTarget(m_spirit.pos);

			m_spirit.sprite.setColor(sf::Color(255, 255, 255, 255 * abs(sinf(m_easingsClock.getElapsedTime().asSeconds()))));

			if (m_easingsClock.getElapsedTime().asSeconds() > 3.14f)
			{
				m_spirit.movementSpeed -= _dt * 10.f;

				if (m_spirit.movementSpeed < 0)
				{
					m_spirit.movementSpeed = 0;
					if (m_spirit.sprite.getColor().a < 2)
					{
						m_spirit.sprite.setColor(sf::Color::Transparent);
						m_camera->SetTarget(sf::Vector2f(69 * 32.f + 16, 28 * 32.f + 16));
						m_door++;
					}
				}
			}
			break;

		case 3:
			m_pieuxAnimation.PlayAnimation("Assets/Souls/Tutorial/Ronces/PieuxInverse/", 1.f);

			if (!m_pieuxAnimation.HasEnded())
			{
				for (int i = 0; i < 5; i++)
				{
					m_pieux[i] = m_pieuxAnimation.GetCurrentSprite();
					m_pieux[i].setPosition(sf::Vector2f(67 * 32.f + 16 + 32 * i, 28 * 32.f + 16));
				}
			}
			else
			{
				for (int i = 0; i < 5; i++)
				{
					m_map->OverWriteCollision(sf::Vector2i(67 + i, 28), SLMap::CollisionTiles::EMPTY);
					m_pieux[i].setPosition(sf::Vector2f(0, 0));
				}

				m_camera->SetTarget(sf::Vector2f(69 * 32.f + 16, 19 * 32.f + 16));
				m_gemSprite.setPosition(sf::Vector2f(69 * 32.f + 16, 15 * 32.f + 16));
				m_easingsClock.restart();

				m_currentTheme.openFromFile("Assets/Souls/Sounds/BGM/Level_Ended.wav");
				m_currentTheme.setLoop(true);
				m_musicVolume = 80.f;
				m_currentTheme.play();

				m_door++;
			}
			break;

		case 4:
			if (m_camera->IsOnTarget())
			{
				offset = sinf(m_easingsClock.getElapsedTime().asSeconds() * 1.5f);
				gemPos = m_gemSprite.getPosition();
				m_gemSprite.setScale(offset, 1);
				gemPos.y += _dt * 25.f;

				if (gemPos.y < 19 * 32.f + 16)
				{
					m_gemSprite.setPosition(gemPos);
				}
				else
				{
					m_isInCinematicMode = false;
					clocc.restart();
					m_door++;
				}
			}
			else
			{
				m_easingsClock.restart();
			}
			break;

		case 5:
			offset = sinf(m_easingsClock.getElapsedTime().asSeconds() * 1.5f);
			m_gemSprite.setScale(offset, 1);
			m_gemSprite.setPosition(sf::Vector2f(69 * 32.f + 16, 19 * 32.f + 16) + sf::Vector2f(0, sinf(clocc.getElapsedTime().asSeconds() * 1.5f) * 10.f));

			if (Collisions::IsCollidingRectRect(m_gemSprite.getGlobalBounds(), m_player->GetHitbox()))
			{
				m_currentTheme.stop();
				ToggleNextEvent();
			}
			break;
		}
	}
}

void SLTutorial::UpdateShroomStates()
{
	std::vector<SLPlayer::Attack> playerAtkVector = m_player->GetAttackVector();

	for (int j = 0; j < 3; j++)
	{
		if (m_ronces[j].active)
		{
			sf::FloatRect hitbox(m_champiTiles[j].x, m_champiTiles[j].y, 32.f, 32.f);

			hitbox.left -= hitbox.width / 2.f;
			hitbox.top -= hitbox.height / 2.f;

			for (int i = 0; i < playerAtkVector.size(); i++)
			{
				if (Collisions::IsCollidingRectRect(playerAtkVector[i].hitbox, hitbox))
				{
					m_sounds.PlaySFX("Shroom", true);
					m_ronces[j].active = false;
					m_ronceToRetract = j;
					for (int k = 0; k < m_ronces[j].tileList.size(); k++)
					{
						m_map->OverWriteCollision(m_ronces[j].tileList[k], SLMap::CollisionTiles::EMPTY);
					}

					m_easingsClock.restart();
					m_door++;
				}
			}
		}
	}
}

void SLTutorial::InitRonces(std::string _mapString)
{
	sf::Sprite sprites[3];
	sf::Vector2i firstTile = sf::Vector2i(67, 63);

	for (int i = 0; i < 3; i++)
	{
		sprites[i] = LoadSprite(std::format("Assets/Souls/Tutorial/Ronces/{}.png", i), false);
	}

	for (int i = 0; i < 3; i++)
	{
		m_ronces[i].active = true;

		m_ronces[i].dir = 0; // Droite
		if (i == 1) m_ronces[i].dir = 1; // Gauche

		for (int j = 0; j < 5; j++)
		{
			m_ronces[i].tileList.push_back(firstTile + sf::Vector2i(j, -i));

			RonceSprite tempSprite;

			sf::Vector2i currentTile = m_ronces[i].tileList.back();
			tempSprite.pos = m_map->GetTileCenter(sf::Vector2i(currentTile.y, currentTile.x)) - sf::Vector2f(16.f, 16.f);

			if (j == 0)
			{
				tempSprite.type = (m_ronces[i].dir == 0) ? START : END;
			}
			else if (j == 4)
			{
				tempSprite.type = (m_ronces[i].dir == 0) ? END : START;
			}
			else
			{
				tempSprite.type = MIDDLE;
			}

			tempSprite.sprite = sprites[tempSprite.type];

			if (m_ronces[i].dir == 1)
			{
				tempSprite.sprite.setOrigin(32, 0);
				tempSprite.sprite.setScale(-1, 1);
			}

			m_ronces[i].sprites.push_back(tempSprite);
		}

		if (_mapString != "SoulsBoss")
		{
			for (int j = 0; j < m_ronces[i].tileList.size(); j++)
			{
				m_map->OverWriteCollision(m_ronces[i].tileList[j], SLMap::CollisionTiles::INVISIBLE_WALL);
			}
		}
	}
}

void SLTutorial::InitVideoPreviews(int _ID)
{
	m_previewVideos[_ID].Load(std::format("Assets/Souls/Tutorial/Videos/{}.mp4", _ID));
}

bool SLTutorial::IsCollidingTriggerTile()
{
	if (m_map->GetTileTypeCollision(m_map->GetTileID(m_player->GetPosition())) == SLMap::CollisionTiles::TRIGGER)
	{
		return true;
	}

	return false;
}

void SLTutorial::OverWriteTrigger()
{
	std::vector<sf::Vector2i> currentTriggerTiled = m_map->GetCurrentRoomTiles(m_player->GetPosition());

	if (m_currentEvent != NORMAL_ATTACK && m_currentEvent != DODGE)
	{
		for (int i = 0; i < currentTriggerTiled.size(); i++)
		{
			m_map->OverWriteCollision(sf::Vector2i(currentTriggerTiled[i].y, currentTriggerTiled[i].x), SLMap::CollisionTiles::EMPTY);
		}
	}
}