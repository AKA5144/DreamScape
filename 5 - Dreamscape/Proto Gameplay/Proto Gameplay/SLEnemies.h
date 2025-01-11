#ifndef SL_ENEMIES_H
#define SL_ENEMIES_H

#include "Common.h"
#include "CreaMaths.h"
#include "ProportionalBars.h"
#include "Collisions.h"
#include "SLEntity.h"
#include "SLSounds.h"

class SLEnemy : public SLEntity
{
public:
	enum EnemyType
	{
		ROSCASS,
		FALKYN
	};

	enum States
	{
		WANDERING, // Se balade
		GAINED_AGGRO, // T'a vu (état de transition entre WANDERING et AGGROING)
		AGGROING, // Te court après / Attends que tu rentre dans son champ d'attaque
		ATTACKING, // Est en train d'attaquer
		SEARCHING, // Te cherche
		LOST_AGGRO, // En a eu marre de te chercher (état de transition entre SEARCHING et WANDERING)
		DYING // Traduis fdp
	};

	void Create(sf::Vector2f _pos, EnemyType _type);
	void Update(float _dt);
	void Display(sf::RenderWindow& _window);

	void SetTarget(sf::Vector2f _pos) { m_target = _pos; }
	void SetPlayerPos(sf::Vector2f _pos) { m_playerPos = _pos; }
	void SetState(States _state) { m_state = _state; }
	void SetLockedStatus(bool _bool) { m_isLocked = _bool; }
	void GetCollidedTilesTypeFunc(std::function<std::vector<int>(sf::Vector2f _startingPos, sf::Vector2f _vector)> _func) { m_GetCollidedTilesType = _func; }

	const EnemyType GetType() { return m_type; }
	const float GetAggroRange() { return m_aggroRange; }
	const std::vector<Attack> GetAttackVector() { return m_attacks; }
	const States GetState() { return m_state; }

	void ClearSounds() { m_sounds.ClearVector(); }

	// Debug
	const sf::FloatRect GetAttackRangeHitbox() { return m_attackRangeHitbox; }
	const sf::Vector2f GetTarget() { return m_target; }
	const Direction GetDirection() { return m_dir; }
	const float GetVisionAngle() { return m_visionAngle; }

	void SetAggroRange(float _aggroRange) { m_aggroRange = _aggroRange; }

	bool IsInVisionCone(sf::Vector2f _pos, float _angle);

	const bool Kill() { m_state = DYING; return m_currentAnimation.HasEnded(); }
private:
	sf::Vector2f m_target;
	sf::Vector2f m_lastKnownTarget;
	sf::Vector2f m_playerPos;
	sf::FloatRect m_attackRangeHitbox;

	sf::RectangleShape* m_healthBar;

	EnemyType m_type;
	States m_state;
	States m_nextState;
	float m_visionAngle;
	float m_attackRange;
	float m_aggroRange;
	bool m_isLocked = false;

	float m_searchingTimer;
	float m_wanderingTimer;

	SLSounds m_sounds;

	// Fix des bugs liés aux statics
	bool m_once = false;
	int m_it = 0;

	void UpdateStates(float _dt);
	void UpdateStateMachine(float _dt);
	void UpdateDirection();
	void UpdateAnimation();
	std::function<std::vector<int>(sf::Vector2f _startingPos, sf::Vector2f _vector)> m_GetCollidedTilesType;

	enum RoscassAttacks
	{
		TRIPLE_SHOT
	};

	enum MeleeEnnemyAttacks
	{
		DEFAULT
	};

	// Attaques
	void CreateAttack(int _type);
	void UpdateAttacks(float _dt);

};

#endif