#include "GameData.h"

int main(void)
{
	GameData* gameData = new GameData;

	gameData->Init();

	while (gameData->m_window.isOpen())
	{
		gameData->Event();
		gameData->Update();
		gameData->Display();
	}
}