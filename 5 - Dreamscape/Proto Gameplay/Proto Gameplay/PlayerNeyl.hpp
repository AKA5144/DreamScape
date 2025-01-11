#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Common.h"
#include "CollisionManagerNeyl.hpp"
#include "CreaMaths.h"
#include "GameState.h"
#include "Particules.hpp"
#include "MenuData.h"

#define LEVEL_END 5738
#define ANIM_DURATION_DEFAULT 0.5f
#define JUMP_COOLDOWN 0.4f
#define JUMP_FORCE 600 //500

enum State
{
	WALKING,
	DASH
};
enum PlayerAnimation
{
	IDLE,
	WALK,
	JUMPSTART,
	JUMPMID,
	JUMPEND,
	GRAB
};

struct KeyInput
{
	sf::Keyboard::Key Forward;
	sf::Keyboard::Key Backward;
	sf::Keyboard::Key Jump;
};

class PlayerPlatformer
{
public:
	PlayerPlatformer();
	~PlayerPlatformer();

	void AddAnim(std::vector<sf::Sprite> _anim);
	void Update(float secondsElapsed, Map _map, Map badMap, GameState& _gameState, bool& _transition, float _noirAlpha, sf::Vector2f& cameraPos, ControlsData*& m_controls, bool _finalBoss, BreakMap breakMap);
	void Draw(sf::RenderWindow& _window);
	void Move(sf::Vector2f _newPos, Map& _map, BreakMap breakMap);
	void DashUpdate(float _dt, Map _map, BreakMap breakMap);
	void SetMove(float _dt, Map _map, ControlsData*& m_controls);
	void DashKey(ControlsData*& m_controls);
	void SetPosition(sf::Vector2f _pos) { position = _pos; }
	void SetPosition(float _x, float _y) { position = { _x,_y }; }
	void Die(sf::Vector2f& cameraPos, float secondsElapsed, bool _finalBoss, bool& _transition, float _noirAlpha);
	void SetSpeed(float _speed) { speed = _speed; }
	bool GetDead() { return hasDied; }
	sf::FloatRect GetRect() { return animations[curAnim][curAnimTile].getGlobalBounds(); }
	sf::Vector2f GetPosition() { return position; }
	float startTimer = 2;
	KeyInput params;

	sf::Vector2f position;
	sf::Vector2f topPointMid;
	sf::Vector2f topPointLeft;
	sf::Vector2f topPointRight;

	sf::Vector2f midPointLeft;
	sf::Vector2f midPointRight;
	sf::SoundBuffer deathSoundBuffer;
	sf::Sound deathSound;
	sf::Vector2f groundPointMid;
	sf::Vector2f groundPointLeft;
	sf::Vector2f groundPointRight;
	bool CheatBool;
	sf::SoundBuffer jumpSoundBuffer;
	sf::SoundBuffer dashSoundBuffer;
	sf::Sound jumpSound;
	sf::Sound dashSound;
	float HP = 100.f;
	sf::SoundBuffer monsterSoundBuffer;
	sf::Sound monsterSound;

	float speed;

	float jumpForce;
	sf::Clock jumpClock;
	bool isJumping = false;

	std::vector<std::vector<sf::Sprite>> animations;
	PlayerAnimation curAnim = WALK;
	unsigned char curAnimTile = 0;
	float curTime = 0;
	float animDuration = 0.5f;
	sf::Vector2i Dir = { 0, 0 };

	bool isDead = false;

	//Collision Points
	
	float velocity = 0.f;

	float direction = 1;

	bool isOnWall;
	bool HasDashed;
	bool hasDied;
	bool airDash = false;
	bool dashing = false;
	sf::Vector2f startDash;
	const float initDashSpeed = 700.f;
	sf::Clock initAirDash;
	const float dashRange = 100;
	float dashSpeed = initDashSpeed;
	State state;
private:


	sf::Vector2f handleInput(float secondsElapsed, Map _map, ControlsData*& m_controls);

	ParticuleManager Pm;
	ParticuleManager PmDeath;
};

#endif // !PLAYER_HPP
