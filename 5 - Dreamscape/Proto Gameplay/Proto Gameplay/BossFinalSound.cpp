#include "BossFinalSound.h"

sf::Music BossFinalTheme;
sf::Sound BossFinalScream;
sf::Sound ChangeWorld;
sf::Sound BossDeath;
sf::Sound BlackHoleSound;
sf::Sound GlyphSound;
sf::Sound HandSound;
sf::Sound LaserSound;
sf::Sound RootSound;
sf::Sound ThornSound;
sf::Sound MineSound;
sf::Sound RegenSound;

sf::Sound WarningThunder;
sf::Sound Thunder;
sf::Sound Apparition;
sf::Sound Disparition;
sf::Sound BounceBall;

void LoadBossSound()
{
	BossFinalTheme.openFromFile("Assets/BossFinal/Son/BossTheme.ogg");
	BossFinalScream = LoadSound("Assets/BossFinal/Son/Scream.ogg");
	BlackHoleSound = LoadSound("Assets/BossFinal/Son/Souls/Black_Hole.wav");
	GlyphSound = LoadSound("Assets/BossFinal/Son/Souls/Glyph.wav");
	HandSound = LoadSound("Assets/BossFinal/Son/Souls/Hands.wav");
	LaserSound = LoadSound("Assets/BossFinal/Son/Souls/Laser.wav");
	RootSound = LoadSound("Assets/BossFinal/Son/Souls/Root.wav");
	ThornSound = LoadSound("Assets/BossFinal/Son/Souls/Thorn.wav");
	ChangeWorld = LoadSound("Assets/BossFinal/Son/ChangeWord.wav");
	MineSound = LoadSound("Assets/BossFinal/Son/STU/Mine.wav");
	RegenSound = LoadSound("Assets/BossFinal/Son/STU/Regen.wav");
	BossDeath = LoadSound("Assets/BossFinal/Son/BossDead.wav");
	WarningThunder = LoadSound("Assets/BossFinal/Son/Platformer/beforeThunder.wav");
	Thunder = LoadSound("Assets/BossFinal/Son/Platformer/ThunderFinalBoss.wav");
	BounceBall = LoadSound("Assets/BossFinal/Son/Platformer/BounceBall.wav");
	Apparition = LoadSound("Assets/BossFinal/Son/Platformer/Apparition.wav");
	Disparition = LoadSound("Assets/BossFinal/Son/Platformer/Disparition.wav");

}

void PlayBossTheme()
{
	BossFinalTheme.setLoop(true);
	BossFinalTheme.play();
}

void StopBossTheme()
{
	BossFinalTheme.stop();
}

void PlayBossScream()
{
	if (BossFinalScream.getStatus() != sf::SoundSource::Playing)
	{
		BossFinalScream.play();
	}
}

void PlayBlackHoleSound()
{
	if (BlackHoleSound.getStatus() != sf::SoundSource::Playing)
	{
		BlackHoleSound.play();
	}
}

void PlayGlyphSound()
{
	if (GlyphSound.getStatus() != sf::SoundSource::Playing)
	{
		GlyphSound.play();
	}
}

void PlayHandSound()
{
	if (HandSound.getStatus() != sf::SoundSource::Playing)
	{
		HandSound.play();
	}
}

void PlayLaserSound()
{
	if (LaserSound.getStatus() != sf::SoundSource::Playing)
	{
		LaserSound.play();
	}
}

void PlayRootSound()
{
	if (RootSound.getStatus() != sf::SoundSource::Playing)
	{
		RootSound.play();
	}
}

void PlayThornSound()
{
	if (ThornSound.getStatus() != sf::SoundSource::Playing)
	{
		ThornSound.play();
	}
}

void PlayChangeWorld()
{
	if (ChangeWorld.getStatus() != sf::SoundSource::Playing)
	{
		ChangeWorld.play();
	}
}

void PlayMineSound()
{
	if (MineSound.getStatus() != sf::SoundSource::Playing)
	{
		MineSound.play();
	}
}

void PlayRegenSound()
{
	if (RegenSound.getStatus() != sf::SoundSource::Playing)
	{
		RegenSound.play();
	}
}

void StopRegenSound()
{
	if (RegenSound.getStatus() == sf::SoundSource::Playing)
	{
		RegenSound.stop();
	}
}

void PlayBossDeath()
{
	if (BossDeath.getStatus() != sf::SoundSource::Playing)
	{
		BossDeath.play();
	}
}

void PlayWarningThunder()
{
	if (WarningThunder.getStatus() != sf::SoundSource::Playing)
	{
		WarningThunder.play();
	}
}
void PlayThunderSound()
{
	if (Thunder.getStatus() != sf::SoundSource::Playing)
	{
		Thunder.play();
	}
}
void PlayApparition()
{
	if (Apparition.getStatus() != sf::SoundSource::Playing)
	{
		Apparition.play();
	}
}
void PlayDisparition()
{
	if (Disparition.getStatus() != sf::SoundSource::Playing)
	{
		Disparition.play();
	}
}
void PlayBounceBall()
{
	BounceBall.play();
}