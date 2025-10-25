#include "Character.h"
#include "Math.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Character::Character() {
	Xpos = 0;
	Ypos = 0;
	Xindex = 0;
	Yindex = 0;
	spriteSize = 16;
	sizeMultiplier = 5;
	speed = 250;
	health = 100;
	attack = 5;
	name = "Default";
	dir = "Assets/Actor/Characters/";
	currentState = IDLE;
	currentDirection = 'D';
	isMoving = false;
	currentFrame = 0;
}

void Character::Load() {
	if (texture.loadFromFile(dir)) {
		std::cout << name << " texture loaded" << '\n';
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(Xindex * spriteSize, Yindex * spriteSize, spriteSize, spriteSize));
		sprite.scale(sizeMultiplier , sizeMultiplier);
		
		// Collision rectangle
		boundingRect.setSize(sf::Vector2f(spriteSize * sizeMultiplier, spriteSize * sizeMultiplier));
		boundingRect.setFillColor(sf::Color::Transparent);
		boundingRect.setOutlineColor(sf::Color::Red);
		boundingRect.setOutlineThickness(1);
	}
	else std::cout << name << " texture failed load" << '\n';
}

void Character::Update(float deltaTime) {
	// Saving positions
	sf::Vector2f pos = sprite.getPosition();
	boundingRect.setPosition(pos);
	Xpos = sprite.getPosition().x;
	Ypos = sprite.getPosition().y;


	static State previousState = IDLE;

	// Reset state timer when state changes
	if (currentState != previousState) {
		stateTimer = 0.0f;
		previousState = currentState;
	}

	// Increment state timer
	stateTimer += deltaTime;

	// Animations
	if (currentState == IDLE) {
		Animation(deltaTime, 1, 0);
	}
	else if (currentState == WALK) {
		Animation(deltaTime, 4, 0);
	}
	else if (currentState == ATTACK) {
		SingleFrame(4);
		// After 0.2 seconds, return to IDLE
		if (stateTimer >= 0.2f) {
			currentState = IDLE;
			stateTimer = 0.0f;
		}
	}
	else if (currentState == JUMP) {
		SingleFrame(5);
		if (stateTimer >= 0.2f) {
			currentState = IDLE;
			stateTimer = 0.0f;
		}
	}
	else if (currentState == SPECIAL1) {
		SingleFrame(6);
	}
	else if (currentState == SPECIAL2) {
		SingleFrame(7);
	}
	else if (currentState == DEAD) {
		SingleFrame(8);
	}
	else // IDLE
		Animation(deltaTime, 1, 0);

}

void Character::Draw(sf::RenderWindow& window) {
	window.draw(sprite);
	window.draw(boundingRect);
};

void Character::Animation(float deltaTime, int frames, int Ypos) {
    animationTimer += deltaTime;

    // Change frame every 0.20 seconds
    const float frameTime = 0.20f;

    if (animationTimer >= frameTime) {
        animationTimer -= frameTime;  // Keep remainder for smooth timing


        // Cycle through n animation frames (0, 1, 2, 3)
		if (frames == 1)
			currentFrame = 0;
		else
			currentFrame = (currentFrame + 1) % frames;

        switch (currentDirection) {
        case 'D':
			sprite.setTextureRect(sf::IntRect(0 * spriteSize, (Ypos + currentFrame) * spriteSize, spriteSize, spriteSize));
            break;
        case 'U':
            sprite.setTextureRect(sf::IntRect(1 * spriteSize, (Ypos + currentFrame) * spriteSize, spriteSize, spriteSize));
            break;
        case 'L':
            sprite.setTextureRect(sf::IntRect(2 * spriteSize, (Ypos + currentFrame) * spriteSize, spriteSize, spriteSize));
            break;
        case 'R':
            sprite.setTextureRect(sf::IntRect(3 * spriteSize, (Ypos + currentFrame) * spriteSize, spriteSize, spriteSize));
            break;
        }
    }
}

void Character::SingleFrame(int Ypos) {
	switch (currentDirection) {
	case 'D':
		sprite.setTextureRect(sf::IntRect(0 * spriteSize, Ypos * spriteSize, spriteSize, spriteSize));
		break;
	case 'U':
		sprite.setTextureRect(sf::IntRect(1 * spriteSize, Ypos * spriteSize, spriteSize, spriteSize));
		break;
	case 'L':
		sprite.setTextureRect(sf::IntRect(2 * spriteSize, Ypos * spriteSize, spriteSize, spriteSize));
		break;
	case 'R':
		sprite.setTextureRect(sf::IntRect(3 * spriteSize, Ypos * spriteSize, spriteSize, spriteSize));
		break;
	}
}


