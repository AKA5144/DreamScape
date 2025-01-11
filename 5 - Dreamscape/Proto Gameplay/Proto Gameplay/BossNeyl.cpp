#include "BossNeyl.h"
sf::Vector2f playerShotVector;
sf::Vector2f playerShotVector2;
void BossNeyl::InitBossNeyl(sf::Vector2f camPos)
{
	laserSoundBuffer.loadFromFile("Assets/Platformer/Sound/laserSound.ogg");
	BossHPSoundBuffer.loadFromFile("Assets/Platformer/Sound/SoundBossHP.ogg");
	laserSound.setBuffer(laserSoundBuffer);
	BossHPSound.setBuffer(BossHPSoundBuffer);
	BossHPSound.setLoop(false);
	irisSprite = LoadSprite("Assets/Platformer/Boss/iris.png", true);
	irisBossSprite = LoadSprite("Assets/Platformer/Boss/iris.png", true);
	for (int i = 0; i < 20; i++)
	{
		bossLaserSprite.push_back(LoadSprite("Assets/Platformer/Boss/BossLaser.png", false));
		bossLaserSprite2.push_back(LoadSprite("Assets/Platformer/Boss/BossLaser.png", false));
	}
	std::vector<sf::Sprite> AnimSpawn;
	AnimSpawn.push_back(LoadSprite("Assets/Platformer/Boss/EyeSpawn/EyeSpawn1.png", 1));
	AnimSpawn.push_back(LoadSprite("Assets/Platformer/Boss/EyeSpawn/EyeSpawn2.png", 1));
	AnimSpawn.push_back(LoadSprite("Assets/Platformer/Boss/EyeSpawn/EyeSpawn3.png", 1));
	AnimSpawn.push_back(LoadSprite("Assets/Platformer/Boss/EyeSpawn/EyeSpawn4.png", 1));
	AnimSpawn.push_back(LoadSprite("Assets/Platformer/Boss/EyeSpawn/EyeSpawn4.png", 1));
	AddAnim(AnimSpawn);

	std::vector<sf::Sprite> AnimClosing;
	AnimClosing.push_back(LoadSprite("Assets/Platformer/Boss/EyeClosing/EyeClosing1.png", 1));
	AnimClosing.push_back(LoadSprite("Assets/Platformer/Boss/EyeClosing/EyeClosing2.png", 1));
	AnimClosing.push_back(LoadSprite("Assets/Platformer/Boss/EyeClosing/EyeClosing3.png", 1));
	AnimClosing.push_back(LoadSprite("Assets/Platformer/Boss/EyeClosing/EyeClosing4.png", 1));
	AnimClosing.push_back(LoadSprite("Assets/Platformer/Boss/EyeClosing/EyeClosing4.png", 1));
	AddAnim(AnimClosing);

	std::vector<sf::Sprite> AnimOpening;
	AnimOpening.push_back(LoadSprite("Assets/Platformer/Boss/EyeOpening/EyeOpening1.png", 1));
	AnimOpening.push_back(LoadSprite("Assets/Platformer/Boss/EyeOpening/EyeOpening2.png", 1));
	AnimOpening.push_back(LoadSprite("Assets/Platformer/Boss/EyeOpening/EyeOpening3.png", 1));
	AnimOpening.push_back(LoadSprite("Assets/Platformer/Boss/EyeOpening/EyeOpening4.png", 1));
	AnimOpening.push_back(LoadSprite("Assets/Platformer/Boss/EyeOpening/EyeOpening4.png", 1));
	AddAnim(AnimOpening);
	std::vector<sf::Sprite> AnimStill;
	AnimStill.push_back(LoadSprite("Assets/Platformer/Boss/EyeStill.png", 1));
	AddAnim(AnimStill);

	std::vector<sf::Sprite> AnimWallEnd;
	AnimWallEnd.push_back(LoadSprite("Assets/Platformer/Boss/WallEnd/WallEnd1.png", false));
	AnimWallEnd.push_back(LoadSprite("Assets/Platformer/Boss/WallEnd/WallEnd2.png", false));
	AnimWallEnd.push_back(LoadSprite("Assets/Platformer/Boss/WallEnd/WallEnd3.png", false));
	AnimWallEnd.push_back(LoadSprite("Assets/Platformer/Boss/WallEnd/WallEnd4.png", false));
	AnimWallEnd.push_back(LoadSprite("Assets/Platformer/Boss/WallEnd/WallEnd4.png", false));
	bossNeylAnimWallEnd.push_back(AnimWallEnd);

	std::vector<sf::Sprite> AnimWallIdle;
	AnimWallIdle.push_back(LoadSprite("Assets/Platformer/Boss/WallIdle/BackgroundWall0.png", 1));
	AnimWallIdle.push_back(LoadSprite("Assets/Platformer/Boss/WallIdle/BackgroundWall1.png", 1));
	AnimWallIdle.push_back(LoadSprite("Assets/Platformer/Boss/WallIdle/BackgroundWall2.png", 1));
	AnimWallIdle.push_back(LoadSprite("Assets/Platformer/Boss/WallIdle/BackgroundWall3.png", 1));
	AnimWallIdle.push_back(LoadSprite("Assets/Platformer/Boss/WallIdle/BackgroundWall3.png", 1));
	AddAnimWall(AnimWallIdle);

	std::vector<sf::Sprite> AnimGenieIdle;
	AnimGenieIdle.push_back(LoadSprite("Assets/Platformer/Boss/BossStillAnim/BossAnim1.png", 1));
	AnimGenieIdle.push_back(LoadSprite("Assets/Platformer/Boss/BossStillAnim/BossAnim2.png", 1));
	AnimGenieIdle.push_back(LoadSprite("Assets/Platformer/Boss/BossStillAnim/BossAnim3.png", 1));
	AnimGenieIdle.push_back(LoadSprite("Assets/Platformer/Boss/BossStillAnim/BossAnim3.png", 1));
	AddAnimGenie(AnimGenieIdle);

	std::vector<sf::Sprite> AnimGenieShield;
	AnimGenieShield.push_back(LoadSprite("Assets/Platformer/Boss/ShieldAnim/ShieldAnim1.png", 1));
	AnimGenieShield.push_back(LoadSprite("Assets/Platformer/Boss/ShieldAnim/ShieldAnim2.png", 1));
	AnimGenieShield.push_back(LoadSprite("Assets/Platformer/Boss/ShieldAnim/ShieldAnim3.png", 1));
	AnimGenieShield.push_back(LoadSprite("Assets/Platformer/Boss/ShieldAnim/ShieldAnim3.png", 1));
	AddAnimGenie(AnimGenieShield);

	std::vector<sf::Sprite> AnimGenieCharge;
	AnimGenieCharge.push_back(LoadSprite("Assets/Platformer/Boss/BossCharge/BossCharge0.png", true));
	AnimGenieCharge.push_back(LoadSprite("Assets/Platformer/Boss/BossCharge/BossCharge1.png", true));
	AnimGenieCharge.push_back(LoadSprite("Assets/Platformer/Boss/BossCharge/BossCharge2.png", true));
	AnimGenieCharge.push_back(LoadSprite("Assets/Platformer/Boss/BossCharge/BossCharge2.png", true));

	AddAnimGenie(AnimGenieCharge);
	std::vector<sf::Sprite> AnimGenieAttack;
	AnimGenieAttack.push_back(LoadSprite("Assets/Platformer/Boss/AnimGenieAttack/AnimGenieAttack1.png", true));
	AnimGenieAttack.push_back(LoadSprite("Assets/Platformer/Boss/AnimGenieAttack/AnimGenieAttack2.png", true));
	AnimGenieAttack.push_back(LoadSprite("Assets/Platformer/Boss/AnimGenieAttack/AnimGenieAttack3.png", true));
	AnimGenieAttack.push_back(LoadSprite("Assets/Platformer/Boss/AnimGenieAttack/AnimGenieAttack3.png", true));
	AddAnimGenie(AnimGenieAttack);

	std::vector<sf::Sprite> AnimGenieDeath;
	AnimGenieDeath.push_back(LoadSprite("Assets/Platformer/Boss/BossDeath/Boss_disappearance_1.png", true));
	AnimGenieDeath.push_back(LoadSprite("Assets/Platformer/Boss/BossDeath/Boss_disappearance_1.png", true));
	AnimGenieDeath.push_back(LoadSprite("Assets/Platformer/Boss/BossDeath/Boss_disappearance_2.png", true));
	AnimGenieDeath.push_back(LoadSprite("Assets/Platformer/Boss/BossDeath/Boss_disappearance_2.png", true));
	AnimGenieDeath.push_back(LoadSprite("Assets/Platformer/Boss/BossDeath/Boss_disappearance_3.png", true));
	AnimGenieDeath.push_back(LoadSprite("Assets/Platformer/Boss/BossDeath/Boss_disappearance_3.png", true));
	AnimGenieDeath.push_back(LoadSprite("Assets/Platformer/Boss/BossDeath/Boss_disappearance_4.png", true));
	AnimGenieDeath.push_back(LoadSprite("Assets/Platformer/Boss/BossDeath/Boss_disappearance_4.png", true));
	AnimGenieDeath.push_back(LoadSprite("Assets/Platformer/Boss/BossDeath/Boss_disappearance_5.png", true));
	AnimGenieDeath.push_back(LoadSprite("Assets/Platformer/Boss/BossDeath/Boss_disappearance_5.png", true));
	AddAnimGenie(AnimGenieDeath);

	std::vector<sf::Sprite> AnimGenieDeathFinal;
	AnimGenieDeathFinal.push_back(LoadSprite("Assets/Platformer/Boss/BossDeath/Boss_disappearance_5.png", true));
	AnimGenieDeathFinal.push_back(LoadSprite("Assets/Platformer/Boss/BossDeath/Boss_disappearance_5.png", true));
	AnimGenieDeathFinal.push_back(LoadSprite("Assets/Platformer/Boss/BossDeath/Boss_disappearance_5.png", true));
	AnimGenieDeathFinal.push_back(LoadSprite("Assets/Platformer/Boss/BossDeath/Boss_disappearance_5.png", true));
	AnimGenieDeathFinal.push_back(LoadSprite("Assets/Platformer/Boss/BossDeath/Boss_disappearance_5.png", true));
	AnimGenieDeathFinal.push_back(LoadSprite("Assets/Platformer/Boss/BossDeath/Boss_disappearance_5.png", true));
	AnimGenieDeathFinal.push_back(LoadSprite("Assets/Platformer/Boss/BossDeath/Boss_disappearance_5.png", true));
	AddAnimGenie(AnimGenieDeathFinal);

	std::vector<sf::Sprite> AnimWallHands;
	AnimWallHands.push_back(LoadSprite("Assets/Platformer/Boss/WallHands/AnimBras1.png", 0));
	AnimWallHands.push_back(LoadSprite("Assets/Platformer/Boss/WallHands/AnimBras2.png", 0));
	AnimWallHands.push_back(LoadSprite("Assets/Platformer/Boss/WallHands/AnimBras3.png", 0));
	AnimWallHands.push_back(LoadSprite("Assets/Platformer/Boss/WallHands/AnimBras4.png", 0));
	AnimWallHands.push_back(LoadSprite("Assets/Platformer/Boss/WallHands/AnimBras5.png", 0));
	AnimWallHands.push_back(LoadSprite("Assets/Platformer/Boss/WallHands/AnimBras6.png", 0));
	AnimWallHands.push_back(LoadSprite("Assets/Platformer/Boss/WallHands/AnimBras6.png", 0));
	AddAnimWallHands(AnimWallHands);

	std::vector<sf::Sprite> AnimGrabHands;
	AnimGrabHands.push_back(LoadSprite("Assets/Platformer/Boss/GrabHandsAnim/GrabHandsAnim1.png", false));
	AnimGrabHands.push_back(LoadSprite("Assets/Platformer/Boss/GrabHandsAnim/GrabHandsAnim2.png", false));
	AnimGrabHands.push_back(LoadSprite("Assets/Platformer/Boss/GrabHandsAnim/GrabHandsAnim3.png", false));
	AnimGrabHands.push_back(LoadSprite("Assets/Platformer/Boss/GrabHandsAnim/GrabHandsAnim3.png", false));
	AddAnimGrabHands(AnimGrabHands);

	laserColliderSprite = LoadSprite("Assets/Platformer/Boss/BossLaser/laserCollider.png", false);
	for (int i = 0; i < 20; i++)
	{
		laserCollider.push_back(laserColliderSprite);
		laserCollider2.push_back(laserColliderSprite);
	}


	std::vector<sf::Sprite> AnimLaser;
	AnimLaser.push_back(LoadSprite("Assets/Platformer/Boss/AnimLaser/AnimLaser1.png", false));
	AnimLaser.push_back(LoadSprite("Assets/Platformer/Boss/AnimLaser/AnimLaser2.png", false));
	AnimLaser.push_back(LoadSprite("Assets/Platformer/Boss/AnimLaser/AnimLaser3.png", false));
	AnimLaser.push_back(LoadSprite("Assets/Platformer/Boss/AnimLaser/AnimLaser4.png", false));
	AnimLaser.push_back(LoadSprite("Assets/Platformer/Boss/AnimLaser/AnimLaser4.png", false));
	AddAnimLaser(AnimLaser);

	std::vector<sf::Sprite> AnimLaserGrey;
	AnimLaserGrey.push_back(LoadSprite("Assets/Platformer/Boss/AnimLaser/AnimLaserGrey1.png", false));
	AnimLaserGrey.push_back(LoadSprite("Assets/Platformer/Boss/AnimLaser/AnimLaserGrey2.png", false));
	AnimLaserGrey.push_back(LoadSprite("Assets/Platformer/Boss/AnimLaser/AnimLaserGrey3.png", false));
	AnimLaserGrey.push_back(LoadSprite("Assets/Platformer/Boss/AnimLaser/AnimLaserGrey4.png", false));
	AddAnimLaser(AnimLaserGrey);
	handAttack.isSpawned = false;

	std::vector<sf::Sprite> AnimEyeBossOpening;
	AnimEyeBossOpening.push_back(LoadSprite("Assets/Platformer/Boss/OpenEyeBoss/OpenEyeBoss1.png", true));
	AnimEyeBossOpening.push_back(LoadSprite("Assets/Platformer/Boss/OpenEyeBoss/OpenEyeBoss2.png", true));
	AnimEyeBossOpening.push_back(LoadSprite("Assets/Platformer/Boss/OpenEyeBoss/OpenEyeBoss3.png", true));
	AnimEyeBossOpening.push_back(LoadSprite("Assets/Platformer/Boss/OpenEyeBoss/OpenEyeBoss3.png", true));
	AddAnimEye(AnimEyeBossOpening);

	std::vector<sf::Sprite> AnimEyeBossAttack;
	AnimEyeBossAttack.push_back(LoadSprite("Assets/Platformer/Boss/AttackEyeBoss/EyeAttack0.png", true));
	AnimEyeBossAttack.push_back(LoadSprite("Assets/Platformer/Boss/AttackEyeBoss/EyeAttack1.png", true));
	AddAnimEye(AnimEyeBossAttack);

	std::vector<sf::Sprite> AnimEyeBossCharge;
	AnimEyeBossCharge.push_back(LoadSprite("Assets/Platformer/Boss/EyeCharge/EyeCharge0.png", true));
	AnimEyeBossCharge.push_back(LoadSprite("Assets/Platformer/Boss/EyeCharge/EyeCharge1.png", true));
	AnimEyeBossCharge.push_back(LoadSprite("Assets/Platformer/Boss/EyeCharge/EyeCharge2.png", true));
	AnimEyeBossCharge.push_back(LoadSprite("Assets/Platformer/Boss/EyeCharge/EyeCharge3.png", true));
	AnimEyeBossCharge.push_back(LoadSprite("Assets/Platformer/Boss/EyeCharge/EyeCharge3.png", true));
	AddAnimEye(AnimEyeBossCharge);

	std::vector<sf::Sprite> AnimEyeDeath;
	AnimEyeDeath.push_back(LoadSprite("Assets/Platformer/Boss/DeathEye/0_0.png", true));
	AnimEyeDeath.push_back(LoadSprite("Assets/Platformer/Boss/DeathEye/0_1.png", true));
	AnimEyeDeath.push_back(LoadSprite("Assets/Platformer/Boss/DeathEye/0_2.png", true));
	AnimEyeDeath.push_back(LoadSprite("Assets/Platformer/Boss/DeathEye/0_3.png", true));
	AddAnimEye(AnimEyeDeath);
	std::vector<sf::Sprite> AnimEyeDeathFinal;
	AnimEyeDeathFinal.push_back(LoadSprite("Assets/Platformer/Boss/DeathEye/0_000.png", true));
	AnimEyeDeathFinal.push_back(LoadSprite("Assets/Platformer/Boss/DeathEye/0_000.png", true));

	AddAnimEye(AnimEyeDeathFinal);

	std::vector<sf::Sprite> AnimEyeBossLaser;
	AnimEyeBossLaser.push_back(LoadSprite("Assets/Platformer/Boss/BossLaser/BossLaserStart0.png", false));
	AnimEyeBossLaser.push_back(LoadSprite("Assets/Platformer/Boss/BossLaser/BossLaserStart1.png", false));
	AnimEyeBossLaser.push_back(LoadSprite("Assets/Platformer/Boss/BossLaser/BossLaserStart2.png", false));
	AnimEyeBossLaser.push_back(LoadSprite("Assets/Platformer/Boss/BossLaser/BossLaserStart2.png", false));
	bossNeylAnimBossLaser.push_back(AnimEyeBossLaser);

	std::vector<sf::Sprite> AnimEyeBossLaserStart;
	AnimEyeBossLaserStart.push_back(LoadSprite("Assets/Platformer/Boss/BossLaser/BossLaser0.png", false));
	AnimEyeBossLaserStart.push_back(LoadSprite("Assets/Platformer/Boss/BossLaser/BossLaser1.png", false));
	AnimEyeBossLaserStart.push_back(LoadSprite("Assets/Platformer/Boss/BossLaser/BossLaser2.png", false));
	AnimEyeBossLaserStart.push_back(LoadSprite("Assets/Platformer/Boss/BossLaser/BossLaser2.png", false));
	bossNeylAnimBossLaser.push_back(AnimEyeBossLaserStart);

	std::vector<sf::Sprite> AnimEyeBossLaserGrey;
	AnimEyeBossLaserGrey.push_back(LoadSprite("Assets/Platformer/Boss/BossLaser/BossLaserGrey0.png", false));
	AnimEyeBossLaserGrey.push_back(LoadSprite("Assets/Platformer/Boss/BossLaser/BossLaserGrey1.png", false));
	AnimEyeBossLaserGrey.push_back(LoadSprite("Assets/Platformer/Boss/BossLaser/BossLaserGrey2.png", false));
	AnimEyeBossLaserGrey.push_back(LoadSprite("Assets/Platformer/Boss/BossLaser/BossLaserGrey2.png", false));
	bossNeylAnimBossLaser.push_back(AnimEyeBossLaserGrey);

	std::vector<sf::Sprite> AnimArtefact;
	AnimArtefact.push_back(LoadSprite("Assets/Platformer/Boss/Artefact/artefact0.png", true));
	AnimArtefact.push_back(LoadSprite("Assets/Platformer/Boss/Artefact/artefact1.png", true));
	AnimArtefact.push_back(LoadSprite("Assets/Platformer/Boss/Artefact/artefact2.png", true));
	AnimArtefact.push_back(LoadSprite("Assets/Platformer/Boss/Artefact/artefact2.png", true));
	bossNeylArtefact.push_back(AnimArtefact);

	posWall.x = (camPos.x - 320 - 160);
	curAnim = SPAWNING;
	curAnimHand = ATTACKING;
	curAnimGenie = IDLEGENIE;
	curAnimWallHands = IDLEHANDS;
	curAnimEye = OPENEYE;
	isSpawned = false;
	spawnerTimer = 6;
	for (int i = 0; i < 20; i++)
	{
		animDurationWallHands[i] = 1.5f + (((float)(rand() % 10)) / 10.f);
		curTimeWallHands[i] = CreaMaths::GetRandomFloat(0.f, animDurationWallHands[i]);
		curAnimTileWallHands[i] = 0;
		speedWallHands[i] = rand() % 8;
	}
	for (int i = 0; i < 20; i++)
		bossNeylAnimLaserTab.push_back(bossNeylAnimLaser);
	for (int i = 0; i < 20; i++)
	{
		bossNeylAnimLaserBossTab.push_back(bossNeylAnimBossLaser);
		bossNeylAnimLaserBossTab2.push_back(bossNeylAnimBossLaser);
	}

}

