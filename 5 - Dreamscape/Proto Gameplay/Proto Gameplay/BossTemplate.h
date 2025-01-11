#ifndef BossTemplate
#define BossTemplate
#include "Common.h"
#include "Animation.h"
#include "Player.h"
#include "ShootThemUp.hpp"
#include "BossFinalSound.h"
#include "Platformer.h"
#include "SoulsLevel.h"
#define COOLDOWN 2

enum BossState
{
	BOSSSOULS,
	BOSSSTU,
	BOSSPARCOUR,

};

enum BossAttack
{
	MineDrop,
	HealSpawn,
	ShootFan,
	DashAttack,
	Thorns,
	BlackHoleAttack,
	Hand,
	RootAttack,
	ChangePhase,
	Lightning,
	Explosion,
	BouncingBall,
	SlidingBall,
	White
};

class Boss
{
public:
	void Set_X(float _x) { pos.x = _x; }
	void Set_Y(float _y) { pos.y = _y; }
	void Set_Pos(sf::Vector2f _pos) { pos = _pos; }
	void Set_BarrePos(sf::Vector2f _pos) { LifeBarrePos = _pos; }
	void Set_Sprite(sf::Sprite _sprite) { Currentsprite = _sprite; }
	void Set_FullBarre(sf::Sprite _LifeBarreFull) { LifeBarreFull = _LifeBarreFull; }
	void Set_EmptyBarre(sf::Sprite _LifeBarreEmpty) { LifeBarreEmpty = _LifeBarreEmpty; }
	void Set_HealBarre(sf::Sprite _LifeBarreHeal) { LifeBarreHeal = _LifeBarreHeal; }
	void Set_ShadowBoss(sf::Sprite _shadowBoss) { shadowBoss = _shadowBoss; }
	void Set_Hp(float _hp) { hp = _hp; }
	void Set_State(BossState _state) { state = _state; }
	void Set_Cooldown(float _cooldown) { cooldown = _cooldown; }
	void Set_IsAttack(bool _IsAttack) { IsAttack = _IsAttack; }
	void Set_CurrentAttack(BossAttack _currentAttack) { currentAttack = _currentAttack; }
	void Set_IsAnimation(bool _IsAnimation) { IsAnimation = _IsAnimation; }
	void Set_SecondPhase(bool _SecondPhase) { SecondPhase = _SecondPhase; }
	void Set_IsInvincible(bool _isInvincible) { isInvincible = _isInvincible; }
	void Set_IsInvinciblePlayer(bool _isInvinciblePlayer) { isInvinciblePlayer = _isInvinciblePlayer; }
	void Set_Timer(float _timer) { timer = _timer; }
	void Set_RandomTimer(float _randomTimer) { randomTimer = _randomTimer; }
	void Set_Scale(float _scale) { scale = _scale; }
	void Set_CanChangeAttack(bool _canChangeAttack) { canChangeAttack = _canChangeAttack; }
	void Set_NeedMove(bool _needMove) { needMove = _needMove; }
	void Set_CurrentPos(short int _currentPos) { currentPos = _currentPos; }
	void Set_isAnimationDeathDone(bool _isAnimationDeathDone) { isAnimationDeathDone = _isAnimationDeathDone; }
	void RestartTouchClock() { touch.restart(); }
	void RestartNewPhaseTime() { newPhaseTime.restart(); }
	void Set_Alpha(float _alpha) { alpha = _alpha; }

