#include "Lobby.h"
#define TAILLE_VIDE 0

sf::Sprite Background;
sf::Sprite PortalOrbe;
sf::Image ImageData;

Portal SoulsPortal;
Portal ShootupPortal;
Portal ParcourPortal;

float scale = 0;

void Portal::UpdateAnimation(float _dt)
{

	if (cooldown.getElapsedTime().asSeconds() >= 0.3)
	{
		cooldown.restart();
		sprite = spriteVector[compteur];
		compteur++;
		if (compteur >= spriteVector.size())
		{
			compteur = 0;
		}
	}

	effect.Rotate(_dt);

}

void Portal::Display(sf::RenderWindow& _window)
{
	effect.Display(_window);
	BlitSprite(sprite, pos, _window, { 3 , 3 });
}

void PortalEffect::Rotate(float _dt)
{
	rotation -= 50 * _dt;
}

void PortalEffect::Display(sf::RenderWindow& _window)
{
	BlitSprite(sprite, pos, _window, { 3 , 3 }, rotation);
}

///////////////////////////////////////////// Load Part /////////////////////////////////////////////
void LoadBackground()
{
	Background = LoadSprite("Assets/Lobby/Divers/Background.png", false);
	ImageData.loadFromFile("Assets/Lobby/Divers/Sign map.png");
}

void LoadPortal(std::string _font, Player& _player)
{
	//Load Portal Sprite Vector

	std::vector <sf::Sprite> STUSpriteVector;
	for (int i = 0; i < 6; i++)
	{
		sf::Sprite sprite;
		sprite = LoadSprite("Assets/Lobby/Portal/PurplePortal/" + std::to_string(i + 1) + ".png", false);
		STUSpriteVector.push_back(sprite);
	}
	ShootupPortal.Set_SpriteVector(STUSpriteVector);

	std::vector <sf::Sprite> ParcourSpriteVector;

	for (int i = 0; i < 6; i++)
	{
		sf::Sprite sprite;
		sprite = LoadSprite("Assets/Lobby/Portal/BluePortal/" + std::to_string(i + 1) + ".png", false);
		ParcourSpriteVector.push_back(sprite);
	}

	ParcourPortal.Set_SpriteVector(ParcourSpriteVector);
	std::vector <sf::Sprite> SoulsSpriteVector;

	for (int i = 0; i < 6; i++)
	{
		sf::Sprite sprite;
		sprite = LoadSprite("Assets/Lobby/Portal/GreenPortal/" + std::to_string(i + 1) + ".png", false);
		SoulsSpriteVector.push_back(sprite);
	}

	SoulsPortal.Set_SpriteVector(SoulsSpriteVector);

	ParcourPortal.Set_Color(sf::Color(205, 250, 205));
	SoulsPortal.Set_Color(sf::Color(205, 205, 250));
	ShootupPortal.Set_Color(sf::Color(250, 205, 205));

	ParcourPortal.effect.Set_Sprite(LoadSprite("Assets/Lobby/Portal/BluePortal/BlueEffect.png", true));
	SoulsPortal.effect.Set_Sprite(LoadSprite("Assets/Lobby/Portal/GreenPortal/GreenEffect.png", true));
	ShootupPortal.effect.Set_Sprite(LoadSprite("Assets/Lobby/Portal/PurplePortal/PurpleEffect.png", true));

	ParcourPortal.effect.Set_Pos({ 336, 815 });
	SoulsPortal.effect.Set_Pos({ 957, 129 });
	ShootupPortal.effect.Set_Pos({ 1595, 824 });

	PortalOrbe = LoadSprite("Assets/Lobby/Portal/Portals-porte.png", false);
}

void LoadCamera(Player& _player, sf::Vector2f& camCoord)
{
	//Coordonnée du joueur au milieu de l'écran
	camCoord = { SCREEN_WIDTH / 2, 694 + TAILLE_VIDE };
	playerView.setCenter(camCoord);
	playerView.setSize(SCREEN_WIDTH / 1.4, SCREEN_HEIGHT / 1.4);
}

//////////////////////////////////////////// Update Part ////////////////////////////////////////////

