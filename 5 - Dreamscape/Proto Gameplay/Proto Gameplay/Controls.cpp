#include "Controls.h"
#include "Player.h"
#include "MenuData.h"


void InitControls(MenuData* _menuData, Player& _player, ControlsData m_controls)
{

	for (int i = 0; i < 106; i++)
	{
		std::string temp = "Assets/Menu/Controls/Keyboard/" + std::to_string(i) + ".png";
		_menuData->keyTex[i].loadFromFile(temp);
	}
	for (int i = 0; i < 6; i++)
	{
		_menuData->keyText[i].setFont(_menuData->keyFont);
		_menuData->keyText[i].setPosition({ ((float)_menuData->windowSize[_menuData->resolutionCursor].x / 8) * 6 - 100,400.f + 40.f * i });
		_menuData->keyText[i].setString(KeyString[m_controls.keyBinding[i]]);
		_menuData->keyText[i].setCharacterSize(24);
		_menuData->keyText[i].setFillColor(sf::Color::White);

		_menuData->keySprite[i].setTexture(_menuData->keyTex[(int)m_controls.keyBinding[i]]);
		_menuData->keySprite[i].setScale({ 3.f,3.f });
		_menuData->keySprite[i].setPosition({ (((float)_menuData->windowSize[_menuData->resolutionCursor].x / 8) * 6 - 100) - _menuData->keySprite[i].getGlobalBounds().width / 2,400.f + 40.f * i });

		_menuData->controlsText[i].setFont(_menuData->keyFont);
		_menuData->controlsText[i].setOutlineColor(sf::Color{ 1,55,116 });
		_menuData->controlsText[i].setOutlineThickness(3);
		_menuData->controlsText[i].setPosition({ ((float)_menuData->windowSize[_menuData->resolutionCursor].x / 8) * 3,400.f + 40.f * i });
		_menuData->controlsText[i].setCharacterSize(24);
		_menuData->controlsText[i].setFillColor(sf::Color::White);
	}
	for (int i = 0; i < 2; i++)
	{
		_menuData->joystickText[i].setFont(_menuData->keyFont);
		_menuData->joystickSprite[i].setScale({ 2.f,2.f });
		_menuData->joystickText[i].setPosition({ ((float)_menuData->windowSize[_menuData->resolutionCursor].x / 8) * 6 + 100,400.f + 40.f * (i + 4) });
		_menuData->joystickSprite[i].setPosition({ ((float)_menuData->windowSize[_menuData->resolutionCursor].x / 8) * 6 + 100,400.f + 40.f * (i + 4) });
		_menuData->joystickText[i].setString(ButtonString[(unsigned int)m_controls.controllerBinding[i]]);
		_menuData->joystickText[i].setCharacterSize(24);
		_menuData->joystickText[i].setFillColor(sf::Color::White);
	}
	_menuData->controlsText[0].setString("Up : ");
	_menuData->controlsText[1].setString("Down : ");
	_menuData->controlsText[2].setString("Left : ");
	_menuData->controlsText[3].setString("Right : ");
	_menuData->controlsText[4].setString("Ability 1 : ");
	_menuData->controlsText[5].setString("Ability 2 : ");
	_menuData->controlMode = KEYBOARD;


}

