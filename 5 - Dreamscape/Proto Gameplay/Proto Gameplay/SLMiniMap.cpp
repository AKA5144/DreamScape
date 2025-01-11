#include "SLMiniMap.h"
#include "Easing.h"

void SLMinimap::SetSettings()
{
	m_borderOffset = { 20, 20 };
	m_size = 0.25f;
}

SLMinimap::SLMinimap(std::string _currentLevel, SLMap* _map, SLPlayer* _player, SLTutorial* _tutorial)
{
	m_map = _map;
	m_player = _player;
	m_tutorial = _tutorial;

	m_decorMap = m_map->GetDecorMap();
	m_collisionMap = m_map->GetCollisionMap();

	m_renderTexture.create(m_map->GetMapSize().x + SCREEN_WIDTH, m_map->GetMapSize().y + SCREEN_HEIGHT);
	m_renderTexture.clear(sf::Color::Black);

	m_shader.loadFromFile("Assets/Souls/Shaders/desaturate.frag", sf::Shader::Fragment);
	m_shader.setUniform("saturation", 0.5f);

	m_filter.setFillColor(sf::Color::Transparent);

	m_shape[12] = LoadSprite("Assets/Souls/Minimap/tree.png", false);
	mescouillesSprite = LoadSprite("Assets/Souls/Minimap/shroomPos.png", true);
	m_forwardArrow = LoadSprite("Assets/Souls/Minimap/minimap_arrow.png", true);
	m_outline = LoadSprite("Assets/Souls/Minimap/outline.png", true);

	sf::Sprite* tempSprite = new sf::Sprite;
	*tempSprite = LoadSprite("Assets/Souls/Minimap/minimapTarget.png", true);
	for (int i = 0; i < 3; i++)
	{
		m_targetSprite[i] = *tempSprite;
	}
	delete tempSprite;

	SetSettings();
	float timer = 0;

	sf::Vector2f outlineSize = sf::Vector2f(m_outline.getTexture()->getSize());

	float openAngle = 30;
	openAngle = 90 - openAngle / 2.f;

	m_shroomsRT.create(outlineSize.x, outlineSize.y);
	m_targetMaskImage.create(outlineSize.x, outlineSize.y, sf::Color::Transparent);

	for (int i = 0; i < outlineSize.x; i++)
	{
		for (int j = 0; j < outlineSize.y; j++)
		{
			sf::Vector2f posTargetVec = CreaMaths::CreateVector(m_outline.getPosition() + outlineSize / 2.f, sf::Vector2f(i, j));

			float angle = CreaMaths::RadiansToDegrees(atan2f(posTargetVec.y, posTargetVec.x));

			if (CreaMaths::IsInBetween(angle, -180 + openAngle, -openAngle))
			{
				m_targetMaskImage.setPixel(i, j, sf::Color::White);
			}
		}
	}

	m_targetMaskTexture.loadFromImage(m_targetMaskImage);
	m_targetMaskSprite.setTexture(m_targetMaskTexture);
	m_targetMaskSprite.setOrigin(outlineSize / 2.f);
}

void SLMinimap::CreateMinimapMask(const sf::RenderWindow& _window)
{
	if (m_maskTexture.getSize().x == 0)
	{
		sf::View* camera = new sf::View(_window.getView());

		m_maskImage.create(camera->getSize().x, camera->getSize().y, sf::Color::Transparent);

		for (int i = 0; i < camera->getSize().x; i++)
		{
			for (int j = 0; j < camera->getSize().y; j++)
			{
				if (Collisions::IsCollidingCirclePoint(sf::Vector2f(camera->getSize().x - camera->getSize().y / 2.f, camera->getSize().y / 2.f), camera->getSize().y / 2.f, sf::Vector2f(i, j)))
				{
					m_maskImage.setPixel(i, j, sf::Color::White);
				}
			}
		}

		m_maskTexture.loadFromImage(m_maskImage);
		m_maskSprite.setTexture(m_maskTexture);

		delete camera;
	}
}