void BossNeyl::UpdateBossNeyl(float dt, sf::Vector2f playerPos, sf::Vector2f camPos)
{
	if (camPos.x > 223 * TILE_SIZE)
		isPhase2Triggered = true;
	else
	{
		isPhase2Triggered = false;
	}

	if (isPhase2Triggered)
		BossPhase(dt, playerPos, camPos);


	if (spawnerTimer < 0)
	{
		if (!isSpawned)
		{
			curAnim = SPAWNING;
		}

		isSpawned = true;
	}
	else
	{
		spawnerTimer -= 1 * dt;
		isSpawned = false;
	}

	if (!isSpawned)
	{
		SetPosition(sf::Vector2f(camPos.x + (rand() % 320), camPos.y - rand() % (int)180));
	}
	else
	{
		//Animation
		curTime += dt;


		EyeShot(dt, playerPos);
		if (BossHP > 0)
			EyeShotBoss(dt, playerPos, camPos);
		curAnimTile = curTime * (bossNeylAnim[curAnim].size() - 1) / animDuration;
		bossNeylAnim[curAnim][curAnimTile].setPosition(pos);
		UpdateBossGenie(dt);

	}
}

void BossNeyl::HandAttackInit(sf::Vector2f camPos)
{

	handAttack.pos.x = camPos.x + (SCREEN_WIDTH / 3 / 2);
	handAttack.pos.y = camPos.y + (SCREEN_HEIGHT / 2);
}

