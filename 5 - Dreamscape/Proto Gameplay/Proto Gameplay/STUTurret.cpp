#include "STUTurret.hpp"

sf::Sprite animTurret[4][4] =
{
	{LoadSprite("Assets/Shoot Them Up/Turret/LineS/1.png", true),
	LoadSprite("Assets/Shoot Them Up/Turret/LineS/2.png", true),
	LoadSprite("Assets/Shoot Them Up/Turret/LineS/3.png", true),
	LoadSprite("Assets/Shoot Them Up/Turret/LineS/4.png", true)},

	{LoadSprite("Assets/Shoot Them Up/Turret/LineD/1.png", true),
	LoadSprite("Assets/Shoot Them Up/Turret/LineD/2.png", true),
	LoadSprite("Assets/Shoot Them Up/Turret/LineD/3.png", true),
	LoadSprite("Assets/Shoot Them Up/Turret/LineD/4.png", true)},

	{LoadSprite("Assets/Shoot Them Up/Turret/WaveS/1.png", true),
	LoadSprite("Assets/Shoot Them Up/Turret/WaveS/2.png", true),
	LoadSprite("Assets/Shoot Them Up/Turret/WaveS/3.png", true),
	LoadSprite("Assets/Shoot Them Up/Turret/WaveS/4.png", true)},

	{LoadSprite("Assets/Shoot Them Up/Turret/WaveD/1.png", true),
	LoadSprite("Assets/Shoot Them Up/Turret/WaveD/2.png", true),
	LoadSprite("Assets/Shoot Them Up/Turret/WaveD/3.png", true),
	LoadSprite("Assets/Shoot Them Up/Turret/WaveD/4.png", true)},
};

void Turret::Move(sf::Vector2f _point, float _dt,bool _rotate)
{
	if (_rotate)
	{
		SpeedAngle >= FLT_MAX ? SpeedAngle = 0.00f : SpeedAngle -= 1 * _dt;

		//Rotation du vecteur entre le vaiseau et le shield
		sf::Vector2f V1 = VectorFromPlayer;
		float x = (V1.x * cosf(SpeedAngle)) - (V1.y * sinf(SpeedAngle));
		float y = (V1.x * sinf(SpeedAngle)) + (V1.y * cosf(SpeedAngle));

		//Position du shield en fonction de la position du vaiseau et du vecteur Ship-Shield apres rotation
		sf::Vector2f newPos{ x + _point.x, y + _point.y };

		pos = newPos;
	}
	else
	{
		pos.x = _point.x;
		pos.y = _point.y - 100;//100 = turretdist dans module player
	}

}

void Turret::Shot(float _dt)
{
	if ((float)attackTimer.getElapsedTime().asSeconds() >= cooldown)
	{
		switch (type)
		{
		case SIMPLE_LINE:
			Sm.AddShoot(pos, 500, 1, PLAYER, LINE_SHOOT);
			attackTimer.restart();
			break;

		case DOUBLE_LINE:
			Sm.AddShoot({ pos.x - 20, pos.y }, 500, 1, PLAYER, LINE_SHOOT);
			Sm.AddShoot({ pos.x + 20, pos.y }, 800, 1, PLAYER, LINE_SHOOT);
			attackTimer.restart();
			break;
		case SIMPLE_WAVE:
			Sm.AddShoot(pos, 500, 1, PLAYER, WAVE_SHOOT);
			attackTimer.restart();
			break;
		case DOUBLE_WAVE:
			Sm.AddShoot({ pos.x - 20, pos.y }, 500, 1, PLAYER, WAVE_SHOOT);
			Sm.AddShoot({ pos.x + 20, pos.y }, 800, 1, PLAYER, WAVE_SHOOT);
			attackTimer.restart();
			break;

		default:
			Sm.AddShoot(pos, 500, 1, PLAYER, LINE_SHOOT);
			attackTimer.restart();
			break;
		}
	}

	Sm.Update(_dt);
}

void Turret::UpdateAnim(float _dt)
{
	animTimer < 4 - 1 ? animTimer += _dt * 4 : animTimer -= 4 - 1;
	currentSprite = (int)animTimer;
	sprite = animTurret[type][currentSprite];
}

void Turret::Update(sf::Vector2f _point, float _dt,bool _rotate)
{
	UpdateAnim(_dt);
	Move(_point,_dt,_rotate);
	Shot(_dt);
}

void Turret::Display(sf::RenderWindow& _window)
{
	Sm.Display(_window);
	BlitSprite(sprite, pos, _window,{3,3});
}
