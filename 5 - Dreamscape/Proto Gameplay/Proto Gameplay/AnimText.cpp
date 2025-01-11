#include "AnimText.h"
#include <string>

AnimText::AnimText()
{

}

AnimText::~AnimText()
{

}

void AnimText::Init(std::string _file, sf::Vector2f _pos, int _line)
{ 
	openFile(_file, _pos, _line);
	initLetter();
}

void AnimText::Update(float _dt)
{
	TextEffect(_dt);
	DialogueApparition(_dt);
	UpdateTextColor();
}

void AnimText::Draw(sf::RenderWindow& _window)
{
	DisplayText(_window);
}

void AnimText::UpdateTextColor()//fonction qui colorie le texte
{
	for (int i = 0; i < dialogue.size(); i++)
	{
		dialogue[i].text.setFillColor(sf::Color(dialogue[i].text.getFillColor().r, dialogue[i].text.getFillColor().g, dialogue[i].text.getFillColor().b, dialogue[i].alpha));
	}
}

void AnimText::DisplayText(sf::RenderWindow& _window)//fonction qui affiche le texte
{
	for (int i = 0; i < dialogue.size(); i++)
	{
		if (i == currentLetter && wordStopClock.getElapsedTime().asSeconds() < WORD_WAIT)
		{
			
		}
		else
		{
			_window.draw(dialogue[i].text);
		}
	}
}

void AnimText::openFile(std::string _file, sf::Vector2f _pos, int _line)//ouvre le fichier
{
	std::ifstream file(_file);

	if (file.is_open())
	{
		std::string line;
		for (int i = 1; i <= _line; i++)
		{
			if (!std::getline(file, line))
			{
				std::cout << "Erreur : Le fichier ne contient pas la ligne spécifiée.\n";
				return;
			}
		}
		for (char c : line)
		{
			mots.push_back(Caracters());
			mots.back().letter = c;
		}
		file.close();
	}
	else
	{
		std::cout << "error in file" << std::endl;
	}
	initPos = _pos;
	StringAnalyse();
}

void foundEffect(std::string _wordToGet, std::vector<effectData>& _textEffectData, std::string _text, Effect _effect)
{
	std::size_t found = _text.find(_wordToGet);//setup la mot  a recherché
	while (found != std::string::npos)
	{
		_textEffectData.push_back(effectData());//si le mot est trouvé ajouté push back la valeur dans le vector
		switch (_effect)
		{
		case SHAKE:
			_textEffectData.back().sfx.Shake = true;//effet shake detecté
			break;
		case COLOR:
			_textEffectData.back().sfx.Color = true;//effet color detecté
			_textEffectData.back().sfx.colorLetter = _text[found + 3];
			_textEffectData.back().sfx.colorLetterOutline = _text[found + 5];
			break;
		default:
			break;
		}

		//chai plus a quoi sa sert mais si on le desactive sa empeche de démarrer 
		_textEffectData.back().limit.effectIndex = found;
		found = _text.find(_wordToGet, found + 1);
	}
}

void AnimText::findEnd(int& _end, int _beginOffset, std::string _text)
{
	int count = 0;//reinitialiser le compteur qui permet d'assigner a la bonne parenthèse
	for (int i = _beginOffset; i < _text.size(); i++)
	{
		if (_text[i] == '(')
		{
			count++;//permet d'eviter de le mettre a la mauvaise parenthèse
		}
		if (_text[i] == ')' && count > 0)
		{
			count--;//mauvaise parenthèse
		}
		if (_text[i] == ')' && count == 0)
		{
			_end = i;//bonne parenthèse, assignation de la fin
			break;
		}
	}
}

void AnimText::foundBegin(int& _begin, int _beginOffset, std::string _text)
{
	//commence a checher la première parenthèse ouvrante a partir du debut de l'effet
	for (int i = _beginOffset; i < _text.size(); i++)
	{
		if (_text[i] == '(')
		{
			_begin = i;//début trouver
			break;
		}
	}
}

void AnimText::replaceLetter(std::vector<effectData> _textEffectData)
{
	for (int i = 0; i < _textEffectData.size(); i++)
	{
		mots[_textEffectData[i].limit.begin].letter = '²';//tranforme le charactere du debut par ²
		mots[_textEffectData[i].limit.end].letter = '²';//tranforme le charactere de la fin par ²
		int offset = _textEffectData[i].limit.begin - _textEffectData[i].limit.effectIndex;
		for (int j = _textEffectData[i].limit.effectIndex; j <= _textEffectData[i].limit.effectIndex + offset; j++)
		{
			mots[j].letter = '²';
		}
	}
}

