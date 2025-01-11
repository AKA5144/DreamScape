#include "PlayerNeyl.hpp"


void PlayerPlatformer::DashKey(ControlsData*& m_controls)
{
	if (sf::Keyboard::isKeyPressed(m_controls->keyBinding[KEYABILITY1]) || sf::Joystick::isButtonPressed(0, (int)ControllerButton::X) || sf::Joystick::isButtonPressed(0, (int)ControllerButton::Y))
	{
		if ((!dashing && !airDash && Dir.x != 0) || (Dir.y != 0 && !airDash))
		{
			dashing = true;
			startDash = position;
			if (isJumping && !airDash)
			{
				airDash = true;
				//	initAirDash.restart().asSeconds();

				velocity = 0;
			}
			else
			{
				isJumping = true;
				airDash = true;
				velocity = 0;
			}
		}
	}
}

void PlayerPlatformer::SetMove(float _dt, Map _map, ControlsData*& m_controls)
{
	sf::Vector2f newPos;
	newPos = position;
	if (!dashing)//fonction qui permet d'initié la direction du dash
	{
		if (sf::Keyboard::isKeyPressed(m_controls->keyBinding[KEYRIGHT]) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 50)
		{
			Dir.x = 1;
		}
		else if (sf::Keyboard::isKeyPressed(m_controls->keyBinding[KEYLEFT]) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -50)
		{
			Dir.x = -1;
		}
		else
		{
			Dir.x = 0;
		}
		if (isJumping && sf::Keyboard::isKeyPressed(m_controls->keyBinding[KEYUP]) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -50)
		{
			Dir.y = -1;
		}
		else if (sf::Keyboard::isKeyPressed(m_controls->keyBinding[KEYDOWN]) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 50)
		{
			Dir.y = 1;
		}
		else
		{
			Dir.y = 0;
		}
	}
}

void PlayerPlatformer::DashUpdate(float _dt, Map _map, BreakMap breakMap)
{
	sf::Vector2f newPos;
	if (dashing)
	{
		float localTimer = initAirDash.getElapsedTime().asSeconds();//timer servent a mettre du delay sur les air dash
		if (localTimer > 0.10f)
		{
			newPos.x = position.x + dashSpeed * _dt * Dir.x;//deplacement du dash
			newPos.y = position.y + (0.8 * dashSpeed) * _dt * Dir.y;
			Move(newPos, _map, breakMap);
			if (isJumping && !IsCollidePointMap(topPointLeft, _map) && !IsCollidePointMap(topPointRight, _map) && !IsCollidePointMap(topPointMid, _map) || (!isJumping && !IsCollidePointMap(groundPointMid, _map) && !IsCollidePointPlayerMap(groundPointLeft, _map) && !IsCollidePointPlayerMap(groundPointRight, _map)))
			{
				;
			}
			else
			{
				dashing = false;
			}
			if (Dir.y < 0)//condition d'arret du dash
			{
				if (position.y < startDash.y - dashRange)
				{
					dashing = false;
				}
			}
			else
			{
				if (position.y > startDash.y + dashRange)
				{
					dashing = false;
				}
			}
			if (Dir.x > 0)
			{
				if (position.x > startDash.x + dashRange)
				{
					dashing = false;
				}
			}
			else
			{
				if (position.x < startDash.x - dashRange)
				{
					dashing = false;
				}
			}
		}
	}
}

PlayerPlatformer::PlayerPlatformer()
{
	state = WALKING;
	speed = 0;
	CheatBool = false;
}

PlayerPlatformer::~PlayerPlatformer()
{

}

//void Player::Die()
//{
//	hasDied = true;
//	sf::Vector2f lastpos(0, 0);
//	DecreaseHP();
//	for (int i = 0; i < respawnPoint.size(); i++)
//	{
//		if (respawnPoint[i].x < position.x)
//		{
//			lastpos = respawnPoint[i];
//		}
//	}
//	position = lastpos;
//}d
sf::CircleShape circlePoint;
sf::CircleShape circlePoint2;
sf::CircleShape circlePoint3;

