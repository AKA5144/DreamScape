#include "Settings.h"
#include "Menu.h"
#include "MenuUpdate.h"
#include "KeyString.h"
#define Y_ACCELERATION -2

void InitSettings(MenuData* _menuData)
{
	for (int i = 0; i < 5; i++)
	{

		_menuData->settingsButton[i].setPosition({ ((float)_menuData->windowSize[_menuData->resolutionCursor].x / 4) * 3 - 300, (float)(_menuData->windowSize[_menuData->resolutionCursor].y * (i + 5)) / 15 + 50 * i });
	}
	_menuData->settingsText[0].setString("Audio");
	_menuData->settingsText[1].setString("Video");
	_menuData->settingsText[2].setString("Controls");
	for (int i = 0; i < 3; i++)
	{

		_menuData->settingsText[i].setFont(_menuData->keyFont);
		_menuData->settingsText[i].setCharacterSize(50);
		_menuData->settingsText[i].setFillColor(sf::Color::White);
		_menuData->settingsText[i].setPosition({ SCREEN_WIDTH / 2.f - 100.f,SCREEN_HEIGHT / 8 });
		_menuData->settingsText[i].setOutlineColor(sf::Color{ 6,2,96 });
		_menuData->settingsText[i].setOutlineThickness(3);

	}
	_menuData->buttonTex[4][0].loadFromFile("Assets/Menu/Audio.png");
	_menuData->buttonTex[5][0].loadFromFile("Assets/Menu/Video.png");
	_menuData->buttonTex[6][0].loadFromFile("Assets/Menu/Controls.png");
	_menuData->buttonTex[7][0].loadFromFile("Assets/Menu/Credits.png");
	_menuData->buttonTex[8][0].loadFromFile("Assets/Menu/Quit2.png");
	_menuData->buttonTex[4][1].loadFromFile("Assets/Menu/Audio shade.png");
	_menuData->buttonTex[5][1].loadFromFile("Assets/Menu/Video shade.png");
	_menuData->buttonTex[6][1].loadFromFile("Assets/Menu/Controls shade.png");
	_menuData->buttonTex[7][1].loadFromFile("Assets/Menu/Credits shade.png");
	_menuData->buttonTex[8][1].loadFromFile("Assets/Menu/Quit shade2.png");

}


