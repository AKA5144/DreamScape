#include "Platformer.h"

enum TutorialNeyl
{
	PREMIER_TUTO,
	DEUXIEME_TUTO,
	MESCOUILLES_TUTO,
	NUMBER_OF_TUTO
};

TutorialNeyl tuto = PREMIER_TUTO;

////////


void FinishedLevel(GameState& _gameState, bool& _transition, float _noirAlpha)
{
	_transition = true;
	if (_noirAlpha >= 254)
	{
		_transition = false;
		_gameState = LOBBY;
	}
}

std::vector <sf::Sprite> tutorialVector;
float curTimeAlphaAnim = 0.f;
float animDurationAlphaAnim = 3.f;
float curTileAlphaAnim = 0.f;
int HP = 5.f;
std::vector<sf::Sprite> screenAlphaAnim;
sf::RectangleShape HPBar;
ParticuleManager pmBroken;
sf::Sprite HPBarSprite;
sf::Sprite playerHead;
sf::Font HPFont;
sf::Text HPText;
float damageTimer = 1.f;

void InitPlatformer(PlatformerData& gameData)
{
	HPFont.loadFromFile("Assets/Font/Monocraft.otf");
	HPText.setFont(HPFont);
	HPText.setString("x" + std::to_string(HP));
	HPText.setCharacterSize(17);

	gameData.PlatformerMusic.openFromFile("Assets/Platformer/Music/levelMusic.wav");
	gameData.PlatformerMusic2.openFromFile("Assets/Platformer/Music/levelMusic2.wav");
	InitMap(gameData.mapSprite, gameData.camera.GetView().getCenter());
	gameData.spriteMap = ReadCSV("Data/Platformer/Maps/SideScroller/finalMap_normal.csv");
	gameData.badMap = ReadBadCSV("Data/Platformer/Maps/SideScroller/finalMap_bad.csv");
	gameData.picMap = ReadPicCSV("Data/Platformer/Maps/SideScroller/finalMap_pic.csv");
	gameData.assetMap = ReadAssetCSV("Data/Platformer/Maps/SideScroller/finalMap_Assets.csv");
	gameData.BackMap = ReadBackCSV("Data/Platformer/Maps/SideScroller/finalMap_back.csv");
	gameData.FinalBossBackMap = ReadBackCSV("Data/Platformer/Maps/SideScroller/finalBossMapBack.csv");
	gameData.FinalBossAssetsMap = ReadAssetCSV("Data/Platformer/Maps/SideScroller/finalBossMapAsset.csv");
	gameData.FinalBossBadMap = ReadBadCSV("Data/Platformer/Maps/SideScroller/finalBossBadMap.csv");
	gameData.breakMap = ReadBreakCSV("Data/Platformer/Maps/SideScroller/finalMap_break.csv");
	gameData.boss.InitBossNeyl(gameData.camera.GetView().getCenter());
	gameData.FinalBossMap = ReadCSV("Data/Platformer/Maps/SideScroller/finalBossMap.csv");
	gameData.FinalBossBadMap = ReadBadCSV("Data/Platformer/Maps/SideScroller/finalBossBadMap.csv");
	playerHead = LoadSprite("Assets/platformer/Sprites/PlayerHead.png", true);
	playerHead.setScale(2, 2);

	std::vector<sf::Sprite> idlePlyAnim;
	idlePlyAnim.push_back(LoadSprite("Assets/Platformer/Sprites/Player/Idle/Idle0.png", 1));
	idlePlyAnim.push_back(LoadSprite("Assets/Platformer/Sprites/Player/Idle/Idle1.png", 1));
	idlePlyAnim.push_back(LoadSprite("Assets/Platformer/Sprites/Player/Idle/Idle2.png", 1));
	idlePlyAnim.push_back(LoadSprite("Assets/Platformer/Sprites/Player/Idle/Idle3.png", 1));

	std::vector<sf::Sprite> walkPlyAnim;
	walkPlyAnim.push_back(LoadSprite("Assets/Platformer/Sprites/Player/walk/Walk0.png", 1));
	walkPlyAnim.push_back(LoadSprite("Assets/Platformer/Sprites/Player/walk/Walk1.png", 1));
	walkPlyAnim.push_back(LoadSprite("Assets/Platformer/Sprites/Player/walk/Walk2.png", 1));
	walkPlyAnim.push_back(LoadSprite("Assets/Platformer/Sprites/Player/walk/Walk3.png", 1));

	std::vector<sf::Sprite> jumpStartPlyAnim;
	jumpStartPlyAnim.push_back(LoadSprite("Assets/Platformer/Sprites/Player/Jump/JumpStart/JumpStart0.png", 1));
	jumpStartPlyAnim.push_back(LoadSprite("Assets/Platformer/Sprites/Player/Jump/JumpStart/JumpStart1.png", 1));
	jumpStartPlyAnim.push_back(LoadSprite("Assets/Platformer/Sprites/Player/Jump/JumpStart/JumpStart2.png", 1));

	std::vector<sf::Sprite> jumpMidPlyAnim;
	jumpMidPlyAnim.push_back(LoadSprite("Assets/Platformer/Sprites/Player/Jump/JumpMid/JumpMid0.png", 1));
	jumpMidPlyAnim.push_back(LoadSprite("Assets/Platformer/Sprites/Player/Jump/JumpMid/JumpMid1.png", 1));
	jumpMidPlyAnim.push_back(LoadSprite("Assets/Platformer/Sprites/Player/Jump/JumpMid/JumpMid2.png", 1));

	std::vector<sf::Sprite> jumpEndPlyAnim;
	jumpEndPlyAnim.push_back(LoadSprite("Assets/Platformer/Sprites/Player/Jump/JumpEnd/JumpEnd0.png", 1));
	jumpEndPlyAnim.push_back(LoadSprite("Assets/Platformer/Sprites/Player/Jump/JumpEnd/JumpEnd1.png", 1));

	std::vector<sf::Sprite> grabAnim;
	grabAnim.push_back(LoadSprite("Assets/Platformer/Sprites/Player/Grab/GrabWait1.png", 1));
	grabAnim.push_back(LoadSprite("Assets/Platformer/Sprites/Player/Grab/GrabWait2.png", 1));
	grabAnim.push_back(LoadSprite("Assets/Platformer/Sprites/Player/Grab/GrabWait3.png", 1));
	grabAnim.push_back(LoadSprite("Assets/Platformer/Sprites/Player/Grab/GrabWait4.png", 1));

	gameData.players.AddAnim(idlePlyAnim);
	gameData.players.AddAnim(walkPlyAnim);
	gameData.players.AddAnim(jumpStartPlyAnim);
	gameData.players.AddAnim(jumpMidPlyAnim);
	gameData.players.AddAnim(jumpEndPlyAnim);
	gameData.players.AddAnim(grabAnim);


	screenAlphaAnim.push_back(LoadSprite("Assets/Platformer/Boss/Symbols/symbols_1.png", 1));
	screenAlphaAnim.push_back(LoadSprite("Assets/Platformer/Boss/Symbols/symbols_2.png", 1));
	screenAlphaAnim.push_back(LoadSprite("Assets/Platformer/Boss/Symbols/symbols_3.png", 1));

	gameData.tutorial = false;


	sf::FloatRect rectFloat = gameData.players.GetRect();
	gameData.players.SetPosition(sf::Vector2f(160, 908));
	gameData.players.params.Backward = sf::Keyboard::Q;
	gameData.players.params.Forward = sf::Keyboard::D;
	gameData.players.params.Jump = sf::Keyboard::Space;
	gameData.players.SetSpeed(400);
	gameData.camera.Init(gameData.players.GetPosition());
	gameData.camera.SetDeadZone(3);
	gameData.camera.SetZoom(1.f / 3);
	gameData.camera.SetSpeed(3.f);
	gameData.cameraPos = gameData.players.GetPosition();
	gameData.camera.SetTarget(gameData.cameraPos);
	gameData.isPhase2Triggered = false;
	gameData.players.jumpSoundBuffer.loadFromFile("Assets/Platformer/Sound/jumpSound.ogg");
	gameData.players.dashSoundBuffer.loadFromFile("Assets/Platformer/Sound/DashSound.ogg");
	gameData.players.jumpSound.setBuffer(gameData.players.jumpSoundBuffer);
	gameData.players.dashSound.setBuffer(gameData.players.dashSoundBuffer);
	gameData.players.jumpSound.setLoop(false);
	gameData.players.jumpSound.setLoop(false);
	gameData.players.monsterSoundBuffer.loadFromFile("Assets/Platformer/Sound/WallSoundEffect.wav");
	gameData.players.monsterSound.setBuffer(gameData.players.monsterSoundBuffer);
	gameData.players.monsterSound.setLoop(true);
	gameData.players.monsterSound.setVolume(0);
	gameData.players.deathSoundBuffer.loadFromFile("Assets/Platformer/Sound/deathSound.wav");
	gameData.players.deathSound.setBuffer(gameData.players.deathSoundBuffer);
	HPBar.setSize(sf::Vector2f(gameData.boss.BossHP * 50, 15));
	HPBar.setFillColor(sf::Color::Green);
	HPBar.setPosition(gameData.camera.GetView().getCenter());
	HPBarSprite = LoadSprite("Assets/Platformer/Sprites/health_bar.png", false);
	HPBarSprite.setPosition(gameData.camera.GetView().getCenter());
	playerHead.setPosition(gameData.camera.GetView().getCenter());
	tutorialVector.push_back(LoadSprite("Assets/Platformer/Sprites/MoveTuto_manette.png", false));
	tutorialVector.push_back(LoadSprite("Assets/Platformer/Sprites/DashTuto_manette.png", false));
	tutorialVector.push_back(LoadSprite("Assets/Platformer/Sprites/BreakTuto_manette.png", false));
	tutorialVector.push_back(LoadSprite("Assets/Platformer/Sprites/LaserTuto_manette.png", false));
	tutorialVector.push_back(LoadSprite("Assets/Platformer/Sprites/LaserTuto_manette.png", false));
}
int actualTutoPlatformer = 0;
void UpdateTutorial(float elapsed, PlatformerData& gameData)
{
	static float timer = 1;

	if (actualTutoPlatformer < tutorialVector.size() - 1)
	{
		if (timer > 0)
		{
			timer -= elapsed;
		}
		if (timer <= 0  && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E) || sf::Joystick::isButtonPressed(0, (int)ControllerButton::A)))
		{
			timer = 1;
			actualTutoPlatformer++;
		}

		tutorialVector[actualTutoPlatformer].setPosition(sf::Vector2f(gameData.players.position.x - 130, gameData.players.position.y - 130));
		tutorialVector[actualTutoPlatformer].setScale(sf::Vector2f(1, 1));
	}
	else
	{
		gameData.tutorial = true;
	}
}
float cameraOffsetY = 40;
float finishTimer = 5;
void UpdatePlatformer(float elapsed, PlatformerData& gameData, sf::RenderWindow& _window, GameState& _gameState, bool& _transition, float _noirAlpha, ControlsData*& m_controls, Player& _player)
{
	if (gameData.players.position.x < gameData.camera.GetView().getCenter().x - 210 && damageTimer < 0)
	{
		HP--;
		damageTimer = 3;
	}
	if (damageTimer < 0 && (IsCollidePointPlayerMap(gameData.players.groundPointLeft, gameData.badMap) || IsCollidePointPlayerMap(gameData.players.groundPointRight, gameData.badMap) || IsCollidePointPlayerMap(gameData.players.topPointLeft, gameData.badMap) || IsCollidePointPlayerMap(gameData.players.topPointRight, gameData.badMap)))
	{
		HP--;
		damageTimer = 2;
	}
	HPText.setString("x" + std::to_string(HP));
	if (!gameData.finalBoss)
	{
		if (!gameData.tutorial)
		{

			gameData.camera.SetTarget(gameData.cameraPos);
			gameData.camera.Update(elapsed);
			UpdateTutorial(elapsed, gameData);
			UpdateMap(gameData.mapSprite, gameData.camera.GetView().getCenter(), gameData.players.GetPosition(), elapsed);

		}
		else
		{
			if (damageTimer > 0)
			{
				damageTimer -= elapsed;
			}
			HPBar.setPosition(sf::Vector2f(gameData.boss.bossNeylAnimGenie[gameData.boss.curAnimGenie][gameData.boss.curAnimTileGenie].getPosition().x - 77, gameData.boss.bossNeylAnimGenie[gameData.boss.curAnimGenie][gameData.boss.curAnimTileGenie].getPosition().y - 32 - 25));
			playerHead.setPosition(sf::Vector2f(gameData.camera.GetView().getCenter().x - 195, gameData.camera.GetView().getCenter().y - 155));
			HPText.setPosition(sf::Vector2f(gameData.camera.GetView().getCenter().x - 150, gameData.camera.GetView().getCenter().y - 155));
			HPBarSprite.setPosition((sf::Vector2f(gameData.boss.bossNeylAnimGenie[gameData.boss.curAnimGenie][gameData.boss.curAnimTileGenie].getPosition().x - 90, gameData.boss.bossNeylAnimGenie[gameData.boss.curAnimGenie][gameData.boss.curAnimTileGenie].getPosition().y - 32 - 25 - 5)));
			HPBar.setSize(sf::Vector2f(gameData.boss.BossHP * 50, 15));

			if (isCollidePointRectangleCentered(gameData.players.topPointMid, gameData.boss.bossNeylAnim[gameData.boss.curAnim][gameData.boss.curAnimTile]) && gameData.players.dashing)
			{
				gameData.boss.spawnerTimer = 5;
				pmBroken.AddParticle(sf::Vector2i(gameData.boss.bossNeylAnim[gameData.boss.curAnim][gameData.boss.curAnimTile].getPosition()), EARTH, 4, sf::Color::White);
			}

			curTimeAlphaAnim += elapsed;
			if (curTimeAlphaAnim > animDurationAlphaAnim)
			{
				curTimeAlphaAnim = 0;
			}
			curTileAlphaAnim = curTimeAlphaAnim * (screenAlphaAnim.size() - 1) / animDurationAlphaAnim;
			screenAlphaAnim[curTileAlphaAnim].setPosition(gameData.camera.GetView().getCenter());
			static float sinCounter = 0.f;
			sinCounter += 7 * elapsed;
			sf::Vector2f wallPlayerVector = gameData.players.position - sf::Vector2f(gameData.cameraPos.x - SCREEN_WIDTH / 6, gameData.cameraPos.y);
			float normeWallPlayerVector = CreaMaths::GetVectorLength(wallPlayerVector);
			float volume = normeWallPlayerVector / 5;
			if (normeWallPlayerVector > 255)
			{
				screenAlphaAnim[curTileAlphaAnim].setColor(sf::Color(255, 255, 255, 0));
			}
			else
				screenAlphaAnim[curTileAlphaAnim].setColor(sf::Color(255, 255, 255, 255 - (normeWallPlayerVector)));

			CreaMaths::Clamp(volume, 0, 100);

			if (IsCollidePointPlayerBreakMap(gameData.players.position, gameData.breakMap) && gameData.players.dashing)
			{
				int tile_left = (int)(gameData.players.position.x / TILE_SIZE);
				int tile_top = (int)(gameData.players.position.y / TILE_SIZE);
				gameData.breakMap[tile_top][tile_left] = BROKEN;
				gameData.breakMap[tile_top - 1][tile_left] = BROKEN;
				gameData.breakMap[tile_top + 1][tile_left] = BROKEN;
				pmBroken.AddParticle(sf::Vector2i(tile_left * TILE_SIZE, tile_top * TILE_SIZE), EARTH, 8, sf::Color::White);
			}

			pmBroken.UpdateParticule(elapsed);
			bool isTouched = false;

			if (gameData.PlatformerMusic.getStatus() != sf::SoundSource::Playing && !gameData.boss.isPhase2Triggered)
				gameData.PlatformerMusic.play();

			if (gameData.PlatformerMusic2.getStatus() != sf::SoundSource::Playing && gameData.boss.isPhase2Triggered)
				gameData.PlatformerMusic2.play();

			if (gameData.boss.isPhase2Triggered)
				gameData.PlatformerMusic.stop();
			else
				gameData.PlatformerMusic2.stop();

			gameData.cameraPos.x += 100 * elapsed;

			gameData.cameraPos.y = gameData.players.GetPosition().y - cameraOffsetY;

			CreaMaths::Clamp(volume, 0, 50);

			gameData.cameraPos.y += 1.5 * (50 - volume) * sin(sinCounter);
			gameData.camera.SetTarget(gameData.cameraPos);
			gameData.camera.Update(elapsed);
			UpdateMap(gameData.mapSprite, gameData.camera.GetView().getCenter(), gameData.players.GetPosition(), elapsed);
			gameData.players.Update(elapsed, gameData.spriteMap, gameData.badMap, _gameState, _transition, _noirAlpha, gameData.cameraPos, m_controls, gameData.finalBoss, gameData.breakMap);

			if (damageTimer < 0 && !gameData.players.CheatBool && (isCollidePointRectangle(gameData.players.groundPointLeft, gameData.boss.bossNeylAnimHand[gameData.boss.curAnimHand][gameData.boss.curAnimTileHand]) || isCollidePointRectangle(gameData.players.groundPointRight, gameData.boss.bossNeylAnimHand[gameData.boss.curAnimHand][gameData.boss.curAnimTileHand]) || isCollidePointRectangle(gameData.players.groundPointMid, gameData.boss.bossNeylAnimHand[gameData.boss.curAnimHand][gameData.boss.curAnimTileHand])))
			{
				HP--;
				damageTimer = 3;
			}
			if (gameData.players.dashing && (isCollidePointRectangleCentered(gameData.players.topPointLeft, gameData.boss.bossNeylAnimGenie[gameData.boss.curAnimGenie][gameData.boss.curAnimTileGenie]) || isCollidePointRectangle(gameData.players.topPointRight, gameData.boss.bossNeylAnimGenie[gameData.boss.curAnimGenie][gameData.boss.curAnimTileGenie]) || isCollidePointRectangle(gameData.players.topPointMid, gameData.boss.bossNeylAnimGenie[gameData.boss.curAnimGenie][gameData.boss.curAnimTileGenie])))
			{
				gameData.boss.LooseHP();
			}


			gameData.boss.UpdateBossNeyl(elapsed, gameData.players.GetPosition(), gameData.camera.GetView().getCenter());
			gameData.boss.UpdateBossNeylWall(gameData.camera.GetView().getCenter(), gameData.camera.GetView().getSize(), elapsed);
			if (gameData.boss.BossHP <= 0)
			{
				gameData.boss.BossHP = 0;
				gameData.PlatformerMusic.stop();
				gameData.PlatformerMusic2.stop();
				finishTimer -= elapsed;
				gameData.boss.pmDeath.AddParticle(sf::Vector2i(gameData.boss.bossNeylAnimGenie[gameData.boss.curAnimGenie][gameData.boss.curAnimTileGenie].getPosition()), SMOG, 2 * (int)finishTimer, sf::Color(169, 106, 35), 3 * 4.f);
			}
			if (finishTimer < 0)
			{
				gameData.players.HP = 5;
				_player.Set_IsBlueTotem(true);
				FinishedLevel(_gameState, _transition, _noirAlpha);
				gameData.players.monsterSound.stop();
			}

			if (gameData.boss.BossHP > 0)
			{
				for (int i = 0; i < 10; i++)
				{
					if (gameData.boss.isPhase2Triggered && gameData.boss.curAnimEye == ATTACKEYE && (isCollidingWithOrientedSprite(gameData.players.topPointMid, gameData.boss.laserCollider[i])
						|| isCollidingWithOrientedSprite(gameData.players.groundPointMid, gameData.boss.laserCollider2[i])))
						/*
						|| isCollidingWithOrientedSprite(gameData.players.midPointLeft, gameData.boss.laserCollider2[i])
						|| isCollidingWithOrientedSprite(gameData.players.midPointRight, gameData.boss.laserCollider[i])
						|| isCollidingWithOrientedSprite(gameData.players.midPointLeft, gameData.boss.laserCollider[i]))*/
					{
						isTouched = true;
					}
					if (!gameData.boss.isPhase2Triggered && gameData.boss.isSpawned && gameData.boss.curAnim == STILL &&
						(isCollidingWithOrientedSprite(gameData.players.midPointRight, gameData.boss.bossNeylAnimLaserTab[i][0][gameData.boss.curAnimTileLaser])
							|| isCollidingWithOrientedSprite(gameData.players.topPointRight, gameData.boss.bossNeylAnimLaserTab[i][0][gameData.boss.curAnimTileLaser])
							|| isCollidingWithOrientedSprite(gameData.players.groundPointRight, gameData.boss.bossNeylAnimLaserTab[i][0][gameData.boss.curAnimTileLaser])))
					{
						isTouched = true;
					}
				}
			}
			if (damageTimer < 0 && isTouched)
			{
				HP--;
				damageTimer = 3;
			}
		}
	}
	else
	{
		//mets ta merde ici
		gameData.players.Update(elapsed, gameData.FinalBossMap, gameData.FinalBossBadMap, _gameState, _transition, _noirAlpha, gameData.cameraPos, m_controls, gameData.finalBoss, gameData.breakMap);
		gameData.cameraPos.x = gameData.players.GetPosition().x;
		gameData.cameraPos.y = gameData.players.GetPosition().y;
		gameData.camera.SetTarget(gameData.cameraPos);
		gameData.camera.Update(elapsed);
		UpdateMap(gameData.mapSprite, gameData.camera.GetView().getCenter(), gameData.players.GetPosition(), elapsed);
	}

}

