#ifndef DEBUG_H
#define DEBUG_H

class Debug
{
public:
	static void ShowHitbox(sf::FloatRect _hitbox, sf::Color _color, sf::RenderWindow& _window)
	{
		sf::RectangleShape hitbox;
		hitbox.setFillColor(sf::Color(_color.r, _color.g, _color.b, 64));
		hitbox.setPosition(_hitbox.left, _hitbox.top);
		hitbox.setSize({ _hitbox.width, _hitbox.height });
		_window.draw(hitbox);
	}

	static void ShowPoint(sf::Vector2f _point, sf::RenderWindow& _window)
	{
		sf::CircleShape point;
		point.setFillColor(sf::Color::Blue);
		point.setRadius(2);
		point.setOrigin(2, 2);
		point.setPosition(_point);
		_window.draw(point);
	}

	static void ShowCircle(sf::Vector2f _center, float _radius, sf::Color _color, sf::RenderWindow& _window)
	{
		sf::CircleShape circle;
		circle.setFillColor(sf::Color(_color.r, _color.g, _color.b, 64));
		circle.setPosition(_center);
		circle.setRadius(_radius);
		circle.setOrigin(_radius, _radius);
		_window.draw(circle);
	}

	static void ShowFPS(float _dt, sf::RenderWindow& _window)
	{
		sf::View camera = _window.getView();
		sf::Text FPSText;

		float fps = 1 / _dt;

		static bool firstCall = false;
		static sf::Font font;
		if (!firstCall)
		{
			font.loadFromFile("Font/Nexa-Heavy.ttf");
			firstCall = true;
		}

		FPSText.setFont(font);
		FPSText.setCharacterSize(32 * camera.getSize().x / _window.getSize().x);
		FPSText.setString("FPS : " + std::to_string((int)fps));

		FPSText.setPosition(camera.getCenter() - camera.getSize() / 2.f);

		fps < 60 ? FPSText.setFillColor(sf::Color::Red) : FPSText.setFillColor(sf::Color::White);
		_window.draw(FPSText);
	}

	static void CoutVector(sf::Vector2f _vector) { std::cout << _vector.x << "x : " << _vector.y << "y" << std::endl; }
	static void CoutFloatRect(sf::FloatRect _rect) { std::cout << _rect.left << "x : " << _rect.top << "y : " << _rect.width << "w : " << _rect.height << "h" << std::endl; }

private:
};

#endif