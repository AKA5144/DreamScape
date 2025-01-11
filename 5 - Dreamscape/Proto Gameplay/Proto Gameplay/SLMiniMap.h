#ifndef SLMINIMAP_H
#define SLMINIMAP_H

#include "Common.h"
#include "SLMap.h"
#include "SLPlayer.h"
#include "SLTutorial.h"

class SLMinimap
{
public:
	SLMinimap(std::string _currentLevel, SLMap* _map, SLPlayer* _player, SLTutorial* _tutorial);
	void Display(sf::RenderWindow& _window, sf::Vector2f _playerDir);

private:
	sf::CircleShape m_filter;
	sf::View m_view;

	sf::Vector2f m_borderOffset;
	float m_size; // en pourcentage (< 1)

	// Masque pour minimap ronde
	sf::RenderTexture m_renderTexture;
	sf::Image m_maskImage;
	sf::Texture m_maskTexture;
	sf::Sprite m_maskSprite;

	sf::Shader m_shader;

	sf::Sprite m_shape[(int)SLMap::DecorTiles::NUMBER_OF_TILES];
	sf::Sprite m_forwardArrow;
	sf::Sprite m_outline;
	sf::Sprite m_targetSprite[3];
	sf::Sprite mescouillesSprite;

	sf::RenderTexture m_shroomsRT;
	sf::Image m_targetMaskImage;
	sf::Texture m_targetMaskTexture;
	sf::Sprite m_targetMaskSprite;

	SLMap::SLMAP_Decor m_decorMap;
	SLMap::SLMAP_Collision m_collisionMap;

	SLMap* m_map;
	SLPlayer* m_player;
	SLTutorial* m_tutorial;
	void SetSettings();
	void CreateMinimapMask(const sf::RenderWindow& _window);
};

#endif