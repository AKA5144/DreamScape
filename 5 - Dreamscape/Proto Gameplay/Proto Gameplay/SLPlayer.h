#ifndef SLPLAYER_H
#define SLPLAYER_H

#include "Common.h"
#include "CreaMaths.h"
#include "Collisions.h"
#include "Animation.h"
#include "ProportionalBars.h"
#include "SLEntity.h"
#include "SLSounds.h"

class SLPlayer : public SLEntity
{
public:
	enum AttackType
	{
		DEFAULT,
		SPECIAL
	};

	enum State
	{
		IDLE,
		WALK,
		ATTACK,
		ATTACKSPE,
		ROLL
	};

	void Init();
	void Update(Config _config, float _dt);
	void Display(sf::RenderWindow& _window);

	const sf::Vector2f GetHitboxCenter() { return { m_hitbox.left + m_hitbox.width / 2.f, m_hitbox.top + m_hitbox.height / 2.f }; }
	sf::Sprite& GetSprite() { return m_sprite; }
	const bool GetLockedMode() { return m_isInLockedMode; }
	const int GetLockedEnemyID() { return m_lockedEnemyID; }
	const sf::Vector3i GetStats() { return sf::Vector3i(m_hp, m_mana, (int)m_stamina); }
	const int GetState() { return m_state; }
	const sf::FloatRect GetLockHitbox() { return m_lockHitbox; }

	void SetLockedTarget(sf::Vector2f _pos) { m_lockedPos = _pos; }
	void SetLockedMode(bool _bool) { m_isInLockedMode = _bool; }
	void SetLockedEnemyID(int _ID) { m_lockedEnemyID = _ID; }

	bool SpecialHitWall(bool _bool) { return _bool; }
	void MoveHitbox(sf::Vector2f _vector) { m_hitbox.left += _vector.x; m_hitbox.top += _vector.y; }
	void SetVelocity(sf::Vector2f _velocity) { m_velocity = _velocity; }

	void RestoreHealth(int _amount) { (m_hp + _amount < m_maxHP) ? m_hp += _amount : m_hp = m_maxHP; }
	void RestoreMana(int _amount) { (m_mana + _amount < m_maxMana) ? m_mana += _amount : m_mana = m_maxMana; }


	void MoveTo(sf::Vector2f _target, float _speed, float _dt); // Pour cinématiques
	void ForceIdle();

private:

	// Gameplay principal
	void Move(Config _config, float _dt);
	void UseAbility(Config _config, float _dt);

	// Attaques
	void CreateAttack(int _type);
	void UpdateAttacks(float _dt);

	// Inputs
	void UpdateKeyboardInputs();
	void UpdateControllerInputs();

	// Cooldown
	void UpdateCooldownBar(float _dt);
	void DisplayCooldownBar(sf::RenderWindow& _window);

	// Cinématiques
	void ForceUpdateDirection();

	// Extras
	void UpdateStates(float _dt);
	void UpdateDirection();
	void UpdateAnimation();
	void UpdateStamina(float _dt);

	State m_state;

	bool m_isInLockedMode;
	int m_lockedEnemyID;
	sf::Vector2f m_lockedPos;
	sf::FloatRect m_lockHitbox;

	int m_mana;
	int m_maxMana;

	float m_stamina;
	float m_maxStamina;
	sf::Clock m_staminaClock;

	bool m_hasHat;
	sf::Sprite m_hatSprite;
	sf::Sprite m_lockSprite;

	sf::RectangleShape* m_coolDownBar;

	SLSounds m_sounds;
};

#endif