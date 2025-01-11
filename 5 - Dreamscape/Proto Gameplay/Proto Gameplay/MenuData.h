#ifndef GAMEDATA__H
#define GAMEDATA__H

#include <iostream>
#include <vector>

#include "common.h"
#include "GameState.h"
#include "Easing.h"

class ControlsData
{
public:
	sf::Keyboard::Key keyBinding[6] = { sf::Keyboard::Key::Z,sf::Keyboard::Key::S,sf::Keyboard::Key::Q,sf::Keyboard::Key::D,sf::Keyboard::Key::LControl,sf::Keyboard::Key::LAlt };
	ControllerButton controllerBinding[2] = { ControllerButton::A,ControllerButton::X };
};

class MenuData
{
public:

	sf::Clock clockbutton;
	bool startClock = false;

	float time;
	float scale = 3.f;

	sf::View menuView;

	int actualButtonSound = 0;

	sf::Sound buttonSound[7];

	sf::Text creditsText[10];
	sf::Text groupText[2];
	sf::Text creditTitleText[2];
	std::string creditsString[10] = { "ALMENAR Killian","D'EURVEILHER Luc","DE SOUZA Charles","MAHFOUF Neyl","MORITS Yohann","RICHARD Antoine","CASTELLANO Andréa","GRATREAUD Lana","KERGUEN Ronan","LEBRET Elodie" };
	std::string groupString[2] = { "PROGRAMMERS : ","ARTISTS : " };



	int menuCursorKeyboard = 0;
	int menuCursorJoystick = 0;
	int menuCursor = 0;
	int resolutionCursor = 2;
	bool caseChoiced[3] = { true,true,false };
	bool canCheck = true;
	bool quitConfirmation = false;
	bool controllerIsChosing[2] = { false,false };
	bool controlMode = true;
	bool choosingControl = false;
	GameState pauseOldState = MENU;
	bool achievementsCheck[4] = { false,false,false,false };
	bool buttonSFXplayed[4] = { true,false,false,false };
	float volume[3] = { 100.f,100.f,100.f };

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	sf::Sound buttonHoverSFX;
	sf::Sound buttonClickSFX;
	sf::SoundBuffer buttonBuff[2];

	sf::Vector2u windowSize[3] = { {854,480},{1280,720},{1920,1080} };
	sf::Sprite menuButton[4];
	sf::Texture joystickTex[10];
	sf::Texture quitText[2][2];
	sf::Texture keyTex[106];
	sf::Sprite blackBg;
	sf::Sprite quitSprite[3];
	sf::Sprite keySprite[6];
	sf::Sprite joystickSprite[2];
	sf::Sprite settingsButton[5];
	sf::Sprite pauseButtons[4];
	sf::Texture achievementsTex[4][2];
	sf::Sprite achievementsSprite[4];
	sf::Texture buttonTex[13][2];
	sf::Sprite background;
	sf::Sprite goBack;
	sf::Sprite title;
	sf::Sprite soundBar[3][2];
	sf::Sprite soundCursor[3];
	sf::Sprite settingsCase[3][2];
	sf::Text settingsText[3];
	sf::Text buttonText[2][3];
	sf::Text keyText[6];
	sf::Text joystickText[6];
	sf::Text controlsText[6];
	sf::Text audioText[3];
	sf::Text videoText[2];
	sf::Text resolutionText[3];
	sf::Sprite pauseText;
	sf::Font keyFont;
	sf::Color color = sf::Color::White;
	sf::Vector2f posSprite[14];
	sf::Texture titleTex;
	float timerOpa = 0;
	float timerSound = 0;
	float mainTimer = 0;
	float timerControl[2] = { 0.f,0.2f };
	sf::Sound tropiSound;
	sf::Music menuMusic;
	sf::SoundBuffer tropiBuffer;
	sf::SoundBuffer menuBuffer;
	bool soundPlayed = false;
	bool musicPlaying = false;
	bool returnMenu = false;
	float y_velocity[13];
	float opacity = 255;
	MenuStateEnum gameState = MAINMENU;

	bool pause = false;

};



#endif