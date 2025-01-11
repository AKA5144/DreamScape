#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "PlayerNeyl.hpp"

#define INIT_NORM (WINDOW_WIDTH)

void CenteredCam(sf::RenderWindow& _window, sf::View& _view, sf::Vector2f playerPos, float dt);

#endif // !CAMERA_HPP
