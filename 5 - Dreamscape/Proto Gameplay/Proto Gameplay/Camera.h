#ifndef CAMERA_H
#define CAMERA_H

#include "Common.h"
#include "CreaMaths.h"

class Camera
{
public:
	void Init(sf::Vector2f _pos);
	void Update(float _dt);

	void SetTarget(sf::Vector2f _pos) { m_targettedPos = _pos; }
	void SetSpeed(float _speed) { m_speed = _speed; }
	void SetZoom(float _zoom) { m_zoom = _zoom; }
	void SetDeadZone(float _length) { m_deadZone = _length; }
	void SetPosition(sf::Vector2f _pos) { m_camera.setCenter(_pos); }

	sf::View GetView() { return m_camera; };
	const sf::FloatRect GetBounds() { return m_bounds; }
	const sf::Vector2f GetTarget() { return m_targettedPos; }
	const sf::Vector2f GetPosition() { return m_pos; }
	const sf::Vector2f GetPosTargetVector() { return CreaMaths::CreateVector(m_pos, m_targettedPos); }
	const bool IsOnTarget() { return !(CreaMaths::GetSquaredLength(GetPosTargetVector()) > m_deadZone * m_deadZone); }
	const sf::Vector2f Get_Pos() { return m_pos; }

private:
	sf::View m_camera;
	sf::Vector2f m_targettedPos;
	sf::Vector2f m_pos;
	sf::FloatRect m_bounds;
	float m_zoom;
	float m_speed;
	float m_deadZone;
};

#endif