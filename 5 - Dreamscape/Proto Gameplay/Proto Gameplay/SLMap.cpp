#include "SLMap.h"
#include <type_traits>

SLMap::SLMap(int _tileSize, std::string _map)
{
	m_tileSize = _tileSize;
	currentMap = _map;
}

void SLMap::OverWriteCollision(sf::Vector2i _ID, CollisionTiles _value)
{
	m_collisionMap[_ID.y][_ID.x] = _value;
}

void SLMap::Init()
{
	LoadMapFromFile(m_collisionMap, "Data/" + currentMap + "/Level_Collisions.csv");
	LoadMapFromFile(m_decorMap, "Data/" + currentMap + "/Level_Décor.csv");
	LoadMapFromFile(m_solMap, "Data/" + currentMap + "/Level_Sol.csv");
	LoadMapFromFile(m_dataMap, "Data/" + currentMap + "/Level_Data.csv");

	m_height = m_collisionMap.size();
	m_width = m_collisionMap[0].size();

	for (unsigned int i = 0; i < (int)DecorTiles::NUMBER_OF_TILES; i++)
	{
		m_tileTexture[i].loadFromFile(std::format("Assets/Souls/Map/{}.png", i));
	}

	gemSprite = LoadSprite("Assets/Souls/Misc/gem.png", true);

	GetMapData();
}

void SLMap::DisplayGround(sf::RenderWindow& _window)
{
	sf::View camera = _window.getView();

	sf::Vector2i startingID = GetTileID(camera.getCenter() - camera.getSize() / 2.f);
	sf::Vector2i endID = GetTileID(camera.getCenter() + camera.getSize() / 2.f);

	for (int i = startingID.x; i < endID.x + 2; i++)
	{
		for (int j = startingID.y; j < endID.y + 1; j++)
		{
			if (i >= 0 && i < m_height && j >= 0 && j < m_width)
			{
				m_tileSprite.setOrigin(0, 0);
				m_tileSprite.setTexture(m_tileTexture[(int)m_solMap[i][j]], true);
				m_tileSprite.setPosition({ j * m_tileSize, i * m_tileSize });
				_window.draw(m_tileSprite);
			}
		}
	}
}

void SLMap::DisplayGround(sf::RenderWindow& _window, sf::RenderTexture& _renderTexture)
{
	sf::View camera = _window.getView();

	sf::Vector2i startingID = GetTileID(camera.getCenter() - camera.getSize() / 2.f);
	sf::Vector2i endID = GetTileID(camera.getCenter() + camera.getSize() / 2.f);

	for (int i = startingID.x; i < endID.x + 2; i++)
	{
		for (int j = startingID.y; j < endID.y + 1; j++)
		{
			if (i >= 0 && i < m_height && j >= 0 && j < m_width)
			{
				m_tileSprite.setOrigin(0, 0);
				m_tileSprite.setTexture(m_tileTexture[(int)m_solMap[i][j]], true);
				m_tileSprite.setPosition({ j * m_tileSize, i * m_tileSize });
				_renderTexture.draw(m_tileSprite);
			}
		}
	}
}

void SLMap::DisplayDecor(sf::RenderWindow& _window, bool _abovePlayer, sf::Vector2f _playerPos)
{
	sf::View camera = _window.getView();

	sf::Vector2i startingID = GetTileID(camera.getCenter() - camera.getSize() / 2.f);
	sf::Vector2i endID = GetTileID(camera.getCenter() + camera.getSize() / 2.f);

	sf::Vector2f textureSize;

	if (_abovePlayer)
	{
		startingID.x = GetTileID(_playerPos).x;
	}

	for (int i = startingID.x; i < endID.x + 2; i++)
	{
		for (int j = startingID.y; j < endID.y + 1; j++)
		{
			if (i >= 0 && i < m_height && j >= 0 && j < m_width)
			{
				if ((int)m_decorMap[i][j] >= 0 && (int)m_decorMap[i][j] != 15)
				{
					m_tileSprite.setTexture(m_tileTexture[(int)m_decorMap[i][j]], true);
					textureSize = sf::Vector2f(m_tileTexture[(int)m_decorMap[i][j]].getSize());

					if ((_abovePlayer && (textureSize.x > 32 || textureSize.y > 32)) || !_abovePlayer)
					{
						if (textureSize.x > 32 || textureSize.y > 32)
						{
							m_tileSprite.setOrigin(textureSize.x / 2.f - m_tileSize / 2.f, textureSize.y / 2.f);
						}
						else
						{
							m_tileSprite.setOrigin(0, 0);
						}

						m_tileSprite.setPosition({ j * m_tileSize, i * m_tileSize });
						_window.draw(m_tileSprite);
					}
				}
			}
		}
	}
}

