#include "STUHud.hpp"
#include "ShootThemUp.hpp"
#include <fstream>

#define MAX_TIPS 3

STUGameState& gameStateInHUD = GetSTUGameState();
STUMiniBoss& MiniBossHUD = GetSTUMIniBoss();

 sf::FloatRect rect;
 sf::FloatRect rectHPBoss;

 void STUHud::LoadTips(int _num)
 {
	 std::fstream tipFile("Assets/Shoot Them Up/HUD/Tips/" + std::to_string(_num + 1) + ".txt");
	 std::string temp;
	 tips = "";

	 float size = 0;

	 while (!tipFile.eof())
	 {
		 tipFile >> temp;

		 temp += " ";
		 float sizeTemp = temp.size() * tipsText.getCharacterSize();

		 size += sizeTemp;

		 if (size > 360)
		 {
			 tips += temp + "\n";
			 size = 0;
		 }
		 else
		 {
			 tips += temp;
		 }
		
	 }

	 tipsText.setString(tips);
	 tipsText.setOrigin({ 0, tipsText.getGlobalBounds().height / 2 });
	 tipsText.setPosition({ 20,6 * SCREEN_HEIGHT / 10 });

	 tipFile.close();
 }

void STUHud::Load(void)
{
	font.loadFromFile("Assets/Shoot Them Up/Font/Monocraft.otf");

	//Left
	currentWaveText.setFont(font);
	currentWaveText.setCharacterSize(60);

	waveCapacityText.setFont(font);
	waveCapacityText.setPosition({ 20,2*SCREEN_HEIGHT / 8 });
	waveCapacityText.setCharacterSize(35);

	numOfEnemies.setFont(font);
	numOfEnemies.setCharacterSize(35);
	numOfEnemies.setPosition({ 20,4*SCREEN_HEIGHT / 8 });


	//Right
	hpText.setFont(font);
	hpText.setCharacterSize(50);
	hpText.setString("HP : ");
	hpText.setPosition({ SCREEN_WIDTH - 340, 30 });

	powerUpText.setFont(font);
	powerUpText.setCharacterSize(50);
	powerUpText.setString("Power Up: \n  %");
	powerUpText.setPosition({ SCREEN_WIDTH - 340,hpText.getPosition().y + hpText.getGlobalBounds().height +  (heartSizeY * 3)});

	scoreFinal.setFont(font);
	scoreFinal.setCharacterSize(50);
	scoreFinal.setString("Score : \n");
	scoreFinal.setPosition({ SCREEN_WIDTH - 340,powerUpText.getPosition().y + powerUpText.getGlobalBounds().height + (powerUpSizeY*4)});

	scoreTemp.setFont(font);
	scoreTemp.setCharacterSize(20);
	scoreTemp.setPosition({ SCREEN_WIDTH - 340,scoreFinal.getPosition().y + (float)(scoreFinal.getGlobalBounds().height*1.3)});

	combo.setFont(font);
	combo.setCharacterSize(30);

	highScore.setFont(font);
	highScore.setCharacterSize(20);
	highScore.setString("High Score : " + std::to_string(ScoreManger.highScore));
	highScore.setPosition({ SCREEN_WIDTH - 340,SCREEN_HEIGHT - highScore.getGlobalBounds().height - 30});

	rect.left = powerUp[1].getPosition().x;
	rect.top = powerUp[1].getPosition().y;
	rect.height = powerUp[1].getTexture()->getSize().y;
	rect.width = powerUp[1].getTexture()->getSize().x * Player.GetPowerUp() / 100;

	rectHPBoss.left = BossHp[1].getPosition().x;
	rectHPBoss.top = BossHp[1].getPosition().y;
	rectHPBoss.height = BossHp[1].getTexture()->getSize().y;
	rectHPBoss.width = BossHp[1].getTexture()->getSize().x * MiniBossHUD.GetHp() / 500;

	bossHpAlpha = 255;
}

