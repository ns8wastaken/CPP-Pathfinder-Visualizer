#pragma once
#include <SFML/Graphics.hpp>


struct Settings
{
    static constexpr uint16_t TileSize = 75;
    static constexpr size_t   SizeX    = 10;
    static constexpr size_t   SizeY    = 10;

    static constexpr int cost_orthogonal = 10;
    static constexpr int cost_diagonal   = 14;
};

struct Colors
{
    static const sf::Color Lines;

    static const sf::Color Empty;
    static const sf::Color Wall;
    static const sf::Color Start;
    static const sf::Color End;
    static const sf::Color Checkpoint;

    static const sf::Color Search;
    static const sf::Color Visited;
    static const sf::Color Path;
};
