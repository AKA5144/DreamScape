#ifndef SL_MAP_H
#define SL_MAP_H

#include "Common.h"
#include "Collisions.h"
#include "Debug.h"

class SLMap
{
public:

	SLMap(int _tileSize, std::string _map);
	~SLMap() {}

	enum class CollisionTiles
	{
		EMPTY = -1,
		WALL,
		TRIGGER,
		INVISIBLE_WALL,
		DEATH_TILE,
		NUMBER_OF_TILES
	};
	typedef std::vector<std::vector<SLMap::CollisionTiles>> SLMAP_Collision;

	enum class DecorTiles
	{
		NUMBER_OF_TILES = 31
	};
	typedef std::vector<std::vector<SLMap::DecorTiles>> SLMAP_Decor;

	enum class DataTiles
	{
		ROSCASS,
		MELEE,
		PLAYER,
		GEM,
		BOSS,
		SHROOMS,
		NUMBER_OF_TILES
	};
	typedef std::vector<std::vector<SLMap::DataTiles>> SLMAP_Data;


	void Init();
	void DisplayGem(sf::RenderWindow& _window);

	void DisplayGround(sf::RenderWindow& _window);
	void DisplayDecor(sf::RenderWindow& _window, bool _abovePlayer = false, sf::Vector2f _playerPos = sf::Vector2f(0, 0));

	void DisplayGround(sf::RenderWindow& _window, sf::RenderTexture& _RT);
	void DisplayDecor(sf::RenderWindow& _window, sf::RenderTexture& _RT, bool _abovePlayer = false, sf::Vector2f _playerPos = sf::Vector2f(0, 0));

	void OverWriteCollision(sf::Vector2i _ID, CollisionTiles _value);

	sf::Vector2f GetMapSize() { return sf::Vector2f(m_width * m_tileSize, m_height * m_tileSize); }
	sf::Vector2f GetMapDimensions() { return sf::Vector2f(m_width, m_height); }

	CollisionTiles GetTileTypeCollision(sf::Vector2i _ID);
	DecorTiles GetTileTypeDecor(sf::Vector2i _ID);
	DataTiles GetTileTypeData(sf::Vector2i _ID);

	SLMAP_Collision GetCollisionMap() { return m_collisionMap; }
	SLMAP_Decor GetDecorMap() { return m_decorMap; }
	SLMAP_Decor GetGroundMap() { return m_solMap; }
	SLMAP_Data GetDataMap() { return m_dataMap; }

	// Tiles
	sf::Vector2i GetTileID(sf::Vector2f _pos);
	sf::FloatRect GetTileBounds(sf::Vector2i _ID);
	sf::Vector2f GetTileCenter(sf::Vector2i _ID) { return sf::Vector2f(GetTileBounds(_ID).left + m_tileSize / 2.f, GetTileBounds(_ID).top + GetTileBounds(_ID).height / 2.f); }
	sf::Vector2f GetDecorTileSize(sf::Vector2i _ID) { return sf::Vector2f(m_tileTexture[(int)m_decorMap[_ID.y][_ID.x]].getSize()); }

	// Data Tiles
	std::vector<sf::Vector2i> GetEnemyTiles() { return m_enemyTiles; }
	sf::Vector2i GetPlayerTile() { return m_playerTile; }
	sf::Vector2i GetBossTile() { return m_bossTile; }
	std::vector<sf::Vector2i> GetShroomTiles() { return m_shroomTiles; }

	// Tiles identification
	std::vector<sf::Vector2i> GetCollidedTiles(sf::Vector2f _startingPos, sf::Vector2f _vector);
	std::vector<int> GetCollidedTilesType(sf::Vector2f _startingPos, sf::Vector2f _vector);
	std::vector<sf::Vector2i> GetCurrentRoomTiles(sf::Vector2f _initialPos);

private:

	std::string currentMap;

	SLMAP_Collision m_collisionMap;
	SLMAP_Decor m_decorMap;
	SLMAP_Decor m_solMap;
	SLMAP_Data m_dataMap;

	int m_width;
	int m_height;
	float m_tileSize;

	sf::Sprite m_tileSprite;
	sf::Texture m_tileTexture[(int)DecorTiles::NUMBER_OF_TILES];

	std::vector<sf::Vector2i> m_enemyTiles;
	sf::Vector2i m_playerTile;
	sf::Vector2i m_bossTile;
	sf::Vector2i m_gemTile;
	std::vector<sf::Vector2i> m_shroomTiles;

	sf::Sprite gemSprite;

	template <typename T>
	void LoadMapFromFile(std::vector<std::vector<T>>& _map, std::string _path);
	void GetMapData();

	std::vector<sf::Vector2i> m_currentRoomTiles;
};

#endif