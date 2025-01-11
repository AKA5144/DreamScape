#include "Menu.h"
#include "MenuInit.h"
#include "Altar.h"
#include "MenuUpdate.h"

void MainMenuUpdate(MenuData* _menuData, sf::RenderWindow& _window, GameState& _gameState, Config config, float _dt, Player& _player)
{
	
	
	if (!_menuData->startClock)
	{
		
		_menuData->clockbutton.restart();
		_menuData->startClock = true;
	}

	for (int i = 0; i < 4; i++)
	{
		_menuData->posSprite[i].x = 900;
		if (i < 4 && _menuData->clockbutton.getElapsedTime().asSeconds() < 3)
		{
			_menuData->posSprite[i].y = -50 + (float)Easing::easeOutElastic((float)_menuData->clockbutton.getElapsedTime().asSeconds(), 0, 450 + 120 * i, 4);

			_menuData->menuButton[i].setPosition({ ((float)_menuData->windowSize[_menuData->resolutionCursor].x / 2)-_menuData->menuButton->getGlobalBounds().width/2,_menuData->posSprite[i].y});
		}
		else
		{
			_menuData->menuButton[i].setPosition({ ((float)_menuData->windowSize[_menuData->resolutionCursor].x / 2) - _menuData->menuButton->getGlobalBounds().width / 2,(float)400 + 120 * i });

		}
	}


		if (_menuData->clockbutton.getElapsedTime().asSeconds() < 3)
		{
			_menuData->title.setScale({(float)Easing::easeOutExpo((float)_menuData->clockbutton.getElapsedTime().asSeconds(), 0, 1, 3)*3.f, (float)Easing::easeOutBack((float)_menuData->clockbutton.getElapsedTime().asSeconds(), 0, 1, 3) * 3.f });

		}
		_menuData->title.setOrigin({ _menuData->title.getLocalBounds().width / 2 ,_menuData->title.getLocalBounds().height / 2 });

		_menuData->title.setPosition({ SCREEN_WIDTH / 2 ,200 });





	/* If the ball reaches the ground, reverse its velocity */

	if (_menuData->menuCursorJoystick < 0)
	{
		_menuData->menuCursorJoystick = 3;
	} 

	if (_menuData->menuCursorJoystick > 3)
	{
		_menuData->menuCursorJoystick = 0;
	}

	if (_menuData->menuCursorKeyboard < 0)
	{
		_menuData->menuCursorKeyboard = 3;
	}

	if (_menuData->menuCursorKeyboard > 3)
	{
		_menuData->menuCursorKeyboard = 0;
	}
	if (_menuData->mainTimer > 0)
	{
		_menuData->mainTimer -= _dt;
	}

	if (_menuData->mainTimer < 0)
	{
		_menuData->mainTimer = 0;
	}
	sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
	for (int i = 0; i < 4; i++)
	{
		_menuData->menuButton[i].setScale({ _menuData->scale, _menuData->scale });
		sf::FloatRect boundingBox = _menuData->menuButton[i].getGlobalBounds();
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
				_menuData->menuButton[i].setTexture(_menuData->buttonTex[i][0]);
				break;
			case(1):
				_menuData->menuButton[i].setTexture(_menuData->buttonTex[i][0]);
				break;
			case(2):
				_menuData->menuButton[i].setTexture(_menuData->buttonTex[i][0]);
				break;
			case(3):
				_menuData->menuButton[i].setTexture(_menuData->buttonTex[i][0]);
				break;
			}
			if (((sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || (sf::Joystick::isButtonPressed(0, (int)ControllerButton::A)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))) && _menuData->mainTimer == 0.f))
			{
				_menuData->menuButton[3].setPosition({ ((float)_menuData->windowSize[_menuData->resolutionCursor].x / 2) - _menuData->menuButton->getGlobalBounds().width / 2,(float)400 + 120 * 3 });

				_menuData->buttonClickSFX.play();

				switch (i)
				{
				case 0:
					_gameState = LOBBY;
					_menuData->menuMusic.stop();


					break;
				case 1:
					LoadGame(_player);
					_menuData->menuMusic.stop();



					_gameState = LOBBY;
					break;
				case 2:
					_menuData->gameState = SETTINGS;
					_menuData->mainTimer = 0.5f;
					break;
				case 3:
					_window.close();
					break;
				}

			}
		}
		else if (_menuData->menuCursor == i)
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
				_menuData->menuButton[i].setTexture(_menuData->buttonTex[i][0]);
				break;
			case(1):
				_menuData->menuButton[i].setTexture(_menuData->buttonTex[i][0]);
				break;
			case(2):
				_menuData->menuButton[i].setTexture(_menuData->buttonTex[i][0]);
				break;
			case(3):
				_menuData->menuButton[i].setTexture(_menuData->buttonTex[i + 5][0]);
				break;
			}
			if (((sf::Joystick::isButtonPressed(0, (int)ControllerButton::A)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))) && _menuData->mainTimer == 0.f)
			{
				_menuData->menuButton[3].setPosition({ ((float)_menuData->windowSize[_menuData->resolutionCursor].x / 2) - _menuData->menuButton->getGlobalBounds().width / 2,(float)400 + 120 * 3 });

				_menuData->buttonClickSFX.play();

				switch (i)
				{
				case 0:
					_gameState = LOBBY;
					_menuData->menuMusic.stop();

					break;
				case 1:
					LoadGame(_player);
					_gameState = LOBBY;
					_menuData->menuMusic.stop();

					break;
				case 2:
					_menuData->gameState = SETTINGS;
					_menuData->mainTimer = 0.5f;
					_menuData->menuCursor = 0;
					_menuData->menuCursorJoystick = 0;
					_menuData->menuCursorKeyboard = 0;
					break;
				case 3:
					_window.close();
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
				_menuData->menuButton[i].setTexture(_menuData->buttonTex[i][1]);
				break;
			case(1):
				_menuData->menuButton[i].setTexture(_menuData->buttonTex[i][1]);
				break;
			case(2):
				_menuData->menuButton[i].setTexture(_menuData->buttonTex[i][1]);
				break;
			case(3):
				_menuData->menuButton[i].setTexture(_menuData->buttonTex[i][1]);
				break;
			}
		}
	}
	if (AnyKey() == sf::Keyboard::Key::Escape && _menuData->mainTimer==0.f)
	{
		_window.close();
	}
}