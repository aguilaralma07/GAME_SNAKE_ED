#include "Inputs.hh"

Inputs::Inputs(){}

Vec2* Inputs::GetKeyboardAxis()
{
    //la clase Keyboard trae la inputs del teclado
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        x = -1;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        x = 1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        y = 1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        y = -1;
    }
    return new Vec2(x, -y);
}

Vec2* Inputs::GetJoystickAxis()
{
    x = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) / 100;
    y = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) / 100;

    x = x > 0.2f ? 1 : x < -0.2f ? -1 : 0;
    y = y > 0.2f ? 1 : y < -0.2f ? -1 : 0;

    return new Vec2(x, y);
}