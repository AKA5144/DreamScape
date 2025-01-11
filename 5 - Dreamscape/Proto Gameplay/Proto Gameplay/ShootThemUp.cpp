#include "ShootThemUp.hpp"

STUgameData SG;
STUGameState STUgameState;

sf::Music STUGameMusic;

void LoadBg(void)
{
	std::string filePath = "Assets/Shoot Them Up/BackGround/";

	//rainbow//
	for (int k = 0; k < BG_MAX1; k++)
	{
		SG.backGround1[k] = LoadSprite(filePath + "Rainbow/" + std::to_string(k + 1) + ".png", false);
		SG.backGround1[k].setOrigin({ (float)SG.backGround1[0].getTexture()->getSize().x / 2,(float)SG.backGround1[0].getTexture()->getSize().y });
	}
	SG.bg1Pos[0] = { SCREEN_WIDTH / 2, 0 };
	SG.bg1Pos[1] = { SCREEN_WIDTH / 2 , (float)SG.backGround1[0].getTexture()->getSize().y * SG.scaleBg.y };
	SG.bg1[0] = 0;
	SG.bg1[1] = 1;


	//starsUp//
	for (int k = 0; k < BG_MAX2; k++)
	{
		SG.backGround2[k] = LoadSprite(filePath + "Stars/Up/" +  std::to_string(k + 1) + ".png", false);
		SG.backGround2[k].setOrigin({ (float)SG.backGround1[0].getTexture()->getSize().x / 2,(float)SG.backGround1[0].getTexture()->getSize().y });
	}
	SG.bg2Pos[0] = { SCREEN_WIDTH / 2, 0 };
	SG.bg2Pos[1] = { SCREEN_WIDTH / 2 , (float)SG.backGround1[0].getTexture()->getSize().y * SG.scaleBg.y };
	SG.bg2[0] = 0;
	SG.bg2[1] = 1;


	//starsDown//
	for (int k = 0; k < BG_MAX3; k++)
	{
		SG.backGround3[k] = LoadSprite(filePath + "Stars/Down/" + std::to_string(k + 1) + ".png", false);
		SG.backGround3[k].setOrigin({ (float)SG.backGround1[0].getTexture()->getSize().x / 2,(float)SG.backGround1[0].getTexture()->getSize().y });
	}
	SG.bg3Pos[0] = { SCREEN_WIDTH / 2, 0 };
	SG.bg3Pos[1] = { SCREEN_WIDTH / 2 , (float)SG.backGround1[0].getTexture()->getSize().y * SG.scaleBg.y };
	SG.bg3[0] = 0;
	SG.bg3[1] = 1;


	//planetsUp//
	for (int k = 0; k < BG_MAX4; k++)
	{
		SG.backGround4[k] = LoadSprite(filePath + "Planets/Up/" + std::to_string(k + 1) + ".png", false);
		SG.backGround4[k].setOrigin({ (float)SG.backGround1[0].getTexture()->getSize().x / 2,(float)SG.backGround1[0].getTexture()->getSize().y });
	}
	SG.bg4Pos[0] = { SCREEN_WIDTH / 2, 0 };
	SG.bg4Pos[1] = { SCREEN_WIDTH / 2 , (float)SG.backGround1[0].getTexture()->getSize().y * SG.scaleBg.y };
	SG.bg4[0] = 0;
	SG.bg4[1] = 1;

	//planetsDown//
	for (int k = 0; k < BG_MAX5; k++)
	{
		SG.backGround5[k] = LoadSprite(filePath + "Planets/Down/" + std::to_string(k + 1) + ".png", false);
		SG.backGround5[k].setOrigin({ (float)SG.backGround1[0].getTexture()->getSize().x / 2,(float)SG.backGround1[0].getTexture()->getSize().y });
	}
	SG.bg5Pos[0] = { SCREEN_WIDTH / 2, 0 };
	SG.bg5Pos[1] = { SCREEN_WIDTH / 2 , (float)SG.backGround1[0].getTexture()->getSize().y * SG.scaleBg.y };
	SG.bg5[0] = 0;
	SG.bg5[1] = 1;


	SG.Em.LoadEntities();
}

void LoadSTU(void)
{
	LoadSTUTuto();
	LoadSTUGameOver();
	LoadBg();
	SG.Hud.Load();
	SG.MiniBoss.Load();

	STUgameState = STU_TUTO;

	STUGameMusic.openFromFile("Assets/Shoot Them Up/Musics/mainMusic.wav");
	STUGameMusic.setLoop(true);

	SG.viewGame.reset(sf::FloatRect(360, 0, 1200, SCREEN_HEIGHT));
	SG.viewHud.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	SG.viewGame.setViewport(sf::FloatRect(0.1875, 0, 0.625, 1));
	SG.viewHud.setViewport(sf::FloatRect(0, 0, 1, 1));
}

