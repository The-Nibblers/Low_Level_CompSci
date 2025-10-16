//
// Created by jenso on 15/10/2025.
//

#ifndef LOW_LEVEL_SETUP_GRID_H
#define LOW_LEVEL_SETUP_GRID_H
#include <functional>
#include <algorithm>
#include <ranges>

struct PairHash {
    size_t operator()(const std::pair<int,int>& p) const noexcept {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};

struct Cell {
    bool alive;
};


class Grid {
public:
    Grid(int windowWidth, int windowHeight);
    bool get(std::pair<int,int> coords);
    void set(std::pair<int,int> coords, bool alive);
    void clear();
    void gridSetup();
private:
    std::unordered_map<std::pair<int,int>, Cell, PairHash> grid;
    int gridWidth= 30;
    int gridHeigth = 30;
    float cellwidth;
    float cellHeight;
    int windowWidth;
    int windowHeight;

};


#endif //LOW_LEVEL_SETUP_GRID_H