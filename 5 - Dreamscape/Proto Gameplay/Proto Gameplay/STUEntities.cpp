#include "STUEntities.hpp"

WaveManager Wm;
STUPlayer player;
ParticuleManager Pm;
STUItems ItemsSTU;
STUScore ScoreSTU;

void EntitiesManager::LoadEntities(void)
{
	player.Load();
	Wm.LoadWave(Wm.actualWave[Wm.GetCurrentWave()]);
	ScoreSTU.LoadScore();
}


void EntitiesManager::UpdateEntities(float _dt, ControlsData*& m_controls)
{
	player.Update(_dt, m_controls);
	Wm.Update(_dt,player);
	Pm.UpdateParticule(_dt);
	ItemsSTU.UpdateItems(_dt);
	ScoreSTU.Update(_dt);
}

void EntitiesManager::DrawEntities(sf::RenderWindow& _window)
{
	Pm.DrawParticule(_window);
	player.Display(_window);
	Wm.Display(_window);
	ItemsSTU.DisplayItems(_window);
}

WaveManager& GetWaveManager(void)
{
	return Wm;
}

STUPlayer& GetPlayer(void)
{
	return player;
}

ParticuleManager& GetParticuleManager(void)
{
	return Pm;
}

STUItems& GetItems(void)
{
	return ItemsSTU;
}

STUScore& GetScoreManager(void)
{
	return ScoreSTU;
}