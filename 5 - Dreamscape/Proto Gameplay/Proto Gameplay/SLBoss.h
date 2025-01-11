#ifndef SL_BOSS2_H
#define SL_BOSS2_H

#include "Common.h"
#include <random>

#include "ProportionalBars.h"
#include "Animation.h"
#include "Collisions.h"
#include "SLPlayer.h"
#include "SLEntity.h"
#include "SLEnemies.h"

class SLBoss : public SLEntity
{
public:

	//Constructeur
	SLBoss() : m_generator(), m_gen(m_generator()), m_limitTimerGenerator(1.f, 5.f), m_state(WAITING), SLEntity() {}

	void Load(SLPlayer* _player);
	void Update(float _dt);
	void Display(sf::RenderWindow& _window);
	void DisplayHealthBar(sf::RenderWindow& _window);

	const bool IsDashing() { return m_lastAttack == DASH && m_state == ATTACKING; }
	const AnimationManager::FrameType GetFrameType() { return m_currentAnimation.GetCurrentFrameType(); }

	void CancelDashHitbox();
	void SetPlayerHit() { m_playerHit = true; }
	const bool GetPlayerHit() { return m_playerHit; }

	const std::vector<sf::Vector2f> GetStageAttacksPos();
	const std::vector<sf::Vector2f> GetAttacksPos();

	enum State
	{
		WAITING,
		RUSHING,
		BAITING,
		TP,
		ATTACKING,
		RECOVERING,
		CHASING,
		NUMBER_OF_STATES
	};

	enum BossAttack
	{
		SLASH_RIGHT,
		SLASH_LEFT,
		ESTOC,
		BLOOM_CLOSE,
		BLOOM_RANGE,
		BLOOM_NUKE,
		BOMB,
		DASH,
		DEEP_ESTOC,
		NUMBER_OF_ATTACKS
	};

private:
	// Random précis
	std::default_random_engine m_generator;
	std::mt19937 m_gen;
	std::uniform_real_distribution<float> m_limitTimerGenerator;

	// Outils pour le random
	std::uniform_real_distribution<float> m_randX;
	std::uniform_real_distribution<float> m_randY;
	sf::Vector2f m_randomRangeX;
	sf::Vector2f m_randomRangeY;
	sf::Vector2f m_randPos;

	State m_state;
	float m_stateTimer; // Le timer en lui même
	float m_stateTimerLimit; // La valeur max du timer (si dépassement, évenement)

	sf::Vector2f m_posTargetVector;
	sf::Vector2f m_dashDirVec;
	float m_reach;

	SLPlayer* m_player;
	bool m_playerHit = false;

	bool m_hasDodged = false;

	bool m_isInPhase2 = false;

	sf::RectangleShape* m_healthBar;
	sf::Sprite m_healthOutline;

	std::vector<BossAttack> m_availableAttacks[NUMBER_OF_ATTACKS];
	BossAttack m_nextAttack[NUMBER_OF_ATTACKS];
	BossAttack m_lastAttack;

	sf::FloatRect m_bossRoom;

	enum RonceSpriteType
	{
		START,
		MIDDLE,
		END
	};

	struct RonceSprite
	{
		sf::Sprite sprite;
		RonceSpriteType type;
		sf::Vector2f pos;
	};

	struct StageAttack
	{
		SLEntity::Attack attack;
		std::vector<RonceSprite> sprites;
		sf::FloatRect hitbox;
		sf::Vector2f firstRoncePos;

		Direction dir;
		float initTimer;
		float idleTimer;
		float mescouillesFloat = 0;
		bool isDeploying = false;
		bool isDeployed = false;
		bool isRetracted = false;
	};

	sf::Sprite m_preloadedStageAttackSprites[2][3];
	std::vector<StageAttack> m_stageAttacks;
	AnimationManager m_ronceAnimation;

	float m_ronceTimer; // Le timer en lui même
	float m_ronceTimerLimit; // La valeur max du timer (si dépassement, évenement)

	void UpdateDirection();
	void UpdateAnimation();
	void UpdateHealthBar();

	void UpdateStates();
	void UpdateStateManager();
	void SetState(int _state);

	void UpdateMovements(float _dt);

	const bool IsPlayerInRange() { return CreaMaths::GetSquaredDistance(m_posTargetVector) <= m_reach * m_reach; }

	void CreateStageAttack(Direction _type);
	void UpdateStageAttacks(float _dt);
	void DisplayStageAttacks(sf::RenderWindow& _window);

	void CreateAttack(int _type);
	int GetRandomAttack();

	void LoadCombos();
	void UpdateCombo();
	void EndCombo();

	sf::FloatRect GetAttackHitbox(int _type);
};

#endif