sf::Vector2f PlayerPlatformer::handleInput(float secondsElapsed, Map _map, ControlsData*& m_controls)
{
#pragma region Init Points
	sf::Vector2u sizeAnim = animations[curAnim][curAnimTile].getTexture()->getSize();

	//Points initialisation
	groundPointMid = position;
	groundPointMid.y = position.y + sizeAnim.y / 2.f - 1;
	midPointLeft = position;
	midPointLeft.x = position.x - sizeAnim.x / 2.f;
	midPointRight = position;
	midPointRight.x = position.x + sizeAnim.x / 2.f - 1;

	groundPointLeft = { position.x - sizeAnim.x / 2.f, position.y + sizeAnim.y / 2.f - 1 };
	groundPointRight = { position.x + sizeAnim.x / 2.f, position.y + sizeAnim.y / 2.f - 1 };

	topPointMid = { position.x, position.y - sizeAnim.y / 2.f - 1 };
	topPointLeft = { position.x - sizeAnim.x / 2.f, position.y - sizeAnim.y / 2.f + 1 };
	topPointRight = { position.x + sizeAnim.x / 2.f, position.y - sizeAnim.y / 2.f + 1 };

#pragma endregion

	sf::Vector2f newPos = position;

	//JUMP 
	if (!isJumping && jumpClock.getElapsedTime().asSeconds() > JUMP_COOLDOWN && IsCollidePointPlayerMap(groundPointMid, _map))
	{
		if (sf::Keyboard::isKeyPressed(params.Jump) || sf::Joystick::isButtonPressed(0, (int)ControllerButton::A) || sf::Joystick::isButtonPressed(0, (int)ControllerButton::B))
		{
			isJumping = true;
			curAnim = JUMPSTART;
			jumpForce = JUMP_FORCE;
			jumpSound.play();
			curTime = 0;//pour bien demarrer a la frame 1 lors du saut

			jumpClock.restart();//pour pas spam
		}
	}
	else if (isJumping && (IsCollidePointPlayerMap(groundPointMid, _map)))
	{
		isJumping = false;
	}


#pragma region replacemnet et grab du mur //touche pas trop
	int tile_left = (int)(position.x / TILE_SIZE);
	int tile_top = (int)(position.y / TILE_SIZE);

	isOnWall = false;

	//Grab the wall
	if ((IsCollidePointPlayerMap(groundPointRight, _map) && !IsCollidePointPlayerMap(groundPointLeft, _map))
		|| ((!IsCollidePointPlayerMap(groundPointRight, _map) && IsCollidePointPlayerMap(groundPointLeft, _map))))
	{
		curAnim = GRAB;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || sf::Joystick::isButtonPressed(0, (int)ControllerButton::RB) || sf::Joystick::isButtonPressed(0, (int)ControllerButton::LB))
		{
			isOnWall = true;
		}
	}
	//Replacement en x
	if ((IsCollidePointPlayerMap(groundPointRight, _map) || IsCollidePointPlayerMap(groundPointLeft, _map)))
	{
		position.x = (tile_left * TILE_SIZE) + TILE_SIZE / 2;

		if (!isOnWall && !dashing)
		{
			if (IsCollidePointPlayerMap({ groundPointLeft.x,groundPointLeft.y - 5 }, _map))
			{
				newPos.x = position.x - 3;
			}
			else if (IsCollidePointPlayerMap({ groundPointRight.x,groundPointRight.y - 5 }, _map))
			{
				newPos.x = position.x + 3.5f;
			}
		}

		//annule le dash
		Dir = { 0,0 };
		dashing = false;
	}

	//Replacement en y
	if ((IsCollidePointPlayerMap(groundPointMid, _map) && (IsCollidePointPlayerMap(groundPointRight, _map) || IsCollidePointPlayerMap(groundPointLeft, _map))) && !isOnWall)
	{
		position.y = (tile_top * TILE_SIZE) + TILE_SIZE / 2;

		//replace les points pour les test de collisions juste apres
		groundPointLeft.y = position.y;
		groundPointRight.y = position.y;

		newPos.y = position.y;

		//annule le dash
		Dir = { 0,0 };
		dashing = false;
	}
#pragma endregion

	// WALK
	if ((sf::Keyboard::isKeyPressed(params.Forward) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 30) && !IsCollidePointPlayerMap(midPointRight, _map) && !isOnWall)
	{
		if (isJumping)
		{
			newPos.x += secondsElapsed * speed / 1.5f; // Speed Modifier midair
		}
		else
		{
			curAnim = WALK;
			newPos.x += secondsElapsed * 0.40 * speed;
		}

		direction = 1;
	}
	else if ((sf::Keyboard::isKeyPressed(params.Backward) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -30) && !IsCollidePointPlayerMap(midPointLeft, _map) && !isOnWall)
	{
		if (isJumping)
		{
			newPos.x -= secondsElapsed * speed / 1.3f; // Speed Modifier midair
		}
		else {
			curAnim = WALK;
			newPos.x -= secondsElapsed * 0.40 * speed;
		}

		direction = -1;
	}
	else
	{
		if (isJumping == false)
		{
			curAnim = IDLE;
		}
	}

	return newPos;
}