void UpdateView(Player& _player, sf::Vector2f& camCoord, bool& animation, float _dt)
{
	if (!animation)
	{
		sf::Vector2f director = _player.Get_Pos() - camCoord;
		float norme = sqrtf(director.x * director.x + director.y * director.y);

		if (norme < 10)
		{
			camCoord = _player.Get_Pos();
		}
		else
		{
			camCoord.x += director.x / norme * 500 * _dt;
			camCoord.y += director.y / norme * 500 * _dt;
		}

		if (camCoord.x <= 690 - TAILLE_VIDE)
		{
			camCoord.x = 690 - TAILLE_VIDE;
		}
		if (camCoord.x >= 1232 + TAILLE_VIDE)
		{
			camCoord.x = 1232 + TAILLE_VIDE;
		}
		if (camCoord.y <= 392 - TAILLE_VIDE)
		{
			camCoord.y = 392 - TAILLE_VIDE;
		}
		if (camCoord.y >= 694 + TAILLE_VIDE)
		{
			camCoord.y = 694 + TAILLE_VIDE;
		}
	}
	playerView.setCenter(camCoord);
}

void UpdatePlayerCollision(Player& _player)
{
	static int posX = 0;
	static int posY = 0;

	static float sizeX = _player.Get_Sprite().getTexture()->getSize().x * 3;
	static float sizeY = _player.Get_Sprite().getTexture()->getSize().y * 3;

	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY / 2; j += sizeY / 2 - 1)
		{
			if (_player.Get_Pos().y < SCREEN_HEIGHT - 5)
			{
				if (ImageData.getPixel((_player.Get_Pos().x - sizeX / 2) + i, _player.Get_Pos().y + j) == sf::Color(255, 0, 0))
				{
					_player.Set_X(_player.Get_Pos().x - 1);
				}
				else if (ImageData.getPixel((_player.Get_Pos().x - sizeX / 2) + i, _player.Get_Pos().y + j) == sf::Color(0, 255, 0))
				{
					_player.Set_Y(_player.Get_Pos().y - 1);

				}
				else if (ImageData.getPixel((_player.Get_Pos().x - sizeX / 2) + i, _player.Get_Pos().y + j) == sf::Color(0, 0, 255))
				{
					_player.Set_Y(_player.Get_Pos().y + 1);

				}
				else if (ImageData.getPixel((_player.Get_Pos().x - sizeX / 2) + i, _player.Get_Pos().y + j) == sf::Color(255, 255, 0))
				{
					_player.Set_X(_player.Get_Pos().x + 1);
				}

				//Portal Collision
				else if (ImageData.getPixel((_player.Get_Pos().x - sizeX / 2) + i, _player.Get_Pos().y + j) == sf::Color(101, 27, 255))
				{
					_player.Set_Y(_player.Get_Pos().y + 1);

				}
				else if (ImageData.getPixel((_player.Get_Pos().x - sizeX / 2) + i, _player.Get_Pos().y + j) == sf::Color(2, 255, 44))
				{
					_player.Set_Y(_player.Get_Pos().y + 1);

				}
				else if (ImageData.getPixel((_player.Get_Pos().x - sizeX / 2) + i, _player.Get_Pos().y + j) == sf::Color(255, 109, 48))
				{
					_player.Set_Y(_player.Get_Pos().y + 1);
				}
			}
		}
	}

	if (_player.Get_Pos().y > Background.getTexture()->getSize().y * 3 - _player.Get_Sprite().getTexture()->getSize().y / 2)
	{
		_player.Set_Y(Background.getTexture()->getSize().y * 3 - _player.Get_Sprite().getTexture()->getSize().y / 2);
	}
}

void UpdatePortalInfo(float _dt, Player& _player)
{
	//Portal info scale 
	if (_player.Get_Direction() == UP && (ImageData.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) == sf::Color(85, 36, 48) || ImageData.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) == sf::Color(53, 27, 88) || ImageData.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) == sf::Color(2, 145, 44)))
	{
		scale += 4 * _dt;
		if (scale >= 1)
		{
			scale = 1;
		}
	}
	//Reset scale si joueur partie
	if (_player.Get_Direction() != UP || ImageData.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) != sf::Color(85, 36, 48) && ImageData.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) != sf::Color(53, 27, 88) && ImageData.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) != sf::Color(2, 145, 44))
	{
		scale = 0;
	}
}

void UpdatePressE(float _dt, Player& _player)
{
	static float Transparence = 255;
	static float a = 3.141592;

	if (_player.Get_Direction() == UP && (ImageData.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) == sf::Color(85, 36, 48) || ImageData.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) == sf::Color(53, 27, 88) || ImageData.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) == sf::Color(2, 145, 44) || ImageData.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) == sf::Color(101, 27, 255) || ImageData.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) == sf::Color(2, 255, 44) || ImageData.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) == sf::Color(255, 109, 48)))
	{
		a += 2 * _dt;
		Transparence = 126 * (cosf(a) + 1);
	}
	else
	{
		Transparence = 0;
		a = 3.141592;
	}
}

