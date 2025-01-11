#ifndef MAPMANAGER_HPP
#define MAPMANAGER_HPP

#include "Common.h"

#define TILE_SIZE 32

struct mapSprite
{
	sf::Sprite p1;
	sf::Sprite p2;
	sf::Sprite p3;
	sf::Sprite p4;
	sf::Sprite p5;
	sf::Sprite p6;
	sf::Sprite p7;

	sf::Sprite topLeftSprite;
	sf::Sprite topSprite;
	sf::Sprite topRightSprite;
	sf::Sprite dotTopLeftSprite;
	sf::Sprite dotTopSprite;
	sf::Sprite dotTopRightSprite;
	sf::Sprite midLeftSprite;
	sf::Sprite midSprite;
	sf::Sprite midRightSprite;
	sf::Sprite dotMidLeftSprite;
	sf::Sprite dotMidRightSprite;
	sf::Sprite botLeftSprite;
	sf::Sprite botMidSprite;
	sf::Sprite botRightSprite;

	sf::Sprite breakSprite;
	
	sf::Sprite dotBotLeftSprite;
	sf::Sprite dotBotSprite;
	sf::Sprite dotBotRightSprite;
	sf::Sprite pointTopLeftSprite;
	sf::Sprite pointTopSprite;
	sf::Sprite pointTopRightSprite;
	sf::Sprite crossTopSprite;


	sf::Sprite pointMidLeftSprite;
	sf::Sprite pointMidRightSprite;
	sf::Sprite crossLeftSprite;
	sf::Sprite crossMidSprite;
	sf::Sprite crossRightSprite;
	sf::Sprite pointBotLeftSprite;
	sf::Sprite pointBotSprite;
	sf::Sprite pointBotRightSprite;
	sf::Sprite crossBotSprite;

	sf::Sprite badtopLeftSprite;
	sf::Sprite badtopSprite;
	sf::Sprite badtopRightSprite;
	sf::Sprite baddotTopLeftSprite;
	sf::Sprite baddotTopSprite;
	sf::Sprite baddotTopRightSprite;
	sf::Sprite badmidLeftSprite;
	sf::Sprite badmidSprite;
	sf::Sprite badmidRightSprite;
	sf::Sprite baddotMidLeftSprite;
	sf::Sprite baddotMidRightSprite;
	sf::Sprite badbotLeftSprite;
	sf::Sprite badbotMidSprite;
	sf::Sprite badbotRightSprite;
	sf::Sprite baddotBotLeftSprite;
	sf::Sprite baddotBotSprite;
	sf::Sprite baddotBotRightSprite;
	sf::Sprite badpointTopLeftSprite;
	sf::Sprite badpointTopSprite;
	sf::Sprite badpointTopRightSprite;
	sf::Sprite badcrossTopSprite;
	sf::Sprite badpointMidLeftSprite;
	sf::Sprite badpointMidRightSprite;
	sf::Sprite badcrossLeftSprite;
	sf::Sprite badcrossMidSprite;
	sf::Sprite badcrossRightSprite;
	sf::Sprite badpointBotLeftSprite;
	sf::Sprite badpointBotSprite;
	sf::Sprite badpointBotRightSprite;
	sf::Sprite badcrossBotSprite;

	sf::Sprite backtopLeftSprite;
	sf::Sprite backtopSprite;
	sf::Sprite backtopRightSprite;
	sf::Sprite backdotTopLeftSprite;
	sf::Sprite backdotTopSprite;
	sf::Sprite backdotTopRightSprite;
	sf::Sprite backmidLeftSprite;
	sf::Sprite backmidSprite;
	sf::Sprite backmidRightSprite;
	sf::Sprite backdotMidLeftSprite;
	sf::Sprite backdotMidRightSprite;
	sf::Sprite backbotLeftSprite;
	sf::Sprite backbotMidSprite;
	sf::Sprite backbotRightSprite;
	sf::Sprite backdotBotLeftSprite;
	sf::Sprite backdotBotSprite;
	sf::Sprite backdotBotRightSprite;
	sf::Sprite backpointTopLeftSprite;
	sf::Sprite backpointTopSprite;
	sf::Sprite backpointTopRightSprite;
	sf::Sprite backcrossTopSprite;
	sf::Sprite backpointMidLeftSprite;
	sf::Sprite backpointMidRightSprite;
	sf::Sprite backcrossLeftSprite;
	sf::Sprite backcrossMidSprite;
	sf::Sprite backcrossRightSprite;
	sf::Sprite backpointBotLeftSprite;
	sf::Sprite backpointBotSprite;
	sf::Sprite backpointBotRightSprite;
	sf::Sprite backcrossBotSprite;

	sf::Sprite picUp;
	sf::Sprite picDown;
	sf::Sprite picLeft;
	sf::Sprite picRight;