	BossAttack Get_CurrentAttack() { return currentAttack; }
	BossState Get_State() { return state; }
	sf::Vector2f Get_Pos() { return pos; }
	sf::Vector2f Get_BarrePos() { return LifeBarrePos; }
	sf::Vector2f Get_ShadowPos() { return shadowPos; }
	sf::Sprite Get_Sprite() { return Currentsprite; }
	sf::Sprite Get_FullBarre() { return LifeBarreFull; }
	sf::Sprite Get_EmptyBarre() { return LifeBarreEmpty; }
	sf::Sprite Get_HealBarre() { return LifeBarreHeal; }
	sf::Sprite Get_ShadowBoss() { return shadowBoss; }
	sf::FloatRect Get_HitBox() { return hitBox; }
	sf::Clock Get_NewPhaseTime() { return newPhaseTime; }
	short int Get_CurrentPos() { return currentPos; }
	int Get_MaxHp() { return maxHp; }
	float Get_Hp() { return hp; }
	float Get_Cooldown() { return cooldown; }
	float Get_Timer() { return timer; }
	float Get_RandomTimer() { return randomTimer; }
	float Get_Scale() { return scale; }
	float Get_Alpha() { return alpha; }
	bool Get_IsAttack() { return IsAttack; }
	bool Get_CanChangeAttack() { return canChangeAttack; }
	bool Get_IsAnimation() { return IsAnimation; }
	bool Get_SecondPhase() { return SecondPhase; }
	bool Get_IsInvincible() { return isInvincible; }
	bool Get_NeedMove() { return needMove; }
	bool Get_isAnimationDeathDone() { return isAnimationDeathDone; }
	bool Get_IsInvinciblePlayer() { return isInvinciblePlayer; }

	void SwitchInvincibility() { isInvincible ? isInvincible = false : isInvincible = true; }
	void UpdateSwitchWorld(float _dt, bool& _transition, float _noirAlpha, SoulsLevel*& _soulsLevel, PlatformerData& _platformer);
	void GenerateNewWorld();
	bool Collide(sf::Vector2f _point, int _damage);
	void BossAnimation();
	void Reset();
	void PlayerCollide();
	void TransitionTP(float timeLeft, bool& _transition, float _noirAlpha, float& _timer, float& _randomTimer);
	void DecreaseHp(float _damage);
	void ShakeCamera(float _dt, SoulsLevel*& _soulsLevel, PlatformerData& _platformer);

	void DisplayHealInfo(sf::RenderWindow& _window);

	void Load();
	void Update(float _dt, bool& _transition, float _noirAlpha, GameState& _gameState, SoulsLevel*& _soulsLevel, PlatformerData& _platformer);
	void Display(sf::RenderWindow& _window);

	std::vector<sf::Sprite> spriteThunder;
	std::vector<sf::Sprite> spriteExplosionTP;
	std::vector<sf::Sprite> spriteExplosion;


private:
	sf::Sprite shadowBoss;
	sf::Vector2f shadowPos;
	sf::Vector2f pos;
	sf::Sprite Currentsprite;
	float maxHp = 1000;
	float hp = 1000;
	float timer = 0;
	float randomTimer = 45 + rand() % 15;
	sf::Sprite LifeBarreFull;
	sf::Sprite LifeBarreEmpty;
	sf::Sprite LifeBarreHeal;
	sf::Vector2f LifeBarrePos;
	sf::FloatRect hitBox;
	BossAttack currentAttack;
	float cooldown = 1;
	bool isTpStart = false;
	bool IsAttack = true;
	bool IsAnimation = false;
	bool SecondPhase = false;
	bool isInvincible = false;
	bool canChangeAttack = false;
	bool isAnimationDeathDone = false;
	bool needMove = false;
	bool isInvinciblePlayer = false;
	sf::Clock touch;
	float scale = 0;
	sf::Clock newPhaseTime;
	BossState state;
	short int currentPos;
	float alpha = 255;
	float waitingForAttack = 3;

	bool needPlatformer = false;
	bool needSTU = false;
	bool needSouls = false;


	//Sprite d'animation de chaque monde
	std::vector<sf::Sprite> spriteTabSTU =
	{
		LoadSprite("Assets/BossFinal/Boss/Idle/STU/1STU.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/STU/2STU.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/STU/3STU.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/STU/4STU.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/STU/5STU.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/STU/6STU.png", true)
	};

