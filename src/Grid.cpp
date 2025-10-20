//
// Created by jenso on 15/10/2025.
//

#include "Grid.h"

#include <iostream>
#include <random>

Grid::Grid(int windowWidth, int windowHeight) {
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
}

bool Grid::get(std::pair<int,int> coords) {
    auto it = grid.find(coords);
    if (it != grid.end()) {
        return it->second.alive;
    }
    return false;
}

void Grid::set(std::pair<int,int> coords, bool alive) {
    grid[coords].alive = alive;
}

void Grid::clear() {
    for (auto& kv : grid) {
        kv.second.alive = false;
    }
}

void Grid::gridSetup() {
    cellHeight = windowHeight / gridHeigth;
    cellwidth  = windowWidth  / gridWidth;

    int w = gridWidth;
    int h = gridHeigth;

    grid.clear();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution randomAlive(0.3);

    std::ranges::for_each(std::ranges::views::iota(0, w * h), [&](int i) {
        int x = i % w;
        int y = i / w;
        bool alive = randomAlive(gen);
        grid.insert({{x, y}, Cell{alive}});
    });
}