void UpdatePortalTp(Player& _player, GameState& _gameState, float& _noirAlpha, bool& _transition, SoulsLevel*& m_soulsLevel)
{
	if (CanGoInLevel())//si le dialogue est fini
	{
		if (ImageData.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) == sf::Color(85, 36, 48))
		{
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Joystick::isButtonPressed(0, (int)ControllerButton::A)))
			{
				_transition = true;
				PlayTeleportationSound();
			}
			if (_noirAlpha >= 254)
			{
				m_soulsLevel = new SoulsLevel("SoulsLevel");
				StopLobbyTheme();
				_transition = false;
				_gameState = SOULS;
			}
		}
		else if (ImageData.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) == sf::Color(53, 27, 88))
		{
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Joystick::isButtonPressed(0, (int)ControllerButton::A)))
			{
				_transition = true;
				PlayTeleportationSound();
			}
			if (_noirAlpha >= 254)
			{
				StopLobbyTheme();
				_transition = false;
				_gameState = PARCOURS;
			}
		}
		else if (ImageData.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) == sf::Color(2, 145, 44))
		{
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Joystick::isButtonPressed(0, (int)ControllerButton::A)))
			{
				_transition = true;
				PlayTeleportationSound();
			}
			if (_noirAlpha >= 254)
			{
				StopLobbyTheme();
				_transition = false;
				_gameState = SHOOTUP;
			}
		}
	}
}

///////////////////////////////////////////// Draw Part /////////////////////////////////////////////

void DisplayBackground(sf::RenderWindow& _window)
{
	BlitSprite(Background, { 0,0 }, _window, { 3 , 3 });
}

void DisplayOther(sf::RenderWindow& _window)
{
	BlitSprite(PortalOrbe, { 0 , 0 }, _window, { 3 , 3 });
	ParcourPortal.Display(_window);
	SoulsPortal.Display(_window);
	ShootupPortal.Display(_window);
}

void DisplayBossInfo(sf::RenderWindow& _window, Player& _player)
{
	static bool dialogueLoaded = false;
	sf::Vector2f posDialogue = (sf::Vector2f)_window.mapPixelToCoords({ 40 * (SCREEN_WIDTH / 120) , SCREEN_HEIGHT - 250 });

	if (_player.Get_Pos().y < SCREEN_HEIGHT)
	{
		if (ImageData.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) == sf::Color(85, 36, 48) || ImageData.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) == sf::Color(255, 109, 48))
		{
			if (Get_Familiar().Get_IsCenter())
			{
				if (!dialogueLoaded)
				{
					_player.Set_Dir(UP);
					InitDialogue(posDialogue, ACTION_RPG_TEXT);
					dialogueLoaded = true;
				}
			}
		}
		else if (ImageData.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) == sf::Color(53, 27, 88) || ImageData.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) == sf::Color(101, 27, 255))
		{
			if (Get_Familiar().Get_IsCenter())
			{
				if (!dialogueLoaded)
				{
					_player.Set_Dir(UP);
					InitDialogue(posDialogue, PLATFORMER_TEXT);
					dialogueLoaded = true;
				}
			}

		}
		else if (ImageData.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) == sf::Color(2, 145, 44) || ImageData.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) == sf::Color(2, 255, 44))
		{

			if (Get_Familiar().Get_IsCenter())
			{
				if (!dialogueLoaded)
				{
					_player.Set_Dir(UP);
					InitDialogue(posDialogue, STU_TEXT);
					dialogueLoaded = true;
				}
			}
		}
		else
		{
			dialogueLoaded = false;
		}
	}
}

////////////////////////////////////////// FONCTION SACREE ////////////////////////////////////////// 

void LoadLobby(Player& _player, std::string _font, sf::Vector2f& camCoord)
{
	LoadBackground();
	LoadPortal(_font, _player);
	LoadCamera(_player, camCoord);
}

void UpdateLobby(float _dt, Player& _player, GameState& _gameState, sf::Vector2f& camCoord, bool& animation, float& _noirAlpha, bool& _transition, SoulsLevel*& m_soulsLevel)
{
	ParcourPortal.UpdateAnimation(_dt);
	SoulsPortal.UpdateAnimation(_dt);
	ShootupPortal.UpdateAnimation(_dt);

	PlayLobbyTheme();
	UpdatePlayerCollision(_player);
	UpdateView(_player, camCoord, animation, _dt);
	UpdatePortalInfo(_dt, _player);
	UpdatePressE(_dt, _player);
	UpdatePortalTp(_player, _gameState, _noirAlpha, _transition, m_soulsLevel);
}

void DisplayLobby(sf::RenderWindow& _window, Player& _player)
{
	_window.setView(playerView);
	DisplayBackground(_window);
	DisplayOther(_window);
}

sf::Image& Get_ImageData()
{
	return ImageData;
}