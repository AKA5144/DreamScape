#include "MapManagerNeyl.hpp"


void InitMap(mapSprite& map, sf::Vector2f camPos)
{
	map.isWalking = false;
	map.p1 = LoadSprite("Assets/Platformer/Parallaxe/p1.png", false);
	map.p2 = LoadSprite("Assets/Platformer/Parallaxe/p2.png", false);
	map.p3 = LoadSprite("Assets/Platformer/Parallaxe/p3.png", false);
	map.p4 = LoadSprite("Assets/Platformer/Parallaxe/p4.png", false);
	map.p5 = LoadSprite("Assets/Platformer/Parallaxe/p5.png", false);
	map.p6 = LoadSprite("Assets/Platformer/Parallaxe/p6.png", false);
	map.p7 = LoadSprite("Assets/Platformer/Parallaxe/p7.png", false);

	map.topLeftSprite = LoadSprite("Assets/Platformer/Tiles/tileset/topLeftSprite.png", false);
	map.topSprite = LoadSprite("Assets/Platformer/Tiles/tileset/topSprite.png", false);
	map.topRightSprite = LoadSprite("Assets/Platformer/Tiles/tileset/topRightSprite.png", false);
	map.dotTopLeftSprite = LoadSprite("Assets/Platformer/Tiles/tileset/dotTopLeftSprite.png", false);
	map.dotTopSprite = LoadSprite("Assets/Platformer/Tiles/tileset/dotTopSprite.png", false);
	map.dotTopRightSprite = LoadSprite("Assets/Platformer/Tiles/tileset/dotTopRightSprite.png", false);
	map.midLeftSprite = LoadSprite("Assets/Platformer/Tiles/tileset/midLeftSprite.png", false);
	map.midSprite = LoadSprite("Assets/Platformer/Tiles/tileset/midSprite.png", false);
	map.midRightSprite = LoadSprite("Assets/Platformer/Tiles/tileset/midRightSprite.png", false);
	map.dotMidLeftSprite = LoadSprite("Assets/Platformer/Tiles/tileset/dotMidLeftSprite.png", false);
	map.dotMidRightSprite = LoadSprite("Assets/Platformer/Tiles/tileset/dotMidRightSprite.png", false);
	map.botLeftSprite = LoadSprite("Assets/Platformer/Tiles/tileset/botLeftSprite.png", false);
	map.botMidSprite = LoadSprite("Assets/Platformer/Tiles/tileset/botMidSprite.png", false);
	map.botRightSprite = LoadSprite("Assets/Platformer/Tiles/tileset/botRightSprite.png", false);
	map.dotBotLeftSprite = LoadSprite("Assets/Platformer/Tiles/tileset/dotBotLeftSprite.png", false);
	map.dotBotSprite = LoadSprite("Assets/Platformer/Tiles/tileset/dotBotSprite.png", false);
	map.dotBotRightSprite = LoadSprite("Assets/Platformer/Tiles/tileset/dotBotRightSprite.png", false);
	map.pointTopLeftSprite = LoadSprite("Assets/Platformer/Tiles/tileset/pointTopLeftSprite.png", false);
	map.pointTopSprite = LoadSprite("Assets/Platformer/Tiles/tileset/pointTopSprite.png", false);
	map.pointTopRightSprite = LoadSprite("Assets/Platformer/Tiles/tileset/pointTopRightSprite.png", false);
	map.crossTopSprite = LoadSprite("Assets/Platformer/Tiles/tileset/crossTopSprite.png", false);
	map.pointMidLeftSprite = LoadSprite("Assets/Platformer/Tiles/tileset/pointMidLeftSprite.png", false);
	map.pointMidRightSprite = LoadSprite("Assets/Platformer/Tiles/tileset/pointMidRightSprite.png", false);
	map.crossLeftSprite = LoadSprite("Assets/Platformer/Tiles/tileset/crossLeftSprite.png", false);
	map.crossMidSprite = LoadSprite("Assets/Platformer/Tiles/tileset/crossMidSprite.png", false);
	map.crossRightSprite = LoadSprite("Assets/Platformer/Tiles/tileset/crossRightSprite.png", false);
	map.pointBotLeftSprite = LoadSprite("Assets/Platformer/Tiles/tileset/pointBotLeftSprite.png", false);
	map.pointBotSprite = LoadSprite("Assets/Platformer/Tiles/tileset/pointBotSprite.png", false);
	map.pointBotRightSprite = LoadSprite("Assets/Platformer/Tiles/tileset/pointBotRightSprite.png", false);
	map.crossBotSprite = LoadSprite("Assets/Platformer/Tiles/tileset/crossBotSprite.png", false);

	map.badtopLeftSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/badtopLeftSprite.png", false);
	map.badtopSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/badtopSprite.png", false);
	map.badtopRightSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/badtopRightSprite.png", false);
	map.baddotTopLeftSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/baddotTopLeftSprite.png", false);
	map.baddotTopSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/baddotTopSprite.png", false);
	map.baddotTopRightSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/baddotTopRightSprite.png", false);
	map.badmidLeftSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/badmidLeftSprite.png", false);
	map.badmidSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/badmidSprite.png", false);
	map.badmidRightSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/badmidRightSprite.png", false);
	map.baddotMidLeftSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/baddotMidLeftSprite.png", false);
	map.baddotMidRightSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/baddotMidRightSprite.png", false);
	map.badbotLeftSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/badbotLeftSprite.png", false);
	map.badbotMidSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/badbotMidSprite.png", false);
	map.badbotRightSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/badbotRightSprite.png", false);
	map.baddotBotLeftSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/baddotBotLeftSprite.png", false);
	map.baddotBotSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/baddotBotSprite.png", false);
	map.baddotBotRightSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/baddotBotRightSprite.png", false);
	map.badpointTopLeftSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/badpointTopLeftSprite.png", false);
	map.badpointTopSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/badpointTopSprite.png", false);
	map.badpointTopRightSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/badpointTopRightSprite.png", false);
	map.badcrossTopSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/badcrossTopSprite.png", false);
	map.badpointMidLeftSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/badpointMidLeftSprite.png", false);
	map.badpointMidRightSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/badpointMidRightSprite.png", false);
	map.badcrossLeftSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/badcrossLeftSprite.png", false);
	map.badcrossMidSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/badcrossMidSprite.png", false);
	map.badcrossRightSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/badcrossRightSprite.png", false);
	map.badpointBotLeftSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/badpointBotLeftSprite.png", false);
	map.badpointBotSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/badpointBotSprite.png", false);
	map.badpointBotRightSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/badpointBotRightSprite.png", false);
	map.badcrossBotSprite = LoadSprite("Assets/Platformer/Tiles/badTileset/badcrossBotSprite.png", false);

	map.backtopLeftSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backtopLeftSprite.png", false);
	map.backtopSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backtopSprite.png", false);
	map.backtopRightSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backtopRightSprite.png", false);
	map.backdotTopLeftSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backdotTopLeftSprite.png", false);
	map.backdotTopSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backdotTopSprite.png", false);
	map.backdotTopRightSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backdotTopRightSprite.png", false);
	map.backmidLeftSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backmidLeftSprite.png", false);
	map.backmidSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backmidSprite.png", false);
	map.backmidRightSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backmidRightSprite.png", false);
	map.backdotMidLeftSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backdotMidLeftSprite.png", false);
	map.backdotMidRightSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backdotMidRightSprite.png", false);
	map.backbotLeftSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backbotLeftSprite.png", false);
	map.backbotMidSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backbotMidSprite.png", false);
	map.backbotRightSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backbotRightSprite.png", false);
	map.backdotBotLeftSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backdotBotLeftSprite.png", false);
	map.backdotBotSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backdotBotSprite.png", false);
	map.backdotBotRightSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backdotBotRightSprite.png", false);
	map.backpointTopLeftSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backpointTopLeftSprite.png", false);
	map.backpointTopSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backpointTopSprite.png", false);
	map.backpointTopRightSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backpointTopRightSprite.png", false);
	map.backcrossTopSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backcrossTopSprite.png", false);
	map.backpointMidLeftSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backpointMidLeftSprite.png", false);
	map.backpointMidRightSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backpointMidRightSprite.png", false);
	map.backcrossLeftSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backcrossLeftSprite.png", false);
	map.backcrossMidSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backcrossMidSprite.png", false);
	map.backcrossRightSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backcrossRightSprite.png", false);
	map.backpointBotLeftSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backpointBotLeftSprite.png", false);
	map.backpointBotSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backpointBotSprite.png", false);
	map.backpointBotRightSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backpointBotRightSprite.png", false);
	map.backcrossBotSprite = LoadSprite("Assets/Platformer/Tiles/backTileset/backcrossBotSprite.png", false);

	map.breakSprite = LoadSprite("Assets/Platformer/Tiles/break.png", false);

	map.picUp = LoadSprite("Assets/Platformer/Tiles/picTileset/picUp.png", false);
	map.picDown = LoadSprite("Assets/Platformer/Tiles/picTileset/picDown.png", false);
	map.picRight = LoadSprite("Assets/Platformer/Tiles/picTileset/picRight.png", false);
	map.picLeft = LoadSprite("Assets/Platformer/Tiles/picTileset/picLeft.png", false);

	map.pilarSprite = LoadSprite("Assets/Platformer/Tiles/AssetTileset/PilarSprite.png", false);
	map.bossStatueSprite = LoadSprite("Assets/Platformer/Tiles/AssetTileset/bossStatueSprite.png", false);
	map.snakeStatueSprite = LoadSprite("Assets/Platformer/Tiles/AssetTileset/snakeStatueSprite.png", false);
	map.pos.x = -32 * 4;
}