	sf::Sprite pilarSprite;
	sf::Sprite bossStatueSprite;
	sf::Sprite snakeStatueSprite;
	bool isWalking;
	sf::Vector2f pos;
};
enum TileSet
{
	NOTHING = -1,
	TOPLEFT = 0,
	TOP = 1,
	TOPRIGHT = 2,
	DOTTOPLEFT = 3,
	DOTTOP = 4,
	DOTTOPRIGHT = 5,
	MIDLEFT = 6,
	MID = 7,
	MIDRIGHT = 8,
	DOTMIDLEFT = 9,
	DOTRIGHT = 11,
	BOTLEFT = 12,
	BOT = 13,
	BOTRIGHT = 14,
	DOTBOTLEFT = 15,
	DOTBOT = 16,
	DOTBOTRIGHT = 17,
	POINTTOPLEFT = 18,
	POINTTOP = 19,
	POINTTOPRIGHT = 20,
	CROSSTOP = 22,
	POINTMIDLEFT = 24,
	POINTMIDRIGHT = 26,
	CROSSLEFT = 27,
	CROSSMID = 28,
	CROSSRIGHT = 29,
	POINTBOTLEFT = 30,
	POINTBOT = 31,
	POINTBOTRIGHT = 32,
	CROSSBOT = 34,
	START = 37,
	TRAP = 18,
	RESET_JUMP = 48
};

enum badTileSet
{
	BADTOPLEFT = 0,
	BADTOP = 1,
	BADTOPRIGHT = 2,
	BADDOTTOPLEFT = 3,
	BADDOTTOP = 4,
	BADDOTTOPRIGHT = 5,
	BADMIDLEFT = 6,
	BADMID = 7,
	BADMIDRIGHT = 8,
	BADDOTMIDLEFT = 9,
	BADDOTRIGHT = 11,
	BADBOTLEFT = 12,
	BADBOT = 13,
	BADBOTRIGHT = 14,
	BADDOTBOTLEFT = 15,
	BADDOTBOT = 16,
	BADDOTBOTRIGHT = 17,
	BADPOINTTOPLEFT = 18,
	BADPOINTTOP = 19,
	BADPOINTTOPRIGHT = 20,
	BADCROSSTOP = 22,
	BADPOINTMIDLEFT = 24,
	BADPOINTMIDRIGHT = 26,
	BADCROSSLEFT = 27,
	BADCROSSMID = 28,
	BADCROSSRIGHT = 29,
	BADPOINTBOTLEFT = 30,
	BADPOINTBOT = 31,
	BADPOINTBOTRIGHT = 32,
	BADCROSSBOT = 34,
};

enum backTileSet
{
	BACKTOPLEFT = 0,
	BACKTOP = 1,
	BACKTOPRIGHT = 2,
	BACKDOTTOPLEFT = 3,
	BACKDOTTOP = 4,
	BACKDOTTOPRIGHT = 5,
	BACKMIDLEFT = 6,
	BACKMID = 7,
	BACKMIDRIGHT = 8,
	BACKDOTMIDLEFT = 9,
	BACKDOTRIGHT = 11,
	BACKBOTLEFT = 12,
	BACKBOT = 13,
	BACKBOTRIGHT = 14,
	BACKDOTBOTLEFT = 15,
	BACKDOTBOT = 16,
	BACKDOTBOTRIGHT = 17,
	BACKPOINTTOPLEFT = 18,
	BACKPOINTTOP = 19,
	BACKPOINTTOPRIGHT = 20,
	BACKCROSSTOP = 22,
	BACKPOINTMIDLEFT = 24,
	BACKPOINTMIDRIGHT = 26,
	BACKCROSSLEFT = 27,
	BACKCROSSMID = 28,
	BACKCROSSRIGHT = 29,
	BACKPOINTBOTLEFT = 30,
	BACKPOINTBOT = 31,
	BACKPOINTBOTRIGHT = 32,
	BACKCROSSBOT = 34,
};

enum picTileset
{
	PICUP,
	PICRIGHT,
	PICLEFT,
	PICDOWN
};
enum AssetTileset
{
	PILARS,
	BOSSSTATUE,
	SNAKESTATUE
};
enum BreakTileset
{
	BROKEN = -1,
	BREAK
};

typedef std::vector<std::vector<TileSet>> Map;
typedef std::vector<std::vector<TileSet>> badMap;
typedef std::vector<std::vector<picTileset>> picMap;
typedef std::vector<std::vector<backTileSet>> backMap;
typedef std::vector<std::vector<AssetTileset>> AssetMap;
typedef std::vector<std::vector<BreakTileset>> BreakMap;

void InitMap(mapSprite& mapSprite, sf::Vector2f camPos);
Map ReadCSV(std::string _fileName);
badMap ReadBadCSV(std::string _fileName);
backMap ReadBackCSV(std::string _fileName);
picMap ReadPicCSV(std::string _fileName);
AssetMap ReadAssetCSV(std::string _fileName);
BreakMap ReadBreakCSV(std::string _fileName);
void DrawParalax(mapSprite map, sf::RenderWindow& _window);
void UpdateMap(mapSprite& map, sf::Vector2f camPos, sf::Vector2f playerPos, float dt);
void UpdateInfinityMap(mapSprite& map, sf::Vector2f camPos, sf::Vector2f playerPos, float dt);
void DrawMap(Map _map, sf::RenderWindow& _window, mapSprite map);
void DrawBackMap(backMap _map, sf::RenderWindow& _window, mapSprite map);
void DrawAssetMap(AssetMap _map, sf::RenderWindow& _window, mapSprite map);
void DrawBadMap(badMap _map, sf::RenderWindow& _window, mapSprite map);
void DrawPicMap(picMap _map, sf::RenderWindow& _window, mapSprite map);
void DrawBreakMap(BreakMap _map, sf::RenderWindow& _window, mapSprite map);
sf::Vector2f GetPosStart(Map& _map);
//void readRespawnPoint(Map map, mapSprite mapSprite);

#endif // !MAPMANAGER_HPP