#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <time.h>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <fstream>
#include <functional>

#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/freeglut.h>
#include <GL/freeglut.h>
#include "SFML/OpenGL.hpp"

#include "Debug.h"
#include "CreaMaths.h"

// Limites de l'écran
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

enum class ControllerButton
{
	A = 0,
	B = 1,
	X = 2,
	Y = 3,
	LB = 4,
	RB = 5,
	SELECT = 6,
	START = 7,
	L3 = 8,
	R3 = 9,
	UNKNOWN = 10
};

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum MenuStateEnum
{
	INTRO,
	MAINMENU,
	GAME,
	SETTINGS,
	CONTROLS,
	SOUND,
	VIDEO,
	CREDITS
};

enum ControlKeys
{
	KEYUP,
	KEYDOWN,
	KEYLEFT,
	KEYRIGHT,
	KEYABILITY1,
	KEYABILITY2
};

enum Config
{
	KEYBOARD,
	CONTROLLER
};

// Prototypes de fonctions
sf::Sound LoadSound(std::string file);
sf::Sprite LoadSprite(std::string _path, bool _centered);
sf::Text LoadText(const std::string _fontPath, sf::String _string, float _characterSize, sf::Vector2f _pos, sf::Color _color = sf::Color::White, bool _isCentered = false);
void BlitSprite(sf::Sprite _sprite, sf::Vector2f _pos, sf::RenderWindow& _window, sf::Vector2f _scale = { 1.0,1.0 }, float _rotation = 0, sf::Color _color = sf::Color::White);
void BlitSprite(sf::Sprite _sprite, sf::Vector2f _pos, sf::RenderTexture& _window, sf::Vector2f _scale = { 1.0,1.0 }, float _rotation = 0, sf::Color _color = sf::Color::White);
void BlitSpriteAdd(sf::Sprite _sprite, sf::Vector2f _pos, sf::RenderWindow& _window, sf::Vector2f _scale, float _rotation, sf::Color _color);
void DrawPixel(sf::Image& _image, int _posX, int _posY, sf::Color _color);
template <typename T>
const bool IsInVector(T _element, std::vector<T> _vector) { return std::find(_vector.begin(), _vector.end(), _element) != _vector.end(); }

sf::Vector2f CenterPos(std::string _sNom);
#endif