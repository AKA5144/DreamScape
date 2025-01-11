#ifndef PARCOURBOSS_HPP
#define PARCOURBOSS_HPP
#include "Common.h"
#include "BossTemplate.h"

class Warning
{
public:
	void Load();
	void Update(float _dt, PlatformerData& _platformerData);
	void Display(sf::RenderWindow& _window);

	bool canDisplay = false;
	bool canMove = true;

private:
	sf::Sprite sprite;
	float alpha;
	sf::Vector2f pos;
};

class Thunder
{
public:
	void Set_X(float _x) { pos.x = _x; }
	void Set_Y(float _y) { pos.y = _y; }
	void Set_Pos(sf::Vector2f _pos) { pos = _pos; }
	void Set_Sprite(sf::Sprite _sprite) { currentSprite = _sprite; }
	void Set_Alpha(float _alpha) { alpha = _alpha; }

	sf::Sprite Get_Sprite() { return currentSprite; }
	sf::Vector2f Get_Pos() { return pos; }
	float Get_AffichageY() { return affichageY; }
	float Get_Alpha() { return alpha; }

	void Animation(float _dt);

	void Update(float _dt, sf::Vector2f _pos, Boss& _theBoss, Warning& _warning, bool& _isAnimationDone, PlatformerData& _platformerData);
	void Display(sf::RenderWindow& _window);

private:
	sf::Sprite currentSprite = LoadSprite("Assets/BossFinal/Attack/Platformer/Thunder/Thunder/1.png", true);
	sf::Vector2f spriteTaille = (sf::Vector2f)currentSprite.getTexture()->getSize();

	sf::Vector2f pos;
	std::vector<sf::Sprite> spriteTab =
	{
		LoadSprite("Assets/BossFinal/Attack/Platformer/Thunder/Thunder/2.png", true),
		LoadSprite("Assets/BossFinal/Attack/Platformer/Thunder/Thunder/3.png", true)
	};
	float affichageY = 0;
	float alpha = 255;
	bool canDisplay = false;
};

class BallBouncing
{
public:
	void Set_X(float _x) { pos.x = _x; }
	void Set_Y(float _y) { pos.y = _y; }
	void Set_Pos(sf::Vector2f _pos) { pos = _pos; }
	void Set_Sprite(sf::Sprite _sprite) { currentSprite = _sprite; }
	void Set_CanDisplay(bool _canDisplay) { canDisplay = _canDisplay; }
	void Set_Director(sf::Vector2f _director) { director = _director; }
	void Set_LifeTime(float _lifeTime) { lifeTime = _lifeTime; }

	sf::Vector2f Get_Pos() { return pos; }
	sf::Sprite Get_Sprite() { return currentSprite; }
	bool Get_CanDisplay() { return canDisplay; }
	float Get_LifeTime() { return lifeTime; }

	void UpdateLifeTime(float _dt);
	void UpdateBorderCollision(float _dt, PlatformerData& _platformerData);

	void Load();
	void Update(float _dt, PlatformerData& _platformerData, Boss& _theBoss);
	void Display(sf::RenderWindow& _window);

private:
	sf::Sprite currentSprite;
	sf::Vector2f pos;
	std::vector <sf::Sprite> spriteTab;
	bool canDisplay = false;
	sf::Vector2f director;
	float lifeTime = 5;
};

class BallSliding
{
public:
	void Set_X(float _x) { pos.x = _x; }
	void Set_Y(float _y) { pos.y = _y; }
	void Set_Pos(sf::Vector2f _pos) { pos = _pos; }
	void Set_IsTouch(bool _isTouch) { isTouch = _isTouch; }

	sf::Vector2f Get_Pos() { return pos; }
	bool Get_CanDisplay() { return canDisplay;}
	bool Get_IsTouch() { return isTouch; }

	void UpdateAnimation(float _dt);

	void Load(PlatformerData& _platformerData, sf::Vector2f _pos);
	void Update(float _dt, PlatformerData& _platformerData, Boss& _theBoss);
	void Display(sf::RenderWindow& _window);

private:
	sf::Sprite currentSprite;
	sf::Vector2f pos;
	std::vector <sf::Sprite> spriteTab;
	bool canDisplay = true;
	bool onLeft = false;
	int compteur = 0;
	sf::Clock cooldown;
	float delay = 0.2;
	float alpha = 0;
	float lifeTime = 15;
	bool isTouch = false;
};

class ExplosionHitBox
{
public:
	void Set_X(float _x) { pos.x = _x; }
	void Set_Y(float _y) { pos.y = _y; }
	void Set_Pos(sf::Vector2f _pos) { pos = _pos; }
	void Set_Sprite(sf::Sprite _sprite) { sprite = _sprite; }
	void Set_Rotation(float _rotation) { rotation = _rotation; }
	void Set_Alpha(float _alpha) { alpha = _alpha; }
	void Set_Scale(float _scale) { scale = _scale; }
	void Set_AttackEnd(bool _attackEnd) { attackEnd = _attackEnd; }

	sf::Vector2f Get_Pos() { return pos; }
	sf::Sprite Get_Sprite() { return sprite; }
	float Get_Rotation() { return rotation; }
	float Get_Alpha() { return alpha; }
	float Get_Scale() { return scale; }
	bool Get_AttackEnd() { return attackEnd; }

	void Reset();

	void Load();
	void Update(Boss& _theBoss, PlatformerData& _platformerData, float _dt);
	void Display(sf::RenderWindow& _window);

private:
	sf::Sprite sprite;
	float rotation = 0;
	float alpha = 255;
	float scale = 0;
	sf::Vector2f pos;
	float timer = 0;
	bool damageDone = false;
	bool attackEnd = false;
};

void LoadParcoursBoss();
void UpdateParcoursBoss(float _dt, PlatformerData& _platformerData, sf::RenderWindow& _window, GameState& _gameState, bool& _transition, float _noirAlpha, ControlsData*& m_controls, Boss& _theBoss, Player& _player);
void DisplayParcoursBoss(sf::RenderWindow& _window, PlatformerData& _platformerData, Boss& _theBoss);

std::vector <BallSliding>& Get_SlidingVector();
void ResetWorld();

#endif // !PARCOURBOSS_HPP
