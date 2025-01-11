#include "GameData.h"
#include <sfeMovie/Movie.hpp>

ParticuleManager ParticuleFinalBoss;
void GameData::Init()
{
	srand(time(NULL));
	rand(); rand(); rand();

	m_window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "DreamScape", sf::Style::Fullscreen);
	m_window.setVerticalSyncEnabled(true);

	gameState = S_INTRO;
	m_player.Init();
	sf::Image cursorImage;
	cursorImage.loadFromFile("Assets/Cursor/cursor.png");
	m_cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(0, 0));

	AnimationManager::Load();
	LoadLobbyManager(m_player, font, camCoord, Noir);
	LoadSTU();
	LoadBoss();
	LoadSoundLobby();
	MenuInit(&menuData,m_player, *m_controls);
	InitPlatformer(platformerData);
	LoadVictory();
	video.Load("Intro.mp4", "Music.ogg");
	video.Play();
	InitPause(&menuData, m_player, *m_controls);
	m_deltaTime.restart();
}

void GameData::Event()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
		{
			m_window.close();
			break;
		}

		case sf::Event::KeyPressed:
		{
			m_config = KEYBOARD;

			switch (event.key.code)
			{


			default:
				break;
			}
			break;
		}
		case sf::Event::MouseMoved:
		{
			m_config = KEYBOARD;
			break;
		}
		case sf::Event::MouseButtonPressed:
		{
			m_config = KEYBOARD;
			break;
		}

		case sf::Event::JoystickButtonPressed:
		{
			m_config = CONTROLLER;
			break;
		}

		case sf::Event::JoystickMoved:
		{
			m_config = CONTROLLER;
			break;
		}

		default:
			break;
		}
	}
	m_config == CONTROLLER ? m_window.setMouseCursorVisible(false) : m_window.setMouseCursorVisible(true);
}

void GameData::Update()
{
	m_dt = m_deltaTime.restart().asSeconds();

	m_transition.Update(m_dt);
	UpdateTransition(m_dt, noirAlpha, transition);
	//ParticuleFinalBoss.AddParticle(sf::Mouse::getPosition(), FINAL_BOSS_HAND, 1, sf::Color::Magenta);
	
	//ParticuleFinalBoss.AddParticle(sf::Mouse::getPosition(), BLACK_HOLE_BOSS, 1000, sf::Color::Magenta, 300);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !menuData.pause && gameState != MENU && gameState != S_INTRO && gameState != VICTORY)
	{
		StopBossTheme();
		StopLobbyTheme();
		platformerData.PlatformerMusic.stop();
		platformerData.PlatformerMusic2.stop();
		menuData.pause = true;
	}

	if (!menuData.pause)
	{

		switch (gameState)
		{
		case S_INTRO:
			if (video.KeyPressedIntro())
			{
				gameState = MENU;
			};
			if (video.GetState() == 0)
			{
				gameState = MENU;
			}
			video.Update();
			break;

		case MENU:MenuUpdate(&menuData, m_window, gameState, m_config, m_dt, m_player, m_controls);
			break;

		case SHOOTUP:
			UpdateShooterLevel();
			break;

		case SOULS:
			UpdateSoulsLevel();
			break;

		case PARCOURS:
			UpdatePlatformerLevel();
			break;

		case LOBBY:
			UpdateLobbyManager(m_dt, m_player, gameState, camCoord, animation, noirAlpha, transition, m_soulsLevel, platformerData);
			if (!transition && !animation)
			{
				m_player.Update(m_config, m_dt, m_controls);
			}
			break;

		case BOSS:
			UpdateBoss(m_dt, gameState, m_player, transition, noirAlpha, m_config, m_soulsLevel, platformerData, m_window, m_controls, m_soulsLevel);
			break;

		case VICTORY:
			UpdateVictory(m_dt, (sf::Vector2f)sf::Mouse::getPosition(m_window), gameState, m_config, transition, noirAlpha);
			break;
		}

		ParticuleFinalBoss.UpdateParticule(m_dt);
	}
	else
	{
		UpdatePause(&menuData, m_window, m_config, m_dt, gameState, menuData.pause, m_player);
	}
}