void PlayerPlatformer::Die(sf::Vector2f& cameraPos, float secondsElapsed, bool _finalBoss, bool& _transition, float _noirAlpha)
{
	if (isDead)
	{
		if(deathSound.getStatus() != sf::Sound::Playing)
		{
			deathSound.play();
		}
		PmDeath.AddParticle(sf::Vector2i(position), EXPLOSIONS, 4, sf::Color(255, 255, 255));
		_transition = true;

		if (_noirAlpha >= 254)
		{
			if (_finalBoss)
			{
				cameraPos = sf::Vector2f(1280, 288);
				SetPosition(sf::Vector2f(1280, 288));
			}
			else
			{
				if (position.x >= 223 * TILE_SIZE)
				{
					cameraPos = sf::Vector2f(223 * TILE_SIZE, 908);
					SetPosition(sf::Vector2f(223 * TILE_SIZE, 908));
				}
				else
				{
					SetPosition(sf::Vector2f(160, 1004));
					cameraPos = sf::Vector2f(160, 1004);
				}
			}
			_transition = false;
			isDead = false;
		}
	}
}

void PlayerPlatformer::Update(float secondsElapsed, Map _map, Map badMap, GameState& _gameState, bool& _transition, float _noirAlpha, sf::Vector2f& cameraPos, ControlsData*& m_controls, bool _finalBoss, BreakMap breakMap)
{
	startTimer -= secondsElapsed;
	static float sinCounter = 0.f;
	sinCounter += 2 * secondsElapsed;
	PmDeath.UpdateParticule(secondsElapsed);
	sf::Vector2f wallPlayerVector = position - sf::Vector2f(cameraPos.x - SCREEN_WIDTH / 6, cameraPos.y);
	float normeWallPlayerVector = CreaMaths::GetVectorLength(wallPlayerVector);
	float volume = normeWallPlayerVector / 5;
	CreaMaths::Clamp(volume, 0, 100);
	monsterSound.setVolume(100 - volume);
	cameraPos.y += 100 * sin(sinCounter);
	if (normeWallPlayerVector > 200)
	{
		monsterSound.setVolume(0);
	}
	if (monsterSound.getStatus() != sf::SoundSource::Playing)
	{
		monsterSound.play();
	}
	//si on descend trop bas ou si on touche une mauvaise Tile
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		SetPosition(225 * TILE_SIZE, 860);
	}
	if ((position.y > 1400) || ((IsCollidePointPlayerMap(groundPointLeft, badMap) || IsCollidePointPlayerMap(groundPointRight, badMap) || IsCollidePointPlayerMap(topPointLeft, badMap) || IsCollidePointPlayerMap(topPointRight, badMap))))
	{
		isDead = true;
	}

	DashKey(m_controls);
	DashUpdate(secondsElapsed, _map, breakMap);
	SetMove(secondsElapsed, _map, m_controls);

	Die(cameraPos, secondsElapsed, _finalBoss, _transition, _noirAlpha);

	// movement
	sf::Vector2f newPos = handleInput(secondsElapsed, _map, m_controls);

	// gravity
	if (!isDead)
	{
		if (isOnWall)
		{
			jumpForce = 0;
			if (sf::Keyboard::isKeyPressed(m_controls->keyBinding[KEYUP]) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -30)
			{
				newPos.y -= secondsElapsed * speed * 0.50f;
			}

			if (sf::Keyboard::isKeyPressed(m_controls->keyBinding[KEYDOWN]) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 30)
			{
				newPos.y += secondsElapsed * speed * 0.50f;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0, (int)ControllerButton::A) || sf::Joystick::isButtonPressed(0, (int)ControllerButton::B))
			{
				jumpForce = JUMP_FORCE;
				isOnWall = false;
				isJumping = true;
			}
		}
		else
		{
			newPos.y += secondsElapsed * speed * 0.5f;
		}

		// jump
		if (isJumping) {
			newPos.y -= secondsElapsed * jumpForce;
			jumpForce -= 960.f * secondsElapsed;
		}

		// annulation du dash
		if (IsCollidePointMap(groundPointMid, _map) || IsCollidePointMap(groundPointLeft, _map) || IsCollidePointMap(groundPointRight, _map))
		{
			airDash = false;
			if (Dir.y == 1 && Dir.x == 0)//condition qui sert au dash purrement vertical vers le bas
			{
				Dir.y = 0;
				dashing = false;
			}
		}

		if (dashing)
		{
			if (dashSound.getStatus() != sf::Sound::Playing)
			{
				dashSound.play();
			}
		}
		//mouvement final
		Move(newPos, _map, breakMap);
	}

	// Animations
	if (curAnim == WALK || curAnim == IDLE)
	{
		curTime += secondsElapsed;

		if (curTime >= animDuration)
		{
			curTime = 0;
		}
		curAnimTile = curTime * animations[curAnim].size() / animDuration;
	}
	else
	{
		if (jumpForce > (JUMP_FORCE / 2))
		{
			curAnim = JUMPSTART;
		}
		else
		{
			if (curAnim == JUMPSTART)
			{
				curTime = 0;
			}
			curAnim = JUMPMID;
		}

		if (curTime < animations[curAnim].size())
		{
			curTime += secondsElapsed * 20;
		}

		curAnimTile = curTime >= animations[curAnim].size() ? animations[curAnim].size() - 1 : curTime;
	}

	animations[curAnim][curAnimTile].setPosition(position);


	//Particules pour le dash
	if (dashing)
	{
		Pm.AddParticle((sf::Vector2i)midPointRight, SMOG, 6	, sf::Color(180, 180, 200));
		Pm.AddParticle((sf::Vector2i)position, HEAT, 8, sf::Color(243, 127, 243));
	}
	Pm.UpdateParticule(secondsElapsed);

	//c'est normal pour que le perso glisse sur les murs
	if (!isOnWall && !isJumping && IsCollidePointMap(topPointLeft, _map) && !IsCollidePointMap(topPointMid, _map) && !IsCollidePointMap(topPointRight, _map))
	{
		position.y += secondsElapsed * speed / 2 * 0.5f;
	}

	if (!isOnWall && !isJumping && !IsCollidePointMap(topPointLeft, _map) && !IsCollidePointMap(topPointMid, _map) && IsCollidePointMap(topPointRight, _map))
	{
		position.y += secondsElapsed * speed / 2 * 0.5f;
	}

	if (!isOnWall && !isJumping && !IsCollidePointMap(groundPointMid, _map))
	{
		position.y += secondsElapsed * speed / 2 * 0.5f;
	}

	//securité au cas où bloqué
	if (IsCollidePointPlayerMap(groundPointRight, _map) && IsCollidePointPlayerMap(groundPointLeft, _map)
		&& IsCollidePointPlayerMap(midPointRight, _map) && IsCollidePointPlayerMap(midPointLeft, _map))
	{
		position.y -= TILE_SIZE;
		position.x -= TILE_SIZE;
	}
	if (isOnWall)
	{
		curAnim = GRAB;
	}
}