void BossNeyl::HandAttack(float dt, sf::Vector2f camPos)
{
	if (handAttack.isSpawned)
	{
		if (handAttack.pos.x > camPos.x - 200)
		{
			if (handAttack.pos.y > camPos.y && handAttack.pos.y > camPos.y + SCREEN_HEIGHT / 4 - 270)
			{
				handAttack.pos.y -= 250 * dt;
			}
			else
			{
				handAttack.pos.x -= 150 * dt;
				curTimeHand += dt;
			}
		}
		else
		{
			handAttack.pos.y += 180 * dt;
			handAttack.pos.x -= 100 * dt;
			if (handAttack.pos.x < camPos.x - 800)
				handAttack.isSpawned = false;
		}
	}
	else
	{
		handAttack.timer -= dt;
	}
	curTimeHand += dt;
	if (curTimeHand > animDurationHand - 1)
	{
		curTimeHand = 0;
	}
	bossNeylAnimHand[curAnimHand][curAnimTileHand].setPosition(handAttack.pos);
	curAnimTileHand = curTimeHand * (bossNeylAnimHand[curAnimHand].size() - 1) / animDurationHand;
}

void BossNeyl::UpdateBossGenie(float dt)
{
	if (curTimeGenie > animDuration)
	{
		curTimeGenie = 0;
	}	curAnimTileGenie = curTimeGenie * (bossNeylAnimGenie[curAnimGenie].size() - 1) / animDuration;
}

