#include "Altar.h"
#define SHAKE 4

Altar altar;

sf::Text PressEText;

Totem SoulsTotem;
Totem ParcourTotem;
Totem ShootupTotem;

bool AnimationAltar = false;


///////////////////////////////////////////// Load Part /////////////////////////////////////////////

void Totem::Display(sf::RenderWindow& _window)
{
	if (IsDisplay)
	{
		BlitSprite(sprite, pos, _window, { 3 , 3 });
	}
}

void LoadSprite(sf::Sprite& _noir)
{
	altar.Set_Sprite(LoadSprite("Assets/Lobby/Altar/Altar.png", true));
	altar.Set_Pos({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });
	_noir = LoadSprite("Assets/Lobby/Divers/Transition.png", false);
}

void LoadPressE(std::string _font, Player& _player)
{
	PressEText = LoadText(_font, "Press E", 40, { _player.Get_Pos().x , _player.Get_Pos().y + 300 }, sf::Color::White, true);
}

void LoadTotem()
{
	ParcourTotem.Set_Sprite(LoadSprite("Assets/Lobby/Altar/Autel_Bleu.png", true));
	ShootupTotem.Set_Sprite(LoadSprite("Assets/Lobby/Altar/Autel_Violet.png", true));
	SoulsTotem.Set_Sprite(LoadSprite("Assets/Lobby/Altar/Autel_Vert.png", true));

	ParcourTotem.Set_Pos({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });
	ShootupTotem.Set_Pos({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });
	SoulsTotem.Set_Pos({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });
}

void SaveGame(Player& _player)
{
	std::fstream save("save.txt", std::ios::out);

	save << _player.Get_IsBlueTotem();
	save << "\n";
	save << _player.Get_IsGreenTotem();
	save << "\n";
	save << _player.Get_IsPurpleTotem();
	save << "\n";
	save << ParcourTotem.Get_IsDisplay();
	save << "\n";
	save << SoulsTotem.Get_IsDisplay();
	save << "\n";
	save << ShootupTotem.Get_IsDisplay();
	save << "\n";
	save << Get_Familiar().Get_State();
}

void LoadGame(Player& _player)
{
	std::fstream save("save.txt", std::ios::in);
	std::string temp;

	save >> temp;
	_player.Set_IsBlueTotem(stoi(temp));
	save >> temp;
	_player.Set_IsGreenTotem(stoi(temp));
	save >> temp;
	_player.Set_IsPurpleTotem(stoi(temp));
	save >> temp;
	ParcourTotem.Set_IsDisplay(stoi(temp));
	save >> temp;
	SoulsTotem.Set_IsDisplay(stoi(temp));
	save >> temp;
	ShootupTotem.Set_IsDisplay(stoi(temp));
	save >> temp;
	Get_Familiar().Set_State((FamiliarState)stoi(temp));
}

//////////////////////////////////////////// Update Part ////////////////////////////////////////////

void Altar::UpdateCollisionAltar(Player& _player)
{
	sf::Vector2f nextPos = _player.Get_Pos() + _player.Get_Velocity();
	float tailleX = sprite.getTexture()->getSize().x * 3 / 2;
	float tailleY = sprite.getTexture()->getSize().y * 3 / 2;

	float taillePlayerX = _player.Get_Sprite().getTexture()->getSize().x / 2;
	float taillePlayerY = _player.Get_Sprite().getTexture()->getSize().y / 2;

	sf::Vector2f collideXRight = _player.Get_Pos() + sf::Vector2f{ _player.Get_Velocity().x , 0 };
	sf::Vector2f collideXLeft = _player.Get_Pos() - sf::Vector2f{ _player.Get_Velocity().x, 0 };
	sf::Vector2f collideXUp = _player.Get_Pos() - sf::Vector2f{ 0, _player.Get_Velocity().y };
	sf::Vector2f collideXDown = _player.Get_Pos() + sf::Vector2f{ 0, _player.Get_Velocity().y };

	if (collideXRight.x + taillePlayerX > pos.x - tailleX && collideXRight.x - taillePlayerX < pos.x + tailleX && collideXRight.y + taillePlayerY > pos.y - tailleY - 5 && collideXRight.y - taillePlayerY < pos.y + tailleY - 7)
	{
		_player.Set_X(_player.Get_Pos().x - _player.Get_Velocity().x);
	}
	if (collideXLeft.x + taillePlayerX > pos.x - tailleX && collideXLeft.x - taillePlayerX < pos.x + tailleX && collideXLeft.y + taillePlayerY > pos.y - tailleY - 5 && collideXLeft.y - taillePlayerY < pos.y + tailleY - 7)
	{
		_player.Set_X(_player.Get_Pos().x + _player.Get_Velocity().x);
	}
	if (collideXUp.x + taillePlayerX > pos.x - tailleX && collideXUp.x - taillePlayerX < pos.x + tailleX && collideXUp.y > pos.y - tailleY && collideXUp.y < pos.y + tailleY)
	{
		_player.Set_Y(_player.Get_Pos().y + _player.Get_Velocity().y);
	}
	if (collideXDown.x + taillePlayerX > pos.x - tailleX && collideXDown.x - taillePlayerX < pos.x + tailleX && collideXDown.y + taillePlayerY * 2.2 > pos.y - tailleY && collideXDown.y < pos.y + tailleY)
	{
		_player.Set_Y(_player.Get_Pos().y - _player.Get_Velocity().y);
	}
}

