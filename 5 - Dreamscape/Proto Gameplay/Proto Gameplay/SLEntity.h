#ifndef SLENTITY_H
#define SLENTITY_H

#include "Common.h"
#include "Animation.h"

class SLEntity
{
public:
	enum StateAttack
	{
		STARTUP,
		ACTIVE,
		RECOVERY
	};

	struct Attack
	{
		sf::Vector2f pos;
		sf::FloatRect hitbox;
		int damage;
		int type;

		// For projectiles
		sf::Sprite sprite;
		sf::Vector2f dirVec;
		float speed;

		// For animated ranged attacks
		AnimationManager anim;
	};

	void DecreaseHP(int _damage) { m_hp -= _damage; m_hit = true; }
	void DeleteAttack(int _ID) { m_attacks.erase(m_attacks.begin() + _ID); }

	void SetPosition(sf::Vector2f _pos) { m_pos = _pos; }
	void SetInvincibilityTimer(float _timer) { m_invincibilityTimer = _timer; m_initialInvincibilityTimer = m_invincibilityTimer; m_isInvincible = true; }
	void Set_Speed(float _speed) { m_speed = _speed; }

	const sf::Vector2f GetPosition() { return m_pos; }
	sf::Vector2f GetSize() { return sf::Vector2f(m_sprite.getTexture()->getSize()); }
	const sf::Vector2f GetVelocity() { return m_velocity; }
	const sf::Vector2f GetFVector() { return m_fVector; }
	const sf::FloatRect GetHitbox() { return m_hitbox; }
	const float GetSpeed() { return m_speed; }
	const int GetHP() { return m_hp; }
	const AnimationManager::FrameType GetAnimationState() { return m_currentAnimation.GetCurrentFrameType(); }

	const bool IsInvincible() { return m_isInvincible; }
	const bool IsMoving() { return CreaMaths::GetVectorLength(m_fVector) != 0; }

	std::vector<Attack>& GetAttackVector() { return m_attacks; }
	void CancelMovement() { m_pos -= m_velocity; m_hitbox.left -= m_velocity.x; m_hitbox.top -= m_velocity.y; }

	//Temporaire
	void GetFrame(std::string _attack, sf::Vector3i& _frames) {
		std::ifstream file("Data/SoulsLevel/Frames/DataAttackBoss.txt");
		std::string line;
		if (file.is_open())
		{
			while (getline(file, line))
			{
				std::string keyword = _attack;
				std::size_t found = line.find(keyword);
				if (found != std::string::npos)
				{
					int count = 0;
					std::stringstream ss(line.substr(found + keyword.length()));
					while (ss >> _frames.x >> _frames.y >> _frames.z && count < 3)
					{
						count++;
					}
					break;
				}
			}
			file.close();
		}
	}
protected:
	sf::Sprite m_sprite;
	sf::Vector2f m_pos;
	sf::Vector2f m_size;
	sf::Vector2f m_fVector;
	sf::Vector2f m_velocity;
	sf::FloatRect m_hitbox;
	Direction m_dir;
	float m_dirAngle; // Angle du vecteur forward
	float m_speed;
	float m_rotation;
	int m_hp;
	int m_maxHP;

	bool m_isInvincible = false;
	bool m_hit = false;

	float m_invincibilityTimer;
	float m_initialInvincibilityTimer;

	// Normalement ça devrait dégager quand les animations seront finies
	float m_cooldown;
	float m_maxCooldown;

	AnimationManager m_currentAnimation;

	std::vector<Attack> m_attacks;

	void UpdateCooldown(float _dt)
	{
		if (m_cooldown > 0)
		{
			m_cooldown -= _dt;
		}
		else
		{
			m_cooldown = 0;
		}
	}

	void UpdateInvincibility(float _dt)
	{
		if (m_invincibilityTimer - _dt > 0)
		{
			m_isInvincible = true;
			m_invincibilityTimer -= _dt;
		}
		else
		{
			m_hit = false;
			m_isInvincible = false;
			m_invincibilityTimer = 0;
			m_initialInvincibilityTimer = 0;
		}
	}
};

#endif