	std::vector<sf::Sprite> spriteTabSouls =
	{
		LoadSprite("Assets/BossFinal/Boss/Idle/Souls/1Souls.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/Souls/2Souls.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/Souls/3Souls.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/Souls/4Souls.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/Souls/5Souls.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/Souls/6Souls.png", true)
	};

	std::vector<sf::Sprite> spriteTabParcours =
	{
		LoadSprite("Assets/BossFinal/Boss/Idle/STU/1STU.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/STU/2STU.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/STU/3STU.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/STU/4STU.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/STU/5STU.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/STU/6STU.png", true)
	};
	//Tableaux des secondes phase
	std::vector<sf::Sprite> spriteTabSTUSecond =
	{
		LoadSprite("Assets/BossFinal/Boss/Idle/STU/1STUSecond.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/STU/2STUSecond.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/STU/3STUSecond.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/STU/4STUSecond.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/STU/5STUSecond.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/STU/6STUSecond.png", true)

	};

	std::vector<sf::Sprite> spriteTabSoulsSecond =
	{
		LoadSprite("Assets/BossFinal/Boss/Idle/Souls/1SoulsSecond.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/Souls/2SoulsSecond.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/Souls/3SoulsSecond.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/Souls/4SoulsSecond.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/Souls/5SoulsSecond.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/Souls/6SoulsSecond.png", true)

	};

	std::vector<sf::Sprite> spriteTabParcoursSecond =
	{
		LoadSprite("Assets/BossFinal/Boss/Idle/STU/1STUSecond.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/STU/2STUSecond.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/STU/3STUSecond.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/STU/4STUSecond.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/STU/5STUSecond.png", true),
		LoadSprite("Assets/BossFinal/Boss/Idle/STU/6STUSecond.png", true)

	};

	std::vector<sf::Sprite> spriteTabDeathSouls;
	std::vector<sf::Sprite> spriteTabDeathSTU;

	std::vector<sf::Sprite> spriteTabTpSTU =
	{
		LoadSprite("Assets/BossFinal/Boss/ChangePhase/STU/1.png", true),
		LoadSprite("Assets/BossFinal/Boss/ChangePhase/STU/2.png", true),
		LoadSprite("Assets/BossFinal/Boss/ChangePhase/STU/3.png", true),
		LoadSprite("Assets/BossFinal/Boss/ChangePhase/STU/4.png", true)

	};

	std::vector<sf::Sprite> spriteTabTpSouls =
	{
		LoadSprite("Assets/BossFinal/Boss/ChangePhase/SOULS/1.png", true),
		LoadSprite("Assets/BossFinal/Boss/ChangePhase/SOULS/2.png", true),
		LoadSprite("Assets/BossFinal/Boss/ChangePhase/SOULS/3.png", true),
		LoadSprite("Assets/BossFinal/Boss/ChangePhase/SOULS/4.png", true)
	};

	std::vector<sf::Sprite> tabVectorSprite[2][3] =
	{
		{spriteTabSouls,
		spriteTabParcours,
		spriteTabSTU} ,
		{spriteTabSoulsSecond,
		spriteTabParcoursSecond,
		spriteTabSTUSecond}
	};
};

class ShieldCircle
{
public:
	void Set_X(float _x) { pos.x = _x; }
	void Set_Y(float _y) { pos.y = _y; }
	void Set_Pos(sf::Vector2f _pos) { pos = _pos; }
	void Set_Sprite(sf::Sprite _sprite) { sprite = _sprite; }
	void Set_Rotation(float _rotation) { rotation = _rotation; }
	void Set_CanDisplay(bool _canDisplay) { canDisplay = _canDisplay; }

	sf::Vector2f Get_Pos() { return pos; }
	sf::Sprite Get_Sprite() { return sprite; }
	float Get_Rotation() { return rotation; }
	bool Get_CanDisplay() { return canDisplay; }

