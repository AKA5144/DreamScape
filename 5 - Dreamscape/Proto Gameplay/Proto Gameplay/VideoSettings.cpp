#include "VideoSettings.h"

void InitVideoSettings(MenuData* _menuData)
{
	for (int i = 0; i < 4; i++)
	{
		_menuData->settingsCase[i][1] = LoadSprite("Assets/Menu/Cases cocher.png", true);
		_menuData->settingsCase[i][0] = LoadSprite("Assets/Menu/Cases cocher vide.png", true);
		_menuData->settingsCase[i][0].setScale({ _menuData->scale,_menuData->scale });
		_menuData->settingsCase[i][1].setScale({ _menuData->scale,_menuData->scale });
		_menuData->settingsCase[i][0].setPosition({ (float)(_menuData->windowSize[_menuData->resolutionCursor].x / 4)*3,(float)(500 + 10 * i) });
		_menuData->settingsCase[i][1].setPosition({ (float)(_menuData->windowSize[_menuData->resolutionCursor].x / 4)*3,(float)(500 + 150 * i) });
	}

	for (int i = 0; i < 2; i++)
	{
		_menuData->videoText[i].setFont(_menuData->keyFont);
		_menuData->videoText[i].setCharacterSize(40);
		_menuData->videoText[i].setFillColor(sf::Color::White);
		_menuData->videoText[i].setPosition({ ((float)_menuData->windowSize[_menuData->resolutionCursor].x / 4),400.f + 150.f * i });

	}
	_menuData->videoText[0].setString("Fullscreen : ");
	_menuData->videoText[1].setString("VSync : ");
	_menuData->videoText[0].setOutlineColor(sf::Color{ 1,55,116 });
	_menuData->videoText[0].setOutlineThickness(3);
	for (int i = 0; i < 3; i++)
	{
		_menuData->resolutionText[i].setPosition({( (float)_menuData->windowSize[_menuData->resolutionCursor].x / 8) * 6 - 100,400 });
		_menuData->resolutionText[i].setFont(_menuData->keyFont);
		_menuData->resolutionText[i].setCharacterSize(24);
		_menuData->resolutionText[i].setFillColor(sf::Color::White);;
	}
	_menuData->resolutionText[0].setString("854x480");
	_menuData->resolutionText[1].setString("1280x720");
	_menuData->resolutionText[2].setString("1920x1080");
}


