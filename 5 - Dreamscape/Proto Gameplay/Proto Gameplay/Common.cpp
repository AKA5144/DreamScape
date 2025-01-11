#include "Common.h"

sf::Sound LoadSound(std::string file)
{
	sf::Sound sound;
	sf::SoundBuffer* tempBuffer = new sf::SoundBuffer();
	tempBuffer->loadFromFile(file);
	sound.setBuffer(*tempBuffer);

	return sound;
}

sf::Sprite LoadSprite(std::string _path, bool _centered)
{
	sf::Sprite sprite;
	sf::Texture* texture = new sf::Texture();

	texture->loadFromFile(_path);
	sprite.setTexture(*texture);

	if (_centered)
	{
		sprite.setOrigin({ (float)texture->getSize().x / 2, (float)texture->getSize().y / 2 });
	}

	return sprite;
}

sf::Text LoadText(const std::string _fontPath, sf::String _string, float _characterSize, sf::Vector2f _pos, sf::Color _color, bool _isCentered )
{
	sf::Text tempText;
	sf::Font* tempFont = new sf::Font();

	tempFont->loadFromFile(_fontPath);
	tempText.setFont(*tempFont);

	tempText.setString(_string);
	tempText.setCharacterSize(_characterSize);
	tempText.setPosition(_pos);
	tempText.setFillColor(_color);

	if (_isCentered)
	{
		tempText.setOrigin(tempText.getGlobalBounds().width / 2, tempText.getGlobalBounds().height / 2);
	}

	return tempText;
}

void BlitSprite(sf::Sprite _sprite, sf::Vector2f _pos, sf::RenderWindow& _window, sf::Vector2f _scale, float _rotation, sf::Color _color)
{
	_sprite.setPosition(_pos);
	_sprite.setScale(_scale);
	_sprite.setRotation(_rotation);
	_sprite.setColor(_color);
	_window.draw(_sprite);
}

void BlitSprite(sf::Sprite _sprite, sf::Vector2f _pos, sf::RenderTexture& _window, sf::Vector2f _scale, float _rotation, sf::Color _color)
{
	_sprite.setPosition(_pos);
	_sprite.setScale(_scale);
	_sprite.setRotation(_rotation);
	_sprite.setColor(_color);
	_window.draw(_sprite);
}

void BlitSpriteAdd(sf::Sprite _sprite, sf::Vector2f _pos, sf::RenderWindow& _window, sf::Vector2f _scale, float _rotation, sf::Color _color)
{
	sf::RenderStates states;
	states.blendMode = sf::BlendAdd;

	_sprite.setPosition(_pos);
	_sprite.setScale(_scale);
	_sprite.setRotation(_rotation);
	_sprite.setColor(_color);

	_window.draw(_sprite,states);
}

void DrawPixel(sf::Image& _image, int _posX, int _posY, sf::Color _color)
{
	if (_posX > 0 && _posY > 0 && _posX < SCREEN_WIDTH && _posY < SCREEN_HEIGHT)
	{
		_image.setPixel(_posX, _posY, _color);
	}
}

sf::Vector2f CenterPos(std::string _sNom)
{
	sf::Sprite tempSprite;
	sf::Texture* tempTexture = new sf::Texture();
	tempTexture->loadFromFile(_sNom);
	tempSprite.setTexture(*tempTexture);
	sf::Vector2u tempTaille = tempTexture->getSize();
	sf::Vector2f nouvelleTaille(tempTaille.x / 4.0f, tempTaille.y / 4.0f);
	return nouvelleTaille;
}