void sortVector(std::vector<effectData>& _textEffectData)
{
	int n = _textEffectData.size();
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = 0; j < n - i - 1; ++j)
		{
			if (_textEffectData[j].limit.effectIndex > _textEffectData[j + 1].limit.effectIndex)
			{
				std::swap(_textEffectData[j], _textEffectData[j + 1]);
			}
		}
	}
}

void AnimText::StringAnalyse()
{
	std::string tempText;//variable temporaire de texte

	for (int i = 0; i < mots.size(); i++)
	{
		tempText = tempText + mots[i].letter;
	}
	//string permettant de trouver les mot clées
	std::string effectBegin("(");
	std::string effectEnd(")");
	std::string colorEffect("/c_");
	std::string shakeEffect("/s_");

	//recherche d'effet
	foundEffect(colorEffect, textEffectData, tempText, COLOR);
	foundEffect(shakeEffect, textEffectData, tempText, SHAKE);
	sortVector(textEffectData);
	//recherche des limite
	for (int i = 0; i < textEffectData.size(); i++)
	{
		foundBegin(textEffectData[i].limit.begin, textEffectData[i].limit.effectIndex, tempText);
		findEnd(textEffectData[i].limit.end, textEffectData[i].limit.effectIndex, tempText);
	}

	//permet d'assigner les effets a l'essemble des lettre concerné
	for (int i = 0; i < textEffectData.size(); i++)
	{
		if (textEffectData[i].sfx.Color == true)
		{
			for (int j = textEffectData[i].limit.begin; j < textEffectData[i].limit.end; j++)
			{
				mots[j].iscolored = true;

				//faire une fonction poue les switch avecenum color
				switch (textEffectData[i].sfx.colorLetter)
				{
				case 'w':
					mots[j].colorIndex = WHITE;
					break;
				case 'M':
					mots[j].colorIndex = MULTICOLORE;
					break;
				case 'b':
					mots[j].colorIndex = BLUE;
					break;
				case 'r':
					mots[j].colorIndex = RED;
					break;
				case 'g':
					mots[j].colorIndex = GREEN;
					break;
				case 'p':
					mots[j].colorIndex = PINK;
					break;
				case 'v':
					mots[j].colorIndex = VIOLET;
					break;
				case 'o':
					mots[j].colorIndex = ORANGE;
					break;
				case 'y':
					mots[j].colorIndex = YELLOW;
					break;
				case 'n':
					mots[j].colorIndex = BLACK;
					break;
				default:
					mots[j].colorIndex = WHITE;
					break;
				}

				switch (textEffectData[i].sfx.colorLetterOutline)
				{
				case 'w':
					mots[j].outlineColor = WHITE;
					break;
				case 'M':
					mots[j].outlineColor = MULTICOLORE;
					break;
				case 'b':
					mots[j].outlineColor = BLUE;
					break;
				case 'r':
					mots[j].outlineColor = RED;
					break;
				case 'g':
					mots[j].outlineColor = GREEN;
					break;
				case 'p':
					mots[j].outlineColor = PINK;
					break;
				case 'v':
					mots[j].outlineColor = VIOLET;
					break;
				case 'o':
					mots[j].outlineColor = ORANGE;
					break;
				case 'y':
					mots[j].outlineColor = YELLOW;
					break;
				case 'n':
					mots[j].outlineColor = BLACK;
					break;
				default:
					mots[j].outlineColor = WHITE;
					break;
				}
			}
		}
		if (textEffectData[i].sfx.Shake == true)
		{
			for (int j = textEffectData[i].limit.begin; j < textEffectData[i].limit.end; j++)
			{
				mots[j].isshaked = true;
			}
		}
	}
	//permet d'effacé les mots clées
	replaceLetter(textEffectData);
	foundWord();
	font.loadFromFile("Assets/Font/Monocraft.otf");

	for (int i = 0; i < mots.size(); i++)
	{
		testString.setFont(font);
		testString.setCharacterSize(CharacterSize);
		testString.setString(testString.getString() + mots[i].letter);//rajouté la lettre a la string de test
		if (testString.getGlobalBounds().width - offsetSize > textLenght)//si dépasse la taille assigné le retour chariot
		{
			int it = i;
			bool chariotFound = false;
			do
			{
				if (mots[it].letter == ' ')
				{
					mots[it].returnLine = true;
					mots[it].letter = '\n';
					offsetSize = testString.getGlobalBounds().width;
					chariotFound = true;
				}
				it -= 1;
			} while (!chariotFound);
		}
	}
}