Map ReadCSV(const std::string _fileName)
{
	Map content;
	std::vector<TileSet> row;
	std::string line;
	std::string word;
	std::fstream file(_fileName, std::ios::in);
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			row.clear();

			std::stringstream str(line);

			while (getline(str, word, ','))
			{
				row.push_back((TileSet)std::stoi(word));
			}
			content.push_back(row);
		}
	}
	else
	{
		std::cout << "Could not open the file" << std::endl;
	}

	return content;
}
//void readRespawnPoint(Map map, mapSprite mapSprite)
//{
//	for (int i = 0; i < map.size(); i++)
//	{
//		for (int j = 0; j < map[i].size(); j++)
//		{
//			if (map[i][j] == RESPAWN_POINT)
//				mapSprite.respawnPoint.push_back(sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE));
//		}
//	}
//}
backMap ReadBackCSV(std::string _fileName)
{
	backMap content;
	std::vector<backTileSet> row;
	std::string line;
	std::string word;

	std::fstream file(_fileName, std::ios::in);
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			row.clear();

			std::stringstream str(line);

			while (getline(str, word, ','))
			{
				row.push_back((backTileSet)std::stoi(word));
			}
			content.push_back(row);
		}
	}
	else
	{
		std::cout << "Could not open the file" << std::endl;
	}

	return content;
}
badMap ReadBadCSV(const std::string _fileName)
{
	badMap content;
	std::vector<TileSet> row;
	std::string line;
	std::string word;

	std::fstream file(_fileName, std::ios::in);
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			row.clear();

			std::stringstream str(line);

			while (getline(str, word, ','))
			{
				row.push_back((TileSet)std::stoi(word));
			}
			content.push_back(row);
		}
	}
	else
	{
		std::cout << "Could not open the file" << std::endl;
	}

	return content;
}
picMap ReadPicCSV(const std::string _fileName)
{
	picMap content;
	std::vector<picTileset> row;
	std::string line;
	std::string word;

	std::fstream file(_fileName, std::ios::in);
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			row.clear();

			std::stringstream str(line);

			while (getline(str, word, ','))
			{
				row.push_back((picTileset)std::stoi(word));
			}
			content.push_back(row);
		}
	}
	else
	{
		std::cout << "Could not open the file" << std::endl;
	}

	return content;
}