void SLMap::DisplayDecor(sf::RenderWindow& _window, sf::RenderTexture& _renderTexture, bool _abovePlayer, sf::Vector2f _playerPos)
{
	sf::View camera = _window.getView();

	sf::Vector2i startingID = GetTileID(camera.getCenter() - camera.getSize() / 2.f);
	sf::Vector2i endID = GetTileID(camera.getCenter() + camera.getSize() / 2.f);

	sf::Vector2f textureSize;

	if (_abovePlayer)
	{
		startingID.x = GetTileID(_playerPos).x;
	}

	for (int i = startingID.x; i < endID.x + 2; i++)
	{
		for (int j = startingID.y; j < endID.y + 1; j++)
		{
			if (i >= 0 && i < m_height && j >= 0 && j < m_width)
			{
				if ((int)m_decorMap[i][j] >= 0 && (int)m_decorMap[i][j] != 15)
				{
					m_tileSprite.setTexture(m_tileTexture[(int)m_decorMap[i][j]], true);
					textureSize = sf::Vector2f(m_tileTexture[(int)m_decorMap[i][j]].getSize());

					if ((_abovePlayer && (int)m_decorMap[i][j] == 12) || !_abovePlayer)
					{
						if (textureSize.x > 32 || textureSize.y > 32)
						{
							m_tileSprite.setOrigin(textureSize.x / 2.f - m_tileSize / 2.f, textureSize.y / 2.f);
						}
						else
						{
							m_tileSprite.setOrigin(0, 0);
						}

						m_tileSprite.setPosition({ j * m_tileSize, i * m_tileSize });
						_renderTexture.draw(m_tileSprite);
					}
				}
			}
		}
	}
}

void SLMap::DisplayGem(sf::RenderWindow& _window)
{
	BlitSprite(gemSprite, GetTileCenter(m_gemTile), _window);
}

sf::Vector2i SLMap::GetTileID(sf::Vector2f _pos)
{
	sf::Vector2i tileID(_pos.y / m_tileSize, _pos.x / m_tileSize);

	if (tileID.x < 0) tileID.x = 0;
	if (tileID.x >= m_height) tileID.x = m_height - 1;

	if (tileID.y < 0) tileID.y = 0;
	if (tileID.y >= m_width) tileID.y = m_width - 1;

	return tileID;
}

SLMap::CollisionTiles SLMap::GetTileTypeCollision(sf::Vector2i _ID)
{
	if (_ID.x >= 0 && _ID.y >= 0 && _ID.y < m_width && _ID.x < m_height)
	{
		return m_collisionMap[_ID.x][_ID.y];
	}
	else return (CollisionTiles)-1;
}
SLMap::DecorTiles SLMap::GetTileTypeDecor(sf::Vector2i _ID)
{
	if (_ID.x >= 0 && _ID.y >= 0 && _ID.y < m_width && _ID.x < m_height)
	{
		return m_decorMap[_ID.x][_ID.y];
	}
	else return (DecorTiles)-1;
}
SLMap::DataTiles SLMap::GetTileTypeData(sf::Vector2i _ID)
{
	if (_ID.x >= 0 && _ID.y >= 0 && _ID.y < m_width && _ID.x < m_height)
	{
		return m_dataMap[_ID.x][_ID.y];
	}
	else return (DataTiles)-1;
}

sf::FloatRect SLMap::GetTileBounds(sf::Vector2i _ID)
{
	return
	{
		_ID.y * m_tileSize,
		_ID.x * m_tileSize,
		 m_tileSize,
		 m_tileSize
	};
}

template <typename T>
void SLMap::LoadMapFromFile(std::vector<std::vector<T>>& _map, std::string _path)
{
	std::ifstream mapFile(_path);

	if (!mapFile.is_open())
	{
		std::cout << "Impossible d'ouvrir le fichier CSV." << std::endl;
	}
	else
	{
		std::string line;
		while (std::getline(mapFile, line))
		{
			// Initialisation d'un flux de chaînes pour extraire les valeurs de la ligne
			std::stringstream ss(line);

			std::vector<T> rowData;

			int value;
			while (ss >> value)
			{
				rowData.push_back(static_cast<T>(value));

				if (ss.peek() != ',')
					break;

				ss.ignore();
			}

			_map.push_back(rowData);
		}
		mapFile.close();
	}
}

