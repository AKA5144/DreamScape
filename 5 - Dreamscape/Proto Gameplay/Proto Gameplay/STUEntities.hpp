#ifndef STUENTITIES_HPP
#define STUENTITIES_HPP


#include "Common.h"
#include "STUPlayer.hpp"
#include "STUWaveManager.hpp"
#include "STUItems.hpp"
#include "STUScore.hpp"
#include "Particules.hpp"

#define MAX_POWER_UP 100

class EntitiesManager
{
public:

	void LoadEntities(void);
	void UpdateEntities(float _dt, ControlsData*& m_controls);
	void DrawEntities(sf::RenderWindow& _window);

private:

};

WaveManager& GetWaveManager(void);
STUPlayer& GetPlayer(void);
ParticuleManager& GetParticuleManager(void);
STUItems& GetItems(void);
STUScore& GetScoreManager(void);
#endif