void AnimText::foundWord()
{
	for (int i = 0; i < mots.size(); i++)
	{
		if (mots[i].letter == '²')
		{
			mots.erase(mots.begin() + i);
			i--;
		}
	}
}

void AnimText::initLetter()
{
	for (int i = 0; i < mots.size(); i++)
	{
		Text tempText;
		tempText.text.setFont(font);
		tempText.text.setCharacterSize(CharacterSize);
		tempText.text.setString(mots[i].letter);
		if (mots[i].iscolored)
		{
			tempText.colorEffect = true;
			tempText.colorIndex = mots[i].colorIndex;
			tempText.outlineColor = mots[i].outlineColor;
		}
		if (mots[i].isshaked)
		{
			tempText.shakeEffect = true;
		}
		if (mots[i].returnLine)
		{
			tempText.returnLine = true;
		}

		sf::FloatRect currentWordBounds = tempText.text.getGlobalBounds();

		if (dialogue.size() <= 0)
		{
			tempText.text.setPosition(initPos);
			tempText.pos = tempText.text.getPosition();
		}
		else
		{
			sf::Vector2f newPos;
			if (!tempText.returnLine)
			{
				newPos =
				{
					dialogue.back().text.getGlobalBounds().left + dialogue.back().text.getGlobalBounds().width,
					dialogue.back().text.getPosition().y
				};
			}
			else
			{
				newPos =
				{
					initPos.x,
					dialogue[0].text.getGlobalBounds().top + (dialogue[0].text.getGlobalBounds().height + (lastReturn * CharacterSize))
				};
				lastReturn += 1;
			}


			tempText.text.setPosition(newPos);
			tempText.pos = newPos;
		}
		tempText.alpha = 0;
		tempText.text.setFillColor(sf::Color(255, 255, 255, tempText.alpha));
		dialogue.push_back(tempText);

	}

}

