#include "SonLobby.h"

sf::Sound AltarMove;
sf::Sound TotemPlace;
sf::Sound AltarAnimationEnd;
sf::Sound Teleportation;
sf::Sound DialogueSound;
sf::Music themelobby;

void LoadSoundLobby()
{
	AltarMove = LoadSound("Assets/Lobby/Sound/AltarMove.ogg");
	TotemPlace = LoadSound("Assets/Lobby/Sound/TotemPlace.ogg");
	AltarAnimationEnd = LoadSound("Assets/Lobby/Sound/AltarAnimationEnd.ogg");
	Teleportation = LoadSound("Assets/Lobby/Sound/teleportation.ogg");
	themelobby.openFromFile("Assets/Lobby/Sound/Theme.ogg");
	DialogueSound = LoadSound("Assets/Menu/dialogueSkip.wav");
}

void PlayAltarSound()
{
	AltarMove.play();
}

void PlayTotemPlace()
{
	if (TotemPlace.getStatus() != sf::SoundSource::Playing)
	{
		TotemPlace.play();
	}
}

void PlayAltarAnimationEnd()
{
	if (AltarAnimationEnd.getStatus() != sf::SoundSource::Playing)
	{
		AltarAnimationEnd.play();
	}
}

void PlayTeleportationSound()
{
	if (Teleportation.getStatus() != sf::SoundSource::Playing)
	{
		Teleportation.play();
	}
}

void PlayLobbyTheme()
{
	themelobby.setLoop(true);
	if (themelobby.getStatus() != sf::SoundSource::Playing)
	{
		themelobby.play();
	}
}

void StopLobbyTheme()
{
	themelobby.stop();
}

void PlayDialogueSound()
{
	if (DialogueSound.getStatus() != sf::SoundSource::Playing)
	{
		DialogueSound.play();
	}
}