void UpadateBg(float _dt)
{
	static float sizeY = (float)SG.backGround1[0].getTexture()->getSize().y * SG.scaleBg.y;

	for (int k = 0; k < BG_MAX1; k++)
	{
		SG.bg1Pos[k].y += 200 * _dt;

		//stars//
		SG.bg2Pos[k].y += 100 * _dt;
		SG.bg3Pos[k].y +=  70 * _dt;

		//planets//
		SG.bg4Pos[k].y += 175 * _dt;
		SG.bg5Pos[k].y += 145 * _dt;
	}


	////1////
	if (SG.bg1Pos[0].y - sizeY > SCREEN_HEIGHT)
	{
		SG.bg1Pos[0] = { SCREEN_WIDTH / 2, SG.bg1Pos[1].y - sizeY };
		SG.bg1[0] == BG_MAX1 - 2 ? SG.bg1[0] = 0 : SG.bg1[0] += 2;
	}

	if (SG.bg1Pos[1].y - sizeY > SCREEN_HEIGHT)
	{
		SG.bg1Pos[1] = { SCREEN_WIDTH / 2, SG.bg1Pos[0].y - sizeY };
		SG.bg1[1] == BG_MAX1 - 1 ? SG.bg1[1] = 1 : SG.bg1[1] += 2;
	}

	////2////
	if (SG.bg2Pos[0].y - sizeY > SCREEN_HEIGHT)
	{
		SG.bg2Pos[0] = { SCREEN_WIDTH / 2, SG.bg2Pos[1].y - sizeY };
		SG.bg2[0] == BG_MAX2 - 1 ? SG.bg2[0] = 0 : SG.bg2[0] += 1;
	}

	if (SG.bg2Pos[1].y - sizeY > SCREEN_HEIGHT)
	{
		SG.bg2Pos[1] = { SCREEN_WIDTH / 2, SG.bg2Pos[0].y - sizeY };
		SG.bg2[1] == BG_MAX2 - 1 ? SG.bg2[1] = 1 : SG.bg2[1] += 1;
	}

	////3////
	if (SG.bg3Pos[0].y - sizeY > SCREEN_HEIGHT)
	{
		SG.bg3Pos[0] = { SCREEN_WIDTH / 2, SG.bg3Pos[1].y - sizeY };
		SG.bg3[0] == BG_MAX3 - 1 ? SG.bg3[0] = 0 : SG.bg3[0] += 1;
	}

	if (SG.bg3Pos[1].y - sizeY > SCREEN_HEIGHT)
	{
		SG.bg3Pos[1] = { SCREEN_WIDTH / 2, SG.bg3Pos[0].y - sizeY };
		SG.bg3[1] == BG_MAX3 - 1 ? SG.bg3[1] = 1 : SG.bg3[1] += 1;
	}

	////4////
	if (SG.bg4Pos[0].y - sizeY > SCREEN_HEIGHT)
	{
		SG.bg4Pos[0] = { SCREEN_WIDTH / 2, SG.bg4Pos[1].y - sizeY };
		SG.bg4[0] == BG_MAX4 - 1 ? SG.bg4[0] = 0 : SG.bg4[0] += 1;
	}

	if (SG.bg4Pos[1].y - sizeY > SCREEN_HEIGHT)
	{
		SG.bg4Pos[1] = { SCREEN_WIDTH / 2, SG.bg4Pos[0].y - sizeY };
		SG.bg4[1] == BG_MAX4 - 1 ? SG.bg4[1] = 1 : SG.bg4[1] += 1;
	}

	////5////
	if (SG.bg5Pos[0].y - sizeY > SCREEN_HEIGHT)
	{
		SG.bg5Pos[0] = { SCREEN_WIDTH / 2, SG.bg5Pos[1].y - sizeY };
		SG.bg5[0] == BG_MAX5 - 1 ? SG.bg5[0] = 0 : SG.bg5[0] += 1;
	}

	if (SG.bg5Pos[1].y - sizeY > SCREEN_HEIGHT)
	{
		SG.bg5Pos[1] = { SCREEN_WIDTH / 2, SG.bg5Pos[0].y - sizeY };
		SG.bg5[1] == BG_MAX4 - 1 ? SG.bg5[1] = 1 : SG.bg5[1] += 1;
	}
}

void UpdateSTUShake(float _dt)
{
	if (SG.shakeTimer > 0)
	{
		SG.shakeTimer -= _dt;

		sf::Vector2f newCamCenter;
		newCamCenter.x = SCREEN_WIDTH / 2 + (-SG.shakePower.x + (float)(rand() % (int)(SG.shakePower.x*2)));
		newCamCenter.y = SCREEN_HEIGHT / 2 + (-SG.shakePower.y + (float)(rand() % (int)(SG.shakePower.y * 2)));
		SG.viewGame.setCenter(newCamCenter);
	}
	else
	{
		SG.viewGame.setCenter({ SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 });
	}
}

