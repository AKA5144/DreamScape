#include "Pause.h"
#include "Altar.h"
#include "MenuUpdate.h"

void InitPause(MenuData* _menuData, Player& _player, ControlsData m_controls)
{
	for (int i = 0; i < 4; i++)
	{
		_menuData->pauseButtons[i] = LoadSprite("Assets/Menu/Pause/" + std::to_string(i) + ".png", true);

		_menuData->buttonTex[9 + i][1].loadFromFile("Assets/Menu/Pause/" + std::to_string(i) + " shade.png");
		_menuData->buttonTex[9 + i][0].loadFromFile("Assets/Menu/Pause/" + std::to_string(i) + ".png");
		_menuData->pauseButtons[i].setTexture(_menuData->buttonTex[8 + i][0]);
	}
	_menuData->quitSprite[0] = LoadSprite("Assets/Menu/Pause/Fenetre quit.png", true);
	_menuData->quitSprite[1] = LoadSprite("Assets/Menu/Pause/yes shade.png", true);
	_menuData->quitSprite[2] = LoadSprite("Assets/Menu/Pause/no shade.png", true);
	_menuData->quitSprite[0].setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	_menuData->quitSprite[1].setPosition(SCREEN_WIDTH / 5 * 2, SCREEN_HEIGHT / 4 * 2 + 50);
	_menuData->quitSprite[2].setPosition(SCREEN_WIDTH / 5 * 3, SCREEN_HEIGHT / 4 * 2 + 50);
	_menuData->quitSprite[0].setScale({ 2.f,2.f });
	_menuData->quitSprite[1].setScale({ 2.f,2.f });
	_menuData->quitSprite[2].setScale({ 2.f,2.f });
	_menuData->blackBg = LoadSprite("Assets/Menu/Pause/blackBG.jpg", true);
	_menuData->pauseText = LoadSprite("Assets/Menu/Pause/pause.png", true);
}


