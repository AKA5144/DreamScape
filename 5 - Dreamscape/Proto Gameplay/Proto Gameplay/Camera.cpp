#include "Camera.h"

void Camera::Init(sf::Vector2f _pos)
{
	m_pos = _pos;
	m_zoom = 1/3.f;
	m_speed = 5.f;
	m_deadZone = 30;

	m_camera.setCenter(m_pos);
	m_camera.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Camera::Update(float _dt)
{
	m_camera.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_camera.zoom(m_zoom);
	m_bounds = {
		m_camera.getCenter().x - m_camera.getSize().x / 2.f,
		m_camera.getCenter().y - m_camera.getSize().y / 2.f,
		m_camera.getSize().x,
		m_camera.getSize().y
	};

	sf::Vector2f camTargetVec = GetPosTargetVector();

	if (CreaMaths::GetSquaredLength(camTargetVec) > m_deadZone * m_deadZone)
	{
		m_pos += camTargetVec * _dt * m_speed;
	}

	m_camera.setCenter(m_pos);
}