void ControlsUpdate(MenuData* _menuData, float _dt, Player& _player, ControlsData*& m_controls, Config config)
{

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) && _menuData->mainTimer == 0.f) {
		_menuData->timerControl[0] = 2.f;
		_menuData->controlMode = KEYBOARD;
		_menuData->choosingControl = true;
	}
	if ((sf::Joystick::isButtonPressed(0, (unsigned int)ControllerButton::START)) && _menuData->mainTimer == 0.f)
	{
		_menuData->timerControl[0] = 2.f;
		_menuData->controlMode = CONTROLLER;
	}

	if (_menuData->menuCursorJoystick < 0)
	{
		_menuData->menuCursorJoystick = 5;
	}

	if (_menuData->menuCursorJoystick > 5)
	{
		_menuData->menuCursorJoystick = 0;
	}

	if (_menuData->menuCursorKeyboard < 0)
	{
		_menuData->menuCursorKeyboard = 5;
	}

	if (_menuData->menuCursorKeyboard > 5)
	{
		_menuData->menuCursorKeyboard = 0;
	}
	if (_menuData->menuCursor < 0)
	{
		_menuData->menuCursor = 5;
	}
	if (_menuData->menuCursor > 5)
	{
		_menuData->menuCursor = 0;
	}
	for (int i = 0; i < 2; i++)
	{
		if (_menuData->timerControl[i] > 0)
		{
			_menuData->timerControl[i] -= _dt;
		}
		if (_menuData->timerControl[i] <= 0)
		{
			_menuData->timerControl[i] = 0;
		}
	}
	if (_menuData->timerControl[0] > 0)
	{
		_menuData->timerControl[0] -= _dt;
	}
	if (_menuData->timerControl[0] <= 0)
	{
		_menuData->timerControl[0] = 0;
	}

	if ((AnyKey() != sf::Keyboard::Key::Unknown && AnyKey() != sf::Keyboard::Key::Enter && AnyKey() != sf::Keyboard::Key::Escape) && _menuData->timerControl[0] > 0 && _menuData->menuCursor < 6 && _menuData->controlMode == KEYBOARD && _menuData->canCheck == true)
	{
		m_controls->keyBinding[_menuData->menuCursor] = AnyKey();
		_menuData->keyText[_menuData->menuCursor].setString(KeyString[m_controls->keyBinding[_menuData->menuCursor]]);
		_menuData->timerControl[0] = 0;
		_menuData->choosingControl = false;

		CheckSameKey(_menuData, m_controls);

	}
	else if ((AnyButton() != ControllerButton::UNKNOWN) && _menuData->timerControl[0] > 0.f && _menuData->menuCursor >= 4 && _menuData->controlMode == CONTROLLER && _menuData->timerControl[0] < 1.9f && _menuData->canCheck == true)
	{
		m_controls->controllerBinding[_menuData->menuCursor - 4] = AnyButton();
		_menuData->joystickText[_menuData->menuCursor - 4].setString(ButtonString[(unsigned int)m_controls->controllerBinding[_menuData->menuCursor - 4]]);
		_menuData->timerControl[0] = 0;
		_menuData->choosingControl = false;

	}
	if (_menuData->timerControl[0] <= 0.f)
	{
		_menuData->timerControl[0] = 0.f;
		_menuData->controllerIsChosing[0] = false;
		_menuData->controllerIsChosing[1] = false;
	}
	else if (_menuData->menuCursor < 6 && config == KEYBOARD)
	{
		_menuData->keyText[_menuData->menuCursor].setString("_");
	}
	else if (_menuData->menuCursor >= 4 && config == CONTROLLER)
	{
		_menuData->joystickText[_menuData->menuCursor - 4].setString("_");
		_menuData->controllerIsChosing[_menuData->menuCursor - 4] = true;

	}
	for (int i = 0; i < 2; i++)
	{

		_menuData->joystickText[i].setPosition({ ((float)_menuData->windowSize[_menuData->resolutionCursor].x / 8) * 6 + 50,400.f + 40.f * (i + 4) });
		_menuData->joystickText[i].setFillColor(sf::Color::White);
	}
	for (int i = 0; i < 6; i++)
	{
		_menuData->keyText[i].setPosition({ ((float)_menuData->windowSize[_menuData->resolutionCursor].x / 8) * 6 - 100,400.f + 40.f * i });
		_menuData->controlsText[i].setPosition({ ((float)_menuData->windowSize[_menuData->resolutionCursor].x / 8) * 2,400.f + 40.f * i });
		_menuData->keyText[i].setFillColor(sf::Color::White);
		_menuData->controlsText[i].setFillColor(sf::Color::White);

		sf::Sprite temp = LoadSprite("Assets/Menu/Controls/Keyboard/" + std::to_string((int)m_controls->keyBinding[i]) + ".png", true);
		_menuData->keySprite[i] = temp;

		_menuData->keySprite[i].setScale({ 3.f,3.f });
		_menuData->keySprite[i].setPosition({ (((float)_menuData->windowSize[_menuData->resolutionCursor].x / 8) * 6 - 100),400.f + 40.f * i });


	}
	_menuData->keyText[_menuData->menuCursor].setFillColor(sf::Color::Red);
	_menuData->controlsText[_menuData->menuCursor].setFillColor(sf::Color::Red);
	if (_menuData->menuCursor >= 4)
	{
		_menuData->joystickText[_menuData->menuCursor - 4].setFillColor(sf::Color::Red);
	}

	if (AnyKey() == sf::Keyboard::Key::Escape || (sf::Joystick::isButtonPressed(0, (int)ControllerButton::B)))
	{
		_menuData->gameState = SETTINGS;
		_menuData->buttonClickSFX.play();
		_menuData->mainTimer = 0.2f;
		_menuData->buttonSFXplayed[0] = true;
		_menuData->buttonSFXplayed[1] = true;
		_menuData->buttonSFXplayed[2] = true;
		_menuData->buttonSFXplayed[3] = true;

	}
}

void DisplayControls(MenuData* _menuData, sf::RenderWindow& _window, ControlsData m_controls)
{
	for (int i = 0; i < 2; i++)
	{
		if (_menuData->controllerIsChosing[i] == false)
		{
			_menuData->joystickSprite[i].setTexture(_menuData->joystickTex[(int)m_controls.controllerBinding[i]]);
			_window.draw(_menuData->joystickSprite[i]);
		}
		else
		{
			_window.draw(_menuData->joystickText[i]);
		}

	}
	for (int i = 0; i < 6; i++)
	{

		_window.draw(_menuData->keySprite[i]);
		_window.draw(_menuData->controlsText[i]);
	}

	_window.draw(_menuData->goBack);
}