void BossNeyl::BossPhase(float dt, sf::Vector2f playerPos, sf::Vector2f camPos)
{
	static bool hasPlayed = false;
	pmDeath.UpdateParticule(dt);
	ShieldTiming -= dt;
	if (handAttack.timer > 0)
		HandAttackInit(camPos);
	else
		handAttack.isSpawned = true;

	HandAttack(dt, camPos);
	EyeShotBoss(dt, playerPos, camPos);

	curTimeGenie += dt;
	if (curTimeGenie > animDurationGenie)
	{
		curTimeGenie = 0;
		if (curAnimGenie == DEATHGENIE)
			hasPlayed = true;
	}

	curTimeArtefact += dt;
	if (curTimeArtefact > animDurationGenie - 1)
	{
		curTimeArtefact = 0;
	}
	curAnimTileArtefact = curTimeGenie * (bossNeylArtefact[0].size() - 1) / animDurationGenie;
	curTimeEyeBoss += dt;
	if (curTimeEyeBoss > animDurationGenie)
	{
		curTimeEyeBoss = 0;
		if (curAnimEye == ATTACKEYE && BossHP > 0)
		{
			curAnimEye = OPENEYE;
			curAnimGenie = IDLEGENIE;
		}
		else if (curAnimEye == CHARGEYE && BossHP > 0)
		{
			curAnimEye = ATTACKEYE;
			curAnimGenie = ATTACKGENIE;
		}
		else if (curAnimEye == OPENEYE && BossHP > 0)
		{
			curAnimEye = CHARGEYE;
			curAnimGenie = CHARGE;
		}
	}
	if (ShieldTiming > 0)
	{
		curAnimGenie = SHIELD;
	}
	if (BossHP == 0 && curAnimGenie != DEATHGENIEFINAL)
	{
		curAnimGenie = DEATHGENIE;
		curAnimEye = DEATHEYE;
	}
	curAnimTileGenie = curTimeGenie * (bossNeylAnimGenie[curAnimGenie].size() - 1) / animDurationGenie;
	if (hasPlayed)
	{
		curAnimGenie = DEATHGENIEFINAL;
		curAnimEye = DEATHEYEFINAL;
		curAnimTileGenie = 0;
	}
	


	curAnimTileEyeBoss = curTimeEyeBoss * (bossNeylAnimEye[curAnimEye].size() - 1) / animDurationGenie;
}


