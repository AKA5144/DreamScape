#include "Credits.h"
#include "KeyString.h"

void InitCredits(MenuData* _menuData)
{
	for (int i = 0; i < 10; i++)
	{
		_menuData->creditsText[i].setString(_menuData->creditsString[i]);
		_menuData->creditsText[i].setFont(_menuData->keyFont);
		_menuData->creditsText[i].setCharacterSize(40);
		_menuData->creditsText[i].setOutlineColor(sf::Color{ 1,55,116 });
		_menuData->creditsText[i].setOutlineThickness(3);
		if (i < 6)
		{
			_menuData->creditsText[i].setPosition({ 450.f, 400.f+100.f*i});
		}
		else
		{
			_menuData->creditsText[i].setPosition({ 1370.f, 450.f + 100.f * (i-6) });
		}
	}
	_menuData->creditTitleText[0].setString("CREDITS");
	_menuData->creditTitleText[1].setString("TropiKrab Studio");
	for (int i = 0; i < 2; i++)
	{
		_menuData->groupText[i].setString(_menuData->groupString[i]);
		_menuData->groupText[i].setFont(_menuData->keyFont);
		_menuData->groupText[i].setCharacterSize(40);
		_menuData->groupText[i].setPosition({ 500.f + 920*i, 300.f });
		_menuData->groupText[i].setOutlineColor(sf::Color{ 1,55,116 });
		_menuData->groupText[i].setOutlineThickness(5);


		_menuData->creditTitleText[i].setFont(_menuData->keyFont);
		_menuData->creditTitleText[i].setCharacterSize(45);
		_menuData->creditTitleText[i].setPosition({ SCREEN_WIDTH / 2, 100.f+100.f*i });
		_menuData->creditTitleText[i].setOutlineColor(sf::Color{ 1,55,116 });
		_menuData->creditTitleText[i].setOutlineThickness(3);
	}


	

}
void UpdateCredits(MenuData* _menuData, GameState& _gameState)
{
	for (int i = 0; i < 10; i++)
	{
		_menuData->creditsText[i].setOrigin({ _menuData->creditsText[i].getLocalBounds().width / 2,_menuData->creditsText[i].getLocalBounds().height / 2 });

	}
	for (int i = 0; i < 2; i++)
	{
		_menuData->creditTitleText[i].setOrigin({ _menuData->creditTitleText[i].getLocalBounds().width / 2,_menuData->creditTitleText[i].getLocalBounds().height / 2 });
		_menuData->groupText[i].setOrigin({ _menuData->groupText[i].getLocalBounds().width / 2,_menuData->groupText[i].getLocalBounds().height / 2 });
	}

	if (((AnyKey() == sf::Keyboard::Key::Escape || (sf::Joystick::isButtonPressed(0, (int)ControllerButton::B))) || (sf::Joystick::isButtonPressed(0, (int)ControllerButton::A) && _menuData->menuCursor == 3)) && _menuData->mainTimer == 0)
	{
		_menuData->gameState = SETTINGS;
		_menuData->mainTimer = 0.2f;
		_menuData->buttonClickSFX.play();

	}
}
void DisplayCredits(MenuData* _menuData,sf::RenderWindow& window)
{

	for (int i = 0; i < 2; i++)
	{ 
		window.draw(_menuData->creditTitleText[i]);

		window.draw(_menuData->groupText[i]);
	}
	for (int i = 0; i < 10; i++)
	{
		window.draw(_menuData->creditsText[i]);
	}
	window.draw(_menuData->goBack);

}