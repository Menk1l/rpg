#pragma once
#include <SFML/Graphics.hpp>

class Character {
protected:
    int Xpos;
    int Ypos;
    int Xindex;
    int Yindex;
    int spriteSize;
    float speed;
    float health;
    float attack;

    // Animation variables
    float animationTimer;
    int currentFrame;

    sf::Texture texture;
    sf::Sprite sprite;
public:
    Character();
    void Load();
    virtual void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);
    std::string name;
    std::string dir;
    char currentDirection;
    bool isMoving;

    enum State {
        IDLE,
        WALK,
        ATTACK,
        DEAD,
        ITEM,
        JUMP,
        SPECIAL1,
        SPECIAL2
    };
    State currentState;
};
