#pragma once
#include "Character.h"

class Player : public Character {
private:
    void move(char key, float deltaTime);

public:
    Player();
    void Update(float deltaTime) override;
};