void SLMap::GetMapData()
{
	m_enemyTiles.clear();

	for (int i = 0; i < m_dataMap.size(); i++)
	{
		for (int j = 0; j < m_dataMap[i].size(); j++)
		{
			DataTiles tileType = m_dataMap[i][j];

			if (tileType == DataTiles::ROSCASS || tileType == DataTiles::MELEE)
			{
				m_enemyTiles.push_back({ i, j });
			}
			else if (tileType == DataTiles::PLAYER)
			{
				m_playerTile = sf::Vector2i(i, j);
			}
			else if (tileType == DataTiles::GEM)
			{
				m_gemTile = sf::Vector2i(i, j);
			}
			else if (tileType == DataTiles::BOSS)
			{
				m_bossTile = sf::Vector2i(i, j);
			}
			else if (tileType == DataTiles::SHROOMS)
			{
				m_shroomTiles.push_back({ i, j });
			}
		}
	}
}

std::vector<sf::Vector2i> SLMap::GetCurrentRoomTiles(sf::Vector2f _initialPos)
{
	m_currentRoomTiles.clear();

	sf::Vector2i currentTile = GetTileID(_initialPos);
	CollisionTiles type = GetTileTypeCollision(currentTile);

	m_currentRoomTiles.push_back(currentTile);

	for (int i = 0; i < m_currentRoomTiles.size(); i++)
	{
		currentTile = m_currentRoomTiles[i];

		for (int j = -1; j <= 1; j++)
		{
			for (int k = -1; k <= 1; k++)
			{
				if (j == 0 || k == 0)
				{
					if (currentTile.x + j < m_height && currentTile.x + j >= 0
						&& currentTile.y + k < m_width && currentTile.y + k >= 0)
					{
						if (m_collisionMap[currentTile.x + j][currentTile.y + k] == type)
						{
							if (std::find(m_currentRoomTiles.begin(), m_currentRoomTiles.end(), currentTile + sf::Vector2i(j, k)) == m_currentRoomTiles.end())
							{
								m_currentRoomTiles.push_back(currentTile + sf::Vector2i(j, k));
							}
						}
					}
				}
			}
		}
	}

	return m_currentRoomTiles;
}

std::vector<sf::Vector2i> SLMap::GetCollidedTiles(sf::Vector2f _startingPos, sf::Vector2f _vector)
{
	std::vector<sf::Vector2i> collidedTiles;

	sf::Vector2i startingTile = GetTileID(_startingPos);
	sf::Vector2i endTile = GetTileID(_startingPos + _vector);

	sf::Vector2f dir;
	dir.x = (startingTile.x <= endTile.x) ? 1 : -1;
	dir.y = (startingTile.y <= endTile.y) ? 1 : -1;

	for (int i = startingTile.x; i != endTile.x + dir.x; i += dir.x)
	{
		for (int j = startingTile.y; j != endTile.y + dir.y; j += dir.y)
		{
			if (Collisions::IsCollidingRectSegment(GetTileBounds({ i, j }), _startingPos, _vector))
			{
				collidedTiles.push_back({ i, j });
			}
		}
	}

	return collidedTiles;
}

std::vector<int> SLMap::GetCollidedTilesType(sf::Vector2f _startingPos, sf::Vector2f _vector)
{
	std::vector<int> collidedTilesType;

	sf::Vector2i startingTile = GetTileID(_startingPos);
	sf::Vector2i endTile = GetTileID(_startingPos + _vector);

	sf::Vector2f dir;
	dir.x = (startingTile.x <= endTile.x) ? 1 : -1;
	dir.y = (startingTile.y <= endTile.y) ? 1 : -1;

	for (int i = startingTile.x; i != endTile.x + dir.x; i += dir.x)
	{
		for (int j = startingTile.y; j != endTile.y + dir.y; j += dir.y)
		{
			if (Collisions::IsCollidingRectSegment(GetTileBounds({ i, j }), _startingPos, _vector))
			{
				collidedTilesType.push_back((int)m_collisionMap[i][j]);
			}
		}
	}

	return collidedTilesType;
}