void DrawPlatformer(PlatformerData& gameData, sf::RenderWindow& _window)
{
	if (!gameData.finalBoss)
	{
		_window.setView(gameData.camera.GetView());
		if (gameData.tutorial)

			DrawParalax(gameData.mapSprite, _window);
		DrawBackMap(gameData.BackMap, _window, gameData.mapSprite);
		DrawMap(gameData.spriteMap, _window, gameData.mapSprite);
		DrawAssetMap(gameData.assetMap, _window, gameData.mapSprite);
		DrawBadMap(gameData.badMap, _window, gameData.mapSprite);
		DrawPicMap(gameData.picMap, _window, gameData.mapSprite);
		DrawBreakMap(gameData.breakMap, _window, gameData.mapSprite);
		_window.draw(screenAlphaAnim[curTileAlphaAnim]);
		pmBroken.DrawParticule(_window);
		if (damageTimer > 0)
		{
			gameData.players.animations[gameData.players.curAnim][gameData.players.curAnimTile].setColor(sf::Color::Red);
		}
		else
		{
			gameData.players.animations[gameData.players.curAnim][gameData.players.curAnimTile].setColor(sf::Color::White);

		}
		gameData.players.Draw(_window);
		gameData.boss.Draw(_window, gameData.camera.GetView().getCenter());
		HPText.setFillColor(sf::Color::White);
		_window.draw(HPText);
		_window.draw(playerHead);
		if (gameData.boss.isPhase2Triggered && gameData.boss.BossHP > 0)
		{
			_window.draw(HPBar);
			_window.draw(HPBarSprite);
		}
		if (!gameData.tutorial)
		{
			DrawParalax(gameData.mapSprite, _window);
			DrawBackMap(gameData.BackMap, _window, gameData.mapSprite);
			DrawMap(gameData.spriteMap, _window, gameData.mapSprite);
			DrawAssetMap(gameData.assetMap, _window, gameData.mapSprite);
			DrawBadMap(gameData.badMap, _window, gameData.mapSprite);
			DrawPicMap(gameData.picMap, _window, gameData.mapSprite);
			DrawBreakMap(gameData.breakMap, _window, gameData.mapSprite);
			_window.draw(tutorialVector[actualTutoPlatformer]);
		}

	}
	else
	{
		_window.setView(gameData.camera.GetView());
		DrawParalax(gameData.mapSprite, _window);
		DrawBackMap(gameData.FinalBossBackMap, _window, gameData.mapSprite);
		DrawAssetMap(gameData.FinalBossAssetsMap, _window, gameData.mapSprite);
		DrawBadMap(gameData.FinalBossBadMap, _window, gameData.mapSprite);
		DrawMap(gameData.FinalBossMap, _window, gameData.mapSprite);
		gameData.players.Draw(_window);
	}
}

int& Get_PlatformerHp()
{
	return HP;
}

sf::RectangleShape& Get_HpBar()
{
	return HPBar;
}

sf::Sprite& Get_PlayerHead()
{
	return playerHead;
}

sf::Text& Get_HpText()
{
	return HPText;
}