void UpdateSettings(MenuData* _menuData, sf::RenderWindow& _window, Config config, float _dt, GameState& _gameState)
{
	/* If the ball reaches the ground, reverse its velocity */

	sf::Vector2i mousePos = sf::Mouse::getPosition(_window);

	bool controlerActivate;



	if (_menuData->menuCursor < 0)
	{
		_menuData->menuCursor = 4;
	}

	if (_menuData->menuCursor > 4)
	{
		_menuData->menuCursor = 0;
	}
	if (_menuData->menuCursorJoystick < 0)
	{
		_menuData->menuCursorJoystick = 4;
	}

	if (_menuData->menuCursorJoystick > 4)
	{
		_menuData->menuCursorJoystick = 0;
	}

	if (_menuData->menuCursorKeyboard < 0)
	{
		_menuData->menuCursorKeyboard = 4;
	}

	if (_menuData->menuCursorKeyboard > 4)
	{
		_menuData->menuCursorKeyboard = 0;
	}

	for (int i = 0; i < 5; i++)
	{

		_menuData->settingsButton[i].setScale({ _menuData->scale, _menuData->scale });
		_menuData->menuButton[i].setPosition({ ((float)_menuData->windowSize[_menuData->resolutionCursor].x / 2) - _menuData->menuButton->getGlobalBounds().width / 2,(float)300 + 120 * i });
		sf::FloatRect boundingBox = _menuData->settingsButton[i].getGlobalBounds();
		if ((boundingBox.contains(sf::Vector2f(mousePos))))
		{
			if (!_menuData->buttonSFXplayed[i])
			{
				PlayButtonSound(_menuData->buttonSound, _menuData->actualButtonSound);
			}
			_menuData->buttonSFXplayed[i] = true;
			_menuData->menuCursor = i;
			_menuData->menuCursorJoystick = i;
			_menuData->menuCursorKeyboard = i;
			switch (i)
			{
			case(0):
				_menuData->settingsButton[i].setTexture(_menuData->buttonTex[i + 4][0]);
				break;
			case(1):
				_menuData->settingsButton[i].setTexture(_menuData->buttonTex[i + 4][0]);
				break;
			case(2):
				_menuData->settingsButton[i].setTexture(_menuData->buttonTex[i + 4][0]);
				break;
			case(3):
				_menuData->settingsButton[i].setTexture(_menuData->buttonTex[i + 4][0]);
				break;
			case(4):
				_menuData->settingsButton[i].setTexture(_menuData->buttonTex[i + 4][0]);
				break;
			}
			if (((sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || (sf::Joystick::isButtonPressed(0, (int)ControllerButton::A)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))) && _menuData->mainTimer == 0.f))
			{
				_menuData->menuButton[i].setPosition({ ((float)_menuData->windowSize[_menuData->resolutionCursor].x / 2) - _menuData->menuButton->getGlobalBounds().width / 2,(float)300 + 120 * i });
				_menuData->buttonClickSFX.play();

				switch (i)
				{
				case 0:
					_menuData->gameState = SOUND;
					_menuData->mainTimer = 0.5f;

					break;
				case 1:
					_menuData->gameState = VIDEO;
					_menuData->mainTimer = 0.5f;
					_menuData->menuCursor = 0;
					_menuData->menuCursorJoystick = 0;
					_menuData->menuCursorKeyboard = 0;


					break;
				case 2:
					_menuData->gameState = CONTROLS;
					_menuData->mainTimer = 0.5f;
					_menuData->menuCursor = 0;
					_menuData->menuCursorJoystick = 0;
					_menuData->menuCursorKeyboard = 0;
					break;
				case 3:
					_menuData->gameState = CREDITS;
					_menuData->mainTimer = 0.5f;
					_menuData->menuCursor = 0;
					_menuData->menuCursorJoystick = 0;
					_menuData->menuCursorKeyboard = 0;
					break;
				case 4:

					_menuData->mainTimer = 1.f;
					_menuData->gameState = MAINMENU;
					_menuData->menuCursor = 0;
					_menuData->menuCursorJoystick = 0;
					_menuData->menuCursorKeyboard = 0;


					break;
				}

			}
		}
		else if (_menuData->menuCursor == i)
		{

			_menuData->menuCursor = i;
			_menuData->menuCursorJoystick = i;
			_menuData->menuCursorKeyboard = i;
			switch (i)
			{
			case(0):
				_menuData->settingsButton[i].setTexture(_menuData->buttonTex[i + 4][0]);
				break;
			case(1):
				_menuData->settingsButton[i].setTexture(_menuData->buttonTex[i + 4][0]);
				break;
			case(2):
				_menuData->settingsButton[i].setTexture(_menuData->buttonTex[i + 4][0]);
				break;
			case(3):
				_menuData->settingsButton[i].setTexture(_menuData->buttonTex[i + 4][0]);
				break;
			case(4):
				_menuData->settingsButton[i].setTexture(_menuData->buttonTex[i + 4][0]);
				break;
			}
			if (((sf::Joystick::isButtonPressed(0, (int)ControllerButton::A)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))) && _menuData->mainTimer == 0.f)
			{
				_menuData->menuButton[i].setPosition({ ((float)_menuData->windowSize[_menuData->resolutionCursor].x / 2) - _menuData->menuButton->getGlobalBounds().width / 2,(float)300 + 120 * i });
				_menuData->buttonClickSFX.play();

				switch (i)
				{
				case 0:
					_menuData->gameState = SOUND;
					_menuData->mainTimer = 0.5f;
					_menuData->menuCursor = 0;
					_menuData->menuCursorJoystick = 0;
					_menuData->menuCursorKeyboard = 0;

					break;
				case 1:
					_menuData->gameState = VIDEO;
					_menuData->mainTimer = 0.5f;
					_menuData->menuCursor = 0;
					_menuData->menuCursorJoystick = 0;
					_menuData->menuCursorKeyboard = 0;;

					break;
				case 2:
					_menuData->menuCursor = 0;
					_menuData->menuCursorJoystick = 0;
					_menuData->menuCursorKeyboard = 0;
					_menuData->gameState = CONTROLS;
					_menuData->mainTimer = 0.5f;
					break;
				case 3:
					_menuData->gameState = CREDITS;
					_menuData->mainTimer = 0.5f;
					_menuData->menuCursor = 0;
					_menuData->menuCursorJoystick = 0;
					_menuData->menuCursorKeyboard = 0;
					break;
				case 4:
					if (!(sf::Joystick::isButtonPressed(0, (int)ControllerButton::A)) && !_menuData->pauseOldState)
					{
						_menuData->mainTimer = 1.f;
						_menuData->gameState = MAINMENU;
						_menuData->menuCursor = 0;
						_menuData->menuCursorJoystick = 0;
						_menuData->menuCursorKeyboard = 0;

					}
					else if (!(sf::Joystick::isButtonPressed(0, (int)ControllerButton::A)) && _menuData->pauseOldState)

					{
						_menuData->mainTimer = 1.f;
						_gameState = LOBBY;
						_menuData->menuCursor = 0;
						_menuData->menuCursorJoystick = 0;
						_menuData->menuCursorKeyboard = 0;

					}
					break;
				}

			}
		}
		else
		{
			_menuData->buttonSFXplayed[i] = false;

			switch (i)
			{
			case(0):
				_menuData->settingsButton[i].setTexture(_menuData->buttonTex[i + 4][1]);
				break;
			case(1):
				_menuData->settingsButton[i].setTexture(_menuData->buttonTex[i + 4][1]);
				break;
			case(2):
				_menuData->settingsButton[i].setTexture(_menuData->buttonTex[i + 4][1]);
				break;
			case(3):
				_menuData->settingsButton[i].setTexture(_menuData->buttonTex[i + 4][1]);
				break;
			case(4):
				_menuData->settingsButton[i].setTexture(_menuData->buttonTex[i + 4][1]);
				break;
			}
		}
		_menuData->settingsButton[i].setPosition({ _menuData->menuButton[i].getPosition().x, _menuData->menuButton[i].getPosition().y });
	}





	if (((AnyKey() == sf::Keyboard::Key::Escape || (sf::Joystick::isButtonPressed(0, (int)ControllerButton::B))) || (sf::Joystick::isButtonPressed(0, (int)ControllerButton::A) && _menuData->menuCursor == 3)) && _menuData->mainTimer == 0.f)
	{
		_menuData->mainTimer = 0.5f;
		if (_menuData->pauseOldState == MENU)
		{
			_menuData->gameState = MAINMENU;
		}
		else
		{
			_gameState = _menuData->pauseOldState;

			_menuData->pause = true;
		}
		_menuData->returnMenu = false;
		_menuData->buttonClickSFX.play();
		_menuData->buttonSFXplayed[0] = true;
		_menuData->buttonSFXplayed[1] = true;
		_menuData->buttonSFXplayed[2] = true;
		_menuData->buttonSFXplayed[3] = true;
	}
	_window.setSize(_menuData->windowSize[_menuData->resolutionCursor]);
}

void DisplaySettings(MenuData* _menuData, sf::RenderWindow& _window)
{
	for (int i = 0; i < 5; i++)
	{
		BlitSprite(_menuData->settingsButton[i], { _menuData->settingsButton[i].getPosition().x, _menuData->settingsButton[i].getPosition().y }, _window, { _menuData->scale, _menuData->scale });
	}
	_window.draw(_menuData->goBack);
}