	void Rotate(float _dt);
	void UpdateAnimation(Boss& _theBoss);

	void Load();
	void UpdateShield(float _dt, sf::Vector2f pos, Boss& _theBoss);
	void Display(sf::RenderWindow& _window);

private:
	sf::Sprite sprite;
	sf::Vector2f pos;
	float rotation;
	bool canDisplay = false;
	std::vector <sf::Sprite> spriteTab;
	int compteur = 0;
	bool isShieldDone = false;
};

class Root
{
public:
	void Set_X(float _x) { pos.x = _x; }
	void Set_Y(float _y) { pos.y = _y; }
	void Set_Pos(sf::Vector2f _pos) { pos = _pos; }
	void Set_CanDisplay(bool _canDisplay) { canDisplay = _canDisplay; }
	void Set_IsPlayerTrapped(bool _isPlayerTrapped) { isPlayerTrapped = _isPlayerTrapped; }
	void Set_CanRetract(bool _canRetract) { canRetract = _canRetract; }
	void Set_Compteur(int _compteur) { compteur = _compteur; }
	void Set_Cooldown(float _cooldown) { cooldown = _cooldown; }
	void Set_CooldownDeload(float _cooldownDeload) { cooldownDeload = _cooldownDeload; }
	void Set_CompteurDeload(int _compteurDeload) { compteurDeload = _compteurDeload; }
	void Set_IsAnimationDone(bool _isAnimationDone) { isAnimationDone = _isAnimationDone; }
	void Set_Sprite(sf::Sprite _sprite) { currentSprite = _sprite; }

	sf::Vector2f Get_Pos() { return pos; }
	sf::Sprite Get_Sprite() { return currentSprite; }
	bool Get_CanDisplay() { return canDisplay; }
	bool Get_IsPlayerTrapped() { return isPlayerTrapped; }
	bool Get_CanRetract() { return canRetract; }
	std::vector <sf::Sprite> Get_SpriteVector() { return spriteVector; }

	void UpdateAnimation(SoulsLevel*& _soulsLevel, float _dt, Root& _root);
	void Retract(SoulsLevel*& _soulsLevel, float _dt);

	void Load();
	void Display(sf::RenderWindow& _window);

private:
	sf::Sprite currentSprite;
	sf::Vector2f pos;
	bool canDisplay = false;
	bool isAnimationDone = false;
	bool isPlayerTrapped = false;
	bool canRetract = false;
	int compteur = 0;
	float cooldown = 0;
	float cooldownDeload = 0;
	int compteurDeload = 5;

	std::vector <sf::Sprite> spriteVector =
	{
		LoadSprite("Assets/BossFinal/Attack/Root/1.png", false),
		LoadSprite("Assets/BossFinal/Attack/Root/2.png", false),
		LoadSprite("Assets/BossFinal/Attack/Root/3.png", false),
		LoadSprite("Assets/BossFinal/Attack/Root/4.png", false),
		LoadSprite("Assets/BossFinal/Attack/Root/5.png", false),
		LoadSprite("Assets/BossFinal/Attack/Root/6.png", false)
	};
};

class Circle
{
public:
	void Set_X(float _x) { pos.x = _x; }
	void Set_Y(float _y) { pos.y = _y; }
	void Set_Pos(sf::Vector2f _pos) { pos = _pos; }
	void Set_Sprite(sf::Sprite _sprite) { sprite = _sprite; }
	void Set_Rotation(float _rotation) { rotation = _rotation; }
	void Set_CanDisplay(bool _canDisplay) { canDisplay = _canDisplay; }

	sf::Vector2f Get_Pos() { return pos; }
	sf::Sprite Get_Sprite() { return sprite; }
	float Get_Rotation() { return rotation; }
	bool Get_CanDisplay() { return canDisplay; }

	void Rotate(float _dt);
	void Load();
	void Update(float _dt);
	void Display(sf::RenderWindow& _window);

private:
	sf::Sprite sprite;
	sf::Vector2f pos;
	float rotation;
	bool canDisplay = false;
};

