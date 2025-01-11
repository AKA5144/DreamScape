#include "Familiar.h"

Familiar familiar;

sf::Image signMap;

Familiar& Get_Familiar()
{
	return familiar;
}

void Familiar::Load()
{
	currentSprite = LoadSprite("Assets/Lobby/Familiar/Familiar1.png", true);
	pos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100 };
	state = STATIC;
	signMap.loadFromFile("Assets/Lobby/Divers/Sign map.png");
}

void Familiar::Fly(float _dt, Player& _player)
{
	sf::Vector2f finalPos = { (float)(_player.Get_Pos().x + _player.Get_Sprite().getTexture()->getSize().x * 3) , (float)(_player.Get_Pos().y - _player.Get_Sprite().getTexture()->getSize().y * 3) };
	sf::Vector2f director = finalPos - pos;
	float norme = director.x * director.x + director.y * director.y;

	if (norme >= 500)
	{
		pos += {director.x * 2 * _dt, director.y * 2 * _dt};
	}
}

void Familiar::Info(float _dt, Player& _player)
{
	if (signMap.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) == sf::Color(85, 36, 48))
	{
		sf::Vector2f finalPlace = { 1080 , 100 };
		sf::Vector2f director = finalPlace - pos;
		float norme = sqrtf(director.x * director.x + director.y * director.y);
		
		if (norme >= 10 && !IsCenter)
		{
			pos += {director.x * 5 * _dt, director.y * 5 * _dt };
		}
		else
		{
			IsCenter = true;
		}

	}
	else if (signMap.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) == sf::Color(53, 27, 88))
	{
		sf::Vector2f finalPlace = { 200 , 790 };
		sf::Vector2f director = finalPlace - pos;
		float norme = sqrtf(director.x * director.x + director.y * director.y);

		if (norme >= 10 && !IsCenter)
		{
			pos += {director.x * 5 * _dt, director.y * 5 * _dt };	
		}
		else
		{
			IsCenter = true;
		}
	}
	else if (signMap.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) == sf::Color(2, 145, 44))
	{
		sf::Vector2f finalPlace = { 1700 , 790 };
		sf::Vector2f director = finalPlace - pos;
		float norme = sqrtf(director.x * director.x + director.y * director.y);

		if (norme >= 10 && !IsCenter)
		{
			pos += {director.x * 5 * _dt, director.y * 5 * _dt };
		}
		else
		{
			IsCenter = true;
		}
	}
	else
	{
		IsCenter = false;
		state = FLY;
	}
}

void Familiar::UpdatePortalDistance(float _dt, Player& _player)
{
	if (state == FLY)
	{
		if (signMap.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) == sf::Color(85, 36, 48)) 
		{
			state = INFO;
		}
		else if (signMap.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) == sf::Color(53, 27, 88))
		{
			state = INFO;
		}
		else if (signMap.getPixel(_player.Get_Pos().x, _player.Get_Pos().y) == sf::Color(2, 145, 44))
		{
			state = INFO;
		}
	}
}

void Familiar::UpdateState(Player& _player, float _dt)
{
	sf::Vector2f distance = _player.Get_Pos() - pos;
	float norme = sqrtf(distance.x * distance.x + distance.y * distance.y);

	sf::Vector2f finalPlace = { _player.Get_Pos().x + _player.Get_Sprite().getTexture()->getSize().x , _player.Get_Pos().y - _player.Get_Sprite().getTexture()->getSize().y };

	sf::Vector2f director = finalPlace - pos;
	float normeDirector = sqrtf(director.x * director.x + director.y * director.y);

	director.x /= normeDirector;
	director.y /= normeDirector;


	if (norme < currentSprite.getTexture()->getSize().y + _player.Get_Sprite().getTexture()->getSize().y / 2 && state == STATIC)
	{
		followPlayer = true;
		canMove = true;
	}

	if (canMove)
	{
		if (normeDirector <= 1)
		{
			canMove = false;
			state = FLY;
		}
		pos += {director.x * 200 * _dt, director.y * 200 * _dt };
	}

	UpdatePortalDistance(_dt, _player);
}

void Familiar::Update(float _dt, Player& _player)
{
	UpdateState(_player, _dt);

	particuleManager.AddParticle((sf::Vector2i)pos, SMOG, 1, sf::Color(0,178,255));
	particuleManager.UpdateParticule(_dt);

	static float a = 11;
	a += 2 * _dt;
	float posY = cos(a) * 50 * _dt;
	pos.y += posY;

	switch (state)
	{
	case STATIC:
		break;
	case FLY:
		Fly(_dt, _player);
		break;
	case INFO:
		Info(_dt, _player);
		break;
	}
}

void Familiar::Display(sf::RenderWindow& _window)
{
	particuleManager.DrawParticule(_window);
	BlitSprite(currentSprite, pos, _window, { 3 , 3 });
}

///////////////////////////////////////////// Load Part /////////////////////////////////////////////



//////////////////////////////////////////// Update Part ////////////////////////////////////////////



///////////////////////////////////////////// Draw Part /////////////////////////////////////////////



////////////////////////////////////////// FONCTION SACREE //////////////////////////////////////////

void LoadFamiliar()
{
	familiar.Load();
}

void UpdateFamiliar(float _dt, Player& _player)
{
	familiar.Update(_dt, _player);

}

void DisplayFamiliar(sf::RenderWindow& _window)
{
	familiar.Display(_window);
}