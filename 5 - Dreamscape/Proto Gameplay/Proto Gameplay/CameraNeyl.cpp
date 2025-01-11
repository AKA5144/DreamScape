#include "CameraNeyl.hpp"

void CenteredCam(sf::RenderWindow& _window, sf::View& _view, sf::Vector2f playerPos, float dt)
{
    sf::Vector2f posPlayer1 = playerPos;

    _view.setSize({ SCREEN_WIDTH /3, SCREEN_HEIGHT/3 });

    _window.setView(_view);
}