void BossNeyl::EyeShot(float dt, sf::Vector2f playerPos)
{
	static bool isLaserPalced = false;

	if (curTime >= animDuration)
	{
		switch (curAnim)
		{
		case SPAWNING:

			curAnim = OPENING;
			break;
		case OPENING:
			curAnim = STILL;
			break;
		case STILL:
			curAnim = CLOSING;
			break;
		case CLOSING:
			spawnerTimer = 6;
			isSpawned = false;
			isLaserPalced = false;
			break;
		default:
			break;
		}
		curTime = 0;
	}

	static float rotation;
	if (isSpawned)
		irisSprite.setPosition(sf::Vector2f(pos.x, pos.y + 4));

	if (curAnim == SPAWNING && !isLaserPalced && isSpawned)
	{
		playerShotVector = sf::Vector2f(playerPos.x - irisSprite.getPosition().x, playerPos.y - irisSprite.getPosition().y);
		float normePlayerShotVector = sqrt(playerShotVector.x * playerShotVector.x + playerShotVector.y * playerShotVector.y);

		playerShotVector.x = playerShotVector.x / normePlayerShotVector;
		playerShotVector.y = playerShotVector.y / normePlayerShotVector;
		rotation = atan2f(playerShotVector.y, playerShotVector.x);

		isLaserPalced = true;
	}

	curTimeLaser += dt;

	if (curTimeLaser > animDurationLaser)
	{
		curTimeLaser = 0;
	}

	for (int i = 0; i < 20; i++)
	{
		curAnimTileLaser = curTimeLaser * (bossNeylAnimLaser[0].size() - 1) / animDurationLaser;

		sf::Vector2f spriteSize(64, 32);
		sf::Vector2f pos(irisSprite.getPosition());

		pos.x += spriteSize.x * cosf(rotation) * i;
		pos.y += spriteSize.x * sinf(rotation) * i;

		bossNeylAnimLaserTab[i][1][curAnimTileLaser].setPosition(pos);
		bossNeylAnimLaserTab[i][1][curAnimTileLaser].setOrigin(0, spriteSize.y / 2);
		bossNeylAnimLaserTab[i][1][curAnimTileLaser].setRotation(CreaMaths::RadiansToDegrees(rotation));
		if (curAnim == SPAWNING)
		{
			bossNeylAnimLaserTab[i][0][curAnimTileLaser].setPosition(pos);
			bossNeylAnimLaserTab[i][0][curAnimTileLaser].setOrigin(0, spriteSize.y / 2);
			bossNeylAnimLaserTab[i][0][curAnimTileLaser].setRotation(CreaMaths::RadiansToDegrees(rotation));
		}
	}
}

