#include "STUShootManager.hpp"


void ShootManager::AddShoot(sf::Vector2f _pos, float _speed, int _damage, STUShootType _who, ShootType _type)
{
	Shoot shoot;

	shoot.SetPos(_pos);
	shoot.SetSpeed(_speed);
	shoot.SetDamage(_damage);
	shoot.SetWho(_who);
	shoot.SetType(_type);
	shoot.SetIsAlive(true);

	shootVector.push_back(shoot);

	if (_who == PLAYER)
	{
		shotSound.play();
	}
}

void ShootManager::AddShoot(sf::Vector2f _pos, sf::Vector2f _dir,float _angle, float _speed, int _damage, STUShootType _who, ShootType _type)
{
	Shoot shoot;

	shoot.SetPos(_pos);
	shoot.SetDir(_dir);
	shoot.SetSpeed(_speed);
	shoot.SetDamage(_damage);
	shoot.SetWho(_who);
	shoot.SetType(_type);
	shoot.SetIsAlive(true);
	shoot.SetAngle(_angle);

	shootVector.push_back(shoot);
}

void ShootManager::Collision(void)
{
	for (int k = 0; k < shootVector.size(); k++)
	{
		if (shootVector[k].GetPos().y > -100 && shootVector[k].GetPos().y < SCREEN_HEIGHT +100)
		{
			
		}
		else
		{
			shootVector[k].SetIsAlive(false);

		}
	}

}

void ShootManager::Update(float _dt)
{
	Collision();

	for (int k = 0; k < shootVector.size(); k++)
	{
		shootVector[k].Update(_dt);
	}

	for (int k = 0; k < shootVector.size(); k++)
	{
		if (!shootVector[k].GetIsAlive())
		{
			if (shootVector[k].GetWho() == PLAYER)
			{
				explodeShot temp;
				temp.pos = shootVector[k].GetPos();
				animHitShot.push_back(temp);
			}

			shootVector.erase(shootVector.begin() + k);
		}
	}

	for (int k = 0; k < animHitShot.size(); k++)
	{
		if (animHitShot[k].currentAnim <= MAX_EXPLODE_SHOT)
		{
			animHitShot[k].currentAnim += 20 * _dt;
		}

		if (animHitShot[k].currentAnim >= MAX_EXPLODE_SHOT)
		{
			animHitShot[k].currentAnim = MAX_EXPLODE_SHOT-1;
			animHitShot[k].isFinish = true;
		}
	}
	for (int k = 0; k < animHitShot.size(); k++)
	{
		if (animHitShot[k].isFinish)
		{
			animHitShot.erase(animHitShot.begin() + k);
		}
	}

	if (animHitShot.size() == 0)
	{
		animHitShot.clear();
	}
}

void ShootManager::Display(sf::RenderWindow& _window)
{
	for (int k = 0; k < shootVector.size(); k++)
	{
		shootVector[k].Display(_window);
	}

	for (int k = 0; k < animHitShot.size(); k++)
	{
		if (animHitShot[k].pos.y > 0)
		BlitSprite(explodeSprite[(int)animHitShot[k].currentAnim], animHitShot[k].pos, _window,{3,3}, animHitShot[k].angle);
	}
}