AssetMap ReadAssetCSV(std::string _fileName)
{
	AssetMap content;
	std::vector<AssetTileset> row;
	std::string line;
	std::string word;

	std::fstream file(_fileName, std::ios::in);
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			row.clear();

			std::stringstream str(line);

			while (getline(str, word, ','))
			{
				row.push_back((AssetTileset)std::stoi(word));
			}
			content.push_back(row);
		}
	}
	else
	{
		std::cout << "Could not open the file" << std::endl;
	}

	return content;
}

BreakMap ReadBreakCSV(std::string _fileName)
{
	BreakMap content;
	std::vector<BreakTileset> row;
	std::string line;
	std::string word;

	std::fstream file(_fileName, std::ios::in);
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			row.clear();

			std::stringstream str(line);

			while (getline(str, word, ','))
			{
				row.push_back((BreakTileset)std::stoi(word));
			}
			content.push_back(row);
		}
	}
	else
	{
		std::cout << "Could not open the file" << std::endl;
	}

	return content;
}

void UpdateMap(mapSprite& map, sf::Vector2f camPos, sf::Vector2f playerPos, float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 50 || sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -50)
	{
		map.isWalking = true;
	}
	else
	{
		map.isWalking = false;
	}
	if (map.isWalking)
		map.pos.x += 2 * dt;

	map.pos.y = camPos.y;

}
void UpdateInfinityMap(mapSprite& map, sf::Vector2f camPos, sf::Vector2f playerPos, float dt)
{

	map.pos.x += 1 * dt;
	map.pos.y = camPos.y;
}
void DrawParalax(mapSprite map, sf::RenderWindow& _window)
{
	for (int i = 0; i < 60; i++)
	{
		BlitSprite(map.p1, sf::Vector2f((0 + map.pos.x * (3.f)) + 624 * i, map.pos.y - 180), _window, { 1,1 }, 0, sf::Color::White);
	}

	for (int i = 0; i < 60; i++)
	{
		BlitSprite(map.p3, sf::Vector2f((0 + map.pos.x * (5.f)) + 624 * i, map.pos.y - 180), _window, { 1,1 }, 0, sf::Color::White);
	}
	for (int i = 0; i < 60; i++)
	{
		BlitSprite(map.p4, sf::Vector2f((0 + map.pos.x * (7)) + 624 * i, map.pos.y - 180), _window, { 1,1 }, 0, sf::Color::White);
	}
	for (int i = 0; i < 60; i++)
	{
		BlitSprite(map.p5, sf::Vector2f((0 + map.pos.x * (9.f)) + 624 * i, map.pos.y - 180), _window, { 1,1 }, 0, sf::Color::White);
	}
	for (int i = 0; i < 60; i++)
	{
		BlitSprite(map.p6, sf::Vector2f((0 + map.pos.x * (11)) + 1280 * i, map.pos.y - 180), _window, { 1,1 }, 0, sf::Color::White);
	}
	for (int i = 0; i < 60; i++)
	{
		BlitSprite(map.p7, sf::Vector2f((0 + map.pos.x * (13)) + map.p7.getGlobalBounds().width * i, map.pos.y - 180), _window, { 1,1 }, 0, sf::Color::White);
	}
	for (int i = 0; i < 60; i++)
	{
		BlitSprite(map.p2, sf::Vector2f((0 + map.pos.x * (14)) + 624 * i, map.pos.y - 180), _window, { 1,1 }, 0, sf::Color::White);
	}
}

