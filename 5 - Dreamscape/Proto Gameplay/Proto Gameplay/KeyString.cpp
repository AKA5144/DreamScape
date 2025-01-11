#include "KeyString.h"


sf::Keyboard::Key AnyKey()
{
    for (int i = 0; i < sf::Keyboard::KeyCount; ++i)
    {
        sf::Keyboard::Key key = static_cast<sf::Keyboard::Key>(i);
        if (sf::Keyboard::isKeyPressed(key))
        {
            return key;
        }
    }
    return sf::Keyboard::Key::Unknown;
}

ControllerButton AnyButton()
{
    if(sf::Joystick::isButtonPressed(0,(unsigned int)ControllerButton::A))
    {
        return ControllerButton::A;
    }
    if (sf::Joystick::isButtonPressed(0, (unsigned int)ControllerButton::B))
    {
        return ControllerButton::B;
    }
    if (sf::Joystick::isButtonPressed(0, (unsigned int)ControllerButton::X))
    {
        return ControllerButton::X;
    }
    if (sf::Joystick::isButtonPressed(0, (unsigned int)ControllerButton::Y))
    {
        return ControllerButton::Y;
    }
    if (sf::Joystick::isButtonPressed(0, (unsigned int)ControllerButton::RB))
    {
        return ControllerButton::RB;
    }
    if (sf::Joystick::isButtonPressed(0, (unsigned int)ControllerButton::LB))
    {
        return ControllerButton::LB;
    }
    if (sf::Joystick::isButtonPressed(0, (unsigned int)ControllerButton::R3))
    {
        return ControllerButton::R3;
    }
    if (sf::Joystick::isButtonPressed(0, (unsigned int)ControllerButton::L3))
    {
        return ControllerButton::L3;
    }
    if (sf::Joystick::isButtonPressed(0, (unsigned int)ControllerButton::START))
    {
        return ControllerButton::START;
    }
    if (sf::Joystick::isButtonPressed(0, (unsigned int)ControllerButton::SELECT))
    {
        return ControllerButton::SELECT;
    }
    return ControllerButton::UNKNOWN;
}

void CheckSameKey(MenuData* _menuData, ControlsData*& m_controls)
{
    for (int i = 0; i < 6; i++)
    {
        if (i != _menuData->menuCursor)
        {
            if (m_controls->keyBinding[_menuData->menuCursor] == m_controls->keyBinding[i])
            {
                m_controls->keyBinding[i] = sf::Keyboard::Key::Unknown;
                _menuData->keyText->setString("_");
            }
        }
    }
}