void SLMinimap::Display(sf::RenderWindow& _window, sf::Vector2f _playerDir)
{
	sf::View camera = _window.getView();

	SLMinimap::CreateMinimapMask(_window);

	m_renderTexture.clear(sf::Color(11, 54, 75, 255));
	m_shroomsRT.clear(sf::Color::Transparent);

	m_view = camera;
	m_view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_view.setViewport(sf::FloatRect(1 - m_size, 0.f, m_size, m_size));
	m_view.setViewport(sf::FloatRect(m_view.getViewport().left - m_borderOffset.x / SCREEN_WIDTH, m_view.getViewport().top + m_borderOffset.y / SCREEN_HEIGHT, m_view.getViewport().width, m_view.getViewport().height));

	m_view.setCenter(camera.getCenter() - sf::Vector2f(m_view.getSize().x / 2.f - m_view.getSize().y / 2.f, 0));
	_window.setView(m_view);

	//m_map->DisplayGround(_window, m_renderTexture);
	//m_map->DisplayDecor(_window, m_renderTexture);

	sf::Vector2i startingID = m_map->GetTileID(m_view.getCenter() - m_view.getSize() / 2.f);
	sf::Vector2i endID = m_map->GetTileID(m_view.getCenter() + m_view.getSize() / 2.f);

	for (int i = startingID.x; i < endID.x + 1; i++)
	{
		for (int j = startingID.y; j < endID.y + 1; j++)
		{
			if (m_decorMap[i][j] == SLMap::DecorTiles(12) || m_collisionMap[i][j] == SLMap::CollisionTiles::WALL)
			{
				m_shape[12].setOrigin(64 / 2.f - 32 / 2.f, 64 / 2.f);
				m_shape[12].setPosition({ j * 32.f, i * 32.f });
				m_renderTexture.draw(m_shape[12]);
			}
		}
	}

	m_filter.setRadius(m_view.getSize().y / 2.f);
	m_filter.setOrigin(m_filter.getRadius(), m_filter.getRadius());
	m_filter.setPosition(m_view.getCenter().x + m_view.getSize().x / 2.f - m_view.getSize().y / 2.f, m_view.getCenter().y);

	m_renderTexture.draw(m_filter);

	std::vector<sf::Vector2f> activeTargets = m_tutorial->GetActiveTargets();
	for (int i = 0; i < activeTargets.size(); i++)
	{
		mescouillesSprite.setPosition(activeTargets[i]);
		m_renderTexture.draw(mescouillesSprite);
	}

	m_maskSprite.setPosition(m_view.getCenter() - m_view.getSize() / 2.f);

	m_renderTexture.draw(m_maskSprite, sf::BlendMultiply);

	m_renderTexture.display();

	sf::Sprite sprite(m_renderTexture.getTexture());
	_window.draw(sprite, &m_shader);

	//m_forwardArrow.setPosition(camera.getCenter().x + camera.getSize().x / 2.f - 0.25f * (m_filter.getRadius() + m_borderOffset.x), camera.getCenter().y - camera.getSize().y / 2.f + 0.25f * (m_filter.getRadius() + m_borderOffset.y));
	m_forwardArrow.setPosition(m_filter.getPosition());
	m_forwardArrow.setScale(8, 8);
	m_forwardArrow.setRotation(90 + CreaMaths::RadiansToDegrees(atan2f(_playerDir.y, _playerDir.x)));
	_window.draw(m_forwardArrow);

	_window.setView(camera);

	sf::Vector2f viewSize(m_view.getSize().x * m_view.getViewport().width, m_view.getSize().y * m_view.getViewport().height);
	viewSize *= 1 / 3.f;

	m_outline.setPosition(camera.getCenter().x + camera.getSize().x / 2.f, camera.getCenter().y - camera.getSize().y / 2.f);
	sf::Vector2f modifiedPos = m_outline.getPosition();
	modifiedPos.x -= m_borderOffset.x * 1 / 3.f;
	modifiedPos.y += m_borderOffset.y * 1 / 3.f;

	modifiedPos.x -= m_filter.getRadius() * 1 / 12.f;
	modifiedPos.y += m_filter.getRadius() * 1 / 12.f;

	m_outline.setPosition(modifiedPos);
	sf::Vector2f outlineSize(m_outline.getTexture()->getSize());

	for (int i = 0; i < activeTargets.size(); i++)
	{
		m_targetSprite[i].setPosition(outlineSize / 2.f);
		m_shroomsRT.draw(m_targetSprite[i], sf::BlendAdd);

		sf::Vector2f shroomPos(m_map->GetTileCenter(m_map->GetShroomTiles()[i]));

		sf::Vector2f posTargetVec = CreaMaths::CreateVector(m_player->GetPosition(), activeTargets[i]);
		float angle = CreaMaths::RadiansToDegrees(atan2f(posTargetVec.y, posTargetVec.x));

		m_targetMaskSprite.setRotation(angle + 90);
		m_targetMaskSprite.setPosition(outlineSize / 2.f);
		m_shroomsRT.draw(m_targetMaskSprite, sf::BlendMultiply);
		m_shroomsRT.display();

		if (CreaMaths::GetSquaredDistance(posTargetVec) > (m_filter.getRadius() - 4) * (m_filter.getRadius() - 4))
		{
			sf::Sprite RTContent(m_shroomsRT.getTexture());
			RTContent.setPosition(modifiedPos - outlineSize / 2.f);
			_window.draw(RTContent);
		}
	}

	_window.draw(m_outline);
}