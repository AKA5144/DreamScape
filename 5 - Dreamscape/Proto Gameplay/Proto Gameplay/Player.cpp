#include "Player.h"

void UpdateKeyboardInputs(sf::Vector2f& m_fVector, Direction& m_dir, ControlsData*& m_controls)
{
	if (sf::Keyboard::isKeyPressed(m_controls->keyBinding[KEYUP]))
	{
		m_dir = UP;
		m_fVector.y--;
	}
	if (sf::Keyboard::isKeyPressed(m_controls->keyBinding[KEYDOWN]))
	{
		m_dir = DOWN;
		m_fVector.y++;
	}
	if (sf::Keyboard::isKeyPressed(m_controls->keyBinding[KEYLEFT]))
	{
		m_dir = LEFT;
		m_fVector.x--;
	}
	if (sf::Keyboard::isKeyPressed(m_controls->keyBinding[KEYRIGHT]))
	{
		m_dir = RIGHT;
		m_fVector.x++;
	}
}

void UpdateControllerInputs(sf::Vector2f& m_fVector, Direction& m_dir)
{
	m_fVector.x = sf::Joystick::getAxisPosition(0, sf::Joystick::X) / 100;
	m_fVector.y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y) / 100;

	if (CreaMaths::IsInBetween(m_fVector.x, -0.25, 0.25))
	{
		m_fVector.x = 0;
	}
	if (CreaMaths::IsInBetween(m_fVector.y, -0.25, 0.25))
	{
		m_fVector.y = 0;
	}

	float vectorAngle = CreaMaths::RadiansToDegrees(atan2f(m_fVector.y, m_fVector.x));

	if (CreaMaths::GetSquaredLength(m_fVector) != 0)
	{
		if (CreaMaths::IsInBetween(vectorAngle, -45, 45))
		{
			m_dir = RIGHT;
		}
		else if (vectorAngle > 135 ||vectorAngle < -135)
		{
			m_dir = LEFT;
		}
		else if (CreaMaths::IsInBetween(vectorAngle, 45, 135))
		{
			m_dir = DOWN;
		}
		else if (CreaMaths::IsInBetween(vectorAngle, -135, -45))
		{
			m_dir = UP;
		}
	}
}

void Player::MovePlayer(Config _config, float _dt, ControlsData*& m_controls)
{
	// Reset forward vector
	m_fVector = { 0, 0 };

	// Input
	if (_config == KEYBOARD)
	{
		UpdateKeyboardInputs(m_fVector, m_dir,m_controls);
	}
	else if (_config == CONTROLLER)
	{
		UpdateControllerInputs(m_fVector, m_dir);
	}

	// The forward vector needs to keep a maximum norm of 1
	if (CreaMaths::GetSquaredLength(m_fVector) > 1)
	{
		CreaMaths::ClampLength(m_fVector, 1);
	}

	// Update the velocity
	m_fVector.x /= 1.5;
	m_fVector.y /= 1.5;
	m_velocity = m_fVector * _dt * m_speed;

	if (m_fVector != sf::Vector2f(0, 0))
	{
		m_state = WALK;
	}
	else
	{
		m_state = IDLE;
	}

	// Update player pos
	m_pos += m_velocity;	
}

void Player::UpdateAnimation(float _animationDuration)
{
	// Entrer toutes les valeurs possibles de l'enum, impérativement dans l'ordre
	std::string statePath[] = { "Idle", "Walk", "Attack", "Roll" };
	std::string dirPath[] = { "Up", "Down", "Left", "Right" };

	std::string path = "";
	path = "Assets/Player/" + statePath[m_state] + "/" + dirPath[m_dir] + "/";

	m_currentAnimation.PlayAnimation(path, _animationDuration);

	m_sprite = m_currentAnimation.GetCurrentSprite();
}

//////////////////////////////////////////////////////////////////////////////////////////////////

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init()
{
	m_sprite = LoadSprite("Assets/Player/Idle/Down/1.png", true);
	m_pos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 1.333333 };
	m_fVector = { 0, 0 };
	m_rotation = 0;
	m_speed = 500.f;
	m_dir = DOWN;
	m_state = IDLE;
}

void Player::Update(Config _config, float _dt, ControlsData*& m_controls)
{
	MovePlayer(_config, _dt, m_controls);

	// La durée totale de l'animation (le temps nécessaire pour que l'animation se complète)
	float animDuration = 0.7;

	UpdateAnimation(animDuration);
}

void Player::Display(sf::RenderWindow& _window)
{
	BlitSprite(m_sprite, m_pos, _window,{3,3});
}