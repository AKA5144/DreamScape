#include "MenuInit.h"
#include "MenuData.h"

#include "KeyString.h"


/*TODO: écrire le corps de la fonction Init qui chargera les sprites, 
instanciera dynamiquement le joueur et les vaisseaux, et appellera la fonction
AjouteObstacle de obstacle.h pour ajouter les premiers obstacles du jeu.*/
void MenuInit(MenuData* _menuData, Player& _player, ControlsData m_controls)
{

	InitSettings(_menuData);
	InitControls(_menuData, _player, m_controls);
	InitSoundSettings(_menuData);
	InitVideoSettings(_menuData);
	InitCredits(_menuData);
	_menuData->menuMusic.openFromFile("Assets/Menu/Menu.ogg");

	_menuData->menuView.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	_menuData->menuView.setCenter({ SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 });
	for (int i = 0; i < 4; i++) 
	{
		_menuData->posSprite[i] = { (float)_menuData->windowSize[_menuData->resolutionCursor].x / 2,-150.f };
		_menuData->menuButton[i].setPosition(_menuData->posSprite[i]);
		_menuData->menuButton[i].setScale({_menuData->scale,_menuData->scale });
	}
	_menuData->buttonTex[0][0].loadFromFile("Assets/Menu/New Game.png");
	_menuData->buttonTex[1][0].loadFromFile("Assets/Menu/Load Game.png");
	_menuData->buttonTex[2][0].loadFromFile("Assets/Menu/Settings.png");
	_menuData->buttonTex[3][0].loadFromFile("Assets/Menu/Quit.png");
	_menuData->buttonTex[0][1].loadFromFile("Assets/Menu/New Game shade.png");
	_menuData->buttonTex[1][1].loadFromFile("Assets/Menu/Load Game shade.png");
	_menuData->buttonTex[2][1].loadFromFile("Assets/Menu/Settings shade.png");
	_menuData->buttonTex[3][1].loadFromFile("Assets/Menu/Quit shade.png");

	_menuData->joystickTex[0].loadFromFile("Assets/Menu/Controls/GamePad/A.png");
	_menuData->joystickTex[1].loadFromFile("Assets/Menu/Controls/GamePad/B.png");
	_menuData->joystickTex[2].loadFromFile("Assets/Menu/Controls/GamePad/X.png");
	_menuData->joystickTex[3].loadFromFile("Assets/Menu/Controls/GamePad/Y.png");
	_menuData->joystickTex[4].loadFromFile("Assets/Menu/Controls/GamePad/L.png");
	_menuData->joystickTex[5].loadFromFile("Assets/Menu/Controls/GamePad/R.png");
	_menuData->joystickTex[6].loadFromFile("Assets/Menu/Controls/GamePad/BACK.png");
	_menuData->joystickTex[7].loadFromFile("Assets/Menu/Controls/GamePad/START.png");
	_menuData->joystickTex[8].loadFromFile("Assets/Menu/Controls/GamePad/LEFTSTICK.png");
	_menuData->joystickTex[9].loadFromFile("Assets/Menu/Controls/GamePad/RIGHTSTICK.png");

	_menuData->buttonSound[0] = LoadSound("Assets/Menu/Sound/Do.wav");
	_menuData->buttonSound[1] = LoadSound("Assets/Menu/Sound/Re.wav");
	_menuData->buttonSound[2] = LoadSound("Assets/Menu/Sound/Mi.wav");
	_menuData->buttonSound[3] = LoadSound("Assets/Menu/Sound/Fa.wav");
	_menuData->buttonSound[4] = LoadSound("Assets/Menu/Sound/Sol.wav");
	_menuData->buttonSound[5] = LoadSound("Assets/Menu/Sound/La.wav");
	_menuData->buttonSound[6] = LoadSound("Assets/Menu/Sound/Si.wav");


	_menuData->titleTex.loadFromFile("Assets/Menu/DreamScape.png");

	sf::IntRect rectSourceSprite(79, 0, 79, 110);
	_menuData->title.setTexture(_menuData->titleTex);

	_menuData->keyFont.loadFromFile("Assets/Menu/Monocraft.otf");
	_menuData->background = LoadSprite("Assets/Menu/MenuBG.png", false);
	_menuData->background.setScale({ 3,3 });
	_menuData->opacity = 255;
	_menuData->goBack = LoadSprite("Assets/Menu/goBack.png", false);
	_menuData->goBack.setPosition({ 20,1000 });

	_menuData->buttonBuff[0].loadFromFile("Assets/Menu/buttonsound.ogg");
	_menuData->buttonBuff[1].loadFromFile("Assets/Menu/Sound/fa_majeur.wav");
	_menuData->buttonHoverSFX.setBuffer(_menuData->buttonBuff[0]);
	_menuData->buttonClickSFX.setBuffer(_menuData->buttonBuff[1]);
	for (int i = 0; i < 7; i++)
	{
		_menuData->buttonSound[i].setVolume(_menuData->volume[1]);
	}
	_menuData->buttonClickSFX.setVolume(_menuData->volume[1]);
}