void AnimText::TextEffect(float _dt)
{
	std::random_device seed;
	std::mt19937 engine(seed());
	std::uniform_real_distribution<float> distribution(0.048, 0.05);
	static sf::Clock LucEpilepticProtection;

	for (int i = 0; i < dialogue.size(); i++)
	{
		if (dialogue[i].colorEffect == true)
		{
			switch (dialogue[i].colorIndex)
			{
			case WHITE:
				dialogue[i].text.setFillColor(sf::Color(255, 255, 255, dialogue[i].alpha));
				break;
			case MULTICOLORE:
				if (LucEpilepticProtection.getElapsedTime().asSeconds() > EPILEPTIC_RGB)
				{
					dialogue[i].text.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, dialogue[i].alpha));
				}
				break;
			case BLUE:
				dialogue[i].text.setFillColor(sf::Color(0, 0, 255, dialogue[i].alpha));
				break;
			case RED:
				dialogue[i].text.setFillColor(sf::Color(255, 0, 0, dialogue[i].alpha));
				break;
			case GREEN:
				dialogue[i].text.setFillColor(sf::Color(0, 255, 0, dialogue[i].alpha));
				break;
			case PINK:
				dialogue[i].text.setFillColor(sf::Color(255, 127, 127, dialogue[i].alpha));
				break;
			case VIOLET:
				dialogue[i].text.setFillColor(sf::Color(127, 0, 255, dialogue[i].alpha));
				break;
			case ORANGE:
				dialogue[i].text.setFillColor(sf::Color(255, 64, 0, dialogue[i].alpha));
				break;
			case YELLOW:
				dialogue[i].text.setFillColor(sf::Color(255, 255, 0, dialogue[i].alpha));
				break;
			case BLACK:
				dialogue[i].text.setFillColor(sf::Color(0, 0, 0, dialogue[i].alpha));
				break;
			default:
				dialogue[i].text.setFillColor(sf::Color(255, 255, 255, dialogue[i].alpha));
				break;
			}
			switch (dialogue[i].outlineColor)
			{
			case WHITE:
				dialogue[i].text.setOutlineColor(sf::Color(255, 255, 255, dialogue[i].alpha));
				break;
			case MULTICOLORE:
				dialogue[i].text.setOutlineColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, dialogue[i].alpha));
				break;
			case BLUE:
				dialogue[i].text.setOutlineColor(sf::Color(0, 0, 255, dialogue[i].alpha));
				break;
			case RED:
				dialogue[i].text.setOutlineColor(sf::Color(255, 0, 0, dialogue[i].alpha));
				break;
			case GREEN:
				dialogue[i].text.setOutlineColor(sf::Color(0, 255, 0, dialogue[i].alpha));
				break;
			case PINK:
				dialogue[i].text.setOutlineColor(sf::Color(255, 127, 127, dialogue[i].alpha));
				break;
			case VIOLET:
				dialogue[i].text.setOutlineColor(sf::Color(127, 0, 255, dialogue[i].alpha));
				break;
			case ORANGE:
				dialogue[i].text.setOutlineColor(sf::Color(255, 127, 0, dialogue[i].alpha));
				break;
			case YELLOW:
				dialogue[i].text.setOutlineColor(sf::Color(255, 255, 0, dialogue[i].alpha));
				break;
			case BLACK:
				dialogue[i].text.setOutlineColor(sf::Color(0, 0, 0, dialogue[i].alpha));
				break;
			default:
				dialogue[i].text.setOutlineColor(sf::Color(255, 255, 255, dialogue[i].alpha));
				break;
			}
			dialogue[i].text.setOutlineThickness(1);
		}
		if (dialogue[i].shakeEffect == true)
		{

			if (dialogue[i].alpha == 255)
			{

				float shakeTime = shakeClock.getElapsedTime().asSeconds();
				float shakeDirection = std::rand() % 360 * 3.14159f / 180.0f;
				float offsetX = dialogue[i].amplitude * std::sin(shakeTime * 2.0f * 3.14159f / 0.5 + shakeDirection);
				float offsetY = dialogue[i].amplitude * std::cos(shakeTime * 2.0f * 3.14159f / 0.5 + shakeDirection);
				dialogue[i].text.setPosition(sf::Vector2f(dialogue[i].initPos.x + offsetX, dialogue[i].initPos.y + offsetY));

				if (shakeTime > dialogue[i].frequency)
				{
					shakeClock.restart();
				}
			}
		}
	}
	if (LucEpilepticProtection.getElapsedTime().asSeconds() > EPILEPTIC_RGB)
	{
		LucEpilepticProtection.restart();
	}

}

void AnimText::DialogueApparition(float _dt)
{
	if (currentLetter < dialogue.size())
	{
		if (wordStopClock.getElapsedTime().asSeconds() >= WORD_WAIT && multiplicator == MINIMAL_MULTIPLICATOR)
		{
			if (dialogue[currentLetter].text.getString() == " ")
			{
				currentLetter++;
				wordStopClock.restart();
			}

			if (dialogue[currentLetter].alpha < 255 && multiplicator == MINIMAL_MULTIPLICATOR)
			{
				dialogue[currentLetter].alpha += _dt * 800 * multiplicator;
				dialogue[currentLetter].alpha = dialogue[currentLetter].alpha > 255 ? 255 : dialogue[currentLetter].alpha;

				if (speed > 0)
				{
					speed -= _dt * 300;
				}
				else
				{
					speed = 1;
				}
				dialogue[currentLetter].text.setPosition(dialogue[currentLetter].pos);
			}
			else
			{
				dialogue[currentLetter].alpha = 255;
				speed = 100;
				dialogue[currentLetter].initPos = dialogue[currentLetter].pos;
				currentLetter++;
			}
		}
		else if (multiplicator == SKIP_MULTIPLICATOR)
		{
			if (dialogue[currentLetter].text.getString() == " ")
			{
				currentLetter++;
				wordStopClock.restart();
			}

			while (currentLetter < dialogue.size())
			{
				dialogue[currentLetter].alpha = 255;
				speed = 100;
				dialogue[currentLetter].initPos = dialogue[currentLetter].pos;
				currentLetter++;
			}
		}
		allDisplay = false;
	}
	else
	{
		multiplicator = MINIMAL_MULTIPLICATOR;
		allDisplay = true;
	}
}
