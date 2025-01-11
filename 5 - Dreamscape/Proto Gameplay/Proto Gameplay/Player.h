#ifndef PLAYER_H
#define PLAYER_H

#include "Common.h"
#include "CreaMaths.h"
#include "Animation.h"
#include "MenuData.h"

class Player
{
public:
	Player();
	~Player();

	void Init();
	void Update(Config _config, float _dt, ControlsData*& m_controls);
	void Display(sf::RenderWindow& _window);

	sf::Vector2f Get_Pos() { return m_pos; }
	sf::Sprite Get_Sprite() { return m_sprite; }

	void Set_X(float _x) { m_pos.x = _x; }
	void Set_Y(float _y) { m_pos.y = _y; }
	void Set_Pos(sf::Vector2f pos) { m_pos = pos; }
	void Set_IsBlueTotem(bool _IsTotemBlue) { IsTotemBlue = _IsTotemBlue; }
	void Set_IsGreenTotem(bool _IsTotemGreen) { IsTotemGreen = _IsTotemGreen; }
	void Set_IsPurpleTotem(bool _IsTotemPurple) { IsTotemPurple = _IsTotemPurple; }
	void Set_Dir(enum Direction _dir) { m_dir = _dir; }

	bool Get_IsBlueTotem() { return IsTotemBlue; }
	bool Get_IsGreenTotem() { return IsTotemGreen; }
	bool Get_IsPurpleTotem() { return IsTotemPurple; }

	sf::Vector2f Get_Velocity() { return m_velocity; }

	Direction Get_Direction() { return m_dir; }
	void UpdateAnimation(float _animationDuration);

private:
	sf::Vector2f m_pos;
	sf::Vector2f m_fVector;
	sf::Vector2f m_velocity;
	sf::Sprite m_sprite;
	float m_rotation;
	float m_speed;
	Direction m_dir;


	void MovePlayer(Config _config, float _dt, ControlsData*& m_controls);

	enum PlayerState
	{
		IDLE,
		WALK,
		ATTACK,
		ROLL
	}m_state;

	AnimationManager m_currentAnimation;

	bool IsTotemBlue = false;
	bool IsTotemGreen = false;
	bool IsTotemPurple = false;
};

#endif