void BossNeyl::EyeShotBoss(float dt, sf::Vector2f playerPos, sf::Vector2f camPos)
{
	float rotation;
	float rotation2;
	static float timer = 4;
	static sf::Vector2f randomPos(rand() % 300 + camPos.x, camPos.y);

	if (curAnimEye == OPENEYE)
		randomPos = sf::Vector2f(rand() % 300 + camPos.x, camPos.y);


	playerShotVector = sf::Vector2f(randomPos.x - (camPos.x - 100 + 34), randomPos.y - (camPos.y - 153));
	playerShotVector2 = sf::Vector2f(randomPos.x - (camPos.x + 100 + 34), randomPos.y - (camPos.y - 153));
	float normePlayerShotVector = sqrt(playerShotVector.x * playerShotVector.x + playerShotVector.y * playerShotVector.y);
	float normePlayerShotVector2 = sqrt(playerShotVector2.x * playerShotVector2.x + playerShotVector2.y * playerShotVector2.y);

	curTimeBossLaser += dt;

	if (curTimeBossLaser > animDurationBossLaser)
	{
		curTimeBossLaser = 0;
	}
	playerShotVector.x = playerShotVector.x / normePlayerShotVector;
	playerShotVector2.x = playerShotVector2.x / normePlayerShotVector2;
	playerShotVector.y = playerShotVector.y / normePlayerShotVector;
	playerShotVector2.y = playerShotVector2.y / normePlayerShotVector2;

	rotation = atan2f(playerShotVector.y, playerShotVector.x);
	rotation2 = atan2f(playerShotVector2.y, playerShotVector2.x);
	sf::Vector2f pos(camPos.x - 100 + 40, camPos.y - camPos.y / 10);
	sf::Vector2f pos2(camPos.x + 100 + 40, camPos.y - camPos.y / 10);


	for (int i = 0; i < 20; i++)
	{
		curAnimTileBossLaser = curTimeBossLaser * (bossNeylAnimBossLaser[0].size() - 1) / animDurationBossLaser;

		sf::Vector2f spriteSize;
		sf::Vector2f spriteSizeCollider;

		spriteSize = { 128, 64 };
		spriteSizeCollider = { 128, 27 };

		pos.x += spriteSize.x * cosf(rotation) * i;
		pos2.x += spriteSize.x * cosf(rotation2) * i;
		pos.y += spriteSize.x * sinf(rotation) * i;
		pos2.y += spriteSize.x * sinf(rotation2) * i;

		if (i < 2)
		{
			laserCollider[i].setPosition(pos);
			laserCollider2[i].setPosition(pos2);
			laserCollider[i].setOrigin(0, spriteSizeCollider.y / 2);
			laserCollider2[i].setOrigin(0, spriteSizeCollider.y / 2);
			laserCollider[i].setRotation(CreaMaths::RadiansToDegrees(rotation));
			laserCollider2[i].setRotation(CreaMaths::RadiansToDegrees(rotation2));

			bossNeylAnimLaserBossTab[i][0][curAnimTileBossLaser].setPosition(pos);
			bossNeylAnimLaserBossTab[i][1][curAnimTileBossLaser].setPosition(pos);
			bossNeylAnimLaserBossTab[i][2][curAnimTileBossLaser].setPosition(pos);
			bossNeylAnimLaserBossTab2[i][0][curAnimTileBossLaser].setPosition(pos2);
			bossNeylAnimLaserBossTab2[i][1][curAnimTileBossLaser].setPosition(pos2);
			bossNeylAnimLaserBossTab2[i][2][curAnimTileBossLaser].setPosition(pos2);
			bossNeylAnimLaserBossTab[i][0][curAnimTileBossLaser].setOrigin(0, spriteSize.y / 2);
			bossNeylAnimLaserBossTab[i][1][curAnimTileBossLaser].setOrigin(0, spriteSize.y / 2);
			bossNeylAnimLaserBossTab[i][2][curAnimTileBossLaser].setOrigin(0, spriteSize.y / 2);
			bossNeylAnimLaserBossTab2[i][0][curAnimTileBossLaser].setOrigin(0, spriteSize.y / 2);
			bossNeylAnimLaserBossTab2[i][1][curAnimTileBossLaser].setOrigin(0, spriteSize.y / 2);
			bossNeylAnimLaserBossTab2[i][2][curAnimTileBossLaser].setOrigin(0, spriteSize.y / 2);
			bossNeylAnimLaserBossTab[i][0][curAnimTileBossLaser].setRotation(CreaMaths::RadiansToDegrees(rotation));
			bossNeylAnimLaserBossTab[i][1][curAnimTileBossLaser].setRotation(CreaMaths::RadiansToDegrees(rotation));
			bossNeylAnimLaserBossTab[i][2][curAnimTileBossLaser].setRotation(CreaMaths::RadiansToDegrees(rotation));
			bossNeylAnimLaserBossTab2[i][0][curAnimTileBossLaser].setRotation(CreaMaths::RadiansToDegrees(rotation2));
			bossNeylAnimLaserBossTab2[i][1][curAnimTileBossLaser].setRotation(CreaMaths::RadiansToDegrees(rotation2));
			bossNeylAnimLaserBossTab2[i][2][curAnimTileBossLaser].setRotation(CreaMaths::RadiansToDegrees(rotation2));
		}
		else
		{
			sf::Vector2f erreur1;
			erreur1 = CreaMaths::CreateVector(bossNeylAnimLaserBossTab[0][0][curAnimTileBossLaser].getPosition(), bossNeylAnimLaserBossTab[1][0][curAnimTileBossLaser].getPosition());

			erreur1.x = (erreur1.x * (i - 1)) + (erreur1.x * (i - 2));
			erreur1.y = (erreur1.y * (i - 1)) + (erreur1.y * (i - 2));

			sf::Vector2f erreur2;
			erreur2 = CreaMaths::CreateVector(bossNeylAnimLaserBossTab2[0][0][curAnimTileBossLaser].getPosition(), bossNeylAnimLaserBossTab2[1][0][curAnimTileBossLaser].getPosition());

			erreur2.x = (erreur2.x * (i - 1)) + (erreur2.x * (i - 2));
			erreur2.y = (erreur2.y * (i - 1)) + (erreur2.y * (i - 2));

			laserCollider[i].setPosition(pos - erreur1);
			laserCollider2[i].setPosition(pos2 - erreur2);
			laserCollider[i].setOrigin(0, spriteSizeCollider.y / 2);
			laserCollider2[i].setOrigin(0, spriteSizeCollider.y / 2);
			laserCollider[i].setRotation(CreaMaths::RadiansToDegrees(rotation));
			laserCollider2[i].setRotation(CreaMaths::RadiansToDegrees(rotation2));

			bossNeylAnimLaserBossTab[i][0][curAnimTileBossLaser].setPosition(pos - erreur1);
			bossNeylAnimLaserBossTab2[i][0][curAnimTileBossLaser].setPosition(pos2 - erreur2);
			bossNeylAnimLaserBossTab[i][0][curAnimTileBossLaser].setOrigin(0, spriteSize.y / 2);
			bossNeylAnimLaserBossTab2[i][0][curAnimTileBossLaser].setOrigin(0, spriteSize.y / 2);
			bossNeylAnimLaserBossTab[i][0][curAnimTileBossLaser].setRotation(CreaMaths::RadiansToDegrees(rotation));
			bossNeylAnimLaserBossTab2[i][0][curAnimTileBossLaser].setRotation(CreaMaths::RadiansToDegrees(rotation2));
		}

	}
}