void UpdatePause(MenuData* _menuData, sf::RenderWindow& _window, Config config, float _dt, GameState& _gameState, bool& pause, Player& m_player)
{

	sf::Event event;

	for (int i = 0; i < 7; i++)
	{
		_menuData->buttonSound[i].setVolume(_menuData->volume[1]);
	}
	_menuData->buttonClickSFX.setVolume(_menuData->volume[1]);
	if (!_menuData->quitConfirmation)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && _menuData->mainTimer == 0 && config == KEYBOARD && _menuData->choosingControl == false)
		{
			_menuData->menuCursorKeyboard--;

			_menuData->mainTimer = 0.25f;
			PlayButtonSound(_menuData->buttonSound, _menuData->actualButtonSound);


		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && _menuData->mainTimer == 0 && config == KEYBOARD && _menuData->choosingControl == false)
		{
			_menuData->menuCursorKeyboard++;

			_menuData->mainTimer = 0.25f;
			PlayButtonSound(_menuData->buttonSound, _menuData->actualButtonSound);


		}

		if ((sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -20) && _menuData->mainTimer == 0 && config == CONTROLLER && _menuData->choosingControl == false)
		{
			_menuData->menuCursorJoystick--;
			_menuData->mainTimer = 0.25f;
			PlayButtonSound(_menuData->buttonSound, _menuData->actualButtonSound);

		}
		if ((sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 20) && _menuData->mainTimer == 0 && config == CONTROLLER && _menuData->choosingControl == false)
		{
			_menuData->menuCursorJoystick++;

			_menuData->mainTimer = 0.25f;
			PlayButtonSound(_menuData->buttonSound, _menuData->actualButtonSound);


		}

		if (config == CONTROLLER)
		{
			_menuData->menuCursor = _menuData->menuCursorJoystick;
			_menuData->menuCursorKeyboard = _menuData->menuCursorJoystick;
		}
		else
		{
			_menuData->menuCursor = _menuData->menuCursorKeyboard;
			_menuData->menuCursorJoystick = _menuData->menuCursorKeyboard;
		}
		if (_menuData->mainTimer > 0)
		{
			_menuData->mainTimer -= _dt;
		}

		if (_menuData->mainTimer < 0)
		{
			_menuData->mainTimer = 0;
		}

		if (_menuData->menuCursor < 0)
		{
			_menuData->menuCursor = 3;
		}

		if (_menuData->menuCursor > 3)
		{
			_menuData->menuCursor = 0;
		}

		sf::Vector2i mousePos1 = sf::Mouse::getPosition(_window);

		for (int i = 0; i < 4; i++)
		{
			_menuData->pauseButtons[i].setPosition({ _window.getView().getCenter().x,(float)(_window.getView().getCenter().y - _window.getView().getSize().y / 2) + (_window.getView().getSize().y / 6) * (i + 2) });

			sf::Vector2f tempScale({ (float)SCREEN_WIDTH / _window.getView().getSize().x,(float)SCREEN_HEIGHT / _window.getView().getSize().x });

			_menuData->pauseText.setPosition({ _window.getView().getCenter().x,(float)(_window.getView().getCenter().y - _window.getView().getSize().y / 2) + (_window.getView().getSize().y / 5) });
			_menuData->pauseButtons[i].setScale({ 3.f * (1 / tempScale.x), 3.f * (1 / tempScale.x) });
			_menuData->pauseText.setScale({ 1.5f * (1 / tempScale.x),1.5f * (1 / tempScale.x) });
			sf::Vector2i buttonPos = _window.mapCoordsToPixel(_menuData->pauseButtons[i].getPosition());
			if (((buttonPos.x-mousePos1.x < _menuData->pauseButtons[i].getGlobalBounds().width / 2)&& (buttonPos.x - mousePos1.x > -_menuData->pauseButtons[i].getGlobalBounds().width / 2)) &&((buttonPos.y - mousePos1.y < _menuData->pauseButtons[i].getGlobalBounds().height / 2) && (buttonPos.y - mousePos1.y > -_menuData->pauseButtons[i].getGlobalBounds().height / 2)))
			{
				_menuData->menuCursor = i;
				_menuData->menuCursorJoystick = i;
				_menuData->menuCursorKeyboard = i;
				switch (i)
				{
				case(0):
					_menuData->pauseButtons[i].setTexture(_menuData->buttonTex[i + 9][0]);
					break;
				case(1):
					_menuData->pauseButtons[i].setTexture(_menuData->buttonTex[i + 9][0]);
					break;
				case(2):
					_menuData->pauseButtons[i].setTexture(_menuData->buttonTex[i + 9][0]);
					break;
				case(3):
					_menuData->pauseButtons[i].setTexture(_menuData->buttonTex[i + 9][0]);
					break;
				}
				if (((sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || (sf::Joystick::isButtonPressed(0, (int)ControllerButton::A)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))) && _menuData->mainTimer == 0.f))
				{
					_menuData->buttonClickSFX.play();

					switch (i)
					{
					case 0:
						pause = false; 

						_menuData->mainTimer = 0.5f;
						_menuData->menuCursor = 0;
						_menuData->menuCursorJoystick = 0;
						_menuData->menuCursorKeyboard = 0;

						break;
					case 1:
						SaveGame(m_player);
						_menuData->mainTimer = 0.5f;
						_menuData->menuCursor = 0;
						_menuData->menuCursorJoystick = 0;
						_menuData->menuCursorKeyboard = 0;


						break;
					case 2:
						_menuData->pauseOldState = _gameState;
						_gameState = MENU;
						pause = false;


						_menuData->gameState = SETTINGS;
						_menuData->mainTimer = 0.5f;
						_menuData->menuCursor = 0;
						_menuData->menuCursorJoystick = 0;
						_menuData->menuCursorKeyboard = 0;
						break;
					case 3:
						_menuData->pauseOldState = MENU;

						_gameState = MENU;
						pause = false;
						_menuData->gameState = MAINMENU;
						_menuData->mainTimer = 0.5f;
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
					_menuData->pauseButtons[i].setTexture(_menuData->buttonTex[i + 9][0]);
					break;
				case(1):
					_menuData->pauseButtons[i].setTexture(_menuData->buttonTex[i + 9][0]);
					break;
				case(2):
					_menuData->pauseButtons[i].setTexture(_menuData->buttonTex[i + 9][0]);
					break;
				case(3):
					_menuData->pauseButtons[i].setTexture(_menuData->buttonTex[i + 9][0]);
					break;
				}
				if (((sf::Joystick::isButtonPressed(0, (int)ControllerButton::A)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))) && _menuData->mainTimer == 0.f)
				{
					_menuData->buttonClickSFX.play();

					switch (i)
					{
					case 0:
						pause = false;
						_menuData->gameState = SOUND;
						_menuData->mainTimer = 0.5f;
						_menuData->menuCursor = 0;
						_menuData->menuCursorJoystick = 0;
						_menuData->menuCursorKeyboard = 0;

						break;
					case 1:
						SaveGame(m_player);
						_menuData->mainTimer = 0.5f;
						_menuData->menuCursor = 0;
						_menuData->menuCursorJoystick = 0;
						_menuData->menuCursorKeyboard = 0;;
						break;
					case 2:
						_menuData->pauseOldState = _gameState;
						_gameState = MENU;
						pause = false;
						_menuData->menuCursor = 0;
						_menuData->menuCursorJoystick = 0;
						_menuData->menuCursorKeyboard = 0;
						_menuData->gameState = SETTINGS;
						_menuData->mainTimer = 0.5f;
						break;
					case 3:
						_gameState = MENU;
						pause = false;

						_menuData->menuCursor = 0;
						_menuData->menuCursorJoystick = 0;
						_menuData->menuCursorKeyboard = 0;
						_menuData->gameState = MAINMENU;
						_menuData->mainTimer = 0.5f;
						break;

					}

				}
			}
			else
			{
				switch (i)
				{
				case(0):
					_menuData->pauseButtons[i].setTexture(_menuData->buttonTex[i + 9][1]);
					break;
				case(1):
					_menuData->pauseButtons[i].setTexture(_menuData->buttonTex[i + 9][1]);
					break;
				case(2):
					_menuData->pauseButtons[i].setTexture(_menuData->buttonTex[i + 9][1]);
					break;
				case(3):
					_menuData->pauseButtons[i].setTexture(_menuData->buttonTex[i + 9][1]);
					break;
				}
			}
		}

	}
	else
	{

	}
}

void DisplayPause(MenuData* _menuData, sf::RenderWindow& _window, ControlsData m_controls)
{

	_menuData->blackBg.setColor(sf::Color({ 255,255,255,110 }));
	_menuData->blackBg.setScale({ 5.f,5.f });
	_window.draw(_menuData->blackBg);
	_window.draw(_menuData->pauseText);
	if (!_menuData->quitConfirmation) {
		for (int i = 0; i < 4; i++)
		{

			_window.draw(_menuData->pauseButtons[i]);
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			_window.draw(_menuData->quitSprite[i]);
		}
	}
}