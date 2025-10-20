//
// Created by jenso on 15/10/2025.
//

#ifndef LOW_LEVEL_SETUP_GAMERULES_H
#define LOW_LEVEL_SETUP_GAMERULES_H

#include "Grid.h"
#include "SFML/Graphics/RenderWindow.hpp"

class GameRules {
public:
    explicit GameRules(Grid& grid);

    void update();
    void render(sf::RenderWindow& window);

private:
    Grid& grid;

    int countAliveNeighbours(int x, int y);
};


#endif //LOW_LEVEL_SETUP_GAMERULES_H