void PlayerPlatformer::AddAnim(std::vector<sf::Sprite> _anim)
{
	animations.push_back(_anim);
}

void PlayerPlatformer::Draw(sf::RenderWindow& _window)
{
	Pm.DrawParticule(_window);
	PmDeath.DrawParticule(_window);
	if (!isDead)
	{
		animations[curAnim][curAnimTile].setScale({ direction,1 });
		animations[curAnim][curAnimTile].setPosition(position);
		_window.draw(animations[curAnim][curAnimTile]);
	}
}

void PlayerPlatformer::Move(sf::Vector2f _newPos, Map& _map, BreakMap breakMap)
{
	if (!IsCollidePointPlayerBreakMap(groundPointRight, breakMap) || dashing)
		position.x = _newPos.x;


	if (isJumping || dashing)
	{
		position.y = _newPos.y;
	}

	if (!isJumping && !IsCollidePointPlayerMap(groundPointMid, _map) && !IsCollidePointPlayerMap(groundPointLeft, _map) && !IsCollidePointPlayerMap(groundPointRight, _map)
		&& !isJumping && !IsCollidePointPlayerBreakMap(groundPointMid, breakMap) && !IsCollidePointPlayerBreakMap(groundPointLeft, breakMap) && !IsCollidePointPlayerBreakMap(groundPointRight, breakMap))
	{
		position.y = _newPos.y;
	}

	if (isOnWall && !IsCollidePointPlayerMap(groundPointMid, _map))
	{
		position.y = _newPos.y;
	}
}