#include "Character.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Character::Character() {
	Xpos = 0;
	Ypos = 0;
	Xindex = 0;
	Yindex = 0;
	spriteSize = 16;
	speed = 250;
	health = 100;
	attack = 5;
	name = "Default";
	dir = "Assets/Actor/Characters/";
	currentState = IDLE;
	currentDirection = 'd';
	isMoving = false;
	animationTimer = 0.0f;
	currentFrame = 0;
}

void Character::Load() {
	if (texture.loadFromFile(dir)) {
		std::cout << name << " texture loaded" << '\n';
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(Xindex * spriteSize, Yindex * spriteSize, spriteSize, spriteSize));
		sprite.scale(3, 3);
	}
	else std::cout << name << " texture failed load" << '\n';
}

void Character::Update(float deltaTime) {
	if (currentState == WALK) {
		animationTimer += deltaTime;

		// Change frame every 0.15 seconds (150ms)
		const float frameTime = 0.15f;

		if (animationTimer >= frameTime) {
			animationTimer -= frameTime;  // Keep remainder for smooth timing

			// Cycle through 4 walking frames (0, 1, 2, 3)
			currentFrame = (currentFrame + 1) % 4;

			switch (currentDirection) {
			case 'D':
				sprite.setTextureRect(sf::IntRect(0 * spriteSize, currentFrame * spriteSize, spriteSize, spriteSize));
				break;
			case 'U':
				sprite.setTextureRect(sf::IntRect(1 * spriteSize, currentFrame * spriteSize, spriteSize, spriteSize));
				break;
			case 'L':
				sprite.setTextureRect(sf::IntRect(2 * spriteSize, currentFrame * spriteSize, spriteSize, spriteSize));
				break;
			case 'R':
				sprite.setTextureRect(sf::IntRect(3 * spriteSize, currentFrame * spriteSize, spriteSize, spriteSize));
				break;

			}
		}
	}
	else if (currentState == IDLE) {
		currentFrame = 0;
		sprite.setTextureRect(sf::IntRect(0, 0, spriteSize, spriteSize));
	}
}

void Character::Draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

