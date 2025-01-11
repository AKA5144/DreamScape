#include "BossFinal.h"


///////////////////////////////////////////// Load Part /////////////////////////////////////////////



//////////////////////////////////////////// Update Part ////////////////////////////////////////////

void UpdatePlayerDeath(GameState& _gameState, Player& _player, bool& _transition, float _noirAlpha, SoulsLevel*& m_soulsLevel)
{
	if (GetTotalPlayerHp() <= 0 || (TheBoss.Get_Hp() <= 0 && TheBoss.Get_isAnimationDeathDone()))
	{
		_transition = true;

		if (_noirAlpha >= 254)
		{
			
			if (GetTotalPlayerHp() <= 0)
			{
				_gameState = LOBBY;
			}
			else if (TheBoss.Get_Hp() <= 0)
			{
				_gameState = VICTORY;
			}
			TheBoss.Reset();
			_player.Set_Pos({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 1.3333333 });
			GetPlayer().SetHp(5);
			GetPlayer().turretVector.clear();

			Turret turret;

			turret.SetType(SIMPLE_LINE);
			turret.SetCoolDown(0.2);

			GetPlayer().turretVector.push_back(turret);

			for (int k = 0; k < GetPlayer().turretVector.size(); k++)
			{
				float angle = k * (360 / GetPlayer().turretVector.size());
				angle *= 3.14 / 180;

				GetPlayer().turretVector[k].SetSpeedAngle(0.00f);

				GetPlayer().turretVector[k].SetVectorFromPlayer({ (float)(GetPlayer().turretDist * cos(angle)), (float)(GetPlayer().turretDist * sin(angle)) });

				GetPlayer().turretVector[k].SetPos(GetPlayer().turretVector[k].GetPos() + GetPlayer().turretVector[k].GetVectorFromPlayer());
			}
			Get_PlatformerHp() = 5;

			TheBoss.Set_Pos({ (float)SCREEN_WIDTH / 2, (float)100 + TheBoss.Get_Sprite().getTexture()->getSize().y / 2 });
			GetMineVector().clear();
			GetBulletVector().clear();
			GetPlayer().Set_Pos({ SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50 });
			PlayLobbyTheme();
			StopBossTheme();
			Get_Familiar().Set_Pos({ SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50 });
			playerView.setCenter({ SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50 });
			_transition = false;
			GetTotalPlayerHp() = 100;
			Get_SlidingVector().clear();
			ResetWorld();

			switch (TheBoss.Get_State())
			{
			case BOSSPARCOUR:TheBoss.Set_Pos({ 1280 , 200 });
				break;
			case BOSSSOULS:TheBoss.Set_Pos({ 350 , 100 });
				break;
			case BOSSSTU://TheBoss.Set_Pos({});
				break;
			}
			
			delete m_soulsLevel;
			
		}
	}
}

void UpdateAllPlayerHp(SoulsLevel*& m_soulsLevel, Boss& _theBoss)
{
	if (_theBoss.Get_IsInvinciblePlayer())
	{
		GetPlayer().SetHp(5);
	}

	if (GetPlayer().GetHp() * 20 > GetTotalPlayerHp())
	{
		GetPlayer().SetHp(GetTotalPlayerHp() / 20);
	}
	else//tir dans stu
	{
		GetTotalPlayerHp() = GetPlayer().GetHp() * 20;
	}

	if (m_soulsLevel->Get_Player().GetHP() > GetTotalPlayerHp())
	{
		float diff = m_soulsLevel->Get_Player().GetHP() - GetTotalPlayerHp();
		m_soulsLevel->Get_Player().DecreaseHP(diff);
	}

	//neyl

	if (Get_PlatformerHp() * 20 > GetTotalPlayerHp())
	{
		Get_PlatformerHp() = GetTotalPlayerHp() / 20;
	}
	else//tir dans stu
	{
		GetTotalPlayerHp() = Get_PlatformerHp() * 20;
	}

}

///////////////////////////////////////////// Draw Part /////////////////////////////////////////////



////////////////////////////////////////// FONCTION SACREE ////////////////////////////////////////// 

void LoadBoss()
{
	TheBoss.Load();
	LoadParcoursBoss();
	LoadBossSound();

	switch (TheBoss.Get_State())
	{
	case BOSSSOULS:TheBoss.Set_Pos({ 350 , 100 });
		break;
	case BOSSSTU:
		break;	
	case BOSSPARCOUR:
		break;
	}
}

void UpdateBoss(float _dt, GameState& _gameState, Player& _player, bool& _transition, float _noirAlpha, Config _config, SoulsLevel*& _soulsLevel, PlatformerData& _platformerData, sf::RenderWindow& _window, ControlsData*& m_controls, SoulsLevel* m_soulsLevel)
{

	switch (TheBoss.Get_State())
	{
	case BOSSSOULS:
		UpdateSoulsBoss(_dt, _config, _soulsLevel, _gameState, _transition, _noirAlpha, _player, TheBoss);
		break;
	case BOSSPARCOUR:
		UpdateParcoursBoss(_dt, _platformerData, _window, _gameState, _transition, _noirAlpha, m_controls, TheBoss, _player);
		break;
	case BOSSSTU:
		UpdateSTUBoss(_dt, _gameState, _player, TheBoss, _transition, _noirAlpha, m_controls);
		break;
	}

	UpdateInvincibility(TheBoss);
	TheBoss.Update(_dt, _transition, _noirAlpha, _gameState, _soulsLevel, _platformerData);
	UpdatePlayerDeath(_gameState, _player, _transition, _noirAlpha, m_soulsLevel);
	UpdateAllPlayerHp(_soulsLevel, TheBoss);
}

void DisplayBoss(sf::RenderWindow& _window, SoulsLevel*& _soulsLevel, PlatformerData& _platformerData)
{
	switch (TheBoss.Get_State())
	{
	case BOSSSOULS:
		DisplaySoulsBoss(_window, _soulsLevel, TheBoss);
		break;
	case BOSSPARCOUR:
		DisplayParcoursBoss(_window, _platformerData, TheBoss);
		break;
	case BOSSSTU:
		DisplaySTUBoss(_window, TheBoss);
		break;
	}

	if (TheBoss.Get_State() != BOSSSOULS)
	{
		TheBoss.Display(_window);
	}
	DisplayHeal(_window, TheBoss);
	if (TheBoss.Get_State() == BOSSPARCOUR)
	{
		_window.draw(Get_HpBar());
	}
}

Boss& GetFinalBoss()
{
	return TheBoss;
}