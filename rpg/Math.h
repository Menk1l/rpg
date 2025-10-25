#pragma once
#include <SFML/Graphics.hpp>

class Math {
	public:
		static bool CheckCollision(sf::FloatRect rect1, sf::FloatRect rect2);
};