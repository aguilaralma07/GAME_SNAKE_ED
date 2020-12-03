#include<iostream>
#include <SFML/Graphics.hpp>
#include<box2d/box2d.h>

#include "Character.hh"
#include "Background.hh"
#include "Inputs.hh"
#include "Tile.hh"
#include "GameObject.hh"
#include "ContactListener.hh"
#include "Score.hh"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GAME_NAME "GAME SNAKE"
#define TILES1 "assets/sprites/tiles1.png"
#define TILES2 "assets/sprites/tiles2.png"
#define SPRITE_SCALE 4.f
#define FPS 120
#define GEL_MOVESPEED 3.0f

int main()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), GAME_NAME);
    sf::Image* iconTexture{new sf::Image()};
    window->setIcon(32, 32, iconTexture->getPixelsPtr());
    sf::Event event;

    b2Vec2* gravity{new b2Vec2(0.f, 0.f)};
    b2World* world{new b2World(*gravity)}; 

    sf::Clock* clock{new sf::Clock()};
    float deltaTime{};

    window->setFramerateLimit(FPS);
    Inputs* inputs{new Inputs()};
    sf::Texture* tilesTexture1{new sf::Texture()};
    tilesTexture1->loadFromFile(TILES1);
    sf::Texture* tilesTexture2{new sf::Texture()};
    tilesTexture2->loadFromFile(TILES2);

    const float tileBaseWidth{16 * SPRITE_SCALE};
    const float tileBaseHeight{16 * SPRITE_SCALE};
    Character* character1{new Character(tilesTexture1, 16 * 1, 16 * 5, 16, 16, 
    SPRITE_SCALE, SPRITE_SCALE, new b2Vec2(400, 300), b2BodyType::b2_dynamicBody, world, window)};
    character1->SetAnimations(
        new Animation*[2]
        {
            new Animation(0, 0, 5, character1->GetSprite(), 40.f),
            new Animation(1, 0, 5, character1->GetSprite(), 50.f)
        }
    );
    
    character1->SetTagName("gel");

    unsigned int N{10}, M{13};
    Maze* maze1{new Maze(N, M, SPRITE_SCALE, 16, tilesTexture2, "assets/mazes/maze1.txt", world)};
    Maze* maze2{new Maze(N, M, SPRITE_SCALE, 16, tilesTexture2, "assets/mazes/maze2.txt", world)};
    Maze*& currentMaze{*&maze1};

    while (window->isOpen())
    {
        while (window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window->close();
            }
        }

        
        Vec2* keyboardAxis{inputs->GetKeyboardAxis()};
        Vec2* joystickAxis{inputs->GetJoystickAxis()};

        if(sf::Joystick::isConnected(0))
        {
            character1->Move(new b2Vec2(joystickAxis->x * deltaTime * GEL_MOVESPEED, joystickAxis->y * deltaTime * GEL_MOVESPEED));
            character1->FlipSpriteX(joystickAxis->x);

            if(std::abs(joystickAxis->x) > 0 || std::abs(joystickAxis->y) > 0)
            {
                character1->GetAnimation(1)->Play(deltaTime);
            }
            else
            {
                character1->GetAnimation(0)->Play(deltaTime);
            }
        }
        else
        {
            character1->Move(new b2Vec2(keyboardAxis->x * deltaTime * GEL_MOVESPEED, keyboardAxis->y * deltaTime * GEL_MOVESPEED));
            character1->FlipSpriteX(keyboardAxis->x);

            if(std::abs(keyboardAxis->x) > 0 || std::abs(keyboardAxis->y) > 0)
            {
          
                character1->GetAnimation(1)->Play(deltaTime);
            }
            else
            {
          
                character1->GetAnimation(0)->Play(deltaTime);
            }
        }

        window->clear(*(new sf::Color(0, 0, 0, 0)));

        for(auto& mazeTile : *currentMaze->GetContainer())
        {
            window->draw(*mazeTile->GetSprite());
        }
    return 0;
}