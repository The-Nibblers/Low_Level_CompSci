//
// Created by jenso on 29/09/2025.
//

#include "SpatialHash.h"

#include <iostream>

SpatialHash::SpatialHash(sf::Vector2i window, float CellSize){
    windowSize = window;
    cellSize = CellSize;
}

void SpatialHash::insertObject(Ball* ball) {
    sf::Vector2f pos = ball->shape.getPosition();

    auto cell_x = pos.x / cellSize;
    auto cell_y = pos.y / cellSize;

    std::pair<int, int> key(cell_x, cell_y);
    grid[key].push_back(ball);

    std::cout << "Cell (" << cell_x << "," << cell_y << ") has "
          << grid[{cell_x, cell_y}].size() << " balls\n";

}

void SpatialHash::removeObject(Ball* ball) {

}
