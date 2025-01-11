#include "SoundSettings.h"
#include "MenuUpdate.h"

void InitSoundSettings(MenuData* _menuData)
{
	_menuData->audioText[0].setString("General : ");
	_menuData->audioText[1].setString("SFX : ");
	_menuData->audioText[2].setString("Music : ");

	for (int i = 0; i < 3; i++)
	{
		_menuData->soundBar[i][1] = LoadSprite("Assets/Menu/Barre son void.png", true);
		_menuData->soundBar[i][0] = LoadSprite("Assets/Menu/Barre son full.png", true);
		_menuData->soundBar[i][0].setScale({ 1.f,1.f });
		_menuData->soundBar[i][1].setScale({ 1.f,1.f });
		_menuData->soundCursor[i].setScale({ 1.f,1.f });
		_menuData->soundBar[i][0].setPosition({ 100.f,(float)(300 + 100 * i) });
		_menuData->soundBar[i][1].setPosition({ 100.f,(float)(300 + 100 * i) });
		_menuData->soundCursor[i].setPosition({ _menuData->soundBar[i][0].getGlobalBounds().left + _menuData->soundBar[i][0].getGlobalBounds().width,_menuData->soundBar[i][0].getGlobalBounds().top + (_menuData->soundBar[i][0].getGlobalBounds().height / 2) });
		_menuData->soundCursor[i] = LoadSprite("Assets/Menu/Curseur Son.png", true);

		_menuData->audioText[i].setFont(_menuData->keyFont);
		_menuData->audioText[i].setCharacterSize(40);
		_menuData->audioText[i].setFillColor(sf::Color::White);
		_menuData->audioText[i].setOutlineColor(sf::Color{6,2,96});
		_menuData->audioText[i].setOutlineThickness(3);
	}
}

