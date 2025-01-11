#ifndef STARS_HPP
#define STARS_HPP

#include "Common.h"
#include "Lobby.h"

class Stars
{
public:
	void Set_X(float _x) { pos.x = _x; }
	void Set_Y(float _y) { pos.y = _y; }
	void Set_Pos(sf::Vector2i _pos) { pos = _pos; }
	void Set_Alpha(float _alpha) { alpha = _alpha; }
	void Set_Compteur(float _compteur) { compteur = _compteur; }

	sf::Sprite Get_Sprite() { return sprite; }
	sf::Vector2i Get_Pos() { return pos; }
	float Get_Alpha() { return alpha; }
	float Get_Compteur() { return compteur; }

	void FindPosition();

	void Load();
	void Update(float _dt);
	void Display(sf::RenderWindow& _window);
	
	int random;

private:
	sf::Sprite sprite;
	sf::Vector2i pos;
	float alpha = 255;
	float compteur = rand() % 10;
	sf::Color color;
};

void LoadStars();
void UpdateStars(float _dt);
void DisplayStars(sf::RenderWindow& _window);

#endif // !STARS_HPP
