//
// Created by jenso on 29/09/2025.
//

#ifndef LOW_LEVEL_SETUP_SPATIALHASH_H
#define LOW_LEVEL_SETUP_SPATIALHASH_H
#include <unordered_map>

#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include "balls.hpp"

struct PairHash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

class SpatialHash {

public:
    SpatialHash();

    void insertObject(Ball*);
    void removeObject(Ball*);

private:
    std::unordered_map<std::pair<int,int>, std::vector<Ball*>, PairHash> grid;
    sf::Vector2i windowSize;
};


#endif //LOW_LEVEL_SETUP_SPATIALHASH_H