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
    static bool wasMousePressed = false;
	static bool jumped = false;
    bool isMoving = false;

    // Skip input processing if character is in an action state
    bool isInActionState = (currentState == ATTACK);
    
    if (!isInActionState) {
        // Movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            move('W', deltaTime);
            isMoving = true;
			// Only set WALK if not in JUMP state
            if (currentState != JUMP) {
                currentState = WALK;
            }
            currentDirection = 'U';
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            move('A', deltaTime);
            isMoving = true;
            if (currentState != JUMP) {
                currentState = WALK;
            }
            currentDirection = 'L';
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            move('S', deltaTime);
            isMoving = true;
            if (currentState != JUMP) {
                currentState = WALK;
            }
            currentDirection = 'D';
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            move('D', deltaTime);
            isMoving = true;
            if (currentState != JUMP) {
                currentState = WALK;
            }
            currentDirection = 'R';
        }

        // Only set IDLE if not moving AND not in JUMP state
        if (!isMoving && currentState != JUMP) {
            currentState = IDLE;
        }

        // Attack
        bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        if (isMousePressed && !wasMousePressed) {
            std::cout << "Player Attack!" << '\n';
            isMoving = true;
            currentState = ATTACK;
        }
        wasMousePressed = isMousePressed;

        // Jump
        bool isJumping = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
        if (isJumping && !jumped) {
            std::cout << "Player Jump!" << '\n';
            isMoving = true;
            currentState = JUMP;
        }
        jumped = isJumping;
    } else {
        // Reset input flags while in action state
        wasMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        jumped = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    }

    Character::Update(deltaTime);
}