class Laser
{
public:
	void Set_X(float _x) { pos.x = _x; }
	void Set_Y(float _y) { pos.y = _y; }
	void Set_Pos(sf::Vector2f _pos) { pos = _pos; }
	void Set_Alpha(float _alpha) { alpha = _alpha; }
	void Set_CanDisplay(bool _canDisplay) { CanDisplay = _canDisplay; }
	void Set_Affichage(float _affichage) { affichageY = _affichage; }
	void Set_Scale(float _scale) { scale = _scale; }
	void Set_Angle(float _angle) { angleLaser = _angle; }
	void Set_Timer(float _timer) { timer = _timer; }
	void Set_Current(float _current) { current = _current; }

	sf::Vector2f Get_Pos() { return pos; }
	sf::Sprite Get_Sprite() { return currentSprite; }
	float Get_Affichage() { return affichageY; }
	sf::Sprite Get_LaserSprite() { return laserSprite; }

	std::vector <sf::Sprite>& Get_VectorSprite() { return LaserSpriteVector; }

	void UpdateAnimation();
	void LaserAnimation();
	void RotateLaser(sf::Vector2f _pos);

	void Load();
	void Update(float _dt, Boss& _theBoss, sf::Vector2f _pos, Root& _root, SoulsLevel*& _soulsLevel);
	void Display(sf::RenderWindow& _window);
	sf::Sprite currentSprite;

private:
	std::vector <sf::Sprite> spriteVector;
	sf::Vector2f pos = { 350 , 100 };
	bool CanDisplay = false;
	float scale = 1;
	std::vector <sf::Sprite> LaserSpriteVector;
	sf::Sprite laserSprite;
	float affichageY = 35;
	float angleLaser = 0;
	float alpha = 255;
	float timer = 0;
	float current = 0;
};

class BlackHole
{
public:
	void Set_X(float _x) { pos.x = _x; }
	void Set_Y(float _y) { pos.y = _y; }
	void Set_Pos(sf::Vector2f _pos) { pos = _pos; }
	void Set_Scale(float _scale) { blackHoleScale = _scale; }
	void Set_signAlpha(float _alpha) { signAlpha = _alpha; }
	void Set_CanDisplaySign(bool _canDisplay) { canDisplaySign = _canDisplay; }
	void Set_CanDisplayHole(bool _canDisplay) { canDisplayHole = _canDisplay; }
	void Set_Rotation(float _rotation) { rotation = _rotation; }

	sf::Sprite Get_SignSprite() { return sign; }
	sf::Sprite Get_BlackHoleSprite() { return blackHole; }
	sf::Vector2f Get_Pos() { return pos; }
	float Get_BlackHoleScale() { return blackHoleScale; }
	float Get_signAlpha() { return signAlpha; }
	bool Get_CanDisplaySign() { return canDisplaySign; }
	bool Get_CanDisplayHole() { return canDisplayHole; }

	float Get_Rotation() { return rotation; }

	void UpdateSignAlpha(float _dt);
	void UpdateRotation(float _dt);
	void Reset();
	void UpdateAttraction(float _dt, SoulsLevel*& _soulsLevel, ParticuleManager& pm, Boss& _theBoss);

	void Load();
	void Update(float _dt, SoulsLevel*& _soulsLevel, ParticuleManager& _pm, Boss& _theBoss);
	void Display(sf::RenderWindow& _window);

private:
	sf::Sprite sign;
	sf::Sprite blackHole;
	sf::Vector2f pos;
	float blackHoleScale = 0;
	float signAlpha = 255;
	bool canDisplaySign = false;
	bool canDisplayHole = false;
	float signTimer = 0;
	float rotation = 0;
};

static Boss TheBoss;

void UpdateInvincibility(Boss& _theBoss);
int& GetTotalPlayerHp();

#endif // !BossTemplate