void UpdateSTU(float _dt, GameState& _gameState, Player& _player, bool& _transition, float& _noirAlpha, ControlsData*& m_controls)
{
	UpdateSTUShake(_dt);

	switch (STUgameState)
	{
	case STU_TUTO:
		if (STUGameMusic.getStatus() != sf::Music::Playing)
		{
			STUGameMusic.play();
		}
		GetPlayer().Update(_dt, m_controls);
		UpadateBg(_dt);
		UpdateSTUTuto(_dt, m_controls);
		SG.Hud.Update(_dt);
		break;
	case STU_GAME:
		UpadateBg(_dt);
		SG.Em.UpdateEntities(_dt, m_controls);
		SG.Hud.Update(_dt);
		break;
	case STU_MINI_BOSS:
		UpadateBg(_dt);
		SG.Em.UpdateEntities(_dt, m_controls);
		SG.MiniBoss.Update(_dt, _gameState, _player, _transition, _noirAlpha);
		SG.Hud.Update(_dt);
		break;
	case STU_BOSS:
		UpadateBg(_dt);
		SG.Em.UpdateEntities(_dt, m_controls);
		SG.Hud.Update(_dt);
		break;
	case STU_GAME_OVER:
		UpdateSTUGameOver(_dt, _gameState, _transition, _noirAlpha);
		break;
	case STU_VICTORY:
		break;
	default:
		break;
	}
}

void DisplayBg(sf::RenderWindow& _window)
{
	_window.setView(SG.viewGame);

	for (int k = 0; k < 2; k++)
	{
		//stars2//
		BlitSprite(SG.backGround3[SG.bg3[k]], SG.bg3Pos[k], _window, SG.scaleBg, 0, sf::Color(255, 255, 255, 255));
	}
	for (int k = 0; k < 2; k++)
	{
		//stars1//
		BlitSprite(SG.backGround2[SG.bg2[k]], SG.bg2Pos[k], _window, SG.scaleBg, 0, sf::Color(255, 255, 255, 255));
	}
	for (int k = 0; k < 2; k++)
	{
		//planets2//
		BlitSprite(SG.backGround5[SG.bg5[k]], SG.bg5Pos[k], _window, SG.scaleBg, 0, sf::Color(255, 255, 255, 255));
	}
	for (int k = 0; k < 2; k++)
	{
		//planets1//
		BlitSprite(SG.backGround4[SG.bg4[k]], SG.bg4Pos[k], _window, SG.scaleBg, 0, sf::Color(255, 255, 255, 255));
	}
	for (int k = 0; k < 2; k++)
	{
		//rainbow//
		BlitSprite(SG.backGround1[SG.bg1[k]], SG.bg1Pos[k], _window, SG.scaleBg, 0, sf::Color(255, 255, 255, 120));
	}
}

void DisplaySTU(sf::RenderWindow& _window)
{
	switch (STUgameState)
	{
	case STU_TUTO:
		DisplayBg(_window);
		GetPlayer().Display(_window);
		_window.setView(SG.viewHud);
		SG.Hud.Display(_window);
		DisplaySTUTuto(_window);
		break;
	case STU_GAME:
		DisplayBg(_window);
		SG.Em.DrawEntities(_window);
		_window.setView(SG.viewHud);
		SG.Hud.Display(_window);
		break;
	case STU_MINI_BOSS:
		DisplayBg(_window);
		SG.Em.DrawEntities(_window);
		SG.MiniBoss.Display(_window);
		_window.setView(SG.viewHud);
		SG.Hud.Display(_window);
		break;
	case STU_BOSS:
		DisplayBg(_window);
		SG.Em.DrawEntities(_window);
		_window.setView(SG.viewHud);
		SG.Hud.Display(_window);
		break;
	case STU_GAME_OVER:
		DisplayBg(_window);
		SG.Em.DrawEntities(_window);
		SG.MiniBoss.Display(_window);
		_window.setView(SG.viewHud);
		SG.Hud.Display(_window);
		DisplaySTUGameOver(_window);
		break;
	case STU_VICTORY:
		break;
	default:
		break;
	}
}

STUGameState& GetSTUGameState(void)
{
	return STUgameState;
}

STUMiniBoss& GetSTUMIniBoss(void)
{
	return SG.MiniBoss;
}

STUgameData& GetSTUGameData(void)
{
	return SG;
}

STUHud& GetSTUHud(void)
{
	return SG.Hud;
}


sf::View& GetGameView(void)
{
	return SG.viewGame;
}

sf::View& GetHudView(void)
{
	return SG.viewHud;
}

void ShakeSTU(sf::Vector2f _shake, float _time)
{
	SG.shakePower = _shake;
	SG.shakeTimer = _time;
}