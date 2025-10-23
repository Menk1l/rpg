#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Character.h"
#include "Player.h"

// Functions
void move(char key, Character& player);

// Main
int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "RPG", sf::Style::Default, settings);

    const int charSpriteSize = 16;
    sf::Clock clock;
    window.setFramerateLimit(60);

    // Initializing objects
    std::vector<sf::Sprite> bullets;
    bullets.reserve(100);

    Player player;
    player.Load();

    Character skeleton;
    skeleton.dir += "Skeleton/Spritesheet.png";
    skeleton.name = "Skeleton";
    skeleton.Load();



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

        // Handeling player logic
        player.Update(deltaTime);

        // Clearing backround
        window.clear(sf::Color(20, 10, 30, 255));

        // Telling what to render
        player.Draw(window);
        skeleton.Draw(window);

        // Rendering
        window.display();
    }

    return 0;
}

