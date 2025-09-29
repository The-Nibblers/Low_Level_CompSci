//
// Created by jenso on 29/09/2025.
//

#ifndef LOW_LEVEL_SETUP_SPATIALHASH_H
#define LOW_LEVEL_SETUP_SPATIALHASH_H
#include <unordered_map>

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>



class SpatialHash {

public:
    SpatialHash();

    void insertObject(object&);
    void removeObject(object&);

private:
    //TODO: change object
    std::unordered_map<sf::Vector2f, std::vector<Object&>> grid;
};


#endif //LOW_LEVEL_SETUP_SPATIALHASH_H