void Altar::UpdatePressEText(float _dt, Player& _player)
{
	static float Transparence = 0;
	static float a = 3.1415;

	if (_player.Get_Direction() == UP && _player.Get_Pos().x < altar.Get_Pos().x + altar.Get_Sprite().getTexture()->getSize().x * 3 / 5 && _player.Get_Pos().x >altar.Get_Pos().x - altar.Get_Sprite().getTexture()->getSize().x * 3 / 5 && _player.Get_Pos().y > altar.Get_Sprite().getTexture()->getSize().y * 3 / 2 + altar.Get_Pos().y && _player.Get_Pos().y < (altar.Get_Sprite().getTexture()->getSize().y * 3 / 2 + altar.Get_Pos().y) + 40)
	{
		a += 2 * _dt;
		Transparence = 126 * (cosf(a) + 1);
		PressEText.setFillColor(sf::Color(255, 255, 255, Transparence));
	}
	else
	{
		Transparence = 3.1415;
	}

}

void UpdateTotemAltar(Player& _player, bool& animation)
{
	if (_player.Get_Direction() == UP && _player.Get_Pos().x < altar.Get_Pos().x + altar.Get_Sprite().getTexture()->getSize().x * 3 / 5 && _player.Get_Pos().x >altar.Get_Pos().x - altar.Get_Sprite().getTexture()->getSize().x * 3 / 5 && _player.Get_Pos().y > altar.Get_Sprite().getTexture()->getSize().y * 3 / 2 + altar.Get_Pos().y && _player.Get_Pos().y < (altar.Get_Sprite().getTexture()->getSize().y * 3 / 2 + altar.Get_Pos().y) + 40)
	{
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Joystick::isButtonPressed(0, (int)ControllerButton::A)) && (_player.Get_IsBlueTotem() || _player.Get_IsGreenTotem() || _player.Get_IsPurpleTotem()))
		{
			AnimationAltar = true;
		}
	}
}

void UpdateTotemAnimation(Player& _player, sf::Vector2f& _camCoord, bool& animation, float _dt)
{
	static bool IsDone = false;

	if (AnimationAltar && !IsDone)
	{
		animation = true;
		static sf::Clock timer;
		sf::Vector2f director = altar.Get_Pos() - _camCoord;
		float norme = sqrtf(director.x * director.x + director.y * director.y);
		director.x = director.x / norme * 1000 * _dt;
		director.y = director.y / norme * 1000 * _dt;


		if (norme > 2 && !ParcourTotem.Get_IsDisplay() && !SoulsTotem.Get_IsDisplay() && !ShootupTotem.Get_IsDisplay())
		{
			_camCoord.x += director.x / 5;
			_camCoord.y += director.y / 5;
		}
		else
		{
			if (_player.Get_IsBlueTotem())
			{
				if (!ParcourTotem.Get_IsDisplay())
				{
					PlayTotemPlace();
				}
				ParcourTotem.Set_IsDisplay(true);
			}

			if (_player.Get_IsGreenTotem() && _player.Get_IsBlueTotem())
			{
				if (timer.getElapsedTime().asSeconds() > 1)
				{
					if (!SoulsTotem.Get_IsDisplay())
					{
						PlayTotemPlace();
					}
					SoulsTotem.Set_IsDisplay(true);
				}
			}
			else if (_player.Get_IsGreenTotem() && !_player.Get_IsBlueTotem())
			{
				if (!SoulsTotem.Get_IsDisplay())
				{
					PlayTotemPlace();
				}
				SoulsTotem.Set_IsDisplay(true);
			}

			if (_player.Get_IsPurpleTotem() && _player.Get_IsBlueTotem() && _player.Get_IsGreenTotem())
			{
				if (timer.getElapsedTime().asSeconds() > 2)
				{
					if (!ShootupTotem.Get_IsDisplay())
					{
						PlayTotemPlace();
					}
					ShootupTotem.Set_IsDisplay(true);
				}
			}
			else if (_player.Get_IsPurpleTotem() && (_player.Get_IsBlueTotem() || _player.Get_IsGreenTotem()))
			{
				if (timer.getElapsedTime().asSeconds() > 1)
				{
					if (!ShootupTotem.Get_IsDisplay())
					{
						PlayTotemPlace();
					}
					ShootupTotem.Set_IsDisplay(true);
				}
			}
			else if (_player.Get_IsPurpleTotem())
			{
				if (!ShootupTotem.Get_IsDisplay())
				{
					PlayTotemPlace();
				}
				ShootupTotem.Set_IsDisplay(true);
			}

			if (ShootupTotem.Get_IsDisplay() && ParcourTotem.Get_IsDisplay() && SoulsTotem.Get_IsDisplay())
			{
				PlayAltarSound();
				IsDone = true;
			}

			if (timer.getElapsedTime().asSeconds() > 3)
			{
				AnimationAltar = false;
				animation = false;
				SaveGame(_player);
			}
		}
	}
}

