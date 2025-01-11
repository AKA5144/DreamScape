#include "STUGameOver.hpp"
#include "ShootThemUp.hpp"
#include "STUEnnemie.hpp"
#include "STUEntities.hpp"

STUGameState& gameStateInGameOver = GetSTUGameState();
ShootManager& shootManagerInGameOver = GetEnnemiShootManager();
WaveManager& waveManagerInGameOver = GetWaveManager();
STUItems& ItemsInGameOver = GetItems();

void LoadSTUGameOver(void)
{

}

void RestartSTU(void)
{
	shootManagerInGameOver.Vector().clear();
	GetParticuleManager().GetVector().clear();
	waveManagerInGameOver.SetCurrentWave(0);
	ItemsInGameOver.GetVector().clear();
	LoadSTU();
}

void UpdateSTUGameOver(float _dt, GameState& _gamestate, bool& _transition, float& _noirAlpha)
{
	_transition = true;

	if (_noirAlpha >= 254)
	{
		_transition = false;
		RestartSTU();
		_gamestate = LOBBY;
	}

}

void DisplaySTUGameOver(sf::RenderWindow& _window)
{

}