#include "SLShaders.h"

void SLShaders::AddLight(sf::Vector2f _pos, float _intensity)
{
	sf::Sprite emptySprite;
	Light tempLight(_pos, _intensity, emptySprite);
	m_lights.push_back(tempLight);
}

void SLShaders::ApplyLights(sf::RenderWindow& _window)
{
	sf::View camera = _window.getView();

	m_shader.setUniform("screenSize", camera.getSize());

	m_RTLights.create(camera.getSize().x, camera.getSize().y);
	m_RTLights.clear(sf::Color(32, 32, 32, 0));

	for (int i = 0; i < m_lights.size(); i++)
	{
		m_lights[i].sprite.setTexture(m_RTLights.getTexture());
		m_lights[i].sprite.setPosition(camera.getSize() / 2.f);
		m_lights[i].sprite.setOrigin(sf::Vector2f(m_lights[i].sprite.getTexture()->getSize()) / 2.f);

		sf::Vector2f pos(m_lights[i].pos.x - camera.getCenter().x + camera.getSize().x / 2.f, m_lights[i].pos.y - camera.getCenter().y + camera.getSize().y / 2.f);
		m_shader.setUniform("pos", pos);
		m_shader.setUniform("intensity", m_lights[i].intensity);

		sf::RenderStates tempState;
		tempState.shader = &m_shader;
		tempState.blendMode = sf::BlendAdd;

		m_RTLights.draw(m_lights[i].sprite, tempState);
	}

	m_RTLights.display();

	m_sceneSprite.setPosition(camera.getCenter());
	m_sceneSprite.setOrigin(camera.getSize() / 2.f);
	m_sceneSprite.setTexture(m_RTLights.getTexture());

	_window.draw(m_sceneSprite, sf::BlendMultiply);

	m_lights.clear();
}