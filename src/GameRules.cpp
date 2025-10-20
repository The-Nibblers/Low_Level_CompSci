//
// Created by jenso on 15/10/2025.
//

#include "GameRules.h"

#include <ranges>

#include "SFML/Graphics/RectangleShape.hpp"

GameRules::GameRules(Grid& grid) : grid(grid) {}

int GameRules::countAliveNeighbours(int x, int y) {
    static const std::vector<std::pair<int,int>> offsets = {
        {-1,-1}, {0,-1}, {1,-1},
        {-1, 0},         {1, 0},
        {-1, 1}, {0, 1}, {1, 1}
    };

    int count = 0;
    for (auto [dx, dy] : offsets) {
        auto nx = x + dx;
        auto ny = y + dy;
        if (nx >= 0 && nx < grid.gridWidth && ny >= 0 && ny < grid.gridHeigth) {
            if (grid.get({nx, ny})) count++;
        }
    }
    return count;
}

void GameRules::update() {
    std::unordered_map<std::pair<int,int>, Cell, PairHash> nextState;

    std::ranges::for_each(std::ranges::views::iota(0, grid.gridWidth * grid.gridHeigth), [&](int i) {
        int x = i % grid.gridWidth;
        int y = i / grid.gridWidth;

        bool alive = grid.get({x, y});
        int neighbours = countAliveNeighbours(x, y);

        bool nextAlive = false;
        if (alive && (neighbours == 2 || neighbours == 3)) nextAlive = true;
        if (!alive && neighbours == 3) nextAlive = true;

        nextState[{x, y}] = Cell{nextAlive};
    });

    grid.grid = std::move(nextState);
}

void GameRules::render(sf::RenderWindow& window) {
    sf::RectangleShape cellShape;
    cellShape.setSize({static_cast<float>(grid.cellwidth), static_cast<float>(grid.cellHeight)});

    std::ranges::for_each(std::ranges::views::iota(0, grid.gridWidth * grid.gridHeigth), [&](int i) {
        int x = i % grid.gridWidth;
        int y = i / grid.gridWidth;

        auto& cell = grid.grid[{x, y}];
        cellShape.setPosition(sf::Vector2f(x * grid.cellwidth, y * grid.cellHeight));

        if (cell.alive)
            cellShape.setFillColor(sf::Color::White);
        else
            cellShape.setFillColor(sf::Color::Black);

        window.draw(cellShape);
    });
}