void SoundSettingsUpdate(MenuData* _menuData, sf::RenderWindow& _window, float _dt)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(_window);


	if (_menuData->menuCursorJoystick < 0)
	{
		_menuData->menuCursorJoystick = 2;
	}

	if (_menuData->menuCursorJoystick > 2)
	{
		_menuData->menuCursorJoystick = 0;
	}

	if (_menuData->menuCursorKeyboard < 0)
	{
		_menuData->menuCursorKeyboard = 2;
	}

	if (_menuData->menuCursorKeyboard > 2)
	{
		_menuData->menuCursorKeyboard = 0;
	}
	for (int i = 0; i < 3; i++)
	{
		_menuData->soundBar[i][0].setPosition({ (float)(_menuData->windowSize[_menuData->resolutionCursor].x / 6)*4,(float)(400 + 100 * i) });
		_menuData->soundBar[i][1].setPosition({ (float)(_menuData->windowSize[_menuData->resolutionCursor].x / 6)*4,(float)(400 + 100 * i) });
		_menuData->audioText[i].setPosition({ (float)(_menuData->windowSize[_menuData->resolutionCursor].x / 6)*2,(float)(400 + 100 * i) });

		_menuData->soundCursor[i].setPosition({ _menuData->soundBar[i][0].getGlobalBounds().left + _menuData->soundBar[i][0].getGlobalBounds().width,_menuData->soundBar[i][0].getGlobalBounds().top + (_menuData->soundBar[i][0].getGlobalBounds().height / 2) });
		_menuData->audioText[i].setFillColor(sf::Color::White);

		sf::FloatRect boundingBox = _menuData->soundBar[i][1].getGlobalBounds();
		_menuData->audioText[_menuData->menuCursor].setFillColor(sf::Color::Red);

		if (boundingBox.contains(sf::Vector2f(mousePos)))
		{
			_menuData->menuCursor = i;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				sf::IntRect soundRect({ 0,0,(int)((mousePos.x - _menuData->soundBar[i][1].getGlobalBounds().left)/ 1.f),(int)(_menuData->soundBar[i][1].getLocalBounds().height) });
				_menuData->soundCursor[i].setPosition({ (_menuData->soundBar[i][0].getGlobalBounds().left + soundRect.width*1.f),_menuData->soundBar[i][0].getGlobalBounds().top + soundRect.height/2 });
				_menuData->soundBar[i][0].setTextureRect(soundRect);
				_menuData->volume[i] = (soundRect.width / _menuData->soundBar[i][1].getGlobalBounds().width) * 100;
				_menuData->volume[1] = _menuData->volume[1] * (_menuData->volume[0] / 100);
				_menuData->volume[2] = _menuData->volume[2] * (_menuData->volume[0] / 100);
				for (int i = 0; i < 7; i++)
				{
					_menuData->buttonSound[i].setVolume(_menuData->volume[1]);
				}
				_menuData->buttonClickSFX.setVolume(_menuData->volume[1]);
				PlayButtonSound(_menuData->buttonSound, _menuData->actualButtonSound);


			}
		}
		if ((sf::Joystick::getAxisPosition(0, sf::Joystick::X) <-20)|| (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
		{
			sf::IntRect soundRect = _menuData->soundBar[_menuData->menuCursor][0].getTextureRect();
			if (soundRect.width > 0 && _menuData->mainTimer==0.f)
			{
				soundRect.width-=5;
				_menuData->mainTimer = 0.2f;
				PlayButtonSound(_menuData->buttonSound, _menuData->actualButtonSound);


			}
			_menuData->soundBar[_menuData->menuCursor][0].setTextureRect(soundRect);
			_menuData->volume[_menuData->menuCursor] = (soundRect.width / _menuData->soundBar[_menuData->menuCursor][1].getGlobalBounds().width) * 100.f;
			_menuData->volume[1] = _menuData->volume[1] * (_menuData->volume[0]) / 100.f;
			_menuData->volume[2] = _menuData->volume[2] * (_menuData->volume[0]) / 100.f;
			_menuData->buttonHoverSFX.setVolume(_menuData->volume[1]);
			_menuData->buttonClickSFX.setVolume(_menuData->volume[1]);
		}
		if ((sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 20)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			sf::IntRect soundRect = _menuData->soundBar[_menuData->menuCursor][0].getTextureRect();
			PlayButtonSound(_menuData->buttonSound, _menuData->actualButtonSound);


			if (soundRect.width < _menuData->soundBar[_menuData->menuCursor][1].getTextureRect().width && _menuData->mainTimer == 0.f)
			{
				soundRect.width+=5;
				_menuData->mainTimer=0.2f;
				PlayButtonSound(_menuData->buttonSound, _menuData->actualButtonSound);


			}
			_menuData->soundBar[_menuData->menuCursor][0].setTextureRect(soundRect);
			_menuData->volume[_menuData->menuCursor] = (soundRect.width / _menuData->soundBar[_menuData->menuCursor][1].getGlobalBounds().width) * 100.f;
			_menuData->volume[1] = _menuData->volume[1] * (_menuData->volume[0] / 100.f);
			_menuData->volume[2] = _menuData->volume[2] * (_menuData->volume[0] / 100.f);
			for (int i = 0; i < 7; i++)
			{
				_menuData->buttonSound[i].setVolume(_menuData->volume[1]);
			}
			_menuData->buttonClickSFX.setVolume(_menuData->volume[1]);
		}

		
		if (_menuData->mainTimer > 0)
		{
			_menuData->mainTimer -= _dt;
		}

		if (_menuData->mainTimer < 0)
		{
			_menuData->mainTimer = 0;
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
}

void DisplaySoundSettings(MenuData* _menuData, sf::RenderWindow& _window)
{
	

	for (int i = 0; i < 3; i++)
	{
		BlitSprite(_menuData->soundBar[i][1], { _menuData->soundBar[i][1].getPosition().x, _menuData->soundBar[i][1].getPosition().y }, _window);
		BlitSprite(_menuData->soundBar[i][0], { _menuData->soundBar[i][0].getPosition().x, _menuData->soundBar[i][0].getPosition().y }, _window);

		_window.draw(_menuData->audioText[i]);

		BlitSprite(_menuData->soundCursor[i], { _menuData->soundCursor[i].getPosition().x, _menuData->soundCursor[i].getPosition().y }, _window);
	}
	_window.draw(_menuData->goBack);
}