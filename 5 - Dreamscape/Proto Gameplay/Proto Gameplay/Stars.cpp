#include "Stars.h"

std::vector <Stars> starsVector;

sf::Sprite tabSprite[3] = {
	LoadSprite("Assets/Lobby/Stars/1.png", false),
	LoadSprite("Assets/Lobby/Stars/2.png", false)
};

void Stars::FindPosition()
{
	sf::Vector2i position;
	position = { (rand() % SCREEN_WIDTH) ,(rand() % SCREEN_HEIGHT) };
	bool IsPosOk = true;

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (position.x + i > 0 && position.x + i < SCREEN_WIDTH && position.y + j > 0 && position.y + j < SCREEN_HEIGHT)
			{
				if (Get_ImageData().getPixel(position.x + i, position.y + j) != sf::Color(255, 255, 255))
				{
					IsPosOk = false;
				}
			}
		}
	}

	if (!IsPosOk)
	{
		FindPosition();
	}
	else
	{
		pos = position;
		IsPosOk = false;
	}

}

void Stars::Load()
{
	random = rand() % 20;

	if (random != 1)
	{
		random = 0;
	}

	sprite = tabSprite[random];
	color = sf::Color(rand() % 255, rand() % 255, 255);
	FindPosition();
}

void Stars::Update(float _dt)
{
	switch (random)
	{
	case 0: compteur += 5 * _dt;
		break;
	case 1: compteur += 1 * _dt;
		break;
	}
	alpha = 85 * (1 + std::cos(compteur));
}

void Stars::Display(sf::RenderWindow& _window)
{
	color.a = alpha;
	BlitSprite(sprite, (sf::Vector2f)pos, _window, { 3 , 3 }, 0 ,color);
}

void LoadStars()
{
	int numberStars = 300 + rand() % 10;

	for (int i = 0; i < numberStars; i++)
	{
		Stars stars;
		stars.Load();
		starsVector.push_back(stars);
	}
}

void UpdateStars(float _dt)
{
	for (int i = 0; i < starsVector.size(); i++)
	{
		starsVector[i].Update(_dt);
	}
}

void DisplayStars(sf::RenderWindow& _window)
{
	for (int i = 0; i < starsVector.size(); i++)
	{
		starsVector[i].Display(_window);
	}
}