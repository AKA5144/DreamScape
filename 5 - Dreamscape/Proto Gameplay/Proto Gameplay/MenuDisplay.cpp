#include "MenuDisplay.h"



/*TODO: écrire le corps de la fonction Display, qui dessine le background, 
* les vaisseaux, le joueur, les obstacles, puis les éléménts d'UI
*/

void MenuDisplay(MenuData* _menuData, sf::RenderWindow& _window, ControlsData m_controls)
{

	_window.setView(_menuData->menuView);
	_window.draw(_menuData->background);
	switch (_menuData->gameState)
	{
	case(MAINMENU):
		for (int i = 0; i < 4; i++)
		{
			
			BlitSprite(_menuData->menuButton[i], { _menuData->menuButton[i].getPosition().x, _menuData->menuButton[i].getPosition().y }, _window, { _menuData->scale,_menuData->scale });

		}
	

	BlitSprite(_menuData->title, { _menuData->title.getPosition().x, _menuData->title.getPosition().y },_window, _menuData->title.getScale());
	
		break;
	case(INTRO):

		break;
	case(GAME):
		
		break;
	case(SETTINGS):
		DisplaySettings(_menuData, _window);
		break;
	case(SOUND):
		DisplaySoundSettings(_menuData, _window);

		break;
	case(CONTROLS):
		DisplayControls(_menuData, _window, m_controls);

		break;
	case(VIDEO):
		DisplayVideoSettings(_menuData, _window);
		break;
	case(CREDITS):
		DisplayCredits(_menuData,_window);
	}

}