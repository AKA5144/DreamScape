#ifndef SLSHADERS_H
#define SLSHADERS_H

#include "Common.h"

class SLShaders
{
public:
    SLShaders()
    {
        m_shader.loadFromFile("Assets/Souls/Shaders/lights.frag", sf::Shader::Fragment);
    }

    void AddLight(sf::Vector2f _pos, float _intensity);
    void ApplyLights(sf::RenderWindow& _window);

private:
    struct Light
    {
        sf::Vector2f pos;
        float intensity;
        sf::Sprite sprite;
    };

    std::vector<Light> m_lights;
    sf::RenderTexture m_RTLights;
    sf::Shader m_shader;
    sf::Sprite m_sceneSprite;
};

#endif