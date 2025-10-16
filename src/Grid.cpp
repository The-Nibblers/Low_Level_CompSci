//
// Created by jenso on 15/10/2025.
//

#include "Grid.h"

#include <iostream>

Grid::Grid(int windowWidth, int windowHeight) {
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
}

bool Grid::get(std::pair<int,int> coords) {

    return false;
}

void Grid::set(std::pair<int,int> coords, bool alive) {

}

void Grid::clear() {

}

void Grid::gridSetup() {
   cellHeight = windowHeight / gridHeigth;
    cellwidth = windowWidth / gridWidth;

    int w = gridWidth + 1;
    int h = gridHeigth + 1;

    std::ranges::for_each(std::views::iota(0, w * h), [&](int i) {
        int x = i % w;
        int y = i / w;
        grid.insert({{x,y}, Cell{true}} );
    });

    for (const auto& kv : grid) {
        const auto& key = kv.first;
        const auto& cell = kv.second;
        std::cout << key.first << " " << key.second << " " << cell.alive << "\n";
    }
}
