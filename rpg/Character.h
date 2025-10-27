#pragma once
#include <SFML/Graphics.hpp>

class Character {
protected:
    int Xpos;
    int Ypos;
    int Xindex;
    int Yindex;
    int spriteSize;
    int sizeMultiplier;
    float speed;
    float health;
    float attack;
    float stateTimer;

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
    void Animation(float deltaTime, int frames, int Ypos);
    void SingleFrame(int Ypos);
    std::string name;
    std::string dir;
    char currentDirection;
    bool isMoving;
    sf::RectangleShape hitbox;
    void SetPosition(float x, float y);


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

    State previousState;
};