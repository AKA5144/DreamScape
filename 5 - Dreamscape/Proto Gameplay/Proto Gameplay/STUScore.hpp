#ifndef STUSCORE_HPP
#define STUSCORE_HPP

#include "Common.h"

class STUScore
{
public:
	STUScore() {};
	~STUScore() {};

	void LoadScore(void);
	void SaveHighScore(void);
	void AddScore(int _score);
	void Update(float _dt);

	int tempScore = 0;
	int finalScore = 0;
	int highScore = 0;

	int combo = 0;
	float comboTimer = 1;
	float actualTimer = 0;
private:

};

#endif