void BossNeyl::UpdateBossNeylWall(sf::Vector2f camPos, sf::Vector2f camSize, float dt)
{
	curAnimWall = IDLEWALL;
	curAnimWallHands = IDLEHANDS;
	static float x = 0;
	x += 0.1;
	posWall.x = (camPos.x - camSize.x / 2 - camSize.x / 4) - 100;
	posWall.y = camPos.y - camSize.y / 2;
	curTimeWall += 2 * dt;
	for (int i = 0; i < 20; i++)
		curTimeWallHands[i] += (rand() % 5) * dt;
	if (curTimeWall >= animDuration)
	{
		curTimeWall = 0;
	}
	for (int i = 0; i < 20; i++)
	{
		if (curTimeWallHands[i] >= animDurationWallHands[i])
		{
			curTimeWallHands[i] = 0;
		}
		curAnimTileWallHands[i] = curTimeWallHands[i] * (bossNeylAnimWallHands[curAnimWallHands].size() - 1) / animDurationWallHands[i];
	}
	curAnimTileWall = curTimeWall * (bossNeylAnim[curAnimWall].size() - 1) / animDuration;
	bossNeylAnimWall[curAnimWall][curAnimTileWall].setPosition(posWall);
}

void BossNeyl::Draw(sf::RenderWindow& _window, sf::Vector2f camPos)
{
	static int x = 0;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			bossNeylAnimWall[curAnimWall][curAnimTileWall].setScale(1, 1);
			bossNeylAnimWallEnd[0][curAnimTileWall].setScale(1, 1);
			bossNeylAnimWall[curAnimWall][curAnimTileWall].setPosition(sf::Vector2f(posWall.x - 50 + 64 * j, posWall.y + 32 * i));
			bossNeylAnimWallEnd[0][curAnimTileWall].setPosition(sf::Vector2f(posWall.x - 50 + 32 + 64 * 4, (posWall.y + 32 * i) - 16));
			_window.draw(bossNeylAnimWall[curAnimWall][curAnimTileWall]);
			_window.draw(bossNeylAnimWallEnd[0][curAnimTileWall]);
		}
	}
	if (isPhase2Triggered)
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				bossNeylAnimWall[curAnimWall][curAnimTileWall].setScale(-1, 1);
				bossNeylAnimWall[curAnimWall][curAnimTileWall].setPosition(sf::Vector2f(100 + camPos.x + SCREEN_WIDTH / 2 - SCREEN_WIDTH / 4 - 64 * j, posWall.y + 32 * i));
				bossNeylAnimWallEnd[0][curAnimTileWall].setScale(-1, 1);
				bossNeylAnimWallEnd[0][curAnimTileWall].setPosition(sf::Vector2f(100 + camPos.x - 32 + SCREEN_WIDTH / 2 - SCREEN_WIDTH / 4 - 64 * 3, (posWall.y + 32 * i) - 16));

				_window.draw(bossNeylAnimWall[curAnimWall][curAnimTileWall]);
				_window.draw(bossNeylAnimWallEnd[0][curAnimTileWall]);
			}
		}
	}
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			speedWallHands[i] += 0.01f;
			bossNeylAnimWallHands[curAnimWallHands][curAnimTileWallHands[i]].setScale(1, 1);
			if (i < 11)
				bossNeylAnimWallHands[curAnimWallHands][curAnimTileWallHands[i]].setPosition(sf::Vector2f(posWall.x + 128 * j + 8 * sin(speedWallHands[i]) - 32, posWall.y + 45 * i + 6 * cos(speedWallHands[i])));
			else
				bossNeylAnimWallHands[curAnimWallHands][curAnimTileWallHands[i]].setPosition(sf::Vector2f(posWall.x + 128 * j + 8 * sin(speedWallHands[i]) + 0, posWall.y + 45 * (i - 10) + 6 * cos(speedWallHands[i])));

			_window.draw(bossNeylAnimWallHands[curAnimWallHands][curAnimTileWallHands[i]]);

		}
	}
	if (isPhase2Triggered)
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				speedWallHands[i] += 0.01f;
				bossNeylAnimWallHands[curAnimWallHands][curAnimTileWallHands[i]].setScale(-1, 1);
				if (i < 11)
					bossNeylAnimWallHands[curAnimWallHands][curAnimTileWallHands[i]].setPosition(sf::Vector2f(camPos.x + SCREEN_WIDTH / 2 - SCREEN_WIDTH / 5 - 100 * j + 8 * sin(speedWallHands[i]) - 12, posWall.y + 45 * i + 6 * cos(speedWallHands[i])));
				else
					bossNeylAnimWallHands[curAnimWallHands][curAnimTileWallHands[i]].setPosition(sf::Vector2f(camPos.x + SCREEN_WIDTH / 2 - SCREEN_WIDTH / 5 - 112 * j + 8 * sin(speedWallHands[i]) - 12, posWall.y + 45 * (i - 10) + 6 * cos(speedWallHands[i])));
				_window.draw(bossNeylAnimWallHands[curAnimWallHands][curAnimTileWallHands[i]]);

			}
		}
	}
	if (!isPhase2Triggered)
	{
		if (isSpawned)
		{
			_window.draw(irisSprite);
			_window.draw(bossNeylAnim[curAnim][curAnimTile]);
			if (curAnim != CLOSING && curAnim != SPAWNING)
			{
				for (int i = 0; i < 10; i++)
					_window.draw(bossNeylAnimLaserTab[i][1][curAnimTileLaser]);
				if (laserSound.getStatus() != sf::Sound::Playing)
				{
					laserSound.play();
				}
			}
		}
		if ((curAnim == STILL) && isSpawned)
		{

			for (int i = 0; i < 10; i++)
			{
				_window.draw(bossNeylAnimLaserTab[i][0][curAnimTileLaser]);
			}
		}
		else
		{
			laserSound.stop();
		}
	}
	else
	{
		
		static float x = 0;
		x += (float)2 / 60;
		bossNeylAnimEye[curAnimEye][curAnimTileEyeBoss].setScale(1, 1);
		bossNeylAnimEye[curAnimEye][curAnimTileEyeBoss].setPosition(camPos.x - 60, camPos.y - 100);
		_window.draw(bossNeylAnimEye[curAnimEye][curAnimTileEyeBoss]);
		bossNeylAnimEye[curAnimEye][curAnimTileEyeBoss].setPosition(camPos.x + 140, camPos.y - 100);
		bossNeylAnimEye[curAnimEye][curAnimTileEyeBoss].setScale(-1, 1);
		_window.draw(bossNeylAnimEye[curAnimEye][curAnimTileEyeBoss]);
		bossNeylAnimGenie[curAnimGenie][curAnimTileGenie].setPosition(sf::Vector2f(camPos.x + 40, 950 - 80 + 5 * sin(x)));


		_window.draw(bossNeylAnimGenie[curAnimGenie][curAnimTileGenie]);

		pmDeath.AddParticle(sf::Vector2i(bossNeylAnimGenie[curAnimGenie][curAnimTileGenie].getPosition()), SMOG, (3 - BossHP) * 4, sf::Color::Red, (3 - BossHP) * 8.f);

		if (BossHP == 1)
			pmDeath.AddParticle(sf::Vector2i(bossNeylAnimGenie[curAnimGenie][curAnimTileGenie].getPosition()), SMOG, (3 - BossHP) * 4, sf::Color::Red, (3 - BossHP) * 4.f);

		if (BossHP > 0)
			pmDeath.DrawParticule(_window);

		if (BossHP == 0)
		{
			bossNeylArtefact[0][curAnimTileArtefact].setPosition(sf::Vector2f(bossNeylAnimGenie[curAnimGenie][curAnimTileGenie].getPosition().x, bossNeylAnimGenie[curAnimGenie][curAnimTileGenie].getPosition().y + 50));
			_window.draw(bossNeylArtefact[0][curAnimTileArtefact]);
		}

		for (int i = 0; i < 20; i++)
		{
			_window.draw(bossLaserSprite[i]);
			_window.draw(bossLaserSprite2[i]);
		}
		if (curAnimEye == CHARGEYE && BossHP > 0)
		{
			for (int i = 0; i < 20; i++)
			{
				_window.draw(bossNeylAnimLaserBossTab[i][2][curAnimTileBossLaser]);
				_window.draw(bossNeylAnimLaserBossTab2[i][2][curAnimTileBossLaser]);
			}
		}
		if (curAnimEye == ATTACKEYE)
		{
			for (int i = 0; i < 20; i++)
			{
				if (i == 0)
				{
					_window.draw(bossNeylAnimLaserBossTab[i][1][curAnimTileBossLaser]);
					_window.draw(bossNeylAnimLaserBossTab2[i][1][curAnimTileBossLaser]);
				}
				else
				{
					_window.draw(bossNeylAnimLaserBossTab[i][0][curAnimTileBossLaser]);
					_window.draw(bossNeylAnimLaserBossTab2[i][0][curAnimTileBossLaser]);
				}
			}

		}
		if ((curAnimEye == CHARGEYE || curAnimEye == ATTACKEYE) && BossHP > 0)
		{
			if (laserSound.getStatus() != sf::Sound::Playing)
			{
				laserSound.play();
			}
		}
		else
		{
			laserSound.stop();
		}
	}
	if (isPhase2Triggered && handAttack.isSpawned)
	{
		_window.draw(bossNeylAnimHand[curAnimHand][curAnimTileHand]);
	}
}