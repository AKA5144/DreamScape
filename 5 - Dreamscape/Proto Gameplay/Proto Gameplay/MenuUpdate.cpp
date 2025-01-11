#include "KeyString.h"
#include "MenuUpdate.h"
#include "Menu.h"
#include "Settings.h"





void MenuUpdate(MenuData* _menuData, sf::RenderWindow& _window, GameState& _gameState, Config config, float _dt, Player& _player, ControlsData*& m_controls)
{
	sf::Event event;


	for (int i = 0; i < 10; i++)
	{
		_menuData->creditsText[i].setOrigin({ _menuData->creditsText[i].getLocalBounds().width / 2,_menuData->creditsText[i].getLocalBounds().height / 2 });

	}
	for (int i = 0; i < 2; i++)
	{
		_menuData->groupText[i].setOrigin({ _menuData->groupText[i].getLocalBounds().width / 2,_menuData->groupText[i].getLocalBounds().height / 2 });
		_menuData->creditTitleText[i].setOrigin({ _menuData->creditTitleText[i].getLocalBounds().width / 2,_menuData->creditTitleText[i].getLocalBounds().height / 2 });

	}




	_menuData->menuMusic.setVolume(_menuData->volume[2]);
	_menuData->menuMusic.setLoop(true);
	if (_gameState == MENU)
	{
		if (_menuData->menuMusic.getStatus() == sf::Sound::Status::Stopped)
		{
			_menuData->menuMusic.play();
		}
	}
	else
	{
		_menuData->menuMusic.stop();

	}
	
	for (int i = 0; i < 7; i++)
	{
		_menuData->buttonSound[i].setVolume(_menuData->volume[1]);
	}
	_menuData->buttonClickSFX.setVolume(_menuData->volume[1]);

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
	switch (_menuData->gameState)
	{
	case(MAINMENU):
		MainMenuUpdate(_menuData, _window, _gameState, config,_dt, _player);
		break;
	case(GAME):
		UpdateSettings(_menuData, _window,config, _dt,_gameState);
		break;
	case(SETTINGS):
		UpdateSettings(_menuData, _window,config, _dt, _gameState);
		break;
	case(CONTROLS):
		ControlsUpdate(_menuData, _dt,_player,m_controls, config);
		break;
	case(VIDEO):
		VideoSettingsUpdate(_menuData, _window, _dt);
		break;
	case(SOUND):
		SoundSettingsUpdate(_menuData, _window, _dt);
		break;
	case(CREDITS):
		UpdateCredits(_menuData,_gameState);
		break;
	}



}

void PlayButtonSound(sf::Sound* _buttonSound, int& _actualButtonSound)
{
	if (_actualButtonSound > 6)
	{
		_actualButtonSound = 0;
	}

	_buttonSound[_actualButtonSound].play();
	_actualButtonSound++;
}