#pragma once
#include <SFML/Graphics.hpp>

#include <limits>


struct Cell
{
    sf::Vector2i index;
    Cell* parent = nullptr;

    uint16_t f_cost = std::numeric_limits<uint16_t>::max();
    uint16_t g_cost = std::numeric_limits<uint16_t>::max();
    uint16_t h_cost = 0;

    /*
    0 = Empty
    1 = Wall
    2 = Checkpoint
    */
    char type = 0;
};
