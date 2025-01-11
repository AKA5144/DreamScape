#include "BossStairs.h"

Stairs BossStairs;


bool bossStairsAnimation = false;

///////////////////////////////////////////// Load Part /////////////////////////////////////////////

void LoadBossStairs()
{
	BossStairs.Set_Pos({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });
	BossStairs.Set_Sprite(LoadSprite("Assets/Lobby/Divers/StairsBoss.png", true));
}

//////////////////////////////////////////// Update Part ////////////////////////////////////////////

void Stairs::UpdateStairsCollision(Player& _player)
{
	//Collision droite de l'escalier
	if (_player.Get_Pos().y > pos.y - sprite.getTexture()->getSize().y * 3 / 2 && _player.Get_Pos().y < pos.y + sprite.getTexture()->getSize().y* 3 / 2 && _player.Get_Pos().x - _player.Get_Sprite().getTexture()->getSize().x / 2 < pos.x + sprite.getTexture()->getSize().x* 3 / 2 && _player.Get_Pos().x - _player.Get_Sprite().getTexture()->getSize().x / 2 > pos.x + sprite.getTexture()->getSize().x * 3/ 2 - 10)
	{
		_player.Set_X(_player.Get_Pos().x + 1);
	}

	//Collision droite de l'escalier
	if (_player.Get_Pos().y > pos.y - sprite.getTexture()->getSize().y * 3 / 2 && _player.Get_Pos().y < pos.y + sprite.getTexture()->getSize().y* 3 / 2 && _player.Get_Pos().x + _player.Get_Sprite().getTexture()->getSize().x / 2 < pos.x + sprite.getTexture()->getSize().x* 3 / 2 && _player.Get_Pos().x + _player.Get_Sprite().getTexture()->getSize().x / 2 > pos.x + sprite.getTexture()->getSize().x* 3 / 2 - 5)
	{
		_player.Set_X(_player.Get_Pos().x - 1);
	}

	//Collision gauche de l'escalier
	if (_player.Get_Pos().y > pos.y - sprite.getTexture()->getSize().y* 3 / 2 && _player.Get_Pos().y < pos.y + sprite.getTexture()->getSize().y* 3 / 2 && _player.Get_Pos().x + _player.Get_Sprite().getTexture()->getSize().x / 2 > pos.x - sprite.getTexture()->getSize().x* 3 / 2 && _player.Get_Pos().x + _player.Get_Sprite().getTexture()->getSize().x / 2 < pos.x - sprite.getTexture()->getSize().x * 3/ 2 + 10)
	{
		_player.Set_X(_player.Get_Pos().x - 1);
	}

	//Collision gauche de l'escalier
	if (_player.Get_Pos().y > pos.y - sprite.getTexture()->getSize().y* 3 / 2 && _player.Get_Pos().y < pos.y + sprite.getTexture()->getSize().y* 3 / 2 && _player.Get_Pos().x - _player.Get_Sprite().getTexture()->getSize().x / 2 > pos.x - sprite.getTexture()->getSize().x* 3 / 2 && _player.Get_Pos().x - _player.Get_Sprite().getTexture()->getSize().x / 2 < pos.x - sprite.getTexture()->getSize().x * 3/ 2 + 5)
	{
		_player.Set_X(_player.Get_Pos().x + 1);
	}
}

void Stairs::DetectAnimation(Player& _player)
{
	if (_player.Get_Pos().x > this->Get_Pos().x - this->Get_Sprite().getTexture()->getSize().x * 3 / 2 && _player.Get_Pos().x < this->Get_Pos().x + this->Get_Sprite().getTexture()->getSize().x * 3 / 2 && _player.Get_Pos().y > this->Get_Pos().y - this->Get_Sprite().getTexture()->getSize().y * 3 / 2 && _player.Get_Pos().y < this->Get_Pos().y + this->Get_Sprite().getTexture()->getSize().y * 3 / 2 - 10)
	{
		bossStairsAnimation = true;
	}
}

void UpdateAnimationTp(Player& _player, float _dt, bool& _transition, GameState& _gameState, float& _noirAlpha, SoulsLevel*& m_soulsLevel, PlatformerData& _platformerData)
{
	if (bossStairsAnimation)
	{
		sf::Vector2f director = BossStairs.Get_Pos() - sf::Vector2f{0 , (float)BossStairs.Get_Sprite().getTexture()->getSize().y * 3 / 2 } - _player.Get_Pos();
		float norme = sqrtf(director.x * director.x + director.y * director.y);
		director.x /= norme;
		director.y /= norme;
		if (norme > 20)
		{
			_transition = true;
			_player.Set_X(_player.Get_Pos().x + director.x * (1000 * _dt));
		}
		if (BossStairs.Get_Pos().x - _player.Get_Pos().x < 2)
		{
			PlayTeleportationSound();
			StopLobbyTheme();
			_player.Set_Y(_player.Get_Pos().y + director.y * (50 * _dt));
		}


		if (_noirAlpha >= 254)
		{
			m_soulsLevel = new SoulsLevel("SoulsBoss");
			_player.Set_Pos({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 1.333333333 });
			_platformerData.players.SetPosition({ 1280 , 288 });
			GetSTUGameState() = STU_BOSS;
			GetWaveManager().waveText.setString("");
			GetWaveManager().GetWaveVector().clear();
			Get_PlatformerHp() = 5;
			_transition = false;
			PlayBossTheme();
			LoadSTUBoss();
			bossStairsAnimation = false;
			_gameState = BOSS;
			LoadSoulsBoss();
			_platformerData.finalBoss = true;
		}
	}
}

///////////////////////////////////////////// Draw Part /////////////////////////////////////////////

void DisplayBossStairs(sf::RenderWindow& _window)
{
	BlitSprite(BossStairs.Get_Sprite(), BossStairs.Get_Pos(), _window, { 3 , 3});
}

////////////////////////////////////////// FONCTION SACREE ////////////////////////////////////////// 

void LoadStairs()
{
	LoadBossStairs();
}

void UpdateStairs(float _dt, Player& _player, bool& _transition, GameState& _gameState, float& _noirAlpha, SoulsLevel*& m_soulsLevel, PlatformerData& _platformerData)
{
	BossStairs.UpdateStairsCollision(_player);
	UpdateAnimationTp(_player, _dt, _transition, _gameState, _noirAlpha, m_soulsLevel, _platformerData);
	BossStairs.DetectAnimation(_player);
}

void DisplayStairs(sf::RenderWindow& _window)
{
	DisplayBossStairs(_window);
}