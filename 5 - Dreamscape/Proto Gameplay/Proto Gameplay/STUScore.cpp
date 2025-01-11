#include "STUScore.hpp"
#include "ShootThemUp.hpp"
#include <fstream>

STUHud& hudInScore = GetSTUHud();

void STUScore::LoadScore(void)
{
	tempScore = 0;
	finalScore = 0;
	highScore = 0;

	combo = 0;
	comboTimer = 1.5;
	actualTimer = 0;

	std::fstream HighScore("Assets/Shoot Them Up/HUD/HighScore.txt", std::ios::in);

	while (!HighScore.eof())
	{
		HighScore >> highScore;
	}

	HighScore.close();
}

void STUScore::SaveHighScore(void)
{
	std::fstream HighScore("Assets/Shoot Them Up/HUD/HighScore.txt", std::ios::out);

	HighScore << highScore;
	
	HighScore.close();
}

void STUScore::AddScore(int _score)
{
	actualTimer = 0;
	combo++;
	tempScore += _score * combo;

	hudInScore.SetComboAngle(-combo + rand() % (combo *2));
}

void STUScore::Update(float _dt)
{
	if (actualTimer > comboTimer)
	{
		finalScore += tempScore;
		tempScore = 0;
		combo = 0;
	}
	else
	{
		actualTimer += _dt;
	}

	if (finalScore > highScore)
	{
		highScore = finalScore;
	}
}