void VideoSettingsUpdate(MenuData* _menuData, sf::RenderWindow& _window, float _dt)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(_window);


	if (_menuData->menuCursor == 4)
	{
		_menuData->resolutionText[_menuData->resolutionCursor].setFillColor(sf::Color::Red);
	}
	else
	{
		_menuData->resolutionText[_menuData->resolutionCursor].setFillColor(sf::Color::White);
	}

	if (_menuData->mainTimer > 0.f)
	{
		_menuData->mainTimer -= _dt;
	}

	if (_menuData->mainTimer <= 0.f)
	{
		_menuData->mainTimer = 0.f;
		_menuData->canCheck = true;

	}

	for (int i = 0; i < 2; i++)
	{
		_menuData->videoText[0].setString("Fullscreen : ");
	}
	for (int i = 0; i < 3; i++)
	{
		_menuData->settingsCase[i][0].setPosition({ (float)(_menuData->windowSize[_menuData->resolutionCursor].x / 4) * 3,(float)(450 + 150 * i) });

		_menuData->settingsCase[i][1].setPosition({ (float)(_menuData->windowSize[_menuData->resolutionCursor].x / 4) * 3,(float)(450 + 150 * i) });

	}



		for (int i = 0; i < 2; i++)
		{
			sf::FloatRect boundingBox = _menuData->settingsCase[i][0].getGlobalBounds();

			if (boundingBox.contains(sf::Vector2f(mousePos)))
			{
				
				_menuData->menuCursor = i;

				if ((sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) && _menuData->mainTimer==0.f)
				{
					if (!_menuData->caseChoiced[i] && _menuData->canCheck == true)
					{
						_menuData->caseChoiced[i] = true;
						_menuData->canCheck = false;
						_menuData->mainTimer = 1.f;
						switch (i)
						{
						case 0:
							_window.close();
							_window.create(sf::VideoMode(_menuData->windowSize[2].x, _menuData->windowSize[2].y), "Projet", sf::Style::Fullscreen);
							break;
						case 1:
							_window.setVerticalSyncEnabled(true);

							break;
						}
					}
					if (_menuData->caseChoiced[i] && _menuData->canCheck == true)
					{
						_menuData->caseChoiced[i] = false;
						_menuData->canCheck = false;
						_menuData->mainTimer = 1.f;
						switch (i)
						{
						case 0:
							_window.close();
							_window.create(sf::VideoMode(_menuData->windowSize[2].x, _menuData->windowSize[2].y), "Projet", sf::Style::Close);
							break;
						case 1:
							_window.setVerticalSyncEnabled(false);

							break;
						};
					}

				}
			}
		}
	if (sf::Joystick::isButtonPressed(0, (int)ControllerButton::A)&&_menuData->mainTimer==0)
	{
		if (_menuData->caseChoiced[0])
		{
			_menuData->caseChoiced[0] = false;
			_menuData->mainTimer = 0.5f;
			_window.close();
			_window.create(sf::VideoMode(_menuData->windowSize[2].x, _menuData->windowSize[2].y), "Projet", sf::Style::Close);
			_window.setVerticalSyncEnabled(true);
		}
		else
		{
			_window.close();
			_window.create(sf::VideoMode(_menuData->windowSize[2].x, _menuData->windowSize[2].y), "Projet", sf::Style::Fullscreen);
			_window.setVerticalSyncEnabled(true);
			_menuData->caseChoiced[0] = true;
			_menuData->mainTimer = 0.5f;

		}
	}
	if (AnyKey() == sf::Keyboard::Key::Escape || (sf::Joystick::isButtonPressed(0, (int)ControllerButton::B)))
	{
		_menuData->buttonClickSFX.play();
		_menuData->gameState = SETTINGS;
		_menuData->mainTimer = 0.2f;
		_menuData->buttonSFXplayed[0] = true;
		_menuData->buttonSFXplayed[1] = true;
		_menuData->buttonSFXplayed[2] = true;
		_menuData->buttonSFXplayed[3] = true;
	}
	_menuData->menuCursorKeyboard = 0;
	_menuData->menuCursorJoystick = 0;

	if (_menuData->resolutionCursor < 0)
	{
		_menuData->resolutionCursor = 0;
	}
	if (_menuData->resolutionCursor > 2)
	{
		_menuData->resolutionCursor = 2;
	}

	if (AnyKey() == sf::Keyboard::Key::Escape || (sf::Joystick::isButtonPressed(0, (int)ControllerButton::B)))
	{
		_menuData->gameState = SETTINGS;
		_menuData->mainTimer = 0.2f;
	}
	_menuData->videoText[_menuData->menuCursor].setFillColor(sf::Color::Red);

}

void DisplayVideoSettings(MenuData* _menuData, sf::RenderWindow& _window)
{
	for (int i = 0; i < 2; i++)
	{
		if (!_menuData->caseChoiced[i])
		{
			BlitSprite(_menuData->settingsCase[i][0], { _menuData->settingsCase[i][0].getPosition().x, _menuData->settingsCase[i][0].getPosition().y }, _window, { _menuData->scale , _menuData->scale });
		}
		if (_menuData->caseChoiced[i])
		{
			BlitSprite(_menuData->settingsCase[i][1], { _menuData->settingsCase[i][1].getPosition().x, _menuData->settingsCase[i][1].getPosition().y }, _window, { _menuData->scale , _menuData->scale });
		}
		_window.draw(_menuData->videoText[i]);

	}

	_window.draw(_menuData->goBack);
}