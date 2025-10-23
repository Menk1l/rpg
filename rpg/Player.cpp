#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"

Player::Player() {
    name = "Player";
    dir = "Assets/Actor/Characters/Boy/SpriteSheet.png";
}

void Player::move(char key, float deltaTime) {
    sf::Vector2f pos = sprite.getPosition();

    switch (key) {
    case 'W':
        sprite.setPosition(pos - sf::Vector2f(0, 1) * speed * deltaTime);
        break;
    case 'A':
        sprite.setPosition(pos - sf::Vector2f(1, 0) * speed * deltaTime);
        break;
    case 'S':
        sprite.setPosition(pos + sf::Vector2f(0, 1) * speed * deltaTime);
        break;
    case 'D':
        sprite.setPosition(pos + sf::Vector2f(1, 0) * speed * deltaTime);
        break;
    default:
        std::cout << "Player movement failed" << '\n';
    }
}

void Player::Update(float deltaTime) {
    bool isMoving = false;

    // Player movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        move('W', deltaTime);
        isMoving = true;
        currentDirection = 'U';
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        move('A', deltaTime);
        isMoving = true;
        currentDirection = 'L';
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        move('S', deltaTime);
        isMoving = true;
        currentDirection = 'D';
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        move('D', deltaTime);
        isMoving = true;
        currentDirection = 'R';
    }

    currentState = isMoving ? WALK : IDLE;

    Character::Update(deltaTime);
}