void DrawBackMap(backMap _map, sf::RenderWindow& _window, mapSprite map)
{
	for (int i = 0; i < _map.size(); i++)
	{
		for (int j = 0; j < _map[i].size(); j++)
		{
			switch (_map[i][j])
			{
			case BACKTOPLEFT:
				BlitSprite(map.backtopLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKTOP:
				BlitSprite(map.backtopSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKTOPRIGHT:
				BlitSprite(map.backtopRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKDOTTOPLEFT:
				BlitSprite(map.backdotTopLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKDOTTOP:
				BlitSprite(map.backdotTopSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKDOTTOPRIGHT:
				BlitSprite(map.backdotTopRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKMIDLEFT:
				BlitSprite(map.backmidLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKMID:
				BlitSprite(map.backmidSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKMIDRIGHT:
				BlitSprite(map.backmidRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKDOTMIDLEFT:
				BlitSprite(map.backdotMidLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKDOTRIGHT:
				BlitSprite(map.backdotMidRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKBOTLEFT:
				BlitSprite(map.backbotLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKBOT:
				BlitSprite(map.backbotMidSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKBOTRIGHT:
				BlitSprite(map.backbotRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKDOTBOTLEFT:
				BlitSprite(map.backdotBotLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKDOTBOT:
				BlitSprite(map.backdotBotSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKDOTBOTRIGHT:
				BlitSprite(map.backdotBotRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKPOINTTOPLEFT:
				BlitSprite(map.backpointTopLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKPOINTTOP:
				BlitSprite(map.backpointTopSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKPOINTTOPRIGHT:
				BlitSprite(map.backpointTopRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKCROSSTOP:
				BlitSprite(map.backcrossTopSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKPOINTMIDLEFT:
				BlitSprite(map.backpointMidLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKPOINTMIDRIGHT:
				BlitSprite(map.backpointMidRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKCROSSLEFT:
				BlitSprite(map.backcrossLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKCROSSMID:
				BlitSprite(map.backcrossMidSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKCROSSRIGHT:
				BlitSprite(map.backcrossRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKPOINTBOTLEFT:
				BlitSprite(map.backpointBotLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKPOINTBOT:
				BlitSprite(map.backpointBotSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKPOINTBOTRIGHT:
				BlitSprite(map.backpointBotRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BACKCROSSBOT:
				BlitSprite(map.backcrossBotSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			}
		}
	}
}

void DrawAssetMap(AssetMap _map, sf::RenderWindow& _window, mapSprite map)
{
	for (int i = 0; i < _map.size(); i++)
	{
		for (int j = 0; j < _map[i].size(); j++)
		{
			switch (_map[i][j])
			{
			case PILARS:
				BlitSprite(map.pilarSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BOSSSTATUE:
				BlitSprite(map.bossStatueSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case SNAKESTATUE:
				BlitSprite(map.snakeStatueSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			}
		}
	}
}

void DrawMap(Map _map, sf::RenderWindow& _window, mapSprite map)
{
	for (int i = 0; i < _map.size(); i++)
	{
		for (int j = 0; j < _map[i].size(); j++)
		{
			switch (_map[i][j])
			{
			case TOPLEFT:
				BlitSprite(map.topLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case TOP:
				BlitSprite(map.topSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case TOPRIGHT:
				BlitSprite(map.topRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case DOTTOPLEFT:
				BlitSprite(map.dotTopLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case DOTTOP:
				BlitSprite(map.dotTopSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case DOTTOPRIGHT:
				BlitSprite(map.dotTopRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case MIDLEFT:
				BlitSprite(map.midLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case MID:
				BlitSprite(map.midSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case MIDRIGHT:
				BlitSprite(map.midRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case DOTMIDLEFT:
				BlitSprite(map.dotMidLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case DOTRIGHT:
				BlitSprite(map.dotMidRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BOTLEFT:
				BlitSprite(map.botLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BOT:
				BlitSprite(map.botMidSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BOTRIGHT:
				BlitSprite(map.botRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case DOTBOTLEFT:
				BlitSprite(map.dotBotLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case DOTBOT:
				BlitSprite(map.dotBotSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case DOTBOTRIGHT:
				BlitSprite(map.dotBotRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case POINTTOPLEFT:
				BlitSprite(map.pointTopLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case POINTTOP:
				BlitSprite(map.pointTopSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case POINTTOPRIGHT:
				BlitSprite(map.pointTopRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case CROSSTOP:
				BlitSprite(map.crossTopSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case POINTMIDLEFT:
				BlitSprite(map.pointMidLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case POINTMIDRIGHT:
				BlitSprite(map.pointMidRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case CROSSLEFT:
				BlitSprite(map.crossLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case CROSSMID:
				BlitSprite(map.crossMidSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case CROSSRIGHT:
				BlitSprite(map.crossRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case POINTBOTLEFT:
				BlitSprite(map.pointBotLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case POINTBOT:
				BlitSprite(map.pointBotSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case POINTBOTRIGHT:
				BlitSprite(map.pointBotRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case CROSSBOT:
				BlitSprite(map.crossBotSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			}
		}
	}
}

void DrawPicMap(picMap _map, sf::RenderWindow& _window, mapSprite map)
{
	for (int i = 0; i < _map.size(); i++)
	{
		for (int j = 0; j < _map[i].size(); j++)
		{
			switch (_map[i][j])
			{
			case PICUP:
				BlitSprite(map.picUp, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case PICRIGHT:
				BlitSprite(map.picRight, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case PICLEFT:
				BlitSprite(map.picLeft, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case PICDOWN:
				BlitSprite(map.picDown, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
			}
		}
	}
}

void DrawBreakMap(BreakMap _map, sf::RenderWindow& _window, mapSprite map)
{
	for (int i = 0; i < _map.size(); i++)
	{
		for (int j = 0; j < _map[i].size(); j++)
		{
			switch (_map[i][j])
			{
			case BREAK:
				BlitSprite(map.breakSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			}
		}
	}
}

void DrawBadMap(const badMap _map, sf::RenderWindow& _window, mapSprite map)
{
	for (int i = 0; i < _map.size(); i++)
	{
		for (int j = 0; j < _map[i].size(); j++)
		{
			switch (_map[i][j])
			{
			case BADTOPLEFT:
				BlitSprite(map.badtopLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADTOP:
				BlitSprite(map.badtopSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADTOPRIGHT:
				BlitSprite(map.badtopRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADDOTTOPLEFT:
				BlitSprite(map.baddotTopLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADDOTTOP:
				BlitSprite(map.baddotTopSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADDOTTOPRIGHT:
				BlitSprite(map.baddotTopRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADMIDLEFT:
				BlitSprite(map.badmidLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADMID:
				BlitSprite(map.badmidSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADMIDRIGHT:
				BlitSprite(map.badmidRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADDOTMIDLEFT:
				BlitSprite(map.baddotMidLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADDOTRIGHT:
				BlitSprite(map.baddotMidRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADBOTLEFT:
				BlitSprite(map.badbotLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADBOT:
				BlitSprite(map.badbotMidSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADBOTRIGHT:
				BlitSprite(map.badbotRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADDOTBOTLEFT:
				BlitSprite(map.baddotBotLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADDOTBOT:
				BlitSprite(map.baddotBotSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADDOTBOTRIGHT:
				BlitSprite(map.baddotBotRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADPOINTTOPLEFT:
				BlitSprite(map.badpointTopLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADPOINTTOP:
				BlitSprite(map.badpointTopSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADPOINTTOPRIGHT:
				BlitSprite(map.badpointTopRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADCROSSTOP:
				BlitSprite(map.badcrossTopSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADPOINTMIDLEFT:
				BlitSprite(map.badpointMidLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADPOINTMIDRIGHT:
				BlitSprite(map.badpointMidRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADCROSSLEFT:
				BlitSprite(map.badcrossLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADCROSSMID:
				BlitSprite(map.badcrossMidSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADCROSSRIGHT:
				BlitSprite(map.badcrossRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADPOINTBOTLEFT:
				BlitSprite(map.badpointBotLeftSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADPOINTBOT:
				BlitSprite(map.badpointBotSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADPOINTBOTRIGHT:
				BlitSprite(map.badpointBotRightSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			case BADCROSSBOT:
				BlitSprite(map.badcrossBotSprite, { j * (float)TILE_SIZE, i * (float)TILE_SIZE }, _window);
				break;
			}
		}
	}
}



sf::Vector2f GetPosStart(const Map& _map)
{
	for (int i = 0; i < _map.size(); i++)
	{
		for (int j = 0; j < _map[i].size(); j++)
		{
			switch (_map[i][j])
			{
			case START:
				return sf::Vector2f(j * TILE_SIZE, SCREEN_HEIGHT - (_map.size() - i) * TILE_SIZE);
				break;
			default:
				break;
			}
		}
	}
}