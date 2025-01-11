#ifndef ANIMTEXT__H
#define ANIMTEXT__H

#include "common.h"
#include <fstream>
#include <sstream>
#include <random>
#include <chrono>
#include <thread>

#define WORD_WAIT 0.1
#define MINIMAL_MULTIPLICATOR 4
#define SKIP_MULTIPLICATOR 80

#define EPILEPTIC_RGB 0.05

enum ColorIndex
{
	WHITE,
	MULTICOLORE,
	BLUE,
	RED,
	GREEN,
	PINK,
	VIOLET,
	ORANGE,
	YELLOW,
	BLACK
};

struct EnableEffect
{
	bool Shake = false;
	bool Color = false;
	char colorLetter;
	char colorLetterOutline;
};

enum Effect
{
	SHAKE,
	COLOR
};
struct Caracters
{
	char letter;
	bool iscolored = false;
	bool isshaked = false;
	bool returnLine = false;
	ColorIndex colorIndex;
	ColorIndex outlineColor;
};

struct Text
{
	sf::Text text;
	bool colorEffect = false;
	bool shakeEffect = false;
	bool returnLine = false;
	ColorIndex colorIndex;
	ColorIndex outlineColor;
	sf::Vector2f pos;
	sf::Vector2f initPos;//sert au shake
	float alpha;
	float amplitude = 1;
	float frequency = 1.f;
	float phase = 0.0f;
};


struct Limit
{
	int begin;
	int end;
	int effectIndex;
};

struct effectData
{
	Limit limit;
	EnableEffect sfx;
};

class AnimText
{
public:
	std::vector<Caracters> mots;
	std::vector<Text> dialogue;
	std::vector<effectData> textEffectData;
	sf::Clock shakeClock;
	sf::Font font;
	int currentLetter = 0;
	float speed = 100;
	sf::Vector2f initPos;
	AnimText();
	~AnimText();
	void Init(std::string _file, sf::Vector2f _pos, int _line);
	void Update(float _dt);
	void Draw(sf::RenderWindow& _window);
	//////////////////////////////////////////////////
	bool allDisplay;
	int multiplicator = MINIMAL_MULTIPLICATOR;
	sf::Clock wordStopClock;

	void SetCharacterSize(int _size) { CharacterSize = _size; }
	int GetCharacterSize()  const { return CharacterSize; }

	void SetTextLimit(int _size) { textLenght = _size; }
	int GetTextLimit() const { return textLenght; }
private:
	int lastReturn = 0;//variable pour savoir qu'elle est le dernier retour chariot
	sf::Text testString;//text servent a tester la taille
	int offsetSize = 0;//variable servant a comparer la taille en mettant un offset 
	int textLenght = 500; //limite de taille du texte en longeur
	int CharacterSize = 48;

	void UpdateTextColor();
	void DisplayText(sf::RenderWindow& _window);
	void openFile(std::string _file, sf::Vector2f _pos, int _line);
	void initLetter();
	void TextEffect(float _dt);
	void DialogueApparition(float _dt);
	void StringAnalyse();
	void foundWord();
	void  replaceLetter(std::vector<effectData> _textEffectData);
	void findEnd(int& _end, int _beginOffset, std::string _text);
	void foundBegin(int& _begin, int _beginOffset, std::string _text);
};
#endif