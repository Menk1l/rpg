#include "Math.h"
#include <SFML/Graphics.hpp>

bool Math::CheckCollision(sf::FloatRect rect1, sf::FloatRect rect2) {
	return rect1.intersects(rect2);
}