void STUHud::UpdateText(void)
{
	//Left
	string = std::to_string(HudWave.GetCurrentWave() + 1);
	GetSTUGameState() != STU_MINI_BOSS ? currentWaveText.setString("WAVE " + string) : currentWaveText.setString("BOSS");
	currentWaveText.setOrigin({ currentWaveText.getGlobalBounds().width / 2, currentWaveText.getGlobalBounds().height / 2 });
	currentWaveText.setPosition({ 360/2, SCREEN_HEIGHT/8 });

	string = std::to_string(HudWave.GetWaveVector().size());
	waveCapacityText.setString("Enemies left : \n" + string);

	numOfEnemies.setString(
		"Willo : " + std::to_string(HudWave.numOfType1) + "\n\n"
		+ "Ghosts : "+ std::to_string(HudWave.numOfType2) + "\n\n"
		+ "Cristals : " + std::to_string(HudWave.numOfType3));



	//Right
	string = std::to_string(Player.GetHp());
	hpText.setString("HP : " + string);

	string = std::to_string((int)Player.GetPowerUp());
	powerUpText.setString("Power Up: \n" + string + " %");

	scoreFinal.setString("Score : \n" + std::to_string(ScoreManger.finalScore));
	scoreTemp.setString("+ " + std::to_string(ScoreManger.tempScore));



	combo.getCharacterSize() > 60 ?
		combo.setCharacterSize(60) :
		combo.setCharacterSize(20 + ScoreManger.combo);

	combo.setString("COMBO X" + std::to_string(ScoreManger.combo));
	combo.setOrigin(combo.getLocalBounds().width / 2.f, combo.getLocalBounds().height / 2.f);
	combo.setPosition(SCREEN_WIDTH - 360 / 2.f, combo.getLocalBounds().height + scoreTemp.getPosition().y + scoreTemp.getGlobalBounds().height);


	combo.getFillColor().r >= 250 ?
		combo.setFillColor(sf::Color(255, 0, 0)) :
		combo.setFillColor(sf::Color(255, 255 - ScoreManger.combo * 20, 255 - ScoreManger.combo * 20)) ;


	//peut-etre a retirer//
	highScore.setString("High Score : " + std::to_string(ScoreManger.highScore));
}

void STUHud::UpdatePowerUp(float _dt)
{
	if (rect.width < powerUp[1].getTexture()->getSize().x * Player.GetPowerUp() / 100)
	{
		rect.width += _dt * 100.f;
	}
	else if (Player.GetPowerUp() <= 0)
	{
		rect.width = 0;
	}

	powerUp[1].setTextureRect((sf::IntRect)rect);
}

void STUHud::UpdateHPBoss(float _dt)
{
	static sf::Clock deadBossClock;

	if (MiniBossHUD.GetHp() <= 0)
	{
		if (bossHpAlpha>5)
		bossHpAlpha = 255 - Easing::easeOutBounce(deadBossClock.getElapsedTime().asSeconds(), 0, 255, 2);
	}
	else
	{
		rectHPBoss.width = BossHp[1].getTexture()->getSize().x * MiniBossHUD.GetHp() / MAX_STU_MINI_BOSS_HP;

		BossHp[1].setTextureRect((sf::IntRect)rectHPBoss);

		deadBossClock.restart();
	}
}

void STUHud::Update(float _dt)
{
	UpdateText();
	UpdatePowerUp(_dt);
	UpdateHPBoss(_dt);

	currentHeart +=  _dt * 7;

	if (currentHeart > 8)
	{
		currentHeart = 0;
	}
}

void STUHud::Display(sf::RenderWindow& _window)
{
	static float sizeX = heartAnim[0].getTexture()->getSize().x * 3;
	static float sizeY = heartAnim[0].getTexture()->getSize().y * 3;

	static sf::Vector2f posTips = { 360/2, 6*SCREEN_HEIGHT/10 };

	BlitSprite(spriteHUD[0], {0,0}, _window,{3,3});
	BlitSprite(spriteHUD[1], {SCREEN_WIDTH - 360,0}, _window,{3,3});
	

	//Left
	if (GetSTUGameState() == STU_MINI_BOSS)
	{
		BlitSprite(BossHp[1], { (float)SCREEN_WIDTH/2, powerUpSizeY }, _window, {3,3},0,sf::Color(255,255,255, bossHpAlpha));
		BlitSprite(BossHp[0], { (float)SCREEN_WIDTH / 2, powerUpSizeY }, _window, { 3,3 }, 0, sf::Color(255, 255, 255, bossHpAlpha));
	}
	_window.draw(currentWaveText);
	_window.draw(waveCapacityText);
	_window.draw(numOfEnemies);

	//Right
	_window.draw(hpText);
	_window.draw(powerUpText);
	_window.draw(scoreFinal);

	if (ScoreManger.tempScore > 0)
	_window.draw(scoreTemp);

	if (ScoreManger.combo > 0)
		_window.draw(combo);

	_window.draw(highScore);

	BlitSprite(powerUp[1], { powerUpText.getPosition().x, powerUpText.getPosition().y + powerUpText.getGlobalBounds().height + powerUpSizeY }, _window, { 3,3 });
	BlitSprite(powerUp[0], { powerUpText.getPosition().x, powerUpText.getPosition().y + powerUpText.getGlobalBounds().height + powerUpSizeY }, _window, { 3,3 });

	for (int k = 0; k < Player.GetHp(); k++)
	{
		BlitSprite(heartAnim[(int)currentHeart], { (sizeX/2) +  hpText.getPosition().x + (k * sizeX),  (sizeY / 2) + hpText.getPosition().y + sizeY}, _window,{3,3});
	}
	
}