void AltarAnimation(bool& animation, float _dt, sf::Vector2f& _camCoord)
{
	static bool SoundPlay = false;
	if (ParcourTotem.Get_IsDisplay() && SoulsTotem.Get_IsDisplay() && ShootupTotem.Get_IsDisplay())
	{
		animation = true;
		if (altar.Get_Pos().y > SCREEN_HEIGHT / 2 - altar.Get_Sprite().getTexture()->getSize().y * 3 + 2)
		{
			altar.Set_Y(altar.Get_Pos().y - 50 * _dt);
			ParcourTotem.Set_Y(altar.Get_Pos().y - 50 * _dt);
			SoulsTotem.Set_Y(altar.Get_Pos().y - 50 * _dt);
			ShootupTotem.Set_Y(altar.Get_Pos().y - 50 * _dt);

			_camCoord.x = altar.Get_Pos().x + (-SHAKE) + (((float)(rand() % RAND_MAX) / RAND_MAX) * (SHAKE * 2));
			_camCoord.y = altar.Get_Pos().y + (-SHAKE) + (((float)(rand() % RAND_MAX) / RAND_MAX) * (SHAKE * 2));
		}
		else
		{
			if (!SoundPlay)
			{
				PlayAltarAnimationEnd();
				SoundPlay = true;
			}
			animation = false;
		}
	}
}

void UpdateTransition(float _dt, float& _noirAlpha, bool& _transition)
{
	if (!_transition)
	{
		if (_noirAlpha > 0)
		{
			_noirAlpha -= _dt * 125;
		}
	}

	if (_transition && _noirAlpha < 255)
	{
		_noirAlpha += _dt * 150;
	}
	if (_noirAlpha >= 255)
	{
		_transition = false;
	}

	if (_noirAlpha <= 0)
	{
		_noirAlpha = 0;
	}
}

///////////////////////////////////////////// Draw Part /////////////////////////////////////////////

void DisplaySprite(sf::RenderWindow& _window)
{
	BlitSprite(altar.Get_Sprite(), altar.Get_Pos(), _window, { 3 , 3 });
}

void DisplayPressE(sf::RenderWindow& _window, Player& _player)
{
	if (_player.Get_Direction() == UP && _player.Get_Pos().x < altar.Get_Pos().x + altar.Get_Sprite().getTexture()->getSize().x * 3 / 5 && _player.Get_Pos().x >altar.Get_Pos().x - altar.Get_Sprite().getTexture()->getSize().x * 3 / 5 && _player.Get_Pos().y > altar.Get_Pos().y && _player.Get_Pos().y + _player.Get_Sprite().getTexture()->getSize().y / 2 < (altar.Get_Sprite().getTexture()->getSize().y * 3 / 2 + altar.Get_Pos().y) + 40)
	{
		if (ParcourTotem.Get_IsDisplay() && SoulsTotem.Get_IsDisplay() && ShootupTotem.Get_IsDisplay())
		{

		}
		else
		{
			PressEText.setPosition({ _player.Get_Pos().x , _player.Get_Pos().y + 50 });
			_window.draw(PressEText);
		}
	}
}

////////////////////////////////////////// FONCTION SACREE ////////////////////////////////////////// 

void LoadAltar(Player& _player, std::string _font, sf::Sprite& _noir)
{
	LoadSprite(_noir);
	LoadPressE(_font, _player);
	LoadTotem();
}

void UpdateAltar(float _dt, Player& _player, sf::Vector2f& _camCoord, bool& animation, float& _noirAlpha, bool& _transition)
{
	altar.UpdateCollisionAltar(_player);
	altar.UpdatePressEText(_dt, _player);
	UpdateTotemAltar(_player, animation);
	UpdateTotemAnimation(_player, _camCoord, animation, _dt);
	AltarAnimation(animation, _dt, _camCoord);

}

void DisplayAltar(sf::RenderWindow& _window, Player& _player)
{
	DisplaySprite(_window);
	DisplayPressE(_window, _player);
	ParcourTotem.Display(_window);
	ShootupTotem.Display(_window);
	SoulsTotem.Display(_window);
	_player.Display(_window);
}