void GameData::Display()
{
	m_window.clear(sf::Color::Black);
	m_window.setMouseCursor(m_cursor);

	switch (gameState)
	{
	case S_INTRO:video.Draw(&m_window);
		break;

	case MENU:MenuDisplay(&menuData, m_window, *m_controls);
		BlitSprite(Noir, m_window.getView().getCenter() - m_window.getView().getSize() / 2.f, m_window, Noir.getScale(), Noir.getRotation(), sf::Color(0, 0, 0, noirAlpha));
		break;

	case SHOOTUP:
		DisplaySTU(m_window);
		playerView.reset({ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT });
		m_window.setView(playerView);
		BlitSprite(Noir, m_window.getView().getCenter() - m_window.getView().getSize() / 2.f, m_window, Noir.getScale(), Noir.getRotation(), sf::Color(0, 0, 0, noirAlpha));
		break;

	case SOULS:
		m_soulsLevel->Display(m_window);
		BlitSprite(Noir, m_window.getView().getCenter() - m_window.getView().getSize() / 2.f, m_window, Noir.getScale(), Noir.getRotation(), sf::Color(0, 0, 0, noirAlpha));
		break;

	case PARCOURS:
		DrawPlatformer(platformerData, m_window);
		BlitSprite(Noir, m_window.getView().getCenter() - m_window.getView().getSize() / 2.f, m_window, Noir.getScale(), Noir.getRotation(), sf::Color(0, 0, 0, noirAlpha));
		break;

	case LOBBY:
		DisplayLobbyManager(m_window, m_player);
		BlitSprite(Noir, m_window.getView().getCenter() - m_window.getView().getSize() / 2.f, m_window, Noir.getScale(), Noir.getRotation(), sf::Color(0, 0, 0, noirAlpha));
		break;

	case BOSS:
		DisplayBoss(m_window, m_soulsLevel, platformerData);
		BlitSprite(Noir, m_window.getView().getCenter() - m_window.getView().getSize() / 2.f, m_window, Noir.getScale(), Noir.getRotation(), sf::Color(255, 255, 255, noirAlpha));
		break;
	case VICTORY:
		DisplayVictory(m_window);
		BlitSprite(Noir, m_window.getView().getCenter() - m_window.getView().getSize() / 2.f, m_window, Noir.getScale(), Noir.getRotation(), sf::Color(0, 0, 0, noirAlpha));
		break;
	}


	if (menuData.pause)
	{
		DisplayPause(&menuData, m_window, *m_controls);
	}

	m_transition.Display(m_window);
	ParticuleFinalBoss.DrawParticule(m_window);
	m_window.display();
}














/////////////////////////////////////////////////////////// Fonctions intermédiaires pour alléger le code

void GameData::UpdateShooterLevel()
{
	UpdateSTU(m_dt, gameState, m_player, transition, noirAlpha, m_controls);
}

void GameData::UpdateSoulsLevel()
{
	if (!m_soulsLevel->HasWon() && !m_soulsLevel->HasLost())
	{
		m_soulsLevel->Update(m_dt, m_config);
	}
	else
	{
		m_transition.Play(1.f, Transition::FADE_IN);

		if (m_transition.HasEnded())
		{
			if (m_soulsLevel->HasWon())
			{
				m_player.Set_IsGreenTotem(true);
			}

			gameState = LOBBY;
			m_transition.ForcePlay(1.f, Transition::FADE_OUT);
			delete m_soulsLevel;
		}
	}
}

void GameData::UpdatePlatformerLevel()
{
	UpdatePlatformer(m_dt, platformerData, m_window, gameState, transition, noirAlpha, m_controls, m_player);
}