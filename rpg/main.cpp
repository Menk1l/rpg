#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Character.h"
#include "Player.h"
#include "Math.h"

// Main
int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "RPG", sf::Style::Default, settings);

    sf::Clock clock;
	window.setVerticalSyncEnabled(true);

    Player player;
    player.Load();

    Character skeleton;
    skeleton.dir += "Skeleton/Spritesheet.png";
    skeleton.name = "Skeleton";
    skeleton.Load();
	skeleton.SetPosition(600.0f, 300.0f);


    // Game Loop
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {       // Checks for events(quitting)
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Calculating Delta Time
        sf::Time deltaTimer = clock.restart();
        float deltaTime = deltaTimer.asSeconds();

        // Clearing backround
        window.clear(sf::Color(20, 10, 30, 255));

        // Handeling player logic
        player.Update(deltaTime);
        // Handeling enemy logic
        skeleton.Update(deltaTime);

        // Telling what to render
        skeleton.Draw(window);
        player.Draw(window);

		// Checking collision
		if (Math::CheckCollision(player.hitbox.getGlobalBounds(), skeleton.hitbox.getGlobalBounds())) {
			std::cout << "Collision Detected" << '\n';
		}

        // Rendering
        window.display();
    }

    return 0;
}

